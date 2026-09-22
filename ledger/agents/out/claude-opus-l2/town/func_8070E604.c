#include "common.h"


extern void func_80016CC4(void);
extern void func_80016DBC(void);
extern void func_80019988(void);
extern s32 func_8001991C(s32, s32);
extern void func_8001A554(s32);
extern void func_8001A7AC(void);
extern s8 D_80016000[];

typedef struct S_80017604_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80017604_0;   /* *(void **)D_80016000 in func_80017604 */

typedef struct S_80017604_1 {
    u8 pad_00[0x2F8];
    void (*unk_2F8)(s32, s32);
} S_80017604_1;   /* ((S_80017604_0 *)(*(void **)D_80016000))->unk_20 in func_80017604 */


/* Run the three teardown passes; when the check fails, stop the scene object and report failure. */
s32 func_80017604(s32 kind, s32 value)
{
    s32 result;

    func_80016CC4();
    func_80016DBC();
    func_80019988();
    if (func_8001991C(kind, value) == 0) {
        func_8001A7AC();
        ((S_80017604_1 *)(((S_80017604_0 *)(*(void **)D_80016000))->unk_20))
            ->unk_2F8(0xE, 0x200);
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
