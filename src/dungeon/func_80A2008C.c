#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017388C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_8017388C_0;   /* arg0 in func_8017388C */

typedef struct S_8017388C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_8017388C_1;   /* arg2 in func_8017388C */

typedef struct S_8017388C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8017388C_2;   /* arg3 in func_8017388C */

typedef struct S_8017388C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8017388C_3;   /* system_base in func_8017388C */


typedef struct S_8017388C_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_8017388C_5;   /* origin in func_8017388C */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
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
extern void func_80173F28(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E84[];
extern u8 D_80174860[];

/* Advance the actor action through animation setup, status handling, and completion. */
void func_8017388C(void *in_action, void *in_context, void *in_sprite, void *in_actor)
{
    void *action = in_action;
    void *context = in_context;
    register void *sprite ASM_REG("$18") = in_sprite;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *actor = in_actor;
    s32 state;

    state = ((S_8017388C_0 *)action)->unk_9B;
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
    if (((S_8017388C_1 *)sprite)->unk_14 & 0xE000) {
        u8 *direction_frames;
        u8 *system_base;

        direction_frames = D_80174860;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_frames;
        func_80047784(sprite,
            direction_frames[((D_80083228 + ((S_8017388C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        system_base = (u8 *)&D_80083460;
        ((S_8017388C_3 *)system_base)->unk_0A--;
        ((S_8017388C_0 *)action)->unk_9B++;
    }
    return;

state_one:
    if ((func_80042900(actor, 1) << 16) != 0) {
        s32 actor_flags;
        u8 *system_base;

        system_base = (u8 *)&D_80083460;
        if (((S_8017388C_3 *)system_base)->unk_02 & 0x1000) {
            return;
        }

        if ((((S_8017388C_2 *)actor)->unk_64 != 0) &&
            (func_800AA6B4(action, context, sprite, 0) != 0)) {
            return;
        }

        if (((S_8017388C_2 *)actor)->unk_25 == 0) {
            if (((S_8017388C_3 *)system_base)->unk_02 & 0x2008) {
                return;
            }
            func_800AA79C(action, context, sprite, actor);
            return;
        }

        if ((func_800A2C34(actor) << 16) != 0) {
            return;
        }

        actor_flags = ((S_8017388C_2 *)actor)->unk_1C;
        if (actor_flags & 0x100) {
            func_800AA258(action, context, sprite, actor);
            return;
        }

        if (actor_flags & 0x80000) {
            func_800AA888(action, context, sprite, actor);
            func_80173F28(action, context, sprite, actor);
            return;
        }

        if (((S_8017388C_2 *)actor)->unk_6D == 0) {
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
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = ((S_8017388C_1 *)sprite)->unk_26;
            if ((((coordinate == ((S_8017388C_5 *)origin)->unk_26) &&
                        (coordinate >= 0)) ||
                    (func_8009FD40(origin, sprite) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(actor, 1);
            }
        }

        if ((func_80042900(actor, 1) << 16) != 0) {
            return;
        }
    }

    if (!(((S_8017388C_1 *)sprite)->unk_14 & 0x8000)) {
        u8 *system_base = (u8 *)&D_80083460;

        ((S_8017388C_3 *)system_base)->unk_0A++;
        ((S_8017388C_0 *)action)->unk_9B++;
        return;
    }
    goto finish;

state_two:
    if (!(((S_8017388C_1 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    {
        u8 *system_base = (u8 *)&D_80083460;
        ((S_8017388C_3 *)system_base)->unk_0A--;
    }

finish:
    ((S_8017388C_2 *)actor)->unk_1C &= ~0x200;
    ((S_8017388C_0 *)action)->unk_8C = D_80170E84;
    ASM_KEEP(action);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}
