#ifndef DUNGEON_SYSTEM_TOWN_MAP_ENTRY_PROCESSOR_G00214_H
#define DUNGEON_SYSTEM_TOWN_MAP_ENTRY_PROCESSOR_G00214_H
/* Town map entry processor shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:dungeon/bank_d0a0:800CFCA8. */

#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    u8 pad0[0x10];
    void (*cb)(void *);
    u8 pad14[0xC];
    s32 field_0x20;
} Node;

extern void process_indexed_entry_record(s32);

extern void *town_map_processor;

/* Functions defined in this translation unit. */
void advance_index_and_mark_completion(void *counterPtr);
void create_town_map_entry_processor(void);

#endif
