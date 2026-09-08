#include "common.h"

typedef struct S_8009F868_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u16 unk_0A;
    u8 * unk_0C;
} S_8009F868_0;   /* state in func_8009F868 */



extern u8 D_80083780[16];
extern s32 D_800832B4[3];
extern u8 D_800DCE60[16];
extern u16 D_80013714;

extern void func_8004D0C8(void *, void *);
extern void func_8004D7A8(s32);
extern void func_8004D294(s32, void *, s32);

void *func_8009F868(void)
{
    u8 *state;
    u8 *entry;
    u8 kind;
    u16 next;

loop:
    state = (u8 *)0x80013710;
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    entry = ((S_8009F868_0 *)state)->unk_0C + ((S_8009F868_0 *)state)->unk_0A * 2;
    kind = entry[1];

    if (kind == 0) {
        if (D_80013714 & 8) {
            ((S_8009F868_0 *)state)->unk_04 |= 0x10;
            return 0;
        }
        ((S_8009F868_0 *)state)->unk_0A = 0;
        ((S_8009F868_0 *)state)->unk_04 &= 0xC;
        func_8004D0C8(D_80083780, state);
        D_800832B4[0] = 0;
        func_8004D7A8(1);
        func_8004D294(0, D_800DCE60, 8);
        return 0;
    }

    if (kind == 0xD0) {
        ((S_8009F868_0 *)state)->unk_08 = 0;
        ((S_8009F868_0 *)state)->unk_0A += (s8)entry[0];
        goto loop;
    }

    if ((s8)entry[0] < 0 ||
        (next = ((S_8009F868_0 *)state)->unk_08 + 1,
         ((S_8009F868_0 *)state)->unk_08 = next,
         (u16)next >= entry[0])) {
        ((S_8009F868_0 *)state)->unk_08 = 0;
        ((S_8009F868_0 *)state)->unk_0A++;
    }
    return entry;
}

/* MECHANISM: The apparent func_8009F870/func_8009F978 calls are local loop and epilogue edges.
   A literal 0x80013710 state base held in guarded $a1 removes the two-word call-site rematerialization.
   Natural locals then reproduce the 0x18 frame, sole $ra save, CFG, widths, and all delay slots. */
