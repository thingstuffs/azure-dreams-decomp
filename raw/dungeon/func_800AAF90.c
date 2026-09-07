#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u8 *manager;
    u8 pad[0x9C];
    u32 value;
} GlobalSlot;

extern GlobalSlot D_80083160[];
extern s32 (*D_800DEFF0[])(s32, void *, void *);

extern s32 func_8003E12C();
extern s32 func_8004C010();
extern void *func_8004CD28();
extern s32 func_800649A0();
extern s32 func_80064A40();
extern s32 func_80064BC0();
extern s32 func_80064CF0();
extern s32 func_80064D80();
extern s32 func_80065480();
extern s32 func_800654B0();
extern s32 func_80065820();
extern void *func_800B0BE0();

s32 func_800B06F0(u8 *arg0, s32 arg1, u8 *arg2)
{
    register u8 *arg0_r ASM_REG("$22") = arg0;
    register s32 dispatch_arg ASM_REG("$4") = arg1;
    register u8 *arg2_r ASM_REG("$18") = arg2;
    register u8 *transform ASM_REG("$23") = (u8 *)0x1F8000D0;
    GlobalSlot *global_addr = D_80083160;
    register u8 *scratch ASM_REG("$17");
    u8 *manager;
    register u8 *initial_manager ASM_REG("$2");
    register u8 *object ASM_REG("$19");
    register u8 **list ASM_REG("$20");
    register u8 *aux ASM_REG("$21");
    u8 *current;
    u32 screen_x;
    register u32 global_value ASM_REG("$3");
    register s32 flip ASM_REG("$16");
    s16 x;
    s16 y;
    register s32 signed_flags ASM_REG("$3");
    register u8 flags ASM_REG("$7");
    register u8 *current_check ASM_REG("$4");
    register u8 **current_arg ASM_REG("$6");
    register u8 *next_manager ASM_REG("$5");
    register s32 result ASM_REG("$2");
    register u32 scaled_x ASM_REG("$2");
    register s32 coord_offset ASM_REG("$3");
#ifdef NON_MATCHING
    s32 hard_zero = 0;
#else
    register s32 hard_zero ASM_REG("$0");
#endif

    ASM_KEEP_NV(arg0_r);
    ASM_KEEP_NV(dispatch_arg);
    ASM_KEEP(transform);
    global_value = *(volatile u32 *)&global_addr->value;
    ASM_KEEP_NV(global_value);
    initial_manager = D_80083160[0].manager;
    ASM_SET(scratch);
    scratch = (u8 *)0x1F800000;
    FIELD(scratch, u32, 0xEC) = global_value;
    object = FIELD(initial_manager, u8 *, 0x8D0);
    FIELD(scratch, u8 *, 0x20) = initial_manager + 0xB0;

dispatch:
    D_800DEFF0[FIELD(arg0_r, u16, 8) & 1](dispatch_arg, arg2_r, scratch);

    list = FIELD(arg0_r, u8 **, 0);
    screen_x = FIELD(scratch, u32, 0xC0);
    aux = FIELD(arg0_r, u8 *, 4);

    if (screen_x < 0x1E0U) {
        scaled_x = screen_x * 4;
        scaled_x += (u32)FIELD(scratch, u8 *, 0x20);
        FIELD(scratch, u8 *, 0xC0) = (u8 *)scaled_x;
        FIELD(scratch, u16, 0xB8) -= 0xA0;
        FIELD(scratch, u16, 0xBA) -= 0x78;
        func_800649A0(screen_x);

        FIELD(scratch, u16, 0x100) = FIELD(arg2_r, u16, 0x16);
        FIELD(scratch, u16, 0x102) = FIELD(arg2_r, u16, 0x18);
        FIELD(scratch, u16, 0x104) = FIELD(arg2_r, u16, 0x1A);
        FIELD(scratch, u32, 0xE4) = FIELD(arg2_r, u16, 0x20);
        FIELD(scratch, u32, 0xE8) = FIELD(arg2_r, u16, 0x22);
        FIELD(scratch, u32, 0x30) = FIELD(arg2_r, u16, 0x1C);
        FIELD(scratch, u32, 0x34) = FIELD(arg2_r, u16, 0x1E);
        FIELD(scratch, u32, 0x38) = 0x1000;

        func_80065820(scratch + 0x100, transform);
        func_80064BC0(transform, scratch + 0x30);
        func_80064D80(transform);
        func_80064CF0(transform);

        current = *list;
        if (current == 0)
            goto lists_done;
loop:
            FIELD(scratch, u16, 0x8C) = 0;
            FIELD(scratch, u16, 0x84) = 0;
            FIELD(scratch, u16, 0x7C) = 0;
            FIELD(scratch, u16, 0x74) = 0;

            current = (u8 *)((u32)current | 0x80000000U);

            if ((current[0] ^ FIELD(arg2_r, u16, 0x14)) & 1) {
                x = -(s8)current[2] - FIELD(arg2_r, u16, 0x20);
                FIELD(scratch, s16, 0x80) = x;
                FIELD(scratch, s16, 0x70) = x;
                x -= current[0xA];
                goto store_x;
            }

            x = (s8)current[2] - FIELD(arg2_r, u16, 0x20);
            FIELD(scratch, s16, 0x80) = x;
            FIELD(scratch, s16, 0x70) = x;
            coord_offset = current[0xA];
            x = x + coord_offset;
store_x:
            FIELD(scratch, s16, 0x88) = x;
            FIELD(scratch, s16, 0x78) = x;

            if ((current[0] ^ FIELD(arg2_r, u16, 0x14)) & 2) {
                y = -(s8)current[3] - FIELD(arg2_r, u16, 0x22);
                FIELD(scratch, s16, 0x7A) = y;
                FIELD(scratch, s16, 0x72) = y;
                y -= current[0xB];
                goto store_y;
            }

            y = (s8)current[3] - FIELD(arg2_r, u16, 0x22);
            FIELD(scratch, s16, 0x7A) = y;
            FIELD(scratch, s16, 0x72) = y;
            coord_offset = current[0xB];
            y = y + coord_offset;
store_y:
            FIELD(scratch, s16, 0x8A) = y;
            FIELD(scratch, s16, 0x82) = y;
            ASM_KEEP(y);

            func_800654B0(
                scratch + 0x70, scratch + 0x78,
                scratch + 0x80, scratch + 0x88,
                scratch + 0xF0, scratch + 0xF4,
                scratch + 0xF8, scratch + 0xFC,
                scratch + 0x90, scratch + 0x94);

            signed_flags = FIELD(current, s8, 0);
            ASM_KEEP_NV(signed_flags);
            flags = current[0];
            if ((signed_flags >= 0) && (flags & 8)) {
                flip = flags & 4;
                if (func_80065480(
                        FIELD(scratch, u32, 0xF0),
                        FIELD(scratch, u32, 0xF4),
                        FIELD(scratch, u32, 0xF8), flags) <= 0) {
                    if (flip != 0) {
                        goto fallback;
                    }
                    goto check_2c;
                }
                if (flip != 0) {
check_2c:
                    if (current[1] == 0x2C) {
                        aux += 4;
                        goto next_list;
                    }
                    goto next_list;
                }
            }

fallback:
            if (current[0] & 4) {
                func_8003E12C(scratch + 0xF0, scratch + 0xF4);
                func_8003E12C(scratch + 0xF8, scratch + 0xFC);
            }

            FIELD(object, s16, 0x08) = FIELD(scratch, u16, 0xF0) + FIELD(scratch, u16, 0xB8);
            FIELD(object, s16, 0x0A) = FIELD(scratch, u16, 0xF2) + FIELD(scratch, u16, 0xBA);
            FIELD(object, s16, 0x10) = FIELD(scratch, u16, 0xF4) + FIELD(scratch, u16, 0xB8);
            FIELD(object, s16, 0x12) = FIELD(scratch, u16, 0xF6) + FIELD(scratch, u16, 0xBA);
            FIELD(object, s16, 0x18) = FIELD(scratch, u16, 0xF8) + FIELD(scratch, u16, 0xB8);
            FIELD(object, s16, 0x1A) = FIELD(scratch, u16, 0xFA) + FIELD(scratch, u16, 0xBA);
            FIELD(object, s16, 0x20) = FIELD(scratch, u16, 0xFC) + FIELD(scratch, u16, 0xB8);
            current_check = current;
            FIELD(object, s16, 0x22) = FIELD(scratch, u16, 0xFE) + FIELD(scratch, u16, 0xBA);
            current_arg = &current;

            if ((current_check[1] & 0xFC) == 0x2C) {
                object = func_800B0BE0(FIELD(scratch, u32, 0xC0), arg2_r, current_arg, object);
                func_8004C010(object - 0x24, aux);
                if (current != 0) {
                    goto loop;
                }
                aux += 4;
                goto next_list;
            }

            {
                u32 call_x;

                call_x = FIELD(scratch, u32, 0xC0);
                ASM_KEEP_NV(call_x);
                object = func_8004CD28(call_x, arg2_r, current_arg, object);
            }
            ASM_KEEP(object);
            if (current != 0) {
                goto loop;
            }

next_list:
            list++;
            current = *list;
            if (*(u8 * volatile *)&current != 0) {
                goto loop;
            }
lists_done:
        func_80064A40();
    }

    next_manager = FIELD(arg0_r, u8 *, -8);
    if (next_manager == 0) {
        goto done;
    }
    arg0_r = next_manager + 0x20;
    dispatch_arg = FIELD(next_manager, s32, 8);
    arg2_r = FIELD(next_manager, u8 *, 0x0C);
    ASM_KEEP(arg0_r);
    goto dispatch;

done:
    manager = global_addr->manager;
    ASM_KEEP_NV(manager);
    result = hard_zero;
    ASM_KEEP(result);
    FIELD(manager, u8 *, 0x8D0) = object;
    return result;
}
