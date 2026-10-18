#include "common.h"

extern void store_supplied_values(s32, s32);
extern s32 func_80017D9C(s32, s32);
extern void call_helper_with_fixed_id_0x118a(s32);
extern s32 func_8001894C(s32);
extern s16 D_80018AEA[];

/* Process the object action when flag 0x510 is set, otherwise update flag 0x511. */
s32 process_scene_action_flag(s32 object, s32 context) {
    store_supplied_values(object, context);
    if (func_8001894C(0x510) != 0) {
        return func_80017D9C(object, context);
    }
    if (func_8001894C(D_80018AEA[0]) == 0) {
        call_helper_with_fixed_id_0x118a(0x511);
    }
    return 0;
}
