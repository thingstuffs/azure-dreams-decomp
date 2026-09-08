#include "common.h"
#include "records/Rec_func_800D6DC0_arg2.h"

typedef struct S_80175594_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    union { u16 s; s16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x8];
    s32 unk_AC;
    u8 pad_B0[0x6];
    u16 unk_B6;
} S_80175594_0;   /* arg0 in func_80175594 */

typedef struct S_80175594_1 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175594_1;   /* arg1 in func_80175594 */


typedef struct S_80175594_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x40];
    s16 unk_88;
} S_80175594_3;   /* object in func_80175594 */



extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E2348[];
extern u8 D_800E23B8[];
extern u8 D_800E23C0[];
extern void *const D_80170920[];
extern s32 D_80171F1C;

extern void func_80047784(void *, u8, s32);
extern s32 func_80069EF8(void);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_800A4E2C(u8 *, u8 *);
extern void func_800A56E0(s32);
extern void func_800AA53C(void *);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s32);
extern void func_800D6DC0(void *, void *, void *, void *);
extern void func_80170A44(void *, void *, void *, void *);
extern void func_80170BB8(void *, void *, void *, void *, s32);
extern void func_80171010(void *, void *, void *, s32, s32, s32);
extern s32 func_8017165C(s32);

/* Advances the entity animation sequence and relocates it to a distant tile. */
void func_80175594(void *motion, void *position, void *entity_in, void *object_in)
{
    register void *entity ASM_REG("$19") = entity_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *object ASM_REG("$23");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 particle_index;
    s32 tries_left;
    s32 burst_x;
    s32 scatter_x;
    s16 random_y;
    s16 ground_z;
    s16 tile_result;
    s32 height_offset;
    s32 dx;
    s32 dy;
    s32 entity_y;
    u8 old_x;
    u8 old_y;
    u8 *reference_entity;
    u8 *animations;

    ASM_KEEP(entity);   /* MATCH pin: keeps a statement from moving across a call/branch */

    {
        static void *const state_labels[] = {
            &&case_0, &&case_1, &&case_2, &&case_3,
            &&case_4, &&case_5, &&case_6, &&case_7
        };
        u32 state = ((S_80175594_0 *)motion)->unk_9B;

        if (state >= 8) {
            goto done;
        }
        object = object_in;
        ASM_KEEP(object);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        (void)state_labels;
        goto *D_80170920[state];
    }

case_0:
    ((S_80175594_1 *)position)->unk_14 = 0;
    ((S_80175594_1 *)position)->unk_10 = 0;
    ((S_80175594_1 *)position)->unk_0C = 0;
    if (((Rec_func_800D6DC0_arg2 *)entity)->unk_14 & 0x8000) {
        ((S_80175594_0 *)motion)->unk_9B = 7;
        ((Rec_func_800D6DC0_arg2 *)entity)->unk_14 |= 0x6000;
        goto done;
    }
    if (((S_80175594_0 *)motion)->unk_A0.at00.v <= 0x6FFFF) {
        goto done;
    }
    ((S_80175594_0 *)motion)->unk_98 |= 8;
    ((S_80175594_3 *)object)->unk_1C &= ~0x40000;
    ((S_80175594_0 *)motion)->unk_A0.at00.v = 0;
    ((S_80175594_0 *)motion)->unk_92.s -= 8;
    ((S_80175594_0 *)motion)->unk_9B++;
    ((S_80175594_0 *)motion)->unk_B6 =
        ((S_80175594_1 *)position)->unk_0A.s + ((S_80175594_0 *)motion)->unk_92.s;
    goto done;

case_1:
    (*(u8 * *)((u8 *)entity + 0x2C)) = D_800E23B8;
    func_80047784(entity,
        D_800E23B8[((D_80083228 + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
        0);
    ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
    goto next_state;

case_2:
    if (++((S_80175594_0 *)motion)->unk_96 < 9) {
        goto done;
    }
    (*(u8 * *)((u8 *)entity + 0x2C)) = D_800E23C0;
    func_80047784(entity,
        D_800E23C0[((D_80083228 + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
        0);
    goto next_state;

case_3:
    if (((S_80175594_0 *)motion)->unk_96++ < 3) {
        goto done;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
    goto next_state;

case_4:
    if (((S_80175594_0 *)motion)->unk_96++ < 0xB) {
        goto done;
    }
    particle_index = 0;
    ((S_80175594_0 *)motion)->unk_96 = 0;
    ((S_80175594_0 *)motion)->unk_9B++;
    ((S_80175594_1 *)position)->unk_14 = 0;
    ((S_80175594_0 *)motion)->unk_AC = 0;
    do {
        burst_x = (s16)(func_8017165C(0x2C) - 0x16);
        random_y = func_8017165C(0x2C) - 0x16;
        func_80171010(motion, position, entity, burst_x, random_y, 0x1E);
        particle_index++;
    } while (particle_index < 6);
    func_800D6DC0(motion, position, entity, object);
    goto done;

case_5:
    switch (((S_80175594_0 *)motion)->unk_96) {
    case 0:
        ((S_80175594_1 *)position)->unk_14 = -0x140000;
        ((S_80175594_0 *)motion)->unk_AC = 0x30000;
        break;
    case 6:
        ((S_80175594_1 *)position)->unk_14 = -0x180000;
        ((S_80175594_0 *)motion)->unk_AC = -0x10000;
        break;
    case 12:
        ((S_80175594_0 *)motion)->unk_AC = -0x20000;
        break;
    }
    ((S_80175594_1 *)position)->unk_14 += ((S_80175594_0 *)motion)->unk_AC;

    if (((S_80175594_0 *)motion)->unk_96 < 2) {
        particle_index = 0;
        do {
            scatter_x = (s16)((func_80069EF8() & 0x1F) - 0x10);
            random_y = (func_80069EF8() & 0x1F) - 0x10;
            func_80171010(motion, position, entity, scatter_x, random_y, 0x1E);
            particle_index++;
        } while (particle_index < 4);
    }
    if (((S_80175594_0 *)motion)->unk_96 == 1) {
        func_80170BB8(motion, position, entity, object, 1);
        func_800A56E0(0x80A);
    }
    if (((S_80175594_0 *)motion)->unk_96 == 2) {
        func_80170A44(motion, position, entity, object);
    }
    if (((S_80175594_0 *)motion)->unk_96 == 6) {
        func_80170BB8(motion, position, entity, object, 0x1A);
        func_800A56E0(0x705);
    }
    if (((S_80175594_0 *)motion)->unk_96++ < 0x2E) {
        goto done;
    }
    goto next_state;

case_6:
    ((S_80175594_1 *)position)->unk_0A.s = ((S_80175594_0 *)motion)->unk_B6;

next_state:
    ((S_80175594_0 *)motion)->unk_96 = 0;
    ((S_80175594_0 *)motion)->unk_9B++;
    goto done;

case_7:
    func_8009A3D0(((Rec_func_800D6DC0_arg2 *)entity)->unk_24, ((Rec_func_800D6DC0_arg2 *)entity)->unk_25,
        (((S_80175594_3 *)object)->unk_1C & 0x2000) ? 0x300 : 0x3000);
    tries_left = 0x20;
    reference_entity = D_80082E80;
    old_x = ((Rec_func_800D6DC0_arg2 *)entity)->unk_24;
    old_y = ((Rec_func_800D6DC0_arg2 *)entity)->unk_25;
    do {
        do {
            tile_result = func_800A4E2C((u8 *)entity + 0x24, (u8 *)entity + 0x25);
        } while (tile_result < 0);

        dx = reference_entity[0x24];
        dy = ((Rec_func_800D6DC0_arg2 *)entity)->unk_24;
        entity_y = ((Rec_func_800D6DC0_arg2 *)entity)->unk_25;
        dx -= dy;
        dy = reference_entity[0x25];
        if (dx < 0) {
            dx = -dx;
        }
        dy -= entity_y;
        if (dy < 0) {
            dy = -dy;
        }
        if (dx + dy >= 0x21) {
            goto coordinates_ready;
        }
    } while (--tries_left >= 0);
    ((Rec_func_800D6DC0_arg2 *)entity)->unk_24 = old_x;
    ((Rec_func_800D6DC0_arg2 *)entity)->unk_25 = old_y;

coordinates_ready:
    ((S_80175594_1 *)position)->unk_02.s = (((Rec_func_800D6DC0_arg2 *)entity)->unk_24 << 6) + 0x20;
    ((S_80175594_1 *)position)->unk_06.s = (((Rec_func_800D6DC0_arg2 *)entity)->unk_25 << 6) + 0x20;
    ground_z = func_800BCB04(((S_80175594_1 *)position)->unk_02.u, ((S_80175594_1 *)position)->unk_06.u,
        -0x200);
    ground_z -= 0x11;
    height_offset = -0x20;
    ((S_80175594_1 *)position)->unk_0A.u = ground_z;
    ((S_80175594_0 *)motion)->unk_92.u = height_offset;
    ((S_80175594_0 *)motion)->unk_A0.at00.v = 0;
    ((S_80175594_3 *)object)->unk_88 = -0x200;
    ground_z = func_800BCB04(
        (((Rec_func_800D6DC0_arg2 *)entity)->unk_24 << 6) | 0x20,
        (((Rec_func_800D6DC0_arg2 *)entity)->unk_25 << 6) | 0x20,
        -0x200);
    ((S_80175594_3 *)object)->unk_88 = ground_z;

    func_8009A21C(((Rec_func_800D6DC0_arg2 *)entity)->unk_24, ((Rec_func_800D6DC0_arg2 *)entity)->unk_25,
        (((S_80175594_3 *)object)->unk_1C & 0x2000) ? 0x300 : 0x3000);
    func_800AA53C(object);
    func_800AD594(object, 0x1000);
    ((S_80175594_0 *)motion)->unk_8C = &D_80171F1C;
    D_8008346C = 0;
    ((S_80175594_1 *)position)->unk_14 = 0;
    ((S_80175594_1 *)position)->unk_10 = 0;
    ((S_80175594_1 *)position)->unk_0C = 0;
    ((S_80175594_0 *)motion)->unk_92.u = height_offset;
    ((S_80175594_3 *)object)->unk_1C |= 0x40000;
    (*(u16 *)((u8 *)motion + 0x98)) |= 8;

    animations = D_800E2348;
    if (((Rec_func_800D6DC0_arg2 *)entity)->unk_2C != animations) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = animations;
        func_80047784(entity,
            animations[((D_80083228 + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800D6DC0_arg2 *)entity)->unk_05 = 1;
        ((S_80175594_0 *)motion)->unk_A0.at02.v = 0;
        ((S_80175594_0 *)motion)->unk_9E = 0;
    }
    ((S_80175594_3 *)object)->unk_46 &= 0x7FFF;

done:
    return;
}

#undef FIELD
