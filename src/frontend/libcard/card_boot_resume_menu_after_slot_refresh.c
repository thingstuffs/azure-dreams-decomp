#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"

typedef struct S_80024FFC_0 {
    u8 * unk_00;
} S_80024FFC_0;   /* arg0 in card_boot_resume_menu_after_slot_refresh; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_8002593C[];

/* Initializes object data and assigns the D_8002593C record pointer. */
void card_boot_resume_menu_after_slot_refresh(void *object_data) {
    card_boot_refresh_five_slot_selection(object_data);
    ((S_80024FFC_0 *)((u8 *)object_data - 0x10))->unk_00 = D_8002593C;
}
