#ifndef ENGINE_WINDOW_CURSOR_SOURCE_H
#define ENGINE_WINDOW_CURSOR_SOURCE_H

#include "engine/window.h"
#include "shared/sprite_part_command.h"

/* The message selector fills the rectangle at window +0x0C. Cursor updates
 * use its origin and UV offsets when they copy a sprite part into the window. */
typedef struct WindowCursorSource {
    s32 initial_value;
    u8 pad_04[8];
    TEX_RECT texture;
} WindowCursorSource;

void copy_texture_descriptor_with_page_offsets(TEX_RECT *texture, SpritePartCommand *source, SpritePartCommand *destination);

#endif
