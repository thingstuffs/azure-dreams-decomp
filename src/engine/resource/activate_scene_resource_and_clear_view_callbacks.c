#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"
#include "engine/resource.h"
#include "engine/scene.h"

/* D_80082E60: global state struct. field_8 is read as a byte (arg to
 * load_scene_resource_group / copied into field_B), then cleared as a halfword;
 * field_E is cleared as a byte. */
struct S_80082E60 {
    char pad0[8];
    union {
        u8 b;
        u16 h;
    } field_8;
    s8 pad_A;
    s8 field_B;
    s8 field_C;
    s8 field_D;
    s8 field_E;
    char pad_F[0xA];
    s8 field_18;
};



/* D_80083160: shared state table; four u32 fields at these offsets are
 * cleared here (declared >8 bytes to force %hi/%lo addressing). */

/* Saves and processes the state byte, then clears pending state and four shared table fields. */
void activate_scene_resource_and_clear_view_callbacks(void)
{
    u8 state_byte = ((struct S_80082E60 *)&runtime_dispatch_state)->field_8.b;

    runtime_dispatch_state.field_B = state_byte;
    load_scene_resource_group(state_byte);

    runtime_dispatch_state.unk_0E = 0;
    runtime_dispatch_state.unk_08 = 0;

    g_game_work.view.slot[2].callback = 0;
    g_game_work.view.slot[3].callback = 0;
    g_game_work.view.slot[0].callback = 0;
    g_game_work.view.slot[1].callback = 0;
}
