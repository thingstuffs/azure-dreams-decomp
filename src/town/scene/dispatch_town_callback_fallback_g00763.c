/* Dispatch town callback fallback g00763.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00763 - CL:town/func_80774928.
 */
#include "town/scene/dispatch_town_callback_fallback_g00763.h"

/* Runs the current town cell's callback, or installs shared buffer pointers when the callback is absent. */
void dispatch_town_callback_or_fallback(s32 value0, s32 value1)
{
    void *ptr;
    s32 callbackIndex;

    ptr = town_scene_root;

    callbackIndex = ((Rec_D_80016000 *)ptr)->entry_index;
    ptr = ((Rec_D_80016000 *)ptr)->event_data;
    ptr = (u8 *)ptr + callbackIndex * sizeof(CallbackEntry);
    ptr = *(void **)ptr;

    if (ptr == 0) {
        set_shared_buffer_pointers(value0, value1);
        return;
    }
    ((Callback)ptr)();
}

void set_shared_buffer_pointers(s32 unused0, s32 unused1) {
    D_800174D8 = D_80017404;
    ((State *)town_scene_root)->child->value = D_8001770A;
}
