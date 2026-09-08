#include "common.h"

typedef struct S_800B06F0_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0xC];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x34];
    s16 unk_70;
    s16 unk_72;
    u16 unk_74;
    u8 pad_76[0x4];
    s16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    u16 unk_84;
    u8 pad_86[0x4];
    s16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    union { u32 i; u8 * p; } unk_C0;   /* accessed as both */
    u8 pad_C4[0x20];
    u32 unk_E4;
    u32 unk_E8;
    u32 unk_EC;
    union { struct { u32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F0;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F4;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F8;   /* overlapping accesses */
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_800B06F0_0;   /* scratch in func_800B06F0 */

typedef struct S_800B06F0_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800B06F0_1;   /* initial_manager in func_800B06F0 */

typedef struct S_800B06F0_2_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800B06F0_2_pre;   /* the 0x8 bytes before arg0_r in func_800B06F0, addressed as arg0_r[-1] */

typedef struct S_800B06F0_2 {
    u8 ** unk_00;
    u8 * unk_04;
    u16 unk_08;
} S_800B06F0_2;   /* arg0_r in func_800B06F0 */

typedef struct S_800B06F0_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_800B06F0_3;   /* arg2_r in func_800B06F0 */

typedef struct S_800B06F0_4 {
    s8 unk_00;
} S_800B06F0_4;   /* current in func_800B06F0 */

typedef struct S_800B06F0_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x4];
    s16 unk_20;
    s16 unk_22;
} S_800B06F0_5;   /* object in func_800B06F0 */

typedef struct S_800B06F0_6 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 * unk_0C;
} S_800B06F0_6;   /* next_manager in func_800B06F0 */

typedef struct S_800B06F0_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800B06F0_7;   /* manager in func_800B06F0 */



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
    u8 *arg0_r = arg0;
    s32 dispatch_arg = arg1;
    u8 *arg2_r = arg2;
    u8 *transform = (u8 *)0x1F8000D0;
    GlobalSlot *global_addr = D_80083160;
    u8 *scratch;
    u8 *manager;
    u8 *initial_manager;
    u8 *object;
    register u8 **list ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *aux;
    u8 *current;
    u32 screen_x;
    u32 global_value;
    register s32 flip ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 x;
    s16 y;
    s32 signed_flags;
    register u8 flags ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *current_check;
    u8 **current_arg;
    u8 *next_manager;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 scaled_x;
    s32 coord_offset;
#ifdef NON_MATCHING
    s32 hard_zero = 0;
#else
    register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#endif

    global_value = *(volatile u32 *)&global_addr->value;
    initial_manager = D_80083160[0].manager;
    ASM_SET(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    scratch = (u8 *)0x1F800000;
    ((S_800B06F0_0 *)scratch)->unk_EC = global_value;
    object = ((S_800B06F0_1 *)initial_manager)->unk_8D0;
    ((S_800B06F0_0 *)scratch)->unk_20 = initial_manager + 0xB0;

dispatch:
    D_800DEFF0[((S_800B06F0_2 *)arg0_r)->unk_08 & 1](dispatch_arg, arg2_r, scratch);

    list = ((S_800B06F0_2 *)arg0_r)->unk_00;
    screen_x = ((S_800B06F0_0 *)scratch)->unk_C0.i;
    aux = ((S_800B06F0_2 *)arg0_r)->unk_04;

    if (screen_x < 0x1E0U) {
        scaled_x = screen_x * 4;
        scaled_x += (u32)((S_800B06F0_0 *)scratch)->unk_20;
        ((S_800B06F0_0 *)scratch)->unk_C0.p = (u8 *)scaled_x;
        ((S_800B06F0_0 *)scratch)->unk_B8 -= 0xA0;
        ((S_800B06F0_0 *)scratch)->unk_BA -= 0x78;
        func_800649A0(screen_x);

        ((S_800B06F0_0 *)scratch)->unk_100 = ((S_800B06F0_3 *)arg2_r)->unk_16;
        ((S_800B06F0_0 *)scratch)->unk_102 = ((S_800B06F0_3 *)arg2_r)->unk_18;
        ((S_800B06F0_0 *)scratch)->unk_104 = ((S_800B06F0_3 *)arg2_r)->unk_1A;
        ((S_800B06F0_0 *)scratch)->unk_E4 = ((S_800B06F0_3 *)arg2_r)->unk_20;
        ((S_800B06F0_0 *)scratch)->unk_E8 = ((S_800B06F0_3 *)arg2_r)->unk_22;
        ((S_800B06F0_0 *)scratch)->unk_30 = ((S_800B06F0_3 *)arg2_r)->unk_1C;
        ((S_800B06F0_0 *)scratch)->unk_34 = ((S_800B06F0_3 *)arg2_r)->unk_1E;
        ((S_800B06F0_0 *)scratch)->unk_38 = 0x1000;

        func_80065820(scratch + 0x100, transform);
        func_80064BC0(transform, scratch + 0x30);
        func_80064D80(transform);
        func_80064CF0(transform);

        current = *list;
        if (current == 0)
            goto lists_done;
loop:
            ((S_800B06F0_0 *)scratch)->unk_8C = 0;
            ((S_800B06F0_0 *)scratch)->unk_84 = 0;
            ((S_800B06F0_0 *)scratch)->unk_7C = 0;
            ((S_800B06F0_0 *)scratch)->unk_74 = 0;

            current = (u8 *)((u32)current | 0x80000000U);

            if ((current[0] ^ ((S_800B06F0_3 *)arg2_r)->unk_14) & 1) {
                x = -(s8)current[2] - ((S_800B06F0_3 *)arg2_r)->unk_20;
                ((S_800B06F0_0 *)scratch)->unk_80 = x;
                ((S_800B06F0_0 *)scratch)->unk_70 = x;
                x -= current[0xA];
                goto store_x;
            }

            x = (s8)current[2] - ((S_800B06F0_3 *)arg2_r)->unk_20;
            ((S_800B06F0_0 *)scratch)->unk_80 = x;
            ((S_800B06F0_0 *)scratch)->unk_70 = x;
            coord_offset = current[0xA];
            x = x + coord_offset;
store_x:
            (*(s16 *)((u8 *)scratch + 0x88)) = x;
            (*(s16 *)((u8 *)scratch + 0x78)) = x;

            if ((current[0] ^ ((S_800B06F0_3 *)arg2_r)->unk_14) & 2) {
                y = -(s8)current[3] - ((S_800B06F0_3 *)arg2_r)->unk_22;
                ((S_800B06F0_0 *)scratch)->unk_7A = y;
                ((S_800B06F0_0 *)scratch)->unk_72 = y;
                y -= current[0xB];
                goto store_y;
            }

            y = (s8)current[3] - ((S_800B06F0_3 *)arg2_r)->unk_22;
            ((S_800B06F0_0 *)scratch)->unk_7A = y;
            ((S_800B06F0_0 *)scratch)->unk_72 = y;
            coord_offset = current[0xB];
            y = y + coord_offset;
store_y:
            ((S_800B06F0_0 *)scratch)->unk_8A = y;
            ((S_800B06F0_0 *)scratch)->unk_82 = y;
            ASM_KEEP(y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

            func_800654B0(
                scratch + 0x70, scratch + 0x78,
                scratch + 0x80, scratch + 0x88,
                scratch + 0xF0, scratch + 0xF4,
                scratch + 0xF8, scratch + 0xFC,
                scratch + 0x90, scratch + 0x94);

            signed_flags = ((S_800B06F0_4 *)current)->unk_00;
            flags = current[0];
            if ((signed_flags >= 0) && (flags & 8)) {
                flip = flags & 4;
                if (func_80065480(
                        ((S_800B06F0_0 *)scratch)->unk_F0.at00.v,
                        ((S_800B06F0_0 *)scratch)->unk_F4.at00.v,
                        ((S_800B06F0_0 *)scratch)->unk_F8.at00.v, flags) <= 0) {
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

            ((S_800B06F0_5 *)object)->unk_08 = ((S_800B06F0_0 *)scratch)->unk_F0.at00u.v + ((S_800B06F0_0 *)scratch)->unk_B8;
            ((S_800B06F0_5 *)object)->unk_0A = ((S_800B06F0_0 *)scratch)->unk_F0.at02.v + ((S_800B06F0_0 *)scratch)->unk_BA;
            ((S_800B06F0_5 *)object)->unk_10 = ((S_800B06F0_0 *)scratch)->unk_F4.at00u.v + ((S_800B06F0_0 *)scratch)->unk_B8;
            ((S_800B06F0_5 *)object)->unk_12 = ((S_800B06F0_0 *)scratch)->unk_F4.at02.v + ((S_800B06F0_0 *)scratch)->unk_BA;
            ((S_800B06F0_5 *)object)->unk_18 = ((S_800B06F0_0 *)scratch)->unk_F8.at00u.v + ((S_800B06F0_0 *)scratch)->unk_B8;
            ((S_800B06F0_5 *)object)->unk_1A = ((S_800B06F0_0 *)scratch)->unk_F8.at02.v + ((S_800B06F0_0 *)scratch)->unk_BA;
            ((S_800B06F0_5 *)object)->unk_20 = ((S_800B06F0_0 *)scratch)->unk_FC + ((S_800B06F0_0 *)scratch)->unk_B8;
            current_check = current;
            ((S_800B06F0_5 *)object)->unk_22 = ((S_800B06F0_0 *)scratch)->unk_FE + ((S_800B06F0_0 *)scratch)->unk_BA;
            current_arg = &current;

            if ((current_check[1] & 0xFC) == 0x2C) {
                object = func_800B0BE0(((S_800B06F0_0 *)scratch)->unk_C0.i, arg2_r, current_arg, object);
                func_8004C010(object - 0x24, aux);
                if (current != 0) {
                    goto loop;
                }
                aux += 4;
                goto next_list;
            }

            {
                u32 call_x;

                call_x = ((S_800B06F0_0 *)scratch)->unk_C0.i;
                ASM_KEEP_NV(call_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                object = func_8004CD28(call_x, arg2_r, current_arg, object);
            }
            ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
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

    next_manager = ((S_800B06F0_2_pre *)arg0_r)[-1].unk_00;
    if (next_manager == 0) {
        goto done;
    }
    arg0_r = next_manager + 0x20;
    dispatch_arg = ((S_800B06F0_6 *)next_manager)->unk_08;
    arg2_r = ((S_800B06F0_6 *)next_manager)->unk_0C;
    goto dispatch;

done:
    manager = global_addr->manager;
    result = hard_zero;
    ((S_800B06F0_7 *)manager)->unk_8D0 = object;
    return result;
}
