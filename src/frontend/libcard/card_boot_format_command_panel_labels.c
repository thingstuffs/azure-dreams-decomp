#include "common.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Processes three table values with addresses spaced 0x48 bytes apart from base + 0x90. */
void card_boot_format_command_panel_labels(CardCommandPanelBody *panel) {
    u8 **tableEntry;
    u8 *entry_text;
    u8 *tableValue;
    s32 entriesProcessed;

    entriesProcessed = 0;
    tableEntry = D_800282BC;
    do {
        tableValue = *tableEntry;
        tableEntry += 1;
        entry_text = panel->label_text[entriesProcessed];
        entriesProcessed += 1;
        decode_fullwidth_text(entry_text, tableValue, 1);
    } while (entriesProcessed < 3);
}
