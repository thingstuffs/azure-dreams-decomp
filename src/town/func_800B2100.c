#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"

void townPopulateItemMenuPageEntries();                 /* extern */
void townPopulateItemMenuLowerEntries(Rec_func_800AF254_arg1 *);                            /* extern */
void townPopulateCurrentItemMenuPage();                      /* extern */
void townUpdateItemMenuPageBounds();                      /* extern */
void townItemMenuNoOp();                 /* extern */


/* Run the record update sequence and process its stored value. */
void townUpdateItemMenuRecord(Rec_func_800AF254_arg1 *record) {
    townPopulateItemMenuLowerEntries(record);
    townUpdateItemMenuPageBounds(record);
    townPopulateCurrentItemMenuPage(record);
    townPopulateItemMenuPageEntries(record->unk_A8.as_s32, record);
    townItemMenuNoOp(record->unk_A8.as_s32, record);
}
