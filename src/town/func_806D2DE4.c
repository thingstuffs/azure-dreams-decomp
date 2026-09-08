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

/* Processes a selected nonzero table value and its owner's parameter if the check succeeds. */
s32 func_800165E4(S_800165E4_0 *tableOwner, s32 entryIndex) {
    u32 entryAddress;
    s16 entryValue;

    entryIndex *= 0x10;
    entryAddress = entryIndex + tableOwner->unk_10;
    entryValue = ((S_800165E4_1 *)((void *)entryAddress))->unk_0C;
    if (entryValue == 0) {
        return 0;
    }
    if (func_80016584() == 0) {
        return 0;
    }
    func_80016CCC(entryValue);
    func_80016D20(tableOwner->unk_18);
    ASM_USE(tableOwner);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    return 1;
}
