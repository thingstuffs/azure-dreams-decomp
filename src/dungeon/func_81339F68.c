#include "common.h"

typedef struct {
    u8 bytes[8];
} Copy8 __attribute__((packed));

typedef struct {
    u8 pad[0xC];
    u8 c;
    u8 d;
    u8 e;
} Particle;

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern s32 rand(void);
extern void func_800B8FC8(void *, void *, void *, s32, s32);
extern void func_800F692C();
extern void func_800F6B2C();
extern void func_80170D2C();

extern s32 D_800814A0;
extern void *D_800814A8;
extern Particle D_80082E80;
extern u8 D_80083498[];
extern s32 D_8008346C;
extern u8 D_80083780[];
extern void *D_800E3D7C;
extern Copy8 D_80164A4C;
extern u8 *D_80175D50;

/* Update a staged particle effect, ramping emission and brightness before fading out. */
void func_80170F68(void *effect) {
    u16 blit_data[8];
    u8 *burst_context;
    u8 *render_state;
    u8 *particle_page;
    Particle *particle;
    register s32 timer_snapshot ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *actor;
    s16 state;
    s16 timer;
    u16 old_timer;
    u16 next_state;
    u8 shade;
    u8 particle_level;
    u32 render_flags;
    s32 burst_x;
    s32 burst_y;
    s32 burst_kind;
    s32 ramp_count;
    s32 ramp_x;
    s32 ramp_y;
    s32 late_count;
    s32 late_x;
    s32 late_y;
    s32 early_count;
    s32 early_x;
    s32 early_y;
    register u32 flag_mask ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 enabled;

    *(Copy8 *)&blit_data[4] = D_80164A4C;
    burst_context = D_80083498;
    state = S16_AT(effect, 0x12);
    render_state = burst_context + 0x20;
    enabled = 1;

    if (state == enabled) {
        goto brighten;
    }
    if (state < 2) {
        if (state == 0) {
            goto wait_actor;
        }
        goto end;
    }
    if (state == 2) {
        goto fade;
    }
    if (state == 3) {
        goto finish;
    }
    goto end;

wait_actor:
    actor = D_800E3D7C;
    if (U8_AT(actor, 0x9A) != 0x11) {
        goto end;
    }
    U16_AT(actor, 0x96) += 0x3C;
    U16_AT(effect, 0x18) = 0;
    U16_AT(effect, 0x12)++;
    S8_AT(actor, 0xA8) = enabled;
    D_80175D50[0x47] = 0;
    goto end;

brighten:
    U16_AT(effect, 0x18)++;
    if (S16_AT(effect, 0x18) == 6) {
        blit_data[0] = blit_data[4] + ((s16)blit_data[6] >> 1);
        blit_data[1] = blit_data[5] + 0x30;
        func_800B8FC8(D_800814A8, &blit_data[4], blit_data, 1, state);
    }
    if (S16_AT(effect, 0x18) >= 7) {
        if ((U16_AT(effect, 0x18) & 3) == 3) {
            burst_kind = (rand() & 0xFF) | 0x80;
            burst_x = (s16)((rand() & 0x7F) - 0x40);
            burst_y = (s16)((rand() & 0x7F) - 0x40);
            func_80170D2C(burst_context, burst_kind, burst_x, burst_y,
                (s16)((rand() & 0x7F) - 0x40));
        }
    }
    flag_mask = 0x10000000;
    particle_page = (u8 *)0x80080000;
    ASM_KEEP_NV(particle_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    particle = (Particle *)(particle_page + 0x2E80);
    particle_level = particle->c;
    U32_AT(render_state, 0x1C) |= flag_mask;
    if (particle_level < 0xFC) {
        shade = particle->e + 3;
        particle->e = shade;
        particle->d = shade;
        particle->c = shade;
    }

    timer = S16_AT(effect, 0x18);
    ramp_count = 0;
    if (timer >= 10) {
        ramp_count = 1;
        if (timer >= 20) {
            ramp_count = 2;
            if (timer >= 30) {
                ramp_count = 3;
                if (timer >= 40) {
                    ramp_count = 5;
                    if (timer < 50) {
                        ramp_count = 4;
                    }
                }
            }
        }
    }
    timer_snapshot = S16_AT(effect, 0x18);
    ASM_KEEP(timer_snapshot);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (ramp_count > 0) {
        do {
            ramp_count--;
            ramp_x = (s16)((rand() & 0x3F) - 0x20);
            ramp_y = (s16)((rand() & 0x3F) - 0x20);
            func_800F692C(D_80083780, ramp_x, ramp_y,
                (s16)(-(rand() & 0x3F) - 0x10));
        } while (ramp_count > 0);
    }
    if (S16_AT(effect, 0x18) >= 0x3C) {
        next_state = U16_AT(effect, 0x12);
        U16_AT(effect, 0x18) = 0;
        goto advance_state;
    }
    goto end;

fade:
    old_timer = U16_AT(effect, 0x18);
    U16_AT(effect, 0x18) = old_timer + 1;
    if ((u32)(old_timer - 0xE) < 9U) {
        late_count = 8;
        do {
            late_count--;
            late_x = (s16)((rand() & 0x3F) - 0x20);
            late_y = (s16)((rand() & 0x3F) - 0x20);
            func_800F6B2C(D_80083780, late_x, late_y,
                (s16)(-(rand() & 0x1F) - 0x18));
        } while (late_count > 0);
    }
    if (S16_AT(effect, 0x18) < 0xE) {
        early_count = 5;
        do {
            early_count--;
            early_x = (s16)((rand() & 0x3F) - 0x20);
            early_y = (s16)((rand() & 0x3F) - 0x20);
            func_800F692C(D_80083780, early_x, early_y,
                (s16)(-(rand() & 0x3F) - 0x10));
        } while (early_count > 0);
    }
    particle_page = (u8 *)0x80080000;
    ASM_KEEP_NV(particle_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    particle = (Particle *)(particle_page + 0x2E80);
    if (particle->c >= 0x81) {
        shade = particle->e - 3;
        particle->e = shade;
        particle->d = shade;
        particle->c = shade;
        goto end;
    }
    flag_mask = 0xEFFFFFFF;
    render_flags = U32_AT(render_state, 0x1C);
    particle->e = 0x80;
    particle->d = 0x80;
    particle->c = 0x80;
    U32_AT(render_state, 0x1C) = render_flags & flag_mask;

    next_state = U16_AT(effect, 0x12);
advance_state:
    U16_AT(effect, 0x12) = next_state + 1;
    goto end;

finish:
    D_8008346C = 0;
    U16_AT(effect, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
