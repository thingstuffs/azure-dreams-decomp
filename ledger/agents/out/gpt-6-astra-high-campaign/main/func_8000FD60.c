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
extern void func_800231E4(s32 arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern s32 func_8004B4A8(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern u8 D_80022CD8[];
extern u8 D_80027DD0[];
extern u8 D_800287E8[];

static __inline__ void set_handler(u8 *base) {
    register u8 *handler_base ASM_REG("$2") = base;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(handler_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ((S_set_handler_0 *)handler_base)->unk_10 = D_80022CD8;
}

/* Creates or resets the entity, initializes its nodes and record, and installs its handler. */
void func_80022D60(s32 value_14, void *entry_index, void *value_0c, s32 value_20) {
    u8 *base;
    u8 *context;

    base = D_800287E8;
    context = base + 0x20;
    if (func_8004B4A8(base) == 0) {
        base = func_8003FE78(0, base, 0x27A);
        func_8004491C(base, D_80027DD0);
    } else {
        func_800231E4(((S_80022D60_0 *)context)->unk_0C != 2);
        ((S_80022D60_1 *)base)->unk_1E &= 0x7FFF;
        bzero(context, 0x9C8);
    }
    func_80022B48(context, 7);
    {
        u8 *body = context;

        ((S_80022D60_1 *)base)->unk_0C = body + 0x8BC;
        ((S_80022D60_2 *)body)->unk_8C8 = func_80022B20(body + 0x8CC);
        func_80022C90(body, value_14, entry_index, value_0c, value_20);
    }
    set_handler(base);
}
