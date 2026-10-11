extern void step(void);
extern void other(void);
void probe(unsigned int *p)
{
    unsigned int a = p[0], b = p[1];
    if (p[18]) step(); else other();
    p[2] = a + 1;
    p[3] = a + 2;
    p[4] = a + 3;
    p[5] = a + 4;
    p[6] = a + 5;
    p[7] = a + 6;
    p[15] = b + 1;
    p[16] = b + 2;
    p[17] = b + 3;
}
