#include "common.h"

extern s32 D_804094E8[4];
extern s32 D_804094E8_2[4];
extern s32 D_804094E8_3[4];
extern s32 D_804094E8_4[4];
extern s32 D_804094EC[4];
extern s32 D_80409500[4];

extern void invoke_callback_for_four_global_values(void);
extern s32 func_80408674(s32 card_channel);

/* Boot step 2: run the loader and either request retry code 5 or bump the attempt counter. */
s32 card_dev_advance_boot_step(void) {
    s32 result;

    result = 0;

    if (D_804094E8[0] == 2) {
        invoke_callback_for_four_global_values();
        if (func_80408674(D_804094EC[0]) == 0) {
            D_804094E8_2[0] = 0;
            result = 5;
        } else {
            D_80409500[0] = 0;
            D_804094E8_3[0] = D_804094E8_4[0] + 1;
        }
    }
    return result;
}
