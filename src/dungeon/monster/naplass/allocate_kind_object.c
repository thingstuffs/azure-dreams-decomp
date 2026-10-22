#include "dungeon/monster/naplass/allocate_kind_object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/naplass/allocate_kind_object.h"

/* Allocate an object, initialize its parts and kind flags, and return its work area. */
/* Creates Naplass with default frames at D_80162194, applies spawn flags, and attempts valid tile
 * placement. */
void *allocate_kind_object(s16 spawn_flags, s16 value_24, s16 value_25, s16 value_0a)
{
    s32 kind;
    void *obj;
    S_8015E870_2 *part_a;
    SpriteFrameState *part_b;
    S_8015E870_1 *work;
    S_8015E870_4 *actor;
    register s32 flags_14;
    register s32 flags_1c;
    s8 saved_value_24;
    s16 saved_value_0a;
    s8 saved_value_25;
    register void *init_obj;
    register void *init_part_a;

    work = 0;
    saved_value_24 = value_24;
    saved_value_0a = value_0a;
    saved_value_25 = value_25;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8015E870_0 *)obj)->unk_10 = func_8015EA3C;
        work->unk_13 = 0x25;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8015E870_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value_0a;
        part_b = ((S_8015E870_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_value_25;
        actor = work;
        part_b->frameTable = D_80162194;
        part_b->unk_24 = saved_value_24;

        if (kind == 1) {
            flags_14 = work->unk_14 | 0x6000;
            flags_1c = work->unk_1C | 0x6000;
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else if (kind >= 2) {
            flags_14 = work->unk_14 | 0x2000;
            flags_1c = work->unk_1C | 0x2000;
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else {
            init_obj = obj;
            if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                init_part_a = part_a;
                work->unk_1C |= 0x200;
                set_or_clear_actor_status_slot(work, 1,
                              (generate_random_value() & 0x3F) | 0x20);
                part_b->frameTable = D_801621DC;
            }
        }
        init_obj = obj;
        initialize_actor_sprite_and_animation(init_obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_8015EE68;
        part_b->flags |= 0xC;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
