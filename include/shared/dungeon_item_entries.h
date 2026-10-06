#ifndef SHARED_DUNGEON_ITEM_ENTRIES_H
#define SHARED_DUNGEON_ITEM_ENTRIES_H
/* Four-byte item records. The second byte is zero in a free slot and is
 * compared with item kinds (including 0x13). The loader writes all four bytes;
 * whole-word copies retain explicit word views. Sixty-four entries are cleared
 * with 0x100 bytes and scanned with a bound of 64. D_800E3648 is separate. */
typedef struct DungeonItemEntry {
    /* 0x00 */ unsigned char unk_00;
    /* 0x01 */ unsigned char kind;
    /* 0x02 */ unsigned char unk_02;
    /* 0x03 */ unsigned char unk_03;
} DungeonItemEntry;
extern DungeonItemEntry D_800E3548[64];
#endif
