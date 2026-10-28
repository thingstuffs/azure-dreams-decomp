#include "common.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Processes three table values with addresses spaced 0x48 bytes apart from base + 0x90. */
void card_boot_format_command_panel_labels(s32 baseAddress) {
    u8 **tableEntry;
    s32 entryAddress;
    u8 *tableValue;
    s32 entryOffset;
    s32 entriesProcessed;

    entriesProcessed = 0;
    tableEntry = D_800282BC;
    entryOffset = 0x90;
    do {
        tableValue = *tableEntry;
        tableEntry += 1;
        entryAddress = baseAddress + entryOffset;
        entryOffset += 0x48;
        entriesProcessed += 1;
        decode_fullwidth_text(entryAddress, tableValue, 1);
    } while (entriesProcessed < 3);
}
