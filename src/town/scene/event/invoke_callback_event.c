#include "common.h"
#include "town/scene/event.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef s32 (*TownCallback)(s32, s32);


/* Invoke the town callback with event 0x11 and value 0x200. */
s32 invoke_callback_event_11(void) {
    return ((TownCallback)(town_scene_root->services->callback_2F8))(0x11, 0x200);
}
