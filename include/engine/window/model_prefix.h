#ifndef ENGINE_WINDOW_MODEL_PREFIX_H
#define ENGINE_WINDOW_MODEL_PREFIX_H
#include "common.h"
/* The model installed by create_window_object exposes this unsigned halfword
 * to both window animation callbacks. No complete model extent is claimed. */
typedef struct WindowModelPrefix {
    u8 pad_00[8];
    u16 unk_08;
} WindowModelPrefix;
#endif
