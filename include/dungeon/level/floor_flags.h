#ifndef DUNGEON_LEVEL_FLOOR_FLAGS_H
#define DUNGEON_LEVEL_FLOOR_FLAGS_H

/* Reveal requests in dungeon_floor_flags. The item handlers announce the
 * revealed object type; draw_nearby_map_markers consumes these requests. */
enum DungeonFloorFlags {
    FLOOR_REVEAL_ELEVATOR = 0x100,
    FLOOR_REVEAL_ITEMS = 0x200,
    FLOOR_REVEAL_TRAPS = 0x800,
    FLOOR_REVEAL_MONSTERS = 0x400,
    FLOOR_ELEVATOR_VISIBLE = 0x1,
    FLOOR_ITEMS_VISIBLE = 0x2,
    FLOOR_MONSTERS_VISIBLE = 0x4,
    FLOOR_TRAPS_VISIBLE = 0x8,
    FLOOR_MAP_VIEW_HOLD = 0x800000,
    FLOOR_MAP_VIEW_HOLD_CLEAR_MASK = 0xFF7FFFFF,
};

/* Four floor features populated by layout generation and read by map markers.
 * Kind 2 is an elevator; x/y are map tiles and height is the stored floor height. */
typedef struct DungeonFloorMarker {
    short kind;
    short x;
    short y;
    short height;
} DungeonFloorMarker;

extern DungeonFloorMarker dungeon_floor_marker_entries[4];

#endif
