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

extern void func_800242C0(void) __attribute__((noreturn));
extern MainObj *func_8003FC64(u32);
extern void func_8003DB94(SubObj *, void *, s32);
extern void func_8004491C(MainObj *, void *);
extern u8 D_8002417C[];
extern u8 D_800DEC70[];
extern u8 D_80045340[];

MainObj *func_800241F8(s32 arg0, VecObj *arg1) {
    MainObj *obj = func_8003FC64(530);
    SubObj *sub;
    VecObj *vec;

    if (obj == 0) {
        register MainObj *rv ASM_REG("$2");

        rv = 0;
        ASM_TAILSLOT_PIN(rv);
        func_800242C0();
        return rv;
    }

    obj->callback = D_8002417C;
    sub = obj->sub;
    obj->arg0 = arg0;
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
    vec->unk2 = arg1->unk2;
    vec->unk6 = arg1->unk6;
    vec->unkA = arg1->unkA;

    return obj;
}

/* MECHANISM: retail parks a DEAD `move v0,zero` (the `return NULL` value of the
 * error path, which the noreturn callee never consumes) in the delay slot of the
 * ASPSX-converted tail `j func_800242C0`; gcc-2.8.1 DCEs that copy entirely and
 * maspsx's LEAD 18 conversion leaves a bare `nop` there. Materialising the zero
 * in a pinned $v0 and marking it with the sanctioned LEAD 28b ASM_TAILSLOT_PIN
 * makes maspsx's _rotate_dead_value_into_tail_j_delay (ARM B, empty-slot sink)
 * sink the copy into the nop slot -- the remaining 1-word substitution. Plain
 * ASM_KEEP is NOT enough: it keeps the copy but leaves it standing before the
 * `j`, costing an extra word (59/58, aligned 5). */
