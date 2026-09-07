#include "common.h"

typedef struct S_set_handler_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_set_handler_0;   /* out in set_handler */

typedef struct S_80022D60_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80022D60_0;   /* context in func_80022D60 */

typedef struct S_80022D60_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80022D60_1;   /* base in func_80022D60 */

typedef struct S_80022D60_2 {
    u8 pad_00[0x8C8];
    s32 unk_8C8;
} S_80022D60_2;   /* body in func_80022D60 */


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
    register u8 *out ASM_REG("$2") = base;   /* MATCH pin: retail register colouring depends on it */

    ASM_KEEP(out);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_set_handler_0 *)out)->unk_10 = D_80022CD8;
}

void func_80022D60(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    u8 *base;
    u8 *context;

    base = D_800287E8;
    context = base + 0x20;
    if (func_8004B4A8(base) == 0) {
        base = func_8003FE78(0, base, 0x27A);
        ASM_KEEP(base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8004491C(base, D_80027DD0);
        func_80022E08(context);
        return;
    }
    func_800231E4(((S_80022D60_0 *)context)->unk_0C != 2);
    ((S_80022D60_1 *)base)->unk_1E &= 0x7FFF;
    bzero(context, 0x9C8);
    func_80022B48(context, 7);
    {
        register u8 *body ASM_REG("$17") = context;   /* MATCH pin: retail keeps a computation the compiler would drop */

        ASM_KEEP(body);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_80022D60_1 *)base)->unk_0C = body + 0x8BC;
        ((S_80022D60_2 *)body)->unk_8C8 = func_80022B20(body + 0x8CC);
        func_80022C90(body, arg0, arg1, arg2, arg3);
    }
    set_handler(base);
}
