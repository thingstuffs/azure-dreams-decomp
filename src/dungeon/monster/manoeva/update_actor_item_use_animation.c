#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/monster/manoeva.h"
#include "sdk/libc.h"

typedef __SIZE_TYPE__ uptr;




typedef struct S_801728E4_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801728E4_5;   /* global in update_actor_item_use_animation */

typedef struct {
    u8 pad00[0x12];
    u8 field12;
    u8 field13;
} ItemInfo;

extern u8 manoeva_action_resume_address[8];
extern u8 manoeva_frame_set_1[8];
extern u8 D_80176648[8];
extern u8 manoeva_frame_set_2[8];

extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void create_actor_linked_effect(void *);

/* Advances an actor's item action through source selection, animation, and cleanup. */
void update_actor_item_use_animation(ActorRecord *action, void *item, SpriteFrameState *sprite, ActorRecord *actor)
{
    ActorRecord *act = actor;
    u8 state;
    s32 use_global_source;
    u16 action_flags;
    s32 item_kind;
    SpriteFrameState *target_sprite;
    ObjectNodeHeader *source_sprite;

    state = action->action_phase.u;
    use_global_source = 0;
    switch (state) {
    case 0:
        {
            ObjectNodeHeader *source_entity;

            item = 0;
            if (((u32)act->flags1C) & ACTOR_PLAYER_SIDE) {
                switch (act->action_flags & 0x3FFF) {
                case 7:
                    use_global_source = 1;
                    /* fallthrough */
                case 3:
                    item = (u8 *)act + 0xE;
                    break;
                case 6:
                    use_global_source = 1;
                    /* fallthrough */
                case 2:
                    item = (u8 *)act + 0xB;
                    break;
                case 5:
                    use_global_source = 1;
                    /* fallthrough */
                case 1:
                    item = (u8 *)act + 8;
                    break;
                default:
                    break;
                }
            } else {
                item_kind = act->action_flags & 0x3FFF;
                switch (item_kind) {
                case 3:
                    item = (u8 *)act + 0xE;
                    break;
                case 2:
                    item = (u8 *)act + 0xB;
                    break;
                case 1:
                    item = (u8 *)act + 8;
                    break;
                default:
                    break;
                }
            }
            if ((*(u8 *)&((EntityRec *)item)->x) == 0) {
                return;
            }

            {
                s16 global_source_test;

                action->action_state_flags &= 0xFF7F;
                global_source_test = use_global_source;
                if (global_source_test) {
                    source_entity = (ObjectNodeHeader *)primary_actor_record;
                    act->target = source_entity;
                    target_sprite = (source_entity - 1)->sprite;
                    act->target_tile_x = target_sprite->tile_x;
                    act->target_tile_y = target_sprite->tile_y;
                } else if (item_action_definitions[(*(u8 *)&((EntityRec *)item)->x)].kind == 2) {
                    source_entity = act->target;
                    if (source_entity != 0) {
                        target_sprite = (source_entity - 1)->sprite;
                        act->target_tile_x = target_sprite->tile_x;
                        act->target_tile_y = target_sprite->tile_y;
                    }
                } else {
                    act->target =
                        scan_actor_along_heading(act,
                                      sprite->tile_x,
                                      sprite->tile_y,
                                      act->facing,
                                      0x10);
                    act->target_tile_x = abs(act->target_tile_x);
                    act->target_tile_y = abs(act->target_tile_y);
                }
            }
        }

        if (!create_actor_spell_effect(act, item, use_global_source, ((u8 *)action + 0x98))) {
            return;
        }
        create_actor_linked_effect(act);
        action->action_phase.u++;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x0800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->action_phase.u++;

    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        (sprite->frameTable) = D_80176648;
        select_sprite_entry(sprite,
            *(u8 *)((uptr)(((g_game_work.view.camera_rotation.parts.viewAngle + act->facing + 0x100) >> 9) & 7) +
                    (uptr)D_80176648),
            0);
        action->action_phase.u++;
        return;

    case 3:
        if (sprite->unk_04 == 6 && (sprite->flags & 0x1000)) {
            action->action_state_flags |= 0x80;
        } else if (sprite->flags & 0xE000) {
            action->action_state_flags |= 0x80;
        }
        if (!(action->action_state_flags & 0x80)) {
            return;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }

        (sprite->frameTable) = manoeva_frame_set_2;
        select_sprite_entry(sprite,
            *(u8 *)((uptr)(((g_game_work.view.camera_rotation.parts.viewAngle + act->facing + 0x100) >> 9) & 7) +
                    (uptr)manoeva_frame_set_2),
            0);
        action->action_phase.u++;
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            (sprite->frameTable) = manoeva_frame_set_1;
            select_sprite_entry(sprite,
                manoeva_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + act->facing + 0x100) >> 9) & 7],
                0);
        }
        ((EntityRec *)item)->flags14 = 0;
        ((EntityRec *)item)->unk_10 = 0;
        ((EntityRec *)item)->unk_0C = 0;
        set_record_integer_tile_center(item, sprite->tile_x, sprite->tile_y);
        source_sprite = ((u8 *)(&g_dungeon_status));
        if (source_sprite->sprite != 0) {
            return;
        }
        ((S_801728E4_5 *)source_sprite)->unk_0A--;
        action->unk_8C.byte_ptr = manoeva_action_resume_address;
        advance_status_timers(act);
        act->target_tile_y = 0;
        act->target_tile_x = 0;
        act->pending_turn_updates = (u8)act->pending_turn_updates - 1;
        act->action_flags &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    default:
        return;
    }
}
