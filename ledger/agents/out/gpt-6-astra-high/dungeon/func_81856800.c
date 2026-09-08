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

BODY_STORAGE void FUNC_81856800_BODY(void *action, void *motion_arg) BODY_ATTR;
/* Updates a staged movement effect, spawning particles and applying its final action. */
BODY_STORAGE void FUNC_81856800_BODY(void *action, void *motion_arg)
{
#ifdef __mips__
    register void *motion ASM_REG("$20");
#else
    void *motion;
#endif
#ifdef __mips__
    register void *object ASM_REG("$23");
#else
    void *object;
#endif
    void *owner;
    u8 *object_base;
    void *effect;
    void *part;
    void *model;
    void *src_point;
    s16 coord_offset[3];
    s32 state;
    s32 index;
    s32 target_height;
    s32 height_limit;
    s32 timer;
    s32 in_range;
    register s32 next_state ASM_REG("$2");
    register s32 t1_reserve ASM_REG("$9");
    register s32 t2_reserve ASM_REG("$10");
    register s32 t3_reserve ASM_REG("$11");
    register s32 t4_reserve ASM_REG("$12");
    register s32 t5_reserve ASM_REG("$13");
    register s32 t6_reserve ASM_REG("$14");
    register s32 t7_reserve ASM_REG("$15");
    register s32 t8_reserve ASM_REG("$24");
    register s32 t9_reserve ASM_REG("$25");
    static void *const dispatch_labels[] = {
        &&case0, &&case1, &&case2, &&case3, &&case5, &&case4, &&done
    };

    (void)dispatch_labels;
    motion = motion_arg;
    object = FIELD(action, void *, 0);
    state = FIELD(action, s16, 0xA);
    owner = FIELD(object, void *, -20);
    object_base = (u8 *)object - 32;

    if (state == 0) {
        goto dispatch_reload;
    }
    if (state == 5) {
        goto dispatch_range;
    }
    {
        void *particle_data;
        s32 frame_index;
        register s32 setup_kind ASM_REG("$2");
        u16 flags;

        index = 7;
        do {
            effect = func_8003FD64(0x312, D_80083498);
            if (effect != 0) {
                particle_data = (u8 *)effect + 32;
                part = FIELD(effect, void *, 0xC);
                ASM_KEEP(part);
                {
                    void *effect_type = D_80024850;

                    FIELD(effect, void *, 0x10) = effect_type;
                }
                FIELD(FIELD(effect, void *, 8), s32, 0) =
                    FIELD(motion, s32, 0) +
                    (((func_80069EF8() & 0x1FF) - 255) << 13);
                FIELD(FIELD(effect, void *, 8), s32, 4) =
                    FIELD(motion, s32, 4) +
                    (((func_80069EF8() & 0x1FF) - 255) << 13);
                FIELD(FIELD(effect, void *, 8), s32, 8) =
                    FIELD(motion, s32, 8) -
                    (((func_80069EF8() & 0x1FF) - 255) << 14) +
                    (s32)0xFFE00000;
                flags = FIELD(part, u16, 20);
                FIELD(part, s16, 30) = 2048;
                FIELD(part, s16, 28) = 2048;
                flags |= 0xC;
                FIELD(part, u16, 20) = flags;
                if (index & 1) {
                    void *texture;
                    register s32 size ASM_REG("$3");

                    {
                        register s32 color ASM_REG("$2");

                        color = 0x00404040;
                        size = 32;
                        texture = D_800DEC70;
                        ASM_CLOBBER("$4");
                        ASM_CLOBBER("$5");
                        ASM_CLOBBER("$6");
                        ASM_CLOBBER("$7");
                        ASM_KEEP(texture);
                        FIELD(part, s32, 12) = color;
                    }
                    setup_kind = 16;
                    FIELD(part, s16, 16) = size;
                    FIELD(part, void *, 0) = texture;
                } else {
                    register s32 color ASM_REG("$3");

                    color = 0x00282828;
                    {
                        register s32 size ASM_REG("$2");

                        size = 96;
                        FIELD(part, s16, 16) = size;
                    }
                    {
                        register void *texture ASM_REG("$2");

                        texture = D_800DEC50;
                        FIELD(part, void *, 0) = texture;
                    }
                    setup_kind = 8;
                    FIELD(part, s32, 12) = color;
                }
                FIELD(particle_data, u16, 74) = setup_kind;
                {
                    void *texture_data;

                    texture_data = FIELD(part, void *, 0);
                    texture_data = FIELD(texture_data, void *, 4);
                    FIELD(part, u8, 4) = 0;
                    FIELD(part, u8, 5) = 0;
                    FIELD(part, void *, 8) = texture_data;
                }
                FIELD(particle_data, void *, 0) = action;
                frame_index = func_80069EF8() & 3;
                FIELD(particle_data, u16, 72) = frame_index;
                FIELD(particle_data, u16, 76) = 0;
            }
            index--;
        } while (index >= 0);
    }

dispatch_reload:
    state = FIELD(action, s16, 0xA);
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

        control = FIELD(action, void *, 4);
        if ((FIELD(control, u16, 0) & 0x80) == 0) {
            goto done;
        }
    }
    if (FIELD(object, void *, 0x60) == 0) {
        FIELD(object, u8, 0x72) = FIELD(owner, u8, 0x24);
        FIELD(object, u8, 0x73) = FIELD(owner, u8, 0x25);
    } else {
        register void *child_owner ASM_REG("$17");

        child_owner = FIELD(FIELD(object, void *, 0x60), void *, -20);
        FIELD(object, u8, 0x72) = FIELD(child_owner, u8, 0x24);
        FIELD(object, u8, 0x73) = FIELD(child_owner, u8, 0x25);
    }
    model = FIELD(object_base, void *, 0xC);
    if (func_8003DE58(FIELD(model, void *, 8), model, coord_offset, 0) == 0) {
        coord_offset[2] = 0;
        coord_offset[1] = 0;
        coord_offset[0] = 0;
    }
    FIELD(motion, u16, 2) = FIELD(FIELD(object_base, void *, 8), u16, 2) + coord_offset[0];
    FIELD(motion, u16, 6) = FIELD(FIELD(object_base, void *, 8), u16, 6) + coord_offset[1];
    FIELD(motion, u16, 0xA) = FIELD(FIELD(object_base, void *, 8), u16, 0xA) + coord_offset[2];
    FIELD(action, u16, 0x50) = 8;
    {
        s32 velocity;
        s32 position;

        velocity = FIELD(object, s8, 0x72);
        velocity <<= 6;
        position = FIELD(motion, u16, 2);
        position -= 32;
        velocity -= position;
        FIELD(motion, s16, 0xE) = velocity;
    }
    {
        s32 quotient;

        quotient = FIELD(motion, s32, 0xC) / FIELD(action, s16, 0x50);
        ASM_KEEP(quotient);
        FIELD(motion, s32, 0xC) = quotient;
    }
    {
        s32 velocity;
        s32 position;

        velocity = FIELD(object, s8, 0x73);
        velocity <<= 6;
        position = FIELD(motion, u16, 6);
        position -= 32;
        velocity -= position;
        FIELD(motion, s16, 0x12) = velocity;
    }
    {
        s32 quotient;

        quotient = FIELD(motion, s32, 0x10) / FIELD(action, s16, 0x50);
        FIELD(motion, s32, 0x10) = quotient;
    }
    height_limit = (s16)(FIELD(FIELD(object_base, void *, 8), u16, 0xA) - 48);
    target_height = func_800BCB04(FIELD(motion, u16, 2), FIELD(motion, u16, 6), height_limit);
    FIELD(motion, s16, 0x16) = target_height - FIELD(motion, u16, 0xA);
    FIELD(motion, s32, 0x14) /= FIELD(action, s16, 0x50);
    func_800A56E0(0x300);
    goto increment_state;

case1:
{
    s32 next_timer;

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    FIELD(motion, s32, 8) += FIELD(motion, s32, 0x14);
    timer = FIELD(action, u16, 0x50) - 1;
    FIELD(action, u16, 0x50) = timer;
    next_timer = 10;
    if ((s16)timer > 0) {
        goto done;
    }
    next_state = FIELD(action, u16, 0xA);
    FIELD(action, u16, 0x50) = next_timer;
    goto increment_loaded;
}

case2:
{
    void *spawn_type;
#ifdef __mips__
    register u8 *spawn_page ASM_REG("$22");
#else
    u8 *spawn_page;
#endif
    timer = FIELD(action, u16, 0x50) - 1;
    FIELD(action, u16, 0x50) = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    if (FIELD(object, void *, 0x60) == 0) {
        FIELD(action, u16, 0xA) = 5;
        goto done;
    }
    index = 8;
    spawn_page = (u8 *)0x80080000;
    spawn_type = D_80024C40;

case2_spawn_loop:
    effect = func_8003FD64(0x201, spawn_page + 0x3498);
    if (effect != 0) {
        part = (u8 *)effect + 32;
        FIELD(effect, void *, 0x10) = spawn_type;
        FIELD(part, u16, 0x48) = index;
        FIELD(part, u16, 4) = FIELD(motion, u16, 2);
        FIELD(part, u16, 6) = FIELD(motion, u16, 6);
        FIELD(part, u16, 8) = FIELD(motion, u16, 0xA);
        FIELD(part, u16, 0x46) = 3;
        FIELD(effect, void *, 0x20) = action;
        FIELD(part, u16, 0x4A) = 0;
    }
    index -= 4;
    if (index >= 0) {
        goto case2_spawn_loop;
    }
    next_state = FIELD(action, u16, 0xA);
    FIELD(action, u16, 0x50) = 8;
    goto increment_loaded;
}

case3:
{
    s32 point_offset;
#ifdef __mips__
    register void *dst_point ASM_REG("$18");
    register s32 modulo_magic ASM_REG("$22");
#else
    void *dst_point;
#endif

    if (FIELD(action, s16, 0x50) >= 6) {
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
        FIELD(motion, u16, 2) + (func_80069EF8() & 0x3F) - 32;
    FIELD(part, u16, 6) =
        FIELD(motion, u16, 6) + (func_80069EF8() & 0x3F) - 32;
    FIELD(part, u16, 8) = FIELD(motion, u16, 0xA);
    FIELD(part, u16, 0x40) = func_80066460(0, 3, 0x2C0, 0x100);
    FIELD(part, s32, 0x34) = 0x00707070;
    if (FIELD(action, u16, 0x50) & 1) {
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
    index = 1;
#ifdef __mips__
    modulo_magic = 0x19C2D14F;
#endif
    point_offset = 0;
    dst_point = (u8 *)part + 8;
    do {
        src_point = (u8 *)part + point_offset;
#ifdef __mips__
        {
            MipsProduct product;
            s32 mod_value;
            s32 mod_sign;
            register s32 mod_quotient ASM_REG("$4");

            mod_value = func_80069EF8();
            product.value = (long long)mod_value * modulo_magic;
            mod_sign = mod_value >> 31;
            mod_quotient = (product.words.hi >> 4) - mod_sign;
            mod_sign = (mod_quotient << 2) + mod_quotient;
            mod_sign = (mod_sign << 5) - mod_quotient;
            mod_quotient = FIELD(src_point, u16, 4);
            mod_value -= mod_sign;
            mod_quotient += mod_value;
            mod_quotient -= 80;
            FIELD(dst_point, u16, 4) = mod_quotient;
        }
        {
            MipsProduct product;
            s32 mod_value;
            s32 mod_sign;
            register s32 mod_quotient ASM_REG("$4");

            mod_value = func_80069EF8();
            product.value = (long long)mod_value * modulo_magic;
            point_offset += 8;
            index++;
            mod_sign = mod_value >> 31;
            mod_quotient = (product.words.hi >> 4) - mod_sign;
            mod_sign = (mod_quotient << 2) + mod_quotient;
            mod_sign = (mod_sign << 5) - mod_quotient;
            mod_quotient = FIELD(src_point, u16, 6);
            mod_value -= mod_sign;
            mod_quotient += mod_value;
            mod_quotient -= 80;
            FIELD(dst_point, u16, 6) = mod_quotient;
        }
#else
        FIELD(dst_point, u16, 4) =
            FIELD(src_point, u16, 4) + (func_80069EF8() % 159) - 80;
        FIELD(dst_point, u16, 6) =
            FIELD(src_point, u16, 6) + (func_80069EF8() % 159) - 80;
        point_offset += 8;
        index++;
#endif
        FIELD(dst_point, u16, 8) =
            FIELD(src_point, u16, 8) - ((func_80069EF8() & 0x1F) + 20);
        dst_point = (u8 *)dst_point + 8;
    } while (index < 5);
    FIELD(part, void *, 0) = action;
    FIELD(part, u16, 0x4A) = 0;
}

case3_tick:
    timer = FIELD(action, u16, 0x50) - 1;
    FIELD(action, u16, 0x50) = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    if (FIELD(object, void *, 0x60) != 0) {
        func_8009CE1C(FIELD(object, void *, 0x60), 10,
                      FIELD(action, u8, 9), 4,
                      FIELD(object, s16, 0x2A), object, 2);
    }
    next_state = FIELD(action, u16, 0xA);
    FIELD(action, u16, 0x50) = 10;
    goto increment_loaded;

case5:
{
#ifdef __mips__
    register void *particle_data ASM_REG("$18");
#else
    void *particle_data;
#endif

    effect = func_8003FD64(0x312, D_80083498);
    if (effect != 0) {
        particle_data = (u8 *)effect + 32;
        part = FIELD(effect, void *, 0xC);
        FIELD(effect, void *, 0x10) = D_80024850;
        FIELD(FIELD(effect, void *, 8), s32, 0) =
            FIELD(motion, s32, 0) +
            (((func_80069EF8() & 0x1FF) - 255) << 13);
        FIELD(FIELD(effect, void *, 8), s32, 4) =
            FIELD(motion, s32, 4) +
            (((func_80069EF8() & 0x1FF) - 255) << 13);
        FIELD(FIELD(effect, void *, 8), s32, 8) =
            FIELD(motion, s32, 8) -
            ((func_80069EF8() & 0x1FF) << 12) + (s32)0xFFE00000;
        FIELD(part, s16, 30) = 3072;
        FIELD(part, s16, 28) = 3072;
        FIELD(part, s16, 16) = 32;
        FIELD(part, void *, 0) = D_800DEE38;
        FIELD(part, s32, 12) = 0x00808080;
        FIELD(part, u16, 20) |= 0xC;
        FIELD(particle_data, u16, 74) = 8;
        {
            void *texture_data;

            texture_data = FIELD(part, void *, 0);
            texture_data = FIELD(texture_data, void *, 4);
            FIELD(part, u8, 4) = 0;
            FIELD(part, u8, 5) = 0;
            FIELD(part, void *, 8) = texture_data;
        }
        FIELD(effect, void *, 0x20) = action;
        FIELD(particle_data, u16, 72) = func_80069EF8() & 3;
        FIELD(particle_data, u16, 76) = 0;
    }
    timer = FIELD(action, u16, 0x50) - 1;
    FIELD(action, u16, 0x50) = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    goto increment_state;
}

increment_state:
    next_state = FIELD(action, u16, 0xA);
increment_loaded:
    next_state++;
    FIELD(action, u16, 0xA) = next_state;
    goto done;

case4:
{
    s32 finish_flags;

    finish_flags = FIELD(action, s16, 0x52);
    if (finish_flags & 0x8000) {
        FIELD(action, u16, 0x52) &= 0x7FFF;
        goto done;
    }
    D_8008346C[0] = 0;
    FIELD((u8 *)action - 2, u16, 0) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

done:
    ASM_SET(t1_reserve);
    ASM_SET(t2_reserve);
    ASM_SET(t3_reserve);
    ASM_SET(t4_reserve);
    ASM_SET(t5_reserve);
    ASM_SET(t6_reserve);
    ASM_SET(t7_reserve);
    ASM_SET(t8_reserve);
    ASM_SET(t9_reserve);
    return;
}


