#include "common.h"

typedef struct {
    void *image;
    void **image_ref;
    s16 value;
    u16 unused;
} ImageEntry;

typedef struct {
    u32 pad0;
    u16 f4;
    u16 f6;
    s16 f8;
    u16 fA;
} SpriteFields;

typedef struct {
    u32 pad0;
    SpriteFields *src;
} DisplayPair;

typedef struct {
    void **slots[22];
} TownSlots;

typedef struct {
    u8 pad0[0x14];
    u8 index;
    u8 pad15[0x43];
    TownSlots *town;
} TownObject;

extern void func_80123ECC(void);

extern u8 D_80126A01[16];
extern u8 D_80126A0D[16];
extern void *D_80126988[4];
extern ImageEntry D_80126E98[];
extern u8 D_80128038[16];
extern DisplayPair *D_80129780[3];

void func_80124728(TownObject *obj)
{
    func_80123ECC();
    D_80126A0D[0] = D_80126A01[0];

    if (*(volatile u8 *)&obj->index == 0x31) {
        *obj->town->slots[21] = D_80128038;
    } else {
        *obj->town->slots[21] = D_80126988[obj->index >> 4];
    }

    D_80129780[0]->src->f8 =
        (s16)(((5 - D_80126E98[obj->index].value) * 6) + 0xD2);
}
