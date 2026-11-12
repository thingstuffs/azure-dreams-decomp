#ifndef SLUS_BLINKING_CURSOR_DATA_H
#define SLUS_BLINKING_CURSOR_DATA_H

#include "common.h"

/* Three 12-byte source templates, at 0x8006A958, 0x8006A964, and
 * 0x8006A970. The page-offset copier reads three u32 values from each. */
extern u32 blinking_cursor_texture_template_0[3];
extern u32 blinking_cursor_texture_template_1[3];
extern u32 blinking_cursor_texture_template_2[3];

/* The paired destination descriptors begin at 0x80082B50, 0x80082B60,
 * and 0x80082B70. The first two are 16 bytes apart; all three use
 * the same 16-byte descriptor contract and feed the cursor sprite. */
extern u8 blinking_cursor_texture_descriptor_0[16];
extern u8 blinking_cursor_texture_descriptor_1[16];
extern u8 blinking_cursor_texture_descriptor_2[16];

#endif
