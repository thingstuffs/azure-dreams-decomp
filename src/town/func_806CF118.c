#include "modules/town_ovl_64f118.h"

void func_80016118(s32 forwardedValue, s32 unused, s32 forwardedData) {
    s32 biasedSelectionValue;
    s32 selectionValue;

    selectionValue = func_80017434();
    biasedSelectionValue = selectionValue;
    func_80016ABC(((selectionValue - ((biasedSelectionValue / 4) * 4)) * 8) + D_80017570, D_80017658,
        forwardedValue, forwardedData);
}
