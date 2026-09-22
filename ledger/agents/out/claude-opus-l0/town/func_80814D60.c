#include "common.h"
#include "m2c_compat.h"

typedef struct SpawnSlot {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} SpawnSlot;   /* slot in func_80814D60 */

typedef struct SpawnMotion {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} SpawnMotion;   /* motion in func_80814D60 */

typedef struct SpawnSeed {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} SpawnSeed;   /* seed in func_80814D60 */


void *func_800373DC();                       /* extern */
M2C_UNK func_8003BC18();           /* extern */
s32 func_80071494();                                /* extern */
extern u8 D_8003C558[];
extern u8 D_802843E8[];
extern s32 D_802843EC[];
extern u8 D_8052FA64[];

/* Spawn a 0x136 effect at the seed's offset position with a randomised vertical kick. */
void func_80814D60(SpawnSeed *seed) {
    u32 page;
    u16 flags;
    s32 global_word;
    void *sprite;
    SpawnMotion *motion;
    SpawnSlot *slot;

    slot = func_800373DC(0x136);
    if (slot != NULL) {
        slot->unk_10 = D_8052FA64;
        func_8003BC18(slot, &D_8003C558);
        motion = slot->unk_08;
        sprite = slot->unk_0C;
        motion->unk_00 = (s32) (seed->unk_00 + 0xFFF90000);
        motion->unk_04 = (s32) (seed->unk_04 + 0xFFFD0000);
        motion->unk_08 = (s32) seed->unk_08;
        motion->unk_0C = (s32) ((s32) seed->unk_0C >> 1);
        motion->unk_14 = (s32) (((func_80071494() & 0x1FF) - 0x100) << 0xA);
        page = 0x00800000;
        (*(volatile s16 *)((u8 *)sprite + 0x1E)) = 0x800;
        (*(volatile s16 *)((u8 *)sprite + 0x1C)) = 0x800;
        (*(volatile s16 *)((u8 *)sprite + 0x10)) = 0x60;
        flags = (*(volatile u16 *)((u8 *)sprite + 0x14));
        (*(void * volatile *)((u8 *)sprite + 0)) = D_802843E8;
        (*(volatile u16 *)((u8 *)sprite + 0x14)) = flags | 0xD;
        global_word = D_802843EC[0];
        page |= 0x80F0;
        (*(volatile s8 *)((u8 *)sprite + 4)) = 0;
        (*(volatile s8 *)((u8 *)sprite + 5)) = 0;
        (*(volatile s32 *)((u8 *)sprite + 0xC)) = page;
        (*(volatile s32 *)((u8 *)sprite + 8)) = global_word;
    }
}
/* MECHANISM: Symbol-typed hi/lo globals preserve the 0x20 frame and natural s2/s1/s0 held roles.
   A guarded v0 flags pin plus volatile tail fields and one scheduler fence reproduce the lhu/address/store order.
   A named 0x00800000 page kept live splits the late ori and fills the global-load delay. */
