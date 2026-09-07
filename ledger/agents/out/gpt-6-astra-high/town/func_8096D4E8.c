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

/* Updates numbered slots and sprite display fields according to the object state. */
void func_80125980(TownObject *object)
{
    register TownObject *obj ASM_REG("$18") = object;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 slot_base;
    s32 entry_id;
    s32 slot_index;
    s32 row_offset;
    s32 column;
    s16 state;
    DisplayPair *display;
    SpriteFields *source_sprite;
    SpriteFields *hidden_sprite;

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
    row_offset = obj->row << 3;
    slot_base = (row_offset + column) * 3;
    slot_index = slot_base + 33;
    entry_id = (obj->digit << 4) + row_offset + column;
    if (func_80123200((u8)entry_id) != 0) {
        *obj->town->slots[slot_index] = D_80127B64;
        slot_index = slot_base + 34;
        *obj->town->slots[slot_index] = D_801269D0[(entry_id + 1) / 10];
        slot_index = slot_base + 35;
        *obj->town->slots[slot_index] = D_801269D0[(entry_id + 1) % 10];
    }
    goto common;

state_2:
    hidden_sprite = obj->town->display->src;
    hidden_sprite->f6 = 0;
    hidden_sprite->f4 = 0;
    goto end;

state_3:
    obj->town->display->src->f8 = D_80126B20[obj->row];
    obj->town->display->src->fA = D_80126B24[obj->index];

common:
    obj->town->display->dst->f6 = obj->town->display->src->f8;
    obj->town->display->dst->f8 = obj->town->display->src->fA;
    source_sprite = obj->town->display->src;
    source_sprite->f6 = 0x800;
    source_sprite->f4 = 0x800;

end:
    return;
}
