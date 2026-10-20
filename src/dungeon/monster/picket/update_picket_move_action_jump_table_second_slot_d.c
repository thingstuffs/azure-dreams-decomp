#include "common.h"

extern void update_picket_move_action_slot_d(void);

/* jump_table; owner: dungeon/func_80E9F490. */
const u32 D_8015E880[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_picket_move_action_slot_d + 0x15C),
    (u32)((u8 *)update_picket_move_action_slot_d + 0x154),
    (u32)((u8 *)update_picket_move_action_slot_d + 0x14C),
    (u32)((u8 *)update_picket_move_action_slot_d + 0x164),
    (u32)((u8 *)update_picket_move_action_slot_d + 0x108),
    (u32)((u8 *)update_picket_move_action_slot_d + 0x100),
    (u32)((u8 *)update_picket_move_action_slot_d + 0xF8)
};
