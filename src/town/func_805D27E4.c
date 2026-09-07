#include "common.h"

typedef struct S_800167E4_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800167E4_0;   /* arg0 in func_800167E4 */

typedef struct S_800167E4_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_800167E4_1;   /* town in func_800167E4 */

typedef struct S_800167E4_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_800167E4_2;   /* town2 in func_800167E4 */

typedef struct S_800167E4_3 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_800167E4_3;   /* ((S_800167E4_1 *)town)->unk_08 * 8 + ((S_800167E4_1 *)town)->unk_40 in func_800167E4 */

typedef struct S_800167E4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_800167E4_4;   /* index * 8 + ((S_800167E4_2 *)town2)->unk_40 in func_800167E4 */



extern s32 func_8001776C(void);
extern void func_80017E1C(void);
extern void func_80018308(void *, s32);
extern void func_800193E0(s32);
extern void func_80019458(s32);
extern s32 func_800194D8(s32);

extern s8 D_80016000[];
extern s16 D_80019676;
extern s32 D_80019AFC;

s32 func_800167E4(S_800167E4_0 *arg0, s32 arg1)
{
    S_800167E4_1 *town;
    s32 id;

    town = *(void **)D_80016000;
    id = arg0->unk_18;
    D_80019AFC = ((S_800167E4_3 *)(town->unk_08 * 8 + town->unk_40))->unk_04;

    if (func_800194D8(id) != 0) {
        {
            S_800167E4_2 *town2;
            s32 index;

            town2 = *(void **)D_80016000;
            index = town2->unk_08;
            ((S_800167E4_4 *)(index * 8 + town2->unk_40))->unk_04 = 0;
        }
        id = arg0->unk_18;
        D_80019AFC = 0;
        func_80019458(id);
    }

    if (func_8001776C() != 0 && func_800194D8(0x637) != 0) {
        if (func_800194D8(D_80019676) == 0 && D_80019AFC == 0) {
            func_80019458(0x637);
            func_80018308(arg0, arg1);
            return 1;
        }
    } else {
        func_800193E0(0x637);
    }

    func_80017E1C();
    return 0;
}

/* MECHANISM: The true-space function holds the town and status global pages in s1/s0,
   while arg0/arg1 remain live in s2/s3 across calls; an s32 named call argument fixes
   load/store scheduling, and a block-local town2/index scope fixes the v0/v1 coloring. */
