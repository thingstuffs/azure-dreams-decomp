#include "common.h"

#define FLD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void *D_80083498;
extern u8 D_80083160[];
extern u8 D_8006CCF8[];
extern s32 D_800E0334[];
extern u8 D_800C9AAC;
extern u8 D_800C9F34;
extern u8 D_80045340;

typedef struct {
    s32 f0;
    s32 f4;
    s16 f8;
    s8 fA;
} D80089430_t;
extern D80089430_t D_80089430;
/* Eleven copied bytes; the source and destination are word aligned. */
typedef struct { u8 bytes[11]; } ResultCopy __attribute__((aligned(4)));

extern void *func_8003FD64(s32 a0, void *a1);
extern u8 func_8009FB34(u8 a0, u8 a1);
extern void func_800A2B04(void *a0, u8 a1, u8 a2);
extern s16 func_800BCB04(u16 a0, u16 a1, s16 a2);
extern void func_8003DB94(void *a0, s32 a1, s32 a2);
extern void func_80099FDC(void *a0);
extern void func_800CB4C0(void *, s16);
extern void func_8004491C(void *a0, void *a1);
extern void func_800A48F0(void *a0, s32 a1, s32 a2);

/* Creates an entity at the given tile and height and initializes its sprite state. */
void *func_800C9850(u16 tile_x, u16 tile_z, u16 height) {
    u8 saved_tile_x = tile_x;
    u8 saved_tile_z = tile_z;
    void *entity;
    void *state;
    void *sprite;
    u8 *camera;
    void *state_tail;
    s32 direction_entry;
    D80089430_t *result_base;
    s32 result_word4;
    s32 tint;
    register s32 tint_arg;

    state = 0;
    entity = func_8003FD64(0x112, &D_80083498);
    if (entity != 0) {
        state = (u8 *)entity + 0x20;
        FLD(entity, void *, 0x10) = &D_800C9AAC;
        FLD(state, s8, 0x13) = 0x2f;
        state_tail = FLD(entity, void *, 8);
        FLD(state_tail, u16, 0xA) = height;
        sprite = FLD(entity, void *, 0xC);
        FLD(sprite, u8, 0x24) = saved_tile_x;
        FLD(sprite, u8, 0x25) = saved_tile_z;
        FLD(sprite, u8, 0x26) = func_8009FB34(FLD(sprite, u8, 0x24), FLD(sprite, u8, 0x25));
        func_800A2B04(state_tail, FLD(sprite, u8, 0x24), FLD(sprite, u8, 0x25));
        FLD(state, s16, 0x88) =
            func_800BCB04(FLD(state_tail, u16, 2), FLD(state_tail, u16, 6), (s16)(FLD(state_tail, u16, 0xA) - 0x20));
        FLD(sprite, s16, 0x1E) = 0x1000;
        FLD(sprite, s16, 0x1C) = 0x1000;
        FLD(sprite, s32, 0xC) = 0x2c808080;
        FLD(state, void *, 0xA4) = D_800E0334;
        FLD(sprite, void *, 0x2C) = D_800E0334;
        camera = D_80083160;
        direction_entry = ((FLD(camera, s16, 0xC8) + FLD(state, s16, 0x2A) + 0x100) >> 7) & 0x1C;
        direction_entry += (s32)FLD(state, void *, 0xA4);
        func_8003DB94(sprite, FLD((void *)direction_entry, s32, 0), 0);
        func_80099FDC(entity);
#ifdef NON_MATCHING
        result_base = &D_80089430;
#endif
        *(ResultCopy *)((u8 *)entity + 0x54) = *(ResultCopy *)&D_80089430;
        FLD(state, s32, 0x1C) |= 0x40000000;
        FLD(state, s8, 0x71) = 0;
        state_tail = state;
        {
            if (D_8006CCF8[((FLD(camera, s16, 0xC8) + FLD(state, s16, 0x2A) + 0x100) >> 9) & 7] != 0) {
                FLD(sprite, u16, 0x14) |= 1;
            } else {
                FLD(sprite, u16, 0x14) &= 0xFFFE;
            }
        }
        tint = 0x404040;
        result_word4 = (s32)(entity);
        tint_arg = 0;
        FLD(state_tail, u8, 0x9A) = 0xFF;
        FLD(state_tail, s8, 0x9C) = -1;
        FLD(state_tail, void *, 0x8C) = &D_800C9F34;
        FLD(state_tail, s16, 0xB6) = 0x10;
        FLD(state, s32, 0x1C) |= 0x40000;
        FLD(state_tail, s16, 0x92) = -0x20;
        FLD(state_tail, s32, 0xAC) = tint;
        func_800CB4C0((void *)result_word4, tint_arg);
        func_8004491C(entity, &D_80045340);
        func_800A48F0(state, 0x1B, 0);
    }
    return state;
}
