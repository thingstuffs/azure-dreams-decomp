#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "dungeon/monster/naplass/allocate_kind_object.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/naplass/allocate_kind_object.h"

/* Allocate an object, initialize its parts and kind flags, and return its work area. */
/* Creates Naplass with default frames at D_80162194, applies spawn flags, and attempts valid tile
 * placement. */
void *allocate_kind_object(s16 spawn_flags, s16 value_24, s16 value_25, s16 value_0a)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
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
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = func_8015EA3C;
        work->unk_13 = MONSTER_NAPLASS;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_value_0a;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_value_25;
        actor = work;
        part_b->frameTable = D_80162194;
        part_b->tile_x = saved_value_24;

        if (kind == 1) {
            flags_14 = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags_1c = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else if (kind >= 2) {
            flags_14 = work->unk_14 | ACTOR_CLASS_ENABLED;
            flags_1c = work->unk_1C | ACTOR_PLAYER_SIDE;
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else {
            init_obj = obj;
            if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                init_part_a = part_a;
                work->unk_1C |= ACTOR_ASLEEP;
                set_or_clear_actor_status_slot(work, STATUS_SLEEP,
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
