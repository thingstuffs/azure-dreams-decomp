#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B8228_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800B8228_0;   /* temp_v0 in func_800B8228 */

typedef struct S_800B8228_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_800B8228_1;   /* temp_v1 in func_800B8228 */

typedef struct S_800B8228_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800B8228_2;   /* temp_s0 in func_800B8228 */

typedef struct S_800B8228_3 {
    u8 pad_00[0xB0];
    s16 unk_B0;
    s16 unk_B2;
} S_800B8228_3;   /* temp_v1_2 in func_800B8228 */


typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;


extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_800A56E0(s32);
extern s32 func_800A7A38(void *, s32);
extern void func_800A7A7C(s32, s32, s32, void *, void *);
extern void func_800BC26C(void *, s32, s32, s32);

extern u8 D_80045340[];
extern u8 D_8006E240[9];
extern u8 D_800B80D8[];

/* Creates and initializes an effect, or invokes its fallback if allocation fails. */
void *func_800B8228(u32 x, u32 y, s32 z, void *effect_data) {
    S_800B8228_2 *appearance;
    void *effect;
    S_800B8228_1 *position;
    S_800B8228_3 *grid_position;

    effect = func_8003FC64(0x12);
    if (effect == NULL)
        goto failure;

    {
        func_8004491C(effect, D_80045340);
        ((S_800B8228_0 *)effect)->unk_10 = D_800B80D8;
        position = ((S_800B8228_0 *)effect)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        position->unk_16 = -0x12;
        appearance = ((S_800B8228_0 *)effect)->unk_0C;
        appearance->unk_0C = 0x808080;
        appearance->unk_1E = 0xC90;
        appearance->unk_1C = 0xC90;
        appearance->unk_08 = func_800A7A38(effect_data, appearance->unk_0C);
        grid_position = (u8 *)effect + 0x20;
        grid_position->unk_B0 = x >> 6;
        grid_position->unk_B2 = y >> 6;
        *(PackedWord *)((u8 *)effect + 0xB8) = *(PackedWord *)effect_data;
        func_800BC26C(effect, 0, 0, 0);
        func_800A56E0(0x51C);
    }

    goto done;

failure:
    func_800A7A7C((s32)(x << 0xA) >> 0x10,
                  (s32)(y << 0xA) >> 0x10,
                  (s32)(z << 0x10) >> 0x10,
                  D_8006E240, effect_data);

done:
    return effect;
}
