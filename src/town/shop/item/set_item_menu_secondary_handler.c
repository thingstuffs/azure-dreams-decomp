#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800AE494;

typedef struct S_800AE4D4_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800AE4D4_0;   /* arg0 in set_item_menu_secondary_handler */

/* Sets the object's pointer at offset 0x10 to D_800AE494. */
void set_item_menu_secondary_handler(S_800AE4D4_0 *object) {
    object->unk_10 = &D_800AE494;
}
