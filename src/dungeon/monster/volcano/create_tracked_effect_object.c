#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/monster/volcano/create_tracked_effect_object.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/volcano/create_tracked_effect_object.h"

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Volcano with default frames at D_80162510, applies spawn flags, and attempts valid tile
 * placement. */
void *create_tracked_effect_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    s32 left;
    s32 right;
    void *work;
    s16 saved_spawn;
    ObjectNodeHeader *obj;
    register s8 saved_variant;
    s8 saved_kind_id;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    void *actor;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8015E854_0 *)work)->unk_13 = MONSTER_VOLCANO;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_spawn;
        part_b = obj->sprite;
        part_b->tile_x = saved_kind_id;
        part_b->tile_y = saved_variant;
        actor = work;
        kind = flags & 3;

        if (kind == 1) {
            ((S_8015E854_0 *)work)->unk_8C = func_8015EE5C;
            left = ((S_8015E854_0 *)work)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = ((S_8015E854_0 *)work)->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((S_8015E854_0 *)work)->unk_14 = left;
            ((S_8015E854_0 *)work)->unk_1C = right;
            part_b->frameTable = volcano_frame_set_4;
        } else {
            if (kind >= 2) {
                ((S_8015E854_0 *)work)->unk_8C = func_8015EE5C;
                left = ((S_8015E854_0 *)work)->unk_14 | ACTOR_CLASS_ENABLED;
                right = ((S_8015E854_0 *)work)->unk_1C | ACTOR_PLAYER_SIDE;
                ((S_8015E854_0 *)work)->unk_14 = left;
                ((S_8015E854_0 *)work)->unk_1C = right;
                part_b->frameTable = volcano_frame_set_4;
            } else {
                if (((flags & ~3) << 16) == 0) {
                    if (!(((S_8015E854_0 *)work)->unk_14 & ACTOR_RESIST_SLEEP)) {
                        if (generate_random_value() & 1) {
                            set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                          (generate_random_value() & 0x3F) | 0x20);
                            part_b->frameTable = D_80162538;
                        }
                    }
                    ((S_8015E854_4 *)actor)->unk_8C = func_8015EE5C;
                    part_b->frameTable = volcano_frame_set_4;
                } else {
                    ((S_8015E854_0 *)work)->unk_8C = func_8015EE5C;
                    part_b->frameTable = volcano_frame_set_4;
                }
            }
        }
        obj->update_callback = func_8015EA58;
        initialize_actor_sprite_and_animation(obj, part_a, part_b, (s16)flags);
        ((S_8015E854_4 *)actor)->unk_9A = 0xFF;
        ((S_8015E854_4 *)actor)->unk_9C = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
