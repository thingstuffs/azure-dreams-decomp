#include "modules/town_ovl_3ef1c8.h"

s32 func_800178B4(S_800178B4_0 *menu, s32 index) {
    s32 offset;
    s32 offset2;
    S_800178B4_2 *slot;

    if ((func_8001A510(0x479) == 0) && (townCheckInteraction13Type3() != 0)) {
        func_8001A418(0x479);
        offset = index * 0x10;
        {
            SceneHandler3 handler;
            s32 slot_addr;

            slot_addr = offset + menu->unk_10;
            handler = townSelectInteractionResultWithRefresh;
            ((S_800178B4_1 *)slot_addr)->handler = handler;
        }
        slot = offset + menu->unk_10;
        slot->unk_08 = &D_8001B718;
        townMarkProgressStateReady();
        return 0;
    }
    if (func_8001A510(0x479) != 0) {
        offset2 = index * 0x10;
        ((S_800178B4_3 *)((offset2 + menu->unk_10)))->handler = func_80017B40;
        ((S_800178B4_3 *)((offset2 + menu->unk_10)))->unk_08 = &D_8001B81C;
    }
    func_8001A418(menu->unk_18);
    return func_80019814(menu, index);
}

/* MECHANISM: Holding menu/index in s0/s1 and delaying the second scaled index restores the 32-byte frame.
   The true-space s32 function uses return 0 for the in-row epilogue edge, removing the phantom call.
   At 2.7.2-cdk-G0, an arm-local v1 pin destructively forms offset + base; post-store ASM_KEEP
   preserves the exact lui/lw/addiu schedule and the ordered addu v1,a0,v1. */
