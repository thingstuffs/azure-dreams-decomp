#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define arg0 in0
#define arg1 in1
#define arg2 arg2_reg
#define arg3 arg3_reg

extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A6D30(void);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern u8 D_8006DE24[0x200];
extern u8 *D_800814A8[3];
extern s16 D_80083228[2];
extern u8 D_80083460[0x20];
extern s32 D_8008346C[3];
extern u8 D_80083498[0x10];
extern u8 D_80045340[0x10];
extern u8 D_800DEA68[0x20];
extern u8 D_80170E68[0x10];
extern void *D_80170838[];
extern u8 D_80173EC0[0x10];
extern u8 D_80174194[0x10];

void func_80172840(void *in0, void *in1, void *in2, void *in3)
{
    s32 index;
    register s32 one ASM_REG("$5");
    u8 *selector;
    s32 phase;
    register s32 special;
    register s32 early_s1 ASM_REG("$17");
    u16 local_values[7];
    volatile s32 xbase;
    s32 ybase;
    void *base;
    register s32 x ASM_REG("$2");
    register s32 y ASM_REG("$3");
    void *status;
    s32 i;
    void *spawn;
    u16 first_x;
    u16 first_dx;
    register u16 second_y ASM_REG("$2");
    register u16 second_dy ASM_REG("$3");
    register u16 third_z ASM_REG("$3");
    register u16 third_dz ASM_REG("$4");
    register s32 color ASM_REG("$6");
    register s32 base_value ASM_REG("$2");
    register u8 *spawn_fields ASM_REG("$5");
    register u32 heading ASM_REG("$2");
    register u8 *xptr ASM_REG("$3");
    register s32 xvalue ASM_REG("$3");
    register u8 *yptr ASM_REG("$2");
    register u8 *yaddr ASM_REG("$4");
    register void *arg2_reg ASM_REG("$20") = in2;
    register void *arg3_reg ASM_REG("$19") = in3;
    ASM_KEEP_NV(arg3);
    ASM_KEEP4_NV(arg2, arg3, early_s1, heading);
    xptr = D_8006CCD8;
    ASM_USE_NV(xptr);
    ASM_KEEP(arg2_reg);

    {
        heading = FIELD(arg3, u16, 0x2A);
        ASM_SCHED_BARRIER();
        one = 1;
        ASM_KEEP_NV(one);
        i = heading >> 8;
        index = i & 0xE;
        xptr = index + xptr;
        ASM_SCHED_BARRIER();
        yptr = (u8 *)D_8006CCE8;
        ASM_KEEP(yptr);
        xvalue = *(s16 *)xptr;
        ASM_KEEP_NV(xvalue);
        yaddr = (u8 *)((unsigned long)index + (unsigned long)yptr);
        ASM_KEEP_NV(yaddr);
        xbase = xvalue;
    }
    phase = FIELD(arg0, u8, 0x9B);
    ybase = *(s16 *)yaddr;
    ASM_SCHED_BARRIER();
    special = 0;

    if (phase == one) {
        goto state_1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_0;
        }
        goto done;
    }
    if (phase == 2) {
        goto state_2;
    }
    goto done;

state_0:
{
    s32 kind;
    void *move_object;
    register s32 special_test ASM_REG("$2");

    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        u32 swi = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        static void *const switch_keep[] = {
            &&special_3, &&special_2, &&special_1, &&kind_none,
            &&special_3, &&special_2, &&special_1
        };

        if (swi >= 7) {
            goto kind_none;
        }
        (void)switch_keep;
        goto *D_80170838[swi];

special_3:
        special = 1;
        goto kind_3;
special_2:
        special = 1;
        goto kind_2;
special_1:
        special = 1;
        goto kind_1;
    }

    kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    if (kind == 2) {
        goto kind_2;
    }
    if (kind < 3) {
        if (kind == one) {
            goto kind_1;
        }
        selector = 0;
        goto have_selector;
    }
    if (kind != 3) {
        selector = 0;
        goto have_selector;
    }

kind_3:
    selector = (u8 *)arg3 + 0x0E;
    goto have_selector;
kind_2:
    selector = (u8 *)arg3 + 0x0B;
    goto have_selector;
kind_1:
    selector = (u8 *)arg3 + 8;
    goto have_selector;
kind_none:
    selector = 0;

have_selector:
    if (*selector != 0) {
        FIELD(arg0, u16, 0x98) &= 0xFF7F;
        ASM_SCHED_BARRIER();
        special_test = special;
        if (special_test != 0) {
            move_object = D_800814A8[0];
            FIELD(arg3, void *, 0x60) = move_object;
            goto copy_record;
        }
        if (D_8006DE24[(*selector * 20) + 0x12] == 2) {
            move_object = FIELD(arg3, void *, 0x60);
            if (move_object != 0) {
copy_record:
                {
                    register void *record ASM_REG("$3") =
                        FIELD(move_object, void *, -0x14);
                    ASM_KEEP(record);
                    FIELD(arg3, u8, 0x72) = FIELD(record, u8, 0x24);
                    ASM_CLOBBER("$4");
                    FIELD(arg3, u8, 0x73) = FIELD(record, u8, 0x25);
                }
            }
            goto apply_move;
        }
        FIELD(arg3, void *, 0x60) = func_800A05A4(
            arg3,
            FIELD(arg2, u8, 0x24),
            FIELD(arg2, u8, 0x25),
            FIELD(arg3, s16, 0x2A),
            0x10);
        x = FIELD(arg3, s8, 0x72);
        y = FIELD(arg3, s8, 0x73);
        ASM_USE2(x, y);
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        FIELD(arg3, u8, 0x72) = x;
        FIELD(arg3, u8, 0x73) = y;

apply_move:
        local_values[0] = FIELD(arg1, u16, 2);
        local_values[1] = FIELD(arg1, u16, 6);
        local_values[2] = FIELD(arg1, u16, 0xA);
        if (func_800A94A0(arg3, selector, special,
                          (u8 *)arg0 + 0x98) == 0) {
            goto done;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x703);
        FIELD(arg0, s16, 0xA8) = -1;
        FIELD(arg0, u8, 0x9B)++;
        goto done;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C[0] = 0;
    FIELD(D_800814A8[0], u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_80170E68;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto done;
}

state_1:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto done;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_2:
    if (FIELD(arg2, s8, 4) == 1 &&
        (FIELD(arg2, u16, 0x14) & 0x1000)) {
        FIELD(arg0, u16, 0xA8) = 4;
    }
    if ((u32)(FIELD(arg2, u8, 4) - 1) < 2U &&
        FIELD(arg2, void *, 0x2C) != D_80174194) {
        if (func_8003DE58(
                (s32)FIELD(arg2, void *, 8), arg2, &local_values[4], 1) == 0) {
            local_values[6] = 0;
            local_values[5] = 0;
            local_values[4] = 0;
        }
        FIELD(arg0, u16, 0xA8)--;
        if ((s16)FIELD(arg0, u16, 0xA8) >= 0) {
            i = 9;
            base = D_800DEA68;
            for (; i >= 0; i--) {
                register void *data ASM_REG("$16");
                spawn = func_8003FD64(0x312, D_80083498);
                if (spawn != 0) {
                    func_8004491C(spawn, D_80045340);
                    data = FIELD(spawn, void *, 0x0C);
                    ASM_KEEP_NV(data);
                    {
                        register void *callback ASM_REG("$8");

                        callback = D_80173EC0;
                        ASM_KEEP_NV(callback);
                        FIELD(spawn, void *, 0x10) = callback;
                    }
                    {
                        register s32 random_x ASM_REG("$2");
                        register s32 origin_x ASM_REG("$3");
                        register s32 offset_x ASM_REG("$4");
                        register s32 base_x ASM_REG("$8");

                        random_x = func_800A6D30() & 0x3F;
                        origin_x = FIELD(arg1, u16, 2);
                        offset_x = local_values[4];
                        base_x = xbase;
                        ASM_USE2_NV(origin_x, offset_x);
                        ASM_USE2_NV(base_x, random_x);
                        origin_x += offset_x;
                        offset_x = base_x << 6;
                        origin_x += offset_x;
                        origin_x += random_x;
                        FIELD(FIELD(spawn, void *, 8), s16, 2) =
                            origin_x - 0x1F;
                    }
                    FIELD(FIELD(spawn, void *, 8), s16, 6) =
                        FIELD(arg1, u16, 6) + local_values[5] +
                        ((s32)ybase << 6) + (func_800A6D30() & 0x3F) - 0x1F;
                    FIELD(FIELD(spawn, void *, 8), s32, 8) = FIELD(arg1, s32, 8);
                    first_x = FIELD(arg1, u16, 2);
                    first_dx = local_values[4];
                    ASM_SCHED_BARRIER();
                    spawn_fields = (u8 *)spawn + 0x20;
                    ASM_KEEP_NV(spawn_fields);
                    FIELD(spawn_fields, s16, 0x0C) = first_x + first_dx;
                    second_y = FIELD(arg1, u16, 6);
                    second_dy = local_values[5];
                    ASM_USE2_NV(second_y, second_dy);
                    ASM_SCHED_BARRIER();
                    color = 0x700000;
                    ASM_KEEP_NV(color);
                    FIELD(spawn_fields, s16, 0x0E) = second_y + second_dy;
                    third_z = FIELD(arg1, u16, 0xA);
                    third_dz = local_values[6];
                    ASM_USE2_NV(third_z, third_dz);
                    FIELD(spawn_fields, s16, 0x48) = 4;
                    ASM_SCHED_BARRIER();
                    FIELD(spawn_fields, s16, 0x10) = third_z + third_dz;
                    FIELD(data, s16, 0x1E) = 0x600;
                    FIELD(data, s16, 0x1C) = 0x600;
                    FIELD(data, s16, 0x10) = 0x60;
                    FIELD(data, void *, 0) = base;
                    FIELD(data, u16, 0x14) |= 0xC;
                    base_value = FIELD(base, s32, 4);
                    ASM_KEEP_DEP_NV(color, base_value);
                    color |= 0x7070;
                    FIELD(data, s8, 4) = 0;
                    FIELD(data, s8, 5) = 0;
                    FIELD(data, s32, 0x0C) = color;
                    FIELD(data, s32, 8) = base_value;
                    FIELD(spawn_fields, s16, 0x4C) = 0;
                }
            }
        }
    }
    if ((FIELD(arg2, s8, 4) == 6 &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        FIELD(arg0, u16, 0x96) = 3;
        FIELD(arg0, u16, 0x98) |= 0x80;
    }
    FIELD(arg0, u16, 0x96)--;
    if ((s16)FIELD(arg0, u16, 0x96) <= 0) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
    }
    if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, void *, 0x2C) != D_80174194) {
        FIELD(arg2, void *, 0x2C) = D_80174194;
        func_80047784(
            arg2,
            D_80174194[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    status = D_80083460;
    if (FIELD(status, s32, 0x0C) != 0) {
        goto done;
    }
    FIELD(status, u16, 0x0A)--;
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, void *, 0x8C) = D_80170E68;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) > 0) {
        FIELD(arg3, u8, 0x6D)--;
    }
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
