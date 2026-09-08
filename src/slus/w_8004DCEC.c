#include "common.h"

typedef void (*FuncPtr_8004DCEC)(char *);
extern FuncPtr_8004DCEC D_800714A4[];
extern int D_80081550;
extern char D_80080B6C[16];

/* Calls the selected mode handler with the shared work buffer. */
void func_8004DCEC(void)
{
    FuncPtr_8004DCEC handler;
    handler = D_800714A4[D_80081550];
    do { } while (0);
    handler(D_80080B6C);
}
