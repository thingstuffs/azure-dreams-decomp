#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct CopyFields {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
} CopyFields;

typedef struct ConfigFields {
    u8 pad0[8];
    void * volatile field8;
    volatile u32 fieldC;
    volatile u16 field10;
    u16 field12;
    volatile u16 field14;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
} ConfigFields;

typedef struct TailFields {
    u8 pad0[0x14];
    u32 field14;
    u8 pad18[0x34];
    u16 field4C;
    u8 pad4E[0x1A];
    u32 field68;
} TailFields;

typedef struct EntityFields {
    u8 pad0[8];
    CopyFields *field8;
    ConfigFields *fieldC;
    void *field10;
    u8 pad14[0xC];
    TailFields tail;
} EntityFields;

extern u8 D_80045340[];
extern u8 D_800C0404[];
extern u8 D_800DF4A4[];

extern EntityFields *func_8003FD64(s32, EntityFields *);
extern void func_80044A50(EntityFields *);
extern void func_800BC318(EntityFields *);
extern void func_8004491C(EntityFields *, void *);

void *func_800C07AC(EntityFields *arg0) {
    EntityFields *obj;
    CopyFields *src;
    CopyFields *dst;
    ConfigFields *cfg;
    TailFields *objTail;
    TailFields *argTail;
    register u16 flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u16 size;

    obj = func_8003FD64(2, arg0);
    if (obj != NULL) {
        func_80044A50(arg0);
        func_800BC318(arg0);
        obj->field10 = D_800C0404;
        func_8004491C(obj, D_80045340);

        src = arg0->field8;
        dst = obj->field8;
        dst->field2 = src->field2;
        dst->field6 = src->field6;
        dst->fieldA = src->fieldA;

        cfg = obj->fieldC;
        cfg->field10 = 0x20;
        cfg->field8 = D_800DF4A4;
        size = 0x1000;
        cfg->field1E = size;
        cfg->field1C = size;
        argTail = &arg0->tail;
        flags = cfg->field14;
        cfg->fieldC = 0x808080;
        cfg->field14 = flags | 0xC;
        objTail = &obj->tail;
        objTail->field4C = 0x10;
        objTail->field68 = argTail;
        argTail->field14 |= 0x100000;
    }
    return obj;
}
