#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern s32 func_80051B50(void *ptr, s32 value, s32 value2);
extern s32 func_80051520(void *ptr, s32 *value_ptr, s32 value2);
extern void func_80051804(s32 value, s32 value2, s32 *value_ptr);
extern void func_80051900(s32 *value_ptr);

typedef struct {
    u8 pad8[8];
    s16 unk8;
    s16 unkA;
} SubStruct2;

typedef struct {
    void *unk0;
    SubStruct2 *unk4;
} SubStruct;

/* Sets up display element content and positions for the selected entry. */
void card_dev_layout_selected_slot_entries(u8 *screen) {
    SubStruct *element;
    s32 formatted_value;

    element = *(SubStruct **)(screen + 0x1EC);
    element->unk4->unk8 = 0x70;
    element->unk4->unkA = 0x10;
    element->unk0 = (void *) &D_80084158;

    element = *(SubStruct **)(screen + 0x1DC);
    element->unk0 = (void *) func_80051B50(screen + 8, (*(s32 *)screen << 7) + (s32) &card_slot_detail_records[0], 1);
    element->unk4->unk8 = 0xF0;
    element->unk4->unkA = 0x91;

    element = *(SubStruct **)(screen + 0x1E0);
    element->unk0 = (void *) func_80051B50(screen + 0x50, (s32) &D_804005EC, 1);
    element->unk4->unk8 = 0x160;
    element->unk4->unkA = 0x91;

    element = *(SubStruct **)(screen + 0x1E8);
    func_80051804(card_slot_detail_records[*(s32 *)screen].words[8], 4, &formatted_value);
    func_80051900(&formatted_value);
    element->unk0 = (void *) func_80051520(screen + 0x80, &formatted_value, 1);
    element->unk4->unk8 = 0x13F;
    element->unk4->unkA = 0x91;

    element = *(SubStruct **)(screen + 0x1F4);
    element->unk0 = (void *) (screen + 0xB0);
    element->unk4->unk8 = 0xAE;
    element->unk4->unkA = 0x18;
}
