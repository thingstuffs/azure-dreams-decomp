#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174910(void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_80170850[];
extern s32 D_801710EC;
extern u8 D_80175E58[];
extern u8 D_80175E60[];
extern u8 D_80175E68[];


typedef struct S_801728A8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_801728A8_0;   /* arg0 in func_801728A8 */


typedef struct S_801728A8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801728A8_2;   /* call_a0 in func_801728A8 */


typedef struct S_801728A8_4 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
} S_801728A8_4;   /* arg3 in func_801728A8 */

/* Updates movement, height, and animation through the action states. */
void func_801728A8(void *action, void *motion, void *sprite, void *actor)
{
    static void *const state_labels[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };
    u8 state;

    state = ((S_801728A8_0 *)action)->unk_9B.n;
    if ((u32)state >= 5) {
        return;
    }
    (void)state_labels;
    goto *D_80170850[state];

L0:
    {
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_801728A8_0 *)action)->unk_9B.n = 4;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, sprite, ((S_801728A8_2 *)actor)->unk_2A, 1);
            return;
        }
    }

L1:
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 -=
        *(s16 *)((u8 *)&D_8006CCD8 +
                 (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v -=
        *(s16 *)((u8 *)&D_8006CCE8 +
                 (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
    ((S_801728A8_0 *)action)->unk_A0.at00.v += 0x60000;
    if (((S_801728A8_0 *)action)->unk_A0.at02.v >= 0x31) {
        ((S_801728A8_0 *)action)->unk_A0.at02.v = 0x30;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        return;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    if (((S_801728A8_0 *)action)->unk_A0.at02.v < 0x30) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175E58;
    func_80047784(sprite,
        D_80175E58[((D_80083228 + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    func_80174910((u8 *)action - 0x20, (u8 *)actor + 0x2A);
    state = ((S_801728A8_0 *)action)->unk_9B.n;
    ((S_801728A8_0 *)action)->unk_96.s = 0;
    goto increment_state;

L2:
    {
        s16 *directions_x;
        s16 *directions_y;
        s16 *direction_x_ptr;
        s16 *direction_y_ptr;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 arc;
        register s32 direction_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 direction_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 step_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register s32 step_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s16 timer;

        directions_x = (s16 *)&D_8006CCD8;
        directions_y = (s16 *)&D_8006CCE8;
        direction_offset = ((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE;
        direction_x_ptr = (s16 *)(direction_offset + (u8 *)directions_x);
        direction_y_ptr = (s16 *)(direction_offset + (u8 *)directions_y);
        do {
            arc = *direction_x_ptr;
        } while (0);
        direction_y = *direction_y_ptr;
        step_x = arc << 16;
        step_y = direction_y << 16;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 += step_x;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v += step_y;
        arc = -func_800644B8(((S_801728A8_0 *)action)->unk_96.s * 170);
        ((S_801728A8_0 *)action)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
        timer = ((S_801728A8_0 *)action)->unk_96.u + 1;
        ((S_801728A8_0 *)action)->unk_96.u = timer;
        if (timer < 9) {
            return;
        }
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175E60;
    func_80047784(sprite,
        D_80175E60[((D_80083228 + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x808);
    state = ((S_801728A8_0 *)action)->unk_9B.n;
increment_state:
    ((S_801728A8_0 *)action)->unk_9B.n = state + 1;
    return;

L3:
    {
        s16 *directions_x;
        s16 *directions_y;
        s16 *direction_x_ptr;
        s16 *direction_y_ptr;
        s32 arc;
        register s32 direction_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 direction_offset;
        register s32 step_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register s32 step_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s16 timer;
        s32 velocity_x;
        s32 velocity_y;

        if (((S_801728A8_0 *)action)->unk_96.s == 10) {
            func_8009C12C(actor, sprite, ((S_801728A8_4 *)actor)->unk_2A.s, 1);
        }
        directions_x = (s16 *)&D_8006CCD8;
        directions_y = (s16 *)&D_8006CCE8;
        direction_offset = ((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE;
        direction_x_ptr = (s16 *)(direction_offset + (u8 *)directions_x);
        direction_y_ptr = (s16 *)(direction_offset + (u8 *)directions_y);
        ASM_KEEP(direction_x_ptr);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        direction_x = *direction_x_ptr;
        arc = *direction_y_ptr;
        step_x = direction_x << 16;
        step_y = arc << 16;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 += step_x;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v += step_y;
        arc = -func_800644B8(((S_801728A8_0 *)action)->unk_96.s * 170);
        ((S_801728A8_0 *)action)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
        timer = ((S_801728A8_0 *)action)->unk_96.u + 1;
        ((S_801728A8_0 *)action)->unk_96.u = timer;
        if (timer < 13) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175E68;
        func_80047784(sprite,
            D_80175E68[((D_80083228 + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
            0);

        velocity_x = -*(s16 *)((u8 *)directions_x +
            (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
        velocity_x += velocity_x >> 2;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = velocity_x;

        velocity_y = -*(s16 *)((u8 *)directions_y +
            (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
        velocity_y += velocity_y >> 2;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = velocity_y;
        ((S_801728A8_0 *)action)->unk_A8 = ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 / 24;
        ((S_801728A8_0 *)action)->unk_AC = ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v / 24;
    }
    ((S_801728A8_0 *)action)->unk_96.s = 12;
    ((S_801728A8_0 *)action)->unk_9B.n++;
    return;

L4:
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 -= ((S_801728A8_0 *)action)->unk_A8;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v -= ((S_801728A8_0 *)action)->unk_AC;
    if (((S_801728A8_0 *)action)->unk_A0.at02.v > 0) {
        ((S_801728A8_0 *)action)->unk_A0.at02u.v -= 0x10;
    } else {
        ((S_801728A8_0 *)action)->unk_A0.at02.v = 0;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 0x100);
    ((S_801728A8_0 *)action)->unk_8C = &D_801710EC;
    D_8008346C = 0;
    (*(u16 *)((u8 *)actor + (0x46))) &= 0x7FFF;
    ((S_801728A8_0 *)action)->unk_98 &= 0xFFF7;
    func_800A4ACC(actor);
}
