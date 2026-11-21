#ifndef SHARED_SPRITE_SOURCE_H
#define SHARED_SPRITE_SOURCE_H
/* Eight-byte source entries selected by func_8003DB94 (SLUS).
 * Its index advances by sizeof(entry)==8; byte zero is copied to sprite +05,
 * and the selected word +04 to sprite +08. Four dungeon source tables also
 * initialize that same sprite layout directly. The selected source points to a renderer command stream, or to another frame
 * entry for a type-1 sequence (advance_actor_step_sequence). The retail table
 * stride is eight bytes and each stored pointer occupies four guest bytes. */
/* Eight-byte entries in caller-supplied sprite source tables.
 * select_record_entry_and_value selects an entry and installs its command source in the sprite part. */
typedef struct SpriteSourceEntry {
    /* 0x00 */ unsigned char frame_ticks; /* table-base animation delay byte copied to sprite +5 when selecting a source entry */
    /* 0x01 */ unsigned char pad_01[3];
    /* 0x04 */ void *source; /* command stream or linked frame entry selected by the animation type */
} SpriteSourceEntry;
#endif
