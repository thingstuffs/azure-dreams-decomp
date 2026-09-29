#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct S_func_8065C3AC_1 {
    u8 pad_00[0x50];
    s32 (*unk_50)(s8 *);
} S_func_8065C3AC_1;

extern s32 D_80018340;
extern u8 D_800183D0;

/* Submit the global value and command 0x17, and save the callback result. */
void func_8065C3AC(void) {
    s8 command_args[2];

    command_args[1] = 0x17;
    command_args[0] = D_800183D0;
    D_80018340 = ((S_func_8065C3AC_1 *)D_80016000->unk_20)->unk_50(command_args);
}
