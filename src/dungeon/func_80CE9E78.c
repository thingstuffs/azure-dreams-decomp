#include "common.h"
#include "records/Rec_func_80172CC0_arg0.h"
#include "records/Rec_D_80082E80.h"



typedef struct S_80173678_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
} S_80173678_1;   /* arg3 in func_80173678 */




extern void func_80047784();
extern s16 D_80083228[5];
extern u8 D_80175E9C[];
extern u8 D_80175EA4[];
extern u8 D_80175EAC[];

/* Reset display state and apply the kind-specific directional entry when its table changes. */
void func_80173678(Rec_func_80172CC0_arg0 *state, s32 unused, Rec_D_80082E80 *display, S_80173678_1 *entity) {
    s32 kind;
    u8 *direction_table;
    u8 *previous_table;

    state->unk_9A.as_s8 = 0x10;
    state->unk_9B.as_s8 = 0;
    kind = entity->unk_48;
    if (kind == 0xE) {
        goto case_14;
    }
    if ((s32) kind < 0xF) {
        if (kind == 0xD) {
            goto case_13;
        }
        return;
    }
    if (kind == 0xF) {
        goto case_15;
    }
    return;

case_13:
    direction_table = D_80175E9C;
    previous_table = display->unk_2C.as_pu8;
    if (previous_table == direction_table) {
        return;
    }
    display->unk_2C.as_pu8 = direction_table;
    func_80047784(display,
                  direction_table[((D_80083228[0] + entity->unk_2A + 0x100) >> 9) & 7],
                  0);
    return;
case_14:
    direction_table = D_80175EA4;
    previous_table = display->unk_2C.as_pu8;
    if (previous_table == direction_table) {
        return;
    }
    display->unk_2C.as_pu8 = direction_table;
    func_80047784(display,
                  direction_table[((D_80083228[0] + entity->unk_2A + 0x100) >> 9) & 7],
                  0);
    return;
case_15:
    direction_table = D_80175EAC;
    previous_table = display->unk_2C.as_pu8;
    if (previous_table == direction_table) {
        return;
    }
    display->unk_2C.as_pu8 = direction_table;
    func_80047784(display,
                  direction_table[((D_80083228[0] + entity->unk_2A + 0x100) >> 9) & 7],
                  0);
}
