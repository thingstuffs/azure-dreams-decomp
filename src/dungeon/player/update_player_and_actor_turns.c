#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/dir_step.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

struct Dst;
struct Elem;
typedef struct {
    u8 pad[0x14];
    u16 unk14;
} S_80048AC8;

typedef s32 (*Callback4)(void *, void *, void *, void *);
extern u8 D_80096384[];
extern void copy_words_forward(int *dst, int *src, int count);   /* extern */
extern void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);             /* extern */
extern void request_scene_dispatch_state(s16 requested_state);                     /* extern */
s16 get_entity_effect_value();                 /* extern */
extern void advance_sprite_animation_and_textures(void *entity);                      /* extern */
void texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags();     /* extern */
extern void step_actor_animation(S_80048AC8 *entity, void *slot_index);             /* extern */
extern void set_camera_targets(void *target_position, void *target_rotation, s32 transition_param); /* extern */
extern void queue_view_slot(int slot_selector);                     /* extern */
extern short SD_Call(int flags);                     /* extern */
s32 read_sound_mode_blocking_status();                         /* extern */
s32 func_800644B8();                             /* extern */
s32 update_sound_settings_from_pad(); /* extern */
s32 check_entity_relation();                 /* extern */
void *find_eligible_actor_at_tile_and_height();           /* extern */
void update_packed_map_levels();                            /* extern */
s32 set_monster_reachability_flag();                             /* extern */
s32 find_active_rect_containing_point();                           /* extern */
void apply_monster_koyaw_data();                 /* extern */
void tick_monster_spawn_timer();                            /* extern */
s32 can_entity_gain_level();                      /* extern */
s32 is_dungeon_action_enabled();                                /* extern */
s16 has_pending_actor_or_turn_action();                         /* extern */
s32 lookup_definition_pair_value();                          /* extern */
s32 advance_status_timers();                      /* extern */
s32 play_sound_if_enabled();                     /* extern */
s32 check_action_available_without_nearby_actor();                                /* extern */
s32 generate_random_value();                                /* extern */
void rotate_actor_movement_queue();                 /* extern */
void emit_scattered_effects_unless_blocked();                      /* extern */
s32 sample_terrain_surface_height();                   /* extern */
void create_record_with_effect_callback();                            /* extern */
s32 select_nearby_target_and_initialize_slot();    /* extern */
extern s8 scene_music_hold;
extern s16 floor_generation_state[3];
extern s16 dungeon_camera_targets[];
extern s8 dungeon_event_pending_flag;
extern u32 D_800DD160;
extern Callback4 D_800DD168[];
extern u16 D_800DD258;
extern u16 D_800DD25A;
extern u8 dungeon_button_latch;
extern s8 camera_transition_timer;
extern s32 player_turn_fraction;
extern s32 familiar_turn_counters_alias;
extern void *actor_update_node_cursor;
extern s32 D_800E4948;

typedef struct S_80089AA0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    u8 pad_20[0x98];
    s32 unk_B8;
    u8 pad_BC[0x9E4];
    union { u8 u; s8 s; } unk_AA0;   /* accessed as both */
} S_80089AA0_1;

typedef struct S_80089AA0_2 {
    u8 pad_00[0xB0];
    u16 unk_B0;
} S_80089AA0_2;   /* held_83178 in update_player_and_actor_turns */

typedef struct S_80089AA0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_3;   /* status_base in update_player_and_actor_turns */

typedef struct S_80089AA0_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s16 unk_0C;
} S_80089AA0_4;

typedef struct S_80089AA0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_5;

typedef struct S_80089AA0_6 {
    s32 unk_00;
} S_80089AA0_6;   /* &D_800E296C in update_player_and_actor_turns */

typedef struct S_80089AA0_7_pre {
    s16 unk_00;
    u8 pad_02[0x6];
} S_80089AA0_7_pre;   /* the 0x8 bytes before copy_dst in update_player_and_actor_turns, addressed as copy_dst[-1] */

typedef struct S_80089AA0_9 {
    s32 unk_00;
} S_80089AA0_9;   /* &D_800E3D70 in update_player_and_actor_turns */

typedef struct S_80089AA0_10 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80089AA0_10;

typedef struct S_80089AA0_11 {
    u8 pad_00[0x25];
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
} S_80089AA0_11;

typedef struct S_80089AA0_13 {
    u32 unk_00;
} S_80089AA0_13;   /* &D_800DD160 in update_player_and_actor_turns */

typedef struct S_80089AA0_14 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    u8 pad_60[0xC];
    s16 unk_6C;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80089AA0_14;

typedef struct S_80089AA0_16 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
    u8 pad_30[0x2C];
    void * unk_5C;
} S_80089AA0_16;   /* arg2 in update_player_and_actor_turns */

typedef struct S_80089AA0_17 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80089AA0_17;   /* table_entry in update_player_and_actor_turns */

typedef struct S_80089AA0_18 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80089AA0_18;   /* arg1 in update_player_and_actor_turns */

typedef struct S_80089AA0_19_pre {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
    u8 pad_04[0x10];
} S_80089AA0_19_pre;   /* 0x14-byte header immediately before the payload. */

typedef struct S_80089AA0_19 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x30];
    union { s32 i; void * p; } unk_5C;   /* accessed as both */
    u8 pad_60[0xA];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
    u8 pad_6E[0x3];
    s8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
    u16 unk_8A;
} S_80089AA0_19;

typedef struct S_80089AA0_20 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80089AA0_20;

typedef struct S_80089AA0_21 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
} S_80089AA0_21;   /* early_status in update_player_and_actor_turns */

typedef struct S_80089AA0_24 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_24;

typedef struct S_80089AA0_27 {
    u8 pad_00[0x3DE8];
    void * unk_3DE8;
} S_80089AA0_27;   /* root_page in update_player_and_actor_turns */

/* Updates the actor, applies movement and input, and processes dungeon actor turns. */
void update_player_and_actor_turns(void *in_actor, void *in_motion, void *in_sprite) {
    void *sprite_or_root;
    void *root;
    void *motion_or_count;
    GameWork *world_state;
    s32 repeat_pass;
    s32 (*update_callback)(void *, void *, void *, void *);
    s32 (*current_callback)(void *, void *, void *, void *);
    s32 *record_or_page;
    s32 *early_status;
    DungeonGlobalStatus *turn_status;
    s32 *loop_status;
    s32 *input_status;
    s32 facing;
    s32 state_or_address;
    s16 floor_height;
    s32 *previous_input;
    s32 flags_or_height;
    s32 height_limit;
    s32 height_or_callback;
    s32 turn_sign;
    s32 retry_callback;
    s32 callback_context;
    s32 companion_index;
    s32 room_index;
    u16 input_flags;
    u16 pass_flags;
    u16 slow_phase;
    u16 normal_phase;
    u16 loop_flags;
    u16 cleared_pass_flags;
    u16 final_flags;
    u16 turn_flags;
    u16 air_flags;
    u16 fall_flags;
    u16 phase_flags;
    u16 next_flags;
    u32 *companion_fraction;
    u32 actor_fraction;
    u32 actor_remainder;
    u32 companion_total;
    u32 companion_remainder;
    u8 actor_limit;
    u8 companion_limit;
    s32 pending_low;
    u8 action_id;
    u8 pending_high;
    s32 companion_points;
    S_80089AA0_11 *companion;
    void *next_link;
    S_80089AA0_20 *linked_sprite;
    S_80089AA0_14 *reset_actor;
    void *companion_slot;
    void *linked_actor;
    void *actor;
    S_80089AA0_2 *world_object;
    void *companion_counters;
    S_80089AA0_3 *status_base;
    DungeonGlobalStatus *callback_status;
    DungeonGlobalStatus *tail_status;
    void *input_snapshot;
    void *next_record;
    u16 initial_flags;

    linked_actor = in_actor;
    world_state = &g_game_work;
    initial_flags = system_update_flags;
    sprite_or_root = in_sprite;
    actor = linked_actor;
    world_object = (u8 *)world_state + 0x18;
    if (initial_flags & 4) {
        record_or_page = (s32 *)0x80080000;
        if ((dungeon_button_latch == 0) && (((s32)world_state->pressed_buttons) != 0)) {
            dungeon_button_latch = 1;
            request_scene_dispatch_state(3);
            return;
        }
    } else {
        record_or_page = (s32 *)0x80080000;
    }
    if ((((S_80089AA0_1 *)record_or_page)->unk_AA0.u != 0) && (dungeon_button_latch == 0) && (read_sound_mode_blocking_status(1) == 0)) {
        SD_Call(0x200);
        ((S_80089AA0_1 *)record_or_page)->unk_AA0.s = 0;
        scene_music_hold = 1;
    }
    if ((*(u16 *)0x80013714) & 4) {
        s16 *effect_data;
        s32 effect_angle;
        s32 angle_step;
        s32 effect_flags;
        effect_data = dungeon_camera_targets;
        effect_flags = *(s32 *)((u8 *)&floor_generation_state);
        effect_angle = effect_data[2];
        if (effect_flags & 1) {
            angle_step = effect_angle + 8;
        } else {
            angle_step = effect_angle - 8;
        }
        effect_data[2] = (s16) angle_step;
        g_game_work.view.slot[2].callback = 0;
        queue_view_slot(1);
        set_camera_targets(0, (s16 *)((u8 *)&dungeon_event_pending_flag - 0xEF), 2);
    }
    (*(s16 *)((u8 *)linked_actor + 0x9E)) = (s16) (((u16) world_object->unk_B0 >> 9) & 7);
    status_base = &g_dungeon_status.turn_scale;
    status_base->unk_02 = (u16) (status_base->unk_02 & 0xFFCF);
    previous_input = &D_800E4948;
    if ((status_base->unk_08 == D_800E4948) && (status_base->unk_0C == ((S_80089AA0_4 *)previous_input)->unk_04)
        && (status_base->unk_10 == ((S_80089AA0_4 *)previous_input)->unk_08)
        && (status_base->unk_14 == ((S_80089AA0_4 *)previous_input)->unk_0C) && !(system_update_flags & 8)
        && ((action_id = (*(u8 *)((u8 *)linked_actor + 0x9A))) != 0x17) && (action_id != 0x27) && (action_id != 0x29)
        && (dungeon_event_pending_flag == 0) && ((status_base->unk_0C != 0) || (status_base->unk_10 != 0) || (status_base->unk_14 != 0)
        || (status_base->unk_08 != 0))) {
        D_800DD160 += 1;
    } else {
        D_800DD160 = 0;
    }
    input_snapshot = ((u8 *)(&g_dungeon_status.activity_counts.parts.pending_movement_count));
    copy_words_forward(&D_800E4948, input_snapshot, 4);
    input_status = (u8 *)input_snapshot - 8;
    if ((((S_80089AA0_5 *)input_status)->unk_0C == 0) && (((S_80089AA0_5 *)input_status)->unk_10 == 0)) {
        input_flags = ((S_80089AA0_5 *)input_status)->unk_02;
        if (!(input_flags & 8) && (((S_80089AA0_5 *)input_status)->unk_08 == 0)
            && (((S_80089AA0_5 *)input_status)->unk_14 == 0) && !(((S_80089AA0_6 *)(&dungeon_floor_flags))->unk_00 & 0x100000)
            && (((S_80089AA0_5 *)input_status)->unk_0A == 0) && !(input_flags & 0x2E01)) {
            if ((set_monster_reachability_flag(input_flags) << 0x10) != 0) {
                create_record_with_effect_callback();
            }
            turn_flags = ((S_80089AA0_5 *)input_status)->unk_02;
            if (turn_flags & 2) {
                ((S_80089AA0_5 *)input_status)->unk_02 = (u16) ((turn_flags & 0xFFFD) | 0x20);
                tick_monster_spawn_timer();
                state_or_address = get_entity_effect_value(actor, 7);
                turn_sign = state_or_address;
                state_or_address = 0x80;
                if (turn_sign <= 0) {
                    state_or_address = 0x100;
                    if (turn_sign < 0) {
                        state_or_address = 0x200;
                    }
                    ((S_80089AA0_7_pre *)input_snapshot)[-1].unk_00 = (s16) state_or_address;
                } else {
                    ((S_80089AA0_7_pre *)input_snapshot)[-1].unk_00 = (s16) state_or_address;
                }
                if (!(system_update_flags & 8)) {
                    g_dungeon_status.turn_counter = (u16) (g_dungeon_status.turn_counter + 1);
                    actor_fraction = ((S_80089AA0_9 *)(&player_turn_fraction))->unk_00 + (*(u8 *)((u8 *)actor + 0x29));
                    player_turn_fraction = (s32)actor_fraction;
                    turn_sign = (*(u8 *)((u8 *)actor + 0x28));
                    if (actor_fraction >= 0x101U) {
                        do {
                            actor_remainder = (u32)player_turn_fraction - 0x100;
                            player_turn_fraction = (s32)actor_remainder;
                            turn_sign += 1;
                        } while (actor_remainder >= 0x101U);
                    }
                    actor_limit = (*(u8 *)((u8 *)actor + 0x29));
                    if ((s32) actor_limit < (s32) turn_sign) {
                        turn_sign = actor_limit;
                    }
                    (*(u8 *)((u8 *)actor + 0x28)) = turn_sign;
                    companion_index = 1;
                    companion_counters = &familiar_turn_counters_alias;
                    companion_fraction = (u32 *)((u8 *)companion_counters + 4);
                    companion_slot = linked_actor + 4;
                    do {
                        companion = ((S_80089AA0_10 *)companion_slot)->unk_AC;
                        if ((companion != 0) && (companion->unk_25 != 0)) {
                            companion_total = *companion_fraction + companion->unk_29;
                            *companion_fraction = companion_total;
                            companion_points = companion->unk_28;
                            if (companion_total >= 0x101U) {
                                do {
                                    companion_remainder = *companion_fraction - 0x100;
                                    *companion_fraction = companion_remainder;
                                    companion_points += 1;
                                } while (companion_remainder >= 0x101U);
                            }
                            companion_limit = companion->unk_29;
                            if ((s32) companion_limit < (s32) companion_points) {
                                companion_points = companion_limit;
                            }
                            companion->unk_28 = companion_points;
                        }
                        companion_fraction -= 1;
                        companion_index -= 1;
                        companion_slot -= 4;
                    } while (companion_index >= 0);
                }
                if ((*(s32 *)((u8 *)actor + 0x1C)) & 0x800) {
                    slow_phase = (*(u16 *)((u8 *)linked_actor + 0xF8));
                    (*(u16 *)((u8 *)linked_actor + 0xF8)) = (u16) (slow_phase + 1);
                    (*(s8 *)((u8 *)actor + 3)) = (s8) ((func_800644B8((s16) slow_phase) >> 8) + 0x30);
                } else {
                    normal_phase = (*(u16 *)((u8 *)linked_actor + 0xF8));
                    (*(u16 *)((u8 *)linked_actor + 0xF8)) = (u16) (normal_phase + 1);
                    (*(s8 *)((u8 *)actor + 3)) = (s8) ((func_800644B8((s16) normal_phase) >> 7) + 0x40);
                }
                (*(s32 *)((u8 *)linked_actor + 0x128)) = (s32) (generate_random_value() & 0xFFFF);
                if (!(system_update_flags & 8)) {
                    (*(u16 *)((u8 *)linked_actor + 0x118)) = (u16) ((*(u16 *)((u8 *)linked_actor + 0x118)) + 1);
                }
                advance_status_timers(actor);
                current_callback = (*(s32 (**)(void *, void *, void *, void *))((u8 *)linked_actor + 0x8C));
                if (current_callback == (Callback4)D_80096384) {

                    if ((get_entity_effect_value(actor, 0xA) << 0x10) == 0) {

                        state_or_address = (s32)handle_player_input;
                        (*(Callback4 *)((u8 *)linked_actor + 0x8C)) = (Callback4)state_or_address;
                        (&g_dungeon_status)->flags = (u16)((&g_dungeon_status)->flags | 4);
                    }

                } else if (current_callback == (Callback4)handle_player_input) {
                    if ((get_entity_effect_value(actor, 0xA) << 0x10) != 0) {
                        (*(Callback4 *)((u8 *)linked_actor + 0x8C)) = (Callback4)D_80096384;
                        (&g_dungeon_status)->flags = (u16)((&g_dungeon_status)->flags | 4);
                    }
                }
            }

            (&g_dungeon_status)->flags =
                (u16)((&g_dungeon_status)->flags & 0xBFFB);
            (*(u32 *)((u8 *)actor + 0x14)) &= 0x7FFE7FFF;
        } else {
            g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 4);
        }
    } else {
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 4);
    }
    if (!(system_update_flags & 8)) {
        if (((*(u8 *)((u8 *)linked_actor + 0x9A)) != 0x17) && (dungeon_event_pending_flag == 0)
            && ((u32) ((S_80089AA0_13 *)(&D_800DD160))->unk_00 >= 0x385U)) {
            reset_actor = dungeon_actor_ring_anchor;
            D_800DD160 = 0;
            do {
                reset_actor->unk_6C = 0;
                reset_actor->unk_71 = (u8) (reset_actor->unk_71 & 0x7F);
                reset_actor = reset_actor->unk_5C + 0x20;
            } while (reset_actor != dungeon_actor_ring_anchor);
            {
                DungeonGlobalStatus *reset_base;
                reset_base = &g_dungeon_status;
                reset_base->activity_counts.parts.pending_movement_count = 0;
                reset_base->activity_counts.parts.pending_action_count = 0;
                reset_base->trap_counts.parts.pending_trap_count = 0;
                reset_base->active_actor = 0;
                reset_base->pending_display_owner = 0;
                reset_base->flags = 0U;
            }
        }
        if (!((*(u16 *)0x80013714) & 8) && (!(g_dungeon_status.flags & 4)
            || (((S_80089AA0_6 *)(&dungeon_floor_flags))->unk_00 & 0x40) || ((*(u8 *)((u8 *)linked_actor + 0x9A)) == 0x17))) {
            dungeon_floor_flags = (s32)(dungeon_floor_flags & ~0x40);
            if ((select_nearby_target_and_initialize_slot(actor - 0x20, in_motion, 8, dungeon_camera_targets[3]) << 0x10) != 0) {
                g_game_work.view.slot[2].callback = 0;
                queue_view_slot(1);
                set_camera_targets(0, dungeon_camera_targets, 2);
            } else {
                camera_transition_timer = 0;
            }
        }
    }
    if (!((*(s32 *)((u8 *)actor + 0x1C)) & 0x20)) {
        if ((get_entity_effect_value(actor, 0xA) << 0x10) != 0) {
            advance_sprite_animation_and_textures(sprite_or_root);
        } else {
            step_actor_animation(sprite_or_root, 1);
        }
    } else {
        ((S_80089AA0_16 *)sprite_or_root)->unk_14 = (u16) (((S_80089AA0_16 *)sprite_or_root)->unk_14 | 0x6000);
    }
    update_callback = (*(s32 (**)(void *, void *, void *, void *))((u8 *)linked_actor + 0x8C));
    if (update_callback != 0) {
        update_callback(linked_actor, in_motion, sprite_or_root, actor);
    }
    D_800DD168[(*(u8 *)((u8 *)linked_actor + 0x9A))](linked_actor, in_motion, sprite_or_root, actor);
    facing = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
    /*
     * Original bug: egg heating clears the mirror bit while updating the cached direction. After canceling, walking in
     * that same direction skips restoring the bit, so Koh walks backward. Refresh it when heating ends too.
     * Found and documented by the Azure Dreams community
     * (adrando.com/guide/bugs.html).
     */
    if ((*(s16 *)((u8 *)linked_actor + 0x94)) != facing) {
        if ((get_entity_effect_value(actor, 0xA) << 0x10) != 0) {
            select_record_entry_and_value(sprite_or_root, ((void **)((S_80089AA0_16 *)sprite_or_root)->unk_2C)[facing],
                ((S_80089AA0_16 *)sprite_or_root)->unk_04);
        } else {
            texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(sprite_or_root, ((u8 *)((S_80089AA0_16 *)sprite_or_root)->unk_2C)[facing],
                ((S_80089AA0_16 *)sprite_or_root)->unk_04, 1);
        }
        (*(s16 *)((u8 *)linked_actor + 0x94)) = facing;
        if (((*(u8 *)((u8 *)linked_actor + 0x9A)) != 0x22) && (dir_sprite_flag[facing] != 0)) {
            ((S_80089AA0_16 *)sprite_or_root)->unk_14 = (u16)(((S_80089AA0_16 *)sprite_or_root)->unk_14 | 1);
        } else {
            ((S_80089AA0_16 *)sprite_or_root)->unk_14 = (u16) (((S_80089AA0_16 *)sprite_or_root)->unk_14 & 0xFFFE);
        }
    }
    room_index = find_active_rect_containing_point(((S_80089AA0_16 *)sprite_or_root)->unk_24, ((S_80089AA0_16 *)sprite_or_root)->unk_25);
    {
        s32 table_index;
        void *table_base;
        S_80089AA0_17 *table_entry;
        ((S_80089AA0_16 *)sprite_or_root)->unk_26 = room_index;
        room_index <<= 24;
        table_index = room_index >> 24;
        if (table_index >= 0) {
            table_base = dungeon_rooms;
            table_entry = table_base + (table_index * 0x14);
            table_entry->unk_0C = (u16) (table_entry->unk_0C | 1);
        }
    }
    apply_monster_koyaw_data((*(s32 *)((u8 *)actor + 0x1C)), sprite_or_root + 0xC);
    motion_or_count = in_motion;
    if (!((*(s32 *)((u8 *)actor + 0x14)) & 0x100000)) {
        ((S_80089AA0_18 *)motion_or_count)->unk_00.at00.v = (s32) (((S_80089AA0_18 *)motion_or_count)->unk_00.at00.v
            + ((S_80089AA0_18 *)motion_or_count)->unk_0C);
        ((S_80089AA0_18 *)motion_or_count)->unk_04.at00.v = (s32) (((S_80089AA0_18 *)motion_or_count)->unk_04.at00.v
            + ((S_80089AA0_18 *)motion_or_count)->unk_10);
        if (!((*(u16 *)((u8 *)linked_actor + 0x98)) & 8)) {
            ((S_80089AA0_18 *)motion_or_count)->unk_14 = (s32) (((S_80089AA0_18 *)motion_or_count)->unk_14
                + ((*(s8 *)((u8 *)linked_actor + 0x9D)) * 0x14000));
            (*(s8 *)((u8 *)linked_actor + 0x9D)) = (s8) ((u8) (*(s8 *)((u8 *)linked_actor + 0x9D)) + 1);
        }
        (*(s32 *)((u8 *)linked_actor + 0x90)) = (s32) ((*(s32 *)((u8 *)linked_actor + 0x90))
            + ((S_80089AA0_18 *)motion_or_count)->unk_14);
        floor_height = sample_terrain_surface_height(((S_80089AA0_18 *)motion_or_count)->unk_00.at02.v,
            ((S_80089AA0_18 *)motion_or_count)->unk_04.at02.v, (s16) ((*(u16 *)((u8 *)actor + 0x88)) - 0x20));
        if (floor_height < 0x200) {
            if (((*(s16 *)((u8 *)linked_actor + 0x92)) + (s16) (*(u16 *)((u8 *)actor + 0x88))) >= floor_height) {
                if (((*(u16 *)((u8 *)linked_actor + 0x98)) & 4) || (((S_80089AA0_18 *)motion_or_count)->unk_14 < 0)) {
                    (*(u16 *)((u8 *)linked_actor + 0xA2)) =
                        (u16)((*(u16 *)((u8 *)linked_actor + 0xA2)) & 0xFFEF);
                } else {
                    (*(s32 *)((u8 *)linked_actor + 0x90)) = 0;
                    ((S_80089AA0_18 *)motion_or_count)->unk_14 = 0;
                    (*(s8 *)((u8 *)linked_actor + 0x9D)) = 0;
                    if (!((*(u16 *)((u8 *)linked_actor + 0xA2)) & 0x10)) {
                        if (!(((S_80089AA0_6 *)(&dungeon_floor_flags))->unk_00 & 0x80000)) {
                            play_sound_if_enabled(0x508);
                        }
                        emit_scattered_effects_unless_blocked(motion_or_count);
                    }
                    (*(u16 *)((u8 *)linked_actor + 0xA2)) = (u16) ((*(u16 *)((u8 *)linked_actor + 0xA2)) | 0x10);
                }
                (*(u16 *)((u8 *)linked_actor + 0xA2)) =
                    (u16)((*(u16 *)((u8 *)linked_actor + 0xA2)) & 0xF7FF);
            } else {
                air_flags = (*(u16 *)((u8 *)linked_actor + 0xA2));
                if (air_flags & 0x800) {
                    (*(u16 *)((u8 *)linked_actor + 0xA2)) = (u16) (air_flags & 0xFFEF);
                }
                (*(u16 *)((u8 *)linked_actor + 0xA2)) = (u16) ((*(u16 *)((u8 *)linked_actor + 0xA2)) | 0x800);
            }
            flags_or_height = (*(s32 *)((u8 *)actor + 0x1C));
            if (flags_or_height & 0x40000000) {

                state_or_address = flags_or_height & 0xBFFFFFFF;
                height_or_callback = (*(u16 *)((u8 *)actor + 0x88));
                (*(s32 *)((u8 *)actor + 0x1C)) = state_or_address;
                height_limit = (*(u16 *)((u8 *)actor + 0x88));
                height_limit -= 0x20;
                height_limit <<= 16;
                height_limit >>= 16;
                (*(u16 *)((u8 *)actor + 0x8A)) = height_or_callback;
                flags_or_height = (s16)sample_terrain_surface_height((((S_80089AA0_16 *)sprite_or_root)->unk_24 << 6) | 0x20,
                    (((S_80089AA0_16 *)sprite_or_root)->unk_25 << 6) | 0x20, height_limit);
                (*(s16 *)((u8 *)linked_actor + 0x92)) = (s16) ((u16) (*(s16 *)((u8 *)linked_actor + 0x92))
                    + ((*(u16 *)((u8 *)actor + 0x88)) - flags_or_height));
                (*(u16 *)((u8 *)actor + 0x88)) = (u16) flags_or_height;
                if (g_dungeon_status.flags & 0x80) {
                    (*(s32 *)((u8 *)linked_actor + 0x90)) = 0;
                    ((S_80089AA0_18 *)motion_or_count)->unk_14 = 0;
                    (*(s8 *)((u8 *)linked_actor + 0x9D)) = 0;
                    (*(u16 *)((u8 *)linked_actor + 0xA2)) =
                        (u16)((*(u16 *)((u8 *)linked_actor + 0xA2)) | 0x10);
                }
            }
        } else {
            fall_flags = (*(u16 *)((u8 *)linked_actor + 0xA2));
            if (fall_flags & 0x800) {
                (*(u16 *)((u8 *)linked_actor + 0xA2)) = (u16) (fall_flags & 0xFFEF);
            }
            (*(u16 *)((u8 *)linked_actor + 0xA2)) = (u16) ((*(u16 *)((u8 *)linked_actor + 0xA2)) | 0x800);
        }
        ((S_80089AA0_18 *)motion_or_count)->unk_0A = (s16) ((*(u16 *)((u8 *)actor + 0x88))
            + (u16) (*(s16 *)((u8 *)linked_actor + 0x92)));
    }
    update_sound_settings_from_pad(linked_actor, motion_or_count, sprite_or_root, actor);
    if (!((*(s32 *)((u8 *)actor + 0x14)) & 0x100000)) {
        if ((D_800DD258 != ((S_80089AA0_16 *)sprite_or_root)->unk_24)
            || (D_800DD25A != ((S_80089AA0_16 *)sprite_or_root)->unk_25)) {
            update_packed_map_levels();
            if ((has_pending_actor_or_turn_action(0) << 0x10) == 0) {
                if ((lookup_definition_pair_value(((S_80089AA0_16 *)sprite_or_root)->unk_24,
                    ((S_80089AA0_16 *)sprite_or_root)->unk_25) << 0x10) != 0) {
                    (*(u16 *)((u8 *)linked_actor + 0xA2)) =
                        (u16)((*(u16 *)((u8 *)linked_actor + 0xA2)) | 0x200);
                } else {
                    (*(u16 *)((u8 *)linked_actor + 0xA2)) = (u16) ((*(u16 *)((u8 *)linked_actor + 0xA2)) & 0xFDFF);
                }
            }
        }
        linked_actor = find_eligible_actor_at_tile_and_height(actor, ((S_80089AA0_16 *)sprite_or_root)->unk_24,
            ((S_80089AA0_16 *)sprite_or_root)->unk_25, (s16) (*(u16 *)((u8 *)actor + 0x88)));
        if (linked_actor != 0) {
            check_entity_relation(linked_actor, primary_actor_record);
            (*(s32 *)((u8 *)linked_actor + 0x1C)) = (s32) ((*(s32 *)((u8 *)linked_actor + 0x1C)) & 0x7FFFFFFF);
        }
        D_800DD258 = (u16) ((S_80089AA0_16 *)sprite_or_root)->unk_24;
        D_800DD25A = (u16) ((S_80089AA0_16 *)sprite_or_root)->unk_25;
    }
    linked_actor = (*(void **)((u8 *)actor + 0x5C)) + 0x20;
    sprite_or_root = actor;
    if (linked_actor != actor) {
        do {
            linked_sprite = ((S_80089AA0_19_pre *)linked_actor)[-1].unk_00.p;
            linked_sprite->unk_14 = (u16) (linked_sprite->unk_14 & 0xFFBF);
            linked_actor = ((S_80089AA0_19 *)linked_actor)->unk_5C.i + 0x20;
        } while (linked_actor != sprite_or_root);
    }
    early_status = &g_dungeon_status.turn_scale;
    if (((S_80089AA0_21 *)early_status)->unk_02 & 0x800) {
        if ((has_pending_actor_or_turn_action(0) << 0x10) == 0) {
            if ((s16) ((S_80089AA0_21 *)early_status)->unk_08 == 0) {
                if (((S_80089AA0_21 *)early_status)->unk_14 == 0) {
                    ((S_80089AA0_21 *)early_status)->unk_02 =
                        (u16) ((((S_80089AA0_21 *)early_status)->unk_02 & 0xF7FF) | 0x2000);
                }
            }
        }
    }
    turn_status = &g_dungeon_status;
    phase_flags = turn_status->flags;
    if (!(phase_flags & 0x400)) {
        if (phase_flags & 0x2000) {
            if ((has_pending_actor_or_turn_action(0) << 0x10) == 0) {
                linked_actor = (*(void **)((u8 *)actor + 0x5C)) + 0x20;
                root = actor;
                if (linked_actor != actor) {
                    do {
                        ((S_80089AA0_19 *)linked_actor)->unk_8A = (u16) ((S_80089AA0_19 *)linked_actor)->unk_88;
                        ((S_80089AA0_19 *)linked_actor)->unk_6A = (u16) ((S_80089AA0_19 *)linked_actor)->unk_2A;
                        linked_actor = ((S_80089AA0_19 *)linked_actor)->unk_5C.i + 0x20;
                    } while (linked_actor != root);
                }
                root = actor;
                do {
                    record_or_page = (*(void **)((u8 *)actor + 0x5C));
                    linked_actor = (u8 *)record_or_page + 0x20;
                    companion_index = 0;
                    if (linked_actor != actor) {
                        do {
                            retry_callback = ((S_80089AA0_1 *)record_or_page)->unk_10;
                            actor_update_node_cursor = ((S_80089AA0_19 *)linked_actor)->unk_5C.p;
                            if (retry_callback > 0) {
                                retry_callback |= 0x80000000;
                                ((s32 (*)(void *, s32, s32)) retry_callback)((u8 *)record_or_page + 0x20,
                                    ((S_80089AA0_1 *)record_or_page)->unk_08, ((S_80089AA0_1 *)record_or_page)->unk_0C);
                                if (!(((S_80089AA0_1 *)record_or_page)->unk_1E & 0x8000)
                                    && (((S_80089AA0_19 *)linked_actor)->unk_71 < 0)
                                    && (((S_80089AA0_19 *)linked_actor)->unk_6D != 0)) {
                                    companion_index += 1;
                                }
                            }
                            record_or_page = actor_update_node_cursor;
                            linked_actor = (u8 *)record_or_page + 0x20;
                        } while (linked_actor != root);
                    }
                } while (companion_index != 0);
                linked_actor = (*(void **)((u8 *)actor + 0x5C)) + 0x20;
                root = actor;
                if (linked_actor != actor) {
                    do {
                        rotate_actor_movement_queue(((S_80089AA0_19_pre *)linked_actor)[-1].unk_00.i, linked_actor);
                        linked_actor = ((S_80089AA0_19 *)linked_actor)->unk_5C.i + 0x20;
                    } while (linked_actor != root);
                }
                g_dungeon_status.flags =
                    (u16)((g_dungeon_status.flags & 0xDFFF) | 0x1000);
            } else {
                turn_status->flags = (u16) (turn_status->flags & 0xDFFF);
                linked_actor = (*(void **)((u8 *)actor + 0x5C)) + 0x20;
                if (linked_actor != actor) {
                    root = (void *)0x800E0000;
                    do {
                        record_or_page = linked_actor - 0x20;
                        height_or_callback = ((S_80089AA0_1 *)record_or_page)->unk_10;
                        ((S_80089AA0_27 *)root)->unk_3DE8 = ((S_80089AA0_19 *)linked_actor)->unk_5C.p;
                        if (height_or_callback > 0) {
                            height_or_callback |= 0x80000000;
                            ((s32 (*)(void *, s32, s32)) height_or_callback)(linked_actor,
                                ((S_80089AA0_1 *)record_or_page)->unk_08, ((S_80089AA0_1 *)record_or_page)->unk_0C);
                        }
                        linked_actor = (u8 *)((S_80089AA0_27 *)root)->unk_3DE8 + 0x20;
                    } while (linked_actor != actor);
                }
                g_dungeon_status.flags =
                    (u16) (g_dungeon_status.flags | 0x2000);
            }
        }
    }
    tail_status = &g_dungeon_status;
    companion_index = 0;
    if (((s32)tail_status->pending_display_owner) > 0) {
        tail_status->pending_display_owner = 0;
    }
    repeat_pass = 0;
    next_flags = tail_status->flags | 1;
    loop_status = tail_status;
    ((S_80089AA0_24 *)loop_status)->unk_02 = next_flags;
    for (;;) {
        if ((dungeon_floor_flags & 0x100000) && ((has_pending_actor_or_turn_action(0) << 0x10) == 0)) {
            actor = (void *)dungeon_actor_ring_anchor;
apply_pending_points:
            pending_high = (*(u8 *)((u8 *)actor + 0x41));
            pending_low = (*(u8 *)((u8 *)actor + 0x42));
            (*(u8 *)((u8 *)actor + 0x42)) = 0U;
            (*(u8 *)((u8 *)actor + 0x41)) = 0U;
            (*(s32 *)((u8 *)actor + 0x18)) = (s32) ((*(s32 *)((u8 *)actor + 0x18)) + ((pending_high << 8) | pending_low));
            if ((can_entity_gain_level(actor, pending_low) << 0x10) != 0) {
                goto store_pending_actor;
            }
            next_link = (*(void **)((u8 *)actor + 0x5C));
            actor = (u8 *)next_link + 0x20;
            if (actor != (void *)dungeon_actor_ring_anchor) {
                goto apply_pending_points;
            }
            dungeon_floor_flags &= ~0x100000;
        }
begin_linked_pass:
        root = (void *)dungeon_actor_ring_anchor;
        record_or_page = ((S_80089AA0_16 *)root)->unk_5C;
        actor = (u8 *)record_or_page + 0x20;
        motion_or_count = 0;
        if (actor != root) {
            do {
                next_record = (*(void * *)((u8 *)actor + 0x5C));
                actor_update_node_cursor = next_record;
                if (((repeat_pass == 0) || ((*(s8 *)((u8 *)actor + 0x6D)) != 0)
                    || (((S_80089AA0_24 *)loop_status)->unk_14 != 0)) && (((S_80089AA0_1 *)record_or_page)->unk_10 > 0)) {
                    linked_actor = (void *)(s32)(s16)has_pending_actor_or_turn_action(0);
                    if (((S_80089AA0_24 *)loop_status)->unk_14 != 0) {
                        if (linked_actor == 0) {
                            if ((((S_80089AA0_1 *)record_or_page)->unk_B8 & 0xFFFF0000) == 0x150000) {
                                ((S_80089AA0_24 *)loop_status)->unk_0C = (void *) ((u8 *)record_or_page + 0x20);
                            } else {
                                record_or_page = actor_update_node_cursor;
                                actor = (u8 *)record_or_page + 0x20;
                                continue;
                            }
                        }
                        state_or_address = (s32)0x80000000;
                        callback_context = ((S_80089AA0_1 *)record_or_page)->unk_08;
                    } else {
                        state_or_address = (s32)0x80000000;
                        callback_context = ((S_80089AA0_1 *)record_or_page)->unk_08;
                    }
                    {
                        height_or_callback = ((S_80089AA0_1 *)record_or_page)->unk_10;
                        height_or_callback |= state_or_address;
                        ((s32 (*)(void *, s32, s32)) height_or_callback)((u8 *)record_or_page + 0x20, callback_context,
                            ((S_80089AA0_1 *)record_or_page)->unk_0C);
                    }
                    if (!(((S_80089AA0_1 *)record_or_page)->unk_1E & 0x8000)) {
                        if ((*(s8 *)((u8 *)actor + 0x6D)) != 0) {
                            motion_or_count = (void *)((s32)motion_or_count + 1);
                        }
                        if ((linked_actor == 0) || ((has_pending_actor_or_turn_action(0) << 0x10) != 0)) {
                            record_or_page = actor_update_node_cursor;
                            actor = (u8 *)record_or_page + 0x20;
                            continue;
                        }
                    }
                    break;
                } else {
                    record_or_page = actor_update_node_cursor;
                    actor = (u8 *)record_or_page + 0x20;
                }
            } while (actor != root);
        }
        loop_flags = ((S_80089AA0_24 *)loop_status)->unk_02;
        if (loop_flags & 0x1000) {
            if (((S_80089AA0_24 *)loop_status)->unk_08 == 0) {
                if (((S_80089AA0_24 *)loop_status)->unk_04 == 0) {
                    ((S_80089AA0_24 *)loop_status)->unk_02 = (u16) ((loop_flags & 0xEFF7) | 0x4000);
                    if (motion_or_count != 0) {
                        repeat_pass = 1;
                        continue;
                    }
                    goto check_pass_completion;
store_pending_actor:
                    ((S_80089AA0_24 *)loop_status)->unk_0C = actor;
                    goto begin_linked_pass;
                }
                return;
            }
        } else {
            if (loop_flags & 0x400) {
                if (!(loop_flags & 0x800)) {
                    if (((has_pending_actor_or_turn_action(0) << 0x10) == 0) && ((is_dungeon_action_enabled() << 0x10) == 0)) {
                        if (companion_index == 0) {
                            companion_index = 1;
                            continue;
                        }
                        pass_flags = ((S_80089AA0_24 *)loop_status)->unk_02;
                        cleared_pass_flags = pass_flags & 0xFBFF;
                        ((S_80089AA0_24 *)loop_status)->unk_02 = cleared_pass_flags;
                        if (!(pass_flags & 0x4000)) {
                            ((S_80089AA0_24 *)loop_status)->unk_02 = (u16) (cleared_pass_flags | 0x800);
                            if (check_action_available_without_nearby_actor() != 0) {
                                ((S_80089AA0_24 *)loop_status)->unk_02 =
                                    (u16)(((S_80089AA0_24 *)loop_status)->unk_02 | 0x80);
                                return;
                            }
                        }
                        return;
                    }
                }
            }
        }
check_pass_completion:
        if ((actor == (void *)dungeon_actor_ring_anchor) && (motion_or_count == 0)) {
            ((S_80089AA0_24 *)loop_status)->unk_02 = (u16) (((S_80089AA0_24 *)loop_status)->unk_02 & 0xFFFE);
        }
        final_flags = ((S_80089AA0_24 *)loop_status)->unk_02;
        if (!(final_flags & 0x80) || (((S_80089AA0_24 *)loop_status)->unk_0C != 0)
            || (((S_80089AA0_24 *)loop_status)->unk_10 != 0) || (((S_80089AA0_24 *)loop_status)->unk_0A != 0)
            || (((S_80089AA0_24 *)loop_status)->unk_08 == 0)) {
            return;
        }
        next_flags = final_flags & 0xFFF7;
        ((S_80089AA0_24 *)loop_status)->unk_02 = next_flags;
    }
}
