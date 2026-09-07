#include "common.h"

typedef struct S_8017427C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017427C_0;   /* arg0 in func_8017427C */

typedef struct S_8017427C_1 {
    u8 pad_00[0xC];
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017427C_1;   /* arg2 in func_8017427C */

typedef struct S_8017427C_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0x8];
    u8 unk_28;
} S_8017427C_2;   /* arg3 in func_8017427C */

typedef struct S_8017427C_3 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8017427C_3;   /* counter in func_8017427C */

typedef struct S_8017427C_4 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8017427C_4;   /* D_800E3D7C + index * 4 in func_8017427C */



extern s8 func_80042518(void *, s32);
extern s32 func_80042900(void *, s32);
extern void func_8004491C(void *, void *);
extern void func_80044A50(void *);
extern void func_800956B8(void *, void *, void *, s32);
extern void func_8009A21C(u8, u8, s32);
extern s32 func_800A1BD0(void *);
extern void func_800A48F0(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_80174B90(void *, void *, void *, void *);

extern s32 D_80045340;
extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80083780[];
extern s32 D_800C6AEC;
extern u8 *D_800E3D7C;
extern u8 D_80170EE4[];
extern u8 D_80176640[];

/* Advances an actor's fade-in sequence and applies its completion updates. */
void func_8017427C(void *actor_state, void *context, S_8017427C_1 *sprite, void *actor_data) {
    void *actor_base;
    s32 actor_flags;
    s32 entry_index;
    s32 tile_mask;
    u8 brightness;
    u8 fade_delay;
    u8 state;
    u8 tile_x;
    u8 tile_y;
    s16 fade_ticks;
    u16 *global_state;

    state = ((S_8017427C_0 *)actor_state)->unk_9B;
    switch (state) {
    case 0:
        actor_base = (u8 *)actor_state - 0x20;
        ((S_8017427C_0 *)actor_state)->unk_96.s = 0x10;
        func_8004491C(actor_base, &D_800C6AEC);
        sprite->unk_0C.at00.v = 0x08000000;
        sprite->unk_10 = 0x20;
        sprite->unk_12 -= 0x80;
        sprite->unk_14 |= 0xC;
        ((S_8017427C_2 *)actor_data)->unk_1C.u |= 0x40000000;
        ((S_8017427C_0 *)actor_state)->unk_9B++;
        /* fall through */

    case 1:
        fade_ticks = ((S_8017427C_0 *)actor_state)->unk_96.s;
        if (fade_ticks == 0) {
            goto advance_state;
        }
        brightness = sprite->unk_0C.at00u.v;
        brightness += (0x80 - brightness) / fade_ticks;
        sprite->unk_0C.at00u.v = brightness;
        sprite->unk_0C.at02.v = brightness;
        sprite->unk_0C.at01.v = brightness;
        ((S_8017427C_0 *)actor_state)->unk_96.u--;
        break;

    case 2:
        actor_base = (u8 *)actor_state - 0x20;
        fade_delay = sprite->unk_0C.at03.v;
        if (fade_delay >= 2) {
            sprite->unk_0C.at03.v = fade_delay - 1;
            break;
        }
        func_80044A50(actor_base);
        func_8004491C(actor_base, &D_80045340);
        sprite->unk_0C.at00.v = 0x00808080;
        sprite->unk_10 = 0;
        sprite->unk_12 += 0x80;
        sprite->unk_14 &= 0xFFF3;
        func_80174B90(actor_base, (u8 *)actor_data + 0x2A,
                      (u8 *)actor_state + 0x9A, (u8 *)actor_state + 0x98);
advance_state:
        ((S_8017427C_0 *)actor_state)->unk_9B++;
        break;

    case 3:
        ((S_8017427C_0 *)actor_state)->unk_8C = D_80170EE4;
        actor_flags = ((S_8017427C_2 *)actor_data)->unk_1C.s;
        ((S_8017427C_2 *)actor_data)->unk_1C.s = actor_flags & 0xEFFFFFFF;
        if (!(((S_8017427C_2 *)actor_data)->unk_1C.s & 0x00400000)) {
            tile_x = sprite->unk_24;
            tile_y = sprite->unk_25;
            tile_mask = 0x3000;
            if (actor_flags & 0x2000) {
                tile_mask = 0x300;
            }
            func_8009A21C(tile_x, tile_y, tile_mask);
        }
        global_state = (u16 *)&D_80083460;
        global_state[5]--;
        if (((S_8017427C_2 *)actor_data)->unk_28 == 0) {
            ((S_8017427C_3 *)global_state)->unk_10 = (u8 *)actor_data - 0x20;
            func_800AAA54(actor_state, context, sprite, D_80176640);
            break;
        }
        if ((((S_8017427C_2 *)actor_data)->unk_14 & 0x4000) &&
            (((S_8017427C_2 *)actor_data)->unk_1C.s & 0x10000)) {
            entry_index = (s16)func_800A1BD0(actor_data);
            if (entry_index < 0) {
                break;
            }
            func_800956B8(D_800E3D7C, D_80083780, D_80082E80,
                          ((S_8017427C_4 *)(D_800E3D7C + entry_index * 4))->unk_D0);
            ((S_8017427C_2 *)actor_data)->unk_1C.s &= 0xFFFEFFFF;
            break;
        }
        if ((func_80042900(actor_data, 0xA) << 0x10) != 0) {
            func_800A48F0(actor_data, 0xA, func_80042518(actor_data, 0xA));
        }
        break;
    }
}
