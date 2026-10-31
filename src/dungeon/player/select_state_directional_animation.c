#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "dungeon/player.h"
#include "engine/graphics.h"

extern u8 player_tile_motion_frames[];
extern u8 player_alternate_motion_frames[];

/* Reset entity state and select its animation page and directional entry. */
void select_state_16_directional_animation(void *entity, void *unused, void *animation, ActorRecord *state) {
    if (!(((Rec_func_8008ACDC_arg0 *)entity)->unk_98 & 0xC)) {
        u8 *page;
        u8 *current_page;

        ((Rec_func_8008ACDC_arg0 *)entity)->unk_9A.as_u8 = 0x16;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_9B.as_u8 = 0;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_8C.as_s32 = 0;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 &= 0xFFFE;
        if (state->flags1C & ACTOR_CARRYING) {
            u8 *alternate_page = player_alternate_motion_frames;
            current_page = (*(u8 **) ((u8 *)animation + 0x2C));
            page = alternate_page;
        } else {
            current_page = (*(u8 * *) ((u8 *)animation + 0x2C));
            page = player_tile_motion_frames;
        }
        if (current_page != page) {
            entity = animation;
            (*(u8 * *)((u8 *)entity + 0x2C)) = page;
            set_sprite_animation_frame(entity, *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7) + (u32)page),
                0, 1);
        }
    }
}
