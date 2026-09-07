#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800CABA8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x8];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_AC;   /* overlapping accesses */
    u16 unk_B0;
    u8 pad_B2[0x4];
    u16 unk_B6;
    s16 unk_B8;
} S_800CABA8_0;   /* arg0 in func_800CABA8 */


typedef struct S_800CABA8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_800CABA8_2;   /* temp_s2 in func_800CABA8 */


extern void *D_80089440[];
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
extern void func_800CAA94(void *, M2C_UNK, void *);
M2C_UNK func_800CAFDC();
M2C_UNK func_800CB4C0();
extern u16 D_80013714;
extern s32 D_8008346C;
extern u8 D_800C9F34;

/* Advances the actor rotation and color effect through fading and cleanup. */
void func_800CABA8(void *effect, M2C_UNK context, void *record, void *actor) {
    static void *const phase_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s16 fade_ticks_left;
    s16 restore_ticks;
    s16 restore_ticks_left;
    s16 next_duration;
    register s32 green_step_or_effect ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 red_step;
    s32 fade_ticks;
    s32 phase_or_ticks;
    register s32 blue_step ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 rotation_done;
    u16 effect_level;
    u16 cycles_left;
    u16 flags;
    u8 fade_blue;
    s32 restore_blue;
    s32 fade_green;
    s32 restore_green;
    register u8 red ASM_REG("$8");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 phase;
    void *effect_base;
    void *actor_state;
    void *actor_or_green;

    actor_or_green = actor;
    phase = ((S_800CABA8_0 *)effect)->unk_9B;
    actor_state = actor_or_green;
    if (phase >= 5U) {
        goto block_23;
    }
    (void)phase_labels; goto *D_80089440[(u32)(phase)];
jt_c0:
    ((S_800CABA8_0 *)effect)->unk_B8 = 1;
    if (!(((Rec_D_80082E80 *)record)->unk_14.at00_u16.v & 0x8000)) {
        goto block_4;
    }
    func_8009C12C(actor_state, record, ((S_800CABA8_2 *)actor_state)->unk_2A, 0);
    ((S_800CABA8_0 *)effect)->unk_9B = 4U;
    return;
block_4:
    ((S_800CABA8_0 *)effect)->unk_B0 = (u16) ((S_800CABA8_2 *)actor_state)->unk_2A;
    ((S_800CABA8_0 *)effect)->unk_9B = (u8) (((S_800CABA8_0 *)effect)->unk_9B + 1);
jt_c1:
    ((S_800CABA8_0 *)effect)->unk_98 |= 8;
    effect_level = ((S_800CABA8_0 *)effect)->unk_A0.at02.v + 0x10;
    ((S_800CABA8_0 *)effect)->unk_A0.at02.v = effect_level;
    if ((s16) effect_level < 0x81) {
        goto block_23;
    }
    ((S_800CABA8_0 *)effect)->unk_A0.at02.v = 0x80U;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    phase_or_ticks = ((S_800CABA8_0 *)effect)->unk_9B;
    next_duration = 8;
    goto block_9;
jt_c2:
    effect_base = effect - 0x20;
    ((S_800CABA8_0 *)effect)->unk_A0.at00.v = (s32) (((S_800CABA8_0 *)effect)->unk_A0.at00.v - (((S_800CABA8_0 *)effect)->unk_A0.at00.v / (s16) ((S_800CABA8_0 *)effect)->unk_96));
    func_800CAFDC(effect_base, ((S_800CABA8_2 *)actor_state)->unk_2A, ((S_800CABA8_0 *)effect)->unk_AC.at00.v);
    func_800CB4C0(effect_base, 1);
    red = (u8) ((S_800CABA8_0 *)effect)->unk_AC.at00.v;
    red_step = (s32) (0xE0 - red) / (s16) ((S_800CABA8_0 *)effect)->unk_96;
    fade_green = ((S_800CABA8_0 *)effect)->unk_AC.at01.v;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    fade_ticks = ((S_800CABA8_0 *)effect)->unk_96;
    ASM_KEEP(fade_ticks);   /* MATCH pin: retail schedule: same instructions, different order without it */
    green_step_or_effect = (s32) (8 - fade_green) / fade_ticks;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    fade_blue = ((S_800CABA8_0 *)effect)->unk_AC.at02.v;
    blue_step = (s32) (8 - fade_blue) / (s16) ((S_800CABA8_0 *)effect)->unk_96;
    fade_ticks_left = (u16) ((S_800CABA8_0 *)effect)->unk_96 - 1;
    ((S_800CABA8_0 *)effect)->unk_96 = fade_ticks_left;
    red = (u8) (red + red_step);
    fade_green += green_step_or_effect;
    ((S_800CABA8_0 *)effect)->unk_AC.at00u.v = red;
    ((S_800CABA8_0 *)effect)->unk_AC.at01.v = (u8) fade_green;
    ((S_800CABA8_0 *)effect)->unk_AC.at02.v = (u8) (fade_blue + blue_step);
    if ((fade_ticks_left << 0x10) > 0) {
        goto block_23;
    }
    func_8009C12C(actor_state, record, ((S_800CABA8_2 *)actor_state)->unk_2A, 0);
    phase_or_ticks = ((S_800CABA8_0 *)effect)->unk_9B;
    ASM_KEEP(phase_or_ticks);   /* MATCH pin: retail basic-block layout depends on it */
    next_duration = 4;
block_9:
    ((S_800CABA8_0 *)effect)->unk_96 = next_duration;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    ((S_800CABA8_0 *)effect)->unk_9B = (u8) (phase_or_ticks + 1);
    return;
jt_c3:
    if ((s16) ((S_800CABA8_0 *)effect)->unk_B0 == ((S_800CABA8_2 *)actor_state)->unk_2A) {
        goto block_12;
    }
    ((S_800CABA8_2 *)actor_state)->unk_2A = (s16) ((u16) ((S_800CABA8_2 *)actor_state)->unk_2A + 0x200);
    rotation_done = 0;
    goto block_13;
block_12:
    rotation_done = 1;
block_13:
    restore_ticks = ((S_800CABA8_0 *)effect)->unk_96;
    if (restore_ticks <= 0) {
        goto block_15;
    }
    red = (u8) ((S_800CABA8_0 *)effect)->unk_AC.at00.v;
    restore_green = ((S_800CABA8_0 *)effect)->unk_AC.at01.v;
    restore_blue = ((S_800CABA8_0 *)effect)->unk_AC.at02.v;
    ((S_800CABA8_0 *)effect)->unk_AC.at00u.v = (u8) (red + ((s32) (0x40 - red) / restore_ticks));
    actor_or_green = restore_green + ((s32) (0x40 - restore_green) / (s16) ((S_800CABA8_0 *)effect)->unk_96);
    ((S_800CABA8_0 *)effect)->unk_AC.at01.v = (u8) actor_or_green;
    ((S_800CABA8_0 *)effect)->unk_AC.at02.v = (u8) (restore_blue + ((s32) (0x40 - restore_blue) / (s16) ((S_800CABA8_0 *)effect)->unk_96));
    goto block_16;
block_15:
    ((S_800CABA8_0 *)effect)->unk_96 = 0;
block_16:
    phase_or_ticks = (u16) ((S_800CABA8_0 *)effect)->unk_96;
    restore_ticks_left = phase_or_ticks - 1;
    phase_or_ticks = rotation_done;
    ((S_800CABA8_0 *)effect)->unk_96 = restore_ticks_left;
    if (phase_or_ticks == 0) {
        goto block_23;
    }
    phase_or_ticks = restore_ticks_left << 0x10;
    if (phase_or_ticks > 0) {
        goto block_23;
    }
    ((S_800CABA8_0 *)effect)->unk_98 = (u16) (((S_800CABA8_0 *)effect)->unk_98 & 0xFFF7);
    ((S_800CABA8_0 *)effect)->unk_9B = (u8) (((S_800CABA8_0 *)effect)->unk_9B + 1);
jt_c4:
    ((S_800CABA8_0 *)effect)->unk_A0.at02.v = 0U;
    func_800A2B04(context, ((Rec_D_80082E80 *)record)->unk_24, ((Rec_D_80082E80 *)record)->unk_25);
    D_8008346C = 0;
    ((S_800CABA8_2 *)actor_state)->unk_46 = (u16) ((*(u16 *)((u8 *)actor_state + 0x46)) & 0x7FFF);
    func_800A4ACC(actor_state);
    cycles_left = ((S_800CABA8_0 *)effect)->unk_B6 - 1;
    ((S_800CABA8_0 *)effect)->unk_B6 = cycles_left;
    green_step_or_effect = (s32) effect;
    if ((cycles_left << 0x10) <= 0) {
        goto block_21;
    }
    if (!(D_80013714 & 8)) {
        goto block_22;
    }
block_21:
    func_800CAA94((void *) green_step_or_effect, context, record);
    return;
block_22:
    ((S_800CABA8_0 *)effect)->unk_8C = &D_800C9F34;
block_23:
    return;
}
