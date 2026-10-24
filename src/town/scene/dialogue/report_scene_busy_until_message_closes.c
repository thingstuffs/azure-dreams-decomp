#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 (*TownCallback)(s32, s32);

extern s32 func_8001A64C(s32);
extern void func_8001A7AC(void);

/* Scene step: while message 0x932 is up report busy, else close it and post event 0xE. */
s32 report_scene_busy_until_message_closes(void) {
    s32 result;

    set_script_flag_94c();
    if (func_8001A64C(F_sbs32_pad08) == 0) {
        func_8001A7AC();
        (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)((s8 *)(&town_scene_root)) + 0x20) + 0x2F8))(0xE, 0x200);
        result = 0;
    } else {
        result = 1;
    }
    return result;
}
