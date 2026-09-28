#ifndef SHARED_DUNGEON_FLOOR_H
#define SHARED_DUNGEON_FLOOR_H

/* Dungeon-overlay .bss floor state (r78 type consolidation phase 7).  Two SEPARATE objects: every row that uses
 * both forms its own lui for each (census/c800E29.jsonl), so they are not fields of one struct. */

/* D_800E296C: a floor state flag word (lw/sw only; bit tests, sets and clears in 60 rows). */
extern int D_800E296C;

/* D_800E2970: the floor's room table, 0x14-byte records indexed by a room number (a map cell: the corridor
 * builder func_80287C4C walks cells as idx % D_8001F660 / idx / D_8001F660 and joins room rectangles; tiles and
 * actors carry an s8 room index, -1 = none).  Offsets from 91 rows (lh/lb => signed, lhu-only => unsigned). */
typedef struct DungeonRoom {
    /* 0x00 */ unsigned short x;     /* room rectangle, map-grid units (func_80287C4C: corridor end = room x/y) */
    /* 0x02 */ unsigned short y;
    /* 0x04 */ short w;              /* rectangle extent */
    /* 0x06 */ short h;
    /* 0x08 */ short unk_08;
    /* 0x0A */ short unk_0A;         /* non-zero: the cell holds a real room (the corridor builder offsets its door) */
    /* 0x0C */ unsigned short flags; /* & 2 tested by 30+ rows before an s8 room index is trusted */
    /* 0x0E */ short unk_0E;
    /* 0x10 */ int unk_10;
} DungeonRoom;                       /* size 0x14 */

extern DungeonRoom D_800E2970[];

#endif
