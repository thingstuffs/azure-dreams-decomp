#ifndef TOWN_SHOP_OBJECT_COMPONENT_REFRESH_G00626_H
#define TOWN_SHOP_OBJECT_COMPONENT_REFRESH_G00626_H
/* Refresh paired object components and their high flags: shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B6EE8. */

#include "common.h"
#include "shared/object_flags.h"
struct StorageMenuObject;
struct StorageMenuNode;

void flag_optional_object_for_removal(void *object);
extern void release_null_terminated_entries(void *entries);

/* Functions defined in this translation unit. */
void release_paired_entry_objects(struct StorageMenuObject *owner);
void release_storage_item_menu(struct StorageMenuNode *object);

#endif
