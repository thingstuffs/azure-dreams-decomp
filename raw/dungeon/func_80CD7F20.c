#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_80158F20[];
extern u8 D_8015BB98[];
extern u8 D_8015E2C8[];
extern u8 D_8015E300[];
extern u8 D_8015E328[];
extern u8 D_8015E360[];

void func_8015B720(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *obj0 ASM_REG("$17") = arg0;
    register void *obj2 ASM_REG("$16") = arg2;
    register void *obj3 ASM_REG("$18") = arg3;
    void *kind;
    register u8 *table ASM_REG("$5");
    register u8 *entry ASM_REG("$2");
    register void *call_obj ASM_REG("$4");
    s32 index;

    if (func_800AC82C(arg0, arg1, arg2, arg3) != 0) {
        if ((func_800AD9B4(obj2, obj3) << 0x10) > 0) {
            if (*(u8 *)((u8 *)obj0 + 0xA7) != 0) {
                *(void **)((u8 *)obj0 + 0x8C) = D_8015BB98;
            } else {
                *(void **)((u8 *)obj0 + 0x8C) = D_80158F20;
            }
        }
        return;
    }

    kind = *(void **)((u8 *)obj2 + 0x2C);
    if (kind == D_8015E300) {
        if (*(s32 *)((u8 *)obj3 + 0x1C) & 0x208) {
            return;
        }
        table = D_8015E2C8;
    } else if (kind == D_8015E360) {
        if (*(s32 *)((u8 *)obj3 + 0x1C) & 0x208) {
            return;
        }
        table = D_8015E328;
    } else {
        return;
    }

    *(void **)((u8 *)obj2 + 0x2C) = table;
    index = (D_80083228 + *(s16 *)((u8 *)obj3 + 0x2A) + 0x100) >> 9;
    call_obj = obj2;
    ASM_KEEP(call_obj);
    entry = (u8 *)((u32)(index & 7) + (u32)table);
    ASM_KEEP(entry);
    func_80047784(call_obj, *entry, 0);
}
