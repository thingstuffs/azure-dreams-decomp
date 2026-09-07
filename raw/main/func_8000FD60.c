#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80022B20(void *arg0);
extern void func_80022B48(void *arg0, s32 arg1);
extern void func_80022C90(void *arg0, s32 arg1, void *arg2, void *arg3, s32 arg4);
extern void func_80022E08(void *arg0);
extern void func_800231E4(s32 arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern s32 func_8004B4A8(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern u8 D_80022CD8[];
extern u8 D_80027DD0[];
extern u8 D_800287E8[];

static __inline__ void set_handler(u8 *base) {
    register u8 *out ASM_REG("$2") = base;

    ASM_KEEP(out);
    FIELD(out, void *, 0x10) = D_80022CD8;
}

void func_80022D60(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    u8 *base;
    u8 *context;

    base = D_800287E8;
    context = base + 0x20;
    if (func_8004B4A8(base) == 0) {
        base = func_8003FE78(0, base, 0x27A);
        ASM_KEEP(base);
        func_8004491C(base, D_80027DD0);
        func_80022E08(context);
        return;
    }
    func_800231E4(FIELD(context, s32, 0xC) != 2);
    FIELD(base, u16, 0x1E) &= 0x7FFF;
    bzero(context, 0x9C8);
    func_80022B48(context, 7);
    {
        register u8 *body ASM_REG("$17") = context;

        ASM_KEEP(body);
        FIELD(base, void *, 0xC) = body + 0x8BC;
        FIELD(body, s32, 0x8C8) = func_80022B20(body + 0x8CC);
        func_80022C90(body, arg0, arg1, arg2, arg3);
    }
    set_handler(base);
}
