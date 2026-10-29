#include "common.h"

extern void *allocate_item_object(s32, s32, s32, void *, s32);

/* Create an item view with the supplied contexts, mode, descriptor, and data; returns the view object. */
void *create_item_view(s32 context, s32 related_context, s32 mode, void *descriptor, s32 item_data) {
    return allocate_item_object(context, related_context, mode, descriptor, item_data);
}
