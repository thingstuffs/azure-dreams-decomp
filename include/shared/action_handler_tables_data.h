#ifndef SHARED_ACTION_HANDLER_TABLES_DATA_H
#define SHARED_ACTION_HANDLER_TABLES_DATA_H

#include "common.h"

/* The next named objects begin eight bytes after each table. */
extern s32 action_object_handler_table[2];
extern s32 movement_action_handler_table[2];
extern s32 countdown_action_handler_table[2];

/* Scene dispatch selects a word by the record index. The placed tables have
 * separate bindings, so this declaration leaves their extents open. */
extern s32 town_scene_record_handlers[];

#endif
