#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#ifndef _WIN32
#include <sys/mman.h>
#endif
#include <elf-module.h>

#define VPRINTF(fmt, a...) do { \
    if (verbose) \
	printf(fmt, ##a); \
} while(0)

/* Module table entry */
typedef struct module {
    struct module *next;
    char *name;
} module_t;

/* Symbol table entry */
typedef struct symbol {
    struct symbol *next;
    module_t *module;
    void *addr;
    char name[0];
} symbol_t;

/* Symbol table */
static symbol_t *symtab = NULL;

/* Module table */
static module_t core_module = {
    .name = "core"
};

static module_t *modtab = &core_module;

/* Program options */
static int verbose = 0;

static void die(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

static void *load_file(char *file, size_t *size)
{
    FILE *f = fopen(file, "rb");
    void *result;

    if (!f)
	return NULL;

    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);
    result = malloc(*size);

    if (!result)
	goto out;

    if (fread(result, 1, *size, f) < *size) {
	free(result);
	result = NULL;
	goto out;
    }

out:
    fclose(f);
    return result;
}

/*
 * Define new symbol. If elf is NULL, it's core API function.
 */
static int define_symbol(elf_module_t *elf, char *name, void *addr)
{
    symbol_t *sym = symtab;
    module_t *module = elf ? elf_module_get_data(elf) : &core_module;

    VPRINTF("define symbol %s in %s.\n", name, module->name);

    while (sym) {
	if (!strcmp(sym->name, name))
	    die("Duplicate definition of `%s'.", name);
	sym = sym->next;
    }

    sym = (symbol_t *) malloc(sizeof(*sym) + strlen(name) + 1);
    strcpy(sym->name, name);
    sym->addr = addr;
    sym->module = module;
    sym->next = symtab;
    symtab = sym;

    return 0;
}

static symbol_t *lookup_symbol(char *name)
{
    symbol_t *sym = symtab;

    while (sym) {
	if (!strcmp(sym->name, name))
	    return sym;
	sym = sym->next;
    }
    return NULL;
}

static module_t *lookup_module(char *name)
{
    module_t *mod = modtab;

    while (mod) {
	if (!strcmp(mod->name, name))
	    return mod;
	mod = mod->next;
    }
    return NULL;
}

static void load_module(char *module);

/*
 * Resolve symbol callback.
 *
 * If symbol is external(starts with 'MODULENAME__'), calls
 * load_module, if needed.
 */
static void *resolve_symbol(elf_module_t *elf, char *name)
{
    char *ptr;
    symbol_t *sym;

    /* load module, if needed */
    VPRINTF("resolve symbol: %s\n", name);
    if ((ptr = strstr(name, "__")) != NULL) {
	char *modname = malloc(ptr - name + 1);

	strncpy(modname, name, ptr - name);
	modname[ptr - name] = '\0';

	VPRINTF("external symbol %s from %s.\n", name, modname);
	if (strcmp(name, modname) && !lookup_module(modname))
	    load_module(modname);
    }

    sym = lookup_symbol(name);

    if (sym) {
	VPRINTF("%s found in %s\n", name, sym->module->name);

	return sym->addr;
    } else {
	die("Undefined symbol `%s'.", name);

	return NULL;
    }
}

static void *allocate(size_t size)
{
#if _WIN32
    return malloc(size);
#else
    return mmap(NULL, size,
	PROT_READ | PROT_WRITE | PROT_EXEC,
	MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
}

static void load_module(char *module)
{
    int err;
    size_t size;
    void *core;
    char fullname[128];
    elf_module_t elf;
    module_t *mod = (module_t *) malloc(sizeof(module_t));
    elf_module_link_cbs_t link = {
	.define = define_symbol,
	.resolve = resolve_symbol,
    };
    void *data;

    VPRINTF("Loading module %s\n", module);
    mod->name = module;

    sprintf(fullname, "%s", module);

    data = load_file(fullname, &size);
    if (!data)
	die("Can not load `%s'\n", module);

    err = elf_module_init(&elf, data, size);
    if (err < 0)
	die("Not an executable.");

    elf_module_set_data(&elf, mod);

    core = allocate(size);
    if (!core)
	die("Not enough memory.");

    err = elf_module_load(&elf, core, &link);
    if (err < 0)
	die("Error loading module.");

    free(data);

    mod->next = modtab;
    modtab = mod;
}
/*
int
main(int argc, char **argv)
{
    int i;
    int (*module_main)(void);

    // standard definitions(core API) 
    define_symbol(NULL, "printf", printf);
    
    if (argc < 2)
	die("Usage: %s <module__function> [ options ] [ mod1 mod2 mod3 ... ]", argv[0]);

    // load and link modules and set options, if any 
    for (i = 2; i < argc; i++) {
	if (!strcmp(argv[i], "-v"))
	    verbose = 1;
	else
	    load_module(argv[i]);
    }

    // call module_main 
    module_main = resolve_symbol(NULL, argv[1]);
    module_main();

    return 0;
}*/
