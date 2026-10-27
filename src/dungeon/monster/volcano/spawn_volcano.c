#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/volcano/spawn_variant_slot_c.h"
#include "shared/monster_ids.h"


/* Creates a Volcano actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_variant_monster_slot_c(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height)
{
    s32 kind;
    s32 left;
    s32 right;
    ActorRecord *work;
    s16 saved_height;
    ObjectNodeHeader *obj;
    register s8 saved_tile_y;
    s8 saved_tile_x;
    void *part_a;
    s16 saved_spawn_flags;
    SpriteFrameState *part_b;
    void *actor;

    work = 0;
    saved_tile_x = tile_x;
    saved_height = spawn_height;
    saved_tile_y = tile_y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    saved_spawn_flags = spawn_flags;
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        work->species = MONSTER_VOLCANO;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        ((SignedHeightView *)part_a)->z = saved_height;
        part_b = obj->sprite;
        part_b->tile_x = saved_tile_x;
        part_b->tile_y = saved_tile_y;
        actor = work;
        kind = spawn_flags & 3;

        if (kind == 1) {
            work->unk_8C.run = func_80158E5C;
            left = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = left;
            work->flags1C = right;
            part_b->frameTable = volcano_slot_c_frame_set;
        } else {
            if (kind >= 2) {
                work->unk_8C.run = func_80158E5C;
                left = work->flags14 | ACTOR_CLASS_ENABLED;
                right = work->flags1C | ACTOR_PLAYER_SIDE;
                work->flags14 = left;
                work->flags1C = right;
                part_b->frameTable = volcano_slot_c_frame_set;
            } else {
                if (((spawn_flags & ~3) << 16) == 0) {
                    if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                        if (generate_random_value() & 1) {
                            set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                          (generate_random_value() & 0x3F) | 0x20);
                            part_b->frameTable = D_8015C538;
                        }
                    }
                    ;
                    ((S_80158854_4 *)actor)->unk_8C = func_80158E5C;
                part_b->frameTable = volcano_slot_c_frame_set;
                } else {
                    work->unk_8C.run = func_80158E5C;
                part_b->frameTable = volcano_slot_c_frame_set;
                }
            }
        }
        obj->update_callback = func_80158A58;
        initialize_actor_sprite_and_animation(obj, part_a, part_b, (s16)saved_spawn_flags);
        ((S_80158854_4 *)actor)->unk_9A = 0xFF;
        ((S_80158854_4 *)actor)->unk_9C = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
