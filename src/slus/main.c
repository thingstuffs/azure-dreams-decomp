#include "common.h"
#include "shared/game_state.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "sdk/libetc.h"
#include "shared/game_work.h"
#include "shared/runtime_dispatch.h"
#include "slus/animation_tick_data.h"

/* The startup loop increments the word at 0x8001021c once per rendered
 * field. The first user-RAM page precedes the SLUS load at 0x8002d000. */
int main(void) {
    GameWork *game = &g_game_work;
    RuntimeDispatchState *scene;
    GameState *clock;

    ResetCallback();
    clock = GAME_STATE;
    initialize_hardware_and_game_state();
    scene = &runtime_dispatch_state;
    for (;;) {
        reset_callbacks_and_clear_vram();
        reset_transition_state();
        select_next_scene_mode();
        while (!(scene->flags0F & 1)) {
            clock->unk_021C += animation_tick_scale;
            game->unk_004++;
            scene->update();
            render_cd_wait_animation_on_new_field();
        }
    }
}
