#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80172F5C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172F5C_0;   /* arg0 in func_80172F5C */

typedef struct S_80172F5C_1 {
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
} S_80172F5C_1;   /* arg3 in func_80172F5C */

typedef struct S_80172F5C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172F5C_2_pre;   /* the 0x14 bytes before obj in func_80172F5C, addressed as obj[-1] */

typedef struct S_80172F5C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172F5C_3;   /* rec in func_80172F5C */

typedef struct S_80172F5C_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172F5C_4;   /* arg2 in func_80172F5C */



typedef struct S_80172F5C_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172F5C_7;   /* block in func_80172F5C */



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

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170E94[];
extern u8 D_80174A7C[];

/* Advances an actor motion, waits for completion, and resets its action state. */
void func_80172F5C(void *state, void *transform, void *sprite, void *actor)
{
    u16 saved_pos[3];
    register u8 *motion ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 use_player;
    void *target;
    s32 target_x;
    s32 target_y;
    s32 wait_ticks;
    u8 *action_state;

    use_player = 0;
    switch (((S_80172F5C_0 *)state)->unk_9B) {
    case 0:
        if (((S_80172F5C_1 *)actor)->unk_1C & 0x2000) {
            static void *const dispatch_labels[] = {&&sw_c, &&sw_b, &&sw_a, &&sel_none};
            extern void *const D_80170878[];
            u32 action_index = (u32)((((S_80172F5C_1 *)actor)->unk_46 & 0x3FFF) - 1);

            if (action_index >= 7) {
                goto sel_none;
            }
            (void)dispatch_labels;
            goto *D_80170878[action_index];
        sw_c:
            use_player = 1;
            goto kind_c;
        sw_b:
            use_player = 1;
            goto kind_b;
        sw_a:
            use_player = 1;
            goto kind_a;
        }

        switch (((S_80172F5C_1 *)actor)->unk_46 & 0x3FFF) {
        case 3:
        kind_c:
            motion = (u8 *)actor + 0xE;
            break;
        case 2:
        kind_b:
            motion = (u8 *)actor + 0xB;
            break;
        case 1:
        kind_a:
            motion = (u8 *)actor + 8;
            break;
        default:
        sel_none:
            motion = (u8 *)0;
            break;
        }

        if (*motion != 0) {
            ((S_80172F5C_0 *)state)->unk_98 &= 0xFF7F;
            {
                s32 is_player_target = use_player;

                ASM_KEEP(is_player_target);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                if (is_player_target != 0) {
                    target = D_800814A8;
                    ((S_80172F5C_1 *)actor)->unk_60 = target;
                    goto have_obj;
                }
            }
            if (((MotionEntry *)D_8006DE24)[*motion].kind == 2) {
                target = ((S_80172F5C_1 *)actor)->unk_60;
                if (target == 0) {
                    goto do_step;
                }
            have_obj:
                action_state = ((S_80172F5C_2_pre *)target)[-1].unk_00;
                ((S_80172F5C_1 *)actor)->unk_72.s = ((S_80172F5C_3 *)action_state)->unk_24;
                ((S_80172F5C_1 *)actor)->unk_73.s = ((S_80172F5C_3 *)action_state)->unk_25;
                goto do_step;
            }
            ((S_80172F5C_1 *)actor)->unk_60 =
                func_800A05A4(actor, ((S_80172F5C_4 *)sprite)->unk_24, ((S_80172F5C_4 *)sprite)->unk_25,
                              ((S_80172F5C_1 *)actor)->unk_2A, 0x10);
            ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            target_x = ((S_80172F5C_1 *)actor)->unk_72.u;
            target_y = ((S_80172F5C_1 *)actor)->unk_73.u;
            if (target_x < 0) {
                target_x = -target_x;
            }
            if (target_y < 0) {
                target_y = -target_y;
            }
            ((S_80172F5C_1 *)actor)->unk_72.s = target_x;
            ((S_80172F5C_1 *)actor)->unk_73.s = target_y;
        do_step:
            saved_pos[0] = ((Rec_D_800E3D7C *)transform)->unk_00.at02_u16.v;
            saved_pos[1] = ((Rec_D_800E3D7C *)transform)->unk_04.at02_u16.v;
            saved_pos[2] = ((Rec_D_800E3D7C *)transform)->unk_08.at02_u16.v;
            if (func_800A94A0(actor, motion, use_player, (u8 *)state + 0x98) == 0) {
                return;
            }
            ((S_80172F5C_4 *)sprite)->unk_14 &= 0xF7FF;
            func_800A56E0(0x703);
            ((S_80172F5C_0 *)state)->unk_9B = ((S_80172F5C_0 *)state)->unk_9B + 1;
            return;
        }

        ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
        func_800A2B04(transform, ((S_80172F5C_4 *)sprite)->unk_24, ((S_80172F5C_4 *)sprite)->unk_25);
        D_8008346C = 0;
        ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        ((S_80172F5C_1 *)actor)->unk_6D.s = ((S_80172F5C_1 *)actor)->unk_6D.s - 1;
        ((S_80172F5C_0 *)state)->unk_8C = D_80170E94;
        ((S_80172F5C_1 *)actor)->unk_73.s = 0;
        ((S_80172F5C_1 *)actor)->unk_72.s = 0;
        ((S_80172F5C_1 *)actor)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_80172F5C_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_80172F5C_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172F5C_0 *)state)->unk_9B = ((S_80172F5C_0 *)state)->unk_9B + 1;
    case 2:
        if ((((S_80172F5C_4 *)sprite)->unk_04 == 6 && (((S_80172F5C_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_80172F5C_4 *)sprite)->unk_14 & 0xE000)) {
            ((S_80172F5C_4 *)sprite)->unk_14 |= 0x800;
            ((S_80172F5C_0 *)state)->unk_98 |= 0x80;
        }
        if ((((S_80172F5C_4 *)sprite)->unk_04 == 7 && (((S_80172F5C_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_80172F5C_4 *)sprite)->unk_14 & 0x8000)) {
            ((S_80172F5C_4 *)sprite)->unk_14 |= 0x800;
            ((S_80172F5C_0 *)state)->unk_96 = 8;
        }
        wait_ticks = ((S_80172F5C_0 *)state)->unk_96 - 1;
        ((S_80172F5C_0 *)state)->unk_96 = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            ((S_80172F5C_0 *)state)->unk_96 = 0;
            ((S_80172F5C_4 *)sprite)->unk_14 &= 0xF7FF;
        }
        if ((((S_80172F5C_4 *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }
        ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
        func_800A2B04(transform, ((S_80172F5C_4 *)sprite)->unk_24, ((S_80172F5C_4 *)sprite)->unk_25);
        {
            u8 *direction_frames = D_80174A7C;

            if (((S_80172F5C_4 *)sprite)->unk_2C != direction_frames) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_frames;
                func_80047784(sprite,
                    direction_frames[((D_80083228 + ((S_80172F5C_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_state = (u8 *)&D_80083460;
        if (((S_80172F5C_7 *)action_state)->unk_0C != 0) {
            return;
        }
        ((S_80172F5C_7 *)action_state)->unk_0A = ((S_80172F5C_7 *)action_state)->unk_0A - 1;
        ((S_80172F5C_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172F5C_0 *)state)->unk_8C = D_80170E94;
        func_800A4ACC(actor);
        if (((S_80172F5C_1 *)actor)->unk_6D.u > 0) {
            ((S_80172F5C_1 *)actor)->unk_6D.s = ((S_80172F5C_1 *)actor)->unk_6D.s - 1;
        }
        ((S_80172F5C_1 *)actor)->unk_73.s = 0;
        ((S_80172F5C_1 *)actor)->unk_72.s = 0;
        ((S_80172F5C_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}
