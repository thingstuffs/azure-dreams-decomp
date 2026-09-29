#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_818D4B94_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818D4B94_2;   /* temp_v0 in func_818D4B94 */


typedef struct S_818D4B94_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818D4B94_4;   /* ((S_818D4B94_2 *)temp_v0)->unk_08 in func_818D4B94 */

typedef struct S_818D4B94_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818D4B94_5;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_818D4B94 */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();      /* extern */
extern M2C_UNK D_80024044;
extern M2C_UNK D_80024294;

typedef struct S_818D4B94_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_818D4B94_0;   /* temp_v0 in func_818D4B94 */

typedef struct S_818D4B94_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u8 pad_3A[0xE];
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
} S_818D4B94_1;   /* temp_s0 in func_818D4B94 */

/* Creates an offset effect with velocity directed back toward the source position. */
void func_818D4B94(EntityRec *source, s32 setting_14, s32 setting_08, s32 duration, s32 offset_x, s32 offset_y, s32 offset_z) {
    s32 signed_duration;
    s32 step_count;
    s32 delta_x;
    s32 velocity;
    S_818D4B94_1 *state;
    void *effect;

    effect = func_8003FD64(0x211, source);
    if (effect != NULL) {
        ((S_818D4B94_0 *)effect)->unk_10 = &D_80024294;
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)effect)->unk_08))->unk_02 = (s16) (((S_818D4B94_5 *)((*(void * *)&source->z)))->unk_02 + offset_x);
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)effect)->unk_08))->unk_06 = (s16) (((S_818D4B94_5 *)((*(void * *)&source->z)))->unk_06 + offset_y);
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)effect)->unk_08))->unk_0A = (s16) (((S_818D4B94_5 *)((*(void * *)&source->z)))->unk_0A + offset_z);
        state = effect + 0x20;
        state->unk_34 = (u16) ((S_818D4B94_5 *)((*(void * *)&source->z)))->unk_02;
        state->unk_36 = (u16) ((S_818D4B94_5 *)((*(void * *)&source->z)))->unk_06;
        state->unk_38 = (u16) ((S_818D4B94_5 *)((*(void * *)&source->z)))->unk_0A;
        signed_duration = (s16) duration;
        delta_x = -(offset_x << 16);
        step_count = signed_duration / 8;
        velocity = delta_x / step_count;
        if (velocity < 0) {
            velocity += 0xF;
            state->unk_48 = velocity >> 4;
        } else {
            state->unk_48 = velocity >> 4;
        }
        velocity = -(offset_y << 16) / step_count;
        if (velocity < 0) {
            velocity += 0xF;
            state->unk_4C = velocity >> 4;
        } else {
            state->unk_4C = velocity >> 4;
        }
        state->unk_50 = -(offset_z << 16) / step_count / 16;
        state->unk_14 = setting_14;
        state->unk_32 = duration;
        func_8004491C(effect, &D_80024044, signed_duration);
        state->unk_08 = setting_08;
    }
}
