void probe(void)
{
    unsigned int *p = (unsigned int *)0x1f800000;
    unsigned int a = p[0];
    a += a;
    a += a;
    a += a;
    p[2] = a;
}
