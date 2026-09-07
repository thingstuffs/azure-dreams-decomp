#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct Packed32 {
    u8 bytes[0x20];
} __attribute__((packed)) Packed32;

extern void func_800A7A7C(s16, s16, s16, void *, void *);
extern s16 func_800A45D8(u16, u16, s16);
extern s16 func_800BCB04(s32, s32, s16);
extern s16 func_800A7234(s8, s8, s16, void *, void *, void *);
extern s32 D_800814A0[3];

extern void func_8014CBD8(void) __attribute__((noreturn));
extern void func_8014CD98(void) __attribute__((noreturn));
extern void func_8014CEB8(void) __attribute__((noreturn));
extern void func_8014CA0C(void) __attribute__((noreturn));
#ifdef __mips__
__asm__(".set func_8014CBD8, 0x8014CBD8");
__asm__(".set func_8014CD98, 0x8014CD98");
__asm__(".set func_8014CEB8, 0x8014CEB8");
__asm__(".set func_8014CA0C, 0x8014CA0C");
#endif

extern void *D_8014C828[];
extern Packed32 D_8014C808;
#ifdef __mips__
__asm__(".set D_8014C828, 0x8014C828");
__asm__(".set D_8014C808, 0x8014C808");

static const u32 split_prefix[] __asm__("func_8014C800")
    __attribute__((section(".text.func_8014C800"), aligned(4))) = {
    0x8014D718, 0x8014D8E0,
    0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
    0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001,
    0x8014C9E8, 0x8014C9F0, 0x8014C9F8, 0x8014CA00,
    0x8014CA08, 0x00000000,
    0x8014E0CC, 0x8014E0CC, 0x8014E0CC, 0x8014E0F8,
    0x8014E078, 0x8014E078, 0x8014E078, 0x8014E024,
    0x8014E05C, 0x8014E0F8, 0x8014E0F8, 0x8014E0BC,
    0x8014F55C, 0x8014F5E8, 0x8014F62C, 0x8014F68C,
    0x8014F750, 0x00000000,
    0x8014F810, 0x8014FA48, 0x8014FA90, 0x8014FBE4,
    0x8014FBF8, 0x00000000,
    0x8014F8C0, 0x8014F8B8, 0x8014F8B0, 0x8014F8C8,
    0x8014F86C, 0x8014F864, 0x8014F85C,
};
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 1752");
#define BODY_NAME func_8014C8BC
#else
#define BODY_NAME func_8014C800
#endif

void BODY_NAME(void *arg0, void *arg1, void *arg2)
    __attribute__((section(".text.func_8014C800")));
void BODY_NAME(void *arg0, void *arg1, void *arg2)
{
    s8 color[4];
    Packed32 points;
    s32 old_z;
    s32 old_z2;
    s16 timer;
    u16 switch_value;
    s32 delta_x;
    s32 delta_y;
    s32 raw_y;
    s32 target_y;
    s32 distance;
#ifdef __mips__
    register s32 velocity_y ASM_REG("$2");
    register s32 point_index ASM_REG("$3");
    register s32 point_accel ASM_REG("$4");
    register s32 point_old_x ASM_REG("$3");
    register s32 point_x ASM_REG("$2");
    register s32 grid_x ASM_REG("$4");
    register s32 grid_x_div ASM_REG("$2");
    register s16 point_y ASM_REG("$2");
    register s32 point_old_y ASM_REG("$3");
    register s32 grid_y ASM_REG("$4");
    register s32 grid_y_div ASM_REG("$2");
    register s32 update_index_x ASM_REG("$2");
    register u8 *update_x ASM_REG("$2");
    register u8 *update_y ASM_REG("$4");
#else
    s32 velocity_y;
    s32 point_index;
    s32 point_accel;
    s32 point_old_x;
    s32 point_x;
    s32 grid_x;
    s32 grid_x_div;
    s16 point_y;
    s32 point_old_y;
    s32 grid_y;
    s32 grid_y_div;
    s32 update_index_x;
    u8 *update_x;
    u8 *update_y;
#endif
    s16 *points_base;
    s16 *point;

#ifdef __mips__
    static void *const switch_keep[5] = {
        &&switch_case0, &&switch_case1, &&switch_case2,
        &&switch_case3, &&switch_default
    };
#endif

#ifdef __mips__
    register void *arg2_reg ASM_REG("$19") = arg2;
    ASM_KEEP_NV(arg2_reg);
#define arg2 arg2_reg
#endif

    points = D_8014C808;

state_one:
    if (FIELD(arg0, s16, 0x2C) != 1) {
        goto state_two_check;
    }
    if (FIELD(arg0, s16, 0x2E) != 0) {
        goto countdown;
    }

    FIELD(arg0, s16, 0x2E)++;
    target_y = FIELD(arg0, s8, 0x5D);
    delta_x = FIELD(arg1, s16, 0x0E) - FIELD(arg0, s8, 0x5C);
    raw_y = FIELD(arg1, s16, 0x12);
    if (delta_x < 0) {
        delta_x = -delta_x;
    }
    delta_y = raw_y - target_y;
    if (delta_y < 0) {
        delta_y = -delta_y;
    }
    distance = delta_x + delta_y;
#ifdef __mips__
    if ((u32)distance < 5U) {
        (void)switch_keep;
        goto *D_8014C828[(u32)distance];
    }
    goto switch_default;
#else
    switch ((u32)distance) {
    case 0:
        goto switch_case0;
    case 1:
        goto switch_case1;
    case 2:
        goto switch_case2;
    case 3:
        goto switch_case3;
    default:
        goto switch_default;
    }
#endif
switch_case0:
#ifdef __mips__
    {
        register s32 call_value ASM_REG("$2") = 4;
        ASM_TAILSLOT_PIN(call_value);
        func_8014CA0C();
    }
#else
    switch_value = 4;
    goto switch_store;
#endif
switch_case1:
#ifdef __mips__
    {
        register s32 call_value ASM_REG("$2") = 8;
        ASM_TAILSLOT_PIN(call_value);
        func_8014CA0C();
    }
#else
    switch_value = 8;
    goto switch_store;
#endif
switch_case2:
#ifdef __mips__
    {
        register s32 call_value ASM_REG("$2") = 12;
        ASM_TAILSLOT_PIN(call_value);
        func_8014CA0C();
    }
#else
    switch_value = 12;
    goto switch_store;
#endif
switch_case3:
#ifdef __mips__
    {
        register s32 call_value ASM_REG("$2") = 14;
        ASM_TAILSLOT_PIN(call_value);
        func_8014CA0C();
    }
#else
    switch_value = 14;
    goto switch_store;
#endif
switch_default:
    switch_value = 16;
switch_store:
    FIELD(arg0, u16, 0x36) = switch_value;
    goto countdown;

countdown:
    timer = FIELD(arg0, s16, 0x36) - 1;
    FIELD(arg0, s16, 0x36) = timer;
    if (timer != 0) {
#ifdef __mips__
        register s32 step_x ASM_REG("$3");
        register s32 next_x ASM_REG("$2");
#else
        s32 step_x;
        s32 next_x;
#endif
        s32 target_x;
        s32 target_y_step;
        step_x = FIELD(arg1, s16, 0x0E) * 64;
        target_x = FIELD(arg1, s16, 2) - 32;
        step_x -= target_x;
        step_x /= timer;
        next_x = FIELD(arg1, u16, 2) + step_x;
        step_x = FIELD(arg1, s16, 0x12);
        FIELD(arg1, s16, 2) = next_x;
        ASM_SCHED_BARRIER();
        step_x *= 64;
        target_y_step = FIELD(arg1, s16, 6) - 32;
        step_x -= target_y_step;
        step_x /= FIELD(arg0, s16, 0x36);
        FIELD(arg1, s16, 6) += step_x;
        FIELD(arg1, s16, 0x0A) +=
            (FIELD(arg1, s16, 0x16) - FIELD(arg1, s16, 0x0A)) /
            FIELD(arg0, s16, 0x36);
    }

    if (FIELD(arg0, s16, 0x36) <= 0) {
        color[0] = 6;
        color[1] = 12;
        color[2] = 0;
        color[3] = 0;
        func_800A7A7C(FIELD(arg1, s16, 0x0E),
                      FIELD(arg1, s16, 0x12),
                      FIELD(arg1, s16, 0x16),
                      FIELD(arg2, void *, 8), color);
#ifdef __mips__
        func_8014CBD8();
        return;
#else
        goto state_two_finish;
#endif
    }

state_one_end:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto state_one;
    }

state_two_check:
    if (FIELD(arg0, s16, 0x2C) != 2) {
        goto state_zero_check;
    }

    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x74);
    FIELD(arg0, s32, 0x74) += FIELD(arg0, s32, 0x80);
    FIELD(arg2, u16, 0x1E) -= 200;
    FIELD(arg2, u16, 0x1C) = FIELD(arg2, u16, 0x1E);
    old_z = FIELD(arg1, s16, 0x0A);
    if (func_800BCB04((FIELD(arg0, s8, 0x5C) << 6) & 0xFFC0,
                      (FIELD(arg0, s8, 0x5D) << 6) & 0xFFC0,
                      (s16)(FIELD(arg1, u16, 0x0A) - 32)) - 7 < old_z) {
        FIELD(arg1, s16, 0x0A) =
            func_800BCB04((FIELD(arg0, s8, 0x5C) << 6) & 0xFFC0,
                          (FIELD(arg0, s8, 0x5D) << 6) & 0xFFC0,
                          (s16)(FIELD(arg1, u16, 0x0A) - 32));
        FIELD(arg1, s16, 8) = 0;
state_two_finish:
        FIELD(FIELD(arg0, void *, 0x40), s16, 0xA4) = 0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        goto done;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto state_two_check;
    }

state_zero_check:
    if (FIELD(arg0, s16, 0x2C) != 0) {
        goto done;
    }

    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x6C);
    FIELD(arg0, s32, 0x6C) += FIELD(arg0, s32, 0x78);
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x70);
    points_base = (s16 *)&points;
    velocity_y = FIELD(arg0, s32, 0x70);
    ASM_USE(velocity_y);
    point_index = FIELD(arg0, s16, 0x34);
    point_accel = FIELD(arg0, s32, 0x7C);
    point = points_base + point_index * 2;
    ASM_USE2(point, point_accel);
    point_old_x = FIELD(arg0, s8, 0x5C);
    velocity_y += point_accel;
    FIELD(arg0, s32, 0x70) = velocity_y;
    point_x = point[0];
    ASM_USE(point_x);
    grid_x = FIELD(arg1, s16, 2);
    point_old_x += point_x;
    if (grid_x < 0) {
        grid_x += 63;
    }
    grid_x_div = grid_x >> 6;
    if (point_old_x != grid_x_div) {
        goto state_zero_z;
    }
    point_y = point[1];
    grid_y = FIELD(arg1, s16, 6);
    point_old_y = FIELD(arg0, s8, 0x5D);
    point_old_y += point_y;
    if (grid_y < 0) {
        grid_y += 63;
    }
    grid_y_div = grid_y >> 6;
    if (point_old_y != grid_y_div) {
        goto state_zero_z;
    }
    if (func_800A45D8(FIELD(arg1, u16, 2),
                      FIELD(arg1, u16, 6),
                      FIELD(arg1, s16, 0x0A)) != 0) {
        goto state_zero_collision;
    }
    if (func_800BCB04(FIELD(arg1, u16, 2),
                      FIELD(arg1, u16, 6),
                      FIELD(arg1, s16, 0x0A)) < 0x200) {
        goto state_zero_update;
    }

state_zero_collision:
    FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x6C);
    FIELD(arg0, s32, 0x6C) = 0;
    FIELD(arg0, s32, 0x78) = 0;
    FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x70);
    FIELD(arg0, s32, 0x70) = 0;
    FIELD(arg0, s32, 0x7C) = 0;
#ifdef __mips__
    func_8014CD98();
    return;
#else
    goto state_zero_z;
#endif

state_zero_update:
    update_index_x = FIELD(arg0, s16, 0x34);
    ASM_KEEP_DEP_NV(arg0, update_index_x);
    point_old_x = FIELD(arg0, u8, 0x5C);
    ASM_KEEP_DEP_NV(arg0, point_old_x);
    update_x = (u8 *)points_base + update_index_x * 4;
    point_old_x += update_x[0];
    FIELD(arg0, s8, 0x5C) = point_old_x;
    update_y = (u8 *)points_base + FIELD(arg0, s16, 0x34) * 4;
    FIELD(arg0, s8, 0x5D) += update_y[2];
    FIELD(arg2, s16, 6) = 0;

state_zero_z:
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x74);
    FIELD(arg0, s32, 0x74) += FIELD(arg0, s32, 0x80);
    old_z2 = FIELD(arg1, s16, 0x0A);
    if (func_800BCB04((FIELD(arg0, s8, 0x5C) << 6) & 0xFFC0,
                      (FIELD(arg0, s8, 0x5D) << 6) & 0xFFC0,
                      (s16)(FIELD(arg1, u16, 0x0A) - 32)) - 16 < old_z2) {
        FIELD(arg1, s16, 0x0A) =
            func_800BCB04((FIELD(arg0, s8, 0x5C) << 6) & 0xFFC0,
                          (FIELD(arg0, s8, 0x5D) << 6) & 0xFFC0,
                          (s16)(FIELD(arg1, u16, 0x0A) - 32));
        FIELD(arg1, s16, 8) = 0;
        FIELD(arg0, s32, 0x7C) = 0;
        FIELD(arg0, s32, 0x70) = 0;
        FIELD(arg0, s32, 0x78) = 0;
        FIELD(arg0, s32, 0x6C) = 0;
        FIELD(arg0, s16, 0x2C)++;
        if (func_800A7234(FIELD(arg0, s8, 0x5C),
                          FIELD(arg0, s8, 0x5D),
                          (s16)(FIELD(arg1, u16, 0x0A) - 32),
                          (u8 *)arg1 + 14,
                          (u8 *)arg1 + 18,
                          (u8 *)arg1 + 22) != 0) {
            goto done;
        }
        FIELD(arg0, s16, 0x2C) = 2;
        FIELD(arg0, s32, 0x74) = -0x80000;
#ifdef __mips__
        func_8014CEB8();
        return;
#endif
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto state_zero_check;
    }
    goto done;

done:
    return;
}

#ifdef __mips__
#undef arg2
#endif
