#include "common.h"

typedef struct Func800BF66CObject {
    u8 pad00[0x48];
    s32 field48;
    u8 pad4c[4];
    s32 field50;
    u8 pad54[0x52];
    s16 fieldA6;
} Func800BF66CObject;

extern void func_8003DB94(s32, s32, s32);
extern void func_8004491C(void *, void *);
extern void func_8008F074(void *, s32, void *);
extern u8 D_80045340[];
extern u8 D_800BC990[];
extern u8 D_800D20CC[];
extern s32 D_800D211C[];
extern s32 D_800D212C;

/* Initialize the object state, motion, and animation. */
void func_800BCDCC(Func800BF66CObject *object, s32 motion, s32 anim) {
    *(void **)((u8 *)object - 0x10) = D_800BC990;
    object->field50 = 0;
    func_8004491C((u8 *)object - 0x20, D_80045340);
    object->fieldA6 = 2;
    func_8008F074(object, motion, D_800D20CC);
    func_8003DB94(anim, D_800D211C[object->fieldA6], 0);
    object->field48 = D_800D212C;
}
