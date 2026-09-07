#include "common.h"

typedef struct S_801736F4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801736F4_0;   /* arg0 in func_801736F4 */

typedef struct S_801736F4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801736F4_1;   /* arg2 in func_801736F4 */

typedef struct S_801736F4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801736F4_2;   /* base in func_801736F4 */

typedef struct S_801736F4_3 {
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
} S_801736F4_3;   /* arg3 in func_801736F4 */

typedef struct S_801736F4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801736F4_4;   /* global in func_801736F4 */

typedef struct S_801736F4_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_801736F4_5;   /* D_800814A8 in func_801736F4 */



extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173A30(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E54;
extern u8 D_80173CD4[];
extern u8 D_80173CDC[];

/* Advances the entity's animation state and processes pending actions. */
void func_801736F4(void *controller, void *context, void *sprite, void *entity)
{
    s32 state;

    state = ((S_801736F4_0 *)controller)->unk_9B;
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
        s32 *counter_state;
        u8 *direction_anims;

        if (!(((S_801736F4_1 *)sprite)->unk_14 & 0xE000)) {
            goto done;
        }

        counter_state = &D_80083460;
        ((S_801736F4_2 *)counter_state)->unk_0A--;
        direction_anims = D_80173CDC;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        func_80047784(sprite,
            direction_anims[((D_80083228 + ((S_801736F4_3 *)entity)->unk_2A + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u8 *dungeon_state;
        u32 entity_flags;

        if (((S_801736F4_3 *)entity)->unk_25 != 0) {
            s32 *counter_state;

            (*(void * *)((u8 *)sprite + 0x2C)) = D_80173CD4;
            func_80047784(sprite,
                D_80173CD4[((D_80083228 + ((S_801736F4_3 *)entity)->unk_2A + 0x100) >> 9) & 7],
                0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            counter_state = &D_80083460;
            ((S_801736F4_2 *)counter_state)->unk_0A++;
            goto increment_state;
        }

        dungeon_state = (u8 *)&D_80083460;
        if (((S_801736F4_4 *)dungeon_state)->unk_02 & 0x1000) {
            goto done;
        }

        if (((S_801736F4_3 *)entity)->unk_64 != 0) {
            if (func_800AA6B4(controller, context, sprite, 0) != 0) {
                goto done;
            }
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            goto done;
        }

        entity_flags = ((S_801736F4_3 *)entity)->unk_1C;
        if (entity_flags & 0x100) {
            func_800AA258(controller, context, sprite, entity);
            goto done;
        }

        if (entity_flags & 0x80000) {
            func_800AA888(controller, context, sprite, entity);
            func_80173A30(controller, context, sprite, entity);
            goto done;
        }

        if (((S_801736F4_3 *)entity)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((func_8009A180(entity,
                    (u8 *)((S_801736F4_5 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((S_801736F4_3 *)entity)->unk_25 == 0) {
            goto done;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80173CD4;
        func_80047784(sprite,
            D_80173CD4[((D_80083228 + ((S_801736F4_3 *)entity)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801736F4_3 *)entity)->unk_1C |= 0x40000;
        ((S_801736F4_4 *)dungeon_state)->unk_0A++;
    }

increment_state:
    ((S_801736F4_0 *)controller)->unk_9B++;
    goto done;

state_two:
    if (((S_801736F4_1 *)sprite)->unk_14 & 0xE000) {
        s32 *counter_state;

        counter_state = &D_80083460;
        ((S_801736F4_2 *)counter_state)->unk_0A--;
        ((S_801736F4_3 *)entity)->unk_1C &= ~0x208;
        ((S_801736F4_0 *)controller)->unk_8C = &D_80170E54;
    }

done:
    return;
}
