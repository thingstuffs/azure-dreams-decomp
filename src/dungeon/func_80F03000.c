#include "common.h"


typedef struct Packed32 {
    u8 bytes[0x20];
} __attribute__((packed)) Packed32;

extern void func_800A7A7C(s16, s16, s16, void *, void *);
extern s16 func_800A45D8(u16, u16, s16);
extern s16 func_800BCB04(s32, s32, s16);
extern s16 func_800A7234(s8, s8, s16, void *, void *, void *);
extern s32 D_800814A0[3];

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

void BODY_NAME(void *actor, void *position, void *effect)
    __attribute__((section(".text.func_8014C800")));

typedef struct S_80F03000_0_pre {
    u16 unk_00;
} S_80F03000_0_pre;   /* the 0x2 bytes before actor in BODY_NAME, addressed as actor[-1] */

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
} S_80F03000_0;   /* actor in BODY_NAME */

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
} S_80F03000_1;   /* position in BODY_NAME */

typedef struct S_80F03000_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80F03000_2;   /* effect in BODY_NAME */

typedef struct S_80F03000_3 {
    u8 pad_00[0xA4];
    s16 unk_A4;
} S_80F03000_3;   /* ((S_80F03000_0 *)actor)->unk_40 in BODY_NAME */

/* Update flight, landing interpolation, and falling completion for a moving actor. */
void BODY_NAME(void *actor, void *position, void *effect)
{
    s8 color[4];
    Packed32 directions;
    s32 fall_z;
    s32 flight_z;
    s16 timer;
    u16 travel_frames;
    s32 delta_x;
    s32 delta_y;
    s32 destination_y;
    s32 start_tile_y;
    s32 distance;
#ifdef __mips__
    register s32 velocity_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 direction_index;
    s32 accel_y;
    register s32 next_tile_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 tile_step_x;
    s32 world_x;
    s32 tile_x;
    register s16 tile_step_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 next_tile_y;
    register s32 world_y ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 tile_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 update_index;
    u8 *direction_x;
    u8 *direction_y;
#else
    s32 velocity_y;
    s32 direction_index;
    s32 accel_y;
    s32 next_tile_x;
    s32 tile_step_x;
    s32 world_x;
    s32 tile_x;
    s16 tile_step_y;
    s32 next_tile_y;
    s32 world_y;
    s32 tile_y;
    s32 update_index;
    u8 *direction_x;
    u8 *direction_y;
#endif
    s16 *direction_base;
    s16 *direction;

#ifdef __mips__
    static void *const switch_keep[5] = {
        &&switch_case0, &&switch_case1, &&switch_case2,
        &&switch_case3, &&switch_default
    };
#endif

#ifdef __mips__
    void *effect_local = effect;
#define effect effect_local
#endif

    directions = D_8014C808;

state_one:
    if (((S_80F03000_0 *)actor)->unk_2C != 1) {
        goto state_two_check;
    }
    if (((S_80F03000_0 *)actor)->unk_2E != 0) {
        goto countdown;
    }

    ((S_80F03000_0 *)actor)->unk_2E++;
    start_tile_y = ((S_80F03000_0 *)actor)->unk_5D;
    delta_x = ((S_80F03000_1 *)position)->unk_0E - ((S_80F03000_0 *)actor)->unk_5C.s;
    destination_y = ((S_80F03000_1 *)position)->unk_12;
    if (delta_x < 0) {
        delta_x = -delta_x;
    }
    delta_y = destination_y - start_tile_y;
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
    travel_frames = 4;
    goto switch_store;
switch_case1:
    travel_frames = 8;
    goto switch_store;
switch_case2:
    travel_frames = 12;
    goto switch_store;
switch_case3:
    travel_frames = 14;
    goto switch_store;
switch_default:
    travel_frames = 16;
switch_store:
    ((S_80F03000_0 *)actor)->unk_36.u = travel_frames;
    goto countdown;

countdown:
    timer = ((S_80F03000_0 *)actor)->unk_36.s - 1;
    ((S_80F03000_0 *)actor)->unk_36.s = timer;
    if (timer != 0) {
#ifdef __mips__
        register s32 axis_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        s32 next_x;
#else
        s32 axis_step;
        s32 next_x;
#endif
        s32 centered_x;
        s32 centered_y;
        axis_step = ((S_80F03000_1 *)position)->unk_0E * 64;
        centered_x = ((S_80F03000_1 *)position)->unk_00.at02.v - 32;
        axis_step -= centered_x;
        axis_step /= timer;
        next_x = ((S_80F03000_1 *)position)->unk_00.at02u.v + axis_step;
        axis_step = ((S_80F03000_1 *)position)->unk_12;
        ((S_80F03000_1 *)position)->unk_00.at02.v = next_x;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        axis_step *= 64;
        centered_y = ((S_80F03000_1 *)position)->unk_04.at02.v - 32;
        axis_step -= centered_y;
        axis_step /= ((S_80F03000_0 *)actor)->unk_36.s;
        ((S_80F03000_1 *)position)->unk_04.at02.v += axis_step;
        ((S_80F03000_1 *)position)->unk_08.at02.v +=
            (((S_80F03000_1 *)position)->unk_16 - ((S_80F03000_1 *)position)->unk_08.at02.v) /
            ((S_80F03000_0 *)actor)->unk_36.s;
    }

    if (((S_80F03000_0 *)actor)->unk_36.s <= 0) {
        color[0] = 6;
        color[1] = 12;
        color[2] = 0;
        color[3] = 0;
        func_800A7A7C(((S_80F03000_1 *)position)->unk_0E,
                      ((S_80F03000_1 *)position)->unk_12,
                      ((S_80F03000_1 *)position)->unk_16,
                      ((S_80F03000_2 *)effect)->unk_08, color);
        goto state_two_finish;
    }

state_one_end:
    if (((S_80F03000_2 *)effect)->unk_14 & 0x8000) {
        goto state_one;
    }

state_two_check:
    if (((S_80F03000_0 *)actor)->unk_2C != 2) {
        goto state_zero_check;
    }

    ((S_80F03000_1 *)position)->unk_08.at00.v += ((S_80F03000_0 *)actor)->unk_74;
    ((S_80F03000_0 *)actor)->unk_74 += ((S_80F03000_0 *)actor)->unk_80;
    ((S_80F03000_2 *)effect)->unk_1E -= 200;
    ((S_80F03000_2 *)effect)->unk_1C = ((S_80F03000_2 *)effect)->unk_1E;
    fall_z = ((S_80F03000_1 *)position)->unk_08.at02.v;
    if (func_800BCB04((((S_80F03000_0 *)actor)->unk_5C.s << 6) & 0xFFC0,
                      (((S_80F03000_0 *)actor)->unk_5D << 6) & 0xFFC0,
                      (s16)(((S_80F03000_1 *)position)->unk_08.at02u.v - 32)) - 7 < fall_z) {
        ((S_80F03000_1 *)position)->unk_08.at02.v =
            func_800BCB04((((S_80F03000_0 *)actor)->unk_5C.s << 6) & 0xFFC0,
                          (((S_80F03000_0 *)actor)->unk_5D << 6) & 0xFFC0,
                          (s16)(((S_80F03000_1 *)position)->unk_08.at02u.v - 32));
        ((S_80F03000_1 *)position)->unk_08.at00u.v = 0;
state_two_finish:
        ((S_80F03000_3 *)(((S_80F03000_0 *)actor)->unk_40))->unk_A4 = 0;
        ((S_80F03000_0_pre *)actor)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        goto done;
    }
    if (((S_80F03000_2 *)effect)->unk_14 & 0x8000) {
        goto state_two_check;
    }

state_zero_check:
    if (((S_80F03000_0 *)actor)->unk_2C != 0) {
        goto done;
    }

    ((S_80F03000_1 *)position)->unk_00.at00.v += ((S_80F03000_0 *)actor)->unk_6C;
    ((S_80F03000_0 *)actor)->unk_6C += ((S_80F03000_0 *)actor)->unk_78;
    ((S_80F03000_1 *)position)->unk_04.at00.v += ((S_80F03000_0 *)actor)->unk_70;
    direction_base = (s16 *)&directions;
    velocity_y = ((S_80F03000_0 *)actor)->unk_70;
    direction_index = ((S_80F03000_0 *)actor)->unk_34;
    accel_y = ((S_80F03000_0 *)actor)->unk_7C;
    direction = direction_base + direction_index * 2;
    ASM_USE2(direction, accel_y);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    next_tile_x = ((S_80F03000_0 *)actor)->unk_5C.s;
    velocity_y += accel_y;
    ((S_80F03000_0 *)actor)->unk_70 = velocity_y;
    tile_step_x = direction[0];
    world_x = ((S_80F03000_1 *)position)->unk_00.at02.v;
    next_tile_x += tile_step_x;
    if (world_x < 0) {
        world_x += 63;
    }
    tile_x = world_x >> 6;
    if (next_tile_x != tile_x) {
        goto state_zero_z;
    }
    tile_step_y = direction[1];
    world_y = ((S_80F03000_1 *)position)->unk_04.at02.v;
    next_tile_y = ((S_80F03000_0 *)actor)->unk_5D;
    next_tile_y += tile_step_y;
    if (world_y < 0) {
        world_y += 63;
    }
    tile_y = world_y >> 6;
    if (next_tile_y != tile_y) {
        goto state_zero_z;
    }
    if (func_800A45D8(((S_80F03000_1 *)position)->unk_00.at02u.v,
                      ((S_80F03000_1 *)position)->unk_04.at02u.v,
                      ((S_80F03000_1 *)position)->unk_08.at02.v) != 0) {
        goto state_zero_collision;
    }
    if (func_800BCB04(((S_80F03000_1 *)position)->unk_00.at02u.v,
                      ((S_80F03000_1 *)position)->unk_04.at02u.v,
                      ((S_80F03000_1 *)position)->unk_08.at02.v) < 0x200) {
        goto state_zero_update;
    }

state_zero_collision:
    ((S_80F03000_1 *)position)->unk_00.at00.v -= ((S_80F03000_0 *)actor)->unk_6C;
    ((S_80F03000_0 *)actor)->unk_6C = 0;
    ((S_80F03000_0 *)actor)->unk_78 = 0;
    ((S_80F03000_1 *)position)->unk_04.at00.v -= ((S_80F03000_0 *)actor)->unk_70;
    ((S_80F03000_0 *)actor)->unk_70 = 0;
    ((S_80F03000_0 *)actor)->unk_7C = 0;
    goto state_zero_reset;

state_zero_update:
    update_index = ((S_80F03000_0 *)actor)->unk_34;
    next_tile_x = ((S_80F03000_0 *)actor)->unk_5C.u;
    direction_x = (u8 *)direction_base + update_index * 4;
    next_tile_x += direction_x[0];
    ((S_80F03000_0 *)actor)->unk_5C.s = next_tile_x;
    direction_y = (u8 *)direction_base + ((S_80F03000_0 *)actor)->unk_34 * 4;
    ((S_80F03000_0 *)actor)->unk_5D += direction_y[2];
state_zero_reset:
    ((S_80F03000_2 *)effect)->unk_06 = 0;

state_zero_z:
    ((S_80F03000_1 *)position)->unk_08.at00.v += ((S_80F03000_0 *)actor)->unk_74;
    ((S_80F03000_0 *)actor)->unk_74 += ((S_80F03000_0 *)actor)->unk_80;
    flight_z = ((S_80F03000_1 *)position)->unk_08.at02.v;
    if (func_800BCB04((((S_80F03000_0 *)actor)->unk_5C.s << 6) & 0xFFC0,
                      (((S_80F03000_0 *)actor)->unk_5D << 6) & 0xFFC0,
                      (s16)(((S_80F03000_1 *)position)->unk_08.at02u.v - 32)) - 16 < flight_z) {
        ((S_80F03000_1 *)position)->unk_08.at02.v =
            func_800BCB04((((S_80F03000_0 *)actor)->unk_5C.s << 6) & 0xFFC0,
                          (((S_80F03000_0 *)actor)->unk_5D << 6) & 0xFFC0,
                          (s16)(((S_80F03000_1 *)position)->unk_08.at02u.v - 32));
        ((S_80F03000_1 *)position)->unk_08.at00u.v = 0;
        ((S_80F03000_0 *)actor)->unk_7C = 0;
        ((S_80F03000_0 *)actor)->unk_70 = 0;
        ((S_80F03000_0 *)actor)->unk_78 = 0;
        ((S_80F03000_0 *)actor)->unk_6C = 0;
        ((S_80F03000_0 *)actor)->unk_2C++;
        if (func_800A7234(((S_80F03000_0 *)actor)->unk_5C.s,
                          ((S_80F03000_0 *)actor)->unk_5D,
                          (s16)(((S_80F03000_1 *)position)->unk_08.at02u.v - 32),
                          (u8 *)position + 14,
                          (u8 *)position + 18,
                          (u8 *)position + 22) != 0) {
            goto done;
        }
        ((S_80F03000_0 *)actor)->unk_2C = 2;
        ((S_80F03000_0 *)actor)->unk_74 = -0x80000;
        goto done;
    }
    if (((S_80F03000_2 *)effect)->unk_14 & 0x8000) {
        goto state_zero_check;
    }
    goto done;

done:
    return;
}

#ifdef __mips__
#undef effect
#endif
