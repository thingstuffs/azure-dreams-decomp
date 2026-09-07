#include "common.h"

typedef void (*FuncPtr_8004DCEC)(char *);
extern FuncPtr_8004DCEC D_800714A4[];
extern int D_80081550;
extern char D_80080B6C[16];

/* Dispatches to the handler selected by D_80081550 (a jump table of per-mode
 * callbacks at D_800714A4), passing it the shared work buffer D_80080B6C. */
void func_8004DCEC(void)
{
    FuncPtr_8004DCEC handler;
    handler = D_800714A4[D_80081550];
    do { } while (0);
    handler(D_80080B6C);
}
