#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

/* D_80082E60: global state struct. field_8 is read as a byte (arg to
 * func_80040CBC / copied into field_B), then cleared as a halfword;
 * field_E is cleared as a byte. */
struct S_80082E60 {
    char pad0[8];
    union {
        u8 b;
        u16 h;
    } field_8;
    s8 pad_A;
    s8 field_B;
    s8 field_C;
    s8 field_D;
    s8 field_E;
    char pad_F[0xA];
    s8 field_18;
};



/* D_80083160: shared state table; four u32 fields at these offsets are
 * cleared here (declared >8 bytes to force %hi/%lo addressing). */


extern void func_80040CBC(s16 a0);

/* Saves and processes the state byte, then clears pending state and four shared table fields. */
void func_80040BB4(void)
{
    u8 state_byte = ((struct S_80082E60 *)&D_80082E60)->field_8.b;

    D_80082E60.field_B = state_byte;
    func_80040CBC(state_byte);

    D_80082E60.unk_0E = 0;
    D_80082E60.unk_08 = 0;

    gameWork.view.slot[2].callback = 0;
    gameWork.view.slot[3].callback = 0;
    gameWork.view.slot[0].callback = 0;
    gameWork.view.slot[1].callback = 0;
}
