#include "common.h"

typedef struct Func800BFE50Object {
    u8 pad00[0x48];
    s32 field48;
    u8 pad4C[4];
    s32 field50;
    u8 pad54[0x68 - 0x54];
    s16 field68;
    u8 pad6A[0x95 - 0x6A];
    u8 field95;
    u8 pad96[0xA0 - 0x96];
    s32 fieldA0;
    s32 fieldA4;
} Func800BFE50Object;

extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void func_8008F074(void *, void *, void *);
extern u8 D_80045340[];
extern u8 D_800BCE78[];
extern u8 D_800D20CC[];
extern s32 D_800D2130;
extern u8 D_800E9E7C[];

/* Initialize the object and dispatch setup according to its state. */
void func_800BD5B0(Func800BFE50Object *object, s32 *params, void *dispatch_context) {
    u8 state;

    *(void **)((u8 *)object - 0x10) = D_800BCE78;
    object->field50 = 0;
    func_8004491C((u8 *)object - 0x20, D_80045340);

    object->fieldA0 = params[0];
    object->fieldA4 = params[1];
    state = object->field95;

    switch (state) {
    default:
        return;

    case 0:
        func_8008F074(object, params, D_800D20CC);
        func_8003DB94(dispatch_context, D_800E9E7C, 0);
        object->field68 = 0;
        object->field48 = D_800D2130;
        return;

    case 1:
        func_8003DB94(dispatch_context, D_800E9E7C, 0);
        object->field68 = 0;
        break;
    }
}
