#include "common.h"

typedef struct SubA {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
} SubA;

typedef struct SubB {
    u8 pad0[6];
    s16 f6;
    void *f8;
    u32 fC;
    u8 pad10[4];
    u16 f14;
    u8 pad16[6];
    s16 f1C;
    s16 f1E;
} SubB;

typedef struct Obj {
    u8 pad0[8];
    SubA *subA;
    SubB *subB;
    void *state;
} Obj;

typedef struct Aux {
    void *f0;
    u8 pad4[6];
    s16 fA;
    u8 padC[2];
    s16 fE;
    u8 pad10[2];
    s16 f12;
    u8 pad14[2];
    u16 f16;
    u8 pad18[2];
    u16 f1A;
    u8 pad1C[0xC];
    void *f28;
    void *f2C;
} Aux;

typedef struct D_80083780_t {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
    u8 pad8[2];
    u16 fA;
} D_80083780_t;

extern s32 func_8003FA44(s32);
extern Obj *func_8003FC64(s32);
extern void func_8004491C(Obj *, void *);
extern void func_800C77D0(Obj *, SubA *, s32, s16);
extern s32 func_8004A658(u8, u8);
extern void func_8003DB94(SubB *, void *, s32);
extern void *func_800BA110();
extern void *func_800BA1D0();
extern void *func_800BA224();
extern void func_800BA2A0(void);
extern void func_800BA308(void);
extern s32 func_800BA33C(s32);
extern void func_800B1768(s32, s32, s32, s32, s32, s32);
extern void func_800B1B10(void *, s32, s32, s32, s32, s32);

extern s32 D_80045340;
extern u8 D_80045C34[];
extern u8 D_80079444[];
extern void *D_800814A8;
extern s32 D_80083460;
extern D_80083780_t D_80083780;
extern u8 D_800B9A78[];
extern s16 D_800DCE66[5];
extern u8 D_800DDC40[];
extern u8 D_800DF368[];
extern u8 *D_800E3D7C[];



typedef struct S_800BA074_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800BA074_0;   /* current in func_800BA074 */

typedef struct S_800BA074_1 {
    u8 pad_00[0x3D7C];
    u8 * unk_3D7C;
} S_800BA074_1;   /* page in func_800BA074 */

typedef struct S_800BA074_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    s32 unk_B0;
} S_800BA074_2;   /* ((S_800BA074_1 *)page)->unk_3D7C in func_800BA074 */

void *func_800BA074(u8 *arg0) {
    Obj *objects[3];
    u8 *input;
    D_80083780_t *data;
    Obj **slot;
    s32 i;
    register u8 *page ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 two;

    input = arg0;

    if (func_8003FA44(3) == 0) {
        return 0;
    }

    i = 0;
    two = 2;
    data = &D_80083780;
    page = (u8 *)0x800E0000;
    slot = objects;
loop:
    *slot = func_8003FC64(0x12);
    if (*slot != 0) {
        SubA *subA;
        SubB *subB;

        (*slot)->state = D_800B9A78;
        if (i == two) {
            func_8004491C(objects[2], D_80045C34);
            goto after_call;
        }

        {
            Obj *callObj;
            void *stateDef;
            callObj = *slot;
            stateDef = &D_80045340;
            func_8004491C(callObj, stateDef);
        }
    after_call:
        subA = (*slot)->subA;
        subA->f2 = data->f2;
        subA->f6 = data->f6;
        subB = (*slot)->subB;
        subB->f1E = 0x1000;
        subB->f1C = 0x1000;
        subB->fC = 0x2C808080;
        subB->f6 = 4;

        if (i == 0) {
            func_800C77D0(objects[0], subA, 8, D_800DCE66[0]);
            subB->f8 = (void *)func_8004A658(input[1], input[0]);
        } else if (i == 1) {
            subB->f8 = D_800DF368;
        } else {
            func_8003DB94(subB, D_80079444, 0);
            subB->f14 |= 0xC;
        }
        {
            Obj *current;
            Aux *aux;

            current = *slot;
            aux = (Aux *)((u8 *)current + 0x20);
            aux->fA = data->fA - D_800DDC40[0];
            ((S_800BA074_0 *)current)->unk_20 = &D_800814A8;
            aux->f12 = i;
            aux->f16 = subA->f2;
            aux->f1A = subA->f6;
            ASM_USE_G_NV(subA);   /* MATCH pin: retail register colouring depends on it */
            if (i != 0) {
                aux->f28 = objects[0];
            } else {
                aux->f2C = input;
            }
            if (func_800BA33C(((S_800BA074_2 *)(((S_800BA074_1 *)page)->unk_3D7C))->unk_AC) != 0) {
                aux->fE = 8;
                aux->f0 = ((S_800BA074_1 *)page)->unk_3D7C + 0xAC;
                if (aux->f12 == two) {
                    subB->fC = 0x101080;
                }
                goto next;
            }
            if (func_800BA33C(((S_800BA074_2 *)(((S_800BA074_1 *)page)->unk_3D7C))->unk_B0) != 0) {
                aux->fE = 8;
                aux->f0 = ((S_800BA074_1 *)page)->unk_3D7C + 0xB0;
                if (aux->f12 == two) {
                    subB->fC = 0x801010;
                }
            }
        }
    }

next:
    i++;
    slot++;
    if (i < 3) {
        goto loop;
    }

    {
        u8 *fieldPtr = (u8 *)&D_80083460;
        *(u16 *)(fieldPtr + 0xA) += 1;
    }
    func_800B1768(0, 0x27, 0x40, 0x209, 0, 0);
    func_800B1B10(input, 0x4C, 0x50, 0x200, 0, 2);
    return objects[0];
}
