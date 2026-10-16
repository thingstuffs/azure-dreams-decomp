#include "modules/dungeon_resource12_slot0.h"

void func_80175180(void *source_arg, void *spawn_pos_arg, void *unused_context)
{
    void *spawn_pos = spawn_pos_arg;
    u16 render_flags;
    void *effect;
    R12_80175180_S_80175180_3 *render_part;
    R12_80175180_S_80175180_4 *position;
    u8 *state;

    effect = func_8003FC64(0x12);
    state = (u8 *)effect + 0x20;
    if (effect != 0) {
        ((R12_80175180_S_80175180_0 *)state)->unk_08 = 0x4A;
        ((R12_80175180_S_80175180_0 *)state)->unk_0A = ((R12_80175180_S_80175180_1 *)source_arg)->unk_96;
        ((R12_80175180_S_80175180_0 *)state)->unk_0C = 0;
        ((R12_80175180_S_80175180_2 *)effect)->unk_10 = ((u8 *)func_801749EC);
        source_arg = func_80045340;
        func_8004491C(effect, source_arg);
        render_part = ((R12_80175180_S_80175180_2 *)effect)->unk_0C;
        render_flags = (*(u16 *)((u8 *)render_part + 0x14));
        render_flags |= 0xC;
        (*(u16 *)((u8 *)render_part + 0x14)) = render_flags;
        render_part->unk_10 = 0x20;
        render_flags |= 0x80;
        (*(u16 *)((u8 *)render_part + 0x14)) = render_flags;
        position = ((R12_80175180_S_80175180_2 *)effect)->unk_08;
        position->unk_00 = ((R12_80175180_S_80175180_5 *)spawn_pos)->unk_00;
        position->unk_04 = ((R12_80175180_S_80175180_5 *)spawn_pos)->unk_04;
        position->unk_08 = ((R12_80175180_S_80175180_5 *)spawn_pos)->unk_08 + 0xFFE80000;
        render_part = ((R12_80175180_S_80175180_2 *)effect)->unk_0C;
        render_part->unk_1E = 0x1000;
        render_part->unk_1C = 0x1000;
        render_part->unk_0E = 0x80;
        render_part->unk_0C = 0x80;
        render_part->unk_0D = 0x80;
    }
}
