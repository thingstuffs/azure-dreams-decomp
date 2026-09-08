#include "common.h"

typedef struct {
    u32 value;
    s8 index;
    u8 pad05[3];
    void *owner;
    u8 pad0C[8];
    u16 flags;
} Entry;

typedef struct {
    u8 pad00[0xC];
    s32 base;
} Owner;

extern void func_80026660(void) __attribute__((noreturn));
extern void func_800266C8(void) __attribute__((noreturn));

void func_8195AE0C(Entry *entry, s16 *step, s32 lower, s32 upper)
{
    Entry *p = entry;
    s32 dead;
    s32 scaled;
    Owner *owner;
    u8 current;

    owner = p->owner;
    p->value = owner->base + p->index * 0x18;
    if (*step > 0) {
        dead = (u8)p->index + 1;
        ASM_TAILSLOT_PIN_TIED(dead);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80026660();
        return;
    }
    if (*step < 0) {
        p->index = (u8)p->index - 1;
    }

    current = (u8)p->index;
    scaled = current << 24;
    if ((s8)current < (s16)lower) {
        dead = p->flags | 0x4000;
        p->index = lower;
        ASM_TAILSLOT_PIN_TIED(dead);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800266C8();
        return;
    }
    if ((s8)current > (s16)upper) {
        dead = p->flags | 0x4000;
        p->index = upper;
        ASM_TAILSLOT_PIN_TIED(dead);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800266C8();
        return;
    }
    p->flags &= 0xBFFF;
}
