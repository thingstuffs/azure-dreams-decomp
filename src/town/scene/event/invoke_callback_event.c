#include "common.h"
#include "town/scene/event.h"
#include "shared/record_ptrs.h"

typedef s32 (*TownCallback)(s32, s32);


/* Invoke the town callback with event 0x11 and value 0x200. */
s32 invoke_callback_event_11(void) {
    return (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)((s8 *)(&town_scene_root)) + 0x20) + 0x2F8))(0x11, 0x200);
}
