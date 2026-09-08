#include "common.h"

typedef struct Source Source;
typedef struct Spawned Spawned;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_80081484[];
extern Source *D_800814A8;
extern u8 D_800E3548[];

extern s32 func_8009A540(s32, s32, s32, s32);
extern Spawned *func_8009B25C(void *, s32, s32, s32);
extern void *func_8009B7B8(void);
extern s32 func_800A4298(Spawned *);
extern s32 func_800A70E4(s32, s32, s32);
extern Spawned *func_800A8E74(void *, s32, s32, void *, void *, s32);
extern void func_8009A3D0(s32, s32, s32);

struct Spawned {
    u8 unk00[0x13];
    u8 kind;
    s32 flags;
    u8 unk18[0x1c];
    s32 value34;
    u8 unk38[4];
    s32 value3c;
    u8 unk40[0x40];
    void *parent;
    u8 unk84[0x38];
    void *fieldbc;
};

struct Source {
    u8 unk00[0x2a];
    u16 index_field;
    u8 unk2c[0x5c];
    s16 height;
};

typedef struct Context {
    u8 unk00[8];
    s32 x;
    s32 y;
} Context;

void *func_8009B5AC(Source *arg0, s32 arg1, s32 arg2) {
    Source **p814a8;
    Spawned *obj;
    u8 *elem;
    s32 x;
    s32 y;
    s32 ry;
    s32 v1;
    s32 probe_result;
    s32 index;
    register s32 tail34 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 tail3c;
    s32 elem_value;
    register u8 *dead_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 tx ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 ty ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    index = (arg0->index_field >> 9) & 7;

    probe_result = func_8009A540(index,
                                 (s16)(arg1 - D_8006CCD8[index]),
                                 (s16)(arg2 - D_8006CCE8[index]),
                                 (s16)(arg0->height - 0x20));
    tx = (u16)arg1;
    ty = (u16)arg2;
    probe_result <<= 0x10;
    p814a8 = &D_800814A8;
    if (probe_result == 0) {
        goto ret_null;
    }

    obj = func_8009B25C(arg0, tx, ty,
                        arg0->height);
    if (obj != (void *)0) {
        if ((obj->flags & 0x80000) && arg0 == *p814a8) {
            D_80081484[0] = obj->kind;
            D_80081484[1] = 0x13;
            v1 = 0x14;
            if (obj->flags & 0x4000) {
                v1 = func_800A4298(obj);
                if ((s16)v1 < 0) {
                    v1 = 0x14;
                }
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            dead_state = D_80081484;
            dead_state[3] = (u8)v1;
            dead_state[2] = 0;
            dead_state = (u8 *)obj;
            ASM_TAILSLOT_PIN(dead_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            return func_8009B7B8();
        }
        return obj;
    }

    x = (s16)arg1;
    y = (s16)arg2;
    ry = (s16)func_800A70E4(x, y, arg0->height);
    if (ry < 0) {
        goto ret_null;
    }
    elem = &D_800E3548[ry * 4];
    obj = func_800A8E74(arg0,
                        ((Context *)((u8 *)arg0 - 0x20))->x,
                        ((Context *)((u8 *)arg0 - 0x20))->y,
                        arg0, elem, ry);
    if (obj == (void *)0) {
        return (void *)1;
    }
    obj->parent = arg0;
    if (arg0 == *p814a8) {
        elem_value = *(s32 *)elem;
        obj->fieldbc = D_80081484;
        *(s32 *)D_80081484 = elem_value;
    }
    elem[1] = 0;
    elem[0] = 0;
    func_8009A3D0(x, y, 0x800);
    dead_state = (u8 *)obj + 0x20;
    tail34 = obj->value34;
    tail3c = obj->value3c;
    tail34 |= 0x80000;
    tail3c |= 0x2000;
    ASM_USE_NV(dead_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    obj->value34 = tail34;
    obj->value3c = tail3c;
    return func_8009B7B8();

ret_null:
    return (void *)0;
}
