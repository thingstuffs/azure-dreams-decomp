#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

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

extern u8 D_80024850[];
extern u8 D_800DEE38[];
extern u8 D_800DEC50[];
extern u8 D_800DEC70[];
extern u8 D_800249BC[];
extern u8 D_80024F40[];
extern u8 D_80024C40[];

void func_80024020(S_func_81856800_1 *action, S_func_81856800_2 *motion_arg);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const module_entry)(S_func_81856800_1 *, S_func_81856800_2 *) __asm__("func_80024000") = func_80024020;

/* Updates a staged movement effect, spawning particles and applying its final action. */
void func_80024020(S_func_81856800_1 *action, S_func_81856800_2 *motion_arg)
{
#ifdef __mips__
    S_func_81856800_2 *motion;
#else
    S_func_81856800_2 *motion;
#endif
    S_func_81856800_3 *object;
    S_func_81856800_5 *owner;
    S_func_81856800_4 *object_base;
    S_func_81856800_4 *effect;
    S_func_81856800_6 *part;
#ifdef __mips__
    S_func_81856800_7 *particle_data;
#endif
    S_func_81856800_10 *model;
    S_func_81856800_11 *src_point;
    s16 coord_offset[3];
    s32 state;
    s32 index;
    s32 target_height;
    s32 height_limit;
    s32 timer;
    s32 next_state;
    s32 next_timer;
    s32 page_or_magic;
    s32 t1_reserve;
    s32 t2_reserve;
    s32 t3_reserve;
    s32 t4_reserve;
    s32 t5_reserve;
    s32 t6_reserve;
    s32 t7_reserve;
    s32 t8_reserve;
    s32 t9_reserve;
    object = action->unk_00;
    state = action->unk_0A.s16_0A;
    owner = ((S_func_81856800_4 *)((u8 *)object - 32))->unk_0C;
    object_base = (S_func_81856800_4 *)((u8 *)object - 32);

    if (state != 0 && state != 5) {
        {
#ifndef __mips__
            S_func_81856800_7 *particle_data;
#endif
            s32 frame_index;
            u16 flags;

            index = 7;
            do {
                effect = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
                if (effect != 0) {
                    particle_data = (S_func_81856800_7 *)((u8 *)effect + 32);
                    part = effect->unk_0C;
                    {
                        void *effect_type = D_80024850;

                        effect->unk_10 = effect_type;
                    }
                    ((S_func_81856800_2 *)effect->unk_08)->unk_00.s32_00 =
                        motion_arg->unk_00.s32_00 +
                        (((func_80069EF8() & 0x1FF) - 255) << 13);
                    ((S_func_81856800_2 *)effect->unk_08)->unk_04.s32_04 =
                        motion_arg->unk_04.s32_04 +
                        (((func_80069EF8() & 0x1FF) - 255) << 13);
                    ((S_func_81856800_2 *)effect->unk_08)->unk_08.s32_08 =
                        motion_arg->unk_08.s32_08 -
                        (((func_80069EF8() & 0x1FF) - 255) << 14) +
                        (s32)0xFFE00000;
                    flags = part->unk_14;
                    part->unk_1E = 2048;
                    part->unk_1C = 2048;
                    flags |= 0xC;
                    part->unk_14 = flags;
                    if (index & 1) {
                        void *texture;

                        {

                            part->unk_10 = 32;
                            texture = D_800DEC70;
                            part->unk_0C = 0x00404040;
                        }
                        part->unk_00 = texture;
                        particle_data->unk_4A = 16;
                    } else {

                        {
                            s32 size;

                            size = 96;
                            part->unk_10 = size;
                        }
                        {
                            void *texture;

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
        state = action->unk_0A.s16_0A;
    }
    switch (state) {
    case 0:
    {
        S_func_81856800_9 *control;

        control = action->unk_04;
        if ((control->unk_00 & 0x80) == 0) {
            return;
        }
    }
        if (object->unk_60 == 0) {
            object->unk_72.u8_72 = owner->unk_24;
            object->unk_73.u8_73 = owner->unk_25;
        } else {


            part = ((S_func_81856800_4 *)((u8 *)object->unk_60 - 32))->unk_0C;
            object->unk_72.u8_72 = ((S_func_81856800_5 *)part)->unk_24;
            object->unk_73.u8_73 = ((S_func_81856800_5 *)part)->unk_25;
        }
        model = object_base->unk_0C;
        if (func_8003DE58(model->unk_08, model, coord_offset, 0) == 0) {
            coord_offset[2] = 0;
            coord_offset[1] = 0;
            coord_offset[0] = 0;
        }
        motion_arg->unk_00.u16_02.unk_02 = ((S_func_81856800_2 *)object_base->unk_08)->unk_00.u16_02.unk_02
            + coord_offset[0];
        motion_arg->unk_04.u16_06.unk_06 = ((S_func_81856800_2 *)object_base->unk_08)->unk_04.u16_06.unk_06
            + coord_offset[1];
        motion_arg->unk_08.u16_0A.unk_0A = ((S_func_81856800_2 *)object_base->unk_08)->unk_08.u16_0A.unk_0A
            + coord_offset[2];
        action->unk_50.u16_50 = 8;
        {
            s32 velocity;
            s32 position;

            velocity = object->unk_72.s8_72;
            velocity <<= 6;
            position = motion_arg->unk_00.u16_02.unk_02;
            position -= 32;
            velocity -= position;
            motion_arg->unk_0C.s16_0E.unk_0E = velocity;
        }
        {
            s32 quotient;

            quotient = motion_arg->unk_0C.s32_0C / action->unk_50.s16_50;
            motion_arg->unk_0C.s32_0C = quotient;
        }
        {
            s32 velocity;
            s16 position;

            velocity = object->unk_73.s8_73;
            velocity <<= 6;
            position = motion_arg->unk_04.u16_06.unk_06;
            position -= 32;
            motion_arg->unk_10.s16_12.unk_12 = (s16)velocity - position;
        }
        {
            s32 quotient;

            quotient = motion_arg->unk_10.s32_10 / action->unk_50.s16_50;
            motion_arg->unk_10.s32_10 = quotient;
        }
        height_limit = (s16)(((S_func_81856800_2 *)object_base->unk_08)->unk_08.u16_0A.unk_0A - 48);
        target_height = func_800BCB04(motion_arg->unk_00.u16_02.unk_02, motion_arg->unk_04.u16_06.unk_06, height_limit);
        motion_arg->unk_14.s16_16.unk_16 = target_height - motion_arg->unk_08.u16_0A.unk_0A;
        motion_arg->unk_14.s32_14 /= action->unk_50.s16_50;
        func_800A56E0(0x300);
        next_state = action->unk_0A.u16_0A;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;

    case 1:
    {
        motion_arg->unk_00.s32_00 += motion_arg->unk_0C.s32_0C;
        motion_arg->unk_04.s32_04 += motion_arg->unk_10.s32_10;
        motion_arg->unk_08.s32_08 += motion_arg->unk_14.s32_14;
        timer = action->unk_50.u16_50 - 1;
        action->unk_50.u16_50 = timer;
        next_timer = 10;
        if ((s16)timer > 0) {
            return;
        }
        next_state = action->unk_0A.u16_0A;
        action->unk_50.u16_50 = next_timer;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;
    }

    case 2:
    {
        void *spawn_type;
        u8 *spawn_page;
        timer = action->unk_50.u16_50 - 1;
        action->unk_50.u16_50 = timer;
        if ((s16)timer > 0) {
            return;
        }
        if (object->unk_60 == 0) {
            action->unk_0A.u16_0A = 5;
            return;
        }
        index = 8;
        page_or_magic = (s32)0x80080000;
        spawn_type = D_80024C40;

case2_spawn_loop:
        effect = func_8003FD64(0x201, (void *)(page_or_magic + 0x3498));
        if (effect != 0) {
            part = (S_func_81856800_6 *)((u8 *)effect + 32);
            effect->unk_10 = spawn_type;
            part->unk_48 = index;
            part->unk_04.u16_04 = motion_arg->unk_00.u16_02.unk_02;
            part->unk_06 = motion_arg->unk_04.u16_06.unk_06;
            part->unk_08.u16_08 = motion_arg->unk_08.u16_0A.unk_0A;
            part->unk_46 = 3;
            effect->unk_20 = action;
            part->unk_4A = 0;
        }
        index -= 4;
        if (index >= 0) {
            goto case2_spawn_loop;
        }
        next_state = action->unk_0A.u16_0A;
        next_timer = 8;
        action->unk_50.u16_50 = next_timer;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;
    }

    case 3:
    {
        s32 point_offset;
#ifdef __mips__
        S_func_81856800_11 *dst_point;
#else
        S_func_81856800_11 *dst_point;
#endif

        if (action->unk_50.s16_50 < 6) {
            effect = func_8003FD64(0x201, ((u8 *)(&D_80083498)));
            if (effect != 0) {
                part = (S_func_81856800_6 *)((u8 *)effect + 32);
                effect->unk_10 = D_80024F40;
                func_8004491C(effect, D_800249BC);
                part->unk_04.u16_04 =
                    motion_arg->unk_00.u16_02.unk_02 + (func_80069EF8() & 0x3F) - 32;
                part->unk_06 =
                    motion_arg->unk_04.u16_06.unk_06 + (func_80069EF8() & 0x3F) - 32;
                part->unk_08.u16_08 = motion_arg->unk_08.u16_0A.unk_0A;
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
                page_or_magic = 0x19C2D14F;
#endif
                point_offset = 0;
                do {
                    dst_point = (S_func_81856800_11 *)((u8 *)part + index * 8);
                    src_point = (S_func_81856800_11 *)((u8 *)part + (index - 1) * 8);
#ifdef __mips__
                    {
                        MipsProduct product;
                        s32 mod_value;
                        s32 mod_sign;
                        s32 mod_quotient;

                        mod_value = func_80069EF8();
                        product.value = (long long)mod_value * page_or_magic;
                        mod_quotient = (product.words.hi >> 4) - ((s32)(mod_value >> 31));
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
                        s32 mod_quotient;

                        mod_value = func_80069EF8();
                        product.value = (long long)mod_value * page_or_magic;

                        mod_quotient = (product.words.hi >> 4) - ((s32)(mod_value >> 31));
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

#endif
                    dst_point->unk_08 =
                        src_point->unk_08 - ((func_80069EF8() & 0x1F) + 20);
                    index++;
                } while (index < 5);
                part->unk_00 = action;
                part->unk_4A = 0;
            }
        }
    }
        timer = action->unk_50.u16_50 - 1;
        action->unk_50.u16_50 = timer;
        if ((s16)timer > 0) {
            return;
        }
        if (object->unk_60 != 0) {
            func_8009CE1C(object->unk_60, 10,
                          action->unk_09, 4,
                          object->unk_2A, object, 2);
        }
        next_state = action->unk_0A.u16_0A;
        next_timer = 10;
        action->unk_50.u16_50 = next_timer;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;

    case 4:
    {
#ifndef __mips__
        S_func_81856800_7 *particle_data;
#endif


        effect = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
        if (effect != 0) {
            particle_data = (S_func_81856800_7 *)((u8 *)effect + 32);
            part = effect->unk_0C;
            effect->unk_10 = D_80024850;
            ((S_func_81856800_2 *)effect->unk_08)->unk_00.s32_00 =
                motion_arg->unk_00.s32_00 +
                (((func_80069EF8() & 0x1FF) - 255) << 13);
            ((S_func_81856800_2 *)effect->unk_08)->unk_04.s32_04 =
                motion_arg->unk_04.s32_04 +
                (((func_80069EF8() & 0x1FF) - 255) << 13);
            ((S_func_81856800_2 *)effect->unk_08)->unk_08.s32_08 =
                motion_arg->unk_08.s32_08 -
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
            return;
        }
        next_state = action->unk_0A.u16_0A;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;
    }


    case 5:
    {
        s32 finish_flags;

        finish_flags = action->unk_52.s16_52;
        if (finish_flags & 0x8000) {
            action->unk_52.u16_52 &= 0x7FFF;
            return;
        }
        dungeonStatus.unk_0C = 0;
        ((S_func_81856800_9 *)((u8 *)action - 2))->unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
    }
}
