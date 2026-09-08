#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002569C_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002569C_6;   /* temp_v0 in func_8002569C */




void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80025160;
extern M2C_UNK D_80025340;
extern u16 D_8002632A;
extern u8 D_80026478[];
extern s16 D_80026878;

typedef struct S_8002569C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_8002569C_0;   /* temp_v0 in func_8002569C */

typedef struct S_8002569C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_8002569C_1;   /* temp_s2 in func_8002569C */

typedef struct S_8002569C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8002569C_2;   /* arg0 in func_8002569C */

typedef struct S_8002569C_3 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    u8 pad_1E[0x4];
    u16 unk_22;
} S_8002569C_3;   /* temp_v1 in func_8002569C */

typedef struct S_8002569C_4 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_8002569C_4;   /* temp_a0 in func_8002569C */

typedef struct S_8002569C_5 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_8002569C_5;   /* temp_v0_3 in func_8002569C */

/* Create an object offset from an origin and record its starting position. */
void *func_8002569C(S_8002569C_2 *origin, s16 angle, s16 radius, s16 height_offset, s32 alloc_arg) {
    s16 height;
    u16 slot_index;
    u16 origin_x;
    u16 origin_z;
    u16 origin_y;
    S_8002569C_4 *position_slot;
    u8 *position_table;
    S_8002569C_1 *positions;
    void *object;
    S_8002569C_5 *paired_slot;
    S_8002569C_3 *object_data;

    object = func_8003FD64(0x202, alloc_arg);
    if (object != NULL) {
        ((S_8002569C_0 *)object)->unk_10 = &D_80025160;
        func_8004491C(object, &D_80025340);
        positions = ((S_8002569C_0 *)object)->unk_08;
        positions->unk_02 = (s16) (origin->unk_02 + ((s32) (func_80064584(angle) * radius) >> 0xF));
        positions->unk_06 = (s16) (origin->unk_06 + ((s32) (func_800644B8(angle) * radius) >> 0xF));
        height = origin->unk_0A + ((s32) (height_offset << 0x10) >> 0x13);
        positions->unk_0A = height;
        if (D_80026878 < height) {
            positions->unk_0A = D_80026878;
        }
        positions->unk_0E = (u16) origin->unk_02;
        positions->unk_12 = (u16) origin->unk_06;
        positions->unk_16 = (u16) origin->unk_0A;
        object_data = (void *) 0xE04020;
        (*(s32 *)((u8 *)(((S_8002569C_6 *)object)->unk_0C) + 0xC)) = (s32) object_data;
        slot_index = D_8002632A;
        object_data = object + 0x20;
        object_data->unk_16 = angle;
        object_data->unk_1C = height_offset;
        object_data->unk_18 = radius;
        object_data->unk_22 = slot_index;
        if ((s16) slot_index < 0x71) {
            position_table = D_80026478;
            position_slot = &position_table[(s16) slot_index * 8];
            origin_x = positions->unk_0E;
            paired_slot = &position_table[((s16) slot_index + 0x10) * 8];
            position_slot->unk_00 = origin_x;
            paired_slot->unk_00 = origin_x;
            origin_y = positions->unk_12;
            position_slot->unk_02 = origin_y;
            paired_slot->unk_02 = origin_y;
            origin_z = positions->unk_16;
            D_8002632A = slot_index + 1;
            position_slot->unk_04 = origin_z;
            paired_slot->unk_04 = origin_z;
        }
    }
    return object;
}
