#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_8016A8B4[];
typedef struct {
    s16 x;
    u16 y;
} InitPair;
typedef struct {
    InitPair pair[8];
} __attribute__((packed)) InitBlock;
void func_800419EC();            /* extern */
void func_80047738();              /* extern */
void func_80047784();         /* extern */
void func_800478B8();  /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80069EF8();                                /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_80170C3C();                            /* extern */
M2C_UNK func_80171A10(); /* extern */
M2C_UNK func_80172A14();      /* extern */
M2C_UNK func_80172B00();      /* extern */
M2C_UNK func_80172CC8(); /* extern */
M2C_UNK func_80172F44(); /* extern */
void func_80173240() __attribute__((noreturn));      /* extern */
void func_801735B0() __attribute__((noreturn));      /* extern */
void func_8017378C() __attribute__((noreturn));      /* extern */
void func_80173C7C() __attribute__((noreturn));      /* extern */
void func_80173CE8() __attribute__((noreturn));      /* extern */
void func_80173CF8() __attribute__((noreturn));      /* extern */
void func_80173D34() __attribute__((noreturn));      /* extern */
void func_80173D38() __attribute__((noreturn));      /* extern */
void func_80173DC4() __attribute__((noreturn));      /* extern */
extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern InitBlock D_8016A894;
extern u8 D_80174C64[];
extern u8 D_80174C6C[];
extern u8 D_80174C7C[];
extern u8 D_80174C84[];
extern u8 D_80174C8C[];
extern u8 D_80174C94[];
extern s32 D_80174CE0;

/* Updates Beldo's scripted movement, idle animation, and particle effects. */
void func_801730AC(void *actor_input, void *motion_input, void *sprite_input) {
    void *actor = actor_input;
    void *motion = motion_input;
    void *sprite = sprite_input;
    InitBlock direction_vectors;
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20 };
    s32 path_angle;
    s16 sprite_direction;
    s16 next_angle;
    s16 spin_timer;
    s16 sprite_angle_base;
    s16 sprite_angle_delta;
    s32 *start_vector;
    s32 *path_vector;
    s32 start_direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 position_x;
    s32 position_y;
    s32 path_direction;
    s32 path_particle_count;
    s32 end_particle_count;
    s32 wait_particle_count;
    s32 move_particle_count;
    s32 wait_particle_mode;
    s32 move_particle_mode;
    u16 initial_timer;
    u16 idle_timer;
    u16 final_timer;
    u16 pause_timer;
    u16 rise_timer;
    u16 path_start_timer;
    u16 path_end_timer;
    u16 turn_timer;
    u16 animation_timer;
    u16 particle_timer;
    u16 move_timer;
    u16 bob_phase;
    u16 previous_angle;
    u8 state;
    u8 *current_animation;
    u8 *path_step;
    u8 *path_start;
    u8 *path_table;
    void *beldo;
    s32 tail_test;
    register s32 tail_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *tail_sprite ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *particle_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 particle_color;
    s32 particle_variation;
    s32 particle_random;

    direction_vectors = D_8016A894;
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    beldo = D_80174CE0 + 0x20;
    func_800478B8(sprite);
    state = M2C_FIELD(actor, u8 *, 0x9A);
    if (state >= 0x15U) {
        goto block_97;
    }
    (void)jt_keep; goto *D_8016A8B4[(u32)(state)];
jt_c0:
    initial_timer = M2C_FIELD(actor, u16 *, 0x96);
    M2C_FIELD(actor, u16 *, 0x96) = (u16) (initial_timer + 1);
    if ((s16) initial_timer < 0x1E) {
        goto block_97;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(motion, s32 *, 0xC) = 0xFFF80000;
    func_80173D34();
    return;
jt_c1:
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    tail_test = M2C_FIELD(actor, u16 *, 0x96) + 1;
    M2C_FIELD(actor, u16 *, 0x96) = (u16) tail_test;
    tail_test = (s16) tail_test < 0x28;
    ASM_TAILSLOT_PIN(tail_test);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80173240();
    return;
jt_c3:
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) & 0xFF7F);
    pause_timer = M2C_FIELD(actor, u16 *, 0x96) + 1;
    M2C_FIELD(actor, u16 *, 0x96) = pause_timer;
    if ((s16) pause_timer < 0xA) {
        goto block_98;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(motion, s32 *, 0xC) = 0;
    func_80173D34();
    return;
jt_c5:
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C8C;
    func_80047784(sprite, D_80174C8C[((s32) (D_80083228 + M2C_FIELD(beldo, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x801);
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    func_80173D34();
    return;
jt_c6:
    if (!(M2C_FIELD(sprite, u16 *, 0x14) & 0x6000)) {
        goto block_98;
    }
    M2C_FIELD(actor, s8 *, 0xB6) = 0;
    M2C_FIELD(beldo, u16 *, 0x88) = (u16) M2C_FIELD(motion, u16 *, 0xA);
    if (M2C_FIELD(sprite, u8 **, 0x2C) == D_80174C64) {
        goto block_97;
    }
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C64;
    func_80047784(sprite, D_80174C64[((s32) (D_80083228 + M2C_FIELD(beldo, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    {
        void *case6_a0 = actor;   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        void *saved_motion = motion;
        void *saved_sprite;
        u8 previous_state;

        ASM_SET(actor);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        previous_state = M2C_FIELD(actor, u8 *, 0x9A);
        saved_sprite = sprite;
        M2C_FIELD(actor, u16 *, 0x96) = 0U;
        M2C_FIELD(actor, u8 *, 0x9A) = (u8) (previous_state + 1);
        func_80172B00(case6_a0, saved_motion, saved_sprite);
    }
    tail_test = 0x80170000;
    ASM_PAGEBASE_PIN(tail_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80173D38();
    return;
jt_c7:
    M2C_FIELD(motion, u16 *, 0xA) = (u16) (M2C_FIELD(motion, u16 *, 0xA) - 8);
    rise_timer = M2C_FIELD(actor, u16 *, 0x96) + 1;
    M2C_FIELD(actor, u16 *, 0x96) = rise_timer;
    if ((s16) rise_timer < 4) {
        goto block_98;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(motion, s32 *, 0xC) = 0;
    M2C_FIELD(actor, u16 *, 0x9E) = 0U;
    M2C_FIELD(actor, u16 *, 0xA2) = 0U;
    M2C_FIELD(actor, s16 *, 0x92) = -0x20;
    func_80173D34();
    return;
jt_c9:
    path_start_timer = M2C_FIELD(actor, u16 *, 0x96);
    M2C_FIELD(actor, u16 *, 0x96) = (u16) (path_start_timer + 1);
    if ((s16) path_start_timer < 7) {
        goto block_97;
    }
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C6C;
    func_80047784(sprite, D_80174C6C[((s32) (D_80083228 + M2C_FIELD(beldo, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(motion, s32 *, 0xC) = 0xFFF80000;
    M2C_FIELD(actor, s16 *, 0xB4) = 5;
    M2C_FIELD(actor, u16 *, 0x96) = 0x10U;
    path_start = D_80174C94;
    path_step = path_start + M2C_FIELD(actor, s16 *, 0xB4) * 2;
    start_direction = path_step[1] & 7;
    start_vector = (s32 *) &direction_vectors.pair[start_direction];
    M2C_FIELD(motion, s16 *, 0xE) = (s16) (M2C_FIELD(start_vector, s16 *, 0) * 0x10);
    M2C_FIELD(motion, s16 *, 0x12) = (s16) (M2C_FIELD(start_vector, u16 *, 2) * 0x10);
    M2C_FIELD(beldo, s16 *, 0x2A) = (s16) (start_direction << 9);
    func_80173D34();
    return;
jt_c10:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) > 0) {
        goto block_29;
    }
    path_table = D_80174C94;
    M2C_FIELD(actor, u16 *, 0x96) = (u16) ((path_table[M2C_FIELD(actor, s16 *, 0xB4) * 2] * 4) + 1);
    path_direction = path_table[M2C_FIELD(actor, s16 *, 0xB4) * 2 + 1] & 7;
    path_vector = (s32 *) &direction_vectors.pair[path_direction];
    M2C_FIELD(motion, s16 *, 0xE) = (s16) (M2C_FIELD(path_vector, s16 *, 0) * 0x10);
    M2C_FIELD(motion, s16 *, 0x12) = (s16) (M2C_FIELD(path_vector, u16 *, 2) * 0x10);
    path_angle = path_direction << 9;
    if (path_angle != M2C_FIELD(beldo, s16 *, 0x2A)) {
        goto block_25;
    }
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    M2C_FIELD(actor, u16 *, 0x96) = (u16) (M2C_FIELD(actor, u16 *, 0x96) - 1);
block_25:
    M2C_FIELD(beldo, s16 *, 0x2A) = path_angle;
    if ((path_table[M2C_FIELD(actor, s16 *, 0xB4) * 2 + 1] & 0xF8) != 0xF8) {
        goto block_27;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0x13U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
block_27:
    M2C_FIELD(actor, u16 *, 0xB4) = (u16) (M2C_FIELD(actor, u16 *, 0xB4) + 1);
    func_801735B0();
    return;
block_29:
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    if (M2C_FIELD(sprite, s8 *, 4) != 5) {
        goto block_32;
    }
    particle_a0 = sprite;
    ASM_SET(sprite);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C6C;
    func_80047784(particle_a0, D_80174C6C[((s32) (D_80083228 + M2C_FIELD(beldo, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    path_particle_count = 0;
    func_800A56E0(0x706);
loop_31:
    path_particle_count += 1;
    particle_random = func_80069EF8();
    particle_a0 = actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_80171A10(particle_a0, M2C_FIELD(beldo, s16 *, 0x2A), particle_color, particle_variation, 0);
    if (path_particle_count < 0x14) {
        goto loop_31;
    }
block_32:
    M2C_FIELD(actor, u16 *, 0x96) = (u16) (M2C_FIELD(actor, u16 *, 0x96) - 1);
    func_80173D34();
    return;
jt_c11:
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    if (M2C_FIELD(sprite, s8 *, 4) != 5) {
        goto block_37;
    }
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C6C;
    func_80047784(sprite, D_80174C6C[((s32) (D_80083228 + M2C_FIELD(beldo, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    end_particle_count = 0;
    func_800A56E0(0x706);
loop_36:
    end_particle_count += 1;
    particle_random = func_80069EF8();
    particle_a0 = actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_80171A10(particle_a0, M2C_FIELD(beldo, s16 *, 0x2A), particle_color, particle_variation, 0);
    if (end_particle_count < 0x14) {
        goto loop_36;
    }
block_37:
    path_end_timer = M2C_FIELD(actor, u16 *, 0x96) - 1;
    M2C_FIELD(actor, u16 *, 0x96) = path_end_timer;
    if ((path_end_timer << 0x10) > 0) {
        goto block_98;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0x2EU;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
#ifndef NON_MATCHING
    tail_state = 0x80170000;
#endif
    current_animation = M2C_FIELD(sprite, u8 **, 0x2C);
#ifdef NON_MATCHING
    tail_sprite = D_80174C64;
#else
    ASM_KEEP(tail_state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    tail_sprite = (u8 *)tail_state + 0x4C64;
#endif
    if (current_animation == tail_sprite) {
        goto block_97;
    }
#ifndef NON_MATCHING
    tail_state = 0x80080000;
    ASM_KEEP(tail_state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#endif
    M2C_FIELD(sprite, u8 **, 0x2C) = tail_sprite;
    func_80173CF8();
    return;
jt_c12:
    turn_timer = M2C_FIELD(actor, u16 *, 0x96) - 1;
    M2C_FIELD(actor, u16 *, 0x96) = turn_timer;
    if ((turn_timer << 0x10) > 0) {
        goto block_46;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 6U;
    if (M2C_FIELD(beldo, s16 *, 0x2A) >= 0x800) {
        goto block_45;
    }
    M2C_FIELD(beldo, s16 *, 0x2A) = (s16) (M2C_FIELD(beldo, u16 *, 0x2A) + 0x200);
    func_8017378C();
    return;
block_45:
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
block_46:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) != 0x28) {
        goto block_48;
    }
    M2C_FIELD(beldo, s16 *, 0x2A) = 0xE00;
block_48:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) != 0x1E) {
        goto block_50;
    }
    M2C_FIELD(beldo, s16 *, 0x2A) = 0;
block_50:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) != 0x1D) {
        goto block_52;
    }
    M2C_FIELD(beldo, s16 *, 0x2A) = 0x200;
block_52:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) != 0x12) {
        goto block_54;
    }
    M2C_FIELD(beldo, s16 *, 0x2A) = 0;
block_54:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) != 0x11) {
        goto block_56;
    }
    M2C_FIELD(beldo, s16 *, 0x2A) = 0xE00;
block_56:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) != 0xA) {
        goto block_98;
    }
    M2C_FIELD(beldo, s16 *, 0x2A) = 0;
    func_80173D38();
    return;
jt_c8:
jt_c13:
    bob_phase = M2C_FIELD(actor, u16 *, 0x9E);
    M2C_FIELD(actor, u16 *, 0x9E) = (u16) (bob_phase + 1);
    M2C_FIELD(actor, s32 *, 0xA0) = (s32) (M2C_FIELD(actor, s32 *, 0xA0) + (func_800644B8((s16) bob_phase * 0x55) * 0x10));
    M2C_FIELD(motion, u16 *, 0xA) = (u16) (M2C_FIELD(beldo, u16 *, 0x88)
        + M2C_FIELD(actor, u16 *, 0x92) - M2C_FIELD(actor, u16 *, 0xA2));
    func_80173D34();
    return;
jt_c14:
    animation_timer = M2C_FIELD(actor, u16 *, 0x96) + 1;
    M2C_FIELD(actor, u16 *, 0x96) = animation_timer;
    if ((s16) animation_timer < 3) {
        goto block_98;
    }
    tail_sprite = (u8 *)0x80170000;
    ASM_KEEP(tail_sprite);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    tail_state = M2C_FIELD(actor, u8 *, 0x9A);
    ASM_KEEP(tail_state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    tail_sprite += 0x4C6C;
    ASM_KEEP(tail_sprite);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    func_80173CE8();
    return;
jt_c15:
    if (M2C_FIELD(sprite, s8 *, 4) != 5) {
        goto block_67;
    }
    particle_a0 = sprite;
    particle_color = 0;
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C6C;
    sprite_angle_base = D_80083228;
    sprite_angle_delta = M2C_FIELD(beldo, s16 *, 0x2A);
    wait_particle_count = particle_color;
    ASM_KEEP_NV(wait_particle_count);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    wait_particle_mode = 1;
    func_80047784(particle_a0, D_80174C6C[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7], particle_color);
    func_800A56E0(0x706);
loop_66:
    wait_particle_count += 1;
    particle_random = func_80069EF8();
    particle_a0 = actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_80171A10(particle_a0, M2C_FIELD(beldo, s16 *, 0x2A), particle_color, particle_variation, wait_particle_mode);
    if (wait_particle_count < 0x14) {
        goto loop_66;
    }
block_67:
    particle_timer = M2C_FIELD(actor, u16 *, 0x96) + 1;
    M2C_FIELD(actor, u16 *, 0x96) = particle_timer;
    if ((s16) particle_timer < 0x19) {
        goto block_98;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(motion, s16 *, 0xE) = -0x10;
    M2C_FIELD(motion, s16 *, 0x12) = 0;
    func_80173D34();
    return;
jt_c16:
    move_timer = M2C_FIELD(actor, u16 *, 0x96) + 1;
    M2C_FIELD(actor, u16 *, 0x96) = move_timer;
    if ((s16) move_timer < 0xA) {
        goto block_72;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(motion, s16 *, 0xE) = 4;
    M2C_FIELD(motion, s16 *, 0x12) = 0;
    func_80172CC8(motion, -0x50, 0, -0x10, 0);
    func_80172CC8(motion, -0x28, 0, -8, 0);
    func_80172CC8(motion, -0x1C, 0, -0x1E, 0);
    func_800419EC(6, 0xC);
    func_800A56E0(0x601);
block_72:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) != 8) {
        goto block_74;
    }
    func_80172CC8(motion, -0x30, 0, -0xA, 1);
    func_80172CC8(motion, -0x18, 0, -0x18, 1);
    func_80172CC8(motion, 0, 0, -0x10, 1);
    func_800419EC(6, 0xC);
    func_800A56E0(0x601);
block_74:
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    if (M2C_FIELD(sprite, s8 *, 4) != 5) {
        goto block_98;
    }
    particle_a0 = sprite;
    ASM_SET(sprite);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    particle_color = 0;
    ASM_KEEP_NV(particle_color);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C6C;
    sprite_angle_base = D_80083228;
    sprite_angle_delta = M2C_FIELD(beldo, s16 *, 0x2A);
    move_particle_count = particle_color;
    ASM_KEEP_NV(move_particle_count);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    move_particle_mode = 1;
    func_80047784(particle_a0, D_80174C6C[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7], particle_color);
    func_800A56E0(0x706);
loop_76:
    move_particle_count += 1;
    particle_random = func_80069EF8();
    particle_a0 = actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_80171A10(particle_a0, M2C_FIELD(beldo, s16 *, 0x2A), particle_color, particle_variation, move_particle_mode);
    if (move_particle_count < 0x14) {
        goto loop_76;
    }
    tail_test = 0x80170000;
    ASM_KEEP(tail_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80173D38();
    return;
jt_c17:
    spin_timer = M2C_FIELD(actor, u16 *, 0x96) + 1;
    M2C_FIELD(actor, u16 *, 0x96) = (u16) spin_timer;
    if (spin_timer >= 0xE) {
        goto block_83;
    }
    if (spin_timer & 1) {
        goto block_83;
    }
    previous_angle = (u16) M2C_FIELD(beldo, s16 *, 0x2A);
    next_angle = previous_angle + 0x200;
    M2C_FIELD(beldo, s16 *, 0x2A) = next_angle;
    if (next_angle < 0x1000) {
        goto block_83;
    }
    M2C_FIELD(beldo, s16 *, 0x2A) = (s16) (previous_angle - 0xE00);
block_83:
    position_x = M2C_FIELD(motion, s32 *, 0);
    velocity_x = M2C_FIELD(motion, s32 *, 0xC);
    position_y = M2C_FIELD(motion, s32 *, 4);
    velocity_y = M2C_FIELD(motion, s32 *, 0x10);
    M2C_FIELD(motion, s32 *, 0) = position_x + velocity_x;
    M2C_FIELD(motion, s32 *, 4) = position_y + velocity_y;
    if ((s16) M2C_FIELD(motion, u16 *, 0xA) >= (s16) M2C_FIELD(beldo, u16 *, 0x88)) {
        goto block_85;
    }
    M2C_FIELD(motion, u16 *, 0xA) = (u16) (M2C_FIELD(motion, u16 *, 0xA) + 6);
block_85:
    if ((s16) M2C_FIELD(actor, u16 *, 0x96) < 0x13) {
        goto block_90;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 0U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(motion, s16 *, 0x12) = 0;
    M2C_FIELD(motion, s16 *, 0xE) = 0;
    func_80173C7C(velocity_x, velocity_y);
    return;
jt_c18:
    idle_timer = M2C_FIELD(actor, u16 *, 0x96) + 1;
    M2C_FIELD(actor, u16 *, 0x96) = idle_timer;
    if ((s16) idle_timer < 0x3C) {
        goto block_90;
    }
    M2C_FIELD(actor, u16 *, 0x96) = 4U;
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    func_80172A14(actor, motion, sprite);
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C7C;
    func_80047784(sprite, D_80174C7C[((s32) (D_80083228 + M2C_FIELD(beldo, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x800);
block_90:
    if ((M2C_FIELD(actor, u16 *, 0x96) & 3) != 1) {
        goto block_98;
    }
    func_80172F44(motion, -0x10, 0, -4);
    func_80172F44(motion, 0xC, 0, -0xC);
    tail_test = 0x80170000;
    ASM_PAGEBASE_PIN(tail_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80173D38();
    return;
jt_c19:
    final_timer = M2C_FIELD(actor, u16 *, 0x96) - 1;
    M2C_FIELD(actor, u16 *, 0x96) = final_timer;
    if ((final_timer << 0x10) > 0) {
        goto block_98;
    }
    M2C_FIELD(actor, u8 *, 0x9A) = (u8) (M2C_FIELD(actor, u8 *, 0x9A) + 1);
    M2C_FIELD(sprite, u8 **, 0x2C) = D_80174C84;
    func_80047784(sprite, D_80174C84[((s32) (D_80083228 + M2C_FIELD(beldo, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    tail_test = 0x80170000;
    ASM_PAGEBASE_PIN(tail_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80173D38();
    return;
jt_c20:
    func_80170C3C();
jt_c2:
jt_c4:
block_97:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
block_98:
    if (D_80174CE0 == 0) {
        goto block_105;
    }
    sprite_direction = ((s32) (D_80083228 + M2C_FIELD(beldo, s16 *, 0x2A) + 0x100) >> 9) & 7;
    if (M2C_FIELD(actor, s16 *, 0x94) == sprite_direction) {
        goto block_101;
    }
    func_80047738(sprite, M2C_FIELD(sprite, u8 **, 0x2C)[sprite_direction], M2C_FIELD(sprite, s8 *, 4));
    M2C_FIELD(actor, s16 *, 0x94) = sprite_direction;
block_101:
    if (D_8006CCF8[sprite_direction] == 0) {
        goto block_104;
    }
    tail_test = M2C_FIELD(sprite, u16 *, 0x14) | 1;
    ASM_TAILSLOT_PIN(tail_test);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80173DC4();
    return;
block_104:
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) & 0xFFFE);
block_105:
    return;
}
