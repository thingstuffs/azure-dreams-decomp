#include "common.h"

typedef struct ImageEntry {
    u8 pad0[8];
    s16 width;
    u8 padA[2];
} ImageEntry;

typedef struct SpriteFields {
    u32 pad0;
    u16 f4;
    u16 f6;
    u16 f8;
} SpriteFields;

typedef struct DisplayPair {
    u32 pad0;
    SpriteFields *src;
} DisplayPair;

typedef struct TownSlots {
    void **slots[8];
} TownSlots;

typedef struct TownObject {
    u8 pad0[0x13];
    volatile u8 digit;
    u8 pad14[0x44];
    TownSlots *town;
} TownObject;

extern void func_80123C18(TownObject *);
extern u8 D_80126A01;
extern void *D_80126988[4];
extern u8 D_80128038[16];
extern ImageEntry D_80126E98[];
extern DisplayPair *D_80129748;

/* Select the town object's digit graphic and adjust its display offset for width. */
void func_801247F8(TownObject *obj)
{
    func_80123C18(obj);
    D_80126A01 = 0;

    if (obj->digit == 0x31) {
        *obj->town->slots[7] = D_80128038;
    } else {
        *obj->town->slots[7] = D_80126988[obj->digit >> 4];
    }

    D_80129748->src->f8 = (5 - D_80126E98[obj->digit].width) * 6 + 0xD2;
}
