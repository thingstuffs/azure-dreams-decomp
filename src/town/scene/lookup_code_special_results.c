#include "modules/town_ovl_64f118.h"
#include "modules/town_ovl_64f118.h"

void lookup_code_with_special_results(s32 forwardedValue, s32 unused, s32 forwardedData) {
    s32 biasedSelectionValue;
    s32 selectionValue;

    selectionValue = func_80017434();
    biasedSelectionValue = selectionValue;
    call_set_script_flag_bit(((selectionValue - ((biasedSelectionValue / 4) * 4)) * 8) + D_80017570, D_80017658,
        forwardedValue, forwardedData);
}
