extern short flags[2];
extern void tick(unsigned int);
void probe(unsigned int n)
{
    unsigned int i;
    flags[0] = 1;
    i = 1;
    while (i < n) { tick(i); ++i; }
}
