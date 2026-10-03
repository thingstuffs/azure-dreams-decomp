#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 D_80018340;
extern u8 D_800183D0;

/* Submit the global value and command 0x17, and save the callback result. */
void func_8065C3AC(void) {
    s8 command_args[2];

    command_args[1] = 0x17;
    command_args[0] = D_800183D0;
    D_80018340 = D_80016000->unk_20->callback_050(command_args);
}
