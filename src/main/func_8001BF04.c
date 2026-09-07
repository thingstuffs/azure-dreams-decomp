#include "common.h"

extern void func_80402A1C(void *arg0, void *arg1);
extern void func_80402BE0(void *arg0);
extern void func_8040274C(void *arg0);
extern void func_804027F8(void);
extern void func_8040293C(void);
extern u8 D_80408ADF[];

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
} Struct8001BF04;

void func_8001BF04(Struct8001BF04 *arg0) {
    s32 var_a0;
    s32 idx;

    func_80402A1C((void *)((s32) arg0 + 0x24), arg0);
    func_80402BE0(arg0);
    idx = arg0->unk08 * 4;
    arg0->unk00 = D_80408ADF[idx];
    func_8040274C(arg0);
    var_a0 = (s32) func_804027F8;
    if (arg0->unk0C == 2) {
        var_a0 = (s32) func_8040293C;
    }
    *(s32 *)((s32) arg0 - 0x10) = var_a0;
}
