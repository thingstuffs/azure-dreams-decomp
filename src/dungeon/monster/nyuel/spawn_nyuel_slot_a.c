#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/nyuel/spawn_factory_slot_a.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_bdb094.h"

/* Creates a Nyuel actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
Func80BBB094PartC *spawn_mode_configured_monster_slot_a(s32 spawn_flags, s16 tile_x, s32 tile_y, s32 spawn_height)
{
    Func80BBB094PartC *result = 0;
    unsigned long slot1;
    s16 saved_tile_y;
    register Func80BBB094PartC *resultAlias;
    Func80BBB094Object *obj;
    Func80BBB094PartA *partA;
    s16 saved_spawn_flags;
    SpriteFrameState *partB;
    s32 mode;
    s32 flag;
    s32 randomTest;
    slot1 = (unsigned long)spawn_height;
    saved_tile_y = tile_y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    saved_spawn_flags = spawn_flags;
    if (obj != 0) {
        result = &obj->unk20;
        result->unk13 = 14;
        register_node(obj, project_sprite_chain);

        partA = obj->unk8;
        partA->unkA = (s32)slot1;
        slot1 = (unsigned long)obj->unkC;
        partB = (Func80BBB094PartB *)slot1;
        partB->tile_x = tile_x;
        partB->tile_y = saved_tile_y;
        resultAlias = result;

        mode = spawn_flags & 3;
        if (mode == 1) {
            result->unk8C = nyuel_slot_a_action_callback;
            result->unk14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            result->unk1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            partB->frameTable = nyuel_frame_set_5;
        } else if (mode >= 2) {
            result->unk8C = nyuel_slot_a_action_callback;
            result->unk14 |= ACTOR_CLASS_ENABLED;
            result->unk1C |= ACTOR_PLAYER_SIDE;
            partB->frameTable = nyuel_frame_set_5;
        } else {
            spawn_flags = (s16)(spawn_flags & -4);
            if (spawn_flags == 0) {
                flag = result->unk14 & ACTOR_RESIST_SLEEP;
                if (flag == 0) {
                    randomTest = generate_random_value() & 1;
                    if (randomTest != 0) {
                        s32 random = generate_random_value();

                        set_or_clear_actor_status_slot(result, STATUS_SLEEP, (random & 0x3F) | 0x20);
                        partB->frameTable = D_80150F00;
                    }
                } else {
                }
                resultAlias->unk8C = (void *)nyuel_slot_a_action_callback;
                partB->frameTable = nyuel_frame_set_5;
            } else {
                result->unk8C = (void *)nyuel_slot_a_action_callback;
                partB->frameTable = nyuel_frame_set_5;
            }
        }

        obj->unk10 = D_8014CA98;
        initialize_actor_sprite_and_animation(obj, partA, partB, saved_spawn_flags);

        resultAlias->unk9A = 0xFF;
        resultAlias->unk9C = -1;
        try_move_actor_to_valid_position(resultAlias, partA, partB, result);
    }
    return result;
}
