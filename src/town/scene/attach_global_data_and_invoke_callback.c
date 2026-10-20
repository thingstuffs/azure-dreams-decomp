#include "town/scene/attach_global_data_and_invoke_callback.h"
#include "town/scene/attach_global_data_and_invoke_callback.h"

/* Attach the global data pointers and invoke the state callback with mode 2. */
void attach_global_data_and_invoke_callback(void)
{
    Rec_D_80016000 *state = D_80016000;
    void *callback_base;

    ((TownPositionState *)state->unk_1C)->unk_40 = &D_8001601C;
    callback_base = state->unk_20;
    D_80017508 = &D_80016084;
    do {
        (*(void (**)(s32, void *))((u8 *)callback_base + 0x28C))(2, state);
    } while (0);
}
