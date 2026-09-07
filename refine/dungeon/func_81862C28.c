#include "common.h"

typedef struct S_81862C28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} S_81862C28_0;   /* temp_v0 in func_81862C28 */

typedef struct S_81862C28_1 {
    u8 unk_00;
    u8 pad_01[0x1];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81862C28_1;   /* temp_s0 in func_81862C28 */

typedef struct S_81862C28_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_81862C28_2;   /* held_arg1 in func_81862C28 */



extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void func_80024694(void) __attribute__((noreturn));
extern void func_800246A4(void) __attribute__((noreturn));
extern s32 func_800A45D8(s32, s32, s16);
extern u16 func_800BCAD0(void *);

extern void func_80024374(void);
extern u8 D_80045340[];
extern u8 D_800DE9D0[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

/* Creates an effect at the origin or in unblocked directions at the given radius. */
void func_81862C28(s32 effect_param, void *origin_arg, s32 radius_arg, u8 *blocked_dirs) {
    register void *origin ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 radius;
    s16 target_y;
    s16 target_x;
    s32 source_y;
    s32 source_x;
    register s32 radius_reg ASM_REG("$6");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 direction;
    register void *x_step ASM_REG("$21");   /* MATCH pin: retail register colouring depends on it */
    register u8 *page_8007 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    S_81862C28_1 *effect_data;
    S_81862C28_0 *effect;
    s32 tile_x;
    s32 tile_dy;
    s32 table_offset;
    s16 origin_z;

    origin = origin_arg;
    ASM_KEEP_NV(origin);   /* MATCH pin: retail schedule: same instructions, different order without it */
    radius = radius_reg;
    radius_reg <<= 0x10;
    if (radius_reg == 0) {
        effect = func_8003FC64(0x212);
        if (effect != 0) {
            effect_data = effect->unk_0C;
            effect->unk_10 = func_80024374;
            effect->unk_20 = effect_param;
            effect->unk_24 = 0;
            effect_data->unk_0E = 0x80;
            effect_data->unk_0D = 0x80;
            effect_data->unk_0C = 0x80;
            func_8003DB94(effect_data, D_800DE9D0, 0);
            effect_data->unk_1C = 0x1000;
            effect_data->unk_1E = 0x3000;
            effect_data->unk_12 = 0x7E0B;
            effect_data->unk_10 |= 0x20;
            effect_data->unk_14 |= 0x10C;
            func_8004491C(effect, D_80045340);
            effect_data = effect->unk_08;
            effect_data->unk_02.s = ((S_81862C28_2 *)origin)->unk_02.s;
            effect_data->unk_06.s = ((S_81862C28_2 *)origin)->unk_06.s;
            effect_data->unk_0A = ((S_81862C28_2 *)origin)->unk_0A.s;
            func_800246A4();
        }
    } else {
        direction = 0;
        page_8007 = (u8 *)0x80070000;
        ASM_KEEP(page_8007);   /* MATCH pin: load-bearing for the whole function shape */
        x_step = page_8007 - 0x3328;
next_direction:
        effect_data = blocked_dirs + direction;
        if (effect_data->unk_00 == 0) {
            source_x = ((S_81862C28_2 *)origin)->unk_02.u;
            if (source_x < 0) {
                source_x += 0x3F;
            }
            tile_x = (source_x >> 6) + (*(u16 *)x_step * radius);
            table_offset = direction << 1;
            source_y = ((S_81862C28_2 *)origin)->unk_06.u;
            if (source_y < 0) {
                source_y += 0x3F;
            }
            tile_dy = *(u16 *)((u8 *)D_8006CCE8 + table_offset) * radius;
            origin_z = ((S_81862C28_2 *)origin)->unk_0A.u;
            target_x = ((tile_x << 0x10) >> 0xA) + 0x20;
            target_y = ((((source_y >> 6) + tile_dy) << 0x10) >> 0xA) + 0x20;
            if ((func_800A45D8(target_x & 0xFFE0, target_y & 0xFFE0, origin_z) << 0x10) != 0) {
                effect_data->unk_00 = 1;
                func_80024694();
            }
            effect = func_8003FC64(0x212);
            if (effect != 0) {
                effect_data = effect->unk_0C;
                effect->unk_10 = func_80024374;
                effect->unk_20 = effect_param;
                effect->unk_24 = 0;
                effect_data->unk_0E = 0x40;
                effect_data->unk_0D = 0x40;
                effect_data->unk_0C = 0x40;
                func_8003DB94(effect_data, D_800DE9D0, 0);
                effect_data->unk_1C = 0x1000;
                effect_data->unk_1E = 0x1800;
                effect_data->unk_12 = 0x7E0B;
                effect_data->unk_10 |= 0x20;
                effect_data->unk_14 |= 0x10C;
                func_8004491C(effect, D_80045340);
                effect_data = effect->unk_08;
                effect_data->unk_02.u = target_x;
                effect_data->unk_06.u = target_y;
                effect_data->unk_0A = ((S_81862C28_2 *)origin)->unk_0A.s;
                effect_data->unk_0A = func_800BCAD0(effect_data);
            }
        }
        direction += 1;
        x_step += 2;
        if (direction < 8) {
            goto next_direction;
        }
    }
}
