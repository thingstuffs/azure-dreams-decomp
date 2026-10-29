#include "common.h"
#include "town/map.h"

extern u8 town_building_records[];

typedef struct BuildingMarkRecord {
    u8 pad_00[0xA];
    s16 marked;
} BuildingMarkRecord;

typedef struct BuildingIndexPage {
    u8 pad_00[0x33A4];
    u8 record_index;
} BuildingIndexPage;

/* Clears record flags, then marks records referenced by nonzero indices in the strided list. */
void mark_referenced_building_records(void) {
    s32 entryIndex;
    u8 *recordCursor;
    u8 *indexPageCursor;
    u8 *recordBase;
    u8 recordIndex;
    s16 markedFlag;

    entryIndex = 0x42;
    recordCursor = town_building_records;
    recordCursor += 0x840;
    do {
        ((BuildingMarkRecord *)recordCursor)->marked = 0;
        entryIndex--;
        recordCursor -= 0x20;
    } while (entryIndex >= 0);

    entryIndex = 0;
    recordBase = town_building_records;
    markedFlag = 1;
    /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: town/func_800BB33C). */
    do {
        indexPageCursor = (u8 *)0x80010000;
    } while (0);
    do {
        recordIndex = ((BuildingIndexPage *)indexPageCursor)->record_index;
        if (recordIndex != 0) {
            BuildingMarkRecord *record = (BuildingMarkRecord *)((recordIndex << 5) + (unsigned long)recordBase);
            record->marked = markedFlag;
        }
        entryIndex++;
        indexPageCursor += 2;
    } while (entryIndex < 0x22);
}
