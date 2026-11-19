#ifndef TOWN_MAP_BUILDING_GRID_G00638_H
#define TOWN_MAP_BUILDING_GRID_G00638_H
/* Building grid. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B9C24, CL:town/func_800B9C70, CL:town/func_800B9C90. */

#include "common.h"
#include "m2c_compat.h"

/* Image IDs used by the building grid exceed four; the full table bound is unknown. */
extern u16 *D_800D1868[];
/* 128-by-128 tile IDs shared by the town map and building grid. */
extern u16 town_tile_grid[];

typedef struct {
    s16 x0;
    s16 y0;
    s16 pad4;
    s16 pad6;
    s16 x1;
    s16 y1;
} func_8009F66C_CoordPair;

/* The 67 stored building records have a 32-byte stride. */
typedef struct TownBuildingRecord {
    u8 tile_entry;
    u8 tile_entry_enabled;
    u8 unk_02;
    u8 kind;
    u8 slot_width;
    u8 slot_height;
    u8 required_partner;
    u8 linked_record_index;
    s16 availability_flag;
    s16 marked;
    func_8009F66C_CoordPair script_rect;
    u8 unk_18[8];
} TownBuildingRecord;

extern TownBuildingRecord town_building_records[67];

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

extern TownBuildingSlotRectangle town_building_slot_rectangles[34];


void initialize_building_region_resources(void);

/* Functions defined in this translation unit. */
void clear_building_grid(s16 *grid);
void update_active_building_entries(void);
void clear_and_initialize_building_grid(void *grid);


void initialize_building_scene_objects(void *draw_param);

struct GameWork;
void no_op_building_callback(struct GameWork *work, s32 size, s32 limit);

#endif
