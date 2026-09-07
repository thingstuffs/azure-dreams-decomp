#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern void func_800240EC(void) __attribute__((noreturn));
extern void func_800242C8(void) __attribute__((noreturn));
extern void func_80024430(void) __attribute__((noreturn));
extern void func_80024504() __attribute__((noreturn));
extern void func_80024560(void) __attribute__((noreturn));
extern void func_80024784(void *, s32);
extern void func_800419EC(s32, s32);
extern void *func_800A05A4();
extern s32 func_800A3820(s32);
extern s32 func_8009D218(void *, s32, void *);
extern void func_800A56E0(s32);
extern s32 func_800BCB04(s32, s32, s32);
extern void func_800C8900(void *, s32, s32);

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DEC28[];
extern u8 D_800E3D68[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];
extern void func_80024594(void);

#ifdef __mips__
void func_818E0800(void);
static const u32 split_prefix[] __asm__("func_818E0800")
    __attribute__((section(".text.func_818E0800"), aligned(4))) = {
    0x8002401C, 0x10001000, 0x14000E10, 0x18000D48,
    0x0FA01000, 0x0DAC1800, 0x0BB82000,
};
__asm__(".globl func_818E0800\n"
        ".size func_818E0800, 1428");
#define BODY_NAME func_818E081C
#else
#define BODY_NAME func_818E0800
#endif

void BODY_NAME(void *arg0_param, void *arg1_param, void *arg2)
{
    register void *arg0 ASM_REG("$21") = arg0_param;
    register void *arg1 ASM_REG("$19") = arg1_param;
    register void *object ASM_REG("$20");
    register void *base ASM_REG("$23");
    register void *alternate ASM_REG("$18");
    register void *raw_alternate ASM_REG("$2");
    register void *state ASM_REG("$17");
    register void *work ASM_REG("$16");
    register void *page;
    register s32 count ASM_REG("$22");
    register void *header;
    register s32 timer;
    s32 initial_state;
    s32 dispatch_state;
    s32 value;
    s32 result;

    object = FIELD(arg0, void *, 0);
    ASM_SCHED_BARRIER();
    timer = FIELD(arg0, u16, 0x50);
    header = FIELD(object, void *, -0x14);
    timer -= 1;
    ASM_USE_NV(timer);
    initial_state = FIELD(arg0, s16, 0xA);
    FIELD(arg0, u16, 0x50) = timer;
    base = (u8 *)object - 0x20;

    if (initial_state == 2) {
        raw_alternate = FIELD(object, void *, 0x60);
        ASM_KEEP_NV(arg0);
        ASM_KEEP_NV(arg1);
        if (raw_alternate == 0) {
            ASM_KEEP(base);
            FIELD(arg1, s32, 0) =
                FIELD(FIELD(base, void *, 8), s32, 0);
            FIELD(arg1, s32, 4) =
                FIELD(FIELD(base, void *, 8), s32, 4);
            raw_alternate = FIELD(base, void *, 8);
            ASM_KEEP(raw_alternate);
            return func_800240EC();
        }
        alternate = (u8 *)raw_alternate - 0x20;
        FIELD(arg1, s32, 0) = FIELD(FIELD(alternate, void *, 8), s32, 0);
        FIELD(arg1, s32, 4) = FIELD(FIELD(alternate, void *, 8), s32, 4);
        FIELD(arg1, s32, 8) = FIELD(FIELD(alternate, void *, 8), s32, 8);
        ASM_SCHED_BARRIER();

        count = 5;
        page = D_800DEC28;
        do {
            alternate = func_8003FD64(0x312, D_80083498);
            if (alternate != 0) {
                func_8004491C(alternate, &D_80045340);
                state = FIELD(alternate, void *, 0xC);
                FIELD(alternate, void *, 0x10) = func_80024594;
                work = (u8 *)alternate + 0x20;
                FIELD(work, u16, 0xC) = FIELD(arg1, u16, 2);
                FIELD(work, u16, 0xE) = FIELD(arg1, u16, 6);
                {
                    register s32 span ASM_REG("$2");
                    span = FIELD(arg1, u16, 0xA);
                    FIELD(work, u16, 0x48) = 0;
                    FIELD(work, u16, 0x16) = 0;
                    FIELD(work, u16, 0x14) = 0;
                    ASM_USE_NV(span);
                    span += 0x10;
                    FIELD(work, u16, 0x10) = span;
                }
                FIELD(work, u16, 0x18) = func_80069EF8();
                FIELD(state, u16, 0x1E) = 0x1000;
                FIELD(state, u16, 0x1C) = 0x1000;
                FIELD(state, u16, 0x10) = 0x60;
                FIELD(state, void *, 0) = page;
                FIELD(state, u16, 0x14) |= 0xC;
                FIELD(state, void *, 8) = FIELD(page, void *, 4);
                FIELD(state, u8, 4) = 0;
                FIELD(state, u8, 5) = 0;
                FIELD(alternate, void *, 0x20) = arg0;
                FIELD(work, u16, 0x4C) = 0;
            }
            count -= 1;
        } while (count >= 0);
    }

    dispatch_state = FIELD(arg0, s16, 0xA);
    if (dispatch_state == 2) {
        goto dispatch_case_2;
    }
    if (dispatch_state >= 3) {
        goto dispatch_high;
    }
    if (dispatch_state == 0) {
        goto dispatch_case_0;
    }
    if (dispatch_state == 1) {
        goto dispatch_case_1;
    }
    return func_80024560();

dispatch_high:
    if (dispatch_state == 0xF0) {
        goto dispatch_case_f0;
    }
    if (dispatch_state == 0xFF) {
        goto dispatch_case_ff;
    }
    return func_80024560();

dispatch_case_0:
        if (!(FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80)) {
            return;
        }
        result = (s32)func_800A05A4(
            object, FIELD(header, u8, 0x24), FIELD(header, u8, 0x25),
            FIELD(object, s16, 0x2A),
            (s16)func_800A3820(0x23));
        FIELD(object, void *, 0x60) = result;
        if (result == 0) {
            FIELD(object, u8, 0x72) = FIELD(header, u8, 0x24);
            FIELD(object, u8, 0x73) = FIELD(header, u8, 0x25);
            return func_800242C8();
        }

        state = FIELD(result, void *, -0x14);
        if (FIELD(state, u16, 0x14) & 0x8000) {
            if (FIELD(arg2, u16, 0x14) & 0x8000) {
                goto state_f0;
            }
        }
        FIELD(object, u8, 0x72) = FIELD(state, u8, 0x24);
        FIELD(object, u8, 0x73) = FIELD(state, u8, 0x25);
        FIELD(arg1, u16, 2) =
            FIELD(FIELD(base, void *, 8), u16, 2);
        FIELD(arg1, u16, 6) =
            FIELD(FIELD(base, void *, 8), u16, 6);
        FIELD(arg1, u16, 0xA) =
            FIELD(FIELD(base, void *, 8), u16, 0xA);
        FIELD(arg0, u16, 0x50) = 8;

        {
            s32 scaled = FIELD(object, s8, 0x72);
            s32 coord = FIELD(arg1, u16, 2);
            scaled <<= 6;
            coord -= 0x20;
            scaled -= coord;
            FIELD(arg1, s16, 0xE) = scaled;
        }
        FIELD(arg1, s32, 0xC) /= FIELD(arg0, s16, 0x50);
        ASM_SCHED_BARRIER();
        {
            s32 scaled = FIELD(object, s8, 0x73);
            s32 coord = FIELD(arg1, u16, 6);
            scaled <<= 6;
            coord -= 0x20;
            scaled -= coord;
            FIELD(arg1, s16, 0x12) = scaled;
        }
        FIELD(arg1, s32, 0x10) /= FIELD(arg0, s16, 0x50);
        value = (s16)(FIELD(FIELD(base, void *, 8), u16, 0xA) - 0x30);
        result = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), value);
        FIELD(arg1, s16, 0x16) = result - FIELD(arg1, u16, 0xA);
        FIELD(arg1, s32, 0x14) /= FIELD(arg0, s16, 0x50);
        func_800A56E0(0x300);
        {
            register s32 next_state ASM_REG("$2");
            next_state = FIELD(arg0, u16, 0xA);
            next_state += 1;
            ASM_TAILSLOT_PIN(next_state);
            return func_80024430();
        }

dispatch_case_1: {
        s32 next_timer;
        FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
        FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
        if (FIELD(arg0, s16, 0x50) > 0) {
            return;
        }
        if (FIELD(object, void *, 0x60) != 0) {
            next_timer = 24;
        } else {
            next_timer = 10;
        }
        FIELD(arg0, s16, 0x50) = next_timer;
        FIELD(arg0, u16, 0xA) += 1;
        return func_80024560();
    }

dispatch_case_2: {
        register s32 action ASM_REG("$4");
        void *case_alternate;
        if (FIELD(arg0, s16, 0x50) > 0) {
            return;
        }
        ASM_SCHED_BARRIER();
        case_alternate = FIELD(object, void *, 0x60);
        action = 8;
        if (case_alternate == 0) {
            ASM_KEEP_NV(action);
            FIELD(arg0, s16, 0x50) = 10;
            return func_80024504(action);
        }
        ASM_KEEP_NV(action);
        func_800419EC(action, 0x10);
        FIELD(arg0, s16, 0x50) = 6;
state_f0:
        FIELD(arg0, u16, 0xA) = 0xF0;
        return func_80024560();
    }

dispatch_case_f0:
        func_80024784(FIELD(object, void *, 0x60), FIELD(arg0, s16, 0x50));
        if (FIELD(arg0, s16, 0x50) == 2 &&
            !func_8009D218(FIELD(object, void *, 0x60), 2, object)) {
            if (FIELD(FIELD(object, void *, 0x60), s32, 0x14) & 1) {
                if (FIELD(object, void *, 0x60) != 0) {
                    value = (FIELD(D_800E3D68, u8, 0) == 0xFF) ? 0xFF : 0x10;
                    func_800C8900(FIELD(object, void *, 0x60), value, 2);
                }
            }
        }
        if (FIELD(arg0, s16, 0x50) > 0) {
            return;
        }
        ASM_SCHED_BARRIER();
        FIELD(arg0, u16, 0xA) = 0xFF;
        return func_80024560();

dispatch_case_ff:
        if (FIELD(arg0, s16, 0x52) & 0x8000) {
            FIELD(arg0, u16, 0x52) &= 0x7FFF;
            return func_80024560();
        }
        if (FIELD(arg0, s16, 0x50) > 0) {
            return;
        }
        D_8008346C[0] = 0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;

}
