#include "slus.h"

struct ObjectPosition;
#include "shared/dungeon_actor_callbacks.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082EB0.h"
#include "dungeon/player.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *player_action_tag[];
extern s32 selected_item_record_alias[];
extern s16 camera_depth_target[5];
extern s32 menu_action_argument[];
extern u8 D_8004F5F4[];
s32 resolve_player_input_facing(s16 direction_offset, u16 *flags, u16 *angle);                /* extern */
s32 check_familiar_deployment_placement(); /* extern */
void display_formatted_context_message(void *context);                   /* extern */
void append_packed_action_record(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte);   /* extern */
s32 play_sound_if_enabled(s32 query_value);                     /* extern */
void *create_panel_effect_object(void *owner);                      /* extern */
s32 create_familiar_selection_marker();                          /* extern */
void update_selection_tile_markers();                 /* extern */
s32 select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s32 slot_value);   /* extern */
extern u8 D_80012D6D;
extern M2C_UNK familiar_menu_action_data;
extern M2C_UNK D_80023C58;
extern M2C_UNK D_80088904;
extern M2C_UNK D_80088934;
extern M2C_UNK D_80088970;
extern M2C_UNK D_800E0040;
extern u8 D_800E2004[];

   /* actor in update_familiar_command_selection */

typedef struct S_80091430_2_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_80091430_2_pre;   /* 0x18-byte header immediately before the payload. */

   /* (*(void **)((u8 *)arg0 + 0x104)) in update_familiar_command_selection */

enum FamiliarCommandPhase {
    FAMILIAR_COMMAND_OPEN = 0,
    FAMILIAR_COMMAND_INPUT = 1,
    FAMILIAR_COMMAND_RESTORE_INPUT = 2,
};

/* Updates the selection, handles dungeon input, and restores the actor callback on exit. */
void update_familiar_command_selection(void *state, s32 context_a, void *context_b, void *actor_ptr) {
    ActorRecord *actor = actor_ptr;
    GameWork *dungeon_state = &g_game_work;
    s16 action_id;
    s16 action_arg;
    s16 selection_code;
    s16 slot_index;
    s32 selection_result;
    s32 selection_ready;
    s32 candidate_flags;
    s32 phase;
    void **candidate_slot;
    ActorRecord *candidate;
    ActorRecord *preview;
    void *selection_data;
    ActorRecord *selection;

    phase = (*(u8 *)((u8 *)state + 0x9B));
    switch (phase) {
    case FAMILIAR_COMMAND_OPEN:
        selection_ready = create_familiar_selection_marker(state + 0x104);
        (*(s32 *)((u8 *)state + 0xC8)) = selection_ready;
        if (selection_ready == 0) {
            return;
        }
        set_message_mode(2);
        runtime_call_selected_mode_handler();
        if ((*(s16 *)((u8 *)state + 0x120)) == 0) {
            if (D_80012D6D == 0) {
                submit_script_with_registered_context(&D_80088904);
            } else {
                submit_script_with_registered_context(&D_80088934);
            }
        } else {
            submit_script_with_registered_context(&D_80088970);
        }
        (*(u8 *)((u8 *)state + 0x9B)) = (u8) ((*(u8 *)((u8 *)state + 0x9B)) + 1);
    case FAMILIAR_COMMAND_INPUT:
        selection_result = resolve_player_input_facing((*(s16 *)((u8 *)state + 0x9E)), state + 0xA2, (*(void **)((u8 *)state
            + 0x104)) + 0x2A);
        selection_code = (s16) selection_result;
        if (selection_code != 0xFFF) {
            ((ActorRecord *)((*(void **)((u8 *)state + 0x104))))->facing = selection_result;
            append_packed_action_record(actor, 0x70, (s32) (*(void **)((u8 *)state + 0x104)) == (*(s32 *)((u8 *)state + 0xB0)),
                (selection_result << 0x10 >> 0x19) & 7);
        }
        if ((*(s16 *)((u8 *)state + 0x120)) == 0) {
            selection_data = (*(void **)((u8 *)state + 0x104));
            if (selection_data != NULL && ((dungeon_state->pressed_buttons) & 0x80)) {
                if ((reject_forbidden_familiar_recall(0) == 0) && !(actor->flags1C & 0x100000)) {
                    actor->unk_8A = (s16) ((s32) (*(void **)((u8 *)state + 0x104)) != (*(s32 *)((u8 *)state + 0xAC)));
                    selected_item_record_alias[0] = 0;
                    if ((check_familiar_deployment_placement(state, context_a, context_b, &action_id, &action_arg, selected_item_record_alias[0]) << 0x10)
                        != 0) {
                        display_formatted_context_message(&D_800E2004);
                    } else {
                        enqueue_script_message_command();
                    }
                    (*(s32 *)((u8 *)state + 0xC8)) = 0;
                    begin_familiar_deployment_change(state, context_a, context_b, action_id, (s32) action_arg);
                    {
                        s32 tail_flags = dungeon_floor_flags;

                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        dungeon_floor_flags = tail_flags & ~0x2000;
                    }
                    return;
                }
            } else {
                if (selection_data != NULL) {
                    if ((dungeon_state->pressed_buttons) & 0x10) {
                        select_nearby_target_and_initialize_slot(selection_data - 0x20, ((S_80091430_2_pre *)selection_data)[-1].unk_00, 8,
                            *camera_depth_target);
                        slot_index = (s32) (*(void **)((u8 *)state + 0x104)) != (*(s32 *)((u8 *)state + 0xAC));
                        actor->unk_8A = slot_index;
                        *menu_action_argument = (s32) slot_index;
                        begin_player_menu_action(state, context_a, context_b, &familiar_menu_action_data);
                        ((Rec_D_80082EB0 *)selected_item_record_alias)->unk_00.as_s32 = 0;
                        (*(s32 *)((u8 *)state + 0xC8)) = 0;
                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        enqueue_script_message_command();
                        return;
                    }
                    if ((dungeon_state->pressed_buttons) & 0x20) {
                        slot_index = (s32) (*(void **)((u8 *)state + 0x104)) != (*(s32 *)((u8 *)state + 0xAC));
                        actor->unk_8A = slot_index;
                        *menu_action_argument = (s32) slot_index;
                        begin_player_menu_action(state, context_a, context_b, &D_80023C58);
                        ((Rec_D_80082EB0 *)selected_item_record_alias)->unk_00.as_s32 = 0;
                        (*(s32 *)((u8 *)state + 0xC8)) = 0;
                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        enqueue_script_message_command();
                        return;
                    }
                    if ((dungeon_state->pressed_buttons) & 0x40) {
                        select_nearby_target_and_initialize_slot(selection_data - 0x20, ((S_80091430_2_pre *)selection_data)[-1].unk_00, 8,
                            *camera_depth_target);
                        slot_index = (s32) (*(void **)((u8 *)state + 0x104)) != (*(s32 *)((u8 *)state + 0xAC));
                        actor->unk_8A = slot_index;
                        *menu_action_argument = (s32) slot_index;
                        begin_player_menu_action(state, context_a, context_b, D_8004F5F4);
                        ((Rec_D_80082EB0 *)selected_item_record_alias)->unk_00.as_s32 = 0;
                        (*(s32 *)((u8 *)state + 0xC8)) = 0;
                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        enqueue_script_message_command();
                        return;
                    }
                }
                selection = (*(void **)((u8 *)state + 0x104));
                if ((selection == (*(s32 *)((u8 *)state + 0xAC)))
                    ? !(dungeon_state->buttons & 2)
                    : ((selection != (*(s32 *)((u8 *)state + 0xB0))) || !(dungeon_state->buttons & 1))) {
                    if (dungeon_state->buttons & 3) {
                        candidate_slot = state + 0xAC;
                        if (!(dungeon_state->buttons & 2)) {
                            candidate_slot = state + 0xB0;
                        }
                        candidate = *candidate_slot;
                        if ((candidate != NULL) && ((*(void **)((u8 *)state + 0x104)) != candidate)) {
                            candidate_flags = candidate->flags1C;
                            if (candidate_flags & 0x20000) {
                                if (!(candidate_flags & 0x80000)) {
                                    (*(void **)((u8 *)state + 0x104)) = candidate;
                                    create_panel_effect_object(candidate);
                                    return;
                                }
                            }
                        }
                    } else {
                        (*(void **)((u8 *)state + 0x104)) = NULL;
                        (*(u8 *)((u8 *)state + 0x9B)) = (u8) ((*(u8 *)((u8 *)state + 0x9B)) + 1);
                        return;
                    }
                }
            }
        } else {
            preview = (*(void **)((u8 *)state + 0x104));
            update_selection_tile_markers(preview, preview->action_flags);
            if ((dungeon_state->pressed_buttons) & 0x60) {
                if ((dungeon_state->pressed_buttons) & 0x20) {
                    play_sound_if_enabled(0x515);
                    selection = (*(void **)((u8 *)state + 0x104));
                    selection->action_flags &= 0x7FFF;
                } else {
                    play_sound_if_enabled(0x503);
                }
                (*(void **)((u8 *)state + 0x104)) = NULL;
                enqueue_script_message_command();
                dungeon_floor_flags &= ~0x2000;
                {
                    void *callback;
                    if (actor->flags1C & 0x100000) {
                        callback = player_action_tag;
                    } else {
                        callback =handle_player_input;
                    }
                    (*(void **)((u8 *)state + 0x8C)) = callback;
                }
                update_selection_tile_markers(NULL, 0U);
                return;
            }
        }
        return;
    case FAMILIAR_COMMAND_RESTORE_INPUT:
        (*(s32 *)((u8 *)state + 0xC8)) = 0;
        enqueue_script_message_command();
        dungeon_floor_flags &= ~0x2000;
        {
            void *callback;
            if (actor->flags1C & 0x100000) {
                callback = player_action_tag;
            } else {
                callback =handle_player_input;
            }
            (*(void **)((u8 *)state + 0x8C)) = callback;
        }
        return;
    default:
        return;
    }
}
