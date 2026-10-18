#include "common.h"

#include "common.h"

#include "records/Rec_func_800384A8_arg0.h"

void func_80038538(Rec_func_800384A8_arg0 *state);
s32 func_80053EF0();                         /* extern */

/* Advance the object's callback once the channel 4 blocking status clears. */
void func_800384F8(s32 object) {
    if (func_80053EF0(4) != 0x100) {
        func_80038538(object);
    }
}
