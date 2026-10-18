#include "modules/dungeon_resource10_slot0.h"

void func_80172730(void *actor_state, void *action_state, void *sprite, void *orientation) {
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9A.as_s8 = 0x10;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9B = 0;
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = ((u8 *)D_801759A0);
    func_80047784(sprite, *((((s32) (g_game_work.view.viewAngle + ((R10_80172730_S_80172688_1 *)orientation)->unk_2A + 0x100)
        >> 9) & 7) + ((u8 *)D_801759A0)), 0);
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_90 = 0;
    ((Rec_func_80171CD4_arg1 *)action_state)->unk_14 = 0;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9D = 0;
}
