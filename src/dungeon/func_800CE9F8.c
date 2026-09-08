#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef void (*Func4)(void *, void *, void *, void *);
extern u16 D_80083462[5];
extern Func4 D_800E22E0[];
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 func_800BCB04();


typedef struct S_800D4158_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D4158_1;   /* arg1 in func_800D4158 */

typedef struct S_800D4158_2 {
    u8 pad_00[0x90];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x3];
    union { u8 u; s8 s; } unk_9D;   /* accessed as both */
    u16 unk_9E;
} S_800D4158_2;   /* arg0 in func_800D4158 */

/* Updates entity callbacks, motion, ground contact, and sprite brightness. */
void func_800D4158(void *entity, S_800D4158_1 *motion, Rec_D_80082E80 *sprite) {
    void *entity_ref = entity;
    u16 motion_flags;
    u32 entity_flags;
    s16 ground_height;
    s32 ground_height_raw;
    s16 pulse_phase;
    s32 brightness;

    if (*D_80083462 & 0x2000) {
        (*(u8 *)((u8 *)entity_ref + 0x71)) = (*(u8 *)((u8 *)entity_ref + 0x71)) & 0x7f;
        goto epilogue;
    }
    if ((*(Func4 *)((u8 *)entity_ref + 0x8c)) != NULL) {
        ((Func4)(*(Func4 *)((u8 *)entity_ref + 0x8c)))(entity_ref, motion, sprite, entity_ref);
    }
    D_800E22E0[(*(u8 *)((u8 *)entity_ref + 0x9a))](entity_ref, motion, sprite, entity_ref);
    if (!(sprite->unk_14.at00_u16.v & 0x8000)) {
        if (!(sprite->unk_14.at00_u16.v & 0x40)) {
            func_800478B8(sprite);
        }
    }
    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;
    motion_flags = ((S_800D4158_2 *)entity)->unk_98;
    if (motion_flags & 8) {
        ((S_800D4158_2 *)entity)->unk_9D.u = 0;
        goto apply_vertical_motion;
    }
    motion->unk_14 += ((S_800D4158_2 *)entity)->unk_9D.s * 0x14000;
    ((S_800D4158_2 *)entity)->unk_9D.s = ((S_800D4158_2 *)entity)->unk_9D.u + 1;
apply_vertical_motion:
    ((S_800D4158_2 *)entity)->unk_90.at00.v += motion->unk_14;
    if (((S_800D4158_2 *)entity)->unk_98 & 4) {
        goto clear_grounded;
    }
    ground_height_raw = func_800BCB04(motion->unk_00.at02.v, motion->unk_04.at02.v,
                        (s16)((*(u16 *)((u8 *)entity_ref + 0x88)) - 0x20));
    ground_height = (s16)ground_height_raw;
    if (ground_height >= 0x200) {
        goto clear_grounded;
    }
    if (((S_800D4158_2 *)entity)->unk_90.at02.v + (*(s16 *)((u8 *)entity_ref + 0x88)) < ground_height) {
        (void)*(volatile u16 *)((s8 *)entity + 0x98);
        goto check_base_height;
    }
    if (ground_height >= (*(s16 *)((u8 *)entity_ref + 0x88))) {
        ((S_800D4158_2 *)entity)->unk_90.at00.v = 0;
    } else {
        ((S_800D4158_2 *)entity)->unk_90.at02.v = ground_height_raw - (*(u16 *)((u8 *)entity_ref + 0x88));
    }
    motion->unk_14 = 0;
    (*(s32 *)((u8 *)entity_ref + 0x1c)) |= 0x08000000;
    ((S_800D4158_2 *)entity)->unk_9D.s = 0;
check_base_height:
    entity_flags = (*(u32 *)((u8 *)entity_ref + 0x1c));
    if (entity_flags & 0x40000000) {
        (*(u32 *)((u8 *)entity_ref + 0x1c)) = entity_flags & 0xbfffffff;
        ground_height_raw = func_800BCB04(
            (sprite->unk_24 << 6) | 0x20,
            (sprite->unk_25 << 6) | 0x20,
            (s16)((*(u16 *)((u8 *)entity_ref + 0x88)) - 0x20));
        ((S_800D4158_2 *)entity)->unk_90.at02.v += (*(u16 *)((u8 *)entity_ref + 0x88)) - ground_height_raw;
        (*(s16 *)((u8 *)entity_ref + 0x88)) = ground_height_raw;
    }
    goto update_height;
clear_grounded:
    (*(u32 *)((u8 *)entity_ref + 0x1c)) &= 0xf7ffffff;
update_height:
    motion->unk_0A = (*(u16 *)((u8 *)entity_ref + 0x88)) +
                                   ((S_800D4158_2 *)entity)->unk_90.at02.v;
update_brightness:
    pulse_phase = ((S_800D4158_2 *)entity)->unk_9E;
    pulse_phase++;
    pulse_phase %= 96;
    ((S_800D4158_2 *)entity)->unk_9E = pulse_phase;
    if ((s16)pulse_phase < 0x19) {
        brightness = (func_800644B8((s16)pulse_phase * 0x55) >> 4) * 0x60;
        brightness = (brightness >> 8) + 0x80;
        sprite->unk_0C.at02_u8.v = brightness;
        sprite->unk_0C.at01_u8.v = brightness;
        sprite->unk_0C.at00_u8.v = brightness;
    } else {
        sprite->unk_0C.at02_u8.v = 0x80;
        sprite->unk_0C.at01_u8.v = 0x80;
        sprite->unk_0C.at00_u8.v = 0x80;
    }
    sprite->unk_14.at00_u16.v |= 0x40;
    (*(u32 *)((u8 *)entity_ref + 0x1c)) |= 0x200;
epilogue:
    return;
}
