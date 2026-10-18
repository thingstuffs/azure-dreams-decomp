#ifndef SLUS_LIST_CURSOR_E0_H
#define SLUS_LIST_CURSOR_E0_H

#include "common.h"

/* Word view of external storage; its complete extent is not established. */
extern s32 D_80083C68[];
extern s32 *D_800814E0;

void reset_scene_frame_callback_list(void);
void append_terminated_runtime_word(s32 value);
void remove_runtime_callback(s32 value);

#endif
