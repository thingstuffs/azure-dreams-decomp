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

void func_800BCDCC(Func800BF66CObject *arg0, s32 arg1, s32 arg2) {
    *(void **)((u8 *)arg0 - 0x10) = D_800BC990;
    arg0->field50 = 0;
    func_8004491C((u8 *)arg0 - 0x20, D_80045340);
    arg0->fieldA6 = 2;
    func_8008F074(arg0, arg1, D_800D20CC);
    func_8003DB94(arg2, D_800D211C[arg0->fieldA6], 0);
    arg0->field48 = D_800D212C;
}
