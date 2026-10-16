#include "common.h"
#include "m2c_compat.h"

void cardBootRefreshPairedChoiceLabels();                         /* extern */
void cardBootSetPairedChoiceAnimations();   /* extern */
void cardBootLayoutLeftRightLabels(s32);                            /* extern */
void func_80026CF0();                         /* extern */
extern M2C_UNK D_8002807C;
extern M2C_UNK D_80028084;

/* Update the record using the two shared data addresses. */
void cardBootInitializePairedChoiceLayout(s32 record_addr) {
    cardBootLayoutLeftRightLabels(record_addr);
    func_80026CF0(record_addr);
    cardBootSetPairedChoiceAnimations(record_addr, &D_8002807C, &D_80028084);
    cardBootRefreshPairedChoiceLabels(record_addr);
}
