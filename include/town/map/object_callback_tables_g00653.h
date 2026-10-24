#ifndef TOWN_MAP_OBJECT_CALLBACK_TABLES_G00653_H
#define TOWN_MAP_OBJECT_CALLBACK_TABLES_G00653_H
/* inferred-strong G00653: object_callback_tables_g00653; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D4668. */

#include "common.h"
#include "shared/object_node.h"

#include "town/map/trigger_callbacks.h"

typedef map_trigger_callback_fn Callback;

extern u8 D_800C1E50[];
extern u8 town_map_trigger_handler[];

/* Functions defined in this translation unit. */
void initialize_object_and_replace_callbacks(void);
void invoke_callbacks_until_terminator(void);

#endif
