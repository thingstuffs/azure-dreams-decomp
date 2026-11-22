#ifndef ENGINE_WINDOW_CURSOR_INIT_H
#define ENGINE_WINDOW_CURSOR_INIT_H

#include "common.h"
struct WindowCursorSource;
#include "records/Rec_D_80081FDC.h"

struct MenuChoiceCursorStorage;

void init_cursor_display_object(struct MenuChoiceCursorStorage *object, Rec_D_80081FDC *display, struct WindowCursorSource *data, s16 data_index, s16 table_offset, void *list_head);
void init_cursor_sprite_object(struct MenuChoiceCursorStorage *storage, Rec_D_80081FDC *transform, struct WindowCursorSource *script_data, s16 cursor_offset, s32 sprite_base, void *owner);

struct Object;
void handle_two_column_menu_input(struct Object *menu, void *unused_1, void *unused_2);

struct Object;
void handle_two_column_menu_input(struct Object *menu, void *unused_1, void *unused_2);

#endif
