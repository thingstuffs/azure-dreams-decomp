#include "common.h"

typedef struct S_80170D2C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x2];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x3A];
    volatile s32 unk_5C;
    volatile s32 unk_60;
    volatile s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
} S_80170D2C_0;   /* work in func_80170D2C */

typedef struct S_80170D2C_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80170D2C_1;   /* obj in func_80170D2C */

typedef struct S_80170D2C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80170D2C_2;   /* packet in func_80170D2C */

typedef struct S_80170D2C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80170D2C_3;   /* prim in func_80170D2C */

typedef struct S_80170D2C_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80170D2C_4;   /* D_80083780 in func_80170D2C */



extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern u8 D_80083780[];
extern u8 D_80170BB0[];
extern u8 D_80173B88[];

/* Create an offset object and initialize its motion and render data. */
void func_80170D2C(s32 unused, s16 duration, s32 offset_x, s32 offset_y, s32 offset_z) {
    register s32 duration_value ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 step_divisor;
    s32 delta_z;
    s32 delta_y;
    register s32 delta_x ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 fixed_value;
    s32 rounded_x;
    s32 rounded_y;
    s32 rounded_z;
    u8 *obj;
    u8 *work;
    u8 *prim;
    u8 *packet;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        work = obj + 0x20;
        ((S_80170D2C_0 *)work)->unk_18 = duration;
        ((S_80170D2C_1 *)obj)->unk_10 = D_80170BB0;
        func_8004491C(obj, &D_80045340);
        packet = ((S_80170D2C_1 *)obj)->unk_0C;
        ((S_80170D2C_2 *)packet)->unk_10 = 0x20;
        ((S_80170D2C_2 *)packet)->unk_06 = 0;
        ((S_80170D2C_2 *)packet)->unk_14 |= 0xC;
        prim = ((S_80170D2C_1 *)obj)->unk_08;
        ((S_80170D2C_3 *)prim)->unk_00.at00.v = ((S_80170D2C_4 *)D_80083780)->unk_00.at00.v;
        ((S_80170D2C_3 *)prim)->unk_04.at00.v = ((S_80170D2C_4 *)D_80083780)->unk_04.at00.v;
        ((S_80170D2C_3 *)prim)->unk_08.at00.v = ((S_80170D2C_4 *)D_80083780)->unk_08.at00.v;
        ((S_80170D2C_3 *)prim)->unk_00.at02.v += offset_x;
        ((S_80170D2C_3 *)prim)->unk_04.at02.v += offset_y;
        ((S_80170D2C_3 *)prim)->unk_08.at02.v += offset_z;
        ((S_80170D2C_0 *)work)->unk_1C = ((S_80170D2C_4 *)D_80083780)->unk_00.at02.v;
        ((S_80170D2C_0 *)work)->unk_1E = ((S_80170D2C_4 *)D_80083780)->unk_04.at02.v;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        fixed_value = duration << 16;
        duration_value = fixed_value >> 16;
        ((S_80170D2C_0 *)work)->unk_20 = ((S_80170D2C_4 *)D_80083780)->unk_08.at02.v;
        step_divisor = duration_value;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        fixed_value = -(offset_x << 16);
        if (duration_value < 0) {
            step_divisor = duration_value + 7;
        }
        step_divisor >>= 3;
        delta_x = fixed_value / step_divisor;
        ((S_80170D2C_0 *)work)->unk_5C = delta_x / 2;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        delta_y = -(offset_y << 16) / step_divisor;
        ((S_80170D2C_0 *)work)->unk_60 = delta_y / 2;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        delta_z = -(offset_z << 16) / step_divisor;
        ((S_80170D2C_0 *)work)->unk_64 = delta_z / 2;
        ASM_KEEP(duration_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        rounded_x = delta_x;
        if (rounded_x < 0) rounded_x += 3;
        ((S_80170D2C_0 *)work)->unk_68 = rounded_x >> 2;
        ASM_KEEP(delta_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        rounded_y = delta_y;
        if (rounded_y < 0) rounded_y += 3;
        ((S_80170D2C_0 *)work)->unk_6C = rounded_y >> 2;
        rounded_z = delta_z;
        if (rounded_z < 0) rounded_z += 3;
        ((S_80170D2C_0 *)work)->unk_70 = rounded_z >> 2;
        packet = ((S_80170D2C_1 *)obj)->unk_0C;
        ((S_80170D2C_2 *)packet)->unk_1E = 0x1000;
        ((S_80170D2C_2 *)packet)->unk_1C = 0x1000;
        ((S_80170D2C_2 *)packet)->unk_0E = 0;
        ((S_80170D2C_2 *)packet)->unk_0D = 0;
        ((S_80170D2C_2 *)packet)->unk_0C = 0;
        __builtin_memcpy(obj + 0x48, D_80173B88, 12);
        ((S_80170D2C_2 *)packet)->unk_08 = obj + 0x48;
    }
}
