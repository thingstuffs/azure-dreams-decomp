#include "common.h"

typedef struct S_80813294_0 {
    void * unk_00;
    union { s16 s; u16 u; u16 p; } unk_04;   /* accessed as both */
    u16 unk_06;
} S_80813294_0;   /* arg0 in func_8052DE94 */

typedef struct S_80813294_1 {
    u8 pad_00[0x16];
    union { u16 s; u16 u; } unk_16;   /* accessed as both */
} S_80813294_1;   /* arg2 in func_8052DE94 */

typedef struct S_80813294_2 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_80813294_2;   /* ((S_80813294_0 *)arg0)->unk_00 in func_8052DE94 */

void func_8052DE94(S_80813294_0 *record, s32 unused, S_80813294_1 *value_record) {
    s32 state;

    state = record->unk_04.s;
    record->unk_06 = record->unk_06 - 1;
    switch (state) {
    case 0:
        if (((S_80813294_2 *)(record->unk_00))->unk_5C == 4) {
            record->unk_06 = 10;
            record->unk_04.p = record->unk_04.u + 1;
        }
        break;
    case 1:
        value_record->unk_16.s = value_record->unk_16.s + 0x40;
        if ((s16)record->unk_06 <= 0) {
            record->unk_04.p = record->unk_04.u + 1;
        }
        break;
    case 2:
        value_record->unk_16.s = value_record->unk_16.s - 0x18;
        if (value_record->unk_16.u < 0x18U) {
            value_record->unk_16.s = 0;
            record->unk_04.s = 0;
        }
        break;
    }
}
