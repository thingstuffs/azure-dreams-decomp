#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, u8 *, s32, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

extern u8 D_80045340;
extern u8 D_80099B18[];
extern u8 D_800DE870[];
extern s32 D_800DEDB0[3];
extern M2C_UNK D_800DEE38;


typedef struct S_80099C58_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80099C58_0;   /* obj in func_80099C58 */

typedef struct S_80099C58_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80099C58_1;   /* s1 in func_80099C58 */

typedef struct S_80099C58_2 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80099C58_2;   /* s2 in func_80099C58 */

typedef struct S_80099C58_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80099C58_3;   /* v1 in func_80099C58 */

/* Spawns a central particle and sixteen particles moving radially from the given position. */
void func_80099C58(s16 x, s16 y, s16 z, s16 flags)
{
    void *particle;
    S_80099C58_1 *motion;
    S_80099C58_2 *effect_state;
    void *sprite;
    S_80099C58_3 *texture_data;
    void *texture;
    s32 spokes_left;
    s32 angle;
    s32 color;

    particle = func_8003FC64(0x212);
    if (particle != NULL) {
        effect_state = (s8 *)particle + 0x20;
        motion = ((S_80099C58_0 *)particle)->unk_08;
        ((S_80099C58_0 *)particle)->unk_10 = D_80099B18;
        motion->unk_02 = x;
        effect_state->unk_12 = x;
        motion->unk_06 = y;
        effect_state->unk_14 = y;
        motion->unk_0A = z;
        effect_state->unk_16 = z;
        effect_state->unk_10 = 0;
        sprite = ((S_80099C58_0 *)particle)->unk_0C;
        if (flags & 2) {
            texture = D_800DEDB0;
        } else if (flags & 4) {
            texture = &D_800DEE38;
        } else {
            texture = D_800DE870;
        }
        (*(void **)((u8 *)sprite + 0)) = texture;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        color = 0x808080;
        ASM_KEEP(color);   /* MATCH pin: retail immediate-load split depends on it */
        texture_data = (*(void * volatile *)((u8 *)sprite + 0));
        texture_data = texture_data->unk_04;
        (*(u16 *)((u8 *)sprite + 0x14)) |= 0x8C;
        (*(s16 *)((u8 *)sprite + 0x10)) = 0x20;
        (*(s32 *)((u8 *)sprite + 0xC)) = color;
        (*(s16 *)((u8 *)sprite + 0x1E)) = 0x1000;
        (*(s16 *)((u8 *)sprite + 0x1C)) = 0x1000;
        (*(void **)((u8 *)sprite + 8)) = texture_data;
        func_8004491C(particle, &D_80045340, color, sprite);
    }

    for (spokes_left = 0x10; spokes_left > 0; spokes_left--) {
        particle = func_8003FC64(0x212);
        if (particle != NULL) {
            effect_state = (s8 *)particle + 0x20;
            angle = spokes_left << 8;
            motion = ((S_80099C58_0 *)particle)->unk_08;
            ((S_80099C58_0 *)particle)->unk_10 = D_80099B18;
            effect_state->unk_0E = 1;
            motion->unk_02 = x;
            effect_state->unk_12 = x;
            motion->unk_06 = y;
            effect_state->unk_14 = y;
            motion->unk_0A = z;
            effect_state->unk_16 = z;
            motion->unk_14 = func_80064584(angle) << 7;
            motion->unk_0C = func_800644B8(angle) << 7;
            effect_state->unk_10 = 0;
            sprite = ((S_80099C58_0 *)particle)->unk_0C;
            if (flags & 2) {
                texture = D_800DEDB0;
            } else if (flags & 4) {
                texture = &D_800DEE38;
            } else {
                texture = D_800DE870;
            }
            (*(void **)((u8 *)sprite + 0)) = texture;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            color = 0x808080;
            ASM_KEEP(color);   /* MATCH pin: retail immediate-load split depends on it */
            texture_data = (*(void * volatile *)((u8 *)sprite + 0));
            texture_data = texture_data->unk_04;
            (*(u16 *)((u8 *)sprite + 0x14)) |= 0x8C;
            (*(s16 *)((u8 *)sprite + 0x10)) = 0x20;
            (*(s32 *)((u8 *)sprite + 0xC)) = color;
            (*(s16 *)((u8 *)sprite + 0x1E)) = 0x1000;
            (*(s16 *)((u8 *)sprite + 0x1C)) = 0x1000;
            (*(void **)((u8 *)sprite + 8)) = texture_data;
            func_8004491C(particle, &D_80045340, color, sprite);
        }
    }
}
