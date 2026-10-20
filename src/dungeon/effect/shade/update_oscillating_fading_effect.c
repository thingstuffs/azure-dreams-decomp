#include "dungeon/effect/shade/update_oscillating_fading_effect.h"


void update_oscillating_fading_effect(void *effect, Row_818F34E4_S_80024CE4_2 *position, Row_818F34E4_S_80024CE4_1 *visual, s32 unused) {
    s16 initialized;
    s16 fade_ticks;
    s16 height_limit;
    s16 ticks_left;
    s16 angle;
    s16 step;
    s32 fade_numerator;
    s32 fade_level;
    s32 wave_height;
    s32 height_offset;
    u16 angle_step;
    u16 amplitude;
    u16 scale;
    void *init_or_snapshot;
    void *global_state;
    void *transform;
    Row_818F34E4_S_80024CE4_0 *view_state;

    D_800259AC = 1;
    global_state = ((void *)&g_game_work.view);
    view_state = (u8 *) global_state + 0xB8;
    initialized = (*(s16 *)((u8 *)effect + 0));
    init_or_snapshot = (void *) (u32) (*(u16 *)((u8 *)effect + 0));
    if (initialized == 0) {
        (*(s16 *)((u8 *)effect + 0)) = (s16) ((u32) init_or_snapshot + 1);
        transform = ((Row_818F34E4_S_80024CE4_3_pre *)((*(void **)((u8 *)effect + 0x2C))))[-1].unk_00;
        (*(Row_818F34E4_Block24 *)((u8 *)effect + 0x44)) = (*(Row_818F34E4_Block24 *)((u8 *)transform + 0));
        init_or_snapshot = effect + 0x44;
        if ((view_state->unk_20 == ((u8 *)(&D_80083780))) && ((*(void **)((u8 *)effect + 0x2C)) == ((int)D_800814A8))) {
            view_state->unk_20 = (u8 *) init_or_snapshot;
            (*(s16 *)((u8 *)effect + 0xA)) = 9;
        }
    }
    (*(u16 *)((u8 *)effect + 0x3C)) = 0x40U;
    (*(u16 *)((u8 *)effect + 2)) = (u16) ((*(u16 *)((u8 *)effect + 2)) - 1);
    (*(u16 *)((u8 *)effect + 0x3A)) = (u16) ((*(u16 *)((u8 *)effect + 0x3A)) + 0x96);
    ticks_left = (*(s16 *)((u8 *)effect + 2));
    if (ticks_left >= 0x51) {
        (*(u16 *)((u8 *)effect + 0x38)) = (u16) ((*(u16 *)((u8 *)effect + 0x38)) + 4);
    } else if (ticks_left < 0x32) {
        amplitude = (*(u16 *)((u8 *)effect + 0x38)) - 5;
        (*(u16 *)((u8 *)effect + 0x38)) = amplitude;
        if ((s16) amplitude < 0) {
            (*(u16 *)((u8 *)effect + 0x38)) = 0U;
        }
    }
    fade_ticks = (s16) (*(u16 *)((u8 *)effect + 2));
    if (fade_ticks < 0x14) {
        fade_numerator = fade_ticks << 7;
        fade_level = fade_numerator / 20;
        visual->unk_0E = fade_level;
        visual->unk_0D = fade_level;
        visual->unk_0C = fade_level;
    }
    scale = visual->unk_1C;
    visual->unk_1A = (u16) (visual->unk_1A + 0x10);
    if (scale < 0x1000U) {
        visual->unk_1C = (u16) (scale + 0x100);
        visual->unk_1E = (u16) (visual->unk_1E + 0x100);
    }
    angle = (*(u16 *)((u8 *)effect + 0x3A));
    angle_step = (*(u16 *)((u8 *)effect + 0x3C));
    for (step = 0; step < 0x20; step++) {
        angle += angle_step;
        if (angle >= 0x1001) {
            angle -= 0x1000;
        }
    }
    transform = ((Row_818F34E4_S_80024CE4_3_pre *)((*(void **)((u8 *)effect + 0x2C))))[-1].unk_00;
    wave_height = func_800644B8(angle) * (s16) (*(u16 *)((u8 *)effect + 0x38));
    height_offset = wave_height * 2;
    (*(s32 *)((u8 *)transform + 8)) = height_offset;
    (*(s32 *)((u8 *)transform + 8)) = (s32) (height_offset + (*(s32 *)((u8 *)effect + 0x40)));
    height_limit = sample_terrain_surface_height(position->unk_02, position->unk_06, position->unk_0A);
    if (height_limit < (*(s16 *)((u8 *)transform + 0xA))) {
        (*(s16 *)((u8 *)transform + 0xA)) = height_limit;
    }
    if ((s16) (*(u16 *)((u8 *)effect + 2)) <= 0) {
        ((Row_818F34E4_S_80024CE4_4 *)((*(void **)((u8 *)effect + 0x30))))->unk_9C = 1;
        if ((*(s16 *)((u8 *)effect + 0xA)) == 9) {
            view_state->unk_20 = ((u8 *)(&D_80083780));
        }
        (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
