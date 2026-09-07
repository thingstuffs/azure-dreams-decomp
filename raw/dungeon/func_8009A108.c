#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern u8 D_80083780[16];
extern s32 D_800832B4[3];
extern u8 D_800DCE60[16];
extern u16 D_80013714;

extern void func_8004D0C8(void *, void *);
extern void func_8004D7A8(s32);
extern void func_8004D294(s32, void *, s32);

void *func_8009F868(void)
{
    register u8 *state ASM_REG("$5");
    u8 *entry;
    u8 kind;
    u16 next;

loop:
    state = (u8 *)0x80013710;
    ASM_KEEP(state);
    entry = FIELD(state, u8 *, 0xC) + FIELD(state, u16, 0xA) * 2;
    kind = entry[1];

    if (kind == 0) {
        if (D_80013714 & 8) {
            FIELD(state, u16, 4) |= 0x10;
            return 0;
        }
        FIELD(state, u16, 0xA) = 0;
        FIELD(state, u16, 4) &= 0xC;
        func_8004D0C8(D_80083780, state);
        D_800832B4[0] = 0;
        func_8004D7A8(1);
        func_8004D294(0, D_800DCE60, 8);
        return 0;
    }

    if (kind == 0xD0) {
        FIELD(state, u16, 8) = 0;
        FIELD(state, u16, 0xA) += (s8)entry[0];
        goto loop;
    }

    if ((s8)entry[0] < 0 ||
        (next = FIELD(state, u16, 8) + 1,
         FIELD(state, u16, 8) = next,
         (u16)next >= entry[0])) {
        FIELD(state, u16, 8) = 0;
        FIELD(state, u16, 0xA)++;
    }
    return entry;
}

/* MECHANISM: The apparent func_8009F870/func_8009F978 calls are local loop and epilogue edges.
   A literal 0x80013710 state base held in guarded $a1 removes the two-word call-site rematerialization.
   Natural locals then reproduce the 0x18 frame, sole $ra save, CFG, widths, and all delay slots. */
