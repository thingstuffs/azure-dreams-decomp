extern void consume(unsigned int, unsigned int);
void probe(unsigned int *p, unsigned int value)
{
    unsigned int raw = p[0];
    unsigned int tag;
    p[2] = raw;
    tag = raw & 0xff000000U;
    p[1] = value;
    p[3] = tag;
    consume(tag, value + 2);
}
