#include "common.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void *D_80024008[];
extern u8 D_800257D0[];
extern u8 D_800257E8[];
extern u8 D_80045340[];
extern s16 D_800257CE[5];
extern u8 D_800DDC40[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];

extern void func_800B835C(void *, s32 *, s32, s32);
extern void *func_8003DF74(void *, void *, s16 *, s32);
extern void func_8004491C(void *, void *);
extern void func_80025654(void *, void *);
extern s16 func_8009FCF0(u8, u8, u8, u8);
extern void func_800A56E0(s32);
extern s32 func_800A45D8(s32, s32, s16);
extern void *func_80024968(void *, void *, s16);
extern void func_80025760(void *, u8, void *);

extern void func_800241B0(void) __attribute__((noreturn));
extern void func_80024344(void) __attribute__((noreturn));
extern void func_800246A8(void) __attribute__((noreturn));
extern void func_800246AC(void) __attribute__((noreturn));
extern void func_800246F8(void) __attribute__((noreturn));

#ifdef __mips__
static const u32 func_81880800_prefix[] __asm__("func_81880800")
    __attribute__((section(".text.func_81880800"), aligned(4))) = {
    0x80024050,
    0,
    0x800240B4,
    0x80024128,
    0x80024394,
    0x8002459C,
    0x800245D8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x800246F8,
    0x8002461C,
    0x800246BC,
};
__asm__(".globl func_81880800\n"
        ".size func_81880800, 1832");
#define FUNC_81880800_BODY func_81880850
#else
#define FUNC_81880800_BODY func_81880800
#endif

void FUNC_81880800_BODY(void *arg0, void *arg1, void *arg2)
{
    register u8 *self ASM_REG("$16") = (u8 *)arg0;
    register u8 *motion ASM_REG("$17") = (u8 *)arg1;
    register u8 *part ASM_REG("$19") = (u8 *)arg2;
    register u8 *owner ASM_REG("$18");
    register u8 *base ASM_REG("$20");
    register u8 *record ASM_REG("$21");
    void *target;
    void *image;
    void *created;
    void *color_ptr;
    s32 state;
    s16 value16;
    s32 value;
    u32 table_value;
    u32 image_height;
    s32 magnitude;
    register s32 velocity ASM_REG("$3");
    register s32 position ASM_REG("$2");
    register s32 adjusted ASM_REG("$4");
    register s32 compare ASM_REG("$2");
    register s32 x_pos ASM_REG("$2");
    register s32 x_vel ASM_REG("$5");
    register s32 y_pos ASM_REG("$3");
    register s32 y_vel ASM_REG("$6");
    register s32 z_base ASM_REG("$3");
    register s32 z_delta ASM_REG("$2");
    register s32 coord ASM_REG("$2");
    register u8 *spawn_base ASM_REG("$7");
    register u32 tail_x ASM_REG("$2");
    register u32 tail_timer ASM_REG("$3");
    register u32 tail_y ASM_REG("$4");
    register s32 calc_x ASM_REG("$4");
    u32 chan0;
    u32 chan1;
    u32 chan2;
    register u32 color ASM_REG("$2");
    register u32 init0 ASM_REG("$8");
    register u32 init1 ASM_REG("$3");
    register s32 tail_value ASM_REG("$2");
    s16 vector[3];
    s32 init[2];
    static void *const keepalive[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4, &&finish
    };

#define arg0 self
#define arg1 motion
#define arg2 part

    owner = F(arg0, void *, 0);
    state = F(arg0, s16, 0xA);
    base = (u8 *)owner - 0x20;
    record = F(base, void *, 8);
    if ((u32)state >= 18U) {
        goto finish;
    }
    (void)keepalive;
    goto *D_80024008[state];

state0:
    color = 0x00808080;
    init0 = 0x01000340;
    init1 = 0x00200020;
    F(arg2, u32, 0xC) = color;
    F(arg2, u16, 0x1E) = 0x800;
    F(arg2, u16, 0x1C) = 0x800;
    F(arg2, void *, 8) = D_800257E8;
    F(arg0, u16, 0x1A) = (F(owner, u16, 0x2A) >> 9) & 7;
    init[0] = init0;
    init[1] = init1;
    func_800B835C(D_800257D0, init, 1, 0);
    F(arg0, u16, 0xA)++;

    if (func_8003DF74(F(F(base, void *, 0xC), void *, 8),
                       F(base, void *, 0xC), vector, 0) == 0) {
        if ((F(F(base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            goto finish;
        }
    }

    F(arg1, u16, 2) = F(record, u16, 2);
    F(arg1, u16, 6) = F(record, u16, 6);
    if (F(F(base, void *, 0xC), u16, 0x14) & 0x8000) {
        tail_value = F(record, u16, 0xA) - 0x40;
        ASM_TAILSLOT_PIN(tail_value);
        func_800241B0();
    }
    F(arg1, u16, 0xA) = F(record, u16, 0xA) + vector[2];

    if ((F(F(arg0, void *, 4), u16, 0) & 0x80) == 0) {
        goto finish;
    }
    if ((F(arg0, u8, 0x16) & 4) == 0) {
        func_8004491C((u8 *)arg0 - 0x20, &D_80045340);
        F(arg2, u16, 0x10) = 0x20;
        F(arg2, u8, 0x0E) = 0x80;
        F(arg2, u8, 0x0D) = 0x80;
        F(arg2, u8, 0x0C) = 0x80;
        F(arg2, u16, 0x14) |= 0xC;
        F(arg0, u8, 0x16) |= 4;
    }

    if (F(owner, void *, 0x60) != 0) {
        void *entry_copy;
        u8 index;
        u8 *table;
        u8 color_value;
        entry_copy = F(F(owner, void *, 0x60), void *, -0x18);
        F(arg0, u16, 0x10) = F(entry_copy, u16, 2);
        F(arg0, u16, 0x12) = F(entry_copy, u16, 6);
        table = D_800DDC40;
        index = F(F(owner, void *, 0x60), u8, 0x13);
        table_value = table[index];
        table_value += 0x20;
        image_height = F(entry_copy, u16, 0xA);
        F(arg0, u16, 0x14) = image_height - table_value;

        {
            s16 color_index;
            color_index = F(arg0, s16, 0x1A);
            entry_copy = F(owner, void *, -0x14);
            color_value = F(entry_copy, u8, 0x24) + D_8006CCD8[color_index];
            F(arg0, u8, 0x20) = color_value;
            F(arg0, u8, 0x22) = color_value;
        }
        {
            s16 color_index;
            color_index = F(arg0, s16, 0x1A);
            color_value = F(entry_copy, u8, 0x25) + D_8006CCE8[color_index];
            F(arg0, u8, 0x21) = color_value;
            F(arg0, u8, 0x23) = color_value;
        }
        {
            register s32 left ASM_REG("$2");
            register s32 right ASM_REG("$3");
            s32 delta;
            left = F(owner, s8, 0x72);
            right = F(entry_copy, u8, 0x24);
            if (left == right) {
                left = F(owner, s8, 0x73);
                right = F(entry_copy, u8, 0x25);
                delta = left - right;
            } else {
                delta = left - right;
            }
            if (delta < 0) {
                delta = -delta;
            }
            F(arg0, u16, 0x18) = delta + 1;
        }
        func_80024344();
    }

    F(arg0, u16, 0x18) = 8;
    F(arg0, u16, 0x10) = F(arg1, u16, 2);
    F(arg0, u16, 0x12) = F(arg1, u16, 6);
    F(arg0, u16, 0x14) = F(owner, u16, 0x88) - 0x50;
    ASM_SCHED_BARRIER();
    value = D_8006CCD8[F(arg0, s16, 0x1A)];
    F(arg1, s16, 0x0E) = value << 3;
    value = D_8006CCE8[F(arg0, s16, 0x1A)];
    F(arg1, s16, 0x12) = value << 3;
    value = F(arg0, u16, 0xA);
    ASM_KEEP(value);
    F(arg0, u16, 0x1C) = 0;
    func_800246AC();

state1:
    velocity = F(arg1, s32, 0x0C);
    position = F(arg1, s32, 0);
    adjusted = velocity;
    ASM_KEEP(adjusted);
    position += velocity;
    F(arg1, s32, 0) = position;
    ASM_KEEP(adjusted);
    adjusted += adjusted >> 4;
    magnitude = adjusted;
    if (adjusted < 0) {
        magnitude = -magnitude;
    }
    position = 0x200000;
    compare = magnitude > position;
    F(arg1, s32, 0x0C) = adjusted;
    if (compare) {
        position = -0x200000;
        if (adjusted > 0) {
            position = 0x200000;
        }
        F(arg1, s32, 0x0C) = position;
    }

    velocity = F(arg1, s32, 0x10);
    position = F(arg1, s32, 4);
    adjusted = velocity;
    ASM_KEEP(adjusted);
    position += velocity;
    F(arg1, s32, 4) = position;
    ASM_KEEP(adjusted);
    adjusted += adjusted >> 4;
    magnitude = adjusted;
    if (adjusted < 0) {
        magnitude = -magnitude;
    }
    position = 0x200000;
    compare = magnitude > position;
    F(arg1, s32, 0x10) = adjusted;
    if (compare) {
        position = -0x200000;
        if (adjusted > 0) {
            position = 0x200000;
        }
        F(arg1, s32, 0x10) = position;
    }

    z_delta = F(arg0, s16, 0x14) << 16;
    z_base = F(arg1, s32, 8);
    z_delta -= z_base;
    z_delta >>= 3;
    z_base += z_delta;
    F(arg1, s32, 8) = z_base;
    func_80025654(arg1, arg2);

    coord = F(arg1, s16, 2);
    if (coord < 0) {
        coord += 0x3F;
    }
    F(arg0, s8, 0x20) = coord >> 6;
    coord = F(arg1, s16, 6);
    if (coord < 0) {
        coord += 0x3F;
    }
    F(arg0, s8, 0x21) = coord >> 6;
    if (F(arg0, s16, 0x22) == F(arg0, s16, 0x20)) {
        goto finish;
    }

    if (F(owner, void *, 0x60) != 0) {
        if (F(arg0, s16, 0x28) == 0) {
            if ((s16)func_8009FCF0(F(arg0, u8, 0x20), F(arg0, u8, 0x21),
                                    F(owner, u8, 0x72), F(owner, u8, 0x73)) < 5) {
                F(arg0, s16, 0x28) = 1;
                func_800A56E0(0x300);
            }
        }
    }
    if (F(owner, void *, 0x60) != 0 &&
        F(owner, s16, 0x72) == F(arg0, s16, 0x20)) {
        F(arg1, u16, 2) = F(arg0, u16, 0x10);
        F(arg1, u16, 6) = F(arg0, u16, 0x12);
        F(arg1, u16, 0xA) = F(arg0, u16, 0x14);
        func_800246A8();
    }

    tail_x = F(arg0, u8, 0x20);
    tail_timer = F(arg0, u16, 0x18) - 1;
    tail_y = F(arg0, u8, 0x21);
    F(arg0, u16, 0x18) = tail_timer;
    tail_timer <<= 16;
    F(arg0, u8, 0x22) = tail_x;
    F(arg0, u8, 0x23) = tail_y;
    if (tail_timer != 0) {
        calc_x = (((s32)F(arg0, s8, 0x20) << 6) + 0x20) & 0xFFE0;
        value = func_800A45D8(
            calc_x,
            (((s32)F(arg0, s8, 0x21) << 6) + 0x20) & 0xFFE0,
            F(arg1, s16, 0x0A));
        if ((value << 16) == 0) {
            goto finish;
        }
    }
    F(arg0, u16, 0x0A) = 0x10;
    func_800246F8();

state2:
    spawn_base = F(owner, void *, 0x60);
    value16 = F(spawn_base, s16, 0x88);
    F(arg0, void *, 0x0C) = func_80024968(arg0, arg1, value16);
    if (F(arg0, void *, 0x0C) == 0) {
        goto finish;
    }
    F(arg2, u16, 0x14) |= 0x80;
    do {
        F(arg0, u16, 0x0A)++;
    } while (0);
    if ((F(F(arg0, void *, 0x0C), u16, 0x1E) & 0x8000) == 0) {
        goto finish;
    }
    target = F(owner, void *, 0x60);
    if (target != 0) {
        func_80025760(target, F(arg0, u8, 9), owner);
    }
    F(arg0, u16, 0x0A) = 0x11;
    func_800246F8();

state3:
    x_pos = F(arg1, s32, 0);
    x_vel = F(arg1, s32, 0x0C);
    y_pos = F(arg1, s32, 4);
    y_vel = F(arg1, s32, 0x10);
    x_pos += x_vel;
    y_pos += y_vel;
    F(arg1, s32, 0) = x_pos;
    F(arg1, s32, 4) = y_pos;
    z_delta = F(arg0, s16, 0x14) << 16;
    z_base = F(arg1, s32, 8);
    z_delta -= z_base;
    z_delta >>= 3;
    z_base += z_delta;
    F(arg1, s32, 8) = z_base;
    chan0 = F(arg2, u8, 0x0C);
    chan1 = F(arg2, u8, 0x0D);
    chan2 = F(arg2, u8, 0x0E);
    F(arg2, u8, 0x0C) = chan0 - (chan0 >> 1);
    F(arg2, u8, 0x0D) = chan1 - (chan1 >> 1);
    F(arg2, u8, 0x0E) = chan2 - (chan2 >> 1);
    func_80025654(arg1, arg2);
    if (F(arg2, u8, 0x0C) >= 2) {
        goto finish;
    }
    F(arg0, u16, 0x0A)++;
    func_800246F8();

state4:
    if (D_800257CE[0] != 0) {
        goto finish;
    }
    D_8008346C[0] = 0;
    F(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;

finish:
    D_800257CE[0] = 0;

#undef arg0
#undef arg1
#undef arg2
}
