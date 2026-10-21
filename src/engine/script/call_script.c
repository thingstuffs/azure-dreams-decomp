#include "common.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"
#include "engine/object.h"
#include "engine/script.h"
extern Rec_D_80082A38 runtime_script_state;

/* Calls func_80035164 for D_80082A38 with the supplied value and mode 2. */
void call_script(s32 value) {
    prepare_script_controller_and_set_cursor(&runtime_script_state, value, 2);
}
