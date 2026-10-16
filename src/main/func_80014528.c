#include "common.h"
#include "m2c_compat.h"

void *cardBootCreateSlotSelectionMenu();                /* extern */
void *cardBootCreateSaveSlotMenu();                    /* extern */
void cardBootDestroyCardChooser();
typedef struct S_80027528_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
} S_80027528_0;   /* arg0 in cardBootOpenSelectedRequestMenu */

/* extern */

/* Updates the record using its current mode and stored value. */
void cardBootOpenSelectedRequestMenu(void *record) {
    s32 mode;

    cardBootDestroyCardChooser(record - 0x20);
    mode = ((S_80027528_0 *)record)->unk_00;
    if (mode == 0) {
        cardBootCreateSlotSelectionMenu(((S_80027528_0 *)record)->unk_14, 0);
        return;
    } else {
        cardBootCreateSaveSlotMenu(((S_80027528_0 *)record)->unk_14, mode);
    }
}
