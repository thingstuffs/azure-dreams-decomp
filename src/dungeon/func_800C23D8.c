#include "common.h"

/* Entity transition state */
typedef struct Entity {
    u8    pad0[0xC];
    void *unkC;      /* 0x0C -> Sub */
    s32   unk10;     /* 0x10 */
    u8    pad14[4];
    s32   unk18;     /* 0x18 state selector */
    u8    pad1C[8];
    s16   unk24;     /* 0x24 countdown */
    u16   unk26;     /* 0x26 */
} Entity;

typedef struct Sub {
    u8  pad0[2];
    s16 f2;   /* 0x02 */
    u8  pad4[2];
    s16 f6;   /* 0x06 */
    u8  pad8[2];
    s16 fA;   /* 0x0A */
} Sub;

/* View over the D_80083178 dispatch/blend record (fields not in game.h struct) */
typedef struct G {
    u8  pad0[0x98];
    s16 f98;   /* 0x98 */
    u8  pad9a[0xA4 - 0x9A];
    s16 fA4;   /* 0xA4 */
    s16 fA6;   /* 0xA6 */
    s16 fA8;   /* 0xA8 */
    u8  padAA[2];
    s16 fAC;   /* 0xAC */
    u8  padAE[2];
    s16 fB0;   /* 0xB0 */
} G;

extern s16 D_800120A2;
extern s16 D_800DD264[];
extern s32 D_800E3D7C[];
extern u16 D_80083460[];
extern u8  D_80083780[];
extern s16 D_800DCE66[5];

extern void func_800C77D0(void *a0, void *a1, s32 a2, s16 a3);

/* Blend toward the entity target, then dispatch the next state. */
void func_800C7B38(void *entity_data) {
    Entity *entity = entity_data;
    G *blend = (G *)&D_80083178;
    s32 state = entity->unk18;

    if (state == 0) goto blend_state;
    if (state == 1) goto dispatch_state;
    return;

blend_state:
    if (entity->unk24 > 0) {
        s16 half_ticks;
        entity->unk10 -= entity->unk10 >> 2;
        blend->f98 = entity->unk26 + (u16)entity->unk10;
        blend->fAC = (u16)blend->fAC + (D_800DD264[D_800120A2] - blend->fAC) / entity->unk24;
        blend->fB0 = (u16)blend->fB0 + (0 - blend->fB0) / entity->unk24;
        blend->fA4 = (u16)blend->fA4 + (((Sub *)entity->unkC)->f2 - blend->fA4) / entity->unk24;
        blend->fA6 = (u16)blend->fA6 + (((Sub *)entity->unkC)->f6 - blend->fA6) / entity->unk24;
        half_ticks = (s16)(u16)entity->unk24 / 2;
        if (half_ticks != 0) {
            blend->fA8 = (u16)blend->fA8 + (((Sub *)entity->unkC)->fA - blend->fA8) / half_ticks;
        }
        {
            s16 ticks_left = (u16)entity->unk24 - 1;
            entity->unk24 = ticks_left;
            if (ticks_left > 0) {
                return;
            }
        }
    }
    blend->fAC = (u16)D_800DD264[D_800120A2];
    blend->fB0 = 0;
    blend->f98 = entity->unk26;
    entity->unk18 += 1;
    return;

dispatch_state:
    func_800C77D0((void *)(D_800E3D7C[0] - 0x20), D_80083780, 8, D_800DCE66[0]);
    D_80083460[5] = D_80083460[5] - 1;
}
