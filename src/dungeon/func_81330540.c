#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80167540_0 {
    u16 unk_00;
    u8 pad_02[0x18];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80167540_0;   /* arg0 in func_80167540; pointer addresses record offset 0x2 */



/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0[3];
s32 rand();                   /* extern */
s16 func_80167088();                         /* extern */

/* Scale effect channels by remaining lifetime, randomize flags, and mark expiration. */
void func_80167540(void *effect_data, void *unused, Rec_D_80082E80 *effect) {
    s16 selected_channel;
    s32 channel_1_scale;
    s32 channel_2_scale;
    s32 channel_0_scale;

    selected_channel = func_80167088(3);
    channel_2_scale = 0x20;
    channel_1_scale = 0x20;
    ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1E = selected_channel;
    channel_0_scale = 0x20;
    if (selected_channel == 0) {
        channel_0_scale = 0x50;
    }
    if (selected_channel == 1) {
        channel_1_scale = 0x50;
    }
    if (selected_channel == 2) {
        channel_2_scale = 0x50;
    }
    effect->unk_0C.at00_s8.v = (s8) ((s32) (channel_0_scale * ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1C);
    effect->unk_0C.at01_s8.v = (s8) ((s32) (channel_1_scale * ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1C);
    effect->unk_0C.at02_s8.v = (s8) ((s32) (channel_2_scale * ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1C);
    ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1A = (s16) ((u16) ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1A - 1);
    if (rand(selected_channel, channel_1_scale, channel_2_scale) & 1) {
        effect->unk_14.at00_u16.v = (u16) (effect->unk_14.at00_u16.v | 1);
    } else {
        effect->unk_14.at00_u16.v = (u16) (effect->unk_14.at00_u16.v & 0xFFFE);
    }
    if (rand() & 1) {
        effect->unk_14.at00_u16.v = (u16) (effect->unk_14.at00_u16.v | 2);
    } else {
        effect->unk_14.at00_u16.v = (u16) (effect->unk_14.at00_u16.v & 0xFFFD);
    }
    func_800478B8(effect);
    if (((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1A <= 0) {
        ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_00 = (u16) (((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
