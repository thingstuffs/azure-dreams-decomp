#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_80404DBC(s32 arg0);
extern void func_80403D24(s32 arg0);
extern void func_804059A8(s32 arg0);
extern void func_80404570(s32 arg0);

/* Dual symbols at the same address force load-via-v1 / store-via-at RMW
 * (retail uses separate %hi materializations, not a reused base reg). */
extern s32 D_8008DAB4[4];
extern s32 D_8008DAB4_2[4];
__asm__(".set D_8008DAB4, 0x8008DAB4");
__asm__(".set D_8008DAB4_2, 0x8008DAB4");

/* Processes object components and sets the object and global 0x8000 flags. */
void func_8001F720(void *object) {
    /* Pin walker to $s0 — pure C assigns it $s1/$s2 under 2.7.2. */
    register s32 *component_cursor ASM_REG("$16");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 component_count;
    s32 component;
    u16 object_flags;
    s32 global_flags;

    component_cursor = (s32 *)((u8 *)object + 0x20);
    if (object != NULL) {
        component_count = 0;
        func_80404DBC(*(s32 *)((u8 *)object + 0x20));
        func_80403D24(*(s32 *)((u8 *)object + 0x38));
        func_804059A8(*(s32 *)((u8 *)object + 0x3C));
        do {
            component = *(s32 *)((u8 *)component_cursor + 4);
            component_cursor = (s32 *)((u8 *)component_cursor + 4);
            component_count += 1;
            func_80404570(component);
        } while (component_count < 5);
        object_flags = *(u16 *)((u8 *)object + 0x1E);
        global_flags = D_8008DAB4[0];
        object_flags |= 0x8000;
        global_flags |= 0x8000;
        *(u16 *)((u8 *)object + 0x1E) = object_flags;
        D_8008DAB4_2[0] = global_flags;
    }
}
