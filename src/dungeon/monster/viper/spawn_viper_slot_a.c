#include "shared/object_node.h"
#include "modules/dungeon_ovl_7f1d5800.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_7f1d5800.h"

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Viper with default frames at D_80150A7C, applies spawn flags, and attempts valid tile placement. */
void *func_8014C894(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    S_8014C894_2 *part_a;
    SpriteFrameState *part_b;
    S_8014C894_1 *work;
    S_8014C894_4 *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->unk_10 = func_8014CA68;
        work->unk_13 = MONSTER_VIPER;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->unk_0A = saved_spawn;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->frameTable = D_80150A7C;
        part_b->unk_24 = saved_kind_id;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind >= 2) {
            left = work->unk_14 | 0x2000;
            right = work->unk_1C | 0x2000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else {
            if (((flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_80150AD4;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_8014CE94;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
