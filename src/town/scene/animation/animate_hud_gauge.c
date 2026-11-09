#include "common.h"
#include "town/scene/animation.h"

typedef struct S_80813294_0 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
} S_80813294_0;   /* arg0 in animate_hud_gauge */

typedef struct S_80813294_1 {
    u8 pad_00[0x16];
    u16 unk_16;
} S_80813294_1;   /* arg2 in animate_hud_gauge */

typedef struct S_80813294_2 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_80813294_2;   /* ((S_80813294_0 *)arg0)->unk_00 in animate_hud_gauge */

/* Waits for parent state 4, raises the gauge value for ten updates, then lowers it to zero. */
void animate_hud_gauge(S_80813294_0 *record, s32 unused, S_80813294_1 *value_record) {
    s32 state;

    state = record->unk_04;
    record->unk_06 = record->unk_06 - 1;
    switch (state) {
    case 0:
        if (((S_80813294_2 *)(record->unk_00))->unk_5C == 4) {
            record->unk_06 = 10;
            record->unk_04 = record->unk_04 + 1;
        }
        break;
    case 1:
        value_record->unk_16 = value_record->unk_16 + 0x40;
        if (record->unk_06 <= 0) {
            record->unk_04 = record->unk_04 + 1;
        }
        break;
    case 2:
        value_record->unk_16 = value_record->unk_16 - 0x18;
        if (value_record->unk_16 < 0x18U) {
            value_record->unk_16 = 0;
            record->unk_04 = 0;
        }
        break;
    }
}
