#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

M2C_UNK func_8008CAA0();
M2C_UNK func_8008CBA0();
M2C_UNK func_8008CF6C();
M2C_UNK func_80090200();
M2C_UNK func_800A2B04();
extern u16 D_80013714[];
extern M2C_UNK D_8004F5F4;
extern s32 D_80082EB0[];
extern M2C_UNK D_80083160[];
extern u16 D_80083462[];
extern s32 D_800E4940[];

/* Reset movement and dispatch actor actions based on state and input flags. */
void func_8008B870(Rec_func_8008ACDC_arg0 *controller, Rec_D_800E3D7C *move_state, Rec_D_80082E80 *entity, Rec_D_800E3D7C *actor) {
    s16 action_state;
    M2C_UNK *input_state = D_80083160;

    move_state->unk_10.at00_s32.v = 0;
    move_state->unk_0C.as_s32 = 0;
    func_800A2B04(move_state, entity->unk_24, entity->unk_25);
    action_state = actor->unk_64.as_s16;
    if ((action_state < 0) || (controller->unk_10C & 1)) {
        entity->unk_14.at00_u16.v = (u16)(entity->unk_14.at00_u16.v & 0xF7FF);
        func_8008CAA0(controller, move_state, entity, actor);
        return;
    }
    if (action_state > 0) {
        func_8008CBA0(controller, move_state, entity, actor);
    }
    if (!(D_80013714[0] & 1) && !(D_80083462[0] & 4) && (input_state[2] & 0x80)) {
        actor->unk_8A.as_s16 = 2;
        D_800E4940[0] = 2;
        func_8008CF6C(controller, move_state, entity, &D_8004F5F4);
        D_80082EB0[0] = 0;
        controller->unk_C8 = 0;
        controller->unk_104 = 0;
        return;
    }
    if ((controller->unk_9A.as_u8 != 0xD) && (actor->unk_1C.as_s32 & 0x200)) {
        entity->unk_14.at00_u16.v = (u16)(entity->unk_14.at00_u16.v & 0xF7FF);
        func_80090200(controller, move_state, entity, actor);
    }
}
