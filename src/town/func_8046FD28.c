#include "common.h"
#include "m2c_compat.h"

s32 func_8001628C();           /* extern */
s32 func_80017E98(s32, M2C_UNK);                                /* extern */
s32 func_80019A04();         /* extern */
s32 func_80019ABC(); /* extern */
s32 func_8001A510();                         /* extern */
extern M2C_UNK D_8001A97C;
extern M2C_UNK D_8001B1FC;
extern M2C_UNK D_8001B63C;
extern M2C_UNK D_8001CDF2;

s32 func_80016D28(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 var_s1;

    if (func_80017E98(arg0, arg1) != 0) {
        s32 page;

        page = (s32) 0x80020000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        return page - 0x49C4;
    }
    var_s1 = func_80019ABC(&D_8001A97C, &D_8001B1FC, arg0, arg2);
    if (func_80019A04(&D_8001A97C, arg0, arg2) != 0) {
        if (func_8001A510(0x799) != 0) {
            s32 page;

            page = (s32) 0x80020000;
            ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
            var_s1 = page - 0x320E;
        } else {
            var_s1 = func_8001628C(arg0, arg1, arg2);
        }
    }
    return var_s1;
}

/* MECHANISM: The true-space name makes the in-row targets local CFG joins instead of phantom calls.
   Short-lived guarded v0 page carriers produce the split 0x80020000/addiu constants in delay slots.
   One s1 result live range across both arms preserves the 0x28 frame and fallback copy/join. */
