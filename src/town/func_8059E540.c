#include "shared/town_pointees.h"
#include "shared/town_root.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8059E540_2 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8059E540_2;   /* page in func_8059E540 */

void func_800168E0();
s32 func_80018964();
extern u8 D_80010000[];
extern M2C_UNK D_80018EE4;
extern M2C_UNK D_80019148[3];

typedef struct S_8059E540_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8059E540_0;   /* page in func_8059E540 */

/* Close the 0x11FC dialogue if it is open, then hand the scene's queued record to the handler slot. */
void func_8059E540(void) {
    void *pending;
    void *new_value;
    Rec_D_80016000 *state;

    if (func_80018964(0x11FC) == 0) {
        u8 *page = (u8 *)0x80010000;
        ((M2C_UNK (*)(M2C_UNK))((TownServiceTable *)(((Rec_D_80016000 *)(((S_8059E540_2 *)page)->unk_6000))->unk_20))->callback_27C)(0);
        ((M2C_UNK (*)(M2C_UNK, M2C_UNK))((TownServiceTable *)(((Rec_D_80016000 *)(((S_8059E540_2 *)page)->unk_6000))->unk_20))->callback_2F4)(-1, -5);
    }
    func_800168E0();
    state = ((S_8059E540_0 *)D_80010000)->unk_6000;
    new_value = (M2C_UNK *)&D_80010000[0xD07C];
    ((TownPositionState *)state->unk_1C)->unk_40 = new_value;
    pending = *(M2C_UNK **)((s8 *)state->unk_40 + (state->unk_08 * 8));
    if (pending != NULL) {
        ((TownPositionState *)state->unk_1C)->unk_40 = pending;
        *(M2C_UNK **)((s8 *)state->unk_40 + (state->unk_08 * 8)) = 0;
    }
    *(M2C_UNK **)&D_80019148[0] = &D_80018EE4;
}
