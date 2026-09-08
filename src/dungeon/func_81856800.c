#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

#ifdef __mips__
typedef union {
    long long value;
    struct {
        s32 hi;
        u32 lo;
    } words;
} MipsProduct;
#endif

extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800BCB04(u16, u16, s16);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern void func_8004491C(void *, void *);
extern void func_800A56E0(s32);
extern void func_8009CE1C(void *, s32, u8, s32, s32, void *, s32);

extern u8 D_80083498[];
extern u8 D_80024850[];
extern u8 D_800DEE38[];
extern u8 D_800DEC50[];
extern u8 D_800DEC70[];
extern u8 D_800249BC[];
extern u8 D_80024F40[];
extern u8 D_80024C40[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];
extern void *D_80024008[];

#ifdef __mips__
extern void func_80024020(void);
extern void func_800241E4(void);
extern void func_80024380(void);
extern void func_800243D8(void);
extern void func_80024488(void);
extern void func_800246AC(void);
extern void func_800247D8(void);

/* The retail compiler puts the pooled six-way dispatch table immediately
 * before this routine.  The first two words are the entry and its null arm;
 * the table used by the jr begins at word two. */
static void (*const func_80024000_prefix[])(void)
    __asm__("func_80024000")
    __attribute__((used, section(".text.func_80024000"), aligned(4))) = {
        func_80024020,
        0,
        func_800241E4,
        func_80024380,
        func_800243D8,
        func_80024488,
        func_800246AC,
        func_800247D8,
    };
__asm__(".globl func_80024000
.type func_80024000,@function
.size func_80024000,2128
");
#define FUNC_81856800_BODY func_80024000_body
#define BODY_STORAGE
#define BODY_ATTR
#else
#define FUNC_81856800_BODY func_80024000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void FUNC_81856800_BODY(void *param0, void *param1) BODY_ATTR;
BODY_STORAGE void FUNC_81856800_BODY(void *param0, void *param1)
{
#ifdef __mips__
    void *arg0 = param0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *arg1 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#else
    void *arg0 = param0;
    void *arg1;
#endif
#ifdef __mips__
    register void *object ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#else
    void *object;
#endif
    void *owner;
#ifdef __mips__
    u8 *base;
#else
    u8 *base;
#endif
#ifdef __mips__
    void *effect;
    void *part;
#else
    void *effect;
    void *part;
#endif
    void *other;
    void *cursor;
    s16 coords[3];
    s32 state;
    s32 i;
    s32 random;
    s32 value;
    s32 timer;
    s32 in_range;
    register s32 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t1_reserve ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t2_reserve ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t3_reserve ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t4_reserve ASM_REG("$12");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t5_reserve ASM_REG("$13");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t6_reserve ASM_REG("$14");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t7_reserve ASM_REG("$15");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t8_reserve ASM_REG("$24");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 t9_reserve ASM_REG("$25");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    static void *const keepalive[] = {
        &&case0, &&case1, &&case2, &&case3, &&case5, &&case4, &&done
    };

    (void)keepalive;
    arg1 = param1;
    object = FIELD(arg0, void *, 0);
    state = FIELD(arg0, s16, 0xA);
    owner = FIELD(object, void *, -20);
    base = (u8 *)object - 32;

    if (state == 0) {
        goto dispatch_reload;
    }
    if (state == 5) {
        goto dispatch_range;
    }
    {
#ifdef __mips__
        void *setup_part;
#else
        void *setup_part;
#endif
        s32 delta;
        register s32 setup_kind ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u16 flags;

        i = 7;
        do {
            effect = func_8003FD64(0x312, D_80083498);
            if (effect != 0) {
                setup_part = (u8 *)effect + 32;
                part = FIELD(effect, void *, 0xC);
                ASM_KEEP(part);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                {
                    void *effect_type = D_80024850;

                    FIELD(effect, void *, 0x10) = effect_type;
                }
                FIELD(FIELD(effect, void *, 8), s32, 0) =
                    FIELD(arg1, s32, 0) +
                    (((func_80069EF8() & 0x1FF) - 255) << 13);
                FIELD(FIELD(effect, void *, 8), s32, 4) =
                    FIELD(arg1, s32, 4) +
                    (((func_80069EF8() & 0x1FF) - 255) << 13);
                FIELD(FIELD(effect, void *, 8), s32, 8) =
                    FIELD(arg1, s32, 8) -
                    (((func_80069EF8() & 0x1FF) - 255) << 14) +
                    (s32)0xFFE00000;
                flags = FIELD(part, u16, 20);
                FIELD(part, s16, 30) = 2048;
                FIELD(part, s16, 28) = 2048;
                flags |= 0xC;
                FIELD(part, u16, 20) = flags;
                if (i & 1) {
                    void *texture;
                    register s32 size ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                    {
                        register s32 color ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        color = 0x00404040;
                        size = 32;
                        texture = D_800DEC70;
                        ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        ASM_KEEP(texture);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        FIELD(part, s32, 12) = color;
                    }
                    setup_kind = 16;
                    FIELD(part, s16, 16) = size;
                    FIELD(part, void *, 0) = texture;
                } else {
                    register s32 color ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                    color = 0x00282828;
                    {
                        register s32 size ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        size = 96;
                        FIELD(part, s16, 16) = size;
                    }
                    {
                        register void *texture ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        texture = D_800DEC50;
                        FIELD(part, void *, 0) = texture;
                    }
                    setup_kind = 8;
                    FIELD(part, s32, 12) = color;
                }
                FIELD(setup_part, u16, 74) = setup_kind;
                {
                    void *texture_data;

                    texture_data = FIELD(part, void *, 0);
                    texture_data = FIELD(texture_data, void *, 4);
                    FIELD(part, u8, 4) = 0;
                    FIELD(part, u8, 5) = 0;
                    FIELD(part, void *, 8) = texture_data;
                }
                FIELD(setup_part, void *, 0) = arg0;
                delta = func_80069EF8() & 3;
                FIELD(setup_part, u16, 72) = delta;
                FIELD(setup_part, u16, 76) = 0;
            }
            i--;
        } while (i >= 0);
    }

dispatch_reload:
    state = FIELD(arg0, s16, 0xA);
dispatch_range:
    in_range = (u32)(s32)state < 6;
dispatch_test:
    if (!in_range) {
        goto done;
    }
    goto *D_80024008[(u32)state];

case0:
    {
        void *control;

        control = FIELD(arg0, void *, 4);
        if ((FIELD(control, u16, 0) & 0x80) == 0) {
            goto done;
        }
    }
    if (FIELD(object, void *, 0x60) == 0) {
        FIELD(object, u8, 0x72) = FIELD(owner, u8, 0x24);
        FIELD(object, u8, 0x73) = FIELD(owner, u8, 0x25);
    } else {
        register void *child_owner ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        child_owner = FIELD(FIELD(object, void *, 0x60), void *, -20);
        FIELD(object, u8, 0x72) = FIELD(child_owner, u8, 0x24);
        FIELD(object, u8, 0x73) = FIELD(child_owner, u8, 0x25);
    }
    other = FIELD(base, void *, 0xC);
    if (func_8003DE58(FIELD(other, void *, 8), other, coords, 0) == 0) {
        coords[2] = 0;
        coords[1] = 0;
        coords[0] = 0;
    }
    FIELD(arg1, u16, 2) = FIELD(FIELD(base, void *, 8), u16, 2) + coords[0];
    FIELD(arg1, u16, 6) = FIELD(FIELD(base, void *, 8), u16, 6) + coords[1];
    FIELD(arg1, u16, 0xA) = FIELD(FIELD(base, void *, 8), u16, 0xA) + coords[2];
    FIELD(arg0, u16, 0x50) = 8;
    {
        s32 velocity;
        s32 position;

        velocity = FIELD(object, s8, 0x72);
        velocity <<= 6;
        position = FIELD(arg1, u16, 2);
        position -= 32;
        velocity -= position;
        FIELD(arg1, s16, 0xE) = velocity;
    }
    {
        s32 quotient;

        quotient = FIELD(arg1, s32, 0xC) / FIELD(arg0, s16, 0x50);
        ASM_KEEP(quotient);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        FIELD(arg1, s32, 0xC) = quotient;
    }
    {
        s32 velocity;
        s32 position;

        velocity = FIELD(object, s8, 0x73);
        velocity <<= 6;
        position = FIELD(arg1, u16, 6);
        position -= 32;
        velocity -= position;
        FIELD(arg1, s16, 0x12) = velocity;
    }
    {
        s32 quotient;

        quotient = FIELD(arg1, s32, 0x10) / FIELD(arg0, s16, 0x50);
        FIELD(arg1, s32, 0x10) = quotient;
    }
    value = (s16)(FIELD(FIELD(base, void *, 8), u16, 0xA) - 48);
    random = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), value);
    FIELD(arg1, s16, 0x16) = random - FIELD(arg1, u16, 0xA);
    FIELD(arg1, s32, 0x14) /= FIELD(arg0, s16, 0x50);
    func_800A56E0(0x300);
    goto increment_state;

case1:
{
    s32 next_timer;

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    timer = FIELD(arg0, u16, 0x50) - 1;
    FIELD(arg0, u16, 0x50) = timer;
    next_timer = 10;
    if ((s16)timer > 0) {
        goto done;
    }
    next_state = FIELD(arg0, u16, 0xA);
    FIELD(arg0, u16, 0x50) = next_timer;
    goto increment_loaded;
}

case2:
{
    void *spawn_type;
#ifdef __mips__
    register u8 *spawn_page ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#else
    u8 *spawn_page;
#endif
    timer = FIELD(arg0, u16, 0x50) - 1;
    FIELD(arg0, u16, 0x50) = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    if (FIELD(object, void *, 0x60) == 0) {
        FIELD(arg0, u16, 0xA) = 5;
        goto done;
    }
    i = 8;
    spawn_page = (u8 *)0x80080000;
    spawn_type = D_80024C40;

case2_spawn_loop:
    effect = func_8003FD64(0x201, spawn_page + 0x3498);
    if (effect != 0) {
        part = (u8 *)effect + 32;
        FIELD(effect, void *, 0x10) = spawn_type;
        FIELD(part, u16, 0x48) = i;
        FIELD(part, u16, 4) = FIELD(arg1, u16, 2);
        FIELD(part, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(part, u16, 8) = FIELD(arg1, u16, 0xA);
        FIELD(part, u16, 0x46) = 3;
        FIELD(effect, void *, 0x20) = arg0;
        FIELD(part, u16, 0x4A) = 0;
    }
    i -= 4;
    if (i >= 0) {
        goto case2_spawn_loop;
    }
    next_state = FIELD(arg0, u16, 0xA);
    FIELD(arg0, u16, 0x50) = 8;
    goto increment_loaded;
}

case3:
{
    s32 offset;
#ifdef __mips__
    register void *loop_other ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 modulo_magic ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 a1_reserve;
    s32 a2_reserve;
    s32 a3_reserve;
#else
    void *loop_other;
#endif

    if (FIELD(arg0, s16, 0x50) >= 6) {
        goto case3_tick;
    }
    effect = func_8003FD64(0x201, D_80083498);
    if (effect == 0) {
        goto case3_tick;
    }
    part = (u8 *)effect + 32;
    FIELD(effect, void *, 0x10) = D_80024F40;
    func_8004491C(effect, D_800249BC);
    FIELD(part, u16, 4) =
        FIELD(arg1, u16, 2) + (func_80069EF8() & 0x3F) - 32;
    FIELD(part, u16, 6) =
        FIELD(arg1, u16, 6) + (func_80069EF8() & 0x3F) - 32;
    FIELD(part, u16, 8) = FIELD(arg1, u16, 0xA);
    FIELD(part, u16, 0x40) = func_80066460(0, 3, 0x2C0, 0x100);
    FIELD(part, s32, 0x34) = 0x00707070;
    if (FIELD(arg0, u16, 0x50) & 1) {
        FIELD(part, s16, 0x38) = 0xA0;
        FIELD(part, s16, 0x3A) = 0;
    } else {
        FIELD(part, s16, 0x38) = 0x80;
        FIELD(part, s16, 0x3A) = 32;
    }
    FIELD(part, s16, 0x3C) = 0xBF;
    FIELD(part, s16, 0x3E) = 0x1F;
    FIELD(part, s16, 0x42) = func_8006649C(0xA0, 0x1F7);
    FIELD(part, u16, 0x46) = 6;
    i = 1;
#ifdef __mips__
    modulo_magic = 0x19C2D14F;
#endif
    offset = 0;
    loop_other = (u8 *)part + 8;
#ifdef __mips__
#endif
    do {
        cursor = (u8 *)part + offset;
#ifdef __mips__
        {
            MipsProduct product;
            s32 mod_value;
            s32 mod_sign;
            register s32 mod_quotient ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            mod_value = func_80069EF8();
            product.value = (long long)mod_value * modulo_magic;
            mod_sign = mod_value >> 31;
            mod_quotient = (product.words.hi >> 4) - mod_sign;
            mod_sign = (mod_quotient << 2) + mod_quotient;
            mod_sign = (mod_sign << 5) - mod_quotient;
            mod_quotient = FIELD(cursor, u16, 4);
            mod_value -= mod_sign;
            mod_quotient += mod_value;
            mod_quotient -= 80;
            FIELD(loop_other, u16, 4) = mod_quotient;
        }
        {
            MipsProduct product;
            s32 mod_value;
            s32 mod_sign;
            register s32 mod_quotient ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            mod_value = func_80069EF8();
            product.value = (long long)mod_value * modulo_magic;
            offset += 8;
            i++;
            mod_sign = mod_value >> 31;
            mod_quotient = (product.words.hi >> 4) - mod_sign;
            mod_sign = (mod_quotient << 2) + mod_quotient;
            mod_sign = (mod_sign << 5) - mod_quotient;
            mod_quotient = FIELD(cursor, u16, 6);
            mod_value -= mod_sign;
            mod_quotient += mod_value;
            mod_quotient -= 80;
            FIELD(loop_other, u16, 6) = mod_quotient;
        }
#else
        FIELD(loop_other, u16, 4) =
            FIELD(cursor, u16, 4) + (func_80069EF8() % 159) - 80;
        FIELD(loop_other, u16, 6) =
            FIELD(cursor, u16, 6) + (func_80069EF8() % 159) - 80;
        offset += 8;
        i++;
#endif
        FIELD(loop_other, u16, 8) =
            FIELD(cursor, u16, 8) - ((func_80069EF8() & 0x1F) + 20);
        loop_other = (u8 *)loop_other + 8;
    } while (i < 5);
    FIELD(part, void *, 0) = arg0;
    FIELD(part, u16, 0x4A) = 0;
#ifdef __mips__
#endif
}

case3_tick:
    timer = FIELD(arg0, u16, 0x50) - 1;
    FIELD(arg0, u16, 0x50) = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    if (FIELD(object, void *, 0x60) != 0) {
        func_8009CE1C(FIELD(object, void *, 0x60), 10,
                      FIELD(arg0, u8, 9), 4,
                      FIELD(object, s16, 0x2A), object, 2);
    }
    next_state = FIELD(arg0, u16, 0xA);
    FIELD(arg0, u16, 0x50) = 10;
    goto increment_loaded;

case5:
{
#ifdef __mips__
    register void *case5_setup_part ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
#else
    void *case5_setup_part;
#endif

    effect = func_8003FD64(0x312, D_80083498);
    if (effect != 0) {
        case5_setup_part = (u8 *)effect + 32;
        part = FIELD(effect, void *, 0xC);
        FIELD(effect, void *, 0x10) = D_80024850;
        FIELD(FIELD(effect, void *, 8), s32, 0) =
            FIELD(arg1, s32, 0) +
            (((func_80069EF8() & 0x1FF) - 255) << 13);
        FIELD(FIELD(effect, void *, 8), s32, 4) =
            FIELD(arg1, s32, 4) +
            (((func_80069EF8() & 0x1FF) - 255) << 13);
        FIELD(FIELD(effect, void *, 8), s32, 8) =
            FIELD(arg1, s32, 8) -
            ((func_80069EF8() & 0x1FF) << 12) + (s32)0xFFE00000;
        FIELD(part, s16, 30) = 3072;
        FIELD(part, s16, 28) = 3072;
        FIELD(part, s16, 16) = 32;
        FIELD(part, void *, 0) = D_800DEE38;
        FIELD(part, s32, 12) = 0x00808080;
        FIELD(part, u16, 20) |= 0xC;
        FIELD(case5_setup_part, u16, 74) = 8;
        {
            void *texture_data;

            texture_data = FIELD(part, void *, 0);
            texture_data = FIELD(texture_data, void *, 4);
            FIELD(part, u8, 4) = 0;
            FIELD(part, u8, 5) = 0;
            FIELD(part, void *, 8) = texture_data;
        }
        FIELD(effect, void *, 0x20) = arg0;
        FIELD(case5_setup_part, u16, 72) = func_80069EF8() & 3;
        FIELD(case5_setup_part, u16, 76) = 0;
    }
    timer = FIELD(arg0, u16, 0x50) - 1;
    FIELD(arg0, u16, 0x50) = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    goto increment_state;
}

increment_state:
    next_state = FIELD(arg0, u16, 0xA);
increment_loaded:
    next_state++;
    FIELD(arg0, u16, 0xA) = next_state;
    goto done;

case4:
{
    s32 case4_state;

    case4_state = FIELD(arg0, s16, 0x52);
    if (case4_state & 0x8000) {
        FIELD(arg0, u16, 0x52) &= 0x7FFF;
        goto done;
    }
    D_8008346C[0] = 0;
    FIELD((u8 *)arg0 - 2, u16, 0) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

done:
    ASM_SET(t1_reserve);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_SET(t2_reserve);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_SET(t3_reserve);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_SET(t4_reserve);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_SET(t5_reserve);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_SET(t6_reserve);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_SET(t7_reserve);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_SET(t8_reserve);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_SET(t9_reserve);
    return;
}


