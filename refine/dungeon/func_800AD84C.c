#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B2FAC_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800B2FAC_0;   /* arg2 in func_800B2FAC */

typedef struct S_800B2FAC_1_pre {
    u16 unk_00;
} S_800B2FAC_1_pre;   /* the 0x2 bytes before arg3 in func_800B2FAC, addressed as arg3[-1] */

typedef struct S_800B2FAC_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B2FAC_1;   /* arg3 in func_800B2FAC */


M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800A2DB8();                      /* extern */
M2C_UNK func_800A32A4();                      /* extern */
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;

/* Update a flagged target and its tile state, then mark it dirty. */
void func_800B2FAC(void *unused_0, void *unused_1, void *source, void *target) {
    M2C_UNK update_mask;
    s32 target_flags;
    u8 tile_x;
    u8 tile_y;
    s32 *global_state;

    if (((S_800B2FAC_0 *)source)->unk_14 & 0xE000) {
        global_state = &D_80083460;
        if (global_state[4] == (target - 0x20)) {
            global_state[4] = global_state[4] & 0x7FFFFFFF;
        }
        func_800A2DB8(target);
        func_800A32A4(target);
        target_flags = ((S_800B2FAC_1 *)target)->unk_1C;
        tile_x = ((S_800B2FAC_0 *)source)->unk_24;
        tile_y = ((S_800B2FAC_0 *)source)->unk_25;
        update_mask = 0x3000;
        if (target_flags & 0x2000) {
            update_mask = 0x300;
        }
        func_8009A3D0(tile_x, tile_y, update_mask);
        func_8009A028(target);
        (*(u16 *)((u8 *)target + -2)) = (u16) (((S_800B2FAC_1_pre *)target)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}
