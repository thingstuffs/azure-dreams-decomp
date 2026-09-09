#include "common.h"
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

typedef struct S_800A5DF8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A5DF8_2;   /* var_v0 in func_800A5DF8 */

typedef struct S_800A5DF8_3 {
    u8 pad_00[0xC4];
    union { s16 s; u16 u; } unk_C4;   /* accessed as both */
    u8 pad_C6[0x2];
    s16 unk_C8;
} S_800A5DF8_3;   /* var_s1 in func_800A5DF8 */

typedef struct S_800A5DF8_4 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5DF8_4;   /* var_s2 in func_800A5DF8 */


s32 func_8008C180();                        /* extern */
s16 func_80094AA0();           /* extern */
M2C_UNK func_80095094();                      /* extern */
M2C_UNK func_80095388();                 /* extern */
M2C_UNK func_800954F4();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
s32 func_800A5894();                          /* extern */
M2C_UNK func_800A55CC();                         /* extern */
s32 func_800C1D44();                             /* extern */
extern u8 D_80083160[];
extern u8 D_80083780[];
extern u8 D_800CFCEF;
extern u8 D_800FE488[];
extern u8 D_800A5FDC[];

/* Updates the actor effect and eases scene values before advancing the state. */
void func_800A5DF8(void *state_arg, void *actor_arg, M2C_UNK context_arg) {
    s16 threshold;
    s16 angle;
    s32 next_offset;
    u16 ticks_left;
    u8 *position;
    register S_800A5DF8_4 *state ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_800A5DF8_0 *actor;
    M2C_UNK context;
    register u8 *scene_state;
    register u8 *effect_data;

    state = state_arg;
    actor = actor_arg;
    context = context_arg;
    scene_state = D_80083160;
    func_80095C80(actor);
    effect_data = D_800FE488;
    threshold = func_80095978(actor, effect_data);
    if (actor->unk_0A >= threshold) {
        func_80095A94(actor, threshold, effect_data);
    } else if (((S_800A5DF8_1 *)(&D_800CFCEF))->unk_00 != 0) {
        actor->unk_14 = 0;
        func_800954F4(actor, threshold);
    } else {
        func_80095388(actor, threshold);
    }
    position = D_80083780;

    if (func_800C1D44(func_8008C180(((S_800A5DF8_2 *)position)->unk_02, ((S_800A5DF8_2 *)position)->unk_06) & 0xFFFF) != 0) {
        actor->unk_14 = (s32) (actor->unk_14 - func_800A5894(actor));
    }
    func_80095094(actor);
    func_80095094(actor);
    angle = func_80094AA0(((S_800A5DF8_3 *)scene_state)->unk_C8, 0, 0x80);
    ((S_800A5DF8_3 *)scene_state)->unk_C8 = angle;
    if ((angle & 0xFFF) < 0x80) {
        ((S_800A5DF8_3 *)scene_state)->unk_C8 = 0;
    }
    ticks_left = state->unk_0A.s - 1;
    state->unk_0A.s = ticks_left;
    {
        s32 shifted_ticks;
        s32 ticks;
        register s32 offset_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        shifted_ticks = (s32) ticks_left << 16;
        ticks = shifted_ticks >> 16;
        offset_step = -0x280;
        if (ticks <= 0) {
            state->unk_0A.u = 0;
        }
        next_offset = ticks > 0
            ? (offset_step = (offset_step - ((S_800A5DF8_3 *)scene_state)->unk_C4.s) / ticks,
               ((S_800A5DF8_3 *)scene_state)->unk_C4.u + offset_step)
            : -0x280;
        ((S_800A5DF8_3 *)scene_state)->unk_C4.s = next_offset;
    }
    if ((state->unk_0A.u == 0) &&
        (((S_800A5DF8_3 *)scene_state)->unk_C8 == 0)) {
        if (state->unk_08 != 0) {
            func_800A55CC(state, actor, context);
        } else {
            state->unk_0A.u = 0;
            state->unk_00 = D_800A5FDC;
        }
    }

    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return;
}
