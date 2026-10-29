#include "shared/entity.h"
#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
struct S_80170E18_3;

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0xA6];
    u16 field_A6;
} D800814A8FieldView_81252D6C;

extern int abs(int);

extern s32 select_sprite_entry();
extern void set_record_integer_tile_center();
extern void play_sound_if_enabled();
extern void create_effect_from_sprite_and_facing(void *unused, MovingPosition *source_transform, void *sprite_template, struct S_80170E18_3 *facing_source);

void update_object_animation(ActorRecord *obj, ObjectPosition *motion, SpriteFrameState *part, ActorRecord *state);
extern u8 beldo_frame_set_1[8];
extern u8 D_80173EDC[8];

typedef struct S_8017256C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_8017256C_0;   /* arg0 in advance_actor_action_and_target */

typedef struct S_8017256C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { void * p; u8 * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_8017256C_1;   /* arg3 in advance_actor_action_and_target */

typedef struct S_8017256C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017256C_3;   /* src in advance_actor_action_and_target */

typedef struct S_8017256C_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017256C_5;   /* arg1 in advance_actor_action_and_target */

/* Advances an actor's action state, updating its target, animation, and completion. */
/* Starts a targeted Beldo spell, emits a sprite effect during its casting sequence, then recenters and
 * updates status. */
void advance_actor_action_and_target(void *action, void *motion, SpriteFrameState *sprite, void *actor)
{
    register s32 is_special = 0;
    u8 *action_entry;
    u32 state;
    u32 prior_state;
    s32 kind;
    u32 kind_index;
    u16 ticks;
    s32 next_ticks;
    u8 *target_link;

    state = ((S_8017256C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((S_8017256C_1 *)actor)->unk_1C & ACTOR_PLAYER_SIDE) {
            kind_index = ((S_8017256C_1 *)actor)->unk_46 & 0x3FFF;
            switch (kind_index) {
            case 7:
                is_special = 1;
                /* fallthrough */
            case 3:
                action_entry = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fallthrough */
            case 2:
                action_entry = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fallthrough */
            case 1:
                action_entry = (u8 *)actor + 8;
                break;
            default:
                action_entry = 0;
                break;
            }
        } else {
            kind = ((S_8017256C_1 *)actor)->unk_46 & 0x3FFF;
            switch (kind) {
            case 3:
                action_entry = (u8 *)actor + 0xE;
                break;
            case 2:
                action_entry = (u8 *)actor + 0xB;
                break;
            case 1:
                action_entry = (u8 *)actor + 8;
                break;
            default:
                action_entry = 0;
                break;
            }
        }
        if (*action_entry != 0) {
            ((S_8017256C_0 *)action)->unk_98 &= 0xFF7F;
            {
                u8 use_player_target = is_special;

                if (use_player_target) {
                    target_link = primary_actor_record;
                    ((S_8017256C_1 *)actor)->unk_60.p = target_link;
                    kind = (s32)*(u8 * *)&((ObjectNodeHeader *)((u8 *)target_link - 0x20))->sprite;

                    ((S_8017256C_1 *)actor)->unk_72.u = ((S_8017256C_3 *)kind)->unk_24;
                    ((S_8017256C_1 *)actor)->unk_73.u = ((S_8017256C_3 *)kind)->unk_25;
                } else if (item_action_definitions[*action_entry].kind == 2) {
                    target_link = ((S_8017256C_1 *)actor)->unk_60.p2;
                    if (target_link != 0) {
                        kind = (s32)*(u8 * *)&((ObjectNodeHeader *)((u8 *)target_link - 0x20))->sprite;

                        ((S_8017256C_1 *)actor)->unk_72.u = ((S_8017256C_3 *)kind)->unk_24;
                        ((S_8017256C_1 *)actor)->unk_73.u = ((S_8017256C_3 *)kind)->unk_25;
                    }
                } else {
                    s32 x;
                    s32 abs_x;
                    s32 abs_y;
                    s32 y;

                    ((S_8017256C_1 *)actor)->unk_60.p = scan_actor_along_heading(
                        actor,
                        sprite->tile_x,
                        sprite->tile_y,
                        ((S_8017256C_1 *)actor)->unk_2A,
                        0x10);
                    abs_x = abs(((S_8017256C_1 *)actor)->unk_72.s);
                    abs_y = abs(((S_8017256C_1 *)actor)->unk_73.s);
                    ((S_8017256C_1 *)actor)->unk_72.u = abs_x;
                    ((S_8017256C_1 *)actor)->unk_73.u = abs_y;
                }
            }
            if (create_actor_spell_effect(actor, action_entry, is_special, (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_8017256C_0 *)action)->unk_96 = 0;
            ((S_8017256C_0 *)action)->unk_9B++;
            ((S_8017256C_5 *)motion)->unk_14 = 0;
            ((S_8017256C_5 *)motion)->unk_10 = 0;
            ((S_8017256C_5 *)motion)->unk_0C = 0;
            return;
        }
        ((S_8017256C_5 *)motion)->unk_14 = 0;
        ((S_8017256C_5 *)motion)->unk_10 = 0;
        ((S_8017256C_5 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        ((D800814A8FieldView_81252D6C *)primary_actor_record)->field_A6--;
        advance_status_timers(actor);
        ((S_8017256C_1 *)actor)->unk_6D--;
        ((S_8017256C_0 *)action)->unk_8C = &update_object_animation;
        ((S_8017256C_1 *)actor)->unk_73.u = 0;
        ((S_8017256C_1 *)actor)->unk_72.u = 0;
        ((S_8017256C_1 *)actor)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_8017256C_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
        ticks = ((S_8017256C_0 *)action)->unk_96;
        next_ticks = ticks + 1;
        ((S_8017256C_0 *)action)->unk_96 = next_ticks;
        if ((s16)ticks < 8 && !(sprite->flags & 0x8000)) {
            return;
        }
        prior_state = ((S_8017256C_0 *)action)->unk_9B;

        ((S_8017256C_0 *)action)->unk_96 = 0;
        ((S_8017256C_0 *)action)->unk_9B = prior_state + 1;
        return;

    case 3:
        if (((S_8017256C_0 *)action)->unk_A2 != 0) {
            ticks = ((S_8017256C_0 *)action)->unk_96;
            next_ticks = ticks + 1;
            ((S_8017256C_0 *)action)->unk_96 = next_ticks;
            if ((s16)ticks < 15 && !(sprite->flags & 0x8000)) {
                return;
            }
        }
        ((S_8017256C_0 *)action)->unk_96 = 0;
        ((S_8017256C_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);
        (sprite->frameTable) = D_80173EDC;
        select_sprite_entry(
            sprite,
            D_80173EDC[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017256C_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;

    case 4:
        create_effect_from_sprite_and_facing(action, motion, sprite, actor);
        ticks = ((S_8017256C_0 *)action)->unk_96;
        next_ticks = ticks + 1;
        ((S_8017256C_0 *)action)->unk_96 = next_ticks;
        if ((s16)ticks < 3 && !(sprite->flags & 0xE000)) {
            return;
        }
        sprite->flags |= 0x800;
        prior_state = ((S_8017256C_0 *)action)->unk_9B;
        ((S_8017256C_0 *)action)->unk_9B = prior_state + 1;
        return;

    case 5:
        sprite->flags |= 0x800;
        ticks = ((S_8017256C_0 *)action)->unk_96;
        next_ticks = ticks + 1;
        ((S_8017256C_0 *)action)->unk_96 = next_ticks;
        if ((s16)ticks < 10 && !(sprite->flags & 0x8000)) {
            return;
        }
        ((S_8017256C_0 *)action)->unk_96 = 0;
        ((S_8017256C_0 *)action)->unk_9B++;
        sprite->flags &= 0xF7FF;
        return;

    case 6:
        ((S_8017256C_0 *)action)->unk_98 |= 0x80;
        ((S_8017256C_0 *)action)->unk_96 = 0;
        ((S_8017256C_0 *)action)->unk_9B++;
        return;

    case 7:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        ((S_8017256C_5 *)motion)->unk_14 = 0;
        ((S_8017256C_5 *)motion)->unk_10 = 0;
        ((S_8017256C_5 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        ((S_8017256C_0 *)action)->unk_9B++;
        if (*(u8 **)&sprite->frameTable == beldo_frame_set_1) {
            return;
        }
        (sprite->frameTable) = beldo_frame_set_1;
        select_sprite_entry(
            sprite,
            beldo_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017256C_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_8017256C_0 *)action)->unk_9E = 0;
        ((S_8017256C_0 *)action)->unk_92 = -0x20;
        return;

    case 8:
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((S_8017256C_0 *)action)->unk_8C = &update_object_animation;
            advance_status_timers(actor);
            ((S_8017256C_1 *)actor)->unk_6D--;
            ((S_8017256C_1 *)actor)->unk_73.u = 0;
            ((S_8017256C_1 *)actor)->unk_72.u = 0;
            ((S_8017256C_1 *)actor)->unk_46 &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }
        return;
    default:
        return;
    }
}
