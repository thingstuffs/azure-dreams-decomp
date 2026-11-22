#include "engine/window/cursor_source.h"
#include "sdk/libgpu.h"

/* Copy the sprite part and translate its page and UV coordinates into the window. */
void copy_texture_descriptor_with_page_offsets(TEX_RECT *texture, SpritePartCommand *source, SpritePartCommand *destination) {
    u32 *source_words = (u32 *)source;
    u32 *destination_words = (u32 *)destination;

    destination_words[0] = source_words[0];
    destination_words[1] = source_words[1];
    destination_words[2] = source_words[2];
    destination->tpage = GetTPage(0, 1, texture->page_x, texture->page_y);
    destination->data.texture.u0 += texture->tex_x + (texture->page_x % 64) * 4;
    destination->data.texture.v0 += (texture->page_y % 256) + texture->tex_y;
}
