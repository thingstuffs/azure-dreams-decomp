extern void sink(unsigned int);
void probe(unsigned int *p, unsigned int n, unsigned int m)
{
    unsigned int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            p[j] = i;
            sink(i);
        }
    }
}
