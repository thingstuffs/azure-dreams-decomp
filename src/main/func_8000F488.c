#include "common.h"

typedef struct {
    s32 words[5];
    u8 flag14;
    u8 pad15;
    u8 pad16;
    u8 count17;
} EntryT;

extern s32 D_800280B4[3];

extern void cardBootMeasureDialogChoiceWord();
extern void cardBootPositionDialogSelectionMarker();

/* Processes the last word of an enabled table entry for the supplied object. */
void cardBootUpdateMessageChoiceHighlight(void *object) {
    s32 result_first;
    s32 result_second;
    s32 result_third;
    EntryT *entry;
    s32 last_index;
    s32 table_index;
    s32 table_base;

    table_base = (s32)D_800280B4;
    table_index = *(s32 *)((u8 *)object + 8);
    entry = (EntryT *)(table_index * 0x18 + table_base);
    last_index = entry->count17 - 1;
    if (entry->flag14 != 0) {
        cardBootMeasureDialogChoiceWord(entry->words[last_index], *(s32 *)object, &result_first, &result_second, &result_third);
        cardBootPositionDialogSelectionMarker(object, result_first, result_second, last_index, result_third);
    }
}
