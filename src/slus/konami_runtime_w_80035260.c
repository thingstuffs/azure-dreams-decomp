#include "common.h"

#include "common.h"
void func_80035164(void *controller, s32 reset_value, s32 requested_selector);     /* extern */
#include "records/Rec_D_80082A38.h"
extern Rec_D_80082A38 D_80082A38;

/* Set the global runtime's script address using mode zero. */
void func_80035260(s32 script_addr) {
    func_80035164(&D_80082A38, script_addr, 0);
}
