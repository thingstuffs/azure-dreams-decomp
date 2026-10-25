#include "town/scene.h"
#include "modules/town_ovl_3ef1c8.h"

/* Reports the alternate gate only when it first sets the override flag. */
s32 apply_scene_override_flag(s32 unused_first, s32 unused_second) {
    if (func_8001A510(0x79F) != 0) {
        return 0;
    }
    if (func_8001A510(0x1391) != 0) {
        func_8001A418(0x79F);
        return 0;
    }
    if (func_8001A510(0x1389) != 0) {
        func_8001A418(0x79F);
        return 1;
    }
    return 0;
}
