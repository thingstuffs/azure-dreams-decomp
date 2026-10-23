#include "shared/actor_property_flags.h"
#include "common.h"
#include "dungeon/monster/cyclone.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80174764_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80174764_0;   /* arg0 in advance_target_interaction */

typedef struct S_80174764_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80174764_3;   /* target in advance_target_interaction */

typedef struct S_80174764_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80174764_4;   /* ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in advance_target_interaction */

extern void select_sprite_entry(void *, s16, s16);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void spawn_312_effect_object(void *, void *, void *);
extern s32 request_random_slot_effect(void *);
extern s32 check_object_code_19(void *);
extern void format_entity_message(s32, void *);
extern void func_80176330(s32, void *);
extern void func_801763CC(s32, void *);

extern u8 cyclone_action_resume_address;
extern u8 cyclone_move_direction_frames[8];

/* Advances the timed target interaction and updates the directional animation. */
void advance_target_interaction(void *action, void *scene, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 sprite_flags;
    u16 timer;
    void *target;

    switch (((S_80174764_0 *)action)->unk_9B) {
    case 0:
        sprite_flags = sprite->flags;
        if (sprite_flags & 0x8000) {
            sprite->flags = sprite_flags | 0x6000;
            if (actor->flags14 & ACTOR_PARTY_MEMBER) {
                target = actor->target;
                if (check_object_code_19(target)) {
                    func_801763CC(1, actor->target);
                } else {
                    func_801763CC(0, actor->target);
                }
            } else {
                target = actor->target;
                if (((S_80174764_3 *)target)->unk_14 & 0x4000) {
                    if (request_random_slot_effect(target)) {
                        func_80176330(1, actor->target);
                    } else {
                        func_80176330(0, actor->target);
                    }
                } else {
                    request_random_slot_effect(target);
                }
            }
            ((S_80174764_0 *)action)->unk_9B = 2;
            return;
        }

        if (sprite->unk_04 == 1) {
            if (!(sprite_flags & 0x1000)) {
                if (!(sprite_flags & 0x6000)) {
                    break;
                }
            }
        } else if (!(sprite_flags & 0x6000)) {
            break;
        }

        spawn_312_effect_object(action, scene, sprite);
        if (actor->flags14 & ACTOR_PARTY_MEMBER) {
            format_entity_message(1, actor);
        } else if (((S_80174764_4 *)(actor->target))->unk_14 & 0x4000) {
            format_entity_message(0, actor);
        }
        play_sound_if_enabled(0x708);
        timer = 0x20;
        ((S_80174764_0 *)action)->unk_96 = timer;
        ((S_80174764_0 *)action)->unk_9B++;
        break;

    case 1:
        timer = ((S_80174764_0 *)action)->unk_96 - 1;
        ((S_80174764_0 *)action)->unk_96 = timer;
        if ((timer << 16) == 0 || (sprite->flags & 0x8000)) {
            if (actor->flags14 & ACTOR_PARTY_MEMBER) {
                target = actor->target;
                if (check_object_code_19(target)) {
                    func_801763CC(1, actor->target);
                } else {
                    func_801763CC(0, actor->target);
                }
            } else {
                target = actor->target;
                if (((S_80174764_3 *)target)->unk_14 & 0x4000) {
                    if (request_random_slot_effect(target)) {
                        func_80176330(1, actor->target);
                    } else {
                        func_80176330(0, actor->target);
                    }
                } else {
                    request_random_slot_effect(target);
                }
            }
            ((S_80174764_0 *)action)->unk_96 = 4;
            ((S_80174764_0 *)action)->unk_9B++;
        }
        break;

    case 2:
        timer = ((S_80174764_0 *)action)->unk_96 - 1;
        ((S_80174764_0 *)action)->unk_96 = timer;
        if ((timer << 16) == 0 || (sprite->flags & 0xE000)) {
            spend_actor_mp(actor, 0x400);
            set_record_integer_tile_center(scene, sprite->tile_x, sprite->tile_y);
            ((S_80174764_0 *)action)->unk_8C = &cyclone_action_resume_address;
            g_dungeon_status.active_actor = 0;
            (actor->action_flags) &= 0x7FFF;
        }
        break;
    }

    if (sprite->flags & 0xE000) {
        s32 direction;

        sprite->frameTable = cyclone_move_direction_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        select_sprite_entry(sprite, cyclone_move_direction_frames[direction & 7], 0);
        ((S_80174764_0 *)action)->unk_98 &= 0xFFF7;
    }
}
