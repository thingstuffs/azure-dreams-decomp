#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800D991C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_800D991C_0;   /* arg0 in func_800D991C */





M2C_UNK func_8003DB94();        /* extern */
s16 func_800A0818();       /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A9A04();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
s32 func_800AD9B4();                  /* extern */
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800D8C64;
extern void *D_800E262C[];

/* Update arcing movement toward a target tile and finish the landing action. */
void func_800D991C(void *motion, void *position, void *sprite, void *actor) {
    M2C_UNK direction_aux;
    void **animations;
    s16 *counters;
    u8 *reference_pos;
    s32 frames_left;
    s16 next_frames;
    s32 target_x;
    s32 velocity_x;
    s32 target_y;
    s32 actor_flags;
    s32 current_x;
    s32 current_y;
    s32 phase;

    phase = ((S_800D991C_0 *)motion)->unk_9B;
    switch (phase) {
        case 0:
            ((S_800D991C_0 *)motion)->unk_98 = (u16) (((S_800D991C_0 *)motion)->unk_98 | 8);
            ((Rec_D_800E3D7C *)position)->unk_14.s32 = 0xFFF00000;
            ((Rec_D_800E3D7C *)actor)->unk_1C.s = (s32) (((Rec_D_800E3D7C *)actor)->unk_1C.s & 0xF7FFFFFF);
            ((S_800D991C_0 *)motion)->unk_A4 = 0;
            ((S_800D991C_0 *)motion)->unk_9B = (u8) (((S_800D991C_0 *)motion)->unk_9B + 1);
            break;
        case 1:
            break;
        case 2:
            goto check_landing;
        default:
            goto tick_timer;
    }
update_motion:
    frames_left = ((S_800D991C_0 *)motion)->unk_96;
    ((S_800D991C_0 *)motion)->unk_90 = (s32) (((S_800D991C_0 *)motion)->unk_90 - ((S_800D991C_0 *)motion)->unk_A4);
    if (frames_left != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        current_x = ((Rec_D_800E3D7C *)position)->unk_00.at02.v - 0x20;
        velocity_x = (s32) ((target_x - current_x) << 0x10) / frames_left;
        current_y = ((Rec_D_800E3D7C *)position)->unk_04.at02.v - 0x20;
        ((Rec_D_800E3D7C *)position)->unk_0C.n = velocity_x;
        target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        ((Rec_D_800E3D7C *)position)->unk_10.at00.v = (s32) ((s32) ((target_y - current_y) << 0x10) / (s16) ((S_800D991C_0 *)motion)->unk_96);
        ((S_800D991C_0 *)motion)->unk_A4 = (s32) (((S_800D991C_0 *)motion)->unk_A4 + ((Rec_D_800E3D7C *)position)->unk_14.s32);
        ((Rec_D_800E3D7C *)position)->unk_14.s32 = (s32) (((Rec_D_800E3D7C *)position)->unk_14.s32 + 0x48000);
    }
    ((S_800D991C_0 *)motion)->unk_90 = (s32) (((S_800D991C_0 *)motion)->unk_90 + ((S_800D991C_0 *)motion)->unk_A4);
    if (((S_800D991C_0 *)motion)->unk_96 < 2) {
        ((S_800D991C_0 *)motion)->unk_90 = 0;
        ((S_800D991C_0 *)motion)->unk_98 = (u16) (((S_800D991C_0 *)motion)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)actor)->unk_1C.s = (s32) (((Rec_D_800E3D7C *)actor)->unk_1C.s | 0x08000000);
        ((S_800D991C_0 *)motion)->unk_9B = (u8) (((S_800D991C_0 *)motion)->unk_9B + 1);
    }
check_landing:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.s & 0x08000000) {
        ((S_800D991C_0 *)motion)->unk_98 = (u16) (((S_800D991C_0 *)motion)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)position)->unk_14.s32 = 0;
        ((Rec_D_800E3D7C *)position)->unk_10.at00.v = 0;
        ((Rec_D_800E3D7C *)position)->unk_0C.n = 0;
        func_800A2B04(position, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        animations = D_800E262C;
        (*(void **)((u8 *)sprite + 0x2C)) = animations;
        func_8003DB94(sprite, *(void **)((u8 *)animations + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.s + 0x100) >> 7) & 0x1C)), 0);
        ((S_800D991C_0 *)motion)->unk_9B = (u8) (((S_800D991C_0 *)motion)->unk_9B + 1);
    }
tick_timer:
    next_frames = (u16) ((S_800D991C_0 *)motion)->unk_96 - 1;
    ((S_800D991C_0 *)motion)->unk_96 = next_frames;
    if ((next_frames << 0x10) <= 0) {
        ((Rec_D_800E3D7C *)position)->unk_14.s32 = 0;
        ((Rec_D_800E3D7C *)position)->unk_10.at00.v = 0;
        ((Rec_D_800E3D7C *)position)->unk_0C.n = 0;
        func_800A2B04(position, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        counters = (s16 *)&D_80083460;
        if (counters[4] != 0) {
            counters[4] = (s16) ((u16) counters[4] - 1);
        }
        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.s;
        if (actor_flags & 0x2000) {
            goto check_next_action;
        }
        if (actor_flags & 0x410) {
            goto check_next_action;
        }
        if (!(actor_flags & 0x20000)) {
            goto check_next_action;
        }
        reference_pos = (u8 *)&D_80082E80;
        ((Rec_D_800E3D7C *)actor)->unk_2A.s = func_800A0818(((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25, reference_pos[0x24], reference_pos[0x25], &direction_aux);
check_next_action:
        if ((func_800AD9B4(sprite, actor) << 0x10) > 0) {
            ((S_800D991C_0 *)motion)->unk_8C = &D_800D8C64;
            func_800A9A04(actor);
        }
    }
}
