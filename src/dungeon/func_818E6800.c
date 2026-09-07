#include "common.h"

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8();
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800A3820(s32);
extern s32 func_800A05A4(void *, u8, u8, s16, s32);
extern s16 func_800BCB04(s32, s32, s16);
extern void func_800A56E0(s32);
extern void func_80044A50(void *);
extern void func_800419EC(s32, s32);
extern void func_8002506C(s32, s16);
extern s32 func_8009D218(s32, s32, void *);
extern void func_800C8900(s32, s32, s32);

extern void func_800240D0(void) __attribute__((noreturn));
extern void func_80024388(void) __attribute__((noreturn));
extern void func_80024724(void) __attribute__((noreturn));
extern void func_80024728(void) __attribute__((noreturn));
extern void func_80024764(void) __attribute__((noreturn));

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80024C7C[];
extern u8 D_80024B60[];
extern u8 D_80024798[];
extern u8 D_800249DC[];
extern u8 D_800249DC_store[] __asm__("D_800249DC");
extern u8 D_800DECF8[];
extern u8 D_800DECF8_load[] __asm__("D_800DECF8");
extern u8 D_800E3D68[];
extern s32 D_8008346C[3];
extern s32 D_800814A0[3];

#define S8(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_818E6800")
    __attribute__((section(".text.func_818E6800"), aligned(4))) = {
    0x8002401C, 0x10001000, 0x14000E10, 0x18000D48,
    0x0FA01000, 0x0DAC1800, 0x0BB82000,
};
__asm__(".globl func_818E6800\n"
        ".size func_818E6800, 1944");
#define BODY_NAME func_818E681C
#else
#define BODY_NAME func_818E6800
#endif

void BODY_NAME(void *arg0, void *arg1, void * volatile arg2)
    __attribute__((section(".text.func_818E6800")));
void BODY_NAME(void *arg0, void *arg1, void * volatile arg2) {
    u8 *base = (u8 *)arg0;
    register u8 *in ASM_REG("$22") = (u8 *)arg1;   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *obj ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *node;
    u8 *header;
    u8 *item;
    u8 *child;
    register u8 *entry ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 count ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 state;
    s32 dx;
    s32 dy;
    s32 tmp;
    s32 value;
    s32 i;
    s16 scratch[3];

    ASM_CLOBBER("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    {
        register s32 original_count ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        obj = (u8 *)S32(base, 0);
        ASM_KEEP_NV(obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
        original_count = U16(base, 80);
        state = S16(base, 10);
        count = original_count - 1;
        ASM_KEEP(count);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
    node = (u8 *)S32(obj, -20);
    header = obj - 32;

#define arg0 base
#define arg1 in

    U16(arg0, 80) = (u16)count;
    if (state > 0) {
        if (state == 2) goto state_2;
        if (state < 3) {
            if (state == 1) goto state_1;
            count = -1;
            ASM_TAILSLOT_PIN(count);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800240D0();
            return;
        }
        if (state >= 242) goto state_other;
        if (state < 240) goto state_other;
        count = 8;
        ASM_TAILSLOT_PIN(count);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800240D0();
        return;
state_1: {
            register s32 tail_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            tail_value = (s16)count;
            state = 20;
            count = state - tail_value;
            ASM_TAILSLOT_PIN(count);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800240D0();
            return;
        }
state_2:
        count = 8;
        ASM_TAILSLOT_PIN(count);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800240D0();
        return;
state_other:
        count = -1;

        ASM_KEEP(count);   /* MATCH pin: retail schedule: same instructions, different order without it */
        i = count;
        while (i >= 0) {
            item = (u8 *)func_8003FD64(786, D_80083498);
            if (item != 0) {
                func_8004491C(item, D_80045340);
                child = (u8 *)S32(item, 12);
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                {
                    register u8 *callback ASM_REG("$8") = D_800249DC_store;   /* MATCH pin: retail register colouring depends on it */
                    S32(item, 16) = (s32)callback;
                }
                U16(S32(item, 8), 2) = (u16)(U16(arg1, 2) +
                                             (func_80069EF8() & 0x1ff) - 256);
                U16(S32(item, 8), 6) = (u16)(U16(arg1, 6) +
                                             (func_80069EF8() & 0x1ff) - 256);
                U16(S32(item, 8), 10) = (u16)(U16(arg1, 10) +
                                              (func_80069EF8() & 0xf) - 8);
                entry = item + 32;
                S32(entry, 28) = S32(arg1, 0);
                S32(entry, 32) = S32(arg1, 4);
                S32(entry, 36) = S32(arg1, 8);
                S32(entry, 52) = S32(arg1, 12);
                S32(entry, 56) = S32(arg1, 16);
                S32(entry, 60) = S32(arg1, 20);
                U16(entry, 72) = U16(arg0, 80);

                {
                    s32 init_word = 0x101010;
                    s32 flags;
                    register u8 *template ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                    s32 template_word;
                    S16(child, 30) = 4096;
                    S16(child, 28) = 4096;
                    S16(child, 16) = 32;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    flags = U16(child, 20);
                    ASM_KEEP(flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    template = D_800DECF8;
                    S32(child, 12) = init_word;
                    init_word = (s32)template;
                    ASM_KEEP(init_word);   /* MATCH pin: retail delay-slot fill depends on it */
                    S32(child, 0) = (s32)template;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    flags |= 0xc;
                    S16(child, 20) = (u16)flags;
                    template_word = S32((u8 *)init_word, 4);
                    U8(child, 4) = 0;
                    U8(child, 5) = 0;
                    S32(child, 8) = template_word;
                }
                S32(item, 32) = (s32)arg0;
                S16(entry, 76) = 0;
            }
            i--;
        }
    }

    {
    s32 mode = S16(arg0, 10);
    if (mode == 240) goto mode_240;
    if (mode < 241) {
        if (mode == 1) goto mode_1;
        if (mode >= 2) goto mode_ge_2;
        if (mode == 0) goto mode_0;
        func_80024764();
        return;
mode_ge_2:
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        if (mode == 2) goto mode_2;
        func_80024764();
        return;
    }
    if (mode == 255) goto mode_255;
    if (mode < 256) {
        if (mode == 241) goto mode_241;
        func_80024764();
        return;
    }
    if (mode == 256) goto mode_256;
    func_80024764();
    return;

mode_0: {
            s32 found;
            s32 delta_x;
            register s32 delta_y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            s32 abs_y;
            if ((U16(S32(arg0, 4), 0) & 0x80) != 0) {
                if (func_8003DE58(S32(S32(header, 12), 8), S32(header, 12), scratch, 0) == 0) {
                    scratch[1] = 0;
                    scratch[0] = 0;
                    scratch[2] = (U16(node, 20) & 0x8000) ? -48 : 0;
                }
                found = func_800A05A4(obj, U8(node, 36), U8(node, 37), S16(obj, 42),
                                     (s16)func_800A3820(36));
                S32(obj, 96) = found;
                if (found == 0) {
                    U8(obj, 114) = U8(node, 36);
                    U8(obj, 115) = U8(node, 37);
                    func_80024388();
                    return;
                }
                child = (u8 *)S32(found, -20);
                if ((U16(child, 20) & 0x8000) != 0) {
                    register u8 *target_arg2 ASM_REG("$8") = (u8 *)arg2;   /* MATCH pin: retail register colouring depends on it */
                    if ((U16(target_arg2, 20) & 0x8000) != 0) {
                        goto set_state_240;
                    }
                }
                U8(obj, 114) = U8(child, 36);
                U8(obj, 115) = U8(child, 37);
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                {
                    u8 *call_base = arg0 - 32;
                    u8 *callback = D_80024798;
                    S32(arg1, 0) = S32(S32(header, 8), 0) + ((s32)scratch[0] << 16);
                    S32(arg1, 4) = S32(S32(header, 8), 4) + ((s32)scratch[1] << 16);
                    S32(arg1, 8) = S32(S32(header, 8), 8) + ((s32)scratch[2] << 16);
                    func_8004491C(call_base, callback);
                }
                delta_x = S8(obj, 114);
                delta_y = U8(node, 36);
                abs_y = U8(node, 37);
                delta_x -= delta_y;
                delta_y = S8(obj, 115);
                if (delta_x < 0) {
                    i = delta_x;
                    ASM_KEEP_NV(i);   /* MATCH pin: retail register colouring depends on it */
                    i = -i;
                } else {
                    i = delta_x;
                }
                delta_y -= abs_y;
                if (delta_y < 0) {
                    abs_y = delta_y;
                    ASM_KEEP_NV(abs_y);   /* MATCH pin: retail register colouring depends on it */
                    abs_y = -abs_y;
                } else {
                    abs_y = delta_y;
                }
                if (i < abs_y) i = abs_y;
                if (i < 4) i = 4;
                delta_y = i << 2;
                U16(arg0, 80) = (u16)delta_y;
                ASM_KEEP_NV(delta_y);   /* MATCH pin: load-bearing for the whole function shape */
                delta_y = (s16)delta_y;
                abs_y = S8(obj, 114);
                delta_x = S16(arg1, 2);
                abs_y <<= 6;
                i = abs_y + 32;
                delta_x = i - delta_x;
                delta_x /= delta_y;
                delta_y = S8(obj, 115);
                delta_y <<= 6;
                abs_y = delta_y + 32;
                delta_y = S16(arg1, 6);
                S32(arg1, 12) = delta_x << 16;
                delta_x = S16(arg0, 80);
                delta_y = abs_y - delta_y;
                delta_y /= delta_x;
                S32(arg1, 16) = delta_y << 16;
                tmp = (S8(obj, 114) << 6) & 0xffc0;
                value = (S8(obj, 115) << 6) & 0xffc0;
                i = (s16)func_800BCB04(tmp, value, U16(S32(header, 8), 10) - 48) - 192;
                {
                    s32 quotient;
                    s32 divisor;
                    quotient = S16(arg1, 10);
                    divisor = S16(arg0, 80);
                    quotient = (i - quotient) / divisor;
                    S32(arg1, 20) = quotient << 16;
                }
                U16(arg0, 82) = 0;
                func_800A56E0(768);
                {
                    s32 next_state;
                    next_state = (s32)(u16)U16(arg0, 10) + 1;
                    ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_80024728();
                }
                return;
            }
        }
            goto mode_done;

mode_1: {
            s16 frame_counter;
            if (S16(arg0, 80) >= 0) {
                S32(arg1, 0) += S32(arg1, 12);
                S32(arg1, 4) += S32(arg1, 16);
                S32(arg1, 8) += S32(arg1, 20);
            }
            frame_counter = (u16)U16(arg0, 82) + 1;
            U16(arg0, 82) = (u16)frame_counter;
            if (frame_counter >= 8) {
                U16(arg0, 82) = 4;
            }
            if (S16(arg0, 80) <= 0 && S16(arg0, 82) == 7) {
                register s32 new_count ASM_REG("$3") = 8;   /* MATCH pin: retail delay-slot fill depends on it */
                s32 tail_state = U16(arg0, 10);
                ASM_KEEP_DEP_NV(new_count, tail_state);   /* MATCH pin: retail basic-block layout depends on it */
                U16(arg0, 80) = (u16)new_count;
                func_80024724();
                return;
            }
            goto mode_done;
        }

mode_2: {
            u16 frame_counter = (u16)U16(arg0, 82) + 1;
            U16(arg0, 82) = frame_counter;
            if (S16(arg0, 80) == mode) {
                if (S32(obj, 96) != 0) {
                    item = (u8 *)func_8003FD64(770, D_80083498);
                    if (item != 0) {
                        func_8004491C(item, D_80024C7C);
                        S32(item, 16) = (s32)D_80024B60;
                        {
                            s32 coordinate = S8(obj, 114);
                            entry = item + 32;
                            S16(entry, 12) = coordinate << 6;
                            coordinate = S8(obj, 115);
                            S16(entry, 14) = coordinate << 6;
                            S16(entry, 16) = U16(arg1, 10);
                        }
                        S32(item, 32) = (s32)arg0;
                        S16(entry, 76) = 0;
                    }
                }
            }
            if (S16(arg0, 80) <= 0) {
                if (S32(obj, 96) != 0) {
set_state_240:
                    U16(arg0, 10) = 240;
                    func_80024764();
                    return;
                }
                goto cleanup_state;
            }
            goto mode_done;
        }

mode_240:
            func_80044A50(arg0 - 32);
            U16(arg0, 80) = 10;
            func_800419EC(8, 16);
            {
                s32 next_state;
                next_state = (s32)(u16)U16(arg0, 10) + 1;
                ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail delay-slot fill depends on it */
                func_80024728();
            }
            return;

mode_241:
            func_8002506C(S32(obj, 96), S16(arg0, 80));
            if (S16(arg0, 80) == 6 && func_8009D218(S32(obj, 96), 4, obj) == 0 &&
                S32(obj, 96) != 0) {
                func_800C8900(S32(obj, 96), U8(D_800E3D68, 0) == 255 ? 255 : 16, 4);
            }
            if (S16(arg0, 80) > 0) goto mode_done;
cleanup_state:
            func_80044A50(arg0 - 32);
            U16(arg0, 10) = 255;
            func_80024764();
            return;

mode_255:
            value = S32(arg0, 16);
            if ((value & 0x8000) != 0) {
                S32(arg0, 16) = value & ~0x8000;
                func_80024764();
                return;
            } else {
                U16(arg0, 80) = 10;
                U16(arg0, 10) = (u16)(U16(arg0, 10) + 1);
                func_80024764();
                return;
            }

mode_256:
            if (S16(arg0, 80) < 0) {
                D_8008346C[0] = 0;
                U16(arg0, -2) = (u16)(U16(arg0, -2) | 0x8000);
                D_800814A0[0] |= 0x8000;
            }
mode_done:
            ;
    }
#undef arg0
#undef arg1
}
