#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_800DA014_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_800DA014_0;   /* in_arg0 in func_800DA014 */



typedef struct S_800DA014_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_800DA014_3;   /* system_base in func_800DA014 */


typedef struct S_800DA014_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_800DA014_5;   /* origin in func_800DA014 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_8003DB94(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_800DA660(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800D8C64[];
extern u8 D_800E262C[];

/* Advances the actor action state and updates its directional animation. */
void func_800DA014(void *controller, void *action_context, void *sprite, void *actor)
{
    s32 state;

    state = ((S_800DA014_0 *)controller)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        u8 *direction_table;
        u8 *system_base;

        direction_table = D_800E262C;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_table;
        func_8003DB94(sprite,
            *(void **)(direction_table + (((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 7) & 28)),
            0);
        system_base = (u8 *)&D_80083460;
        ((S_800DA014_3 *)system_base)->unk_0A--;
        ((S_800DA014_0 *)controller)->unk_9B++;
    }
    return;

state_one:
    {
        s32 actor_flags;
        u8 *system_base;

        system_base = (u8 *)&D_80083460;
        if (((S_800DA014_3 *)system_base)->unk_02 & 0x1000) {
            return;
        }

        if ((((Rec_D_800E3D7C *)actor)->unk_64.as_s16 != 0) &&
            (func_800AA6B4(controller, action_context, sprite, 0) != 0)) {
            return;
        }

        if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
            if (((S_800DA014_3 *)system_base)->unk_02 & 0x2008) {
                return;
            }
            func_800AA79C(controller, action_context, sprite, actor);
            return;
        }

        if ((func_800A2C34(actor) << 16) != 0) {
            return;
        }

        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
        if (actor_flags & 0x100) {
            func_800AA258(controller, action_context, sprite, actor);
            return;
        }

        if (actor_flags & 0x80000) {
            func_800AA888(controller, action_context, sprite, actor);
            func_800DA660(controller, action_context, sprite, actor);
            return;
        }

        if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
            return;
        }

        if ((func_800A2C34(actor) << 16) != 0) {
            if ((func_8009A180(actor,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(actor);
        func_800A9A04(actor);

        if ((func_80042900(actor, 1) << 16) != 0) {
            u8 *reference_sprite;
            s8 coordinate;

            reference_sprite = D_80082E80;
            coordinate = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;
            if ((((coordinate == ((S_800DA014_5 *)reference_sprite)->unk_26) &&
                        (coordinate >= 0)) ||
                    (func_8009FD40(reference_sprite, sprite) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(actor, 1);
            }
        }

        if ((func_80042900(actor, 1) << 16) == 0) {
            u8 *direction_table;

            direction_table = D_800E262C;
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_table;
            func_8003DB94(sprite,
                *(void **)(direction_table + (((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 7) & 28)),
                0);
        } else {
            return;
        }
    }

    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        u8 *system_base = (u8 *)&D_80083460;

        ((S_800DA014_3 *)system_base)->unk_0A++;
        ((S_800DA014_0 *)controller)->unk_9B++;
        return;
    }
    goto finish;

state_two:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        u8 *system_base = (u8 *)&D_80083460;
        ((S_800DA014_3 *)system_base)->unk_0A--;
    }

finish:
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= ~0x200;
    ((S_800DA014_0 *)controller)->unk_8C = D_800D8C64;
}
