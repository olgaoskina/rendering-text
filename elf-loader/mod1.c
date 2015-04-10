extern char *mod2__get_name(void);
extern int mod2__var;

static void
call_mod2(void)
{
    printf("calling function from mod2....\n");
    printf("mod2__var: %i\n", mod2__var);
    printf("response: %s\n", mod2__get_name());
}

int
mod1__main(void)
{
    int i;

    printf ("Module 1 selftest: ");

    for (i = 0; i < 10; i++)
	printf("%i ", i);

    printf ("... module 1 is ok\n");

    call_mod2();

    return 1025;
}
