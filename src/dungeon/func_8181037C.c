#include "common.h"

extern s32 dungeonAllocateItemObject(s32, s32, s32, s32, s32);

/* Create an item view with the supplied contexts, mode, descriptor, and data. */
void func_8002537C(s32 context, s32 related_context, s32 mode, s32 item_id, s32 item_data) {
    dungeonAllocateItemObject(context, related_context, mode, item_id, item_data);
}
