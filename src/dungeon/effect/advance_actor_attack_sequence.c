
struct ObjectPosition;
#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/effect.h"
#include "dungeon/effect/object.h"

typedef struct S_80048A44_Obj S_80048A44_Obj;

void set_sprite_animation_frame(S_80048A44_Obj *obj, s16 frame_group, s16 frame_index, s32 slot_index); /* extern */
void process_unflagged_linked_entries();                         /* extern */
s32 resolve_attack_damage_and_effects();    /* extern */
void set_record_integer_tile_center();              /* extern */
s32 play_sound_if_enabled();                     /* extern */
s32 update_attached_effect_state();             /* extern */
s32 select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s32 slot_value); /* extern */
extern u8 actor_attack_frames[];
extern u8 D_800DD068[];
extern u8 D_800DD070[];
extern u8 D_800DD078[];
extern u8 D_800DD080[];
extern u8 player_attack_start_frames[];
extern u8 player_attack_followup_frames[];
extern u8 D_800DD098[];
extern u8 D_800DD0A0[];
extern u8 D_800DD0A8[];
extern u8 D_800DD0B0[];
extern s32 D_800DF244[];
extern s16 D_800DF248[];

typedef struct S_800B348C_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x2];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x23];
    u8 * unk_CC;
    u8 pad_D0[0x24];
    s32 unk_F4;
    u8 pad_F8[0xA];
    u8 unk_102;
} S_800B348C_0;   /* action_state in advance_actor_attack_sequence */

typedef struct S_800B348C_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800B348C_4_pre;   /* the 0x14 bytes before attack_target in advance_actor_attack_sequence, addressed as attack_target[-1] */

typedef struct S_800B348C_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B348C_4;   /* attack_target in advance_actor_attack_sequence */

typedef struct S_800B348C_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B348C_7;   /* ((S_800B348C_4_pre *)attack_target)[-1].unk_00 in advance_actor_attack_sequence */

/* Advances the attack and mixing sequence, resetting element flags at its start and finish. */
void advance_actor_attack_sequence(void *action_state, ObjectPosition *motion, void *animation, ActorRecord *actor) {
    u8 *windup_animations;
    u8 *attack_animations;
    u8 *mix_animations;
    s32 sound_id;
    s32 vertical_velocity;
    s32 unused_result;
    s32 launch_direction_offset;
    s32 resume_direction_offset;
    u16 attack_delay;
    u16 mix_delay;
    u16 return_delay;
    u8 jt_index;

#define motion motion
#define animation animation
    jt_index = ((S_800B348C_0 *)action_state)->unk_9B;
    switch (jt_index) {
    case 0:
        actor->flags14 = (s32) (actor->flags14 & ~7);
        ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
        D_800DF248[0] = 0;
        return;
    case 1:
        if (((S_800B348C_0 *)action_state)->unk_A6 != 0) {
            (*(u8 **)((u8 *)animation + 0x2C)) = actor_attack_frames;
            set_sprite_animation_frame(animation, actor_attack_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0,
                1);
            ((S_800B348C_0 *)action_state)->unk_CC = 0;
            if ((u16) ((S_800B348C_0 *)action_state)->unk_A6 >= 2U) {
                return;
            }
        } else {
            ((S_800B348C_0 *)action_state)->unk_F4 = 0;
        }
        ((S_800B348C_0 *)action_state)->unk_98 = (u16) (((S_800B348C_0 *)action_state)->unk_98 & 0xDFFF);
        ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
    case 2:
        if (((S_800B348C_0 *)action_state)->unk_A6 == 0) {
            select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, motion, 8, 0x300);
            (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD068;
            set_sprite_animation_frame(animation, D_800DD068[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0,
                1);
            ((S_800B348C_0 *)action_state)->unk_CC = 0;
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
            return;
        }
        break;
    case 3:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            launch_direction_offset = ((u16) actor->facing >> 8) & 0xE;
            motion->velocity_x = (s32) (*(s16 *)((u8 *)((s8 *)dir_step_x) + launch_direction_offset) << 0x11);
            motion->velocity_y = (s32) (*(s16 *)((u8 *)((s8 *)dir_step_y) + launch_direction_offset) << 0x11);
            motion->velocity_z = 0xFFEBC000;
            (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD070;
            set_sprite_animation_frame(animation, D_800DD070[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0,
                1);
            {
                u8 *next_animations;

                if (((s32)actor->unk_4C) != 0) {
                    next_animations = D_800DD078;
                } else {
                    next_animations = D_800DD0A8;
                }
                ((S_800B348C_0 *)action_state)->unk_CC = next_animations;
            }
            ((S_800B348C_0 *)action_state)->unk_98 = (u16) (((S_800B348C_0 *)action_state)->unk_98 & 0xFFF7);
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
            return;
        }
        break;
    case 4:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            windup_animations = ((S_800B348C_0 *)action_state)->unk_CC;
            (*(u8 **)((u8 *)animation + 0x2C)) = windup_animations;
            set_sprite_animation_frame(animation, *(windup_animations + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                >> 9) & 7)), 0, 1);
            {
                u8 *next_v1;

                if (((s32)actor->unk_4C) != 0) {
                    next_v1 = D_800DD080;
                } else {
                    next_v1 = D_800DD0B0;
                }
                    ((S_800B348C_0 *)action_state)->unk_CC = next_v1;
            }
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
            return;
        }
        break;
    case 5:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            if (((S_800B348C_0 *)action_state)->unk_A8 != 0) {
                D_800DF248[0] = 1;
                ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
                return;
            }
            ((S_800B348C_0 *)action_state)->unk_96.u = 4U;
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 0xA);
            return;
        }
        break;
    case 15:
        attack_delay = ((S_800B348C_0 *)action_state)->unk_96.u - 1;
        ((S_800B348C_0 *)action_state)->unk_96.u = attack_delay;
        if (((attack_delay << 0x10) <= 0) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
            sound_id = 0x606;
            if (((s32)actor->unk_4C) != 0) {
                sound_id = 0x605;
            }
            play_sound_if_enabled(sound_id);
            attack_animations = ((S_800B348C_0 *)action_state)->unk_CC;
            (*(u8 **)((u8 *)animation + 0x2C)) = attack_animations;
            set_sprite_animation_frame(animation, *(attack_animations + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                >> 9) & 7)), 0, 1);
            ((S_800B348C_0 *)action_state)->unk_CC = player_attack_start_frames;
            ((S_800B348C_0 *)action_state)->unk_96.u = 2U;
            ((S_800B348C_0 *)action_state)->unk_9B = 7U;
            return;
        }
        break;
    case 6:
        ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v
            | 0x800);
        ((S_800B348C_0 *)action_state)->unk_98 = (u16) (((S_800B348C_0 *)action_state)->unk_98 | 8);
        vertical_velocity = motion->velocity_z;
        motion->velocity_x = 0;
        motion->velocity_y = 0;
        motion->velocity_z = 0;
        mix_delay = ((S_800B348C_0 *)action_state)->unk_96.u - 1;
        ((S_800B348C_0 *)action_state)->unk_96.u = mix_delay;
        D_800DF244[0] = vertical_velocity;
        if ((s16)mix_delay < 0) {
            resume_direction_offset = ((u16) actor->facing >> 8) & 0xE;
            motion->velocity_x = (s32) (*(s16 *)((u8 *)((s8 *)dir_step_x) + resume_direction_offset) << 0x11);
            motion->velocity_y = (s32) (*(s16 *)((u8 *)((s8 *)dir_step_y) + resume_direction_offset) << 0x11);
            motion->velocity_z = vertical_velocity;
            ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v =
                (u16) (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xF7FF);
            ((S_800B348C_0 *)action_state)->unk_96.u = 4U;
            ((S_800B348C_0 *)action_state)->unk_98 = (u16) (((S_800B348C_0 *)action_state)->unk_98 & 0xFFF7);
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
            allocate_payload_object(action_state - 0x20, ((S_800B348C_0 *)action_state)->unk_F4, 0x40);
            mix_animations = ((S_800B348C_0 *)action_state)->unk_CC;
            (*(u8 **)((u8 *)animation + 0x2C)) = mix_animations;
            set_sprite_animation_frame(animation, *(mix_animations + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                >> 9) & 7)), 0, 1);
            ((S_800B348C_0 *)action_state)->unk_CC = player_attack_start_frames;
            apply_effect_bonuses(((S_800B348C_0 *)action_state)->unk_A8, actor->target, actor);
            return;
        }
        break;
    case 7:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000) {
            ((S_800B348C_0 *)action_state)->unk_96.u = 0U;
        } else {
            ((S_800B348C_0 *)action_state)->unk_96.u = (u16) (((S_800B348C_0 *)action_state)->unk_96.u - 1);
        }
        if (((S_800B348C_0 *)action_state)->unk_96.s == 0) {
            if (((S_800B348C_0 *)action_state)->unk_102 == 0) {
                s32 attack_target;

                attack_target = resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
                if (attack_target != 0) {
                    update_attached_effect_state(((S_800B348C_0 *)action_state)->unk_A8, attack_target, actor);
                    ((S_800B348C_0 *)action_state)->unk_A8 = 0U;
                } else {
                    attack_target = (s32)actor->target;
                    if (attack_target != 0) {
                        actor->target = 0;
                        ((S_800B348C_4 *)attack_target)->unk_1C = (s32) (((S_800B348C_4 *)attack_target)->unk_1C & 0xEFFFFFFF);
                        ((S_800B348C_7 *)(((S_800B348C_4_pre *)attack_target)[-1].unk_00))->unk_0C = 0x808080;
                        }
                }
            } else {
                ActorRecord *attached_object;

                attached_object = actor->target;
                if (attached_object != 0) {
                    attached_object->flags14 = (s32) (attached_object->flags14 | 0x01000000);
                }
            }
        }
        if (((s16) ((S_800B348C_0 *)action_state)->unk_96.u <= 0)
            && (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000)) {
            (*(u8 **)((u8 *)animation + 0x2C)) = player_attack_start_frames;
            set_sprite_animation_frame(animation, player_attack_start_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0,
                1);
            ((S_800B348C_0 *)action_state)->unk_CC = player_attack_followup_frames;
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
        }
                /* fallthrough */
    case 8:
        if (((S_800B348C_0 *)action_state)->unk_A2 & 0x10) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if (((S_800B348C_0 *)action_state)->unk_A8 != 0) {
                ((S_800B348C_0 *)action_state)->unk_A8 = 0U;
            }
            if ((s16) ((S_800B348C_0 *)action_state)->unk_96.u <= 0) {
                (*(u8 **)((u8 *)animation + 0x2C)) = player_attack_followup_frames;
                set_sprite_animation_frame(animation, player_attack_followup_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                    >> 9) & 7], 0, 1);
                ((S_800B348C_0 *)action_state)->unk_CC = D_800DD098;
                ((S_800B348C_0 *)action_state)->unk_9B = 9U;
                return;
            }
        }
        break;
    case 9:
    {
        s32 delta_x;
        s32 delta_y;

        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            motion->velocity_z = 0;
            (*(u8 **)((u8 *)animation + 0x2C)) = D_800DD098;
            set_sprite_animation_frame(animation, D_800DD098[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0,
                1);
            ((S_800B348C_0 *)action_state)->unk_96.u = 2U;
            delta_x = ((Rec_D_80082E80 *)animation)->unk_24 << 6;
            delta_y = motion->x.w.i;
            delta_y -= 0x20;
            delta_x -= delta_y;
            motion->velocity_x = (s32) ((delta_x << 0x10) / (s16) ((S_800B348C_0 *)action_state)->unk_96.u);
            delta_y = motion->y.w.i - 0x20;
            motion->velocity_y = (s32) ((s32) (((((Rec_D_80082E80 *)animation)->unk_25 << 6) - delta_y)
                << 0x10) / (s16) ((S_800B348C_0 *)action_state)->unk_96.u);
load_state_9b:
bump_state_9b:
            ((S_800B348C_0 *)action_state)->unk_9B = (u8) (((S_800B348C_0 *)action_state)->unk_9B + 1);
            return;
        }
        break;
    }
    case 10:
    {
        DungeonGlobalStatus *end_base;
        s32 end_mask;
        s32 end_timer_state;
        return_delay = ((S_800B348C_0 *)action_state)->unk_96.u - 1;
        ((S_800B348C_0 *)action_state)->unk_96.u = return_delay;
        if (((return_delay << 0x10) <= 0) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)animation)->unk_24, ((Rec_D_80082E80 *)animation)->unk_25);
            {
                void *case10_animation;
                case10_animation = animation;
                (*(u8 **)((u8 *)case10_animation + 0x2C)) = D_800DD0A0;
                set_sprite_animation_frame(case10_animation, D_800DD0A0[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                    >> 9) & 7], 0, 1);
            }
            process_unflagged_linked_entries(actor->next_actor_header);
            end_base = (s32 *)((u32)&g_dungeon_status.turn_scale);
            end_mask = -8;
            end_base->flags = (u16) (end_base->flags | 0x412);
            ((S_800B348C_0 *)action_state)->unk_8C = handle_player_input;
            end_timer_state = D_800DF248[0];
            actor->flags14 &= end_mask;
            if (end_timer_state == 0) {
                end_base->active_actor = 0;
            }
            ((S_800B348C_0 *)action_state)->unk_96.u = 0U;
        }
        break;
    }
    default:
        break;
    }
}
#undef motion
#undef animation
