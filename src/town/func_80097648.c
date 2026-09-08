#include "common.h"

typedef struct {
    s32 unk0[3];
    s32 x;
    s32 y;
} TownObject;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s16 func_80094BC8(s32, s16);
extern u8 D_80083160[];

/* Reduce object coordinates toward direction-dependent limits without overshooting. */
void func_80094DA8(TownObject *object) {
    u8 *state;
    s16 direction;
    s32 y_direction;
    s32 component_x;
    s32 limit_x;
    register s32 limit_abs_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 current_abs_x;
    s32 current_x;
    s32 step_x;
    register s32 clamp_work_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 clamp_abs_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 component_y;
    s32 limit_y;
    register s32 limit_abs_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 current_abs_y;
    s32 current_y;
    s32 step_y;
    s32 clamp_work_y;
    register s32 clamp_abs_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    state = D_80083160;
    direction = func_80094BC8(*(s32 *)(state + 8), *(s16 *)(state + 0xC8));
    if (direction != -1) {
        component_x = func_800644B8(direction);
        current_abs_x = object->x;
        limit_x = component_x << 7;
        limit_abs_x = limit_x;
        if (limit_x < 0) {
            limit_abs_x = -limit_abs_x;
        }
        if (current_abs_x < 0) {
            current_abs_x = -current_abs_x;
        }
#ifdef __mips__
        if (!(limit_abs_x < current_abs_x)) {
            clamp_work_x = (u32)(u16)direction << 16;
            goto x_done;
        }
#else
        if (limit_abs_x < current_abs_x) {
#endif
            component_x = func_800644B8(direction);
            current_x = object->x;
            step_x = component_x << 6;
            if (((current_x < 0) && (step_x < 0)) ||
                ((current_x > 0) && (step_x > 0))) {
                object->x = object->x - step_x;
            }
            clamp_work_x = object->x;
            clamp_abs_x = limit_x;
            if (limit_x < 0) {
                clamp_abs_x = -clamp_abs_x;
            }
            if (clamp_work_x < 0) {
                clamp_work_x = -clamp_work_x;
            }
            clamp_work_x = clamp_work_x < clamp_abs_x;
#ifdef __mips__
            __asm__ __volatile__(".set\tnoreorder\n\t.set\tnomacro");
            if (!clamp_work_x) {
                goto x_done;
            }
            clamp_work_x = (u32)(u16)direction << 16;
            object->x = limit_x;
            __asm__ __volatile__(".set\tmacro\n\t.set\treorder");
#else
            if (clamp_work_x) {
                object->x = limit_x;
            }
            clamp_work_x = (u32)(u16)direction << 16;
#endif
#ifndef __mips__
        } else {
            clamp_work_x = (u32)(u16)direction << 16;
        }
#else
x_done:
#endif

        y_direction = (s32)clamp_work_x >> 16;
        component_y = func_80064584(y_direction);
        current_abs_y = object->y;
        limit_y = component_y << 7;
        limit_abs_y = limit_y;
        if (limit_y < 0) {
            limit_abs_y = -limit_abs_y;
        }
        if (current_abs_y < 0) {
            current_abs_y = -current_abs_y;
        }
        if (limit_abs_y < current_abs_y) {
            component_y = func_80064584(y_direction);
            current_y = object->y;
            step_y = component_y << 6;
            if (((current_y < 0) && (step_y < 0)) ||
                ((current_y > 0) && (step_y > 0))) {
                object->y = object->y - step_y;
            }
            clamp_work_y = object->y;
            clamp_abs_y = limit_y;
            if (limit_y < 0) {
                clamp_abs_y = -clamp_abs_y;
            }
            if (clamp_work_y < 0) {
                clamp_work_y = -clamp_work_y;
            }
            clamp_work_y = clamp_work_y < clamp_abs_y;
            if (clamp_work_y) {
                object->y = limit_y;
            }
        }
    }
}
