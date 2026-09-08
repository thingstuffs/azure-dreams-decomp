#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017409C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_8017409C_0;   /* arg0 in func_8017409C */


typedef struct S_8017409C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017409C_2;   /* base in func_8017409C */


typedef struct S_8017409C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8017409C_4;   /* global in func_8017409C */




extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_801719DC;
extern u8 D_80174684[];
extern u8 D_8017468C[];

/* Advance actor states and directional animations while handling entity flags. */
void func_8017409C(void *actor, void *context, void *animation, void *entity)
{
    s32 state;

    state = ((S_8017409C_0 *)actor)->unk_9B;
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
        s32 *dungeon_state;
        u8 *direction_frames;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            goto done;
        }

        dungeon_state = &D_80083460;
        ((S_8017409C_2 *)dungeon_state)->unk_0A--;
        direction_frames = D_80174684;
        (*(void * *)((u8 *)animation + 0x2C)) = direction_frames;
        func_80047784(animation,
            direction_frames[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u8 *dungeon_state;
        u32 entity_flags;

        if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v != 0) {
            s32 *dungeon_state;

            (*(void * *)((u8 *)animation + 0x2C)) = D_8017468C;
            func_80047784(animation,
                D_8017468C[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 |= 0x40000;
            dungeon_state = &D_80083460;
            ((S_8017409C_2 *)dungeon_state)->unk_0A++;
            goto increment_state;
        }

        dungeon_state = (u8 *)&D_80083460;
        if (((S_8017409C_4 *)dungeon_state)->unk_02 & 0x1000) {
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
            goto done;
        }

        if (entity_flags & 0x80000) {
            u16 actor_value;
            u16 value_delta;
            u32 packed_delta;

            func_800AA888(actor, context, animation, entity);
            actor_value = ((S_8017409C_0 *)actor)->unk_92;
            value_delta = ((S_8017409C_0 *)actor)->unk_A4.at02.v;
            packed_delta = ((S_8017409C_0 *)actor)->unk_A4.at00.v;
            ((S_8017409C_0 *)actor)->unk_A4.at02.v = 0;
            ((S_8017409C_0 *)actor)->unk_B8 = 0;
            ((S_8017409C_0 *)actor)->unk_AC = 0;
            ((S_8017409C_0 *)actor)->unk_B0 = 0;
            ((S_8017409C_0 *)actor)->unk_92 = actor_value - value_delta;
            ((S_8017409C_0 *)actor)->unk_A8 = packed_delta;
            func_801743F0(actor, context, animation, entity);
            goto done;
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

        (*(void * *)((u8 *)animation + 0x2C)) = D_8017468C;
        func_80047784(animation,
            D_8017468C[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
        ((S_8017409C_4 *)dungeon_state)->unk_0A++;
    }

increment_state:
    ((S_8017409C_0 *)actor)->unk_9B++;
    goto done;

state_two:
    if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {
        s32 *dungeon_state;

        dungeon_state = &D_80083460;
        ((S_8017409C_2 *)dungeon_state)->unk_0A--;
        ((S_8017409C_0 *)actor)->unk_8C = &D_801719DC;
    }

done:
    return;
}
