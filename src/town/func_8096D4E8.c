#include "common.h"

typedef struct SpriteFields {
    u32 pad0;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
} SpriteFields;

typedef struct DisplayPair {
    u32 pad0;
    SpriteFields *src;
    SpriteFields *dst;
} DisplayPair;

typedef struct TownSlots {
    void **slots[97];
    DisplayPair *display;
} TownSlots;

typedef struct TownObject {
    u8 pad0[4];
    s16 state;
    u8 pad6[9];
    u8 digit;
    u8 row;
    u8 index;
    u8 column;
    u8 pad13[0x45];
    TownSlots *town;
} TownObject;

extern u8 func_80123200(u32);
extern void *D_801269D0[10];
extern u16 D_80126B20[2];
extern u16 D_80126B24[8];
extern u8 D_80127B64[16];

void func_80125980(TownObject *arg0)
{
    register TownObject *obj ASM_REG("$18") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 block;
    s32 value;
    s32 slot;
    s32 row8;
    s32 column;
    s16 state;
    DisplayPair *display;
    SpriteFields *source;
    SpriteFields *hide;

    state = obj->state;
    if (state == 2) {
        goto state_2;
    }
    if (state < 3) {
        if (state == 1) {
            goto state_1;
        }
        goto end;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_1:
    column = obj->column;
    row8 = obj->row << 3;
    block = (row8 + column) * 3;
    slot = block + 33;
    value = (obj->digit << 4) + row8 + column;
    if (func_80123200((u8)value) != 0) {
        *obj->town->slots[slot] = D_80127B64;
        slot = block + 34;
        *obj->town->slots[slot] = D_801269D0[(value + 1) / 10];
        slot = block + 35;
        *obj->town->slots[slot] = D_801269D0[(value + 1) % 10];
    }
    goto common;

state_2:
    hide = obj->town->display->src;
    hide->f6 = 0;
    hide->f4 = 0;
    goto end;

state_3:
    obj->town->display->src->f8 = D_80126B20[obj->row];
    obj->town->display->src->fA = D_80126B24[obj->index];

common:
    obj->town->display->dst->f6 = obj->town->display->src->f8;
    obj->town->display->dst->f8 = obj->town->display->src->fA;
    source = obj->town->display->src;
    source->f6 = 0x800;
    source->f4 = 0x800;

end:
    return;
}
