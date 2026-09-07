#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[2];
    u16 fieldA;
    u8 padC[0x18];
    u8 field24;
    u8 field25;
    u8 pad26[6];
    void *field2C;
} Func812A5000Child;

typedef struct {
    u8 pad0[8];
    Func812A5000Child *child1;
    Func812A5000Child *child0;
    void *field10;
} Func812A5000Parent;

typedef struct {
    u8 pad0[0x13];
    u8 field13;
    u32 field14;
    u8 pad18[4];
    u32 field1C;
    u8 pad20[0xA];
    s16 field2A;
    u8 pad2C[0x60];
    void *field8C;
    u8 pad90[2];
    s16 field92;
    u8 pad94[6];
    u8 field9A;
    u8 pad9B;
    s8 field9C;
} Func812A5000Entity;

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80175C30[];
extern u8 D_80171FA4[];
void *func_8003FD64();                 /* extern */
M2C_UNK func_8004491C();                /* extern */
M2C_UNK func_800A9C18(); /* extern */
M2C_UNK func_800AA36C(); /* extern */
s32 func_800F6D28();                          /* extern */
extern volatile void *D_800FBE1C[];
extern u8 D_80170A4C[];

void *func_812A50AC(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    Func812A5000Parent *parent;
    Func812A5000Child *child0;
    Func812A5000Child *child1;
    Func812A5000Entity *entity;

    entity = NULL;
    parent = func_8003FD64(0x112, D_80083498);
    if (parent != NULL) {
        if (D_800FBE1C[0] == 0) {
            D_800FBE1C[0] = parent;
        }
        entity = (Func812A5000Entity *)((u8 *)parent + 0x20);
        parent->field10 = D_80170A4C;
        entity->field13 = 0x39;
        func_8004491C(parent, D_80045340);
        child0 = parent->child0;
        child1 = parent->child1;
        child0->field24 = arg1;
        child0->field25 = arg2;
        child0->field2C = D_80175C30;
        child1->field2 = (s16)((child0->field24 << 6) + 0x20);
        child1->field6 = (s16)((child0->field25 << 6) + 0x20);
        child1->fieldA = arg3;
        entity->field2A = (s16)(func_800F6D28(child1) << 9);
        entity->field13 = 2;
        entity->field14 |= 0x6000;
        entity->field1C |= 0x6000;
        func_800A9C18(parent, child1, child0, arg0);
        entity->field9A = 0xFF;
        entity->field9C = -1;
        entity->field8C = D_80171FA4;
        entity->field92 = -0x20;
        entity->field13 = 0x39;
        entity->field1C |= 0x40000;
        func_800AA36C(entity, child1, child0, entity);
    }
    return entity;
}
