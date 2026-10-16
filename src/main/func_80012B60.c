#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025B60_0 {
    M2C_UNK * unk_00;
} S_80025B60_0;   /* arg0 in cardBootEnterSlotSelectionInput; pointer addresses record offset 0x10 */


void cardBootRecheckSelectedChannel();                            /* extern */
void cardBootRefreshFiveSlotSelection(void *);                            /* extern */
extern M2C_UNK D_8002593C;

/* Update the record, run the shared follow-up, and install its next table. */
void cardBootEnterSlotSelectionInput(void *record_data) {
    cardBootRefreshFiveSlotSelection(record_data);
    cardBootRecheckSelectedChannel();
    ((S_80025B60_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_8002593C;
}
