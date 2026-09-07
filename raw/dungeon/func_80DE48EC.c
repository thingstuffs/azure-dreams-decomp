#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s32 func_80047784();
extern s32 func_8009B4B0();
extern s32 func_800A2B5C();
extern s32 func_800A44E0();
extern s32 func_800A4ACC();
extern s32 func_800A5690();
extern s16 func_800BCB04();
extern s32 func_800C77D0();
extern s32 func_800C7930();
extern void func_80172338(void) __attribute__((noreturn));

extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174558[];

s32 func_801720EC(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    struct local_state {
        void *saved_ptr;
        volatile u8 pad[20];
    } state;
    register s32 result ASM_REG("$23") = 0;
    register void *entity ASM_REG("$17") = arg3;
    u16 flags;
    s32 direction;
    register u16 base_x ASM_REG("$19");
    register u16 base_y ASM_REG("$20");
    register s32 delta_offset ASM_REG("$3");
    s16 x;
    s16 y;
    u16 *y_delta;
    u16 *x_delta;
    u8 *x_base;
    s16 height;

    FIELD(entity, u8, 0x71) &= 0x7f;
    flags = D_80083462;
    if (flags & 0x2000) {
        goto tail;
    }

    if (!(FIELD(entity, u16, 0x46) & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }

    if ((s16)func_800A2B5C(entity) != 0) {
        return -1;
    }

    {
        register void *ptr ASM_REG("$8");
        ptr = (u8 *)entity - 0x20;
        state.saved_ptr = ptr;
        func_800C7930(ptr, arg1, 8, 0x300);
    }
    if ((s16)func_800A2B5C(entity) == 0) {
        goto body;
    }

tail:
    {
        register s32 tail_result ASM_REG("$2") = -1;
        ASM_TAILSLOT_PIN(tail_result);
        func_80172338();
    }

body:

    base_x = FIELD(arg2, u8, 0x24);
    base_y = FIELD(arg2, u8, 0x25);
    x = base_x;
    y = base_y;
    direction = (FIELD(entity, u16, 0x2a) >> 9) & 7;
    if ((s16)func_800A44E0(x << 6, y << 6, FIELD(entity, s16, 0x88), direction << 9) != 0) {
        return 0;
    }

    ASM_SCHED_BARRIER();
    x_base = (u8 *)&D_8006CCD8;
    ASM_SCHED_BARRIER();
    delta_offset = direction << 1;
    x_delta = (u16 *)(x_base + delta_offset);
    ASM_KEEP_NV(delta_offset);
    y_delta = (u16 *)((u8 *)&D_8006CCE8 + delta_offset);
    {
        register s32 next_x ASM_REG("$5");
        register s32 next_y ASM_REG("$6");
        next_x = *x_delta;
        next_y = *y_delta;
        if (func_8009B4B0(entity, (base_x + next_x) & 0xffff,
                          (base_y + next_y) & 0xffff) != 0) {
            return 0;
        }
    }
    ASM_USE2_NV(base_x, base_y);

    if ((s16)func_800A5690() == 0) {
        return 0;
    }

    height = func_800BCB04((((x + (s16)*x_delta) << 6) + 0x20) & 0xffe0,
                           (((y + (s16)*y_delta) << 6) + 0x20) & 0xffe0,
                           (s16)(FIELD(entity, u16, 0x88) - 0x20));
    if (height >= 0x201) {
        return 0;
    }
    if ((s16)(height - FIELD(entity, u16, 0x88)) >= -0x3f) {
        register void *output ASM_REG("$8") = arg0;
        FIELD(output, volatile s8, 0x9b) = 0;
        FIELD(output, volatile s32, 0x8c) = 0;
        FIELD(output, volatile s8, 0x9a) = 0x17;
        FIELD(arg2, u8 *, 0x2c) = D_80174558;
        func_80047784(arg2,
                      D_80174558[((D_80083228 + FIELD(entity, s16, 0x2a) + 0x100) >> 9) & 7],
                      0);
        func_800A4ACC(entity);
        {
            register s32 call_a2 ASM_REG("$6") = 8;
            register s32 call_a3 ASM_REG("$7") = 0x300;
            register void *call_a0 ASM_REG("$4") = state.saved_ptr;
            ASM_KEEP_NV(call_a2);
            ASM_KEEP_NV(call_a3);
            ASM_KEEP_NV(call_a0);
            FIELD(entity, u8, 0x6d)--;
            func_800C77D0(call_a0, arg1, call_a2, call_a3);
        }
        ASM_USE_NV(result);
        return 1;
    }
    return 0;
}
