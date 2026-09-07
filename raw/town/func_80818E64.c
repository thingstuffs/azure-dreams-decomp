#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80046398[];

typedef struct Copy24 {
    s32 word[6];
} Copy24;

void func_80022E64(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *obj;
    void *dst;
    void *data;

    obj = func_8003FC64(0x136);
    if (obj != NULL) {
        func_8004491C(obj, D_80046398);
        dst = FIELD(obj, void *, 8);
        *(Copy24 *)dst = *(Copy24 *)arg0;
        data = FIELD(obj, void *, 0xC);
        FIELD(obj, s32, 0x20) = arg3;
        FIELD(obj, s32, 0x10) = arg2;
        FIELD(data, s16, 0x1C) = 0x1000;
        FIELD(data, s16, 0x1E) = 0x1000;
        FIELD(data, s16, 0x20) = 0x1000;
        FIELD(data, s16, 0x12) = 0;
        FIELD(data, s16, 0x14) = 0;
        FIELD(data, s16, 0x10) = 0;
        FIELD(data, s16, 0x16) = 0;
        FIELD(data, s16, 0x18) = 0;
        FIELD(data, s16, 0x1A) = 0;
        FIELD(data, s32, 0) = 0;
        FIELD(data, s8, 4) = 0;
        FIELD(data, s8, 5) = 0;
        FIELD(data, s16, 6) = 0xA;
        FIELD(data, s32, 0xC) = 0x808080;
        FIELD(data, s32, 8) = arg1;
    }
}
