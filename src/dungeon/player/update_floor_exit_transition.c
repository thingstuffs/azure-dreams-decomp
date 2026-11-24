#include "shared/runtime_dispatch.h"
#include "shared/game_state.h"
#include "shared/object_node.h"
#include "common.h"

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
#include "dungeon/item/effect.h"
#include "dungeon/player.h"
#include "dungeon/data.h"
#include "dungeon/menu.h"

extern u8 resident_globals_page[];

   /* ((Rec_D_800E3D7C *)arg0)->unk_C8 in update_floor_exit_transition */


typedef struct S_800930F0_5 {
    union { s32 * s; void * (*u)(s32, s32); } unk_00;   /* accessed as both */
    s32 unk_04;
    s32 unk_08;
} S_800930F0_5;   /* &D_800E4938 in update_floor_exit_transition */

typedef struct S_800930F0_6 {
    s32 unk_00;
} S_800930F0_6;   /* &D_800E296C in update_floor_exit_transition */

typedef struct S_800930F0_8 {
    u8 pad_00[0x3CD0];
    u8 unk_3CD0;
} S_800930F0_8;

typedef struct S_800930F0_9 {
    u8 pad_00[0x2E76];
    u16 unk_2E76;
} S_800930F0_9;   /* store_base in update_floor_exit_transition */

s32 get_entity_class();

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} __attribute__((packed)) UnalignedCopy3;

extern M2C_UNK D_80021268;
extern s16 current_dungeon_floor;
extern void *D_800DCF64;
extern void *dungeon_menu_action_state[];

/* Advances the dungeon transition through its delay, setup, and completion phases. */
void update_floor_exit_transition(PlayerRecord *state, ObjectPosition *unused,
                                  MovingTile *tile, ActorRecord *actor)
{
    s32 *transition_base;
    s32 *slot_cursor;
    s32 slot_index;
    s32 slot_object;
    void *load_status;
    u16 wait_ticks;
    u8 phase;
    void *created_object;
    s16 *type_values;

    phase = state->actor.action_phase;
    switch (phase) {
    case 0:
        slot_index = 1;
        state->actor.action_timer = 0U;
        create_map_position_object((tile->tile_x << 6) | 0x20, (tile->tile_y << 6) | 0x20);
        type_values = &actor_event_values;
        slot_cursor = (s32 *)state + 1;
        actor->flags1C = (actor->flags1C | 0x40000000);
        do {
            slot_object = ((ActorRecord *)slot_cursor)->unk_AC.value;
            if (slot_object != 0) {
                create_orbiting_teleport_effect(slot_object, type_values[get_entity_class(slot_object)], (s16)slot_index, 0);
            }
            slot_index -= 1;
            slot_cursor -= 1;
        } while (slot_index >= 0);
        state->actor.action_phase = (u8) (state->actor.action_phase + 1);
    case 1:
        wait_ticks = state->actor.action_timer + 1;
        state->actor.action_timer = wait_ticks;
        if ((s16) wait_ticks < 0x3D) {
            break;
        }
        transition_base = (s32 *)0x800E0000;
        if (GAME_STATE->log.head.flags & 4) {
            if (((S_800930F0_8 *)transition_base)->unk_3CD0 != 0) {
                break;
            }
            ((S_800930F0_8 *)transition_base)->unk_3CD0 = 1;
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
            GAME_STATE->log.head.flags = 0;
            GAME_STATE->log.head.length = 0;
            GAME_STATE->log.head.repeat = 0;
            GAME_STATE->log.head.cursor = 0;
            check_action_boundary_and_set_flag();
        }
        if (GAME_STATE->dungeon_mode_state != 0) {
            if (GAME_STATE->dungeon_mode_state == 1) {
                GAME_STATE->dungeon_floor = GAME_STATE->dungeon_floor + 1;
                reset_tagged_entry_states();
                GAME_STATE->dungeon_mode_state = 0;
            } else {
                GAME_STATE->dungeon_floor = GAME_STATE->dungeon_floor + 1;
            }
        } else {
            GAME_STATE->dungeon_floor = GAME_STATE->dungeon_floor + 1;
        }
        play_sound_if_enabled(0x514);
        ((S_800930F0_5 *)(&dungeon_menu_action_state))->unk_00.s = &D_80021268;
        reference_tile_object.unk_038 = 0;
        (*&dungeon_floor_flags) = (s32) (((S_800930F0_6 *)(&dungeon_floor_flags))->unk_00 | 0x2000);
        state->actor.action_phase = (u8) (state->actor.action_phase + 1);
        break;
    case 2:
        load_status = create_expanding_screen_rectangle();
        D_800DCF64 = load_status;
        if (load_status == 0) {
            break;
        }
        state->actor.action_phase = (u8) (state->actor.action_phase + 1);
        break;
    case 3:
        created_object = ((S_800930F0_5 *)(&dungeon_menu_action_state))->unk_00.u(((S_800930F0_5 *)(&dungeon_menu_action_state))->unk_04,
            ((S_800930F0_5 *)(&dungeon_menu_action_state))->unk_08);
        state->unk_C8 = created_object;
        if (created_object == NULL) {
            return;
        }
        state->actor.action_phase = (u8) (state->actor.action_phase + 1);
    case 4:
        if (!(((ObjectNodeHeader *)(state->unk_C8))->flags & 0x8000)) {
            break;
        }
        request_scene_dispatch_state(scene_mode_code);
        current_dungeon_floor = *(u16 *)0x80010234;
        mark_sprite_resources_for_purge();
        state->actor.action_phase = (u8) (state->actor.action_phase + 1);
        break;
    case 16:
        transition_base = (s32 *)0x800E0000;
        if (GAME_STATE->log.head.flags & 4) {
            if (((S_800930F0_8 *)transition_base)->unk_3CD0 != 0) {
                break;
            }
            ((S_800930F0_8 *)transition_base)->unk_3CD0 = 1;
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
        state->actor.action_phase = (u8) (state->actor.action_phase + 1);
    case 17:
    default:
        break;
    }
    g_game_work.view.slot[0].callback = 0;
    g_game_work.view.slot[2].callback = 0;
    (*&dungeon_floor_flags) = (s32) (((S_800930F0_6 *)(&dungeon_floor_flags))->unk_00 | 0x40000);
    return;
}
