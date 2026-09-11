#include "common.h"
extern int abs(int);

typedef struct Vec3Work {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Vec3Work;

typedef struct LocalWork {
    Vec3Work base;
    u16 delta[3];
} LocalWork;

typedef struct S_81087818_0 {
    union { s16 s; u16 u; } unk_00;
    union { s16 s; u16 u; } unk_02;
    union { s16 s; u16 u; } unk_04;
    union { s16 s; u16 u; } unk_06;
    union { s16 s; u16 u; } unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x18];
    union {
        s32 word;
        struct { u8 pad_00[2]; s16 unk_2A; } half;
    } unk_28;
    union {
        s32 word;
        struct { u8 pad_00[2]; s16 unk_2E; } half;
    } unk_2C;
    union {
        s32 word;
        struct { u8 pad_00[2]; union { s16 s; u16 u; } unk_32; } half;
    } unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    void *unk_40;
    Vec3Work *unk_44;
    void *unk_48;
    void *unk_4C;
} S_81087818_0;

typedef struct S_81087818_1 {
    u8 pad_00[8];
    void *unk_08;
    u8 pad_0C[8];
    u16 unk_14;
    u8 pad_16[0x16];
    void *unk_2C;
    u8 pad_30[0x78];
    s16 unk_A8;
    s16 unk_AA;
    s16 unk_AC;
    u8 unk_AE;
} S_81087818_1;

typedef struct S_81087818_2 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
} S_81087818_2;

typedef struct S_81087818_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_81087818_3;

typedef struct S_81087818_4 {
    u8 pad_00[2];
    union { s16 s; u16 u; } unk_02;
    u8 pad_04[2];
    union { s16 s; u16 u; } unk_06;
    u8 pad_08[2];
    union { s16 s; u16 u; } unk_0A;
} S_81087818_4;

typedef struct S_81087818_5 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;
} S_81087818_5;

typedef struct S_81087818_7 {
    s32 *unk_00;
} S_81087818_7;

extern void func_800478B8(void *);
extern void *func_8003DE58(void *, void *, u16 *, s32);
extern s32 func_80069EF8(void);
extern s32 func_800644B8(s16);
extern s32 func_80064584(s16);
extern void func_8009C12C(void *, void *, s16, s16);
extern void func_800C77D0(void *, void *, s32, s32);
extern void func_80175A90(Vec3Work *, Vec3Work *);

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0;
extern u8 D_800DDC40[];
extern void *D_80170888[];
extern u8 D_80175F68;

/* Updates staged movement to a target and back to the actor's base position. */
void func_80175018(S_81087818_0 *motion, Vec3Work *trajectory, void *context)
{
    LocalWork work;
#define base work.base
#define delta work.delta
    s32 next_state;
    u32 state;
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4
    };

    motion->unk_02.u++;
    func_800478B8(context);

    base = *motion->unk_44;
    delta[0] = delta[1] = delta[2] = 0;
    {
        S_81087818_1 *actor = motion->unk_48;
        if ((actor->unk_14 & 0x9FFF) == 0 &&
            func_8003DE58(actor->unk_08, actor, delta, 3) != 0) {
            ((S_81087818_4 *)&base)->unk_02.u += delta[0];
            ((S_81087818_4 *)&base)->unk_06.u += delta[1];
            ((S_81087818_4 *)&base)->unk_0A.u += delta[2];
            motion->unk_0A = delta[0];
            motion->unk_0C = delta[1];
            motion->unk_0E = delta[2];
        } else {
            ((S_81087818_4 *)&base)->unk_02.u += motion->unk_0A;
            ((S_81087818_4 *)&base)->unk_06.u += motion->unk_0C;
            ((S_81087818_4 *)&base)->unk_0A.u += motion->unk_0E;
        }
    }

    state = (u32)motion->unk_00.s;
    if (state >= 5) {
        goto finish;
    }
    (void)state_labels;
    goto *D_80170888[state];

state0:
{
    S_81087818_1 *actor = motion->unk_40;
    S_81087818_2 *source;
    s32 base_x;
    s32 base_y;
    register s32 distance_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 distance_y;
    register u32 direction_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 *direction_table;
    s32 tile_x;

    motion->unk_28.word = motion->unk_2C.word = motion->unk_30.word = 0;
    motion->unk_34 = motion->unk_38 = motion->unk_3C = 0;
    switch (actor->unk_AE) {
    case 1:
        source = motion->unk_4C;
        tile_x = actor->unk_A8;
        direction_offset = source->unk_2A.u;
        direction_table = D_8006CCD8;
        direction_offset = (direction_offset >> 8) & 0xE;
        motion->unk_28.half.unk_2A =
            (tile_x * 64) +
            ((*(s16 *)((u8 *)direction_table + direction_offset) + 1) * 32);
        motion->unk_2C.half.unk_2E =
            (((S_81087818_1 *)motion->unk_40)->unk_AA * 64) +
            ((*(s16 *)((u8 *)D_8006CCE8 + direction_offset) + 1) * 32);
        motion->unk_30.half.unk_32.u = ((S_81087818_4 *)&base)->unk_0A.u;

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        distance_x = motion->unk_28.half.unk_2A;
        base_x = ((S_81087818_4 *)&base)->unk_02.s;
        base_y = ((S_81087818_4 *)&base)->unk_06.s;
        distance_x -= base_x;
        if (distance_x < 0) {
            distance_x = -distance_x;
        }
        delta[0] = distance_x;
        distance_y = motion->unk_2C.half.unk_2E - base_y;
        distance_y = abs(distance_y);
        delta[1] = distance_y;
        motion->unk_04.s = delta[0];
        if (motion->unk_04.s < (s16)delta[1]) {
            motion->unk_04.u = delta[1];
        }
        motion->unk_04.s = (s16)motion->unk_04.u >> 5;
        if (motion->unk_04.s == 0) {
            motion->unk_04.u = 1;
        }
        trajectory->dx = motion->unk_28.word - base.x;
        trajectory->dy = motion->unk_2C.word - base.y;
        trajectory->dz = 0;
        break;

    case 2:
    {
        s32 *position;
        S_81087818_3 *node;
        s32 axis = 1;
        s32 distance_x;
        s32 distance_y;
        s32 distance_z;
        u8 *delta_scan;
        s32 origin_x;
        s32 origin_y;
        s32 origin_z;
        s32 height;
        s32 position_z;

        node = ((S_81087818_2 *)motion->unk_4C)->unk_60;
        position = ((S_81087818_7 *)((u8 *)node - 0x18))->unk_00;
        motion->unk_28.word = position[0];
        motion->unk_2C.word = position[1];
        height = D_800DDC40[((S_81087818_3 *)((S_81087818_2 *)motion->unk_4C)->unk_60)->unk_13];
        position_z = position[2];
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        distance_x = motion->unk_28.half.unk_2A;
        motion->unk_30.word = position_z - (height << 15);

        origin_x = ((S_81087818_4 *)&base)->unk_02.s;
        origin_y = ((S_81087818_4 *)&base)->unk_06.s;
        distance_x -= origin_x;
        distance_x = abs(distance_x);
        delta[0] = distance_x;
        distance_y = motion->unk_2C.half.unk_2E - origin_y;
        distance_y = abs(distance_y);
        delta[1] = distance_y;
        distance_z = motion->unk_30.half.unk_32.s;
        origin_z = ((S_81087818_4 *)&base)->unk_0A.s;
        delta_scan = (u8 *)&base + 2;
        distance_z -= origin_z;
        distance_z = abs(distance_z);
        delta[2] = distance_z;

        motion->unk_04.s = delta[0];
        for (axis = 1; axis < 3; axis++, delta_scan += 2) {
            if (((S_81087818_5 *)delta_scan)->unk_18.s > motion->unk_04.s) {
                motion->unk_04.u = ((S_81087818_5 *)delta_scan)->unk_18.u;
            }
        }
        motion->unk_04.s = (s16)motion->unk_04.u >> 5;
        if (motion->unk_04.s == 0) {
            motion->unk_04.u = 1;
        }
        trajectory->dx = motion->unk_28.word - base.x;
        trajectory->dy = motion->unk_2C.word - base.y;
        trajectory->dz = motion->unk_30.word - base.z;
        break;
    }
    case 0:
    default:
        break;
    }

    trajectory->x = base.x;
    trajectory->y = base.y;
    trajectory->z = base.z;
    motion->unk_00.u++;
    motion->unk_02.u = 0;
    goto finish;
}

state1:
{
    trajectory->dx /= 2;
    trajectory->dy /= 2;
    trajectory->dz /= 2;
    trajectory->x += trajectory->dx;
    trajectory->y += trajectory->dy;
    trajectory->z += trajectory->dz;
    if (motion->unk_02.s < motion->unk_04.s) {
        goto call_helper;
    }

    trajectory->x = motion->unk_28.word;
    trajectory->y = motion->unk_2C.word;
    trajectory->z = motion->unk_30.word;
    motion->unk_02.u = 0;
    {
        S_81087818_1 *actor = motion->unk_40;
        if (actor->unk_AE != 2) {
            s32 return_dz;

            trajectory->dx = (base.x - trajectory->x) >> (motion->unk_04.s + 1);
            trajectory->dy = (base.y - trajectory->y) >> (motion->unk_04.s + 1);
            return_dz = (base.z - trajectory->z) >> (motion->unk_04.s + 1);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            next_state = 3;
            trajectory->dz = return_dz;
        } else {
            next_state = motion->unk_00.u + 1;
        }
    }
    goto commit_state;
}

state2:
{
    s32 elevation_factor;
    s32 azimuth_factor;
    {
        s32 random_angle = func_80069EF8();
        s32 biased_angle = random_angle;
        s32 base_angle = motion->unk_06.u + 0x400;
        s32 quotient;
        s32 remainder;

        if (random_angle < 0) {
            biased_angle = random_angle + 0x7FF;
        }
        quotient = biased_angle >> 11;
        remainder = random_angle - (quotient << 11);
        motion->unk_06.u = base_angle + remainder;
    }
    {
        s32 random_angle = func_80069EF8();
        s32 biased_angle = random_angle;
        s32 base_angle = motion->unk_08.u + 0x400;
        s32 quotient;
        s32 remainder;

        if (random_angle < 0) {
            biased_angle = random_angle + 0x7FF;
        }
        quotient = biased_angle >> 11;
        remainder = random_angle - (quotient << 11);
        motion->unk_08.u = base_angle + remainder;
    }

    elevation_factor = func_800644B8(motion->unk_06.s);
    azimuth_factor = func_800644B8(motion->unk_08.s);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    elevation_factor >>= 4;
    azimuth_factor >>= 4;
    trajectory->x = motion->unk_28.word + ((elevation_factor * azimuth_factor) << 5);
    elevation_factor = func_800644B8(motion->unk_06.s);
    azimuth_factor = func_80064584(motion->unk_08.s);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    elevation_factor >>= 4;
    azimuth_factor >>= 4;
    trajectory->y = motion->unk_2C.word + ((elevation_factor * azimuth_factor) << 5);
    trajectory->z = motion->unk_30.word + ((func_80064584(motion->unk_06.s) >> 4) << 13);

    if (motion->unk_02.s < 8) {
        goto call_helper;
    }
    {
        S_81087818_1 *actor = motion->unk_40;
        if (actor->unk_AE == 2) {
            S_81087818_2 *source = motion->unk_4C;
            func_8009C12C(source, motion->unk_48,
                          source->unk_2A.s, actor->unk_AC);
        }
    }
    trajectory->dx = (base.x - trajectory->x) >> (motion->unk_04.s + 1);
    trajectory->dy = (base.y - trajectory->y) >> (motion->unk_04.s + 1);
    trajectory->dz = (base.z - trajectory->z) >> (motion->unk_04.s + 1);
    motion->unk_02.u = 0;

    next_state = motion->unk_00.u + 1;
commit_state:
    motion->unk_00.u = next_state;
call_helper:
    func_80175A90(&base, trajectory);
    goto finish;
}

state3:
{
    if (motion->unk_02.s < motion->unk_04.s) {
        trajectory->dx *= 2;
        trajectory->dy *= 2;
        trajectory->dz *= 2;
        trajectory->x += trajectory->dx;
        trajectory->y += trajectory->dy;
        trajectory->z += trajectory->dz;
        func_80175A90(&base, trajectory);
        goto finish;
    }
    trajectory->x = base.x;
    trajectory->y = base.y;
    trajectory->z = base.z;
    {
        S_81087818_1 *actor = motion->unk_48;
        u16 flags = actor->unk_14;
        if (!(flags & 0x800)) {
            goto finish;
        }
        actor->unk_14 = flags & 0xF7FF;
    }
    motion->unk_00.u++;
    motion->unk_02.u = 0;
}

state4:
{
    S_81087818_1 *actor = motion->unk_48;
    if (actor->unk_2C != &D_80175F68) {
        (*(u16 *)((u8 *)motion - 2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
    actor->unk_14 &= 0xF7FF;
    trajectory->x = base.x;
    trajectory->y = base.y;
    trajectory->z = base.z;
}

finish:
    if (motion->unk_00.s != 0) {
        func_800C77D0((u8 *)motion - 0x20, trajectory, 8, 0x300);
    }
#undef delta
#undef base
}
