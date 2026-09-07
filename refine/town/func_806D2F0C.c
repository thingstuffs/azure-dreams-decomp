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

/* Processes the selected record's pair and optional context action, then returns the record's value. */
s32 func_8001670C(u32 records, s32 condition_arg, u32 context, s32 record_selector)
{
    s32 record_index;
    u32 pair;

    record_index = func_800161EC(records, record_selector);
    pair = (((S_8001670C_0 *)(record_index * 8 + records))->unk_02 * 4)
         + ((S_8001670C_1 *)context)->unk_14;
    func_80016510(((S_8001670C_2 *)pair)->unk_00, ((S_8001670C_2 *)pair)->unk_02);
    if (condition_arg != 0 && func_80016654(condition_arg) != 0) {
        func_80016CCC(((S_8001670C_1 *)context)->unk_18);
    }
    return ((S_8001670C_0 *)(record_index * 8 + records))->unk_04;
}
