#include "common.h"
#include "dungeon/actor.h"
#include "shared/monster_ids.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/animation.h"
#include "dungeon/player.h"
#include "sdk/bzero.h"
#include "slus.h"
#include "engine/entity.h"

typedef struct S_800D8590_0 {
    u8 pad_00[0xC];
    u8 * unk_0C;
    s32 unk_10;
} S_800D8590_0;



extern u8 D_800D8728[];

extern void *actor_action_frames[];

/* Reset the entity state and animation, then update its child flags. */
void *reset_actor_animation_state(ActorRecord *body)
{
    u8 *child;
    u8 *map;
    s32 map_index;
    void *entity_arg;
    u8 *parent;
    ActorRecord *object;
    s32 frame_index;

    entity_arg = body;
    parent = ((void *)body) - 0x20;
    if ((u8 *)(g_dungeon_status.pending_display_owner) == parent) {
        g_dungeon_status.pending_display_owner = (s32)parent & 0x7FFFFFFF;
    }

    child = ((S_800D8590_0 *)parent)->unk_0C;
    if (body->species == 0) {
        clear_player_linked_action_flags();
        ((SpriteFrameState *)child)->flags |= 0x8000;
        ((SpriteFrameState *)child)->clut = 0;
        ((SpriteFrameState *)child)->flags &= 0xFFF3;
        return body;
    } else {
        if (body->species == MONSTER_TYRANT) {
            clear_slots_of_type(body, 0x1A);
        }

        if ((body->species == MONSTER_PULUNPA) &&
            (body->unk_A4.bytes[3] != 0) &&
            ((u8)(body->unk_A8) != 0)) {
            map = *(u8 * *)&dungeon_actor_ring_anchor;
            map_index = (u8)(body->unk_A8);
            map += map_index;
            map[0xF9] = 1;
        }
        bzero(parent + 0xAC, 0x24);

        object = (ActorRecord *)(parent + 0x20);
        object->unk_AC.value = ((S_800D8590_0 *)parent)->unk_10;
        ((S_800D8590_0 *)parent)->unk_10 = (s32)D_800D8728 & 0x7FFFFFFF;
        object->unk_A8 = body->species;
        body->species = MONSTER_FROG;
        object->action_id = 0xFF;
        object->unk_9C = -1;
        object->unk_8C.byte_ptr = update_actor_facing_animation;
        (*(void ** *)(child + 0x2C)) = actor_action_frames;

        frame_index = (g_game_work.view.camera_rotation.parts.viewAngle + body->facing + 0x100) >> 7;
        select_record_entry_and_value(child,
                      actor_action_frames[(frame_index >> 2) & 7], 0);
        object->unk_A0.parts.low = 0x14;
        ((SpriteFrameState *)child)->flags |= 0x8000;
        ((SpriteFrameState *)child)->clut = 0;
        ((SpriteFrameState *)child)->flags &= 0xFFF3;
        return body;
    }
}
