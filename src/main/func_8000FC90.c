#include "common.h"

extern void cardBootBindMessageDialogRecord(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);
extern void cardBootInitializeMessageRenderTemplates(s32 entity, s32 primary_data, s32 secondary_data);
extern void cardBootInitializeDialogPacketsAndDisplay(s32 record);

/* Sets record fields, processes its embedded data, and updates the record. */
void cardBootInitializeMessageDialogLayout(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20) {
    cardBootBindMessageDialogRecord(record, value_14, entry_index, value_0c, value_20);
    cardBootInitializeMessageRenderTemplates(record + 0x8BC, record + 0x894, record + 0x8A4);
    cardBootInitializeDialogPacketsAndDisplay(record);
}
