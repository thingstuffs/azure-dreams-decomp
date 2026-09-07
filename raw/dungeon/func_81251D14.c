#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s32 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, s32, void *);

extern void func_801718A4() __attribute__((noreturn));
extern void func_801719A0(void) __attribute__((noreturn));
extern void func_801719C0(void *);
extern void func_80171BE0(void *, void *, void *, void *);
extern s32 func_80172330(void *, void *, void *, s32);
extern void func_801736B8(void *, void *, void *, void *);
extern void func_80173D6C(void *, void *, void *);

extern u16 D_80013714;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80171514;
extern u8 D_80173E8C[8];
extern u8 D_80173E94[];
extern u8 D_80173EC4[];
extern u8 D_80173EE4[];

void func_80171514(void *arg0_, void *arg1_, void *arg2_, void *arg3_)
{
    static void *const keepalive[] = {
        &&case_stop, &&case_callback, &&case_action, &&case_default
    };
    register void *obj ASM_REG("$17") = arg0_;
    register void *motion ASM_REG("$19") = arg1_;
    register void *part ASM_REG("$18") = arg2_;
    register void *state ASM_REG("$16") = arg3_;
#define arg0 obj
#define arg1 motion
#define arg2 part
#define arg3 state
    u32 entry_status = D_80083462;
    s32 flags;
    s32 result;
    s32 kind;
    s32 jump_index;
    s32 entry_index;
    u8 *entry_base;
    u8 *entry;
    u8 *animation;
    s16 distance;

    if (entry_status & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 14;
        func_801719C0(arg0);
        func_801719A0();
    }
    ASM_KEEP(obj);
    ASM_KEEP(motion);
    ASM_KEEP(part);
    ASM_KEEP(state);

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, u8 *, 0x2C) == D_80173EC4) {
            FIELD(arg0, u8, 0x9A) = 13;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, u32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            func_801719A0();
        }
        if (func_800AA924(arg0, arg1, arg2, D_80173E94) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_801719A0();
        }

        ASM_KEEP(obj);
        if (FIELD(arg0, u8, 0x9A) != 14) {
            FIELD(arg0, u8, 0x9A) = 14;
        }
        if (FIELD(arg2, u8 *, 0x2C) != D_80173E8C) {
            FIELD(arg2, u8 *, 0x2C) = D_80173E8C;
            func_80047784(
                arg2,
                D_80173E8C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg2, u8, 5) = 1;
            FIELD(arg0, s16, 0xA2) = 0;
            FIELD(arg0, s16, 0x9E) = 0;
        }

        FIELD(arg3, u32, 0x1C) |= 0x40000;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80173EE4) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            u16 old_value;
            u16 amount;

            func_800AA888(arg0, arg1, arg2, arg3);
            old_value = FIELD(arg0, u16, 0x92);
            amount = FIELD(arg0, u16, 0xA2);
            FIELD(arg0, s16, 0xA2) = 0;
            FIELD(arg0, s16, 0x9E) = 0;
            FIELD(arg0, u16, 0x92) = old_value - amount;
            func_801736B8(arg0, arg1, arg2, arg3);
            func_801719A0();
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, u8, 0x26) = result;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            goto case_stop;
        }

        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto case_default;
        }

        if ((FIELD(arg3, u16, 0x46) & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }

            if (D_80013714 & 8) {
                register void *tail_arg ASM_REG("$4");
                u8 tail_flags;

                func_80173D6C(arg0, arg1, arg2);
                tail_flags = FIELD(arg3, u8, 0x71);
                ASM_SCHED_BARRIER();
                tail_arg = arg3;
                ASM_KEEP(tail_arg);
                tail_flags &= 0x7F;
                ASM_KEEP(tail_flags);
                FIELD(arg3, u8, 0x71) = tail_flags;
                func_801718A4(tail_arg);
            }

            if ((s16)func_80172330(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            FIELD(arg3, u16, 0x46) |= 0x4000;
            if ((FIELD(arg3, u16, 0x46) & 0x8000) == 0) {
                goto case_default;
            }
        }

        kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
        jump_index = kind - 1;
        if ((u32)jump_index >= 12U) {
            goto case_default;
        }
        (void)keepalive;
        goto *D_80170808[jump_index];

case_stop:
        func_800A9A0C(arg3);
        func_801719A0();

case_callback:
        FIELD(arg0, void * volatile, 0x8C) = &D_80171514;
        func_800A9A0C(arg3);
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_801719A0();

case_action:
        func_800AAF00(arg0, arg1, arg2, 0, &D_80171514);
        func_801719A0();

case_default:
        func_80171BE0(arg0, arg1, arg2, arg3);
        func_801719A0();
    }

    flags = FIELD(arg3, u32, 0x1C);
    if ((flags & 0x2000) == 0) {
        entry_index = (s8)result;
        if (entry_index >= 0) {
            entry_base = D_800E2970;
            entry = entry_index * 20 + entry_base;
            if (FIELD(entry, u16, 0xC) & 2) {
                return;
            }
        }
        if ((flags & 0x430) == 0) {
            animation = D_80082E80;
            if ((s16)func_8009FD7C(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    animation[0x24], animation[0x25]) != 0) {
                result = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    animation[0x24], animation[0x25], &distance);
                FIELD(arg3, s16, 0x2A) = result;
            }
        }
    }
}
#undef arg0
#undef arg1
#undef arg2
#undef arg3

/* MECHANISM: Natural entry-status initialization plus long-lived pinned arguments yields the retail 0x38 frame/save order.
   A volatile callback-pointer lvalue preserves retail's sw; jal; nop sequence and removes the displacement cascade.
   Separate entry-base/result locals keep the table base in v0 and coalesce the indexed address into v1.
   A scoped a0 tail argument, value barrier, and scheduler fence retain the s0 delay-store base with the move in the load slot. */
