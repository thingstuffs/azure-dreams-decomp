#ifndef ENGINE_WINDOW_CURSOR_INIT_H
#define ENGINE_WINDOW_CURSOR_INIT_H

#include "common.h"
#include "records/Rec_D_80081FDC.h"

void init_cursor_display_object(void *object, void *display, s32 *data, s16 data_index, s16 table_offset, void *list_head);
void init_cursor_sprite_object(void *node_addr, Rec_D_80081FDC *transform, s32 *script_data, s16 cursor_offset, s32 sprite_base, void *owner);

#endif
