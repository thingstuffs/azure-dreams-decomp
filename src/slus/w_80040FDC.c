#include "common.h"

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

/* Passes the indexed entry's nested pointer to func_8003F8F8 if both pointers exist. */
void func_80040FDC(u16 index) {
    s32 byte_offset = (s32)index * 3 * 4;
    S_8006CE80 *entry = (S_8006CE80 *)((u8 *)D_8006CE80 + byte_offset);
    S_8006CE80_inner *inner = entry->unk4;

    if (inner != (S_8006CE80_inner *)0) {
        void *target = inner->unk8;

        if (target != (void *)0) {
            func_8003F8F8(target);
        }
    }
}
