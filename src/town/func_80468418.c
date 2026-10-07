#include "shared/town_event_state.h"
#include "common.h"

extern u32 func_8001E670(s32 condition_id);
extern s32 func_8001E82C(void);
extern void func_800196A4(void);

extern u8 D_80018A30[];

/* Shop tick: on an idle counter, run the 0x1E82C check and bump the pending count. */
u8 *func_80019418(void) {
    if (func_8001E670(20) == 0) {
        return D_80018A30;
    }
    if (func_8001E82C() != 0) {
        func_800196A4();
    }
    D_8001E950->unk_00 += 1;
    return (u8 *)0;
}
