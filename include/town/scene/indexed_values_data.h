#ifndef TOWN_SCENE_INDEXED_VALUES_DATA_H
#define TOWN_SCENE_INDEXED_VALUES_DATA_H

/* D_80016470 is indexed at a 12-byte stride. The scene selector reads the
 * signed halfword at +4 and the mode-two marker tests the word at +8. */
typedef struct TownIndexedValueRecord {
    int value;
    short flag;
    unsigned short reserved;
    int condition;
} TownIndexedValueRecord;

extern TownIndexedValueRecord town_indexed_values[];

#endif
