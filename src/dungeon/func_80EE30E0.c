#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct {
    u8 bytes[32];
} __attribute__((packed)) Copy32;

extern Copy32 D_80170808;
extern u8 D_80045340;
extern u8 D_80077C50[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_801708BC[];
extern s32 D_80171CE8;
extern u8 D_80174EB8[];
extern u8 D_80174F18[];

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

/* Spawns a moving actor and advances the action through animation and recovery. */
void func_801748E0(void *action_work, void *position, void *sprite, void *actor) {
    Copy32 direction_vectors = D_80170808;
    s32 state;
    u16 timer;
    u16 flags;
    u8 *animations;
    s32 direction_index;
    void *spawned_actor;
    void *spawned_sprite;
    void *spawned_work;
    void *spawned_pos;
    void *direction_ptr;
    s16 direction_y;
    s32 tile_coord;

    state = U8_AT(action_work, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    S32_AT(position, 0x14) = 0;
    S32_AT(position, 0x10) = 0;
    S32_AT(position, 0x0C) = 0;
    timer = U16_AT(action_work, 0x96) + 1;
    U16_AT(action_work, 0x96) = timer;
    if (((s16)timer < 0x14) && !(U16_AT(sprite, 0x14) & 0x8000)) {
        goto done;
    }
    animations = D_80174F18;
    PTR_AT(sprite, 0x2C) = animations;
    func_80047784(sprite,
        animations[((D_80083228 + S16_AT(actor, 0x2A) + 0x100) >> 9) & 7], 0);
    U16_AT(action_work, 0x96) = 0x14;
    U8_AT(action_work, 0x9B) = U8_AT(action_work, 0x9B) + 1;

state_1:
    if ((S16_AT(action_work, 0x96) == 0x13) || (U16_AT(sprite, 0x14) & 0x8000)) {
        if (!(U16_AT(sprite, 0x14) & 0x8000)) {
            func_800A56E0(0x707);
        }
        spawned_actor = func_8003FC64(0x12);
        if (spawned_actor != 0) {
            PTR_AT(spawned_actor, 0x10) = D_801708BC;
            spawned_work = (u8 *)spawned_actor + 0x20;
            func_8004491C(spawned_actor, &D_80045340);
            spawned_sprite = PTR_AT(spawned_actor, 0x0C);
            U16_AT(spawned_sprite, 0x14) &= 0xFFF3;
            PTR_AT(spawned_work, 0x40) = action_work;
            spawned_pos = PTR_AT(spawned_actor, 8);
            S16_AT(spawned_pos, 2) = U16_AT(position, 2);
            S16_AT(spawned_pos, 6) = U16_AT(position, 6);
            S16_AT(spawned_pos, 0x0A) = U16_AT(position, 0x0A) - 0x20;
            direction_ptr = &direction_vectors;
            direction_index = ((u16)S16_AT(actor, 0x2A) >> 7) & 0x1C;
            S32_AT(spawned_work, 0x6C) = S16_AT(direction_ptr, direction_index) << 0x13;
            direction_index = ((u16)S16_AT(actor, 0x2A) >> 7) & 0x1C;
            S32_AT(spawned_work, 0x70) =
                (*(u16 *)(direction_index + (u8 *)direction_ptr + 2)) << 0x13;
            S32_AT(spawned_work, 0x74) = 0xFFF20000;
            S32_AT(spawned_work, 0x80) = 0x14900;
            S16_AT(spawned_work, 0x34) = ((u16)S16_AT(actor, 0x2A) >> 9) & 7;
            spawned_sprite = PTR_AT(spawned_actor, 0x0C);
            S16_AT(spawned_sprite, 0x1E) = 0x1000;
            S16_AT(spawned_sprite, 0x1C) = 0x1000;
            direction_index = ((u16)S16_AT(actor, 0x2A) >> 7) & 0x1C;
            direction_ptr = direction_index + (u8 *)direction_ptr;
            direction_y = *(volatile u16 *)((u8 *)direction_ptr + 2);
            S16_AT(spawned_sprite, 6) = direction_y * 6;
            S16_AT(action_work, 0xA4) = 0x4D;
            tile_coord = S16_AT(position, 2);
            if (tile_coord < 0) {
                tile_coord += 0x3F;
            }
            S8_AT(spawned_work, 0x5C) = tile_coord >> 6;
            tile_coord = S16_AT(position, 6);
            if (tile_coord < 0) {
                tile_coord += 0x3F;
            }
            S8_AT(spawned_work, 0x5D) = tile_coord >> 6;
            U8_AT(spawned_sprite, 0x0E) = 0x80;
            U8_AT(spawned_sprite, 0x0D) = 0x80;
            U8_AT(spawned_sprite, 0x0C) = 0x80;
            PTR_AT(spawned_sprite, 8) = D_80077C50;
        }
    }
    if ((S16_AT(action_work, 0x96) == 0x12) || (U16_AT(sprite, 0x14) & 0x8000)) {
        U16_AT(sprite, 0x14) |= 0x800;
    }
    timer = U16_AT(action_work, 0x96) - 1;
    U16_AT(action_work, 0x96) = timer;
    if (((s32)(timer << 16) <= 0) || (U16_AT(sprite, 0x14) & 0x8000)) {
        U8_AT(action_work, 0x9B) = U8_AT(action_work, 0x9B) + 1;
        U16_AT(sprite, 0x14) &= 0xF7FF;
        goto done;
    }
    goto done;

state_2:
    if (((S8_AT(sprite, 4) == state) && (U16_AT(sprite, 0x14) & 0x1000)) ||
        (U16_AT(sprite, 0x14) & 0x8000)) {
        U16_AT(sprite, 0x14) |= 0x800;
        U16_AT(action_work, 0x96) = 0x23;
    }
    timer = U16_AT(action_work, 0x96) - 1;
    U16_AT(action_work, 0x96) = timer;
    if (((s32)(timer << 16) <= 0) || (U16_AT(sprite, 0x14) & 0x8000)) {
        U16_AT(action_work, 0x96) = 0;
        U16_AT(sprite, 0x14) &= 0xF7FF;
    }
    if (!(U16_AT(sprite, 0x14) & 0xE000)) {
        goto done;
    }
    S32_AT(position, 0x14) = 0;
    S32_AT(position, 0x10) = 0;
    S32_AT(position, 0x0C) = 0;
    func_800A2B04(position, U8_AT(sprite, 0x24), U8_AT(sprite, 0x25));
    if (PTR_AT(sprite, 0x2C) == D_80174EB8) {
        goto done;
    }
    PTR_AT(sprite, 0x2C) = D_80174EB8;
    U16_AT(sprite, 0x14) &= 0xF7FF;
    direction_index = ((D_80083228 + S16_AT(actor, 0x2A) + 0x100) >> 9) & 7;
    func_80047784(sprite, U8_AT(PTR_AT(sprite, 0x2C), direction_index), 0);
    U8_AT(action_work, 0x9B) = U8_AT(action_work, 0x9B) + 1;
    goto done;

state_3:
    if (S16_AT(action_work, 0xA4) != 0x4D) {
        func_800AD594(actor, 0x2000);
        PTR_AT(action_work, 0x8C) = &D_80171CE8;
        D_8008346C = 0;
        U16_AT(actor, 0x46) &= 0x7FFF;
    }

done:
    return;
}
