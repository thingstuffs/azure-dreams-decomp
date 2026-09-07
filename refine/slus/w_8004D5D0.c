#include "common.h"

typedef struct {
    short pad0;
    short f2;
    short pad4;
    short f6;
    short pad8;
    short fA;
} S_8004D5D0_D80083780;

extern S_8004D5D0_D80083780 D_80083780;
extern void func_8004D4AC(void);

/* Copies rotation angles from D_80083780 into D_80083178 and builds matrices. */
void func_8004D5D0(void)
{
    D_80083178.state_94.v[2].x = D_80083780.f2;
    D_80083178.state_94.v[2].y = D_80083780.f6;
    D_80083178.state_94.v[2].z = D_80083780.fA;
    func_8004D4AC();
}
