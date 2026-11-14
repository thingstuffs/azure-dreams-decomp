#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"
#include "town/scene/position_entries.h"
#include "town/scene/event.h"
#include "town/scene/flags.h"

void decrement_entry_counter_if_flag(void);                            /* extern */
extern s16 scene_request_flag_id;
extern ScenePositionEntry D_80018B38;
extern s32 D_80018E38;

/* Runs the town interaction handler and returns its saved result. */
s32 select_response_starting_mia_bikou(void *object, s32 unused, s32 context) {
    s32 result;

    result = apply_entry_position(&D_80018B38, &D_80018E38, object, context);
    if ((get_script_flag_mask(scene_request_flag_id) == 0) && (resolve_entry_flag(&D_80018B38, object, context) == 0)) {
        decrement_entry_counter_if_flag();
    }
    set_script_flag_bit(Ft_s07_mia_bikou_start);
    return result;
}
