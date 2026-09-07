#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_8008CABC();
extern M2C_UNK *D_800D0414;
extern s32 D_800FE5CC;

s16 func_80096440(s32 *arg0)
{
    s32 local[6];
    s32 first_result;
    M2C_UNK **map_slot;
    s32 *base;
    s32 second_result;
    s32 delta;
    u32 magnitude;
    u32 bias;
    s32 limit;

    map_slot = &D_800D0414;
    base = arg0;
    local[0] = base[0];
    local[1] = base[1];
    local[2] = base[2];
    first_result = func_8008CABC(local, *map_slot, 6);
    delta = D_800FE5CC;
    limit = 0x140000;
    bias = (u32)limit;
    magnitude = (u32)delta;
    magnitude += bias;
    magnitude -= bias;
    if (delta < 0) {
        magnitude = (u32)limit - (magnitude + (u32)limit);
    }
    if ((s32)magnitude <= limit) {
        return (s16)first_result;
    }

    local[0] = base[0] - (delta / 2);
    second_result = func_8008CABC(local, *map_slot, 6, delta);
    if ((s16)first_result < (s16)second_result) {
        return (s16)second_result;
    }
    return (s16)first_result;
}
