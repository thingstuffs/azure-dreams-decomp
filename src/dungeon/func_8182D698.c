#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
extern s32 D_800814A0[];
extern void func_80025010(void) __attribute__((noreturn));
s32 func_800478B8();
s32 func_80069EF8();

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct {
    void *child;
    u8 pad[0x44];
    u16 count;
    u16 pad4a;
    s16 kind;
} Object;

typedef struct {
    u8 pad[0x0C];
    u8 limit;
    u8 value_d;
    u8 value_e;
    u8 pad_f[5];
    u16 flags;
} Effect;

/* Advance motion with damping and downward acceleration, then count down or fade the effect. */
void func_8182D698(Object *object, Motion *motion, Effect *effect) {
    s16 state;

    ((s32 *)object->child)[3] |= 0x8000;
    {
        s32 y;
        s32 y_velocity;

        {
            register s32 x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 x_velocity;

            x = motion->x;
            x_velocity = motion->dx;
            y = motion->y;
            y_velocity = motion->dy;
            x += x_velocity;
            motion->x = x;
        }
        {
            register s32 z ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 z_velocity;
            volatile s32 *x_velocity_addr = &motion->dx;
            s32 x_drag;
            s32 random_value;
            s32 z_jitter;
            s32 falling_velocity;

            z = motion->z;
            z_velocity = motion->dz;
            y += y_velocity;
            motion->y = y;
            random_value = *x_velocity_addr;
            z += z_velocity;
            x_drag = random_value >> 3;
            motion->z = z;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            {
                register s32 y_velocity_copy ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                y_velocity_copy = y_velocity;
                ASM_KEEP(y_velocity_copy);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                motion->dx = random_value - x_drag;
                motion->dy = y_velocity_copy - (y_velocity_copy >> 3);
            }
            random_value = func_80069EF8(x_drag, y_velocity);
            z_jitter = random_value * 4;
            falling_velocity = motion->dz;
            falling_velocity -= 0x4000;
            motion->dz = falling_velocity - z_jitter;
        }
    }

    state = object->kind;
    if (state == 0) {
        goto countdown;
    }
    if (state == 1) {
        goto fade;
    }
    func_80025010();

countdown: {
        u16 ticks_left = object->count - 1;
        object->count = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            func_8004491C((u8 *)object - 0x20, D_80045340);
            object->kind++;
            func_80025010();
        }
    }
    return;

fade:
        func_800478B8(effect);
        if (effect->flags & 0x6000) {
            effect->pad[4] = 0;
            effect->pad[5] = 0;
        }
        {
            s32 fade_step = (func_80069EF8() & 0xF) + 4;
            if (fade_step >= effect->limit) {
                *(s32 *)((u8 *)effect + 0xC) = 0;
                *((u16 *)((u8 *)object - 2)) |= 0x8000;
                D_800814A0[0] |= 0x8000;
                func_80025010();
            } else {
                u8 fade_value = effect->value_e - fade_step;
                effect->value_e = fade_value;
                effect->value_d = fade_value;
                effect->limit = fade_value;
            }
        }
}
