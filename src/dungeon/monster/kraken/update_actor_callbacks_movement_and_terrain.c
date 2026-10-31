#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

#include "shared/entity.h"
#include "shared/dungeon_trail_views.h"
#include "engine/texture.h"
#include "dungeon/actor.h"
#include "dungeon/level.h"
#include "dungeon/item.h"


void advance_sprite_animation_and_textures(void *entity);
s32 refresh_actor_facing_and_lifecycle();
void update_actor_animation_and_dispatch(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *status);
extern M2C_UNK D_80174174[];
extern u8 kraken_frame_set_1[];
extern u8 kraken_action_handlers[];


typedef struct S_80170B64_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x1A];
    ActorActionHandler unk_8C;
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x2];
    union { s8 s; u8 u; } unk_9D;   /* accessed as both */
    u8 pad_9E[0x2];
    union { u16 u; s16 s; } unk_A0;   /* accessed as both */
    u8 pad_A2[0x6];
    s16 unk_A8;
    u8 pad_AA[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_AC;   /* overlapping accesses */
} S_80170B64_0;   /* arg0 in update_actor_callbacks_movement_and_terrain */

   /* arg1 in update_actor_callbacks_movement_and_terrain */

typedef struct S_80170B64_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { void * p; s32 i; } unk_2C;   /* accessed as both */
} S_80170B64_2;   /* arg2 in update_actor_callbacks_movement_and_terrain */

typedef struct S_80170B64_3 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170B64_3;   /* work in update_actor_callbacks_movement_and_terrain */

/* Update actor callbacks, movement, sprite direction, and terrain-relative height. */
void update_actor_callbacks_movement_and_terrain(ActorRecord *body, ObjectPosition *motion, void *sprite_arg)
{
    S_80170B64_3 *actor_base = (S_80170B64_3 *)body;
    ActorActionHandler update_callback;
    ActorActionHandler pause_callback;
    s16 floor_offset;
    s16 view_direction;
    s16 tile_height;
    s32 hover_floor_offset;
    s32 animated_flags;
    s32 animation_table;
    s32 static_flags;
    s32 static_animation_table;
    s32 actor_flags;
    s16 previous_state;
    u16 sprite_flags;

    if (g_dungeon_status.flags & 0x2000) {
        void *paused_actor = body;
        pause_callback = body->unk_8C.handler;
        if (pause_callback == &update_actor_animation_and_dispatch) {
            pause_callback(paused_actor, motion, sprite_arg, paused_actor);
            return;
        }
        body->movement_queue_state &= 0x7F;
        return;
    }


    previous_state = (s8)((S_80170B64_0 *)body)->unk_6D;
    if (refresh_actor_facing_and_lifecycle(body, motion, sprite_arg, body) == 0) {
        update_callback = body->unk_8C.handler;
        if (update_callback != 0) {
            update_callback(body, motion, sprite_arg, body);
        }
        ((s32 (**)(void *, void *, void *, void *))&kraken_action_handlers)
        [body->action_id.u](body, motion, sprite_arg, body);
        if ((s16)previous_state != (s8)((S_80170B64_0 *)body)->unk_6D) {
            try_move_actor_to_valid_position(body, motion, sprite_arg, body);
        }
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        if (!(body->flags1C & 0x40000) &&
            !(body->action_state_flags & 8)) {
            motion->velocity_z = motion->velocity_z +
                (body->unk_9D.s * 0x14000);
            body->unk_9D.u++;
        } else {
            body->unk_9D.s = 0;
        }

        body->unk_90.value = body->unk_90.value +
            motion->velocity_z;
        sprite_flags = ((S_80170B64_2 *)sprite_arg)->unk_14;
        if (!(sprite_flags & 0x8000)) {
            view_direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A + 0x100) >> 9) & 7;
            if (body->unk_94 != view_direction) {
                select_indirect_table_entry(sprite_arg,
                    *(((u8 *)((S_80170B64_2 *)sprite_arg)->unk_2C.p) + view_direction),
                    ((S_80170B64_2 *)sprite_arg)->unk_04.s8);
                body->unk_94 = view_direction;
            }
            if (dir_sprite_flag[view_direction] != 0) {
                ((S_80170B64_2 *)sprite_arg)->unk_14 |= 1;
            } else {
                ((S_80170B64_2 *)sprite_arg)->unk_14 &= 0xFFFE;
            }
            apply_monster_koyaw_data(actor_base->unk_1C.s, sprite_arg + 0xC);
            if (!(actor_base->unk_1C.s & 0x20)) {
                if (!(((S_80170B64_2 *)sprite_arg)->unk_14 & 0x40)) {
                    advance_sprite_animation_and_textures(sprite_arg);
                }
            } else {
                ((S_80170B64_2 *)sprite_arg)->unk_14 |= 0x7000;
                actor_base->unk_1C.s &= 0xFFFBFFFF;
            }
            animated_flags = actor_base->unk_1C.s & 0xF7FFFFFF;
            actor_base->unk_1C.s = animated_flags;
            if (animated_flags & 0x40000) {
                if (!(((S_80170B64_2 *)sprite_arg)->unk_14 & 0x40)) {
                    animation_table = ((S_80170B64_2 *)sprite_arg)->unk_2C.i;
                    if (animation_table == (s32)&kraken_frame_set_1) {
                        ((S_80170B64_0 *)body)->unk_AC.at00.v = 0;
                    } else if (animation_table == (s32)&D_80174174) {
                        body->unk_A0.parts.low++;
                        if (((S_80170B64_2 *)sprite_arg)->unk_04.u16 == 0x100) {
                            body->unk_A0.parts.low = 0;
                            ((S_80170B64_0 *)body)->unk_AC.at00.v = 0;
                        }
                        if (((S_80170B64_0 *)body)->unk_A0.s < 5) {
                            ((S_80170B64_0 *)body)->unk_AC.at00.v += -0x33333;
                        } else {
                            ((S_80170B64_0 *)body)->unk_AC.at00.v += 0x12492;
                        }
                    }
                }
                if (!(body->action_state_flags & 8)) {
                    hover_floor_offset = sample_terrain_surface_height(((TrailMotion *)motion)->x.unk_02.unk_02,
                        ((TrailMotion *)motion)->y.unk_06.unk_06,
                        (s16)(actor_base->unk_88 - 0x20)) -
                        actor_base->unk_88;
                    if (body->unk_90.parts.high.s > ((s16)hover_floor_offset - 0x20)) {
                        body->unk_90.parts.high.s =
                            body->unk_90.parts.high.u - 8;
                    } else if (body->unk_90.parts.high.s <
                               ((s16)hover_floor_offset - 0x28)) {
                        body->unk_90.parts.high.s =
                            body->unk_90.parts.high.u + 8;
                    }
                }
            } else {
                s32 height_adjustment = ((S_80170B64_0 *)body)->unk_AC.at00.v;
                body->unk_A8.s = 0;
                ((S_80170B64_0 *)body)->unk_AC.at00.v = 0;
                body->unk_90.value -= height_adjustment;
                if (!(body->action_state_flags & 8)) {
                    floor_offset = sample_terrain_surface_height(((TrailMotion *)motion)->x.unk_02.unk_02,
                        ((TrailMotion *)motion)->y.unk_06.unk_06,
                        (s16)(actor_base->unk_88 - 0x20)) -
                        actor_base->unk_88;
                    if (floor_offset < body->unk_90.parts.high.s) {
                        body->unk_90.parts.high.s = floor_offset;
                        body->unk_9D.s = 0;
                        motion->velocity_z = 0;
                        actor_base->unk_1C.u |= 0x08000000;
                    }
                }
            }
        } else {
            if (sprite_flags & 0x800) {
                ((S_80170B64_2 *)sprite_arg)->unk_14 = sprite_flags & 0x8FFF;
            } else {
                ((S_80170B64_2 *)sprite_arg)->unk_14 = sprite_flags | 0x7000;
            }
            static_flags = actor_base->unk_1C.s & 0xF7FFFFFF;
            actor_base->unk_1C.s = static_flags;
            if (!(static_flags & 0x40000)) {

                s32 height_adjustment = ((S_80170B64_0 *)body)->unk_AC.at00.v;
                body->unk_A8.s = 0;
                ((S_80170B64_0 *)body)->unk_AC.at00.v = 0;
                body->unk_90.value -= height_adjustment;
                if (!(body->action_state_flags & 8)) {
                    floor_offset = sample_terrain_surface_height(((TrailMotion *)motion)->x.unk_02.unk_02,
                        ((TrailMotion *)motion)->y.unk_06.unk_06,
                        (s16)(actor_base->unk_88 - 0x20)) -
                        actor_base->unk_88;
                    if (floor_offset < body->unk_90.parts.high.s) {
                        body->unk_90.parts.high.s = floor_offset;
                        body->unk_9D.s = 0;
                        motion->velocity_z = 0;
                        actor_base->unk_1C.u |= 0x08000000;
                    }
                }
            } else {
                if (!(((S_80170B64_2 *)sprite_arg)->unk_14 & 0x40)) {
                    static_animation_table = ((S_80170B64_2 *)sprite_arg)->unk_2C.i;
                    if (static_animation_table == (s32)&kraken_frame_set_1) {
                        ((S_80170B64_0 *)body)->unk_AC.at00.v = 0;
                    } else if (static_animation_table == (s32)&D_80174174) {
                        body->unk_A0.parts.low++;
                        if (((S_80170B64_2 *)sprite_arg)->unk_04.u16 == 0x100) {
                            body->unk_A0.parts.low = 0;
                            ((S_80170B64_0 *)body)->unk_AC.at00.v = 0;
                        }
                        if (((S_80170B64_0 *)body)->unk_A0.s < 5) {
                            ((S_80170B64_0 *)body)->unk_AC.at00.v += -0x33333;
                        } else {
                            ((S_80170B64_0 *)body)->unk_AC.at00.v += 0x12492;
                        }
                    }
                }
                if (!(body->action_state_flags & 8)) {
                    hover_floor_offset = sample_terrain_surface_height(((TrailMotion *)motion)->x.unk_02.unk_02,
                        ((TrailMotion *)motion)->y.unk_06.unk_06,
                        (s16)(actor_base->unk_88 - 0x20)) -
                        actor_base->unk_88;
                    if (body->unk_90.parts.high.s > ((s16)hover_floor_offset - 0x20)) {
                        body->unk_90.parts.high.s =
                            body->unk_90.parts.high.u - 8;
                    } else if (body->unk_90.parts.high.s < ((s16)hover_floor_offset - 0x28)) {
                        body->unk_90.parts.high.s =
                            body->unk_90.parts.high.u + 8;
                    }
                }
            }
        }
        actor_flags = actor_base->unk_1C.s;
        if (actor_flags & 0x40000000) {
            actor_base->unk_1C.s = actor_flags & 0xBFFFFFFF;
            tile_height = sample_terrain_surface_height(
                (((S_80170B64_2 *)sprite_arg)->unk_24 << 6) | 0x20,
                (((S_80170B64_2 *)sprite_arg)->unk_25 << 6) | 0x20,
                (s16)(actor_base->unk_88 - 0x20));
            if (tile_height < 0x200) {
                body->unk_90.parts.high.s = (u16)body->unk_90.parts.high.s +
                    (actor_base->unk_88 - tile_height);
                actor_base->unk_88 = tile_height;
            }
        }
        motion->z.w.i = body->unk_AC.halves.high.u +
            (actor_base->unk_88 + (u16)body->unk_90.parts.high.s);
        ((S_80170B64_2 *)sprite_arg)->unk_14 |= 0x40;
    }

}
