#include "common.h"


extern void func_8009A21C(s32, s32, s32);
extern void func_800A4300(void *, s32);
extern s16 func_800A71F4(void);

extern s32 D_800814A0;
extern s32 D_80082E80;
extern u16 D_80083460[];
extern s32 D_800E3548[];
typedef struct {
    u8 x;
    u8 y;
    u16 value2;
    u16 value4;
    u16 pad6;
    s32 value8;
} D_800E36C8_Entry;
extern D_800E36C8_Entry D_800E36C8[];
extern s32 D_800E3D7C;

typedef struct {
    u8 pad0[0x98];
    s32 field98;
    u8 pad9C[4];
    s16 fieldA0;
    u8 padA2[8];
    s16 fieldAA;
    s16 fieldAC;
    s16 fieldAE;
} FuncObj;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} FuncVec;

/* Ease the thrown object toward its landing tile; on arrival record it in the floor's item table and finish. */
void func_800A77AC(FuncObj *obj, FuncVec *pos, FuncVec *target) {
    s16 steps;
    u16 remaining;
    s32 slot;
    s32 x;
    s32 y;
    s32 z;
    u16 height;
    D_800E36C8_Entry *entry;

    x = pos->x;
    pos->x = x +
        (((((obj->fieldAA << 6) + 0x20) << 0x10) - x) /
         obj->fieldA0);
    y = pos->y;
    pos->y = y +
        (((((obj->fieldAC << 6) + 0x20) << 0x10) - y) /
         obj->fieldA0);
    z = pos->z;
    steps = obj->fieldA0;
    pos->z = z +
        (((obj->fieldAE << 0x10) - z) / steps);

    remaining = (u16)obj->fieldA0 - 1;
    obj->fieldA0 = remaining;
    if ((s16)remaining <= 0) {
        slot = func_800A71F4();
        if (slot >= 0) {
            D_800E3548[slot] = obj->field98;
            entry = &D_800E36C8[slot];
            entry->x = obj->fieldAA;
            entry->y = obj->fieldAC;
            height = obj->fieldAE;
            entry->value2 = height;
            entry->value4 = height;
            entry->value8 = target->z;
            func_8009A21C(obj->fieldAA, obj->fieldAC, 0x800);
            func_800A4300(&D_80082E80, D_800E3D7C);
        }
        D_80083460[5]--;
        /* the u16 two bytes BEFORE the object: a negative offset, which the field-typing
           pass (tools/xform/t4_fields.py) refuses to fold into a struct; a `_pre` struct
           spelling was tried here and costs 9 words (const-remat), so it stays an explicit cast */
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        D_800814A0 = D_800814A0 | 0x8000;
    }
}

/* MECHANISM: Preserve the seed's 0x20 frame, s0 object hold, s1 target hold, and v0 entry pin.
   The allocator call is zero-arity: the preceding signed divisor may remain incidental in a0,
   avoiding the false unsigned reload at word 36 and restoring retail's post-mflo nop. */
