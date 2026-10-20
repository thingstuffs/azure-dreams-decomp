#include "modules/dungeon_resource10_slot0.h"
#include "shared/sprite_frame_state.h"

void func_80172730(void *actor_state, void *action_state, SpriteFrameState *sprite, void *orientation) {
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9A.as_s8 = 0x10;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9B = 0;
    sprite->frameTable = ((u8 *)D_801759A0);
    select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80172730_S_80172688_1 *)orientation)->unk_2A + 0x100)
        >> 9) & 7) + ((u8 *)D_801759A0)), 0);
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_90 = 0;
    ((Rec_func_80171CD4_arg1 *)action_state)->unk_14 = 0;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9D = 0;
}
