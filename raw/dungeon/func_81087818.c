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

void func_80175018(void *arg0, Vec3Work *arg1, void *arg2)
{
    LocalWork local;
#define base local.base
#define delta local.delta
    register s32 next_state ASM_REG("$2");
    u32 swi;
    static void *const sw_keep[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4
    };

    FIELD(arg0, u16, 2)++;
    func_800478B8(arg2);

    base = *FIELD(arg0, Vec3Work *, 0x44);
    delta[0] = delta[1] = delta[2] = 0;
    {
        void *actor = FIELD(arg0, void *, 0x48);
        if ((FIELD(actor, u16, 0x14) & 0x9FFF) == 0 &&
            func_8003DE58(FIELD(actor, void *, 8), actor, delta, 3) != 0) {
            FIELD(&base, u16, 2) += delta[0];
            FIELD(&base, u16, 6) += delta[1];
            FIELD(&base, u16, 0xA) += delta[2];
            FIELD(arg0, u16, 0xA) = delta[0];
            FIELD(arg0, u16, 0xC) = delta[1];
            FIELD(arg0, u16, 0xE) = delta[2];
        } else {
            FIELD(&base, u16, 2) += FIELD(arg0, u16, 0xA);
            FIELD(&base, u16, 6) += FIELD(arg0, u16, 0xC);
            FIELD(&base, u16, 0xA) += FIELD(arg0, u16, 0xE);
        }
    }

    swi = (u32)FIELD(arg0, s16, 0);
    if (swi >= 5) {
        goto finish;
    }
    (void)sw_keep;
    goto *D_80170888[swi];

state0:
{
    void *actor = FIELD(arg0, void *, 0x40);
    void *source;
    register s32 base_x ASM_REG("$3");
    register s32 base_y ASM_REG("$4");
    register s32 diff1_x ASM_REG("$2");
    register s32 diff1_y ASM_REG("$3");
    register u32 value ASM_REG("$4");
    s16 *direction_table;
    s32 actor_coord;

    FIELD(arg0, s32, 0x28) = FIELD(arg0, s32, 0x2C) = FIELD(arg0, s32, 0x30) = 0;
    FIELD(arg0, s32, 0x34) = FIELD(arg0, s32, 0x38) = FIELD(arg0, s32, 0x3C) = 0;
    switch (FIELD(actor, u8, 0xAE)) {
    case 1:
        source = FIELD(arg0, void *, 0x4C);
        actor_coord = FIELD(actor, s16, 0xA8);
        value = FIELD(source, u16, 0x2A);
        ASM_SCHED_BARRIER();
        direction_table = D_8006CCD8;
        value = (value >> 8) & 0xE;
        ASM_KEEP(value);
        FIELD(arg0, s16, 0x2A) =
            (actor_coord * 64) +
            ((*(s16 *)((u8 *)direction_table + value) + 1) * 32);
        FIELD(arg0, s16, 0x2E) =
            (FIELD(FIELD(arg0, void *, 0x40), s16, 0xAA) * 64) +
            ((*(s16 *)((u8 *)D_8006CCE8 + value) + 1) * 32);
        FIELD(arg0, u16, 0x32) = FIELD(&base, u16, 0xA);

        ASM_SCHED_BARRIER();
        diff1_x = FIELD(arg0, s16, 0x2A);
        ASM_KEEP(diff1_x);
        base_x = FIELD(&base, s16, 2);
        base_y = FIELD(&base, s16, 6);
        diff1_x -= base_x;
        if (diff1_x < 0) {
            diff1_x = -diff1_x;
        }
        ASM_KEEP(diff1_x);
        delta[0] = diff1_x;
        diff1_y = FIELD(arg0, s16, 0x2E) - base_y;
        if (diff1_y < 0) {
            diff1_y = -diff1_y;
        }
        ASM_KEEP(diff1_y);
        delta[1] = diff1_y;
        FIELD(arg0, s16, 4) = delta[0];
        if (FIELD(arg0, s16, 4) < (s16)delta[1]) {
            FIELD(arg0, u16, 4) = delta[1];
        }
        FIELD(arg0, s16, 4) = (s16)FIELD(arg0, u16, 4) >> 5;
        if (FIELD(arg0, s16, 4) == 0) {
            FIELD(arg0, u16, 4) = 1;
        }
        arg1->dx = FIELD(arg0, s32, 0x28) - base.x;
        arg1->dy = FIELD(arg0, s32, 0x2C) - base.y;
        arg1->dz = 0;
        break;

    case 2:
    {
        s32 *position;
        void *node;
        s32 i = 1;
        register s32 diff_x ASM_REG("$4");
        s32 diff_y;
        register s32 diff_z ASM_REG("$2");
        register u8 *delta_scan ASM_REG("$5");
        s32 case2_base_x;
        s32 case2_base_y;
        s32 case2_base_z;
        s32 height;
        s32 position_z;

        ASM_USE_NV(i);
        node = FIELD(FIELD(arg0, void *, 0x4C), void *, 0x60);
        position = FIELD(node, s32 *, -0x18);
        FIELD(arg0, s32, 0x28) = position[0];
        FIELD(arg0, s32, 0x2C) = position[1];
        height = D_800DDC40[FIELD(FIELD(FIELD(arg0, void *, 0x4C), void *, 0x60), u8, 0x13)];
        position_z = position[2];
        ASM_SCHED_BARRIER();
        diff_x = FIELD(arg0, s16, 0x2A);
        FIELD(arg0, s32, 0x30) = position_z - (height << 15);

        case2_base_x = FIELD(&base, s16, 2);
        case2_base_y = FIELD(&base, s16, 6);
        ASM_KEEP_NV(diff_x);
        diff_x -= case2_base_x;
        if (diff_x < 0) {
            diff_x = -diff_x;
        }
        delta[0] = diff_x;
        diff_y = FIELD(arg0, s16, 0x2E) - case2_base_y;
        if (diff_y < 0) {
            diff_y = -diff_y;
        }
        delta[1] = diff_y;
        diff_z = FIELD(arg0, s16, 0x32);
        case2_base_z = FIELD(&base, s16, 0xA);
        ASM_SCHED_BARRIER();
        delta_scan = (u8 *)&base + 2;
        ASM_USE_NV(delta_scan);
        ASM_KEEP_NV(diff_z);
        diff_z -= case2_base_z;
        if (diff_z < 0) {
            diff_z = -diff_z;
        }
        delta[2] = diff_z;

        FIELD(arg0, s16, 4) = delta[0];
        for (i = 1; i < 3; i++, delta_scan += 2) {
            if (FIELD(delta_scan, s16, 0x18) > FIELD(arg0, s16, 4)) {
                FIELD(arg0, u16, 4) = FIELD(delta_scan, u16, 0x18);
            }
        }
        FIELD(arg0, s16, 4) = (s16)FIELD(arg0, u16, 4) >> 5;
        if (FIELD(arg0, s16, 4) == 0) {
            FIELD(arg0, u16, 4) = 1;
        }
        arg1->dx = FIELD(arg0, s32, 0x28) - base.x;
        arg1->dy = FIELD(arg0, s32, 0x2C) - base.y;
        arg1->dz = FIELD(arg0, s32, 0x30) - base.z;
        break;
    }
    case 0:
    default:
        break;
    }

    arg1->x = base.x;
    arg1->y = base.y;
    arg1->z = base.z;
    FIELD(arg0, u16, 0)++;
    FIELD(arg0, u16, 2) = 0;
    goto finish;
}

state1:
{
    arg1->dx /= 2;
    arg1->dy /= 2;
    arg1->dz /= 2;
    arg1->x += arg1->dx;
    arg1->y += arg1->dy;
    arg1->z += arg1->dz;
    if (FIELD(arg0, s16, 2) < FIELD(arg0, s16, 4)) {
        goto call_helper;
    }

    arg1->x = FIELD(arg0, s32, 0x28);
    arg1->y = FIELD(arg0, s32, 0x2C);
    arg1->z = FIELD(arg0, s32, 0x30);
    FIELD(arg0, u16, 2) = 0;
    {
        void *actor = FIELD(arg0, void *, 0x40);
    if (FIELD(actor, u8, 0xAE) != 2) {
        s32 final_dz;

        arg1->dx = (base.x - arg1->x) >> (FIELD(arg0, s16, 4) + 1);
        arg1->dy = (base.y - arg1->y) >> (FIELD(arg0, s16, 4) + 1);
        final_dz = (base.z - arg1->z) >> (FIELD(arg0, s16, 4) + 1);
        ASM_SCHED_BARRIER();
        next_state = 3;
        arg1->dz = final_dz;
    } else {
        next_state = FIELD(arg0, u16, 0) + 1;
    }
    }
    goto commit_state;
}

state2:
{
    s32 trig_value;
    s32 trig_value2;
    {
        s32 random_value = func_80069EF8();
        s32 adjusted_value = random_value;
        s32 base_angle = FIELD(arg0, u16, 6) + 0x400;
        s32 quotient;
        s32 remainder;

        if (random_value < 0) {
            adjusted_value = random_value + 0x7FF;
        }
        quotient = adjusted_value >> 11;
        remainder = random_value - (quotient << 11);
        FIELD(arg0, u16, 6) = base_angle + remainder;
    }
    {
        s32 random_value = func_80069EF8();
        s32 adjusted_value = random_value;
        s32 base_angle = FIELD(arg0, u16, 8) + 0x400;
        s32 quotient;
        s32 remainder;

        if (random_value < 0) {
            adjusted_value = random_value + 0x7FF;
        }
        quotient = adjusted_value >> 11;
        remainder = random_value - (quotient << 11);
        FIELD(arg0, u16, 8) = base_angle + remainder;
    }

    trig_value = func_800644B8(FIELD(arg0, s16, 6));
    trig_value2 = func_800644B8(FIELD(arg0, s16, 8));
    ASM_SCHED_BARRIER();
    ASM_KEEP_NV(trig_value);
    trig_value >>= 4;
    trig_value2 >>= 4;
    arg1->x = FIELD(arg0, s32, 0x28) + ((trig_value * trig_value2) << 5);
    trig_value = func_800644B8(FIELD(arg0, s16, 6));
    trig_value2 = func_80064584(FIELD(arg0, s16, 8));
    ASM_SCHED_BARRIER();
    ASM_KEEP_NV(trig_value);
    trig_value >>= 4;
    trig_value2 >>= 4;
    arg1->y = FIELD(arg0, s32, 0x2C) + ((trig_value * trig_value2) << 5);
    arg1->z = FIELD(arg0, s32, 0x30) + ((func_80064584(FIELD(arg0, s16, 6)) >> 4) << 13);

    if (FIELD(arg0, s16, 2) < 8) {
        goto call_helper;
    }
    {
        void *actor = FIELD(arg0, void *, 0x40);
        if (FIELD(actor, u8, 0xAE) == 2) {
            void *source = FIELD(arg0, void *, 0x4C);
            func_8009C12C(source, FIELD(arg0, void *, 0x48),
                          FIELD(source, s16, 0x2A), FIELD(actor, s16, 0xAC));
        }
    }
    arg1->dx = (base.x - arg1->x) >> (FIELD(arg0, s16, 4) + 1);
    arg1->dy = (base.y - arg1->y) >> (FIELD(arg0, s16, 4) + 1);
    arg1->dz = (base.z - arg1->z) >> (FIELD(arg0, s16, 4) + 1);
    FIELD(arg0, u16, 2) = 0;

    next_state = FIELD(arg0, u16, 0) + 1;
commit_state:
    ASM_USE_NV(next_state);
    FIELD(arg0, u16, 0) = next_state;
call_helper:
    func_80175A90(&base, arg1);
    goto finish;
}

state3:
{
    if (FIELD(arg0, s16, 2) < FIELD(arg0, s16, 4)) {
        arg1->dx *= 2;
        arg1->dy *= 2;
        arg1->dz *= 2;
        arg1->x += arg1->dx;
        arg1->y += arg1->dy;
        arg1->z += arg1->dz;
        func_80175A90(&base, arg1);
        goto finish;
    }
    arg1->x = base.x;
    arg1->y = base.y;
    arg1->z = base.z;
    {
        void *actor = FIELD(arg0, void *, 0x48);
        u16 flags = FIELD(actor, u16, 0x14);
        if (!(flags & 0x800)) {
            goto finish;
        }
        FIELD(actor, u16, 0x14) = flags & 0xF7FF;
    }
    FIELD(arg0, u16, 0)++;
    FIELD(arg0, u16, 2) = 0;
}

state4:
{
    void *actor = FIELD(arg0, void *, 0x48);
    if (FIELD(actor, void *, 0x2C) != &D_80175F68) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
    FIELD(actor, u16, 0x14) &= 0xF7FF;
    arg1->x = base.x;
    arg1->y = base.y;
    arg1->z = base.z;
}

finish:
    if (FIELD(arg0, s16, 0) != 0) {
        func_800C77D0((u8 *)arg0 - 0x20, arg1, 8, 0x300);
    }
#undef delta
#undef base
}
