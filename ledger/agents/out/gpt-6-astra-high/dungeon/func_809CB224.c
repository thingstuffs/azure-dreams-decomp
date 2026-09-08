#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80172A24_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172A24_0;   /* arg0 in func_80172A24 */

typedef struct S_80172A24_1 {
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
} S_80172A24_1;   /* arg3 in func_80172A24 */

typedef struct S_80172A24_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A24_2_pre;   /* the 0x14 bytes before obj in func_80172A24, addressed as obj[-1] */

typedef struct S_80172A24_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A24_3;   /* rec in func_80172A24 */




typedef struct S_80172A24_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A24_7;   /* block in func_80172A24 */



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
extern u8 D_80173C7C[];

/* Advances an actor's motion action and clears its state when the action finishes. */
void func_80172A24(void *action_state, void *transform, void *sprite, void *actor)
{
    u16 position[4];
    u8 *motion;
    register s32 use_player_target ASM_REG("$21");   /* MATCH pin: keeps a constant in a register as retail does */
    void *target;
    register void *target_record ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 target_x;
    s32 target_y;
    s32 delay;
    u8 *action_status;

    use_player_target = 0;
    switch (((S_80172A24_0 *)action_state)->unk_9B) {
    case 0:
        if (((S_80172A24_1 *)actor)->unk_1C & 0x2000) {
            static void *const dispatch_labels[] = {&&player_motion_3, &&player_motion_2, &&player_motion_1, &&no_motion};
            extern void *const D_80170838[];
            u32 motion_index = (u32)((((S_80172A24_1 *)actor)->unk_46 & 0x3FFF) - 1);

            if (motion_index >= 7) {
                goto no_motion;
            }
            (void)dispatch_labels;
            goto *D_80170838[motion_index];
        player_motion_3:
            use_player_target = 1;
            goto motion_3;
        player_motion_2:
            use_player_target = 1;
            goto motion_2;
        player_motion_1:
            use_player_target = 1;
            goto motion_1;
        }

        switch (((S_80172A24_1 *)actor)->unk_46 & 0x3FFF) {
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
            ((S_80172A24_0 *)action_state)->unk_98 &= 0xFF7F;
            ASM_KEEP(motion);   /* MATCH pin: retail delay-slot fill depends on it */
            {
                s32 player_target = use_player_target;

                ASM_KEEP(player_target);   /* MATCH pin: retail delay-slot fill depends on it */
                if (player_target != 0) {
                    target = D_800814A8;
                    ((S_80172A24_1 *)actor)->unk_60 = target;
                    goto have_target;
                }
            }
            if (((MotionEntry *)D_8006DE24)[*motion].kind == 2) {
                target = ((S_80172A24_1 *)actor)->unk_60;
                if (target == 0) {
                    goto advance_motion;
                }
            have_target:
                target_record = ((S_80172A24_2_pre *)target)[-1].unk_00;
                ((S_80172A24_1 *)actor)->unk_72.s = ((S_80172A24_3 *)target_record)->unk_24;
                ((S_80172A24_1 *)actor)->unk_73.s = ((S_80172A24_3 *)target_record)->unk_25;
                goto advance_motion;
            }
            ((S_80172A24_1 *)actor)->unk_60 =
                func_800A05A4(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                              ((S_80172A24_1 *)actor)->unk_2A, 0x10);
            ASM_KEEP(actor);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            target_x = ((S_80172A24_1 *)actor)->unk_72.u;
            target_y = ((S_80172A24_1 *)actor)->unk_73.u;
            if (target_x < 0) {
                target_x = -target_x;
            }
            if (target_y < 0) {
                target_y = -target_y;
            }
            ((S_80172A24_1 *)actor)->unk_72.s = target_x;
            ((S_80172A24_1 *)actor)->unk_73.s = target_y;
        advance_motion:
            position[0] = ((Rec_D_800E3D7C *)transform)->unk_00.at02_u16.v;
            position[1] = ((Rec_D_800E3D7C *)transform)->unk_04.at02_u16.v;
            position[2] = ((Rec_D_800E3D7C *)transform)->unk_08.at02_u16.v;
            if (func_800A94A0(actor, motion, use_player_target, (u8 *)action_state + 0x98) == 0) {
                return;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(position, (*motion - 1) % 3);
            ((S_80172A24_0 *)action_state)->unk_9B = ((S_80172A24_0 *)action_state)->unk_9B + 1;
            return;
        }

        ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        D_8008346C = 0;
        ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        ((S_80172A24_1 *)actor)->unk_6D.s = ((S_80172A24_1 *)actor)->unk_6D.s - 1;
        ((S_80172A24_0 *)action_state)->unk_8C = D_80170E54;
        ((S_80172A24_1 *)actor)->unk_73.s = 0;
        ((S_80172A24_1 *)actor)->unk_72.s = 0;
        ((S_80172A24_1 *)actor)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172A24_0 *)action_state)->unk_9B = ((S_80172A24_0 *)action_state)->unk_9B + 1;
        /* fallthrough */
    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 4 && (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_80172A24_0 *)action_state)->unk_96 = 0x3;
            ((S_80172A24_0 *)action_state)->unk_98 |= 0x80;
        }
        delay = ((S_80172A24_0 *)action_state)->unk_96 - 1;
        ((S_80172A24_0 *)action_state)->unk_96 = delay;
        if ((s16)delay <= 0) {
            ((S_80172A24_0 *)action_state)->unk_96 = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }
        ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
        func_800A2B04(transform, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        {
            u8 *direction_table = D_80173C7C;

            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                func_80047784(sprite,
                    direction_table[((D_80083228 + ((S_80172A24_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_status = (u8 *)&D_80083460;
        if (((S_80172A24_7 *)action_status)->unk_0C != 0) {
            return;
        }
        ((S_80172A24_7 *)action_status)->unk_0A = ((S_80172A24_7 *)action_status)->unk_0A - 1;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172A24_0 *)action_state)->unk_8C = D_80170E54;
        func_800A4ACC(actor);
        if (((S_80172A24_1 *)actor)->unk_6D.u > 0) {
            ((S_80172A24_1 *)actor)->unk_6D.s = ((S_80172A24_1 *)actor)->unk_6D.s - 1;
        }
        ((S_80172A24_1 *)actor)->unk_73.s = 0;
        ((S_80172A24_1 *)actor)->unk_72.s = 0;
        ((S_80172A24_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}
