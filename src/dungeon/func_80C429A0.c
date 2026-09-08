#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801741A0_0_pre {
    u16 unk_00;
} S_801741A0_0_pre;   /* the 0x2 bytes before arg0 in func_801741A0, addressed as arg0[-1] */

typedef struct S_801741A0_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} S_801741A0_0;   /* arg0 in func_801741A0 */




M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
M2C_UNK func_8017406C();      /* extern */
extern s32 D_800814A0[3];

/* Update the effect's orbit and height, fade its color, and mark it for removal when its life expires. */
void func_801741A0(void *effect, Rec_D_800E3D7C *position, Rec_D_80082E80 *primitive) {
    s16 life;
    s16 angle;
    s16 next_life;

    angle = ((S_801741A0_0 *)effect)->unk_1E - 0x12C;
    ((S_801741A0_0 *)effect)->unk_1E = (u16) angle;
    position->unk_00.at00_s32.v = (s32) (((S_801741A0_0 *)effect)->unk_40 + (func_80064584(angle) * 0x280));
    position->unk_04.at00_s32.v = (s32) (((S_801741A0_0 *)effect)->unk_44 + (func_800644B8((s16) ((S_801741A0_0 *)effect)->unk_1E) * 0x280));
    position->unk_08.at00_s32.v = (s32) (position->unk_08.at00_s32.v + 0xFFF60000);
    func_800478B8(primitive);
    if ((((S_801741A0_0 *)effect)->unk_1A < 0x11) && (((S_801741A0_0 *)effect)->unk_20 == 0) && !(rand() & 0xF)) {
        func_8017406C(effect, position, primitive);
    }
    life = ((S_801741A0_0 *)effect)->unk_1A;
    if (life < 0xA) {
        primitive->unk_0C.at00_s8.v = (s8) ((((S_801741A0_0 *)effect)->unk_00 * life) / 9);
        primitive->unk_0C.at01_s8.v = (s8) ((((S_801741A0_0 *)effect)->unk_01 * ((S_801741A0_0 *)effect)->unk_1A) / 9);
        primitive->unk_0C.at02_s8.v = (s8) ((((S_801741A0_0 *)effect)->unk_02 * ((S_801741A0_0 *)effect)->unk_1A) / 9);
    }
    next_life = (u16) ((S_801741A0_0 *)effect)->unk_1A - 1;
    ((S_801741A0_0 *)effect)->unk_1A = next_life;
    if ((next_life << 0x10) <= 0) {
        ((S_801741A0_0_pre *)effect)[-1].unk_00 = (u16) (((S_801741A0_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
