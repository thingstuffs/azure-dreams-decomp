#include "modules/town_map_props.h"
#include "common.h"

typedef struct S_800BDFA0_0 {
    u8 pad_00[0x68];
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x36];
    s32 unk_A0;
    s32 unk_A4;
} S_800BDFA0_0;   /* record in initialize_record_visual_state */



void initialize_record_visual_state(S_800BDFA0_0 *record, s32 unused, s32 value) {
    s16 state;

    func_800478B8(value);
    state = record->unk_68.s;
    switch (state) {
    case 0:
        if ((func_800352FC() != 0) && (check_transform_identifier_and_hook(record) != 0)) {
            func_8003DB94(value, record->unk_A4, 0);
            record->unk_68.u++;
        }
        break;
    case 1:
        if ((func_800352FC() == 0) || (check_transform_identifier_and_hook(record) == 0)) {
            record->unk_68.u++;
        }
        break;
    case 2:
        if ((func_800352FC() != 0) && (check_transform_identifier_and_hook(record) != 0)) {
            func_8003DB94(value, record->unk_A0, 0);
            record->unk_68.u++;
        }
        break;
    case 3:
        if ((func_800352FC() == 0) || (check_transform_identifier_and_hook(record) == 0)) {
            record->unk_68.s = 0;
        }
        break;
    }
}
