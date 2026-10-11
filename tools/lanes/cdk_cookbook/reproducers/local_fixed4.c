void probe(void)
{
    unsigned int *p = (unsigned int *)0x1f800000;
    unsigned int a = p[0], b = p[1];
    unsigned int c = p[2];
    a += a;
    a += a;
    a += a;
    p[2] = a;
    p[3] = b;
    p[4] = c;
}
