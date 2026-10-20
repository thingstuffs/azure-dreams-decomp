#include "common.h"

#include "common.h"
void prepare_script_controller_and_set_cursor(void *controller, s32 reset_value, s32 requested_selector);     /* extern */
#include "records/Rec_D_80082A38.h"
extern Rec_D_80082A38 D_80082A38;

/* Set the global runtime's script address using mode zero. */
void set_script_address(s32 script_addr) {
    prepare_script_controller_and_set_cursor(&D_80082A38, script_addr, 0);
}
