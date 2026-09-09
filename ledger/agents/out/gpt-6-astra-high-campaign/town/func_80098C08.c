#include "common.h"

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
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 x_delta;
    register s32 abs_delta ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 offset_limit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    probe_pos.x = input_pos->x;
    probe_pos.y = input_pos->y;
    probe_pos.z = input_pos->z;
    initial_result = func_8008CA20(&probe_pos, D_800D0410[0], 6);
    {
        s32 *globals_page = (s32 *)0x80100000;
        ASM_KEEP(globals_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        x_delta = globals_page[-0x68D];
    }
    offset_limit = 0x140000;
    abs_delta = x_delta;
    if (x_delta < 0) {
        abs_delta = -abs_delta;
    }
    if (abs_delta <= offset_limit) {
        result = initial_result;
    } else {
        probe_pos.x = input_pos->x - (x_delta / 2);
        result = func_8008CA20(&probe_pos, D_800D0410[0], 6, x_delta);
        if (result >= initial_result) {
            result = initial_result;
        }
    }
    return result;
}
