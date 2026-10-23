#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 (*Callback)(s32);

extern void func_80018570(s32);
extern s32 func_80018668(s32);

/* Triggers 0xA7 when the state callback returns one and 0xA7 is inactive. */
s32 triggers_x_7_state_callback(void) {
    if ((*(Callback *)((u8 *)*(void **)((u8 *)town_scene_root + 0x20) + 0x2D4))(0) != 1) {
        return 0;
    }
    if (func_80018668(F_30kinko_talk) != 0) {
        return 0;
    }
    func_80018570(F_30kinko_talk);
    return 1;
}
