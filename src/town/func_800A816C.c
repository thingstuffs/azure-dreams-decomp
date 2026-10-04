#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "m2c_compat.h"

typedef struct S_800A58CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A58CC_0;   /* (void *) shared_s0 in func_800A58CC */

typedef struct S_800A58CC_2 {
    void * unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800A58CC_2;   /* arg0 in func_800A58CC */


s32 func_8008C180();                        /* extern */
s16 func_80094AA0();               /* extern */
void func_80095094();                      /* extern */
void func_80095388();                 /* extern */
void func_800954F4();                 /* extern */
s16 func_80095978();               /* extern */
void func_80095A94();      /* extern */
void func_80095C80();                      /* extern */
s32 func_800A5894();                          /* extern */
s32 func_800C1D44();                             /* extern */
extern s32 D_800A5A98;
extern M2C_UNK D_800FE488;
extern u8 D_800D0000[];

/* Updates the object and interpolates town angles before advancing the state. */
void func_800A58CC(S_800A58CC_2 *state_arg, void *object) {
    s16 threshold;
    s32 pitch_step;
    s16 yaw;
    s32 object_ref;
    s32 target_yaw;
    s32 yaw_delta;
    s32 pitch;
    u16 ticks;
    GameWork *town;
    EntityRec *coords;

         /* MATCH: Order the s2 parameter copy before the s0 copy. */
    object_ref = (s32) object;
    town = &gameWork;
    func_80095C80((void *) object_ref);
    threshold = func_80095978((void *) object_ref, &D_800FE488);
    if (((S_800A58CC_0 *)((void *) object_ref))->unk_0A >= threshold) {
        func_80095A94((void *) object_ref, threshold, &D_800FE488);
    } else {
        if (D_800D0000[-0x311] != 0) {
            ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = 0;
            func_800954F4((void *) object_ref);
        } else {
            func_80095388((void *) object_ref);
        }
    }
    coords = &D_80083780;
    if (func_800C1D44(func_8008C180(coords->x.w.i, coords->y.w.i) & 0xFFFF) != 0) {
        pitch_step = ((S_800A58CC_0 *)((void *) object_ref))->unk_14 - func_800A5894((void *) object_ref);
        ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = pitch_step;
    }
    func_80095094((void *) object_ref);
    func_80095094((void *) object_ref);
    target_yaw = (state_arg->unk_10 - 0x800) & 0xFFF;
    yaw = func_80094AA0(town->view.viewAngle, target_yaw, 0x80);
    town->view.viewAngle = yaw;
    do {
        yaw_delta = (yaw & 0xFFF) - target_yaw;
    } while (0);
    if (yaw_delta < 0) {
        yaw_delta = 0 - yaw_delta;
    }
    if (yaw_delta < 0x80) {
        town->view.viewAngle = target_yaw;
    }
    ticks = state_arg->unk_0A.s - 1;
    state_arg->unk_0A.s = ticks;
    {
        s32 shifted_ticks;
        s32 ticks_left;
        shifted_ticks = (s32) ticks << 16;
        ticks_left = shifted_ticks >> 16;
        pitch_step = -0x2B0;
        if (ticks_left <= 0) {
            state_arg->unk_0A.u = 0;
        }
        pitch = ticks_left > 0
            ? (pitch_step -= town->view.unk_0AC, pitch_step /= ticks_left,
               ((u16)town->view.unk_0AC) + pitch_step)
        : -0x2B0;
        town->view.unk_0AC = pitch;
    }
    if ((state_arg->unk_0A.u == 0) && (town->view.viewAngle == target_yaw)) {
        state_arg->unk_0A.u = 0;
        state_arg->unk_00 = &D_800A5A98;
    }
}
