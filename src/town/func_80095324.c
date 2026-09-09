#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80035208();
M2C_UNK func_8008B158();
M2C_UNK func_8009451C();
M2C_UNK func_800945B8();
M2C_UNK func_80094660();
M2C_UNK func_800946A0();
M2C_UNK func_80094944();
M2C_UNK func_80094984();
M2C_UNK func_80094C1C();
M2C_UNK func_80094C74();
M2C_UNK func_80095094();
M2C_UNK func_8009567C();
s32 func_80095760();
s16 func_80095978();
M2C_UNK func_80095A94();
M2C_UNK func_80095C80();
M2C_UNK func_800988C8();
s32 func_8009FF50();
s32 func_800A9D74();

extern u8 D_80083160[];
extern M2C_UNK D_80093B00;
extern M2C_UNK D_8009B828;
extern M2C_UNK D_8009B8E8;
extern u8 D_8009B9BC[];
extern s32 D_800CFCB4;
extern u8 D_800CFCEF;
extern M2C_UNK D_800D0128;
extern u8 D_800FE488[];
extern s32 *D_800FE5D8;

typedef struct S_80092A84_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80092A84_1;   /* state in func_80092A84 */


typedef struct S_80092A84_3 {
    u8 pad_00[0x50];
    void * unk_50;
} S_80092A84_3;   /* entity in func_80092A84 */

typedef struct S_80092A84_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092A84_4;   /* base in func_80092A84 */

/* Updates the actor's position and dispatches town actions from input and interaction state. */
void func_80092A84(Rec_func_80094268_arg0 *actor, Rec_D_800E3D7C *body, M2C_UNK context) {
    u8 *input_state;
    u8 *position_data;
    s32 *interaction_ctrl;
    s16 position;
    s32 input_flags;
    s32 action_result;
    S_80092A84_3 *entity;
    void *handler;
    S_80092A84_4 *interaction_state;

    input_state = D_80083160;
    func_80095C80(body);
    func_80095094(body);

    position_data = D_800FE488;
    position = func_80095978(body, position_data);
    if ((position - body->unk_08.at02_s16.v) >= 4) {
        if (D_800CFCEF == 0) {
            func_80094660(actor, body, context);
            return;
        }
    } else if (D_800CFCEF == 0) {
        func_80095A94(body, position, position_data);
    }

    input_flags = ((S_80092A84_1 *)input_state)->unk_10;
    if (input_flags & 0x10) {
        func_800945B8(actor, body, context);
        return;
    }
    if (input_flags & 0x40) {
        func_800946A0(actor, body, context);
        return;
    }

    interaction_ctrl = &D_800CFCB4;
    if ((func_80095760(interaction_ctrl) == -1) && (func_8009FF50() == 0)) {
        func_8009567C(interaction_ctrl);
        func_80094C1C(actor);
        func_80094984(&D_800D0128, actor, context);
        func_800988C8(actor, body, context);

        entity = actor->unk_2C;
        handler = entity->unk_50;
        if ((handler != &D_8009B828) && (handler != &D_8009B8E8)) {
            if (handler != D_8009B9BC) {
                actor->unk_2C = 0;
            }
        }

        interaction_state = &D_800CFCB4;
        action_result = func_800A9D74(interaction_state->unk_10, actor->unk_2C);
        if (action_result != 0) {
            func_80035208(action_result);
        } else {
            func_8008B158(interaction_state->unk_10);
        }
        D_800FE5D8 = (s32 *)&D_80093B00;
        return;
    }

    if (((S_80092A84_1 *)input_state)->unk_08 & 0xF000) {
        position = actor->unk_3E.as_u16 - 1;
        actor->unk_3E.as_u16 = position;
        func_80094944(position, 0xC);
        func_80094C1C(actor);
        func_80094C74(body);
        return;
    }

    func_8009451C(actor, body, context);
}
