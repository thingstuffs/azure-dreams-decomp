#ifndef MORE_FRAGMENT_C0BEC_H
#define MORE_FRAGMENT_C0BEC_H
#include "common.h"
void *get_unused_text_buffer();
void *clear_byte_and_advance(s8 *byte_ptr);
s32 display_text_with_fullwidth_adjustment(s8 *text);
#endif
