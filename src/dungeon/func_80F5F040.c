#include "common.h"

typedef struct S_80172840_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172840_0;   /* arg3 in func_80172840 */

typedef struct S_80172840_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80172840_1;   /* arg0 in func_80172840 */

typedef struct S_80172840_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172840_2_pre;   /* the 0x14 bytes before move_object in func_80172840, addressed as move_object[-1] */

typedef struct S_80172840_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172840_3;   /* record in func_80172840 */

typedef struct S_80172840_4 {
    u8 pad_00[0x4];
    union { s8 s; u8 u; } unk_04;   /* accessed as both */
    u8 pad_05[0x3];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80172840_4;   /* arg2 in func_80172840 */

typedef struct S_80172840_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172840_5;   /* arg1 in func_80172840 */

typedef struct S_80172840_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80172840_6;   /* D_800814A8[0] in func_80172840 */

typedef struct S_80172840_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172840_7;   /* spawn in func_80172840 */

typedef struct S_80172840_8 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x36];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80172840_8;   /* spawn_fields in func_80172840 */

typedef struct S_80172840_9 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80172840_9;   /* data in func_80172840 */

typedef struct S_80172840_10 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172840_10;   /* base in func_80172840 */

typedef struct S_80172840_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172840_11;   /* status in func_80172840 */

typedef struct S_80172840_12 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
} S_80172840_12;   /* ((S_80172840_7 *)spawn)->unk_08 in func_80172840 */


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
    s32 one;
    u8 *selector;
    s32 phase;
    register s32 special;
    register s32 early_s1 ASM_REG("$17");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u16 local_values[7];
    volatile s32 xbase;
    s32 ybase;
    S_80172840_10 *base;
    register s32 x ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 y;
    S_80172840_11 *status;
    s32 i;
    void *spawn;
    u16 first_x;
    u16 first_dx;
    u16 second_y;
    u16 second_dy;
    u16 third_z;
    u16 third_dz;
    s32 color;
    s32 base_value;
    u8 *spawn_fields;
    u32 heading;
    u8 *xptr;
    s32 xvalue;
    register u8 *yptr ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *yaddr;
    register void *arg2_reg ASM_REG("$20") = in2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *arg3_reg ASM_REG("$19") = in3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP4_NV(arg2, arg3, early_s1, heading);   /* MATCH pin: retail schedule: same instructions, different order without it */
    xptr = D_8006CCD8;

    {
        heading = ((S_80172840_0 *)arg3)->unk_2A.s;
        one = 1;
        i = heading >> 8;
        index = i & 0xE;
        xptr = index + xptr;
           /* MATCH pin: keeps a statement from moving across a call/branch */
        yptr = (u8 *)D_8006CCE8;
        xvalue = *(s16 *)xptr;
        yaddr = (u8 *)((unsigned long)index + (unsigned long)yptr);
        xbase = xvalue;
    }
    phase = ((S_80172840_1 *)arg0)->unk_9B;
    ybase = *(s16 *)yaddr;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
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
    register s32 special_test ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    if (((S_80172840_0 *)arg3)->unk_1C & 0x2000) {
        u32 swi = (((S_80172840_0 *)arg3)->unk_46 & 0x3FFF) - 1;
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

    kind = ((S_80172840_0 *)arg3)->unk_46 & 0x3FFF;
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
        ((S_80172840_1 *)arg0)->unk_98 &= 0xFF7F;
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        special_test = special;
        if (special_test != 0) {
            move_object = D_800814A8[0];
            ((S_80172840_0 *)arg3)->unk_60 = move_object;
            goto copy_record;
        }
        if (D_8006DE24[(*selector * 20) + 0x12] == 2) {
            move_object = ((S_80172840_0 *)arg3)->unk_60;
            if (move_object != 0) {
copy_record:
                {
                    register void *record ASM_REG("$3") =
                        ((S_80172840_2_pre *)move_object)[-1].unk_00;
                    ((S_80172840_0 *)arg3)->unk_72.s = ((S_80172840_3 *)record)->unk_24;
                    ((S_80172840_0 *)arg3)->unk_73.s = ((S_80172840_3 *)record)->unk_25;
                }
            }
            goto apply_move;
        }
        ((S_80172840_0 *)arg3)->unk_60 = func_800A05A4(
            arg3,
            ((S_80172840_4 *)arg2)->unk_24,
            ((S_80172840_4 *)arg2)->unk_25,
            ((S_80172840_0 *)arg3)->unk_2A.u,
            0x10);
        x = ((S_80172840_0 *)arg3)->unk_72.u;
        y = ((S_80172840_0 *)arg3)->unk_73.u;
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        ((S_80172840_0 *)arg3)->unk_72.s = x;
        ((S_80172840_0 *)arg3)->unk_73.s = y;

apply_move:
        local_values[0] = ((S_80172840_5 *)arg1)->unk_02;
        local_values[1] = ((S_80172840_5 *)arg1)->unk_06;
        local_values[2] = ((S_80172840_5 *)arg1)->unk_08.at02.v;
        if (func_800A94A0(arg3, selector, special,
                          (u8 *)arg0 + 0x98) == 0) {
            goto done;
        }
        ((S_80172840_4 *)arg2)->unk_14 &= 0xF7FF;
        func_800A56E0(0x703);
        ((S_80172840_1 *)arg0)->unk_A8.s = -1;
        ((S_80172840_1 *)arg0)->unk_9B++;
        goto done;
    }

    ((S_80172840_5 *)arg1)->unk_14 = 0;
    ((S_80172840_5 *)arg1)->unk_10 = 0;
    ((S_80172840_5 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172840_4 *)arg2)->unk_24, ((S_80172840_4 *)arg2)->unk_25);
    D_8008346C[0] = 0;
    ((S_80172840_6 *)(D_800814A8[0]))->unk_A6--;
    func_800A4ACC(arg3);
    ((S_80172840_0 *)arg3)->unk_6D.s--;
    ((S_80172840_1 *)arg0)->unk_8C = D_80170E68;
    ((S_80172840_0 *)arg3)->unk_73.s = 0;
    ((S_80172840_0 *)arg3)->unk_72.s = 0;
    ((S_80172840_0 *)arg3)->unk_46 &= 0x7FFF;
    goto done;
}

state_1:
    if (func_8003F270() != 0) {
        ((S_80172840_4 *)arg2)->unk_14 |= 0x800;
        goto done;
    }
    ((S_80172840_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172840_1 *)arg0)->unk_9B++;

state_2:
    if (((S_80172840_4 *)arg2)->unk_04.s == 1 &&
        (((S_80172840_4 *)arg2)->unk_14 & 0x1000)) {
        ((S_80172840_1 *)arg0)->unk_A8.u = 4;
    }
    if ((u32)(((S_80172840_4 *)arg2)->unk_04.u - 1) < 2U &&
        ((S_80172840_4 *)arg2)->unk_2C != D_80174194) {
        if (func_8003DE58(
                (s32)((S_80172840_4 *)arg2)->unk_08, arg2, &local_values[4], 1) == 0) {
            local_values[6] = 0;
            local_values[5] = 0;
            local_values[4] = 0;
        }
        ((S_80172840_1 *)arg0)->unk_A8.u--;
        if ((s16)((S_80172840_1 *)arg0)->unk_A8.u >= 0) {
            i = 9;
            base = D_800DEA68;
            for (; i >= 0; i--) {
                register void *data ASM_REG("$16");   /* MATCH pin: retail schedule: same instructions, different order without it */
                spawn = func_8003FD64(0x312, D_80083498);
                if (spawn != 0) {
                    func_8004491C(spawn, D_80045340);
                    data = ((S_80172840_7 *)spawn)->unk_0C;
                    ASM_KEEP_NV(data);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    {
                        register void *callback ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */

                        callback = D_80173EC0;
                        ((S_80172840_7 *)spawn)->unk_10 = callback;
                    }
                    {
                        s32 random_x;
                        s32 origin_x;
                        s32 offset_x;
                        register s32 base_x ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */

                        random_x = func_800A6D30() & 0x3F;
                        origin_x = ((S_80172840_5 *)arg1)->unk_02;
                        offset_x = local_values[4];
                        base_x = xbase;
                        ASM_USE2_NV(base_x, random_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
                        origin_x += offset_x;
                        offset_x = base_x << 6;
                        origin_x += offset_x;
                        origin_x += random_x;
                        ((S_80172840_12 *)(((S_80172840_7 *)spawn)->unk_08))->unk_02 =
                            origin_x - 0x1F;
                    }
                    ((S_80172840_12 *)(((S_80172840_7 *)spawn)->unk_08))->unk_06 =
                        ((S_80172840_5 *)arg1)->unk_06 + local_values[5] +
                        ((s32)ybase << 6) + (func_800A6D30() & 0x3F) - 0x1F;
                    ((S_80172840_12 *)(((S_80172840_7 *)spawn)->unk_08))->unk_08 = ((S_80172840_5 *)arg1)->unk_08.at00.v;
                    first_x = ((S_80172840_5 *)arg1)->unk_02;
                    first_dx = local_values[4];
                    spawn_fields = (u8 *)spawn + 0x20;
                    ((S_80172840_8 *)spawn_fields)->unk_0C = first_x + first_dx;
                    second_y = ((S_80172840_5 *)arg1)->unk_06;
                    second_dy = local_values[5];
                    color = 0x700000;
                    ((S_80172840_8 *)spawn_fields)->unk_0E = second_y + second_dy;
                    third_z = ((S_80172840_5 *)arg1)->unk_08.at02.v;
                    third_dz = local_values[6];
                    ((S_80172840_8 *)spawn_fields)->unk_48 = 4;
                    ((S_80172840_8 *)spawn_fields)->unk_10 = third_z + third_dz;
                    ((S_80172840_9 *)data)->unk_1E = 0x600;
                    ((S_80172840_9 *)data)->unk_1C = 0x600;
                    ((S_80172840_9 *)data)->unk_10 = 0x60;
                    ((S_80172840_9 *)data)->unk_00 = base;
                    ((S_80172840_9 *)data)->unk_14 |= 0xC;
                    base_value = base->unk_04;
                    color |= 0x7070;
                    ((S_80172840_9 *)data)->unk_04 = 0;
                    ((S_80172840_9 *)data)->unk_05 = 0;
                    ((S_80172840_9 *)data)->unk_0C = color;
                    ((S_80172840_9 *)data)->unk_08 = base_value;
                    ((S_80172840_8 *)spawn_fields)->unk_4C = 0;
                }
            }
        }
    }
    if ((((S_80172840_4 *)arg2)->unk_04.s == 6 &&
         (((S_80172840_4 *)arg2)->unk_14 & 0x1000)) ||
        (((S_80172840_4 *)arg2)->unk_14 & 0xE000)) {
        ((S_80172840_4 *)arg2)->unk_14 |= 0x800;
        ((S_80172840_1 *)arg0)->unk_96 = 3;
        ((S_80172840_1 *)arg0)->unk_98 |= 0x80;
    }
    ((S_80172840_1 *)arg0)->unk_96--;
    if ((s16)((S_80172840_1 *)arg0)->unk_96 <= 0) {
        ((S_80172840_1 *)arg0)->unk_96 = 0;
        ((S_80172840_4 *)arg2)->unk_14 &= 0xF7FF;
    }
    if ((((S_80172840_4 *)arg2)->unk_14 & 0xE000) == 0) {
        goto done;
    }
    ((S_80172840_5 *)arg1)->unk_14 = 0;
    ((S_80172840_5 *)arg1)->unk_10 = 0;
    ((S_80172840_5 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172840_4 *)arg2)->unk_24, ((S_80172840_4 *)arg2)->unk_25);
    if (((S_80172840_4 *)arg2)->unk_2C != D_80174194) {
        ((S_80172840_4 *)arg2)->unk_2C = D_80174194;
        func_80047784(
            arg2,
            D_80174194[((D_80083228[0] + ((S_80172840_0 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
            0);
    }
    status = D_80083460;
    if (status->unk_0C != 0) {
        goto done;
    }
    status->unk_0A--;
    ((S_80172840_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172840_1 *)arg0)->unk_8C = D_80170E68;
    func_800A4ACC(arg3);
    if (((S_80172840_0 *)arg3)->unk_6D.u > 0) {
        ((S_80172840_0 *)arg3)->unk_6D.s--;
    }
    ((S_80172840_0 *)arg3)->unk_73.s = 0;
    ((S_80172840_0 *)arg3)->unk_72.s = 0;
    ((S_80172840_0 *)arg3)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
