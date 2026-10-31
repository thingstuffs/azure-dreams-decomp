#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/killer.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "engine/graphics.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"


typedef struct S_80173C20_1 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0x18];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80173C20_1;   /* entity_data in advance_directional_lift_effect */



extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
u8 *clear_byte_and_advance(u8 *byte_ptr);
extern u8 *append_entity_display_text(void *record, u8 *out);
s32 display_text_with_fullwidth_adjustment(s8 *text);
void spend_actor_mp(ActorRecord *entity, s32 base_reduction);

extern void *actor_update_node_cursor;
extern u8 D_80170854[];
extern u8 D_80170874[];
extern u8 killer_action_resume_address;
extern u8 D_80174090[];
extern u8 D_80174098[];
extern u8 D_801740A0[];

/* Displays a directional message, animates a rising attack, applies damage, spends MP, and restores actor
 * state. */
void advance_directional_lift_effect(void *action_record, ObjectPosition *motion_data, SpriteFrameState *status_record, void *entity_data_arg)
{
    S_80173C20_1 *entity_data = entity_data_arg;
    s32 state;
    void *saved;
    s32 value;
    s32 index;
    u16 timer;

    state = ((ActorRecord *)action_record)->action_phase.u;
    switch (state) {
    case 0:
        saved = get_unused_text_buffer();
        if ((entity_data->unk_2A.s >> 9) & 1) {
            clear_byte_and_advance(expand_text_control_codes(
                D_80170854, append_entity_display_text(entity_data, saved)));
        } else {
            clear_byte_and_advance(expand_text_control_codes(
                D_80170874, append_entity_display_text(entity_data, saved)));
        }
        display_text_with_fullwidth_adjustment(saved);

        if (status_record->flags & 0x8000) {
            ((ActorRecord *)action_record)->action_phase.u = 3;
            ((ActorRecord *)action_record)->action_timer.u = 0;
            status_record->flags |= 0x6000;
            resolve_attack_damage_and_effects(entity_data, status_record, entity_data->unk_2A.u, 1);
            break;
        }
        status_record->frameTable = D_80174090;
        index = (g_game_work.view.camera_rotation.parts.viewAngle + entity_data->unk_2A.u + 0x100) >> 9;
        select_sprite_entry(status_record, D_80174090[index & 7], 0);
        ((ActorRecord *)action_record)->unk_90.value = 0;
        ((ActorRecord *)action_record)->action_state_flags |= 8;
        motion_data->velocity_z = 0xFFF00000;
        ((ActorRecord *)action_record)->action_phase.u++;
        break;
    case 1:
        value = motion_data->velocity_z + 0x20000;
        motion_data->velocity_z = value;
        ((ActorRecord *)action_record)->unk_90.value += value;
        if (!(status_record->flags & 0xE000)) {
            break;
        }
        status_record->frameTable = D_80174098;
        index = (g_game_work.view.camera_rotation.parts.viewAngle + entity_data->unk_2A.u + 0x100) >> 9;
        select_sprite_entry(status_record, D_80174098[index & 7], 0);
        ((ActorRecord *)action_record)->action_timer.u = 8;
        ((ActorRecord *)action_record)->action_state_flags &= 0xFFF7;
        ((ActorRecord *)action_record)->action_phase.u++;
        break;
    case 2:
        timer = ((ActorRecord *)action_record)->action_timer.u - 1;
        ((ActorRecord *)action_record)->action_timer.u = timer;
        if (((timer << 16) == 0) || (status_record->flags & 0x8000)) {
            resolve_attack_damage_and_effects(entity_data, status_record, entity_data->unk_2A.u, 1);
        }
        if (!(status_record->flags & 0xE000)) {
            break;
        }
        status_record->frameTable = D_801740A0;
        index = (g_game_work.view.camera_rotation.parts.viewAngle + entity_data->unk_2A.u + 0x100) >> 9;
        select_sprite_entry(status_record, D_801740A0[index & 7], 0);

        ((ActorRecord *)action_record)->action_phase.u++;
        break;
    case 3:
        if (status_record->flags & 0xE000) {
            motion_data->velocity_y = 0;
            motion_data->velocity_x = 0;
            spend_actor_mp(entity_data_arg, 0x1000);
            ((ActorRecord *)action_record)->unk_8C.address = &killer_action_resume_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(entity_data);

            if (((ActorRecord *)action_record)->action_state_flags & 0x4000) {
                entity_data->unk_1C |= ACTOR_ANGRY;
            } else {
                entity_data->unk_1C &= ~ACTOR_ANGRY;
            }
            entity_data->unk_03 = ((ActorRecord *)action_record)->unk_AC.byte;
            if (entity_data->unk_6D == 0) {
                entity_data->unk_46 &= 0x7FFF;
            } else {
                actor_update_node_cursor = (u8 *)entity_data - 0x20;
            }
        }
        break;
    }
}
