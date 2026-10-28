#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800232F4_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    void * unk_04;
    u16 * unk_08;
    void * unk_0C;
    u8 pad_10[0x6];
    s16 unk_16;
} S_800232F4_0;   /* obj in update_minigame_outbound_motion */

typedef struct S_800232F4_1 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_800232F4_1;   /* owner in update_minigame_outbound_motion */


extern void format_decimal_field_space_padded(s32 value, s32 width, char *buf);
/* Updates the display value, then moves the object outward and flags it when out of bounds. */
void update_minigame_outbound_motion(void *object)
{
    S_800232F4_0 *obj;
    S_800232F4_1 *owner;
    s16 state;
    register u16 step;

    obj = object;
    state = obj->unk_00.s;
    owner = obj->unk_0C;

    switch (state) {
    case 0:
    step = *obj->unk_08;
    format_decimal_field_space_padded(step * 100, 5,
                  obj->unk_04 + 4);
    if (owner->unk_5C != 3) {
        return;
    }

    if (obj->unk_16 < 120) {
        obj->unk_02.s = -8;
    } else {
        obj->unk_02.s = 8;
    }
    obj->unk_00.u++;
        break;

    case 1:
    obj->unk_16 += obj->unk_02.s;
    obj->unk_16 += obj->unk_02.s >> 2;
    if ((u16)(obj->unk_16 + 8) >= 249) {
        (*(u16 *)((u8 *)obj + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
        break;
    }
}
