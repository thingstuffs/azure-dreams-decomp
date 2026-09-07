#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

void func_8080EEC4(u8 **arg0, u8 *arg1, u8 *arg2)
{
    LocalRecord local;
    register u8 *work ASM_REG("$20");
    s32 dx;
    s32 dy;
    register s32 dx_square ASM_REG("$5");
    s32 dy_square;
    register s32 distance ASM_REG("$6");
    register s32 step ASM_REG("$5");
    s32 step_copy;
    register s32 offset ASM_REG("$2");
    register s32 base ASM_REG("$3");
    register s32 case_value ASM_REG("$2");
    register s32 case_x ASM_REG("$3");
    register s32 case_delta ASM_REG("$2");
    s32 value;
    register s32 limit ASM_REG("$3");
    register s32 shift ASM_REG("$17");
    register s32 i ASM_REG("$6");
    register s32 x ASM_REG("$6");
    s32 state;
    s32 old_angle;
    register s32 copied ASM_REG("$3");
    register s32 farval ASM_REG("$2");
    register s32 farconst ASM_REG("$3");
    register s32 early_far ASM_REG("$2");
    register s32 case5_old ASM_REG("$2");
    register s32 case5_next ASM_REG("$3");

    static void *const keepalive[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3,
        &&case_4, &&case_5, &&switch_done
    };

    dx = (D_80132AE8 - 0x03600000) >> 16;
    dy = (D_80132AEC - 0x03600000) >> 16;
    work = *arg0;
    old_angle = FIELD(arg2, u16, 0x1A);
    local.rect.packed = D_80526470;
    dx_square = dx * dx;
    dy_square = dy * dy;
    distance = func_8006AB90(dx_square + dy_square);
    ASM_SCHED_BARRIER();
    copied = FIELD(arg1, s32, 8);
    FIELD(arg0, s32, 0x60) = copied;

    if (D_80132AEC > 0x035FFFFF) {
        if (distance < 0xB9) {
            goto close_range;
        }
        early_far = distance < 0xD1;
        ASM_KEEP(early_far);
        return func_80529C1C();
    }

    if (distance < 0xC1) {
        goto close_range;
    }
    goto far_check;

close_range:
    if (D_80132AF2 >= FIELD(arg1, s16, 0xA)) {
        D_80132AE8 = FIELD(arg0, s32, 4);
        D_80132AEC = FIELD(arg0, s32, 8);
    }
    FIELD(arg0, s32, 0x58) = D_80132AE8;
    FIELD(arg0, s32, 0x5C) = D_80132AEC;
    if (distance < 0x80) {
        FIELD(arg0, u16, 0x62) -= (0x80 - distance) >> 1;
        return func_80529D0C();
    }
    goto copy_position;

far_check:
    if (distance >= 0xD1) {
        goto set_far_default;
    }

    if (D_80132AF2 >= FIELD(arg1, s16, 0xA)) {
        D_80132AE8 = FIELD(arg0, s32, 4);
        D_80132AEC = FIELD(arg0, s32, 8);
    }

    {
        register s32 dx_abs ASM_REG("$3") = dx;
        register s32 dy_abs ASM_REG("$2");
        if (dx < 0) {
            dx_abs = -dx_abs;
        }
        dy_abs = dy;
        if (dy < 0) {
            dy_abs = -dy_abs;
        }
        if (dx_abs > dy_abs || D_80132AEC <= 0x033FFFFF) {
        FIELD(arg0, s32, 0x5C) = D_80132AEC;
        if (dx > 0) {
            farval = D_80132AE8;
            ASM_KEEP(farval);
            farconst = -0x00280000;
            ASM_TAILSLOT_PIN_TIED(farconst);
            return func_80529CC0();
        }
        FIELD(arg0, s32, 0x58) = D_80132AE8 + 0x00280000;
        return func_80529D0C();
    } else {
        FIELD(arg0, s32, 0x58) = D_80132AE8;
        if (dy > 0) {
            farval = D_80132AEC;
            farval -= 0x00280000;
            ASM_TAILSLOT_PIN_TIED(farval);
            return func_80529D08();
        }
        farval = D_80132AEC;
        farval += 0x00280000;
        ASM_TAILSLOT_PIN_TIED(farval);
        return func_80529D08();
        }
    }

set_far_default:
    FIELD(arg0, s32, 0x58) = 0x03600000;
    FIELD(arg0, s32, 0x5C) = 0x03600000;

copy_position:
    FIELD(arg0, s32, 4) = D_80132AE8;
    FIELD(arg0, s32, 8) = D_80132AEC;

    value = FIELD(work, s32, 0x14) /
        ((FIELD(work, s16, 0x22) << 8) + 0x300);
    offset = (3 - FIELD(work, s16, 0x22)) << 5;
    base = value + 0x40;
    step = offset + base;

    state = FIELD(arg0, s16, 0x70);
    if ((u32)state < 8) {
        goto *D_8052647C[state];
    }
    goto switch_done;

case_0:
        case_x = FIELD(arg2, u8, 0xE);
        case_delta = 0x80 - case_x;
        case_x = *(volatile u8 *)(arg2 + 0xE) + (case_delta >> 1);
        FIELD(arg2, u8, 0xE) = case_x;
        FIELD(arg2, u8, 0xD) = case_x;
        FIELD(arg2, u8, 0xC) = case_x;
        FIELD(arg0, s32, 0x6C) = 0x00080000;
        return func_8052A04C();

case_1:
        case_value = FIELD(arg0, s16, 0x72);
        case_value += (case_value + 0x10) >> 4;
        FIELD(arg0, s16, 0x72) = case_value;
        if (step < (s16)case_value) {
            FIELD(arg0, s16, 0x72) = step;
            FIELD(arg0, s16, 0x70) = 2;
        }
        FIELD(arg2, u16, 0x1A) += FIELD(arg0, u16, 0x72);
        return func_8052A04C();

case_2:
        case_value = FIELD(arg2, u16, 0x1A);
        case_value += step;
        FIELD(arg2, u16, 0x1A) = case_value;
        step_copy = step;
        if (distance >= 0xA1 && D_80132AEC > 0x03600000 &&
            FIELD(work, s16, 0x18) == 5) {
            FIELD(arg0, s16, 0x72) = step_copy;
            FIELD(arg0, s16, 0x70) = 3;
            return func_8052A04C();
        }
        goto switch_done;

case_3:
        dx = FIELD(arg2, u16, 0x1A) & 0x7FF;
        dy = 0x155;
        if (dx >= 0x6AB) {
            FIELD(work, s16, 0x24) = 0;
            return func_80529EC4();
        } else {
            i = 4;
            limit = 0x554;
            ASM_KEEP(limit);
        limit_loop:
            if (dx < limit) {
                i--;
                if (i >= 0) {
                    limit -= dy;
                    goto limit_loop;
                }
            }
            FIELD(work, s16, 0x24) = (i & 1) ? 1 : 2;
        }
        FIELD(work, s16, 0x1A) = 0;
        ASM_SCHED_BARRIER();
        shift = FIELD(work, s16, 0x22) == 2 ? 6 : 5;
        value = FIELD(arg0, s16, 0x72);
        value -= value >> shift;
        FIELD(arg0, s16, 0x72) = value;
        FIELD(arg2, u16, 0x1A) += value;
        FIELD(work, u16, 0x1A) += FIELD(arg0, u16, 0x72);
        if (FIELD(arg0, s16, 0x72) < (1 << shift)) {
            FIELD(arg0, s16, 0x74) = 0;
            FIELD(arg0, s16, 0x70) = 5;
            return func_8052A04C();
        }
        goto switch_done;

case_4:
        FIELD(arg2, u16, 0x1A) += FIELD(arg0, u16, 0x72);
        FIELD(work, u16, 0x1A) += FIELD(arg0, u16, 0x72);
        case_value = FIELD(arg0, u16, 0x74) + 1;
        FIELD(arg0, u16, 0x74) = case_value;
        ASM_SCHED_BARRIER();
        if ((case_value & 3) == 0) {
            FIELD(arg0, u16, 0x72) -= 2;
        }
        if (FIELD(arg0, s16, 0x72) < 4) {
            FIELD(arg0, s16, 0x70) = 0;
            return func_8052A04C();
        }
        goto switch_done;

case_5:
        FIELD(arg0, s16, 0x70) = 7;
        FIELD(arg0, s16, 0x72) = 0;
        ASM_SCHED_BARRIER();
        dx = 0;
        dy = 0x7A;
    case_5_loop:
            local.rect.natural.x = dy;
            local.rect.natural.w = 6;
            x = ((s16)FIELD(arg0, u16, 0x72) >> 1) + dx;
            func_8006E854(&local, D_8053067C + ((x % 3) << 5));
            dy += 0x10;
            dx++;
        if (dx < 3) {
            goto case_5_loop;
        }
        case5_old = FIELD(arg0, u16, 0x72);
        case5_next = case5_old + 1;
        FIELD(arg0, u16, 0x72) = case5_next;
        if ((s16)case5_old >= 0xC6) {
            FIELD(arg0, s16, 0x70) = 0;
        }
        goto switch_done;

switch_done:

    FIELD(arg2, u16, 0x1A) &= 0xFFF;
    if ((old_angle >> 8) !=
        (*(volatile u16 *)(arg2 + 0x1A) >> 8)) {
        func_80058F88(0x701);
    }
}
