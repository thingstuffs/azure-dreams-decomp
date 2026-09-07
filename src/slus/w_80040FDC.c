#include "common.h"

/* Given a u16 index, looks up D_8006CE80[idx] (12-byte struct elements). If the
 * element's `unk4` pointer is non-null, and that pointed-to struct's `unk8`
 * field is also non-null, calls func_8003F8F8() with that inner pointer. */
/* Struct pointed to by D_8006CE80[i].unk4; its field at offset 8 is a pointer
 * passed to func_8003F8F8. */
typedef struct S_8006CE80_inner {
    s32 unk0;
    s32 unk4;
    void *unk8;
} S_8006CE80_inner;

/* Array element struct for D_8006CE80, 12 bytes wide (idx*12 indexing). */
typedef struct S_8006CE80 {
    s32 unk0;
    S_8006CE80_inner *unk4;
    s32 unk8;
} S_8006CE80;

extern S_8006CE80 D_8006CE80[64];
extern void func_8003F8F8(void *arg);

void func_80040FDC(u16 idx) {
    s32 byteoff = (s32)idx * 3 * 4;
    S_8006CE80 *elem = (S_8006CE80 *)((u8 *)D_8006CE80 + byteoff);
    S_8006CE80_inner *p = elem->unk4;

    if (p != (S_8006CE80_inner *)0) {
        void *q = p->unk8;

        if (q != (void *)0) {
            func_8003F8F8(q);
        }
    }
}
