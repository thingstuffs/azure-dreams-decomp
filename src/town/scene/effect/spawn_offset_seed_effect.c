#include "common.h"
#include "shared/dungeon_projectile_views.h"

   /* slot in spawn_offset_seed_effect */

typedef struct SpawnMotion {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} SpawnMotion;   /* motion in spawn_offset_seed_effect */

typedef struct SpawnSeed {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} SpawnSeed;   /* seed in spawn_offset_seed_effect */


void *func_800373DC();                       /* extern */
s32 func_8003BC18(void *, void *);
s32 func_80071494();                                /* extern */
extern u8 score_sprite_draw_callback_address[];
extern u8 D_802843E8[];
extern s32 D_802843EC[];
extern u8 D_8052FA64[];

/* Spawn a 0x136 effect at the seed's offset position with a randomised vertical kick. */
void spawn_offset_seed_effect(SpawnSeed *seed) {
    u32 page;
    u16 flags;
    s32 global_word;
    void *sprite;
    SpawnMotion *motion;
    ProjectileObject *slot;

    slot = func_800373DC(0x136);
    if (slot != 0) {
        slot->unk_10 = D_8052FA64;
        func_8003BC18(slot, &score_sprite_draw_callback_address);
        motion = slot->unk_08;
        sprite = slot->unk_0C;
        motion->unk_00 = (s32) (seed->unk_00 + 0xFFF90000);
        motion->unk_04 = (s32) (seed->unk_04 + 0xFFFD0000);
        motion->unk_08 = (s32) seed->unk_08;
        motion->unk_0C = (s32) ((s32) seed->unk_0C >> 1);
        motion->unk_14 = (s32) (((func_80071494() & 0x1FF) - 0x100) << 0xA);
        page = 0x00800000;
        (*(s16 *)((u8 *)sprite + 0x1E)) = 0x800;
        (*(s16 *)((u8 *)sprite + 0x1C)) = 0x800;
        (*(s16 *)((u8 *)sprite + 0x10)) = 0x60;
        flags = (*(u16 *)((u8 *)sprite + 0x14));
        (*(void * *)((u8 *)sprite + 0)) = D_802843E8;
        (*(u16 *)((u8 *)sprite + 0x14)) = flags | 0xD;
        global_word = D_802843EC[0];
        page |= 0x80F0;
        (*(s8 *)((u8 *)sprite + 4)) = 0;
        (*(s8 *)((u8 *)sprite + 5)) = 0;
        (*(s32 *)((u8 *)sprite + 0xC)) = page;
        (*(s32 *)((u8 *)sprite + 8)) = global_word;
    }
}
/* MECHANISM: Symbol-typed hi/lo globals preserve the 0x20 frame and natural s2/s1/s0 held roles. A
   named 0x00800000 page kept live splits the late ori and fills the global-load delay. */
