#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A58CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A58CC_0;   /* (void *) shared_s0 in func_800A58CC */

typedef struct S_800A58CC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A58CC_1;   /* coords in func_800A58CC */

typedef struct S_800A58CC_2 {
    void * unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800A58CC_2;   /* arg0 in func_800A58CC */

typedef struct S_800A58CC_3 {
    u8 pad_00[0xC4];
    union { s16 s; u16 u; } unk_C4;   /* accessed as both */
    u8 pad_C6[0x2];
    s16 unk_C8;
} S_800A58CC_3;   /* town in func_800A58CC */


s32 func_8008C180();                        /* extern */
s16 func_80094AA0();               /* extern */
M2C_UNK func_80095094();                      /* extern */
M2C_UNK func_80095388();                 /* extern */
M2C_UNK func_800954F4();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
s32 func_800A5894();                          /* extern */
s32 func_800C1D44();                             /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80083780;
extern s32 D_800A5A98;
extern M2C_UNK D_800FE488;
extern u8 D_800D0000[];

/* Updates the object and interpolates town angles before advancing the state. */
void func_800A58CC(S_800A58CC_2 *state_arg, void *object) {
    register S_800A58CC_2 *state ASM_REG("$18") = state_arg; /* MATCH: Keep the object in retail s2 across the merged control-flow arms. */
    s16 threshold;
    s16 yaw;
    s32 object_ref;
    s32 target_yaw;
    s32 yaw_delta;
    s32 pitch;
    u16 ticks;
    u8 *town;
    u8 *coords;

     /* MATCH: Order the s2 parameter copy before the s0 copy. */
    object_ref = (s32) object;
    town = D_80083160;
    func_80095C80((void *) object_ref);
    threshold = func_80095978((void *) object_ref, &D_800FE488);
    if (((S_800A58CC_0 *)((void *) object_ref))->unk_0A >= threshold) {
        func_80095A94((void *) object_ref, threshold, &D_800FE488);
    } else {
        if (D_800D0000[-0x311] != 0) {
            ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = 0;
            func_800954F4((void *) object_ref, threshold);
        } else {
            func_80095388((void *) object_ref, threshold);
        }
    }
    coords = (u8 *)&D_80083780;
    if (func_800C1D44(func_8008C180(((S_800A58CC_1 *)coords)->unk_02, ((S_800A58CC_1 *)coords)->unk_06) & 0xFFFF) != 0) {
        ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = (s32) (((S_800A58CC_0 *)((void *) object_ref))->unk_14 - func_800A5894((void *) object_ref));
    }
    func_80095094((void *) object_ref);
    func_80095094((void *) object_ref);
    target_yaw = (state->unk_10 - 0x800) & 0xFFF;
    yaw = func_80094AA0(((S_800A58CC_3 *)town)->unk_C8, target_yaw, 0x80);
    ((S_800A58CC_3 *)town)->unk_C8 = yaw;
    do {
        yaw_delta = (yaw & 0xFFF) - target_yaw;
    } while (0);
    if (yaw_delta < 0) {
        yaw_delta = 0 - yaw_delta;
    }
    if (yaw_delta < 0x80) {
        ((S_800A58CC_3 *)town)->unk_C8 = target_yaw;
    }
    ticks = state->unk_0A.s - 1;
    state->unk_0A.s = ticks;
    {
        s32 shifted_ticks;
        s32 ticks_left;
        register s32 pitch_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        shifted_ticks = (s32) ticks << 16;
        ticks_left = shifted_ticks >> 16;
        pitch_step = -0x2B0;
        if (ticks_left <= 0) {
            state->unk_0A.u = 0;
        }
        pitch = ticks_left > 0
            ? (pitch_step = (pitch_step - ((S_800A58CC_3 *)town)->unk_C4.s) / ticks_left,
               ((S_800A58CC_3 *)town)->unk_C4.u + pitch_step)
            : -0x2B0;
        ((S_800A58CC_3 *)town)->unk_C4.s = pitch;
    }
    if ((state->unk_0A.u == 0) && (((S_800A58CC_3 *)town)->unk_C8 == target_yaw)) {
        state->unk_0A.u = 0;
        state->unk_00 = &D_800A5A98;
    }
}
