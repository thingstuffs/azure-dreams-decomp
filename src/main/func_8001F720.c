#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_80404DBC(s32 value);
extern void func_80403D24(s32 value);
extern void func_804059A8(s32 value);
extern void func_80404570(s32 value);

/* Dual symbols at the same address force load-via-v1 / store-via-at RMW
 * (retail uses separate %hi materializations, not a reused base reg). */
extern s32 D_8008DAB4[4];
extern s32 D_8008DAB4_2[4];

/* Processes object components and sets the object and global 0x8000 flags. */
void func_8001F720(void *object) {
    s32 *component_cursor;
    s32 component_count;
    u16 object_flags;
    s32 global_flags;

    component_cursor = (s32 *)((u8 *)object + 0x20);
    if (object != NULL) {
        func_80404DBC(*(s32 *)((u8 *)object + 0x20));
        func_80403D24(*(s32 *)((u8 *)object + 0x38));
        func_804059A8(*(s32 *)((u8 *)object + 0x3C));
        for (component_count = 0; component_count < 5; component_count++) {
            func_80404570(component_cursor[component_count + 1]);
        }
        object_flags = *(u16 *)((u8 *)object + 0x1E);
        global_flags = D_8008DAB4[0];
        object_flags |= 0x8000;
        global_flags |= 0x8000;
        *(u16 *)((u8 *)object + 0x1E) = object_flags;
        D_8008DAB4_2[0] = global_flags;
    }
}
