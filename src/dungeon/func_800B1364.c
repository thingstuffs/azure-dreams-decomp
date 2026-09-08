#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad[0x29C];
    void *table[1];
} D_80010000_T;

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[3];
} Copy12;

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80089310[];
s32 func_8003C06C();
s32 func_8003DE58();
M2C_UNK func_8003E188();
void func_800424E0();
M2C_UNK func_80042640();
void func_80048A44();
M2C_UNK func_80069E78();
M2C_UNK func_80093C70();
M2C_UNK func_80093D8C();
void func_80098B38();
void *func_80098CF8();
s16 func_8009904C();
s32 func_80099090();
s32 func_800990FC();
s32 func_80099194();
s32 func_80099254();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_80099734();
M2C_UNK func_80099F04();
M2C_UNK func_80099F70();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_8009F644();
void *func_8009F868();
s32 func_8009F988();
void *(*func_800A0B94())(M2C_UNK, u8, u8, s16);
s32 func_800A1618();
M2C_UNK func_800A1D4C();
M2C_UNK func_800A56E0();
M2C_UNK func_800A5720();
s32 func_800A6D30();
M2C_UNK func_800A90E8();
M2C_UNK func_800B1768();
M2C_UNK func_800B4C7C();
M2C_UNK func_800B8024();
extern M2C_UNK D_80013714;
#define D_80010000_PTR ((D_80010000_T *)0x80010000)
extern s32 D_8007359C;
extern s32 D_80081484;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern s16 D_8008346A;
extern u32 D_800835E4[];
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_800B69DC;
extern s8 D_800DCF4F;
extern u8 D_800DD108[];
extern u8 D_800DD110[];
extern u8 D_800DD118[];
extern u8 D_800DD130[];
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern u8 D_800DDC40;
extern M2C_UNK D_800E0458;
extern M2C_UNK D_800E0A2A;
extern M2C_UNK D_800E0A33;
extern s8 D_800E2968;
extern M2C_UNK D_800E296C;
extern u8 D_800E3544;
extern void *D_800E3D7C;
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];

void func_800B6AC4(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11 };
    s16 sp18[3];
    register u8 *var_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v0_rand;
    s32 temp_v1_mask;
    s32 saved_word;
    s32 var_v0;
    register s32 var_v0_test ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 var_v0_2;
    s32 temp_v0_11;
    u8 temp_v0_4;
    u16 temp_v0;
    u16 temp_v0_10;
    u16 temp_v1_2;
    u16 temp_v1_9;
    u32 temp_a0_3;
    u8 *temp_a0;
    u8 *temp_v0_2;
    u8 *temp_v1_3;
    u8 *var_v0_3;
    u8 temp_v1;
    register u8 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *temp_a0_2;
    void *temp_a0_4;
    void *temp_a0_5;
    void *temp_a0_6;
    void *temp_a0_7;
    void *temp_a0_8;
    void *temp_t0;
    void *temp_v0_3;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v1_4;
    u32 *temp_v1_5;
    u32 *loop_table;
    void *temp_v1_6;
    void *temp_v1_7;
    register void *temp_v1_8 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *var_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *var_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *var_a3;
    M2C_UNK *var_s0 = (M2C_UNK *)&D_80083160;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 0xCU) {
        goto block_75;
    }
    (void)jt_keep; goto *D_80089310[(u32)(temp_v1)];
jt_c0: {
    register u8 *case0_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    case0_page = (u8 *)0x80080000;
    ASM_KEEP_NV(case0_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    var_a1 = case0_page + 0x3160;
    if ((((s32) (M2C_FIELD(var_a1, s16 *, 0xC8) + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) != 2) {
        goto block_4;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD108;
    func_80048A44(arg2, D_800DD108[((s32) (M2C_FIELD(var_a1, s16 *, 0xC8) + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    next_state = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0x96) = 0x12U;
    goto block_72;
}
block_4:
    M2C_FIELD(arg3, s16 *, 0x2A) = (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x2A) + 0x200);
    return;
jt_c1:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) != 0) {
        goto block_7;
    }
    func_800A56E0(0x701);
block_7:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_75;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD110;
    func_80048A44(arg2, D_800DD110[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    if (M2C_FIELD(&D_80013714, u16 *, 0) & 1) {
        goto block_10;
    }
    func_800B1768(0x22, 0xF2, 0xBA, 0x105, 0, 8);
    func_800B1768(0x23, 0xE0, 0xCE, 0x104, 1, 8);
block_10: {
    u8 *ptr;
    u8 *saved;
    void *callback;
    ptr = M2C_FIELD(arg0, u8 **, 0xBC);
    saved = ptr;
    ASM_KEEP_NV(saved);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    M2C_FIELD(arg0, u8 **, 0xC0) = ptr;
    saved_word = M2C_FIELD(saved, s32 *, 0);
    callback = &D_800B69DC;
    M2C_FIELD(arg0, void **, 0x8C) = callback;
    D_80081484 = saved_word;
    return;
}
jt_c2:
    temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
    if (temp_v1_2 & 0xE000) {
        goto block_13;
    }
    {
    void *d83460 = &D_80083460;
    M2C_FIELD(d83460, u16 *, 2) = (u16) (M2C_FIELD(d83460, u16 *, 2) | 4);
    }
    goto block_14;
block_13:
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_v1_2 | 0x6800);
block_14:
    if (D_80083462 & 4) {
        goto block_75;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    var_v0 = 0;
    if (!(M2C_FIELD(&D_80013714, u16 *, 0) & 1)) {
        goto block_20;
    }
    temp_v0_3 = func_8009F868();
    if (temp_v0_3 != NULL) {
        goto block_18;
    }
    func_800B1768(0x22, 0xF2, 0xBA, 0x105, 0, 8);
    func_800B1768(0x23, 0xE0, 0xCE, 0x104, 1, 8);
    return;
block_18:
    temp_v0_4 = M2C_FIELD(temp_v0_3, u8 *, 1) & 0xF8;
    D_800E3544 = temp_v0_4;
    if (temp_v0_4 == 0x60) {
        goto block_22;
    }
    func_8009F988();
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD118;
    func_80048A44(arg2, D_800DD118[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    goto block_30;
block_20:
    if (!(M2C_FIELD(var_s0, s32 *, 8) & 0x40)) {
        goto block_23;
    }
block_22:
    var_v0 = 1;
block_23:
    var_v0_test = var_v0;
    if (var_v0_test == 0) {
        goto block_27;
    }
    func_8009F644(arg3, 0x60, 0, 0);
    func_800A56E0(0x500);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0x97FF);
    M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
    temp_v0_rand = (func_800A6D30() & 3) + 1;
    temp_a0 = M2C_FIELD(arg0, u8 **, 0xBC);
    M2C_FIELD(temp_a0, u8 *, 2) = (s8) (M2C_FIELD(temp_a0, u8 *, 2) - temp_v0_rand);
    temp_v1_3 = M2C_FIELD(arg0, u8 **, 0xBC);
    if ((s8) M2C_FIELD(temp_v1_3, u8 *, 2) > 0) {
        goto block_26;
    }
    M2C_FIELD(temp_v1_3, u8 *, 2) = 0U;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD118;
    func_80048A44(arg2, D_800DD118[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
    M2C_FIELD(arg3, s16 *, 0x8A) = func_8009904C(M2C_FIELD(arg0, u8 **, 0xBC));
block_26:
    func_800B4C7C(0xA4, arg3, (s16) (0x64 - (s8) M2C_FIELD(M2C_FIELD(arg0, u8 **, 0xBC), u8 *, 2)), 0);
    return;
block_27:
    {
    register s32 t27 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    t27 = M2C_FIELD(&D_80013714, u16 *, 0) & 1;
    if (t27) {
        goto block_75;
    }
    t27 = M2C_FIELD(var_s0, s32 *, 0x10) & 0x20;
    if (t27 == 0) {
        goto block_75;
    }
    }
    func_8009F644(arg3, 0xA8, 0, 0);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD118;
    func_80048A44(arg2, D_800DD118[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    func_800A56E0(0x515);
block_30:
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = NULL;
    M2C_FIELD(arg0, u8 *, 0x9B) = 4U;
    return;
jt_c3:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_75;
    }
    var_s0 = &D_80083460;
    if (M2C_FIELD(var_s0, u16 *, 2) & 2) {
        goto block_34;
    }
    func_80099F70(M2C_FIELD(arg3, s32 *, 0x5C));
    func_80099F04(M2C_FIELD(arg3, s32 *, 0x5C));
    M2C_FIELD(var_s0, u16 *, 2) = (u16) (M2C_FIELD(var_s0, u16 *, 2) | 0x812);
block_34:
    M2C_FIELD(arg0, u8 *, 0x9B) = 2U;
    return;
jt_c4:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_75;
    }
    func_80098B38(&D_80081484);
    {
    void *callback = &D_8008ACDC;
    temp_v1_mask = M2C_FIELD(&D_800E296C, s32 *, 0) & 0xFFDFFFFF;
    M2C_FIELD(arg0, void **, 0x8C) = callback;
    (*(s32 *)&D_800E296C) = temp_v1_mask;
    }
    return;
jt_c5:
    temp_v0_5 = func_80098CF8(arg0, arg1, arg2, &D_80081484);
    if (temp_v0_5 == NULL) {
        goto block_75;
    }
    M2C_FIELD(temp_v0_5, s16 *, 0xCC) = 2;
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x22;
    M2C_FIELD(arg0, u8 *, 0x9B) = 6U;
    return;
jt_c6:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_75;
    }
    if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, sp18, 0) != 0) {
        goto block_42;
    }
    sp18[1] = 0;
    sp18[0] = 0;
    sp18[2] = 0 - D_800DDC40;
block_42:
    func_800B8024(M2C_FIELD(arg1, s16 *, 2) + sp18[0], M2C_FIELD(arg1, s16 *, 6) + sp18[1], M2C_FIELD(arg1, s16 *, 0xA) + sp18[2]);
    goto block_71;
jt_c7:
    temp_v0_2 = M2C_FIELD(arg0, u8 **, 0xC0);
    D_800E2968 = 1;
    temp_v0_9 = func_800A1618(*temp_v0_2, 2);
    temp_v0_6 = func_800A0B94(*M2C_FIELD(arg0, u8 **, 0xC0), temp_v0_9, 1)(2, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
    if (temp_v0_6 == NULL) {
        goto block_75;
    }
    func_8003E188(M2C_FIELD(temp_v0_6, u8 *, 0x13), 0);
    func_800A90E8(M2C_FIELD(arg0, u8 **, 0xC0));
    temp_v0_7 = M2C_FIELD(temp_v0_6, void **, -0x14);
    func_8009A3D0(M2C_FIELD(temp_v0_7, u8 *, 0x24), M2C_FIELD(temp_v0_7, u8 *, 0x25), 0x300);
    if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, sp18, 0) != 0) {
        goto block_46;
    }
    sp18[1] = 0;
    sp18[0] = 0;
    sp18[2] = 0 - D_800DDC40;
block_46:
    temp_a0_2 = M2C_FIELD(temp_v0_6, void **, -0x18);
    M2C_FIELD(temp_a0_2, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + (u16) sp18[0]);
    M2C_FIELD(temp_a0_2, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + (u16) sp18[1]);
    temp_v0_8 = (u16) M2C_FIELD(arg1, s16 *, 0xA) + (u16) sp18[2];
    M2C_FIELD(temp_a0_2, s16 *, 0xA) = temp_v0_8;
    M2C_FIELD(temp_v0_6, s16 *, 0x88) = temp_v0_8;
    M2C_FIELD(arg3, void **, 0x60) = temp_v0_6;
    func_80042640(temp_v0_6, M2C_FIELD(temp_v0_6, u8 *, 0x13));
    func_800424E0(temp_v0_6, M2C_FIELD(temp_v0_6, u8 *, 0x13), 0);
    M2C_FIELD(temp_v0_6, u8 *, 0x43) = 0xFF;
    M2C_FIELD(temp_v0_6, void **, 0x60) = arg3;
    M2C_FIELD(temp_v0_6, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_v0_6, s32 *, 0x1C) | 0x80000);
    M2C_FIELD(temp_v0_6, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_6, s32 *, 0x14) | 0x104000);
    temp_v1_4 = M2C_FIELD(arg3, void **, 0x60);
    M2C_FIELD(temp_v1_4, u16 *, 0x98) = (u16) (M2C_FIELD(temp_v1_4, u16 *, 0x98) | 0xC);
    func_80069E78(temp_v0_6 + 0x34, func_8003C06C(M2C_FIELD(temp_v0_6, u8 *, 0x13)));
    temp_a0_3 = D_800835E4[M2C_FIELD(D_800E3D7C, u8 *, 0x11)];
    temp_v1_5 = D_800835E4 + 1;
    M2C_FIELD(temp_v0_6, u32 *, 0x18) = temp_a0_3;
    if (temp_a0_3 < temp_v1_5[M2C_FIELD(temp_v0_6, u8 *, 0x11)]) {
        goto block_49;
    }
    loop_table = temp_v1_5;
loop_48:
    func_800A1D4C(temp_v0_6, 0);
    if (loop_table[M2C_FIELD(temp_v0_6, u8 *, 0x11)] <= (u32) M2C_FIELD(temp_v0_6, u32 *, 0x18)) {
        goto loop_48;
    }
block_49:
    M2C_FIELD(temp_v0_6, u8 *, 0x28) = (u8) M2C_FIELD(temp_v0_6, u8 *, 0x29);
    M2C_FIELD(temp_v0_6, u8 *, 0x26) = (u8) M2C_FIELD(temp_v0_6, u8 *, 0x68);
    M2C_FIELD(temp_v0_6, u8 *, 0x27) = (u8) M2C_FIELD(temp_v0_6, u8 *, 0x69);
    if (M2C_FIELD(&D_80013714, u16 *, 0) & 1) {
        goto block_51;
    }
    {
    u16 ctr;
    u8 *ctl;
    D_800DCF4F = 1;
    ctl = (u8 *)&D_80083460;
    ctr = M2C_FIELD(ctl, u16 *, 0xA);
    M2C_FIELD(ctl, u16 *, 0xA) = (u16) (ctr + 1);
    }
block_51:
    temp_v0_9 = func_800990FC();
    var_v0_2 = func_80099194(&D_800E0A33, func_80099734(temp_v0_6, func_80099194(&D_800E0A2A, func_80099194(M2C_FIELD(((M2C_FIELD(temp_v0_6, u8 *, 0x13) * 0x14) + D_8007359C), M2C_UNK **, 4), func_8009929C(8, temp_v0_9)))));
    if ((*(u16 *)&D_80013714) & 1) {
        goto block_53;
    }
    var_v0_2 = func_80099254(&D_800E0458, func_8009929C(0x4C, func_8009929C(0x11, var_v0_2)));
block_53:
    func_80099290(var_v0_2);
    func_800A5720(temp_v0_9);
    M2C_FIELD(arg0, u16 *, 0x96) = 0x20U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    if ((*(u16 *)&D_80013714) & 1) {
        goto block_56;
    }
    temp_a0_4 = &D_80083460;
    if ((s16) M2C_FIELD(temp_a0_4, u16 *, 0xA) < 2) {
        goto block_75;
    }
    M2C_FIELD(temp_a0_4, u16 *, 0xA) = (u16) (M2C_FIELD(temp_a0_4, u16 *, 0xA) - 1);
    return;
block_56:
    temp_a0_4 = &D_80083460;
    if (M2C_FIELD(temp_a0_4, s16 *, 0xA) <= 0) {
        goto block_75;
    }
    M2C_FIELD(temp_a0_4, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(temp_a0_4, s16 *, 0xA) - 1);
    return;
jt_c8:
    if (D_8008346A != 0) {
        goto block_75;
    }
    temp_v0_10 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_10;
    var_a0 = arg2;
    if ((temp_v0_10 << 0x10) <= 0) {
        goto block_62;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        goto block_62;
    }
    if (M2C_FIELD(var_s0, s32 *, 0x10) == 0) {
        goto block_75;
    }
block_62:
    var_a1 = D_800DD130;
    M2C_FIELD(var_a0, M2C_UNK **, 0x2C) = var_a1;
    var_v0_3 = (u8 *) ((u32) (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + (u32) var_a1);
    var_a2 = NULL;
    goto block_70;
jt_c9:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_75;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD138;
    func_80048A44(arg2, D_800DD138[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x200);
    func_80093C70(arg0, arg1, arg2);
    func_80093D8C(arg0, arg1, arg2);
    temp_v0_11 = func_80099090();
    temp_a0_5 = D_80010000_PTR->table[M2C_FIELD(arg3, s16 *, 0x8A)];
    M2C_FIELD(temp_a0_5, s8 *, 1) = 0x13;
    temp_v1 = (u8) *M2C_FIELD(arg0, u8 **, 0xC0);
    M2C_FIELD(temp_a0_5, s8 *, 3) = temp_v0_11;
    M2C_FIELD(temp_a0_5, s8 *, 2) = 0;
    M2C_FIELD(temp_a0_5, u8 *, 0) = temp_v1;
    D_800E3DF0[temp_v0_11] = temp_v1_6 = (temp_v0_11 * 0x8C) + D_800E3E48;
    var_a2 = M2C_FIELD(arg3, void **, 0x60);
    var_a3 = temp_v1_6;
    temp_t0 = var_a2 + 0x80;
loop_66:
    *(Copy16 *)var_a3 = *(Copy16 *)var_a2;
    var_a2 += 0x10;
    var_a3 += 0x10;
    if (var_a2 != temp_t0) {
        goto loop_66;
    }
    ASM_KEEP_NV(var_a2);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    *(Copy12 *)var_a3 = *(Copy12 *)var_a2;
    temp_a0_6 = M2C_FIELD(arg3, void **, 0x60);
    M2C_FIELD(temp_a0_6, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0_6, s32 *, 0x1C) | 0x400000);
    temp_v1_7 = M2C_FIELD(arg3, void **, 0x60);
    M2C_FIELD(temp_v1_7, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v1_7, s32 *, 0x14) & 0xFFEFFFFF);
    func_800A56E0(0x704);
    goto block_71;
jt_c10:
    temp_a0_7 = M2C_FIELD(arg3, void **, 0x60);
    if (!(M2C_FIELD(temp_a0_7, s32 *, 0x1C) & 0x800000)) {
        goto block_75;
    }
    func_8009A028(temp_a0_7);
    var_a2 = NULL;
    temp_a0_5 = D_80010000_PTR->table[M2C_FIELD(arg3, s16 *, 0x8A)];
    temp_a0_8 = D_800E3DF0[M2C_FIELD(temp_a0_5, u8 *, 3) & 0x1F];
    M2C_FIELD(temp_a0_8, s32 *, 0x14) = (s32) (M2C_FIELD(temp_a0_8, s32 *, 0x14) & ~0x4000);
    temp_v1_8 = M2C_FIELD(arg3, void **, 0x60);
    {
    u8 *page;
    page = (u8 *)0x80080000;
    M2C_FIELD(temp_v1_8, u16 *, -2) = (u16) (M2C_FIELD(temp_v1_8, u16 *, -2) | 0x8000);
    temp_v1_8 = (void *) M2C_FIELD(page, s32 *, 0x14A0);
    temp_v1_8 = (void *) ((s32) temp_v1_8 | 0x8000);
    var_a1 = D_800DD140;
    var_a0 = arg2;
    M2C_FIELD(var_a0, u8 **, 0x2C) = var_a1;
    var_v0_3 = var_a1 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7);
    M2C_FIELD(page, s32 *, 0x14A0) = (s32) temp_v1_8;
    }
block_70:
    func_80048A44(var_a0, *var_v0_3, var_a2, 1);
block_71:
    next_state = M2C_FIELD(arg0, u8 *, 0x9B);
block_72:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (next_state + 1);
    return;
jt_c11:
    temp_v1_9 = M2C_FIELD(arg2, u16 *, 0x14);
    if (!(temp_v1_9 & 0xE000)) {
        goto block_75;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_v1_9 & 0xFDFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8008ACDC;
    ASM_USE2(arg0, arg0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
block_75:
    return;
}
