#include "common.h"

typedef struct TownFlagWord {
    u8 pad00[3];
    u8 flags;
} TownFlagWord;

typedef struct TownColorNode {
    u8 pad00[4];
    s32 *color;
} TownColorNode;

typedef struct TownColorBank {
    u8 pad00[0x24];
    s32 *end[5];
    TownColorNode *layer0[5];
    TownColorNode *layer1[5];
    TownColorNode *layer2[5];
} TownColorBank;

typedef struct TownObject {
    u8 pad00[0x18];
    s32 palette_index;
    u8 pad1C[8];
    TownFlagWord *flag_words;
    u8 pad28[0xA4];
    TownColorBank *color_bank;
} TownObject;

extern s32 D_80080B54;
extern s32 D_800D15EC[];

/* Set a color slot's layer and end colors from the indexed flags and object palette. */
void func_800B09EC(TownObject *object, s32 index)
{
    s32 slot = index % 5;
    u8 flags = object->flag_words[index].flags;

    if (flags & 0x20) {
        object->color_bank->layer0[slot]->color[0] = 0x40C020;
        object->color_bank->layer1[slot]->color[0] = 0x40C020;
        object->color_bank->layer2[slot]->color[0] = 0x40C020;
        object->color_bank->end[slot][0] = D_800D15EC[object->palette_index];
        return;
    }

    if (flags & 0x80) {
        object->color_bank->layer0[slot]->color[0] = 0x505050;
        object->color_bank->layer1[slot]->color[0] = 0x505050;
        object->color_bank->layer2[slot]->color[0] = 0x505050;
        object->color_bank->end[slot][0] = 0;
        return;
    }

    object->color_bank->layer0[slot]->color[0] = D_80080B54;
    object->color_bank->layer1[slot]->color[0] = D_80080B54;
    object->color_bank->layer2[slot]->color[0] = D_80080B54;
    object->color_bank->end[slot][0] = 0;
}
