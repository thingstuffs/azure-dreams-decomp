#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"

extern void func_80404C44(CardBackgroundBody *object, ObjectNodeHeader *owner);

typedef struct {
    u8 pad_00[4];
    s32 field_04;
    u8 pad_08[0x214];
    s32 field_21C;
    struct CardDevMenuEntry **entry_table;
} Obj;

typedef struct {
    u8 pad_00[0x0C];
    MenuDisplayNode *field_0C;
    void *field_10;
    u8 pad_14[0x0A];
    u16 flags;
    Obj obj;
} Root;

/* This unit declares the static node through its entry-table slot. */
extern Root card_background_object;

/* Create or reset the card background object and initialize its callback. */
void * init_card_background_object(ObjectNodeHeader *owner, s32 *selection_flag) {
    Root *base;
    CardBackgroundBody *obj;

    base = &card_background_object;
    obj = NODE_BODY(base);

    if (func_80047FD8(base) == 0) {
        base = func_8003C714(0, base, 0xC9);
        if (base == 0) {
            func_8007C040(D_8040062C, D_80400654, 0x17A);
            func_8007BEF0(1);
        }
        func_80040560(base, card_status_query_address);
    } else {
        card_dev_flag_object_dirty(base);
        {
            u16 flags = card_background_object.flags;
            flags &= 0x7FFF;
            card_background_object.flags = flags;
        }
        func_8007BFE0(obj, 0x304);
    }
    D_804F281B[0] = 8;
    D_805030EF[0] = 8;
    card_background_init_entry_tables(obj, 7);
    base->field_0C = &obj->template_node;
    obj->template_node.unk_0C = card_background_bind_dialog_template(obj->entry_table);
    func_80404C44(obj, (obj->selection_flag = selection_flag, owner));
    card_dev_select_sub_block((base->field_10 = card_dev_select_sub_block, obj));
    return base;
}
