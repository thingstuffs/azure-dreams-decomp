#ifndef ENGINE_MENU_ANIMATED_SELECTION_BODY_H
#define ENGINE_MENU_ANIMATED_SELECTION_BODY_H

#include "common.h"

/* Control words in the body created by create_animated_selection_menu.
 * The callback and entry/actor-link prefix remains opaque. */
typedef struct AnimatedSelectionMenuBody {
    u8 pad_00[0x24];
    s32 count;
    s32 transition_frames;
    s32 transition_tick;
    s32 selected_index;
    s32 previous_index;
    s32 repeat_ticks;
} AnimatedSelectionMenuBody;

#endif
