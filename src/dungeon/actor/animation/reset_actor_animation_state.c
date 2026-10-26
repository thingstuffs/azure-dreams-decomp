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

typedef struct S_800D8590_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    s16 unk_2A;
    u8 pad_2C[0x7B];
    u8 unk_A7;
    u8 unk_A8;
} S_800D8590_1;

typedef struct S_800D8590_2 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x3];
    s16 unk_A0;
    u8 pad_A2[0x6];
    s16 unk_A8;
    u8 pad_AA[0x2];
    s32 unk_AC;
} S_800D8590_2;

typedef struct S_800D8590_3 {
    u8 pad_00[0x12];
    s16 unk_12;
    u16 unk_14;
} S_800D8590_3;

extern void clear_slots_of_type();

extern u8 D_800D8728[];

extern void *actor_action_frames[];

/* Reset the entity state and animation, then update its child flags. */
void *reset_actor_animation_state(void *entity)
{
    u8 *child;
    u8 *map;
    s32 map_index;
    void *entity_arg;
    u8 *parent;
    u8 *object;
    s32 frame_index;

    entity_arg = entity;
    parent = entity - 0x20;
    if ((u8 *)(g_dungeon_status.pending_display_owner) == parent) {
        g_dungeon_status.pending_display_owner = (s32)parent & 0x7FFFFFFF;
    }

    child = ((S_800D8590_0 *)parent)->unk_0C;
    if (((S_800D8590_1 *)entity)->unk_13 == 0) {
        clear_player_linked_action_flags();
        ((S_800D8590_3 *)child)->unk_14 |= 0x8000;
        ((S_800D8590_3 *)child)->unk_12 = 0;
        ((S_800D8590_3 *)child)->unk_14 &= 0xFFF3;
        return entity;
    } else {
        if (((S_800D8590_1 *)entity)->unk_13 == MONSTER_TYRANT) {
            clear_slots_of_type(entity, 0x1A);
        }

        if ((((S_800D8590_1 *)entity)->unk_13 == MONSTER_PULUNPA) &&
            (((S_800D8590_1 *)entity)->unk_A7 != 0) &&
            (((S_800D8590_1 *)entity)->unk_A8 != 0)) {
            map = *(u8 * *)&dungeon_actor_ring_anchor;
            map_index = ((S_800D8590_1 *)entity)->unk_A8;
            map += map_index;
            map[0xF9] = 1;
        }
        bzero(parent + 0xAC, 0x24);

        object = parent + 0x20;
        ((S_800D8590_2 *)object)->unk_AC = ((S_800D8590_0 *)parent)->unk_10;
        ((S_800D8590_0 *)parent)->unk_10 = (s32)D_800D8728 & 0x7FFFFFFF;
        ((S_800D8590_2 *)object)->unk_A8 = ((S_800D8590_1 *)entity)->unk_13;
        ((S_800D8590_1 *)entity)->unk_13 = MONSTER_FROG;
        ((S_800D8590_2 *)object)->unk_9A = 0xFF;
        ((S_800D8590_2 *)object)->unk_9C = -1;
        ((S_800D8590_2 *)object)->unk_8C = update_actor_facing_animation;
        (*(void ** *)((u8 *)child + 0x2C)) = actor_action_frames;

        frame_index = (g_game_work.view.camera_rotation.parts.viewAngle + ((S_800D8590_1 *)entity)->unk_2A + 0x100) >> 7;
        select_record_entry_and_value(child,
                      *(void **)((u8 *)actor_action_frames + (frame_index & 0x1C)), 0);
        ((S_800D8590_2 *)object)->unk_A0 = 0x14;
        ((S_800D8590_3 *)child)->unk_14 |= 0x8000;
        ((S_800D8590_3 *)child)->unk_12 = 0;
        ((S_800D8590_3 *)child)->unk_14 &= 0xFFF3;
        return entity;
    }
}
