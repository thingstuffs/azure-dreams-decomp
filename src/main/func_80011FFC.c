#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024FFC_0 {
    u8 * unk_00;
} S_80024FFC_0;   /* arg0 in cardBootResumeMenuAfterSlotRefresh; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_8002593C[];

extern void cardBootRefreshFiveSlotSelection(void *);
/* Initializes object data and assigns the D_8002593C record pointer. */
void cardBootResumeMenuAfterSlotRefresh(void *object_data) {
    cardBootRefreshFiveSlotSelection(object_data);
    ((S_80024FFC_0 *)((u8 *)object_data - 0x10))->unk_00 = D_8002593C;
}
