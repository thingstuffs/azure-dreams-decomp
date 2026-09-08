#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A9AFC_2 {
    u8 pad_00[0x73];
    u8 unk_73;
    u8 pad_74[0x7];
    u8 unk_7B;
} S_800A9AFC_2;   /* (arg1 + ((S_800A9AFC_0 *)arg1)->unk_71) in func_800A9AFC */




M2C_UNK func_80042900();             /* extern */
M2C_UNK func_80069F28();     /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */

typedef struct S_800A9AFC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
    u8 pad_6C[0x5];
    u8 unk_71;
    u8 pad_72[0x2];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
    u8 pad_7D[0xB];
    u16 unk_88;
    u16 unk_8A;
} S_800A9AFC_0;   /* arg1 in func_800A9AFC */

typedef struct S_800A9AFC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A9AFC_1;   /* arg0 in func_800A9AFC */

/* Rotates queued coordinates into the current position and updates tile flags. */
void func_800A9AFC(S_800A9AFC_1 *position, void *state) {
    M2C_UNK clear_mask;
    M2C_UNK set_mask;
    s32 status_result;
    u8 next_x;
    u8 next_y;

    if (((S_800A9AFC_0 *)state)->unk_71 & 0x7F) {
        status_result = (s16) func_80042900(state, 0x1B);
        if (status_result == 0) {
            M2C_UNK flags;
            u8 tile_x;
            u8 tile_y;

            flags = ((S_800A9AFC_0 *)state)->unk_1C;
            tile_x = position->unk_24;
            tile_y = position->unk_25;
            clear_mask = 0x3000;
            if (flags & 0x2000) {
                clear_mask = 0x300;
            }
            func_8009A3D0(tile_x, tile_y, clear_mask);
        }
        next_x = ((S_800A9AFC_0 *)state)->unk_74;
        next_y = ((S_800A9AFC_0 *)state)->unk_7C;
        func_80069F28(state + 0x74, state + 0x75, 0xF);
        ((S_800A9AFC_2 *)((state + ((S_800A9AFC_0 *)state)->unk_71)))->unk_73 = (u8) position->unk_24;
        ((S_800A9AFC_2 *)((state + ((S_800A9AFC_0 *)state)->unk_71)))->unk_7B = (u8) position->unk_25;
        position->unk_24 = next_x;
        position->unk_25 = next_y;
        ((S_800A9AFC_0 *)state)->unk_88 = (u16) ((S_800A9AFC_0 *)state)->unk_8A;
        ((S_800A9AFC_0 *)state)->unk_2A = (u16) ((S_800A9AFC_0 *)state)->unk_6A;
        if (status_result == 0) {
            M2C_UNK flags;
            u8 tile_x;
            u8 tile_y;

            flags = ((S_800A9AFC_0 *)state)->unk_1C;
            tile_x = position->unk_24;
            tile_y = position->unk_25;
            set_mask = 0x3000;
            if (flags & 0x2000) {
                set_mask = 0x300;
            }
            func_8009A21C(tile_x, tile_y, set_mask);
        }
        ((S_800A9AFC_0 *)state)->unk_8A = 0U;
    }
}
