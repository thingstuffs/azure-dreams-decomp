#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

s32 func_80018BD0(s32);
s32 func_80018C50(s32 flagIndex);                         /* extern */

/* Process 0xFB7 and 0xFB8, then return whether the 0xFC0 check succeeds. */
s32 process_succeeds(void) {
    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);
    return func_80018C50(Fr_cheriru_scene03) != 0;
}
