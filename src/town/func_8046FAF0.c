#include "modules/town_ovl_3ef1c8.h"

void townInvokeMatchCallbackOrLookup(void)
{
    s32 lookup_result;

    if (func_800196F4(0xD, 3) != 0) {
        (*((s32 (**)(s32))
            (((s8 *) (*((void **) (((s8 *) D_80016000) + 0x20)))) + 0x78)))(0);
        return;
    }
    lookup_result = func_8001979C(0xD, 3);
    if (lookup_result != (-1)) {
        func_80018F74(lookup_result);
    }
}
