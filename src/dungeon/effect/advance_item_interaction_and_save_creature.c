#include "shared/actor_status_flags.h"
#include "shared/dungeon_actor_callbacks.h"
#include "dungeon/effect/state.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/effect.h"
#include "dungeon/menu.h"
#include "dungeon/player/item.h"
#include "dungeon/player/object.h"
#include "dungeon/player/state.h"

typedef struct {
    u8 pad[0x29C];
    void *table[1];
} D_80010000_T;

typedef struct {
    s32 words[35];
} CreatureSave;

typedef struct S_func_800B1364_1 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x20];
    u8 *unk_BC;
    u8 *unk_C0;
} S_func_800B1364_1;

typedef struct S_func_800B1364_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_800B1364_2;

typedef struct S_func_800B1364_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 *unk_2C;
} S_func_800B1364_3;

typedef struct S_func_800B1364_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    void *unk_60;
    u8 pad_64[0x24];
    u16 unk_88;
    s16 unk_8A;
} S_func_800B1364_4;

typedef struct S_func_800B1364_5 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x1];
    u8 unk_13;
    s32 unk_14;
    u32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x6];
    u8 unk_26;
    u8 unk_27;
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0x19];
    u8 unk_43;
    u8 pad_44[0x1C];
    void *unk_60;
    u8 pad_64[0x4];
    u8 unk_68;
    u8 unk_69;
    u8 pad_6A[0x1E];
    s16 unk_88;
    u8 pad_8A[0xE];
    u16 unk_98;
} S_func_800B1364_5;

typedef struct S_func_800B1364_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_func_800B1364_7;

typedef struct S_func_800B1364_9 {
    u8 unk_00;
    s8 unk_01;
    s8 unk_02;
    union {
        s8 s8;
        u8 u8;
    } unk_03;
} S_func_800B1364_9;

typedef struct S_func_800B1364_10 {
    u8 pad_00[0xCC];
    s16 unk_CC;
} S_func_800B1364_10;

typedef struct S_func_800B1364_11 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_func_800B1364_11;

typedef struct S_func_800B1364_12 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_func_800B1364_12;

typedef struct S_func_800B1364_13 {
    s32 unk_00;
} S_func_800B1364_13;

typedef struct S_func_800B1364_14 {
    u16 unk_00;
} S_func_800B1364_14;

typedef struct S_func_800B1364_15 {
    s32 unk_00;
} S_func_800B1364_15;

typedef struct S_func_800B1364_17 {
    u8 pad_00[0x4];
    void *unk_04;
} S_func_800B1364_17;

typedef struct S_func_800B1364_18 {
    void *unk_00;
    void *unk_04;
} S_func_800B1364_18;

typedef struct S_func_800B1364_19 {
    u16 unk_00;
} S_func_800B1364_19;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 resolve_record_orientation_or_fallback();
s32 func_8003E188(s32, s32);
s32 func_80042640(void *, s32);
void set_sprite_animation_frame();
s32 strcpy(void *, s32);
void create_familiar_deployment_overlay();
void clear_slot_and_update_linked_state(s32 *slot);
s16 find_table_value_index();
void * get_unused_text_buffer(); /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */
u8 * expand_text_control_codes();
void * copy_four_text_bytes();
void *clear_byte_and_advance();
void * write_text_byte_and_advance();
u8 * append_entity_display_text();
void process_unflagged_linked_entries(s32 firstEntryBase);
void process_unflagged_linked_entries_alt(s32 firstNodeBase);
void unlink_entity_node();
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
void append_packed_action_record(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte);
#include "dungeon/item.h"
#include "engine/resource.h"
#include "slus.h"

void *(*load_monster_resource_data())(s32, u8, u8, s16);
u8 * find_or_retain_sprite_resource_slot();
void raise_entity_level(void *entity_data, s32 show_message);
s32 play_sound_if_enabled(s32 query_value);
s32 display_text_with_fullwidth_adjustment();
s32 generate_random_value(void);
void clear_selected_item_flag_400();
void *create_actor_value_popup();
#define D_80010000_PTR ((D_80010000_T *)0x80010000)
extern s32 monster_species_table;
extern s32 held_item_record;
extern u32 level_experience_table[];

extern s8 dungeon_event_pending_flag;
extern u8 D_800DD108[];
extern u8 D_800DD110[];
extern u8 familiar_save_alt_frames[];
extern u8 familiar_summon_frames[];
extern u8 familiar_save_restore_frames[];
extern s32 D_800814A0;
extern u8 familiar_save_frames[];
extern u8 familiar_defeat_text[];
extern u8 D_800E0A2A[9];
extern u8 D_800E0A33[15];
extern s8 entity_spawn_variant_code;
extern u8 active_actor_command_code;
extern void *familiar_record_slots[];
extern u8 familiar_record_storage[];

/* Advances the item interaction, spawning, initializing, and saving a linked creature. */
void advance_item_interaction_and_save_creature(S_func_800B1364_1 *action, S_func_800B1364_2 *position, S_func_800B1364_3 *sprite,
    S_func_800B1364_4 *actor) {
    s16 spawn_offset[3];
    s16 spawn_height;
    void *creature_variant;
    void *message_start;
    s32 wear;
    s32 event_flags;
    s32 item_word;
    s32 use_item;
    s16 use_item_test;
    void *message_end;
    s32 save_slot;
    u8 command;
    u16 sound_timer;
    u16 wait_timer;
    u16 sprite_flags;
    u16 final_flags;
    u32 experience;
    S_func_800B1364_12 *used_item;
    u8 *spawn_item;
    S_func_800B1364_12 *worn_item;
    u8 *direction_anim;
    GameWork *view_base;
    u8 state;
    u8 species;
    u8 next_state;
    S_func_800B1364_2 *creature_pos;
    DungeonGlobalStatus *summon_state;
    S_func_800B1364_9 *item_entry;
    S_func_800B1364_5 *stored_creature;
    S_func_800B1364_5 *finished_creature;
    S_func_800B1364_5 *saved_creature;
    S_func_800B1364_11 *input_command;
    S_func_800B1364_10 *item_effect;
    S_func_800B1364_5 *creature;
    S_func_800B1364_3 *creature_sprite;
    S_func_800B1364_5 *linked_creature;
    u32 *level_thresholds;
    u32 *level_table;
    void *save_data;
    S_func_800B1364_5 *hidden_creature;
    void *release_value;
    S_func_800B1364_7 *global_state = (S_func_800B1364_7 *)((s32 *)&g_game_work.draw_buffer);

    state = action->unk_9B;
    switch ((u32)(state)) {
    case 0:
    {
        view_base = &g_game_work;
        if ((((s32) (view_base->view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7) == 2) {
            sprite->unk_2C = D_800DD108;
            set_sprite_animation_frame(sprite, D_800DD108[((s32) (view_base->view.camera_rotation.parts.viewAngle + actor->unk_2A
                + 0x100) >> 9) & 7], 0, 1);
            next_state = action->unk_9B;
            action->unk_96 = 0x12U;
            action->unk_9B = (u8) (next_state + 1);
            return;
        }
    }
        actor->unk_2A = (s16) ((u16) actor->unk_2A + 0x200);
        return;
    case 1:
        sound_timer = action->unk_96 - 1;
        action->unk_96 = sound_timer;
        if ((sound_timer << 0x10) == 0) {
            play_sound_if_enabled(0x701);
        }
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        sprite->unk_2C = D_800DD110;
        set_sprite_animation_frame(sprite, D_800DD110[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7], 0, 1);
        action->unk_9B = (u8) (action->unk_9B + 1);
        if (!(((S_func_800B1364_14 *)&system_update_flags)->unk_00 & 1)) {
            build_floating_number_widget(0x22, 0xF2, 0xBA, 0x105, 0, 8);
            build_floating_number_widget(0x23, 0xE0, 0xCE, 0x104, 1, 8);
        }
        {
            u8 *item;
            S_func_800B1364_13 *saved_item;
            void *callback;
            item = action->unk_BC;
            action->unk_C0 = item;
            saved_item = (S_func_800B1364_13 *)action->unk_BC;
            item_word = saved_item->unk_00;
            callback = &dispatch_actor_state_handler;
            action->unk_8C = callback;
            held_item_record = item_word;
            return;
        }
    case 2:
        sprite_flags = sprite->unk_14;
        if (!(sprite_flags & 0xE000)) {
            DungeonGlobalStatus *control_state = &g_dungeon_status;
            control_state->flags = (u16) (control_state->flags | 4);
        } else {
            sprite->unk_14 = (u16) (sprite_flags | 0x6800);
        }
        if (g_dungeon_status.flags & 4) {
            return;
        }
        use_item = 0;
        if (((S_func_800B1364_14 *)0x80013714)->unk_00 & 1) {
            input_command = advance_monster_timed_sequence();
            if (input_command == NULL) {
                build_floating_number_widget(0x22, 0xF2, 0xBA, 0x105, 0, 8);
                build_floating_number_widget(0x23, 0xE0, 0xCE, 0x104, 1, 8);
                return;
            }
            command = input_command->unk_01 & 0xF8;
            active_actor_command_code = command;
            if (command != 0x60) {
                read_monster_script_entry();
                sprite->unk_2C = familiar_save_alt_frames;
                set_sprite_animation_frame(sprite, familiar_save_alt_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
                    0, 1);
                sprite->unk_14 = (u16) (sprite->unk_14 & 0xF7FF);
                action->unk_8C = NULL;
                action->unk_9B = 4U;
                return;
            }
            use_item = 1;
        } else if (global_state->unk_08 & 0x40) {
            use_item = 1;
        }
        use_item_test = use_item;
        if (use_item_test != 0) {
            append_packed_action_record(actor, 0x60, 0, 0);
            play_sound_if_enabled(0x500);
            sprite->unk_14 = (u16) (sprite->unk_14 & 0x97FF);
            action->unk_9B = 3U;
            wear = (generate_random_value() & 3) + 1;
            used_item = (S_func_800B1364_12 *)action->unk_BC;
            used_item->unk_02 = (s8) (used_item->unk_02 - wear);
            worn_item = (S_func_800B1364_12 *)action->unk_BC;
            if ((s8) worn_item->unk_02 <= 0) {
                worn_item->unk_02 = 0U;
                sprite->unk_2C = familiar_save_alt_frames;
                set_sprite_animation_frame(sprite, familiar_save_alt_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
                    0, 1);
                sprite->unk_14 = (u16) (sprite->unk_14 & 0xF7FF);
                action->unk_9B = 5U;
                actor->unk_8A = find_table_value_index(action->unk_BC);
            }
            create_actor_value_popup(0xA4, actor, (s16) (0x64 - (s8) ((S_func_800B1364_12 *)action->unk_BC)->unk_02), 0);
            return;
        }
        {
            s32 cancel_test;
            cancel_test = ((S_func_800B1364_14 *)&system_update_flags)->unk_00 & 1;
            if (cancel_test) {
                return;
            }
            cancel_test = global_state->unk_10 & 0x20;
            if (cancel_test == 0) {
                return;
            }
        }
        append_packed_action_record(actor, 0xA8, 0, 0);
        sprite->unk_2C = familiar_save_alt_frames;
        set_sprite_animation_frame(sprite, familiar_save_alt_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7], 0, 1);
        sprite->unk_14 = (u16) (sprite->unk_14 & 0xF7FF);
        play_sound_if_enabled(0x515);
        action->unk_8C = NULL;
        action->unk_9B = 4U;
        return;
    case 3:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        global_state = (S_func_800B1364_7 *)&g_dungeon_status.turn_scale;
        if (!(global_state->unk_02 & 2)) {
            process_unflagged_linked_entries_alt(actor->unk_5C);
            process_unflagged_linked_entries(actor->unk_5C);
            global_state->unk_02 = (u16) (global_state->unk_02 | 0x812);
        }
        action->unk_9B = 2U;
        return;
    case 4:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        clear_slot_and_update_linked_state(&held_item_record);
        {
            void *callback = handle_player_input;
            event_flags = ((S_func_800B1364_15 *)&dungeon_floor_flags)->unk_00 & 0xFFDFFFFF;
            action->unk_8C = callback;
            (*(s32 *)&dungeon_floor_flags) = event_flags;
        }
        return;
    case 5:
        item_effect = begin_holding_item(action, position, sprite, &held_item_record);
        if (item_effect == NULL) {
            return;
        }
        item_effect->unk_CC = 2;
        action->unk_9A = 0x22;
        action->unk_9B = 6U;
        return;
    case 6:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        if (resolve_record_orientation_or_fallback(sprite->unk_08, sprite, spawn_offset, 0) == 0) {
            spawn_offset[1] = 0;
            spawn_offset[0] = 0;
            spawn_offset[2] = 0 - (*((u8 *)entity_height_offsets));
        }
        spawn_directed_and_scattered_particles(position->unk_02 + spawn_offset[0], position->unk_06 + spawn_offset[1],
            position->unk_0A + spawn_offset[2]);
        action->unk_9B = (u8) (action->unk_9B + 1);
        return;
    case 7:
        spawn_item = action->unk_C0;
        entity_spawn_variant_code = 1;
        creature_variant = find_or_retain_sprite_resource_slot(*spawn_item, 2);
        creature = load_monster_resource_data(*action->unk_C0, creature_variant, 1)(2, sprite->unk_24, sprite->unk_25,
            (s16) (actor->unk_88 - 0x20));
        if (creature == NULL) {
            return;
        }
        func_8003E188(creature->unk_13, 0);
        clear_selected_item_flag_400(action->unk_C0);
        creature_sprite = ((S_func_800B1364_18 *)((u8 *)creature - 0x18))->unk_04;
        update_map_cell_flags_with_item_limit(creature_sprite->unk_24, creature_sprite->unk_25, 0x300);
        if (resolve_record_orientation_or_fallback(sprite->unk_08, sprite, spawn_offset, 0) == 0) {
            spawn_offset[1] = 0;
            spawn_offset[0] = 0;
            spawn_offset[2] = 0 - (*((u8 *)entity_height_offsets));
        }
        creature_pos = ((S_func_800B1364_18 *)((u8 *)creature - 0x18))->unk_00;
        creature_pos->unk_02 = (s16) ((u16) position->unk_02 + (u16) spawn_offset[0]);
        creature_pos->unk_06 = (s16) ((u16) position->unk_06 + (u16) spawn_offset[1]);
        spawn_height = (u16) position->unk_0A + (u16) spawn_offset[2];
        creature_pos->unk_0A = spawn_height;
        creature->unk_88 = spawn_height;
        actor->unk_60 = creature;
        func_80042640(creature, creature->unk_13);
        apply_actor_template_and_class(creature, creature->unk_13, 0);
        creature->unk_43 = 0xFF;
        creature->unk_60 = actor;
        creature->unk_1C = (s32) (creature->unk_1C | ACTOR_LIFTED);
        creature->unk_14 = (s32) (creature->unk_14 | 0x104000);
        linked_creature = actor->unk_60;
        linked_creature->unk_98 = (u16) (linked_creature->unk_98 | 0xC);
        strcpy((u8 *)creature + 0x34, runtime_get_mode_indexed_value(creature->unk_13));
        experience = level_experience_table[dungeon_actor_ring_anchor->level];
        level_thresholds = level_experience_table + 1;
        creature->unk_18 = experience;
        if (experience >= level_thresholds[creature->unk_11]) {
            level_table = level_thresholds;
            do {
                raise_entity_level(creature, 0);
            } while (level_table[creature->unk_11] <= (u32) creature->unk_18);
        }
        creature->unk_28 = (u8) creature->unk_29;
        creature->unk_26 = (u8) creature->unk_68;
        creature->unk_27 = (u8) creature->unk_69;
        if (!(((S_func_800B1364_14 *)&system_update_flags)->unk_00 & 1)) {
            u16 summon_count;
            DungeonGlobalStatus *summon_control;
            dungeon_event_pending_flag = 1;
            summon_control = &g_dungeon_status;
            summon_count = ((u16)summon_control->activity_counts.parts.pending_action_count);
            summon_control->activity_counts.parts.pending_action_count = (u16) (summon_count + 1);
        }
        message_start = get_unused_text_buffer();
        message_end = expand_text_control_codes(D_800E0A33, append_entity_display_text(creature, expand_text_control_codes(D_800E0A2A,
            expand_text_control_codes(((S_func_800B1364_17 *)((creature->unk_13 * 0x14) + monster_species_table))->unk_04,
            write_text_byte_and_advance(8, message_start)))));
        if (!((*(u16 *)(&system_update_flags)) & 1)) {
            message_end = copy_four_text_bytes(&familiar_defeat_text, write_text_byte_and_advance(0x4C, write_text_byte_and_advance(0x11, message_end)));
        }
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message_start);
        *(u16 *)((u8 *)action + 0x96) = 0x20U;
        action->unk_9B = (u8) (action->unk_9B + 1);
        if (!((*(u16 *)(&system_update_flags)) & 1)) {
            summon_state = &g_dungeon_status;
            if ((s16) ((u16)summon_state->activity_counts.parts.pending_action_count) < 2) {
                return;
            }
            summon_state->activity_counts.parts.pending_action_count = (u16) (((u16)summon_state->activity_counts.parts.pending_action_count) - 1);
            return;
        }
        summon_state = &g_dungeon_status;
        if (summon_state->activity_counts.parts.pending_action_count <= 0) {
            return;
        }
        summon_state->activity_counts.parts.pending_action_count = (s16) ((u16) summon_state->activity_counts.parts.pending_action_count - 1);
        return;
    case 8:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        wait_timer = action->unk_96 - 1;
        action->unk_96 = wait_timer;
        if ((wait_timer << 0x10) > 0) {
            if (!(sprite->unk_14 & 0x8000)) {
                if (global_state->unk_10 == 0) {
                    return;
                }
            }
        }
        sprite->unk_2C = familiar_summon_frames;
        direction_anim = familiar_summon_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7);
        set_sprite_animation_frame(sprite, *direction_anim, 0, 1);
        action->unk_9B = (u8) (action->unk_9B + 1);
        return;
    case 9:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        sprite->unk_2C = familiar_save_restore_frames;
        set_sprite_animation_frame(sprite, familiar_save_restore_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7], 0, 1);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x200);
        create_familiar_deployment_effect_with_owner_state(action, position, sprite);
        create_familiar_deployment_overlay(action, position, sprite);
        save_slot = find_first_unused_entity_entry();
        item_entry = D_80010000_PTR->table[actor->unk_8A];
        item_entry->unk_01 = 0x13;
        species = (u8) *action->unk_C0;
        item_entry->unk_03.s8 = save_slot;
        item_entry->unk_02 = 0;
        item_entry->unk_00 = species;
        familiar_record_slots[save_slot] = save_data = (save_slot * 0x8C) + familiar_record_storage;
        *(CreatureSave *)save_data = *(CreatureSave *)actor->unk_60;
        stored_creature = actor->unk_60;
        stored_creature->unk_1C = (s32) (stored_creature->unk_1C | 0x400000);
        hidden_creature = actor->unk_60;
        hidden_creature->unk_14 = (s32) (hidden_creature->unk_14 & 0xFFEFFFFF);
        play_sound_if_enabled(0x704);
        action->unk_9B = (u8) (action->unk_9B + 1);
        return;
    case 10:
        finished_creature = actor->unk_60;
        if (!(finished_creature->unk_1C & 0x800000)) {
            return;
        }
        unlink_entity_node(finished_creature);
        item_entry = D_80010000_PTR->table[actor->unk_8A];
        saved_creature = familiar_record_slots[item_entry->unk_03.u8 & 0x1F];
        saved_creature->unk_14 = (s32) (saved_creature->unk_14 & ~0x4000);
        release_value = actor->unk_60;
        ((S_func_800B1364_19 *)((u8 *)release_value - 2))->unk_00 =
            (u16) (((S_func_800B1364_19 *)((u8 *)release_value - 2))->unk_00 | 0x8000);
        D_800814A0 |= OBJECT_REMOVE_PENDING;
        sprite->unk_2C = familiar_save_frames;
        direction_anim = familiar_save_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7);
        set_sprite_animation_frame(sprite, *direction_anim, 0, 1);
read_next_state:
        action->unk_9B = (u8) (action->unk_9B + 1);
        return;
    case 11:
        final_flags = sprite->unk_14;
        if (!(final_flags & 0xE000)) {
            return;
        }
        sprite->unk_14 = (u16) (final_flags & 0xFDFF);
        action->unk_8C = handle_player_input;
        return;
    default:
        return;
    }
}
