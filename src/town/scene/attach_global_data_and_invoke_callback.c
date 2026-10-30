#include "town/scene/attach_global_data_and_invoke_callback.h"
#include "town/scene.h"
#include "town/scene/hooks.h"
extern u8 D_800177C4[];
extern s32 func_800161E4(void);
#include "town/scene/attach_global_data_and_invoke_callback.h"

/* Attach the global data pointers and invoke the state callback with mode 2. */
void attach_global_data_and_invoke_callback(void)
{
    Rec_D_80016000 *state = town_scene_root;
    void *callback_base;

    state->position->unk_40 = &scene_event_data;
    callback_base = state->services;
    D_80017508 = &D_80016084;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: town/func_8079A1EC). */
    do {
        (*(void (**)(s32, void *))((u8 *)callback_base + 0x28C))(2, state);
    } while (0);
}
/* One complete terminal choice; the next scene object begins at +0x84. */
TownTerminalChoice D_80016074[1] = {
    { func_800161E4, func_800161DC, D_800177C4, 0, 0 },
};
