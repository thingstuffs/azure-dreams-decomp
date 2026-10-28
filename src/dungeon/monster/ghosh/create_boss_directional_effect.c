#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/ghosh.h"
#include "engine/node.h"
#include "sdk/libc.h"

typedef struct
{
    u8 b[32];
}
DungeonTable;
extern u8 ghosh_object_callback_2[];
struct ObjectNodeHeader; void * allocate_list_node(s32, struct ObjectNodeHeader * *);
extern DungeonTable ghosh_effect_direction_vectors;
extern void func_801718E4(u8 *effect, s32 *motion);

/* Creates an effect with direction-based position offsets and randomized velocity. */
/* Creates a directional Ghosh particle with forward-biased velocity and wide or narrow random spread
 * selected by mode. */
void create_boss_directional_effect(void *source, s16 angle, s32 initial_value, s32 unused, s16 spread_mode)
{
    u16 saved_angle = angle;
    void *effect_obj;
    DungeonTable direction_table = ghosh_effect_direction_vectors;
    void *y_position;
    void *x_position;
    void *motion;
    void *direction_entry;
    void *y_motion;
    ObjectNodeHeader *effect;
    s32 motion_value;
    s32 y_velocity;
    void *velocity_base;
    u8 *entry;

    effect = allocate_list_node(0x211, source);
    if (effect != 0) {
        effect->update_callback = &func_801718E4;
        entry = (u8 *)&direction_table + ((angle >> 7) & 0x1C);
        effect->position->x.w.i =
            (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) source) + 8)))) + 2)));
        effect->position->y.w.i =
            (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) source) + 8)))) + 6)));
        effect->position->z.w.i =
            (s16) ((*((u16 *) (((s8 *) (*((void **) (((s8 *) source) + 8)))) + 0xA))) - 0x14);
        x_position = effect->position;
        *((u16 *) (((s8 *) x_position) + 2)) = (u16) ((*((u16 *) (((s8 *) x_position) + 2)))
            + ((*((s16 *) (entry + 0))) * 0x10));
        y_position = effect->position;
        *((u16 *) (((s8 *) y_position) + 6)) = (u16) ((*((u16 *) (((s8 *) y_position) + 6)))
            + (((s32) ((*((u16 *) (entry + 2))) << 0x10)) >> 0xC));
        effect->sprite->depth_bias = 6;
        source = ((void *)effect) + 0x20;
        if (spread_mode == 0) {
            effect->position->velocity_x =
                (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
            y_velocity = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
            velocity_base = effect->position;
            *((s32 *) (((s8 *) velocity_base) + 0x10)) = y_velocity;
        }
        else {
            effect->position->velocity_x =
                (s32) (((rand() & 0x7FFF) - 0x4000) << 6);
            y_velocity = (s32) (((rand() & 0x7FFF) - 0x4000) << 6);
            velocity_base = effect->position;
            *((s32 *) (((s8 *) velocity_base) + 0x10)) = y_velocity;
        }
        motion_value = (s32) (((rand() & 0x7FFF) - 0x4000) << 5);
        direction_entry = (u8 *)&direction_table + ((saved_angle >> 7) & 0x1C);
        motion = (effect_obj = effect->position);
        *((s32 *) (((s8 *) motion) + 0x14)) = motion_value;
        effect_obj = effect;

        motion = *((void **) (((s8 *) effect_obj) + 8));
        *((s32 *) (((s8 *) motion) + 0xC)) = (s32) ((*((s32 *) (((s8 *) motion) + 0xC)))
            + ((*((s16 *) (((s8 *) direction_entry) + 0))) * 0x160000));
        y_motion = *((void **) (((s8 *) effect_obj) + 8));
        *((s32 *) (((s8 *) y_motion) + 0x10)) = (s32) ((*((s32 *) (((s8 *) y_motion) + 0x10)))
            + (((s16) (*((u16 *) (((s8 *) direction_entry) + 2)))) * 0x160000));
        *((u16 *) (((s8 *) source) + 0x14)) = saved_angle;
        *((s16 *) (((s8 *) source) + 0x32)) = 7;
        *((s16 *) (((s8 *) source) + 0x34)) = 7;
        register_node(effect_obj, ghosh_object_callback_2);
        *((s32 *) source) = initial_value;
        *((s32 *) (((s8 *) source) + 8)) = initial_value;
    }
}
