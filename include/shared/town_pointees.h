#ifndef SHARED_TOWN_POINTEES_H
#define SHARED_TOWN_POINTEES_H

/* Observed TOWN root pointees. Sizes below describe accessed layout only;
 * allocation ends and identities of nested pointers remain unproved.
 * Position +04/+08 are advanced by +10/+14 in the movement update; setters,
 * range tests and tile-to-world scaling independently use the same words.
 * +10/+14 also receive position copies, so no universal velocity name is used. */
typedef struct TownPositionState {
    /* 0x00 */ int unk_00;
    /* 0x04 */ int x;
    /* 0x08 */ int y;
    /* 0x0C */ unsigned char pad_0C[4];
    /* 0x10 */ int unk_10;
    /* 0x14 */ int unk_14;
    /* 0x18 */ int unk_18;
    /* 0x1C */ int unk_1C;
    /* 0x20 */ unsigned char pad_20[0x14];
    /* 0x34 */ int unk_34;
    /* 0x38 */ int unk_38;
    /* 0x3C */ int unk_3C;
    /* 0x40 */ void *unk_40;
} TownPositionState;

/* Root +24: +68 reaches another record, +70 reaches a buffer/map state.
 * Similarity to other shared layouts alone does not identify those objects. */
typedef struct TownResourceLinks {
    /* 0x00 */ unsigned char pad_00[0x68];
    /* 0x68 */ void *unk_68;
    /* 0x6C */ void *gridRows;
    /* 0x70 */ void *unk_70;
} TownResourceLinks;

/* Root +40 has indexed eight-byte views as well as these fixed fields.
 * No extent for that indexed region is asserted here. */
typedef struct TownEventCursor {
    /* 0x00 */ unsigned char pad_00[6];
    /* 0x06 */ unsigned char eventIndex; /* increments modulo seven before event-table indexing */
    /* 0x07 */ unsigned char counter; /* incremented and decremented; zero dispatch in func_80016824 */
} TownEventCursor;

typedef struct TownProgressState {
    /* 0x000 */ unsigned char pad_000[0x68];
    /* 0x068 */ TownEventCursor eventCursor;
    /* 0x070 */ unsigned char pad_070[0x40];
    /* 0x0B0 */ int unk_B0;
    /* 0x0B4 */ unsigned char pad_0B4[0x5C];
    /* 0x110 */ int unk_110;
    /* 0x114 */ signed char unk_114;
    /* 0x115 */ unsigned char pad_115[3];
} TownProgressState;
#endif
