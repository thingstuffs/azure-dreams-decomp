#include "common.h"
#include "records/Rec_func_800247B8_arg0.h"

#define UNALIGNED32(expr) (expr)

typedef struct {
    u8 bytes[12];
} Block12;

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern s32 D_800D4954;
extern Block12 D_800E233C;


typedef struct S_800D4AB0_0 {
    u8 pad_00[0x5A];
    s16 unk_5A;
    s16 unk_5C;
    u8 pad_5E[0x2A];
    void * unk_88;
} S_800D4AB0_0;   /* temp_v1 in func_800D4AB0 */


typedef struct S_800D4AB0_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800D4AB0_2;   /* temp_a3 in func_800D4AB0 */

typedef struct S_800D4AB0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D4AB0_3;   /* temp_a0 in func_800D4AB0 */

typedef struct S_800D4AB0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D4AB0_4;   /* temp_v1_2 in func_800D4AB0 */

typedef struct S_800D4AB0_5_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800D4AB0_5_pre;   /* the 0x18 bytes before ((Rec_func_800247B8_arg0 *)arg0)->unk_88 in func_800D4AB0, addressed as ((Rec_func_800247B8_arg0 *)arg0)->unk_88[-1] */

/* Creates an effect linked to the owner with an offset position and initialized render data. */
void func_800D4AB0(Rec_func_800247B8_arg0 *owner) {
    S_800D4AB0_3 *position;
    S_800D4AB0_2 *render_data;
    void *effect;
    S_800D4AB0_0 *effect_state;
    S_800D4AB0_4 *source_position;

    effect = func_8003FC64(0x12);
    effect_state = effect + 0x20;
    if (effect != 0) {
        effect_state->unk_5A = 0x78;
        effect_state->unk_5C = 0x78;
        effect_state->unk_88 = owner->unk_88;
        (*(s32 * *)((u8 *)effect + 0x10)) = &D_800D4954;
        func_8004491C(effect, &D_80045340);
        render_data = (*(void * *)((u8 *)effect + 0xC));
        render_data->unk_10 = 0x60;
        render_data->unk_06 = 0;
        render_data->unk_14 = render_data->unk_14 | 0xC;
        source_position = ((S_800D4AB0_5_pre *)(owner->unk_88))[-1].unk_00;
        position = (*(void * *)((u8 *)effect + 0x8));
        position->unk_02 = source_position->unk_02;
        position->unk_06 = source_position->unk_06;
        position->unk_0A = source_position->unk_0A - 0x32;
        render_data = (*(void * *)((u8 *)effect + 0xC));
        render_data->unk_0E = 0x80;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        render_data->unk_1E = 0;
        render_data->unk_1C = 0;
        (*(Block12 *)((u8 *)effect + 0x96)) = D_800E233C;
        render_data->unk_08 = effect + 0x96;
    }
}
