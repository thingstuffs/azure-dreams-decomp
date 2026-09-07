#include "common.h"

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

typedef struct S_80173678_0 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80173678_0;   /* arg0 in func_80173678 */

typedef struct S_80173678_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
} S_80173678_1;   /* arg3 in func_80173678 */

typedef struct S_80173678_2 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_80173678_2;   /* arg2 in func_80173678 */



extern void func_80047784();
extern s16 D_80083228[5];
extern u8 D_80175E9C[];
extern u8 D_80175EA4[];
extern u8 D_80175EAC[];

/* Reset display state and apply the kind-specific directional entry when its table changes. */
void func_80173678(S_80173678_0 *state, s32 unused, S_80173678_2 *display, S_80173678_1 *entity) {
    s32 kind;
    u8 *direction_table;
    u8 *previous_table;

    state->unk_9A = 0x10;
    state->unk_9B = 0;
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
    previous_table = display->unk_2C;
    if (previous_table == direction_table) {
        return;
    }
    display->unk_2C = direction_table;
    func_80047784(display,
                  direction_table[((D_80083228[0] + entity->unk_2A + 0x100) >> 9) & 7],
                  0);
    return;
case_14:
    direction_table = D_80175EA4;
    previous_table = display->unk_2C;
    if (previous_table == direction_table) {
        return;
    }
    display->unk_2C = direction_table;
    func_80047784(display,
                  direction_table[((D_80083228[0] + entity->unk_2A + 0x100) >> 9) & 7],
                  0);
    return;
case_15:
    direction_table = D_80175EAC;
    previous_table = display->unk_2C;
    if (previous_table == direction_table) {
        return;
    }
    display->unk_2C = direction_table;
    func_80047784(display,
                  direction_table[((D_80083228[0] + entity->unk_2A + 0x100) >> 9) & 7],
                  0);
}
