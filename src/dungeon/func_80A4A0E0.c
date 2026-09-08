#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801738E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x1A];
    u16 unk_B6;
    u16 unk_B8;
} S_801738E0_0;   /* arg0 in func_801738E0 */

typedef struct S_801738E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801738E0_1;   /* arg2 in func_801738E0 */

typedef struct S_801738E0_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801738E0_2;   /* base in func_801738E0 */

typedef struct S_801738E0_3 {
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
} S_801738E0_3;   /* arg3 in func_801738E0 */

typedef struct S_801738E0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801738E0_4;   /* global in func_801738E0 */




extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173C34(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8017140C;
extern u8 D_80175894[];
extern u8 D_8017588C[];

/* Advance the actor animation state and process pending actions. */
void func_801738E0(void *entity, void *context, void *anim, void *actor)
{
    s32 state;

    state = ((S_801738E0_0 *)entity)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto at_least_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

at_least_two:
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    {
        s32 *scene_state;
        u8 *direction_anims;

        if (!(((S_801738E0_1 *)anim)->unk_14 & 0xE000)) {
            goto done;
        }

        scene_state = &D_80083460;
        ((S_801738E0_2 *)scene_state)->unk_0A--;
        direction_anims = D_80175894;
        (*(void * *)((u8 *)anim + 0x2C)) = direction_anims;
        func_80047784(anim,
            direction_anims[((D_80083228 + ((S_801738E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u8 *scene_state;
        u32 actor_flags;

        if (((S_801738E0_3 *)actor)->unk_25 != 0) {
            s32 *scene_state;

            (*(void * *)((u8 *)anim + 0x2C)) = D_8017588C;
            func_80047784(anim,
                D_8017588C[((D_80083228 + ((S_801738E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801738E0_3 *)actor)->unk_1C |= 0x40000;
            scene_state = &D_80083460;
            ((S_801738E0_2 *)scene_state)->unk_0A++;
            goto increment_state;
        }

        scene_state = (u8 *)&D_80083460;
        if (((S_801738E0_4 *)scene_state)->unk_02 & 0x1000) {
            goto done;
        }

        if (((S_801738E0_3 *)actor)->unk_64 != 0) {
            if (func_800AA6B4(entity, context, anim, 0) != 0) {
                goto done;
            }
        }

        if ((func_800A2C34(actor) << 16) != 0) {
            goto done;
        }

        actor_flags = ((S_801738E0_3 *)actor)->unk_1C;
        if (actor_flags & 0x100) {
            func_800AA258(entity, context, anim, actor);
            goto done;
        }

        if (actor_flags & 0x80000) {
            u16 entity_value;
            u16 pending_delta;

            func_800AA888(entity, context, anim, actor);
            entity_value = ((S_801738E0_0 *)entity)->unk_92;
            pending_delta = ((S_801738E0_0 *)entity)->unk_B6;
            ((S_801738E0_0 *)entity)->unk_B6 = 0;
            ((S_801738E0_0 *)entity)->unk_B8 = 0;
            ((S_801738E0_0 *)entity)->unk_92 = entity_value - pending_delta;
            func_80173C34(entity, context, anim, actor);
            goto done;
        }

        if (((S_801738E0_3 *)actor)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            if ((func_8009A180(actor,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(actor);
        func_800A9A04(actor);
        if (((S_801738E0_3 *)actor)->unk_25 == 0) {
            goto done;
        }

        (*(void * *)((u8 *)anim + 0x2C)) = D_8017588C;
        func_80047784(anim,
            D_8017588C[((D_80083228 + ((S_801738E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801738E0_3 *)actor)->unk_1C |= 0x40000;
        ((S_801738E0_4 *)scene_state)->unk_0A++;
    }

increment_state:
    ((S_801738E0_0 *)entity)->unk_9B++;
    goto done;

state_two:
    if (((S_801738E0_1 *)anim)->unk_14 & 0xE000) {
        s32 *scene_state;

        scene_state = &D_80083460;
        ((S_801738E0_2 *)scene_state)->unk_0A--;
        ((S_801738E0_3 *)actor)->unk_1C &= ~0x208;
        ((S_801738E0_0 *)entity)->unk_8C = &D_8017140C;
    }

done:
    return;
}
