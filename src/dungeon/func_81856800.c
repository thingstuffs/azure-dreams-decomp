#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_func_81856800_1 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 s16_0A;
        u16 u16_0A;
    } unk_0A;
    u8 pad_0C[0x44];
    union {
        s16 s16_50;
        u16 u16_50;
    } unk_50;
    union {
        s16 s16_52;
        u16 u16_52;
    } unk_52;
} S_func_81856800_1;

typedef struct S_func_81856800_2 {
    union {
        s32 s32_00;
        struct {
            u8 pad_00[0x2];
            u16 unk_02;
        } u16_02;
    } unk_00;
    union {
        s32 s32_04;
        struct {
            u8 pad_04[0x2];
            u16 unk_06;
        } u16_06;
    } unk_04;
    union {
        s32 s32_08;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } u16_0A;
    } unk_08;
    union {
        s32 s32_0C;
        struct {
            u8 pad_0C[0x2];
            s16 unk_0E;
        } s16_0E;
    } unk_0C;
    union {
        s32 s32_10;
        struct {
            u8 pad_10[0x2];
            s16 unk_12;
        } s16_12;
    } unk_10;
    union {
        s32 s32_14;
        struct {
            u8 pad_14[0x2];
            s16 unk_16;
        } s16_16;
    } unk_14;
} S_func_81856800_2;

typedef struct S_func_81856800_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    union {
        s8 s8_72;
        u8 u8_72;
    } unk_72;
    union {
        s8 s8_73;
        u8 u8_73;
    } unk_73;
} S_func_81856800_3;

typedef struct S_func_81856800_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_func_81856800_4;

typedef struct S_func_81856800_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_81856800_5;

typedef struct S_func_81856800_6 {
    void * unk_00;
    union {
        u16 u16_04;
        u8 u8_04;
        struct {
            u8 pad_04[0x1];
            u8 unk_05;
        } u8_05;
    } unk_04;
    u16 unk_06;
    union {
        void * ptr_08;
        u16 u16_08;
    } unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x14];
    s32 unk_34;
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    u16 unk_40;
    s16 unk_42;
    u8 pad_44[0x2];
    u16 unk_46;
    u16 unk_48;
    u16 unk_4A;
} S_func_81856800_6;

typedef struct S_func_81856800_7 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
} S_func_81856800_7;

typedef struct S_func_81856800_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_func_81856800_8;

typedef struct S_func_81856800_9 {
    u16 unk_00;
} S_func_81856800_9;

typedef struct S_func_81856800_10 {
    u8 pad_00[0x8];
    void * unk_08;
} S_func_81856800_10;

typedef struct S_func_81856800_11 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
} S_func_81856800_11;


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

BODY_STORAGE void FUNC_81856800_BODY(S_func_81856800_1 *action, void *motion_arg) BODY_ATTR;
/* Updates a staged movement effect, spawning particles and applying its final action. */
BODY_STORAGE void FUNC_81856800_BODY(S_func_81856800_1 *action, void *motion_arg)
{
#ifdef __mips__
    register S_func_81856800_2 *motion ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#else
    S_func_81856800_2 *motion;
#endif
#ifdef __mips__
    S_func_81856800_3 *object;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#else
    S_func_81856800_3 *object;
#endif
    S_func_81856800_5 *owner;
    S_func_81856800_4 *object_base;
    S_func_81856800_4 *effect;
    S_func_81856800_6 *part;
    S_func_81856800_10 *model;
    S_func_81856800_11 *src_point;
    s16 coord_offset[3];
    s32 state;
    s32 index;
    s32 target_height;
    s32 height_limit;
    s32 timer;
    s32 in_range;
    register s32 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t1_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t2_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t3_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t4_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t5_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t6_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t7_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t8_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t9_reserve;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    static void *const dispatch_labels[] = {
        &&case0, &&case1, &&case2, &&case3, &&case5, &&case4, &&done
    };

    (void)dispatch_labels;
    motion = motion_arg;
    object = action->unk_00;
    state = action->unk_0A.s16_0A;
    owner = ((S_func_81856800_4 *)((u8 *)object - 32))->unk_0C;
    object_base = (S_func_81856800_4 *)((u8 *)object - 32);

    if (state == 0) {
        goto dispatch_reload;
    }
    if (state == 5) {
        goto dispatch_range;
    }
    {
        S_func_81856800_7 *particle_data;
        s32 frame_index;
        u16 flags;

        index = 7;
        do {
            effect = func_8003FD64(0x312, D_80083498);
            if (effect != 0) {
                particle_data = (S_func_81856800_7 *)((u8 *)effect + 32);
                part = effect->unk_0C;
                ASM_KEEP(part);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                {
                    void *effect_type = D_80024850;

                    effect->unk_10 = effect_type;
                }
                ((S_func_81856800_2 *)effect->unk_08)->unk_00.s32_00 =
                    motion->unk_00.s32_00 +
                    (((func_80069EF8() & 0x1FF) - 255) << 13);
                ((S_func_81856800_2 *)effect->unk_08)->unk_04.s32_04 =
                    motion->unk_04.s32_04 +
                    (((func_80069EF8() & 0x1FF) - 255) << 13);
                ((S_func_81856800_2 *)effect->unk_08)->unk_08.s32_08 =
                    motion->unk_08.s32_08 -
                    (((func_80069EF8() & 0x1FF) - 255) << 14) +
                    (s32)0xFFE00000;
                flags = part->unk_14;
                part->unk_1E = 2048;
                part->unk_1C = 2048;
                flags |= 0xC;
                part->unk_14 = flags;
                if (index & 1) {
                    void *texture;
                    register s32 size ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                    {

                        size = 32;
                        texture = D_800DEC70;
                           /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                           /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                           /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                           /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        part->unk_0C = 0x00404040;
                    }
                    part->unk_10 = size;
                    part->unk_00 = texture;
                    particle_data->unk_4A = 16;
                } else {

                    {
                        s32 size;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        size = 96;
                        part->unk_10 = size;
                    }
                    {
                        void *texture;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        texture = D_800DEC50;
                        part->unk_00 = texture;
                    }
                    part->unk_0C = 0x00282828;
                    particle_data->unk_4A = 8;
                }
                {
                    S_func_81856800_8 *texture_data;

                    texture_data = part->unk_00;
                    texture_data = texture_data->unk_04;
                    part->unk_04.u8_04 = 0;
                    part->unk_04.u8_05.unk_05 = 0;
                    part->unk_08.ptr_08 = texture_data;
                }
                particle_data->unk_00 = action;
                frame_index = func_80069EF8() & 3;
                particle_data->unk_48 = frame_index;
                particle_data->unk_4C = 0;
            }
            index--;
        } while (index >= 0);
    }

dispatch_reload:
    state = action->unk_0A.s16_0A;
dispatch_range:
    in_range = (u32)(s32)state < 6;
dispatch_test:
    if (!in_range) {
        goto done;
    }
    goto *D_80024008[(u32)state];

case0:
    {
        S_func_81856800_9 *control;

        control = action->unk_04;
        if ((control->unk_00 & 0x80) == 0) {
            goto done;
        }
    }
    if (object->unk_60 == 0) {
        object->unk_72.u8_72 = owner->unk_24;
        object->unk_73.u8_73 = owner->unk_25;
    } else {
        register S_func_81856800_5 *child_owner ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        child_owner = ((S_func_81856800_4 *)((u8 *)object->unk_60 - 32))->unk_0C;
        object->unk_72.u8_72 = child_owner->unk_24;
        object->unk_73.u8_73 = child_owner->unk_25;
    }
    model = object_base->unk_0C;
    if (func_8003DE58(model->unk_08, model, coord_offset, 0) == 0) {
        coord_offset[2] = 0;
        coord_offset[1] = 0;
        coord_offset[0] = 0;
    }
    motion->unk_00.u16_02.unk_02 = ((S_func_81856800_2 *)object_base->unk_08)->unk_00.u16_02.unk_02 + coord_offset[0];
    motion->unk_04.u16_06.unk_06 = ((S_func_81856800_2 *)object_base->unk_08)->unk_04.u16_06.unk_06 + coord_offset[1];
    motion->unk_08.u16_0A.unk_0A = ((S_func_81856800_2 *)object_base->unk_08)->unk_08.u16_0A.unk_0A + coord_offset[2];
    action->unk_50.u16_50 = 8;
    {
        s32 velocity;
        s32 position;

        velocity = object->unk_72.s8_72;
        velocity <<= 6;
        position = motion->unk_00.u16_02.unk_02;
        position -= 32;
        velocity -= position;
        motion->unk_0C.s16_0E.unk_0E = velocity;
    }
    {
        s32 quotient;

        quotient = motion->unk_0C.s32_0C / action->unk_50.s16_50;
        ASM_KEEP(quotient);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        motion->unk_0C.s32_0C = quotient;
    }
    {
        s32 velocity;
        s32 position;

        velocity = object->unk_73.s8_73;
        velocity <<= 6;
        position = motion->unk_04.u16_06.unk_06;
        position -= 32;
        velocity -= position;
        motion->unk_10.s16_12.unk_12 = velocity;
    }
    {
        s32 quotient;

        quotient = motion->unk_10.s32_10 / action->unk_50.s16_50;
        motion->unk_10.s32_10 = quotient;
    }
    height_limit = (s16)(((S_func_81856800_2 *)object_base->unk_08)->unk_08.u16_0A.unk_0A - 48);
    target_height = func_800BCB04(motion->unk_00.u16_02.unk_02, motion->unk_04.u16_06.unk_06, height_limit);
    motion->unk_14.s16_16.unk_16 = target_height - motion->unk_08.u16_0A.unk_0A;
    motion->unk_14.s32_14 /= action->unk_50.s16_50;
    func_800A56E0(0x300);
    goto increment_state;

case1:
{
    s32 next_timer;

    motion->unk_00.s32_00 += motion->unk_0C.s32_0C;
    motion->unk_04.s32_04 += motion->unk_10.s32_10;
    motion->unk_08.s32_08 += motion->unk_14.s32_14;
    timer = action->unk_50.u16_50 - 1;
    action->unk_50.u16_50 = timer;
    next_timer = 10;
    if ((s16)timer > 0) {
        goto done;
    }
    next_state = action->unk_0A.u16_0A;
    action->unk_50.u16_50 = next_timer;
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
    timer = action->unk_50.u16_50 - 1;
    action->unk_50.u16_50 = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    if (object->unk_60 == 0) {
        action->unk_0A.u16_0A = 5;
        goto done;
    }
    index = 8;
    spawn_page = (u8 *)0x80080000;
    spawn_type = D_80024C40;

case2_spawn_loop:
    effect = func_8003FD64(0x201, spawn_page + 0x3498);
    if (effect != 0) {
        part = (S_func_81856800_6 *)((u8 *)effect + 32);
        effect->unk_10 = spawn_type;
        part->unk_48 = index;
        part->unk_04.u16_04 = motion->unk_00.u16_02.unk_02;
        part->unk_06 = motion->unk_04.u16_06.unk_06;
        part->unk_08.u16_08 = motion->unk_08.u16_0A.unk_0A;
        part->unk_46 = 3;
        effect->unk_20 = action;
        part->unk_4A = 0;
    }
    index -= 4;
    if (index >= 0) {
        goto case2_spawn_loop;
    }
    next_state = action->unk_0A.u16_0A;
    action->unk_50.u16_50 = 8;
    goto increment_loaded;
}

case3:
{
    s32 point_offset;
#ifdef __mips__
    register S_func_81856800_11 *dst_point ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 modulo_magic ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#else
    S_func_81856800_11 *dst_point;
#endif

    if (action->unk_50.s16_50 >= 6) {
        goto case3_tick;
    }
    effect = func_8003FD64(0x201, D_80083498);
    if (effect == 0) {
        goto case3_tick;
    }
    part = (S_func_81856800_6 *)((u8 *)effect + 32);
    effect->unk_10 = D_80024F40;
    func_8004491C(effect, D_800249BC);
    part->unk_04.u16_04 =
        motion->unk_00.u16_02.unk_02 + (func_80069EF8() & 0x3F) - 32;
    part->unk_06 =
        motion->unk_04.u16_06.unk_06 + (func_80069EF8() & 0x3F) - 32;
    part->unk_08.u16_08 = motion->unk_08.u16_0A.unk_0A;
    part->unk_40 = func_80066460(0, 3, 0x2C0, 0x100);
    part->unk_34 = 0x00707070;
    if (action->unk_50.u16_50 & 1) {
        part->unk_38 = 0xA0;
        part->unk_3A = 0;
    } else {
        part->unk_38 = 0x80;
        part->unk_3A = 32;
    }
    part->unk_3C = 0xBF;
    part->unk_3E = 0x1F;
    part->unk_42 = func_8006649C(0xA0, 0x1F7);
    part->unk_46 = 6;
    index = 1;
#ifdef __mips__
    modulo_magic = 0x19C2D14F;
#endif
    point_offset = 0;
    dst_point = (S_func_81856800_11 *)((u8 *)part + 8);
    do {
        src_point = (S_func_81856800_11 *)((u8 *)part + point_offset);
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
            mod_quotient = src_point->unk_04;
            mod_value -= mod_sign;
            mod_quotient += mod_value;
            mod_quotient -= 80;
            dst_point->unk_04 = mod_quotient;
        }
        {
            MipsProduct product;
            s32 mod_value;
            s32 mod_sign;
            register s32 mod_quotient ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            mod_value = func_80069EF8();
            product.value = (long long)mod_value * modulo_magic;
            point_offset += 8;
            index++;
            mod_sign = mod_value >> 31;
            mod_quotient = (product.words.hi >> 4) - mod_sign;
            mod_sign = (mod_quotient << 2) + mod_quotient;
            mod_sign = (mod_sign << 5) - mod_quotient;
            mod_quotient = src_point->unk_06;
            mod_value -= mod_sign;
            mod_quotient += mod_value;
            mod_quotient -= 80;
            dst_point->unk_06 = mod_quotient;
        }
#else
        dst_point->unk_04 =
            src_point->unk_04 + (func_80069EF8() % 159) - 80;
        dst_point->unk_06 =
            src_point->unk_06 + (func_80069EF8() % 159) - 80;
        point_offset += 8;
        index++;
#endif
        dst_point->unk_08 =
            src_point->unk_08 - ((func_80069EF8() & 0x1F) + 20);
        dst_point = (S_func_81856800_11 *)((u8 *)dst_point + 8);
    } while (index < 5);
    part->unk_00 = action;
    part->unk_4A = 0;
}

case3_tick:
    timer = action->unk_50.u16_50 - 1;
    action->unk_50.u16_50 = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    if (object->unk_60 != 0) {
        func_8009CE1C(object->unk_60, 10,
                      action->unk_09, 4,
                      object->unk_2A, object, 2);
    }
    next_state = action->unk_0A.u16_0A;
    action->unk_50.u16_50 = 10;
    goto increment_loaded;

case5:
{
#ifdef __mips__
    register S_func_81856800_7 *particle_data ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#else
    S_func_81856800_7 *particle_data;
#endif

    effect = func_8003FD64(0x312, D_80083498);
    if (effect != 0) {
        particle_data = (S_func_81856800_7 *)((u8 *)effect + 32);
        part = effect->unk_0C;
        effect->unk_10 = D_80024850;
        ((S_func_81856800_2 *)effect->unk_08)->unk_00.s32_00 =
            motion->unk_00.s32_00 +
            (((func_80069EF8() & 0x1FF) - 255) << 13);
        ((S_func_81856800_2 *)effect->unk_08)->unk_04.s32_04 =
            motion->unk_04.s32_04 +
            (((func_80069EF8() & 0x1FF) - 255) << 13);
        ((S_func_81856800_2 *)effect->unk_08)->unk_08.s32_08 =
            motion->unk_08.s32_08 -
            ((func_80069EF8() & 0x1FF) << 12) + (s32)0xFFE00000;
        part->unk_1E = 3072;
        part->unk_1C = 3072;
        part->unk_10 = 32;
        part->unk_00 = D_800DEE38;
        part->unk_0C = 0x00808080;
        part->unk_14 |= 0xC;
        particle_data->unk_4A = 8;
        {
            S_func_81856800_8 *texture_data;

            texture_data = part->unk_00;
            texture_data = texture_data->unk_04;
            part->unk_04.u8_04 = 0;
            part->unk_04.u8_05.unk_05 = 0;
            part->unk_08.ptr_08 = texture_data;
        }
        effect->unk_20 = action;
        particle_data->unk_48 = func_80069EF8() & 3;
        particle_data->unk_4C = 0;
    }
    timer = action->unk_50.u16_50 - 1;
    action->unk_50.u16_50 = timer;
    if ((s16)timer > 0) {
        goto done;
    }
    goto increment_state;
}

increment_state:
    next_state = action->unk_0A.u16_0A;
increment_loaded:
    next_state++;
    action->unk_0A.u16_0A = next_state;
    goto done;

case4:
{
    s32 finish_flags;

    finish_flags = action->unk_52.s16_52;
    if (finish_flags & 0x8000) {
        action->unk_52.u16_52 &= 0x7FFF;
        goto done;
    }
    D_8008346C[0] = 0;
    ((S_func_81856800_9 *)((u8 *)action - 2))->unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

done:
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return;
}


