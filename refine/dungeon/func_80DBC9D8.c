#include "common.h"
#include "records/Rec_D_800814A8.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801741D8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801741D8_0;   /* arg0 in func_801741D8 */

typedef struct S_801741D8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801741D8_1;   /* arg2 in func_801741D8 */

typedef struct S_801741D8_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801741D8_2;   /* arg3 in func_801741D8 */

typedef struct S_801741D8_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801741D8_3;   /* counter in func_801741D8 */

typedef struct S_801741D8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_801741D8_4;   /* global_state in func_801741D8 */





extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174890(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171E20[];
extern u8 D_80175404[];
extern u8 D_8017540C[];

/* Advance the actor action state and update its directional animation. */
void func_801741D8(void *controller_in, void *context_in, void *sprite_in, void *actor_in)
{
    void *controller = controller_in;
    register void *context ASM_REG("$19") = context_in;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *sprite ASM_REG("$17") = sprite_in;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *actor;
    u8 state;
    u8 *global_state;
    void *check_target;
    void *active_actor;
    s8 tile;

    state = ((S_801741D8_0 *)controller)->unk_9B;
    actor = actor_in;
    switch (state) {
    case 0:
        if (((S_801741D8_1 *)sprite)->unk_14 & 0xE000) {
            u8 *counter;

            (*(void * *)((u8 *)sprite + 0x2C)) = D_80175404;
            func_80047784(sprite,
                D_80175404[((D_80083228 + ((S_801741D8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            counter = (u8 *)&D_80083460;
            ((S_801741D8_3 *)counter)->unk_0A--;
            goto increment_state;
        }
        break;

    case 1:
        if ((s16)func_80042900(actor, 1) == 0) {
            goto set_effect;
        }

        global_state = (u8 *)&D_80083460;
        if (((S_801741D8_4 *)global_state)->unk_02 & 0x1000) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_64 != 0) {
            if (func_800AA6B4(controller, context, sprite, 0) != 0) {
                break;
            }
        }

        if (((S_801741D8_2 *)actor)->unk_25 == 0) {
            if (((S_801741D8_4 *)global_state)->unk_02 & 0x2008) {
                break;
            }
            func_800AA79C(controller, context, sprite, actor);
            break;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_1C & 0x100) {
            func_800AA258(controller, context, sprite, actor);
            break;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_1C & 0x80000) {
            func_800AA888(controller, context, sprite, actor);
            func_80174890(controller, context, sprite, actor);
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_6D == 0) {
            break;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            if ((s16)func_8009A180(
                    actor, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                break;
            }
        }

        func_800A9A0C(actor);
        func_800A9A04(actor);
        if ((s16)func_80042900(actor, 1) != 0) {
            check_target = D_80082E80;
            tile = ((S_801741D8_1 *)sprite)->unk_26;
            if (tile != ((Rec_D_80082E80 *)D_80082E80)->unk_26.as_s8 || tile < 0) {
                s16 distance;

                distance = func_8009FD40(D_80082E80, sprite);
                active_actor = actor;
                if (distance >= 2) {
                    goto final_call;
                }
                check_target = active_actor;
            }
            if ((func_800A6D30(check_target) & 7) == 0) {
                func_80042B68(actor, 1);
            }
        }

        active_actor = actor;
final_call:
        if ((s16)func_80042900(active_actor, 1) != 0) {
            break;
        }

set_effect:
        (*(void * *)((u8 *)sprite + 0x2C)) = D_8017540C;
        func_80047784(sprite,
            D_8017540C[((D_80083228 + ((S_801741D8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((S_801741D8_1 *)sprite)->unk_14 & 0x8000) {
            goto set_owner;
        } else {
            register u8 *counter ASM_REG("$2") = (u8 *)&D_80083460;   /* MATCH pin: keeps a constant in a register as retail does */
            ((S_801741D8_3 *)counter)->unk_0A++;
        }

increment_state:
        ((S_801741D8_0 *)controller)->unk_9B++;
        break;

    case 2:
        if (((S_801741D8_1 *)sprite)->unk_14 & 0xE000) {
            register u8 *counter ASM_REG("$2") = (u8 *)&D_80083460;   /* MATCH pin: keeps a constant in a register as retail does */
            ((S_801741D8_3 *)counter)->unk_0A--;
set_owner:
            ((S_801741D8_0 *)controller)->unk_8C = D_80171E20;
        }
        break;

    default:
        break;
    }
    return;
}

/* MECHANISM: Keep the s2/s3/s1 argument homes but remove their entry ASM_KEEP fences;
   sched2 then emits the 0x28-frame tail saves as s0,ra,s4 and delays a3->s0.
   A named s16 distance plus two-edge $a0 active_actor makes word 167 target the final call. */
