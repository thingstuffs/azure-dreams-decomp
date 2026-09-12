#include "common.h"

typedef struct S_801734B0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801734B0_0;   /* arg0 in func_801734B0 */

typedef struct S_801734B0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801734B0_1;   /* arg2 in func_801734B0 */

typedef struct S_801734B0_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801734B0_2;   /* arg3 in func_801734B0 */

typedef struct S_801734B0_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801734B0_3;   /* counter_base in func_801734B0 */

typedef struct S_801734B0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_801734B0_4;   /* global_base in func_801734B0 */

typedef struct S_801734B0_5 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x22];
    u16 unk_B6;
    u16 unk_B8;
} S_801734B0_5;   /* copy_arg0 in func_801734B0 */

typedef struct S_801734B0_6 {
    u8 pad_00[0x58];
    void * unk_58;
} S_801734B0_6;   /* owner in func_801734B0 */

typedef struct S_801734B0_7 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_801734B0_7;   /* origin in func_801734B0 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173C34(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_8017140C[];
extern u8 D_80175894[];
extern u8 D_80175894[];

/* Updates actor state, animation, and callbacks according to entity and dungeon flags. */
void func_801734B0(void *in_actor, void *in_context, void *in_sprite, void *in_entity)
{
    void *context = in_context;
    s32 entity_flags;
    u16 stat_value;
    u16 stat_delta;
    register u8 *page_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *global_base ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 state;

    state = ((S_801734B0_0 *)in_actor)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(((S_801734B0_1 *)in_sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    (*(void * *)((u8 *)in_sprite + 0x2C)) = D_80175894;
    func_80047784(in_sprite,
        D_80175894[((D_80083228 + ((S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801734B0_0 *)in_actor)->unk_96 = 0;
    {
        u8 *counter_base = (u8 *)&D_80083460;
        u16 counter_value;

        counter_value = ((S_801734B0_3 *)counter_base)->unk_0A;
        counter_value--;
        ((S_801734B0_3 *)counter_base)->unk_0A = counter_value;
    }
    goto increment_state;

state_one:
    if ((func_80042900(in_entity, 1) << 16) != 0) {
        page_base = (u8 *)0x80080000;
        goto state_one_active;
    }
    (*(void * *)((u8 *)in_sprite + 0x2C)) = D_80175894;
    func_80047784(in_sprite,
        D_80175894[((D_80083228 + ((S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801734B0_2 *)in_entity)->unk_1C.s |= 0x40000;
    if (!(((S_801734B0_1 *)in_sprite)->unk_14 & 0x8000)) {
        goto increment_counter;
    }
    ((S_801734B0_2 *)in_entity)->unk_1C.s &= ~0x200;
    goto assign_callback;

state_one_active:
    ASM_KEEP(page_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    global_base = page_base + 0x3460;
    {
        if (((S_801734B0_4 *)global_base)->unk_02 & 0x1000) {
            goto done;
        }
        if (((S_801734B0_2 *)in_entity)->unk_64 != 0) {
            if (func_800AA6B4(in_actor, context, in_sprite, 0) != 0) {
                goto done;
            }
        }
        if (((S_801734B0_2 *)in_entity)->unk_25 == 0) {
            if (((S_801734B0_4 *)global_base)->unk_02 & 0x2008) {
                goto done;
            }
            func_800AA79C(in_actor, context, in_sprite, in_entity);
            goto done;
        }
        if ((func_800A2C34(in_entity) << 16) != 0) {
            goto done;
        }
        entity_flags = ((S_801734B0_2 *)in_entity)->unk_1C.u;
        if (entity_flags & 0x100) {
            func_800AA258(in_actor, context, in_sprite, in_entity);
            goto done;
        }
        if (entity_flags & 0x80000) {

            func_800AA888(in_actor, context, in_sprite, in_entity);
            ASM_KEEP(in_actor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            stat_value = ((S_801734B0_5 *)in_actor)->unk_92;
            stat_delta = ((S_801734B0_5 *)in_actor)->unk_B6;
            ((S_801734B0_5 *)in_actor)->unk_B6 = 0;
            ((S_801734B0_5 *)in_actor)->unk_B8 = 0;
            ((S_801734B0_5 *)in_actor)->unk_92 = stat_value - stat_delta;
            func_80173C34(in_actor, context, in_sprite, in_entity);
            goto done;
        }
        if (((S_801734B0_2 *)in_entity)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(in_entity) << 16) != 0) {
            void *owner = D_800814A8;

            if ((func_8009A180(in_entity,
                    (u8 *)((S_801734B0_6 *)owner)->unk_58 + 0x20) << 16) != 0) {
                goto done;
            }
        }
        func_800A9A0C(in_entity);
        func_800A9A04(in_entity);
        if ((func_80042900(in_entity, 1) << 16) != 0) {
            u8 *origin = D_80082E80;
            s8 tile = ((S_801734B0_1 *)in_sprite)->unk_26;

            if (((tile == ((S_801734B0_7 *)origin)->unk_26) && (tile >= 0)) ||
                ((s16)func_8009FD40(origin, in_sprite) < 2)) {
                if (!(func_800A6D30() & 7)) {
                    func_80042B68(in_entity, 1);
                }
            }
        }
        if ((func_80042900(in_entity, 1) << 16) != 0) {
            goto done;
        }
    }
    (*(void * *)((u8 *)in_sprite + 0x2C)) = D_80175894;
    func_80047784(in_sprite,
        D_80175894[((D_80083228 + ((S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7],
        0);
    {
        u32 updated_flags;

        updated_flags = ((S_801734B0_2 *)in_entity)->unk_1C.s;
        updated_flags |= 0x40000;
        ((S_801734B0_2 *)in_entity)->unk_1C.s = updated_flags;
    }
    if (((S_801734B0_1 *)in_sprite)->unk_14 & 0x8000) {
        ((S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;
        goto assign_callback;
    }

increment_counter:
    {
        u8 *counter_base = (u8 *)&D_80083460;
        register u16 counter_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        counter_value = ((S_801734B0_3 *)counter_base)->unk_0A;
        counter_value++;
        ((S_801734B0_3 *)counter_base)->unk_0A = counter_value;
    }

increment_state:
    ((S_801734B0_0 *)in_actor)->unk_9B++;
    goto done;

state_two:
    if (!(((S_801734B0_1 *)in_sprite)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_801734B0_3 *)counter_base)->unk_0A--;
    }

clear_callback:
    ((S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;

assign_callback:
    ((S_801734B0_0 *)in_actor)->unk_8C = D_8017140C;

done:
    return;
}
