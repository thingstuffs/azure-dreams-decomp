#ifndef SHARED_DUNGEON_ITEM_ENTRIES_H
#define SHARED_DUNGEON_ITEM_ENTRIES_H
/* Four-byte item records. The second byte is zero in a free slot and is
 * compared with item kinds (including 0x13). The loader writes all four bytes;
 * whole-word copies retain explicit word views. Sixty-four entries are cleared
 * with 0x100 bytes and scanned with a bound of 64. D_800E3648 is separate. */
/* Four-byte item descriptor in the floor item pool.
 * reset_dungeon_runtime_state clears 64 entries; the floor spawn routine fills free entries. */
typedef struct DungeonItemEntry {
    /* 0x00 */ unsigned char unk_00; /* item subtype within the category stored in kind */
    /* 0x01 */ unsigned char kind; /* item category; zero marks a free entry in the 64-slot floor pool */
    /* 0x02 */ signed char amount; /* signed per-item value (enhancement or charges); the item-name formatter prints it signed */
    /* 0x03 */ unsigned char unk_03;
} DungeonItemEntry;
extern DungeonItemEntry dungeon_ground_items[64];
/* Copy of the selected floor item, or a two-byte lookup result with kind 0x14. */
extern DungeonItemEntry temporary_item_record;

/* Position metadata paired with a floor item. The floor generators walk
 * twelve-byte entries. Setup clears 64 entries with 0x300 bytes. The lift and
 * drop paths read both heights. The renderer consumes the sprite source at +8. */
typedef struct DungeonItemPosition {
    unsigned char x;
    unsigned char y;
    short height;
    short ground_height;
    unsigned char pad_06;
    unsigned char field_07;
    int sprite_source_word; /* 32-bit address returned by get_item_sprite_source */
} DungeonItemPosition;
extern DungeonItemPosition dungeon_ground_item_positions[64];
#endif
