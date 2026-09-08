#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

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
void func_80175018(void *motion, Vec3Work *trajectory, void *context)
{
    LocalWork work;
#define base work.base
#define delta work.delta
    s32 next_state;
    u32 state;
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4
    };

    FIELD(motion, u16, 2)++;
    func_800478B8(context);

    base = *FIELD(motion, Vec3Work *, 0x44);
    delta[0] = delta[1] = delta[2] = 0;
    {
        void *actor = FIELD(motion, void *, 0x48);
        if ((FIELD(actor, u16, 0x14) & 0x9FFF) == 0 &&
            func_8003DE58(FIELD(actor, void *, 8), actor, delta, 3) != 0) {
            FIELD(&base, u16, 2) += delta[0];
            FIELD(&base, u16, 6) += delta[1];
            FIELD(&base, u16, 0xA) += delta[2];
            FIELD(motion, u16, 0xA) = delta[0];
            FIELD(motion, u16, 0xC) = delta[1];
            FIELD(motion, u16, 0xE) = delta[2];
        } else {
            FIELD(&base, u16, 2) += FIELD(motion, u16, 0xA);
            FIELD(&base, u16, 6) += FIELD(motion, u16, 0xC);
            FIELD(&base, u16, 0xA) += FIELD(motion, u16, 0xE);
        }
    }

    state = (u32)FIELD(motion, s16, 0);
    if (state >= 5) {
        goto finish;
    }
    (void)state_labels;
    goto *D_80170888[state];

state0:
{
    void *actor = FIELD(motion, void *, 0x40);
    void *source;
    s32 base_x;
    s32 base_y;
    register s32 distance_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 distance_y;
    register u32 direction_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 *direction_table;
    s32 tile_x;

    FIELD(motion, s32, 0x28) = FIELD(motion, s32, 0x2C) = FIELD(motion, s32, 0x30) = 0;
    FIELD(motion, s32, 0x34) = FIELD(motion, s32, 0x38) = FIELD(motion, s32, 0x3C) = 0;
    switch (FIELD(actor, u8, 0xAE)) {
    case 1:
        source = FIELD(motion, void *, 0x4C);
        tile_x = FIELD(actor, s16, 0xA8);
        direction_offset = FIELD(source, u16, 0x2A);
        direction_table = D_8006CCD8;
        direction_offset = (direction_offset >> 8) & 0xE;
        FIELD(motion, s16, 0x2A) =
            (tile_x * 64) +
            ((*(s16 *)((u8 *)direction_table + direction_offset) + 1) * 32);
        FIELD(motion, s16, 0x2E) =
            (FIELD(FIELD(motion, void *, 0x40), s16, 0xAA) * 64) +
            ((*(s16 *)((u8 *)D_8006CCE8 + direction_offset) + 1) * 32);
        FIELD(motion, u16, 0x32) = FIELD(&base, u16, 0xA);

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        distance_x = FIELD(motion, s16, 0x2A);
        base_x = FIELD(&base, s16, 2);
        base_y = FIELD(&base, s16, 6);
        distance_x -= base_x;
        if (distance_x < 0) {
            distance_x = -distance_x;
        }
        delta[0] = distance_x;
        distance_y = FIELD(motion, s16, 0x2E) - base_y;
        if (distance_y < 0) {
            distance_y = -distance_y;
        }
        delta[1] = distance_y;
        FIELD(motion, s16, 4) = delta[0];
        if (FIELD(motion, s16, 4) < (s16)delta[1]) {
            FIELD(motion, u16, 4) = delta[1];
        }
        FIELD(motion, s16, 4) = (s16)FIELD(motion, u16, 4) >> 5;
        if (FIELD(motion, s16, 4) == 0) {
            FIELD(motion, u16, 4) = 1;
        }
        trajectory->dx = FIELD(motion, s32, 0x28) - base.x;
        trajectory->dy = FIELD(motion, s32, 0x2C) - base.y;
        trajectory->dz = 0;
        break;

    case 2:
    {
        s32 *position;
        void *node;
        s32 axis = 1;
        s32 distance_x;
        s32 distance_y;
        register s32 distance_z ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        u8 *delta_scan;
        s32 origin_x;
        s32 origin_y;
        s32 origin_z;
        s32 height;
        s32 position_z;

        node = FIELD(FIELD(motion, void *, 0x4C), void *, 0x60);
        position = FIELD(node, s32 *, -0x18);
        FIELD(motion, s32, 0x28) = position[0];
        FIELD(motion, s32, 0x2C) = position[1];
        height = D_800DDC40[FIELD(FIELD(FIELD(motion, void *, 0x4C), void *, 0x60), u8, 0x13)];
        position_z = position[2];
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        distance_x = FIELD(motion, s16, 0x2A);
        FIELD(motion, s32, 0x30) = position_z - (height << 15);

        origin_x = FIELD(&base, s16, 2);
        origin_y = FIELD(&base, s16, 6);
        distance_x -= origin_x;
        if (distance_x < 0) {
            distance_x = -distance_x;
        }
        delta[0] = distance_x;
        distance_y = FIELD(motion, s16, 0x2E) - origin_y;
        if (distance_y < 0) {
            distance_y = -distance_y;
        }
        delta[1] = distance_y;
        distance_z = FIELD(motion, s16, 0x32);
        origin_z = FIELD(&base, s16, 0xA);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        delta_scan = (u8 *)&base + 2;
        ASM_KEEP_NV(distance_z);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        distance_z -= origin_z;
        if (distance_z < 0) {
            distance_z = -distance_z;
        }
        delta[2] = distance_z;

        FIELD(motion, s16, 4) = delta[0];
        for (axis = 1; axis < 3; axis++, delta_scan += 2) {
            if (FIELD(delta_scan, s16, 0x18) > FIELD(motion, s16, 4)) {
                FIELD(motion, u16, 4) = FIELD(delta_scan, u16, 0x18);
            }
        }
        FIELD(motion, s16, 4) = (s16)FIELD(motion, u16, 4) >> 5;
        if (FIELD(motion, s16, 4) == 0) {
            FIELD(motion, u16, 4) = 1;
        }
        trajectory->dx = FIELD(motion, s32, 0x28) - base.x;
        trajectory->dy = FIELD(motion, s32, 0x2C) - base.y;
        trajectory->dz = FIELD(motion, s32, 0x30) - base.z;
        break;
    }
    case 0:
    default:
        break;
    }

    trajectory->x = base.x;
    trajectory->y = base.y;
    trajectory->z = base.z;
    FIELD(motion, u16, 0)++;
    FIELD(motion, u16, 2) = 0;
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
    if (FIELD(motion, s16, 2) < FIELD(motion, s16, 4)) {
        goto call_helper;
    }

    trajectory->x = FIELD(motion, s32, 0x28);
    trajectory->y = FIELD(motion, s32, 0x2C);
    trajectory->z = FIELD(motion, s32, 0x30);
    FIELD(motion, u16, 2) = 0;
    {
        void *actor = FIELD(motion, void *, 0x40);
        if (FIELD(actor, u8, 0xAE) != 2) {
            s32 return_dz;

            trajectory->dx = (base.x - trajectory->x) >> (FIELD(motion, s16, 4) + 1);
            trajectory->dy = (base.y - trajectory->y) >> (FIELD(motion, s16, 4) + 1);
            return_dz = (base.z - trajectory->z) >> (FIELD(motion, s16, 4) + 1);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            next_state = 3;
            trajectory->dz = return_dz;
        } else {
            next_state = FIELD(motion, u16, 0) + 1;
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
        s32 base_angle = FIELD(motion, u16, 6) + 0x400;
        s32 quotient;
        s32 remainder;

        if (random_angle < 0) {
            biased_angle = random_angle + 0x7FF;
        }
        quotient = biased_angle >> 11;
        remainder = random_angle - (quotient << 11);
        FIELD(motion, u16, 6) = base_angle + remainder;
    }
    {
        s32 random_angle = func_80069EF8();
        s32 biased_angle = random_angle;
        s32 base_angle = FIELD(motion, u16, 8) + 0x400;
        s32 quotient;
        s32 remainder;

        if (random_angle < 0) {
            biased_angle = random_angle + 0x7FF;
        }
        quotient = biased_angle >> 11;
        remainder = random_angle - (quotient << 11);
        FIELD(motion, u16, 8) = base_angle + remainder;
    }

    elevation_factor = func_800644B8(FIELD(motion, s16, 6));
    azimuth_factor = func_800644B8(FIELD(motion, s16, 8));
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    elevation_factor >>= 4;
    azimuth_factor >>= 4;
    trajectory->x = FIELD(motion, s32, 0x28) + ((elevation_factor * azimuth_factor) << 5);
    elevation_factor = func_800644B8(FIELD(motion, s16, 6));
    azimuth_factor = func_80064584(FIELD(motion, s16, 8));
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    elevation_factor >>= 4;
    azimuth_factor >>= 4;
    trajectory->y = FIELD(motion, s32, 0x2C) + ((elevation_factor * azimuth_factor) << 5);
    trajectory->z = FIELD(motion, s32, 0x30) + ((func_80064584(FIELD(motion, s16, 6)) >> 4) << 13);

    if (FIELD(motion, s16, 2) < 8) {
        goto call_helper;
    }
    {
        void *actor = FIELD(motion, void *, 0x40);
        if (FIELD(actor, u8, 0xAE) == 2) {
            void *source = FIELD(motion, void *, 0x4C);
            func_8009C12C(source, FIELD(motion, void *, 0x48),
                          FIELD(source, s16, 0x2A), FIELD(actor, s16, 0xAC));
        }
    }
    trajectory->dx = (base.x - trajectory->x) >> (FIELD(motion, s16, 4) + 1);
    trajectory->dy = (base.y - trajectory->y) >> (FIELD(motion, s16, 4) + 1);
    trajectory->dz = (base.z - trajectory->z) >> (FIELD(motion, s16, 4) + 1);
    FIELD(motion, u16, 2) = 0;

    next_state = FIELD(motion, u16, 0) + 1;
commit_state:
    FIELD(motion, u16, 0) = next_state;
call_helper:
    func_80175A90(&base, trajectory);
    goto finish;
}

state3:
{
    if (FIELD(motion, s16, 2) < FIELD(motion, s16, 4)) {
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
        void *actor = FIELD(motion, void *, 0x48);
        u16 flags = FIELD(actor, u16, 0x14);
        if (!(flags & 0x800)) {
            goto finish;
        }
        FIELD(actor, u16, 0x14) = flags & 0xF7FF;
    }
    FIELD(motion, u16, 0)++;
    FIELD(motion, u16, 2) = 0;
}

state4:
{
    void *actor = FIELD(motion, void *, 0x48);
    if (FIELD(actor, void *, 0x2C) != &D_80175F68) {
        FIELD(motion, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
    FIELD(actor, u16, 0x14) &= 0xF7FF;
    trajectory->x = base.x;
    trajectory->y = base.y;
    trajectory->z = base.z;
}

finish:
    if (FIELD(motion, s16, 0) != 0) {
        func_800C77D0((u8 *)motion - 0x20, trajectory, 8, 0x300);
    }
#undef delta
#undef base
}
