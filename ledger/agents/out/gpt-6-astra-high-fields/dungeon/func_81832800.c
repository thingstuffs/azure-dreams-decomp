#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DEA68[];
extern u8 D_800DED70[];
extern s32 D_8008346C[];
extern s32 D_800814A0[3];
extern void func_80024354(void) __attribute__((noreturn));
extern void func_80024488(void) __attribute__((noreturn));
extern void func_80024490(void) __attribute__((noreturn));
extern void func_800247B4(void) __attribute__((noreturn));
void *func_8003FD64();                     /* extern */
M2C_UNK func_8004491C();                /* extern */
s32 func_80069EF8();                /* extern */
M2C_UNK func_8009CE1C(); /* extern */
void *func_800A05A4();      /* extern */
s16 func_800A3820();                         /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80024860;
extern M2C_UNK D_800248F0;

typedef struct S_func_81832800_1 {
    void *unk_00;
    u16 *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    u16 unk_0A;
    u8 pad_0C[0x44];
    u16 unk_50;
    union { s16 as_s16; u16 as_u16; } unk_52;
} S_func_81832800_1;

typedef struct S_func_81832800_2 {
    u8 pad_00[0x14];
    union { s32 as_s32; u32 as_u32; } unk_14;
    u8 pad_18[0x12];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
} S_func_81832800_2;

typedef struct S_func_81832800_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_81832800_3;

typedef struct S_func_81832800_4 {
    union {
        s32 as_s32;
        struct {
            u8 pad_00[2];
            union { s16 as_s16; u16 as_u16; } unk_02;
        } parts;
    } unk_00;
    union {
        s32 as_s32;
        struct {
            u8 pad_04[2];
            union { s16 as_s16; u16 as_u16; } unk_06;
        } parts;
    } unk_04;
    union {
        s32 as_s32;
        struct {
            u8 pad_08[2];
            union { s16 as_s16; u16 as_u16; } unk_0A;
        } parts;
    } unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_func_81832800_4;

typedef struct S_func_81832800_5 {
    void *unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    union { s16 as_s16; u16 as_u16; } unk_1C;
    union { s16 as_s16; u16 as_u16; } unk_1E;
    u8 pad_20[4];
    u8 unk_24;
    u8 unk_25;
} S_func_81832800_5;

typedef struct S_func_81832800_6 {
    void *unk_00;
    u8 pad_04[8];
    u16 unk_0C;
    u16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x3A];
    s16 unk_4C;
} S_func_81832800_6;

typedef struct S_func_81832800_7 {
    u8 pad_00[4];
    s32 unk_04;
} S_func_81832800_7;

typedef struct S_func_81832800_8 {
    s16 unk_00;
} S_func_81832800_8;

typedef struct S_func_81832800_9 {
    u16 unk_00;
} S_func_81832800_9;

extern void func_80024004(void);
__asm__(".set func_80024004, 0x80024004");

/* Retail places ONE 4-byte word (0x80024004) immediately before this
 * function's own code, under the func_81832800 symbol: the row's true base is
 * 0x80024000 and that word points at 0x80024004, the first instruction of the
 * body.  Same composite shape as the matched sibling func_81844800 (8-entry
 * table + body in one .text.<func> section).  Prior drafts modelled this word
 * as a dead `lb $v0, 0x4004($zero)` retained by a volatile-asm keep; that
 * keep is
 * a sched2 barrier and is what pinned the D_8006CCD8 %hi below the callee-save
 * stores. */
#ifdef __mips__
static void (*const func_81832800_table[])(void)
    __asm__("func_81832800")
    __attribute__((section(".text.func_81832800"), aligned(4))) = {
        func_80024004,
    };
__asm__(".globl func_81832800\n"
        ".type func_81832800,@function\n"
        ".size func_81832800, 2024");
#define BODY_NAME composite_body_81832800
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_81832800")))
#else
#define BODY_NAME func_81832800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *effect_in, void *position_in, void *effect_sprite) BODY_ATTR;
/* Advance the effect state, move toward its target, and animate spawned particles. */
BODY_STORAGE void BODY_NAME(void *effect_in, void *position_in, void *effect_sprite) {
    S_func_81832800_3 *source_object;
    s32 step_x;
    s32 step_y;
    s32 ground_height;
    s16 state;
    s32 color;
    s32 height_delta;
    register s32 spawn_value ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 height_step;
    s32 source_y;
    s32 jitter_base;
    s32 scale_random;
    register s32 state_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 delta_x;
    s32 random_x;
    s32 random_y;
    s32 random_height;
    s32 jitter_count;
    register s32 count ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 rounded_x;
    s32 rounded_y;
    s32 rounded_height;
    s32 jitter_x;
    s32 jitter_y;
    s32 origin_x;
    s32 origin_y;
    u16 scale_y;
    u16 spawn_state;
    u16 scale_x;
    S_func_81832800_2 *target;
    S_func_81832800_4 *jitter_position_x;
    S_func_81832800_4 *jitter_position_y;
    S_func_81832800_4 *burst_position;
    S_func_81832800_4 *burst_position_y;
    S_func_81832800_4 *target_position;
    S_func_81832800_5 *source_sprite;
    S_func_81832800_5 *sprite;
    S_func_81832800_6 *particle_data;
    S_func_81832800_2 *source;
    S_func_81832800_3 *object;
    S_func_81832800_4 *particle_position;
    S_func_81832800_2 *found_target;
    S_func_81832800_4 *height_position;
    register u32 sprite_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 init_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *particle_callback;
    S_func_81832800_7 *particle_texture;
    register S_func_81832800_1 *effect ASM_REG("$22") = effect_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register S_func_81832800_4 *position ASM_REG("$23") = position_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    sprite_flags = (u32) D_8006CCD8;
    source = effect->unk_00;
    init_value = source->unk_2A;
    ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    source_sprite = ((S_func_81832800_3 *) ((u8 *) source - 0x20))->unk_0C;
    count = (u16) init_value >> 8;
    spawn_value = count & 0xE;
    step_x = (s32) ((S_func_81832800_8 *) ((u8 *) (void *) sprite_flags + spawn_value))->unk_00;
    step_y = (s32) ((S_func_81832800_8 *) ((u8 *) D_8006CCE8 + spawn_value))->unk_00;
    spawn_state = effect->unk_0A;
    effect->unk_50 = (u16) (effect->unk_50 - 1);
    source_object = (S_func_81832800_3 *) ((u8 *) source - 0x20);
    if ((u32) (spawn_state - 1) < 3U) {
        count = 3;
        if ((s16) spawn_state < 3) {
            count = 5;
        }
        particle_callback = &D_80024860;
        particle_texture = (S_func_81832800_7 *) D_800DEA68;
        if (count >= 0) {
first_spawn_loop:
            object = func_8003FD64(0x312, D_80083498);
            if (object != NULL) {
                void *callback;
                S_func_81832800_4 *spawn_position;
                func_8004491C(object, D_80045340);
                sprite = object->unk_0C;
                spawn_position = object->unk_08;
                callback = particle_callback;
                object->unk_10 = callback;
                spawn_position->unk_00.as_s32 = (s32) position->unk_00.as_s32;
                particle_data = (S_func_81832800_6 *) ((u8 *) object + 0x20);
                jitter_count = 1;
                ((S_func_81832800_4 *) object->unk_08)->unk_04.as_s32 = (s32) position->unk_04.as_s32;
                do {
                    spawn_value = func_80069EF8();
                    jitter_position_x = object->unk_08;
                    init_value = jitter_position_x->unk_00.parts.unk_02.as_u16;
                    jitter_x = spawn_value;
                    jitter_base = init_value - 0x10;
                    if (spawn_value < 0) {
                        jitter_x = spawn_value + 0x1F;
                    }
                    init_value = spawn_value - ((jitter_x >> 5) << 5);
                    init_value = jitter_base + init_value;
                    jitter_position_x->unk_00.parts.unk_02.as_u16 = (u16) init_value;
                    spawn_value = func_80069EF8(spawn_value, jitter_position_x, jitter_base);
                    jitter_position_y = object->unk_08;
                    init_value = jitter_position_y->unk_04.parts.unk_06.as_u16;
                    jitter_y = spawn_value;
                    jitter_base = init_value - 0x10;
                    if (spawn_value < 0) {
                        jitter_y = spawn_value + 0x1F;
                    }
                    init_value = spawn_value - ((jitter_y >> 5) << 5);
                    init_value = jitter_base + init_value;
                    jitter_count -= 1;
                    jitter_position_y->unk_04.parts.unk_06.as_u16 = (u16) init_value;
                } while (jitter_count >= 0);
                particle_position = object->unk_08;
                ((S_func_81832800_4 *) object->unk_08)->unk_08.parts.unk_0A.as_s16 = func_800BCB04(particle_position->unk_00.parts.unk_02.as_u16, particle_position->unk_04.parts.unk_06.as_u16, (s16) (position->unk_08.parts.unk_0A.as_u16 - 0x30));
                height_position = object->unk_08;
                if (height_position->unk_08.parts.unk_0A.as_s16 >= 0x200) {
                    height_position->unk_08.parts.unk_0A.as_s16 = (s16) position->unk_08.parts.unk_0A.as_u16;
                }
                position->unk_08.parts.unk_0A.as_u16 = (u16) ((S_func_81832800_4 *) object->unk_08)->unk_08.parts.unk_0A.as_s16;
                color = 0xC0C0C0;
                {
                    s32 scale = 0x1400;
                    sprite_flags = sprite->unk_14;
                    sprite->unk_1E.as_s16 = (s16) scale;
                    sprite->unk_1C.as_s16 = (s16) scale;
                    sprite->unk_10 = 0;
                    sprite->unk_0C = color;
                    sprite->unk_00 = particle_texture;
                    sprite_flags |= 0xC;
                    sprite->unk_14 = sprite_flags;
                    init_value = particle_texture->unk_04;
                }
                sprite->unk_04 = 0;
                sprite->unk_05 = 0;
                sprite->unk_08 = init_value;
                particle_data->unk_00 = effect;
                particle_data->unk_4C = 0;
            }
            count -= 1;
            if (count >= 0) {
                goto first_spawn_loop;
            }
        }
    }
    state = (s16) effect->unk_0A;
    if (state != 2) {
        if (state < 3) {
            if (state != 0) {
                if (state != 1) {
                    func_800247B4();
                    return;
                }
                goto state_1;
            }
            goto state_0;
        } else if (state != 0xF0) {
            if (state < 0xF1) {
                if (state != 3) {
                    func_800247B4();
                    return;
                }
                count = 3;
                goto state_3;
            }
            if (state != 0xFF) {
                func_800247B4();
                return;
            }
            goto state_FF;
        }
        goto state_F0;
    }
    goto state_2;

state_0:
    if (*effect->unk_04 & 0x80) {
        found_target = func_800A05A4(source, source_sprite->unk_24, source_sprite->unk_25, (s16) source->unk_2A, (s32) func_800A3820(6));
        source->unk_60 = found_target;
        if (found_target == NULL) {
            source->unk_72 = (u8) source_sprite->unk_24;
            source->unk_73 = (u8) source_sprite->unk_25;
            func_80024354();
            return;
        }
        sprite = ((S_func_81832800_3 *) ((u8 *) found_target - 0x20))->unk_0C;
        if (!(sprite->unk_14 & 0x8000) || !(((S_func_81832800_5 *) effect_sprite)->unk_14 & 0x8000)) {
            source->unk_72 = (u8) sprite->unk_24;
            source->unk_73 = (u8) sprite->unk_25;
            position->unk_00.as_s32 = (s32) ((S_func_81832800_4 *) source_object->unk_08)->unk_00.as_s32;
            position->unk_04.as_s32 = (s32) ((S_func_81832800_4 *) source_object->unk_08)->unk_04.as_s32;
            position->unk_08.as_s32 = (s32) ((S_func_81832800_4 *) source_object->unk_08)->unk_08.as_s32;
            delta_x = (s8) source->unk_72;
            state_value = source_sprite->unk_24;
            source_y = source_sprite->unk_25;
            delta_x -= state_value;
            state_value = (s8) source->unk_73;
            count = delta_x;
            if (delta_x < 0) {
                count = 0 - count;
            }
            state_value -= source_y;
            jitter_count = state_value;
            if (state_value < 0) {
                jitter_count = 0 - jitter_count;
            }
            if (count < jitter_count) {
                count = jitter_count;
            }
            init_value = count * 4;
            effect->unk_50 = init_value;
            position->unk_0C = (s32) (step_x << 0x14);
            position->unk_10 = (s32) (step_y << 0x14);
            func_800A56E0(0x300);
            init_value = effect->unk_0A;
            init_value += 1;
            ASM_TAILSLOT_PIN(init_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_80024490();
            return;
        }
        goto state_F0_end;
    }
    return;

state_1:
    if ((s16) effect->unk_50 >= 0) {
        position->unk_00.as_s32 += position->unk_0C;
        position->unk_04.as_s32 += position->unk_10;
        func_800247B4();
        return;
    }
    state_value = effect->unk_0A;
    ASM_KEEP(state_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    delta_x = 6;
    ASM_TAILSLOT_PIN(delta_x);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024488();
    return;

state_2:
    if ((s16) effect->unk_50 <= 0) {
        sprite_flags = 0x100000;
        target = source->unk_60;
        if (target == NULL) {
            goto state_null;
        }
        target->unk_14.as_s32 = (s32) (target->unk_14.as_s32 | sprite_flags);
        effect->unk_50 = 0x14U;
        effect->unk_0A += 1;
        func_800247B4();
        return;
    }
    return;

state_3:
    ground_height = (s16) func_800BCB04(position->unk_00.parts.unk_02.as_u16, position->unk_04.parts.unk_06.as_u16, (s16) (position->unk_08.parts.unk_0A.as_u16 - 0x30));
    do {
        object = func_8003FD64(0x312, D_80083498);
        if (object != NULL) {
            void *callback;
            func_8004491C(object, D_80045340);
            particle_data = (S_func_81832800_6 *) ((u8 *) object + 0x20);
            sprite = object->unk_0C;
            callback = &D_800248F0;
            object->unk_10 = callback;
            rounded_x = func_80069EF8();
            random_x = rounded_x;
            burst_position = object->unk_08;
            origin_x = position->unk_00.parts.unk_02.as_u16;
            particle_data->unk_0C = origin_x;
            if (random_x < 0) {
                rounded_x = random_x + 0x7F;
            }
            burst_position->unk_00.parts.unk_02.as_s16 = (s16) ((origin_x + (random_x - ((rounded_x >> 7) << 7))) - 0x40);
            rounded_y = func_80069EF8((s32) origin_x, burst_position);
            random_y = rounded_y;
            burst_position_y = object->unk_08;
            origin_y = position->unk_04.parts.unk_06.as_u16;
            particle_data->unk_0E = origin_y;
            if (random_y < 0) {
                rounded_y = random_y + 0x7F;
            }
            burst_position_y->unk_04.parts.unk_06.as_s16 = (s16) ((origin_y + (random_y - ((rounded_y >> 7) << 7))) - 0x40);
            rounded_height = func_80069EF8((s32) origin_y, burst_position_y);
            random_height = rounded_height;
            burst_position = object->unk_08;
            particle_data->unk_10 = ground_height;
            if (random_height < 0) {
                rounded_height = random_height + 0x3F;
            }
            burst_position->unk_08.parts.unk_0A.as_s16 = (s16) ((ground_height + (random_height - ((rounded_height >> 6) << 6))) - 0x80);
            color = 0x101010;
            sprite_flags = sprite->unk_14;
            sprite->unk_1E.as_s16 = 0x1000;
            sprite->unk_1C.as_s16 = 0x1000;
            sprite->unk_10 = 0x20;
            sprite->unk_0C = color;
            sprite->unk_00 = D_800DED70;
            sprite_flags |= 0xC;
            sprite->unk_14 = sprite_flags;
            init_value = (s32) ((S_func_81832800_7 *) D_800DED70)->unk_04;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->unk_08 = init_value;
            object->unk_20 = effect;
            particle_data->unk_4C = 0;
        }
        count -= 1;
    } while (count >= 0);
    object = source->unk_60 - 0x20;
    target_position = object->unk_08;
    height_delta = target_position->unk_08.parts.unk_0A.as_s16 - 0x18;
    height_delta = ground_height - height_delta;
    height_step = height_delta / 10;
    target_position->unk_08.parts.unk_0A.as_s16 = (s16) ((u16) target_position->unk_08.parts.unk_0A.as_s16 + height_step);
    sprite = object->unk_0C;
    if ((u16) sprite->unk_1C.as_u16 >= 0x21C1U) {
        sprite->unk_1C.as_u16 = 0x2000U;
    }
    scale_random = func_80069EF8();
    sprite->unk_1C.as_u16 = (u16) (sprite->unk_1C.as_u16 + ((scale_random & 0x1FF) + 0x100));
    if ((u16) sprite->unk_1E.as_u16 < 0x76CU) {
        sprite->unk_1E.as_u16 = 0x800U;
    }
    sprite->unk_1E.as_u16 = (u16) (sprite->unk_1E.as_u16 - ((func_80069EF8() & 0xFF) + 0x80));
    if ((s16) effect->unk_50 > 0) {
        return;
    }
    if (source->unk_60 != NULL) {
        goto state_3_continue;
    }

state_null:
    effect->unk_0A = 0xFF;
    func_800247B4();
    return;

state_3_continue:
    func_8009CE1C(source->unk_60, 8, effect->unk_09, 4, (s32) (s16) source->unk_2A, source, 2);
    effect->unk_50 = 6U;

state_F0_end:
    effect->unk_0A = 0xF0;
    func_800247B4();
    return;

state_F0:
    sprite = ((S_func_81832800_3 *) ((u8 *) source->unk_60 - 0x20))->unk_0C;
    scale_x = sprite->unk_1C.as_u16;
    scale_y = sprite->unk_1E.as_u16;
    sprite->unk_1C.as_u16 = (u16) (scale_x + ((s32) (0x1000 - scale_x) >> 2));
    sprite->unk_1E.as_u16 = (u16) (scale_y + ((s32) (0x1000 - scale_y) >> 2));
    if ((s16) effect->unk_50 <= 0) {
        sprite->unk_1E.as_u16 = 0x1000U;
        sprite->unk_1C.as_u16 = 0x1000U;
        effect->unk_0A = 0xFFU;
        ((S_func_81832800_2 *) source->unk_60)->unk_14.as_u32 &= ~0x100000U;
        func_800247B4();
        return;
    }
    return;

state_FF:
    if (effect->unk_52.as_s16 & 0x8000) {
        effect->unk_52.as_u16 &= 0x7FFF;
        func_800247B4();
        return;
    }
    ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    *D_8008346C = 0;
    ((S_func_81832800_9 *) ((u8 *) effect - 2))->unk_00 = (u16) (((S_func_81832800_9 *) ((u8 *) effect - 2))->unk_00 | 0x8000);
    D_800814A0[0] |= 0x8000;
}

