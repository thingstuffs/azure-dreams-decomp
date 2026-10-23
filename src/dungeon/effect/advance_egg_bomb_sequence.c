#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/level.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Coord;

extern s32 entity_level_thresholds[];
extern void func_8003E188(s32 field_index, s32 flag);
extern void func_80042640(void *obj, s16 monsterId);
void apply_actor_template_and_class(); /* extern */
s32 get_unused_text_buffer();
s32 expand_text_control_codes();
void *clear_byte_and_advance();
s32 write_text_byte_and_advance();
s32 append_entity_display_text();
void display_formatted_context_message(); /* extern */
s32 *(*load_monster_resource_data())(s32, s16, s16, s16); /* extern */
s32 find_or_retain_sprite_resource_slot();
s32 raise_entity_level(); /* extern */
s32 choose_usable_ability_or_attack();
s32 choose_best_eligible_entry();
s16 set_or_clear_actor_status_slot(); /* extern */
s32 display_text_with_fullwidth_adjustment(); /* extern */
void clear_selected_item_flag_400();
void check_entity_relation(s32 *, u8 *);
extern u8 D_800E0A42[];
extern u8 D_800E0A56[20];
extern u8 D_800E0A6A[12];


typedef struct S_800B7774_0_pre {
    u16 unk_00;
} S_800B7774_0_pre;   /* the 0x2 bytes before arg0 in advance_egg_bomb_sequence, addressed as arg0[-1] */

typedef struct S_800B7774_0 {
    u8 unk_00;
    u8 pad_01[0x3];
    s32 * unk_04;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
    s16 unk_0E;
} S_800B7774_0;   /* arg0 in advance_egg_bomb_sequence */

typedef struct S_800B7774_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_800B7774_1;   /* controls_base in advance_egg_bomb_sequence */

typedef struct S_800B7774_2_pre {
    s32 unk_00;
    u8 pad_04[0x10];
} S_800B7774_2_pre;   /* 0x14-byte header immediately before the payload. */

typedef struct S_800B7774_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x1];
    u8 unk_13;
    u8 pad_14[0x4];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x17];
    u8 unk_43;
    u8 pad_44[0x2];
    union { u16 u; s16 s; } unk_46;   /* accessed as both */
    u8 pad_48[0x18];
    s32 unk_60;
} S_800B7774_2;


typedef struct S_800B7774_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800B7774_4;   /* arg2 in advance_egg_bomb_sequence */

typedef struct S_800B7774_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800B7774_5;   /* state_base in advance_egg_bomb_sequence */

typedef struct S_800B7774_6_pre {
    u16 unk_00;
} S_800B7774_6_pre;   /* 0x2-byte header immediately before the payload. */

/* Spawns and levels the egg bomb monster, then advances its activation and cleanup. */
void advance_egg_bomb_sequence(void *egg_bomb, Coord *position, void *effect) {
    s16 spawn_x;
    s16 spawn_y;
    s32 held_x;
    s32 held_y;
    u16 action_parameter;
    s16 phase;
    s32 *monster;
    s32 *tracked_monster;
    s32 action_data;
    s32 message_id;
    s32 action_id;
    s32 target_experience;
    s16 egg_bomb_level;
    u16 remaining_frames;
    GameWork *state_base;
    Coord *coord_arg = position;

    state_base = &g_game_work;
    phase = ((S_800B7774_0 *)egg_bomb)->unk_0A.s;
    switch (phase) {
    case 0:
        if ((find_valid_nearby_position(0, (u16) coord_arg->x >> 6, (u16) coord_arg->y >> 6, &spawn_x, &spawn_y) << 0x10) == 0) {
            {
                g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
            }
            display_formatted_context_message(&D_800E0A42);
            (*(u16 *)((u8 *)egg_bomb + (-2))) = (u16) (((S_800B7774_0_pre *)egg_bomb)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            return;
        }
        held_x = spawn_x;
        held_y = spawn_y;
        monster = load_monster_resource_data(((S_800B7774_0 *)egg_bomb)->unk_00,
            find_or_retain_sprite_resource_slot(((S_800B7774_0 *)egg_bomb)->unk_00, 2), 1)(2, held_x, held_y, (s16) (coord_arg->z - 0x20));
        ((S_800B7774_0 *)egg_bomb)->unk_04 = monster;
        if (monster != NULL) {
            func_8003E188(((S_800B7774_2 *)monster)->unk_13, 0);
            clear_selected_item_flag_400(egg_bomb);
            func_80042640(monster, ((S_800B7774_2 *)monster)->unk_13);
            apply_actor_template_and_class(monster, ((S_800B7774_2 *)monster)->unk_13, 0);
            ((S_800B7774_2 *)monster)->unk_43 = 0xFE;
            set_or_clear_actor_status_slot(monster, STATUS_NO_TILE_OCCUPANCY, 0);
            {
                s32 clamp_value;
                u32 first_call_arg;
                s32 first_call_mode;
                s32 raw_first_result;
                clamp_value = (*(u8 *)((u8 *)&((ActorRecord *)((u8 *)dungeon_actor_ring_anchor))->unk_10 + 1)) + 0x32;
                egg_bomb_level = clamp_value;
                if (clamp_value >= 0x64) {
                    egg_bomb_level = 0x63;
                }
                {
                    s32 *scan_arg = entity_level_thresholds;
                    /*
                     * Original bug: level-99 EXP still satisfies the loop test, but raise_entity_level stops changing
                     * the level at 99. Stop at the cap to avoid an infinite spawn loop.
                     * Found and documented by the Azure Dreams community
                     * (adrando.com/guide/bugs.html).
                     */
                    target_experience = entity_level_thresholds[egg_bomb_level];
                    ((S_800B7774_2 *)monster)->unk_18 = target_experience;
                    if ((u32) target_experience >= (u32) entity_level_thresholds[((S_800B7774_2 *)monster)->unk_11]) {
                        s32 *loop_base = entity_level_thresholds;
                        do {
                            raise_entity_level(monster, 0);
                        } while ((u32) loop_base[((S_800B7774_2 *)monster)->unk_11]
                            <= (u32) ((S_800B7774_2 *)monster)->unk_18);
                        scan_arg = monster;
                    }
                    raw_first_result = get_unused_text_buffer(scan_arg);
                }
                first_call_mode = 8;
                first_call_arg = raw_first_result;
                message_id = first_call_arg;
                raw_first_result = write_text_byte_and_advance(first_call_mode, first_call_arg);
                clear_byte_and_advance(expand_text_control_codes(D_800E0A6A, write_text_byte_and_advance(0xA, append_entity_display_text(monster,
                    expand_text_control_codes(D_800E0A56, raw_first_result)))));
            }
            display_text_with_fullwidth_adjustment(message_id);
            {
                s32 *call_obj;
                u8 *call_state;
                call_obj = monster;
                call_state = ((u8 *)dungeon_actor_ring_anchor);
                ((S_800B7774_0 *)egg_bomb)->unk_0C = 0x10U;
                check_entity_relation(call_obj, call_state);
            }
            ((S_800B7774_0 *)egg_bomb)->unk_0A.u = (u16) (((S_800B7774_0 *)egg_bomb)->unk_0A.u + 1);
        }

        break;
    case 1:
        remaining_frames = ((S_800B7774_0 *)egg_bomb)->unk_0C - 1;
        ((S_800B7774_0 *)egg_bomb)->unk_0C = remaining_frames;
        if (((remaining_frames << 0x10) > 0) && !(((S_800B7774_4 *)effect)->unk_14 & 0x8000)
            && (((s32)state_base->pressed_buttons) == 0)) {
            break;
        }
        ((S_800B7774_0 *)egg_bomb)->unk_0A.u = (u16) (((S_800B7774_0 *)egg_bomb)->unk_0A.u + 1);
        break;
    case 2:
        monster = ((S_800B7774_0 *)egg_bomb)->unk_04;
        if (((S_800B7774_0 *)egg_bomb)->unk_0E == 0) {
            ((S_800B7774_2 *)monster)->unk_60 = choose_best_eligible_entry(((S_800B7774_2_pre *)monster)[-1].unk_00, monster, 2);
            {
                g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 2);
            }
            action_data = ((S_800B7774_2 *)monster)->unk_60;
            ((S_800B7774_2 *)monster)->unk_46.u = 0x800C;
            if (action_data != 0) {
                action_id = choose_usable_ability_or_attack(monster, action_data, &action_parameter, 1);
                ((S_800B7774_2 *)monster)->unk_2A = action_parameter;
                if ((s16) action_id >= 0) {
                    ((S_800B7774_2 *)monster)->unk_46.s = (s16) (action_id | 0x8000);
                }
            }
        }
        ((PlayerRecord *)((u8 *)dungeon_actor_ring_anchor))->pending_item_action = 0;
        (*(s32 *)((u8 *)monster + (0x1C))) = (s32) (((S_800B7774_2 *)monster)->unk_1C | 0x400000);
        {
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
        (*(u16 *)((u8 *)egg_bomb + (-2))) = (u16) (((S_800B7774_0_pre *)egg_bomb)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        break;
    }
    tracked_monster = ((S_800B7774_0 *)egg_bomb)->unk_04;
    if ((tracked_monster != NULL) && (((S_800B7774_6_pre *)tracked_monster)[-1].unk_00 & 0x8000)) {
        ((S_800B7774_0 *)egg_bomb)->unk_0E = 1;
    }
}
