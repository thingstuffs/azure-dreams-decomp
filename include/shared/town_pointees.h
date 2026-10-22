#ifndef SHARED_TOWN_POINTEES_H
#define SHARED_TOWN_POINTEES_H

/* Observed TOWN root pointees. Sizes below describe accessed layout only;
 * allocation ends and identities of nested pointers remain unproved.
 * Position +04/+08 are advanced by +10/+14 in the movement update; setters,
 * range tests and tile-to-world scaling independently use the same words.
 * +10/+14 also receive position copies, so no universal velocity name is used. */
/* Position/auxiliary state owned through the town root at +0x1C.
 * Scene coordinate setters write x/y; the allocation initializer remains unproven. */
typedef struct TownPositionState {
    /* 0x00 */ int unk_00;
    /* 0x04 */ int x; /* town X position; tile-based setters scale coordinates by 64 before adding offsets */
    /* 0x08 */ int y; /* town Y position; tile-based setters scale coordinates by 64 before adding offsets */
    /* 0x0C */ unsigned char pad_0C[4];
    /* 0x10 */ int unk_10; /* auxiliary X word; movement adds it to x, other callbacks store position copies */
    /* 0x14 */ int unk_14; /* auxiliary Y word; movement adds it to y, other callbacks store position copies */
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
/* Resource/table graph reached through the town scene root at +0x24.
 * Scene serializers follow gridRows; its allocating initializer remains untraced. */
typedef struct TownResourceLinks {
    /* 0x00 */ unsigned char pad_00[0x68];
    /* 0x68 */ void *unk_68;
    /* 0x6C */ void *gridRows; /* grid row directory with 0x14-byte entries; row +0x0C points to cell records */
    /* 0x70 */ void *unk_70;
} TownResourceLinks;

/* Root +40 has indexed eight-byte views as well as these fixed fields.
 * No extent for that indexed region is asserted here. */
/* Event cursor within the town root progress state, updated by scene event callbacks.
 * The seven-entry event selector wraps eventIndex; the adjacent counter controls countdown dispatch. */
typedef struct TownEventCursor {
    /* 0x00 */ unsigned char pad_00[6];
    /* 0x06 */ unsigned char eventIndex; /* event table index, incremented modulo 7 */
    /* 0x07 */ unsigned char counter; /* scene countdown byte; decremented and dispatched when it reaches zero */
} TownEventCursor;

/* Town event/progress context reached through the scene root at +0x40.
 * Event callbacks update its embedded cursor; the remaining fields have callback-specific uses. */
typedef struct TownProgressState {
    /* 0x000 */ unsigned char pad_000[0x68];
    /* 0x068 */ TownEventCursor eventCursor; /* seven-entry event selector and countdown byte */
    /* 0x070 */ unsigned char pad_070[0x40];
    /* 0x0B0 */ int unk_B0;
    /* 0x0B4 */ unsigned char pad_0B4[0x5C];
    /* 0x110 */ int unk_110;
    /* 0x114 */ signed char unk_114;
    /* 0x115 */ unsigned char pad_115[3];
} TownProgressState;

/* Exact access views shared across registered binary consumers. */
/* Item-panel callback's selected value, separate from motion and event entries. */
typedef struct TownPanelSelectionView {
    unsigned char pad_00[8];
    int unk_08;
} TownPanelSelectionView;

/* Format callback's kind value, separate from coordinate Z. */
typedef struct TownFormatKindView {
    unsigned char pad_00[8];
    int unk_08;
} TownFormatKindView;

/* Town resource group selector at +0xA, separate from signed motion height. */
typedef struct TownResourceGroupView {
    unsigned char pad_00[0xA];
    short unk_0A;
} TownResourceGroupView;

/* Town search work reads the pointer and its signed high half in distinct paths.
 * Preserve both live alternatives; this view cannot become ObjectPayloadView. */
typedef struct TownSearchWorkView {
    unsigned char pad_00[8];
    union {
        struct { void *v; } at00;
        struct { unsigned char pad[2]; short v; } at02;
    } unk_08;
} TownSearchWorkView;

/* Resource holder reached through TownResourceLinks, without allocator proof. */
typedef struct TownNestedPayloadView {
    unsigned char pad_00[8];
    void *unk_08;
} TownNestedPayloadView;

/* Signed nested resource value; its +0xA offset alone does not establish height. */
typedef struct TownNestedRecordValueView {
    unsigned char pad_00[0xA];
    short unk_0A;
} TownNestedRecordValueView;

/* Grid-output callback word selected from the controller's two source values.
 * Its pointer is a callback output, not proven to be a delayed motion record. */
typedef struct TownGridOutputView {
    unsigned char pad_00[8];
    int unk_08;
} TownGridOutputView;

/* Destination Y word rooted at the town context's +0x1C position state.
 * Keep this separate from the delayed effect's Z coordinate. */
typedef struct TownDestinationYView {
    unsigned char pad_00[8];
    int unk_08;
} TownDestinationYView;

#endif
