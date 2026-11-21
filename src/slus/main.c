#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "sdk/libetc.h"
#include "shared/game_work.h"
#include "shared/runtime_dispatch.h"
#include "slus/animation_tick_data.h"

/* The startup loop increments the word at 0x8001021c once per rendered
 * field. The first user-RAM page precedes the SLUS load at 0x8002d000. */
typedef struct ResidentClockPage {
    u8 reserved_000[0x21c];
    u32 ticks;
} ResidentClockPage;

int main(void) {
    GameWork *game = &g_game_work;
    RuntimeDispatchState *scene;
    ResidentClockPage *clock;

    ResetCallback();
    clock = (ResidentClockPage *)0x80010000;
    initialize_hardware_and_game_state();
    scene = &runtime_dispatch_state;
    for (;;) {
        reset_callbacks_and_clear_vram();
        reset_transition_state();
        select_next_scene_mode();
        while (!(scene->flags0F & 1)) {
            clock->ticks += animation_tick_scale;
            game->unk_004++;
            scene->update();
            render_cd_wait_animation_on_new_field();
        }
    }
}
