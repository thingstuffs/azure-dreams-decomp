#include "common.h"

extern void *D_8002014C[5];
extern u8 D_80026F80[];
extern u8 D_800F7968[16];
extern u8 D_800F79E8[16];
extern s32 D_800814A0;

extern s32 rand(void);
extern void func_800478B8(void *);
extern void func_8003DB94(void *, void *, s32);
extern void func_800252B8(s32, s32, s32, s32);
extern void func_800253BC(void *, s32, s32);
extern void func_80026CE4(s32);
extern void func_8008F134(void *);

typedef struct B {
    u8 pad0[0x10];
    s16 field10;
    u8 pad12[0x18 - 0x12];
    s16 field18;
    u16 field1a;
} B;

typedef struct A {
    B *unk0;
    u8 pad4[0x50 - 0x04];
    s16 state;
    u16 timer;
    u8 pad54[2];
    s16 field56;
    u16 flags;
} A;

typedef struct C {
    s32 w0;
    s32 w4;
    s32 w8;
    u8 pad0c[0x14 - 0x0c];
    s32 w20;
} C;

typedef struct D {
    void *unk0;
    u8 pad4[0x0c - 0x04];
    union { u8 b; s32 w; } f0c;
    u8 pad10[0x14 - 0x10];
    u16 h14;
} D;

typedef struct Local {
    void *p;
    s32 a;
    s32 b;
    s16 c;
    u16 d;
    s16 e;
} Local;

/* Updates entity animation, vertical motion, particles, and timed removal. */
void func_8002582C(A *entity, C *motion, D *sprite) {
    B *cell = entity->unk0;
    s32 cell_flags;
    s32 state;
    s32 particles_left;
    s32 random_value;
    s32 particle_x;
    static void *const keepalive[5] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    if (entity->flags & 2) {
        if (sprite->f0c.b) {
            sprite->f0c.w += 0xfffefeff;
        }
    }

    cell_flags = cell->field1a;
    cell->field1a = cell_flags | 2;
    if (entity->flags & 1) {
        cell->field1a = cell_flags | 6;
    }

    func_800478B8(sprite);
    if (entity->flags & 4) {
        if (sprite->unk0 == (void *)D_800F7968) {
            func_8003DB94(sprite, D_800F79E8, 0);
        }
    }
    if (sprite->h14 & 0x6000) {
        func_8003DB94(sprite, D_800F7968, 0);
    }

    state = entity->state;
    if ((u32)state >= 5U) {
        goto END;
    }
    goto *D_8002014C[state];

L0:
    if (motion->w8 > 0) {
        motion->w8 += motion->w20;
        particles_left = 3;
        for (;;) {
            random_value = rand();
            particle_x = motion->w0;
            particle_x += ((random_value & 0xff) - 128) << 14;
            random_value = rand();
            func_800252B8(0x808080, particle_x, motion->w4 + 0x80000, (random_value & 0xf) << 16);
            if (--particles_left < 0) {
                goto END;
            }
        }
    }
    motion->w8 = 0;
    motion->w20 = 0;
    entity->state = 1;
    goto END;

L1:
    if (cell->field1a & 1) {
        Local effect;
        u8 *effect_entry = D_80026F80 + cell->field18 * 400 + cell->field10 * 40 + (entity->field56 * 12 + 4);
        effect.d = *(u16 *)(effect_entry + 8);
        effect.a = *(s32 *)(effect_entry + 0);
        effect.b = *(s32 *)(effect_entry + 4);
        effect.c = 0;
        effect.e = 0;
        effect.p = entity;
        func_800253BC(&effect, motion->w4, 0);
    }
    goto END;

L2:
    {
        s32 timer_left = entity->timer - 1;
        entity->timer = timer_left;
        if ((s16)timer_left <= 0) {
            if (entity->field56 == 0) {
                func_80026CE4(90);
            }
            motion->w20 = 0x40000;
            entity->state = 3;
        }
    }
    goto END;

L3:
    if (motion->w8 > 0x7fffff) {
        goto L3_over;
    }
    {
        s32 height = motion->w8 + motion->w20;
        motion->w8 = height;
        if (height <= 0x3fffff) {
            particles_left = 3;
            for (;;) {
                random_value = rand();
                particle_x = random_value & 0xff;
                particle_x -= 128;
                particle_x <<= 14;
                particle_x += 0x5600000;
                random_value = rand();
                func_800252B8(0x808080, particle_x, motion->w4 + 0x80000, (random_value & 0xf) << 16);
                if (--particles_left < 0) {
                    goto END;
                }
            }
        }
    }
    goto END;

L3_over:
    entity->timer = 2;
    entity->state = 4;
    goto END;

L4:
    {
        s32 timer_left = entity->timer - 1;
        entity->timer = timer_left;
        if ((s16)timer_left <= 0) {
            func_8008F134((u8 *)entity + 4);
            *(u16 *)((u8 *)entity - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }

END:
    entity->flags &= ~2;
}
