typedef struct { int a; int b; short s; unsigned char c; } S;
typedef struct { int x; int y; } GS;
extern int G;
extern int H[4];
extern GS GSV;
extern short SG;
/* A: struct store through a pointer, then a bare global scalar load.  sched.c true_dependence:
   in_struct+varying vs !in_struct+fixed -> assumed independent -> the load may move above the store. */
int fA(S *p, int v) { p->a = v; return G; }
/* B: the same store spelled as a cast (not in_struct) -> conflict assumed -> store then load. */
int fB(S *p, int v) { *(int *)((char *)p + 0) = v; return G; }
/* C: the global spelled as an array element (in_struct, fixed) -> conflict assumed. */
int fC(S *p, int v) { p->a = v; return H[0]; }
/* D: the global spelled as a struct member (in_struct, fixed) -> conflict assumed. */
int fD(S *p, int v) { p->a = v; return GSV.x; }
/* E: QImode store never gets the exemption. */
int fE(S *p, int v) { p->c = v; return G; }
/* F: a short (HImode) struct store vs a bare global -> exemption applies. */
int fF(S *p, int v) { p->s = v; return G; }
/* G/H: the reverse direction - a bare global store, then a struct load through a pointer. */
int fG(S *p, int v) { G = v; return p->a; }
int fH(S *p, int v) { G = v; return *(int *)((char *)p + 0); }
