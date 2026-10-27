#include "script_symbols.h"
#include "common.h"

s32 func_80017D9C(s32, s32);
extern void func_80018854(s32); /* placed copy of set_script_flag_bit */
s32 func_800188CC(s32);

typedef struct S_800164E8_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800164E8_0;   /* arg0 in process_scene_request_state */

/* Process the object identifier and 0x50C before forwarding the object and value. */
void process_scene_request_state(S_800164E8_0 *object, s32 value) {
    func_80018854(object->unk_18);
    func_800188CC(F_sbs07_pad21);
    func_80017D9C(object, value);
}
