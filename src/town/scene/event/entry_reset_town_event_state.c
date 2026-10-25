#include "script_symbols.h"
#include "shared/town_pointees.h"
#include "shared/town_root.h"
#include "town/scene/event_state_dispatch_g00731.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8059E540_2 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8059E540_2;   /* page in func_8059E540 */

s32 func_80018964(s32 flagIndex);
extern u8 D_80010000[];
extern M2C_UNK D_80018EE4;
extern M2C_UNK D_80019148[3];

typedef struct S_8059E540_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8059E540_0;   /* page in func_8059E540 */

/* Close the 0x11FC dialogue if it is open, then hand the scene's queued record to the handler slot. */
void restore_pending_town_event(void) {
    void *pending;
    void *new_value;
    Rec_D_80016000 *state;

    if (func_80018964(Fp_pool_open) == 0) {
        u8 *page = (u8 *)0x80010000;
        ((s32 (*)(s32))((TownServiceTable *)(((Rec_D_80016000 *)(((S_8059E540_2 *)page)->unk_6000))->services))->callback_27C)(0);
        ((s32 (*)(s32, s32))((TownServiceTable *)(((Rec_D_80016000 *)(((S_8059E540_2 *)page)->unk_6000))->services))->callback_2F4)(-1, -5);
    }
    reset_town_event_state();
    state = ((S_8059E540_0 *)D_80010000)->unk_6000;
    new_value = (s32 *)&D_80010000[0xD07C];
    ((TownPositionState *)state->position)->unk_40 = new_value;
    pending = *(s32 **)((s8 *)state->event_data + (state->entry_index * 8));
    if (pending != NULL) {
        ((TownPositionState *)state->position)->unk_40 = pending;
        *(s32 **)((s8 *)state->event_data + (state->entry_index * 8)) = 0;
    }
    *(s32 **)&D_80019148[0] = &D_80018EE4;
}
