#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"

typedef struct S_8002546C_0 {
    s32 * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_8002546C_0;   /* arg0 in card_boot_wait_before_copying_slot; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */

/* Decrement the record counter and replace its pointer when the counter becomes negative. */
void card_boot_wait_before_copying_slot(void *record_data) {
    s32 counter;

    counter = ((S_8002546C_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_8002546C_0 *)((u8 *)record_data - 0x10))->unk_4C = counter;
    if (counter < 0) {
        ((S_8002546C_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80025398;
    }
}
