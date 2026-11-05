#include "shared/actor_property_flags.h"
#include "common.h"
#include "dungeon/monster/cyclone.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "dungeon/system.h"




extern void select_sprite_entry(void *, s16, s16);


extern void *create_source_to_owner_sprite(void *, void *, void *);
extern s32 consume_object_code_19(void *);
extern void show_entity_message(s32, void *);
extern void show_entity_message_with_prefix(s32, void *);
extern void func_801763CC(s32, void *);

extern u8 cyclone_move_direction_frames[8];

/* Advances the timed target interaction and updates the directional animation. */
void advance_target_interaction(ActorRecord *action, ObjectPosition *scene, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 sprite_flags;
    u16 timer;
    ActorRecord *target;

    switch (action->action_phase.u) {
    case 0:
        sprite_flags = sprite->flags;
        if (sprite_flags & 0x8000) {
            sprite->flags = sprite_flags | 0x6000;
            if (actor->flags14 & ACTOR_PARTY_MEMBER) {
                target = actor->target;
                if (consume_object_code_19(target)) {
                    func_801763CC(1, actor->target);
                } else {
                    func_801763CC(0, actor->target);
                }
            } else {
                target = actor->target;
                if (target->flags14 & 0x4000) {
                    if (request_random_slot_effect(target)) {
                        show_entity_message_with_prefix(1, actor->target);
                    } else {
                        show_entity_message_with_prefix(0, actor->target);
                    }
                } else {
                    request_random_slot_effect(target);
                }
            }
            action->action_phase.u = 2;
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

        create_source_to_owner_sprite(action, scene, sprite);
        if (actor->flags14 & ACTOR_PARTY_MEMBER) {
            show_entity_message(1, actor);
        } else if (((ActorRecord *)(actor->target))->flags14 & 0x4000) {
            show_entity_message(0, actor);
        }
        play_sound_if_enabled(0x708);
        timer = 0x20;
        action->action_timer.u = timer;
        action->action_phase.u++;
        break;

    case 1:
        timer = action->action_timer.u - 1;
        action->action_timer.u = timer;
        if ((timer << 16) == 0 || (sprite->flags & 0x8000)) {
            if (actor->flags14 & ACTOR_PARTY_MEMBER) {
                target = actor->target;
                if (consume_object_code_19(target)) {
                    func_801763CC(1, actor->target);
                } else {
                    func_801763CC(0, actor->target);
                }
            } else {
                target = actor->target;
                if (target->flags14 & 0x4000) {
                    if (request_random_slot_effect(target)) {
                        show_entity_message_with_prefix(1, actor->target);
                    } else {
                        show_entity_message_with_prefix(0, actor->target);
                    }
                } else {
                    request_random_slot_effect(target);
                }
            }
            action->action_timer.u = 4;
            action->action_phase.u++;
        }
        break;

    case 2:
        timer = action->action_timer.u - 1;
        action->action_timer.u = timer;
        if ((timer << 16) == 0 || (sprite->flags & 0xE000)) {
            spend_actor_mp(actor, 0x400);
            set_record_integer_tile_center(scene, sprite->tile_x, sprite->tile_y);
            action->unk_8C.address = update_actor_animation;
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
        action->action_state_flags &= 0xFFF7;
    }
}
