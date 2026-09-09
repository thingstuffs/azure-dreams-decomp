#include "common.h"

typedef struct SubObj {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 padF[3];
    s16 unk12;
    u16 unk14;
    u8 pad16[6];
    s16 unk1C;
    s16 unk1E;
} SubObj;

typedef struct VecObj {
    u16 pad0;
    u16 unk2;
    u16 pad4;
    u16 unk6;
    u16 pad8;
    u16 unkA;
} VecObj;

typedef struct MainObj {
    u8 pad0[8];
    VecObj *vec;
    SubObj *sub;
    void *callback;
    u8 pad14[0xC];
    s32 arg0;
} MainObj;

extern MainObj *func_8003FC64(u32);
extern void func_8003DB94(SubObj *, void *, s32);
extern void func_8004491C(MainObj *, void *);
extern u8 D_8002417C[];
extern u8 D_800DEC70[];
extern u8 D_80045340[];

/* Creates an object with initialized render state and a copy of the supplied vector. */
MainObj *func_800241F8(s32 object_value, VecObj *source_vec) {
    MainObj *obj = func_8003FC64(530);
    SubObj *sub;
    VecObj *vec;
    register MainObj *result ASM_REG("$2");

    if (obj == 0) {
        result = 0;
    } else {
        obj->callback = D_8002417C;
        sub = obj->sub;
        obj->arg0 = object_value;
        sub->b = 128;
        sub->g = 128;
        sub->r = 128;
        func_8003DB94(sub, D_800DEC70, 0);

        sub->unk1E = 4096;
        sub->unk1C = 4096;
        sub->unk12 = 0x7E09;
        sub->unk14 |= 0x100;
        func_8004491C(obj, D_80045340);

        vec = obj->vec;
        vec->unk2 = source_vec->unk2;
        vec->unk6 = source_vec->unk6;
        vec->unkA = source_vec->unkA;

        result = obj;
    }
    return result;
}
