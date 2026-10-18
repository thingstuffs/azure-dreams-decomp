#include "modules/dungeon_ovl_188298c.h"

void advance_counter_and_propagate_target_flags(void *state, s32 context, Rec_D_80082E80 *target) {
    u16 update_count;
    ovl_188298c_81862B74_S_81862B74_1 *linked_object;

    linked_object = ((ovl_188298c_81862B74_S_81862B74_0 *)state)->unk_00;
    linked_object->unk_14 = (u16) (linked_object->unk_14 + 1);
    func_800478B8(target);
    update_count = ((ovl_188298c_81862B74_S_81862B74_0 *)state)->unk_04 + 1;
    ((ovl_188298c_81862B74_S_81862B74_0 *)state)->unk_04 = update_count;
    if ((s16) update_count == 0xA) {
        spawn_jittered_type_212_effect(((ovl_188298c_81862B74_S_81862B74_0 *)state)->unk_00, context);
    }
    if (target->unk_14.at00_u16.v & 0x6000) {
        ((ovl_188298c_81862B74_S_81862B74_0_pre *)state)[-1].unk_00 = (u16) (((ovl_188298c_81862B74_S_81862B74_0_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
