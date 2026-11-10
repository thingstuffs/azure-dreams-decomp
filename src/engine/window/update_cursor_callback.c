#include "common.h"

#include "engine/window.h"
#include "slus.h"

/* Advances sprite animation when unlink_cursor_when_finished returns zero. */
void update_cursor_callback(WindowCursorBody *state, ObjectPosition *position, SpriteFrameState *sprite) {
    if (unlink_cursor_when_finished((struct Func37534State *)state) == 0) {
        advance_sprite_animation_and_textures(sprite);
    }
}
