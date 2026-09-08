#include "common.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct {
    s32 words[3];
} TableEntry;

extern s32 func_80026ED0();
extern s32 func_80027368();
extern s32 func_8003DE58();
extern void *func_8003FD64();
extern s32 func_8004491C();

extern s32 D_80026680[3];
extern TableEntry D_80028820[];
extern s32 D_80083498[3];
extern s32 D_800CEEFC[3];
extern u8 D_800DDC40[9];



typedef struct S_80026A84_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80026A84_1;   /* temp_v0 in func_80026A84 */

typedef struct S_80026A84_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80026A84_2;   /* arg0 in func_80026A84 */

typedef struct S_80026A84_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80026A84_3;   /* temp_a2 in func_80026A84 */

typedef struct S_80026A84_4 {
    u8 pad_00[0x8];
    TableEntry * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026A84_4;   /* temp_a0 in func_80026A84 */

typedef struct S_80026A84_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    u8 pad_0C[0x5A];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
} S_80026A84_5;   /* temp_a3 in func_80026A84 */

typedef struct S_80026A84_6 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
} S_80026A84_6;   /* var_a1 in func_80026A84 */

typedef struct S_80026A84_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80026A84_7;   /* arg1 in func_80026A84 */

/* Creates six linked effects at an offset from the origin and initializes their points. */
void *func_80026A84(S_80026A84_2 *origin, S_80026A84_7 *target_pos, s32 effect_param, Rec_D_80082E80 *source)
{
    u16 offset[3];
    s32 *callback;
    TableEntry *effect_entry;
    s32 effect_index;
    s32 point_index;
    u16 coord_xz;
    u16 coord_y;
    register void *render_data ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_80026A84_3 *effect_pos;
    S_80026A84_5 *effect_data;
    void *effect;
    register void *point_cursor ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *chain_head;

    chain_head = NULL;
    offset[0] = offset[1] = 0;
    if (func_8003DE58(source->unk_08, source, offset, 0) == 0) {
        offset[2] = (0 - D_800DDC40[0]) + 0x10;
    }
    callback = D_80026680;
    effect_index = 0;
    do { effect_entry = D_80028820; } while (0);
    do {
        effect = func_8003FD64(0x12, D_80083498);
        if (effect != NULL) {
            ((S_80026A84_1 *)effect)->unk_10 = callback;
            func_8004491C(effect, D_800CEEFC);
            effect_pos = ((S_80026A84_1 *)effect)->unk_08;
            coord_xz = origin->unk_02 + offset[0];
            effect_pos->unk_02 = coord_xz;
            effect_pos->unk_0E = coord_xz;
            point_index = 0;
            coord_y = origin->unk_06 + offset[1];
            effect_pos->unk_06 = coord_y;
            effect_pos->unk_12 = coord_y;
            effect_data = effect + 0x20;
            coord_xz = origin->unk_0A + offset[2];
            effect_pos->unk_0A = coord_xz;
            effect_pos->unk_16 = coord_xz;
            render_data = ((S_80026A84_1 *)effect)->unk_0C;
            point_cursor = effect_data;
            ((S_80026A84_4 *)render_data)->unk_1E = 0x1000;
            ((S_80026A84_4 *)render_data)->unk_1C = 0x1000;
            ((S_80026A84_4 *)render_data)->unk_08 = effect_entry;
            ((S_80026A84_4 *)render_data)->unk_14 = ((S_80026A84_4 *)render_data)->unk_14 | 0xC;
            ((S_80026A84_1 *)effect)->unk_20 = target_pos;
            effect_data->unk_04 = effect_param;
            effect_data->unk_66 = 0x20;
            effect_data->unk_6E = effect_index;
            do {
                ((S_80026A84_6 *)point_cursor)->unk_24 = effect_pos->unk_02;
                ((S_80026A84_6 *)point_cursor)->unk_26 = effect_pos->unk_06;
                point_index += 1;
                ((S_80026A84_6 *)point_cursor)->unk_28 = effect_pos->unk_0A;
                point_cursor += 8;
            } while (point_index < 8);
            effect_data->unk_08 = chain_head;
            chain_head = effect;
        }
        effect_index += 1;
        effect_entry += 1;
    } while (effect_index < 6);
    func_80026ED0((s16)(origin->unk_02 + offset[0]),
                  (s16)(origin->unk_06 + offset[1]),
                  (s16)(origin->unk_0A + offset[2]), 0x800);
    func_80027368(target_pos->unk_02, target_pos->unk_06,
                  target_pos->unk_0A, effect_param);
    return effect;
}
