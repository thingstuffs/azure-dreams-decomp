#ifndef TOWN_SCENE_ENTRY_OUTPUT_H
#define TOWN_SCENE_ENTRY_OUTPUT_H

#include "common.h"

s32 *prepare_selected_entry_buffer(s32 entry_index);
void *build_selected_record_buffer(s32 entry_index);
/* Placed entry point for build_selected_record_buffer. */
void *func_8001AA80(s32 entry_index);

#endif
