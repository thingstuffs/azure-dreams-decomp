#include "common.h"

typedef struct S_80083120 {
    s16 field0;
    s16 field2;
    s16 field4;
    s16 field6;
} S_80083120;

extern S_80083120 D_80083120[8];
extern int D_80082EC0[128];
extern int D_80083110[4];
extern volatile s16 D_80013714[6];

extern void func_8003DB4C(int *p, int n);
extern void func_800499BC(void);
extern void func_8004437C(s32 a0, s32 a1);
extern void func_8004425C(s32 a0);

/* Clears global state blocks and a flag, then reinitializes subsystem defaults. */
void func_8003D8B0(void)
{
    s32 word_index;

    func_8003DB4C((int *)D_80083120, 0x10);
    func_8003DB4C(D_80082EC0, 0x80);

    {
        int *state_words = D_80083110;
        for (word_index = 3; word_index >= 0; word_index--) {
            *(state_words + word_index) = 0;
        }
    }

    D_80013714[0] = 0;

    func_800499BC();
    func_8004437C(0x2A, 0);
    func_8004425C(0);
}
