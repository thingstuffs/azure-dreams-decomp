#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_func_801724B0_arg0.h"
#include "shared/entity.h"

typedef struct S_80047784 S_80047784;

struct SpriteFrameState;
void select_sprite_entry(void *, s16, s16);         /* extern */
extern u8 D_800E2360;

/* Initializes state and configures the target using an angle-indexed table entry. */
void initialize_angle_indexed_target(void *state, s32 unused, SpriteFrameState *target, EntityRec *angleSource) {
    ((Rec_func_801724B0_arg0 *)state)->unk_9A = 0x10;
    ((Rec_func_801724B0_arg0 *)state)->unk_9B = 0;
    target->frameTable = &D_800E2360;
    select_sprite_entry(target, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + angleSource->facing + 0x100) >> 9) & 7) + &D_800E2360),
        0);
    ((Rec_func_801724B0_arg0 *)state)->unk_AA = 0;
}
