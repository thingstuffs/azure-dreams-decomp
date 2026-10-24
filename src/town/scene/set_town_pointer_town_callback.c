#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*TownCallback)(s32, s32);

extern s32 func_8001A64C(s32);
extern s8 D_8001C921[];

/* Sets the town owner's data pointer and invokes a town callback if the 0x939 check returns zero. */
s32 set_town_pointer_town_callback(void) {
    void *town;
    void *townOwner;
    void *callbackTable;
    TownCallback callback;

    set_script_flag_94c();
    if (func_8001A64C(F_sbs32_pad15) != 0) {
        return 1;
    }

    town = *(void **)((s8 *)(&town_scene_root));
    townOwner = *(void **)((s8 *)town + 0x1C);
    *(void **)((s8 *)townOwner + 0x40) = D_8001C921;

    callbackTable = *(void **)((s8 *)town + 0x20);
    callback = *(TownCallback *)((s8 *)callbackTable + 0x2F8);
    callback(0xF, 0x200);
    return 0;
}
