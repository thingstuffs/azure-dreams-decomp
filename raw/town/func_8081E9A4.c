#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 *child;
    u8 pad04[0x10];
    s32 amount;
    s16 state;
    s16 timer;
    s16 count;
    s16 ticks;
    u16 flags;
    s16 phase;
    s16 phase2;
} TownEffect;

typedef struct {
    s16 kind;
    s16 unused;
    void *owner;
    u8 pad08[0x4C];
    s16 x;
    s16 y;
} EffectMessage;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
} EffectScratch;

typedef struct {
    EffectMessage message;
    EffectScratch scratch;
    s16 digits[3];
} EffectFrame;

extern void *D_80020078[13];
extern void *D_800200B0[63];
extern void *D_800201B0[27];

extern u8 D_800220A8[];
extern u8 D_80024450[];
extern u8 D_80045340[];
extern u8 D_80082E80[];
extern u8 D_80083498[];
extern u8 D_80083160[];
extern u8 D_800834B8[];
extern u8 D_80083780[];
extern s32 D_80012D5C[3];
extern s32 D_80024558[3];
extern s32 D_80100E18[3];
extern u8 D_800D0078[];
extern u8 D_800D0080[];
extern u8 D_800D00A0[];
extern u8 D_800D00A8[];
extern u8 D_800D00B8[];
extern u8 D_80097D2C[];
extern void func_8002222C(void);

extern void func_80020570(void *, void *);
extern s32 func_800352FC(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80053DA8(s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern void func_80093864(void);
extern void func_80093C70(void);
extern void func_80093CEC(void *);
extern void func_80093D48(void *, void *, void *, ...);
extern s32 func_800B1BEC(s32, s32, s32);
extern void func_800B1DBC(s32);

void func_800211A4(TownEffect *input)
{
    u8 *state_global;
    u8 *primitive;
    u8 *child;
    TownEffect *arg0 = input;
    EffectFrame frame;
    s32 state;
#define message frame.message
#define scratch frame.scratch
#define digits frame.digits

    static void *const state_labels[14] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7,
        &&state_8, &&state_9, &&state_10, &&state_11,
        &&state_12, &&state_12_amount
    };
    static void *const counter_labels[12] = {
        &&counter_a, &&counter_b, &&counter_c, &&counter_d,
        &&counter_e, &&counter_f, &&counter_g, &&counter_h,
        &&counter_i, &&counter_j, &&counter_k, &&counter_l
    };

    state_global = D_80083160;
    child = (u8 *)arg0->child + 0x20;
    state = arg0->state;
    primitive = D_800834B8;
    if ((u32)state >= 13) {
        goto common_done;
    }
    (void)state_labels;
    goto *D_80020078[(u32)state];

state_0:
{
    void *object;
    void *object_child;
    u8 *object_link;
    s32 i;
    s32 base;
    u16 flags;
    void *msgp;
    flags = arg0->flags;
    D_80100E18[0] = 1;
    arg0->phase = 3;
    arg0->ticks = 0;
    arg0->amount = 0;
    flags &= ~2;
    arg0->flags = flags;
    func_80093864();
    func_80053DA8(0x700);
    arg0->state = 1;
    arg0->flags &= ~8;
    base = 0x05200000;

    message.kind = 0;
    message.owner = arg0;
    message.x = 2;
state0_outer:
    message.y = 9;
    msgp = &message;
state0_inner:
    {
        s32 row_depth;
        s32 grid_x;
        grid_x = message.x;
        row_depth = 0x03E00000;
        scratch.b = row_depth;
        scratch.f = 0;
        scratch.e = 0;
        scratch.d = 0;
        scratch.a = base - (grid_x << 22);
        scratch.c = -((s32)message.y << 19);
        func_80020570(msgp, &scratch);
    }
    if (--message.y >= 0) {
        msgp = &message;
        goto state0_inner;
    }
    if (--message.x >= 0) {
        goto state0_outer;
    }

    for (i = 2; i >= 0; i--) {
        object = func_8003FD64(0x112, D_80083498);
        if (object != 0) {
            object_child = FIELD(object, void *, 0x0C);
            FIELD(object, void *, 0x10) = D_800220A8;
            object_link = (u8 *)object + 0x20;
            func_8004491C(object, D_80045340);
            FIELD(FIELD(object, void *, 0x08), u32, 0x00) =
                (i << 23) + 0x04600000;
            FIELD(FIELD(object, void *, 0x08), u32, 0x04) = 0x03600000;
            FIELD(FIELD(object, void *, 0x08), u32, 0x08) = 0xFE000000;
            FIELD(object_child, u16, 0x1C) =
                FIELD(object_child, u16, 0x1E) = 0x1000;
            FIELD(object_child, u16, 0x14) |= 0x000C;
            FIELD(object_child, u32, 8) = *(u32 *)(D_80024450 + (i << 2));
            FIELD(object_child, u8, 4) = 0;
            FIELD(object_child, u8, 5) = 0;
            FIELD(object_child, u32, 0x0C) = 0x00808080;
            FIELD(object_link, void *, 4) = arg0;
        }
    }
    goto common_done;
}

state_1:
{
    u8 *motion;
    s32 handle;
    s32 value;
    if (arg0->phase == 3) {
        goto common_done;
    }
    func_80053DA8(0x523);
    handle = func_800B1BEC(0, -80, 64);
    value = 6 / (arg0->phase + 1);
    D_80024558[0] = handle;
    FIELD(arg0, s32, 0x10) = value;
    if (func_800352FC(value) == 0) {
        motion = D_80083780;
        FIELD(motion, s32, 0x14) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        FIELD(primitive, u16, 0x10) = 0;
        func_80093CEC(D_800D0078);
        FIELD(primitive, void *, 0) = D_80097D2C;
        FIELD(primitive, void *, 4) = func_8002222C;
    }
    FIELD(child, s16, 0x70) = 1;
    FIELD(child, s16, 0x72) = 16;
    FIELD(child, s16, 0x74) = 20;
    arg0->timer = 5;
    arg0->state = 2;
    goto common_done;
}

state_2:
{
    s32 value;
    if ((FIELD(state_global, s32, 8) & 0x5000) != 0) {
        if (arg0->timer-- < 0) {
            arg0->timer = 0;
        }
    } else {
        arg0->timer = 5;
    }
    if ((FIELD(state_global, s32, 0x10) & 0x1000) == 0) {
        if ((FIELD(state_global, s32, 8) & 0x1000) == 0 || arg0->timer > 0) {
            goto state_3_body;
        }
    }
    if (arg0->amount < 10000 && (u32)D_80012D5C[0] >= 100) {
        func_80053DA8(0x502);
        D_80012D5C[0] -= 100;
        arg0->amount = arg0->amount + 100;
        goto state_3_after_shake;
    }

state_3:
state_3_body:
    if ((FIELD(state_global, s32, 0x10) & 0x4000) == 0) {
        if ((FIELD(state_global, s32, 8) & 0x4000) == 0 || arg0->timer > 0) {
            goto state_3_after_shake;
        }
    }
    if (arg0->amount >= 100) {
        func_80053DA8(0x502);
        D_80012D5C[0] += 100;
        arg0->amount = arg0->amount - 100;
    }

state_3_after_shake:
    arg0->ticks = arg0->amount / 100;
    if (arg0->ticks != 0) {
        value = FIELD(state_global, s32, 0x10);
    } else {
        value = FIELD(state_global, s32, 0x10);
    }
    if ((value & 0x40) != 0) {
        if (arg0->amount > 0) {
            arg0->state = 3;
            arg0->timer = 9;
            FIELD(D_80083780, s32, 0x14) = -0x240000;
            goto common_done;
        }
        goto common_done;
    }
    if ((value & 0x20) == 0) {
        goto common_done;
    }
    if (FIELD(child, s16, 0x70) != 0) {
        FIELD(child, s16, 0x70) = 3;
    }
    arg0->state = 10;
    goto common_done;
}

state_4:
{
    u8 *motion;
    u16 *prim_angle;
    s16 *timer_ptr;
    s32 *motion_word;
    s32 q1;
    s32 t2;
    s32 c2;
    prim_angle = (u16 *)primitive;
    timer_ptr = &arg0->timer;
    prim_angle[8] = (prim_angle[8] + 0x200) & 0xFFF;
    if (--*timer_ptr <= 0) {
        *timer_ptr = 10;
        motion = D_80083780;
        motion_word = (s32 *)motion;
        c2 = 0x02A00000;
        q1 = (0x03600000 - motion_word[0]) / arg0->timer;
        t2 = motion_word[1];
        motion_word[3] = q1;
        motion_word[4] = (c2 - t2) / arg0->timer;
        arg0->state = 11;
    }
    goto common_done;
}

state_5:
{
    u16 *prim_angle;
    u16 *timer_ptr;
    s32 value;
    prim_angle = (u16 *)primitive;
    timer_ptr = (u16 *)&arg0->timer;
    prim_angle[8] = (prim_angle[8] + 0x200) & 0xFFF;
    value = *timer_ptr - 1;
    *timer_ptr = (s16)value;
    if ((s16)value <= 0) {
        FIELD(D_80083780, s32, 0) = 0x03600000;
        FIELD(D_80083780, s32, 4) = 0x02A00000;
        FIELD(D_80083780, s32, 0x10) = 0;
        FIELD(D_80083780, s32, 0x0C) = 0;
        FIELD(D_80083780, s32, 0x14) = 0x00180000;
        arg0->state = 12;
    }
    goto common_done;
}

state_6:
{
    u8 *motion;
    s32 value;
    motion = D_80083780;
    value = (FIELD(primitive, u16, 0x10) + 0x200) & 0xFFF;
    FIELD(primitive, u16, 0x10) = value;
    if (FIELD(motion, s32, 8) < (s32)0xFF000000 || value != 0) {
        goto common_done;
    }
    FIELD(motion, s32, 8) = (s32)0xFF000000;
    arg0->state = 4;
    func_80093D48(primitive, motion, D_80082E80, (s32)0xFF000000);
    func_80093C70();
    goto common_done;
}

state_7:
{
    u8 *motion;
    if ((FIELD(state_global, s32, 0x10) & 0x40) == 0 ||
        FIELD(child, s16, 0x70) != 2) {
        goto common_done;
    }
    func_80053DA8(0x50A);
    func_80093CEC(D_800D00A0);
    motion = D_80083780;
    FIELD(motion, s32, 0x10) = 0x48000;
    FIELD(motion, s32, 0x14) = (s32)0xFFF40000;
    arg0->count = 0;
    arg0->state = 5;
    goto common_done;
}

state_8:
{
    u8 *motion;
    s32 value;
    s32 limit;
    s32 counter;
    limit = 0x9FFFF;
    motion = D_80083780;
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    FIELD(motion, s32, 8) += FIELD(motion, s32, 0x14);
    if (FIELD(motion, s32, 0x14) <= limit) {
        FIELD(motion, s32, 0x14) += 0x20000;
    }
    value = (u16)arg0->count;
    arg0->count = (s16)(value + 1);
    counter = (s16)value;
    if ((u32)counter < 63) {
        (void)counter_labels;
        goto *D_800200B0[(u32)counter];
    }
    goto counter_done;

counter_a:
    func_80093CEC(D_800D00A8);
    goto counter_done;
counter_b:
    func_80093CEC(D_800D00B8);
    goto counter_done;
counter_c:
    func_80053DA8(0x508);
    {
        s32 vx = 0x18000;
        u8 *p = D_800D0078;
        u8 *m;
        m = D_80083780;
        FIELD(m, s32, 0x14) = (s32)0xFFF40000;
        FIELD(m, s32, 0x10) = vx;
        func_80093CEC(p);
    }
    goto counter_done;
counter_d:
    func_80093CEC(D_800D00B8);
    goto counter_done;
counter_e:
    func_80093CEC(D_800D00A8);
    goto counter_done;
counter_f:
    func_80053DA8(0x508);
    {
        u8 *p = D_800D0078;
        u8 *m;
        m = D_80083780;
        FIELD(m, s32, 0x14) = (s32)0xFFF80000;
        FIELD(m, s32, 0x10) = 0x20000;
        func_80093CEC(p);
    }
    goto counter_done;
counter_g:
    func_80053DA8(0x508);
    FIELD(D_80083780, s32, 0x14) = (s32)0xFFFC0000;
    func_80093CEC(D_800D0078);
    goto counter_done;
counter_h:
    func_80053DA8(0x508);
    FIELD(D_80083780, s32, 0x14) = (s32)0xFFFC8000;
    func_80093CEC(D_800D0078);

counter_done:
    if (FIELD(child, s16, 0x70) != 3) {
        goto common_done;
    }
    {
        u8 *p = D_800D0078;
        u8 *m;
        m = D_80083780;
        FIELD(m, s32, 0x14) = (s32)0xFFFB0000;
        FIELD(m, s32, 0x10) = 0;
        FIELD(m, s32, 8) = (s32)0xFFC00000;
        func_80093CEC(p);
    }
    arg0->count = 0;
    arg0->state = 6;
    goto common_done;
}

state_9:
{
    u8 *motion;
    s32 *motion_word;
    s32 value;
    s32 counter;
    s32 index;

    motion = D_80083780;
    motion_word = (s32 *)motion;
    motion_word[2] += motion_word[5];
    motion_word[5] += 0x10000;
    value = (u16)arg0->count;
    counter = value + 1;
    arg0->count = (s16)counter;
    index = (s16)value;
    if ((u32)index < 27) {
        (void)counter_labels;
        goto *D_800201B0[(u32)index];
    }
    goto counter9_done;

counter_i:
    func_80093CEC(D_800D00A8);
    goto counter9_done;
counter_j:
    func_80093CEC(D_800D00B8);
    goto counter9_done;
counter_k:
    func_80053DA8(0x508);
    FIELD(D_80083780, s32, 0x14) = (s32)0xFFFC0000;
    func_80093CEC(D_800D0078);
    goto counter9_done;
counter_l:
    func_80053DA8(0x508);
    {
        s32 vy;
        counter = (s32)(D_800834B8 + 0x2C8);
        vy = (s32)0xFFFD0000;
        FIELD((u8 *)counter, s32, 0x14) = vy;
    }
    func_80093CEC(D_800D0078);

counter9_done:
    if (arg0->count != 28) {
        goto common_done;
    }
    {
        u8 *p = D_800D0078;
        u8 *m;
        FIELD(child, s16, 0x70) = 4;
        m = D_80083780;
        FIELD(m, s32, 0x14) = 0;
        FIELD(m, s32, 8) = (s32)0xFFC00000;
        func_80093CEC(p);
    }
    arg0->count = 3;
    arg0->state = 7;
    goto common_done;
}

state_10:
{
    s32 value;
    u8 *motion;
    s32 *motion_word;
    s16 *timer_ptr;
    value = arg0->timer;
    value = func_800644B8(0x1000 - value);
    motion = D_80083780;
    motion_word = (s32 *)motion;
    motion_word[0] = (s32)((u32)(value * 5) << 9) + 0x03600000;
    timer_ptr = (s16 *)((u8 *)arg0 + 0x1A);
    value = func_80064584(0x1000 - *timer_ptr);
    motion_word[1] = (s32)((u32)(value * 5) << 9) + 0x03600000;
    if (--arg0->count == 0) {
        func_80093CEC(D_800D0080);
    }
    if (FIELD(child, s16, 0x70) != 0) {
        goto common_done;
    }
    if (arg0->phase == arg0->phase2) {
        FIELD(child, s16, 0x70) = 6;
        arg0->timer = 30;
        arg0->state = 8;
    } else {
        arg0->amount = 0;
        arg0->state = 10;
    }
    goto common_done;
}

state_11:
{
    s32 i;
    s32 tick_dec;
    s32 timer_dec;
    s32 hp;
    s32 angle;
    s32 quotient;
    s32 tens;
    s32 hundred;
    s32 ten;
    s32 one;
    s32 digit_sum;
    s32 random_value;
    s32 digit_signed;
    u16 digit_hp;
    u8 *digit;
    tick_dec = (u16)arg0->ticks - 2;
    arg0->ticks = (s16)tick_dec;
    if ((s16)tick_dec < 0) {
        func_80093864();
        arg0->ticks = 0;
        arg0->flags |= 8;
    }
    timer_dec = (u16)arg0->timer - 1;
    arg0->timer = (s16)timer_dec;
    if ((s16)timer_dec > 0 || (arg0->flags & 8) == 0) {
        goto common_done;
    }

    i = (FIELD(arg0, s32, 0x14) * FIELD(arg0, s32, 0x10)) / 100;
    FIELD(arg0, s16, 0x1A) = 0xF0;
    quotient = i / 10;
    one = i - quotient * 10;
    digits[0] = (s16)one;
    digit_sum = (s16)one;
    tens = quotient / 10;
    ten = quotient - tens * 10;
    digits[1] = (s16)ten;
    digit_sum += (s16)ten;
    hundred = tens - (tens / 10) * 10;
    digit_sum += (s16)hundred;
    digits[2] = (s16)hundred;
    if (digit_sum < 10) {
        if ((s16)hundred > 0) {
            digit_sum += 9;
            digits[2] = (s16)(hundred - 1);
            digits[1] = (s16)(ten + 10);
        } else if ((s16)ten > 0) {
            digit_sum += 9;
            digits[1] = (s16)(ten - 1);
            digits[0] = (s16)(one + 10);
        }
    }
    arg0->flags &= ~8;
    message.kind = 1;
    message.owner = arg0;
    FIELD(&message, u8, 0x1D) = 0;
    message.unused = 8;
    i = 0;
    while (i < digit_sum) {
        do {
            random_value = func_80069EF8();
            message.x = (s16)(random_value % 3);
            digit = (u8 *)((s32)message.x * 2 + (s32)(u8 *)&frame);
            digit_signed = FIELD(digit, s16, 0x70);
            digit_hp = FIELD(digit, u16, 0x70);
        } while (digit_signed <= 0);
        do {
            FIELD(digit, s16, 0x70) = digit_hp - 1;
        } while (0);
        hp = 0x03600000;
        angle = (i << 12) / digit_sum;
        scratch.a = hp;
        scratch.b = hp;
        scratch.c = (s32)0xFF800000;
        scratch.d = (s32)((u32)(func_800644B8(angle) * 5) << 6);
        scratch.e = (s32)((u32)(func_80064584(angle) * 5) << 6);
        scratch.f = (s32)0xFFF80000;
        func_80020570(&message, &scratch);
        i++;
    }
    arg0->state = 9;
    goto common_done;
}

state_12:
{
    s32 value;
    value = (u16)arg0->timer - 1;
    arg0->timer = (s16)value;
    if ((s16)value > 0) {
        goto common_done;
    }
    func_800B1DBC(D_80024558[0]);
    arg0->state = 0;
    arg0->flags |= 2;
    goto common_done;
}

state_12_amount:
{
    s32 value;
    s32 money;
    if (FIELD(arg0, s32, 0x14) != 0) {
        money = D_80012D5C[0];
        if (arg0->ticks < 2) {
            D_80012D5C[0] = money + 100;
        } else {
            D_80012D5C[0] = money + 200;
        }
    }
    value = (u16)arg0->ticks - 2;
    arg0->ticks = (s16)value;
    if ((s16)value > 0) {
        goto common_done;
    }
    func_800B1DBC(D_80024558[0]);
    arg0->ticks = 0;
    arg0->state = 0;
    arg0->flags |= 0xA;
    func_80093D48(primitive, D_80083780, D_80082E80);
}

common_done:
    arg0->flags &= ~1;
}
