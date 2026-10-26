#include "shared/audio_commands.h"
#include "dungeon/monster/cyclone.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
extern int abs(int);
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef struct S_80172FC0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
    s32 unk_A4;
    u8 pad_A8[0x4];
    s16 unk_AC;
    union { u16 u; s16 s; } unk_AE;   /* accessed as both */
    u8 pad_B0[0x2];
    u16 unk_B2;
    s32 unk_B4;
    u16 unk_B8;
    u16 unk_BA;
} S_80172FC0_0;   /* arg0 in update_shrinking_fading_effect */

typedef struct S_80172FC0_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172FC0_3;   /* owner in update_shrinking_fading_effect */

typedef struct S_80172FC0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FC0_5;   /* arg1_s4 in update_shrinking_fading_effect */

typedef struct S_80172FC0_6 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172FC0_6;   /* selected_model in update_shrinking_fading_effect */

extern s32 resolve_record_orientation_or_fallback(s32, void *, u16 *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_actor_linked_effect(void *);
extern void *create_directional_render_object(void *, void *, void *);

extern s32 D_800814A0;

extern u8 cyclone_move_direction_frames[];
extern u8 cyclone_fade_direction_frames[];
extern u8 cyclone_view_direction_entries[];

/* Updates an actor effect through shrinking, fading, and restoring its sprite. */
/* Starts the selected spell, shrinks and swaps the sprite, fades it out, then restores its appearance and
 * movement. */
void update_shrinking_fading_effect(void *anim, void *transform_arg, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 offset[3];
    s32 is_special;
    u8 *effect_id;
    u8 state;
    u16 timer;
    void *main_actor;
    void *child;

    state = ((S_80172FC0_0 *)anim)->unk_9B;
    is_special = 0;
    switch (state) {
    case 0:
        if (((u32)actor->flags1C) & ACTOR_PLAYER_SIDE) {
            s32 effect_kind;

            effect_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (effect_kind) {
            case 7:
                is_special = 1;
            case 3:
                effect_id = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
            case 2:
                effect_id = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
            case 1:
                effect_id = (u8 *)actor + 8;
                break;
            default:
                effect_id = 0;
                break;
            }
        } else {
            s32 effect_kind;

            effect_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (effect_kind) {
            case 3:
                effect_id = (u8 *)actor + 0xE;
                break;
            case 2:
                effect_id = (u8 *)actor + 0xB;
                break;
            case 1:
                effect_id = (u8 *)actor + 8;
                break;
            default:
                effect_id = 0;
                break;
            }
        }
        if (*effect_id != 0) {
            void *effect;

            ((S_80172FC0_0 *)anim)->unk_98 &= 0xFF7F;
            if ((s16)is_special != 0) {
                effect = primary_actor_record;
                actor->target = effect;
                main_actor = ((ObjectNodeHeader *)((u8 *)effect - 0x20))->sprite;
                actor->target_tile_x = ((S_80172FC0_3 *)main_actor)->unk_24;
                actor->target_tile_y = ((S_80172FC0_3 *)main_actor)->unk_25;
            } else if (item_action_definitions[*effect_id].kind == 2) {
                effect = actor->target;
                if (effect != 0) {
                    main_actor = ((ObjectNodeHeader *)((u8 *)effect - 0x20))->sprite;
                    actor->target_tile_x = ((S_80172FC0_3 *)main_actor)->unk_24;
                    actor->target_tile_y = ((S_80172FC0_3 *)main_actor)->unk_25;
                }
            } else {
                actor->target = scan_actor_along_heading(
                    actor,
                    sprite->tile_x,
                    sprite->tile_y,
                    actor->facing,
                    0x10);
                actor->target_tile_x =
                    abs(actor->target_tile_x);
                actor->target_tile_y =
                    abs(actor->target_tile_y);
            }
            if (create_actor_spell_effect(actor, effect_id, is_special, (u8 *)anim + 0x98) == 0) {
                return;
            }
            create_actor_linked_effect(actor);
            {
                u8 next_state;

                next_state = ((S_80172FC0_0 *)anim)->unk_9B;
                next_state++;
                ((S_80172FC0_0 *)anim)->unk_9B = next_state;
                return;
            }
        }

        ((S_80172FC0_5 *)transform_arg)->unk_14 = 0;
        ((S_80172FC0_5 *)transform_arg)->unk_10 = 0;
        ((S_80172FC0_5 *)transform_arg)->unk_0C = 0;
        set_record_integer_tile_center(transform_arg, sprite->tile_x, sprite->tile_y);
        main_actor = primary_actor_record;
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)main_actor + 0xA6))--;
        advance_status_timers(actor);
        actor->pending_turn_updates--;
        ((S_80172FC0_0 *)anim)->unk_8C = update_actor_animation;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_80172FC0_0 *)anim)->unk_AE.u = 8;
        ((S_80172FC0_0 *)anim)->unk_9B++;

    case 2:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer > 0) {
            u16 scale;

            scale = sprite->scale_y - 0x100;
            sprite->scale_y = scale;
            sprite->scale_x = scale;
            return;
        }

        ((S_80172FC0_0 *)anim)->unk_A0 = create_directional_render_object(anim, transform_arg, sprite);
        {
            s32 direction;
            u8 frame;
            void *model_root;
            void *model;
            void *model_table;
            void *selected_model;

            {
                s32 model_direction;
                s32 view_angle;
                s32 actor_angle;

                view_angle = g_game_work.view.camera_rotation.parts.viewAngle;
                actor_angle = actor->facing;
                model_root = *(void **)&sprite->animation_resource;
                model_direction =
                    ((view_angle + actor_angle + 0x100) >> 9) & 7;
                model = *(void **)model_root;
                model_table = *(void **)model;
                selected_model =
                    ((void **)model_table)[cyclone_view_direction_entries[model_direction]];
            }
            {
                s32 model_data;

                sprite->unk_00 = selected_model;
                model_data = ((S_80172FC0_6 *)selected_model)->unk_04;
                {

                    sprite->source = model_data;
                    offset[2] = 0;
                    offset[1] = 0;
                    offset[0] = 0;
                    if (resolve_record_orientation_or_fallback(
                            *(s32 *)&sprite->source, sprite, offset, 0) != 0) {
                        u16 height_offset;

                        ((S_80172FC0_5 *)transform_arg)->unk_02 += offset[0];
                        ((S_80172FC0_5 *)transform_arg)->unk_06 += offset[1];
                        height_offset = offset[2];
                        ((S_80172FC0_0 *)anim)->unk_B2 = height_offset;
                        ((S_80172FC0_0 *)anim)->unk_90.at02.v =
                            ((S_80172FC0_5 *)transform_arg)->unk_0A - ((u16)actor->ground_height) +
                            (s16)height_offset / 2;
                    }
                }
            }
            ((S_80172FC0_0 *)anim)->unk_98 |= 8;
            actor->flags1C &= ACTOR_REFRESH_GROUND_CLEAR_MASK;
            sprite->frameTable = cyclone_fade_direction_frames;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
            frame = cyclone_fade_direction_frames[direction];
            select_sprite_entry(sprite, frame, 0);
            sprite->scale_y = 0x800;
            sprite->scale_x = 0x800;
        }
        {
            u8 next_state;

            next_state = ((S_80172FC0_0 *)anim)->unk_9B;
            timer = 8;
            ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
            next_state++;
            ((S_80172FC0_0 *)anim)->unk_9B = next_state;
            return;
        }

    case 3:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer >= 0) {
            u16 scale;

            scale = sprite->scale_y + 0x100;
            sprite->scale_y = scale;
            sprite->scale_x = scale;
            ((S_80172FC0_0 *)anim)->unk_90.at02.v += (s16)((S_80172FC0_0 *)anim)->unk_B2 >> 4;
            return;
        }
        ((S_80172FC0_0 *)anim)->unk_AE.u = 4;
        ((S_80172FC0_0 *)anim)->unk_98 |= 0x80;
        ((S_80172FC0_0 *)anim)->unk_9B++;
        return;

    case 4:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer >= 0) {
            return;
        }
        timer = 9;
        ((S_80172FC0_0 *)anim)->unk_B4 = sprite->color.word;
        ((S_80172FC0_0 *)anim)->unk_BA = sprite->tpage_abr;
        ((S_80172FC0_0 *)anim)->unk_B8 = sprite->clut;
        sprite->clut -= 0x80;
        {
            u8 next_state;

            next_state = ((S_80172FC0_0 *)anim)->unk_9B;
            ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
            next_state++;
            ((S_80172FC0_0 *)anim)->unk_9B = next_state;
            return;
        }

    case 5:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer <= 0) {
            return;
        }
        actor->flags1C |= 0x10000000;
        sprite->flags |= 0xC;
        sprite->tpage_abr |= 0x20;
        sprite->color.c.r -= sprite->color.c.r / (s16)((S_80172FC0_0 *)anim)->unk_AE.u;
        sprite->color.c.g -= sprite->color.c.g / (s16)((S_80172FC0_0 *)anim)->unk_AE.u;
        sprite->color.c.b -= sprite->color.c.b / (s16)((S_80172FC0_0 *)anim)->unk_AE.u;
        if (((S_80172FC0_0 *)anim)->unk_AE.s != 1) {
            return;
        }
        {
            u8 next_state;

            next_state = ((S_80172FC0_0 *)anim)->unk_9B;
            timer = 8;
            ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
            next_state++;
            ((S_80172FC0_0 *)anim)->unk_9B = next_state;
            return;
        }

    case 6:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer > 0 && !(sprite->flags & 0x8000)) {
            return;
        }
        child = ((S_80172FC0_0 *)anim)->unk_A0;
        if (child != 0) {
            ObjectNodeHeader *active_child;
            s32 pool_flags;
            s32 new_pool_flags;
            u32 child_flags;

            pool_flags = D_800814A0;
            ((S_80172FC0_0 *)anim)->unk_AC = 0;
            ((S_80172FC0_0 *)anim)->unk_A4 = 0;
            ((S_80172FC0_0 *)anim)->unk_90.at00.v = 0;
            active_child = ((S_80172FC0_0 *)anim)->unk_A0;
            child_flags = ~active_child->flags;
            child_flags &= 0x7FFF;
            child_flags = ~child_flags;
            new_pool_flags = pool_flags | 0x8000;
            D_800814A0 = new_pool_flags;
            active_child->flags = child_flags;
            ((S_80172FC0_0 *)anim)->unk_A0 = 0;
        }
        actor->flags1C &= 0xEFFFFFFF;
        sprite->clut = ((S_80172FC0_0 *)anim)->unk_B8;
        sprite->color.word = ((S_80172FC0_0 *)anim)->unk_B4;
        sprite->tpage_abr = ((S_80172FC0_0 *)anim)->unk_BA;
        ((S_80172FC0_5 *)transform_arg)->unk_14 = 0;
        ((S_80172FC0_5 *)transform_arg)->unk_10 = 0;
        ((S_80172FC0_5 *)transform_arg)->unk_0C = 0;
        set_record_integer_tile_center(transform_arg, sprite->tile_x, sprite->tile_y);
        ((S_80172FC0_0 *)anim)->unk_98 &= 0xFFF7;
        actor->flags1C |= ACTOR_REFRESH_GROUND;
        if (sprite->frameTable != cyclone_move_direction_frames) {
            s32 direction;

            (sprite->frameTable) = cyclone_move_direction_frames;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, cyclone_move_direction_frames[direction], 0);
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((S_80172FC0_0 *)anim)->unk_8C = update_actor_animation;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        advance_status_timers(actor);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->pending_turn_updates--;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
    default:
        return;
    }
}
