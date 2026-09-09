#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_8003DB94();
void *func_8003FC64();
s32 func_8004491C();
s32 rand();
extern s32 D_80024264;
extern s32 D_800D36D0;
extern s32 D_800DEF08;

typedef struct S_800243BC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_800243BC_0;   /* temp_v0 in func_800243BC */

typedef struct S_800243BC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
} S_800243BC_1;   /* temp_v1 in func_800243BC */

typedef struct S_800243BC_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800243BC_2;   /* temp_s0 in func_800243BC */

typedef struct S_800243BC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800243BC_3;   /* arg1 in func_800243BC */

typedef struct S_800243BC_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800243BC_4;   /* temp_v1_3 in func_800243BC */

/* Creates an object with a random sprite variant and copies its transform. */
s32 func_800243BC(s32 owner_id, S_800243BC_3 *transform)
{
    s32 random_value;
    s32 rounded_random;
    s32 return_value;
    S_800243BC_2 *sprite;
    void *object;
    S_800243BC_1 *state;
    S_800243BC_4 *object_transform;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = object + 0x20;
        ((S_800243BC_0 *)object)->unk_10 = &D_80024264;
        state->unk_08 = owner_id;
        ((S_800243BC_0 *)object)->unk_20 = 0;
        state->unk_02 = 0;
        state->unk_04 = 0x10;
        sprite = ((S_800243BC_0 *)object)->unk_0C;
        sprite->unk_12 = 0x7E02;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        sprite->unk_1E = 0;
        sprite->unk_1C = 0;
        sprite->unk_14 = (s16)(sprite->unk_14 | 0xC);
        sprite->unk_10 = (u16)(sprite->unk_10 | 0x20);
        sprite->unk_14 = (u16)(sprite->unk_14 | 0x100);
        random_value = rand();
        rounded_random = random_value;
        if (random_value < 0) {
            rounded_random = random_value + 0xF;
        }
        func_8003DB94(sprite, &D_800DEF08,
                      (s16)(random_value - ((rounded_random >> 4) * 0x10)));
        func_8004491C(object, &D_800D36D0);
        object_transform = ((S_800243BC_0 *)object)->unk_08;
        return_value = (s32)object;
        *object_transform = *(S_800243BC_4 *)transform;
        return return_value;
    }
    return 0;
}
