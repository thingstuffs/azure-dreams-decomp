#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800942B0();        /* extern */
M2C_UNK func_80094378();        /* extern */
M2C_UNK func_80094C1C();                         /* extern */
M2C_UNK func_80095094();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
extern u8 D_80083160[];
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
void func_80091000(s32 controller, Rec_D_800E3D7C *actor, M2C_UNK context) {
    s16 ground_height;
    u8 *input_state = D_80083160;

    func_80095C80(actor);
    func_80095094(actor);
    ground_height = func_80095978(actor, &D_800FE488);
    if ((ground_height - actor->unk_08.at02_s16.v) >= 4) {
        if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80094378(controller, actor, context);
            return;
        }
        goto handle_input;
    }
    if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
        func_80095A94(actor, ground_height, &D_800FE488);
    }
handle_input:
    if (((S_80091000_2 *)input_state)->unk_10 & 0x10) {
        func_800942B0(controller, actor, context);
        return;
    }
    if (((S_80091000_2 *)input_state)->unk_08 & 0xF000) {
        func_80094C1C(controller);
    }
}
