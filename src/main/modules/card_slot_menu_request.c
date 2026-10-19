/* Card slot menu request and its file-private helper. */
#include "common.h"
#include "m2c_compat.h"
/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80025B38_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025B38_0;
/* cfail-repair: tf7-phase1-cache-v3 */
static void card_boot_set_slot_menu_request();

static void card_boot_set_slot_menu_request(S_80025B38_0 *object, s32 value) {
    object->unk_20 = value;
}

void card_boot_initialize_slot_menu_request(void *object, s32 value) {
    card_boot_set_slot_menu_request(object, value);
}
