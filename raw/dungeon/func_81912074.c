#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct {
    s32 words[6];
} Copy24;

extern void *func_8003FC64();
extern s32 D_800253F4;

void *func_80025874(s32 arg0, Copy24 *arg1, s16 arg2) {
    void *obj;
    void *fields;
    void *dst;
    register void *result ASM_REG("$2");

    do { obj = func_8003FC64(0x212); } while (0);
    result = 0;
    if (obj != 0) {
        FIELD(obj, void *, 0x10) = &D_800253F4;
        fields = obj + 0x20;
        FIELD(obj, s32, 0x20) = arg0;
        FIELD(fields, s16, 8) = 8;
        FIELD(fields, s16, 0x10) = 2;
        FIELD(fields, s16, 0xE) = 0x48;
        FIELD(fields, s16, 0x12) = 1;
        FIELD(fields, s16, 4) = 0;
        FIELD(fields, s16, 6) = 0;
        FIELD(fields, s16, 0xA) = 0;
        FIELD(fields, s16, 0xC) = 0;
        FIELD(fields, u8, 0x40) = 0xC0;
        FIELD(fields, s8, 0x42) = 0;
        FIELD(fields, s8, 0x41) = 0;
        FIELD(fields, s16, 0x14) = arg2;
        dst = FIELD(obj, void *, 8);
        result = obj;
        *(Copy24 *)dst = *arg1;
    }
    return result;
}
