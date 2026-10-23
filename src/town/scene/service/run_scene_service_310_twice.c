#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*TownCallback)(s32, s32, s32);


// Invoke the town callback twice with command 0x2B, passing 0x9000 then zero.
void run_scene_service_310_twice(void)
{
    (*(TownCallback *)((s8 *)*(void **)((u8 *)town_scene_root + 0x20) + 0x310))(
        0x2B, 0x200, 0x9000);
    (*(TownCallback *)((u8 *)*(void **)((u8 *)town_scene_root + 0x20) + 0x310))(
        0x2B, 0x200, 0);
}
