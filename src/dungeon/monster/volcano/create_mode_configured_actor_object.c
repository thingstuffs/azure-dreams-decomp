#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/monster/volcano/create_mode_configured_actor_object.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/volcano/create_mode_configured_actor_object.h"

/* Creates a Volcano actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_mode_configured_actor_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    void *result = NULL;
    ObjectNodeHeader *root;
    ObjectPosition *position;
    s16 held_flags;
    s32 kind;
    s8 saved_a;
    s16 saved_c;
    s8 saved_b;

    {
        SpriteFrameState *arg3_part;
        void *arg2_work;

        saved_a = attr_a;
        saved_c = attr_c;
        saved_b = attr_b;
        root = allocate_list_node(0x112, &scene_object_list_anchor.next);
        held_flags = spawn_flags;
        if (root != NULL) {
            result = (u8 *)root + 0x20;
            ((S_8016A800_0 *)result)->unk_13 = MONSTER_VOLCANO;
            register_node(root, project_sprite_chain);

            position = root->position;
            kind = spawn_flags & 3;
            position->z.w.i = saved_c;
            arg3_part = root->sprite;
            arg3_part->tile_x = saved_a;
            arg3_part->tile_y = saved_b;
            arg2_work = result;

            if (kind == 1) {
                ((S_8016A800_0 *)result)->unk_8C = func_8016AE5C;
                ((S_8016A800_0 *)result)->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                ((S_8016A800_0 *)result)->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                arg3_part->frameTable = volcano_frame_set_5;
            } else {
                if (kind >= 2) {
                    ((S_8016A800_0 *)result)->unk_8C = func_8016AE5C;
                    ((S_8016A800_0 *)result)->unk_14 |= ACTOR_CLASS_ENABLED;
                    ((S_8016A800_0 *)result)->unk_1C |= ACTOR_PLAYER_SIDE;
                    arg3_part->frameTable = volcano_frame_set_5;
                } else {
                    if ((s16)(spawn_flags & ~3) == 0) {
                        if (!(((S_8016A800_0 *)result)->unk_14 & ACTOR_RESIST_SLEEP)) {
                            spawn_flags = generate_random_value();
                            if (spawn_flags & 1) {
                                set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                                arg3_part->frameTable = D_8016E538;
                            }
                        }
                        ((S_8016A800_4 *)arg2_work)->unk_8C = func_8016AE5C;
                        arg3_part->frameTable = volcano_frame_set_5;
                    } else {
                        ((S_8016A800_0 *)result)->unk_8C = func_8016AE5C;
                        arg3_part->frameTable = volcano_frame_set_5;
                    }

                }
            }
            root->update_callback = func_8016AA58;
            initialize_actor_sprite_and_animation(root, position, arg3_part, (s16)held_flags);
            ((S_8016A800_4 *)arg2_work)->unk_9A = 0xFF;
            ((S_8016A800_4 *)arg2_work)->unk_9C = -1;
            try_move_actor_to_valid_position(arg2_work, position, arg3_part, result);
        }
    }
    return result;
}
