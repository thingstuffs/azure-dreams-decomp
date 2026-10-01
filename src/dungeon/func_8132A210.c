#include "common.h"

typedef s32 M2C_UNK;
typedef struct
{
    u8 b[32];
}
DungeonTable;
extern u8 D_80171704[];
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern DungeonTable D_8016A894;
extern M2C_UNK D_801718E4;

/* Creates an effect with direction-based position offsets and randomized velocity. */
void func_80171A10(void *source, s16 angle, s32 initial_value, s32 unused, s16 spread_mode)
{
    u16 saved_angle = angle;
    void *effect_obj;
    DungeonTable direction_table = D_8016A894;
    void *y_position;
    void *x_position;
    void *motion;
    void *direction_entry;
    void *y_motion;
    void *effect;
    s32 motion_value;
    s32 y_velocity;
    void *velocity_base;
    u8 *entry;

    effect = func_8003FD64(0x211, source);
    if (effect != 0) {
        *((M2C_UNK **) (((s8 *) effect) + 0x10)) = &D_801718E4;
        entry = (u8 *)&direction_table + ((angle >> 7) & 0x1C);
        *((u16 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 2)) =
            (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) source) + 8)))) + 2)));
        *((u16 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 6)) =
            (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) source) + 8)))) + 6)));
        *((s16 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 0xA)) =
            (s16) ((*((u16 *) (((s8 *) (*((void **) (((s8 *) source) + 8)))) + 0xA))) - 0x14);
        x_position = *((void **) (((s8 *) effect) + 8));
        *((u16 *) (((s8 *) x_position) + 2)) = (u16) ((*((u16 *) (((s8 *) x_position) + 2)))
            + ((*((s16 *) (entry + 0))) * 0x10));
        y_position = *((void **) (((s8 *) effect) + 8));
        *((u16 *) (((s8 *) y_position) + 6)) = (u16) ((*((u16 *) (((s8 *) y_position) + 6)))
            + (((s32) ((*((u16 *) (entry + 2))) << 0x10)) >> 0xC));
        *((s16 *) (((s8 *) (*((void **) (((s8 *) effect) + 0xC)))) + 6)) = 6;
        source = effect + 0x20;
        if (spread_mode == 0) {
            *((s32 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 0xC)) =
                (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 7);
            y_velocity = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 7);
            velocity_base = *((void **) (((s8 *) effect) + 8));
            *((s32 *) (((s8 *) velocity_base) + 0x10)) = y_velocity;
        }
        else {
            *((s32 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 0xC)) =
                (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 6);
            y_velocity = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 6);
            velocity_base = *((void **) (((s8 *) effect) + 8));
            *((s32 *) (((s8 *) velocity_base) + 0x10)) = y_velocity;
        }
        motion_value = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 5);
        direction_entry = (u8 *)&direction_table + ((saved_angle >> 7) & 0x1C);
        motion = (effect_obj = *((void **) (((s8 *) effect) + 8)));
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
        func_8004491C(effect_obj, D_80171704);
        *((s32 *) source) = initial_value;
        *((s32 *) (((s8 *) source) + 8)) = initial_value;
    }
}
