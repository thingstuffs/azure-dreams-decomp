#ifndef ENGINE_NODE_ALLOCATION_H
#define ENGINE_NODE_ALLOCATION_H

#include "common.h"
#include "shared/object_node.h"

/* Object-pool allocation and list initialization. */
/* allocate_list_node.c */
void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);

/* evict_node_and_allocate.c */
void *evict_node_and_allocate(s32 flags, void *excluded_node);

/* initialize_runtime_node_storage.c */
/* Caller-owned node storage and the slot holding its list head. */
void *initialize_runtime_node_storage(s32 flags, void *storage, s16 word_count, void *list_storage);

#endif
