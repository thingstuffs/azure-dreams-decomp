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

typedef struct S_func_8132B8AC_0 {
    u8 pad_00[0x92];
    union { s16 s; u16 u; } unk_92;
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[2];
    u8 unk_9A;
    u8 pad_9B[3];
    u16 unk_9E;
    union {
        s32 unk_A0;
        struct { u8 pad_A0[2]; u16 unk_A2; } unk_A2;
    } unk_A0;
    u8 pad_A4[0x10];
    union { s16 s; u16 u; } unk_B4;
    s8 unk_B6;
} S_func_8132B8AC_0;

typedef struct S_func_8132B8AC_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[2];
    u16 unk_0A;
    union {
        s32 unk_0C;
        struct { u8 pad_0C[2]; s16 unk_0E; } unk_0E;
    } unk_0C;
    union {
        s32 unk_10;
        struct { u8 pad_10[2]; s16 unk_12; } unk_12;
    } unk_10;
} S_func_8132B8AC_1;

typedef struct S_func_8132B8AC_2 {
    u8 pad_00[4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 *unk_2C;
} S_func_8132B8AC_2;

typedef struct S_func_8132B8AC_3 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_func_8132B8AC_3;

typedef struct S_func_8132B8AC_4 {
    u8 pad_00[0x3228];
    s16 unk_3228;
} S_func_8132B8AC_4;

typedef struct S_func_8132B8AC_5 {
    u8 unk_00;
} S_func_8132B8AC_5;

/* Updates Beldo's scripted movement, idle animation, and particle effects. */
void func_801730AC(void *actor_input, void *motion_input, void *sprite_input) {
    register S_func_8132B8AC_0 *actor ASM_REG("$17") = actor_input; /* MATCH: shared-tail control flow must retain the retail actor register. */
    S_func_8132B8AC_1 *motion = motion_input;
    S_func_8132B8AC_2 *sprite = sprite_input;
    InitBlock direction_vectors;
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20 };
    s32 path_angle;
    s16 sprite_direction;
    s16 next_angle;
    s16 spin_timer;
    s16 sprite_angle_base;
    s16 sprite_angle_delta;
    InitPair *start_vector;
    InitPair *path_vector;
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
    S_func_8132B8AC_3 *beldo;
    s32 tail_test;
    register s32 tail_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *tail_sprite;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *particle_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 particle_color;
    s32 particle_variation;
    s32 particle_random;

    direction_vectors = D_8016A894;
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    beldo = (S_func_8132B8AC_3 *)(D_80174CE0 + 0x20);
    func_800478B8(sprite);
    state = actor->unk_9A;
    if (state >= 0x15U) {
        goto block_97;
    }
    (void)jt_keep; goto *D_8016A8B4[(u32)(state)];
jt_c0:
    initial_timer = actor->unk_96;
    actor->unk_96 = (u16) (initial_timer + 1);
    if ((s16) initial_timer < 0x1E) {
        goto block_97;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0C = 0xFFF80000;
    goto block_97;
jt_c1:
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    tail_test = actor->unk_96 + 1;
    actor->unk_96 = (u16) tail_test;
    tail_test = (s16) tail_test < 0x28;
    goto pause_complete;
jt_c3:
    sprite->unk_14 = (u16) (sprite->unk_14 & 0xFF7F);
    tail_test = actor->unk_96 + 1;
    pause_timer = (u16) tail_test;
    actor->unk_96 = pause_timer;
    tail_test = (s16) tail_test < 0xA;
pause_complete:
    if (tail_test) {
        goto block_98;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0C = 0;
    goto block_97;
jt_c5:
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C8C;
    func_80047784(sprite, D_80174C8C[((s32) (D_80083228 + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x801);
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    goto block_97;
jt_c6:
    if (!(sprite->unk_14 & 0x6000)) {
        goto block_98;
    }
    actor->unk_B6 = 0;
    beldo->unk_88 = (u16) motion->unk_0A;
    if (sprite->unk_2C == D_80174C64) {
        goto block_97;
    }
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C64;
    func_80047784(sprite, D_80174C64[((s32) (D_80083228 + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    {
        void *case6_a0 = actor;   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        void *saved_motion = motion;
        void *saved_sprite;
        u8 previous_state;

        ASM_SET(actor);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        previous_state = actor->unk_9A;
        saved_sprite = sprite;
        actor->unk_96 = 0U;
        actor->unk_9A = (u8) (previous_state + 1);
        func_80172B00(case6_a0, saved_motion, saved_sprite);
    }
    goto block_98;
jt_c7:
    motion->unk_0A = (u16) (motion->unk_0A - 8);
    rise_timer = actor->unk_96 + 1;
    actor->unk_96 = rise_timer;
    if ((s16) rise_timer < 4) {
        goto block_98;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0C = 0;
    actor->unk_9E = 0U;
    actor->unk_A0.unk_A2.unk_A2 = 0U;
    actor->unk_92.s = -0x20;
    goto block_97;
jt_c9:
    path_start_timer = actor->unk_96;
    actor->unk_96 = (u16) (path_start_timer + 1);
    if ((s16) path_start_timer < 7) {
        goto block_97;
    }
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    func_80047784(sprite, D_80174C6C[((s32) (D_80083228 + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    motion->unk_0C.unk_0C = 0xFFF80000;
    actor->unk_B4.s = 5;
    actor->unk_96 = 0x10U;
    path_start = D_80174C94;
    path_step = path_start + actor->unk_B4.s * 2;
    start_direction = path_step[1] & 7;
    start_vector = (InitPair *) &direction_vectors.pair[start_direction];
    motion->unk_0C.unk_0E.unk_0E = (s16) (start_vector->x * 0x10);
    motion->unk_10.unk_12.unk_12 = (s16) (start_vector->y * 0x10);
    beldo->unk_2A.s = (s16) (start_direction << 9);
    goto block_97;
jt_c10:
    if ((s16) actor->unk_96 > 0) {
        goto block_29;
    }
    path_table = D_80174C94;
    actor->unk_96 = (u16) ((path_table[actor->unk_B4.s * 2] * 4) + 1);
    path_direction = path_table[actor->unk_B4.s * 2 + 1] & 7;
    path_vector = (InitPair *) &direction_vectors.pair[path_direction];
    motion->unk_0C.unk_0E.unk_0E = (s16) (path_vector->x * 0x10);
    motion->unk_10.unk_12.unk_12 = (s16) (path_vector->y * 0x10);
    path_angle = path_direction << 9;
    if (path_angle != beldo->unk_2A.s) {
        goto block_25;
    }
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
    actor->unk_96 = (u16) (actor->unk_96 - 1);
block_25:
    beldo->unk_2A.s = path_angle;
    if ((path_table[actor->unk_B4.s * 2 + 1] & 0xF8) != 0xF8) {
        goto block_27;
    }
    actor->unk_96 = 0x13U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
block_27:
    actor->unk_B4.u = (u16) (actor->unk_B4.u + 1);
    goto path_particles;
block_29:
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
path_particles:
    if (sprite->unk_04 != 5) {
        goto block_32;
    }
    particle_a0 = sprite;
       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    func_80047784(particle_a0, D_80174C6C[((s32) (D_80083228 + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    path_particle_count = 0;
    func_800A56E0(0x706);
loop_31:
    path_particle_count += 1;
    particle_random = func_80069EF8();
    particle_a0 = (u8 *)actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_80171A10(particle_a0, beldo->unk_2A.s, particle_color, particle_variation, 0);
    if (path_particle_count < 0x14) {
        goto loop_31;
    }
block_32:
    actor->unk_96 = (u16) (actor->unk_96 - 1);
    goto block_97;
jt_c11:
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
    if (sprite->unk_04 != 5) {
        goto block_37;
    }
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    func_80047784(sprite, D_80174C6C[((s32) (D_80083228 + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    end_particle_count = 0;
    func_800A56E0(0x706);
loop_36:
    end_particle_count += 1;
    particle_random = func_80069EF8();
    particle_a0 = (u8 *)actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_80171A10(particle_a0, beldo->unk_2A.s, particle_color, particle_variation, 0);
    if (end_particle_count < 0x14) {
        goto loop_36;
    }
block_37:
    path_end_timer = actor->unk_96 - 1;
    actor->unk_96 = path_end_timer;
    if ((path_end_timer << 0x10) > 0) {
        goto block_98;
    }
    actor->unk_96 = 0x2EU;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
#ifndef NON_MATCHING
    tail_state = 0x80170000;
#endif
    current_animation = sprite->unk_2C;
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
       /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#endif
    sprite->unk_2C = tail_sprite;
    goto update_animation;
jt_c12:
    turn_timer = actor->unk_96 - 1;
    actor->unk_96 = turn_timer;
    if ((turn_timer << 0x10) > 0) {
        goto block_46;
    }
    actor->unk_96 = 6U;
    if (beldo->unk_2A.s >= 0x800) {
        goto block_45;
    }
    beldo->unk_2A.s = (s16) (beldo->unk_2A.u + 0x200);
    goto block_46;
block_45:
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
block_46:
    if ((s16) actor->unk_96 != 0x28) {
        goto block_48;
    }
    beldo->unk_2A.s = 0xE00;
block_48:
    if ((s16) actor->unk_96 != 0x1E) {
        goto block_50;
    }
    beldo->unk_2A.s = 0;
block_50:
    if ((s16) actor->unk_96 != 0x1D) {
        goto block_52;
    }
    beldo->unk_2A.s = 0x200;
block_52:
    if ((s16) actor->unk_96 != 0x12) {
        goto block_54;
    }
    beldo->unk_2A.s = 0;
block_54:
    if ((s16) actor->unk_96 != 0x11) {
        goto block_56;
    }
    beldo->unk_2A.s = 0xE00;
block_56:
    if ((s16) actor->unk_96 != 0xA) {
        goto block_98;
    }
    beldo->unk_2A.s = 0;
    goto block_98;
jt_c8:
jt_c13:
    bob_phase = actor->unk_9E;
    actor->unk_9E = (u16) (bob_phase + 1);
    actor->unk_A0.unk_A0 = (s32) (actor->unk_A0.unk_A0 + (func_800644B8((s16) bob_phase * 0x55) * 0x10));
    motion->unk_0A = (u16) (beldo->unk_88
        + actor->unk_92.u - actor->unk_A0.unk_A2.unk_A2);
    goto block_97;
jt_c14:
    animation_timer = actor->unk_96 + 1;
    actor->unk_96 = animation_timer;
    if ((s16) animation_timer < 3) {
        goto block_98;
    }
#ifdef NON_MATCHING
    tail_sprite = D_80174C6C;
    tail_state = actor->unk_9A;
#else
    tail_sprite = (u8 *)0x80170000;
    ASM_KEEP(tail_sprite);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    tail_state = actor->unk_9A;
       /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    tail_sprite += 0x4C6C;
       /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif
    actor->unk_96 = 0U;
    goto advance_animation;
jt_c15:
    if (sprite->unk_04 != 5) {
        goto block_67;
    }
    particle_a0 = sprite;
    particle_color = 0;
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    sprite_angle_base = D_80083228;
    sprite_angle_delta = beldo->unk_2A.s;
    wait_particle_count = particle_color;
    ASM_KEEP_NV(wait_particle_count);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    wait_particle_mode = 1;
    func_80047784(particle_a0, D_80174C6C[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7], particle_color);
    func_800A56E0(0x706);
loop_66:
    wait_particle_count += 1;
    particle_random = func_80069EF8();
    particle_a0 = (u8 *)actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_80171A10(particle_a0, beldo->unk_2A.s, particle_color, particle_variation, wait_particle_mode);
    if (wait_particle_count < 0x14) {
        goto loop_66;
    }
block_67:
    particle_timer = actor->unk_96 + 1;
    actor->unk_96 = particle_timer;
    if ((s16) particle_timer < 0x19) {
        goto block_98;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0E.unk_0E = -0x10;
    motion->unk_10.unk_12.unk_12 = 0;
    goto block_97;
jt_c16:
    move_timer = actor->unk_96 + 1;
    actor->unk_96 = move_timer;
    if ((s16) move_timer < 0xA) {
        goto block_72;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0E.unk_0E = 4;
    motion->unk_10.unk_12.unk_12 = 0;
    func_80172CC8(motion, -0x50, 0, -0x10, 0);
    func_80172CC8(motion, -0x28, 0, -8, 0);
    func_80172CC8(motion, -0x1C, 0, -0x1E, 0);
    func_800419EC(6, 0xC);
    func_800A56E0(0x601);
block_72:
    if ((s16) actor->unk_96 != 8) {
        goto block_74;
    }
    func_80172CC8(motion, -0x30, 0, -0xA, 1);
    func_80172CC8(motion, -0x18, 0, -0x18, 1);
    func_80172CC8(motion, 0, 0, -0x10, 1);
    func_800419EC(6, 0xC);
    func_800A56E0(0x601);
block_74:
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
    if (sprite->unk_04 != 5) {
        goto block_98;
    }
    particle_a0 = sprite;
    ASM_SET(sprite);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    particle_color = 0;
    ASM_KEEP_NV(particle_color);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    sprite_angle_base = D_80083228;
    sprite_angle_delta = beldo->unk_2A.s;
    move_particle_count = particle_color;
    ASM_KEEP_NV(move_particle_count);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    move_particle_mode = 1;
    func_80047784(particle_a0, D_80174C6C[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7], particle_color);
    func_800A56E0(0x706);
loop_76:
    move_particle_count += 1;
    particle_random = func_80069EF8();
    particle_a0 = (u8 *)actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    func_80171A10(particle_a0, beldo->unk_2A.s, particle_color, particle_variation, move_particle_mode);
    if (move_particle_count < 0x14) {
        goto loop_76;
    }
    goto block_98;
jt_c17:
    spin_timer = actor->unk_96 + 1;
    actor->unk_96 = (u16) spin_timer;
    if (spin_timer >= 0xE) {
        goto block_83;
    }
    if (spin_timer & 1) {
        goto block_83;
    }
    previous_angle = (u16) beldo->unk_2A.s;
    next_angle = previous_angle + 0x200;
    beldo->unk_2A.s = next_angle;
    if (next_angle < 0x1000) {
        goto block_83;
    }
    beldo->unk_2A.s = (s16) (previous_angle - 0xE00);
block_83:
    position_x = motion->unk_00;
    velocity_x = motion->unk_0C.unk_0C;
    position_y = motion->unk_04;
    velocity_y = motion->unk_10.unk_10;
    motion->unk_00 = position_x + velocity_x;
    motion->unk_04 = position_y + velocity_y;
    if ((s16) motion->unk_0A >= (s16) beldo->unk_88) {
        goto block_85;
    }
    motion->unk_0A = (u16) (motion->unk_0A + 6);
block_85:
    if ((s16) actor->unk_96 < 0x13) {
        goto block_90;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_10.unk_12.unk_12 = 0;
    motion->unk_0C.unk_0E.unk_0E = 0;
    goto block_90;
jt_c18:
    idle_timer = actor->unk_96 + 1;
    actor->unk_96 = idle_timer;
    if ((s16) idle_timer < 0x3C) {
        goto block_90;
    }
    actor->unk_96 = 4U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    func_80172A14(actor, motion, sprite);
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C7C;
    func_80047784(sprite, D_80174C7C[((s32) (D_80083228 + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x800);
block_90:
    if ((actor->unk_96 & 3) != 1) {
        goto block_98;
    }
    func_80172F44(motion, -0x10, 0, -4);
    func_80172F44(motion, 0xC, 0, -0xC);
    goto block_98;
jt_c19:
    final_timer = actor->unk_96 - 1;
    actor->unk_96 = final_timer;
    if ((final_timer << 0x10) > 0) {
        goto block_98;
    }
#ifdef NON_MATCHING
    tail_sprite = D_80174C84;
    tail_state = actor->unk_9A;
#else
    tail_sprite = (u8 *)0x80170000;
    ASM_KEEP(tail_sprite); /* MATCH: split the animation address around the state load. */
    tail_state = actor->unk_9A;
    tail_sprite += 0x4C84;
#endif
advance_animation:
    tail_state += 1;
    actor->unk_9A = (u8) tail_state;
    tail_state = 0x80080000;
    sprite->unk_2C = tail_sprite;
update_animation:
#ifdef NON_MATCHING
    func_80047784(sprite, tail_sprite[((s32) (D_80083228 + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
#else
    tail_state = (((s32) (((S_func_8132B8AC_4 *)tail_state)->unk_3228 + beldo->unk_2A.s + 0x100) >> 9) & 7) + (s32) tail_sprite;
    func_80047784(sprite, ((S_func_8132B8AC_5 *)tail_state)->unk_00, 0);
#endif
    goto block_98;
jt_c20:
    func_80170C3C();
jt_c2:
jt_c4:
block_97:
       /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
block_98:
    if (D_80174CE0 == 0) {
        goto block_105;
    }
    sprite_direction = ((s32) (D_80083228 + beldo->unk_2A.s + 0x100) >> 9) & 7;
    if (actor->unk_94 == sprite_direction) {
        goto block_101;
    }
    func_80047738(sprite, sprite->unk_2C[sprite_direction], sprite->unk_04);
    actor->unk_94 = sprite_direction;
block_101:
    if (D_8006CCF8[sprite_direction] != 0) {
        tail_test = sprite->unk_14 | 1;
    } else {
block_104:
        tail_test = sprite->unk_14 & 0xFFFE;
    }
    sprite->unk_14 = (u16) tail_test;
block_105:
    return;
}
