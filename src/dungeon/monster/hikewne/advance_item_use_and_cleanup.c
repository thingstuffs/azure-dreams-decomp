#include "shared/audio_commands.h"
#include "dungeon/monster/hikewne.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "engine/cd.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

extern void select_sprite_entry(void *, s32, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_directional_template_effect(void *, void *, void *, void *);

extern u8 hikewne_direction_frames[];
extern u8 D_80174110[];
extern u8 hikewne_frame_set_17[];

typedef struct S_80172A48_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_80172A48_0;   /* arg0 in advance_item_use_and_cleanup */

   /* the 0x14 bytes before active in advance_item_use_and_cleanup, addressed as active[-1] */

   /* linked in advance_item_use_and_cleanup */

/* Advance item use through effect activation, actor animation, and cleanup. */
/* Starts a targeted spell, waits for loading, emits directional effects, and restores the actor after
 * either sequence. */
void advance_item_use_and_cleanup(void *action, ObjectPosition *motion, SpriteFrameState *actor, void *item)
{
    register u8 *effect_slot;
    s16 is_special;
    s32 effect_special;
    s16 next_state;
    u8 state;
    void *target;
    void *linked;

    is_special = 0;
    state = ((S_80172A48_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)item + 0x1C)) & ACTOR_PLAYER_SIDE) {
            u32 kind_index;

            kind_index = ((*(u16 *)((u8 *)item + 0x46)) & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                is_special = 1;
            case 2:
                effect_slot = (u8 *)item + 0xE;
                break;
            case 5:
                is_special = 1;
            case 1:
                effect_slot = (u8 *)item + 0xB;
                break;
            case 4:
                is_special = 1;
            case 0:
                effect_slot = (u8 *)item + 8;
                break;
            default:
                effect_slot = 0;
                break;
            }
        } else {
            s32 item_kind;

            item_kind = (*(u16 *)((u8 *)item + 0x46)) & 0x3FFF;
            switch (item_kind) {
            case 3:
                effect_slot = (u8 *)item + 0xE;
                break;
            case 2:
                effect_slot = (u8 *)item + 0xB;
                break;
            case 1:
                effect_slot = (u8 *)item + 8;
                break;
            default:
                effect_slot = 0;
                break;
            }
        }

        if (*effect_slot != 0) {
            ((S_80172A48_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 special_target;

                special_target = is_special;
                if (special_target != 0) {
                    target = primary_actor_record;
                    (*(void * *)((u8 *)item + 0x60)) = target;
                    linked = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    (*(u8 *)((u8 *)item + 0x72)) = ((MovingTile *)linked)->tile_x;
                    (*(u8 *)((u8 *)item + 0x73)) = ((MovingTile *)linked)->tile_y;
                } else {
                    u8 effect_id;

                    effect_id = *effect_slot;
                    if (item_action_definitions[effect_id].kind == 2) {
                        target = (*(void **)((u8 *)item + 0x60));
                        if (target != 0) {
                            linked = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                            (*(u8 *)((u8 *)item + 0x72)) = ((MovingTile *)linked)->tile_x;
                            (*(u8 *)((u8 *)item + 0x73)) = ((MovingTile *)linked)->tile_y;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        target = scan_actor_along_heading(
                            item, actor->tile_x, actor->tile_y,
                            (*(s16 *)((u8 *)item + 0x2A)), 0x10);
                        (*(void **)((u8 *)item + 0x60)) = target;
                        dx = abs(*(s8 *)((u8 *)item + 0x72));
                        dy = abs(*(s8 *)((u8 *)item + 0x73));
                        (*(u8 *)((u8 *)item + 0x72)) = dx;
                        (*(u8 *)((u8 *)item + 0x73)) = dy;
                    }
                }
            }

            effect_special = is_special;
            if (create_actor_spell_effect(item, effect_slot, effect_special, (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_80172A48_0 *)action)->unk_96.u = 0;
            ((S_80172A48_0 *)action)->unk_9B++;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if ((u32)(*effect_slot - 0x2E) >= 3) {
                return;
            }
            if (effect_special == 1) {
                return;
            }
            ((S_80172A48_0 *)action)->unk_9B = 0x10;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(item);
        (*(u8 *)((u8 *)item + 0x6D))--;
        ((S_80172A48_0 *)action)->unk_8C = update_actor_behavior_animation_and_facing;
        (*(u8 *)((u8 *)item + 0x73)) = 0;
        (*(u8 *)((u8 *)item + 0x72)) = 0;
        (*(u16 *)((u8 *)item + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            actor->flags |= 0x800;
            return;
        }
        actor->flags &= 0xF7FF;
        ((S_80172A48_0 *)action)->unk_9B++;

    case 2:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 8) {
            if (!(actor->flags & 0x8000)) {
                return;
            }
        }
    }
        next_state = ((S_80172A48_0 *)action)->unk_9B;
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        next_state++;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;

    case 3:
        if (((S_80172A48_0 *)action)->unk_A2 != 0) {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 15) {
                if (!(actor->flags & 0x8000)) {
                    return;
                }
            }
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);
        (actor->frameTable) = D_80174110;
        select_sprite_entry(actor,
            *((u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7) + (u32)D_80174110)),
            0);
        return;

    case 4:
        create_directional_template_effect(action, motion, actor, item);
        {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 3) {
                if (!(actor->flags & 0xE000)) {
                    return;
                }
            }
        }
        actor->flags |= 0x800;
        ((S_80172A48_0 *)action)->unk_9B++;
        return;

    case 5:
        actor->flags |= 0x800;
        {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 10) {
                if (!(actor->flags & 0x8000)) {
                    return;
                }
            }
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        actor->flags &= 0xF7FF;
        return;

    case 6:
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_98 |= 0x80;
        ((S_80172A48_0 *)action)->unk_9B++;
        return;

    case 7:
        if (!(actor->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
        ((S_80172A48_0 *)action)->unk_9B++;
        if (*(u8 **)&actor->frameTable == hikewne_direction_frames) {
            return;
        }
        {
            u8 *model = hikewne_direction_frames;

            (actor->frameTable) = model;
            select_sprite_entry(actor,
                model[((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }
        ((S_80172A48_0 *)action)->unk_9E = 0;
        ((S_80172A48_0 *)action)->unk_92 = -0x20;
        return;

    case 8:
    {

        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        ((S_80172A48_0 *)action)->unk_8C = update_actor_behavior_animation_and_facing;
        advance_status_timers(item);
        (*(u8 *)((u8 *)item + 0x73)) = 0;
        (*(u8 *)((u8 *)item + 0x72)) = 0;
        (*(u8 *)((u8 *)item + 0x6D))--;
        (*(u16 *)((u8 *)item + 0x46)) &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
    }
        return;

    case 16:
        if (get_cd_command_queue_depth()) {
            actor->flags |= 0x800;
            return;
        }
        actor->flags &= 0xF7FF;
        ((S_80172A48_0 *)action)->unk_9B++;

    case 17:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 8 &&
            !(actor->flags & 0x8000)) {
            return;
        }
    }
        next_state = ((S_80172A48_0 *)action)->unk_9B;
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        next_state++;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;

    case 18:
        if (((S_80172A48_0 *)action)->unk_A2 != 0) {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 15 &&
                !(actor->flags & 0x8000)) {
                return;
            }
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);
                    /* MATCH: the preceding eight-byte model table uses a distinct address expression in this arm. */
        (actor->frameTable) = (u8 *)((u32)hikewne_frame_set_17 - 8);
        select_sprite_entry(actor,
            *((u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7)
                + (u32)(u8 *)((u32)hikewne_frame_set_17 - 8))),
            0);
        return;

    case 19:
        create_directional_template_effect(action, motion, actor, item);
        {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 2 &&
                !(actor->flags & 0xE000)) {
                return;
            }
        }
        actor->flags |= 0x800;
        next_state = ((S_80172A48_0 *)action)->unk_9B;
        next_state++;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;

    case 20:
        actor->flags |= 0x800;
        if (((S_80172A48_0 *)action)->unk_96.s < 5) {
            create_directional_template_effect(action, motion, actor, item);
        }
        {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 10 &&
                !(actor->flags & 0x8000)) {
                return;
            }
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        actor->flags &= 0xF7FF;
        ((S_80172A48_0 *)action)->unk_98 |= 0x80;
        return;

    case 21:
        if (!(actor->flags & 0xE000)) {
            return;
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        {

            (actor->frameTable) = hikewne_frame_set_17;
            select_sprite_entry(actor,
                *((u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7)
                    + (u32)hikewne_frame_set_17)),
                0);
        }
        return;

    case 22:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 5) {
            return;
        }
    }
        next_state = ((S_80172A48_0 *)action)->unk_9B;
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        next_state++;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;

    case 23:
        next_state = 6;
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;
    default:
        return;
    }

}
