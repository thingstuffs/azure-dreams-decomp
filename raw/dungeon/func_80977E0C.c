#include "common.h"

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30();
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173E00(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern void *D_801708D0[];
extern u8 D_801714D4[];
extern u8 D_801740F0[];
extern u8 D_801740F8[];
extern u8 D_80174150[];
extern u8 D_80174158[];
extern u8 D_80174160[];

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_8017360C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4, &&state_5
    };
    u8 *effect;
    s32 index;
    s32 next_state;
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state >= 6) {
        return;
    }
    (void)jt_keep;
    goto *D_801708D0[state];

state_0:
    {
        u8 *global;
        register u8 *effect_page ASM_REG("$5");
        if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
            return;
        }

        effect_page = (u8 *)0x80170000;
        ASM_KEEP(effect_page);
        effect = effect_page + 0x40F8;
        FIELD(arg2, void *, 0x2C) = effect;
        index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
        index &= 7;
        index += (s32)effect;
        func_80047784(arg2, *(u8 *)index, 0);
        global = (u8 *)&D_80083460;
        FIELD(global, u16, 0xA)--;
        next_state = FIELD(arg0, u8, 0x9B) + 1;
        goto store_state;
    }

state_1:
        if (FIELD(arg0, s16, 0x92) != 0) {
            return;
        }
        {
            register u8 *effect_page ASM_REG("$5");
            effect_page = (u8 *)0x80170000;
            ASM_KEEP(effect_page);
            effect = effect_page + 0x4150;
        }
        goto effect_common;

state_2:
        if ((s16)FIELD(arg0, u16, 0x96)++ < 2) {
            return;
        }
        {
            register u8 *effect_page ASM_REG("$5");
            effect_page = (u8 *)0x80170000;
            ASM_KEEP(effect_page);
            effect = effect_page + 0x4158;
        }
        goto effect_common;

state_3:
        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *global = (u8 *)&D_80083460;
            s32 flags;

            if ((FIELD(global, u16, 2) & 0x1000) != 0) {
                return;
            }

            if ((FIELD(arg3, s16, 0x64) != 0) &&
                func_800AA6B4(arg0, arg1, arg2, 0)) {
                return;
            }

            if (FIELD(arg3, u8, 0x25) == 0) {
                if ((FIELD(global, u16, 2) & 0x2008) != 0) {
                    return;
                }
                func_800AA79C(arg0, arg1, arg2, arg3);
                goto done;
            }

            if ((s16)func_800A2C34(arg3) != 0) {
                return;
            }

            flags = FIELD(arg3, s32, 0x1C);
            if ((flags & 0x100) != 0) {
                func_800AA258(arg0, arg1, arg2, arg3);
                goto done;
            }

            {
            u32 large_flag = 0x80000;
            if ((flags & large_flag) != 0) {
                u16 amount;

                func_800AA888(arg0, arg1, arg2, arg3);
                amount = FIELD(arg0, u16, 0x92);
                amount -= FIELD(arg0, u16, 0xA2);
                FIELD(arg0, u16, 0xA2) = 0;
                FIELD(arg0, u16, 0x9E) = 0;
                FIELD(arg0, u16, 0x92) = amount;
                func_80173E00(arg0, arg1, arg2, arg3);
                goto done;
            }
            }

            if (FIELD(arg3, s8, 0x6D) == 0) {
                return;
            }

            if ((s16)func_800A2C34(arg3) != 0) {
                void *owner = D_800814A8;

                if ((s16)func_8009A180(arg3,
                        (u8 *)FIELD(owner, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }

            func_800A9A0C(arg3);
            func_800A9A04(arg3);
            if ((func_80042900(arg3, 1) << 16) != 0) {
                u8 *room_base = D_80082E80;
                s8 room = FIELD(arg2, s8, 0x26);

                if ((room != FIELD(room_base, s8, 0x26)) || (room < 0)) {
                    if ((s16)func_8009FD40(room_base, arg2) >= 2) {
                        goto final_check;
                    }
                }

                if ((func_800A6D30() & 7) != 0) {
                    goto final_check;
                }
                func_80042B68(arg3, 1);
            }
final_check:
            if ((func_80042900(arg3, 1) << 16) != 0) {
                return;
            }
        }

        {
            register u8 *effect_page ASM_REG("$5");
            effect_page = (u8 *)0x80170000;
            ASM_KEEP(effect_page);
            effect = effect_page + 0x4160;
        }
        FIELD(arg2, void *, 0x2C) = effect;
        index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
        index &= 7;
        index += (s32)effect;
        func_80047784(arg2, *(u8 *)index, 0);
        if ((FIELD(arg2, u16, 0x14) & 0x8000) != 0) {
            goto finished;
        }
        FIELD(arg0, u8, 0x9B)++;
        {
            u8 *global = (u8 *)&D_80083460;
            FIELD(global, u16, 0xA)++;
        }
        goto done;

state_4:
        {
        register u32 phase_flag ASM_REG("$3") = 0x40000;
        register u8 *effect_page ASM_REG("$5");
        u32 phase_flags;

        if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
            return;
        }

        ASM_KEEP(phase_flag);
        effect_page = (u8 *)0x80170000;
        ASM_KEEP(effect_page);
        phase_flags = FIELD(arg3, u32, 0x1C);
        effect = effect_page + 0x40F8;
        phase_flags |= phase_flag;
        FIELD(arg3, u32, 0x1C) = phase_flags;
effect_common:
        FIELD(arg2, void *, 0x2C) = effect;
        index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
        index &= 7;
        index += (s32)effect;
        func_80047784(arg2, *(u8 *)index, 0);
        FIELD(arg0, u16, 0x96) = 0;
        next_state = FIELD(arg0, u8, 0x9B) + 1;
store_state:
        FIELD(arg0, u8, 0x9B) = next_state;
        goto done;
        }

state_5:
        if ((s16)FIELD(arg0, u16, 0x96)++ < 4) {
            return;
        }

        {
            register u8 *effect_page ASM_REG("$5");
            effect_page = (u8 *)0x80170000;
            ASM_KEEP(effect_page);
            effect = effect_page + 0x40F0;
        }
        FIELD(arg2, void *, 0x2C) = effect;
        index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
        index &= 7;
        index += (s32)effect;
        func_80047784(arg2, *(u8 *)index, 0);
        {
            u8 *global = (u8 *)&D_80083460;
            FIELD(global, u16, 0xA)--;
        }

finished:
        FIELD(arg0, void *, 0x8C) = D_801714D4;
done:
        return;
}

/* MECHANISM: retail sets no $a0 for the func_800A6D30 call — on the `bgez` fast path
   $a0 still holds &D_80082E80 (the func_8009FD40 arg base), and the jal delay slot is a
   real nop, so the retail source called it ARG-LESS (K&R decl, zero-arg call). Passing
   arg3 made gcc emit a redundant `move $a0,$s0` into that delay slot (the whole 1-word
   residue two prior runs plateaued on). Rest of the shape: $5-pinned 0x80170000 page base
   per effect table, extern jtbl_D_801708D0 computed-goto dispatch, &D_80083460 held base
   for the 0xA counter RMW. */
