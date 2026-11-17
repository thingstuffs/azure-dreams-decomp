#include "common.h"
#include "shared/object_flags.h"
#include "engine/item.h"
#include "engine/resource.h"
#include "town/shop/state.h"
#include "town/shop/storage_menu.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_800B5020(void *a0);

/* Releases display entries and linked resources, then marks the object and global list for cleanup. */
void release_storage_owner_menu(StorageMenuNode *object)
{
    StorageMenuObject *resourceFields;
    u16 objectFlags;
    s32 globalFlags;

    if (object != NULL) {
        resourceFields = &object->menu;
        release_null_terminated_entries(object->menu.allocations);
        flag_object_for_removal((u16 *)resourceFields->data);
        func_800B5020(resourceFields->parts);
        objectFlags = object->header.flags | 0x8000;
        globalFlags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        object->header.flags = objectFlags;
        object_flag_block.flags = globalFlags;
    }
}
