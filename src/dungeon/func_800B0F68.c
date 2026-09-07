#include "common.h"

typedef struct DungeonEffect {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 field_A;
    s32 field_C;
    s32 field_10;
    u8 pad14[2];
    s16 field_16;
    u16 flags;
} DungeonEffect;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);
extern void func_8009A350(s32, s32, s32, u16 *);
extern void func_800B653C(DungeonEffect *, s16);
extern void func_800B67F0(void);
extern void func_800B6814(void *);

void func_800B66C8(void *arg0)
{
    DungeonEffect effect;
    void *object;
    register s32 x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 y;
    s32 angle;
    s32 count;
    s32 step;
    register s32 i ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u16 field_A;

    object = arg0;
    x = *(s16 *)((u8 *)object + 2);
    if (x < 0) {
        x += 0x3F;
    }
    y = *(s16 *)((u8 *)object + 6);
    x >>= 6;
    ASM_KEEP(x);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (y < 0) {
        y += 0x3F;
    }
    func_8009A350(x - 1, y >> 6, 0, &effect.flags);
    if (effect.flags & 0x400) {
        func_800B6814(object);
        func_800B67F0();
        return;
    }

    i = 0;
    count = (rand() & 7) | 4;
    ASM_KEEP(count);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    step = 0x1000 / count;
    angle = rand();
    field_A = *(u16 *)((u8 *)object + 0xA);
    effect.field_16 = -4;
    effect.field_A = field_A;
    if (count != 0) {
        do {
            i++;
            effect.x = *(u16 *)((u8 *)object + 2) +
                       (rand() & 0x1F) - 0x10;
            effect.y = *(u16 *)((u8 *)object + 6) +
                       (rand() & 0x1F) - 0x10;
            effect.field_C = func_80064584(angle) << 5;
            effect.field_10 = func_800644B8(angle) << 5;
            func_800B653C(&effect, angle);
            angle += step;
        } while (i < count);
    }
}

/* MECHANISM: The 0x1c-byte stack record exposes retail fields at sp+0x10.
   ABI-wide angle avoids a sixth saved value; pins encode the saved hold roles.
   X stays in v0 across Y hazards; RNG is ABI-wide and the emitter narrows it.
   A split field_A read/store holds v1 across the independent -4 record store. */
