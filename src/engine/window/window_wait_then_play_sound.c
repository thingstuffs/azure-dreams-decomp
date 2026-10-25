#include "common.h"

#include "common.h"
#include "engine/effect.h"
#include "engine/resource.h"
#include "engine/window.h"
#include "engine/window/message.h"

struct Rec_func_80036210_arg0;
struct S_80035C44_0;

typedef struct Func80035BE0State {
    u8 pad00[0x64];
    u16 counter;
    u8 pad66[2];
    void (*callback)(struct Rec_func_80036210_arg0 *, struct S_80035C44_0 *);
    u8 pad6c[0x0c];
    u8 resource_group;
    s8 resource_index;
} Func80035BE0State;

/* Count down, activate the selected graphics resource, and advance the callback. */
void activate_delayed_window_resource(Func80035BE0State *state) {
    u16 counter;

    counter = state->counter;
    counter--;
    state->counter = counter;
    if ((s16)counter < 0) {
        activate_indexed_resource_and_upload_images(state->resource_group, state->resource_index);
        initialize_shared_sprite_fade_display();
        state->callback = grow_window_extent_to_sixty_four;
    }
}
