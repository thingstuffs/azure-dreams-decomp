#include "dungeon/actor/status.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/item/monster_resource_slots_g00325.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/level.h"
#include "slus.h"
#include "dungeon/item/message.h"
#include "engine/util.h"
#include "dungeon/item.h"
#include "dungeon/effect/egg_bomb.h"
#include "dungeon/system.h"
#include "engine/entity.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Coord;

extern s32 entity_level_thresholds[];
s32 choose_usable_ability_or_attack(struct Actor *actor, struct Actor *target, u16 *out_angle, s32 prefer_ability);
s32 choose_best_eligible_entry(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
#include "dungeon/actor/effect.h"
#include "dungeon/player/object.h"
#include "shared/object_node.h"
extern u8 D_800E0A42[];
extern u8 D_800E0A56[20];
extern u8 D_800E0A6A[12];


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

/* Spawns and levels the egg bomb monster, then advances its activation and cleanup. */
void advance_egg_bomb_sequence(EggBombBody *egg_bomb, Coord *position, void *effect) {
    s16 spawn_x;
    s16 spawn_y;
    s32 held_x;
    s32 held_y;
    u16 action_parameter;
    s16 phase;
    ActorRecord *monster;
    ActorRecord *tracked_monster;
    s32 action_data;
    void *message_id;
    s32 action_id;
    s32 target_experience;
    s16 egg_bomb_level;
    u16 remaining_frames;
    GameWork *state_base;
    Coord *coord_arg = position;

    state_base = &g_game_work;
    phase = (s16)egg_bomb->unk_0A;
    switch (phase) {
    case 0:
        if ((find_valid_nearby_position(0, (u16) coord_arg->x >> 6, (u16) coord_arg->y >> 6, &spawn_x, &spawn_y) << 0x10) == 0) {
            {
                g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
            }
            display_formatted_context_message(&D_800E0A42);
            (NODE_HEADER(egg_bomb)->flags) = (u16) (NODE_HEADER(egg_bomb)->flags | NODE_REMOVE);
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            return;
        }
        held_x = spawn_x;
        held_y = spawn_y;
        monster = load_monster_code_module(egg_bomb->unk_00,
            find_or_retain_sprite_resource_slot(egg_bomb->unk_00, 2), 1)(2, held_x, held_y, (s16) (coord_arg->z - 0x20));
        egg_bomb->unk_04 = monster;
        if (monster != NULL) {
            set_packed_2bit_flag(monster->species, 0);
            clear_selected_item_flag_400(egg_bomb);
            init_monster_from_stats(monster, monster->species);
            apply_actor_template_and_class(monster, monster->species, 0);
            monster->unk_43 = 0xFE;
            {
                void *body = monster;
                ActorRecord *actor = body;

                set_or_clear_actor_status_slot(actor, STATUS_NO_TILE_OCCUPANCY, 0);
            }
            {
                s32 clamp_value;
                void *first_call_arg;
                s32 first_call_mode;
                void * raw_first_result;
                clamp_value = dungeon_actor_ring_anchor->level + 0x32;
                egg_bomb_level = clamp_value;
                if (clamp_value >= 0x64) {
                    egg_bomb_level = 0x63;
                }
                {
                    /*
                     * BUG: level-99 EXP still satisfies the loop test, but raise_entity_level stops changing
                     * the level at 99. Stop at the cap to avoid an infinite spawn loop.
                     * Found and documented by the Azure Dreams community
                     * (adrando.com/guide/bugs.html).
                     */
                    target_experience = entity_level_thresholds[egg_bomb_level];
                    monster->experience = target_experience;
                    if ((u32) target_experience >= (u32) entity_level_thresholds[monster->level]) {
                        s32 *loop_base = entity_level_thresholds;
                        do {
                            raise_entity_level(monster, 0);
                        } while ((u32) loop_base[monster->level]
                            <= (u32) monster->experience);
                    }
                    raw_first_result = get_unused_text_buffer();
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
                ActorRecord *call_obj;
                ActorRecord *call_state;
                call_obj = monster;
                call_state = dungeon_actor_ring_anchor;
                egg_bomb->unk_0C = 0x10U;
                check_entity_relation(call_obj, call_state);
            }
            egg_bomb->unk_0A = (u16) (egg_bomb->unk_0A + 1);
        }

        break;
    case 1:
        remaining_frames = egg_bomb->unk_0C - 1;
        egg_bomb->unk_0C = remaining_frames;
        if (((remaining_frames << 0x10) > 0) && !(((S_800B7774_4 *)effect)->unk_14 & 0x8000)
            && ((state_base->pressed_buttons) == 0)) {
            break;
        }
        egg_bomb->unk_0A = (u16) (egg_bomb->unk_0A + 1);
        break;
    case 2:
        monster = egg_bomb->unk_04;
        if (egg_bomb->unk_0E == 0) {
            ((S_800B7774_2 *)monster)->unk_60 = choose_best_eligible_entry(NODE_HEADER(monster)->sprite, monster, 2);
            {
                g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 2);
            }
            action_data = ((S_800B7774_2 *)monster)->unk_60;
            monster->action_flags = 0x800C;
            if (action_data != 0) {
                action_id = choose_usable_ability_or_attack(monster, action_data, &action_parameter, 1);
                monster->facing = action_parameter;
                if ((s16) action_id >= 0) {
                    monster->action_flags = (s16) (action_id | 0x8000);
                }
            }
        }
        ((PlayerRecord *)((u8 *)dungeon_actor_ring_anchor))->pending_item_action = 0;
        monster->flags1C = (s32) (monster->flags1C | 0x400000);
        {
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
        (NODE_HEADER(egg_bomb)->flags) = (u16) (NODE_HEADER(egg_bomb)->flags | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        break;
    }
    tracked_monster = egg_bomb->unk_04;
    if ((tracked_monster != NULL) && (NODE_HEADER(tracked_monster)->flags & 0x8000)) {
        egg_bomb->unk_0E = 1;
    }
}
