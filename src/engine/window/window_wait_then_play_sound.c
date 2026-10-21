#include "common.h"

#include "common.h"
#include "engine/effect.h"
#include "engine/resource.h"
#include "engine/window.h"
#include "engine/window/message.h"

typedef struct Func80035BE0State {
    u8 pad00[0x64];
    u16 counter;
    u8 pad66[2];
    void (*callback)(void *, void *);
    u8 pad6c[0x0c];
    u8 sound_id;
    s8 sound_arg;
} Func80035BE0State;

/* Count down, then play the configured sound and advance the callback. */
void window_wait_then_play_sound(Func80035BE0State *state) {
    u16 counter;

    counter = state->counter;
    counter--;
    state->counter = counter;
    if ((s16)counter < 0) {
        activate_indexed_resource_and_upload_images(state->sound_id, state->sound_arg);
        initialize_shared_sprite_fade_display();
        state->callback = grow_window_extent_to_sixty_four;
    }
}
