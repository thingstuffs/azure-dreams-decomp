#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

/* The first seven words are the retail function bank.  The actual C body
 * starts at +0x1c; its dispatch table is the resident table at 0x80024008. */
#ifdef __mips__
static const u32 func_8197C800_bank[] __asm__("func_8197C800")
    __attribute__((section(".text.func_8197C800"), aligned(4))) = {
    0x8002401C, 0x00000000, 0x80024090, 0x800240EC,
    0x80024248, 0x80024284, 0x800245E0,
};
#define FUNC_8197C800_BODY func_8197C81C
#else
#define FUNC_8197C800_BODY func_8197C800
#endif

extern void *D_80024008[];
extern void *D_800814A8[];
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80083780[];
extern u32 D_800246C0[];
extern u8 D_80024BB8[];
extern u8 D_80024C68[];
extern u8 D_80082E80[];
extern u8 D_800DEDB0[];
extern u8 D_800DE9D0[];
extern u8 D_800DEC00[];
extern u8 D_80083460[];
extern s32 D_800814A0[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u16 D_80082E94[];

extern void *func_8003FD64(s32, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_80069EF8(void);
extern void func_8009CE1C(void *, s32, s32, s32, s16, void *, s32);

/* These are the original absolute shared-tail entry points used by this
 * copied overlay bank. */
extern void func_800245D0(void) __attribute__((noreturn));
extern void func_800245D8(void) __attribute__((noreturn));
extern void func_8002468C(void) __attribute__((noreturn));

void FUNC_8197C800_BODY(void *input, void *output)
    __attribute__((section(".text.func_8197C800")));

void FUNC_8197C800_BODY(void *input, void *output)
{
    s16 coords[3];
    s32 state;
    register void *arg0 ASM_REG("$19") = input;
    register void *arg1 ASM_REG("$21") = output;
    register void *base ASM_REG("$8");
    register void *root ASM_REG("$18");
    void *anchor;
    register void **dispatch ASM_REG("$2");
    register u8 *entry ASM_REG("$3");
    void *segment;
    void *obj;
    void *node;
    void *src_position;
    void *dst_position;
    void *status;
    register void *tail ASM_REG("$20");
    s32 i;
    register s32 r ASM_REG("$2");
    register s32 v ASM_REG("$23");
    register s32 index ASM_REG("$3");
    register s32 random ASM_REG("$5");
    register s16 *table ASM_REG("$2");
    u16 angle;
    u16 tail_state;
    register u16 tail_timer ASM_REG("$3");
    register u8 *page ASM_REG("$22");
    register u8 *page2 ASM_REG("$21");
    u8 *image;
    register u8 *image0 ASM_REG("$21");
    u16 timer;
    static void *const keepalive[] = {
        &&case_zero, &&case_one, &&case_two, &&case_three, &&case_four
    };

    ASM_KEEP(arg0);
    timer = FIELD(arg0, u16, 0x50);
    base = FIELD(arg0, void *, 0);
    state = FIELD(arg0, s16, 0xA);
    timer -= 1;
    FIELD(arg0, u16, 0x50) = timer;
    root = (u8 *)base - 0x20;

    (void)keepalive;
    if ((u32)state < 5) {
        dispatch = D_80024008;
        ASM_KEEP(dispatch);
        entry = (u8 *)(((u32)state << 2) + (u32)dispatch);
        ASM_KEEP(entry);
        goto *((void *)*(void **)entry);
    }
    return;

case_zero:
    FIELD(D_800814A8[0], s32, 0xF4) = 0;
    FIELD(arg1, s32, 0) = FIELD(FIELD(root, void *, 8), s32, 0);
    FIELD(arg1, s32, 4) = FIELD(FIELD(root, void *, 8), s32, 4);
    FIELD(arg1, s32, 8) = FIELD(FIELD(root, void *, 8), s32, 8);
    FIELD(arg0, u16, 0xA) += 1;

case_one:
    if (!(FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80)) {
        return;
    }

    segment = D_800814A8[0];
    FIELD(arg0, u16, 0x50) = 10;
    FIELD(segment, u16, 0xA6) -= 1;
    FIELD(segment, u8, 0xA8) = FIELD(arg0, u8, 8);
    obj = func_8003FD64(0x312, D_80083498);
    if (obj == 0) {
        goto case_one_tail;
    }
    if (func_8003DE58(FIELD(FIELD(root, void *, 0xC), void *, 8),
                      FIELD(root, void *, 0xC), coords, 0) == 0) {
        coords[2] = 0;
        coords[1] = 0;
        coords[0] = 0;
    }
    tail = (u8 *)obj + 0x20;
    FIELD(obj, void *, 0x10) = D_800246C0;
    func_8004491C(obj, D_80045340);
    random = 0x00800000u;
    ASM_KEEP(random);
    node = FIELD(obj, void *, 0xC);
    index = coords[0];
    src_position = FIELD(root, void *, 8);
    dst_position = FIELD(obj, void *, 8);
    r = FIELD(src_position, s32, 0) + (index << 16);
    FIELD(arg1, s32, 0) = r;
    FIELD(dst_position, s32, 0) = r;
    index = coords[1];
    src_position = FIELD(root, void *, 8);
    dst_position = FIELD(obj, void *, 8);
    r = FIELD(src_position, s32, 4) + (index << 16);
    FIELD(arg1, s32, 4) = r;
    FIELD(dst_position, s32, 4) = r;
    index = coords[2];
    src_position = FIELD(root, void *, 8);
    dst_position = FIELD(obj, void *, 8);
    r = FIELD(src_position, s32, 8) + (index << 16);
    FIELD(arg1, s32, 8) = r;
    FIELD(dst_position, s32, 8) = r;
    FIELD(node, s16, 0x1E) = 0x800;
    FIELD(node, s16, 0x1C) = 0x800;
    FIELD(node, s16, 0x10) = 0x20;
    FIELD(node, void *, 0) = D_800DEDB0;
    FIELD(node, u16, 0x14) |= 0xC;
    FIELD(node, void *, 8) = FIELD(D_800DEDB0, void *, 4);
    random |= 0x8080u;
    FIELD(node, u8, 4) = 0;
    FIELD(node, u8, 5) = 0;
    FIELD(node, void *, 0xC) = (void *)random;
    FIELD(obj, void *, 0x20) = arg0;
    FIELD(tail, u16, 0x4C) = 0;
    goto case_one_tail;

case_one_tail:
    tail_state = FIELD(arg0, u16, 0xA) + 1;
    ASM_TAILSLOT_PIN(tail_state);
    func_800245D8();

case_two:
    if (FIELD(arg0, s16, 0x50) > 0) {
        return;
    }
    r = func_80053EF0(4);
    if (r != 2) {
        func_800A56E0(0x300);
    } else {
        func_800A56E0(0x4300);
    }
    tail_state = FIELD(arg0, u16, 0xA);
    ASM_KEEP(tail_state);
    tail_timer = 16;
    ASM_TAILSLOT_PIN(tail_timer);
    func_800245D0();

case_three:
    if (FIELD(arg0, s16, 0x50) >= 3) {
        goto two_finish;
    }
    i = 1;
    page = (u8 *)0x80080000;
    {
        void *p;
        p = D_80083780;
        r = func_800BCB04(FIELD(p, u16, 2), FIELD(p, u16, 6),
                          (s16)(FIELD(p, u16, 0xA) - 0x80));
        v = (s16)((r << 16) >> 16);
    }
    ASM_KEEP(page);
    anchor = D_80024BB8;
    r = (s32)0x80080000;
    ASM_KEEP(r);
    image0 = (u8 *)r + 0x2E80;
    do {
        obj = func_8003FD64(0x312, D_80083498);
        if (obj != 0) {
            FIELD(obj, void *, 0x10) = anchor;
            func_8004491C(obj, D_80045340);
            node = FIELD(obj, void *, 0xC);
            tail = (u8 *)obj + 0x20;
            random = func_80069EF8();
            angle = FIELD(FIELD(page, void *, 0x14A8), u16, 0x2A);
            index = (s16)angle >> 9;
            table = D_8006CCD8;
            {
                s32 sum;
                s32 shifted;
                s32 adjusted;
                s32 remainder;
                void *position;
                sum = FIELD(image0, u8, 0x24) + table[index];
                adjusted = random;
                ASM_SCHED_BARRIER();
                position = FIELD(obj, void *, 8);
                ASM_KEEP(position);
                shifted = sum << 6;
                if (random < 0) {
                    adjusted = random + 31;
                }
                remainder = random - ((adjusted >> 5) << 5) + 16;
                r = shifted + remainder;
                FIELD(position, s16, 2) = r;
            }
            random = func_80069EF8();
            angle = FIELD(FIELD(page, void *, 0x14A8), u16, 0x2A);
            index = (s16)angle >> 9;
            table = D_8006CCE8;
            {
                s32 sum;
                s32 shifted;
                s32 adjusted;
                s32 remainder;
                void *position;
                sum = FIELD(image0, u8, 0x25) + table[index];
                adjusted = random;
                ASM_SCHED_BARRIER();
                position = FIELD(obj, void *, 8);
                ASM_KEEP(position);
                shifted = sum << 6;
                if (random < 0) {
                    adjusted = random + 31;
                }
                remainder = random - ((adjusted >> 5) << 5) + 16;
                r = shifted + remainder;
                FIELD(position, s16, 6) = r;
            }
            {
                register u32 color ASM_REG("$4");
                register void *template ASM_REG("$3");
                register void *position ASM_REG("$2");
                color = 0x00600000u;
                ASM_KEEP(color);
                position = FIELD(obj, void *, 8);
                ASM_SCHED_BARRIER();
                template = (void *)0x800E0000;
                ASM_KEEP(template);
                FIELD(position, s16, 0xA) = v;
                FIELD(node, s16, 0x1C) = 0x1800;
                FIELD(node, s16, 0x1E) = 0x2000;
                FIELD(node, s16, 0x10) = 0x60;
                {
                    register u16 flags ASM_REG("$2");
                    ASM_SCHED_BARRIER();
                    flags = FIELD(node, u16, 0x14);
                    ASM_SCHED_BARRIER();
                    template = (u8 *)template - 0x1630;
                    FIELD(node, void *, 0) = template;
                    flags |= 0xC;
                    FIELD(node, u16, 0x14) = flags;
                    FIELD(node, void *, 8) = FIELD(template, void *, 4);
                }
                FIELD(node, u8, 4) = 0;
                FIELD(node, u8, 5) = 0;
                FIELD(node, void *, 0xC) = (void *)(color | 0x6060u);
                FIELD(obj, void *, 0x20) = arg0;
                FIELD(tail, u16, 0x4C) = 0;
            }
        }
        i -= 1;
    } while (i >= 0);

    i = 9;
    anchor = D_80024C68;
    image = D_80082E80;
    page2 = (u8 *)0x80080000;
    do {
        obj = func_8003FD64(0x312, D_80083498);
        if (obj != 0) {
            FIELD(obj, void *, 0x10) = anchor;
            func_8004491C(obj, D_80045340);
            node = FIELD(obj, void *, 0xC);
            tail = (u8 *)obj + 0x20;
            random = func_80069EF8();
            angle = FIELD(FIELD(page2, void *, 0x14A8), u16, 0x2A);
            index = (s16)angle >> 9;
            table = D_8006CCD8;
            {
                s32 sum;
                s32 shifted;
                s32 adjusted;
                s32 remainder;
                void *position;
                sum = FIELD(image, u8, 0x24) + table[index];
                adjusted = random;
                ASM_SCHED_BARRIER();
                position = FIELD(obj, void *, 8);
                ASM_KEEP(position);
                shifted = sum << 6;
                if (random < 0) {
                    adjusted = random + 63;
                }
                remainder = random - ((adjusted >> 6) << 6);
                r = shifted + remainder;
                FIELD(position, s16, 2) = r;
            }
            random = func_80069EF8();
            angle = FIELD(FIELD(page2, void *, 0x14A8), u16, 0x2A);
            index = (s16)angle >> 9;
            table = D_8006CCE8;
            {
                s32 sum;
                s32 shifted;
                s32 adjusted;
                s32 remainder;
                void *position;
                sum = FIELD(image, u8, 0x25) + table[index];
                adjusted = random;
                ASM_SCHED_BARRIER();
                position = FIELD(obj, void *, 8);
                ASM_KEEP(position);
                shifted = sum << 6;
                if (random < 0) {
                    adjusted = random + 63;
                }
                remainder = random - ((adjusted >> 6) << 6);
                r = shifted + remainder;
                FIELD(position, s16, 6) = r;
            }
            r = func_80069EF8();
            FIELD(FIELD(obj, void *, 8), s16, 0xA) = v - (r & 0x1F);
            r = func_80069EF8();
            {
                register u32 color ASM_REG("$5");
                register s32 size ASM_REG("$2");
                register void *template ASM_REG("$3");
                color = 0x00100000u;
                ASM_KEEP(color);
                FIELD(FIELD(obj, void *, 8), s32, 0x14) =
                    (s32)0xFFE60000 - (r << 2);
                FIELD(node, s16, 0x1E) = 0x800;
                FIELD(node, s16, 0x1C) = 0x800;
                ASM_SCHED_BARRIER();
                size = 0x20;
                template = (void *)0x800E0000;
                ASM_KEEP(template);
                FIELD(node, s16, 0x10) = size;
                {
                    register u16 flags ASM_REG("$2");
                    ASM_SCHED_BARRIER();
                    flags = FIELD(node, u16, 0x14);
                    ASM_SCHED_BARRIER();
                    template = (u8 *)template - 0x1400;
                    FIELD(node, void *, 0) = template;
                    flags |= 0xC;
                    FIELD(node, u16, 0x14) = flags;
                    FIELD(node, void *, 8) = FIELD(template, void *, 4);
                }
                FIELD(node, u8, 4) = 0;
                FIELD(node, u8, 5) = 0;
                FIELD(node, void *, 0xC) = (void *)(color | 0x1010u);
                FIELD(obj, void *, 0x20) = arg0;
                FIELD(tail, u16, 0x4C) = 0;
            }
        }
        i -= 1;
    } while (i >= 0);

two_finish:
    if (FIELD(arg0, s16, 0x50) > 0) {
        return;
    }
    FIELD(arg0, u16, 0x50) = 32;
    FIELD(arg0, u16, 0xA) += 1;
    func_8002468C();

case_four:
    if (!(D_80082E94[0] & 0x8000) && FIELD(arg0, s16, 0x50) >= 0) {
        return;
    }
    if (FIELD(arg0, s16, 0x52) & 0x8000) {
        FIELD(arg0, u16, 0x52) &= 0x7FFF;
        func_8002468C();
    }
    ASM_SCHED_BARRIER();
    func_8009CE1C(FIELD(D_800814A8[0], void *, 0x60), 8,
                  FIELD(arg0, u8, 9), 10,
                  FIELD(base, s16, 0x2A), base, 2);
    status = D_80083460;
    FIELD(status, u32, 0xC) = 0;
    FIELD(status, u16, 0xA) -= 1;
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

#ifdef __mips__
__asm__(
    ".globl func_8197C800\n"
    ".type func_8197C800,@function\n"
    ".size func_8197C800,1728\n");
#endif
