#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024FAC_0 {
    M2C_UNK * unk_00;
} S_80024FAC_0;   /* arg0 in cardBootPollStatusAndDismissDialog; pointer addresses record offset 0x10 */


s32 cardBootDebounceCardStatusEvents();                                /* extern */
s32 cardBootCloseMessageDialog();                     /* extern */
void cardBootRestoreSavedSelectionCallback(void *);                            /* extern */
extern M2C_UNK D_8002593C;

/* Update the record and switch its table when the status reaches four. */
void cardBootPollStatusAndDismissDialog(void *record_data) {
    cardBootRestoreSavedSelectionCallback(record_data);
    if (cardBootDebounceCardStatusEvents() >= 4) {
        cardBootCloseMessageDialog(0);
        ((S_80024FAC_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_8002593C;
    }
}
