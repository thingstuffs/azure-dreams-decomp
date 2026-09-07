#include "common.h"

#define FIELD(base, type_ptr, offset) (*(type_ptr)((u8 *)(base) + (offset)))

extern void func_80016CC4(void);
extern void func_80016DBC(void);
extern void func_80019988(void);
extern s32 func_8001991C(s32, s32);
extern void func_8001A554(s32);
extern void func_8001A7AC(void);
extern s8 D_80016000[];

s32 func_80017604(s32 arg0, s32 arg1)
{
    s32 result;

    func_80016CC4();
    func_80016DBC();
    func_80019988();
    if (func_8001991C(arg0, arg1) == 0) {
        func_8001A7AC();
        FIELD(FIELD(*(void **)D_80016000, void **, 0x20),
              void (**)(s32, s32), 0x2F8)(0xE, 0x200);
        result = 0;
    } else {
        func_8001A554(0x931);
        result = 1;
    }

    return result;
}

/* MECHANISM: True-space naming makes the apparent func_80017684 jump a local
   epilogue edge; a shared result local preserves the retail failure-first CFG.
   Two call-spanning arguments naturally occupy s0/s1, while the wide array
   declaration forces D_80016000 through its retail hi/lo access. */
