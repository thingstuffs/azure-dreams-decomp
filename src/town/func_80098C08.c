#include "common.h"
extern int abs(int);

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} Vec3s32;

extern s16 func_8008CA20();
extern void *D_800D0410[3];
extern s32 D_800FE5CC[3];

/* Return the lower probe result, sampling an X offset when the displacement exceeds the limit. */
s32 func_80096368(Vec3s32 *input_pos) {
    Vec3s32 probe_pos;
    s16 initial_result;
    s32 result;
    s32 x_delta;

    probe_pos.x = input_pos->x;
    probe_pos.y = input_pos->y;
    probe_pos.z = input_pos->z;
    initial_result = func_8008CA20(&probe_pos, D_800D0410[0], 6);
    x_delta = D_800FE5CC[0];
    if (abs(x_delta) <= 0x140000) {
        return initial_result;
    }
    probe_pos.x = input_pos->x - (x_delta / 2);
    result = func_8008CA20(&probe_pos, D_800D0410[0], 6, x_delta);
    if (result < initial_result) {
        return result;
    }
    return initial_result;
}
