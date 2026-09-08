#include "common.h"

#include "common.h"

#ifdef NON_MATCHING
#define LEGACY_KEEP(var) ((void)0)
#else
#define LEGACY_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

typedef struct S_800477F4_Sub {
    u16 f0;
    s16 typeB;
    struct S_800477F4_Sub *next;
} S_800477F4_Sub;

typedef struct S_800477F4_Node {
    u8 pad0[2];
    s16 typeA;
    u8 pad4[4];
    S_800477F4_Sub step;
} S_800477F4_Node;

typedef struct S_800477F4_Actor {
    void *cur;
    u8 f4;
    u8 f5;
    u8 pad6[2];
    s32 f8;
    u8 padC[8];
    u16 flags;
} S_800477F4_Actor;

extern u8 D_80080A84[16];

/* Advances the actor's timed step sequence and updates its state flags. */
void func_800477F4(S_800477F4_Actor *actor)
{
    u16 old_flags;
    s32 flags;
    register S_800477F4_Node *node ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    register S_800477F4_Sub *step ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */

    old_flags = actor->flags;
    flags = old_flags & 0xCFFF;
    if (old_flags & 0x800) {
        goto store_flags;
    }

    {
        u8 ticks_left = actor->f5 - 1;
        actor->f5 = ticks_left;
        if ((s8)ticks_left > 0) {
            goto store_flags;
        }
    }

    node = (S_800477F4_Node *)actor->cur;
    step = &node->step;
    if (node->typeA == 0) {
        goto store_flags;
    }
    LEGACY_KEEP(step);

    {
        s16 step_type = *(s16 *)((char *)step + 2);
        if (step_type == 0) {
            flags |= 0x5000;
            goto store_step;
        }
        if (step_type == 1) {
            step = step->next;
            flags |= 0x2000;
            actor->f4 = 0;
            goto update_step;
        }
    }

    actor->f4 = actor->f4 + 1;

update_step:
    actor->f5 = step->f0 / D_80080A84[0];
    flags |= 0x1000;
    actor->f8 = (s32)step->next;

store_step:
    actor->cur = step;

store_flags:
    actor->flags = flags;
}
