#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/town.h"
#include "engine/util.h"
#include "frontend/libcard.h"
#include "frontend/card.h"
#include "sdk/libc.h"







typedef struct S_80024390_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    s32 * unk_0C;
} S_80024390_2;   /* table_base in card_boot_format_saved_slot_details */



#include "engine/text.h"
extern u8 D_800200A4[0x100];
extern s32 D_80027FD4[0x40];
extern u8 D_800282D8[0x100];
extern u8 D_800282E8[0x100];
extern u8 D_800283A8[0x100];

/* Builds and positions saved-slot text, play time and eight icons from the selected card record. */
void card_boot_format_saved_slot_details(CardSlotDetails *record) {
    u8 textBuffer[256];
    u8 numberBuffer[16];
    s32 coordinate;
    s32 *tableCursor;
    s32 totalMinutes;
    s32 hours;
    s32 elapsedSeconds;
    s32 value;
    u32 displayValue;
    u32 boundedValue;
    u32 one;
    s32 width;
    s32 scaledTime;
    CardSaveSlot *recordBase;
    void *assetDataBase;
    void *loop_base;
    void *asset0;
    void *asset1;
    void *asset2;
    void *asset3;
    void *asset4;
    void *asset5;
    void *asset6;
    S_80024390_2 *table_base;
    CardDetailDisplayNode *assetSlot;
    CardSaveSlot *recordData;
    void *recordCursor;
    s32 *global_table;

    assetSlot = record->text_nodes[0];
    format_unsigned_double_byte_decimal(record->selected_slot + 1, (u8 *)(&textBuffer));
    strcat(&textBuffer, D_800282D8);
    assetDataBase = card_slot_payload;
    strcat(&textBuffer, (record->selected_slot << 7) + assetDataBase);
    asset0 = (u8 *)record + 0x84;
    decode_fullwidth_text(asset0, (u8 *)(&textBuffer), 1);
    assetSlot->payload.data = asset0;
    assetSlot->block->fields.x = 0xA8;
    assetSlot->block->fields.y = 0x110;
    assetSlot = record->text_nodes[1];
    strcpy(&textBuffer, D_800282E8);
    asset1 = (u8 *)record + 0x204;
    decode_fullwidth_text(asset1, (u8 *)(&textBuffer), 1);
    assetSlot->payload.data = asset1;
    assetSlot->block->fields.x = 0xA0;
    assetSlot->block->fields.y = 0x110;
    recordBase = assetDataBase - 0xC;
    if (recordBase[record->selected_slot].halfwords[4] != 0) {
        table_base = D_800283A8;
        assetSlot = record->text_nodes[2];
        strcpy(&textBuffer, table_base->unk_08);
        format_unsigned_double_byte_decimal(recordBase[record->selected_slot].words[13], (u8 *)(&numberBuffer));
        strcat(&textBuffer, &numberBuffer);
        strcat(&textBuffer, table_base->unk_0C);
        asset2 = (u8 *)record + 0x384;
        decode_fullwidth_text(asset2, (u8 *)(&textBuffer), 1);
        assetSlot->payload.data = asset2;
        assetSlot->block->fields.x = 0xB8;
        assetSlot->block->fields.y = 0x140;
    }
    assetSlot = record->text_nodes[3];
    func_8004E5A0(recordBase[record->selected_slot].words[9], 0xA, (char *)(&textBuffer));
    remap_flagged_string_bytes((u8 *)(&textBuffer));
    asset3 = (u8 *)record + 0x504;
    build_positioned_text_glyphs(asset3, (u8 *)(&textBuffer), 1);
    assetSlot->payload.data = asset3;
    assetSlot->block->fields.x = 0x148;
    assetSlot->block->fields.y = 0x110;
    recordData = recordBase + record->selected_slot;
    scaledTime = (u32)recordData->words[7] / 60;
    elapsedSeconds = scaledTime;
    assetSlot = record->text_nodes[4];
    hours = elapsedSeconds / 3600;
    value = 0x3E7;
    if (hours < 0x3E8) {
        value = hours;
    }
    func_8004E5A0(value, 3, (char *)(&textBuffer));
    strcat(&textBuffer, D_800200A4);
    totalMinutes = elapsedSeconds / 60;
    func_8004E5E8(totalMinutes - (hours * 0x3C), 2, (char *)numberBuffer);
    strcat(&textBuffer, &numberBuffer);
    strcat(&textBuffer, D_800200A4);
    func_8004E5E8(elapsedSeconds - (totalMinutes * 0x3C), 2, (char *)numberBuffer);
    strcat(&textBuffer, &numberBuffer);
    remap_flagged_string_bytes((u8 *)(&textBuffer));
    asset4 = (u8 *)record + 0x684;
    build_positioned_text_glyphs(asset4, (u8 *)(&textBuffer), 1);
    assetSlot->payload.data = asset4;
    assetSlot->block->fields.x = 0x150;
    assetSlot->block->fields.y = 0x120;
    displayValue = (u32)recordBase[record->selected_slot].words[11];
    assetSlot = record->text_nodes[5];
    boundedValue = 0x3E7;
    if (displayValue < 0x3E8U) {
        boundedValue = displayValue;
    }
    func_8004E5A0((s32) boundedValue, 3, (char *)(&textBuffer));
    remap_flagged_string_bytes((u8 *)(&textBuffer));
    asset5 = (u8 *)record + 0x804;
    build_positioned_text_glyphs(asset5, (u8 *)(&textBuffer), 1);
    assetSlot->payload.data = asset5;
    assetSlot->block->fields.x = 0x100;
    assetSlot->block->fields.y = 0x120;
    assetSlot = record->text_nodes[6];
    func_8004E5A0(recordBase[record->selected_slot].words[10], 2, (char *)(&textBuffer));
    remap_flagged_string_bytes((u8 *)(&textBuffer));
    asset6 = (u8 *)record + 0x984;
    build_positioned_text_glyphs(asset6, (u8 *)(&textBuffer), 1);
    value = 0;
    loop_base = recordBase;
    global_table = D_80027FD4;
    one = 1;
    width = 0xB0;
    coordinate = 0x34;
    tableCursor = global_table;
    recordCursor = record;
    assetSlot->payload.data = asset6;
    assetSlot->block->fields.x = 0x188;
    assetSlot->block->fields.y = 0x130;
    do {
        assetSlot = ((CardSlotDetails *)recordCursor)->icon_nodes[0];
        recordData = (void *)(record->selected_slot << 7);
        recordData = (void *)((u32)recordData + (u32)loop_base);
        if (recordData->words[12] & (one << value)) {
            displayValue = *tableCursor;
        } else {
            displayValue = global_table[8];
        }
        tableCursor += 1;
        recordCursor += 4;
        value += 1;
        assetSlot->payload.word = (s32) displayValue;
        assetSlot->block->fields.x = coordinate;
        assetSlot->block->fields.y = width;
        coordinate += 0x10;
    } while (value < 8);
}
