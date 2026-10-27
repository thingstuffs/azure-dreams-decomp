#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"
#include "town/scene/position_entries.h"

void decrement_current_entry_counter_condition(void);                            /* extern */
s32 invoke_system_callback_21_c(void *entry_table, void *context, s32 entry_key);         /* extern */
s32 call_helper_with_fixed_id_0x118a(s32);
extern s16 scene_request_flag_id;
extern ScenePositionEntry D_80018B38;
extern s32 D_80018E38;

/* Runs the town interaction handler and returns its saved result. */
s32 process_request(void *object, s32 unused, s32 context) {
    s32 result;

    result = func_80018044(&D_80018B38, &D_80018E38, object, context);
    if ((func_8001894C(scene_request_flag_id) == 0) && (invoke_system_callback_21_c(&D_80018B38, object, context) == 0)) {
        decrement_current_entry_counter_condition();
    }
    call_helper_with_fixed_id_0x118a(Ft_s07_mia_bikou_start);
    return result;
}
