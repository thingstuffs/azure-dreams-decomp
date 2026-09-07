#include "common.h"

#define FIELD(ptr, type_ptr, offset) (*(type_ptr)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern u16 D_80083780[];
extern s32 D_80170F68;
extern s8 D_80175DC1;

void func_801713F0(void) {
    void *obj;
    void *child;
    void *dst;

    obj = func_8003FC64(0x112);
    if (obj != 0) {
        child = FIELD(obj, void **, 0xC);
        FIELD(obj, s16 *, 0x38) = 0;
        FIELD(obj, s32 **, 0x10) = &D_80170F68;
        func_8004491C(obj, &D_80045340);
        dst = FIELD(obj, void **, 8);
        FIELD(child, u16 *, 0x14) = (u16)(FIELD(child, u16 *, 0x14) | 0x80);
        FIELD(dst, u16 *, 2) = D_80083780[1];
        FIELD(dst, u16 *, 6) = D_80083780[3];
        FIELD(dst, u16 *, 0xA) = D_80083780[5];
        FIELD(child, s16 *, 0x1E) = 0x1000;
        FIELD(child, s16 *, 0x1C) = 0x1000;
        FIELD(child, u8 *, 0xE) = 0x80;
        FIELD(child, u8 *, 0xD) = 0x80;
        FIELD(child, u8 *, 0xC) = 0x80;
        D_80175DC1 = 0;
    }
}
