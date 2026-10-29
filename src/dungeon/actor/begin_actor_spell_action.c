#include "shared/actor_status_flags.h"
#include "dungeon/actor/status.h"
#include "dungeon/item/actor_target.h"

struct ObjectPosition;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/graphics.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

typedef struct S_800AAF00_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    s16 unk_46;
    u8 pad_48[0x18];
    void *unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_800AAF00_0;   /* obj in begin_actor_spell_action */

typedef struct S_800AAF00_2 {
    u8 pad_00[0x98];
    union { s32 s32; u16 u16; } unk_98;   /* accessed as both */
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x74];
    void * unk_11C;
} S_800AAF00_2;   /* D_800E3D7C in begin_actor_spell_action */

typedef struct S_800AAF00_3 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_800AAF00_3;   /* owner in begin_actor_spell_action */

struct ActorRecord;
extern s16 try_claim_dungeon_action_slot(struct ActorRecord *actor);
extern s32 generate_random_value(void);
extern void select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);

/* Updates the object action state and applies direction data to its target. */
void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state) {
    void *object;
    s32 special_action;
    u8 *slot_data;
    DefEntry *type_data;
    DefEntry *type_table;
    u16 *slot_flags;
    u16 input_flags;
    s32 slot_offset;
    s32 type_index;

    object = actor;
    ((S_800AAF00_0 *)object)->unk_71 &= 0x7F;
    input_flags = g_dungeon_status.flags;
    special_action = 0;

    if (!(input_flags & 0x2008)) {
        if ((((S_800AAF00_0 *)object)->unk_1C & ACTOR_PLAYER_SIDE) &&
            ((((S_800AAF00_0 *)object)->unk_46 & 0x3FFF) >= 5)) {
            special_action = 1;
            if (((((S_800AAF00_2 *)((u8 *)dungeon_actor_ring_anchor))->unk_98.s32 & 0x3000) == 0x2000) &&
                (((S_800AAF00_2 *)((u8 *)dungeon_actor_ring_anchor))->unk_A6 == 0)) {
                dungeon_actor_ring_anchor->action_state_flags |= 0x1000;
                ((S_800AAF00_2 *)((u8 *)dungeon_actor_ring_anchor))->unk_A6++;
                g_dungeon_status.activity_counts.parts.pending_action_count++;
            } else {
                advance_status_timers(object);
                ((S_800AAF00_0 *)object)->unk_6D--;
                ((S_800AAF00_3 *)actor)->unk_8C = next_state;

                return;
            }
        } else {
            if ((input_flags & 8) || ((try_claim_dungeon_action_slot(object) << 16) != 0)) {
                return;
            }
            select_nearby_target_and_initialize_slot((u8 *)object - 0x20, effect_param, 8, 0x300);
            if ((try_claim_dungeon_action_slot(object) << 16) != 0) {
                return;
            }
        }
        if (!special_action) {
            if (((S_800AAF00_0 *)object)->unk_1C & ACTOR_CONFUSED) {
                s32 object_flags;
                object_flags = ((S_800AAF00_0 *)object)->unk_14;
                if (!(object_flags & 0x80000000)) {
                    object_flags |= 0x80000000;
                    ((S_800AAF00_0 *)object)->unk_14 = object_flags;
                    ((S_800AAF00_0 *)object)->unk_2A.u += (generate_random_value() & 7) << 9;
                }
            }

            slot_flags = (u16 *)((u8 *)object + 0x46);
            if (!(*slot_flags & 0x4000)) {
                slot_offset = *slot_flags;
                slot_offset &= 0x3FFF;
                type_index = slot_offset;
                type_index--;
                type_table = item_action_definitions;
                slot_offset = type_index * 3;
                slot_data = object;
                slot_data += slot_offset;
                type_index = slot_data[8];
                type_data = type_table + type_index;
                if ((type_data->kind == 2) && (((S_800AAF00_0 *)object)->unk_60 == 0)) {
                    ((S_800AAF00_0 *)object)->unk_60 = scan_actor_along_heading(
                        object,
                        target->tile_x,
                        target->tile_y,
                        ((S_800AAF00_0 *)object)->unk_2A.s,
                        type_data->unk_13);

                }
            }
        } else {
            ((S_800AAF00_2 *)((u8 *)dungeon_actor_ring_anchor))->unk_11C = object;
        }

        ((S_800AAF00_3 *)actor)->unk_9A = 0x12;
        ((S_800AAF00_3 *)actor)->unk_9B = 0;
        ((S_800AAF00_3 *)actor)->unk_8C = 0;
        if (direction_table != 0) {
            (target->frameTable) = direction_table;
            select_sprite_entry(
                target,
                direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_800AAF00_0 *)object)->unk_2A.s + 0x100) >> 9) & 7],
                0);
        }
        target->flags |= 0x800;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }

}
