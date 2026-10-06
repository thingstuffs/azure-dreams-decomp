#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "m2c_compat.h"

typedef struct S_800A5DF8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A5DF8_0;   /* var_s0 in func_800A5DF8 */

typedef struct S_800A5DF8_1 {
    u8 unk_00;
} S_800A5DF8_1;   /* &D_800CFCEF in func_800A5DF8 */

typedef struct S_800A5DF8_4 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5DF8_4;   /* var_s2 in func_800A5DF8 */


s32 func_8008C180();                        /* extern */
s16 func_80094AA0();           /* extern */
void func_80095094();                      /* extern */
void func_80095388();                 /* extern */
void func_800954F4();                 /* extern */
s16 func_80095978();               /* extern */
void func_80095A94();      /* extern */
void func_80095C80();                      /* extern */
s32 func_800A5894();                          /* extern */
void func_800A55CC();                         /* extern */
s32 func_800C1D44();                             /* extern */
extern u8 D_800CFCEF;
extern u8 D_800A5FDC[];

/* Updates the actor effect and eases scene values before advancing the state. */
void func_800A5DF8(S_800A5DF8_4 *state, S_800A5DF8_0 *actor, s32 context) {
    s16 threshold;
    s32 offset_step;
    s16 angle;
    s32 next_offset;
    u16 ticks_left;
    register GameWork *scene_state;
    register u8 *effect_data;

    scene_state = &gameWork;
    func_80095C80(actor);
    effect_data = ((u8 *)&D_800FE488);
    threshold = func_80095978(actor, effect_data);
    if (actor->unk_0A >= threshold) {
        func_80095A94(actor, threshold, effect_data);
    } else if (((S_800A5DF8_1 *)(&D_800CFCEF))->unk_00 != 0) {
        actor->unk_14 = 0;
        func_800954F4(actor);
    } else {
        func_80095388(actor);
    }

    if (func_800C1D44(func_8008C180(D_80083780.x.w.i, D_80083780.y.w.i) & 0xFFFF) != 0) {
        offset_step = actor->unk_14 - func_800A5894(actor);
        actor->unk_14 = offset_step;
    }
    func_80095094(actor);
    func_80095094(actor);
    angle = func_80094AA0(scene_state->view.viewAngle, 0, 0x80);
    scene_state->view.viewAngle = angle;
    if ((angle & 0xFFF) < 0x80) {
        scene_state->view.viewAngle = 0;
    }
    ticks_left = state->unk_0A.s - 1;
    state->unk_0A.s = ticks_left;
    {
        s32 shifted_ticks;
        s32 ticks;
        shifted_ticks = (s32) ticks_left << 16;
        ticks = shifted_ticks >> 16;
        offset_step = -0x280;
        if (ticks <= 0) {
            state->unk_0A.u = 0;
        }
        next_offset = ticks > 0
            ? (offset_step -= scene_state->view.unk_0AC, offset_step /= ticks,
               ((u16)scene_state->view.unk_0AC) + offset_step)
        : -0x280;
        scene_state->view.unk_0AC = next_offset;
    }
    if ((state->unk_0A.u == 0) &&
        (scene_state->view.viewAngle == 0)) {
        if (state->unk_08 != 0) {
            func_800A55CC(state, actor, context);
        } else {
            state->unk_0A.u = 0;
            state->unk_00 = D_800A5FDC;
        }
    }

    return;
}
