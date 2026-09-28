#ifndef SHARED_DEF_TABLE_H
#define SHARED_DEF_TABLE_H

/* D_8006DE24 (SLUS .data): a read-only table of 0x14-byte definition records indexed by an item / action id (rows
 * call it item_defs, action_table, ability_table, MotionEntry - what the ids name is not proven, so the type stays
 * DefEntry).  Rows reach it by index only (census/cde24.jsonl, r78 phase 8: 60 rows); read-only (lw/lbu).
 *   kind (+0x12): lbu 49 - compared with 2 by nearly every user (`D_8006DE24[id].kind == 2`).
 *   +0x10 / +0x11 / +0x13: lbu; +0x00 / +0x08: lw.  Other fields stay unk_. */
typedef struct DefEntry {
    /* 0x00 */ int unk_00;
    /* 0x04 */ int unk_04;
    /* 0x08 */ int unk_08;
    /* 0x0C */ int unk_0C;
    /* 0x10 */ unsigned char unk_10;
    /* 0x11 */ unsigned char unk_11;
    /* 0x12 */ unsigned char kind;
    /* 0x13 */ unsigned char unk_13;
} DefEntry;

extern DefEntry D_8006DE24[];

#endif
