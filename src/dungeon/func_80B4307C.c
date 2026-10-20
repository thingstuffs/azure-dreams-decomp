#include "modules/dungeon_resource12_slot0.h"
#include "shared/sprite_frame_state.h"

void *func_8017087C(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    R12_8017087C_Work *work;
    void *obj;
    R12_8017087C_S_8017087C_1 *part_a;
    SpriteFrameState *part_b;
    void *resource;
    R12_8017087C_Work *actor;
    s32 left;
    s32 right;
    s8 held_a;
    s16 held_c;
    s8 held_b;
    void *call_a1;

    work = 0;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (R12_8017087C_Work *)((u8 *)obj + 0x20);
        ((R12_8017087C_S_8017087C_0 *)obj)->unk_10 = ((u8 *)create_directional_template_effect);
        work->byte13 = 0xC;
        register_node(obj, project_sprite_chain);

        resource = ((u8 *)D_80175A54);
        part_a = ((R12_8017087C_S_8017087C_0 *)obj)->unk_08;
        part_a->unk_0A = held_c;
        part_b = ((R12_8017087C_S_8017087C_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = work;
        part_b->frameTable = resource;
        part_b->unk_24 = held_a;

        if (kind == 1) {
            left = work->flags14 | 0x6000;
            right = work->flags1c | 0x6000;
            work->flags14 = left;
            work->flags1c = right;
        } else if (kind >= 2) {
            left = work->flags14 | 0x2000;
            right = work->flags1c | 0x2000;
            work->flags14 = left;
            work->flags1c = right;
        } else {
            call_a1 = obj;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(work->flags14 & 0x200)) {
                    call_a1 = part_a;
                    left = generate_random_value();
                    call_a1 = obj;
                    if (left & 1) {
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = ((u8 *)D_80175A9C);
                    }
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, spawn_flags);
        actor->byte9a = 0xFF;
        actor->byte9c = -1;
        actor->ptr8c = ((void *)update_actor_state_and_select_target);
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
