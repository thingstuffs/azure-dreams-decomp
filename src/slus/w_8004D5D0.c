#include "common.h"

/* func_8004D5D0 -- copies three rotation/angle halfwords from D_80083780
 * (0x2,0x6,0xA) into the D_80083178 dispatch table (0xA4,0xA6,0xA8), then
 * builds matrices via func_8004D4AC. Uses the canonical game.h S_80083178. */
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

void func_8004D5D0(void)
{
    D_80083178.state_94.v[2].x = D_80083780.f2;
    D_80083178.state_94.v[2].y = D_80083780.f6;
    D_80083178.state_94.v[2].z = D_80083780.fA;
    func_8004D4AC();
}
