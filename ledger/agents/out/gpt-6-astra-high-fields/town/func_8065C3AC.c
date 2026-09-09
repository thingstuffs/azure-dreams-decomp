#include "common.h"

typedef struct S_func_8065C3AC_0 {
    u8 pad_00[0x20];
    void *unk_20;
} S_func_8065C3AC_0;

typedef struct S_func_8065C3AC_1 {
    u8 pad_00[0x50];
    s32 (*unk_50)(s8 *);
} S_func_8065C3AC_1;

extern void *D_80016000;
extern s32 D_80018340;
extern u8 D_800183D0;

/* Submit the global value and command 0x17, and save the callback result. */
void func_8065C3AC(void) {
    s8 command_args[2];

    command_args[1] = 0x17;
    command_args[0] = D_800183D0;
    D_80018340 = ((S_func_8065C3AC_1 *)((S_func_8065C3AC_0 *)D_80016000)->unk_20)->unk_50(command_args);
}
