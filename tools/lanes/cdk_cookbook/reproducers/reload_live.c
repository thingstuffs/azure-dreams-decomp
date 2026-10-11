struct Pair { unsigned int x, y, z; };
unsigned int probe(struct Pair *p, unsigned int value)
{
    p->x = value;
    p->y = p->x + 1;
    return p->x + value;
}
