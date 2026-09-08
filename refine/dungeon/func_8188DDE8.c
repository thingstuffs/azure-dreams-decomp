#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void func_800649A0(s32);
extern void func_80064A40(void);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065320(void *, void *, void *);
extern void func_80065820(void *, void *);
extern u16 D_80026472[5];
extern s32 D_800814A0;

/* Rotate and move four effect vertices, fade their colors, and mark the effect expired when its lifetime ends. */
void func_800255E8(void *effect, void *motion, void *rotation)
{
    u16 angles[3];
    s32 matrix[8];
    u16 *scratch = (u16 *)0x1F800000;
    void *motion_state = motion;
    u16 *counter_page;
    s32 center_z;
    u16 vertex_z;
    u16 update_count;
    u16 relative_z;
    s32 red_a;
    s32 green_a;
    s32 blue_a;
    s32 red_b;
    register s32 green_b ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    register s32 blue_b ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 red_step_a;
    s32 green_step_a;
    s32 blue_step_a;
    s32 red_step_b;
    register s32 green_step_b ASM_REG("$11");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 blue_step_b ASM_REG("$9");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 frames_left;
    s32 frames_test;

    scratch[0x70 / 2] = U16_AT(effect, 0x34) - U16_AT(motion_state, 2);
    scratch[0x78 / 2] = U16_AT(effect, 0x3C) - U16_AT(motion_state, 2);
    scratch[0x80 / 2] = U16_AT(effect, 0x44) - U16_AT(motion_state, 2);
    scratch[0x88 / 2] = U16_AT(effect, 0x4C) - U16_AT(motion_state, 2);
    scratch[0x72 / 2] = U16_AT(effect, 0x36) - U16_AT(motion_state, 6);
    scratch[0x7A / 2] = U16_AT(effect, 0x3E) - U16_AT(motion_state, 6);
    scratch[0x82 / 2] = U16_AT(effect, 0x46) - U16_AT(motion_state, 6);
    scratch[0x8A / 2] = U16_AT(effect, 0x4E) - U16_AT(motion_state, 6);
    scratch[0x74 / 2] = U16_AT(effect, 0x38) - U16_AT(motion_state, 0xA);
    scratch[0x7C / 2] = U16_AT(effect, 0x40) - U16_AT(motion_state, 0xA);
    counter_page = (u16 *)0x80020000;

    update_count = counter_page[0x6472 / 2];
    vertex_z = U16_AT(effect, 0x48);
    center_z = U16_AT(motion_state, 0xA);
    update_count++;
    relative_z = vertex_z - center_z;
    counter_page[0x6472 / 2] = update_count;
    scratch[0x84 / 2] = relative_z;
    scratch[0x8C / 2] = U16_AT(effect, 0x50) - U16_AT(motion_state, 0xA);
    func_800649A0(center_z);

    angles[0] = U16_AT(rotation, 0x16);
    angles[1] = U16_AT(rotation, 0x18);
    angles[2] = 0;
    matrix[7] = 0;
    matrix[6] = 0;
    matrix[5] = 0;
    func_80065820(angles, matrix);
    func_80064D80(matrix);
    func_80064CF0(matrix);

    func_80065320(scratch + 0x70 / 2, scratch + 0x98 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x78 / 2, scratch + 0xA0 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x80 / 2, scratch + 0xA8 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x88 / 2, scratch + 0xB0 / 2,
                  scratch + 0x94 / 2);
    func_80064A40();

    S32_AT(motion_state, 0) = S32_AT(motion_state, 0) + S32_AT(motion_state, 0xC);
    S32_AT(motion_state, 4) = S32_AT(motion_state, 4) + S32_AT(motion_state, 0x10);
    S32_AT(motion_state, 8) = S32_AT(motion_state, 8) + S32_AT(motion_state, 0x14);

    U16_AT(effect, 0x34) = scratch[0x98 / 2] + U16_AT(motion_state, 2);
    U16_AT(effect, 0x3C) = scratch[0xA0 / 2] + U16_AT(motion_state, 2);
    U16_AT(effect, 0x44) = scratch[0xA8 / 2] + U16_AT(motion_state, 2);
    U16_AT(effect, 0x4C) = scratch[0xB0 / 2] + U16_AT(motion_state, 2);
    U16_AT(effect, 0x36) = scratch[0x9A / 2] + U16_AT(motion_state, 6);
    U16_AT(effect, 0x3E) = scratch[0xA2 / 2] + U16_AT(motion_state, 6);
    U16_AT(effect, 0x46) = scratch[0xAA / 2] + U16_AT(motion_state, 6);
    U16_AT(effect, 0x4E) = scratch[0xB2 / 2] + U16_AT(motion_state, 6);
    U16_AT(effect, 0x38) = scratch[0x9C / 2] + U16_AT(motion_state, 0xA);

    red_a = U8_AT(effect, 0x54);
    ASM_KEEP_NV(red_a);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    red_step_a = red_a / S16_AT(effect, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    green_a = U8_AT(effect, 0x55);
    ASM_KEEP_NV(green_a);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    green_step_a = green_a / S16_AT(effect, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    blue_a = U8_AT(effect, 0x56);
    ASM_KEEP_NV(blue_a);   /* MATCH pin: load-bearing for the whole function shape */
    blue_step_a = blue_a / S16_AT(effect, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    red_b = U8_AT(effect, 0x58);
    ASM_KEEP_NV(red_b);   /* MATCH pin: retail register colouring depends on it */
    red_step_b = red_b / S16_AT(effect, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    green_b = U8_AT(effect, 0x59);
    green_step_b = green_b / S16_AT(effect, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    blue_b = U8_AT(effect, 0x5A);
    blue_step_b = blue_b / S16_AT(effect, 0x1A);

    U16_AT(effect, 0x40) = scratch[0xA4 / 2] + U16_AT(motion_state, 0xA);
    U16_AT(effect, 0x48) = scratch[0xAC / 2] + U16_AT(motion_state, 0xA);
    U16_AT(effect, 0x50) = scratch[0xB4 / 2] + U16_AT(motion_state, 0xA);
    frames_left = (u16)S16_AT(effect, 0x1A) - 1;
    S16_AT(effect, 0x1A) = frames_left;
    frames_test = frames_left << 16;

    red_a -= red_step_a;
    green_a -= green_step_a;
    blue_a -= blue_step_a;
    red_b -= red_step_b;
    green_b -= green_step_b;
    blue_b -= blue_step_b;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    U8_AT(effect, 0x54) = red_a;
    U8_AT(effect, 0x55) = green_a;
    U8_AT(effect, 0x56) = blue_a;
    U8_AT(effect, 0x58) = red_b;
    U8_AT(effect, 0x59) = green_b;
    U8_AT(effect, 0x5A) = blue_b;

    if (frames_test <= 0) {
        U16_AT(effect, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
