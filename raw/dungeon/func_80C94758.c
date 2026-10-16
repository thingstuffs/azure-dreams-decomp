#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
void func_80047784(void *, u8, M2C_UNK);         /* extern */

extern u8 D_801752C4[8];


typedef struct S_80171F58_0 {
    u8 pad_00[0x9A];
    s8 action;
    s8 action_tick;
} S_80171F58_0;   /* state in func_80171F58 */

typedef struct S_80171F58_1 {
    u8 pad_00[0x2C];
    M2C_UNK * unk_2C;
} S_80171F58_1;   /* render_state in func_80171F58 */

typedef struct S_80171F58_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80171F58_2;   /* entity in func_80171F58 */

/* Select the overlay animation for the camera-relative facing and enter action 16. */
void func_80171F58(S_80171F58_0 *state, void *unused_position, S_80171F58_1 *render_state, S_80171F58_2 *entity) {
    state->action = 0x10;
    state->action_tick = 0;
    render_state->unk_2C = D_801752C4;
    func_80047784(render_state, *((((s32) (gameWork.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7) + D_801752C4), 0);
}
