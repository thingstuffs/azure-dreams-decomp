#include "common.h"
#include "shared/dir_step.h"
#include "shared/dungeon_floor.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern u8 D_80170F74[];
extern EntityCallback D_80173D90[];

extern void func_8004491C(void *, void *);
extern void select_indirect_table_entry(void *, u8, s8);
extern void func_800478B8(void *);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s32 sample_terrain_surface_height(s32, s32, s16);

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

#ifndef __mips__
static const u32 D_80F0928C[]
__attribute__((section(".text.update_entity_callbacks_and_floor"))) = {
    0x3C028008,
    0x94423462,
};
#endif

/* Update entity callbacks, appearance, movement, and floor contact. */
void update_entity_callbacks_and_floor(void *entity_state, void *entity_motion, void *entity_part)
{
    void *state_alias = entity_state;
    u16 part_flags;
    u16 fade_frame;
    u8 *direction_frames;
    s32 sample_height;
    s16 base_height;
    s32 view_direction;
    s32 state_flags;

    if (g_dungeon_status.flags & 0x2000) {
        EntityCallback early_callback;

        early_callback = ((CallbackActorState *)entity_state)->callback;
        if (early_callback == (EntityCallback)D_80170F74) {
            early_callback(entity_state, entity_motion, entity_part, entity_state);
        } else {
            ((CallbackActorState *)entity_state)->status &= 0x7F;
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

            call_state = entity_state;
            call_motion = entity_motion;
            call_part = entity_part;
            old_mode = (s8)((CallbackActorState *)entity_state)->action_count.value;
            call_context = entity_state;
            if (refresh_actor_facing_and_lifecycle(call_state, call_motion, call_part, call_context) != 0) {
                return;
            }
        }

        callback = ((CallbackActorState *)entity_state)->callback;
        if (callback != 0) {
            callback(entity_state, entity_motion, entity_part, entity_state);
        }
        D_80173D90[((CallbackActorState *)entity_state)->handler_index](entity_state, entity_motion, entity_part, entity_state);

        if ((s16)old_mode != ((CallbackActorState *)entity_state)->action_count.signed_value) {
            try_move_actor_to_valid_position(entity_state, entity_motion, entity_part, entity_state);
        }

        if ((D_800E296C & 4) && (((CallbackActorState *)entity_state)->fade_frame.signed_value < 0)) {
            if (((CallbackActorState *)entity_state)->fade_state != 0) {
                ((CallbackActorState *)entity_state)->fade_frame.signed_value = 0;
                ((CallbackActorState *)entity_state)->fade_state = 0;
                ((CallbackActorSprite *)entity_part)->color = 0;
                func_8004491C((u8 *)entity_state - 0x20, func_80045340);
            }
        }

        if (((CallbackActorState *)entity_state)->fade_frame.signed_value >= 0) {
            ((CallbackActorSprite *)entity_part)->color += 0x101010;
            fade_frame = ((CallbackActorState *)entity_state)->fade_frame.value;
            ((CallbackActorState *)entity_state)->fade_frame.signed_value = fade_frame + 1;
            if ((s16)fade_frame >= 9) {
                ((CallbackActorSprite *)entity_part)->color = 0x808080;
                ((CallbackActorSprite *)entity_part)->flags &= 0xFFF3;
                ((CallbackActorSprite *)entity_part)->color_offset += 0x80;
                ((CallbackActorState *)entity_state)->fade_frame.signed_value = -1;
            }
        }

        part_flags = ((CallbackActorSprite *)entity_part)->flags;
        if (!(part_flags & 0x8000)) {
            view_direction = (g_game_work.view.viewAngle + ((CallbackActorState *)state_alias)->facing + 0x100) >> 9;
            direction = view_direction & 7;
            if (((CallbackActorState *)entity_state)->sprite_direction != direction) {
                direction_frames = ((CallbackActorSprite *)entity_part)->direction_frames;
                if (direction_frames != 0) {
                    select_indirect_table_entry(entity_part, direction_frames[direction], ((CallbackActorSprite *)entity_part)->frame);
                }
                ((CallbackActorState *)entity_state)->sprite_direction = direction;
            }

            direction_enabled = dir_sprite_flag[direction];
            if (direction_enabled != 0) {
                ((CallbackActorSprite *)entity_part)->flags |= 1;
            } else {
                ((CallbackActorSprite *)entity_part)->flags &= 0xFFFE;
            }

            if (!(((CallbackActorState *)state_alias)->flags & 0x20)) {
                if (!(((CallbackActorSprite *)entity_part)->flags & 0x40)) {
                    func_800478B8(entity_part);
                }
            } else {
                ((CallbackActorSprite *)entity_part)->flags |= 0x7000;
            }
            apply_monster_koyaw_data(((CallbackActorState *)state_alias)->flags, &((CallbackActorSprite *)entity_part)->color);
        } else {
            if (part_flags & 0x800) {
                ((CallbackActorSprite *)entity_part)->flags = part_flags & 0x8FFF;
            } else {
                ((CallbackActorSprite *)entity_part)->flags = part_flags | 0x7000;
            }
        }

        ((CallbackActorMotion *)entity_motion)->x.value += ((CallbackActorMotion *)entity_motion)->velocity_x;
        ((CallbackActorMotion *)entity_motion)->y.value += ((CallbackActorMotion *)entity_motion)->velocity_y;

        if (((CallbackActorState *)entity_state)->action_flags & 8) {
            ((CallbackActorState *)entity_state)->fall_ticks.signed_value = 0;
        } else {
            ((CallbackActorMotion *)entity_motion)->velocity_z += ((CallbackActorState *)entity_state)->fall_ticks.signed_value * 0x14000;
            ((CallbackActorState *)entity_state)->fall_ticks.value++;
        }

        ((CallbackActorState *)entity_state)->height_offset.value += ((CallbackActorMotion *)entity_motion)->velocity_z;
        if (!(((CallbackActorState *)entity_state)->action_flags & 4)) {
            sample_height = sample_terrain_surface_height(((CallbackActorMotion *)entity_motion)->x.halves.integer, ((CallbackActorMotion *)entity_motion)->y.halves.integer,
                                          (s16)(((CallbackActorState *)state_alias)->floor_height - 0x20));
            if ((s16)sample_height < 0x200) {
                base_height = ((CallbackActorState *)state_alias)->floor_height;
                if ((((CallbackActorState *)entity_state)->height_offset.signed_halves.integer + base_height) < (s16)sample_height) {
                    ((CallbackActorState *)state_alias)->flags &= 0xF7FFFFFF;
                } else {
                    if ((s16)sample_height >= base_height) {
                        ((CallbackActorState *)entity_state)->height_offset.value = 0;
                        ((CallbackActorMotion *)entity_motion)->velocity_z = 0;
                        ((CallbackActorState *)state_alias)->flags |= 0x08000000;
                        ((CallbackActorState *)entity_state)->fall_ticks.signed_value = 0;
                    } else {
                        ((CallbackActorMotion *)entity_motion)->velocity_z = 0;
                        ((CallbackActorState *)state_alias)->flags |= 0x08000000;
                        ((CallbackActorState *)entity_state)->fall_ticks.signed_value = 0;
                        ((CallbackActorState *)entity_state)->height_offset.signed_halves.integer = (s16)sample_height - ((CallbackActorState *)state_alias)->floor_height;
                    }
                }
                state_flags = ((CallbackActorState *)state_alias)->flags;
                if (state_flags & 0x40000000) {
                    ((CallbackActorState *)state_alias)->flags = state_flags & 0xBFFFFFFF;
                    sample_height = sample_terrain_surface_height((((CallbackActorSprite *)entity_part)->tile_x << 6) | 0x20,
                                                 (((CallbackActorSprite *)entity_part)->tile_y << 6) | 0x20,
                                                 (s16)(((CallbackActorState *)state_alias)->floor_height - 0x20));
                    ((CallbackActorState *)entity_state)->height_offset.signed_halves.integer += ((CallbackActorState *)state_alias)->floor_height - sample_height;
                    ((CallbackActorState *)state_alias)->floor_height = sample_height;
                }
                ((CallbackActorMotion *)entity_motion)->z.signed_halves.integer = ((CallbackActorState *)state_alias)->floor_height + ((CallbackActorState *)entity_state)->height_offset.unsigned_halves.integer;
                ((CallbackActorSprite *)entity_part)->flags |= 0x40;
                return;
            }
        }
        ((CallbackActorState *)state_alias)->flags &= 0xF7FFFFFF;

        ((CallbackActorMotion *)entity_motion)->z.signed_halves.integer = ((CallbackActorState *)state_alias)->floor_height + ((CallbackActorState *)entity_state)->height_offset.unsigned_halves.integer;
        ((CallbackActorSprite *)entity_part)->flags |= 0x40;
    }

    return;
}
