#include "common.h"

extern void textureBuildAHex48ByteTwoColorSwappedPatternBlocksReturnsBase(void *cursor, void *pattern_data);
extern s32 D_800D15B8;

/* Initialize the record with global data and set its high flag bit. */
void townInitializeItemMenuPanelRectangle(void *record) {
    textureBuildAHex48ByteTwoColorSwappedPatternBlocksReturnsBase(record, &D_800D15B8);
    *(u8 *) ((u8 *) record + 0x3C) = *(u8 *) ((u8 *) record + 0x3C) | 0x80;
}
