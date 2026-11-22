#ifndef SLUS_BLINKING_CURSOR_DATA_H
#define SLUS_BLINKING_CURSOR_DATA_H

#include "common.h"
#include "shared/sprite_part_command.h"

/* Three 12-byte source templates, at 0x8006A958, 0x8006A964, and
 * 0x8006A970. The page-offset copier reads three u32 values from each. */
extern SpritePartCommand blinking_cursor_texture_template_0;
extern SpritePartCommand blinking_cursor_texture_template_1;
extern SpritePartCommand blinking_cursor_texture_template_2;

/* The paired destination descriptors begin at 0x80082B50, 0x80082B60,
 * and 0x80082B70. The first two are 16 bytes apart; all three use
 * the same 16-byte descriptor contract and feed the cursor sprite. */
typedef struct BlinkingCursorDescriptor {
    SpritePartCommand part;
    u32 trailing_word;
} BlinkingCursorDescriptor;

extern BlinkingCursorDescriptor blinking_cursor_texture_descriptor_0;
extern BlinkingCursorDescriptor blinking_cursor_texture_descriptor_1;
extern BlinkingCursorDescriptor blinking_cursor_texture_descriptor_2;

/* Three pointer-sized variant entries before the template at 0x8006A988. */
extern void *texture_descriptor_variant_values[3];

#endif
