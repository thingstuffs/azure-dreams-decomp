#include "modules/dungeon_ovl_1870800.h"
#include "shared/object_flags.h"

typedef struct ParticleOwner {
    u8 pad_00[0x52];
    u16 flags;
} ParticleOwner;

typedef struct ParticleEffect {
    ParticleOwner *owner;
    u8 pad_04[0x44];
    s16 delay;
    s16 fade_step;
    s16 state;
    s16 lifetime;
} ParticleEffect;

typedef struct ParticleMotion {
    s32 x, y, z;
    s32 vx, vy, vz;
} ParticleMotion;

typedef struct ParticlePrimitive {
    u8 pad_00[4];
    u8 frame_x, frame_y;
    u8 pad_06[6];
    u8 red, green, blue;
    u8 pad_0F[5];
    u16 flags;
} ParticlePrimitive;

struct RegistrationNode;
struct S_80045340_Entry;
extern s32 func_8004491C(struct RegistrationNode *, s32);
extern s32 func_80045340(void *, s32, struct S_80045340_Entry *, s32);
extern void func_800478B8(void *);
extern s32 func_80069EF8(void);

/* Delay a spawned particle, then integrate its motion and fade until deletion.
 * Retail: [file 0x1870FDC,0x1871178), [RAM 0x800247DC,0x80024978).
 */
void func_800247DC(void *effect, void *position, void *primitive)
{
    ParticleEffect *p = effect;
    ParticleMotion *motion = position;
    ParticlePrimitive *sprite = primitive;

    p->owner->flags |= 0x8000;
    switch (p->state) {
    case 0:
        if (--p->delay <= 0) {
            func_8004491C((struct RegistrationNode *)((u8 *)p - 0x20), (s32)func_80045340);
            p->state++;
        }
        break;
    case 1:
        func_800478B8(sprite);
        if (sprite->flags & 0x6000) {
            sprite->frame_x = 0;
            sprite->frame_y = 0;
        }
        motion->x += motion->vx;
        motion->y += motion->vy;
        if (motion->vz != 0) {
            motion->z += motion->vz;
            motion->vz += 0x8000 + (func_80069EF8() & 0xFFF);
        }
        if (--p->lifetime <= 0) {
            if (sprite->red >= p->fade_step) {
                sprite->red = sprite->green = sprite->blue -= p->fade_step;
            } else {
                ((u16 *)p)[-1] |= 0x8000;
                objectFlagBlock.flags |= 0x8000;
            }
        }
        break;
    }
}
