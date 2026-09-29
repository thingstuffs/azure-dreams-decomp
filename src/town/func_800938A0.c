#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"

M2C_UNK func_800942B0();        /* extern */
M2C_UNK func_80094378();        /* extern */
M2C_UNK func_80094C1C();                         /* extern */
M2C_UNK func_80095094();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
extern M2C_UNK D_800CFCEF;
extern M2C_UNK D_800FE488;


typedef struct S_80091000_1 {
    u8 unk_00;
} S_80091000_1;   /* &D_800CFCEF in func_80091000 */

typedef struct S_80091000_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80091000_2;   /* state in func_80091000 */

/* Update the actor against ground height, then dispatch input actions. */
void func_80091000(s32 controller, EntityRec *actor, M2C_UNK context) {
    s16 ground_height;
    GameWork *input_state = &gameWork;

    func_80095C80(actor);
    func_80095094(actor);
    ground_height = func_80095978(actor, &D_800FE488);
    if ((ground_height - actor->z.w.i) >= 4) {
        if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80094378(controller, actor, context);
            return;
        }
    } else {
        if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80095A94(actor, ground_height, &D_800FE488);
        }
    }
    if (((s32)input_state->unk_010) & 0x10) {
        func_800942B0(controller, actor, context);
        return;
    }
    if (input_state->buttons & 0xF000) {
        func_80094C1C(controller);
    }
}
