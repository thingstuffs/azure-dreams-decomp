#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

u32 func_800374F4();                     /* extern */
M2C_UNK func_800478B8();                      /* extern */
void func_8009539C();                      /* extern */
extern M2C_UNK D_800A38A8;
extern M2C_UNK D_800D0B20;


typedef struct S_800A378C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x1E];
    s16 unk_22;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} S_800A378C_0;   /* arg0 in func_800A378C */

/* Updates the transform until the countdown expires, then resets appearance and advances state. */
void func_800A378C(S_800A378C_0 *state, EntityRec *transform, Rec_D_80082E80 *appearance) {
    s32 ticks_left;

    ticks_left = state->unk_24 - 1;
    state->unk_24 = ticks_left;
    if (ticks_left < 0) {
        transform->unk_0C = 0;
        transform->unk_10 = 0;
        transform->flags14 = 0;
        appearance->unk_0C.at02_s8.v = 0x40;
        appearance->unk_0C.at01_s8.v = 0x40;
        appearance->unk_0C.at00_s8.v = 0x40;
        appearance->unk_10.as_s16 = 0x20;
        appearance->unk_14.at00_u16.v = (u16) (appearance->unk_14.at00_u16.v | 0x1C);
        state->unk_00 = &D_800A38A8;
        transform->unk_0C = 0;
        transform->unk_10 = 0;
        transform->flags14 =
            ((((u16) func_800374F4(0x1000)) << 1) + 0x2000) << 4;
        return;
    }
    transform->unk_0C = (s32) (transform->unk_0C - state->unk_2C);
    transform->unk_10 = (s32) (transform->unk_10 - state->unk_30);
    transform->flags14 = (s32) (transform->flags14 - state->unk_34);
    func_8009539C(transform);
    if (*(&D_800D0B20 + state->unk_22) != 0) {
        func_800478B8(appearance);
    }
}
