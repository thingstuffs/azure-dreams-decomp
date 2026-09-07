#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_80024008[];
extern u8 D_80026470[];
extern u8 D_80026474[];
extern u8 D_80026476[];
extern u8 D_80026478[];
extern u8 D_80026484[];
extern u8 D_80026490[];
extern u8 D_80026472[];
extern u8 D_800265C0[];
extern u8 D_800265C4[];
extern u8 D_800269C8[];
extern u8 D_80045340[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern u8 D_8008346C[];
extern u8 D_800814A0[];

#ifdef __mips__
extern u8 D_80020000[];
__asm__(".set D_80020000, 0x80020000");
extern u8 D_80080000[];
__asm__(".set D_80080000, 0x80080000");
#endif

extern void func_800B835C(void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(u32);
extern void func_8002495C(void *, void *);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_80065F90(s16, s16);
extern s32 func_800262AC(s16, s16, s16);
extern void func_800A56E0(s32);
extern void func_80026404(void *, u8, void *);

#ifdef __mips__
static const u32 func_80024000_prefix[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x80024050, 0x00000000, 0x800240B4,
    0x80024160, 0x800243B4, 0x800245D4, 0x80024628,
    0x80024770, 0x80024770, 0x80024770, 0x80024770,
    0x80024770, 0x80024770, 0x80024770, 0x80024770,
    0x80024770, 0x80024770, 0x80024770,
    0x80024698, 0x80024738,
};
__asm__(".globl func_80024000\n"
        ".size func_80024000, 1964");
#define FUNC_8188C800_BODY func_80024000_impl
#else
#define FUNC_8188C800_BODY func_80024000
#endif

void FUNC_8188C800_BODY(void *arg0, void *arg1, void *arg2)
{
#ifdef __mips__
    register u8 *self ASM_REG("$16") = (u8 *)arg0;
    register u8 *motion ASM_REG("$17") = (u8 *)arg1;
    register u8 *part ASM_REG("$19");
    register u8 *owner ASM_REG("$18");
    register u8 *base ASM_REG("$20");
    register u8 *record ASM_REG("$21");
    register u8 *tail_page0 ASM_REG("$2");
    register u8 *tail_page1 ASM_REG("$3");
#else
    u8 *self = (u8 *)arg0;
    u8 *motion = (u8 *)arg1;
    u8 *part = (u8 *)arg2;
    u8 *owner;
    u8 *base;
    u8 *record;
    u8 *tail_page0;
    u8 *tail_page1;
#endif
    register s32 state;
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_3, &&case_3,
        &&case_3, &&case_5, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&case_5_tail, &&done,
    };

    owner = FIELD(self, u8 *, 0);
    state = FIELD(self, s16, 0xA);
    base = owner - 32;
    record = FIELD(base, u8 *, 8);
    part = (u8 *)arg2;
    if (state < 0 || state >= 18) {
        goto done;
    }
    {
        void **table = D_80024008;
        s32 index = state << 2;
        ASM_KEEP(table);
        (void)keepalive;
        goto *(*(void **)(index + (u32)table));
    }

case_0:
    {
    s32 scratch[4];
#ifdef __mips__
        register u32 color ASM_REG("$2") = 0x00808080;
        register u32 init0 ASM_REG("$11") = 0x01000340;
        register u32 init1 ASM_REG("$10") = 0x00200020;
        register u8 *page ASM_REG("$8") = (u8 *)0x80020000;
        register u8 *addr ASM_REG("$9");
        ASM_KEEP(color);
        ASM_KEEP(init0);
        ASM_KEEP(init1);
        ASM_KEEP(page);
#else
        u32 color = 0x00808080;
        u32 init0 = 0x01000340;
        u32 init1 = 0x00200020;
        u8 *page = D_80026484;
        u8 *addr;
#endif
    addr = page + 0x6484;
    ASM_KEEP(addr);
    FIELD(part, u32, 0xC) = color;
    FIELD(part, u16, 0x1E) = 0x555;
    FIELD(part, u16, 0x1C) = 0x555;
    FIELD(part, void *, 8) = D_80026490;
    FIELD(D_80026470, u16, 0) = 0;
    FIELD(D_80026474, u16, 0) = 0;
    FIELD(D_80026476, u16, 0) = 0;
    FIELD(D_800265C0, u32, 0) = 0;
    FIELD(D_800265C4, u32, 0) = 0;
    {
        u16 packed = FIELD(owner, u16, 0x2A);
        FIELD(page, u16, 0x6484) = 0x1010;
        FIELD(addr, u32, 8) = 0;
        FIELD(self, u16, 0x16) = (packed >> 9) & 7;
    }
    scratch[2] = init0;
    scratch[3] = init1;
    func_800B835C(addr - 12, scratch + 2, 1, 0);
    FIELD(self, u16, 0xA)++;
    if (func_8003DF74(FIELD(FIELD(base, void *, 0xC), void *, 8),
                      FIELD(base, void *, 0xC), scratch, 0) == 0) {
        if (!(FIELD(FIELD(base, void *, 0xC), u16, 0x14) & 0x8000)) {
            goto done;
        }
    }
    FIELD(motion, u16, 2) = FIELD(record, u16, 2);
    FIELD(motion, u16, 6) = FIELD(record, u16, 6);
#ifdef __mips__
    {
        register u16 height ASM_REG("$2");
#else
    {
        u16 height;
#endif
        if (FIELD(FIELD(base, void *, 0xC), u16, 0x14) & 0x8000) {
            ASM_SCHED_BARRIER();
            height = FIELD(record, u16, 0xA) - 64;
        } else {
            ASM_SCHED_BARRIER();
            height = FIELD(record, u16, 0xA);
#ifdef __mips__
            {
                register u16 addend ASM_REG("$3") = FIELD(scratch, u16, 4);
#else
            {
                u16 addend = FIELD(scratch, u16, 4);
#endif
                ASM_KEEP_NV(addend);
                height = height + addend;
            }
        }
        ASM_KEEP_NV(height);
        FIELD(motion, u16, 0xA) = height;
        FIELD(self, u16, 0x32) = height;
        ASM_SCHED_BARRIER();
    }
    if (!(FIELD(FIELD(self, void *, 4), u16, 0) & 0x80)) {
        goto done;
    }
    if (!(FIELD(self, u8, 0x12) & 4)) {
        func_8004491C(self - 32, D_80045340);
        FIELD(part, u16, 0x10) = 32;
        FIELD(part, u8, 0x0E) = 128;
        FIELD(part, u8, 0x0D) = 128;
        FIELD(part, u8, 0x0C) = 128;
        FIELD(part, u16, 0x14) |= 0xC;
        FIELD(self, u8, 0x12) |= 4;
    }
    {
        u8 *target = FIELD(owner, u8 *, 0x60);
        if (target != 0) {
            u8 *target_part = FIELD(target, u8 *, -24);
            FIELD(self, u16, 0x0C) = FIELD(target_part, u16, 2);
            FIELD(self, u16, 0x0E) = FIELD(target_part, u16, 6);
            FIELD(self, u16, 0x10) = FIELD(target_part, u16, 0x0A) -
                                      D_800DDC40[0];
            {
                u8 *target_record = FIELD(owner, u8 *, -20);
                u8 x = FIELD(target_record, u8, 0x24) +
                       D_8006CCD8[FIELD(self, s16, 0x16) * 2];
                FIELD(self, u8, 0x1E) = x;
                FIELD(self, u8, 0x20) = x;
                {
                    u8 y = FIELD(target_record, u8, 0x25) +
                           D_8006CCE8[FIELD(self, s16, 0x16) * 2];
                    FIELD(self, u8, 0x1F) = y;
                    FIELD(self, u8, 0x21) = y;
                }
                {
#ifdef __mips__
                    register s32 lhs ASM_REG("$2") = FIELD(owner, s8, 0x72);
                    register s32 rhs ASM_REG("$3") =
                        FIELD(target_record, u8, 0x24);
#else
                    s32 lhs = FIELD(owner, s8, 0x72);
                    s32 rhs = FIELD(target_record, u8, 0x24);
#endif
                    s32 delta;
                    ASM_KEEP_NV(lhs);
                    ASM_KEEP_NV(rhs);
                    if (lhs == rhs) {
                        lhs = FIELD(owner, s8, 0x73);
                        rhs = FIELD(target_record, u8, 0x25);
                    }
                    delta = lhs - rhs;
                    if (delta < 0) {
                        ASM_SCHED_BARRIER();
                        delta = -delta;
                    }
                    FIELD(self, u16, 0x14) = delta + 1;
                }
            }
            goto case_0_finish_coords;
        }
    }
    FIELD(self, u16, 0x14) = 8;
    FIELD(self, u16, 0x0C) = FIELD(motion, u16, 2);
    FIELD(self, u16, 0x0E) = FIELD(motion, u16, 6);
    FIELD(self, u16, 0x10) = FIELD(owner, u16, 0x88) - 80;

case_0_finish_coords:
    FIELD(motion, s16, 0x0E) =
        FIELD(D_8006CCD8, s16, FIELD(self, s16, 0x16) * 2) * 8;
    FIELD(motion, s16, 0x12) =
        FIELD(D_8006CCE8, s16, FIELD(self, s16, 0x16) * 2) * 8;
    goto case_increment;
    }

case_1:
    {
#ifdef __mips__
        register s32 velocity ASM_REG("$3");
#else
        s32 velocity;
#endif
        register s32 adjusted ASM_REG("$4");
        register s32 magnitude ASM_REG("$3");
        velocity = FIELD(motion, s32, 0x0C);
        adjusted = velocity;
        ASM_KEEP_NV(adjusted);
        (*(volatile s32 *)((u8 *)motion + 0)) += velocity;
        ASM_SCHED_BARRIER();
        adjusted += adjusted >> 4;
        magnitude = adjusted;
        if (adjusted < 0) {
            ASM_KEEP_NV(magnitude);
            magnitude = -magnitude;
        }
        FIELD(motion, s32, 0x0C) = adjusted;
        if (magnitude > 0x200000) {
            s32 limit = -0x200000;
            if (adjusted > 0) {
                limit = 0x200000;
            }
            FIELD(motion, s32, 0x0C) = limit;
        }
    }
    {
#ifdef __mips__
        register s32 velocity ASM_REG("$3");
#else
        s32 velocity;
#endif
        register s32 adjusted ASM_REG("$4");
        register s32 magnitude ASM_REG("$3");
        velocity = FIELD(motion, s32, 0x10);
        adjusted = velocity;
        ASM_KEEP_NV(adjusted);
        (*(volatile s32 *)((u8 *)motion + 4)) += velocity;
        ASM_SCHED_BARRIER();
        adjusted += adjusted >> 4;
        magnitude = adjusted;
        if (adjusted < 0) {
            ASM_KEEP_NV(magnitude);
            magnitude = -magnitude;
        }
        FIELD(motion, s32, 0x10) = adjusted;
        if (magnitude > 0x200000) {
            s32 limit = -0x200000;
            if (adjusted > 0) {
                limit = 0x200000;
            }
            FIELD(motion, s32, 0x10) = limit;
        }
    }
    {
        s32 value = FIELD(self, s32, 0x30);
        s32 delta = (((s32)FIELD(self, s16, 0x10) << 16) - value) >> 4;
        FIELD(self, s32, 0x30) = value + delta;
    }
    {
        s32 value = FIELD(motion, s32, 8);
        s32 delta = (((s32)FIELD(self, s16, 0x10) << 16) - value) >> 4;
        FIELD(motion, s32, 8) = value + delta;
    }
    FIELD(motion, s32, 8) += func_800644B8((s32)FIELD(self, s16, 0x18) << 7) << 6;
    func_8002495C(motion, part);
    {
        s32 x = FIELD(motion, s16, 2);
        if (x < 0) {
            x += 63;
        }
        FIELD(self, u8, 0x1E) = x >> 6;
        {
            s32 y = FIELD(motion, s16, 6);
            if (y < 0) {
                y += 63;
            }
            FIELD(self, u8, 0x1F) = y >> 6;
        }
    }
    if (FIELD(self, s16, 0x20) == FIELD(self, s16, 0x1E)) {
        goto done;
    }
    if (FIELD(owner, void *, 0x60) != 0) {
        if ((FIELD(owner, u32, 0x70) & 0xFFFF0000) ==
            (FIELD(self, u32, 0x1C) & 0xFFFF0000)) {
            s32 snap_x = FIELD(owner, s8, 0x72);
            s32 snap_y;
            snap_x <<= 6;
            snap_x += 32;
            FIELD(motion, u16, 2) = snap_x;
            snap_y = FIELD(owner, s8, 0x73);
            snap_y <<= 6;
            snap_y += 32;
            FIELD(motion, u16, 6) = snap_y;
            FIELD(motion, u16, 0x0A) = FIELD(self, u16, 0x10);
            func_8002495C(motion, part);
            {
                u8 *target = FIELD(owner, u8 *, 0x60);
                u16 next = FIELD(self, u16, 0xA) + 1;
                u16 height = FIELD(target, u16, 0x88);
                FIELD(self, u16, 0xA) = next;
                FIELD(D_800269C8, u16, 0) = height;
            }
            goto done;
        }
    }

case_0_count_tail:
    {
        u8 old_x = FIELD(self, u8, 0x1E);
        s16 count = FIELD(self, u16, 0x14) - 1;
        u8 old_y = FIELD(self, u8, 0x1F);
        FIELD(self, u16, 0x14) = count;
        FIELD(self, u8, 0x20) = old_x;
        FIELD(self, u8, 0x21) = old_y;
        if (count != 0) {
            s32 x = FIELD(self, s8, 0x1E);
            s32 height;
            s32 y;
            ASM_SCHED_BARRIER();
            height = FIELD(self, s16, 0x32);
            ASM_USE_NV(height);
            x <<= 6;
            x += 32;
            x &= 0xFFE0;
            ASM_USE_NV(x);
            y = FIELD(self, s8, 0x1F);
            y <<= 6;
            y += 32;
            y &= 0xFFE0;
            if ((func_800A45D8(x, y, height) << 16) == 0) {
                goto done;
            }
        }
    }
    FIELD(self, u16, 0xA) = 16;
    goto done;

case_3:
    func_80065F90(FIELD(motion, s16, 0x0E), FIELD(motion, s16, 0x12));
    FIELD(self, s32, 0x2C) =
        func_800262AC(FIELD(motion, s16, 2), FIELD(motion, s16, 6),
                      FIELD(motion, s16, 0x0A));
    if (FIELD(self, s32, 0x2C) == 0) {
        goto done;
    }
    if (FIELD(owner, void *, 0x60) != 0) {
        func_800A56E0(0x300);
    }
    FIELD(self, u16, 0xA)++;
    FIELD(part, u8, 0x0C) -= FIELD(part, u8, 0x0C) >> 2;
    FIELD(part, u8, 0x0D) -= FIELD(part, u8, 0x0D) >> 2;
    FIELD(part, u8, 0x0E) -= FIELD(part, u8, 0x0E) >> 2;
    if (!(FIELD(FIELD(self, void *, 0x2C), u16, 0x1E) & 0x8000)) {
        goto done;
    }
    if (FIELD(owner, void *, 0x60) != 0) {
        func_80026404(FIELD(owner, void *, 0x60), FIELD(self, u8, 9), owner);
    }
    goto case_5_tail_prepare;

case_5:
    FIELD(motion, s32, 0) += FIELD(motion, s32, 0x0C);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    {
        s32 value = ((s32)FIELD(self, s16, 0x10) << 16) -
                    FIELD(motion, s32, 8);
        value >>= 4;
        FIELD(motion, s32, 8) += value;
    }
    FIELD(part, u8, 0x0C) -= FIELD(part, u8, 0x0C) >> 1;
    FIELD(part, u8, 0x0D) -= FIELD(part, u8, 0x0D) >> 1;
    FIELD(part, u8, 0x0E) -= FIELD(part, u8, 0x0E) >> 1;
    func_8002495C(motion, part);
    if (FIELD(part, u8, 0x0C) < 2) {
case_increment:
        FIELD(self, u16, 0xA)++;
    }
    goto done;

case_5_tail:
    if (FIELD(D_80026472, s16, 0) != 0) {
        goto done;
    }
case_5_tail_prepare:
    tail_page0 = (u8 *)0x80080000;
    ASM_KEEP(tail_page0);
case_5_tail_effect:
    FIELD(tail_page0, u32, 0x346C) = 0;
    FIELD(self, u16, -2) |= 0x8000;
    tail_page1 = (u8 *)0x80080000;
    ASM_KEEP(tail_page1);
    FIELD(tail_page1, u32, 0x14A0) |= 0x8000;
    goto done;

done:
    {
        u16 frame = FIELD(self, u16, 0x18);
        FIELD(D_80026472, u16, 0) = 0;
        FIELD(self, u16, 0x18) = frame + 1;
    }
}
