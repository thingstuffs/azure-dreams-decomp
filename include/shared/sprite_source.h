#ifndef SHARED_SPRITE_SOURCE_H
#define SHARED_SPRITE_SOURCE_H
/* Eight-byte source entries selected by func_8003DB94 (SLUS).
 * Its index advances by sizeof(entry)==8; byte zero is copied to sprite +05,
 * and the selected word +04 to sprite +08. Four dungeon source tables also
 * initialize that same sprite layout directly. The word's encoding and the
 * tables' allocation extents remain unknown; signed/unsigned reads coexist. */
typedef struct SpriteSourceEntry {
    /* 0x00 */ unsigned char unk_00;
    /* 0x01 */ unsigned char pad_01[3];
    /* 0x04 */ int unk_04;
} SpriteSourceEntry;
#endif
