#include "common.h"

extern s32 allocate_item_object(s32, s32, s32, s32, s32);

/* Create an item view with the supplied contexts, mode, descriptor, and data. */
void create_item_view(s32 context, s32 related_context, s32 mode, s32 item_id, s32 item_data) {
    allocate_item_object(context, related_context, mode, item_id, item_data);
}
