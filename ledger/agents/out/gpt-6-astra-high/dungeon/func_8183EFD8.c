#include "common.h"
#include "m2c_compat.h"

typedef struct S_8183EFD8_0_pre {
    u16 unk_00;
} S_8183EFD8_0_pre;   /* the 0x2 bytes before r_arg0 in func_8183EFD8, addressed as r_arg0[-1] */

typedef struct S_8183EFD8_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { u16 u; s16 s; } unk_4C;   /* accessed as both */
} S_8183EFD8_0;   /* r_arg0 in func_8183EFD8 */

typedef struct S_8183EFD8_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8183EFD8_1;   /* temp_v1 in func_8183EFD8 */

typedef struct S_8183EFD8_2 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_8183EFD8_2;   /* arg2 in func_8183EFD8 */

typedef struct S_8183EFD8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8183EFD8_3;   /* arg1 in func_8183EFD8 */

typedef struct S_8183EFD8_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8183EFD8_4;   /* temp_v0_4 in func_8183EFD8 */

typedef struct S_8183EFD8_5 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8183EFD8_5;   /* child in func_8183EFD8 */

typedef struct S_8183EFD8_6 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8183EFD8_6;   /* temp_s0 in func_8183EFD8 */

typedef struct S_8183EFD8_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8183EFD8_7;   /* D_800DECF8 in func_8183EFD8 */

typedef struct S_8183EFD8_8 {
    u8 pad_00[0x48];
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
} S_8183EFD8_8;   /* temp_v1_3 in func_8183EFD8 */

typedef struct S_8183EFD8_9 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_8183EFD8_9;   /* ((S_8183EFD8_4 *)temp_v0_4)->unk_08 in func_8183EFD8 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083498[];
extern u8 D_800DECF8[];
extern s32 D_800814A0[];
void func_80024A5C() __attribute__((noreturn)); /* extern */
void *func_8003FD64();                 /* extern */
s32 func_80069EF8();                          /* extern */
extern u8 D_80024688[];

/* Brightens and accelerates an effect, spawns particles, then fades it out. */
void func_8183EFD8(void *effect_arg, S_8183EFD8_3 *motion, S_8183EFD8_2 *sprite) {
    register void *effect ASM_REG("$19") = effect_arg;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 color;
    s32 phase;
    s32 z_velocity;
    s32 random;
    s32 count_or_step;
    u8 bright_level;
    u8 fade_level;
    S_8183EFD8_6 *particle_sprite;
    void *particle;
    S_8183EFD8_1 *owner;
    S_8183EFD8_8 *particle_state;
    void *particle_data;

    ASM_KEEP_NV(effect);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    owner = ((S_8183EFD8_0 *)effect)->unk_00;
    owner->unk_52 = (u16) (owner->unk_52 | 0x8000);
    phase = *(s16 *)((s8 *)effect + 0x4C);
    ((S_8183EFD8_0 *)effect)->unk_48 = (u16) (((S_8183EFD8_0 *)effect)->unk_48 - 1);
    if (phase == 1) {
        goto accelerate;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto brighten;
        }
        func_80024A5C();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    count_or_step = 0x10;
    if (phase == 2) {
        goto fade_out;
    }
    func_80024A5C();

brighten:
    func_800478B8(sprite);
    if ((u8) sprite->unk_0C.at00.v < 0x81U) {
        bright_level = sprite->unk_0C.at02.v + 0x20;
        sprite->unk_0C.at02.v = bright_level;
        sprite->unk_0C.at01.v = bright_level;
        sprite->unk_0C.at00.v = bright_level;
    }
    if ((s16) ((S_8183EFD8_0 *)effect)->unk_48 <= 0) {
        ((S_8183EFD8_0 *)effect)->unk_48 = 0x10U;
        ((S_8183EFD8_0 *)effect)->unk_4C.u = (u16) (((S_8183EFD8_0 *)effect)->unk_4C.u + 1);
        func_80024A5C();
    }
    goto end;

accelerate:
    z_velocity = motion->unk_14 + 0x8000;
    motion->unk_14 = z_velocity;
    motion->unk_08 = (s32) (motion->unk_08 + z_velocity);
    count_or_step = 0x14;
    if ((s16) ((S_8183EFD8_0 *)effect)->unk_48 <= 0) {
        particle_data = D_80024688;
        ((S_8183EFD8_0 *)effect)->unk_4C.s = (s16) ((u16) ((S_8183EFD8_0 *)effect)->unk_4C.s + 1);
        do {
            particle = func_8003FD64(0x312, D_80083498);
            if (particle != NULL) {
                ((S_8183EFD8_4 *)particle)->unk_10 = particle_data;
                particle_sprite = ((S_8183EFD8_4 *)particle)->unk_0C;
                ((S_8183EFD8_9 *)(((S_8183EFD8_4 *)particle)->unk_08))->unk_00 = (s32) motion->unk_00;
                ((S_8183EFD8_9 *)(((S_8183EFD8_4 *)particle)->unk_08))->unk_04 = (s32) motion->unk_04;
                random = func_80069EF8();
                {
                    S_8183EFD8_5 *particle_motion = ((S_8183EFD8_4 *)particle)->unk_08;
                    particle_motion->unk_08 = (s32) (motion->unk_08 + ((random & 0x1F) << 0x10));
                    random = func_80069EF8(particle_motion);
                }
                ((S_8183EFD8_9 *)(((S_8183EFD8_4 *)particle)->unk_08))->unk_0C = (s32) (((random & 0xFFF) - 0x7FF) << 8);
                random = func_80069EF8();
                color = 0x800000;
                ASM_KEEP_NV(color);   /* MATCH pin: retail immediate-load split depends on it */
                ((S_8183EFD8_9 *)(((S_8183EFD8_4 *)particle)->unk_08))->unk_10 = (s32) (((random & 0xFFF) - 0x7FF) << 8);
                particle_sprite->unk_1E = 0x1000;
                particle_sprite->unk_1C = 0x1000;
                particle_sprite->unk_10 = 0x20;
                particle_sprite->unk_00 = D_800DECF8;
                particle_sprite->unk_14 = (u16) (particle_sprite->unk_14 | 0xC);
                random = (s32) ((S_8183EFD8_7 *)D_800DECF8)->unk_04;
                color |= 0x8080;
                particle_sprite->unk_04 = 0;
                particle_sprite->unk_05 = 0;
                particle_sprite->unk_0C = color;
                particle_sprite->unk_08 = random;
                particle_state = particle + 0x20;
                particle_state->unk_48 = (s16) (func_80069EF8((void *)color) & 3);
                particle_state->unk_4A = 0xC;
                particle_state->unk_4C = 0;
                ((S_8183EFD8_4 *)particle)->unk_20 = (void *) ((S_8183EFD8_0 *)effect)->unk_00;
            }
            count_or_step -= 1;
        } while (count_or_step >= 0);
        func_80024A5C();
    }
    goto end;

fade_out:
    if (count_or_step >= (s32) sprite->unk_0C.at00.v) {
        sprite->unk_0C.at00u.v = 0;
        ((S_8183EFD8_0_pre *)effect)[-1].unk_00 = (u16) (((S_8183EFD8_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
        func_80024A5C();
    }
    fade_level = sprite->unk_0C.at02.v - 0x10;
    sprite->unk_0C.at02.v = fade_level;
    sprite->unk_0C.at01.v = fade_level;
    sprite->unk_0C.at00.v = fade_level;

end:
    return;
}
