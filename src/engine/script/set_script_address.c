#include "common.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"
#include "engine/object.h"
#include "engine/script.h"
extern Rec_D_80082A38 runtime_script_state;

/* Set the global runtime's script address using mode zero. */
void set_script_address(s32 script_addr) {
    prepare_script_controller_and_set_cursor(&runtime_script_state, script_addr, 0);
}
