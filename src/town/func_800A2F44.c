#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A06A4_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
    s32 unk_18;
    M2C_UNK * unk_1C;
    u8 pad_20[0x40];
    M2C_UNK * unk_60;
    u8 pad_64[0x14];
    s16 unk_78;
    u8 pad_7A[0x4];
    s16 unk_7E;
    u8 pad_80[0x20];
    s16 unk_A0;
    u8 pad_A2[0x2];
    u8 unk_A4;
} S_800A06A4_0;   /* arg0 in func_800A06A4; pointer addresses record offset 0x10 */


extern M2C_UNK D_800A0708;
extern M2C_UNK D_800A07A4;
extern M2C_UNK D_800A0AC8;
extern M2C_UNK D_800A0BE4;
extern M2C_UNK D_800D09E0;

/* Initialize the record and select its handler according to its variant. */
void func_800A06A4(void *record_data, s32 initial_value) {
    u8 variant;

    variant = ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_A4;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800A0708;
    {
        union { M2C_UNK *pointer; s32 value; } handler;

        if (variant == 1) {
            handler.value = 2;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_A0 = handler.value;
            handler.pointer = &D_800A0BE4;
        } else if (variant == 0) {
            handler.pointer = &D_800A0AC8;
            goto store_handler;
        } else {
            handler.pointer = &D_800A07A4;
        }
        ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_7E = 0;
store_handler:
        ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_60 = handler.pointer;
    }
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_18 = initial_value;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_1C = &D_800D09E0;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_78 = 0;
}
