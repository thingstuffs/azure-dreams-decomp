#ifndef ENGINE_NODE_REGISTRATION_H
#define ENGINE_NODE_REGISTRATION_H

#include "common.h"

struct ObjectNodeHeader;

s32 register_node(struct ObjectNodeHeader *entry, void *registration_id);
void unlink_node_if_registered(void *block_data);

#endif
