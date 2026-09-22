#include "common.h"
#include "m2c_compat.h"

typedef struct S_800178B4_3 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    M2C_UNK * unk_08;
} S_800178B4_3;   /* (offset2 + menu->unk_10) in func_800178B4 */


s32 func_800169EC();                                /* extern */
M2C_UNK func_80017808();                      /* extern */
M2C_UNK func_80019814();                 /* extern */
M2C_UNK func_8001A418();                         /* extern */
s32 func_8001A510();                         /* extern */
extern M2C_UNK D_80016A3C;
extern M2C_UNK D_80017B40;
extern M2C_UNK D_8001B718;
extern M2C_UNK D_8001B81C;

typedef struct S_800178B4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} S_800178B4_0;   /* menu in func_800178B4 */

typedef struct S_800178B4_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800178B4_1;   /* slot_addr in func_800178B4 */

typedef struct S_800178B4_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
} S_800178B4_2;   /* slot in func_800178B4 */

/* Install the town menu slot's handler pair: the first call takes flag 0x479 and the primary pair, later calls take the alternate pair, then both run the menu's own hook. */
s32 func_800178B4(S_800178B4_0 *menu, s32 index) {
    s32 offset;
    s32 offset2;
    S_800178B4_2 *slot;

    if ((func_8001A510(0x479) == 0) && (func_800169EC() != 0)) {
        func_8001A418(0x479);
        offset = index * 0x10;
        {
            M2C_UNK *handler;
            s32 slot_addr;

            slot_addr = offset + menu->unk_10;
            handler = &D_80016A3C;
            ((S_800178B4_1 *)slot_addr)->unk_04 = handler;
        }
        slot = offset + menu->unk_10;
        slot->unk_08 = &D_8001B718;
        func_80017808(slot);
        return 0;
    }
    if (func_8001A510(0x479) != 0) {
        offset2 = index * 0x10;
        ((S_800178B4_3 *)((offset2 + menu->unk_10)))->unk_04 = &D_80017B40;
        ((S_800178B4_3 *)((offset2 + menu->unk_10)))->unk_08 = &D_8001B81C;
    }
    func_8001A418(menu->unk_18);
    return func_80019814(menu, index);
}

/* MECHANISM: Holding menu/index in s0/s1 and delaying the second scaled index restores the 32-byte frame.
   The true-space s32 function uses return 0 for the in-row epilogue edge, removing the phantom call.
   At 2.7.2-cdk-G0, an arm-local v1 pin destructively forms offset + base; post-store ASM_KEEP
   preserves the exact lui/lw/addiu schedule and the ordered addu v1,a0,v1. */
