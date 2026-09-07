#include "common.h"

#include "common.h"

extern s32 func_80049E6C(s32 a0);
extern void func_8004FFF4(void *arg0);

extern u8 D_80077E3C[12];
extern u8 D_80077E48[12];
extern u8 D_80077E54[12];
extern u8 D_80077E60[12];
extern u8 D_80077E6C[12];
extern u8 D_80077E78[12];
extern u8 D_80077E84[12];
extern u8 D_80077F80[12];
extern u8 D_80077F8C[12];
extern u8 D_80081485[12];

typedef struct S_800506BC_Mid {
    s32 val;
    void *subA;
    void *subB;
} S_800506BC_Mid;

typedef struct S_800506BC_Obj {
    S_800506BC_Mid *slot0;
    S_800506BC_Mid *arr5[5];
    S_800506BC_Mid *slot18;
    void *unk1C;
    S_800506BC_Mid *slot20;
    S_800506BC_Mid *slot24;
    S_800506BC_Mid *arr6[6];
} S_800506BC_Obj;

typedef struct S_800506BC_Ctx {
    u8 pad0[0x10];
    s32 flag10;
    s32 flag14;
    u8 pad18[0x2C - 0x18];
    s32 val2C;
} S_800506BC_Ctx;

void func_800506BC(S_800506BC_Obj *obj, S_800506BC_Ctx *ctx)
{
    s16 offB2;
    s16 offA;
    s16 offB;
    register s32 k ASM_REG("$5");   /* MATCH pin: slus-diff */
    s32 k2;
    S_800506BC_Mid **cursor;
    S_800506BC_Mid **cursor2;
    S_800506BC_Mid *temp;
    S_800506BC_Mid *slot18;
    u8 *choice;

    obj->slot0->val = func_80049E6C(6);
    obj->arr5[0]->val = (s32) D_80077E3C;
    obj->arr5[1]->val = (s32) D_80077E48;
    obj->arr5[2]->val = (s32) D_80077E54;
    obj->arr5[3]->val = (s32) D_80077E60;
    obj->arr5[4]->val = (s32) D_80077E6C;
    slot18 = obj->slot18;
    if (D_80081485[0] == 0) {
        choice = D_80077F80;
    } else {
        choice = D_80077F8C;
    }
    slot18->val = (s32) choice;
    obj->slot20->val = (s32) D_80077E78;
    obj->slot24->val = (s32) D_80077E84;

    ctx->flag10 = 1;
    ctx->flag14 = 1;
    func_8004FFF4(obj);

    k = 0xA;
    offB = 0;
    cursor = obj->arr6;
    offA = -0x28;
    *(s16 *) ((u8 *) obj->slot0->subA + 0xA) = 0;
    do {
        (*cursor)->val = ctx->val2C;
        k++;
        *(s16 *) ((u8 *) (*cursor)->subA + 0xA) = offA;
        temp = *cursor;
        cursor++;
        offA += 0x10;
        *(s16 *) ((u8 *) temp->subB + 0x2) = offB;
        offB += 0xC4;
    } while (k < 0x10);

    k2 = 1;
    offB2 = 0;
    cursor2 = obj->arr5;
    do {
        temp = *cursor2;
        cursor2++;
        k2++;
        *(s16 *) ((u8 *) temp->subB + 0x2) = offB2;
        offB2 += 0xC4;
    } while (k2 < 6);

    *(s16 *) ((u8 *) obj->slot20->subB + 0x6) = -4;
}
