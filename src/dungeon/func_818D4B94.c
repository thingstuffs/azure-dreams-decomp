#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

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
void func_818D4B94(Rec_D_800E3D7C *source, s16 setting_14, s32 setting_08, s32 duration, s32 offset_x, s32 offset_y, s32 offset_z) {
    s16 saved_setting_14 = setting_14;
    s32 saved_setting_08 = setting_08;
    s32 saved_duration = duration;
    register s32 saved_offset_x ASM_REG("$18") = offset_x;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 saved_offset_y ASM_REG("$19") = offset_y;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 saved_offset_z ASM_REG("$20") = offset_z;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 signed_duration;
    s32 biased_duration;
    s32 step_count;
    s32 return_delta_x;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    S_818D4B94_1 *state;
    void *effect;

    effect = func_8003FD64(0x211, source);
    if (effect != NULL) {
        ((S_818D4B94_0 *)effect)->unk_10 = &D_80024294;
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)effect)->unk_08))->unk_02 = (s16) (((S_818D4B94_5 *)(source->unk_08.at00_pv.v))->unk_02 + saved_offset_x);
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)effect)->unk_08))->unk_06 = (s16) (((S_818D4B94_5 *)(source->unk_08.at00_pv.v))->unk_06 + saved_offset_y);
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)effect)->unk_08))->unk_0A = (s16) (((S_818D4B94_5 *)(source->unk_08.at00_pv.v))->unk_0A + saved_offset_z);
        state = effect + 0x20;
        state->unk_34 = (u16) ((S_818D4B94_5 *)(source->unk_08.at00_pv.v))->unk_02;
        state->unk_36 = (u16) ((S_818D4B94_5 *)(source->unk_08.at00_pv.v))->unk_06;
        state->unk_38 = (u16) ((S_818D4B94_5 *)(source->unk_08.at00_pv.v))->unk_0A;
        signed_duration = (s16) saved_duration;
        biased_duration = signed_duration;
        return_delta_x = 0 - (saved_offset_x << 0x10);
        if (signed_duration < 0) {
            biased_duration = signed_duration + 7;
        }
        step_count = biased_duration >> 3;
        velocity_x = return_delta_x / step_count;
        if (velocity_x < 0) {
            velocity_x += 0xF;
        }
        state->unk_48 = velocity_x >> 4;
        ASM_KEEP(saved_offset_x);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        velocity_y = (s32) (0 - (saved_offset_y << 0x10)) / step_count;
        if (velocity_y < 0) {
            velocity_y += 0xF;
        }
        state->unk_4C = velocity_y >> 4;
        ASM_KEEP(saved_offset_y);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_setting_14);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_duration);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_setting_08);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        velocity_z = (s32) (0 - (saved_offset_z << 0x10)) / step_count;
        if (velocity_z < 0) {
            velocity_z += 0xF;
        }
        state->unk_50 = (s32) (velocity_z >> 4);
        state->unk_14 = saved_setting_14;
        state->unk_32 = saved_duration;
        func_8004491C(effect, &D_80024044, signed_duration);
        ASM_KEEP(saved_offset_z);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        state->unk_08 = saved_setting_08;
    }
}

/* MECHANISM: Exact 0x38 frame with raw arguments pinned to retail's s1-s7 roles.
   A raw s32 arg3 plus signed s16 local, mutable quotient locals, and pre-branch numerator reproduce the CFG.
   Keep seams before division and after the call preserve s4 while allowing the global address delay-slot hoist. */
