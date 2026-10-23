#ifndef ENGINE_WINDOW_MESSAGE_H
#define ENGINE_WINDOW_MESSAGE_H
/* Prototypes of the functions defined in src/engine/window/message/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_80035ABC_0;
struct S_80035C44_0;
struct Rec_func_80036210_arg0;
struct S_80036988_0;
struct S_80036988_1;

/* copy_window_offset_rectangle.c */
void copy_window_offset_rectangle(struct S_80036988_0 *destination, struct S_80036988_1 *source);

/* grow_window_extent_to_sixty_four.c */
void grow_window_extent_to_sixty_four(struct Rec_func_80036210_arg0 *state, struct S_80035C44_0 *progress);

/* queue_window_texture_draw_mode.c */
void queue_window_texture_draw_mode(s32 ot_index);

/* shrink_window_extent_to_two.c */
void shrink_window_extent_to_two(struct Rec_func_80036210_arg0 *state, struct S_80035ABC_0 *entry);

#endif
