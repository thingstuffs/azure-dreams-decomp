#include "shared/town_root.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800175E0();
extern M2C_UNK D_8001624C;
extern M2C_UNK D_800177C8;
extern M2C_UNK *D_8001794C[3];
extern M2C_UNK D_8001802A;
extern u8 D_80010000[];

typedef void (*TownCall)(s32, s32);

typedef struct S_func_8047E1C0_3 {
    u8 pad_00[0x2EC];
    TownCall unk_2EC;
} S_func_8047E1C0_3;

/* Updates town state pointers and dispatches a town call. */
void func_8047E1C0(void) {
    void *state_data;
    s32 call_code;
    TownServiceTable *dispatch_table;

    call_code = 0x3B0;
    state_data = &D_8001802A;
    ((TownPositionState *)((Rec_D_80016000 *)(*(void **)((u8 *)D_80010000 + 0x6000)))->unk_1C)->unk_40 = state_data;
    dispatch_table = *(void **)((u8 *)(*(void **)((u8 *)D_80010000 + 0x6000)) + 0x20);
    *(M2C_UNK **)&D_8001794C[0] = &D_800177C8;
    ((TownCall)dispatch_table->callback_2EC)(call_code, 0x100);
    func_800175E0(0x98);
    *(void **)((s8 *)((Rec_D_80016000 *)(*(void **)((u8 *)D_80010000 + 0x6000)))->unk_40
        + ((Rec_D_80016000 *)(*(void **)((u8 *)D_80010000 + 0x6000)))->unk_08 * 8) = &D_8001624C;
}
