#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80170838[];
void func_80047784();
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
M2C_UNK func_800AD594();
extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80170E9C;
extern u8 D_80174F30;
extern u8 D_80174F38;
extern u8 D_80174F40;


typedef struct S_80172524_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
} S_80172524_0;   /* arg0 in func_80172524 */

/* Advance the action phases, updating movement and directional animation. */
void func_80172524(void *action, void *motion, void *sprite, void *actor) {
    static void *const phase_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    u16 move_ticks;
    u16 settle_ticks;
    u8 phase;
    register u8 *animations ASM_REG("$5"); /* Pin preserves the shared animation argument register. */

    phase = ((S_80172524_0 *)action)->unk_9B.n;
    if (phase >= 6U) {
        goto done;
    }
    (void)phase_labels; goto *D_80170838[(u32)(phase)];
jt_c0:
    ((S_80172524_0 *)action)->unk_98 = (u16) (((S_80172524_0 *)action)->unk_98 | 8);
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        goto start_motion;
    }
    ((S_80172524_0 *)action)->unk_9B.n = 5U;
    ((S_80172524_0 *)action)->unk_96.u = 0U;
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x6000);
    func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    return;
start_motion:
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (s32) (*(s16 *)(&D_8006CCD8 + (((u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE)) << 0x14);
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (s32) (*(s16 *)(&D_8006CCE8 + (((u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE)) << 0x14);
    goto advance_phase;
jt_c1:
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (s32) ((s32) ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 >> 1);
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (s32) ((s32) ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v >> 1);
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    animations = &D_80174F30;
    goto set_animation;
jt_c2:
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (s32) ((s32) ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 >> 1);
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (s32) ((s32) ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v >> 1);
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    func_800A56E0(0x808);
    animations = &D_80174F38;
    goto set_animation;
jt_c3:
    if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 != 2) {
        goto check_animation;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) {
        goto check_animation;
    }
    func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    {
        register u16 move_duration ASM_REG("$3") = 6;   /* Pin preserves register allocation. */
        phase = ((S_80172524_0 *)action)->unk_9B.v;
        ((S_80172524_0 *)action)->unk_96.u = move_duration;
    }
    goto store_next_phase;
check_animation:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    (*(M2C_UNK **)((u8 *)sprite + (0x2C))) = &D_80174F40;
    func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_80174F40), 0);
    func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    ((S_80172524_0 *)action)->unk_9B.n = 5U;
    ((S_80172524_0 *)action)->unk_96.u = 0;
    return;
jt_c4:
    move_ticks = ((S_80172524_0 *)action)->unk_96.u - 1;
    ((S_80172524_0 *)action)->unk_96.u = move_ticks;
    if ((s16) move_ticks <= 0) {
        goto stop_motion;
    }
    {
        s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        s32 current_coord = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_coord - current_coord) << 0x10) / (s16) move_ticks;
    }
    {
        s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        s32 current_coord = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = ((target_coord - current_coord) << 0x10) / ((S_80172524_0 *)action)->unk_96.s;
    }
    goto check_move_done;
stop_motion:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
check_move_done:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    animations = &D_80174F40;
set_animation:
    (*(M2C_UNK **)((u8 *)sprite + (0x2C))) = (M2C_UNK *)animations;
    func_80047784(sprite, *(u8 *)((((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)animations), 0);
advance_phase:
    phase = ((S_80172524_0 *)action)->unk_9B.n;
store_next_phase:
    ((S_80172524_0 *)action)->unk_9B.n = phase + 1;
    return;
jt_c5:
    settle_ticks = ((S_80172524_0 *)action)->unk_96.u - 1;
    ((S_80172524_0 *)action)->unk_96.u = settle_ticks;
    if ((s16) settle_ticks <= 0) {
        goto stop_settling;
    }
    {
        s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        s32 current_coord = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_coord - current_coord) << 0x10) / (s16) settle_ticks;
    }
    {
        s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        s32 current_coord = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = ((target_coord - current_coord) << 0x10) / ((S_80172524_0 *)action)->unk_96.s;
    }
    goto check_settle_done;
stop_settling:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
check_settle_done:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    ((S_80172524_0 *)action)->unk_98 = (u16) (((S_80172524_0 *)action)->unk_98 & 0xFFF7);
    func_800AD594(actor, 0x100);
    ((S_80172524_0 *)action)->unk_8C = &D_80170E9C;
    D_8008346C = 0;
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = (u16) ((*(u16 *)((u8 *)actor + (0x46))) & 0x7FFF);
    func_800A4ACC(actor);
done:
    return;
}
