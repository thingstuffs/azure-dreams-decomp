#include "common.h"

typedef struct S_800238D4_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_800238D4_0;   /* base in func_800238D4 */

typedef struct S_800238D4_1 {
    u8 pad_00[0x19C];
    s32 unk_19C;
} S_800238D4_1;   /* work in func_800238D4 */



extern s32 func_8004B4A8(void *arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_80023A00(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern void func_800237EC(void *arg0, s32 arg1);
extern s32 func_800237C4(void *arg0);
extern void func_80023894(void *arg0, s32 arg1);
extern void func_80023258(void *arg0);

extern u8 D_80027DD0[];
extern u8 D_800291D0[];

void *func_800238D4(s32 arg0)
{
    u8 *base;
    u8 *work;

    base = D_800291D0;
    work = D_800291D0 + 0x20;
    if (func_8004B4A8(base) == 0) {
        base = func_8003FE78(0, base, 0x112);
        func_8004491C(base, D_80027DD0);
    } else {
        func_80023A00(base);
        ((S_800238D4_0 *)base)->unk_1E &= 0x7FFF;
        bzero(work, 0x428);
    }

    func_800237EC(work, 0x12);
    ((S_800238D4_0 *)base)->unk_0C = work + 0x190;
    ((S_800238D4_1 *)work)->unk_19C = func_800237C4(work + 0x1A0);
    func_80023894(work, arg0);
    *(void (**)(void *))(base + 0x10) = func_80023258;
    func_80023258(work);
    return base;
}
