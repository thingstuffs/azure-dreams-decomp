#include "script_symbols.h"
#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"

extern ScenePositionEntry D_80018E1C;
extern ScenePositionEntry D_80018E34;
extern s32 scene_request_context;

extern s32 func_80018C50(s32 flagIndex);

/* Selects data using query 0xFBC and forwards it with the supplied values. */
void select_query(void *primaryValue, s32 unusedValue, s32 secondaryValue) {

    if (func_80018C50(F_chriru_hospital_trg) != 0) {
        func_800181C8(&D_80018E34, &scene_request_context, primaryValue, secondaryValue);
    } else {
        func_800181C8(&D_80018E1C, &scene_request_context, primaryValue, secondaryValue);
    }
}
