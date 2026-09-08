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

void func_80170F68(void *arg0) {
    u16 stack[8];
    u8 *base;
    u8 *flags;
    u8 *particle_page;
    Particle *particle;
    register s32 dead_timer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *obj;
    s16 state;
    s16 timer;
    u16 old_timer;
    u16 next_state;
    u8 shade;
    u8 particle_level;
    u32 flag_value;
    s32 burst_x;
    s32 burst_y;
    s32 burst_kind;
    s32 count_1;
    s32 x_1;
    s32 y_1;
    s32 count_2;
    s32 x_2;
    s32 y_2;
    s32 count_3;
    s32 x_3;
    s32 y_3;
    register u32 mask ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 one;

    *(Copy8 *)&stack[4] = D_80164A4C;
    base = D_80083498;
    state = S16_AT(arg0, 0x12);
    flags = base + 0x20;
    one = 1;

    if (state == one) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    obj = D_800E3D7C;
    if (U8_AT(obj, 0x9A) != 0x11) {
        goto end;
    }
    U16_AT(obj, 0x96) += 0x3C;
    U16_AT(arg0, 0x18) = 0;
    U16_AT(arg0, 0x12)++;
    S8_AT(obj, 0xA8) = one;
    D_80175D50[0x47] = 0;
    goto end;

state_1:
    U16_AT(arg0, 0x18)++;
    if (S16_AT(arg0, 0x18) == 6) {
        stack[0] = stack[4] + ((s16)stack[6] >> 1);
        stack[1] = stack[5] + 0x30;
        func_800B8FC8(D_800814A8, &stack[4], stack, 1, state);
    }
    if (S16_AT(arg0, 0x18) >= 7) {
        if ((U16_AT(arg0, 0x18) & 3) == 3) {
            burst_kind = (rand() & 0xFF) | 0x80;
            burst_x = (s16)((rand() & 0x7F) - 0x40);
            burst_y = (s16)((rand() & 0x7F) - 0x40);
            func_80170D2C(base, burst_kind, burst_x, burst_y,
                (s16)((rand() & 0x7F) - 0x40));
        }
    }
    mask = 0x10000000;
    particle_page = (u8 *)0x80080000;
    ASM_KEEP_NV(particle_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    particle = (Particle *)(particle_page + 0x2E80);
    particle_level = particle->c;
    U32_AT(flags, 0x1C) |= mask;
    if (particle_level < 0xFC) {
        shade = particle->e + 3;
        particle->e = shade;
        particle->d = shade;
        particle->c = shade;
    }

    timer = S16_AT(arg0, 0x18);
    count_1 = 0;
    if (timer >= 10) {
        count_1 = 1;
        if (timer >= 20) {
            count_1 = 2;
            if (timer >= 30) {
                count_1 = 3;
                if (timer >= 40) {
                    count_1 = 5;
                    if (timer < 50) {
                        count_1 = 4;
                    }
                }
            }
        }
    }
    dead_timer = S16_AT(arg0, 0x18);
    ASM_KEEP(dead_timer);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (count_1 > 0) {
        do {
            count_1--;
            x_1 = (s16)((rand() & 0x3F) - 0x20);
            y_1 = (s16)((rand() & 0x3F) - 0x20);
            func_800F692C(D_80083780, x_1, y_1,
                (s16)(-(rand() & 0x3F) - 0x10));
        } while (count_1 > 0);
    }
    if (S16_AT(arg0, 0x18) >= 0x3C) {
        next_state = U16_AT(arg0, 0x12);
        U16_AT(arg0, 0x18) = 0;
        goto advance_state;
    }
    goto end;

state_2:
    old_timer = U16_AT(arg0, 0x18);
    U16_AT(arg0, 0x18) = old_timer + 1;
    if ((u32)(old_timer - 0xE) < 9U) {
        count_2 = 8;
        do {
            count_2--;
            x_2 = (s16)((rand() & 0x3F) - 0x20);
            y_2 = (s16)((rand() & 0x3F) - 0x20);
            func_800F6B2C(D_80083780, x_2, y_2,
                (s16)(-(rand() & 0x1F) - 0x18));
        } while (count_2 > 0);
    }
    if (S16_AT(arg0, 0x18) < 0xE) {
        count_3 = 5;
        do {
            count_3--;
            x_3 = (s16)((rand() & 0x3F) - 0x20);
            y_3 = (s16)((rand() & 0x3F) - 0x20);
            func_800F692C(D_80083780, x_3, y_3,
                (s16)(-(rand() & 0x3F) - 0x10));
        } while (count_3 > 0);
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
    mask = 0xEFFFFFFF;
    flag_value = U32_AT(flags, 0x1C);
    particle->e = 0x80;
    particle->d = 0x80;
    particle->c = 0x80;
    U32_AT(flags, 0x1C) = flag_value & mask;

    next_state = U16_AT(arg0, 0x12);
advance_state:
    U16_AT(arg0, 0x12) = next_state + 1;
    goto end;

state_3:
    D_8008346C = 0;
    U16_AT(arg0, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
