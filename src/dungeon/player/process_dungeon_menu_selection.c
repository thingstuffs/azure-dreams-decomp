#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008D024_arg0.h"
#include "records/Rec_D_80082EB0.h"
#include "dungeon/level.h"
#include "dungeon/player.h"
#include "dungeon/player/item.h"
#include "dungeon/player/object.h"
#include "dungeon/player/position.h"

typedef struct S_80090C10_1 {
    union { s32 s; void * (*u)(s32, s32); } unk_00;   /* accessed as both */
    s32 unk_04;
    s32 unk_08;
} S_80090C10_1;   /* &D_800E4938 in process_dungeon_menu_selection */

typedef struct S_80090C10_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80090C10_4;

typedef struct S_80090C10_5 {
    s32 unk_00;
} S_80090C10_5;   /* &D_800E296C in process_dungeon_menu_selection */

typedef struct S_80090C10_6 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
} S_80090C10_6;   /* (*(void **)&D_80082EB0) in process_dungeon_menu_selection */

typedef struct S_80090C10_8 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x40];
    s32 unk_60;
} S_80090C10_8;

typedef struct S_80090C10_9 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80090C10_9;   /* (((s32) (*(void **)&D_80082EB0) * 4) + arg0) in process_dungeon_menu_selection */

typedef struct S_80090C10_10 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x32];
    u16 unk_46;
} S_80090C10_10;

typedef struct S_80090C10_11 {
    void * unk_00;
    u8 pad_04[0x4];
    u16 unk_08;
} S_80090C10_11;   /* case_base in process_dungeon_menu_selection */

typedef struct S_80090C10_12 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80090C10_12;   /* ((Rec_func_8008D024_arg0 *)arg0)->unk_C8 in process_dungeon_menu_selection */

typedef struct S_80090C10_13 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
} S_80090C10_13;   /* ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv in process_dungeon_menu_selection */

typedef struct S_80090C10_14 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80090C10_14;   /* (((s32) ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv * 4) + arg0) in process_dungeon_menu_selection */

typedef struct DdcbcEntry {
    u8 pad[7];
    u8 flags;
} DdcbcEntry;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8002534C(void *, s32, void *, ActorRecord *); /* extern */
void select_record_entry_and_value();        /* extern */
s32 get_entity_effect_value();                 /* extern */
void set_sprite_animation_frame(); /* extern */
void read_vram_blocks_to_buffer();                            /* extern */
void begin_deferred_item_action(); /* extern */
void initialize_action_state_29(); /* extern */
s32 request_familiar_deployment_change(); /* extern */
void resolve_familiar_deployment_request(); /* extern */
void restore_player_control_callback();              /* extern */
void equip_item_and_update_status();              /* extern */
void change_equipped_item_and_notify();              /* extern */
s16 get_special_table_data_index();                          /* extern */
s32 get_unused_text_buffer();                                /* extern */
s32 expand_text_control_codes();                  /* extern */
void *clear_byte_and_advance();                         /* extern */
s32 append_entity_display_text();                        /* extern */
void display_formatted_context_message();                   /* extern */
void append_packed_action_record();   /* extern */
s32 display_text_with_fullwidth_adjustment();                         /* extern */
s32 is_selectable_menu_target();                             /* extern */
void update_selection_tile_markers();            /* extern */
extern M2C_UNK D_8001EF2C;
extern M2C_UNK D_8004F5F4;
extern M2C_UNK selected_item_record_alias;
extern s32 selected_item_action_alias;
extern s8 spell_effect_selector_cache;
extern u8 player_wait_frames[];
extern u8 player_carry_frames[];
extern u8 actor_default_frames[];
extern DdcbcEntry species_growth_table[];
extern M2C_UNK D_800E0462;
extern M2C_UNK D_800E0472;
extern M2C_UNK D_800E0542;
extern M2C_UNK D_800E0571;
extern u8 D_800E069D[32];
extern u8 D_800E06BD[3];
extern u8 D_800E06C0[32];
extern u8 D_800E06E0[3];
extern s32 familiar_record_slots[];
extern s32 dungeon_menu_action_state[];

/* Wait for the menu to close, then dispatch the selected item or companion action. */
void process_dungeon_menu_selection(void *state, s32 context, SpriteFrameState *sprite, ActorRecord *actor) {
    s16 tile_x;
    s16 tile_y;
    u8 *anim_table;
    s32 item_text_id;
    s16 action_index;
    s32 ui_flags;
    s32 item_result;
    s32 direction;
    s32 text_buffer;
    s32 text_end;
    s32 state_allowed;
    s32 phase;
    u8 companion_flags;
    s32 companion_value;
    void *menu;
    void *selection;
    void *companion;

    phase = ((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8;
    switch (phase) {
    case 0:
        spell_effect_selector_cache = -1;
        read_vram_blocks_to_buffer();
        if (((S_80090C10_1 *)(&dungeon_menu_action_state))->unk_00.s != &D_8004F5F4) {
            if ((get_entity_effect_value(actor, 0xA) << 0x10) != 0) {
                sprite->frameTable = &actor_default_frames;
                select_record_entry_and_value(sprite, *(s32 *)(actor_default_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                    >> 7) & 0x1C)), 0);
            } else {
                if (actor->flags1C & 0x100000) {
                    anim_table = player_carry_frames;
                } else {
                    anim_table = player_wait_frames;
                }
                sprite->frameTable = anim_table;
                set_sprite_animation_frame(sprite, *(anim_table + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                    0, 1);
            }
        }
        ((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 = (u8) (((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 + 1);
    case 1:
        menu = ((S_80090C10_1 *)(&dungeon_menu_action_state))->unk_00.u(((S_80090C10_1 *)(&dungeon_menu_action_state))->unk_04,
            ((S_80090C10_1 *)(&dungeon_menu_action_state))->unk_08);
        ((Rec_func_8008D024_arg0 *)state)->unk_C8 = menu;
        if (menu == NULL) {
            return;
        }
        ((Rec_func_8008D024_arg0 *)state)->unk_96 = 0;
        ((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv = NULL;
        selection = &selected_item_record_alias;
        ((S_80090C10_4 *)selection)->unk_04 = 0;
        ((S_80090C10_4 *)selection)->unk_08 = 0;
        ((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 = (u8) (((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 + 1);
    case 2:
        break;
    default:
        return;
    }
    if (((S_80090C10_12 *)(((Rec_func_8008D024_arg0 *)state)->unk_C8))->unk_1E & 0x8000) {
        update_selection_tile_markers(0, 0);
        ui_flags = ((S_80090C10_5 *)(&dungeon_floor_flags))->unk_00;
        ((Rec_func_8008D024_arg0 *)state)->unk_C8 = NULL;
        (*(s32 *)&dungeon_floor_flags) = ui_flags & ~0x2000;
    }
    if (((Rec_func_8008D024_arg0 *)state)->unk_C8 != NULL) {
        return;
    }
    switch (selected_item_action_alias) {
    case 1:
        append_packed_action_record(actor, 0x48, get_special_table_data_index(((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv), 0);
        if (((S_80090C10_6 *)((*(void **)&selected_item_record_alias)))->unk_01 == 0x11) {
            change_equipped_item_and_notify(actor, (*(void **)&selected_item_record_alias));
            selected_item_action_alias = 0;
            break;
        }
        equip_item_and_update_status(actor, (*(void **)&selected_item_record_alias));
        selected_item_action_alias = 0;
        break;
    case 2:
        if (((S_80090C10_13 *)(((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv))->unk_01 == 0x11) {
            append_packed_action_record(actor, 0x48, get_special_table_data_index((*(void * *)&actor->unk_50)), 0);
            change_equipped_item_and_notify(actor, NULL);
            selected_item_action_alias = 0;
            break;
        }
        append_packed_action_record(actor, 0x48, get_special_table_data_index(actor->unk_4C), 0);
        equip_item_and_update_status(actor, NULL);
        selected_item_action_alias = 0;
        break;
    case 21:
        if (((S_80090C10_13 *)(((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv))->unk_03 & 0x20) {
            display_formatted_context_message(&D_800E0542);
            selected_item_action_alias = 0;
            break;
        }
        if (is_selectable_menu_target(((Rec_func_8008D024_arg0 *)state)->unk_AC) != 0 || is_selectable_menu_target(((Rec_func_8008D024_arg0 *)state)->unk_B0) != 0) {
            initialize_action_state_29(state, context, sprite, actor);
            return;
        }
        display_formatted_context_message(&D_800E0571);
        selected_item_action_alias = 0;
        break;
    case 3:
    case 4:
    case 20:
        item_result = dispatch_dungeon_category_action(actor, ((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv, 3, 0);
        if (item_result >= 0) {
            item_text_id = (s16) get_special_table_data_index((*(void **)&selected_item_record_alias));
            append_packed_action_record(actor, 0x48, item_text_id, get_special_table_data_index(((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_04));
            if (item_result > 0) {
                goto block_64;
            }
            if (item_result >= 0) {
                return;
            }
        }
        if (((S_80090C10_6 *)((*(void **)&selected_item_record_alias)))->unk_01 != 0x15) {
            return;
        }
        ((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 = 3U;
        return;
    case 5:
        append_packed_action_record(actor, 0x58, 0, get_special_table_data_index(((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv));
        begin_holding_item(state, context, sprite, (*(void **)&selected_item_record_alias));
        selected_item_action_alias = 0;
        break;
    case 8:
    case 9:
        append_packed_action_record(actor, 0x98, 0, get_special_table_data_index(((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv));
        if (((S_80090C10_6 *)((*(void **)&selected_item_record_alias)))->unk_03 & 0x20) {
            resolve_familiar_deployment_request(state, context, sprite, (*(void **)&selected_item_record_alias));
            selected_item_action_alias = 0;
            break;
        }
        direction = ((u16) actor->facing >> 9) & 7;
        if ((find_valid_nearby_position(0, (s16) (sprite->unk_24 + dir_step_x[direction]),
            (s16) (sprite->unk_25 + dir_step_y[direction]), &tile_x, &tile_y) << 0x10) == 0) {
            text_buffer = get_unused_text_buffer();
            text_end = append_entity_display_text(familiar_record_slots[((S_80090C10_6 *)((*(void **)&selected_item_record_alias)))->unk_03 & 0x1F],
                expand_text_control_codes(D_800E069D, text_buffer));
            clear_byte_and_advance(expand_text_control_codes(D_800E06BD, text_end));
            display_text_with_fullwidth_adjustment(text_buffer);
            selected_item_action_alias = 0;
            break;
        }
        if (begin_familiar_summoning(state, context, sprite, (*(void **)&selected_item_record_alias)) != 0) {
            return;
        }
        text_buffer = get_unused_text_buffer();
        text_end = append_entity_display_text(familiar_record_slots[((S_80090C10_6 *)((*(void **)&selected_item_record_alias)))->unk_03 & 0x1F],
            expand_text_control_codes(D_800E06C0, text_buffer));
        clear_byte_and_advance(expand_text_control_codes(D_800E06E0, text_end));
        display_text_with_fullwidth_adjustment(text_buffer);
        goto block_64;
    case 10:
        func_8002534C(state, context, sprite, actor);
        ((Rec_func_8008D024_arg0 *)state)->unk_C8 = NULL;
        return;
    case 14:
        begin_deferred_item_action(state, context, sprite, actor);
        ((Rec_func_8008D024_arg0 *)state)->unk_C8 = NULL;
        goto block_64;
    case 12:
        companion_value = (s32) ((S_80090C10_14 *)((((s32) ((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv * 4)
            + state)))->unk_AC;
        if (!(((S_80090C10_8 *)((void *)companion_value))->unk_1C & 0x80000)) {
            ((S_80090C10_8 *)((void *)companion_value))->unk_60 = 0;
        }
        if (((S_80090C10_1 *)(&dungeon_menu_action_state))->unk_00.s == &D_8001EF2C) {
            selected_item_action_alias = 0;
            break;
        }
        companion = ((S_80090C10_9 *)((((s32) (*(void **)&selected_item_record_alias) * 4) + state)))->unk_AC;
        companion_value = ((S_80090C10_10 *)companion)->unk_46 & 0x3FFF;
        if ((u32) (companion_value - 5) < 3U) {
            selected_item_action_alias = 0;
            break;
        }
        if ((u32) (companion_value - 9) < 2U) {
            companion_flags = species_growth_table[((S_80090C10_10 *)companion)->unk_13].flags;
            if (companion_value != 9) {
                state_allowed = companion_flags & 2;
            } else {
                state_allowed = companion_flags & 1;
            }
            if (state_allowed != 0) {
                selected_item_action_alias = 0;
                break;
            }
        }
        if (begin_familiar_command_selection(state, context, sprite, (s16) ((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv, 1) != 0) {
            return;
        }
        selected_item_action_alias = 0;
        break;
    case 16:
        ((Rec_func_8008D024_arg0 *)state)->unk_BC = (void *) ((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv;
        if (begin_target_flagged_action(state, context, sprite, actor) != 0) {
            return;
        }
        selected_item_action_alias = 0;
        break;
    case 6:
    case 7:
    {
        u8 *action_data = (u8 *)&selected_item_record_alias;
        action_index = ((S_80090C10_11 *)action_data)->unk_08 - 6;
        actor->unk_8A = action_index;
        if (request_familiar_deployment_change(state, context, sprite, ((S_80090C10_11 *)action_data)->unk_00, (s32) action_index) == 0) {
            return;
        }
        selected_item_action_alias = 0;
        break;
    }
    case 17:
    case 18:
        register_item_object_in_free_slot(((Rec_D_80082EB0 *)(&selected_item_record_alias))->unk_00.as_pv, &D_800E0462, &D_800E0472, 1);
        goto block_64;
    case 19:
        begin_special_tile_transition(state, context, sprite, actor);
        return;
    case 15:
    default:
block_64:
        selected_item_action_alias = 0;
    }
    if (((Rec_func_8008D024_arg0 *)state)->unk_C8 != NULL) {
        return;
    }
    ((Rec_func_8008D024_arg0 *)state)->unk_A2 = (u16) (((Rec_func_8008D024_arg0 *)state)->unk_A2 | 0x40);
    restore_player_control_callback(state, actor);
    return;
}
