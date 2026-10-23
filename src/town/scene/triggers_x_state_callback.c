#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

extern s32 func_80018668(s32);
extern void func_80018570(s32);

/* Triggers 0xA6 when the state callback returns zero and 0xA6 is inactive. */
s32 triggers_x_6_state_callback(void)
{
    if ((*(s32 (**)(s32))(*(void **)((u8 *)town_scene_root + 0x20) + 0x2D4))(0) == 0) {
        if (func_80018668(F_10kinko_talk) == 0) {
            func_80018570(F_10kinko_talk);
            return 1;
        }
    }
    return 0;
}
