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

/* Initialize entry data, enable context flags, and set subobject offsets. */
void func_800506BC(S_800506BC_Obj *obj, S_800506BC_Ctx *ctx)
{
    s16 fixed_offset;
    s16 layout_offset;
    s16 shared_offset;
    s32 shared_index;
    s32 fixed_index;
    S_800506BC_Mid **shared_entry;
    S_800506BC_Mid **fixed_entry;
    S_800506BC_Mid *entry;
    S_800506BC_Mid *variant_entry;
    u8 *variant_data;

    obj->slot0->val = func_80049E6C(6);
    obj->arr5[0]->val = (s32) D_80077E3C;
    obj->arr5[1]->val = (s32) D_80077E48;
    obj->arr5[2]->val = (s32) D_80077E54;
    obj->arr5[3]->val = (s32) D_80077E60;
    obj->arr5[4]->val = (s32) D_80077E6C;
    variant_entry = obj->slot18;
    if (D_80081485[0] == 0) {
        variant_data = D_80077F80;
    } else {
        variant_data = D_80077F8C;
    }
    variant_entry->val = (s32) variant_data;
    obj->slot20->val = (s32) D_80077E78;
    obj->slot24->val = (s32) D_80077E84;

    ctx->flag10 = 1;
    ctx->flag14 = 1;
    func_8004FFF4(obj);

    do {
        shared_index = 0xA;
    } while (0);
    shared_offset = 0;
    shared_entry = obj->arr6;
    layout_offset = -0x28;
    *(s16 *) ((u8 *) obj->slot0->subA + 0xA) = 0;
    do {
        (*shared_entry)->val = ctx->val2C;
        shared_index++;
        *(s16 *) ((u8 *) (*shared_entry)->subA + 0xA) = layout_offset;
        entry = *shared_entry;
        shared_entry++;
        layout_offset += 0x10;
        *(s16 *) ((u8 *) entry->subB + 0x2) = shared_offset;
        shared_offset += 0xC4;
    } while (shared_index < 0x10);

    fixed_index = 1;
    fixed_offset = 0;
    fixed_entry = obj->arr5;
    do {
        entry = *fixed_entry;
        fixed_entry++;
        fixed_index++;
        *(s16 *) ((u8 *) entry->subB + 0x2) = fixed_offset;
        fixed_offset += 0xC4;
    } while (fixed_index < 6);

    *(s16 *) ((u8 *) obj->slot20->subB + 0x6) = -4;
}
