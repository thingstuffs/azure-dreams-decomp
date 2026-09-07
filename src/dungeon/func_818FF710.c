#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A0.h"

typedef struct { u8 bytes[8]; } Packed8 __attribute__((packed));
typedef struct { u8 bytes[12]; } Packed12 __attribute__((packed));
typedef struct { u8 bytes[32]; } Packed32 __attribute__((packed));
typedef union {
    Packed8 packed;
    s16 half[6];
} Local28;
typedef union {
    Packed32 packed;
    struct {
        s16 first;
        u16 second;
    } pair[8];
} Local38;

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80024058[];
M2C_UNK func_8002407C();          /* extern */
M2C_UNK func_800244CC(); /* extern */
M2C_UNK func_80024DB8(); /* extern */
extern void func_80025158(void) __attribute__((noreturn));
extern void func_800252B4(void) __attribute__((noreturn));
extern void func_80025DF4(void) __attribute__((noreturn));
s32 func_8003DE58();     /* extern */
void *func_8003FC64();                       /* extern */
s32 func_8004491C();           /* extern */
s16 func_80066460(); /* extern */
s32 func_80069EF8();                                /* extern */
s32 func_800A4778();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B8FC8(); /* extern */
extern Packed8 D_80024028;
extern Packed32 D_80024038;
extern M2C_UNK D_800245EC;
extern M2C_UNK D_800246F8;
extern M2C_UNK D_80024780;
extern M2C_UNK D_8002499C;
extern Packed12 D_80025E28;
extern Packed12 D_80025E34;
extern Packed12 D_80025E40;
extern Packed12 D_80025E58;
extern Packed12 D_80025E70;
extern M2C_UNK D_80025E80;
extern M2C_UNK D_80045340;
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;
extern u8 D_800DDC40[];
extern u8 D_800E3D68;


typedef struct S_818FF710_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_818FF710_0;   /* temp_s0 in func_818FF710 */

typedef struct S_818FF710_1 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_1;   /* arg2 in func_818FF710 */

typedef struct S_818FF710_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818FF710_2_pre;   /* the 0x14 bytes before temp_s7 in func_818FF710, addressed as temp_s7[-1] */

typedef struct S_818FF710_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_818FF710_2;   /* temp_s7 in func_818FF710 */

typedef struct S_818FF710_3 {
    s16 unk_00;
} S_818FF710_3;   /* &D_80025E80 in func_818FF710 */

typedef struct S_818FF710_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818FF710_4;   /* temp_a1 in func_818FF710 */

typedef struct S_818FF710_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    union { s32 i; void * p; } unk_10;   /* accessed as both */
    s32 unk_14;
} S_818FF710_5;   /* arg1 in func_818FF710 */

typedef struct S_818FF710_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818FF710_6;   /* temp_s2 in func_818FF710 */

typedef struct S_818FF710_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_818FF710_7_pre;   /* the 0x18 bytes before temp_v1_3 in func_818FF710, addressed as temp_v1_3[-1] */

typedef struct S_818FF710_7 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_7;   /* temp_v1_3 in func_818FF710 */

typedef struct S_818FF710_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818FF710_8;   /* temp_a3_case1 in func_818FF710 */

typedef struct S_818FF710_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_818FF710_9;   /* temp_a0 in func_818FF710 */

typedef struct S_818FF710_10_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818FF710_10_pre;   /* the 0x14 bytes before temp_v1_9 in func_818FF710, addressed as temp_v1_9[-1] */

typedef struct S_818FF710_10 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_10;   /* temp_v1_9 in func_818FF710 */

typedef struct S_818FF710_11 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_11;   /* temp_v1_10 in func_818FF710 */

typedef struct S_818FF710_12 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_818FF710_12;   /* temp_a0_2 in func_818FF710 */

typedef struct S_818FF710_13 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_818FF710_13;   /* temp_a3 in func_818FF710 */

typedef struct S_818FF710_14 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1E];
    void * unk_2C;
    void * unk_30;
    void * unk_34;
    void * unk_38;
    void * unk_3C;
    void * unk_40;
} S_818FF710_14;   /* temp_s1 in func_818FF710 */

typedef struct S_818FF710_15 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
} S_818FF710_15;   /* temp_s0_2 in func_818FF710 */

typedef struct S_818FF710_16 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_16;   /* temp_v1_12 in func_818FF710 */

typedef struct S_818FF710_17 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_17;   /* temp_a3_3 in func_818FF710 */

typedef struct S_818FF710_18 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_18;   /* temp_s0_4 in func_818FF710 */

typedef struct S_818FF710_19 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_19;   /* temp_v1_13 in func_818FF710 */

typedef struct S_818FF710_20 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_20;   /* temp_a3_4 in func_818FF710 */

typedef struct S_818FF710_21 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_21;   /* temp_s0_6 in func_818FF710 */

typedef struct S_818FF710_22 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_22;   /* temp_v1_14 in func_818FF710 */

typedef struct S_818FF710_23 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_23;   /* temp_a3_5 in func_818FF710 */

typedef struct S_818FF710_24 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818FF710_24;   /* temp_s0_8 in func_818FF710 */

typedef struct S_818FF710_25 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_25;   /* temp_v1_15 in func_818FF710 */

typedef struct S_818FF710_26 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF710_26;   /* temp_a3_6 in func_818FF710 */

typedef struct S_818FF710_27 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_27;   /* temp_v1_18 in func_818FF710 */

typedef struct S_818FF710_28 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_818FF710_28;   /* temp_a0_3 in func_818FF710 */


typedef struct S_818FF710_30 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FF710_30;   /* ((S_818FF710_0 *)temp_s0)->unk_0C in func_818FF710 */

typedef struct S_818FF710_31_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_818FF710_31_pre;   /* the 0x18 bytes before ((S_818FF710_2 *)temp_s7)->unk_60 in func_818FF710, addressed as ((S_818FF710_2 *)temp_s7)->unk_60[-1] */

typedef struct S_818FF710_31 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF710_31;   /* ((S_818FF710_2 *)temp_s7)->unk_60 in func_818FF710 */

typedef struct S_818FF710_32 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_818FF710_32;   /* ((S_818FF710_15 *)temp_s0_2)->unk_08 in func_818FF710 */

typedef struct S_818FF710_33 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_818FF710_33;   /* ((S_818FF710_18 *)temp_s0_4)->unk_08 in func_818FF710 */

void func_818FF710(void *arg0, void *arg1, void *arg2) {
    u16 sp20[3];
    Local28 sp28;
    Local38 sp38;
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c8 };
    s32 temp_v0_15;
    s32 temp_v1;
    s32 e80;
    void *tmp30;
    void *tmp30b;
    s32 copyw;
    s16 temp_v1_17;
    s32 temp_a3_2;
    M2C_UNK temp_v1_6;
    M2C_UNK temp_v1_7;
    M2C_UNK temp_v1_8;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_v0_2;
    s32 temp_v0;
    register void *p32 ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s8 temp_v0_4;
    u16 temp_v0_10;
    u16 temp_v0_12;
    u16 temp_v0_14;
    u16 temp_v0_16;
    u16 temp_v0_17;
    u16 temp_v0_18;
    u16 temp_v0_3;
    u16 tsp20;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_8;
    u16 temp_v1_11;
    u16 temp_v1_16;
    u16 temp_v1_19;
    u16 temp_v1_2;
    u16 temp_v1_5;
    u16 temp_parent_flags;
    u16 var_v0;
    u8 temp_v0_2;
    register s32 temp_v1_4 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 flagrl ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_a1;
    S_818FF710_9 *temp_a0;
    S_818FF710_12 *temp_a0_2;
    S_818FF710_28 *temp_a0_3;
    S_818FF710_4 *temp_a1;
    register void *temp_a3 ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *a0v4 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *a1v4;
    register void *temp_a3_case1 ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_a3_3 ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_a3_4 ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_a3_5 ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_a3_6 ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    S_818FF710_0 *temp_s0;
    S_818FF710_15 *temp_s0_2;
    S_818FF710_18 *temp_s0_4;
    register void *temp_s0_6 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register void *temp_s0_8 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    S_818FF710_14 *temp_s1;
    S_818FF710_6 *temp_s2;
    void *temp_s7;
    void *temp_v0_11;
    register void *temp_v0_13 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *temp_v0_7 ASM_REG("$22");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *temp_v0_9;
    S_818FF710_11 *temp_v1_10;
    S_818FF710_16 *temp_v1_12;
    S_818FF710_19 *temp_v1_13;
    S_818FF710_22 *temp_v1_14;
    S_818FF710_25 *temp_v1_15;
    S_818FF710_27 *temp_v1_18;
    void *temp_v1_3;
    void *temp_v1_9;

    void *arg0_reg = arg0;
    register void *arg1_reg ASM_REG("$19") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    register void *arg2_reg ASM_REG("$17") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP_NV(arg0_reg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_NV(arg2_reg);   /* MATCH pin: load-bearing for the whole function shape */
#define arg0 arg0_reg
#define arg1 arg1_reg
#define arg2 arg2_reg

    temp_s7 = (*(void **)((u8 *)arg0 + 0));
    sp28.packed = D_80024028;
    sp38.packed = D_80024038;
    temp_v1 = (*(s16 *)((u8 *)arg0 + 0xA));
    temp_s0 = temp_s7 - 0x20;
    temp_s2 = temp_s0->unk_08;
    if ((u32) temp_v1 >= 9U) {
        goto block_66;
    }
    (void)jt_keep; goto *D_80024058[(u32)(temp_v1)];
jt_c0:
    ((S_818FF710_1 *)arg2)->unk_0C.at00.v = 0x808080;
    (*(Packed12 *)((u8 *)arg0 + 0x96)) = D_80025E70;
    ((S_818FF710_1 *)arg2)->unk_08 = (void *) (arg0 + 0x96);
    temp_parent_flags = ((S_818FF710_2 *)temp_s7)->unk_2A;
    ((S_818FF710_3 *)(&D_80025E80))->unk_00 = 1;
    (*(s16 *)((u8 *)arg0 + 0x7E)) = (s16) ((temp_parent_flags >> 9) & 7);
    (*(s16 *)((u8 *)arg0 + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)arg0 + 0xA)) + 1);
jt_c1:
    temp_a1 = temp_s0->unk_0C;
    if (func_8003DE58(temp_a1->unk_08, temp_a1, &sp20[0], 0) != 0) {
        goto block_5;
    }
    if (!(((S_818FF710_30 *)(temp_s0->unk_0C))->unk_14 & 0x8000)) {
        goto block_66;
    }
block_5:
    ((S_818FF710_5 *)arg1)->unk_00.at02.v = (u16) temp_s2->unk_02;
    ((S_818FF710_5 *)arg1)->unk_04.at02.v = (u16) temp_s2->unk_06;
    temp_v1_2 = temp_s2->unk_0A;
    ((S_818FF710_5 *)arg1)->unk_08.at02.v = temp_v1_2;
    if (!(((S_818FF710_30 *)(temp_s0->unk_0C))->unk_14 & 0x8000)) {
        ((S_818FF710_5 *)arg1)->unk_00.at02.v = (u16) (((S_818FF710_5 *)arg1)->unk_00.at02.v + sp20[0]);
        ((S_818FF710_5 *)arg1)->unk_04.at02.v = (u16) (((S_818FF710_5 *)arg1)->unk_04.at02.v + sp20[1]);
        var_v0 = (u16) (((S_818FF710_5 *)arg1)->unk_08.at02.v + sp20[2]);
        ASM_TAILSLOT_PIN(var_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80025158();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    var_v0 = (u16) (temp_v1_2 - 0x40);
    ((S_818FF710_5 *)arg1)->unk_08.at02.v = var_v0;
    if ((*(u8 *)((u8 *)arg0 + 0x7A)) & 4) {
        goto block_10;
    }
    func_8004491C(arg0 - 0x20, &D_80045340);
    ((S_818FF710_1 *)arg2)->unk_10 = 0x60;
    ((S_818FF710_1 *)arg2)->unk_0C.at02.v = 0x14;
    ((S_818FF710_1 *)arg2)->unk_0C.at01.v = 0x14;
    ((S_818FF710_1 *)arg2)->unk_0C.at00u.v = 0x14;
    ((S_818FF710_1 *)arg2)->unk_1E = 0x1000;
    ((S_818FF710_1 *)arg2)->unk_1C = 0x1000;
    ((S_818FF710_1 *)arg2)->unk_14 = (u16) (((S_818FF710_1 *)arg2)->unk_14 | 0xC);
    (*(u8 *)((u8 *)arg0 + 0x7A)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x7A)) | 4);
block_10:
    if (!(*(*(u16 **)((u8 *)arg0 + 4)) & 0x80)) {
        goto block_66;
    }
    temp_v1_3 = ((S_818FF710_2 *)temp_s7)->unk_60;
    if (temp_v1_3 == NULL) {
        goto block_17;
    }
    temp_a3_case1 = ((S_818FF710_7_pre *)temp_v1_3)[-1].unk_00;
    (*(s16 *)((u8 *)arg0 + 0x78)) = (s16) (((S_818FF710_8 *)temp_a3_case1)->unk_0A - (D_800DDC40[((S_818FF710_7 *)temp_v1_3)->unk_13] + 0x40));
    temp_a0 = ((S_818FF710_2_pre *)temp_s7)[-1].unk_00;
    (*(s8 *)((u8 *)arg0 + 0xA2)) = (s8) (temp_a0->unk_24 + D_8006CCD8[(*(s16 *)((u8 *)arg0 + 0x7E)) * 2]);
    (*(s8 *)((u8 *)arg0 + 0xA3)) = (s8) (temp_a0->unk_25 + D_8006CCE8[(*(s16 *)((u8 *)arg0 + 0x7E)) * 2]);
    temp_v0 = ((S_818FF710_2 *)temp_s7)->unk_72;
    temp_v1_4 = temp_a0->unk_24;
    if (temp_v0 != temp_v1_4) {
        var_v0_2 = temp_v0 - temp_v1_4;
        goto block_14;
    }
    temp_v0 = ((S_818FF710_2 *)temp_s7)->unk_73;
    temp_v1_4 = temp_a0->unk_25;
    var_v0_2 = temp_v0 - temp_v1_4;
block_14:
    if (var_v0_2 >= 0) {
        goto block_16;
    }
    var_v0_2 = 0 - var_v0_2;
block_16:
    (*(s8 *)((u8 *)arg0 + 0x7B)) = (s8) ((var_v0_2 * 2) - 1);
    func_800252B4();
block_17:
    (*(s16 *)((u8 *)arg0 + 0x78)) = (s16) (((S_818FF710_2 *)temp_s7)->unk_88 - 0x50);
    (*(s8 *)((u8 *)arg0 + 0x7B)) = 0x20;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    ((S_818FF710_5 *)arg1)->unk_0C = (s32) (sp38.pair[(*(s16 *)((u8 *)arg0 + 0x7E))].first << 0x10);
    ((S_818FF710_5 *)arg1)->unk_10.i = (s32) (sp38.pair[(*(s16 *)((u8 *)arg0 + 0x7E))].second << 0x10);
    ((S_818FF710_5 *)arg1)->unk_14 = (s32) ((s32) (((*(s16 *)((u8 *)arg0 + 0x78)) << 0x10) - ((S_818FF710_5 *)arg1)->unk_08.at00.v) / (s8) (*(s8 *)((u8 *)arg0 + 0x7B)));
    temp_v0_2 = (u8) (*(s8 *)((u8 *)arg0 + 0x7B));
    (*(u16 *)((u8 *)arg0 + 0x82)) = 0U;
    (*(s16 *)((u8 *)arg0 + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)arg0 + 0xA)) + 1);
    (*(s16 *)((u8 *)arg0 + 0x88)) = (s16) (s8) (u8) (*(s8 *)((u8 *)arg0 + 0x7B));
    (*(s16 *)((u8 *)arg0 + 0x8A)) = (s16) ((s8) temp_v0_2 * (s8) temp_v0_2);
    func_80024DB8(arg0, arg1, arg2);
    func_80025DF4();
    return;
jt_c2:
    var_s0 = 0;
loop_20:
    var_s0 += 1;
    {
        register void *a0v ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 a1v;
        s32 a2v;
        register s32 a3v ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 rv;
        rv = func_80069EF8();
        a0v = arg0 - 0x20;
        a2v = 0x2020E0;
        ASM_KEEP_NV(a2v);   /* MATCH pin: retail schedule: same instructions, different order without it */
        a3v = (rv & 0xFF) | 0x80;
        ASM_KEEP_NV(a3v);   /* MATCH pin: retail schedule: same instructions, different order without it */
        a1v = (*(s16 *)((u8 *)arg0 + 0x7E));
        func_800244CC(a0v, a1v, a2v, a3v, 0, 0, 0);
    }
    if (var_s0 < 4) {
        goto loop_20;
    }
    temp_v1_5 = ((S_818FF710_1 *)arg2)->unk_1A;
    temp_v0_3 = temp_v1_5 + 0x190;
    ((S_818FF710_1 *)arg2)->unk_1A = temp_v0_3;
    if ((u32) (temp_v0_3 & 0xFFFF) < 0x1001U) {
        goto block_23;
    }
    ((S_818FF710_1 *)arg2)->unk_1A = (u16) (temp_v1_5 - 0xE70);
block_23:
    temp_v1_6 = ((*(s16 *)((u8 *)arg0 + 0x88)) - (*(s8 *)((u8 *)arg0 + 0x7B))) + 1;
    ((S_818FF710_1 *)arg2)->unk_0C.at00u.v = (s8) (((s32) (temp_v1_6 * temp_v1_6 * 0x6C) / (s16) (*(s16 *)((u8 *)arg0 + 0x8A))) + 0x14);
    temp_v1_7 = ((*(s16 *)((u8 *)arg0 + 0x88)) - (*(s8 *)((u8 *)arg0 + 0x7B))) + 1;
    ((S_818FF710_1 *)arg2)->unk_0C.at01.v = (s8) (((s32) (temp_v1_7 * temp_v1_7 * 0x6C) / (s16) (*(s16 *)((u8 *)arg0 + 0x8A))) + 0x14);
    temp_v1_8 = ((*(s16 *)((u8 *)arg0 + 0x88)) - (*(s8 *)((u8 *)arg0 + 0x7B))) + 1;
    ((S_818FF710_1 *)arg2)->unk_0C.at02.v = (s8) (((s32) (temp_v1_8 * temp_v1_8 * 0x6C) / (s16) (*(s16 *)((u8 *)arg0 + 0x8A))) + 0x14);
    if ((func_800A4778(((S_818FF710_5 *)arg1)->unk_00.at02.v, ((S_818FF710_5 *)arg1)->unk_04.at02.v, (s16) ((S_818FF710_5 *)arg1)->unk_08.at02.v, ((S_818FF710_2 *)temp_s7)->unk_60) << 0x10) == 0) {
        goto block_25;
    }
    (*(s16 *)((u8 *)arg0 + 0xA)) = 8;
    (*(u16 *)((u8 *)arg0 + 0x82)) = 0U;
    ((S_818FF710_1 *)arg2)->unk_0C.at02.v = 0;
    ((S_818FF710_1 *)arg2)->unk_0C.at01.v = 0;
    ((S_818FF710_1 *)arg2)->unk_0C.at00u.v = 0;
    func_80025DF4();
    return;
block_25:
    temp_v0_4 = (u8) (*(s8 *)((u8 *)arg0 + 0x7B)) - 1;
    (*(s8 *)((u8 *)arg0 + 0x7B)) = temp_v0_4;
    if ((temp_v0_4 << 0x18) > 0) {
        goto block_31;
    }
    if (((S_818FF710_2 *)temp_s7)->unk_60 == NULL) {
        goto block_30;
    }
    (*(s16 *)((u8 *)arg0 + 0xA)) = 3;
    (*(u16 *)((u8 *)arg0 + 0x82)) = 0U;
    func_800A56E0(0x300);
    temp_v1_9 = ((S_818FF710_2 *)temp_s7)->unk_60;
    temp_v1_10 = ((S_818FF710_10_pre *)temp_v1_9)[-1].unk_00;
    if ((u32) (((S_818FF710_10 *)temp_v1_9)->unk_13 - 0x33) < 4U) {
        goto block_29;
    }
    temp_v1_10->unk_14 = (u16) (temp_v1_10->unk_14 | 0x800);
    temp_a0_2 = ((S_818FF710_2 *)temp_s7)->unk_60;
    temp_a0_2->unk_14 = (s32) (temp_a0_2->unk_14 | 0x100000);
block_29:
    temp_a3 = ((S_818FF710_31_pre *)(((S_818FF710_2 *)temp_s7)->unk_60))[-1].unk_00;
    ((S_818FF710_5 *)arg1)->unk_00.at02.v = (u16) ((S_818FF710_13 *)temp_a3)->unk_02;
    ((S_818FF710_5 *)arg1)->unk_04.at02.v = (u16) ((S_818FF710_13 *)temp_a3)->unk_06;
    ((S_818FF710_5 *)arg1)->unk_08.at02.v = (u16) (*(s16 *)((u8 *)arg0 + 0x78));
    func_80024DB8(arg0, arg1, arg2, temp_a3);
    func_80025DF4();
    return;
block_30:
    (*(s16 *)((u8 *)arg0 + 0xA)) = 8;
    (*(u16 *)((u8 *)arg0 + 0x82)) = 0U;
    ((S_818FF710_1 *)arg2)->unk_0C.at02.v = 0;
    ((S_818FF710_1 *)arg2)->unk_0C.at01.v = 0;
    ((S_818FF710_1 *)arg2)->unk_0C.at00u.v = 0;
    func_80024DB8(arg0, arg1, arg2);
    func_80025DF4();
    return;
block_31:
    temp_a3 = ((S_818FF710_5 *)arg1)->unk_10.p;
    ((S_818FF710_5 *)arg1)->unk_00.at00.v = (s32) (((S_818FF710_5 *)arg1)->unk_00.at00.v + ((S_818FF710_5 *)arg1)->unk_0C);
    ((S_818FF710_5 *)arg1)->unk_04.at00.v = (s32) (((S_818FF710_5 *)arg1)->unk_04.at00.v + (s32) temp_a3);
    ((S_818FF710_5 *)arg1)->unk_08.at00.v = (s32) (((S_818FF710_5 *)arg1)->unk_08.at00.v + ((S_818FF710_5 *)arg1)->unk_14);
    func_80024DB8(arg0, arg1, arg2, temp_a3);
    func_80025DF4();
    return;
jt_c3: {
    s32 temp_fp;
    s32 cv;
    register s16 *sp28_0 ASM_REG("$20");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s16 *sp28_4 ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    register s16 *b1 ASM_REG("$5");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 *b2 ASM_REG("$6");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 c880;
    s32 c84;
    s32 c832;
    temp_v1_11 = ((S_818FF710_1 *)arg2)->unk_1A;
    temp_v0_5 = temp_v1_11 + 0x190;
    ((S_818FF710_1 *)arg2)->unk_1A = temp_v0_5;
    if ((u32) (temp_v0_5 & 0xFFFF) < 0x1001U) {
        goto block_34;
    }
    ((S_818FF710_1 *)arg2)->unk_1A = (u16) (temp_v1_11 - 0xE70);
block_34:
    func_80024DB8(arg0, arg1, arg2);
    temp_v0_6 = (*(u16 *)((u8 *)arg0 + 0x82)) + 1;
    (*(u16 *)((u8 *)arg0 + 0x82)) = temp_v0_6;
    if ((s16) temp_v0_6 != 1) {
        goto block_36;
    }
    sp28_0 = &sp28.half[0];
    b1 = sp28_0;
    sp28_4 = &sp28.half[4];
    b2 = sp28_4;
    ASM_SET(c832);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_SET(c84);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_SET(c880);   /* MATCH pin: retail schedule: same instructions, different order without it */
    c832 = 0x340;
    cv = 0x154;
    sp28.half[1] = (s16) cv;
    cv = 0x60;
    sp28.half[2] = (s16) cv;
    c84 = 0x54;
    c880 = 0x370;
    sp28.half[0] = (s16) c832;
    sp28.half[3] = (s16) c84;
    sp28.half[4] = (s16) c880;
    cv = 0x19A;
    sp28.half[5] = (s16) cv;
    func_800B8FC8(((S_818FF710_2 *)temp_s7)->unk_60, b1, b2, 1, (s32) (s16) temp_v0_6);
    b1 = sp28_0;
    b2 = sp28_4;
    ASM_KEEP_NV(b1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_NV(b2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    cv = 0x1A8;
    sp28.half[1] = (s16) cv;
    cv = 0x60;
    sp28.half[2] = (s16) cv;
    sp28.half[0] = (s16) c832;
    sp28.half[3] = (s16) c84;
    sp28.half[4] = (s16) c880;
    cv = 0x1EF;
    sp28.half[5] = (s16) cv;
    func_800B8FC8(((S_818FF710_2 *)temp_s7)->unk_60, b1, b2, 1, (s32) (s16) temp_v0_6);
block_36:
    temp_fp = (s16) (*(u16 *)((u8 *)arg0 + 0x82));
    if (temp_fp != 4) {
        goto block_66;
    }
    temp_v0_7 = func_8003FC64(0x212);
    temp_s1 = temp_v0_7 + 0x20;
    if (temp_v0_7 == NULL) {
        goto block_39;
    }
    temp_s1->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)temp_v0_7 + 0x10)) = &D_800246F8;
    func_8004491C(temp_v0_7, &D_80045340);
    temp_s0_2 = (*(void **)((u8 *)temp_v0_7 + 0xC));
    temp_s0_2->unk_06 = 0;
    temp_s0_2->unk_14 |= 0xC;
    temp_s0_2->unk_10 = 0x40;
    flagrl = temp_s0_2->unk_14;
    temp_s0_2->unk_14 = (u16) (flagrl | 0x80);
    temp_v1_12 = (*(void **)((u8 *)temp_v0_7 + 8));
    temp_s1->unk_0A = 0;
    temp_s1->unk_0C = 0;
    temp_a3_3 = ((S_818FF710_31_pre *)(((S_818FF710_2 *)temp_s7)->unk_60))[-1].unk_00;
    temp_v1_12->unk_00 = (s32) ((S_818FF710_17 *)temp_a3_3)->unk_00;
    temp_v1_12->unk_04 = (s32) ((S_818FF710_17 *)temp_a3_3)->unk_04;
    temp_v1_12->unk_08 = (s32) ((S_818FF710_17 *)temp_a3_3)->unk_08;
    temp_s0_2 = (*(void **)((u8 *)temp_v0_7 + 0xC));
    temp_s0_2->unk_1C = 0x1004;
    temp_s0_2->unk_1E = 0x1004;
    temp_s0_2->unk_22 = (s16) ((s32) (0 - D_800DDC40[((S_818FF710_31 *)(((S_818FF710_2 *)temp_s7)->unk_60))->unk_13]) / 2);
    temp_s0_2->unk_0E = 0x80;
    temp_s0_2->unk_0D = 0x80;
    temp_s0_2->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)temp_v0_7 + 0x40)) = D_80025E34;
    temp_s0_2->unk_08 = (void *) (temp_v0_7 + 0x40);
    ((S_818FF710_32 *)(temp_s0_2->unk_08))->unk_04 = func_80066460(2, 2, 0x340, 0x154);
block_39:
    temp_v0_9 = func_8003FC64(0x212);
    temp_s1 = temp_v0_9 + 0x20;
    if (temp_v0_9 == NULL) {
        goto block_41;
    }
    temp_s1->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)temp_v0_9 + 0x10)) = &D_80024780;
    func_8004491C(temp_v0_9, &D_80045340);
    temp_s0_4 = (*(void **)((u8 *)temp_v0_9 + 0xC));
    temp_s0_4->unk_14 &= 0xFFF3;
    temp_s0_4->unk_10 = 0x20;
    temp_s0_4->unk_14 |= 0x80;
    temp_s1->unk_2C = temp_s7;
    tmp30 = ((S_818FF710_2 *)temp_s7)->unk_60;
    temp_s1->unk_34 = arg0;
    temp_s1->unk_30 = tmp30;
    temp_s0_4->unk_06 = 0;
    temp_v1_13 = (*(void **)((u8 *)temp_v0_9 + 8));
    temp_s1->unk_0A = 0;
    temp_s1->unk_0C = 0;
    temp_a3_4 = ((S_818FF710_31_pre *)(((S_818FF710_2 *)temp_s7)->unk_60))[-1].unk_00;
    temp_v1_13->unk_00 = (s32) ((S_818FF710_20 *)temp_a3_4)->unk_00;
    temp_v1_13->unk_04 = (s32) ((S_818FF710_20 *)temp_a3_4)->unk_04;
    temp_v1_13->unk_08 = (s32) ((S_818FF710_20 *)temp_a3_4)->unk_08;
    temp_s0_4 = (*(void **)((u8 *)temp_v0_9 + 0xC));
    temp_s0_4->unk_1E = 0x1000;
    temp_s0_4->unk_1C = 0x1000;
    temp_s0_4->unk_0E = 0x80;
    temp_s0_4->unk_0D = 0x80;
    temp_s0_4->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)temp_v0_9 + 0x40)) = D_80025E40;
    temp_s0_4->unk_08 = (void *) (temp_v0_9 + 0x40);
    ((S_818FF710_33 *)(temp_s0_4->unk_08))->unk_04 = func_80066460(2, 1, 0x340, 0x1A8);
block_41:
    temp_v0_11 = func_8003FC64(0x212);
    temp_s1 = temp_v0_11 + 0x20;
    if (temp_v0_11 == NULL) {
        goto block_43;
    }
    temp_s1->unk_02 = 0x78;
    (*(M2C_UNK **)((u8 *)temp_v0_11 + 0x10)) = &D_800245EC;
    func_8004491C(temp_v0_11, &D_80045340);
    temp_s0_6 = (*(void **)((u8 *)temp_v0_11 + 0xC));
    ((S_818FF710_21 *)temp_s0_6)->unk_06 = 0;
    ((S_818FF710_21 *)temp_s0_6)->unk_14 &= 0xFFF3;
    ((S_818FF710_21 *)temp_s0_6)->unk_10 = 0x20;
    flagrl = ((S_818FF710_21 *)temp_s0_6)->unk_14;
    ((S_818FF710_21 *)temp_s0_6)->unk_14 = (u16) (flagrl | 0x80);
    temp_v1_14 = (*(void **)((u8 *)temp_v0_11 + 8));
    temp_s1->unk_0A = 0;
    temp_s1->unk_0C = 0;
    temp_a3_5 = ((S_818FF710_31_pre *)(((S_818FF710_2 *)temp_s7)->unk_60))[-1].unk_00;
    temp_v1_14->unk_00 = (s32) ((S_818FF710_23 *)temp_a3_5)->unk_00;
    temp_v1_14->unk_04 = (s32) ((S_818FF710_23 *)temp_a3_5)->unk_04;
    temp_v1_14->unk_08 = (s32) ((S_818FF710_23 *)temp_a3_5)->unk_08;
    temp_s0_6 = (*(void **)((u8 *)temp_v0_11 + 0xC));
    ((S_818FF710_21 *)temp_s0_6)->unk_0E = 0x80;
    ((S_818FF710_21 *)temp_s0_6)->unk_0D = 0x80;
    ((S_818FF710_21 *)temp_s0_6)->unk_0C = 0x80;
    ((S_818FF710_21 *)temp_s0_6)->unk_1E = 0;
    ((S_818FF710_21 *)temp_s0_6)->unk_1C = 0;
    (*(Packed12 *)((u8 *)temp_v0_11 + 0x40)) = D_80025E58;
    ((S_818FF710_21 *)temp_s0_6)->unk_08 = (void *) (temp_v0_11 + 0x40);
block_43:
    temp_v0_13 = func_8003FC64(0x212);
    temp_s1 = temp_v0_13 + 0x20;
    if (temp_v0_13 == NULL) {
        goto block_45;
    }
    a0v4 = temp_v0_13;
    a1v4 = (void *) &D_80045340;
    ASM_KEEP_NV(a1v4);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s1->unk_2C = temp_s7;
    tmp30b = ((S_818FF710_2 *)temp_s7)->unk_60;
    p32 = (void *) (temp_v0_7 + 0x20);
    temp_s1->unk_38 = p32;
    p32 = (void *) (temp_v0_11 + 0x20);
    temp_s1->unk_3C = p32;
    p32 = (void *) (temp_v0_9 + 0x20);
    temp_s1->unk_40 = p32;
    temp_s1->unk_34 = arg0;
    temp_s1->unk_30 = tmp30b;
    (*(M2C_UNK **)((u8 *)temp_v0_13 + 0x10)) = &D_8002499C;
    func_8004491C(a0v4, a1v4);
    temp_s0_8 = (*(void **)((u8 *)temp_v0_13 + 0xC));
    ((S_818FF710_24 *)temp_s0_8)->unk_06 = 0;
    ((S_818FF710_24 *)temp_s0_8)->unk_14 |= 0xC;
    ((S_818FF710_24 *)temp_s0_8)->unk_10 = 0x20;
    flagrl = ((S_818FF710_24 *)temp_s0_8)->unk_14;
    ((S_818FF710_24 *)temp_s0_8)->unk_14 = (u16) (flagrl | 0x80);
    temp_v1_15 = (*(void **)((u8 *)temp_v0_13 + 8));
    temp_s1->unk_0A = 0;
    temp_s1->unk_0C = 0;
    temp_a3_6 = ((S_818FF710_31_pre *)(((S_818FF710_2 *)temp_s7)->unk_60))[-1].unk_00;
    temp_v1_15->unk_00 = (s32) ((S_818FF710_26 *)temp_a3_6)->unk_00;
    temp_v1_15->unk_04 = (s32) ((S_818FF710_26 *)temp_a3_6)->unk_04;
    temp_v1_15->unk_08 = (s32) ((S_818FF710_26 *)temp_a3_6)->unk_08;
    temp_s0_8 = (*(void **)((u8 *)temp_v0_13 + 0xC));
    ((S_818FF710_24 *)temp_s0_8)->unk_1E = 0x1000;
    ((S_818FF710_24 *)temp_s0_8)->unk_1C = 0x1000;
    ((S_818FF710_24 *)temp_s0_8)->unk_0E = 0x80;
    ((S_818FF710_24 *)temp_s0_8)->unk_0D = 0x80;
    ((S_818FF710_24 *)temp_s0_8)->unk_0C = 0x80;
    (*(Packed12 *)((u8 *)temp_v0_13 + 0x40)) = D_80025E28;
    ((S_818FF710_24 *)temp_s0_8)->unk_08 = (void *) (temp_v0_13 + 0x40);
    ASM_KEEP(temp_v0_13);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
block_45:
    temp_v0_15 = (s16) (*(u16 *)((u8 *)arg0 + 0x82));
    if (temp_v0_15 != temp_fp) {
        goto block_66;
    }
    (*(s16 *)((u8 *)arg0 + 0xA)) = temp_v0_15;
    (*(u16 *)((u8 *)arg0 + 0x82)) = 0U;
    (*(s16 *)((u8 *)arg0 + 0x90)) = 0;
    func_80025DF4();
    return;
}
jt_c4:
    var_s0_2 = 0;
    (*(u16 *)((u8 *)arg0 + 0x82)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x82)) + 1);
loop_48:
    var_s0_2 += 1;
    {
        register void *a0v ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 a1v;
        s32 a2v;
        register s32 a3v ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 rv;
        rv = func_80069EF8();
        a0v = arg0 - 0x20;
        a2v = 0x2020E0;
        ASM_KEEP_NV(a2v);   /* MATCH pin: retail schedule: same instructions, different order without it */
        a3v = (rv & 0xFF) | 0x80;
        ASM_KEEP_NV(a3v);   /* MATCH pin: retail schedule: same instructions, different order without it */
        a1v = (*(s16 *)((u8 *)arg0 + 0x7E));
        func_800244CC(a0v, a1v, a2v, a3v, 0, 0, 0);
    }
    if (var_s0_2 < 3) {
        goto loop_48;
    }
    temp_v1_16 = ((S_818FF710_1 *)arg2)->unk_1A;
    temp_v0_16 = temp_v1_16 + 0x190;
    ((S_818FF710_1 *)arg2)->unk_1A = temp_v0_16;
    if ((u32) (temp_v0_16 & 0xFFFF) < 0x1001U) {
        goto block_51;
    }
    ((S_818FF710_1 *)arg2)->unk_1A = (u16) (temp_v1_16 - 0xE70);
block_51:
    temp_v1_17 = (s16) (*(u16 *)((u8 *)arg0 + 0x82));
    if (temp_v1_17 < 0x51) {
        goto block_53;
    }
    ((S_818FF710_1 *)arg2)->unk_0C.at00u.v = (s8) (((0x64 - temp_v1_17) << 7) / 20);
    ((S_818FF710_1 *)arg2)->unk_0C.at01.v = (s8) (((0x64 - (s16) (*(u16 *)((u8 *)arg0 + 0x82))) << 7) / 20);
    ((S_818FF710_1 *)arg2)->unk_0C.at02.v = (s8) (((0x64 - (s16) (*(u16 *)((u8 *)arg0 + 0x82))) << 7) / 20);
block_53:
    func_80024DB8(arg0, arg1, arg2);
    if ((s16) (*(u16 *)((u8 *)arg0 + 0x82)) >= 0x64) {
        goto block_59;
    }
    func_80025DF4();
    return;
jt_c5:
    if ((*(s16 *)((u8 *)arg0 + 0x90)) == 0) {
        goto block_66;
    }
    var_a1 = 0xFF;
    if (D_800E3D68 == 0xFF) {
        goto block_58;
    }
    var_a1 = (*(u8 *)((u8 *)arg0 + 9));
block_58:
    func_8002407C(((S_818FF710_2 *)temp_s7)->unk_60, var_a1, temp_s7);
block_59:
    (*(u16 *)((u8 *)arg0 + 0x82)) = 0U;
    (*(s16 *)((u8 *)arg0 + 0xA)) = (s16) ((u16) (*(s16 *)((u8 *)arg0 + 0xA)) + 1);
    func_80025DF4();
    return;
jt_c6:
    temp_v0_17 = (*(u16 *)((u8 *)arg0 + 0x82)) + 1;
    (*(u16 *)((u8 *)arg0 + 0x82)) = temp_v0_17;
    if ((s16) temp_v0_17 < 0x1F) {
        goto block_66;
    }
    temp_v1_18 = ((S_818FF710_31_pre *)(((S_818FF710_2 *)temp_s7)->unk_60))[-1].unk_04;
    temp_v1_18->unk_14 = (u16) (temp_v1_18->unk_14 & 0xF7FF);
    temp_a0_3 = ((S_818FF710_2 *)temp_s7)->unk_60;
    temp_a0_3->unk_14 = (s32) (temp_a0_3->unk_14 & 0xFFEFFFFF);
    (*(s16 *)((u8 *)arg0 + 0xA)) = 8;
    (*(u16 *)((u8 *)arg0 + 0x82)) = 0x1EU;
    func_80025DF4();
    return;
jt_c8:
    temp_v1_19 = (*(u16 *)((u8 *)arg0 + 0x82));
    temp_v0_18 = temp_v1_19 + 1;
    (*(u16 *)((u8 *)arg0 + 0x82)) = temp_v0_18;
    if ((s16) temp_v0_18 < 0x1F) {
        goto block_66;
    }
    e80 = (s32) ((S_818FF710_3 *)(&D_80025E80))->unk_00;
    (*(u16 *)((u8 *)arg0 + 0x82)) = temp_v1_19;
    if (e80 != 0) {
        goto block_65;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)arg0 + -2)) = (u16) ((*(u16 *)((u8 *)arg0 + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((Rec_D_800814A0 *)(&D_800814A0))->unk_00 | 0x8000);
    func_80025DF4();
    return;
block_65:
    (*(s16 *)&D_80025E80) = 0;
block_66:
    return;
}
