#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016ABC(); /* extern */
s32 func_80017434();                                /* extern */
extern u8 D_80017570;
extern M2C_UNK D_80017658;

/* Selects an 8-byte table entry by signed remainder modulo four and forwards the supplied arguments. */
void func_806CF118(s32 forwardedValue, M2C_UNK unused, M2C_UNK forwardedData) {
    s32 biasedSelectionValue;
    s32 selectionValue;

    selectionValue = func_80017434();
    biasedSelectionValue = selectionValue;
    if (selectionValue < 0) {
        biasedSelectionValue = selectionValue + 3;
    }
    func_80016ABC(((selectionValue - ((biasedSelectionValue >> 2) * 4)) * 8) + &D_80017570, &D_80017658, forwardedValue, forwardedData);
}
