#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80579100_1 {
    u8 pad_00[0x35C0];
    s16 unk_35C0;
} S_80579100_1;   /* temp_a1 in func_80579100 */


M2C_UNK func_80017398();             /* extern */
extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_80017500;
extern s16 D_800175B4;
extern M2C_UNK *D_800175B8;

/* Selects the global buffer, clamps the state value to at least 30, and invokes func_80017398 three times. */
void func_80579100(void) {
    S_80579100_1 *activeState;
    s32 valueBeforeClamp;

    activeState = D_80016000->unk_38.as_pv;
    valueBeforeClamp = activeState->unk_35C0;
    D_800175B8 = &D_80017500;
    if (valueBeforeClamp < 0x1E) {
        activeState->unk_35C0 = 0x1E;
    }
    func_80017398(0x5D9, activeState);
    func_80017398(0x5DA);
    D_800175B4 = 0;
    func_80017398(0x5DB);
}
