#ifndef SHARED_DUNGEON_FLOOR_H
#define SHARED_DUNGEON_FLOOR_H

/* Dungeon-overlay .bss floor state (r78 type consolidation phase 7).  Two SEPARATE objects: every row that uses
 * both forms its own lui for each (census/c800E29.jsonl), so they are not fields of one struct. */

/* D_800E296C: a floor state flag word (lw/sw only; bit tests, sets and clears in 60 rows). */
extern int dungeon_floor_flags;

/* D_800E2970: the floor's room table, 0x14-byte records indexed by a room number (a map cell: the corridor
 * builder func_80287C4C walks cells as idx % D_8001F660 / idx / D_8001F660 and joins room rectangles; tiles and
 * actors carry an s8 room index, -1 = none).  Offsets from 91 rows (lh/lb => signed, lhu-only => unsigned). */
/* One room rectangle in the current floor room table; generation routines populate it.
 * Tile/actor room indices select these entries; -1 means no room. */
typedef struct DungeonRoom {
    /* 0x00 */ unsigned short x; /* room rectangle starting column, in map tiles */
    /* 0x02 */ unsigned short y; /* room rectangle starting row, in map tiles */
    /* 0x04 */ short w; /* room rectangle width, in map tiles */
    /* 0x06 */ short h; /* room rectangle height, in map tiles */
    /* 0x08 */ short unk_08;
    /* 0x0A */ short unk_0A; /* nonzero when this generation cell contains a real room */
    /* 0x0C */ unsigned short flags; /* room state bits; readers test bit 1 before trusting a stored room index */
    /* 0x0E */ short unk_0E;
    /* 0x10 */ int unk_10;
} DungeonRoom;                       /* size 0x14 */

extern DungeonRoom dungeon_rooms[];


/* Exact access views shared across registered binary consumers. */
/* Unsigned map tile identifier and flag bits read with two-byte element stride. */
typedef struct MapTileHalfView {
    unsigned short unk_00;
} MapTileHalfView;

#endif
