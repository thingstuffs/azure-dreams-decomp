#include "common.h"

typedef struct HalfFields {
    u8 pad0[4];
    u16 field4;
    u16 field6;
    u16 field8;
    u16 fieldA;
} HalfFields;

typedef struct Pair {
    u8 pad0[4];
    HalfFields *first;
    HalfFields *second;
} Pair;

typedef struct Pool {
    u32 *slots[97];
    Pair *pair;
} Pool;

typedef struct TownObject {
    u8 pad0[4];
    s16 state;
    u8 pad6[9];
    u8 digit;
    u8 side;
    u8 pad11[0x47];
    Pool *pool;
} TownObject;

extern u8 func_80123200(u8 value);
extern u32 D_801269D0[];
extern u16 D_80126B20[];
extern u16 D_80126B24;
extern u8 D_80127B64[];

/* Updates the object's number display and paired fields for its current state. */
void func_80125BB0(TownObject *obj)
{
    register TownObject *object ASM_REG("$18") = obj;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 side_offset;
    s32 entry_index;
    s32 slot_index;
    s32 index_base;
    s32 side_stride16;
    s32 side_stride8;
    Pair *pair;
    HalfFields *primary;
    HalfFields *secondary;

    switch (object->state) {
    case 1:
        index_base = 1 - object->side;
        side_stride8 = index_base << 3;
        side_stride16 = index_base << 4;
        side_offset = side_stride16 + side_stride8;
        slot_index = side_offset + 33;
        index_base = object->digit << 4;
        index_base = index_base + 1;
        entry_index = index_base - object->side;

        if (func_80123200((u8)entry_index) != 0) {
            s32 display_number = entry_index + 1;

            *object->pool->slots[slot_index] = (u32)D_80127B64;
            slot_index = side_offset + 34;
            *object->pool->slots[slot_index] = D_801269D0[display_number / 10];
            slot_index = side_offset + 35;
            *object->pool->slots[slot_index] = D_801269D0[display_number % 10];
        }
        break;

    case 2: {
        HalfFields *primary = object->pool->pair->first;
        primary->field6 = 0;
        primary->field4 = 0;
        return;
    }

    case 3:
        object->pool->pair->first->field8 = D_80126B20[object->side];
        object->pool->pair->first->fieldA = D_80126B24;
        break;

    default:
        return;
    }

    pair = object->pool->pair;
    primary = pair->first;
    secondary = pair->second;
    secondary->field6 = primary->field8;
    pair = object->pool->pair;
    primary = pair->first;
    secondary = pair->second;
    secondary->field8 = primary->fieldA;
    primary = object->pool->pair->first;
    primary->field6 = 0x800;
    primary->field4 = 0x800;
}
