#include "shared/actor_property_flags.h"
#include "sdk/libgte.h"
#include "shared/actor_status_ids.h"
/* One native TU; source order follows the complete ledger cohort. */
#include "dungeon/effect/trap.h"
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "dungeon/effect.h"
#include "dungeon/item.h"
#include "dungeon/player.h"
#include "dungeon/system.h"
struct Dst;
struct Elem;

void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 play_sound_if_enabled(s32 query_value);
extern void D_800CB9DC();
extern u8 D_800DF650[];

typedef struct S_800CBB98_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)();
    u8 pad_14[0xC];
    void * unk_20;
} S_800CBB98_0;

typedef struct S_800CBB98_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CBB98_1;

typedef struct S_800CBB98_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800CBB98_2;

typedef struct S_800CBB98_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800CBB98_3;   /* held_arg3 in create_owned_tile_center_effect */

typedef struct S_800CBB98_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CBB98_4;   /* global_base in create_owned_tile_center_effect */

/* Creates an effect at the tile center, links it to its owner, and increments the effect count. */
void *create_owned_tile_center_effect(s16 tile_x, u16 tile_y, s16 height, void *owner) {
    s16 saved_height = height;
    S_800CBB98_3 *saved_owner = owner;
    u16 saved_tile_x = tile_x;
    u16 saved_tile_y = tile_y;
    S_800CBB98_2 *sprite;
    S_800CBB98_0 *effect;
    S_800CBB98_1 *position;
    u32 tile_x_low;
    u32 tile_y_low;

    effect = allocate_flagged_object_node(2);
    if (effect != 0) {
        effect->unk_10 = &D_800CB9DC;
        register_node(effect, project_sprite_chain);
        position = effect->unk_08;
        tile_x_low = (u32)saved_tile_x & 0xFFFFU;
        position->unk_02 = (s16) (tile_x_low * 64 + 0x20);
        tile_y_low = (u32)saved_tile_y & 0xFFFFU;
        position->unk_06 = (s16) (tile_y_low * 64 + 0x20);
        position->unk_0A = saved_height;
        sprite = effect->unk_0C;
        sprite->unk_0C = 0x808080;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        select_record_entry_and_value(sprite, D_800DF650, 0);
        effect->unk_20 = saved_owner;
        saved_owner->unk_14 = (s32) (saved_owner->unk_14 | 0x100000);
        play_sound_if_enabled(0x614);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    }
    return effect;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"

typedef struct S_800CBCA0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CBCA0_0_pre;   /* the 0x14 bytes before arg0 in check_entity_chance_and_trigger_parent_action, addressed as arg0[-1] */


typedef struct S_800CBCA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CBCA0_1;   /* parent in check_entity_chance_and_trigger_parent_action */


extern void adjust_source_value_and_finalize(void *context, const void *source);
extern s32 generate_random_value(void);
extern void * create_owned_tile_center_effect(s16 tile_x, u16 tile_y, s16 height, void *owner);
extern u8 D_800E1AE6[];


/* Checks an entity's flags and random roll before attempting its parent-based action. */
s32 check_entity_chance_and_trigger_parent_action(void *entity, s32 input_a, s32 input_b, s32 input_c)
{
    S_800CBCA0_1 *parent;
    s32 action_result;
    s32 roll;
    s32 divisor;
    s32 random_value;
    void *rng_entity = entity;

    if ((*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3)) != 0) {
        if (((EntityRec *)entity)->flags14 & ACTOR_PARTY_MEMBER) {
            roll = 1;
            return roll;
        }
    }
    if (trap_request_blocked == 0) {
        random_value = (u16)generate_random_value();
        if ((*(u8 *)((u8 *)&((EntityRec *)entity)->x + 3)) != 0) {
            divisor = random_value % (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 3));
            goto value_ready2;
        }
    }
    roll = 0;
    goto value_ready;
value_ready2:
    roll = divisor;
value_ready:

    if (roll < 0x30) {
        parent = ((S_800CBCA0_0_pre *)entity)[-1].unk_00;
        action_result = create_owned_tile_center_effect(parent->unk_24,
                               parent->unk_25,
                               ((EntityRec *)entity)->unk_88, entity);
        if (action_result != 0) {
            if ((*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3)) == 0) {
                clear_player_linked_action_flags();
                adjust_source_value_and_finalize(entity, D_800E1AE6);
            }
        }
    } else {
        if ((*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3)) == 0) {
            display_fixed_item_action_message();
        }
        return 1;
    }
    return action_result != 0;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

extern u8 D_800E1B08[];
extern u8 D_800E1B2E[];

extern void display_formatted_context_message(); /* Unprototyped: one or three arguments; retail retains only the text context. */
extern s32 get_entity_effect_value();
extern void initialize_timed_motion_step(); /* Unprototyped: two or three arguments; retail reads only the first two. */
extern s32 play_sound_if_enabled(s32 query_value);

/* Advances a timed Z transition, waits for readiness, and marks completion. */
void advance_timed_z_transition(s16 *transition) {
    GameView *state = &g_game_work.view;
    s16 phase = transition[1];

    switch (phase) {
    case 0:
        state->view_rotation_offset.parts.view_rotation_offset_z = state->view_rotation_offset.parts.view_rotation_offset_z + (0x800 - state->view_rotation_offset.parts.view_rotation_offset_z) / transition[2];
        {
            u16 frames_left = (u16)transition[2] - 1;
            transition[2] = frames_left;
            if ((s32)(frames_left << 16) > 0) {
                return;
            }
            {
                DungeonGlobalStatus *settings = &g_dungeon_status;
                transition[1] = (u16)transition[1] + 1;
                state->view_rotation_offset.parts.view_rotation_offset_z = -0x800;
                settings->activity_counts.parts.pending_action_count = (u16)((u16)settings->activity_counts.parts.pending_action_count) - 1;
                display_formatted_context_message(D_800E1B08);
            }
        }
        return;

    case 1:
    {
        DungeonGlobalStatus *settings = &g_dungeon_status;
        if ((settings->flags & 0x10) &&
            ((get_entity_effect_value(((u8 *)dungeon_actor_ring_anchor), 0x1C) << 16) == 0)) {
            transition[2] = 0x10;
            transition[1] = (u16)transition[1] + 1;
            settings->activity_counts.parts.pending_action_count = (u16)((u16)settings->activity_counts.parts.pending_action_count) + 1;
            initialize_timed_motion_step(0x10, 8);
            play_sound_if_enabled(0x818);
        }
    }
        return;

    case 2:
        state->view_rotation_offset.parts.view_rotation_offset_z = state->view_rotation_offset.parts.view_rotation_offset_z + (0 - state->view_rotation_offset.parts.view_rotation_offset_z) / transition[2];
        {
            u16 frames_left = (u16)transition[2] - 1;
            transition[2] = frames_left;
            if ((s32)(frames_left << 16) <= 0) {
                DungeonGlobalStatus *settings = &g_dungeon_status;
                u8 *message = D_800E1B2E;
                settings->activity_counts.parts.pending_action_count = (u16)((u16)settings->activity_counts.parts.pending_action_count) - 1;
                state->view_rotation_offset.parts.view_rotation_offset_z = 0;
                display_formatted_context_message(message);
                ((u16 *)transition)[-1] = ((u16 *)transition)[-1] | 0x8000;
                object_flag_block.flags = ((u32)object_flag_block.flags) | 0x8000;
            }
        }

        break;
    }
}
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern s32 D_800CBDB4;
extern u8 D_800E1B5D;

extern s32 has_enough_available_runtime_nodes(s32 a0);
extern s32 get_entity_effect_value();
extern s16 set_or_clear_actor_status_slot();
extern void initialize_timed_motion_step(); /* Unprototyped: two or three arguments; retail reads only the first two. */
extern s32 play_sound_if_enabled(s32 query_value);
extern void display_formatted_context_message(); /* Unprototyped: one or three arguments; retail retains only the text context. */

/* Creates an effect for the active entity or displays its status message. */
s32 create_active_entity_effect_or_message(s32 entity)
{
    void *effect;
    s32 status;
    register s32 effect_id;
    register s32 effect_id_half;

    if (entity == ((s32)dungeon_actor_ring_anchor)) {
        if (has_enough_available_runtime_nodes(1) == 0) {
            return 0;
        }
        status = get_entity_effect_value(entity, 0x1C);
        if ((status << 0x10) == 0) {
            if ((set_or_clear_actor_status_slot(entity, 0x1C, 0x10) << 0x10) >= 0) {
                effect = allocate_flagged_object_node(2);
                effect_id = 0x10;
                *(void **)((u8 *)effect + 0x10) = &D_800CBDB4;
                effect_id_half = effect_id;
                *(s16 *)((u8 *)effect + 0x24) = effect_id_half;
                g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
                initialize_timed_motion_step(effect_id, 8);
                play_sound_if_enabled(0x818);
                return 1;
            }
        } else {
            display_formatted_context_message(&D_800E1B5D);
        }
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#define U8(p,o) (*(u8 *)((u8 *)(p)+(o)))
#define S16(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U16(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define U32(p,o) (*(u32 *)((u8 *)(p)+(o)))
#define P32(p,o) (*(void **)((u8 *)(p)+(o)))
extern s32 generate_random_value(void);
extern s16 set_or_clear_actor_status_slot();
extern s32 play_sound_if_enabled(s32 query_value);
extern void adjust_source_value_and_finalize(void *context, const void *source);

extern u8 D_800E1BBC[];
/* Attempts a random status effect and plays its visual and sound effects on success. */
s32 attempt_random_status_effect(void *entity, s32 rng_input_a, s32 rng_input_b, s32 rng_input_c)
{
    u8 notify_failure = 0;
    s32 random_value;
    s16 roll_or_failure;
    void *parent;

    if (!trap_request_blocked &&
        (random_value = generate_random_value() & 0xffff,
         U8(entity, 3))) {
        s32 remainder;

        remainder = random_value % U8(entity, 3);
        roll_or_failure = remainder;
    } else {
        roll_or_failure = 0;
    }
    if (roll_or_failure < 0x30 && (set_or_clear_actor_status_slot(entity, STATUS_SPEED, -0x10) << 16) >= 0) {
        parent = P32(entity, -0x14);
        if (!(U16(parent, 0x14) & 0x8000)) {
            spawn_randomized_particle_burst((U8(parent, 0x24) << 6) | 0x20,
                          (U8(parent, 0x25) << 6) | 0x20,
                          S16(entity, 0x88), 0x202020, 0x40, 0);
            play_sound_if_enabled(0x615);
        }
        if (U32(entity, 0x14) & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(entity, D_800E1BBC);
        }
    } else {
        roll_or_failure = U8(entity, 0x13) == 0;
        notify_failure = roll_or_failure;
    }
    roll_or_failure = notify_failure;
    if (roll_or_failure) {
        display_fixed_item_action_message();
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"

typedef struct S_800CC18C_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x13];
    u8 unk_1B;
    u8 pad_1C[0xF];
    u8 unk_2B;
} S_800CC18C_0;   /* arg0 in resolve_random_trap_outcome; pointer addresses record offset 0x18 */



extern u8 D_800E1BDA[];
extern void adjust_source_value_and_finalize(void *context, const void *source);
extern s32 play_sound_if_enabled(s32 query_value);
extern s32 generate_random_value(void);
extern s32 begin_actor_random_warp(void *, s32, s32, void *);


/* Resolve a ranged random check, apply its effects, and return the outcome. */
s32 resolve_random_trap_outcome(void *entity, s32 forwarded_1, s32 forwarded_2, s32 forwarded_3) {
    s16 roll;
    s32 random_value;
    s32 remainder;
    s16 outcome;
    s32 feedback_kind;
    s32 feedback_or_result;

    outcome = 0;
    if (trap_request_blocked == 0) {
        random_value = generate_random_value() & 0xFFFF;
        if (((s32)(((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_1B)) != 0) {
            roll = ((s32)(((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_1B));
            remainder = random_value % roll;
            roll = remainder;
        } else {
            roll = 0;
        }
    } else {
        roll = 0;
    }
    if (roll < 0x40) {
        begin_actor_random_warp(entity, ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_00,
            ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_04, entity);
        play_sound_if_enabled(0x705);
        if (trap_request_blocked != 0) {
            outcome = -1;
        }
        feedback_kind = ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_2B == 0;
    } else {
        outcome = 1;
        feedback_kind = (((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_2B == 0) * 2;
    }
    feedback_or_result = feedback_kind;
    if (feedback_or_result != 0) {
        if (feedback_or_result == 1) {
            adjust_source_value_and_finalize(entity, &D_800E1BDA);
        } else {
            display_fixed_item_action_message();
        }
    }
    if (((s16)(outcome)) < 0) {
        return 0;
    }
    if (((s16)(outcome)) != 0) {
        feedback_or_result = 1;
    } else {
        feedback_or_result = -1;
    }
    return feedback_or_result;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"



extern s32 try_apply_confusion_status(void *object, s32 amount, s32 slots);
extern s32 play_sound_if_enabled(s32 query_value);

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xE];
    u8 x;
    u8 y;
} Entry;

/* Run the 0x10-slot request for the object with the budget the global mode picks; on refusal give the fallback cue, otherwise raise the tile effect and sound 0x611 unless the owning entry is flagged. */
s32 attempt_trap_request_ten_slots(void *object) {
    s32 amount = 0x40;
    Entry *entry;

    if (trap_request_blocked != 0) {
        amount = 0x400;
    }
    if (try_apply_confusion_status(object, amount, 0x10) == 0) {
        if (*(u8 *)((u8 *)object + 0x13) == 0) {
            display_fixed_item_action_message();
            return 1;
        }
        return 1;
    }
    entry = *(Entry **)((u8 *)object - 0x14);
    if (!(entry->flags & 0x8000)) {
        spawn_randomized_particle_burst((entry->x << 6) | 0x20,
                      (entry->y << 6) | 0x20,
                      *(s16 *)((u8 *)object + 0x88), 0x802020, 0x20, 0);
        play_sound_if_enabled(0x611);
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern s16 D_8006CCD8[], D_8006CCE8[];
extern s32 find_object_near_tile_height();
extern void apply_attack_power_and_element_effects();
extern s32 find_entry_at_tile_coordinates(s16 x, s16 y, s16 z);
extern s32 find_floor_item_at_world_position(s32 input_x, s32 input_y, s32 input_z);
extern s32 take_map_item_slot(void *object, s16 slot);


/* Advance the effect, process collisions, and mark it finished when its steps run out. */
void advance_trap_effect_and_process_collisions(void *effect)
{
    s32 target;
    s16 entry_index;

    U16(effect, 0) += D_8006CCD8[U8(effect, 6)];
    U16(effect, 2) += D_8006CCE8[U8(effect, 6)];
    target = find_object_near_tile_height(U16(effect, 0), U16(effect, 2), S16(effect, 4));
    if (target) {
        apply_attack_power_and_element_effects(target, 6, U8(((u8 *)dungeon_actor_ring_anchor), 0x11), 9,
                      (s16)(U8(effect, 6) << 9), 0, 3);
    }
    entry_index = find_entry_at_tile_coordinates(S16(effect, 0), S16(effect, 2), S16(effect, 4));
    if (entry_index >= 0) {
        if (((u8 *)floor_objects)[entry_index * 4] == 7) {
            take_map_item_slot(0, entry_index);
        } else {
            U32(floor_objects, entry_index * 4) = 0;
        }
    }
    entry_index = find_floor_item_at_world_position(S16(effect, 0), S16(effect, 2), S16(effect, 4));
    if (entry_index >= 0) {
        U32(((u8 *)dungeon_ground_items), entry_index * 4) = 0;
    }
    U8(effect, 7)--;
    if (!U8(effect, 7)) {
        U16(effect, -2) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_800CC4F0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} S_800CC4F0_0;   /* arg1 in update_directional_trap_effect */

typedef struct S_800CC4F0_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    s16 unk_06;
    s16 unk_08;
} S_800CC4F0_1;   /* arg0 in update_directional_trap_effect; pointer addresses record offset 0x2 */


extern void * create_tile_center_quad_effect(s16 tile_x, s16 tile_y, s16 z, s16 tail_value, s16 render_mode, u16 tail_config);

/* Updates directional motion, emits paired effects, and marks completion when the timer expires. */
void update_directional_trap_effect(void *effect_data, S_800CC4F0_0 *position) {
    u16 ticks_left;

    position->unk_0E = (u16) (position->unk_0E + (rcos(((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_06)
        >> 6));
    position->unk_12 = (u16) (position->unk_12 + (rsin(((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_06)
        >> 6));
    if (((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_08 == 0) {
        create_tile_center_quad_effect((u16) position->unk_02 >> 6, (u16) position->unk_06 >> 6, position->unk_0A,
            ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_06, 0, 1);
        create_tile_center_quad_effect((u16) position->unk_02 >> 6, (u16) position->unk_06 >> 6, position->unk_0A,
            ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_06, 1, 1);
    }
    ticks_left = ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_04 - 1;
    ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_04 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_00 = (u16) (((S_800CC4F0_1 *)((u8 *)effect_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "shared/game_work.h"

extern s32 linked_mesh_processor_address[3];
typedef struct DungeonObject
{
    s8 pad0[8];
    struct DungeonVertex *field8;
    struct DungeonPacket *fieldC;
    void *field10;
}
DungeonObject;
typedef struct DungeonVertex
{
    s8 pad0[2];
    s16 field2;
    s8 pad4[2];
    s16 field6;
    s8 pad8[2];
    s16 fieldA;
    s8 padC[2];
    s16 fieldE;
    s8 pad10[2];
    s16 field12;
    s8 pad14[2];
    s16 field16;
}
DungeonVertex;
typedef struct DungeonPacket
{
    s8 pad0[6];
    s16 field6;
    void *field8;
    s32 fieldC;
    s16 field10;
    s16 field12;
    u16 field14;
    s16 field16;
    s8 pad18[4];
    u16 field1C;
    u16 field1E;
}
DungeonPacket;
extern s32 D_800CC4F0;

/* Create a dungeon object at the tile center and initialize its rendering settings. */
void *create_tile_center_quad_effect(s16 tile_x, s16 tile_y, s16 z, s16 tail_value, s16 render_mode, u16 tail_config)
{
    DungeonObject *obj;
    DungeonVertex *vertex;
    DungeonVertex *tail_vertex;
    DungeonPacket *packet;
    s32 packet_color;
    s16 world_x;
    s16 world_y;
    s16 saved_render_mode;
    obj = allocate_flagged_object_node(0x202);
    saved_render_mode = (s16) render_mode;
    if (obj != 0) {
        obj->field10 = &D_800CC4F0;
        register_node(obj, linked_mesh_processor_address);
        packet_color = 0x00800000;
        world_x = ((tile_x << 0x10) >> 0xA) + 0x20;
        vertex = obj->field8;
        packet_color |= 0x8080;
        vertex->field2 = world_x;
        vertex->fieldE = world_x;
        world_y = ((tile_y << 0x10) >> 0xA) + 0x20;
        vertex->field6 = world_y;
        vertex->field12 = world_y;
        vertex->fieldA = z;
        vertex->field16 = z;
        packet = obj->fieldC;
        packet->fieldC = packet_color;
        packet->field8 = D_800E03D4;
        packet->field14 = packet->field14 | 0xC;
        if ((render_mode << 0x10) != 0) {
            packet->field1E = 0x1000;
        }
        else {
            packet->field1E = 0x400;
        }
        packet->field1C = packet->field1E;
        if ((saved_render_mode << 0x10) == 0) {
            packet->field10 = 0x20;
        }
        else {
            packet->field10 = 0x60;
        }
        packet->field6 = 0x20;
        tail_vertex = (DungeonVertex *) (((s8 *) obj) + 0x20);
        *((s16 *) (((s8 *) tail_vertex) + 4)) = tail_value;
        tail_vertex->field2 = 8;
        *((u16 *) (((s8 *) tail_vertex) + 6)) = tail_config;
    }
    return obj;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/object_flags.h"



/* Fade the color toward 0xE0, then to black, and flag completion. */
void fade_trap_color_to_black(TrapFadeWork *fade, void *unused, SpriteFrameState *color) {
    s16 steps;
    s16 brighten_left;
    s16 darken_left;
    s32 blue_step;
    u8 blue;
    u8 red;
    u8 green;

    if (fade->phase.s == 0) {
        red = color->color.c.r;
        color->color.c.r = red + ((0xE0 - red) / fade->frames_left.s);
        green = color->color.c.g;
        steps = fade->frames_left.s;
        blue = color->color.c.b;
        color->color.c.g = green + ((0xE0 - green) / steps);
        blue_step = (0xE0 - blue) / fade->frames_left.s;
        color->color.c.b = blue + blue_step;
        brighten_left = fade->frames_left.u - 1;
        fade->frames_left.s = brighten_left;
        if ((brighten_left << 16) <= 0) {
            fade->frames_left.s = 0x10;
            fade->phase.u++;
            return;
        }
    } else {
        color->color.c.r = color->color.c.r - (color->color.c.r / fade->frames_left.s);
        color->color.c.g = color->color.c.g - (color->color.c.g / fade->frames_left.s);
        color->color.c.b = color->color.c.b - (color->color.c.b / fade->frames_left.s);
        darken_left = fade->frames_left.u - 1;
        fade->frames_left.s = darken_left;
        if ((darken_left << 16) <= 0) {
            ((ObjectNodeHeader *)((u8 *)fade - 0x20))->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"

typedef struct CoordBlock {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} CoordBlock;

typedef struct DescBlock {
    u8 pad0[6];
    s16 pre6;
    void *page;
    u8 padC[4];
    s16 size;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    u16 copy;
    u16 mode;
} DescBlock;


typedef struct ObjectBlock {
    u8 pad0[8];
    CoordBlock *coords;
    DescBlock *desc;
    void *resource;
} ObjectBlock;


extern u8 D_800CC744[];



/* Create an object at grid coordinates and initialize its display and tail data. */
ObjectBlock *create_grid_effect_object(s16 grid_x, s16 grid_y, s16 z, s16 value, s16 size_mode) {
    ObjectBlock *obj;
    TrapFadeWork *tail;
    CoordBlock *coords;
    DescBlock *desc;

    obj = allocate_flagged_object_node(2);
    if (obj != 0) {
        obj->resource = D_800CC744;
        register_node(obj, draw_linked_sprites_clipped);
        coords = obj->coords;
        coords->x = (s16)(((grid_x << 16) >> 10) + 0x20);
        coords->y = (s16)(((grid_y << 16) >> 10) + 0x20);
        coords->z = z;
        desc = obj->desc;
        desc->page = D_800E03D4;
        desc->flags |= 0xC;
        desc->mode = (size_mode << 16) != 0 ? 0x6000 : 0x3000;
        desc->copy = desc->mode;
        desc->size = (size_mode << 16) != 0 ? 0x60 : 0x20;
        desc->pre6 = 0x20;
        tail = (TrapFadeWork *)((u8 *)obj + 0x20);
        tail->value = value;
        tail->frames_left.s = 4;
        tail->mode = size_mode;
    }
    return obj;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"


/* Decrements the record countdown and marks completion when it reaches zero. */
void tick_byte_timed_trap_effect(void *record) {
    u8 countdown;

    countdown = *(u8 *)((u8 *)record + 7) - 1;
    *(u8 *)((u8 *)record + 7) = countdown;
    if (!(countdown & 0xFF)) {
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        *(u16 *)((u8 *)record - 2) =
            (u16)(*(u16 *)((u8 *)record - 2) | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"


typedef struct S_800CCA14_0 {
    u8 pad_00[0x10];
    u8 * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x1];
    s8 unk_27;
} S_800CCA14_0;

typedef struct S_800CCA14_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CCA14_1;   /* count_base in create_five_part_target_effect */

typedef struct S_800CCA14_2 {
    u8 pad_00[0x10];
    u8 * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    s8 unk_26;
    s8 unk_27;
} S_800CCA14_2;


void *initialize_scene_object_in_buffer();      /* extern */
s32 find_object_near_tile_height();                   /* extern */
void apply_attack_power_and_element_effects(); /* extern */
extern void * create_tile_center_quad_effect(s16 tile_x, s16 tile_y, s16 z, s16 tail_value, s16 render_mode, u16 tail_config);
extern u8 D_800CC370;
extern u8 D_800CC9BC;
extern u8 trap_resource_slot;
extern u8 dungeon_resource_buffer;

/* Creates a five-part effect at the given position and applies its target effect. */
void create_five_part_target_effect(u16 x, u16 y, s16 z) {
    s32 direction;
    s32 first_base_angle;
    s32 first_angle;
    s32 base_angle;
    s32 angle;
    s32 target;
    s32 part_index;
    u16 part_x;
    u16 part_y;
    u16 part_z;
    S_800CCA14_0 *effect;
    S_800CCA14_2 *part;

    effect = initialize_scene_object_in_buffer(0, (trap_resource_slot * 0xC8) + (u8 *)&dungeon_resource_buffer, 0xA);
    effect->unk_10 = &D_800CC9BC;
    effect->unk_20 = x;
    effect->unk_22 = y;
    effect->unk_24 = z;
    effect->unk_27 = 8;
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    part_index = 3;
    do {
        part = initialize_scene_object_in_buffer(0, (((trap_resource_slot * 5) + part_index) * 0x28) + ((u8 *)&dungeon_resource_buffer + 0x28), 0xA);
        part->unk_10 = &D_800CC370;
        part_x = (u16) effect->unk_20;
        direction = part_index * 2;
        part->unk_20 = part_x;
        part_y = (u16) effect->unk_22;
        part_index -= 1;
        part->unk_22 = part_y;
        part_z = (u16) effect->unk_24;
        part->unk_27 = 8;
        part->unk_26 = direction;
        part->unk_24 = part_z;
    } while (part_index >= 0);
    base_angle = (part_index << 0x1A) >> 0x10;
    first_base_angle = base_angle;
    create_grid_effect_object((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, first_base_angle, 0);
    part_index = 3;
    create_grid_effect_object((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, base_angle, 1);
    do {
        angle = (part_index << 0x1A) >> 0x10;
        first_angle = angle;
        create_tile_center_quad_effect((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, first_angle, 0, 0);
        create_tile_center_quad_effect((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, angle, 1, 1);
        part_index -= 1;
    } while (part_index >= 0);
    target = find_object_near_tile_height(effect->unk_20, effect->unk_22, (s16) effect->unk_24);
    if (target != 0) {
        apply_attack_power_and_element_effects(target, 0xC, dungeon_actor_ring_anchor->level, 9, 0x400, 0, 3);
    }
}
#include "modules/trap_effects_candidate.h"
#include "common.h"

typedef struct {
    u8 pad[3];
    u8 flags;
} Entry4;




extern u8 trap_resource_slot;
extern s32 D_800DCF78;

extern s32 play_sound_if_enabled(s32 query_value);
s32 generate_random_value(void);
void draw_textured_ellipse(void *, void *, s32, s32);
extern void create_five_part_target_effect(u16 x, u16 y, s16 z);

/* Take the item in map slot `slot`: with no object, drop the slot's 0x80 flag and bump the pickup count; otherwise roll the object's 0x3 chance and give the fallback cue at or above 0x40, then cue 0x817 for the slot's item. */
s32 take_map_item_slot(void *object, s16 slot)
{
    s32 stack_args[2];
    s16 value;
    s32 random;
    s32 index;
    s32 scaled_index;
    s32 field;
    s8 count;
    s32 flags;
    u8 *map_base;
    u8 *item_base;
    u8 *entry;
    u8 *item;
    u8 * item_2;
    u8 *countp;
    s32 tail_index;
    u8 *tail_base;

    if (object == 0) {
        map_base = (u8 *)floor_objects;
        index = slot;
        scaled_index = index * 4;
        entry = scaled_index + map_base;
        flags = entry[3];
        if (flags & 0x80) {
            value = flags & 0x7F;
            item_base = (u8 *)dungeon_floor_object_positions;
            entry[3] = value;
            item = item_base + index * 24;
            countp = &trap_resource_slot;
            field = *(u16 *)(item + 0x14);
            count = *countp;
            field &= 0xF7FF;
            count++;
            *(u16 *)(item + 0x14) = field;
            *countp = count;
        } else {
            return 1;
        }
    } else {
        if (trap_request_blocked != 0) {
            value = 0;
        } else {
            random = generate_random_value() & 0xFFFF;
            if (*((u8 *)object + 3) != 0) {
                value = random % *((u8 *)object + 3);
            } else {
                value = 0;
            }
        }

        if (value >= 0x40) {
            display_fixed_item_action_message();
            value = 1;
            return value;
        }

        D_800DCF78 = 0x00202080;
        stack_args[0] = 0x01000340;
        stack_args[1] = 0x00200020;
        draw_textured_ellipse((u8 *)&D_800DCF78 - 0x10, stack_args, 1, 0);
        trap_resource_slot = 0;
    }

    tail_base = (u8 *)dungeon_floor_object_positions;
    tail_index = slot;
    item_2 = tail_base + tail_index * 24;
    create_five_part_target_effect(item_2[6], item_2[7], *(s16 *)(item_2 + 0x12));
    play_sound_if_enabled(0x817);
    return 1;
}

/* MECHANISM: Recover true-space joins locally and model the call workspace as an
   escaping 8-byte stack record.  Hold object/slot in s0/s1 and use guarded a0/v1
   RNG/remainder roles so the explicit result merge survives before the threshold. */
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_800CCDA0_0 {
    s32 unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    s16 unk_08;
    s16 unk_0A;
} S_800CCDA0_0;   /* arg0 in update_bouncing_trap_effect */

typedef struct S_800CCDA0_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800CCDA0_1;   /* arg1 in update_bouncing_trap_effect */

typedef struct S_800CCDA0_2 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800CCDA0_2;   /* base in update_bouncing_trap_effect */

typedef struct S_800CCDA0_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x4];
    union { u16 s; u16 u; } unk_1A;   /* accessed as both */
} S_800CCDA0_3;   /* arg2 in update_bouncing_trap_effect */


extern void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, s32, s32);
extern s32 play_sound_if_enabled(s32 query_value);




/* Updates a bouncing effect's motion, rotation, and fading until its lifetime expires. */
void update_bouncing_trap_effect(void *effect, void *motion, void *sprite)
{
    u16 ticks_or_angle;

    if (((S_800CCDA0_0 *)effect)->unk_04.s == 0) {
        ((S_800CCDA0_1 *)motion)->unk_14 += 0x20000;

        ticks_or_angle = ((S_800CCDA0_0 *)effect)->unk_06.s - 1;
        ((S_800CCDA0_0 *)effect)->unk_06.s = ticks_or_angle;
        if ((ticks_or_angle << 16) == 0) {
            play_sound_if_enabled(0x701);
        }

        if (((S_800CCDA0_0 *)effect)->unk_0A < ((S_800CCDA0_1 *)motion)->unk_08.at02.v) {
            apply_attack_power_and_element_effects(((S_800CCDA0_0 *)effect)->unk_00, 10,
                          ((u8 *)dungeon_actor_ring_anchor)[0x11], 8,
                          (((S_800CCDA0_0 *)effect)->unk_08 << 25) >> 16, 0, 2);

            ((S_800CCDA0_1 *)motion)->unk_14 = -((S_800CCDA0_1 *)motion)->unk_14;
            ((S_800CCDA0_1 *)motion)->unk_0C =
                rcos(g_game_work.view.camera_rotation.parts.viewAngle) << 8;
            ((S_800CCDA0_1 *)motion)->unk_10 =
                rsin(g_game_work.view.camera_rotation.parts.viewAngle) << 8;

            ((S_800CCDA0_3 *)sprite)->unk_14 |= 0xC;
            ((S_800CCDA0_0 *)effect)->unk_06.s = 12;
            ((S_800CCDA0_0 *)effect)->unk_04.u++;
        }
    } else {
        u16 angle;
        s16 ticks_left;

        ((S_800CCDA0_1 *)motion)->unk_14 += 0x80000;
        angle = ((S_800CCDA0_3 *)sprite)->unk_1A.s;
        ticks_left = ((S_800CCDA0_0 *)effect)->unk_06.u;
        angle += (0x400 - angle) / ticks_left;
        ((S_800CCDA0_3 *)sprite)->unk_1A.s = angle;

        {
            s32 wobble_angle;

            ticks_or_angle = ((S_800CCDA0_0 *)effect)->unk_06.s;
            wobble_angle = ((S_800CCDA0_3 *)sprite)->unk_1A.u;
            if (ticks_or_angle & 1) {
                ticks_or_angle = wobble_angle + 0x100;
            } else {
                ticks_or_angle = wobble_angle - 0x100;
            }
            ((S_800CCDA0_3 *)sprite)->unk_1A.u = ticks_or_angle;
        }

        ((S_800CCDA0_3 *)sprite)->unk_0C -=
            ((S_800CCDA0_3 *)sprite)->unk_0C / ((S_800CCDA0_0 *)effect)->unk_06.u;
        ((S_800CCDA0_3 *)sprite)->unk_0D -=
            ((S_800CCDA0_3 *)sprite)->unk_0D / ((S_800CCDA0_0 *)effect)->unk_06.u;
        ((S_800CCDA0_3 *)sprite)->unk_0E -=
            ((S_800CCDA0_3 *)sprite)->unk_0E / ((S_800CCDA0_0 *)effect)->unk_06.u;

        ticks_or_angle = ((S_800CCDA0_0 *)effect)->unk_06.s - 1;
        ((S_800CCDA0_0 *)effect)->unk_06.s = ticks_or_angle;
        if ((ticks_or_angle << 16) == 0) {
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }

    ((S_800CCDA0_1 *)motion)->unk_00 += ((S_800CCDA0_1 *)motion)->unk_0C;
    ((S_800CCDA0_1 *)motion)->unk_04 += ((S_800CCDA0_1 *)motion)->unk_10;
    ((S_800CCDA0_1 *)motion)->unk_08.at00.v += ((S_800CCDA0_1 *)motion)->unk_14;
}
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800CD004_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD004_0_pre;   /* the 0x14 bytes before arg0 in spawn_source_sprite_effect, addressed as arg0[-1] */

typedef struct S_800CD004_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    u8 pad_14[0x74];
    u16 unk_88;
} S_800CD004_0;   /* arg0 in spawn_source_sprite_effect */

typedef struct S_800CD004_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800CD004_1;   /* object in spawn_source_sprite_effect */

typedef struct S_800CD004_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CD004_2;   /* map in spawn_source_sprite_effect */

typedef struct S_800CD004_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD004_3;   /* quad in spawn_source_sprite_effect */

typedef struct S_800CD004_4 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_800CD004_4;   /* sprite in spawn_source_sprite_effect */

typedef struct S_800CD004_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD004_5;   /* tail in spawn_source_sprite_effect */

typedef struct S_800CD004_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CD004_6;   /* counter in spawn_source_sprite_effect */


extern s32 rand(void);
extern s32 play_sound_if_enabled(s32 query_value);
extern s32 generate_random_value(void);

extern u8 D_800CCDA0;
extern u8 D_800DFD0C[];
extern u8 D_800DFD30[];


/* Spawn a sprite effect for the source or invoke its fallback action. */
s32 spawn_source_sprite_effect(void *source, s32 rng_arg_1, s32 rng_arg_2, s32 rng_arg_3)
{
    s32 random;
    s16 roll;
    s32 tile_x;
    void *effect;
    S_800CD004_3 *quad;
    S_800CD004_5 *effect_state;
    S_800CD004_4 *sprite;
    S_800CD004_2 *map;
    void *texture;
    s32 color;
    s32 variant;
    u32 height_offset;
    s32 height_delta;
    void *init_effect;

    if (trap_request_blocked == 0) {
        random = generate_random_value() & 0xFFFF;
        if (((S_800CD004_0 *)source)->unk_03 != 0) {
            roll = random % ((S_800CD004_0 *)source)->unk_03;
        } else {
            roll = 0;
        }
    } else {
        roll = 0;
    }

    if (roll < 0x30) {
        effect = allocate_flagged_object_node(2);
        if (effect != NULL) {
            init_effect = effect;
            ((S_800CD004_1 *)effect)->unk_10 = &D_800CCDA0;
            register_node(init_effect, project_sprite_chain);

            map = ((S_800CD004_0_pre *)source)[-1].unk_00;
            tile_x = map->unk_24;
            quad = ((S_800CD004_1 *)effect)->unk_08;
            quad->unk_02 = (tile_x << 6) + 0x20;
            quad->unk_06 = (map->unk_25 << 6) + 0x20;
            quad->unk_0A = ((S_800CD004_0 *)source)->unk_88 - 0x200;

            sprite = ((S_800CD004_1 *)effect)->unk_0C;
            sprite->unk_1E = 0x1000;
            sprite->unk_1C = 0x1000;
            color = 0x808080;
            sprite->unk_0C = color;

            variant = rand();
            if (variant & 3) {
                texture = D_800DFD0C;
            } else {
                texture = D_800DFD30;
            }
            sprite->unk_08 = texture;
            sprite->unk_10 = 0x20;

            height_offset = entity_height_offsets[((S_800CD004_0 *)source)->unk_13];
            effect_state = (u8 *)effect + 0x20;
            height_delta = ((S_800CD004_0 *)source)->unk_88 - height_offset;
            effect_state->unk_0A = height_delta;
            ((S_800CD004_1 *)effect)->unk_20 = source;
            effect_state->unk_06 = 0xC;

            g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
            play_sound_if_enabled(0x50D);
        }
    } else {
        if (((S_800CD004_0 *)source)->unk_13 == 0) {
            display_fixed_item_action_message();
        }
        return 1;
    }
    return effect != NULL;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"


extern void adjust_source_value_and_finalize(void *context, const void *source);
extern s32 play_sound_if_enabled(s32 query_value);
extern s32 roll_chance_and_run_action(void *record, s16 chance, s8 action);
extern void wrap_position_and_set_state_value(s32);
extern s32 D_800DCF0C;
extern u8 D_800E1BF3[];



typedef struct S_800CD1A4_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD1A4_0_pre;   /* the 0x14 bytes before actor in roll_trap_hit_and_raise_event_520, addressed as actor[-1] */


typedef struct S_800CD1A4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD1A4_1;   /* owner in roll_trap_hit_and_raise_event_520 */

/* Roll the actor's trap check; on a hit mark it, play the burst at the owner's tile and raise event 0x520. */
s32 roll_trap_hit_and_raise_event_520(void *actor) {
    s32 chance;
    S_800CD1A4_1 *owner;

    chance = 0x40;
    if (trap_request_blocked != 0) {
        chance = 0x400;
    }
    if (roll_chance_and_run_action(actor, chance, 0x10) == 0) {
        if ((*(u8 *)((u8 *)&((EntityRec *)actor)->unk_10 + 3)) == 0) {
            display_fixed_item_action_message();
            return 1;
        }
        return 1;
    }
    adjust_source_value_and_finalize(actor, &D_800E1BF3);
    if ((*(u8 *)((u8 *)&((EntityRec *)actor)->unk_10 + 3)) == 0) {
        wrap_position_and_set_state_value(D_800DCF0C);
    }
    owner = ((S_800CD1A4_0_pre *)actor)[-1].unk_00;
    if (!(owner->unk_14 & 0x8000)) {
        spawn_randomized_particle_burst((owner->unk_24 << 6) | 0x20,
                      (owner->unk_25 << 6) | 0x20,
                      ((EntityRec *)actor)->unk_88, 0x808080, 0x20, 0);
        play_sound_if_enabled(0x520);
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CD294_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x74];
    s16 unk_9C;
} S_800CD294_0;   /* arg0 in check_trap_record_and_trigger_effects; pointer addresses record offset 0x14 */

typedef struct S_800CD294_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD294_1;


/* cfail-repair: tf7-phase1-cache-v3 */

extern s32 D_800DCF14;
extern void adjust_source_value_and_finalize(void *context, const void *source);
extern s32 play_sound_if_enabled(s32 query_value);
s32 roll_threshold_effect_variant_b(struct State *state_ptr, s16 limit_input, s8 byte_input);        /* extern */
void wrap_position_and_set_state_value(s32 state_value);                         /* extern */
extern u8 D_800E1C03[17];

/* Checks the record and triggers the associated visual and sound effects on success. */
s32 check_trap_record_and_trigger_effects(void *record_data) {
        /* Retail forwards the current argument registers into display_fixed_item_action_message
       untouched; this row never writes the fourth argument. */
    s32 check_mask;
    S_800CD294_1 *entity;

    check_mask = 0x40;
    if (trap_request_blocked != 0) {
        check_mask = 0x400;
    }
    if (roll_threshold_effect_variant_b(record_data, check_mask, 0x10) == 0) {
        if (((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_27 == 0) {
            display_fixed_item_action_message();
            return 1;
        }
        return 1;
    }
    adjust_source_value_and_finalize(record_data, D_800E1C03);
    if (((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_27 == 0) {
        wrap_position_and_set_state_value(D_800DCF14);
    }
    entity = ((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_00;
    if (!(entity->unk_14 & 0x8000)) {
        spawn_randomized_particle_burst((entity->unk_24 << 6) | 0x20, (entity->unk_25 << 6) | 0x20,
            ((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_9C, 0xFFFFFF, 0x40, 0);
        play_sound_if_enabled(0x612);
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


extern void adjust_source_value_and_finalize(void *context, const void *source);
extern s32 roll_threshold_effect_variant_a(struct State *state_ptr, s16 limit_input, s8 byte_input);
extern void wrap_position_and_set_state_value(s32 state_value);
extern s32 D_800DCF1C;
extern u8 D_800E1C14[17];



typedef struct S_800CD384_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD384_0_pre;   /* the 0x14 bytes before object in attempt_trap_request_eight_slots, addressed as object[-1] */


typedef struct S_800CD384_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD384_1;   /* entry in attempt_trap_request_eight_slots */

/* Run the 8-slot request for the object with the budget the global mode picks; on refusal give the fallback cue, otherwise apply the effect and raise the tile marker unless the owning entry is flagged. */
s32 attempt_trap_request_eight_slots(void *object) {
    s32 amount;
    S_800CD384_1 *entry;

    amount = 0x40;
    if (trap_request_blocked != 0) {
        amount = 0x400;
    }
    if (roll_threshold_effect_variant_a(object, amount, 8) == 0) {
        if (((EntityRec *)object)->flags14 & ACTOR_PARTY_MEMBER) {
            display_fixed_item_action_message();
            return 1;
        }
        return 1;
    }
    adjust_source_value_and_finalize(object, D_800E1C14);
    if ((*(u8 *)((u8 *)&((EntityRec *)object)->unk_10 + 3)) == 0) {
        wrap_position_and_set_state_value(D_800DCF1C);
    }
    entry = ((S_800CD384_0_pre *)object)[-1].unk_00;
    if (!(entry->unk_14 & 0x8000)) {
        spawn_randomized_particle_burst((entry->unk_24 << 6) | 0x20,
                      (entry->unk_25 << 6) | 0x20,
                      ((EntityRec *)object)->unk_88, 0x802080, 0x20, 1);
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_800CD474_0_pre {
    u16 unk_00;
} S_800CD474_0_pre;   /* the 0x2 bytes before arg0 in advance_falling_trap_effect, addressed as arg0[-1] */

typedef struct S_800CD474_0 {
    void *unk_00;
    s16 unk_04;
    u16 unk_06;
    s16 unk_08;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
} S_800CD474_0;   /* arg0 in advance_falling_trap_effect */

typedef struct S_800CD474_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CD474_1;   /* arg1 in advance_falling_trap_effect */

typedef struct S_800CD474_2 {
    u8 pad_00[0xC];
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
} S_800CD474_2;   /* arg2 in advance_falling_trap_effect */

typedef struct S_800CD474_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CD474_3;   /* global_base in advance_falling_trap_effect */


extern void initialize_timed_motion_step(); /* Unprototyped: two or three arguments; retail reads only the first two. */
extern s32 play_sound_if_enabled(s32 query_value);

/* Advance a falling effect through impact, flashing, and fade-out. */
void advance_falling_trap_effect(void *effect, S_800CD474_1 *motion, S_800CD474_2 *primitive) {
    s16 state;
    s32 color;
    u16 sound_timer;
    u16 hold_timer;
    u16 fade_timer;
    u16 target_y;

    state = ((S_800CD474_0 *)effect)->unk_04;
    if (state == 0) {
        motion->unk_14 += 0x20000;
        sound_timer = ((S_800CD474_0 *)effect)->unk_06 - 1;
        ((S_800CD474_0 *)effect)->unk_06 = sound_timer;
        if ((sound_timer << 16) == 0) {
            play_sound_if_enabled(0x701);
        }
        if ((motion->unk_08.at02.v + 0x10) >= ((S_800CD474_0 *)effect)->unk_0A.s) {
            initialize_timed_motion_step(8, 8);
            target_y = ((S_800CD474_0 *)effect)->unk_0A.u;
            motion->unk_14 = 0;
            motion->unk_08.at02.v = target_y;
            ((S_800CD474_0 *)effect)->unk_06 = 8;
            ((S_800CD474_0 *)effect)->unk_04 = (u16)((S_800CD474_0 *)effect)->unk_04 + 1;
            play_sound_if_enabled(0x612);
        }
        color = 0x404040;
        if (((S_800CD474_0 *)effect)->unk_0C & 1) {
            color = 0x808080;
        }
        primitive->unk_0C.at00.v = color;
    } else if (state == 1) {
        color = 0x404040;
        if (((S_800CD474_0 *)effect)->unk_0C & 1) {
            color = 0x808080;
        }
        primitive->unk_0C.at00.v = color;
        hold_timer = ((S_800CD474_0 *)effect)->unk_06 - 1;
        ((S_800CD474_0 *)effect)->unk_06 = hold_timer;
        if ((hold_timer << 16) <= 0) {
            ((S_800CD474_0 *)effect)->unk_06 = 0x10;
            primitive->unk_0C.at00.v = 0x808080;
            ((S_800CD474_0 *)effect)->unk_04 = (u16)((S_800CD474_0 *)effect)->unk_04 + 1;
            if (((S_800CD474_0 *)effect)->unk_08 == 0) {
                apply_mode_selected_trap_mask(((S_800CD474_0 *)effect)->unk_00, 0x10);
            }
        }
    } else {
        primitive->unk_0C.at00u.v = primitive->unk_0C.at00u.v -
                               (primitive->unk_0C.at00u.v / (s16)((S_800CD474_0 *)effect)->unk_06);
        primitive->unk_0C.at01.v = primitive->unk_0C.at01.v -
                               (primitive->unk_0C.at01.v / (s16)((S_800CD474_0 *)effect)->unk_06);
        primitive->unk_0C.at02.v = primitive->unk_0C.at02.v -
                               (primitive->unk_0C.at02.v / (s16)((S_800CD474_0 *)effect)->unk_06);
        fade_timer = ((S_800CD474_0 *)effect)->unk_06 - 1;
        ((S_800CD474_0 *)effect)->unk_06 = fade_timer;
        if ((fade_timer << 16) <= 0) {
            ((S_800CD474_0_pre *)effect)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
        }
    }
    motion->unk_08.at00.v += motion->unk_14;
    ((S_800CD474_0 *)effect)->unk_0C += 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"

extern s32 try_apply_effect_four_by_chance(void *actor, s32 chance, s32 action);            /* extern */


/* Apply the global-mode mask to the target with a fixed value of 0x10. */
void apply_mode_selected_trap_mask(void *target, s32 unused_mask)
{
    s32 mode_mask;

    mode_mask = 0x40;
    if (trap_request_blocked != 0) {
        mode_mask = 0x400;
    }
    try_apply_effect_four_by_chance(target, mode_mask, 0x10);
}
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"


extern s32 has_enough_available_runtime_nodes(s32 limit);
extern s32 play_sound_if_enabled(s32 query_value);
extern s32 generate_random_value(void);


extern u8 D_800CD474[];
extern u8 D_800E03E0[];



typedef struct S_800CD6E0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD6E0_0_pre;   /* the 0x14 bytes before arg0 in create_four_owner_sprite_effects, addressed as arg0[-1] */

typedef struct S_800CD6E0_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    u8 pad_14[0x74];
    u16 unk_88;
} S_800CD6E0_0;   /* arg0 in create_four_owner_sprite_effects */

typedef struct S_800CD6E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD6E0_1;   /* owner in create_four_owner_sprite_effects */

typedef struct S_800CD6E0_2 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800CD6E0_2;   /* (obj = func_8003FC64(2)) in create_four_owner_sprite_effects */

typedef struct S_800CD6E0_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x10];
    void * unk_20;
} S_800CD6E0_3;   /* obj in create_four_owner_sprite_effects */

typedef struct S_800CD6E0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD6E0_4;   /* prim in create_four_owner_sprite_effects */

typedef struct S_800CD6E0_6 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
} S_800CD6E0_6;   /* spr in create_four_owner_sprite_effects */

typedef struct S_800CD6E0_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
} S_800CD6E0_7;   /* link in create_four_owner_sprite_effects */

/* Conditionally creates four sprites around the source owner. */
s32 create_four_owner_sprite_effects(void *source, s16 slot_index, s32 slot_bits) {
    void *effect;
    S_800CD6E0_1 *owner;
    S_800CD6E0_4 *position;
    S_800CD6E0_6 *sprite;
    S_800CD6E0_7 *effect_link;
    s32 color;
    s16 *x_offsets;
    DungeonGlobalStatus *effect_counts;
    s32 effect_index;
    s32 random;
    s16 roll;
    s32 spawn_roll;
    s32 owner_coord;
    s32 owner_coord_2;
    s32 y_offset;
    s32 y_table;
    s32 y_entry;
    void *update_callback;

    if (trap_request_blocked != 0) {
        roll = 0;
    } else {
        random = generate_random_value() & 0xFFFF;
        if (((S_800CD6E0_0 *)source)->unk_03 != 0) {
            roll = random % ((S_800CD6E0_0 *)source)->unk_03;
        } else {
            roll = 0;
        }
    }

    if (roll < 0x30) {
        owner = ((S_800CD6E0_0_pre *)source)[-1].unk_00;
        if (owner->unk_14 & 0x8000) {
            apply_mode_selected_trap_mask(source, 0x10);
            return 1;
        }
        if (has_enough_available_runtime_nodes(4) == 0) {
            return 0;
        }

        effect_index = 0;
        update_callback = (void *)D_800CD474;
        effect_counts = &g_dungeon_status;
        x_offsets = dir_step_x;
        for (; effect_index < 4; x_offsets += 2) {
            ((S_800CD6E0_2 *)((effect = allocate_flagged_object_node(2))))->unk_10 = update_callback;
            register_node(effect, draw_linked_sprites_clipped);
            color = 0x808080;
            y_offset = effect_index << 2;

            owner_coord_2 = owner->unk_24 << 6;
            spawn_roll = *x_offsets;
            position = ((S_800CD6E0_3 *)effect)->unk_08;
            spawn_roll = (spawn_roll << 5) + 0x20;
            owner_coord_2 += spawn_roll;
            y_table = (u32)dir_step_y;
            y_entry = y_offset + y_table;
            y_table = owner_coord_2;
            position->unk_02 = y_table;
            owner_coord = owner->unk_25 << 6;
            spawn_roll = *(s16 *)y_entry;
            spawn_roll = (spawn_roll << 5) + 0x20;
            owner_coord += spawn_roll;
            position->unk_06 = owner_coord;
            position->unk_0A = ((S_800CD6E0_0 *)source)->unk_88 - 0x200;

            sprite = ((S_800CD6E0_3 *)effect)->unk_0C;
            spawn_roll = 0x1000;
            sprite->unk_1C = spawn_roll;
            spawn_roll = 0x2000;
            sprite->unk_1E = spawn_roll;
            spawn_roll = (s32)D_800E03E0;
            sprite->unk_08 = (void *)spawn_roll;
            sprite->unk_10 = 0x20;
            sprite->unk_16 = 0x400;
            sprite->unk_0C = color;
            sprite->unk_18 = (effect_index << 10) + 0x400;
            sprite->unk_14 |= 0xC;

            effect_link = (S_800CD6E0_7 *)((u8 *)effect + 0x20);
            effect_link->unk_0A = ((S_800CD6E0_0 *)source)->unk_88;
            ((S_800CD6E0_3 *)effect)->unk_20 = source;
            effect_link->unk_06 = 0xC;
            color = effect_index;
            effect_link->unk_08 = color;
            ((S_800CD6E0_3 *)effect)->unk_20 = source;
            effect_index++;
            effect_counts->activity_counts.parts.pending_action_count++;
            play_sound_if_enabled(0x50D);
        }

        return 1;
    }

    if (((S_800CD6E0_0 *)source)->unk_13 == 0) {
        display_fixed_item_action_message();
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

/* Object shape as seen by tick_trap_effect_countdown: a 32-bit handle/value field at
 * offset 0x00 and a 16-bit countdown field at offset 0x06. The 16-bit
 * "used"/flags field one halfword before the object (offset -2) is the
 * same shape referenced by the D_800814A0 sibling family (code5.c,
 * code9.c, w_8004FE78.c, ...). */
typedef struct S_800C81B0_a0 {
    s32 field_0;            /* 0x00 */
    u8 pad4[0x6 - 0x4];
    u16 field_6;             /* 0x06 */
} S_800C81B0_a0;

/* Shared counter/flags block; only the 16-bit field at offset 0xA is
 * touched here. */
extern s32 run_action_ten_if_eligible(ActorRecord *entity, s8 action_arg);

/* Ticks the object's countdown, releasing its handle and updating the shared counter and flags on expiry. */
void tick_trap_effect_countdown(S_800C81B0_a0 *object)
{
    s16 countdown;

    countdown = --object->field_6;
    if (countdown <= 0) {
        run_action_ten_if_eligible(object->field_0, 0x10);
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        ((u16 *)object)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"


extern s32 get_entity_effect_value();
extern void adjust_source_value_and_finalize(void *context, const void *source);
extern s16 set_or_clear_actor_status_slot();
extern u8 D_800E1C25[];

/* Runs action 0xA when eligible, using the prior state for the flagged callback. */
s32 run_action_ten_if_eligible(ActorRecord *entity, s8 action_arg) {
    u8 updated_state;
    u8 prior_state;
    u8 initial_state;

    initial_state = entity->species;
    if (initial_state != 0x2E) {
        if (((initial_state != 0x1E) || ((entity->unk_A4 == 0) && (entity->unk_AA == 0)))
            && ((get_entity_effect_value(entity, STATUS_FROG) << 0x10) == 0)) {
            prior_state = entity->species;
            if ((s16)set_or_clear_actor_status_slot(entity, STATUS_FROG, action_arg) >= 0) {
                if (entity->flags14 & ACTOR_PARTY_MEMBER) {
                    updated_state = entity->species;
                    entity->species = prior_state;
                    adjust_source_value_and_finalize(entity, D_800E1C25);
                    entity->species = updated_state;
                }
            }
        }
    }
    return 0;
}
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"


extern s32 get_entity_effect_value();
extern s32 has_enough_available_runtime_nodes(s32);
extern void spawn_vertical_particle_burst(s16 x, s16 y, s16 z, s32 sprite_id, s16 play_sound);
extern s32 play_sound_if_enabled(s32 query_value);
extern s32 generate_random_value(void);
extern s32 run_action_ten_if_eligible(ActorRecord *entity, s8 action_arg);
extern u8 D_800CD910[];
extern u8 D_800DF820[];

/* Step trigger: stop when all four 0x2C slots are taken, then roll the object's 0x3 chance and either spawn the 0x613 effect object over the owning tile (returning -1) or give the fallback cue. */
s32 trigger_step_trap_effect(void *object) {
    s16 index;
    s32 seed;
    s32 result;
    void *entry;
    void *effect;

    result = 1;
    if ((get_entity_effect_value(object, STATUS_FROG) << 0x10) == 0) {
        index = 0;
        for (; index < 4; index++) {
            if (*(s8 *)((u8 *)object + ((index << 0x10) >> 0xF) + 0x2C) == 0) {
                break;
            }
        }
        if (index >= 4) {
            return 1;
        }
        if (trap_request_blocked == 0) {
            seed = generate_random_value() & 0xFFFF;
            if (*(u8 *)((u8 *)object + 3) != 0) {
                index = seed % *(u8 *)((u8 *)object + 3);
            } else {
                index = 0;
            }
        } else {
            index = 0;
        }
        if (index < 0x40) {
            entry = *(void **)((u8 *)object - 0x14);
            if (*(u16 *)((u8 *)entry + 0x14) & 0x8000) {
                run_action_ten_if_eligible(object, 0x10);
                return -1;
            }
            result = 0;
            if (has_enough_available_runtime_nodes(2) != 0) {
                effect = allocate_flagged_object_node(2);
                *(u8 **)((u8 *)effect + 0x10) = D_800CD910;
                *(void **)((u8 *)effect + 0x20) = object;
                *(s16 *)((u8 *)effect + 0x26) = 0xC;
                spawn_vertical_particle_burst(
                    ((*(u8 *)((u8 *)entry + 0x24)) << 6) | 0x20,
                    ((*(u8 *)((u8 *)entry + 0x25)) << 6) | 0x20,
                    *(s16 *)((u8 *)object + 0x88), D_800DF820, 0);
                play_sound_if_enabled(0x613);
                {
                    g_dungeon_status.activity_counts.parts.pending_action_count++;
                }
                return -1;
            }
            return result;
        }
        if (*(u8 *)((u8 *)object + 0x13) == 0) {
            display_fixed_item_action_message();
        }
        return result;
    }
    return result;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern s32 get_entity_effect_value();
extern s32 generate_random_value(void);



/* Rolls an actor effect chance, queues a pending action on success, and displays the failure message
   otherwise. */
s32 roll_trap_trigger_chance(void *ptr, s32 unused1, s32 unused2, s32 unused3)
{
    s32 source_value;
    register s16 divisor;
    s32 remainder_value;
    s16 value;

    if (*(u8 *)((u8 *)ptr + 0x13) == 0) {
        value = 0;
        if (trap_request_blocked == 0) {
            source_value = generate_random_value() & 0xFFFF;
            if (((u8)(*(u8 *)((u8 *)ptr + 3))) != 0) {
                remainder_value = source_value % ((s16)((s32)((u8)(*(u8 *)((u8 *)ptr + 3)))));
                value = remainder_value;
            }
        }

        if (get_entity_effect_value(ptr, STATUS_FROG) << 16) {
            value = 0xFF;
        }

        if (value < 0x30) {
            *(u16 *)(((u8 *)dungeon_actor_ring_anchor) + 0xA2) |= 0x100;
            g_dungeon_status.activity_counts.parts.pending_action_count += 1;
        } else if (*(u8 *)((u8 *)ptr + 0x13) == 0) {
                        /* garbage-passthru: a3 is 10 left by get_entity_effect_value, not a caller-held C value. */
            display_fixed_item_action_message();
        }
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"




extern u8 D_800DF870[];

extern s32 generate_random_value(void);
extern s32 play_sound_if_enabled(s32 query_value);
extern void attempt_action_six_if_eligible(void *, s32, s32);
extern void spawn_vertical_particle_burst(s16 x, s16 y, s16 z, s32 sprite_id, s16 play_sound);

/* Applies a chance-based effect, with visual and sound feedback for unflagged entries. */
s32 apply_chance_based_trap_effect(void *state, s32 unused_1, s32 unused_2, s32 unused_3)
{
    s16 roll;
    s32 random_value;
    s32 effect_amount;
    Entry *entry;

    if (!trap_request_blocked &&
        (random_value = generate_random_value() & 0xffff,
         *(u8 *)((u8 *)state + 3))) {
        s32 remainder;
        remainder = random_value % *(u8 *)((u8 *)state + 3);
        roll = remainder;
    } else {
        roll = 0;
    }
    if (roll < 0x30) {
        effect_amount = 0x20;
        if (trap_request_blocked != 0) {
            effect_amount = 0x400;
        }
        attempt_action_six_if_eligible(state, effect_amount, 0x10);

        entry = *(Entry **)((u8 *)state - 0x14);
        if (!(entry->flags & 0x8000)) {
            spawn_vertical_particle_burst((entry->x << 6) | 0x20,
                          (entry->y << 6) | 0x20,
                          *(s16 *)((u8 *)state + 0x88), D_800DF870, 0);
            play_sound_if_enabled(0x70A);
            return 1;
        }
        return 1;
    }

    if (*(u8 *)((u8 *)state + 0x13) == 0) {
        display_fixed_item_action_message();
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"


typedef struct S_800CDE0C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    s32 unk_5C;
} S_800CDE0C_0;

/* Set flag 0x40000000 on every record in the circular list. */
void mark_all_actors_with_high_flag(void) {
    void *first_record;
    S_800CDE0C_0 *record;

    record = dungeon_actor_ring_anchor;
    first_record = record;
    do {
        record->unk_1C = (s32) (record->unk_1C | 0x40000000);
        record = record->unk_5C + 0x20;
    } while (record != first_record);
}
#include "modules/trap_effects_candidate.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"











/* Add amount to active entries at the given coordinates in both arrays. */
void add_value_to_active_entries_at_tile(s16 x, s16 y, s32 amount)
{
    s32 entry_index;
    s32 first_x;
    s32 first_y;
    s32 second_x;
    s32 second_y;
    DungeonItemEntry *first_active;
    ActiveEntry *second_active;
    FirstEntry *first_entry;
    SecondEntry *second_entry;

    entry_index = 0;
    first_x = x;
    first_y = y;
    do {
        first_entry = &dungeon_ground_item_positions[entry_index];
        first_active = &dungeon_ground_items[entry_index];
        if (first_active->kind != 0 &&
            first_entry->x == first_x &&
            first_entry->y == first_y) {
            first_entry->value += amount;
        }
        entry_index++;
    } while (entry_index < 64);

    entry_index = 0;
    second_x = x;
    second_y = y;
    do {
        second_active = &floor_objects[entry_index];
        second_entry = &dungeon_floor_object_positions[entry_index];
        if (second_active->active != 0 &&
            second_entry->x == second_x &&
            second_entry->y == second_y) {
            second_entry->value += amount;
        }
        entry_index++;
    } while (entry_index < 32);
}
#include "modules/trap_effects_candidate.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"











/* Sets the value of all active entries at the given coordinates in both tables. */
void set_value_of_active_entries_at_tile(s16 x, s16 y, s16 value) {
    FirstEntry *first_entry;
    DungeonItemEntry *first_status;
    SecondEntry *second_entry;
    ActiveEntry *second_status;
    s32 first_index;
    s32 first_x;
    s32 first_y;
    s32 second_x;
    s32 second_y;

    first_index = 0;
    first_x = x;
    first_y = y;
    do {
        first_entry = &dungeon_ground_item_positions[first_index];
        first_status = &dungeon_ground_items[first_index];
        if (first_status->kind != 0 && first_entry->x == first_x && first_entry->y == first_y) {
            first_entry->value = value;
        }
        first_index++;
    } while (first_index < 64);

    first_index = 0;
    second_x = x;
    second_y = y;
    do {
        second_status = &floor_objects[first_index];
        second_entry = &dungeon_floor_object_positions[first_index];
        if (second_status->active != 0 && second_entry->x == second_x && second_entry->y == second_y) {
            second_entry->value = value;
        }
        first_index++;
    } while (first_index < 32);
}

/* MECHANISM: Frameless leaf with exact 12-byte/24-byte record strides and narrow stores.
   Removing inherited keeps restored raw arg holds in t1/t2 and the exact 58-word shape.
   A guarded t0 pin for the second counter closed the final a1/a3/t0 role rotation. */
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    s16 x;
    s16 y;
    s16 initial[25];
    s16 target[25];
    s16 timer;
    s16 state;
    s16 delay;
    s16 flag;
} DungeonEffect;

typedef struct {
    u16 unused;
    s16 height;
    u16 other;
} DungeonTile;


extern void refresh_packed_grid_nibbles(void);
extern s32 play_sound_if_enabled(s32 query_value);
extern void mark_all_actors_with_high_flag(void);
extern void add_value_to_active_entries_at_tile(s16 x, s16 y, s32 amount);
extern void set_value_of_active_entries_at_tile(s16 x, s16 y, s16 value);
extern void initialize_timed_motion_step(); /* Unprototyped: two or three arguments; retail reads only the first two. */

/* Animate a 5x5 tile patch to target heights, wait, then restore its initial heights. */
void update_long_lived_trap_effect(DungeonEffect *effect) {
    s16 *target_ptr;
    s16 *initial_ptr;
    s16 target_ticks;
    s16 restore_ticks;
    s16 state;
    s32 target_step;
    s32 restore_step;
    MapGrid *grid;
    DungeonTile *tiles;
    s32 x_or_mask;
    s32 target_col;
    s32 snap_target_col;
    s32 restore_col;
    s32 snap_initial_col;
    s32 target_row;
    s32 restore_row;
    s32 origin_y;
    s32 row_shift;
    s32 origin_x;
    u16 *snap_target_ptr;
    u16 *snap_initial_ptr;
    u16 target_height;
    u16 initial_height;
    u16 delay_ticks;
    u8 *target_row_base;
    u8 *snap_target_base;
    u8 *initial_row_base;
    u8 *snap_initial_base;

    state = effect->state;
    if (state == 0) {
        grid = &g_game_work.map;
        tiles = ((DungeonTile *)grid->cells);
        target_row = 0;
        target_row_base = effect;
        do {
            target_col = 0;
            target_ptr = (s16 *)(target_row_base + 0x36);
            do {
                origin_y = effect->y;
                row_shift = grid->shiftX;
                origin_x = effect->x;
                target_step = (s32)(*target_ptr - tiles[((target_row + origin_y) << row_shift) + origin_x
                    + target_col].height) / effect->timer;
                target_ptr++;
                tiles[((target_row + origin_y) << row_shift) + origin_x + target_col].height =
                    (u16)tiles[((target_row + origin_y) << row_shift) + origin_x + target_col].height + target_step;
                add_value_to_active_entries_at_tile((s16)((u16)effect->x + target_col),
                              (s16)((u16)effect->y + target_row),
                              (s16)-target_step);
                target_col++;
            } while (target_col < 5);
            target_row++;
            target_row_base += 0xA;
        } while (target_row < 5);

        mark_all_actors_with_high_flag();
        if (!((u16)effect->timer & 7)) {
            play_sound_if_enabled(0x818);
        }
        target_ticks = (u16)effect->timer - 1;
        effect->timer = target_ticks;
        target_row = 0;
        if ((target_ticks << 16) <= 0) {
            snap_target_base = effect;
            do {
                snap_target_col = 0;
                snap_target_ptr = (u16 *)(snap_target_base + 0x36);
snap_target_tile:
                origin_y = effect->y;
                row_shift = grid->shiftX;
                origin_x = effect->x;
                tiles[((target_row + origin_y) << row_shift) + origin_x + snap_target_col].height = *snap_target_ptr;
                target_height = *snap_target_ptr;
                snap_target_ptr++;
                set_value_of_active_entries_at_tile((s16)((u16)effect->x + snap_target_col),
                              (s16)((u16)effect->y + target_row),
                              (s16)-target_height);
                snap_target_col++;
                if (snap_target_col < 5) {
                    goto snap_target_tile;
                }
                target_row++;
                snap_target_base += 0xA;
            } while (target_row < 5);
            refresh_packed_grid_nibbles();
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            dungeon_floor_flags &= 0xFFF7FFFF;
            effect->state++;
            return;
        }
    } else if (state == 1) {
        if (g_dungeon_status.flags & 0x10) {
            delay_ticks = (u16)effect->delay - 1;
            effect->delay = delay_ticks;
            if ((delay_ticks << 16) <= 0) {
                g_dungeon_status.activity_counts.parts.pending_action_count++;
                effect->timer = 0x20;
                initialize_timed_motion_step(0x20, 8);
                effect->state++;
                dungeon_floor_flags |= 0x80000;
            }
        }
    } else {
        grid = &g_game_work.map;
        tiles = ((DungeonTile *)grid->cells);
        restore_row = 0;
        initial_row_base = effect;
        do {
            restore_col = 0;
            initial_ptr = (s16 *)(initial_row_base + 4);
            do {
                origin_y = effect->y;
                row_shift = grid->shiftX;
                origin_x = effect->x;
                restore_step = (s32)(*initial_ptr - tiles[((restore_row + origin_y) << row_shift) + origin_x
                    + restore_col].height) / effect->timer;
                initial_ptr++;
                tiles[((restore_row + origin_y) << row_shift) + origin_x + restore_col].height =
                    (u16)tiles[((restore_row + origin_y) << row_shift) + origin_x + restore_col].height + restore_step;
                add_value_to_active_entries_at_tile((s16)((u16)effect->x + restore_col),
                              (s16)((u16)effect->y + restore_row),
                              (s16)-restore_step);
                restore_col++;
            } while (restore_col < 5);
            restore_row++;
            initial_row_base += 0xA;
        } while (restore_row < 5);

        if (!((u16)effect->timer & 7)) {
            play_sound_if_enabled(0x818);
        }
        restore_ticks = (u16)effect->timer - 1;
        effect->timer = restore_ticks;
        if ((restore_ticks << 16) <= 0) {
            restore_row = 0;
            snap_initial_base = effect;
            do {
                snap_initial_col = 0;
                snap_initial_ptr = (u16 *)(snap_initial_base + 4);
                for (;;) {
                    origin_y = effect->y;
                    row_shift = grid->shiftX;
                    origin_x = effect->x;
                    tiles[((restore_row + origin_y) << row_shift) + origin_x + snap_initial_col].height = *snap_initial_ptr;
                    initial_height = *snap_initial_ptr;
                    snap_initial_ptr++;
                    x_or_mask = (s16)((u16)effect->x + snap_initial_col);
                    set_value_of_active_entries_at_tile(x_or_mask,
                                  (s16)((u16)effect->y + restore_row),
                                  (s16)-initial_height);
                    snap_initial_col++;
                    if (snap_initial_col < 5) {
                        continue;
                    }
                    restore_row++;
                    snap_initial_base += 0xA;

                    break;
                }
            } while (restore_row < 5);
            refresh_packed_grid_nibbles();
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            x_or_mask = 0xBFF70000;
            if (effect->flag == 0) {
                x_or_mask = 0x7FF70000;
            }
            x_or_mask |= 0xFFFF;
            dungeon_floor_flags &= x_or_mask;
            *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        mark_all_actors_with_high_flag();
    }
    return;
}
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800CE4E8_0 {
    s16 unk_00;
    s16 unk_02;
    u8 pad_04[0x64];
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    union { u16 s; s16 u; } unk_6E;   /* accessed as both */
} S_800CE4E8_0;

typedef struct S_800CE4E8_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CE4E8_1;   /* global_base in create_dual_grid_trap_effect */


typedef struct {
    u8 pad_00[0x10];
    void *field_10;
    u8 pad_14[0xC];
    s16 field_20;
    s16 field_22;
} GridEffectObject;

extern void initialize_timed_motion_step(); /* Unprototyped: two or three arguments; retail reads only the first two. */
extern s32 random_dungeon_range_16(s32, s32);
extern s32 get_surface_height_at_coordinates(s32, s32);

extern u8 floor_trap_update_address[];

/* Creates a dungeon object with two 5x5 value grids and sets its effect flags. */
void * create_dual_grid_trap_effect(s32 center_x, s32 center_y, s16 unused_value, void *unused_data, s32 reverse_offset)
{
    u16 offset_mode;
    s32 reverse_flag;
    s32 col;
    s32 row;
    s32 tile_value;
    s32 rand_max;
    s32 origin_x;
    s32 origin_y;
    u16 *base_cell;
    u16 *offset_cell;
    s32 random_offset;
    u8 *base_row;
    u8 *grid_data;
    GridEffectObject *object;
    u8 *row_data;
    u8 *row_base;

    object = allocate_flagged_object_node(2);
    offset_mode = reverse_offset;
    if (object != NULL) {
        row = 0;
        reverse_flag = (s16)reverse_offset;
        grid_data = (u8 *)&object->field_20;
        row_data = grid_data;
        object->field_10 = floor_trap_update_address;
        object->field_20 = center_x - 2;
        ((S_800CE4E8_0 *)grid_data)->unk_02 = center_y - 2;
        do {
            col = 0;
            row_base = row_data;
            offset_cell = (u16 *)(row_data + 0x36);
            do {
                base_row = grid_data;
                origin_x = ((S_800CE4E8_0 *)base_row)->unk_00;
                origin_y = ((S_800CE4E8_0 *)base_row)->unk_02;
                tile_value = get_surface_height_at_coordinates(
                    ((col + origin_x) << 6) & 0xFFC0,
                    ((row + origin_y) << 6) & 0xFFC0);
                rand_max = 3;
                base_row = row_base + 4;
                base_cell = (u16 *)((unsigned long)(col * 2) +
                    (unsigned long)base_row);
                *base_cell = -tile_value;
                random_offset = random_dungeon_range_16(1, rand_max);
                random_offset = (random_offset & 0xFFFF) << 5;
                *offset_cell = random_offset;
                if (reverse_flag != 0) {
                    *offset_cell = -random_offset;
                }
                col++;
                *offset_cell += *base_cell;
                offset_cell++;
            } while (col < 5);
            row++;
            row_data += 0xA;
        } while (row < 5);

        ((S_800CE4E8_0 *)grid_data)->unk_6C = 0x10;
        ((S_800CE4E8_0 *)grid_data)->unk_68 = 0x20;
        ((S_800CE4E8_0 *)grid_data)->unk_6E.s = offset_mode;
        initialize_timed_motion_step(0x20, 8);

        if (((S_800CE4E8_0 *)grid_data)->unk_6E.u == 0) {
            dungeon_floor_flags |= 0x80080000;
        } else {
            dungeon_floor_flags |= 0x40080000;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
    return object;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/dungeon_floor.h"


extern void * create_dual_grid_trap_effect(s32 center_x, s32 center_y, s16 unused_value, void *unused_data, s32 reverse_offset);

/* Return success if either global high flag is set, otherwise test the record lookup. */
s32 check_trap_record_or_global_override(void *record) {
    void *source_record;

    if (dungeon_floor_flags & 0xC0000000) {
        return 1;
    }
    source_record = *(void **)((s8 *)record - 0x14);
    return create_dual_grid_trap_effect(((u8 *)source_record)[0x24], ((u8 *)source_record)[0x25], *(s16 *)((s8 *)record + 0x88),
        record, 0) != 0;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/dungeon_floor.h"

extern void * create_dual_grid_trap_effect(s32 center_x, s32 center_y, s16 unused_value, void *unused_data, s32 reverse_offset);

/* Checks the entity at its linked coordinates unless a global override is set. */
s32 check_linked_entity_or_global_override(void *entity) {
    void *position_record;

    if (dungeon_floor_flags & 0xC0000000) {
        return 1;
    }
    position_record = *(void **)((u8 *)entity - 0x14);
    return create_dual_grid_trap_effect(
        *(u8 *)((u8 *)position_record + 0x24),
        *(u8 *)((u8 *)position_record + 0x25),
        *(s16 *)((u8 *)entity + 0x88),
        entity,
        1) != 0;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CE748_0 {
    void * unk_00;
    u8 pad_04[0x13];
    u8 unk_17;
    u8 pad_18[0x10];
    s32 unk_28;
    u8 pad_2C[0x34];
    void * unk_60;
    void * unk_64;
    u8 pad_68[0x34];
    s16 unk_9C;
} S_800CE748_0;   /* record in update_trap_effect_grid; pointer addresses record offset 0x14 */

typedef struct S_800CE748_1 {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
} S_800CE748_1;   /* firstEntry in update_trap_effect_grid */

typedef struct S_800CE748_2 {
    u8 unk_00;
    u8 pad_01[0x1];
    s8 unk_02;
} S_800CE748_2;   /* secondEntry in update_trap_effect_grid */

typedef struct S_800CE748_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CE748_3;   /* objectData in update_trap_effect_grid */



void *get_unused_text_buffer(void);
u8 *expand_text_control_codes(u8 *src, u8 *dst);
void clear_byte_and_advance(s8 *byte_ptr);
void * write_text_byte_and_advance(s8 value, s8 *dest);
extern s32 play_sound_if_enabled(s32 query_value);
void display_text_with_fullwidth_adjustment(s8 *text);
s32 generate_random_value(void);
s32 is_linked_object_flagged_10000(void *);

extern u8 D_800E1B76[18];
extern u8 D_800E1B87[18];
extern u8 D_800E1B99[18];
extern u8 D_800E1BAA[18];

/* Rolls against two linked item slots, reduces eligible amounts, reports outcomes, and emits a burst
   on success. */
s32 update_trap_effect_grid(void *record, s32 unused1, s32 unused2, s32 unused3) {
    s32 randomValueSecond;
    s32 randomValueFirst;
    void *secondLookupValue;
    void *firstLookupValue;
    void *initialValue;
    s32 entryCode;
    void *currentValue;
    s16 entryFlags;
    s32 triggerFlags;
    s32 entryValue;
    S_800CE748_1 *firstEntry;
    S_800CE748_2 *secondEntry;
    S_800CE748_3 *objectData;

    triggerFlags = 0;
    entryFlags = 0;
    if (is_linked_object_flagged_10000(record) == 0) {
        s16 probability;
        s32 random_mod;
        firstEntry = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_60;
        if (firstEntry != NULL) {

            entryFlags = 1;
            if (firstEntry->unk_01 == 0xF) {
                s32 is_one;

                is_one = firstEntry->unk_00 == 1;
                entryFlags = is_one;
            }
            if (trap_request_blocked == 0) {
                                /* garbage-passthru: a1/a3 are residue from is_linked_object_flagged_10000, without a defined C value. */
                randomValueFirst = generate_random_value() & 0xFFFF;
                if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17 != 0) {
                    random_mod = randomValueFirst % ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17;
                    probability = random_mod;
                } else {
                    probability = 0;
                }
            } else {
                probability = 0;
            }
            if (probability < 0x40) {
                if (!(entryFlags & 1)) {
                    if (firstEntry->unk_02 >= -0x62) {
                        firstEntry->unk_02 = (s8) ((u8) firstEntry->unk_02 - 1);
                    }
                }
                triggerFlags = 1;
            }
        }
        secondEntry = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_64;
        if (secondEntry != NULL) {

            entryValue = secondEntry->unk_00;
            entryCode = entryValue & 0xFF;
            if ((entryCode == 1) || (entryCode == 7) || (((u32) (entryValue - 2) < 2U) != 0)) {
                entryFlags |= 2;
            }
            if (trap_request_blocked == 0) {
                                /* garbage-passthru: a1/a3 remain residue from earlier calls. */
                randomValueSecond = generate_random_value() & 0xFFFF;
                if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17 != 0) {
                    random_mod = randomValueSecond % ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17;
                    probability = random_mod;
                } else {
                    probability = 0;
                }
            } else {
                probability = 0;
            }
            if (probability < 0x40) {
                if (!(entryFlags & 2)) {
                    if (secondEntry->unk_02 >= -0x62) {
                        secondEntry->unk_02 = (s8) ((u8) secondEntry->unk_02 - 1);
                    }
                }
                triggerFlags |= 2;
            }
        }
    }
    if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_28 & 0x4000) {
        if ((triggerFlags << 0x10) == 0) {
                        /* garbage-passthru: a3 remains residue from earlier calls. */
            display_fixed_item_action_message();
        } else {
                        /* garbage-passthru: a3 remains residue from earlier calls. */
            initialValue = get_unused_text_buffer();
            currentValue = initialValue;
            if (triggerFlags & 1) {
                firstLookupValue = apply_type_based_entry_adjustments(((S_800CE748_0 *)((u8 *)record - 0x14))->unk_60, currentValue);
                {

                    if (!(entryFlags & 1)) {
                        currentValue = expand_text_control_codes(D_800E1B76, firstLookupValue);
                    } else {
                        currentValue = expand_text_control_codes(D_800E1B87, firstLookupValue);
                    }
                }
                if (triggerFlags & 2) {
                    currentValue = write_text_byte_and_advance(0xA, currentValue);
                }
            }
            if (triggerFlags & 2) {
                secondLookupValue = apply_type_based_entry_adjustments(((S_800CE748_0 *)((u8 *)record - 0x14))->unk_64, currentValue);
                {

                    if (!(entryFlags & 2)) {
                        currentValue = expand_text_control_codes(D_800E1B99, secondLookupValue);
                    } else {
                        currentValue = expand_text_control_codes(D_800E1BAA, secondLookupValue);
                    }
                }
            }
            clear_byte_and_advance(currentValue);
            display_text_with_fullwidth_adjustment(initialValue);
        }
    }
    if ((triggerFlags << 0x10) != 0) {
        objectData = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_00;
        if (!(objectData->unk_14 & 0x8000)) {
            spawn_randomized_particle_burst((objectData->unk_24 << 6) | 0x20, (objectData->unk_25 << 6) | 0x20,
                ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_9C, 0xC0C040, 0x20, 0);
            play_sound_if_enabled(0x615);
        }
    }
    return 1;
}
#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef void *(*SpawnFunc)(s32, s32, s32, s32);

typedef struct DungeonSlot {
    u8 unk0;
    u8 unk1;
    s8 count;
    u8 unk3;
} DungeonSlot;

typedef struct AreaRecord {
    u8 x;
    u8 unk1;
    u8 y;
    u8 unk3;
    u16 width;
    u16 height;
    u8 pad[12];
} AreaRecord;

extern u32 level_experience_table[];
extern u8 D_800E1C3A;
extern s8 entity_spawn_variant_code;


extern s32 has_enough_available_runtime_nodes(s32);
extern void initialize_timed_motion_step(); /* Unprototyped: two or three arguments; retail reads only the first two. */
extern void func_80042640(void *, s32);
extern void select_sound_stream(s32, s32);
extern void SD_Call(s32);
extern void display_formatted_context_message(); /* Unprototyped: one or three arguments; retail retains only the text context. */
extern s32 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern SpawnFunc load_monster_resource_data(s32 resource_id, u8 *resource_entry, s32 wait_for_read);
extern void retain_spawn_resource(s16 entry_type, s16 entry_key);
extern u8 *find_or_retain_sprite_resource_slot(s32, s32);
extern void raise_entity_level(void *, s32);
extern s32 play_sound_if_enabled(s32 query_value);
extern s32 generate_random_value(void);
extern s32 random_dungeon_range_16(s32, s32);

/* Spawns and levels monster den monsters, then advances the event delays and cleanup. */
void advance_monster_den_sequence(void *den_event) {
    u16 flags;
    s16 area_index;
    s16 state;
    u16 next_state;
    s32 tail_value;
    s32 y;
    s32 spawn_x;
    s32 area_x;
    s32 entry_y;
    s32 count;
    s16 retries_left;
    s32 monster_level;
    s32 monster_type;
    void *spawn_availability;
    u8 *area;
    u8 *monster_entry;
    void *monster;
    u32 *level_thresholds;
    u16 delay_timer;
    AreaRecord *areas;

    state = *(s16 *)(den_event + 6);
    if (state == 0) {
        u32 area_byte;

        area_byte = ((u8)reference_tile_object.room_index);
        area_index = (s8)area_byte;
        if ((s32)(area_byte << 24) >= 0) {
            count = ((DungeonSlot *)floor_objects)[*(s16 *)(den_event + 0xC)].count;
            if (count >= 0) {
                do {
                    if (has_enough_available_runtime_nodes(3) == 0) {
                        ((DungeonSlot *)floor_objects)[*(s16 *)(den_event + 0xC)].count -= count;
                        return;
                    }

                    entry_y = generate_random_value();
                    monster_entry = g_dungeon_status.monster_spawn_table + (entry_y & 0x1E);
                    monster_type = monster_entry[0];
                    monster_level = monster_entry[1];
                    spawn_availability = find_or_retain_sprite_resource_slot(monster_type, 1);
                    if (spawn_availability != 0) {
                        u8 * area_calc;
                        retries_left = 0xF;
                        areas = (AreaRecord *)dungeon_rooms;
                        area = (u8 *)&areas[area_index];
                        do {
                            spawn_x = random_dungeon_range_16(0, (u16)(((AreaRecord *)area)->width - 1));
                            y = random_dungeon_range_16(0, (u16)(((AreaRecord *)area)->height - 1));
                            area_x = area[0];
                            entry_y = area[2];
                            spawn_x += area_x;
                            entry_y += y;
                            y = entry_y;
                            entry_y = spawn_x;
                            entry_y &= 0xFF;
                            entry_y--;
                            if (!(((s16)get_offset_map_cell_value_and_flags(entry_y, (u8)y, 0,
                                                      &flags) == 0) ||
                                  ((flags & 0xB700) != 0))) {
                                break;
                            }
                            retries_left--;
                        } while (retries_left >= 0);

                        if (retries_left >= 0) {
                            s16 spawn_type;

                            entity_spawn_variant_code = 1;
                            spawn_type = monster_type;
                            monster = load_monster_resource_data(spawn_type, spawn_availability, 1)
                            (0, (u8)spawn_x, (u8)y, -0x400);
                            if (monster != 0) {
                                retain_spawn_resource(spawn_type, 1);
                                func_80042640(monster, spawn_type);
                                ((u8 *)monster)[0x43] = generate_random_value();
                                ((u8 *)monster)[0x12] = 0;

                                {

                                    area_calc = (u8 *)(level_experience_table);
                                    entry_y = ((u32 *)area_calc)[monster_level];
                                    area_calc = (u8 *)((((u32 *)area_calc) + 1));
                                    *(u32 *)((u8 *)monster + 0x18) = entry_y;
                                    entry_y = (u32)entry_y <
                                        ((u32 *)area_calc)[((u8 *)monster)[0x11]];
                                    if (entry_y == 0) {
                                        level_thresholds = (u32 *)area_calc;
                                        do {
                                            raise_entity_level(monster, 0);
                                        } while (level_thresholds[((u8 *)monster)[0x11]] <=
                                                 *(u32 *)((u8 *)monster + 0x18));
                                    }
                                }
                                ((u8 *)monster)[0x9A] = 0x16;
                                *(s32 *)((u8 *)monster + 0x8C) = 0;
                                *(s32 *)((u8 *)monster + 0x1C) &= 0xF7FBFFFF;
                                *(u16 *)((u8 *)monster + 0x92) -= 0x200;
                            }
                        }
                    }

                    count--;
                } while (count >= 0);
            }
        }
        next_state = *(u16 *)(den_event + 6);
        tail_value = 10;
        *(u16 *)(den_event + 4) = tail_value;
                 /* MATCH: keep the timer store before the state increment. */
        *(u16 *)(den_event + 6) = next_state + 1;
    } else if (state == 1) {
        delay_timer = *(u16 *)(den_event + 4) - 1;
        *(u16 *)(den_event + 4) = delay_timer;
        if ((s16)delay_timer >= 0) {
            return;
        }
        display_formatted_context_message(&D_800E1C3A);
        initialize_timed_motion_step(0xC, 0x18);
        play_sound_if_enabled(0x602);
        next_state = *(u16 *)(den_event + 6);
        tail_value = 0x10;
        *(u16 *)(den_event + 4) = tail_value;
                 /* MATCH: keep the timer store before the state increment. */
        *(u16 *)(den_event + 6) = next_state + 1;
    } else {
        delay_timer = *(u16 *)(den_event + 4) - 1;
        *(u16 *)(den_event + 4) = delay_timer;
        if ((s16)delay_timer < 0) {
            select_sound_stream(0, 1);
            SD_Call(0x200);
            *(s32 *)((u8 *)floor_objects + *(s16 *)(den_event + 0xC) * 4) = 0;
            {

                g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
            }
            *(u16 *)(den_event - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "engine/node.h"
struct State;

extern u8 D_800CEA44[];


extern s32 has_enough_available_runtime_nodes(s32 limit);
extern void SD_Call(s32 flags);

/* Clamp an indexed entry and create its node if processing succeeds. */
unsigned int clamp_entry_and_create_effect_node(void *object, s16 entry_index)
{
    s32 result;
    u8 *state_page;
    u8 *entry;
    register u8 *entries;
    DungeonGlobalStatus *state;
    void *node;
    int entry_ready;

    if (*((u8 *)object + 0x13) != 0) {
        return 1;
        result = 1;
    } else {
        state = &g_dungeon_status;
        entries = (u8 *)floor_objects;
        entry = (((s32)(entry_index << 0x10) >> 0xE) + (u8 *)entries);
        if ((s16)(((u16)state->monster_count) + *(s8 *)(entry + 2)) >= 0x21) {
            *(u8 *)(entry + 2) = 0x20 - *(u8 *)((u16 *)&state->monster_count);
        }

        result = has_enough_available_runtime_nodes(*(s8 *)(entry + 2) + 1);
        entry_ready = result != 0;
        if (entry_ready) {
            node = allocate_flagged_object_node(2);
            if (node != 0) {
                *(u8 **)((u8 *)node + 0x10) = D_800CEA44;
                *(s16 *)((u8 *)node + 0x2C) = entry_index;
                (*(u16 *)&state->activity_counts.parts.pending_action_count) += 1;
                SD_Call(0xB1);
            }
            result = node != 0;
        } else {
            result = 0;
        }
    }

    return result;
}
