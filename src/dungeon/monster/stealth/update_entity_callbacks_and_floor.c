#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/dungeon_floor.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "engine/node.h"

typedef void (*EntityCallback)(void *, void *, void *, void *);

#include "dungeon/monster/stealth.h"
#include "dungeon/item.h"
#include "engine/texture.h"

extern EntityCallback stealth_callbacks[];

extern void advance_sprite_animation_and_textures(void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

/* Local views retain the signed and packed accesses used by this actor update. */
typedef union {
    s32 value;
    struct { u16 fraction; u16 integer; } halves;
} MotionCoordinate;

typedef struct {
    u8 pad_00[0x1C];
    s32 flags;
    u8 pad_20[0xA];
    s16 facing;
    u8 pad_2C[0x41];
    union { s8 signed_value; u8 value; } action_count;
    u8 pad_6E[3];
    u8 status;
    u8 pad_72[0x16];
    u16 floor_height;
    u8 pad_8A[2];
    EntityCallback callback;
    union {
        s32 value;
        struct { u16 fraction; s16 integer; } signed_halves;
        struct { u16 fraction; u16 integer; } unsigned_halves;
    } height_offset;
    s16 sprite_direction;
    u8 pad_96[2];
    u16 action_flags;
    u8 handler_index;
    u8 pad_9B[2];
    union { s8 signed_value; u8 value; } fall_ticks;
    u8 pad_9E[6];
    union { s16 signed_value; u16 value; } fade_frame;
    s16 fade_state;
} CallbackActorState;

typedef struct {
    MotionCoordinate x;
    MotionCoordinate y;
    union {
        MotionCoordinate coordinate;
        struct { u16 fraction; s16 integer; } signed_halves;
    } z;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
} CallbackActorMotion;

typedef struct {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[7];
    s32 color;
    u8 pad_10[2];
    u16 color_offset;
    u16 flags;
    u8 pad_16[0xE];
    u8 tile_x;
    u8 tile_y;
    u8 pad_26[6];
    u8 *direction_frames;
} CallbackActorSprite;

/* Update entity callbacks, appearance, movement, and floor contact. */
void update_entity_callbacks_and_floor(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    CallbackActorState *state_alias = (CallbackActorState *)body;
    u16 part_flags;
    u16 fade_frame;
    u8 *direction_frames;
    s32 sample_height;
    s16 base_height;
    s32 view_direction;
    s32 state_flags;

    if (g_dungeon_status.flags & 0x2000) {
        EntityCallback early_callback;

        early_callback = body->unk_8C.run;
        if (early_callback == (EntityCallback)stealth_behavior_entry) {
            early_callback(body, motion, sprite, body);
        } else {
            body->movement_queue_state &= 0x7F;
        }
        return;
    }

    {
        EntityCallback callback;
        s16 old_mode;
        s16 direction;
        u8 direction_enabled;

        {
            void *call_state;
            void *call_motion;
            void *call_part;
            void *call_context;

            call_state = body;
            call_motion = motion;
            call_part = sprite;
            old_mode = (s8)body->pending_turn_updates;
            call_context = body;
            if (refresh_actor_facing_and_lifecycle(call_state, call_motion, call_part, call_context) != 0) {
                return;
            }
        }

        callback = body->unk_8C.run;
        if (callback != 0) {
            callback(body, motion, sprite, body);
        }
        stealth_callbacks[body->action_id.u](body, motion, sprite, body);

        if ((s16)old_mode != body->pending_turn_updates) {
            try_move_actor_to_valid_position(body, motion, sprite, body);
        }

        if ((dungeon_floor_flags & 4) && (body->unk_A4.halves.low.s < 0)) {
            if (body->unk_A4.halves.high.s != 0) {
                body->unk_A4.halves.low.s = 0;
                body->unk_A4.halves.high.s = 0;
                sprite->color.word = 0;
                register_node((ObjectNodeHeader *)body - 1, project_sprite_chain);
            }
        }

        if (body->unk_A4.halves.low.s >= 0) {
            sprite->color.word += 0x101010;
            fade_frame = body->unk_A4.halves.low.u;
            body->unk_A4.halves.low.s = fade_frame + 1;
            if ((s16)fade_frame >= 9) {
                sprite->color.word = 0x808080;
                sprite->flags &= 0xFFF3;
                sprite->clut += 0x80;
                body->unk_A4.halves.low.s = -1;
            }
        }

        part_flags = sprite->flags;
        if (!(part_flags & 0x8000)) {
            view_direction = (g_game_work.view.camera_rotation.parts.viewAngle + state_alias->facing + 0x100) >> 9;
            direction = view_direction & 7;
            if (body->unk_94 != direction) {
                direction_frames = *(u8 **)&sprite->frameTable;
                if (direction_frames != 0) {
                    select_indirect_table_entry(sprite, direction_frames[direction], sprite->unk_04);
                }
                body->unk_94 = direction;
            }

            direction_enabled = dir_sprite_flag[direction];
            if (direction_enabled != 0) {
                sprite->flags |= 1;
            } else {
                sprite->flags &= 0xFFFE;
            }

            if (!(state_alias->flags & 0x20)) {
                if (!(sprite->flags & 0x40)) {
                    advance_sprite_animation_and_textures(sprite);
                }
            } else {
                sprite->flags |= 0x7000;
            }
            apply_monster_koyaw_data(state_alias->flags, &sprite->color.word);
        } else {
            if (part_flags & 0x800) {
                sprite->flags = part_flags & 0x8FFF;
            } else {
                sprite->flags = part_flags | 0x7000;
            }
        }

        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;

        if (body->action_state_flags & 8) {
            body->unk_9D.s = 0;
        } else {
            motion->velocity_z += body->unk_9D.s * 0x14000;
            body->unk_9D.u++;
        }

        body->unk_90.value += motion->velocity_z;
        if (!(body->action_state_flags & 4)) {
            sample_height = sample_terrain_surface_height(((CallbackActorMotion *)motion)->x.halves.integer, ((CallbackActorMotion *)motion)->y.halves.integer,
                                          (s16)(state_alias->floor_height - 0x20));
            if ((s16)sample_height < 0x200) {
                base_height = state_alias->floor_height;
                if ((body->unk_90.parts.high.s + base_height) < (s16)sample_height) {
                    state_alias->flags &= 0xF7FFFFFF;
                } else {
                    if ((s16)sample_height >= base_height) {
                        body->unk_90.value = 0;
                        motion->velocity_z = 0;
                        state_alias->flags |= 0x08000000;
                        body->unk_9D.s = 0;
                    } else {
                        motion->velocity_z = 0;
                        state_alias->flags |= 0x08000000;
                        body->unk_9D.s = 0;
                        body->unk_90.parts.high.s = (s16)sample_height - state_alias->floor_height;
                    }
                }
                state_flags = state_alias->flags;
                if (state_flags & 0x40000000) {
                    state_alias->flags = state_flags & 0xBFFFFFFF;
                    sample_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                                                 (sprite->tile_y << 6) | 0x20,
                                                 (s16)(state_alias->floor_height - 0x20));
                    body->unk_90.parts.high.s += state_alias->floor_height - sample_height;
                    state_alias->floor_height = sample_height;
                }
                motion->z.w.i = state_alias->floor_height + body->unk_90.parts.high.u;
                sprite->flags |= 0x40;
                return;
            }
        }
        state_alias->flags &= 0xF7FFFFFF;

        motion->z.w.i = state_alias->floor_height + body->unk_90.parts.high.u;
        sprite->flags |= 0x40;
    }

    return;
}
