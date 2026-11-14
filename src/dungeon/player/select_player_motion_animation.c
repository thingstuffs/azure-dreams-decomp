#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "dungeon/player.h"
#include "engine/graphics.h"
#include "dungeon/data.h"

/* Reset entity state and select its animation page and directional entry. */
void select_player_motion_animation(void *entity_data, ObjectPosition *unused, void *animation, ActorRecord *state) {
    ActorRecord *entity = entity_data;

    if (!(entity->action_state_flags & 0xC)) {
        u8 *page;
        u8 *current_page;

        entity->action_id = 0x16;
        entity->action_phase = 0;
        entity->unk_8C.word = 0;
        entity->unk_A0.parts.high &= 0xFFFE;
        if (state->flags1C & ACTOR_CARRYING) {
            u8 *alternate_page = player_alternate_motion_frames;
            current_page = (*(u8 **) ((u8 *)animation + 0x2C));
            page = alternate_page;
        } else {
            current_page = (*(u8 * *) ((u8 *)animation + 0x2C));
            page = player_tile_motion_frames;
        }
        if (current_page != page) {
            entity_data = animation;
            (*(u8 * *)((u8 *)entity_data + 0x2C)) = page;
            set_sprite_animation_frame(entity_data, *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7) + (u32)page),
                0, 1);
        }
    }
}
