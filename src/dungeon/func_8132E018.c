#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80165018_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80165018_0;   /* obj in func_80165018 */


typedef struct S_80165018_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80165018_2;   /* state in func_80165018 */

typedef struct S_80165018_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80165018_3;   /* pos in func_80165018 */

typedef struct S_80165018_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80165018_4;   /* tail in func_80165018 */

typedef struct S_80165018_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80165018_5;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80165018 */

typedef struct S_80165018_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80165018_6;   /* ((S_80165018_0 *)obj)->unk_08 in func_80165018 */

typedef struct S_80165018_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
} S_80165018_7;   /* ((S_80165018_0 *)obj)->unk_0C in func_80165018 */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80164BC4[];
extern u8 D_80164DA4[];


/* Create an effect at a randomized offset from its parent and initialize its state. */
void func_80165018(Rec_D_800E3D7C *parent, s32 effect_value, s16 effect_size, s32 offset_x, s32 offset_y,
                   s32 offset_z) {
    register s32 saved_offset_y ASM_REG("$19") = offset_y;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 saved_offset_z ASM_REG("$20") = offset_z;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *effect;
    S_80165018_2 *state;
    S_80165018_4 *effect_data;
    S_80165018_3 *transform;
    register s32 jitter ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 coordinate ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    effect = func_8003FD64(0x211, parent);
    if (effect != 0) {
        ((S_80165018_0 *)effect)->unk_10 = D_80164DA4;
        jitter = rand() & 7;
        coordinate = ((S_80165018_5 *)(parent->unk_08.at00_pv.v))->unk_02 + offset_x;
        coordinate -= 3;
        coordinate += jitter;
        ((S_80165018_6 *)(((S_80165018_0 *)effect)->unk_08))->unk_02 = (s16)coordinate;
        jitter = rand() & 7;
        coordinate = ((S_80165018_5 *)(parent->unk_08.at00_pv.v))->unk_06 + saved_offset_y;
        coordinate -= 3;
        coordinate += jitter;
        ((S_80165018_6 *)(((S_80165018_0 *)effect)->unk_08))->unk_06 = (s16)coordinate;
        jitter = rand() & 7;
        coordinate = ((S_80165018_5 *)(parent->unk_08.at00_pv.v))->unk_0A + saved_offset_z;
        coordinate -= 3;
        coordinate += jitter;
        ((S_80165018_6 *)(((S_80165018_0 *)effect)->unk_08))->unk_0A = (s16)coordinate;
        ((S_80165018_7 *)(((S_80165018_0 *)effect)->unk_0C))->unk_06 = 0;
        state = ((S_80165018_0 *)effect)->unk_0C;
        effect_data = (u8 *)effect + 0x20;
        state->unk_14 = state->unk_14 | 0xC;
        ((S_80165018_7 *)(((S_80165018_0 *)effect)->unk_0C))->unk_10 = 0x20;
        transform = ((S_80165018_0 *)effect)->unk_08;
        transform->unk_14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        effect_data->unk_32 = effect_size;
        effect_data->unk_34 = effect_size;
        func_8004491C(effect, D_80164BC4);
        ((S_80165018_0 *)effect)->unk_20 = effect_value;
        effect_data->unk_08 = effect_value;
    }
}

/* MECHANISM: s3/s4 stack-argument holds reproduce the 0x30 frame and seven-register save set.
   Pinned v0 RNG plus pinned v1 compound accumulation preserves all three coordinate sequences.
   One cached obj+8 pointer collapses the three zero stores to retail's single-load form. */
