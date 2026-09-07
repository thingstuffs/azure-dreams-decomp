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

void func_80125BB0(TownObject *obj)
{
    register TownObject *object ASM_REG("$18") = obj;
    s32 offset;
    s32 value;
    s32 slot;
    s32 temp;
    s32 hi;
    s32 lo;
    Pair *pair;
    HalfFields *fields;
    HalfFields *other;

    switch (object->state) {
    case 1:
        temp = 1 - object->side;
        lo = temp << 3;
        hi = temp << 4;
        offset = hi + lo;
        slot = offset + 33;
        temp = object->digit << 4;
        temp = temp + 1;
        value = temp - object->side;

        if (func_80123200((u8)value) != 0) {
            s32 number = value + 1;

            *object->pool->slots[slot] = (u32)D_80127B64;
            slot = offset + 34;
            *object->pool->slots[slot] = D_801269D0[number / 10];
            slot = offset + 35;
            *object->pool->slots[slot] = D_801269D0[number % 10];
        }
        break;

    case 2: {
        HalfFields *f2 = object->pool->pair->first;
        f2->field6 = 0;
        f2->field4 = 0;
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
    fields = pair->first;
    other = pair->second;
    other->field6 = fields->field8;
    pair = object->pool->pair;
    fields = pair->first;
    other = pair->second;
    other->field8 = fields->fieldA;
    fields = object->pool->pair->first;
    fields->field6 = 0x800;
    fields->field4 = 0x800;
}
