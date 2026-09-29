#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
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
void func_801730AC(S_func_8132B8AC_0 *actor, S_func_8132B8AC_1 *motion, void *sprite_input) {

    S_func_8132B8AC_2 *sprite = sprite_input;
    InitBlock direction_vectors;
    s32 path_angle;
    s32 final_direction;
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
    u8 *path_step;
    u8 *path_start;
    u8 *path_table;
    S_func_8132B8AC_3 *beldo;
    s32 tail_test;
    u32 tail_state;
    u8 *tail_sprite;
    void *particle_a0;
    s32 particle_color;
    s32 particle_variation;
    s32 particle_random;

    direction_vectors = D_8016A894;
    beldo = (S_func_8132B8AC_3 *)(D_80174CE0 + 0x20);
    func_800478B8(sprite);
    state = actor->unk_9A;
    switch (state) {
    case 0:
    initial_timer = actor->unk_96;
    actor->unk_96 = (u16) (initial_timer + 1);
    if ((s16) initial_timer < 0x1E) {
        break;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0C = 0xFFF80000;
    break;
    case 1:
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    tail_test = actor->unk_96 + 1;
    actor->unk_96 = (u16) tail_test;
    tail_test = (s16) tail_test < 0x28;
    if (!tail_test) {
        actor->unk_96 = 0U;
        actor->unk_9A = (u8) (actor->unk_9A + 1);
        motion->unk_0C.unk_0C = 0;
    }
    break;
    case 3:
    sprite->unk_14 = (u16) (sprite->unk_14 & 0xFF7F);
    tail_test = actor->unk_96 + 1;
    pause_timer = (u16) tail_test;
    actor->unk_96 = pause_timer;
    tail_test = (s16) tail_test < 0xA;
    if (!tail_test) {
        actor->unk_96 = 0U;
        actor->unk_9A = (u8) (actor->unk_9A + 1);
        motion->unk_0C.unk_0C = 0;
    }
    break;
    case 5:
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C8C;
    func_80047784(sprite, D_80174C8C[((s32) (gameWork.view.viewAngle + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x801);
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    break;
    case 6:
    if (!(sprite->unk_14 & 0x6000)) {
        break;
    }
    actor->unk_B6 = 0;
    beldo->unk_88 = (u16) motion->unk_0A;
    if (sprite->unk_2C == D_80174C64) {
        break;
    }
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C64;
    func_80047784(sprite, D_80174C64[((s32) (gameWork.view.viewAngle + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    {
        void *case6_a0 = actor;
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
    break;
    case 7:
    motion->unk_0A = (u16) (motion->unk_0A - 8);
    rise_timer = actor->unk_96 + 1;
    actor->unk_96 = rise_timer;
    if ((s16) rise_timer < 4) {
        break;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0C = 0;
    actor->unk_9E = 0U;
    actor->unk_A0.unk_A2.unk_A2 = 0U;
    actor->unk_92.s = -0x20;
    break;
    case 9:
    path_start_timer = actor->unk_96;
    actor->unk_96 = (u16) (path_start_timer + 1);
    if ((s16) path_start_timer < 7) {
        break;
    }
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    func_80047784(sprite, D_80174C6C[((s32) (gameWork.view.viewAngle + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
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
    break;
    case 10:
    if ((s16) actor->unk_96 <= 0) {
    path_table = D_80174C94;
    actor->unk_96 = (u16) ((path_table[actor->unk_B4.s * 2] * 4) + 1);
    path_direction = path_table[actor->unk_B4.s * 2 + 1] & 7;
    path_vector = (InitPair *) &direction_vectors.pair[path_direction];
    motion->unk_0C.unk_0E.unk_0E = (s16) (path_vector->x * 0x10);
    motion->unk_10.unk_12.unk_12 = (s16) (path_vector->y * 0x10);
    path_angle = path_direction << 9;
    if (path_angle == beldo->unk_2A.s) {
        motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
        motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
        actor->unk_96 = (u16) (actor->unk_96 - 1);
    }
    beldo->unk_2A.s = path_angle;
    if ((path_table[actor->unk_B4.s * 2 + 1] & 0xF8) == 0xF8) {
        actor->unk_96 = 0x13U;
        actor->unk_9A = (u8) (actor->unk_9A + 1);
        motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
        motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
    }
    actor->unk_B4.u = (u16) (actor->unk_B4.u + 1);
    } else {
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
    }
    if (sprite->unk_04 == 5) {
    particle_a0 = sprite;
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    func_80047784(particle_a0, D_80174C6C[((s32) (gameWork.view.viewAngle + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    path_particle_count = 0;
    func_800A56E0(0x706);
loop_31:
    particle_random = func_80069EF8();
    particle_a0 = (u8 *)actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    func_80171A10(particle_a0, beldo->unk_2A.s, particle_color, particle_variation, 0);
    path_particle_count += 1;
    if (path_particle_count < 0x14) {
        goto loop_31;
    }
    }
    actor->unk_96 = (u16) (actor->unk_96 - 1);
    break;
    case 11:
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
    if (sprite->unk_04 == 5) {
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    func_80047784(sprite, D_80174C6C[((s32) (gameWork.view.viewAngle + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    end_particle_count = 0;
    func_800A56E0(0x706);
    do {
        end_particle_count += 1;
        particle_random = func_80069EF8();
        particle_a0 = (u8 *)actor - 0x20;
        particle_color = 0x8080FF;
        particle_variation = (particle_random & 0xFF) | 0x80;
        ASM_KEEP4(particle_a0, particle_color, particle_variation, beldo);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        func_80171A10(particle_a0, beldo->unk_2A.s, particle_color, particle_variation, 0);
    } while (end_particle_count < 0x14);
    }
    path_end_timer = actor->unk_96 - 1;
    actor->unk_96 = path_end_timer;
    if ((path_end_timer << 0x10) > 0) {
        break;
    }
    actor->unk_96 = 0x2EU;
    actor->unk_9A++;
#ifdef NON_MATCHING
    tail_sprite = D_80174C64;
#else
    tail_sprite = D_80174C64;
#endif
    if (sprite->unk_2C == tail_sprite) {
        break;
    }
#ifndef NON_MATCHING
    tail_state = 0x80080000;
#endif
    sprite->unk_2C = tail_sprite;
    goto update_animation;
    case 12:
    turn_timer = actor->unk_96 - 1;
    actor->unk_96 = turn_timer;
    if ((turn_timer << 0x10) <= 0) {
        actor->unk_96 = 6U;
        if (beldo->unk_2A.s < 0x800) {
            beldo->unk_2A.s = (s16) (beldo->unk_2A.u + 0x200);
        } else {
            actor->unk_96 = 0U;
            actor->unk_9A = (u8) (actor->unk_9A + 1);
        }
    }
    if ((s16) actor->unk_96 == 0x28) {
        beldo->unk_2A.s = 0xE00;
    }
    if ((s16) actor->unk_96 == 0x1E) {
        beldo->unk_2A.s = 0;
    }
    if ((s16) actor->unk_96 == 0x1D) {
        beldo->unk_2A.s = 0x200;
    }
    if ((s16) actor->unk_96 == 0x12) {
        beldo->unk_2A.s = 0;
    }
    if ((s16) actor->unk_96 == 0x11) {
        beldo->unk_2A.s = 0xE00;
    }
    if ((s16) actor->unk_96 == 0xA) {
        beldo->unk_2A.s = 0;
    }
    break;
    case 8:
    case 13:
    bob_phase = actor->unk_9E;
    actor->unk_9E = (u16) (bob_phase + 1);
    actor->unk_A0.unk_A0 = (s32) (actor->unk_A0.unk_A0 + (func_800644B8((s16) bob_phase * 0x55) * 0x10));
    motion->unk_0A = (u16) (beldo->unk_88
        + actor->unk_92.u - actor->unk_A0.unk_A2.unk_A2);
    break;
    case 14:
    animation_timer = actor->unk_96 + 1;
    actor->unk_96 = animation_timer;
    if ((s16) animation_timer < 3) {
        break;
    }
#ifdef NON_MATCHING
    tail_sprite = D_80174C6C;
    tail_state = actor->unk_9A;
#else
    tail_sprite = (u8 *)0x80170000;
    ASM_KEEP(tail_sprite);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    tail_state = actor->unk_9A;
    tail_sprite += 0x4C6C;
#endif
    actor->unk_96 = 0U;
    goto advance_animation;
    case 15:
    if (sprite->unk_04 == 5) {
    particle_a0 = sprite;
    particle_color = 0;
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    sprite_angle_base = gameWork.view.viewAngle;
    sprite_angle_delta = beldo->unk_2A.s;
    func_80047784(particle_a0, D_80174C6C[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7], particle_color);
    wait_particle_count = particle_color;
    func_800A56E0(0x706);
    wait_particle_mode = 1;
loop_66:
    particle_random = func_80069EF8();
    particle_a0 = (u8 *)actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    func_80171A10(particle_a0, beldo->unk_2A.s, particle_color, particle_variation, wait_particle_mode);
    wait_particle_count += 1;
    if (wait_particle_count < 0x14) {
        goto loop_66;
    }
    }
    particle_timer = actor->unk_96 + 1;
    actor->unk_96 = particle_timer;
    if ((s16) particle_timer < 0x19) {
        break;
    }
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0E.unk_0E = -0x10;
    motion->unk_10.unk_12.unk_12 = 0;
    break;
    case 16:
    move_timer = actor->unk_96 + 1;
    actor->unk_96 = move_timer;
    if ((s16) move_timer >= 0xA) {
    actor->unk_96 = 0U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    motion->unk_0C.unk_0E.unk_0E = 4;
    motion->unk_10.unk_12.unk_12 = 0;
    func_80172CC8(motion, -0x50, 0, -0x10, 0);
    func_80172CC8(motion, -0x28, 0, -8, 0);
    func_80172CC8(motion, -0x1C, 0, -0x1E, 0);
    func_800419EC(6, 0xC);
    func_800A56E0(0x601);
    }
    if ((s16) actor->unk_96 == 8) {
    func_80172CC8(motion, -0x30, 0, -0xA, 1);
    func_80172CC8(motion, -0x18, 0, -0x18, 1);
    func_80172CC8(motion, 0, 0, -0x10, 1);
    func_800419EC(6, 0xC);
    func_800A56E0(0x601);
    }
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
    if (sprite->unk_04 == 5) {
    particle_a0 = sprite;
    particle_color = 0;
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C6C;
    sprite_angle_base = gameWork.view.viewAngle;
    sprite_angle_delta = beldo->unk_2A.s;
    func_80047784(particle_a0, D_80174C6C[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7], particle_color);
    move_particle_count = particle_color;
    func_800A56E0(0x706);
    move_particle_mode = 1;
loop_76:
    particle_random = func_80069EF8();
    particle_a0 = (u8 *)actor - 0x20;
    particle_color = 0x8080FF;
    particle_variation = (particle_random & 0xFF) | 0x80;
    func_80171A10(particle_a0, beldo->unk_2A.s, particle_color, particle_variation, move_particle_mode);
    move_particle_count += 1;
    if (move_particle_count < 0x14) {
        goto loop_76;
    }
    }
    break;
    case 17:
    spin_timer = actor->unk_96 + 1;
    actor->unk_96 = (u16) spin_timer;
    if (spin_timer < 0xE) {
    if (!(spin_timer & 1)) {
    previous_angle = (u16) beldo->unk_2A.s;
    next_angle = previous_angle + 0x200;
    beldo->unk_2A.s = next_angle;
    if (next_angle >= 0x1000) {
    beldo->unk_2A.s = (s16) (previous_angle - 0xE00);
    }
    }
    }
    position_x = motion->unk_00;
    velocity_x = motion->unk_0C.unk_0C;
    position_y = motion->unk_04;
    velocity_y = motion->unk_10.unk_10;
    motion->unk_00 = position_x + velocity_x;
    motion->unk_04 = position_y + velocity_y;
    if ((s16) motion->unk_0A < (s16) beldo->unk_88) {
        motion->unk_0A = (u16) (motion->unk_0A + 6);
    }
    if ((s16) actor->unk_96 >= 0x13) {
        actor->unk_96 = 0U;
        actor->unk_9A = (u8) (actor->unk_9A + 1);
        motion->unk_10.unk_12.unk_12 = 0;
        motion->unk_0C.unk_0E.unk_0E = 0;
    }
    if ((actor->unk_96 & 3) == 1) {
    func_80172F44(motion, -0x10, 0, -4);
    func_80172F44(motion, 0xC, 0, -0xC);
    }
    break;
    case 18:
    idle_timer = actor->unk_96 + 1;
    actor->unk_96 = idle_timer;
    if ((s16) idle_timer >= 0x3C) {
    actor->unk_96 = 4U;
    actor->unk_9A = (u8) (actor->unk_9A + 1);
    func_80172A14(actor, motion, sprite);
    *(u8 **)((u8 *)sprite + 0x2C) = D_80174C7C;
    func_80047784(sprite, D_80174C7C[((s32) (gameWork.view.viewAngle + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x800);
    }
    if ((actor->unk_96 & 3) == 1) {
    func_80172F44(motion, -0x10, 0, -4);
    func_80172F44(motion, 0xC, 0, -0xC);
    }
    break;
    case 19:
    final_timer = actor->unk_96 - 1;
    actor->unk_96 = final_timer;
    if ((final_timer << 0x10) > 0) {
        break;
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
    func_80047784(sprite, tail_sprite[((s32) (gameWork.view.viewAngle + beldo->unk_2A.s + 0x100) >> 9) & 7], 0);
#else
    tail_state = (((s32) (((S_func_8132B8AC_4 *)tail_state)->unk_3228 + beldo->unk_2A.s + 0x100) >> 9) & 7) + (s32) tail_sprite;
    func_80047784(sprite, ((S_func_8132B8AC_5 *)tail_state)->unk_00, 0);
#endif
    break;
    case 20:
        func_80170C3C();
        break;
    default:
        break;
    }
    if (D_80174CE0 == 0) {
        return;
    }
    final_direction = ((s32) (gameWork.view.viewAngle + beldo->unk_2A.s + 0x100) >> 9) & 7;
    sprite_direction = final_direction;
    if (actor->unk_94 != sprite_direction) {
        func_80047738(sprite, sprite->unk_2C[sprite_direction], sprite->unk_04);
        actor->unk_94 = sprite_direction;
    }
    if (dirSpriteFlag[sprite_direction] != 0) {
        tail_test = sprite->unk_14 | 1;
    } else {
        tail_test = sprite->unk_14 & 0xFFFE;
    }
    sprite->unk_14 = (u16) tail_test;
    return;
}
