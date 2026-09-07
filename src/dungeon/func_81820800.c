#include "common.h"
#include "m2c_compat.h"

extern void *jtbl_80024008[];
__asm__(".set jtbl_80024008, 0x80024008");
void *func_8003FD64();
s32 func_8004491C();
s32 func_80069EF8();
M2C_UNK func_8009CE1C();
void *func_800A05A4();
s16 func_800A3820();
s32 func_800A4688();
M2C_UNK func_800A56E0();
s16 func_800BCB04();
extern M2C_UNK D_800245B4;
extern M2C_UNK D_80024A1C;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;

extern void func_80024020(void);
extern void func_80024148(void);
extern void func_8002439C(void);
extern void func_800244D4(void);
extern void func_80024518(void);
extern void func_8002453C(void);
__asm__(".set func_80024020, 0x80024020");
__asm__(".set func_80024148, 0x80024148");
__asm__(".set func_8002439C, 0x8002439c");
__asm__(".set func_800244D4, 0x800244d4");
__asm__(".set func_80024518, 0x80024518");
__asm__(".set func_8002453C, 0x8002453c");

/* Composite carve: retail places an 8-word bank (entry pointer, a zero word and
 * the 6-entry state jump table) immediately before this function's own code,
 * all under the func_80024000 symbol.  The bank is pinned to the function's own
 * named section so it lands ahead of the compiled body in the same output
 * section, byte-for-byte and gap-free (cf. the landed sister-floor module
 * func_81844800.c). */
#ifdef __mips__
static void (*const func_80024000_table[])(void)
    __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
        func_80024020,
        0,
        func_80024148,
        func_8002439C,
        func_8002439C,
        func_800244D4,
        func_80024518,
        func_8002453C,
    };
__asm__(".globl func_80024000\n"
        ".type func_80024000,@function\n"
        ".size func_80024000, 1460");
#define BODY_NAME composite_body_81820800
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80024000")))
#else
#define BODY_NAME func_80024000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *arg0, void *arg1, void *arg2) BODY_ATTR;
BODY_STORAGE void BODY_NAME(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    void *state_obj;
    void *owner;
    register void *input2 ASM_REG("$16");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_s5 ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *temp_v0_2;
    void *temp_v1_2;
    void *temp_s0_2;
    void *temp_v0_3;
    void *sp20;
    s32 sp24;
    s32 sp28;
    register s32 var_s6 ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 var_s7 ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    M2C_UNK var_s3;
    register s32 temp_s2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 temp_s4 ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s8 *base_y ASM_REG("$3");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 var_a0 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 var_s2;
    s32 temp_v0_4;
    s32 temp_v1_3;
    s16 temp_v0;
    s32 temp_v1;
    s16 var_s4;
    register M2C_UNK temp_a0 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    u16 header_raw;
    u16 duration;
    u16 temp_s0;
    u16 temp_s1;
    s32 coord_x;
    s32 coord_y;
    state_obj = arg0;
    input2 = arg2;
    base_y = (s8 *) &D_8006CCD8;
    temp_s5 = M2C_FIELD(state_obj, void **, 0);
    owner = (void *) ((u8 *) temp_s5 - 0x20);
    header_raw = M2C_FIELD(temp_s5, u16 *, 0x2A);
    temp_s2 = header_raw >> 8;
    temp_a0 = temp_s2 & 0xE;
    ASM_KEEP_DEP_NV(temp_a0, header_raw);   /* MATCH pin: keeps a statement from moving across a call/branch */
    sp20 = M2C_FIELD(temp_s5, void **, -0x14);
    sp24 = *(s16 *)(temp_a0 + base_y);
    sp28 = *(s16 *)(temp_a0 + (s8 *)&D_8006CCE8);
    ASM_KEEP_NV(input2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_NV(state_obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (M2C_FIELD(state_obj, s16 *, 0xA) != 1) {
        goto block_3;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    temp_s2 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(M2C_FIELD(owner, void **, 8), u16 *, 0xA) - 0x30));
    if (temp_s2 >= 0x200) {
        goto block_3;
    }
    M2C_FIELD(arg1, s16 *, 0xA) = temp_s2;
block_3:
    temp_v1 = M2C_FIELD(state_obj, s16 *, 0xA);
    M2C_FIELD(state_obj, u16 *, 0x50) = (u16) (M2C_FIELD(state_obj, u16 *, 0x50) - 1);
    if ((u32) temp_v1 >= 6U) {
        goto block_38;
    }
    (void)jt_keep; goto *jtbl_80024008[(u32)(temp_v1)];
jt_c0:
    if (!(*M2C_FIELD(state_obj, u16 **, 4) & 0x80)) {
        goto block_38;
    }
    {
        void *work;
        s32 prior = func_800A3820(3) << 0x10;
        work = sp20;
        temp_v0_2 = func_800A05A4(temp_s5, M2C_FIELD(work, u8 *, 0x24), M2C_FIELD(work, u8 *, 0x25), (s16) M2C_FIELD(temp_s5, u16 *, 0x2A), prior >> 0x10);
    }
    M2C_FIELD(temp_s5, void **, 0x60) = temp_v0_2;
    if (temp_v0_2 != NULL) {
        goto block_11;
    }
    var_s3 = 0;
    var_s7 = 0;
    var_s6 = 0;
loop_8:
    {
        void *work = sp20;
        register s32 cx ASM_REG("$3");   /* MATCH pin: retail immediate-load split depends on it */
        s32 cy;
        cx = (M2C_FIELD(work, u8 *, 0x24) + var_s6) << 6;
        coord_x = cx + 0x20;
        cy = (M2C_FIELD(work, u8 *, 0x25) + var_s7) << 6;
        coord_y = cy + 0x20;
        ASM_KEEP_NV(coord_x);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP_NV(coord_y);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
    if ((func_800A4688((u16) coord_x, (u16) coord_y, func_800BCB04((u16) coord_x, (u16) coord_y, -0x400), (s16) M2C_FIELD(temp_s5, u16 *, 0x2A), M2C_FIELD(temp_s5, void **, 0x60)) << 0x10) != 0) {
        goto block_10;
    }
    var_s3 += 1;
    var_s7 += sp28;
    var_s6 += sp24;
    if (var_s3 < 2) {
        goto loop_8;
    }
block_10:
    ASM_USE(coord_x);   /* MATCH pin: retail register colouring depends on it */
    ASM_USE2(coord_x, coord_y);   /* MATCH pin: load-bearing for the whole function shape */
    {
        void *work = sp20;
        M2C_FIELD(temp_s5, u8 *, 0x72) = (u8) (M2C_FIELD(work, u8 *, 0x24) + (sp24 * var_s3));
        M2C_FIELD(temp_s5, u8 *, 0x73) = (u8) (M2C_FIELD(work, u8 *, 0x25) + (sp28 * var_s3));
    }
    goto block_13;
block_11:
    temp_v1_2 = M2C_FIELD(temp_v0_2, void **, -0x14);
    M2C_FIELD(temp_s5, u8 *, 0x72) = (u8) M2C_FIELD(temp_v1_2, u8 *, 0x24);
    M2C_FIELD(temp_s5, u8 *, 0x73) = (u8) M2C_FIELD(temp_v1_2, u8 *, 0x25);
    if (!(M2C_FIELD(temp_v1_2, u16 *, 0x14) & 0x8000)) {
        goto block_13;
    }
    if (M2C_FIELD(input2, u16 *, 0x14) & 0x8000) {
        goto block_28;
    }
block_13:
    {
        void *work;
        s32 actor_x;
        s32 actor_y;
        s32 work_x;
        s32 work_y;
        work = sp20;
        actor_x = (s8)M2C_FIELD(temp_s5, u8 *, 0x72);
        actor_y = (s8)M2C_FIELD(temp_s5, u8 *, 0x73);
        work_x = M2C_FIELD(work, u8 *, 0x24);
        work_y = M2C_FIELD(work, u8 *, 0x25);
        temp_s2 = actor_x - work_x;
        temp_s4 = actor_y - work_y;
        ASM_KEEP(work_y);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(work_x);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(actor_y);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(actor_x);   /* MATCH pin: keeps a statement from moving across a call/branch */
    }
    var_s3 = temp_s2;
    if (temp_s2 >= 0) {
        goto block_15;
    }
    var_s3 = 0 - var_s3;
block_15:
    var_a0 = temp_s4;
    if (temp_s4 >= 0) {
        goto block_17;
    }
    var_a0 = 0 - var_a0;
block_17:
    if (var_s3 >= var_a0) {
        goto block_19;
    }
    var_s3 = var_a0;
block_19:
    M2C_FIELD(state_obj, u16 *, 0x50) = (u16) (var_s3 * 0xC);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (((M2C_FIELD(sp20, u8 *, 0x24) << 6) + 0x20) << 0x10);
    M2C_FIELD(arg1, s32 *, 4) = (s32) (((M2C_FIELD(sp20, u8 *, 0x25) << 6) + 0x20) << 0x10);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((sp24 << 0x16) / 12);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((sp28 << 0x16) / 12);
    func_800A56E0(0x300);
    M2C_FIELD(state_obj, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) + 1);
    return;

jt_c1:
jt_c2:
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x100);
    var_s4 = 0;
    if (M2C_FIELD(temp_s5, void **, 0x60) != NULL) {
        goto block_22;
    }
    var_s4 = -1;
block_22:
    var_s2 = 2;
    var_s3 = (s32)&D_800245B4;
loop_23:
    temp_v0_3 = func_8003FD64(0x201, &D_80083498);
    if (temp_v0_3 == NULL) {
        goto block_25;
    }
    M2C_FIELD(temp_v0_3, s32 *, 0x10) = var_s3;
    func_8004491C(temp_v0_3, &D_80024A1C);
    duration = M2C_FIELD(state_obj, u16 *, 0x50);
    temp_s0_2 = temp_v0_3 + 0x20;
    M2C_FIELD(temp_s0_2, s16 *, 0x54) = var_s4;
    M2C_FIELD(temp_s0_2, u16 *, 0x52) = duration;
    M2C_FIELD(temp_s0_2, s16 *, 0x4C) = (s16) (func_80069EF8() & 0xFFF);
    M2C_FIELD(temp_s0_2, u16 *, 0x4E) = (u16) M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(temp_s0_2, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(temp_s0_2, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(temp_s0_2, s32 *, 0xC) = 0;
    temp_v0_4 = M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(temp_s0_2, s32 *, 0x1C) = temp_v0_4;
    M2C_FIELD(temp_s0_2, s32 *, 0x10) = temp_v0_4;
    temp_v1_3 = M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(temp_s0_2, s32 *, 0x24) = 0xFFFD0000;
    M2C_FIELD(temp_s0_2, s32 *, 0x18) = 0xFFFD0000;
    M2C_FIELD(temp_s0_2, s32 *, 0x20) = temp_v1_3;
    M2C_FIELD(temp_s0_2, s32 *, 0x14) = temp_v1_3;
    M2C_FIELD(temp_s0_2, u16 *, 0x50) = (u16) M2C_FIELD(arg1, s16 *, 0xA);
    M2C_FIELD(temp_v0_3, void **, 0x20) = state_obj;
    M2C_FIELD(temp_s0_2, s16 *, 0x56) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) - 1);
block_25:
    var_s2 -= 1;
    if (var_s2 >= 0) {
        goto loop_23;
    }
    if ((s16) M2C_FIELD(state_obj, u16 *, 0x50) > 0) {
        goto block_38;
    }
    M2C_FIELD(state_obj, u16 *, 0x50) = 5U;
    M2C_FIELD(state_obj, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) + 1);
    if (M2C_FIELD(temp_s5, void **, 0x60) != NULL) {
        goto block_38;
    }
block_28:
    M2C_FIELD(state_obj, s16 *, 0xA) = 3;
    return;
jt_c3:
    if (M2C_FIELD(temp_s5, void **, 0x60) == NULL) {
        goto block_31;
    }
    func_8009CE1C(M2C_FIELD(temp_s5, void **, 0x60), 0x10, M2C_FIELD(state_obj, u8 *, 9), 4, (s32) (s16) M2C_FIELD(temp_s5, u16 *, 0x2A), temp_s5, 2);
block_31:
    M2C_FIELD(state_obj, u16 *, 0x50) = 0x10U;
    M2C_FIELD(state_obj, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) + 1);
    return;
jt_c4:
    if ((s16) M2C_FIELD(state_obj, u16 *, 0x50) > 0) {
        goto block_38;
    }
    M2C_FIELD(state_obj, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0xA) + 1);
    return;
jt_c5:
    if (!(M2C_FIELD(state_obj, s16 *, 0x52) & 0x8000)) {
        goto block_37;
    }
    M2C_FIELD(state_obj, s16 *, 0x52) = (s16) ((u16) M2C_FIELD(state_obj, s16 *, 0x52) & 0x7FFF);
    return;
block_37:
    D_8008346C = 0;
    M2C_FIELD(state_obj, u16 *, -2) = (u16) (M2C_FIELD(state_obj, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
block_38:
    return;
}
