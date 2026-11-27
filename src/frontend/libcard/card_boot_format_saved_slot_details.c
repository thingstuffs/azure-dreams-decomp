#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/town.h"
#include "engine/util.h"
#include "frontend/libcard.h"
#include "frontend/card.h"
#include "sdk/libc.h"
#include "engine/text.h"

typedef struct CardSlotNumberText {
    u8 pad_00[8];
    char *prefix;
    char *suffix;
} CardSlotNumberText;

extern char D_800200A4[0x100];
extern s32 D_80027FD4[0x40];
extern char card_slot_name_label_message[0x100];
extern char D_800282E8[0x100];
extern CardSlotNumberText D_800283A8;

/* Builds and positions saved-slot text, play time and eight icons from the selected card record. */
void card_boot_format_saved_slot_details(CardSlotDetails *record) {
    char textBuffer[256];
    char numberBuffer[16];
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
    char *slot_titles;
    CardSaveSlot *loop_base;
    u8 *asset0;
    u8 *asset1;
    u8 *asset2;
    u8 *asset3;
    u8 *asset4;
    u8 *asset5;
    u8 *asset6;
    CardSlotNumberText *number_text;
    CardDetailDisplayNode *assetSlot;
    CardSaveSlot *recordData;
    s32 *global_table;

    assetSlot = record->text_nodes[0];
    format_fullwidth_decimal(record->selected_slot + 1, (u8 *)textBuffer);
    strcat(textBuffer, card_slot_name_label_message);
    slot_titles = (char *)card_slot_payload;
    strcat(textBuffer, (record->selected_slot << 7) + slot_titles);
    asset0 = record->text_buffers[0];
    decode_fullwidth_text(asset0, (u8 *)textBuffer, 1);
    assetSlot->payload.data = asset0;
    assetSlot->block->fields.x = 0xA8;
    assetSlot->block->fields.y = 0x110;
    assetSlot = record->text_nodes[1];
    strcpy(textBuffer, D_800282E8);
    asset1 = record->text_buffers[1];
    decode_fullwidth_text(asset1, (u8 *)textBuffer, 1);
    assetSlot->payload.data = asset1;
    assetSlot->block->fields.x = 0xA0;
    assetSlot->block->fields.y = 0x110;
    recordBase = (CardSaveSlot *)(slot_titles - 0xC);
    if (recordBase[record->selected_slot].halfwords[4] != 0) {
        number_text = &D_800283A8;
        assetSlot = record->text_nodes[2];
        strcpy(textBuffer, number_text->prefix);
        format_fullwidth_decimal(recordBase[record->selected_slot].fields.unk_34, (u8 *)numberBuffer);
        strcat(textBuffer, numberBuffer);
        strcat(textBuffer, number_text->suffix);
        asset2 = record->text_buffers[2];
        decode_fullwidth_text(asset2, (u8 *)textBuffer, 1);
        assetSlot->payload.data = asset2;
        assetSlot->block->fields.x = 0xB8;
        assetSlot->block->fields.y = 0x140;
    }
    assetSlot = record->text_nodes[3];
    format_int_space_padded(recordBase[record->selected_slot].fields.unk_24, 0xA, textBuffer);
    remap_flagged_string_bytes((u8 *)textBuffer);
    asset3 = record->text_buffers[3];
    build_positioned_text_glyphs(asset3, (u8 *)textBuffer, 1);
    assetSlot->payload.data = asset3;
    assetSlot->block->fields.x = 0x148;
    assetSlot->block->fields.y = 0x110;
    recordData = recordBase + record->selected_slot;
    scaledTime = recordData->fields.play_frames / 60;
    elapsedSeconds = scaledTime;
    assetSlot = record->text_nodes[4];
    hours = elapsedSeconds / 3600;
    value = 0x3E7;
    if (hours < 0x3E8) {
        value = hours;
    }
    format_int_space_padded(value, 3, textBuffer);
    strcat(textBuffer, D_800200A4);
    totalMinutes = elapsedSeconds / 60;
    format_int_zero_padded(totalMinutes - (hours * 0x3C), 2, numberBuffer);
    strcat(textBuffer, numberBuffer);
    strcat(textBuffer, D_800200A4);
    format_int_zero_padded(elapsedSeconds - (totalMinutes * 0x3C), 2, numberBuffer);
    strcat(textBuffer, numberBuffer);
    remap_flagged_string_bytes((u8 *)textBuffer);
    asset4 = record->text_buffers[4];
    build_positioned_text_glyphs(asset4, (u8 *)textBuffer, 1);
    assetSlot->payload.data = asset4;
    assetSlot->block->fields.x = 0x150;
    assetSlot->block->fields.y = 0x120;
    displayValue = (u32)recordBase[record->selected_slot].fields.unk_2C;
    assetSlot = record->text_nodes[5];
    boundedValue = 0x3E7;
    if (displayValue < 0x3E8U) {
        boundedValue = displayValue;
    }
    format_int_space_padded((s32) boundedValue, 3, textBuffer);
    remap_flagged_string_bytes((u8 *)textBuffer);
    asset5 = record->text_buffers[5];
    build_positioned_text_glyphs(asset5, (u8 *)textBuffer, 1);
    assetSlot->payload.data = asset5;
    assetSlot->block->fields.x = 0x100;
    assetSlot->block->fields.y = 0x120;
    assetSlot = record->text_nodes[6];
    format_int_space_padded(recordBase[record->selected_slot].words[10], 2, textBuffer);
    remap_flagged_string_bytes((u8 *)textBuffer);
    asset6 = record->text_buffers[6];
    build_positioned_text_glyphs(asset6, (u8 *)textBuffer, 1);
    value = 0;
    loop_base = recordBase;
    global_table = D_80027FD4;
    one = 1;
    width = 0xB0;
    coordinate = 0x34;
    tableCursor = global_table;
    assetSlot->payload.data = asset6;
    assetSlot->block->fields.x = 0x188;
    assetSlot->block->fields.y = 0x130;
    do {
        assetSlot = record->icon_nodes[value];
        recordData = (CardSaveSlot *)((record->selected_slot * sizeof(*recordData)) + (u32)loop_base);
        if (recordData->fields.icon_flags & (one << value)) {
            displayValue = *tableCursor;
        } else {
            displayValue = global_table[8];
        }
        tableCursor += 1;
        value += 1;
        assetSlot->payload.word = (s32) displayValue;
        assetSlot->block->fields.x = coordinate;
        assetSlot->block->fields.y = width;
        coordinate += 0x10;
    } while (value < 8);
}
