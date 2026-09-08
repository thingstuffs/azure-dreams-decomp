#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80173880_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173880_0;   /* arg0 in func_80173880 */

typedef struct S_80173880_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173880_1;   /* arg2 in func_80173880 */

typedef struct S_80173880_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173880_2;   /* arg3 in func_80173880 */

typedef struct S_80173880_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173880_3;   /* system_base in func_80173880 */

typedef struct S_80173880_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173880_4;   /* held_base in func_80173880 */


typedef struct S_80173880_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173880_6;   /* origin in func_80173880 */



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
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174060(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u16 D_80083460[];
extern u8 D_801710F4[];
extern u8 D_80174F40[];
extern u8 D_80174F48[];
extern u8 D_80174F50[];

/* Advances an actor's action state, updating directional animations and status transitions. */
void func_80173880(void *in_action, void *in_context, void *in_sprite, void *in_actor)
{
    void *action = in_action;
    void *context = in_context;
    void *sprite = in_sprite;
    void *actor = in_actor;
    u8 *input_state;
    s32 state;

    state = ((S_80173880_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto done;

state_zero:
    if (((S_80173880_1 *)sprite)->unk_14 & 0xE000) {
        u8 *anim_table;
        u8 *system_state;

        anim_table = D_80174F50;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((D_80083228 + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        system_state = (u8 *)&D_80083460;
        ((S_80173880_3 *)system_state)->unk_0A--;
        goto increment_state;
    }
    goto done;

state_one:
    if (((S_80173880_1 *)sprite)->unk_14 & 0xE000) {
        u8 *anim_table;

        anim_table = D_80174F48;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((D_80083228 + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    if ((func_80042900(actor, 1) << 16) != 0) {
        goto state_one_long;
    }

    {
        {
            u8 *anim_table;

            anim_table = D_80174F50;
            (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
            func_80047784(sprite,
                anim_table[((D_80083228 + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        if (((S_80173880_1 *)sprite)->unk_14 & 0x8000) {
            goto finish;
        }

        {
            register u8 *system_state ASM_REG("$2") = (u8 *)&D_80083460;   /* MATCH pin: retail register colouring depends on it */

            ((S_80173880_3 *)system_state)->unk_0A++;
        }
        goto increment_state;
    }

state_one_long:
    {
        s32 actor_flags;

        input_state = (u8 *)&D_80083460;
        if (((S_80173880_4 *)input_state)->unk_02 & 0x1000) {
            goto done;
        }

        if (((S_80173880_2 *)actor)->unk_64 != 0) {
            if (func_800AA6B4(action, context, sprite, 0) != 0) {
                goto done;
            }
        }

        if (((S_80173880_2 *)actor)->unk_25 == 0) {
            if (((S_80173880_4 *)input_state)->unk_02 & 0x2008) {
                goto done;
            }
            func_800AA79C(action, context, sprite, actor);
            goto done;
        }

        if ((func_800A2C34(actor) << 16) != 0) {
            goto done;
        }

        actor_flags = ((S_80173880_2 *)actor)->unk_1C.s;
        if (actor_flags & 0x100) {
            func_800AA258(action, context, sprite, actor);
            goto done;
        }

        if (actor_flags & 0x80000) {
            func_800AA888(action, context, sprite, actor);
            func_80174060(action, context, sprite, actor);
            goto done;
        }

        if (((S_80173880_2 *)actor)->unk_6D == 0) {
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

        if ((func_80042900(actor, 1) << 16) != 0) {
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = ((S_80173880_1 *)sprite)->unk_26;
            if ((((coordinate == ((S_80173880_6 *)origin)->unk_26) &&
                        (coordinate >= 0)) ||
                    (func_8009FD40(origin, sprite) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(actor, 1);
            }
        }

        if ((func_80042900(actor, 1) << 16) != 0) {
            goto done;
        }
    }

    {
        u8 *anim_table;

        anim_table = D_80174F50;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((D_80083228 + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    if (((S_80173880_1 *)sprite)->unk_14 & 0x8000) {
        goto finish;
    }

    {
        u8 *system_state = (u8 *)&D_80083460;
        register u16 state_count ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

        state_count = ((S_80173880_3 *)system_state)->unk_0A;
        state_count++;
        ASM_KEEP(state_count);   /* MATCH pin: retail branch polarity depends on it */
        ((S_80173880_3 *)system_state)->unk_0A = state_count;
    }
    goto increment_state;

state_two:
    if (((S_80173880_1 *)sprite)->unk_14 & 0xE000) {
        u8 *anim_table;

        anim_table = D_80174F40;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((D_80083228 + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }
    goto done;

increment_state:
    ((S_80173880_0 *)action)->unk_9B++;
    goto done;

state_three:
    if (!(((S_80173880_1 *)sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *system_state;

        system_state = (u8 *)&D_80083460;
        ((S_80173880_3 *)system_state)->unk_0A--;
    }

finish:
    ((S_80173880_2 *)actor)->unk_1C.u &= ~0x200;
    ((S_80173880_0 *)action)->unk_8C = D_801710F4;

done:
    ASM_KEEP(action);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(context);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(sprite);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    return;
}
