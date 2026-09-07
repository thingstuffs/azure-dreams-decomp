/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() 0

s32 func_8003AD08();
void func_800419EC();
s32 func_80042900();
M2C_UNK func_80094E34();
s32 func_80098250();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_8009955C();
s32 func_80099734();
M2C_UNK func_80099C58();
M2C_UNK func_8009BF7C();
M2C_UNK func_8009BFF8();
void *func_8009C31C();
void *func_8009C3EC();
void *func_8009C4A4();
void *func_8009C4F4();
void *func_8009C544();
void *func_8009C57C();
void *func_8009C644();
void *func_8009C6A4();
void *func_8009C6D0(s32, s32);
void *func_8009C908();
s32 func_8009CD58();
M2C_UNK func_800A2D68();
M2C_UNK func_800A56E0();
M2C_UNK func_800A5720();
M2C_UNK func_800B4C7C();
s16 func_800B5ED0();
M2C_UNK func_800C7DEC();
s32 func_800C82B8();
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern void *D_80083470[3];
extern M2C_UNK D_800E0D7B;
extern M2C_UNK D_800E0D92;
extern M2C_UNK D_800E0D9E;
extern M2C_UNK D_800E0DB8;
extern M2C_UNK D_800E0DD0;
extern M2C_UNK D_800E0DDD;
extern M2C_UNK D_800E0DEA;
extern M2C_UNK D_800E3648;
extern void *D_800E3D7C[3];


typedef struct S_8009C12C_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    s32 unk_1C;
    union { u16 n; volatile u16 v; } unk_20;   /* accessed as both */
    u8 pad_22[0x8];
    s16 unk_2A;
    u8 pad_2C[0x20];
    u16 * unk_4C;
    u8 pad_50[0x10];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    s16 unk_88;
    u8 pad_8A[0x1C];
    s16 unk_A6;
    u8 unk_A8;
} S_8009C12C_0;   /* arg0 in func_8009C12C */

typedef struct S_8009C12C_1 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_8009C12C_1;   /* entry_page in func_8009C12C */

typedef struct S_8009C12C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8009C12C_2;   /* arg1 in func_8009C12C */

typedef struct S_8009C12C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8009C12C_3_pre;   /* the 0x14 bytes before temp_s1 in func_8009C12C, addressed as temp_s1[-1] */

typedef struct S_8009C12C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x2];
    union { u16 n; volatile u16 v; s16 n2; } unk_22;   /* accessed as both */
    u8 pad_24[0x3];
    u8 unk_27;
    u8 pad_28[0x38];
    void * unk_60;
    union { s16 n; volatile s16 v; } unk_64;   /* accessed as both */
    u8 pad_66[0x22];
    u16 unk_88;
} S_8009C12C_3;   /* temp_s1 in func_8009C12C */

typedef struct S_8009C12C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x3D66];
    void * unk_3D7C;
} S_8009C12C_4;   /* temp_ptr in func_8009C12C */

typedef struct S_8009C12C_5 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_8009C12C_5;   /* (void *)var_s0 in func_8009C12C */

typedef struct S_8009C12C_6 {
    u8 pad_00[0x3470];
    void * unk_3470;
} S_8009C12C_6;   /* var_v1 in func_8009C12C */

typedef struct S_8009C12C_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_8009C12C_7;   /* table_v0 in func_8009C12C */

void *func_8009C12C(void *arg0_in, void *arg1_in, s16 arg2, s16 arg3) {
    void *arg0 = arg0_in;
    S_8009C12C_2 *arg1 = arg1_in;
    s16 temp_v0;
    s16 temp_v0_5;
    s32 var_a2;
    s16 var_s6;
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_s0_2;
    register s32 temp_s3 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 temp_s7 ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 temp_v0_3 ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 temp_v0_6;
    s8 temp_s8;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_7;
    register s32 temp_v1_5 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_a3;
    u32 bf_arg;
    register s32 var_s0 ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 var_s2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 var_v0_2;
    s32 var_v0_3;
    register s32 var_v0_4 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_v0_5;
    u16 *temp_v0_4;
    u16 temp_v1_2;
    u16 temp_v1_4;
    register u8 temp_v0_7 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    S_8009C12C_4 *temp_ptr;
    register s16 *table_base ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s16 *table_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 table_raw ASM_REG("$12");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 table_a0 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 table_step ASM_REG("$9");   /* MATCH pin: load-bearing for the whole function shape */
    s32 table_a1;
    register s32 table_b0 ASM_REG("$10");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 table_x ASM_REG("$11");   /* MATCH pin: retail register colouring depends on it */
    s32 table_y;
    register s32 hard_zero ASM_REG("$0");   /* MATCH pin: retail register colouring depends on it */
    struct {
        volatile u16 arg2;
        u8 gap[6];
        u16 arg3;
    } homes;
    register void **var_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    void *temp_s1;
    void *var_a0;
    void *var_v0;

    var_s2 = 0;
#ifdef NON_MATCHING
    hard_zero = 0;
#endif
    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_8009C12C_0 *)arg0)->unk_73 = 0;
    ASM_KEEP(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_8009C12C_0 *)arg0)->unk_72 = 0;
    ASM_KEEP(arg2);   /* MATCH pin: keeps a statement from moving across a call/branch */
    homes.arg2 = arg2;
    temp_s1 = ((S_8009C12C_0 *)arg0)->unk_60;
    var_s6 = var_s2;
    homes.arg3 = arg3;
    if (temp_s1 == NULL) {
        S_8009C12C_1 *entry_page;
        entry_page = (void *)0x800E0000;
        var_v0 = NULL;
        if (arg0 == entry_page->unk_3D7C) {
            temp_v0 = func_800B5ED0(arg1->unk_24, arg1->unk_25, arg2, ((S_8009C12C_0 *)arg0)->unk_88);
            var_v0 = NULL;
            if (temp_v0 >= 0) {
                s32 table_a0;
                s32 table_v1;
                s32 built;
                temp_v0_3 = func_800990FC();
                built = func_8009929C(8, temp_v0_3);
                table_a0 = temp_v0 << 2;
                table_v1 = (s32)&D_800E3648;
                table_a0 += table_v1;
                built = func_8009955C(table_a0, built);
                built = func_80099194(&D_800E0D7B, built);
                func_80099290(built);
                func_800A5720(temp_v0_3);
                func_800A56E0(0x700);
                func_800A2D68(arg0, 8);
                func_800B4C7C(0x82, arg0, 8, 1);
                func_8009C908();
            }
        }
        return NULL;
    }
    temp_v0_3 = func_800990FC();
    var_s0 = temp_v0_3;
    temp_s8 = ((S_8009C12C_0 *)arg0)->unk_13;
    temp_v0_7 = *(volatile u8 *)((s8 *)arg0 + 0x13);
    if (temp_s8 >= 0) {
        temp_ptr = ((S_8009C12C_3_pre *)temp_s1)[-1].unk_00;
        temp_v1_2 = temp_ptr->unk_14;
        if (!(arg1->unk_14 & temp_v1_2 & 0x8000) || ((temp_v0_7 == 0x23) && (((S_8009C12C_0 *)arg0)->unk_A6 != 0) && !(temp_v1_2 & 0x8000))) {
            var_s0 = func_8009929C(0xA, func_80099194(&D_800E0D92, func_80099734(arg0, temp_v0_3)));
            ASM_TAILSLOT_PIN_TIED(var_s0);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_8009C31C();
        }
        temp_v1_3 = ((S_8009C12C_0 *)arg0)->unk_14.s32 & 0x4000;
        if ((temp_v1_3 != 0) || (var_s6 = -1, ((((S_8009C12C_3 *)temp_s1)->unk_14 & 0x4000) != 0))) {
            var_a0 = temp_s1;
            if (temp_v1_3 != 0) {
                var_a0 = arg0;
            }
            var_s0 = func_80099194(&D_800E0D9E, func_80099734(var_a0, var_s0));
            var_s6 = 1;
        }
        goto block_17;
    }
block_17:
    ((S_8009C12C_3 *)temp_s1)->unk_14 = (s32) (((S_8009C12C_3 *)temp_s1)->unk_14 | 0x01000000);
    if (((S_8009C12C_0 *)arg0)->unk_14.s32 & 0x04000000) {
        func_800B4C7C(3, temp_s1, -1, 0);
        if (((S_8009C12C_0 *)arg0)->unk_13 >= 0) {
            var_v0_5 = var_s6 << 16;
            var_s2 = var_v0_5 >> 16;
            if (var_s2 == 0) {
                var_s0 = func_80099194(&D_800E0DB8, func_80099734(temp_s1, var_s0));
            }
            var_v0 = NULL;
            if (var_s2 >= 0) {
                func_80099290(var_s0);
                func_800A5720(temp_v0_3);
                func_8009C908();
                return (void *)hard_zero;
            }
            return var_v0;
        }
        func_8009C908();
        return (void *)hard_zero;
    }
    temp_v0_4 = ((S_8009C12C_0 *)arg0)->unk_4C;
    if ((temp_v0_4 != NULL) && (*temp_v0_4 == 0xF0D)) {
        ((S_8009C12C_3 *)temp_s1)->unk_22.n = ((S_8009C12C_3 *)temp_s1)->unk_27;
        return func_8009C3EC();
    }
    ((S_8009C12C_3 *)temp_s1)->unk_22.v = (u16) (((S_8009C12C_3 *)temp_s1)->unk_27 + func_80098250(temp_s1));
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    if ((func_80042900(temp_s1, 0xA) << 0x10) != 0) {
        ((S_8009C12C_3 *)temp_s1)->unk_22.n = (u16) ((s32) (((S_8009C12C_3 *)temp_s1)->unk_22.n << 0x10) >> 0x11);
    }
    {
        s16 field_22 = ((S_8009C12C_3 *)temp_s1)->unk_22.n2;
        u16 field_22_u = ((S_8009C12C_3 *)temp_s1)->unk_22.v;
        if (field_22 == 0) {
            ((S_8009C12C_3 *)temp_s1)->unk_22.n = (u16) (field_22_u + 1);
        }
    }
    temp_s7 = func_8009CD58(arg0, 7, 1);
    temp_s3 = func_8009CD58(temp_s1, 7, 0);
    if (temp_s7 & 1) {
        if ((func_80042900(temp_s1, 0x13) << 0x10) != 0) {
            ((S_8009C12C_0 *)arg0)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)arg0)->unk_20.n << 0x10) >> 0x12);
            return func_8009C4A4();
        }
        if (temp_s3 & 4) {
            var_s2 += 1;
        }
        var_v0_2 = temp_s3 & 2;
        if (var_v0_2) {
            var_s2 -= 2;
            goto block_41;
        }
        goto block_42;
    }
block_41:
block_42:
    var_v0_2 = temp_s7 & 2;
    if (var_v0_2 != 0) {
        if ((func_80042900(temp_s1, 0x14) << 0x10) != 0) {
            ((S_8009C12C_0 *)arg0)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)arg0)->unk_20.n << 0x10) >> 0x12);
            return func_8009C4F4();
        }
        if (temp_s3 & 1) {
            var_s2 += 1;
        }
        var_v0_3 = temp_s3 & 4;
        if (var_v0_3) {
            var_s2 -= 2;
            goto block_50;
        }
        goto block_51;
    }
block_50:
block_51:
    var_v0_3 = temp_s7 & 4;
    if (var_v0_3 != 0) {
        if ((func_80042900(temp_s1, 0x12) << 0x10) != 0) {
            ((S_8009C12C_0 *)arg0)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)arg0)->unk_20.n << 0x10) >> 0x12);
            return func_8009C544();
        }
        var_v0_3 = temp_s3 & 2;
        if (var_v0_3) {
            var_s2 += 1;
        }
        var_v0_3 = temp_s3 & 1;
        if (var_v0_3) {
            var_s2 -= 2;
        }
        goto block_59;
    }
block_59:
    temp_v0_5 = (u16) ((S_8009C12C_0 *)arg0)->unk_88 - ((S_8009C12C_3 *)temp_s1)->unk_88;
    if (temp_v0_5 >= 0x20) {
        var_s2 -= 1;
        ASM_TAILSLOT_PIN_TIED(var_s2);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_8009C57C();
    }
    var_v0_4 = temp_v0_5 < -0x1F;
    if (var_v0_4 == 0) {
        var_v0_4 = var_s2 << 0x10;
    } else {
        var_s2 += 1;
        var_v0_4 = var_s2 << 0x10;
    }
    {
        s32 first_lhs;
        register s32 first_product ASM_REG("$12");   /* MATCH pin: load-bearing for the whole function shape */
        u16 first_current;
        register void *first_call_arg ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
        first_lhs = (s16)((S_8009C12C_0 *)arg0)->unk_20.n;
        ASM_KEEP(first_lhs);   /* MATCH pin: retail register colouring depends on it */
        first_product = first_lhs * (var_v0_4 >> 0x10);
        first_call_arg = arg0;
        first_current = ((S_8009C12C_0 *)arg0)->unk_20.v;
        ASM_KEEP4(first_call_arg, first_current, first_product, first_lhs);   /* MATCH pin: load-bearing for the whole function shape */
        first_lhs = first_product >> 3;
        ((S_8009C12C_0 *)arg0)->unk_20.n = (u16)(first_current + first_lhs);
        temp_v0_6 = func_800C82B8(first_call_arg);
    }
    if (temp_v0_6 != 0) {
        u16 second_current;
        register s32 second_scaled ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 second_product ASM_REG("$12");   /* MATCH pin: load-bearing for the whole function shape */
        second_current = ((S_8009C12C_0 *)arg0)->unk_20.n;
        second_scaled = (s32)(second_current << 0x10) >> 0x13;
        second_product = second_scaled * temp_v0_6;
        ((S_8009C12C_0 *)arg0)->unk_20.n = (u16)(second_current + second_product);
    }
    if (((S_8009C12C_0 *)arg0)->unk_1C & 0x01000000) {
        temp_v1 = (s32) ((s16) ((S_8009C12C_3 *)temp_s1)->unk_22.n - (s16) ((S_8009C12C_0 *)arg0)->unk_20.n) / 2;
        temp_v1_7 = (s32) ((s16) temp_v1 + ((u32) (temp_v1 << 0x10) >> 0x1F)) >> 1;
        ((S_8009C12C_3 *)temp_s1)->unk_64.n = (s16) (temp_v1 + temp_v1_7);
        return func_8009C644(temp_v1_7);
    }
    ((S_8009C12C_3 *)temp_s1)->unk_64.v = (s16) ((s32) ((s16) ((S_8009C12C_3 *)temp_s1)->unk_22.n - (s16) ((S_8009C12C_0 *)arg0)->unk_20.n) / 2);
    if (((S_8009C12C_3 *)temp_s1)->unk_64.n >= 0) {
        ((S_8009C12C_3 *)temp_s1)->unk_64.n = -1;
    }
    var_s2 = func_80042900(temp_s1, 0x1D);
    var_v0_5 = var_s6 << 0x10;
    if (var_v0_5 == 0) {
        var_s0 = func_80099734(temp_s1, var_s0);
        if (((S_8009C12C_0 *)arg0)->unk_14.s32 & 0x2000) {
            void *c6a4_arg = &D_800E0DD0;
            ASM_TAILSLOT_PIN_TIED(c6a4_arg);   /* MATCH pin: retail basic-block layout depends on it */
            return func_8009C6A4(c6a4_arg);
        }
        var_s0 = func_80099194(&D_800E0DDD, var_s0);
        if ((var_s2 << 0x10) != 0) {
            return func_8009C6D0(0, var_s0);
        }
        {
            s32 ad08_a0 = 0 - ((S_8009C12C_3 *)temp_s1)->unk_64.n;
            register s32 ad08_a1 ASM_REG("$5") = var_s0;   /* MATCH pin: load-bearing for the whole function shape */
            ASM_USE2(ad08_a0, ad08_a1);   /* MATCH pin: retail keeps a computation the compiler would drop */
            var_s0 = func_8003AD08(ad08_a0, ad08_a1);
        }
        ASM_KEEP(var_s0);   /* MATCH pin: retail delay-slot fill depends on it */
        var_s0 = func_80099194(&D_800E0DEA, var_s0);
        ASM_KEEP(var_s6);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        var_v0_5 = var_s6 << 0x10;
        goto block_79;
    }
block_79:
    if (var_v0_5 >= 0) {
        func_80099290(var_s0);
        func_800A5720(temp_v0_3);
    }
    {
        register u16 late_arg3 ASM_REG("$12");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 late_signed ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 late_one;
        late_arg3 = *(volatile u16 *)&homes.arg3;
        late_one = 1;
        late_signed = (s16)late_arg3;
        if (late_signed == late_one) {
            func_800C7DEC(arg0, temp_s1);
        }
    }
    bf_arg = 0xDFFFFFFF;
    temp_ptr = (void *)0x800E0000;
    ASM_KEEP_DEP_NV(temp_ptr, bf_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s0_2 = ((S_8009C12C_3 *)temp_s1)->unk_1C & bf_arg;
    temp_ptr = temp_ptr->unk_3D7C;
    ((S_8009C12C_3 *)temp_s1)->unk_1C = temp_s0_2;
    if (temp_s1 == temp_ptr) {
        func_8009BFF8(temp_s1, arg0);
    }
    var_v0_5 = var_s2 << 0x10;
    var_a2 = 0;
    if (var_v0_5 == 0) {
        var_v0_5 = 0 - (u16) ((S_8009C12C_3 *)temp_s1)->unk_64.n;
        var_v0_5 <<= 0x10;
        var_a2 = var_v0_5 >> 0x10;
    }
    func_800B4C7C(3, temp_s1, var_a2, 0);
    var_s0 = 0x800E0000;
    ASM_KEEP(var_s0);   /* MATCH pin: retail delay-slot fill depends on it */
    var_v1 = (void **)0x80080000;
    if (temp_s1 == ((S_8009C12C_5 *)((void *)var_s0))->unk_3D7C) {
        func_80094E34();
        var_v1 = (void **)0x80080000;
    }
    ((S_8009C12C_3 *)temp_s1)->unk_60 = arg0;
    ((S_8009C12C_0 *)arg0)->unk_60 = temp_s1;
    ((S_8009C12C_6 *)var_v1)->unk_3470 = temp_s1 - 0x20;
    if (((S_8009C12C_0 *)arg0)->unk_1C & 0x01000000) {
        register s32 bf_four ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
        func_800A56E0(0x700);
        bf_arg = ((S_8009C12C_0 *)arg0)->unk_14.u16;
        bf_four = 4;
        bf_arg &= 0x2000;
        bf_arg <<= 0x10;
        ASM_KEEP(bf_arg);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        bf_arg >>= 0x10;
        func_8009BF7C(bf_arg, bf_four);
    }
    func_800A56E0(0x601);
    if (!(arg1->unk_14 & 0x8000)) {
        func_800419EC(8, 0x10);
    }
    var_a3 = temp_s7 << 0x10;
    if (arg0 == ((S_8009C12C_5 *)((void *)var_s0))->unk_3D7C) {
        if (((S_8009C12C_0 *)arg0)->unk_A8 != 0) {
            return temp_s1;
        }
    }
    var_a3 = temp_s7 << 0x10;
    var_a3 >>= 0x10;
    table_base = (s16 *)0x80070000;
    ASM_KEEP(table_base);
    table_raw = homes.arg2;
    table_base = (s16 *)((s32)table_base - 0x3328);
    temp_v1_5 = (table_raw >> 9) & 7;
    temp_a2 = temp_v1_5 * 2;
    table_v0 = (s16 *)(temp_a2 + (s32)table_base);
    ASM_KEEP(table_v0);
    temp_v1_5 = (temp_v1_5 + 4) & 7;
    temp_v1_5 *= 2;
    table_base = (s16 *)(temp_v1_5 + (s32)table_base);
    table_raw = homes.arg3;
    ASM_KEEP(table_raw);
    table_a0 = *table_v0;
    table_v0 = (s16 *)0x80070000;
    ASM_KEEP(table_v0);
    table_step = (s16)table_raw;
    table_x = table_a0 * table_step;
    table_v0 = (s16 *)((s32)table_v0 - 0x3318);
    temp_a2 += (s32)table_v0;
    temp_v1_5 += (s32)table_v0;
    table_a1 = *table_base;
    table_y = arg1->unk_25;
    table_b0 = *(s16 *)temp_a2;
    table_v0 = (s16 *)((S_8009C12C_0 *)arg0)->unk_60;
    temp_v1_5 = *(s16 *)temp_v1_5;
    table_a1 <<= 5;
    table_a1 += 0x20;
    temp_v1_5 <<= 5;
    temp_v1_5 += 0x20;
    table_a0 = arg1->unk_24;
    temp_a2 = ((S_8009C12C_7 *)table_v0)->unk_88 - 0x30;
    temp_a2 = (s16)temp_a2;
    table_v0 = (s16 *)(s32)((S_8009C12C_0 *)arg0)->unk_2A;
    table_a0 += table_x;
    table_a0 <<= 6;
    table_a0 += table_a1;
    table_a0 = (s16)table_a0;
    table_step = table_b0 * table_step;
    table_y += table_step;
    table_y <<= 6;
    table_y += temp_v1_5;
    table_y = (s16)table_y;
    func_80099C58(table_a0, table_y, temp_a2, var_a3, (s32)table_v0);
    ASM_SET(table_b0);
    return temp_s1;
}
