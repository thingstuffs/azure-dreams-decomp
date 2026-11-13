#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H
/* Prototypes of the functions defined in src/engine/input/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* get_pad_buttons.c */
s32 get_held_pad_buttons(void);

/* get_pad_trigger_buttons.c */
s32 get_pressed_pad_buttons(void);

#endif
