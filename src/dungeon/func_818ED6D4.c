#include "modules/dungeon_ovl_190d6a4.h"

void create_linked_effect_segments(ParticleWork *work, ParticlePosition *position) {
    *(s16 *)D_80026428 = 1;
    if (position->z.half.high < (s16)sample_terrain_surface_height(position->x, position->y, (s16)((u16)position->z.half.high + 2))) {
        position->z.word += 0x20000 + (rand() & 0xFFF);
    }
    work->lifetime = (u16)work->lifetime - 8;
    if (work->lifetime <= 0) {
        *(u16 *)((u8 *)work - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
