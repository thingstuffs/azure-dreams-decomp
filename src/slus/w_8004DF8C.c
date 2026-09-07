#include "common.h"

#include "common.h"

typedef void (*FuncPtr)(char *);

extern char *strcpy(char *dst, char *src);
extern char *strcat(char *dst, char *src);
extern char *strrchr(char *s, int c);
extern char D_80083E18[0x100];
extern char D_80071404[];
extern FuncPtr D_800714A4[];
extern s32 D_80081550;
extern s32 D_80081548;
extern s32 D_8008154C;

void func_8004DF8C(char *arg0)
{
    char *base;
    char *p;
    char *dst;
    u32 addr;
    s32 *q;
    FuncPtr handler;

    p = D_80083E18;
    p = p + 1;
    strcpy(p, (D_80083E18[0] = 8, arg0));
    do { } while (0);
    dst = p;
    ASM_KEEP(dst);   /* MATCH pin: slus-diff */
    strcat(dst, D_80071404);
    base = D_80083E18;
    p = strrchr(base, 0);
    *p = 0x19;
    p = p + 1;
    *p = 2;
    p = p - (-1);
    *p = 0x1A;
    p = p + 1;
    q = &D_80081548;
    addr = (u32)q;
    p[1] = (char)(addr >> 8);
    p[2] = (char)(addr >> 16);
    p[0] = (char)addr;
    p[3] = (char)(addr >> 24);
    p = p + 4;
    q = &D_8008154C;
    addr = (u32)q;
    p[1] = (char)(addr >> 8);
    p[2] = (char)(addr >> 16);
    p[0] = (char)addr;
    p[3] = (char)(addr >> 24);
    handler = D_800714A4[D_80081550];
    handler(base);
    q[-1] = 0x2300030C;
    D_8008154C = 0x2300040C;
}
