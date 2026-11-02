#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_func_80171CD4_arg0.h"
#include "records/Rec_func_80171CD4_arg1.h"
#include "dungeon/monster/saber.h"
#include "engine/graphics.h"

typedef struct S_80047784 S_80047784;


struct SpriteFrameState;
extern u8 D_80174E04;

/* Initialize actor state and select the sprite frame for its facing angle. */
void initialize_actor_facing_sprite(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, void *orientation) {
    body->action_id.s = 0x10;
    body->action_phase.s = 0;
    sprite->frameTable = &D_80174E04;
    select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)orientation)->facing + 0x100)
        >> 9) & 7) + &D_80174E04), 0);
    body->unk_90.value = 0;
    position->velocity_z = 0;
    body->unk_9D.s = 0;
}
