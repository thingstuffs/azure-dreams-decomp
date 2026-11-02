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

typedef struct S_800D8590_0 {
    u8 pad_00[0xC];
    u8 * unk_0C;
    s32 unk_10;
} S_800D8590_0;


typedef struct S_800D8590_3 {
    u8 pad_00[0x12];
    s16 unk_12;
    u16 unk_14;
} S_800D8590_3;

extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);

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
        ((S_800D8590_3 *)child)->unk_14 |= 0x8000;
        ((S_800D8590_3 *)child)->unk_12 = 0;
        ((S_800D8590_3 *)child)->unk_14 &= 0xFFF3;
        return body;
    } else {
        if (body->species == MONSTER_TYRANT) {
            clear_slots_of_type(body, 0x1A);
        }

        if ((body->species == MONSTER_PULUNPA) &&
            (body->unk_A4.bytes[3] != 0) &&
            (body->unk_A8.byte != 0)) {
            map = *(u8 * *)&dungeon_actor_ring_anchor;
            map_index = body->unk_A8.byte;
            map += map_index;
            map[0xF9] = 1;
        }
        bzero(parent + 0xAC, 0x24);

        object = (ActorRecord *)(parent + 0x20);
        object->unk_AC.value = ((S_800D8590_0 *)parent)->unk_10;
        ((S_800D8590_0 *)parent)->unk_10 = (s32)D_800D8728 & 0x7FFFFFFF;
        object->unk_A8.s = body->species;
        body->species = MONSTER_FROG;
        object->action_id.u = 0xFF;
        object->unk_9C = -1;
        object->unk_8C.byte_ptr = update_actor_facing_animation;
        (*(void ** *)(child + 0x2C)) = actor_action_frames;

        frame_index = (g_game_work.view.camera_rotation.parts.viewAngle + body->facing + 0x100) >> 7;
        select_record_entry_and_value(child,
                      *(void **)((u8 *)actor_action_frames + (frame_index & 0x1C)), 0);
        object->unk_A0.parts.low = 0x14;
        ((S_800D8590_3 *)child)->unk_14 |= 0x8000;
        ((S_800D8590_3 *)child)->unk_12 = 0;
        ((S_800D8590_3 *)child)->unk_14 &= 0xFFF3;
        return body;
    }
}
