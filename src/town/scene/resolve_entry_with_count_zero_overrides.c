#include "town/scene/position_entries.h"
#include "town/scene/flags.h"
#include "modules/town_ovl_5ff1d0.h"
#include "town/player.h"
#include "town/scene.h"

extern ScenePositionEntry D_80018750[];
extern u8 D_8001A41C[];
extern u8 D_80018D54[];
extern u8 D_80018F15[];
extern u8 D_800190C3[];

long resolve_entry_with_count_zero_overrides(TownObjectSet *context, s32 unused, s32 selection) {
    long result = apply_entry_position(D_80018750, &D_800188BC, context, selection);

    if (resolve_entry_flag(D_80018750, context, selection) && selection == 0x26) {
        result = (long)D_8001A41C;
    }
    if (get_town_state_count() == 0) {
        if (selection == 0x34) {
            result = (long)D_80018D54;
        } else if (selection == 0x35) {
            result = (long)D_80018F15;
        } else if (selection == 0x36) {
            result = (long)D_800190C3;
        }
    }
    return result;
}
