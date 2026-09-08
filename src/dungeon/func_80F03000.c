#include "common.h"


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

typedef struct S_80F03000_0_pre {
    u16 unk_00;
} S_80F03000_0_pre;   /* the 0x2 bytes before arg0 in BODY_NAME, addressed as arg0[-1] */

typedef struct S_80F03000_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x4];
    s16 unk_34;
    union { u16 u; s16 s; } unk_36;   /* accessed as both */
    u8 pad_38[0x8];
    void * unk_40;
    u8 pad_44[0x18];
    union { s8 s; u8 u; } unk_5C;   /* accessed as both */
    s8 unk_5D;
    u8 pad_5E[0xE];
    s32 unk_6C;
    s32 unk_70;
    s32 unk_74;
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
} S_80F03000_0;   /* arg0 in BODY_NAME */

typedef struct S_80F03000_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80F03000_1;   /* arg1 in BODY_NAME */

typedef struct S_80F03000_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80F03000_2;   /* arg2 in BODY_NAME */

typedef struct S_80F03000_3 {
    u8 pad_00[0xA4];
    s16 unk_A4;
} S_80F03000_3;   /* ((S_80F03000_0 *)arg0)->unk_40 in BODY_NAME */

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
    register s32 velocity_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 point_index;
    s32 point_accel;
    register s32 point_old_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 point_x;
    s32 grid_x;
    s32 grid_x_div;
    register s16 point_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 point_old_y;
    register s32 grid_y ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 grid_y_div ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 update_index_x;
    u8 *update_x;
    u8 *update_y;
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
    void *arg2_reg = arg2;
#define arg2 arg2_reg
#endif

    points = D_8014C808;

state_one:
    if (((S_80F03000_0 *)arg0)->unk_2C != 1) {
        goto state_two_check;
    }
    if (((S_80F03000_0 *)arg0)->unk_2E != 0) {
        goto countdown;
    }

    ((S_80F03000_0 *)arg0)->unk_2E++;
    target_y = ((S_80F03000_0 *)arg0)->unk_5D;
    delta_x = ((S_80F03000_1 *)arg1)->unk_0E - ((S_80F03000_0 *)arg0)->unk_5C.s;
    raw_y = ((S_80F03000_1 *)arg1)->unk_12;
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
        s32 call_value = 4;
        ASM_TAILSLOT_PIN(call_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_8014CA0C();
    }
#else
    switch_value = 4;
    goto switch_store;
#endif
switch_case1:
#ifdef __mips__
    {
        s32 call_value = 8;
        ASM_TAILSLOT_PIN(call_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_8014CA0C();
    }
#else
    switch_value = 8;
    goto switch_store;
#endif
switch_case2:
#ifdef __mips__
    {
        s32 call_value = 12;
        ASM_TAILSLOT_PIN(call_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_8014CA0C();
    }
#else
    switch_value = 12;
    goto switch_store;
#endif
switch_case3:
#ifdef __mips__
    {
        s32 call_value = 14;
        ASM_TAILSLOT_PIN(call_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_8014CA0C();
    }
#else
    switch_value = 14;
    goto switch_store;
#endif
switch_default:
    switch_value = 16;
switch_store:
    ((S_80F03000_0 *)arg0)->unk_36.u = switch_value;
    goto countdown;

countdown:
    timer = ((S_80F03000_0 *)arg0)->unk_36.s - 1;
    ((S_80F03000_0 *)arg0)->unk_36.s = timer;
    if (timer != 0) {
#ifdef __mips__
        register s32 step_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        s32 next_x;
#else
        s32 step_x;
        s32 next_x;
#endif
        s32 target_x;
        s32 target_y_step;
        step_x = ((S_80F03000_1 *)arg1)->unk_0E * 64;
        target_x = ((S_80F03000_1 *)arg1)->unk_00.at02.v - 32;
        step_x -= target_x;
        step_x /= timer;
        next_x = ((S_80F03000_1 *)arg1)->unk_00.at02u.v + step_x;
        step_x = ((S_80F03000_1 *)arg1)->unk_12;
        ((S_80F03000_1 *)arg1)->unk_00.at02.v = next_x;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        step_x *= 64;
        target_y_step = ((S_80F03000_1 *)arg1)->unk_04.at02.v - 32;
        step_x -= target_y_step;
        step_x /= ((S_80F03000_0 *)arg0)->unk_36.s;
        ((S_80F03000_1 *)arg1)->unk_04.at02.v += step_x;
        ((S_80F03000_1 *)arg1)->unk_08.at02.v +=
            (((S_80F03000_1 *)arg1)->unk_16 - ((S_80F03000_1 *)arg1)->unk_08.at02.v) /
            ((S_80F03000_0 *)arg0)->unk_36.s;
    }

    if (((S_80F03000_0 *)arg0)->unk_36.s <= 0) {
        color[0] = 6;
        color[1] = 12;
        color[2] = 0;
        color[3] = 0;
        func_800A7A7C(((S_80F03000_1 *)arg1)->unk_0E,
                      ((S_80F03000_1 *)arg1)->unk_12,
                      ((S_80F03000_1 *)arg1)->unk_16,
                      ((S_80F03000_2 *)arg2)->unk_08, color);
#ifdef __mips__
        func_8014CBD8();
        return;
#else
        goto state_two_finish;
#endif
    }

state_one_end:
    if (((S_80F03000_2 *)arg2)->unk_14 & 0x8000) {
        goto state_one;
    }

state_two_check:
    if (((S_80F03000_0 *)arg0)->unk_2C != 2) {
        goto state_zero_check;
    }

    ((S_80F03000_1 *)arg1)->unk_08.at00.v += ((S_80F03000_0 *)arg0)->unk_74;
    ((S_80F03000_0 *)arg0)->unk_74 += ((S_80F03000_0 *)arg0)->unk_80;
    ((S_80F03000_2 *)arg2)->unk_1E -= 200;
    ((S_80F03000_2 *)arg2)->unk_1C = ((S_80F03000_2 *)arg2)->unk_1E;
    old_z = ((S_80F03000_1 *)arg1)->unk_08.at02.v;
    if (func_800BCB04((((S_80F03000_0 *)arg0)->unk_5C.s << 6) & 0xFFC0,
                      (((S_80F03000_0 *)arg0)->unk_5D << 6) & 0xFFC0,
                      (s16)(((S_80F03000_1 *)arg1)->unk_08.at02u.v - 32)) - 7 < old_z) {
        ((S_80F03000_1 *)arg1)->unk_08.at02.v =
            func_800BCB04((((S_80F03000_0 *)arg0)->unk_5C.s << 6) & 0xFFC0,
                          (((S_80F03000_0 *)arg0)->unk_5D << 6) & 0xFFC0,
                          (s16)(((S_80F03000_1 *)arg1)->unk_08.at02u.v - 32));
        ((S_80F03000_1 *)arg1)->unk_08.at00u.v = 0;
state_two_finish:
        ((S_80F03000_3 *)(((S_80F03000_0 *)arg0)->unk_40))->unk_A4 = 0;
        ((S_80F03000_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        goto done;
    }
    if (((S_80F03000_2 *)arg2)->unk_14 & 0x8000) {
        goto state_two_check;
    }

state_zero_check:
    if (((S_80F03000_0 *)arg0)->unk_2C != 0) {
        goto done;
    }

    ((S_80F03000_1 *)arg1)->unk_00.at00.v += ((S_80F03000_0 *)arg0)->unk_6C;
    ((S_80F03000_0 *)arg0)->unk_6C += ((S_80F03000_0 *)arg0)->unk_78;
    ((S_80F03000_1 *)arg1)->unk_04.at00.v += ((S_80F03000_0 *)arg0)->unk_70;
    points_base = (s16 *)&points;
    velocity_y = ((S_80F03000_0 *)arg0)->unk_70;
    point_index = ((S_80F03000_0 *)arg0)->unk_34;
    point_accel = ((S_80F03000_0 *)arg0)->unk_7C;
    point = points_base + point_index * 2;
    ASM_USE2(point, point_accel);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    point_old_x = ((S_80F03000_0 *)arg0)->unk_5C.s;
    velocity_y += point_accel;
    ((S_80F03000_0 *)arg0)->unk_70 = velocity_y;
    point_x = point[0];
    grid_x = ((S_80F03000_1 *)arg1)->unk_00.at02.v;
    point_old_x += point_x;
    if (grid_x < 0) {
        grid_x += 63;
    }
    grid_x_div = grid_x >> 6;
    if (point_old_x != grid_x_div) {
        goto state_zero_z;
    }
    point_y = point[1];
    grid_y = ((S_80F03000_1 *)arg1)->unk_04.at02.v;
    point_old_y = ((S_80F03000_0 *)arg0)->unk_5D;
    point_old_y += point_y;
    if (grid_y < 0) {
        grid_y += 63;
    }
    grid_y_div = grid_y >> 6;
    if (point_old_y != grid_y_div) {
        goto state_zero_z;
    }
    if (func_800A45D8(((S_80F03000_1 *)arg1)->unk_00.at02u.v,
                      ((S_80F03000_1 *)arg1)->unk_04.at02u.v,
                      ((S_80F03000_1 *)arg1)->unk_08.at02.v) != 0) {
        goto state_zero_collision;
    }
    if (func_800BCB04(((S_80F03000_1 *)arg1)->unk_00.at02u.v,
                      ((S_80F03000_1 *)arg1)->unk_04.at02u.v,
                      ((S_80F03000_1 *)arg1)->unk_08.at02.v) < 0x200) {
        goto state_zero_update;
    }

state_zero_collision:
    ((S_80F03000_1 *)arg1)->unk_00.at00.v -= ((S_80F03000_0 *)arg0)->unk_6C;
    ((S_80F03000_0 *)arg0)->unk_6C = 0;
    ((S_80F03000_0 *)arg0)->unk_78 = 0;
    ((S_80F03000_1 *)arg1)->unk_04.at00.v -= ((S_80F03000_0 *)arg0)->unk_70;
    ((S_80F03000_0 *)arg0)->unk_70 = 0;
    ((S_80F03000_0 *)arg0)->unk_7C = 0;
#ifdef __mips__
    func_8014CD98();
    return;
#else
    goto state_zero_z;
#endif

state_zero_update:
    update_index_x = ((S_80F03000_0 *)arg0)->unk_34;
    point_old_x = ((S_80F03000_0 *)arg0)->unk_5C.u;
    update_x = (u8 *)points_base + update_index_x * 4;
    point_old_x += update_x[0];
    ((S_80F03000_0 *)arg0)->unk_5C.s = point_old_x;
    update_y = (u8 *)points_base + ((S_80F03000_0 *)arg0)->unk_34 * 4;
    ((S_80F03000_0 *)arg0)->unk_5D += update_y[2];
    ((S_80F03000_2 *)arg2)->unk_06 = 0;

state_zero_z:
    ((S_80F03000_1 *)arg1)->unk_08.at00.v += ((S_80F03000_0 *)arg0)->unk_74;
    ((S_80F03000_0 *)arg0)->unk_74 += ((S_80F03000_0 *)arg0)->unk_80;
    old_z2 = ((S_80F03000_1 *)arg1)->unk_08.at02.v;
    if (func_800BCB04((((S_80F03000_0 *)arg0)->unk_5C.s << 6) & 0xFFC0,
                      (((S_80F03000_0 *)arg0)->unk_5D << 6) & 0xFFC0,
                      (s16)(((S_80F03000_1 *)arg1)->unk_08.at02u.v - 32)) - 16 < old_z2) {
        ((S_80F03000_1 *)arg1)->unk_08.at02.v =
            func_800BCB04((((S_80F03000_0 *)arg0)->unk_5C.s << 6) & 0xFFC0,
                          (((S_80F03000_0 *)arg0)->unk_5D << 6) & 0xFFC0,
                          (s16)(((S_80F03000_1 *)arg1)->unk_08.at02u.v - 32));
        ((S_80F03000_1 *)arg1)->unk_08.at00u.v = 0;
        ((S_80F03000_0 *)arg0)->unk_7C = 0;
        ((S_80F03000_0 *)arg0)->unk_70 = 0;
        ((S_80F03000_0 *)arg0)->unk_78 = 0;
        ((S_80F03000_0 *)arg0)->unk_6C = 0;
        ((S_80F03000_0 *)arg0)->unk_2C++;
        if (func_800A7234(((S_80F03000_0 *)arg0)->unk_5C.s,
                          ((S_80F03000_0 *)arg0)->unk_5D,
                          (s16)(((S_80F03000_1 *)arg1)->unk_08.at02u.v - 32),
                          (u8 *)arg1 + 14,
                          (u8 *)arg1 + 18,
                          (u8 *)arg1 + 22) != 0) {
            goto done;
        }
        ((S_80F03000_0 *)arg0)->unk_2C = 2;
        ((S_80F03000_0 *)arg0)->unk_74 = -0x80000;
#ifdef __mips__
        func_8014CEB8();
        return;
#endif
    }
    if (((S_80F03000_2 *)arg2)->unk_14 & 0x8000) {
        goto state_zero_check;
    }
    goto done;

done:
    return;
}

#ifdef __mips__
#undef arg2
#endif
