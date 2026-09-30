#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8187B9E8_0 {
    u8 pad_00[0x16];
    s16 unk_16[23];
    s16 unk_44[23];
    s16 unk_72[23];
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



extern void *func_8003FC64(s32);
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80069EF8();
extern u8 D_800249F4[];
extern u8 D_80024D40[];

/* Create an effect with 23 random radial vectors and initialize its position and state. */
void func_8187B9E8(s32 radius, s32 initial_value, s16 extent, u16 position_x, u16 position_y, u16 position_z) {
    s32 point_count;
    s32 angle_a;
    s32 angle_b;
    s32 plane_radius;
    u32 component;
    S_8187B9E8_2 *position;
    void *effect;
    S_8187B9E8_4 *state;
    S_8187B9E8_3 *scale;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        point_count = 0;
        state = (u8 *)effect + 0x20;
        do {
            angle_a = func_80069EF8() & 0xFFF;
            angle_b = func_80069EF8() & 0xFFF;
            plane_radius = (radius * func_80064584(angle_a)) >> 12;
            component = (plane_radius * func_800644B8(angle_b)) >> 12;
            ((S_8187B9E8_0 *)state)->unk_16[point_count] = component;
            component = (plane_radius * func_80064584(angle_b)) >> 12;
            ((S_8187B9E8_0 *)state)->unk_44[point_count] = component;
            component = (radius * func_800644B8(angle_a)) >> 12;
            ((S_8187B9E8_0 *)state)->unk_72[point_count] = component;
            point_count++;
        } while (point_count < 0x17);
        position = ((S_8187B9E8_1 *)effect)->unk_08;
        position->unk_02 = position_x;
        position->unk_06 = position_y;
        position->unk_0A = position_z;
        scale = ((S_8187B9E8_1 *)effect)->unk_0C;
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        state->unk_14 = 0x17;
        ((S_8187B9E8_1 *)effect)->unk_10 = D_80024D40;
        state->unk_A0 = (func_80069EF8() & 0x3F) + 0x3C;
        state->unk_10 = extent;
        state->unk_12 = extent;
        func_8004491C(effect, D_800249F4);
        state->unk_00 = initial_value;
    }
}
