#include "common.h"


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} PackedRect;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} NaturalRect;

typedef union {
    PackedRect packed;
    NaturalRect natural;
} RectUnion;

typedef struct {
    RectUnion rect;
    u8 pad[16];
} LocalRecord;

extern s32 D_80132AE8;
extern volatile s32 D_80132AEC;
extern s16 D_80132AF2;
extern PackedRect D_80526470;
extern u8 D_8053067C[];
extern void *D_8052647C[];

extern s32 func_8006AB90(s32);
extern void func_8006E854(LocalRecord *, void *);
extern void func_80058F88(s32);
extern void func_80529C1C(void) __attribute__((noreturn));
extern void func_80529CC0(void) __attribute__((noreturn));
extern void func_80529D0C(void) __attribute__((noreturn));
extern void func_80529D08(void) __attribute__((noreturn));
extern void func_80529EC4(void) __attribute__((noreturn));
extern void func_8052A04C(void) __attribute__((noreturn));


typedef struct S_8080EEC4_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_8080EEC4_0;   /* arg2 in func_8080EEC4 */

typedef struct S_8080EEC4_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8080EEC4_1;   /* arg1 in func_8080EEC4 */

typedef struct S_8080EEC4_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4C];
    s32 unk_58;
    s32 unk_5C;
    u8 pad_60[0x2];
    u16 unk_62;
    u8 pad_64[0x8];
    s32 unk_6C;
    s16 unk_70;
    union { s16 s; u16 u; } unk_72;   /* accessed as both */
    union { s16 s; u16 u; } unk_74;   /* accessed as both */
} S_8080EEC4_2;   /* arg0 in func_8080EEC4 */

typedef struct S_8080EEC4_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    s16 unk_18;
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    u8 pad_1C[0x6];
    s16 unk_22;
    s16 unk_24;
} S_8080EEC4_3;   /* work in func_8080EEC4 */

void func_8080EEC4(u8 **arg0, u8 *arg1, u8 *arg2)
{
    LocalRecord local;
    register u8 *work ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 dx;
    s32 dy;
    s32 dx_square;
    s32 dy_square;
    register s32 distance ASM_REG("$6");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 step ASM_REG("$5");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 step_copy;
    register s32 offset ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 base ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 case_value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 case_x;
    s32 case_delta;
    s32 value;
    s32 limit;
    register s32 shift ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    register s32 i ASM_REG("$6");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 x ASM_REG("$6");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 state;
    s32 old_angle;
    s32 copied;
    register s32 farval ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 farconst ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 early_far ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 case5_old;
    s32 case5_next;

    static void *const keepalive[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3,
        &&case_4, &&case_5, &&switch_done
    };

    dx = (D_80132AE8 - 0x03600000) >> 16;
    dy = (D_80132AEC - 0x03600000) >> 16;
    work = *arg0;
    old_angle = ((S_8080EEC4_0 *)arg2)->unk_1A;
    local.rect.packed = D_80526470;
    dx_square = dx * dx;
    dy_square = dy * dy;
    distance = func_8006AB90(dx_square + dy_square);
    copied = ((S_8080EEC4_1 *)arg1)->unk_08.at00.v;
    (*(s32 *)((u8 *)arg0 + (0x60))) = copied;

    if (D_80132AEC > 0x035FFFFF) {
        if (distance < 0xB9) {
            goto close_range;
        }
        early_far = distance < 0xD1;
        ASM_KEEP(early_far);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_80529C1C();
    }

    if (distance < 0xC1) {
        goto close_range;
    }
    goto far_check;

close_range:
    if (D_80132AF2 >= ((S_8080EEC4_1 *)arg1)->unk_08.at02.v) {
        D_80132AE8 = ((S_8080EEC4_2 *)arg0)->unk_04;
        D_80132AEC = (*(s32 *)((u8 *)arg0 + (8)));
    }
    (*(s32 *)((u8 *)arg0 + (0x58))) = D_80132AE8;
    ((S_8080EEC4_2 *)arg0)->unk_5C = D_80132AEC;
    if (distance < 0x80) {
        ((S_8080EEC4_2 *)arg0)->unk_62 -= (0x80 - distance) >> 1;
        return func_80529D0C();
    }
    goto copy_position;

far_check:
    if (distance >= 0xD1) {
        goto set_far_default;
    }

    if (D_80132AF2 >= ((S_8080EEC4_1 *)arg1)->unk_08.at02.v) {
        D_80132AE8 = ((S_8080EEC4_2 *)arg0)->unk_04;
        D_80132AEC = (*(s32 *)((u8 *)arg0 + (8)));
    }

    {
        register s32 dx_abs ASM_REG("$3") = dx;   /* MATCH pin: load-bearing for the whole function shape */
        register s32 dy_abs ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
        if (dx < 0) {
            dx_abs = -dx_abs;
        }
        dy_abs = dy;
        if (dy < 0) {
            dy_abs = -dy_abs;
        }
        if (dx_abs > dy_abs || D_80132AEC <= 0x033FFFFF) {
        ((S_8080EEC4_2 *)arg0)->unk_5C = D_80132AEC;
        if (dx > 0) {
            farval = D_80132AE8;
            ASM_KEEP(farval);   /* MATCH pin: retail basic-block layout depends on it */
            farconst = -0x00280000;
            ASM_TAILSLOT_PIN_TIED(farconst);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_80529CC0();
        }
        ((S_8080EEC4_2 *)arg0)->unk_58 = D_80132AE8 + 0x00280000;
        return func_80529D0C();
    } else {
        ((S_8080EEC4_2 *)arg0)->unk_58 = D_80132AE8;
        if (dy > 0) {
            farval = D_80132AEC;
            farval -= 0x00280000;
            ASM_TAILSLOT_PIN_TIED(farval);   /* MATCH pin: retail delay-slot fill depends on it */
            return func_80529D08();
        }
        farval = D_80132AEC;
        farval += 0x00280000;
        ASM_TAILSLOT_PIN_TIED(farval);   /* MATCH pin: retail delay-slot fill depends on it */
        return func_80529D08();
        }
    }

set_far_default:
    ((S_8080EEC4_2 *)arg0)->unk_58 = 0x03600000;
    ((S_8080EEC4_2 *)arg0)->unk_5C = 0x03600000;

copy_position:
    (*(s32 *)((u8 *)arg0 + (4))) = D_80132AE8;
    ((S_8080EEC4_2 *)arg0)->unk_08 = D_80132AEC;

    value = ((S_8080EEC4_3 *)work)->unk_14 /
        ((((S_8080EEC4_3 *)work)->unk_22 << 8) + 0x300);
    offset = (3 - ((S_8080EEC4_3 *)work)->unk_22) << 5;
    base = value + 0x40;
    step = offset + base;

    state = ((S_8080EEC4_2 *)arg0)->unk_70;
    if ((u32)state < 8) {
        goto *D_8052647C[state];
    }
    goto switch_done;

case_0:
        case_x = ((S_8080EEC4_0 *)arg2)->unk_0E;
        case_delta = 0x80 - case_x;
        case_x = *(volatile u8 *)(arg2 + 0xE) + (case_delta >> 1);
        ((S_8080EEC4_0 *)arg2)->unk_0E = case_x;
        ((S_8080EEC4_0 *)arg2)->unk_0D = case_x;
        ((S_8080EEC4_0 *)arg2)->unk_0C = case_x;
        ((S_8080EEC4_2 *)arg0)->unk_6C = 0x00080000;
        return func_8052A04C();

case_1:
        case_value = ((S_8080EEC4_2 *)arg0)->unk_72.s;
        case_value += (case_value + 0x10) >> 4;
        ((S_8080EEC4_2 *)arg0)->unk_72.s = case_value;
        if (step < (s16)case_value) {
            ((S_8080EEC4_2 *)arg0)->unk_72.s = step;
            ((S_8080EEC4_2 *)arg0)->unk_70 = 2;
        }
        ((S_8080EEC4_0 *)arg2)->unk_1A += ((S_8080EEC4_2 *)arg0)->unk_72.u;
        return func_8052A04C();

case_2:
        case_value = ((S_8080EEC4_0 *)arg2)->unk_1A;
        case_value += step;
        ((S_8080EEC4_0 *)arg2)->unk_1A = case_value;
        step_copy = step;
        if (distance >= 0xA1 && D_80132AEC > 0x03600000 &&
            ((S_8080EEC4_3 *)work)->unk_18 == 5) {
            ((S_8080EEC4_2 *)arg0)->unk_72.s = step_copy;
            ((S_8080EEC4_2 *)arg0)->unk_70 = 3;
            return func_8052A04C();
        }
        goto switch_done;

case_3:
        dx = ((S_8080EEC4_0 *)arg2)->unk_1A & 0x7FF;
        dy = 0x155;
        if (dx >= 0x6AB) {
            ((S_8080EEC4_3 *)work)->unk_24 = 0;
            return func_80529EC4();
        } else {
            i = 4;
            limit = 0x554;
        limit_loop:
            if (dx < limit) {
                i--;
                if (i >= 0) {
                    limit -= dy;
                    goto limit_loop;
                }
            }
            ((S_8080EEC4_3 *)work)->unk_24 = (i & 1) ? 1 : 2;
        }
        ((S_8080EEC4_3 *)work)->unk_1A.s = 0;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        shift = ((S_8080EEC4_3 *)work)->unk_22 == 2 ? 6 : 5;
        value = ((S_8080EEC4_2 *)arg0)->unk_72.s;
        value -= value >> shift;
        ((S_8080EEC4_2 *)arg0)->unk_72.s = value;
        ((S_8080EEC4_0 *)arg2)->unk_1A += value;
        ((S_8080EEC4_3 *)work)->unk_1A.u += ((S_8080EEC4_2 *)arg0)->unk_72.u;
        if (((S_8080EEC4_2 *)arg0)->unk_72.s < (1 << shift)) {
            ((S_8080EEC4_2 *)arg0)->unk_74.s = 0;
            ((S_8080EEC4_2 *)arg0)->unk_70 = 5;
            return func_8052A04C();
        }
        goto switch_done;

case_4:
        ((S_8080EEC4_0 *)arg2)->unk_1A += ((S_8080EEC4_2 *)arg0)->unk_72.u;
        ((S_8080EEC4_3 *)work)->unk_1A.u += ((S_8080EEC4_2 *)arg0)->unk_72.u;
        case_value = ((S_8080EEC4_2 *)arg0)->unk_74.u + 1;
        ((S_8080EEC4_2 *)arg0)->unk_74.u = case_value;
        if ((case_value & 3) == 0) {
            ((S_8080EEC4_2 *)arg0)->unk_72.u -= 2;
        }
        if (((S_8080EEC4_2 *)arg0)->unk_72.s < 4) {
            ((S_8080EEC4_2 *)arg0)->unk_70 = 0;
            return func_8052A04C();
        }
        goto switch_done;

case_5:
        ((S_8080EEC4_2 *)arg0)->unk_70 = 7;
        ((S_8080EEC4_2 *)arg0)->unk_72.s = 0;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        dx = 0;
        dy = 0x7A;
    case_5_loop:
            local.rect.natural.x = dy;
            local.rect.natural.w = 6;
            x = ((s16)((S_8080EEC4_2 *)arg0)->unk_72.u >> 1) + dx;
            func_8006E854(&local, D_8053067C + ((x % 3) << 5));
            dy += 0x10;
            dx++;
        if (dx < 3) {
            goto case_5_loop;
        }
        case5_old = ((S_8080EEC4_2 *)arg0)->unk_72.u;
        case5_next = case5_old + 1;
        ((S_8080EEC4_2 *)arg0)->unk_72.u = case5_next;
        if ((s16)case5_old >= 0xC6) {
            ((S_8080EEC4_2 *)arg0)->unk_70 = 0;
        }
        goto switch_done;

switch_done:

    ((S_8080EEC4_0 *)arg2)->unk_1A &= 0xFFF;
    if ((old_angle >> 8) !=
        (*(volatile u16 *)(arg2 + 0x1A) >> 8)) {
        func_80058F88(0x701);
    }
}
