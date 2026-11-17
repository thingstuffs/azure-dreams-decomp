#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/volcano/spawn_variant_slot_c.h"
#include "shared/monster_ids.h"
#include "dungeon/monster/volcano/spawn_volcano_slot_f.h"


/* Creates a Volcano actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_volcano(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    ActorRecord *result = NULL;
    ObjectNodeHeader *root;
    ObjectPosition *position;
    s16 held_flags;
    s32 kind;
    s8 saved_a;
    s16 saved_c;
    s8 saved_b;

    {
        SpriteFrameState *arg3_part;
        ActorRecord *arg2_work;

        saved_a = attr_a;
        saved_c = attr_c;
        saved_b = attr_b;
        root = allocate_list_node(0x112, &scene_object_list_anchor.next);
        held_flags = spawn_flags;
        if (root != NULL) {
            result = NODE_BODY(root);
            result->species = MONSTER_VOLCANO;
            register_node(root, project_sprite_chain);

            position = root->position;
            kind = spawn_flags & 3;
            position->z.w.i = saved_c;
            arg3_part = root->sprite;
            arg3_part->tile_x = saved_a;
            arg3_part->tile_y = saved_b;
            arg2_work = result;

            if (kind == 1) {
                result->unk_8C.address = func_80158E5C;
                result->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                result->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                arg3_part->frameTable = volcano_slot_c_frame_set;
            } else {
                if (kind >= 2) {
                    result->unk_8C.address = func_80158E5C;
                    result->flags14 |= ACTOR_CLASS_ENABLED;
                    result->flags1C |= ACTOR_PLAYER_SIDE;
                    arg3_part->frameTable = volcano_slot_c_frame_set;
                } else {
                    if ((s16)(spawn_flags & ~3) == 0) {
                        if (!(result->flags14 & ACTOR_RESIST_SLEEP)) {
                            spawn_flags = generate_random_value();
                            if (spawn_flags & 1) {
                                set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                                arg3_part->frameTable = D_8015C538;
                            }
                        }
                        arg2_work->unk_8C.address = func_80158E5C;
                        arg3_part->frameTable = volcano_slot_c_frame_set;
                    } else {
                        result->unk_8C.address = func_80158E5C;
                        arg3_part->frameTable = volcano_slot_c_frame_set;
                    }

                }
            }
            root->update_callback = func_80158A58;
            initialize_actor_sprite_and_animation(root, position, arg3_part, (s16)held_flags);
            arg2_work->action_id = 0xFF;
            arg2_work->unk_9C = -1;
            try_move_actor_to_valid_position(arg2_work, position, arg3_part, result);
        }
    }
    return result;
}
