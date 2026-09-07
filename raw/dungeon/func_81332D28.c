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

extern u8 D_80083498[];
extern u8 *D_80175D50[3];
extern u8 D_80045340[];
extern u8 D_8016A36C[];
extern u8 *func_8003FD64(s32, u8 *);
extern void func_8004491C(u8 *, u8 *);
extern void func_800A9C18(u8 *, void *, void *, s32);
extern void func_800AA36C(u8 *, void *, void *, u8 *);
extern s32 func_800F6598(void);
extern M2C_UNK D_80169EC0;
extern M2C_UNK D_80173980;

u8 *func_80169D28(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u8 *result;
    s32 mode;
    u8 *obj;
    u8 *child;
    u8 *first;
    u8 *second;

    result = NULL;
    if (func_800F6598() == 0) {
        obj = func_8003FD64(0x112, D_80083498);
        if (obj != NULL) {
            result = obj + 0x20;
            *D_80175D50 = obj;
            M2C_FIELD(obj, M2C_UNK **, 0x10) = &D_80169EC0;
            child = obj + 0x20;
            M2C_FIELD(child, s8 *, 0x13) = 0x38;
            func_8004491C(obj, D_80045340);
            first = M2C_FIELD(obj, void **, 8);
            M2C_FIELD(first, s16 *, 0xA) = arg3;
            second = M2C_FIELD(obj, void **, 0xC);
            mode = arg0 & 3;
            M2C_FIELD(second, s8 *, 0x24) = arg1;
            M2C_FIELD(second, M2C_UNK **, 0x2C) = &D_80173980;
            M2C_FIELD(second, s8 *, 0x25) = arg2;
            if (mode == 1) {
                M2C_FIELD(child, s32 *, 0x14) = M2C_FIELD(child, s32 *, 0x14) | 0x6000;
                M2C_FIELD(child, s32 *, 0x1C) = M2C_FIELD(child, s32 *, 0x1C) | 0x6000;
            } else if (mode >= 2) {
                M2C_FIELD(child, s32 *, 0x14) = M2C_FIELD(child, s32 *, 0x14) | 0x2000;
                M2C_FIELD(child, s32 *, 0x1C) = M2C_FIELD(child, s32 *, 0x1C) | 0x2000;
            }
            M2C_FIELD(child, s8 *, 0xAC) = 0;
            M2C_FIELD(second, u16 *, 0x14) = M2C_FIELD(second, u16 *, 0x14) | 0x400;
            func_800A9C18(obj, first, second, arg0);
            M2C_FIELD(child, u8 *, 0x9A) = 0xFF;
            M2C_FIELD(child, s8 *, 0x9C) = -1;
            M2C_FIELD(child, u8 **, 0x8C) = D_8016A36C;
            M2C_FIELD(child, s8 *, 0xAA) = 0;
            M2C_FIELD(second, u16 *, 0x14) = M2C_FIELD(second, u16 *, 0x14) | 0x80;
            func_800AA36C(child, first, second, result);
        }
    }
    return result;
}
