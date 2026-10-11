extern short flags[2];
extern void tick(unsigned int);
void probe(unsigned int n)
{
    unsigned int i = 1;
    flags[0] = 1;
    while (i < n) { tick(i); ++i; }
}
