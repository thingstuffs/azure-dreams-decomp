#include "shared/monster_ids.h"
#include "dungeon/level/floor_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/entity.h"

extern u8 floor_objects[];
extern u8 dungeon_ground_item_positions[];
extern u8 dungeon_floor_object_positions[];
extern u8 dungeon_floor_marker_entries[];

extern s32 rsin(s32);
extern void append_adjusted_type_two_entry(s32, s32, u8 *, s32);
extern s32 get_masked_grid_nibble(s32, s32);
extern void draw_green_type_two_markers(void);
extern void draw_purple_entry_markers(void);
extern void draw_blue_enabled_entry_markers(void);
extern void draw_red_active_entry_markers(void);
extern void redraw_type_three_floor_markers(void);
extern s32 get_tile_chebyshev_distance(u8 *, u8 *);

typedef struct {
    u8 x;
    u8 y;
    u8 pad[10];
} MapEntry;

typedef struct {
    s16 type;
    s16 x;
    s16 y;
    s16 pad;
} ObjectEntry;

typedef struct {
    u8 exists;
    u8 active;
    u8 pad;
    u8 flags;
} EntryInfo;

typedef struct {
    u8 pad[6];
    u8 x;
    u8 y;
    u8 rest[16];
} LargeMapEntry;

/* Services pending redraw flags, then draws map markers for nearby monsters, dropped items, and large map entries. */
void draw_nearby_map_markers(s32 draw_param) {
    u8 colour[4];
    ActorRecord *head;
    u8 *entry;
    long playerAndIndex;
    u8 *player;
    GameWork *system;
    MapEntry *mapEntry;
    ObjectEntry *objectEntry;
    EntryInfo *info;
    LargeMapEntry *largeMapEntry;
    s32 brightness;
    u8 *firstColour;
    s32 firstContext;
    s32 distance;

    system = &g_game_work;
    head = dungeon_actor_ring_anchor;

    if (dungeon_floor_flags & 0x1000) {
        dungeon_floor_flags &= ~0x1000;
        redraw_type_three_floor_markers();
    }
    if (dungeon_floor_flags & FLOOR_REVEAL_MONSTERS) {
        dungeon_floor_flags &= ~FLOOR_REVEAL_MONSTERS;
        draw_red_active_entry_markers();
    }
    if (dungeon_floor_flags & FLOOR_REVEAL_ITEMS) {
        dungeon_floor_flags &= ~FLOOR_REVEAL_ITEMS;
        draw_blue_enabled_entry_markers();
    }
    if (dungeon_floor_flags & FLOOR_REVEAL_TRAPS) {
        dungeon_floor_flags &= ~FLOOR_REVEAL_TRAPS;
        draw_purple_entry_markers();
    }
    if (dungeon_floor_flags & FLOOR_REVEAL_ELEVATOR) {
        dungeon_floor_flags &= ~FLOOR_REVEAL_ELEVATOR;
        draw_green_type_two_markers();
    }

    brightness = (rsin(system->unk_004 << 8) >> 6) + 0x80;
    firstColour = colour;
    if (brightness >= 0x100) {
        brightness = 0xff;
    }
    firstContext = draw_param;
    player = (u8 *)&reference_tile_object;
    colour[3] = 0x68;
    colour[2] = 0;
    colour[1] = brightness;
    colour[0] = brightness;
    append_adjusted_type_two_entry(player[0x24], player[0x25], firstColour, firstContext);

    entry = ((u8 *)head->next_actor_header) + 0x20;
    colour[1] = 0;
    if (entry != head) {
        for (; entry != head; entry = *(u8 **)(entry + 0x5c) + 0x20) {
            union { s32 value; } entryFlag = {0};
            union { s32 value; } entryType = {0};
            union { long value; } markerKind = {0};
            union { long value; } kind = {0};
            union { u8 * value; } object = {0};
            if (*(s8 *)(entry + 0x13) > 0) {
                object.value = *(u8 * *)&((ObjectNodeHeader *)((u8 *)entry - 0x20))->sprite;
                if (!(dungeon_floor_flags & FLOOR_MONSTERS_VISIBLE)) {
                    if (*(s8 *)(object.value + 0x26) < 0 ||
                        *(s8 *)(object.value + 0x26) != reference_tile_object.room_index) {
                        distance = get_tile_chebyshev_distance(object.value,
                                                 (u8 *)&reference_tile_object);
                        if ((s16)distance >= 4) {
                            continue;
                        }
                    }
                }

                kind.value = 0;
                if ((entryType.value = entry[0x13]) == MONSTER_MANOEVA) {
                    if ((entryFlag.value = entry[0xad]) != 0) {
                        kind.value = 2;
                    } else {
                        kind.value = 1;
                    }
                } else if ((entryType.value = entry[0x13]) != MONSTER_STEALTH ||
                           (*(s16 *)(entry + 0xa6)) == 0 ||
                           (dungeon_floor_flags & FLOOR_MONSTERS_VISIBLE)) {
                    kind.value = 1;
                }

                markerKind.value = kind.value;
                if (markerKind.value != 0) {
                    if (markerKind.value == 2) {
                        colour[2] = brightness;
                        colour[0] = 0;
                    }
                    append_adjusted_type_two_entry(object.value[0x24], object.value[0x25], colour, draw_param);
                    if (markerKind.value == 2) {
                        colour[2] = 0;
                        colour[0] = brightness;
                    }
                }
            }
        }
    }
    playerAndIndex = 0;
    mapEntry = (MapEntry *)dungeon_ground_item_positions;
    info = (EntryInfo *)((u8 *)dungeon_ground_items);
    colour[2] = brightness;
    colour[0] = 0;
    do {
        if (info[playerAndIndex].active != 0) {
            if ((dungeon_floor_flags & FLOOR_ITEMS_VISIBLE) ||
                get_masked_grid_nibble(mapEntry[playerAndIndex].x,
                              mapEntry[playerAndIndex].y)) {
                append_adjusted_type_two_entry(mapEntry[playerAndIndex].x,
                              mapEntry[playerAndIndex].y, colour, draw_param);
            }
        }
        playerAndIndex++;
    } while (playerAndIndex < 0x40);

    playerAndIndex = 0;
    objectEntry = (ObjectEntry *)dungeon_floor_marker_entries;
    colour[2] = 0;
    colour[1] = brightness;
    for (; playerAndIndex < 4 && objectEntry[playerAndIndex].type == 2; playerAndIndex++) {
        if ((dungeon_floor_flags & FLOOR_ELEVATOR_VISIBLE) ||
            get_masked_grid_nibble(objectEntry[playerAndIndex].x,
                          objectEntry[playerAndIndex].y)) {
            append_adjusted_type_two_entry((u16)objectEntry[playerAndIndex].x,
                          (u16)objectEntry[playerAndIndex].y, colour, draw_param);
        }
    }

    playerAndIndex = 0;
    largeMapEntry = (LargeMapEntry *)dungeon_floor_object_positions;
    info = (EntryInfo *)floor_objects;
    colour[1] = 0x20;
    colour[2] = brightness;
    colour[0] = brightness;
    do {
        if (info[playerAndIndex].active != 0 &&
            info[playerAndIndex].exists != 0 &&
            !(info[playerAndIndex].flags & 0x40)) {
            if ((dungeon_floor_flags & FLOOR_TRAPS_VISIBLE) ||
                (!(info[playerAndIndex].flags & 0x80) &&
                 get_masked_grid_nibble(largeMapEntry[playerAndIndex].x,
                               largeMapEntry[playerAndIndex].y))) {
                append_adjusted_type_two_entry(largeMapEntry[playerAndIndex].x,
                              largeMapEntry[playerAndIndex].y, colour, draw_param);
            }
        }
        playerAndIndex++;
    } while (playerAndIndex < 0x20);
}
