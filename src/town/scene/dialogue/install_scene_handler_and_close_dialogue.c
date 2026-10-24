#include "town/scene.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*TownCallback)(s32, s32);

extern void func_8001A7AC(void);
extern s8 D_8001BCB4[];

/* Scene entry: install the D_8001BCB4 handler, close the dialogue and post event 0xE. */
s32 install_scene_handler_and_close_dialogue(void) {
    set_script_flag_94c();
    *(void **)((s8 *)*(void **)((s8 *)*(void **)((s8 *)(&town_scene_root)) + 0x1C) + 0x40) = D_8001BCB4;
    func_8001A7AC();
    (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)((s8 *)(&town_scene_root)) + 0x20) + 0x2F8))(0xE, 0x200);
    return 0;
}
