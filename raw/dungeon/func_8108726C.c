#include "common.h"

#define FIELD(obj, type, off) (*(type *)((u8 *)(obj) + (off)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);

extern u8 D_80045340[9];
extern u8 D_80174A00[9];

s32 func_80174A6C(void *arg0, void *arg1, void *arg2)
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
        FIELD(prim, s16, 0x1E) = 0x2000;
        FIELD(prim, s16, 0x1C) = 0x2000;
        FIELD(prim, u16, 6) = 1;
        FIELD(prim, u16, 0x14) |= 0xC;
        FIELD(prim, u16, 0x10) |= 0x20;
        func_80047784(prim, 0x39, 0);

        {
            register void *query_arg ASM_REG("$5") = arg2;
            register u16 *query_out ASM_REG("$6");
            register s32 w0 ASM_REG("$2");
            register s32 w1 ASM_REG("$3");
            s32 w2;
            s32 w3;

            ASM_KEEP(query_arg);
            dst = FIELD(obj, void *, 8);
            ASM_KEEP(dst);
            query_out = query_result;
            ASM_KEEP(query_out);

            w0 = FIELD(arg1, s32, 0x00);
            w1 = FIELD(arg1, s32, 0x04);
            w2 = FIELD(arg1, s32, 0x08);
            w3 = FIELD(arg1, s32, 0x0C);
            FIELD(dst, s32, 0x00) = w0;
            FIELD(dst, s32, 0x04) = w1;
            FIELD(dst, s32, 0x08) = w2;
            FIELD(dst, s32, 0x0C) = w3;
            w0 = FIELD(arg1, s32, 0x10);
            w1 = FIELD(arg1, s32, 0x14);
            FIELD(dst, s32, 0x10) = w0;
            FIELD(dst, s32, 0x14) = w1;

            query_result[2] = 0;
            query_result[1] = 0;
            query_result[0] = 0;
            if (func_8003DE58(FIELD(query_arg, s32, 8), query_arg,
                              query_out, 0) != 0) {
                FIELD(dst, u16, 2) += query_result[0];
                FIELD(dst, u16, 6) += query_result[1];
                FIELD(dst, u16, 0xA) += query_result[2];
            }
        }
        return (s32)obj;
    }
    return 0;
}
