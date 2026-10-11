extern void sink(unsigned int);
unsigned int probe(unsigned int x, unsigned int flag)
{
    unsigned int copy = x;
    if (flag) sink(x);
    return copy + 1;
}
