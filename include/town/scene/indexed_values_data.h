#ifndef TOWN_SCENE_INDEXED_VALUES_DATA_H
#define TOWN_SCENE_INDEXED_VALUES_DATA_H

/* Eight 12-byte scene-selection entries. Bank 3E5000 uses the table at
 * 0x8001791C. Its placed selectors use 0x80016470 in banks 3F5000 and 3F9800. */
typedef struct TownIndexedValueRecord {
    int value;  /* Selection kind matched against the output records. */
    short flag; /* Script flag enabling this entry. */
    short selected_flag; /* Set when the paired-flag scan selects this entry. */
    int condition; /* A nonzero entry is marked without an explicit selection. */
} TownIndexedValueRecord;

extern TownIndexedValueRecord town_indexed_values[8];
extern TownIndexedValueRecord town_selection_records[8];

#endif
