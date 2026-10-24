#include "common.h"
#include "m2c_compat.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"

typedef struct S_80027A68_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0x4];
    void *request;
} S_80027A68_0;   /* arg0 in func_80027A68 */

/* Store the supplied field values and capture the helper result. */
void card_boot_init_channel_record(S_80027A68_0 *record, void *request, s32 value_00) {
    record->request = request;
    record->unk_00 = value_00;
    record->unk_0C = card_boot_has_selected_channel();
}
