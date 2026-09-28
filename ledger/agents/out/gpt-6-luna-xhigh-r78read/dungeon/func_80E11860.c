#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80173DD4_arg0.h"

typedef struct S_80175060_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80175060_0;   /* temp_v0 in func_80175060 */

typedef struct S_80175060_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80175060_1;   /* temp_s0 in func_80175060 */


typedef struct S_80175060_3 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175060_3;   /* temp_v1_2 in func_80175060 */



void func_8003DB94(void *, void *, s32);  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEA68;
extern M2C_UNK D_80174F64;

/* Creates an object with randomized phase and rotation and copies its initial state. */
s32 func_80175060(Rec_func_80173DD4_arg0 *owner, Rec_D_800E3D7C *initial_state) {
    s32 initial_color;
    s32 part_setting;
    s32 phase_random;
    s32 rotation_random;
    s32 phase_rounding_input;
    s32 rotation_rounding_input;
    S_80175060_1 *object_part;
    void *object;
    S_80175060_3 *object_state;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        ((S_80175060_0 *)object)->unk_10 = &D_80174F64;
        phase_rounding_input = rand();
        phase_random = phase_rounding_input;
        object_part = object + 0x20;
        if (phase_random < 0) {
            phase_rounding_input = phase_random + 0xFFF;
        }
        initial_color = 0x606060;
        object_part->unk_04 = (s16) (phase_random - ((phase_rounding_input >> 0xC) << 0xC));
        part_setting = 4;
        object_part->unk_08 = (s16) part_setting;
        object_part = ((S_80175060_0 *)object)->unk_0C;
        object_part->unk_0C = initial_color;
        object_part->unk_14 = (u16) (object_part->unk_14 | 0xC);
        object_part->unk_10 = (u16) (object_part->unk_10 | 0x20);
        func_8003DB94(object_part, &D_800DEA68, 0);
        func_800478B8(object_part);
        rotation_rounding_input = rand();
        rotation_random = rotation_rounding_input;
        if (rotation_random < 0) {
            rotation_rounding_input = rotation_random + 0xFFF;
        }
        object_part->unk_1A = (s16) (rotation_random - ((rotation_rounding_input >> 0xC) << 0xC));
        object_part->unk_1E = 0x1000;
        object_part->unk_1C = 0x1000;
        func_8004491C(object, &D_80045340);
        {
            s32 state_word_04;

            object_state = ((S_80175060_0 *)object)->unk_08;
            *object_state = *(S_80175060_3 *)initial_state;
            state_word_04 = object_state->unk_04;
            object_state->unk_0C = object_state->unk_00;
            object_state->unk_10 = state_word_04;
        }
        object_state->unk_08.at02.v = owner->unk_88;
        return (s32) object;
    }
    return 0;
}

