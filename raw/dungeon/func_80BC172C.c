#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80170884[];
extern void *func_8003FD64(s32, void *);
extern M2C_UNK func_8004491C(void *, void *);
extern s32 rand(void);
extern M2C_UNK D_80170BFC;

void func_80BC172C(void *arg0, register s16 arg1, register s32 arg2, register s32 arg3, register s32 arg4, register s32 arg5, register s32 arg6) {
    register void *held_arg0 = arg0;
    register s16 held_arg1 = arg1;
    register s32 held_arg2 = arg2;
    register s32 held_arg4 = arg4;
    register s32 held_arg5 = arg5;
    register s32 held_arg6 = arg6;
    void *temp_s0;
    void *temp_v0;
    u16 temp_coord;

    temp_v0 = func_8003FD64(0x211, held_arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80170BFC;
        do {
        temp_coord = M2C_FIELD(M2C_FIELD(held_arg0, void **, 8), u16 *, 2);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (temp_coord + held_arg4);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(held_arg0, void **, 8), u16 *, 6) + held_arg5);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) ((M2C_FIELD(M2C_FIELD(held_arg0, void **, 8), u16 *, 0xA) + held_arg6) - 0x64);
        } while (0);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0xC), s16 *, 6) = 6;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x10) = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        M2C_FIELD(temp_s0, s16 *, 0x14) = held_arg1;
        M2C_FIELD(temp_s0, s16 *, 0x32) = 5;
        M2C_FIELD(temp_s0, s16 *, 0x34) = 5;
        func_8004491C(temp_v0, D_80170884);
        M2C_FIELD(temp_v0, s32 *, 0x20) = held_arg2;
        M2C_FIELD(temp_s0, s32 *, 8) = held_arg2;
    }
}
