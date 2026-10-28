#include "shared/audio_commands.h"
#include "dungeon/monster/baloon.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "sdk/libc.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"

extern void select_sprite_entry(void *, s32, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void play_sound_if_enabled(s32);
extern void * create_actor_spell_effect(void *actor, void *record_data, s16 mode, void *context);
extern void spawn_angled_random_velocity_effect(void *, s32, s32);
extern void spawn_directional_random_velocity_effect(void *, s32);

extern u8 baloon_default_frames[];
extern u8 baloon_fall_frames[8];
extern u8 D_800E2398[8];

typedef struct S_80173B08_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
} S_80173B08_0;   /* arg0 in update_actor_item_use */

typedef struct S_80173B08_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173B08_2;   /* linked in update_actor_item_use */

/* Updates the actor's item-use state, animation, and effects. */
/* Starts a targeted spell, settles to ground height, emits forward and surrounding particles, then
 * restores its hover. */
void update_actor_item_use(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
{
    u8 *item_slot;
    u32 stage;
    s32 flag;
    s16 effect_count;
    u32 state;
    void *target;

    flag = 0;
    state = ((S_80173B08_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            u32 kind_index;

            kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                flag = 1;
            case 2:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 5:
                flag = 1;
            case 1:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 4:
                flag = 1;
            case 0:
                item_slot = (u8 *)actor + 8;
                break;
            case 3:
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 action_kind;

            action_kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (action_kind) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((S_80173B08_0 *)action)->unk_98 &= 0xFF7F;
            {
                u8 is_special;
                void *item_id;

                is_special = flag;
                if (is_special != 0) {
                    target = primary_actor_record;
                    (*(void * *)((u8 *)actor + 0x60)) = target;
                    item_id = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173B08_2 *)item_id)->unk_24;
                    (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173B08_2 *)item_id)->unk_25;
                } else {
                    item_id = (void *)(*item_slot);
                    if (item_action_definitions[((u8)item_id)].kind == 2) {
                        target = (*(void * *)((u8 *)actor + 0x60));
                        if (target != 0) {
                            item_id = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                            (*(u8 *)((u8 *)actor + 0x72)) = ((S_80173B08_2 *)item_id)->unk_24;
                            (*(u8 *)((u8 *)actor + 0x73)) = ((S_80173B08_2 *)item_id)->unk_25;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)scan_actor_along_heading(
                            actor, sprite->tile_x, sprite->tile_y,
                            (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                        (*(void * *)((u8 *)actor + 0x60)) = (void *)dx;
                        dx = abs(*(s8 *)((u8 *)actor + 0x72));
                        dy = abs(*(s8 *)((u8 *)actor + 0x73));
                        (*(u8 *)((u8 *)actor + 0x72)) = dx;
                        (*(u8 *)((u8 *)actor + 0x73)) = dy;
                    }
                }
            }

            if (create_actor_spell_effect(actor, item_slot, flag,
                              (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_80173B08_0 *)action)->unk_9B++;
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
            advance_status_timers(actor);
            (*(u8 *)((u8 *)actor + 0x6D))--;
            ((S_80173B08_0 *)action)->unk_8C = update_actor_turn_behavior;
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            return;
        }

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_80173B08_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
        ((S_80173B08_0 *)action)->unk_9B++;
        ((S_80173B08_0 *)action)->unk_98 &= 0xFFF7;
        (*(u32 *)((u8 *)actor + 0x1C)) &= 0xFFFBFFFF;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;

    case 3:
        if (sprite->flags & 0x8000) {
            ((S_80173B08_0 *)action)->unk_9B = 7;
            sprite->flags |= 0x6000;
            ((S_80173B08_0 *)action)->unk_98 |= 0x80;
            return;
        }
        {
            s16 floor_height;

            floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                  ((u16)motion->y.w.i),
                                  (s16)((*(u16 *)((u8 *)actor + 0x88)) - 0x20));
            if ((((S_80173B08_0 *)action)->unk_92.s -
                 (s16)(floor_height - (*(u16 *)((u8 *)actor + 0x88)))) != 0) {
                return;
            }
        }
        ((S_80173B08_0 *)action)->unk_96.u = 0;
        stage = ((S_80173B08_0 *)action)->unk_9B;
        stage++;
        ((S_80173B08_0 *)action)->unk_9B = stage;
        sprite->frameTable = D_800E2398;
        select_sprite_entry(sprite, D_800E2398[((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7], 0);
        return;

    case 4:
    {
        s16 timer;

        timer = ((S_80173B08_0 *)action)->unk_96.u;
        ((S_80173B08_0 *)action)->unk_96.u = timer + 1;
        if (timer < 12 && !(sprite->flags & 0xE000)) {
            return;
        }
    }
        ((S_80173B08_0 *)action)->unk_98 |= 0x80;
        sprite->flags |= 0x800;
        ((S_80173B08_0 *)action)->unk_96.u = 0x12;
        ((S_80173B08_0 *)action)->unk_9B++;
        effect_count = 0;
        do {
            spawn_angled_random_velocity_effect((u8 *)action - 0x20,
                          (*(s16 *)((u8 *)actor + 0x2A)), 0xE0E0E0);
            effect_count++;
        } while ((s16)effect_count < 3);
        return;

    case 5:
        if ((g_dungeon_status.active_actor) == 0) {
            ((S_80173B08_0 *)action)->unk_96.u = 0;
        }
        if (((S_80173B08_0 *)action)->unk_96.s >= 10) {
            effect_count = 0;
            do {
                spawn_angled_random_velocity_effect((u8 *)action - 0x20,
                              (*(s16 *)((u8 *)actor + 0x2A)), 0xE0E0E0);
                effect_count++;
            } while ((s16)effect_count < 3);
        }
        if ((u32)(((S_80173B08_0 *)action)->unk_96.u - 10) < 7) {
            s16 angle;

            for (angle = 0; angle < 0x1000; angle += 0x200) {
                if (angle != (*(s16 *)((u8 *)actor + 0x2A))) {
                    effect_count = 0;
                    do {
                        spawn_directional_random_velocity_effect((u8 *)action - 0x20, angle);
                        effect_count++;
                    } while ((s16)effect_count <= 0);
                }
            }
        }
        {
            s16 timer;

            timer = ((S_80173B08_0 *)action)->unk_96.u - 1;
            ((S_80173B08_0 *)action)->unk_96.u = timer;
            if (timer > 0 && !(sprite->flags & 0xE000)) {
                return;
            }
        }
        ((S_80173B08_0 *)action)->unk_96.u = 0;
        sprite->flags &= 0xF7FF;
        state = ((S_80173B08_0 *)action)->unk_98;
        stage = ((S_80173B08_0 *)action)->unk_9B;
        stage++;
        state |= 8;
        ((S_80173B08_0 *)action)->unk_9B = stage;
        ((S_80173B08_0 *)action)->unk_98 = state;
        sprite->frameTable = baloon_fall_frames;
        select_sprite_entry(sprite, baloon_fall_frames[((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7], 0);
        return;

    case 6:
        if (((S_80173B08_0 *)action)->unk_92.s >= -0x1F) {
            ((S_80173B08_0 *)action)->unk_92.u -= 4;
            return;
        }
        ((S_80173B08_0 *)action)->unk_9B++;

    case 7:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if (*(u8 * *)&sprite->frameTable != baloon_default_frames) {
            sprite->frameTable = baloon_default_frames;
            select_sprite_entry(
                sprite,
                baloon_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
                0);
            ((S_80173B08_0 *)action)->unk_9E = 0;
            ((S_80173B08_0 *)action)->unk_98 |= 8;
            (*(u32 *)((u8 *)actor + 0x1C)) |= 0x40000;
            ((S_80173B08_0 *)action)->unk_92.s = -0x20;
            sprite->flags &= 0xFFF3;
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((S_80173B08_0 *)action)->unk_8C = update_actor_turn_behavior;
            advance_status_timers(actor);
        }
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

        return;
    }
}
