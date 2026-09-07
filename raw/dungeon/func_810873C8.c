#include "common.h"

#define FIELD(obj, type, off) (*(type *)((u8 *)(obj) + (off)))

typedef struct {
    s32 w[6];
} Block24;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);

extern u8 D_80045340[9];
extern u8 D_80174A00[9];

s32 func_80174BC8(void *arg0, void *arg1, void *arg2)
{
    u16 query_result[3];
    void *obj;
    void *dst;
    void *prim;

    obj = func_8003FC64(0x312);
    if (obj != 0) {
        FIELD(obj, void *, 0x10) = D_80174A00;
        func_8004491C(obj, D_80045340);

        prim = FIELD(obj, void *, 0xC);
        FIELD(prim, s32, 0x28) = FIELD(arg2, s32, 0x28);
        FIELD(prim, u8, 0xE) = 0x80;
        FIELD(prim, u8, 0xD) = 0x80;
        FIELD(prim, u8, 0xC) = 0x80;
        FIELD(prim, s16, 0x1E) = 0x1000;
        FIELD(prim, s16, 0x1C) = 0x1000;
        FIELD(prim, u16, 6) = 1;
        FIELD(prim, u16, 0x14) |= 0xC;
        FIELD(prim, u16, 0x10) |= 0x20;
        func_80047784(prim, 0x37, 0);

        dst = FIELD(obj, void *, 8);
        *(Block24 *)dst = *(Block24 *)arg1;

        query_result[2] = 0;
        query_result[1] = 0;
        query_result[0] = 0;
        if (func_8003DE58(FIELD(arg2, s32, 8), arg2, query_result, 0) != 0) {
            FIELD(dst, u16, 2) += query_result[0];
            FIELD(dst, u16, 6) += query_result[1];
            FIELD(dst, u16, 0xA) += query_result[2];
        }
        return (s32)obj;
    }
    return 0;
}
