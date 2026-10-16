/* Relink of matched main/func_80011FAC; every changed retail word is a paired relocation. */
#define D_8002593C D_8002789C
#define cardBootRestoreSavedSelectionCallback func_800274A8
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024FAC_0 {
    M2C_UNK * unk_00;
} S_80024FAC_0;   /* arg0 in func_800274D8; pointer addresses record offset 0x10 */


s32 cardBootDebounceCardStatusEvents();                                /* extern */
s32 cardBootCloseMessageDialog();                     /* extern */
extern void func_800274A8(void *);                            /* extern */
extern M2C_UNK D_8002789C;

/* Update the record and switch its table when the status reaches four. */
void func_800274D8(void *record_data) {
    func_800274A8(record_data);
    if (cardBootDebounceCardStatusEvents() >= 4) {
        cardBootCloseMessageDialog(0);
        ((S_80024FAC_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_8002789C;
    }
}
