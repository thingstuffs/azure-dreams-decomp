#include "modules/town_ovl_64f118.h"
#include "modules/town_ovl_64f118.h"
#include "town/player.h"
#include "town/scene/motion.h"

/*
 * Selects one of four eight-byte flag records using the signed remainder of func_80017434 divided
 * by four, then forwards it with D_80017658 and the supplied values.
 */
void lookup_code_with_special_results(s32 forwardedValue, s32 unused, s32 forwardedData) {
    s32 biasedSelectionValue;
    s32 selectionValue;

    selectionValue = get_linked_record_field_2_d_60();
    biasedSelectionValue = selectionValue;
    apply_entry_position(((selectionValue - ((biasedSelectionValue / 4) * 4)) * 8) + D_80017570, D_80017658,
        forwardedValue, forwardedData);
}
