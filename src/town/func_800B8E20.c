#include "common.h"


typedef s32 M2C_UNK;


void *textureBuildAHex48ByteTwoColorSwappedPatternBlocksReturnsBase();

typedef struct S_800B6580_0 {
    u8 pad_00[0x3C];
    u8 unk_3C;
} S_800B6580_0;   /* arg0 in townSetMonsterStatusPanelHeight */

/* Applies a rectangle to the object and sets its high flag. */
void townSetMonsterStatusPanelHeight(S_800B6580_0 *object, s16 height) {
    s16 rectangle[4];

    rectangle[0] = 0xC6;
    rectangle[1] = 6;
    rectangle[3] = height;
    rectangle[2] = 0x76;
    textureBuildAHex48ByteTwoColorSwappedPatternBlocksReturnsBase(object, &rectangle[0]);
    object->unk_3C = (u8)(object->unk_3C | 0x80);
}
