#include "common.h"

typedef struct Link {
    u8 pad_00[0x14];
    u16 counter;
} Link;

typedef struct Entity {
    u16 flags;
    u8 pad_02[0xA];
    Link *link;
    s16 timer;
    s16 limit;
} Entity;

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct Aux {
    u8 pad_00[0x1A];
    u16 angle;
} Aux;

extern s32 D_800814A0[3];

#ifdef __mips__
extern void func_80024C74(void);
extern void func_80024CD4(void);
extern void func_80024D7C(void);
extern void func_8002511C(void);
extern void func_80025178(void);
extern void func_8002519C(void);
extern void func_800251D0(void);
extern void func_8002526C(void);
extern void func_800252A4(void);

/* Retail places a 10-entry (40-byte) callee jump table immediately before this
 * function's own code, all under one 248-byte symbol. The table is pinned to
 * the function's own named section (NOT the generic ".text") so it lands
 * ahead of the compiled body in the same output section, byte-for-byte and
 * gap-free -- a naked-asm label + `section(".text")` (the original approach)
 * leaves the table in the literal ".text" section, which tools/ccproc.py
 * never renames (it only fires on a genuine `.ent NAME`), so the overlay
 * gate's `.text.func_81892800`-scoped KEEP rule finds nothing there and the
 * table silently zero-fills. */
static void (*const func_81892800_table[])(void)
    __attribute__((section(".text.func_81892800"))) = {
        func_80024C74,
        0,
        func_80024CD4,
        func_80024D7C,
        func_8002511C,
        func_80025178,
        func_8002519C,
        func_800251D0,
        func_8002526C,
        func_800252A4,
    };
#endif

/* Advance motion and rotation, then set completion flags when the timer exceeds its limit. */
void func_81892800(Entity *entity, Motion *motion, Aux *aux) {
    s16 timer;

    entity->link->counter++;
    motion->x += motion->dx;
    motion->y += motion->dy;
    if (entity->timer < 8) {
        motion->dz *= 2;
    }
    motion->z += motion->dz;
    aux->angle += 0x300;
    timer = (u16)entity->timer + 1;
    entity->timer = timer;
    if (entity->limit < timer) {
        entity[-1].limit |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
