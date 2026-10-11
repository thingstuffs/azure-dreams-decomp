extern void consume(unsigned int, unsigned int);
void probe(unsigned int *p, unsigned int value)
{
    unsigned int tag;
    tag = p[0];
    tag &= 0xff000000U;
    p[1] = value;
    consume(tag, value + 2);
}
