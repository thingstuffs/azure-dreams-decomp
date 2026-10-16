#include "common.h"
#include "shared/object_flags.h"
typedef struct { u8 pad[0x32]; s16 lifetime; } ParticleWork;
typedef union { s32 word; struct { u16 low; s16 high; } half; } ParticleFixed;
typedef struct { u16 pad0, x, pad4, y; ParticleFixed z; } ParticlePosition;
extern s16 D_80026428;
extern s32 func_800BCB04(s32, s32, s16);
extern s32 rand(void);
/* Raise a particle below terrain, then retire it when its lifetime expires. */
void func_80024ED4(ParticleWork *work, ParticlePosition *position) {
    D_80026428 = 1;
    if (position->z.half.high < (s16)func_800BCB04(position->x, position->y, (s16)((u16)position->z.half.high + 2))) {
        position->z.word += 0x20000 + (rand() & 0xFFF);
    }
    work->lifetime = (u16)work->lifetime - 8;
    if (work->lifetime <= 0) {
        *(u16 *)((u8 *)work - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
