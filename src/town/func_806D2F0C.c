#include "common.h"

typedef struct S_8001670C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    s32 unk_04;
} S_8001670C_0;   /* index * 8 + records in func_8001670C */

typedef struct S_8001670C_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    s16 unk_18;
} S_8001670C_1;   /* ctx in func_8001670C */

typedef struct S_8001670C_2 {
    s16 unk_00;
    s16 unk_02;
} S_8001670C_2;   /* pair in func_8001670C */



extern s32 func_800161EC(u32, s32);
extern void func_80016510(s32, s32);
extern s32 func_80016654(s32);
extern void func_80016CCC(s32);

s32 func_8001670C(u32 records, s32 optional, u32 ctx, s32 arg3)
{
    s32 index;
    u32 pair;

    index = func_800161EC(records, arg3);
    pair = (((S_8001670C_0 *)(index * 8 + records))->unk_02 * 4)
         + ((S_8001670C_1 *)ctx)->unk_14;
    func_80016510(((S_8001670C_2 *)pair)->unk_00, ((S_8001670C_2 *)pair)->unk_02);
    if (optional != 0 && func_80016654(optional) != 0) {
        func_80016CCC(((S_8001670C_1 *)ctx)->unk_18);
    }
    return ((S_8001670C_0 *)(index * 8 + records))->unk_04;
}
