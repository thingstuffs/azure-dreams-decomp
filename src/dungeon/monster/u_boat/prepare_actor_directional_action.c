#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/actor_status_flags.h"
#include "dungeon/actor/status.h"

struct ObjectPosition;
#include "common.h"
#include "dungeon/system/random.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/effect.h"
#include "dungeon/monster/u_boat.h"
#include "dungeon/player/object.h"

typedef struct S_801717D0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    s16 unk_46;
    u8 pad_48[0x18];
    void *unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_801717D0_0;   /* self in prepare_actor_directional_action */

typedef struct S_801717D0_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801717D0_2;   /* counter_base in prepare_actor_directional_action */

typedef struct S_801717D0_3 {
    u8 pad_00[0x98];
    s32 unk_98;
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_801717D0_3;   /* player in prepare_actor_directional_action */

typedef struct S_801717D0_5 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 unk_13;
} S_801717D0_5;   /* entry in prepare_actor_directional_action */


/* Prepares an entity action, updates its directional animation, and advances the counter. */
void prepare_actor_directional_action(ActorRecord *entity, ObjectPosition *action_param, SpriteFrameState *action_sprite, u8 *frame_table, s32 fallback_state)
{
    S_801717D0_0 *self;
    S_801717D0_3 *player;
    u8 *action_slot;
    u8 *action_table;
    S_801717D0_5 *action_entry;
    u16 *action_flags;
    s32 action_word;
    u16 counter;
    s32 special_action;
    s32 selection_index;
    s32 entry_index;
    s32 state_flags;

    special_action = 0;
    self = (S_801717D0_0 *)entity;
    self->unk_71 &= 0x7F;

    if ((self->unk_1C & ACTOR_PLAYER_SIDE) && ((self->unk_46 & 0x3FFF) >= 5)) {
        special_action = 1;
        if ((*(u16 *)((u8 *)&dungeon_actor_ring_anchor->unk_A4.value + 2)) == 2) {
            counter = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
            counter--;
            g_dungeon_status.activity_counts.parts.pending_action_count = counter;
        }

        player = ((S_801717D0_3 *)dungeon_actor_ring_anchor);
        if ((player->unk_98 & 0x3000) == 0x2000 &&
            player->unk_A6 != special_action) {
            player->unk_A6 = special_action;
            *(u16 *)&player->unk_98 |= 0x1000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
        } else {
            advance_status_timers((ActorRecord *)self);
            self->unk_6D--;
            entity->unk_8C.word = fallback_state;
            return;
        }
    } else {
        if (g_dungeon_status.flags & 8) {
            return;
        }
        if ((try_claim_dungeon_action_slot((ActorRecord *)self) << 16) != 0) {
            return;
        }

        select_nearby_target_and_initialize_slot(NODE_HEADER(self), action_param, 8, 0x300);
        if ((try_claim_dungeon_action_slot((ActorRecord *)self) << 16) != 0) {
            return;
        }
    }
    if (special_action == 0) {
        if (self->unk_1C & ACTOR_CONFUSED) {
            state_flags = self->unk_14;
            if (!(state_flags & 0x80000000)) {
                state_flags |= 0x80000000;
                self->unk_14 = state_flags;
                self->unk_2A = (u16)self->unk_2A + ((generate_random_value() & 7) << 9);
            }
        }

        action_flags = (u16 *)((u8 *)self + 0x46);
        if (!(*action_flags & 0x4000)) {
            action_word = *action_flags;
            selection_index = action_word & 0x3FFF;
            entry_index = selection_index - 1;
            action_table = item_action_definitions;
            action_slot = (u8 *)self;
            action_slot += entry_index * 3;
            entry_index = action_slot[8];
            action_entry = (S_801717D0_5 *)(action_table + entry_index * 20);
            if (action_entry->unk_12 == 2) {
                self->unk_60 =
                    scan_actor_along_heading((ActorRecord *)self,
                                  action_sprite->tile_x,
                                  action_sprite->tile_y,
                                  self->unk_2A,
                                  action_entry->unk_13);
            }
        }
        entity->action_id = 0x12;
    } else {
        entity->action_id = 0x12;
    }

    entity->action_phase = 0;
    entity->unk_8C.word = 0;

    if (frame_table != 0) {
        (action_sprite->frameTable) = frame_table;
        selection_index = (g_game_work.view.camera_rotation.parts.viewAngle + self->unk_2A + 0x100) >> 9;
        select_sprite_entry(action_sprite, frame_table[selection_index & 7], 0);
    }

    ((S_801717D0_2 *)((u8 *)&g_dungeon_status.turn_scale))->unk_0A++;

    return;
}
