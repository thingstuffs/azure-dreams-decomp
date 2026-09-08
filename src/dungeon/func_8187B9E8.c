#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8187B9E8_0 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x2C];
    s16 unk_44;
    u8 pad_46[0x2C];
    s16 unk_72;
} S_8187B9E8_0;   /* v in func_8187B9E8 */

typedef struct S_8187B9E8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8187B9E8_1;   /* p in func_8187B9E8 */

typedef struct S_8187B9E8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8187B9E8_2;   /* r0 in func_8187B9E8 */

typedef struct S_8187B9E8_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8187B9E8_3;   /* r1 in func_8187B9E8 */

typedef struct S_8187B9E8_4 {
    s32 unk_00;
    u8 pad_04[0xC];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x8A];
    s16 unk_A0;
} S_8187B9E8_4;   /* q in func_8187B9E8 */



typedef union {
    u16 value;
    s32 word;
} U16Arg;

extern void *func_8003FC64(s32);
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80069EF8();
extern u8 D_800249F4[];
extern u8 D_80024D40[];

/* Create an effect with 23 random radial vectors and initialize its position and state. */
void func_8187B9E8(s32 radius, s32 initial_value, s16 extent, u16 position_x, U16Arg position_y, U16Arg position_z) {
    register s32 held_radius ASM_REG("$23") = radius;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 position_xyz[3];
    s32 point_count;
    s32 angle_a;
    s32 angle_b;
    s32 plane_radius;
    register s32 component ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 work_value ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *effect;
    S_8187B9E8_4 *state;
    S_8187B9E8_2 *position;
    S_8187B9E8_3 *scale;
    register u8 *point ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    work_value = position_y.value;
    position_xyz[1] = work_value;
    work_value = position_z.value;
    position_xyz[2] = work_value;
    position_xyz[0] = position_x;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        point_count = 0;
        state = (u8 *)effect + 0x20;
        point = state;
        do {
            point_count++;
            angle_a = func_80069EF8() & 0xFFF;
            angle_b = func_80069EF8() & 0xFFF;
            work_value = held_radius * func_80064584(angle_a);
            plane_radius = work_value >> 12;
            work_value = plane_radius * func_800644B8(angle_b);
            component = work_value >> 12;
            ((S_8187B9E8_0 *)point)->unk_16 = component;
            work_value = plane_radius * func_80064584(angle_b);
            component = work_value >> 12;
            ((S_8187B9E8_0 *)point)->unk_44 = component;
            work_value = held_radius * func_800644B8(angle_a);
            component = work_value >> 12;
            ((S_8187B9E8_0 *)point)->unk_72 = component;
            point = (u8 *)point + 2;
        } while (point_count < 0x17);
        position = ((S_8187B9E8_1 *)effect)->unk_08;
        work_value = position_xyz[0];
        position->unk_02 = work_value;
        work_value = position_xyz[1];
        position->unk_06 = work_value;
        work_value = position_xyz[2];
        position->unk_0A = work_value;
        ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        scale = ((S_8187B9E8_1 *)effect)->unk_0C;
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        state->unk_14 = 0x17;
        ((S_8187B9E8_1 *)effect)->unk_10 = D_80024D40;
        state->unk_A0 = (func_80069EF8() & 0x3F) + 0x3C;
        state->unk_10 = extent;
        state->unk_12 = extent;
        func_8004491C(effect, D_800249F4);
        work_value = *(volatile s32 *)&initial_value;
        ASM_KEEP(work_value);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        state->unk_00 = work_value;
    }
}
