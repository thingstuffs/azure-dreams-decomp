#include "town/scene/position_entries.h"
#include "town/scene/flags.h"
#include "town/scene.h"

extern ScenePositionEntry D_8001748C[];
extern u8 D_80017580[];
extern u8 D_80017A2F[];

long resolve_entry_with_override_49(TownObjectSet *context, s32 unused, s32 selection) {
    ScenePositionEntry *entries = D_8001748C;
    long result = apply_entry_position(entries, D_80017580, context, selection);

    if (selection == 49 && resolve_entry_flag(entries, context, 49)) {
        return (long)D_80017A2F;
    }
    return result;
}
