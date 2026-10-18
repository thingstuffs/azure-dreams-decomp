#include "common.h"

#include "common.h"
void func_80035164(void *controller, s32 reset_value, s32 requested_selector);     /* extern */
#include "records/Rec_D_80082A38.h"
extern Rec_D_80082A38 D_80082A38;

/* Calls func_80035164 for D_80082A38 with the supplied value and mode 2. */
void func_80035208(s32 value) {
    func_80035164(&D_80082A38, value, 2);
}
