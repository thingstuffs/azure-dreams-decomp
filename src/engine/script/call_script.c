#include "common.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"
#include "engine/object.h"
#include "engine/script.h"
extern Rec_D_80082A38 runtime_script_state;

/* Prepares runtime_script_state with the supplied cursor value in mode 2. */
void call_script(s32 value) {
    prepare_script_controller_and_set_cursor(&runtime_script_state, value, 2);
}
