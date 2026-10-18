#include "modules/dungeon_ovl_19a332c.h"

void step_and_clamp_entry_index(void *object, s16 *index_step, s32 min_index, s32 max_index) {
    s16 step;
    s32 shifted_index;
    u32 clamp_flags;
    u8 index;
    ovl_19a332c_81984AF4_S_81984AF4_0 *obj = object;
    s32 initial_index = obj->unk_04.s;
    ovl_19a332c_81984AF4_S_81984AF4_1 *owner = obj->unk_08;

    obj->unk_00 =
        owner->unk_0C + (initial_index * 22);
    step = *index_step;
    if (step > 0) {
        obj->unk_04.u = obj->unk_04.u + 1;
    } else if (step < 0) {
        obj->unk_04.u =
            obj->unk_04.u - 1;
    }
    index = (u8)obj->unk_04.s;
    shifted_index = index << 24;
    if ((s8)index < (s16)min_index) {
        clamp_flags = obj->unk_14.s | 0x4000;
        obj->unk_04.s = min_index;
        obj->unk_14.u = clamp_flags;
        return;
    }
    if ((s8)index > (s16)max_index) {
        clamp_flags = obj->unk_14.s | 0x4000;
        obj->unk_04.s = max_index;
        obj->unk_14.u = clamp_flags;
        return;
    }
    obj->unk_14.u &= 0xBFFF;
}
