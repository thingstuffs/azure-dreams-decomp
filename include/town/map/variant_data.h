#ifndef TOWN_MAP_VARIANT_DATA_H
#define TOWN_MAP_VARIANT_DATA_H

#include "common.h"

/* The entry walker passes these twenty-byte records to the town object spawner. */
typedef struct TownSpawnEntry {
    s8 active; /* its address is saved so object cleanup can clear it */
    u8 flags;
    s16 bitmap_bit;
    u8 facing_index;
    u8 state_94;
    u8 state_95;
    u8 variant;
    s32 creation_argument; /* door spawns use an address-valued key */
    s32 callback_id; /* target address or tagged callback-table index */
    u16 x_offset;
    u16 y_offset;
} TownSpawnEntry;

typedef s32 (*TownRectangleCallback)(void);

/* An appended rectangle owns a terminated list of spawn groups and an optional setup callback. */
typedef struct TownRectangle {
    u16 origin_x;
    u16 origin_y;
    s16 x_offset;
    s16 y_offset;
    s16 width;
    s16 height;
    TownSpawnEntry **entry_list;
    TownRectangleCallback callback;
} TownRectangle;

typedef struct TownMapVariantRecord {
    u8 entry_kind;
    u8 unk_01[3];
    u8 rect_width;
    u8 rect_height;
    u8 unk_06[6];
    TownRectangle position_entry;
} TownMapVariantRecord;

/* The 67 stored building records have a 32-byte stride. */
typedef struct TownBuildingRecord {
    u8 tile_entry;
    u8 tile_entry_enabled;
    u8 unk_02;
    u8 kind;
    u8 slot_width;
    u8 slot_height;
    u8 partner_building_id;
    u8 linked_building_id;
    s16 availability_bit;
    s16 marked;
    TownRectangle position_entry;
} TownBuildingRecord;

/* The 34 eight-byte slots end where town_map_variants begins. */
typedef struct TownBuildingSlotRectangle {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 kind;
    u8 unk_05;
    u8 first_building_id;
    u8 second_building_id;
} TownBuildingSlotRectangle;

/* Selected town-map variant byte at 0x800D381A. */
extern u8 town_map_variant;
extern TownBuildingRecord town_building_records[67];
extern TownBuildingSlotRectangle town_building_slot_rectangles[34];
extern TownMapVariantRecord town_map_variants[];

#endif
