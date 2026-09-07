#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_8004B248();
M2C_UNK func_80053DA8();
M2C_UNK func_80064F00();
M2C_UNK func_80064F20();
M2C_UNK func_80123130();
s32 func_801264AC();
M2C_UNK func_80126620();

extern M2C_UNK D_8004CAA0;
extern s8 D_80080A84;
extern int D_800814A0;
extern s32 D_80083200;
extern M2C_UNK D_80126704;

void func_801267B8(void) {
    s32 work;
    s32 global_flags;
    u16 object_flags;
    void *obj;

    obj = func_8003FC64(0);
    work = (u8 *)obj + 0x20;
    if (obj != NULL) {
        if (func_801264AC(work) != 0) {
            D_80080A84 = 1;
            func_80123130();
            FIELD(obj, void *, 0xC) = (u8 *)obj + 0x68;
            func_80126620(work);
            func_8004491C(obj, &D_8004CAA0);
            FIELD(obj, M2C_UNK *, 0x10) = &D_80126704;
            D_80083200 = 0x200;
            func_80064F20(0x200);
            func_80064F00(0xA0, 0x78);
            func_80053DA8(0x701);
            return;
        }
        func_8004B248((u8 *)obj + 0x7C);
        global_flags = D_800814A0;
        object_flags = FIELD(obj, u16, 0x1E);
        FIELD(obj, u16, 0x1E) = object_flags | 0x8000;
        D_800814A0 = global_flags | 0x8000;
    }
}
