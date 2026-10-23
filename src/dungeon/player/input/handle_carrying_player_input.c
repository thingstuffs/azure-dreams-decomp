#include "shared/actor_status_flags.h"
#include "shared/dungeon_actor_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/player/input.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/item.h"
#include "dungeon/player.h"
#include "dungeon/player/motion.h"
#include "dungeon/player/object.h"

extern s32 func_8002534C(void *, void *, void *, void *); /* extern */
void set_sprite_animation_frame(); /* extern */
void apply_pending_byte_increase(); /* extern */
void begin_player_menu_action(); /* extern */
s16 resolve_player_input_facing();             /* extern */
s32 request_familiar_deployment_change(void *, void *, void *, s32, u32); /* extern */
s16 dispatch_selected_item_use();                /* extern */
void resolve_familiar_deployment_request(); /* extern */
void *advance_monster_timed_sequence();                        /* extern */
s32 read_monster_script_entry();                    /* extern */
void *select_item_record_pointer();                      /* extern */
s32 can_entity_gain_level();                  /* extern */
void set_record_integer_tile_center();              /* extern */
s32 has_pending_actor_or_turn_action();                          /* extern */
              /* extern */
s32 lookup_definition_pair_value();                          /* extern */
s32 generate_random_value(void);                          /* extern */
extern M2C_UNK player_menu_action_data;
extern void * create_animated_selection_menu_owner(void *unused, void *source);
extern void submit_enabled_saved_display_value(void);
extern u8 player_wait_frames[];
extern u8 player_carry_frames[];
extern s32 (*actor_command_handlers[])(s32, u16);
extern u8 active_actor_command_code;
extern s32 menu_action_argument;

typedef struct S_8008EAC8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_8008EAC8_1;   /* arg3 in handle_carrying_player_input */

typedef struct S_8008EAC8_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_8008EAC8_6;

typedef struct S_8008EAC8_7 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8008EAC8_7;

typedef struct S_8008EAC8_9 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_8008EAC8_9;

/* Handles commands while carrying an object, including movement, menus, familiar actions, putting it
   down, and throwing. */
void handle_carrying_player_input(void *object, void *aux_entity, SpriteFrameState *sprite, void *entity) {
    GameWork *held_D_80083160 = &g_game_work;
    s16 new_facing;
    s16 value_64;
    s32 target_facing;
    s32 code;
    s32 flags14;
    s32 flags1C;
    u16 facing;
    u16 flags_a2;
    s32 facing_bits;
    u16 flags_a2_late;
    u32 slot;
    u8 data_50;
    u8 data_78;
    u8 data_80;
    u8 data_90;
    u8 data_70;
    s32 expected_facing;
    u16 direction;
    void *move_state;
    s32 tail_data_flags;
    SpriteFrameState *call_arg;
    void *record;
    void *looked_up;

    if (((Rec_func_8008ACDC_arg0 *)object)->unk_9A.as_u8 != 0xE) {
        if (((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0x100) {
            begin_wake_nearby_monsters(object, aux_entity, sprite, entity);
            return;
        }
    }
    ((Rec_func_8008ACDC_arg0 *)object)->unk_9A.as_u8 = 0xEU;
    if (!(((S_8008EAC8_1 *)entity)->unk_14 & 0x100000)) {
        select_position_data_and_update_owner(sprite, entity);
        ((EntityRec *)aux_entity)->unk_10 = 0;
        ((EntityRec *)aux_entity)->unk_0C = 0;
        set_record_integer_tile_center(aux_entity, sprite->tile_x, sprite->tile_y);
    }
    sprite->flags = (u16) (sprite->flags & 0xF7FF);
    ((Rec_func_8008ACDC_arg0 *)object)->unk_9B.as_s8 = 0;
    g_dungeon_status.flags = (u16) (g_dungeon_status.flags & 0xFF7F);
    value_64 = ((S_8008EAC8_1 *)entity)->unk_64;
    if ((value_64 < 0) || (((Rec_func_8008ACDC_arg0 *)object)->unk_10C & 1)) {
        begin_player_damage_reaction(object, aux_entity, sprite, entity);
        return;
    }
    if (value_64 > 0) {
        apply_pending_byte_increase(object, aux_entity, sprite, entity);
    }
    flags14 = ((S_8008EAC8_1 *)entity)->unk_14;
    if (flags14 & 0x20000) {
        ((S_8008EAC8_1 *)entity)->unk_14 = (s32) (flags14 & 0xFFFDFFFF);
    }
    if (!(((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0x10)) {
        select_state_16_directional_animation(object, aux_entity, sprite, entity);
        return;
    }
    flags1C = ((S_8008EAC8_1 *)entity)->unk_1C;
    if (flags1C & ACTOR_ASLEEP) {
        begin_player_sleep_action(object, aux_entity, sprite, entity);
        return;
    }
    if (!(flags1C & ACTOR_CARRYING)) {
        call_arg = sprite;
        {
            void *callback = handle_player_input;
            u8 *table = (u8 *) &player_wait_frames;
            ((Rec_func_8008ACDC_arg0 *)object)->unk_8C.as_pv = callback;
            call_arg->frameTable = table;
            set_sprite_animation_frame(call_arg, *((u8 *) (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) ((S_8008EAC8_1 *)entity)->unk_2A.u
                + 0x100) >> 9) & 7) + (u32) table), 0, 1);
        }
        return;
    }
    if ((((Rec_func_8008ACDC_arg0 *)object)->unk_124 != 0) && (((can_entity_gain_level(entity) << 0x10) == 0)
        || (begin_selected_target_level_up(object, aux_entity, sprite, entity) == 0))) {
        if (!(g_dungeon_status.flags & 4)) {
            if (((S_8008EAC8_1 *)entity)->unk_1C & 0x20) {
                if (!((*(u16 *)0x80013714) & 1) && (((u32)held_D_80083160->buttons) & 0x80)) {
                    ((S_8008EAC8_1 *)entity)->unk_8A = 2;
                    menu_action_argument = 2;
                    begin_player_menu_action(object, aux_entity, sprite, &create_animated_selection_menu_owner);
                    reference_tile_object.selected_item = 0;
                    ((Rec_func_8008ACDC_arg0 *)object)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)object)->unk_104 = 0;
                    return;
                }
                begin_player_wait_turn(object, aux_entity, sprite, entity);
                return;
            }
            if ((*(u16 *)0x80013714) & 1) {
                flags_a2 = ((Rec_func_8008ACDC_arg0 *)object)->unk_A2;
                ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 = (u16) (flags_a2 & 0xFFFE);
                if (flags_a2 & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 = (u16) (flags_a2 & 0xFDFE);
                }
                record = advance_monster_timed_sequence();
                if (record != NULL) {
                    direction = ((S_8008EAC8_6 *)record)->unk_01 & 7;
                    facing = ((S_8008EAC8_1 *)entity)->unk_2A.u;
                    expected_facing = (u8)direction;
                    target_facing = direction << 9;
                    facing_bits = facing & 0xFFF;
                    expected_facing = ((u8)expected_facing) << 9;
                    ((S_8008EAC8_1 *)entity)->unk_2A.u = facing_bits;
                    if (facing_bits != expected_facing) {
                        s32 signed_target;
                        s32 diff;
                        {
                            s32 normalized;
                            if (facing & 0x800) {
                                normalized = facing_bits | 0xF800;
                            } else {
                                normalized = facing & 0x7FF;
                            }
                            ((S_8008EAC8_1 *)entity)->unk_2A.u = normalized;
                        }
                        {
                            if (target_facing & 0x800) {
                                diff = target_facing | 0xF800;
                            } else {
                                diff = target_facing & 0x7FF;
                            }
                            target_facing = diff;
                        }
                        facing_bits = (u32) target_facing << 16;
                        signed_target = facing_bits >> 16;
                        diff = ((S_8008EAC8_1 *)entity)->unk_2A.s;
                        facing_bits = ((S_8008EAC8_1 *)entity)->unk_2A.u;
                        diff -= signed_target;
                        if (diff < 0) {
                            diff = 0 - diff;
                        }
                        if (diff >= 0x801) {
                            ((S_8008EAC8_1 *)entity)->unk_2A.u = (u16) ((target_facing & ~0xFFF) | (facing_bits & 0xFFF));
                        }
                        {
                            s32 step;
                            step = ((S_8008EAC8_1 *)entity)->unk_2A.s;
                            facing_bits = ((S_8008EAC8_1 *)entity)->unk_2A.u;
                            step = signed_target < step;
                            if (step) {
                                step = facing_bits - 0x200;
                            } else {
                                step = facing_bits + 0x200;
                            }
                            ((S_8008EAC8_1 *)entity)->unk_2A.u = step;
                        }
                        read_monster_script_entry(target_facing);
                        call_arg = sprite;
                        call_arg->frameTable = player_carry_frames;
                        set_sprite_animation_frame(call_arg, *((u8 *) (((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                            + (s16) ((S_8008EAC8_1 *)entity)->unk_2A.u + 0x100) >> 9) & 7) + (u32) player_carry_frames), 0, 1);
                        return;
                    }
                    active_actor_command_code = (s8) (((S_8008EAC8_6 *)record)->unk_01 & 0xF8);
                    code = active_actor_command_code;
                    switch (code) {
                    case 0x10:
                        begin_player_wait_turn(object, aux_entity, sprite, entity);
                        return;
                    case 0x48:
                        if (dispatch_selected_item_use(object, ((S_8008EAC8_6 *)record)->unk_00 & 0x1F,
                            ((S_8008EAC8_6 *)record)->unk_02 & 0x1F) >= 0) {
                            initialize_monster_script_counter();
                            return;
                        }
                        read_monster_script_entry();
                        return;
                    case 0x50:
                        data_50 = ((S_8008EAC8_6 *)record)->unk_00;
                        record = (void *) ((u32) (data_50 & 0x60) >> 5);
                        looked_up = select_item_record_pointer(data_50 & 0x1F, facing);
                        if (dispatch_dungeon_category_action(((S_8008EAC8_7 *)(((((u32) record) * 4) + object)))->unk_AC, looked_up, 0x15,
                            0) < 0) {
                            read_monster_script_entry();
                            return;
                        }
                        return;
                    case 0x68:
                        looked_up = select_item_record_pointer(((S_8008EAC8_6 *)record)->unk_00 & 0x1F, facing);
                        slot = ((S_8008EAC8_6 *)record)->unk_00;
                        slot &= 0x60;
                        slot >>= 5;
                        request_familiar_deployment_change(object, aux_entity, sprite, (s32) looked_up, slot);
                        return;
                    case 0x88:
                        slot = ((S_8008EAC8_6 *)record)->unk_00;
                        slot &= 0x60;
                        slot >>= 5;
                        {
                            s32 fourth;
                            fourth = ((FamiliarItemSlotView *)(((slot * 4) + (u8 *)object)))->item_address;
                            request_familiar_deployment_change(object, aux_entity, sprite, fourth, slot);
                        }
                        return;
                    case 0x70:
                        data_70 = ((S_8008EAC8_6 *)record)->unk_00;
                        set_linked_actor_octant_facing((u32) (data_70 & 0x60) >> 5, data_70 & 7);
                        return;
                    case 0x78:
                        data_78 = ((S_8008EAC8_6 *)record)->unk_00;
                        set_linked_actor_code_and_mirror((u32) (data_78 & 0x60) >> 5, data_78 & 0x1F);
                        return;
                    case 0x80:
                        data_80 = ((S_8008EAC8_6 *)record)->unk_00;
                        set_linked_actor_pending_halfword((u32) (data_80 & 0x60) >> 5, data_80 & 0x1F);
                        return;
                    case 0x90:
                        data_90 = ((S_8008EAC8_6 *)record)->unk_00;
                        set_familiar_formation_offset((u32) (data_90 & 0x60) >> 5, data_90 & 7);
                        return;
                    case 0x98:
                        looked_up = select_item_record_pointer(((S_8008EAC8_6 *)record)->unk_00 & 0x1F, facing);
                        if (((S_8008EAC8_9 *)looked_up)->unk_03 & 0x20) {
                            resolve_familiar_deployment_request(object, aux_entity, sprite, looked_up);
                            return;
                        }
                        begin_familiar_summoning(object, aux_entity, sprite, looked_up);
                        return;
                    case 0xA0:
                        func_8002534C(object, aux_entity, sprite, entity);
                        return;
                    case 0xD8:
                        actor_command_handlers[((S_8008EAC8_6 *)record)->unk_00 & 0x7F](target_facing, facing);
                        return;
                    case 8:
                        move_state = object;
                        try_move_carrying_player(move_state, aux_entity, sprite, entity);
                        return;
                    case 0x28:
                        try_begin_put_down_carried_object(object, aux_entity, sprite, entity);
                        return;
                    case 0x30:
                        ((Rec_func_8008ACDC_arg0 *)object)->unk_96.as_s16 = 6;
                        begin_throw_carried_object(object, aux_entity, sprite, entity);
                        return;
                    default:
                        return;
                    }
                }
            } else {
                s32 flag_200;

                flag_200 = ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0x200;
                active_actor_command_code = 0;
                if (flag_200 && ((has_pending_actor_or_turn_action(entity) << 0x10) == 0) && !(g_dungeon_status.flags & 4)) {
                    ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 =
                        (u16) (((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0xFDFF);
                    if ((lookup_definition_pair_value(sprite->tile_x, sprite->tile_y) << 0x10)
                        != 0) {
                        begin_player_menu_action(object, aux_entity, sprite, &player_menu_action_data);
                        return;
                        return;
                    }
                }
                if (((u32)held_D_80083160->buttons) & 0x80) {
                    begin_player_menu_action(object, aux_entity, sprite, &submit_enabled_saved_display_value);
                    return;
                }
                if ((((u32)held_D_80083160->buttons) & 0x10) || !(((u32)held_D_80083160->buttons) & 3)
                    || (begin_familiar_command_selection(object, aux_entity, sprite, (((u32) ((u32)held_D_80083160->buttons) >> 1) ^ 1) & 1, 0)
                    == 0)) {
                    new_facing = resolve_player_input_facing(((Rec_func_8008ACDC_arg0 *)object)->unk_9E, object + 0xA2, entity + 0x2A);
                    if (new_facing != 0xFFF) {
                        ((S_8008EAC8_1 *)entity)->unk_2A.u = (u16) new_facing;
                        if (!(((u32)held_D_80083160->buttons) & 0x10)) {
                            flags_a2_late = ((Rec_func_8008ACDC_arg0 *)object)->unk_A2;
                            if (!(flags_a2_late & 0x400)) {
                                ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 = (u16) (flags_a2_late & 0xFFFE);
                                if (((S_8008EAC8_1 *)entity)->unk_1C & 0x400) {
                                    ((S_8008EAC8_1 *)entity)->unk_2A.u =
                                        (u16) (((S_8008EAC8_1 *)entity)->unk_2A.u + (generate_random_value() & 0xE00));
                                }
                                move_state = object;
                                try_move_carrying_player(move_state, aux_entity, sprite, entity);
                                return;
                            }
                        }
                    }
                    tail_data_flags = ((u32)held_D_80083160->buttons);
                    if ((tail_data_flags & 0x30) == 0x30) {
                        ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 =
                            (u16) (((Rec_func_8008ACDC_arg0 *)object)->unk_A2 & 0xFFFE);
                        begin_player_wait_turn(object, aux_entity, sprite, entity);
                        return;
                    }
                    {
                        s32 flag40;

                        flags_a2_late = ((Rec_func_8008ACDC_arg0 *)object)->unk_A2;
                        flag40 = flags_a2_late & 0x40;
                        if (flag40) {
                            flag40 = tail_data_flags & 0x40;
                            if (flag40 == 0) {
                                ((Rec_func_8008ACDC_arg0 *)object)->unk_A2 = (u16) (flags_a2_late & 0xFFBF);
                            }
                        } else if (tail_data_flags & 0x40) {
                            if (!(tail_data_flags & 0x20)) {
                                try_begin_put_down_carried_object(object, aux_entity, sprite, entity);
                                return;
                            }
                            ((Rec_func_8008ACDC_arg0 *)object)->unk_96.as_s16 = 6;
                            begin_throw_carried_object(object, aux_entity, sprite, entity);
                            return;
                        }
                    }
                    call_arg = sprite;
                    call_arg->frameTable = player_carry_frames;
                    set_sprite_animation_frame(call_arg, *((u8 *) (((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                        + (s16) ((S_8008EAC8_1 *)entity)->unk_2A.u + 0x100) >> 9) & 7) + (u32) player_carry_frames), 0, 1);
                }
            }
        } else {
            call_arg = sprite;
            call_arg->frameTable = player_carry_frames;
            set_sprite_animation_frame(call_arg, *((u8 *) (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) ((S_8008EAC8_1 *)entity)->unk_2A.u
                + 0x100) >> 9) & 7) + (u32) player_carry_frames), 0, 1);
        }
    }
}
