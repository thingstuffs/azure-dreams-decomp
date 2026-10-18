#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017D9C();             /* extern */
M2C_UNK call_helper_with_fixed_id_0x118a();                         /* extern */
M2C_UNK func_800188CC();                     /* extern */

typedef struct S_800164E8_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800164E8_0;   /* arg0 in process_scene_request_state */

/* Process the object identifier and 0x50C before forwarding the object and value. */
void process_scene_request_state(S_800164E8_0 *object, M2C_UNK value) {
    call_helper_with_fixed_id_0x118a(object->unk_18);
    func_800188CC(0x50C);
    func_80017D9C(object, value);
}
