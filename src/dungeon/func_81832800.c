#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DEA68[];
extern u8 D_800DED70[];
extern s32 D_8008346C[];
extern s32 D_800814A0[3];
extern void func_80024354(void) __attribute__((noreturn));
extern void func_80024488(void) __attribute__((noreturn));
extern void func_80024490(void) __attribute__((noreturn));
extern void func_800247B4(void) __attribute__((noreturn));
void *func_8003FD64();                     /* extern */
M2C_UNK func_8004491C();                /* extern */
s32 func_80069EF8();                /* extern */
M2C_UNK func_8009CE1C(); /* extern */
void *func_800A05A4();      /* extern */
s16 func_800A3820();                         /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80024860;
extern M2C_UNK D_800248F0;

extern void func_80024004(void);
__asm__(".set func_80024004, 0x80024004");

/* Retail places ONE 4-byte word (0x80024004) immediately before this
 * function's own code, under the func_81832800 symbol: the row's true base is
 * 0x80024000 and that word points at 0x80024004, the first instruction of the
 * body.  Same composite shape as the matched sibling func_81844800 (8-entry
 * table + body in one .text.<func> section).  Prior drafts modelled this word
 * as a dead `lb $v0, 0x4004($zero)` retained by a volatile-asm keep; that
 * keep is
 * a sched2 barrier and is what pinned the D_8006CCD8 %hi below the callee-save
 * stores. */
#ifdef __mips__
static void (*const func_81832800_table[])(void)
    __asm__("func_81832800")
    __attribute__((section(".text.func_81832800"), aligned(4))) = {
        func_80024004,
    };
__asm__(".globl func_81832800\n"
        ".type func_81832800,@function\n"
        ".size func_81832800, 2024");
#define BODY_NAME composite_body_81832800
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_81832800")))
#else
#define BODY_NAME func_81832800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *arg0_in, void *arg1_in, void *arg2) BODY_ATTR;
BODY_STORAGE void BODY_NAME(void *arg0_in, void *arg1_in, void *arg2) {
    void *sp20;
    s32 sp24;
    s32 sp28;
    s32 temp_s2;
    s16 temp_v1_3;
    s16 var_a0;
    register s32 temp_a0_2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_a2;
    s32 temp_v0_2;
    s32 temp_v0_3;
    register s32 temp_v0_6 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_s2;
    s32 var_s2_2;
    register s32 var_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_s4_2;
    s32 var_s4_3;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    u16 temp_a0_7;
    u16 temp_v1;
    u16 temp_v1_8;
    u16 var_v0;
    void *temp_a0_8;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;
    void *temp_a1_4;
    void *temp_a1_5;
    void *temp_fp;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s1;
    void *temp_s3;
    void *temp_s5;
    void *temp_v0;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_7;
    void *temp_v1_2;
    register u32 temp_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 temp_init_word ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *cb_page;
    void *spr_page;
    register void *arg0 ASM_REG("$22") = arg0_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *arg1 ASM_REG("$23") = arg1_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    temp_flags = (u32) D_8006CCD8;
    temp_s5 = M2C_FIELD(arg0, void **, 0);
    temp_init_word = M2C_FIELD(temp_s5, u16 *, 0x2A);
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_fp = M2C_FIELD(temp_s5, void **, -0x14);
    var_s4 = (u16) temp_init_word >> 8;
    temp_a0_2 = var_s4 & 0xE;
    sp24 = (s32) M2C_FIELD((void *) temp_flags, s16 *, temp_a0_2);
    sp28 = (s32) M2C_FIELD(D_8006CCE8, s16 *, temp_a0_2);
    temp_v1 = M2C_FIELD(arg0, u16 *, 0xA);
    M2C_FIELD(arg0, u16 *, 0x50) = (u16) (M2C_FIELD(arg0, u16 *, 0x50) - 1);
    sp20 = temp_s5 - 0x20;
    if ((u32) (temp_v1 - 1) < 3U) {
        var_s4 = 3;
        if ((s16) temp_v1 < 3) {
            var_s4 = 5;
        }
        cb_page = &D_80024860;
        spr_page = D_800DEA68;
        if (var_s4 >= 0) {
first_spawn_loop:
                temp_v0 = func_8003FD64(0x312, D_80083498);
                if (temp_v0 != NULL) {
                    void *temp_t0;
                    void *payload;
                    func_8004491C(temp_v0, D_80045340);
                    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
                    payload = M2C_FIELD(temp_v0, void **, 8);
                    temp_t0 = cb_page;
                    M2C_FIELD(temp_v0, void **, 0x10) = temp_t0;
                    M2C_FIELD(payload, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
                    temp_s3 = temp_v0 + 0x20;
                    var_s2 = 1;
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
                    do {
                        temp_a0_2 = func_80069EF8();
                        temp_a1 = M2C_FIELD(temp_v0, void **, 8);
                        temp_init_word = M2C_FIELD(temp_a1, u16 *, 2);
                        var_v1 = temp_a0_2;
                        temp_a2 = temp_init_word - 0x10;
                        if (temp_a0_2 < 0) {
                            var_v1 = temp_a0_2 + 0x1F;
                        }
                        temp_init_word = temp_a0_2 - ((var_v1 >> 5) << 5);
                        temp_init_word = temp_a2 + temp_init_word;
                        M2C_FIELD(temp_a1, u16 *, 2) = (u16) temp_init_word;
                        temp_a0_2 = func_80069EF8(temp_a0_2, temp_a1, temp_a2);
                        temp_a1_2 = M2C_FIELD(temp_v0, void **, 8);
                        temp_init_word = M2C_FIELD(temp_a1_2, u16 *, 6);
                        var_v1_2 = temp_a0_2;
                        temp_a2 = temp_init_word - 0x10;
                        if (temp_a0_2 < 0) {
                            var_v1_2 = temp_a0_2 + 0x1F;
                        }
                        temp_init_word = temp_a0_2 - ((var_v1_2 >> 5) << 5);
                        temp_init_word = temp_a2 + temp_init_word;
                        var_s2 -= 1;
                        M2C_FIELD(temp_a1_2, u16 *, 6) = (u16) temp_init_word;
                    } while (var_s2 >= 0);
                    temp_v0_4 = M2C_FIELD(temp_v0, void **, 8);
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = func_800BCB04(M2C_FIELD(temp_v0_4, u16 *, 2), M2C_FIELD(temp_v0_4, u16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x30));
                    temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
                    if (M2C_FIELD(temp_v1_2, s16 *, 0xA) >= 0x200) {
                        M2C_FIELD(temp_v1_2, s16 *, 0xA) = (s16) M2C_FIELD(arg1, u16 *, 0xA);
                    }
                    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA);
                    temp_a0_2 = 0xC0C0C0;
                    {
                    s32 scale = 0x1400;
                    temp_flags = M2C_FIELD(temp_s0, u16 *, 0x14);
                    M2C_FIELD(temp_s0, s16 *, 0x1E) = (s16) scale;
                    M2C_FIELD(temp_s0, s16 *, 0x1C) = (s16) scale;
                    M2C_FIELD(temp_s0, s16 *, 0x10) = 0;
                    M2C_FIELD(temp_s0, s32 *, 0xC) = temp_a0_2;
                    M2C_FIELD(temp_s0, void **, 0) = spr_page;
                    temp_flags |= 0xC;
                    M2C_FIELD(temp_s0, u16 *, 0x14) = temp_flags;
                    temp_init_word = M2C_FIELD(spr_page, s32 *, 4);
                    }
                    M2C_FIELD(temp_s0, s8 *, 4) = 0;
                    M2C_FIELD(temp_s0, s8 *, 5) = 0;
                    M2C_FIELD(temp_s0, s32 *, 8) = temp_init_word;
                    M2C_FIELD(temp_s3, void **, 0) = arg0;
                    M2C_FIELD(temp_s3, s16 *, 0x4C) = 0;
                }
                var_s4 -= 1;
                if (var_s4 >= 0) {
                    goto first_spawn_loop;
                }
        }
    }
    temp_v1_3 = (s16) M2C_FIELD(arg0, u16 *, 0xA);
    if (temp_v1_3 != 2) {
        if (temp_v1_3 < 3) {
            if (temp_v1_3 != 0) {
                if (temp_v1_3 != 1) {
                    func_800247B4();
                    return;
                }
                goto state_1;
            }
            goto state_0;
        } else if (temp_v1_3 != 0xF0) {
            if (temp_v1_3 < 0xF1) {
                if (temp_v1_3 != 3) {
                    func_800247B4();
                    return;
                }
                var_s4 = 3;
                goto state_3;
            }
            if (temp_v1_3 != 0xFF) {
                func_800247B4();
                return;
            }
            goto state_FF;
        }
        goto state_F0;
    }
    goto state_2;

state_0:
    if (*M2C_FIELD(arg0, u16 **, 4) & 0x80) {
        temp_v0_5 = func_800A05A4(temp_s5, M2C_FIELD(temp_fp, u8 *, 0x24), M2C_FIELD(temp_fp, u8 *, 0x25), (s16) M2C_FIELD(temp_s5, u16 *, 0x2A), (s32) func_800A3820(6));
        M2C_FIELD(temp_s5, void **, 0x60) = temp_v0_5;
        if (temp_v0_5 == NULL) {
            M2C_FIELD(temp_s5, u8 *, 0x72) = (u8) M2C_FIELD(temp_fp, u8 *, 0x24);
            M2C_FIELD(temp_s5, u8 *, 0x73) = (u8) M2C_FIELD(temp_fp, u8 *, 0x25);
            func_80024354();
            return;
        }
        temp_s0 = M2C_FIELD(temp_v0_5, void **, -0x14);
        if (!(M2C_FIELD(temp_s0, u16 *, 0x14) & 0x8000) || !(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(temp_s5, u8 *, 0x72) = (u8) M2C_FIELD(temp_s0, u8 *, 0x24);
            M2C_FIELD(temp_s5, u8 *, 0x73) = (u8) M2C_FIELD(temp_s0, u8 *, 0x25);
            M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(M2C_FIELD(sp20, void **, 8), s32 *, 0);
            M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(M2C_FIELD(sp20, void **, 8), s32 *, 4);
            M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(M2C_FIELD(sp20, void **, 8), s32 *, 8);
            temp_v1_4 = (s8) M2C_FIELD(temp_s5, u8 *, 0x72);
            temp_v0_6 = M2C_FIELD(temp_fp, u8 *, 0x24);
            temp_a0_6 = M2C_FIELD(temp_fp, u8 *, 0x25);
            temp_v1_4 -= temp_v0_6;
            temp_v0_6 = (s8) M2C_FIELD(temp_s5, u8 *, 0x73);
            var_s4 = temp_v1_4;
            if (temp_v1_4 < 0) {
                var_s4 = 0 - var_s4;
            }
            temp_v0_6 -= temp_a0_6;
            var_s2 = temp_v0_6;
            if (temp_v0_6 < 0) {
                var_s2 = 0 - var_s2;
            }
            if (var_s4 < var_s2) {
                var_s4 = var_s2;
            }
            temp_init_word = var_s4 * 4;
            M2C_FIELD(arg0, u16 *, 0x50) = temp_init_word;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (sp24 << 0x14);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (sp28 << 0x14);
            func_800A56E0(0x300);
            temp_init_word = M2C_FIELD(arg0, u16 *, 0xA);
            temp_init_word += 1;
            ASM_TAILSLOT_PIN(temp_init_word);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_80024490();
            return;
        }
        goto state_F0_end;
    }
    return;

state_1:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) >= 0) {
        M2C_FIELD(arg1, s32 *, 0) += M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(arg1, s32 *, 4) += M2C_FIELD(arg1, s32 *, 0x10);
        func_800247B4();
        return;
    }
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0xA);
    ASM_KEEP(temp_v0_6);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    temp_v1_4 = 6;
    ASM_TAILSLOT_PIN(temp_v1_4);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024488();
    return;

state_2:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) <= 0) {
        temp_flags = 0x100000;
        temp_a0_8 = M2C_FIELD(temp_s5, void **, 0x60);
        if (temp_a0_8 == NULL) {
            goto state_null;
        }
        M2C_FIELD(temp_a0_8, s32 *, 0x14) = (s32) (M2C_FIELD(temp_a0_8, s32 *, 0x14) | temp_flags);
        M2C_FIELD(arg0, u16 *, 0x50) = 0x14U;
        M2C_FIELD(arg0, u16 *, 0xA) += 1;
        func_800247B4();
        return;
    }
    return;

state_3:
    temp_s2 = (s16) func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x30));
    do {
        temp_v0 = func_8003FD64(0x312, D_80083498);
        if (temp_v0 != NULL) {
            void *temp_t0;
            func_8004491C(temp_v0, D_80045340);
            temp_s3 = temp_v0 + 0x20;
            temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
            temp_t0 = &D_800248F0;
            M2C_FIELD(temp_v0, void **, 0x10) = temp_t0;
            var_v0_2 = func_80069EF8();
            temp_v1_5 = var_v0_2;
            temp_a1_3 = M2C_FIELD(temp_v0, void **, 8);
            temp_a0_3 = M2C_FIELD(arg1, u16 *, 2);
            M2C_FIELD(temp_s3, u16 *, 0xC) = temp_a0_3;
            if (temp_v1_5 < 0) {
                var_v0_2 = temp_v1_5 + 0x7F;
            }
            M2C_FIELD(temp_a1_3, s16 *, 2) = (s16) ((temp_a0_3 + (temp_v1_5 - ((var_v0_2 >> 7) << 7))) - 0x40);
            var_v0_3 = func_80069EF8((s32) temp_a0_3, temp_a1_3);
            temp_v1_6 = var_v0_3;
            temp_a1_4 = M2C_FIELD(temp_v0, void **, 8);
            temp_a0_4 = M2C_FIELD(arg1, u16 *, 6);
            M2C_FIELD(temp_s3, u16 *, 0xE) = temp_a0_4;
            if (temp_v1_6 < 0) {
                var_v0_3 = temp_v1_6 + 0x7F;
            }
            M2C_FIELD(temp_a1_4, s16 *, 6) = (s16) ((temp_a0_4 + (temp_v1_6 - ((var_v0_3 >> 7) << 7))) - 0x40);
            var_v0_4 = func_80069EF8((s32) temp_a0_4, temp_a1_4);
            temp_v1_7 = var_v0_4;
            temp_a1_3 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_s3, s16 *, 0x10) = temp_s2;
            if (temp_v1_7 < 0) {
                var_v0_4 = temp_v1_7 + 0x3F;
            }
            M2C_FIELD(temp_a1_3, s16 *, 0xA) = (s16) ((temp_s2 + (temp_v1_7 - ((var_v0_4 >> 6) << 6))) - 0x80);
            temp_a0_2 = 0x101010;
            temp_flags = M2C_FIELD(temp_s0, u16 *, 0x14);
            M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_s0, s32 *, 0xC) = temp_a0_2;
            M2C_FIELD(temp_s0, u8 **, 0) = D_800DED70;
            temp_flags |= 0xC;
            M2C_FIELD(temp_s0, u16 *, 0x14) = temp_flags;
            temp_init_word = (s32) M2C_FIELD(D_800DED70, s32 *, 4);
            M2C_FIELD(temp_s0, s8 *, 4) = 0;
            M2C_FIELD(temp_s0, s8 *, 5) = 0;
            M2C_FIELD(temp_s0, s32 *, 8) = temp_init_word;
            M2C_FIELD(temp_v0, void **, 0x20) = arg0;
            M2C_FIELD(temp_s3, s16 *, 0x4C) = 0;
        }
        var_s4 -= 1;
    } while (var_s4 >= 0);
    temp_v0 = M2C_FIELD(temp_s5, void **, 0x60) - 0x20;
    temp_a1_5 = M2C_FIELD(temp_v0, void **, 8);
    temp_v0_6 = M2C_FIELD(temp_a1_5, s16 *, 0xA) - 0x18;
    temp_v0_6 = temp_s2 - temp_v0_6;
    temp_a0_5 = temp_v0_6 / 10;
    M2C_FIELD(temp_a1_5, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(temp_a1_5, s16 *, 0xA) + temp_a0_5);
    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
    if ((u16) M2C_FIELD(temp_s0, u16 *, 0x1C) >= 0x21C1U) {
        M2C_FIELD(temp_s0, u16 *, 0x1C) = 0x2000U;
    }
    temp_v0_2 = func_80069EF8();
    M2C_FIELD(temp_s0, u16 *, 0x1C) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x1C) + ((temp_v0_2 & 0x1FF) + 0x100));
    if ((u16) M2C_FIELD(temp_s0, u16 *, 0x1E) < 0x76CU) {
        M2C_FIELD(temp_s0, u16 *, 0x1E) = 0x800U;
    }
    M2C_FIELD(temp_s0, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x1E) - ((func_80069EF8() & 0xFF) + 0x80));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) > 0) {
        return;
    }
    if (M2C_FIELD(temp_s5, void **, 0x60) != NULL) {
        goto state_3_continue;
    }

state_null:
    M2C_FIELD(arg0, u16 *, 0xA) = 0xFF;
    func_800247B4();
    return;

state_3_continue:
    func_8009CE1C(M2C_FIELD(temp_s5, void **, 0x60), 8, M2C_FIELD(arg0, u8 *, 9), 4, (s32) (s16) M2C_FIELD(temp_s5, u16 *, 0x2A), temp_s5, 2);
    M2C_FIELD(arg0, u16 *, 0x50) = 6U;

state_F0_end:
    M2C_FIELD(arg0, u16 *, 0xA) = 0xF0;
    func_800247B4();
    return;

state_F0:
    temp_s0 = M2C_FIELD(M2C_FIELD(temp_s5, void **, 0x60), void **, -0x14);
    temp_v1_8 = M2C_FIELD(temp_s0, u16 *, 0x1C);
    temp_a0_7 = M2C_FIELD(temp_s0, u16 *, 0x1E);
    M2C_FIELD(temp_s0, u16 *, 0x1C) = (u16) (temp_v1_8 + ((s32) (0x1000 - temp_v1_8) >> 2));
    M2C_FIELD(temp_s0, u16 *, 0x1E) = (u16) (temp_a0_7 + ((s32) (0x1000 - temp_a0_7) >> 2));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) <= 0) {
        M2C_FIELD(temp_s0, u16 *, 0x1E) = 0x1000U;
        M2C_FIELD(temp_s0, u16 *, 0x1C) = 0x1000U;
        M2C_FIELD(arg0, u16 *, 0xA) = 0xFFU;
        M2C_FIELD(M2C_FIELD(temp_s5, void **, 0x60), u32 *, 0x14) &= ~0x100000U;
        func_800247B4();
        return;
    }
    return;

state_FF:
    if (M2C_FIELD(arg0, s16 *, 0x52) & 0x8000) {
        M2C_FIELD(arg0, u16 *, 0x52) &= 0x7FFF;
        func_800247B4();
        return;
    }
    ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    *D_8008346C = 0;
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0[0] |= 0x8000;
}

