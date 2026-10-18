#include "modules/dungeon_resource16_slot0.h"

void update_expanding_spiral_effect(void *effect, R16_80173738_FuncArg1 *position, Rec_D_80082E80 *primitive) {
    s16 life;
    s16 next_life;
    s32 y_offset;
    s32 base_y;
    s32 z_step;
    void *primitive_dst;

    ((R16_80173738_S_80173738_0 *)effect)->unk_1E = (u16) (((R16_80173738_S_80173738_0 *)effect)->unk_1E - 0x12C);
    ((R16_80173738_S_80173738_0 *)effect)->unk_20 = (u16) (((R16_80173738_S_80173738_0 *)effect)->unk_20 + 2);
    position->unk00 = (s32) (((R16_80173738_S_80173738_0 *)effect)->unk_40
        + ((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_20 * func_80064584((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_1E) * 0x10));
    y_offset = (s16) ((R16_80173738_S_80173738_0 *)effect)->unk_20 * func_800644B8((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_1E);
    primitive_dst = primitive;
    z_step = 0xFFF40000U;
    base_y = ((R16_80173738_S_80173738_0 *)effect)->unk_44;
    position->unk08 = (s32) (position->unk08 + z_step);
    position->unk04 = (s32) (base_y + (y_offset * 0x10));
    func_800478B8(primitive_dst);
    if (primitive->unk_14.at00_u16.v & 0x4000) {
        func_8003DB94(primitive, ((M2C_UNK *)D_800DEC70), 0);
    }
    life = ((R16_80173738_S_80173738_0 *)effect)->unk_1A;
    if (life < 0xA) {
        primitive->unk_0C.at00_s8.v = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_00 * life) / 9);
        primitive->unk_0C.at01_s8.v = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_01 * ((R16_80173738_S_80173738_0 *)effect)->unk_1A) / 9);
        primitive->unk_0C.at02_s8.v = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_02 * ((R16_80173738_S_80173738_0 *)effect)->unk_1A) / 9);
    }
    next_life = (u16) ((R16_80173738_S_80173738_0 *)effect)->unk_1A - 1;
    ((R16_80173738_S_80173738_0 *)effect)->unk_1A = next_life;
    if ((next_life << 0x10) <= 0) {
        ((R16_80173738_S_80173738_0_pre *)effect)[-1].unk_00 = (u16) (((R16_80173738_S_80173738_0_pre *)effect)[-1].unk_00 | 0x8000);
        ((R16_80173738_S_80173738_2 *)((s32 *)(&object_flag_block)))->unk_00 =
            (s32) (((R16_80173738_S_80173738_2 *)((s32 *)(&object_flag_block)))->unk_00 | 0x8000);
    }
}
