#include "shared/runtime_dispatch.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/player/item.h"
#include "dungeon/system.h"
#include "engine/entity.h"
#include "engine/texture.h"
#include "engine/resource.h"
#include "slus.h"
extern u8 resident_globals_page[];

   /* ((Rec_D_800E3D7C *)arg0)->unk_C8 in update_floor_exit_transition */

typedef struct S_800930F0_3 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_800930F0_3;

typedef struct S_800930F0_4 {
    u8 pad_00[0x234];
    s32 unk_234;
    u8 pad_238[0x1E58];
    s32 unk_2090;
    u8 pad_2094[0x1680];
    union { u16 s; s16 u; } unk_3714;   /* accessed as both */
    s16 unk_3716;
    s16 unk_3718;
    s16 unk_371A;
} S_800930F0_4;

typedef struct S_800930F0_5 {
    union { s32 * s; void * (*u)(s32, s32); } unk_00;   /* accessed as both */
    s32 unk_04;
    s32 unk_08;
} S_800930F0_5;   /* &D_800E4938 in update_floor_exit_transition */

typedef struct S_800930F0_6 {
    s32 unk_00;
} S_800930F0_6;   /* &D_800E296C in update_floor_exit_transition */

typedef struct S_800930F0_7 {
    u16 unk_00;
} S_800930F0_7;   /* &D_80013714 in update_floor_exit_transition */

typedef struct S_800930F0_8 {
    u8 pad_00[0x3CD0];
    union { u8 s; s8 u; } unk_3CD0;   /* accessed as both */
} S_800930F0_8;

typedef struct S_800930F0_9 {
    u8 pad_00[0x2E76];
    u16 unk_2E76;
} S_800930F0_9;   /* store_base in update_floor_exit_transition */

s32 get_entity_class();
void snapshot_inventory_and_familiars(void *input_state); /* extern */
s32 play_sound_if_enabled(s32 query_value); /* extern */
s32 check_action_boundary_and_set_flag(void); /* extern */
s32 create_map_position_object(s32 world_x, s32 world_z);
void *create_orbiting_teleport_effect();
extern s32 D_80010234;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} __attribute__((packed)) UnalignedCopy3;
extern UnalignedCopy3 D_80012080;
extern UnalignedCopy3 D_80013710;
extern M2C_UNK D_80021268;
extern u16 current_dungeon_floor;
extern u8 scene_mode_code;
extern s16 actor_event_values[];
extern s32 D_800DCF64;
extern u8 dungeon_button_latch;
extern void *dungeon_menu_action_state[];

/* Advances the dungeon transition through its delay, setup, and completion phases. */
void update_floor_exit_transition(PlayerRecord *state, s32 unused, MovingTile *tile, ActorRecord *actor) {
    s32 *transition_base;
    S_800930F0_4 *saved_state_base;
    s32 *slot_cursor;
    s32 slot_index;
    s32 slot_object;
    s32 load_status;
    u16 wait_ticks;
    u8 phase;
    void *created_object;
    s16 *type_values;

    phase = state->actor.action_phase.u;
    switch (phase) {
    case 0:
        slot_index = 1;
        state->actor.action_timer.u = 0U;
        create_map_position_object((tile->tile_x << 6) | 0x20, (tile->tile_y << 6) | 0x20);
        type_values = &actor_event_values;
        slot_cursor = (s32 *)state + 1;
        actor->flags1C = (s32) (actor->flags1C | 0x40000000);
        do {
            slot_object = ((S_800930F0_3 *)slot_cursor)->unk_AC;
            if (slot_object != 0) {
                create_orbiting_teleport_effect(slot_object, type_values[get_entity_class(slot_object)], (s16)slot_index, 0);
            }
            slot_index -= 1;
            slot_cursor -= 1;
        } while (slot_index >= 0);
        state->actor.action_phase.u = (u8) (state->actor.action_phase.u + 1);
    case 1:
        wait_ticks = state->actor.action_timer.u + 1;
        state->actor.action_timer.u = wait_ticks;
        if ((s16) wait_ticks < 0x3D) {
            break;
        }
        transition_base = (s32 *)0x800E0000;
        saved_state_base = (S_800930F0_4 *)0x80010000;
        if (saved_state_base->unk_3714.s & 4) {
            if (((S_800930F0_8 *)transition_base)->unk_3CD0.s != 0) {
                break;
            }
            ((S_800930F0_8 *)transition_base)->unk_3CD0.u = 1;
            request_scene_dispatch_state(3U);
            break;
        }
        snapshot_inventory_and_familiars(state);
        snapshot_inventory_familiar_records();
        {
            UnalignedCopy3 *copy_src;
            UnalignedCopy3 *copy_dst;

            copy_src = (UnalignedCopy3 *)0x80013710;
            copy_dst = (UnalignedCopy3 *)0x80012080;
            *copy_dst = *copy_src;
            saved_state_base->unk_3714.u = 0;
            saved_state_base->unk_3716 = 0;
            saved_state_base->unk_3718 = 0;
            saved_state_base->unk_371A = 0;
            check_action_boundary_and_set_flag();
        }
        if (saved_state_base->unk_2090 != 0) {
            if (saved_state_base->unk_2090 == 1) {
                saved_state_base->unk_234 = (s32) (saved_state_base->unk_234 + 1);
                reset_tagged_entry_states();
                saved_state_base->unk_2090 = 0;
            } else {
                saved_state_base->unk_234 = (s32) (saved_state_base->unk_234 + 1);
            }
        } else {
            saved_state_base->unk_234 = (s32) (saved_state_base->unk_234 + 1);
        }
        play_sound_if_enabled(0x514);
        ((S_800930F0_5 *)(&dungeon_menu_action_state))->unk_00.s = &D_80021268;
        reference_tile_object.unk_038 = 0;
        (*(s32 *)&dungeon_floor_flags) = (s32) (((S_800930F0_6 *)(&dungeon_floor_flags))->unk_00 | 0x2000);
        state->actor.action_phase.u = (u8) (state->actor.action_phase.u + 1);
        break;
    case 2:
        load_status = create_expanding_screen_rectangle();
        D_800DCF64 = load_status;
        if (load_status == 0) {
            break;
        }
        state->actor.action_phase.u = (u8) (state->actor.action_phase.u + 1);
        break;
    case 3:
        created_object = ((S_800930F0_5 *)(&dungeon_menu_action_state))->unk_00.u(((S_800930F0_5 *)(&dungeon_menu_action_state))->unk_04,
            ((S_800930F0_5 *)(&dungeon_menu_action_state))->unk_08);
        state->unk_C8 = created_object;
        if (created_object == NULL) {
            return;
        }
        state->actor.action_phase.u = (u8) (state->actor.action_phase.u + 1);
    case 4:
        if (!(((ObjectNodeHeader *)(state->unk_C8))->flags & 0x8000)) {
            break;
        }
        request_scene_dispatch_state(scene_mode_code);
        current_dungeon_floor = *(u16 *)0x80010234;
        mark_sprite_resources_for_purge();
        state->actor.action_phase.u = (u8) (state->actor.action_phase.u + 1);
        break;
    case 16:
        transition_base = (s32 *)0x800E0000;
        if (((S_800930F0_7 *)(((s32 *)&system_update_flags)))->unk_00 & 4) {
            if (((S_800930F0_8 *)transition_base)->unk_3CD0.s != 0) {
                break;
            }
            ((S_800930F0_8 *)transition_base)->unk_3CD0.u = 1;
            request_scene_dispatch_state(3U);
            break;
        }
        snapshot_inventory_and_familiars(state);
        snapshot_inventory_familiar_records();
        {
            s32 command;
            s32 zero_arg_1;
            s32 zero_arg_2;
            u32 zero_arg_3;
            S_800930F0_9 *flags_base;
            u16 flags;

            command = 6;
            zero_arg_1 = 0;
            zero_arg_2 = zero_arg_1;
            zero_arg_3 = zero_arg_1;
            flags_base = (S_800930F0_9 *)resident_globals_page;
            flags = 0x8000;
            flags_base->unk_2E76 = flags;
            request_scene_state_with_parameters(command, zero_arg_1, zero_arg_2, zero_arg_3, 0x8000);
        }
        state->actor.action_phase.u = (u8) (state->actor.action_phase.u + 1);
    case 17:
    default:
        break;
    }
    g_game_work.view.slot[0].callback = 0;
    g_game_work.view.slot[2].callback = 0;
    (*(s32 *)&dungeon_floor_flags) = (s32) (((S_800930F0_6 *)(&dungeon_floor_flags))->unk_00 | 0x40000);
    return;
}
