extern void sink(unsigned int);
unsigned int probe(unsigned int x, unsigned int flag)
{
    if (flag) sink(x);
    return x + 1;
}
