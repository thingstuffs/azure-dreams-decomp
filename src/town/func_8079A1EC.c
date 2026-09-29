#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 D_8001601C;
extern s32 D_80016084;
extern void *D_80017508;

/* Attach the global data pointers and invoke the state callback with mode 2. */
void func_8079A1EC(void)
{
    Rec_D_80016000 *state = D_80016000;
    void *callback_base;

    *(void **)(state->unk_1C + 0x40) = &D_8001601C;
    callback_base = state->unk_20;
    D_80017508 = &D_80016084;
    do {
        (*(void (**)(s32, void *))((u8 *)callback_base + 0x28C))(2, state);
    } while (0);
}
