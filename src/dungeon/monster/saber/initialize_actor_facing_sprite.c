#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_func_80171CD4_arg0.h"
#include "records/Rec_func_80171CD4_arg1.h"

typedef struct S_80047784 S_80047784;

typedef struct S_80172688_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172688_1;   /* arg3 in initialize_actor_facing_sprite */

struct SpriteFrameState;
extern void select_sprite_entry(struct SpriteFrameState *, s16, s16);         /* extern */
extern u8 D_80174E04;

/* Initialize actor state and select the sprite frame for its facing angle. */
void initialize_actor_facing_sprite(void *actor_state, void *action_state, SpriteFrameState *sprite, void *orientation) {
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9A.as_s8 = 0x10;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9B = 0;
    sprite->frameTable = &D_80174E04;
    select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172688_1 *)orientation)->unk_2A + 0x100)
        >> 9) & 7) + &D_80174E04), 0);
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_90 = 0;
    ((Rec_func_80171CD4_arg1 *)action_state)->unk_14 = 0;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9D = 0;
}
