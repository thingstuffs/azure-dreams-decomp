#include "common.h"

typedef struct S_8195EE48_0 {
    u8 pad_00[0x3C];
    s16 unk_3C;
    u8 pad_3E[0xA];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    u8 pad_4E[0x12];
    s16 unk_60;
    s16 unk_62;
} S_8195EE48_0;   /* arg0 in func_8195EE48 */

typedef struct S_8195EE48_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8195EE48_1;   /* arg1 in func_8195EE48 */



extern s32 rand();
extern void func_8002472C(void) __attribute__((noreturn));
extern u16 D_80027330[5];

void func_8195EE48(S_8195EE48_0 *arg0, S_8195EE48_1 *arg1)
{
    s32 temp_a0;
    s16 temp_a1;
    s16 temp_v0;
    register u16 counter ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    counter = D_80027330[0];
    temp_a0 = arg0->unk_48;
    D_80027330[0] = counter + 1;
    if (temp_a0 == 0) {
        temp_a1 = arg0->unk_4C;
        if (temp_a1 > 0) {
            temp_a0 = arg0->unk_3C;
            arg0->unk_3C =
                (u16)arg0->unk_3C +
                ((arg0->unk_62 + arg0->unk_60 - temp_a0) / temp_a1);
            arg1->unk_08.at02.v =
                ((u16)arg0->unk_3C + (rand(temp_a0, temp_a1) & 3)) - 2;
        }
        temp_v0 = (u16)arg0->unk_4C - 1;
        arg0->unk_4C = temp_v0;
        if ((temp_v0 << 16) <= 0) {
            arg0->unk_4C = 0x20;
            arg0->unk_48 = (u16)arg0->unk_48 + 1;
            func_8002472C();
        }
    } else {
        arg1->unk_00 += arg1->unk_0C;
        arg1->unk_04 += arg1->unk_10;
        arg1->unk_08.at00.v += arg1->unk_14;
    }
}

/* MECHANISM: An s32-held 0x48 condition produces retail's signed load and exact s0/s1/ra frame.
   Reading the counter first preserves retail emission order; a guarded $v1 runtime-value pin
   fixes the final counter/base coloring while the natural CFG retains both delay-slot stores. */
