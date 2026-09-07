#include "common.h"

/* Linked-entry struct used by the D_8006CE80 table: each 0xC-byte slot
 * holds an unrelated value, a "next"-style pointer to another entry of
 * the same layout, and a trailing value. */
typedef struct S_8006CE80 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ struct S_8006CE80 *unk4;
    /* 0x8 */ s32 unk8;
} S_8006CE80;

extern S_8006CE80 D_8006CE80[];

extern void func_8003F9E0(S_8006CE80 *a0);

/* Given an index into D_8006CE80, walk two "next" hops and, if both are
 * non-null, dispatch the final entry to func_8003F9E0. */
void func_80041038(u16 a0) {
    S_8006CE80 *v0 = &D_8006CE80[(u16)a0 & 0xFFFF];
    S_8006CE80 *p = v0->unk4;

    if (p != 0) {
        p = p->unk4;
        if (p != 0) {
            func_8003F9E0(p);
        }
    }
}
