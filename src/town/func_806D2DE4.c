#include "common.h"

typedef struct S_800165E4_0 {
    u8 pad_00[0x10];
    u32 unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} S_800165E4_0;   /* arg0 in func_800165E4 */

typedef struct S_800165E4_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_800165E4_1;   /* (void *)entry in func_800165E4 */



extern s32 func_80016584();
extern void func_80016CCC();
extern void func_80016D20();

s32 func_800165E4(S_800165E4_0 *arg0, s32 arg1) {
    u32 entry;
    s16 value;

    arg1 *= 0x10;
    entry = arg1 + arg0->unk_10;
    value = ((S_800165E4_1 *)((void *)entry))->unk_0C;
    if (value == 0) {
        return 0;
    }
    if (func_80016584() == 0) {
        return 0;
    }
    func_80016CCC(value);
    func_80016D20(arg0->unk_18);
    ASM_USE(arg0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    return 1;
}
