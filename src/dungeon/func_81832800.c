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
    void *source_object;
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
    void *target;
    void *jitter_position_x;
    void *jitter_position_y;
    void *burst_position;
    void *burst_position_y;
    void *target_position;
    void *source_sprite;
    void *sprite;
    void *particle_data;
    void *source;
    void *object;
    void *particle_position;
    void *found_target;
    void *height_position;
    register u32 sprite_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 init_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *particle_callback;
    void *particle_texture;
    register void *effect ASM_REG("$22") = effect_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *position ASM_REG("$23") = position_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    sprite_flags = (u32) D_8006CCD8;
    source = M2C_FIELD(effect, void **, 0);
    init_value = M2C_FIELD(source, u16 *, 0x2A);
    ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    source_sprite = M2C_FIELD(source, void **, -0x14);
    count = (u16) init_value >> 8;
    spawn_value = count & 0xE;
    step_x = (s32) M2C_FIELD((void *) sprite_flags, s16 *, spawn_value);
    step_y = (s32) M2C_FIELD(D_8006CCE8, s16 *, spawn_value);
    spawn_state = M2C_FIELD(effect, u16 *, 0xA);
    M2C_FIELD(effect, u16 *, 0x50) = (u16) (M2C_FIELD(effect, u16 *, 0x50) - 1);
    source_object = source - 0x20;
    if ((u32) (spawn_state - 1) < 3U) {
        count = 3;
        if ((s16) spawn_state < 3) {
            count = 5;
        }
        particle_callback = &D_80024860;
        particle_texture = D_800DEA68;
        if (count >= 0) {
first_spawn_loop:
            object = func_8003FD64(0x312, D_80083498);
            if (object != NULL) {
                void *callback;
                void *spawn_position;
                func_8004491C(object, D_80045340);
                sprite = M2C_FIELD(object, void **, 0xC);
                spawn_position = M2C_FIELD(object, void **, 8);
                callback = particle_callback;
                M2C_FIELD(object, void **, 0x10) = callback;
                M2C_FIELD(spawn_position, s32 *, 0) = (s32) M2C_FIELD(position, s32 *, 0);
                particle_data = object + 0x20;
                jitter_count = 1;
                M2C_FIELD(M2C_FIELD(object, void **, 8), s32 *, 4) = (s32) M2C_FIELD(position, s32 *, 4);
                do {
                    spawn_value = func_80069EF8();
                    jitter_position_x = M2C_FIELD(object, void **, 8);
                    init_value = M2C_FIELD(jitter_position_x, u16 *, 2);
                    jitter_x = spawn_value;
                    jitter_base = init_value - 0x10;
                    if (spawn_value < 0) {
                        jitter_x = spawn_value + 0x1F;
                    }
                    init_value = spawn_value - ((jitter_x >> 5) << 5);
                    init_value = jitter_base + init_value;
                    M2C_FIELD(jitter_position_x, u16 *, 2) = (u16) init_value;
                    spawn_value = func_80069EF8(spawn_value, jitter_position_x, jitter_base);
                    jitter_position_y = M2C_FIELD(object, void **, 8);
                    init_value = M2C_FIELD(jitter_position_y, u16 *, 6);
                    jitter_y = spawn_value;
                    jitter_base = init_value - 0x10;
                    if (spawn_value < 0) {
                        jitter_y = spawn_value + 0x1F;
                    }
                    init_value = spawn_value - ((jitter_y >> 5) << 5);
                    init_value = jitter_base + init_value;
                    jitter_count -= 1;
                    M2C_FIELD(jitter_position_y, u16 *, 6) = (u16) init_value;
                } while (jitter_count >= 0);
                particle_position = M2C_FIELD(object, void **, 8);
                M2C_FIELD(M2C_FIELD(object, void **, 8), s16 *, 0xA) = func_800BCB04(M2C_FIELD(particle_position, u16 *, 2), M2C_FIELD(particle_position, u16 *, 6), (s16) (M2C_FIELD(position, u16 *, 0xA) - 0x30));
                height_position = M2C_FIELD(object, void **, 8);
                if (M2C_FIELD(height_position, s16 *, 0xA) >= 0x200) {
                    M2C_FIELD(height_position, s16 *, 0xA) = (s16) M2C_FIELD(position, u16 *, 0xA);
                }
                M2C_FIELD(position, u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(object, void **, 8), s16 *, 0xA);
                color = 0xC0C0C0;
                {
                    s32 scale = 0x1400;
                    sprite_flags = M2C_FIELD(sprite, u16 *, 0x14);
                    M2C_FIELD(sprite, s16 *, 0x1E) = (s16) scale;
                    M2C_FIELD(sprite, s16 *, 0x1C) = (s16) scale;
                    M2C_FIELD(sprite, s16 *, 0x10) = 0;
                    M2C_FIELD(sprite, s32 *, 0xC) = color;
                    M2C_FIELD(sprite, void **, 0) = particle_texture;
                    sprite_flags |= 0xC;
                    M2C_FIELD(sprite, u16 *, 0x14) = sprite_flags;
                    init_value = M2C_FIELD(particle_texture, s32 *, 4);
                }
                M2C_FIELD(sprite, s8 *, 4) = 0;
                M2C_FIELD(sprite, s8 *, 5) = 0;
                M2C_FIELD(sprite, s32 *, 8) = init_value;
                M2C_FIELD(particle_data, void **, 0) = effect;
                M2C_FIELD(particle_data, s16 *, 0x4C) = 0;
            }
            count -= 1;
            if (count >= 0) {
                goto first_spawn_loop;
            }
        }
    }
    state = (s16) M2C_FIELD(effect, u16 *, 0xA);
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
    if (*M2C_FIELD(effect, u16 **, 4) & 0x80) {
        found_target = func_800A05A4(source, M2C_FIELD(source_sprite, u8 *, 0x24), M2C_FIELD(source_sprite, u8 *, 0x25), (s16) M2C_FIELD(source, u16 *, 0x2A), (s32) func_800A3820(6));
        M2C_FIELD(source, void **, 0x60) = found_target;
        if (found_target == NULL) {
            M2C_FIELD(source, u8 *, 0x72) = (u8) M2C_FIELD(source_sprite, u8 *, 0x24);
            M2C_FIELD(source, u8 *, 0x73) = (u8) M2C_FIELD(source_sprite, u8 *, 0x25);
            func_80024354();
            return;
        }
        sprite = M2C_FIELD(found_target, void **, -0x14);
        if (!(M2C_FIELD(sprite, u16 *, 0x14) & 0x8000) || !(M2C_FIELD(effect_sprite, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(source, u8 *, 0x72) = (u8) M2C_FIELD(sprite, u8 *, 0x24);
            M2C_FIELD(source, u8 *, 0x73) = (u8) M2C_FIELD(sprite, u8 *, 0x25);
            M2C_FIELD(position, s32 *, 0) = (s32) M2C_FIELD(M2C_FIELD(source_object, void **, 8), s32 *, 0);
            M2C_FIELD(position, s32 *, 4) = (s32) M2C_FIELD(M2C_FIELD(source_object, void **, 8), s32 *, 4);
            M2C_FIELD(position, s32 *, 8) = (s32) M2C_FIELD(M2C_FIELD(source_object, void **, 8), s32 *, 8);
            delta_x = (s8) M2C_FIELD(source, u8 *, 0x72);
            state_value = M2C_FIELD(source_sprite, u8 *, 0x24);
            source_y = M2C_FIELD(source_sprite, u8 *, 0x25);
            delta_x -= state_value;
            state_value = (s8) M2C_FIELD(source, u8 *, 0x73);
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
            M2C_FIELD(effect, u16 *, 0x50) = init_value;
            M2C_FIELD(position, s32 *, 0xC) = (s32) (step_x << 0x14);
            M2C_FIELD(position, s32 *, 0x10) = (s32) (step_y << 0x14);
            func_800A56E0(0x300);
            init_value = M2C_FIELD(effect, u16 *, 0xA);
            init_value += 1;
            ASM_TAILSLOT_PIN(init_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_80024490();
            return;
        }
        goto state_F0_end;
    }
    return;

state_1:
    if ((s16) M2C_FIELD(effect, u16 *, 0x50) >= 0) {
        M2C_FIELD(position, s32 *, 0) += M2C_FIELD(position, s32 *, 0xC);
        M2C_FIELD(position, s32 *, 4) += M2C_FIELD(position, s32 *, 0x10);
        func_800247B4();
        return;
    }
    state_value = M2C_FIELD(effect, u16 *, 0xA);
    ASM_KEEP(state_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    delta_x = 6;
    ASM_TAILSLOT_PIN(delta_x);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024488();
    return;

state_2:
    if ((s16) M2C_FIELD(effect, u16 *, 0x50) <= 0) {
        sprite_flags = 0x100000;
        target = M2C_FIELD(source, void **, 0x60);
        if (target == NULL) {
            goto state_null;
        }
        M2C_FIELD(target, s32 *, 0x14) = (s32) (M2C_FIELD(target, s32 *, 0x14) | sprite_flags);
        M2C_FIELD(effect, u16 *, 0x50) = 0x14U;
        M2C_FIELD(effect, u16 *, 0xA) += 1;
        func_800247B4();
        return;
    }
    return;

state_3:
    ground_height = (s16) func_800BCB04(M2C_FIELD(position, u16 *, 2), M2C_FIELD(position, u16 *, 6), (s16) (M2C_FIELD(position, u16 *, 0xA) - 0x30));
    do {
        object = func_8003FD64(0x312, D_80083498);
        if (object != NULL) {
            void *callback;
            func_8004491C(object, D_80045340);
            particle_data = object + 0x20;
            sprite = M2C_FIELD(object, void **, 0xC);
            callback = &D_800248F0;
            M2C_FIELD(object, void **, 0x10) = callback;
            rounded_x = func_80069EF8();
            random_x = rounded_x;
            burst_position = M2C_FIELD(object, void **, 8);
            origin_x = M2C_FIELD(position, u16 *, 2);
            M2C_FIELD(particle_data, u16 *, 0xC) = origin_x;
            if (random_x < 0) {
                rounded_x = random_x + 0x7F;
            }
            M2C_FIELD(burst_position, s16 *, 2) = (s16) ((origin_x + (random_x - ((rounded_x >> 7) << 7))) - 0x40);
            rounded_y = func_80069EF8((s32) origin_x, burst_position);
            random_y = rounded_y;
            burst_position_y = M2C_FIELD(object, void **, 8);
            origin_y = M2C_FIELD(position, u16 *, 6);
            M2C_FIELD(particle_data, u16 *, 0xE) = origin_y;
            if (random_y < 0) {
                rounded_y = random_y + 0x7F;
            }
            M2C_FIELD(burst_position_y, s16 *, 6) = (s16) ((origin_y + (random_y - ((rounded_y >> 7) << 7))) - 0x40);
            rounded_height = func_80069EF8((s32) origin_y, burst_position_y);
            random_height = rounded_height;
            burst_position = M2C_FIELD(object, void **, 8);
            M2C_FIELD(particle_data, s16 *, 0x10) = ground_height;
            if (random_height < 0) {
                rounded_height = random_height + 0x3F;
            }
            M2C_FIELD(burst_position, s16 *, 0xA) = (s16) ((ground_height + (random_height - ((rounded_height >> 6) << 6))) - 0x80);
            color = 0x101010;
            sprite_flags = M2C_FIELD(sprite, u16 *, 0x14);
            M2C_FIELD(sprite, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(sprite, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(sprite, s16 *, 0x10) = 0x20;
            M2C_FIELD(sprite, s32 *, 0xC) = color;
            M2C_FIELD(sprite, u8 **, 0) = D_800DED70;
            sprite_flags |= 0xC;
            M2C_FIELD(sprite, u16 *, 0x14) = sprite_flags;
            init_value = (s32) M2C_FIELD(D_800DED70, s32 *, 4);
            M2C_FIELD(sprite, s8 *, 4) = 0;
            M2C_FIELD(sprite, s8 *, 5) = 0;
            M2C_FIELD(sprite, s32 *, 8) = init_value;
            M2C_FIELD(object, void **, 0x20) = effect;
            M2C_FIELD(particle_data, s16 *, 0x4C) = 0;
        }
        count -= 1;
    } while (count >= 0);
    object = M2C_FIELD(source, void **, 0x60) - 0x20;
    target_position = M2C_FIELD(object, void **, 8);
    height_delta = M2C_FIELD(target_position, s16 *, 0xA) - 0x18;
    height_delta = ground_height - height_delta;
    height_step = height_delta / 10;
    M2C_FIELD(target_position, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(target_position, s16 *, 0xA) + height_step);
    sprite = M2C_FIELD(object, void **, 0xC);
    if ((u16) M2C_FIELD(sprite, u16 *, 0x1C) >= 0x21C1U) {
        M2C_FIELD(sprite, u16 *, 0x1C) = 0x2000U;
    }
    scale_random = func_80069EF8();
    M2C_FIELD(sprite, u16 *, 0x1C) = (u16) (M2C_FIELD(sprite, u16 *, 0x1C) + ((scale_random & 0x1FF) + 0x100));
    if ((u16) M2C_FIELD(sprite, u16 *, 0x1E) < 0x76CU) {
        M2C_FIELD(sprite, u16 *, 0x1E) = 0x800U;
    }
    M2C_FIELD(sprite, u16 *, 0x1E) = (u16) (M2C_FIELD(sprite, u16 *, 0x1E) - ((func_80069EF8() & 0xFF) + 0x80));
    if ((s16) M2C_FIELD(effect, u16 *, 0x50) > 0) {
        return;
    }
    if (M2C_FIELD(source, void **, 0x60) != NULL) {
        goto state_3_continue;
    }

state_null:
    M2C_FIELD(effect, u16 *, 0xA) = 0xFF;
    func_800247B4();
    return;

state_3_continue:
    func_8009CE1C(M2C_FIELD(source, void **, 0x60), 8, M2C_FIELD(effect, u8 *, 9), 4, (s32) (s16) M2C_FIELD(source, u16 *, 0x2A), source, 2);
    M2C_FIELD(effect, u16 *, 0x50) = 6U;

state_F0_end:
    M2C_FIELD(effect, u16 *, 0xA) = 0xF0;
    func_800247B4();
    return;

state_F0:
    sprite = M2C_FIELD(M2C_FIELD(source, void **, 0x60), void **, -0x14);
    scale_x = M2C_FIELD(sprite, u16 *, 0x1C);
    scale_y = M2C_FIELD(sprite, u16 *, 0x1E);
    M2C_FIELD(sprite, u16 *, 0x1C) = (u16) (scale_x + ((s32) (0x1000 - scale_x) >> 2));
    M2C_FIELD(sprite, u16 *, 0x1E) = (u16) (scale_y + ((s32) (0x1000 - scale_y) >> 2));
    if ((s16) M2C_FIELD(effect, u16 *, 0x50) <= 0) {
        M2C_FIELD(sprite, u16 *, 0x1E) = 0x1000U;
        M2C_FIELD(sprite, u16 *, 0x1C) = 0x1000U;
        M2C_FIELD(effect, u16 *, 0xA) = 0xFFU;
        M2C_FIELD(M2C_FIELD(source, void **, 0x60), u32 *, 0x14) &= ~0x100000U;
        func_800247B4();
        return;
    }
    return;

state_FF:
    if (M2C_FIELD(effect, s16 *, 0x52) & 0x8000) {
        M2C_FIELD(effect, u16 *, 0x52) &= 0x7FFF;
        func_800247B4();
        return;
    }
    ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    *D_8008346C = 0;
    M2C_FIELD(effect, u16 *, -2) = (u16) (M2C_FIELD(effect, u16 *, -2) | 0x8000);
    D_800814A0[0] |= 0x8000;
}

