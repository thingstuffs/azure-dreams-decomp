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

extern void *func_8003FD64(s32 a0, void *a1);
extern u8 func_8009FB34(u8 a0, u8 a1);
extern void func_800A2B04(void *a0, u8 a1, u8 a2);
extern s16 func_800BCB04(u16 a0, u16 a1, s16 a2);
extern void func_8003DB94(void *a0, s32 a1, s32 a2);
extern void func_80099FDC(void *a0);
extern void func_800CB4C0(void *a0, s32 a1, s32 a2);
extern void func_8004491C(void *a0, void *a1);
extern void func_800A48F0(void *a0, s32 a1, s32 a2);

/* Creates an entity at the given tile and height and initializes its sprite state. */
void *func_800C9850(u8 tile_x, u8 tile_z, u16 height) {
    register u16 saved_height ASM_REG("$17") = height;
    register u8 saved_tile_x ASM_REG("$20") = tile_x;
    register u8 saved_tile_z ASM_REG("$21") = tile_z;
    void *entity;
    void *state;
    void *position;
    void *sprite;
    u8 *camera;
    register void *state_tail ASM_REG("$16");
    register s32 direction_entry ASM_REG("$2");
    register u8 *result_page ASM_REG("$2");
    register D80089430_t *result_base ASM_REG("$6");
    register s32 result_word0 ASM_REG("$3");
    register s32 result_word4 ASM_REG("$4");
    register s32 result_half ASM_REG("$5");
    s32 tint;
    register void *tint_entity ASM_REG("$4");
    register s32 tint_arg;

    ASM_KEEP_NV(saved_height);
    ASM_KEEP_NV(saved_tile_x);
    ASM_KEEP_NV(saved_tile_z);
    state = 0;
    entity = func_8003FD64(0x112, &D_80083498);
    if (entity != 0) {
        state = (u8 *)entity + 0x20;
        FLD(entity, void *, 0x10) = &D_800C9AAC;
        FLD(state, s8, 0x13) = 0x2f;
        position = FLD(entity, void *, 8);
        FLD(position, u16, 0xA) = saved_height;
        sprite = FLD(entity, void *, 0xC);
        FLD(sprite, u8, 0x24) = saved_tile_x;
        FLD(sprite, u8, 0x25) = saved_tile_z;
        FLD(sprite, u8, 0x26) = func_8009FB34(FLD(sprite, u8, 0x24), FLD(sprite, u8, 0x25));
        func_800A2B04(position, FLD(sprite, u8, 0x24), FLD(sprite, u8, 0x25));
        FLD(state, s16, 0x88) =
            func_800BCB04(FLD(position, u16, 2), FLD(position, u16, 6), (s16)(FLD(position, u16, 0xA) - 0x20));
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
#else
        result_page = (u8 *)0x80090000;
        ASM_KEEP_NV(result_page);
        result_base = (D80089430_t *)(result_page - 0x6BD0);
#endif
        ASM_KEEP_NV(result_base);
        result_word0 = result_base->f0;
        result_word4 = result_base->f4;
        result_half = result_base->f8;
        FLD(entity, s32, 0x54) = result_word0;
        FLD(entity, s32, 0x58) = result_word4;
        FLD(entity, s16, 0x5C) = result_half;
        {
            register s32 result_byte ASM_REG("$3");
            result_byte = result_base->fA;
            FLD(entity, s8, 0x5E) = result_byte;
        }
        FLD(state, s32, 0x1C) |= 0x40000000;
        FLD(state, s8, 0x71) = 0;
        direction_entry = ((FLD(camera, s16, 0xC8) + FLD(state, s16, 0x2A) + 0x100) >> 9) & 7;
        state_tail = state;
        {
            u32 sprite_flags;
            if (D_8006CCF8[direction_entry] != 0) {
                sprite_flags = FLD(sprite, u16, 0x14) | 1;
            } else {
                sprite_flags = FLD(sprite, u16, 0x14) & 0xFFFE;
            }
            FLD(sprite, u16, 0x14) = sprite_flags;
        }
        ASM_MEM_BARRIER();
        tint = 0x404040;
        tint_entity = entity;
        tint_arg = 0;
        ASM_KEEP4(tint, tint_entity, tint_arg, state);
        FLD(state_tail, u8, 0x9A) = 0xFF;
        FLD(state_tail, s8, 0x9C) = -1;
        FLD(state_tail, void *, 0x8C) = &D_800C9F34;
        FLD(state_tail, s16, 0xB6) = 0x10;
        FLD(state, s32, 0x1C) |= 0x40000;
        FLD(state_tail, s16, 0x92) = -0x20;
        FLD(state_tail, s32, 0xAC) = tint;
        func_800CB4C0(tint_entity, tint_arg, tint);
        func_8004491C(entity, &D_80045340);
        func_800A48F0(state, 0x1B, 0);
    }
    return state;
}
