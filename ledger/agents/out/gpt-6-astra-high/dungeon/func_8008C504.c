#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80091C64_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x76];
    u16 unk_11A;
} S_80091C64_0;   /* arg0 in func_80091C64 */

typedef struct S_80091C64_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_80091C64_1;   /* arg3 in func_80091C64 */

typedef struct S_80091C64_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_80091C64_2;   /* arg1 in func_80091C64 */


typedef struct S_80091C64_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80091C64_4;   /* var_v1 in func_80091C64 */


extern void *D_800889A8[];
void func_80048A44();
s32 func_800644B8();
s32 func_80064584();
M2C_UNK func_800A2B04();
M2C_UNK func_800A56E0();
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_8008EAC8;
extern u8 D_800DD038[];
extern u8 D_800DD058[];

/* Animate a hop and return to the entity's tile, then restore its facing and behavior. */
void func_80091C64(void *motion, void *position, void *entity, void *actor) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    M2C_UNK *next_behavior;
    M2C_UNK *action_tracker;
    s16 frames_left;
    u8 phase;
    u8 completed_phase;
    register u16 return_duration ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 target_x;
    s32 current_x;
    s32 y_work;
    register s32 y_step ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u16 delay_left;
    u16 hop_frames_left;
    u16 return_frames_left;

    phase = ((S_80091C64_0 *)motion)->unk_9B;
    if (phase >= 5U) {
        goto done;
    }
    (void)jt_keep; goto *D_800889A8[(u32)(phase)];
jt_c0:
    delay_left = ((S_80091C64_0 *)motion)->unk_96.s - 1;
    ((S_80091C64_0 *)motion)->unk_96.s = delay_left;
    if ((s16) delay_left >= 9) {
        goto done;
    }
    (*(u8 **)((u8 *)entity + 0x2C)) = D_800DD038;
    func_80048A44(entity, D_800DD038[((s32) (D_80083228 + ((S_80091C64_1 *)actor)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    ((S_80091C64_0 *)motion)->unk_98 = (u16) (((S_80091C64_0 *)motion)->unk_98 | 0xC);
    ((S_80091C64_0 *)motion)->unk_9B = (u8) (((S_80091C64_0 *)motion)->unk_9B + 1);
    func_800A56E0(0x701);
    return;
jt_c1:
    if (((S_80091C64_0 *)motion)->unk_96.u == 0) {
        goto tick_hop;
    }
    ((S_80091C64_2 *)position)->unk_00.at00.v = (s32) (((S_80091C64_2 *)position)->unk_00.at00.v + (func_80064584(((S_80091C64_1 *)actor)->unk_2A + 0x400) << 6));
    ((S_80091C64_2 *)position)->unk_04.at00.v = (s32) (((S_80091C64_2 *)position)->unk_04.at00.v + (func_800644B8(((S_80091C64_1 *)actor)->unk_2A + 0x400) << 6));
    ((S_80091C64_0 *)motion)->unk_92 = (s16) ((s32) (0 - func_800644B8((s16) ((S_80091C64_0 *)motion)->unk_96.s << 8)) >> 8);
tick_hop:
    hop_frames_left = ((S_80091C64_0 *)motion)->unk_96.s - 1;
    ((S_80091C64_0 *)motion)->unk_96.s = hop_frames_left;
    if ((hop_frames_left << 0x10) > 0) {
        goto done;
    }
    (*(u8 **)((u8 *)entity + 0x2C)) = D_800DD058;
    func_80048A44(entity, D_800DD058[((s32) (D_80083228 + ((S_80091C64_1 *)actor)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    completed_phase = ((S_80091C64_0 *)motion)->unk_9B;
    ((S_80091C64_0 *)motion)->unk_92 = 0;
    goto advance_phase;
jt_c2:
    if (D_8008346C != 0) {
        goto done;
    }
    (*(u8 **)((u8 *)entity + 0x2C)) = D_800DD038;
    func_80048A44(entity, D_800DD038[((s32) (D_80083228 + ((S_80091C64_1 *)actor)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    completed_phase = ((S_80091C64_0 *)motion)->unk_9B;
    return_duration = 8U;
    ((S_80091C64_0 *)motion)->unk_96.s = return_duration;
advance_phase:
    ((S_80091C64_0 *)motion)->unk_9B = (u8) (completed_phase + 1);
    return;
jt_c3:
    frames_left = (s16) ((S_80091C64_0 *)motion)->unk_96.s;
    if (frames_left == 0) {
        goto tick_return;
    }
    target_x = ((Rec_D_80082E80 *)entity)->unk_24 << 6;
    current_x = ((S_80091C64_2 *)position)->unk_00.at02.v - 0x20;
    ((S_80091C64_2 *)position)->unk_00.at00.v = (s32) (((S_80091C64_2 *)position)->unk_00.at00.v + ((target_x - current_x) << 0x10) / frames_left);
    y_step = ((Rec_D_80082E80 *)entity)->unk_25;
    y_work = ((S_80091C64_2 *)position)->unk_04.at02.v;
    y_step <<= 6;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    y_work -= 0x20;
    y_step = (y_step - y_work) << 0x10;
    y_work = ((S_80091C64_0 *)motion)->unk_96.u;
    y_step /= y_work;
    y_work = ((S_80091C64_2 *)position)->unk_04.at00.v + y_step;
    ((S_80091C64_2 *)position)->unk_04.at00.v = y_work;
    ((S_80091C64_0 *)motion)->unk_92 = (s16) ((s32) (0 - func_800644B8((s16) ((S_80091C64_0 *)motion)->unk_96.s << 8)) >> 8);
tick_return:
    return_frames_left = ((S_80091C64_0 *)motion)->unk_96.s - 1;
    ((S_80091C64_0 *)motion)->unk_96.s = return_frames_left;
    if ((return_frames_left << 0x10) > 0) {
        goto done;
    }
    func_800A2B04(position, ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25);
    ((S_80091C64_0 *)motion)->unk_92 = 0;
    ((S_80091C64_0 *)motion)->unk_9B = (u8) (((S_80091C64_0 *)motion)->unk_9B + 1);
    (*(u8 **)((u8 *)entity + 0x2C)) = D_800DD058;
    func_80048A44(entity, D_800DD058[((s32) (D_80083228 + ((S_80091C64_1 *)actor)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    return;
jt_c4:
    action_tracker = &D_80083460;
    ((S_80091C64_4 *)action_tracker)->unk_0A = (u16) (((S_80091C64_4 *)action_tracker)->unk_0A - 1);
    ((S_80091C64_1 *)actor)->unk_2A = (s16) ((S_80091C64_0 *)motion)->unk_11A;
    if (!(((S_80091C64_1 *)actor)->unk_1C & 0x100000)) {
        goto default_behavior;
    }
    next_behavior = &D_8008EAC8;
    goto restore_behavior;
default_behavior:
    next_behavior = &D_8008ACDC;
restore_behavior:
    ((S_80091C64_0 *)motion)->unk_8C = next_behavior;
    ((S_80091C64_1 *)actor)->unk_14 = (s32) (((S_80091C64_1 *)actor)->unk_14 & 0xFFFDFFFF);
    ((S_80091C64_0 *)motion)->unk_98 = (u16) (((S_80091C64_0 *)motion)->unk_98 & 0xFFF3);
    ((S_80091C64_0 *)motion)->unk_A2 = (u16) (((S_80091C64_0 *)motion)->unk_A2 | 0x10);
done:
    return;
}
