#ifndef ENGINE_TEXT_GLYPH_BODY_H
#define ENGINE_TEXT_GLYPH_BODY_H
#include "common.h"
/* Common observed prefix of the text nodes drawn by build_text_glyph_sprites.
 * create_settings_color_effect copies 0x30 bytes; callback-specific tail and
 * owner fields are intentionally not inferred here. */
typedef struct TextGlyphBody {
    u8 pad_00[4];
    u8 *text;
    u8 pad_08[8];
    s32 color;
    s16 x;
    u16 y;
    s16 blend_mode;
    u16 clut;
    u16 flags;
} TextGlyphBody;
#endif
