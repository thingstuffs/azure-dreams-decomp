#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

extern void func_8003DB94();
extern void func_80040AA0(s32);
extern void func_8008CBA0();
extern void func_8008CF6C();
extern s16 func_8009074C();
extern s32 func_80094EA4(void);
extern void func_8009693C(void) __attribute__((noreturn));
extern void func_80096990() __attribute__((noreturn));
extern void func_800969B8();
extern void func_80096AC0();
extern void func_80096C24();
extern s32 func_800973F0();
extern void func_80097898();
extern void func_80097C50();
extern void *func_8009F868();
extern void func_8009F988();
extern s32 func_800A2C34();
extern void func_800A4300();
extern s32 func_800A4474();
extern void func_800A56E0();
extern s32 func_800A6D30(void);

extern u16 D_80013714[];
extern u8 D_800245A8[];
extern u8 D_8004F5F4[];
extern s32 D_80082EB0[];
extern u8 D_80083160[];
extern s16 D_80083228[];
extern u8 D_80083460[];
extern void *D_800DD274[];
extern void (*D_800DD830[])();
extern u8 D_800E3544[];
extern s32 D_800E4940[];

void func_80096384(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_a0;
    register s32 kind ASM_REG("$2");
    s32 angle_target;
    s32 normalized;
    register s32 sign_tmp ASM_REG("$3");
    s32 signed_target;
    s32 current_s;
    u32 current_u;
    s32 var_v0_4;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_v0_3;
    u32 tail_data_flags;
    u16 temp_a1;
    u16 temp_v1_2;
    u16 temp_v1_5;
    u16 temp_v1_6;
    u8 *temp_a1_2;
    void *temp_v0_2;
    u8 *temp_s5 = D_80083160;
    u8 *temp_s4;
    register u16 *flags_page ASM_REG("$4");
    s32 flags;
    s32 temp_s4_value = 0x32;
    s32 temp_state;

    if (FIELD(arg0, u8, 0x9A) != temp_s4_value) {
        FIELD(arg2, void *, 0x2C) = D_800DD274;
        func_8003DB94(arg2,
            *(void **)((u8 *)D_800DD274 +
                ((((s32)(FIELD(temp_s5, s16, 0xC8) +
                    FIELD(arg3, s16, 0x2A) + 0x100)) >> 7) & 0x1C)),
            0);
        FIELD(arg0, u8, 0x9A) = temp_s4_value;
        FIELD(arg0, u16, 0xA2) &= 0xFEFF;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, s8, 0x9B) = 0;
        FIELD(arg0, s16, 0x96) = 0;
        func_800A4300(arg2, arg3);
    }

    temp_s4 = D_80083460;
    FIELD(temp_s4, u16, 2) &= 0xFF7F;
    temp_v0 = FIELD(arg3, s16, 0x64);
    if (temp_v0 < 0) {
        func_80097898(arg0, arg1, arg2, arg3);
        func_80096990();
    }
    if (temp_v0 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }

    temp_v1 = FIELD(arg3, s32, 0x14);
    if (temp_v1 & 0x20000) {
        FIELD(arg3, s32, 0x14) = temp_v1 & 0xFFFDFFFF;
    }

    temp_v1_2 = FIELD(arg0, u16, 0xA2);
    if (!(temp_v1_2 & 0x10)) {
        func_80096AC0(arg0, arg1, arg2, arg3);
        func_80096990();
    }

    temp_a0 = FIELD(arg3, s32, 0x1C);
    if (temp_a0 & 0x200) {
        func_80097C50(arg0, arg1, arg2, arg3);
        func_80096990();
    }

    if (!(FIELD(temp_s4, u16, 2) & 4)) {
        if (!(temp_a0 & 0x20)) {
            ASM_SCHED_BARRIER();
            flags_page = (u16 *)0x80010000;
            ASM_KEEP_NV(flags_page);
            flags = flags_page[0x1B8A];
            if (flags & 1) {
                FIELD(arg0, u16, 0xA2) = temp_v1_2 & 0xFFFE;
                if (temp_v1_2 & 0x200) {
                    FIELD(arg0, u16, 0xA2) = temp_v1_2 & 0xFDFE;
                }

                temp_v0_2 = func_8009F868(flags);
                if (temp_v0_2 != 0) {
                    kind = FIELD(temp_v0_2, u8, 1) & 7;
                    temp_a1 = FIELD(arg3, u16, 0x2A);
                    ASM_KEEP_NV(kind);
                    kind &= 0xFF;
                    temp_a0 = kind << 9;
                    ASM_KEEP_NV(temp_a0);
                    sign_tmp = temp_a1 & 0xFFF;
                    ASM_KEEP_NV(sign_tmp);
                    angle_target = temp_a0;
                    ASM_KEEP_NV(angle_target);
                    FIELD(arg3, u16, 0x2A) = sign_tmp;

                    if (sign_tmp != angle_target) {
                        normalized = temp_a1 & 0x800;
                        if (!normalized) {
                            normalized = temp_a1 & 0x7FF;
                        } else {
                            normalized = sign_tmp | 0xF800;
                        }
                        FIELD(arg3, u16, 0x2A) = normalized;

                        normalized = temp_a0 & 0x800;
                        if (!normalized) {
                            normalized = temp_a0 & 0x7FF;
                        } else {
                            normalized = temp_a0 | 0xF800;
                        }
                        temp_a0 = normalized;
                        ASM_KEEP_NV(temp_a0);
                        sign_tmp = temp_a0 << 16;
                        ASM_KEEP_NV(sign_tmp);
                        signed_target = sign_tmp >> 16;
                        ASM_MEM_BARRIER();
                        current_s = FIELD(arg3, s16, 0x2A);
                        current_u = FIELD(arg3, u16, 0x2A);
                        var_v0_3 = current_s - signed_target;
                        if (var_v0_3 < 0) {
                            var_v0_3 = 0 - var_v0_3;
                        }
                        if (var_v0_3 >= 0x801) {
                            FIELD(arg3, u16, 0x2A) = (u16)
                                ((temp_a0 & ~0xFFF) | (current_u & 0xFFF));
                        }
                        ASM_MEM_BARRIER();
                        current_s = FIELD(arg3, s16, 0x2A);
                        ASM_KEEP_NV(current_s);
                        current_u = FIELD(arg3, u16, 0x2A);
                        ASM_KEEP_NV(current_u);
                        var_v0_4 = signed_target < current_s;
                        if (!var_v0_4) {
                            var_v0_4 = current_u + 0x200;
                        } else {
                            var_v0_4 = current_u - 0x200;
                        }
                        FIELD(arg3, u16, 0x2A) = var_v0_4;
                        func_8009F988(temp_a0, signed_target);
                        func_8009693C();
                    }

                    D_800E3544[0] = FIELD(temp_v0_2, u8, 1) & 0xF8;
                    temp_state = D_800E3544[0];
                    if (temp_state != 0x10) {
                        if (temp_state < 0x11) {
                            if (temp_state != 8) {
                                func_8009693C();
                            }
                            goto block_state_8;
                        }
                        if (temp_state != 0x18) {
                            if (temp_state != 0xD8) {
                                func_8009693C();
                            }
                            goto block_state_D8;
                        }
                        goto block_state_18;
                    }
                    goto block_state_10;
block_state_8:
                    func_80096C24(arg0, arg1, arg2, arg3);
                    func_80096990();
block_state_10:
                    func_800969B8(arg0, arg1, arg2, arg3);
                    func_80096990();
block_state_18:
                    func_800973F0(arg0, arg1, arg2, arg3);
                    func_8009693C();
block_state_D8:
                    D_800DD830[FIELD(temp_v0_2, u8, 0) & 0x7F]();
                    func_8009693C();
                }
            } else {
                D_800E3544[0] = 0;
                if (flags & 4) {
                    func_80040AA0(3);
                    func_80096990();
                }

                if ((func_80094EA4() << 16) != 0) {
                    FIELD(arg0, s16, 0xA4) = 0;
                }

                if ((FIELD(arg0, u16, 0xA2) & 0x200) &&
                    ((func_800A2C34(arg3) << 16) == 0) &&
                    !(FIELD(temp_s4, u16, 2) & 4) &&
                    ((func_800A4474(FIELD(arg2, u8, 0x24),
                        FIELD(arg2, u8, 0x25)) << 16) != 0)) {
                    FIELD(arg0, u16, 0xA2) &= 0xFDFF;
                    func_8008CF6C(arg0, arg1, arg2, D_800245A8);
                    func_80096990();
                }

                if (FIELD(temp_s5, s32, 8) & 0x80) {
                    FIELD(arg3, s16, 0x8A) = 2;
                    D_800E4940[0] = 2;
                    func_8008CF6C(arg0, arg1, arg2, D_8004F5F4);
                    D_80082EB0[0] = 0;
                    FIELD(arg0, s32, 0xC8) = 0;
                    FIELD(arg0, s32, 0x104) = 0;
                    func_80096990();
                }

                ASM_SCHED_BARRIER();
                temp_a1_2 = (u8 *)arg0 + 0xA2;
                if (FIELD(temp_s5, s32, 8) & 3) {
                    func_800A56E0(0x506, temp_a1_2);
                    func_80096990();
                }

                temp_v0_3 = func_8009074C(FIELD(arg0, s16, 0x9E),
                    temp_a1_2, (u8 *)arg3 + 0x2A);
                if (temp_v0_3 != 0xFFF) {
                    FIELD(arg3, s16, 0x2A) = temp_v0_3;
                    if (!(FIELD(temp_s5, s32, 8) & 0x10)) {
                        temp_v1_5 = FIELD(arg0, u16, 0xA2);
                        if (!(temp_v1_5 & 0x400)) {
                            FIELD(arg0, u16, 0xA2) = temp_v1_5 & 0xFFFE;
                            if (FIELD(arg3, s32, 0x1C) & 0x400) {
                                FIELD(arg3, s16, 0x2A) =
                                    FIELD(arg3, u16, 0x2A) +
                                    (func_800A6D30() & 0xE00);
                            }
                            func_80096C24(arg0, arg1, arg2, arg3);
                            if (FIELD(arg0, u8, 0x9A) != 0x32) {
                                func_80096990();
                            }
                            goto block_78;
                        }
                    }
                    FIELD(arg0, s16, 0x96) = 0;
                }

block_78:
                tail_data_flags = FIELD(temp_s5, u32, 8);
                if ((tail_data_flags & 0x30) == 0x30) {
                    FIELD(arg0, u16, 0xA2) &= 0xFFFE;
                    func_800969B8(arg0, arg1, arg2, arg3);
                    func_80096990();
                }

                temp_v1_6 = FIELD(arg0, u16, 0xA2);
                temp_v0_4 = temp_v1_6 & 0x40;
                if (temp_v0_4 != 0) {
                    temp_v0_4 = tail_data_flags & 0x40;
                    if (temp_v0_4 == 0) {
                        FIELD(arg0, u16, 0xA2) = temp_v1_6 & 0xFFBF;
                        func_8009693C();
                    }
                    goto block_88;
                }
                temp_v0_4 = tail_data_flags & 0x40;
                if (temp_v0_4 == 0) {
                    goto block_87;
                }
                FIELD(arg0, u16, 0xA2) = temp_v1_6 & 0xFFFE;
                if ((func_800973F0(arg0, arg1, arg2, arg3) << 16) != 0) {
                    return;
                }
                goto block_87;
            }
        } else {
            goto block_state_10;
        }
        } else {
block_87:
        temp_v1_6 = FIELD(arg0, u16, 0xA2);
block_88:
        if (temp_v1_6 & 1) {
            FIELD(arg0, u16, 0xA2) = temp_v1_6 & 0xFFFE;
            FIELD(arg2, void *, 0x2C) = D_800DD274;
            func_8003DB94(arg2,
                *(void **)((u8 *)D_800DD274 +
                    ((((s32)(D_80083228[0] + FIELD(arg3, s16, 0x2A) +
                        0x100)) >> 7) & 0x1C)),
                0);
        }
    }
}
