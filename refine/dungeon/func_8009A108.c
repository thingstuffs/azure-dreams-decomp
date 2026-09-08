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

/* Advances a timed sequence, following relative jumps and handling its end. */
void *func_8009F868(void)
{
    u8 *state;
    u8 *entry;
    u8 opcode;
    u16 elapsed_ticks;

loop:
    state = (u8 *)0x80013710;
    ASM_KEEP(state);
    entry = ((S_8009F868_0 *)state)->unk_0C + ((S_8009F868_0 *)state)->unk_0A * 2;
    opcode = entry[1];

    if (opcode == 0) {
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

    if (opcode == 0xD0) {
        ((S_8009F868_0 *)state)->unk_08 = 0;
        ((S_8009F868_0 *)state)->unk_0A += (s8)entry[0];
        goto loop;
    }

    if ((s8)entry[0] < 0 ||
        (elapsed_ticks = ((S_8009F868_0 *)state)->unk_08 + 1,
         ((S_8009F868_0 *)state)->unk_08 = elapsed_ticks,
         (u16)elapsed_ticks >= entry[0])) {
        ((S_8009F868_0 *)state)->unk_08 = 0;
        ((S_8009F868_0 *)state)->unk_0A++;
    }
    return entry;
}

