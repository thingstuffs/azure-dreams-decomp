#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern s32 func_80051B50(void *buffer, s32 value, s32 option);
extern s32 get_table_entry_by_flag(void);

typedef struct {
    u8 pad8[8];
    s16 unk8;
    s16 unkA;
} SubStruct2;

typedef struct {
    void *unk0;
    SubStruct2 *unk4;
} SubStruct;

/* Initializes data pointers and layout values for three child entries. */
void card_dev_layout_title_entries(u8 *owner) {
    SubStruct *child;
    s32 resource_index;

    child = *(SubStruct **)(owner + 0x1DC);
    resource_index = get_table_entry_by_flag() >= 3;
    child->unk0 = (void *) func_80051B50(owner + 8, D_80408CB0[resource_index], 1);
    child->unk4->unk8 = 0xF0;
    child->unk4->unkA = 0x91;

    child = *(SubStruct **)(owner + 0x1EC);
    child->unk4->unk8 = 0x70;
    child->unk4->unkA = 0x10;
    child->unk0 = (void *) &D_8008432C;

    child = *(SubStruct **)(owner + 0x1F4);
    child->unk0 = (void *) (owner + 0xB0);
    child->unk4->unk8 = 0xAE;
    child->unk4->unkA = 0x18;
}
