#ifndef SHARED_ANIMATION_VIEWS_H
#define SHARED_ANIMATION_VIEWS_H
#include "common.h"
/* Byte-matching workaround: retain the packed four-word copy for animation
 * entries with a 0x16 stride and only two-byte alignment. A naturally
 * two-aligned spelling remains a follow-up; this is not a final game layout. */
typedef struct { s32 words[4]; } __attribute__((packed)) PackedWords4;
/* One animation entry; the explicit tail byte preserves its measured stride. */
/* Borrowed 22-byte animation table entry; update_traveling expands it into a current-frame block.
 * The animation owner supplies the table; its allocator is not established here. */
typedef struct AnimEntry {
    PackedWords4 words;
    s16 field_10;
    s8 field_12; /* widened to dst->field_14 */
    s8 field_13; /* widened to dst->field_18 */
    s8 field_14; /* widened to dst->field_1C */
    u8 pad_15;
} AnimEntry;
/* Caller-owned animation cursor; set_animation_entry_address resolves the entry through its owner.
 * advance_animation_index_within_bounds steps and clamps the signed entry index. */
typedef struct AnimPlayer {
    s32 entry; /* current entry address, owner table base plus signed index * 22 bytes */
    u8 index; /* current animation entry index, interpreted as signed for bounds checks */
    u8 pad_05[3];
    void *owner; /* animation owner whose +0x0C word supplies the entry table base */
    u8 pad_0C[8];
    u16 flags; /* animation cursor flags; bit 0x4000 marks a clamped index and is cleared in range */
} AnimPlayer;
/* Caller-provided animation table owner, followed by the animation cursor helpers.
 * This sparse view does not establish an allocation boundary. */
typedef struct AnimOwner { u8 pad_00[0xC]; s32 table; /* base address of the animation table with 22-byte entries */ } AnimOwner;

/* Exact access views shared across registered binary consumers. */
/* Leading unsigned frame value divided by the animation rate divisor. */
/* Leading halfword of a caller-owned animation frame entry, selected by set_sprite_animation_frame. */
typedef struct AnimationFrameRate {
    /* 0x00 */ unsigned short value; /* frame rate/delay value divided by animation_tick_scale before storage at sprite +5 */
} AnimationFrameRate;

#endif
