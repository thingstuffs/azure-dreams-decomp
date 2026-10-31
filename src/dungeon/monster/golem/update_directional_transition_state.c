#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/graphics.h"
#include "shared/entity.h"


extern u8 golem_action_continuation_address[];
extern u8 golem_direction_frames[];
extern u8 golem_alt_direction_frames[];



/* Updates directional animation and entity state when the transition flags allow. */
void update_directional_transition_state(ActorRecord *entity, ObjectPosition *position, SpriteFrameState *sprite,
    ActorRecord *actor)
{
    GameWork *scene_data = &g_game_work;
    u8 state = entity->action_phase.u;

    switch (state) {
    case 0:
        if (sprite->flags & 0xE000) {
            sprite->frameTable = golem_alt_direction_frames;
            select_sprite_entry(sprite,
                golem_alt_direction_frames[((scene_data->view.camera_rotation.parts.viewAngle +
                    actor->facing + 0x100) >> 9) & 7], 0);
            entity->action_phase.u++;
        }
        break;
    case 1:
    {
        s32 scene_flags = scene_data->buttons;

        /*
         * BUG: Select blocks the Golem idle reservation's release and leaves its normal callback null. The
         * watchdog clears the count after 901 unchanged updates outside Koh's idle. Movement then expects a ready
         * familiar to leave its tile, but this Golem still cannot move while Select blocks completion, so Koh can
         * enter its tile. Found and documented by the Azure Dreams community (adrando.com/guide/bugs.html).
         */
        if (!(scene_flags & 0x100) && (scene_flags & 0xFFFF)) {
            sprite->frameTable = golem_direction_frames;
            select_sprite_entry(sprite,
                golem_direction_frames[((scene_data->view.camera_rotation.parts.viewAngle +
                    actor->facing + 0x100) >> 9) & 7], 0);
            entity->unk_8C.address = golem_action_continuation_address;
            entity->unk_A4.halves.high.s = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
    }
        break;
    }
}
