#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_80033B2C();                         /* extern */
M2C_UNK func_80094088();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_80094414();     /* extern */
M2C_UNK func_80094474();     /* extern */
M2C_UNK func_800944BC();     /* extern */
M2C_UNK func_8009451C();     /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
s32 func_8009567C(void *);            /* extern */
s32 func_80095840();               /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800CFCEF;
extern M2C_UNK D_800FE488;


typedef struct S_80092320_1 {
    u8 unk_00;
} S_80092320_1;   /* &D_800CFCEF in func_80092320 */

typedef struct S_80092320_2 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092320_2;   /* state in func_80092320 */


/* Update the actor and select an action from the reference value, state flags, and timer. */
void func_80092320(Rec_func_80094268_arg0 *action, Rec_D_800E3D7C *actor, M2C_UNK context) {
    u8 *state = D_80083160;
    s16 reference_value;
    s32 action_result;
    u16 ticks_left;

    func_80095C80(actor);
    func_80094C1C(action);
    func_80095094(actor);
    reference_value = func_80095978(actor, &D_800FE488);
    if ((reference_value - actor->unk_08.at02_s16.v) >= 4) {
        if (((S_80092320_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80094378(action, actor, context);
            goto done;
        }
        goto check_state;
    }
    if (((S_80092320_1 *)(&D_800CFCEF))->unk_00 == 0) {
        func_80095A94(actor, reference_value, &D_800FE488);
    }
check_state:
    if (((S_80092320_2 *)state)->unk_10 & 0x10) {
        func_800942B0(action, actor, context);
        goto done;
    }
    ticks_left = action->unk_0A.as_u16 - 1;
    action->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        func_80094414(action, actor, context);
        goto done;
    }
    if (((S_80092320_2 *)state)->unk_10 & 0x40) {
        action_result = func_80095840(action, &D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(action, actor, context);
                goto done;
            }
            func_800944BC(action, actor, context);
            goto done;
        }
        if (func_80033B2C(0xA4) != 0) {
            func_80094088(action, actor, context);
            goto done;
        }
    } else if (func_8009567C(&D_800CFCB4) <= 0) {
        func_80094474(action, actor, context);
    }
done:
    return;
}
