/* Relink of matched town/func_800B2670; every changed retail word is a paired relocation. */
#define D_800D15B8 D_800D161C
#include "common.h"

extern void textureBuildAHex48ByteTwoColorSwappedPatternBlocksReturnsBase(void *cursor, void *pattern_data);
extern s32 D_800D161C;

/* Initialize the record with global data and set its high flag bit. */
void func_800B18F8(void *record) {
    textureBuildAHex48ByteTwoColorSwappedPatternBlocksReturnsBase(record, &D_800D161C);
    *(u8 *) ((u8 *) record + 0x3C) = *(u8 *) ((u8 *) record + 0x3C) | 0x80;
}
