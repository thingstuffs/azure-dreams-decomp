#include "common.h"

#include "common.h"
#include "engine/menu.h"
#include "slus.h"
#include "slus/data.h"

extern u8 menu_leaf_template_6[12];
extern u8 held_item_kind_alias[12];

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
void initialize_gauge_menu_display_rows(S_800506BC_Obj *obj, S_800506BC_Ctx *ctx)
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

    obj->slot0->val = get_menu_count_template(6);
    obj->arr5[0]->val = (s32) menu_leaf_template_0;
    obj->arr5[1]->val = (s32) menu_leaf_template_1;
    obj->arr5[2]->val = (s32) menu_leaf_template_2;
    obj->arr5[3]->val = (s32) menu_leaf_template_3;
    obj->arr5[4]->val = (s32) menu_leaf_template_4;
    variant_entry = obj->slot18;
    if (held_item_kind_alias[0] == 0) {
        variant_data = menu_leaf_variant_template_0;
    } else {
        variant_data = menu_leaf_variant_template_1;
    }
    variant_entry->val = (s32) variant_data;
    obj->slot20->val = (s32) menu_leaf_template_5;
    obj->slot24->val = (s32) menu_leaf_template_6;

    ctx->flag10 = 1;
    ctx->flag14 = 1;
    reset_six_object_leaf_records(obj);

    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: slus/w_800506BC). */
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
