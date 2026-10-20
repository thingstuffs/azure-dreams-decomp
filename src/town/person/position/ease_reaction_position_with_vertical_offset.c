#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/position_views.h"

void initialize_reaction_data_and_timer_13(void *);                            /* extern */


typedef struct S_800CA134_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800CA134_0;   /* arg0 in ease_reaction_position_with_vertical_offset */

typedef struct S_800CA134_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 n; u16 v; } unk_0A;   /* accessed as both */
} S_800CA134_1;   /* arg1 in ease_reaction_position_with_vertical_offset */

   /* target in ease_reaction_position_with_vertical_offset */

typedef struct S_800CA134_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800CA134_3;   /* target_table->unk_08 in ease_reaction_position_with_vertical_offset */

/* Decrement the lifetime and ease the position toward the target with a vertical offset. */
void ease_reaction_position_with_vertical_offset(void *state, void *position) {
    ObjectNodeHeader *target_table;
    s32 x_delta;
    s32 y_delta;
    u16 ticks_left;

    ticks_left = ((S_800CA134_0 *)state)->unk_6C - 1;
    ((S_800CA134_0 *)state)->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        initialize_reaction_data_and_timer_13(state);
        return;
    }
    target_table = &D_80083498;
    x_delta = ((S_800CA134_3 *)(target_table->unk_08))->unk_02
        - ((S_800CA134_1 *)position)->unk_02;
    (*(s16 *)((u8 *)position + (2))) = (s16) ((u16) ((S_800CA134_1 *)position)->unk_02 + (x_delta / 4));
    y_delta = ((S_800CA134_3 *)(target_table->unk_08))->unk_06
        - ((S_800CA134_1 *)position)->unk_06;
    (*(s16 *)((u8 *)position + (6))) = (s16) ((u16) ((S_800CA134_1 *)position)->unk_06 + (y_delta / 4));
    {
        SignedHeightView *target;
        s32 z_step;
        s32 target_z;

        target = target_table->unk_08;
        z_step = ((S_800CA134_1 *)position)->unk_0A.n;
        target_z = target->unk_0A;
        z_step += 0xD0;
        z_step = target_z - z_step;
        ((S_800CA134_1 *)position)->unk_0A.n += z_step / 4;
    }
}
