extern void consume(unsigned int, unsigned int);
void probe(unsigned int *p, unsigned int value)
{
    unsigned int tag = p[0];
    p[2] = tag;
    tag &= 0xff000000U;
    p[1] = value;
    p[3] = tag;
    consume(tag, value + 2);
}
