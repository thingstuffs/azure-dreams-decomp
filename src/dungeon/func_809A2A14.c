#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174574(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_801710EC;
extern u8 D_80175EA0[];
extern u8 D_80175EC0[];


typedef struct S_80174214_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80174214_0;   /* arg0 in func_80174214 */


typedef struct S_80174214_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174214_2;   /* base in func_80174214 */


typedef struct S_80174214_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80174214_4;   /* global in func_80174214 */


/* Advances the actor action state, updating directional animation and entity status. */
void func_80174214(void *actor, void *context, void *animation, void *entity)
{
    s32 state;

    state = ((S_80174214_0 *)actor)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto at_least_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

at_least_two:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    {
        s32 *action_counts;
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            goto done;
        }

        action_counts = &D_80083460;
        ((S_80174214_2 *)action_counts)->unk_0A--;
        direction_anims = D_80175EA0;
        if (((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv != direction_anims) {
            (*(void * *)((u8 *)animation + (0x2C))) = direction_anims;
            func_80047784(animation,
                direction_anims[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            goto increment_state;
        }
        goto increment_state;
    }

state_one:
    {
        u8 *action_status;
        u32 entity_flags;

        if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v != 0) {
            s32 *action_counts;

            (*(void * *)((u8 *)animation + (0x2C))) = D_80175EC0;
            func_80047784(animation,
                D_80175EC0[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 |= 0x40000;
            action_counts = &D_80083460;
            ((S_80174214_2 *)action_counts)->unk_0A++;
            goto increment_state;
        }

        action_status = (u8 *)&D_80083460;
        if (((S_80174214_4 *)action_status)->unk_02 & 0x1000) {
            goto done;
        }

        if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, animation, 0) != 0) {
                goto done;
            }
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            goto done;
        }

        entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32;
        if (entity_flags & 0x100) {
            func_800AA258(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stat_value;
            u16 stat_delta;

            func_800AA888(actor, context, animation, entity);
            stat_value = ((S_80174214_0 *)actor)->unk_92;
            stat_delta = ((S_80174214_0 *)actor)->unk_A2;
            ((S_80174214_0 *)actor)->unk_A2 = 0;
            ((S_80174214_0 *)actor)->unk_9E = 0;
            ((S_80174214_0 *)actor)->unk_92 = stat_value - stat_delta;
            func_80174574(actor, context, animation, entity);
            return;
        }

        if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 == 0) {
            goto done;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((func_8009A180(entity,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
            goto done;
        }

        (*(void * *)((u8 *)animation + (0x2C))) = D_80175EC0;
        func_80047784(animation,
            D_80175EC0[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 |= 0x40000;
        ((S_80174214_4 *)action_status)->unk_0A++;
    }

increment_state:
    ((S_80174214_0 *)actor)->unk_9B++;
    return;

state_two:
    if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {
        s32 *action_counts;

        action_counts = &D_80083460;
        ((S_80174214_2 *)action_counts)->unk_0A--;
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 &= ~8;
        ((S_80174214_0 *)actor)->unk_8C = &D_801710EC;
    }

done:
    return;
}
