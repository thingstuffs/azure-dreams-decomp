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

void func_8182D698(Object *arg0, Motion *arg1, Effect *arg2) {
    s16 state;

    ((s32 *)arg0->child)[3] |= 0x8000;
    {
        s32 y;
        s32 dy;

        {
            register s32 x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            s32 dx0;

            x = arg1->x;
            dx0 = arg1->dx;
            y = arg1->y;
            dy = arg1->dy;
            x += dx0;
            arg1->x = x;
        }
        {
            register s32 z ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            s32 dz;
            s32 dx;
            volatile s32 *dx_addr = &arg1->dx;
            s32 dx_step;
            s32 random;
            s32 scaled;
            s32 tail;

            z = arg1->z;
            dz = arg1->dz;
            y += dy;
            arg1->y = y;
            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
            dx = *dx_addr;
            z += dz;
            dx_step = dx >> 3;
            arg1->z = z;
            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
            {
                register s32 dy_copy ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

                dy_copy = dy;
                ASM_KEEP(dy_copy);   /* MATCH pin: keeps a statement from moving across a call/branch */
                arg1->dx = dx - dx_step;
                arg1->dy = dy_copy - (dy_copy >> 3);
            }
            random = func_80069EF8(dx_step, dy);
            scaled = random * 4;
            tail = arg1->dz;
            tail -= 0x4000;
            arg1->dz = tail - scaled;
        }
    }

    state = arg0->kind;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    func_80025010();

state_zero: {
        u16 count = arg0->count - 1;
        arg0->count = count;
        if ((count << 0x10) <= 0) {
            func_8004491C((u8 *)arg0 - 0x20, D_80045340);
            arg0->kind++;
            func_80025010();
        }
    }
    return;

state_one:
        func_800478B8(arg2);
        if (arg2->flags & 0x6000) {
            arg2->pad[4] = 0;
            arg2->pad[5] = 0;
        }
        {
            s32 amount = (func_80069EF8() & 0xF) + 4;
            if (amount >= arg2->limit) {
                *(s32 *)((u8 *)arg2 + 0xC) = 0;
                *((u16 *)((u8 *)arg0 - 2)) |= 0x8000;
                D_800814A0[0] |= 0x8000;
                func_80025010();
            } else {
                u8 value = arg2->value_e - amount;
                arg2->value_e = value;
                arg2->value_d = value;
                arg2->limit = value;
            }
        }
}
