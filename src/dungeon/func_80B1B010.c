#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80172810_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172810_0;   /* arg0 in func_80172810 */

typedef struct S_80172810_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172810_1;   /* arg3 in func_80172810 */

typedef struct S_80172810_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172810_2_pre;   /* the 0x14 bytes before obj in func_80172810, addressed as obj[-1] */

typedef struct S_80172810_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172810_3;   /* rec in func_80172810 */

typedef struct S_80172810_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172810_4;   /* arg2 in func_80172810 */



typedef struct S_80172810_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172810_7;   /* block in func_80172810 */



typedef struct {
    u8 pad0[0x12];
    u8 kind;
    u8 pad13;
} MotionEntry;

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800DA840(void *, s16);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170E54[];
extern u8 D_801739C0[];

/* Advances an actor motion through selection, playback, and completion cleanup. */
void func_80172810(void *action_state, void *position, void *sprite, void *actor)
{
    u16 saved_position[4];
    u8 *motion;
    register s32 use_player ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *target;
    s32 offset_x;
    s32 offset_y;
    s32 wait_ticks;
    u8 *action_globals;

    use_player = 0;
    switch (((S_80172810_0 *)action_state)->unk_9B) {
    case 0:
        if (((S_80172810_1 *)actor)->unk_1C & 0x2000) {
            static void *const dispatch_labels[] = {&&player_motion_3, &&player_motion_2, &&player_motion_1, &&no_motion};
            extern void *const D_80170838[];
            u32 action_index = (u32)((((S_80172810_1 *)actor)->unk_46 & 0x3FFF) - 1);

            if (action_index >= 7) {
                goto no_motion;
            }
            (void)dispatch_labels;
            goto *D_80170838[action_index];
        player_motion_3:
            use_player = 1;
            goto motion_3;
        player_motion_2:
            use_player = 1;
            goto motion_2;
        player_motion_1:
            use_player = 1;
            goto motion_1;
        }

        switch (((S_80172810_1 *)actor)->unk_46 & 0x3FFF) {
        case 3:
        motion_3:
            motion = (u8 *)actor + 0xE;
            break;
        case 2:
        motion_2:
            motion = (u8 *)actor + 0xB;
            break;
        case 1:
        motion_1:
            motion = (u8 *)actor + 8;
            break;
        default:
        no_motion:
            motion = (u8 *)0;
            break;
        }

        if (*motion != 0) {
            ((S_80172810_0 *)action_state)->unk_98 &= 0xFF7F;
            ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            {
                s32 player_target = use_player;

                ASM_KEEP(player_target);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                if (player_target != 0) {
                    target = D_800814A8;
                    ((S_80172810_1 *)actor)->unk_60 = target;
                    goto have_target;
                }
            }
            if (((MotionEntry *)D_8006DE24)[*motion].kind == 2) {
                target = ((S_80172810_1 *)actor)->unk_60;
                if (target == 0) {
                    goto apply_motion;
                }
            have_target:
                offset_y = ((S_80172810_2_pre *)target)[-1].unk_00;
                ((S_80172810_1 *)actor)->unk_72.s = ((S_80172810_3 *)offset_y)->unk_24;
                ((S_80172810_1 *)actor)->unk_73.s = ((S_80172810_3 *)offset_y)->unk_25;
                goto apply_motion;
            }
            ((S_80172810_1 *)actor)->unk_60 =
                func_800A05A4(actor, ((S_80172810_4 *)sprite)->unk_24, ((S_80172810_4 *)sprite)->unk_25,
                              ((S_80172810_1 *)actor)->unk_2A, 0x10);
            ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            offset_x = ((S_80172810_1 *)actor)->unk_72.u;
            offset_y = ((S_80172810_1 *)actor)->unk_73.u;
            if (offset_x < 0) {
                offset_x = -offset_x;
            }
            if (offset_y < 0) {
                offset_y = -offset_y;
            }
            ((S_80172810_1 *)actor)->unk_72.s = offset_x;
            ((S_80172810_1 *)actor)->unk_73.s = offset_y;
        apply_motion:
            saved_position[0] = ((Rec_D_800E3D7C *)position)->unk_00.at02_u16.v;
            saved_position[1] = ((Rec_D_800E3D7C *)position)->unk_04.at02_u16.v;
            saved_position[2] = ((Rec_D_800E3D7C *)position)->unk_08.at02_u16.v;
            if (func_800A94A0(actor, motion, use_player, (u8 *)action_state + 0x98) == 0) {
                return;
            }
            ((S_80172810_4 *)sprite)->unk_14 &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(saved_position, (*motion - 1) % 3);
            ((S_80172810_0 *)action_state)->unk_9B = ((S_80172810_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((Rec_D_800E3D7C *)position)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)position)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)position)->unk_0C.as_s32 = 0;
        func_800A2B04(position, ((S_80172810_4 *)sprite)->unk_24, ((S_80172810_4 *)sprite)->unk_25);
        D_8008346C = 0;
        ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        ((S_80172810_1 *)actor)->unk_6D.s = ((S_80172810_1 *)actor)->unk_6D.s - 1;
        ((S_80172810_0 *)action_state)->unk_8C = D_80170E54;
        ((S_80172810_1 *)actor)->unk_73.s = 0;
        ((S_80172810_1 *)actor)->unk_72.s = 0;
        ((S_80172810_1 *)actor)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_80172810_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_80172810_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172810_0 *)action_state)->unk_9B = ((S_80172810_0 *)action_state)->unk_9B + 1;
        /* fallthrough */
    case 2:
        if ((((S_80172810_4 *)sprite)->unk_04 == 14 && (((S_80172810_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_80172810_4 *)sprite)->unk_14 & 0xE000)) {
            ((S_80172810_4 *)sprite)->unk_14 |= 0x800;
            ((S_80172810_0 *)action_state)->unk_96 = 0x3;
            ((S_80172810_0 *)action_state)->unk_98 |= 0x80;
        }
        wait_ticks = ((S_80172810_0 *)action_state)->unk_96 - 1;
        ((S_80172810_0 *)action_state)->unk_96 = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            ((S_80172810_0 *)action_state)->unk_96 = 0;
            ((S_80172810_4 *)sprite)->unk_14 &= 0xF7FF;
        }
        if ((((S_80172810_4 *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }
        ((Rec_D_800E3D7C *)position)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)position)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)position)->unk_0C.as_s32 = 0;
        func_800A2B04(position, ((S_80172810_4 *)sprite)->unk_24, ((S_80172810_4 *)sprite)->unk_25);
        {
            u8 *direction_frames = D_801739C0;

            if (((S_80172810_4 *)sprite)->unk_2C != direction_frames) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_frames;
                func_80047784(sprite,
                    direction_frames[((D_80083228 + ((S_80172810_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_globals = (u8 *)&D_80083460;
        if (((S_80172810_7 *)action_globals)->unk_0C != 0) {
            return;
        }
        ((S_80172810_7 *)action_globals)->unk_0A = ((S_80172810_7 *)action_globals)->unk_0A - 1;
        ((S_80172810_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172810_0 *)action_state)->unk_8C = D_80170E54;
        func_800A4ACC(actor);
        if (((S_80172810_1 *)actor)->unk_6D.u > 0) {
            ((S_80172810_1 *)actor)->unk_6D.s = ((S_80172810_1 *)actor)->unk_6D.s - 1;
        }
        ((S_80172810_1 *)actor)->unk_73.s = 0;
        ((S_80172810_1 *)actor)->unk_72.s = 0;
        ((S_80172810_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}
