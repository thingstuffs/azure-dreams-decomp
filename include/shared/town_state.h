#ifndef SHARED_TOWN_STATE_H
#define SHARED_TOWN_STATE_H

/* Record reached through the town root at +0x38. These are observed fields,
 * not a claim about the full allocation size. +0x2D5C is both threshold-tested
 * and incremented/decremented; its game meaning is not established. Unsigned
 * matches the comparisons and /100 arithmetic; signed views retain casts.
 * The pointer list beginning at +0x29C and byte regions +0x3640/+0x3700 need
 * further extent/type evidence and remain padding in this partial layout. */
typedef struct TownStateRecord {
    /* 0x0000 */ unsigned char pad_0000[0x2D5C];
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
} TownStateRecord;

#endif
