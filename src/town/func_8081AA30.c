#include "common.h"

typedef struct S_80024A30_0_pre {
    u16 unk_00;
} S_80024A30_0_pre;   /* the 0x2 bytes before arg0 in func_80024A30, addressed as arg0[-1] */

typedef struct S_80024A30_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80024A30_0;   /* arg0 in func_80024A30 */

typedef struct S_80024A30_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80024A30_1;   /* temp_v0 in func_80024A30 */



extern s32 D_800814A0[3];

/* Waits for a trigger flag, then decreases the level and sets completion flags. */
void func_80024A30(void *state) {
    S_80024A30_1 *trigger;
    s16 phase;
    u16 phase_bits;
    s32 level;

    trigger = ((S_80024A30_0 *)state)->unk_04;
    phase = ((S_80024A30_0 *)state)->unk_00.s;
    phase_bits = *(volatile u16 *)state;

    switch (phase) {
    case 0:
        if (trigger->unk_0C & 2) {
            ((S_80024A30_0 *)state)->unk_00.u = phase_bits + 1;
        }
        break;

    case 1:
        level = ((S_80024A30_0 *)state)->unk_08 + 0xFFF7F7F8U;
        ((S_80024A30_0 *)state)->unk_08 = level;
        if (level <= 0x80808) {
            ((S_80024A30_0_pre *)state)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
        break;
    }

    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
