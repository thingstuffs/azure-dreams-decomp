#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern void select_sprite_entry();

extern u8 golem_action_continuation_address[];
extern u8 golem_direction_frames[];
extern u8 golem_alt_direction_frames[];

typedef struct S_func_810870DC_0 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
} S_func_810870DC_0;

typedef struct S_func_810870DC_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_func_810870DC_2;

/* Updates directional animation and entity state when the transition flags allow. */
void update_directional_transition_state(S_func_810870DC_0 *entity, void *unused, SpriteFrameState *animation,
    S_func_810870DC_2 *orientation)
{
    GameWork *scene_data = &g_game_work;
    u8 state = entity->unk_9B;

    switch (state) {
    case 0:
        if (animation->flags & 0xE000) {
            animation->frameTable = golem_alt_direction_frames;
            select_sprite_entry(animation,
                golem_alt_direction_frames[((scene_data->view.camera_rotation.parts.viewAngle +
                    orientation->unk_2A + 0x100) >> 9) & 7], 0);
            entity->unk_9B++;
        }
        break;
    case 1:
    {
        s32 scene_flags = scene_data->buttons;

        /*
         * Original bug: Select blocks the Golem idle reservation's release and leaves its normal callback null. The
         * watchdog clears the count after 901 unchanged updates outside Koh's idle. Movement then expects a ready
         * familiar to leave its tile, but this Golem still cannot move while Select blocks completion, so Koh can
         * enter its tile. Found and documented by the Azure Dreams community (adrando.com/guide/bugs.html).
         */
        if (!(scene_flags & 0x100) && (scene_flags & 0xFFFF)) {
            animation->frameTable = golem_direction_frames;
            select_sprite_entry(animation,
                golem_direction_frames[((scene_data->view.camera_rotation.parts.viewAngle +
                    orientation->unk_2A + 0x100) >> 9) & 7], 0);
            entity->unk_8C = golem_action_continuation_address;
            entity->unk_A6 = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
    }
        break;
    }
}
