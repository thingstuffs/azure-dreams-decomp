#ifndef SHARED_TOWN_STATE_H
#define SHARED_TOWN_STATE_H

/* Record reached through the town root at +0x38. These are observed fields,
 * not a claim about the full allocation size. +0x2D5C is both threshold-tested
 * and incremented/decremented; its game meaning is not established. Unsigned
 * matches the comparisons and /100 arithmetic; signed views retain casts.
 * The list has twenty usable entries plus its zero terminator. The allocator
 * rejects indices >=20; compaction writes the terminator after twenty entries.
 * The history writer shifts twelve bytes per group; readers iterate sixteen
 * groups. Head indices wrap at the per-group limit. Allocation end unknown. */
/* The slot serializer reads bytes 0/1 as x/y indices into the grid. A slot
 * is four bytes: the allocator scales by four and the serializer copies four.
 * Only bit 7 of the last byte is identified here (set for a zero grid field). */
typedef struct TownListEntry {
    /* 0x00 */ unsigned char gridX;
    /* 0x01 */ unsigned char gridY;
    /* 0x02 */ unsigned char unk_02;
    /* 0x03 */ unsigned char flags;
} TownListEntry;

typedef struct TownStateRecord {
    /* 0x0000 */ unsigned char pad_0000[0x248];
    /* 0x0248 */ TownListEntry slots[20];
    /* 0x0298 */ unsigned char pad_0298[4];
    /* 0x029C */ void *entries[21];
    /* 0x02F0 */ unsigned char pad_02F0[0x2A6C];
    /* 0x2D5C */ unsigned int unk_2D5C;
    /* 0x2D60 */ int unk_2D60;
    /* 0x2D64 */ unsigned char pad_2D64[4];
    /* 0x2D68 */ unsigned int unk_2D68;
    /* 0x2D6C */ unsigned char pad_2D6C[0x41C];
    /* 0x3188 */ int unk_3188;
    /* 0x318C */ unsigned char pad_318C[0x430];
    /* 0x35BC */ short unk_35BC;
    /* 0x35BE */ short unk_35BE;
    /* 0x35C0 */ short unk_35C0;
    /* 0x35C2 */ unsigned char pad_35C2[0x7E];
    /* 0x3640 */ unsigned char history[16][12];
    /* 0x3700 */ unsigned char headIndices[16];
} TownStateRecord;

#endif
