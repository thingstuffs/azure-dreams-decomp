#include "dungeon/level/generate.h"

void setup_run_and_load_track(void) {
    floor_generate_isolated_80285A70_State13710 *state;
    floor_generate_isolated_80285A70_Page8001 *page1;
    floor_generate_isolated_80285A70_TrackRecord *track;
    s16 *clearp;
    s32 value;
    s32 track_no;
    s32 action;
    s32 i;
    {
        GameWork *xor_base;
        u16 entry_flags;

        state = (floor_generate_isolated_80285A70_State13710 *)0x80013710;
        entry_flags = state->flags;
        xor_base = &g_game_work;

        if (entry_flags & 2) {
            u32 r;
            u16 fl;

            func_800A6D98(state->seed);
            r = generate_random_value();
            state->field8 = 0;
            state->fieldA = 0;
            state->field6 = 0;
            state->seed += r & 0xFFFF;
            (*(floor_generate_isolated_80285A70_SaveHead *)D_80081468).seed = state->seed;
            fl = state->flags;
            (*(floor_generate_isolated_80285A70_SaveHead *)D_80081468).level = ((floor_generate_isolated_80285A70_LevelPage *)0x80010000)->level;
            fl &= 0xFFFC;
            state->flags = fl;
            func_8004D0C8(((u8 *)(&D_80083780)));
            bzero((void *)0x80013720, 0x2000);
        } else if (entry_flags & 1) {
            state->field8 = 0;
            state->fieldA = 0;
            (*(floor_generate_isolated_80285A70_SaveHead *)D_80081468).seed = state->seed;
            (*(floor_generate_isolated_80285A70_SaveHead *)D_80081468).level = ((floor_generate_isolated_80285A70_LevelPage *)0x80010000)->level;
            func_8004D0C8(((u8 *)(&D_80083780)));
        } else {
            u32 hi;

            state->flags = 0;
            value = rand();
            hi = rand();
            state->field8 = 0;
            state->field6 = 0;
            state->field11 = 0;
            state->field10 = 0;
            state->seed = (*(floor_generate_isolated_80285A70_SaveHead *)D_80081468).seed = (value | (hi << 16)) ^ xor_base->unk_004;
            func_8004D0C8(((u8 *)(&D_80083780)));
            bzero((void *)0x80013720, 0x2000);
        }
    }

    srand((*(floor_generate_isolated_80285A70_SaveHead *)D_80081468).seed);
    func_800A6D98((*(floor_generate_isolated_80285A70_SaveHead *)D_80081468).seed);
    store_monster_direction_nibble();
    D_80082E60.flags16 = 0;
    D_800E3D6C = 0;
    clear_dungeon_object_entries();
    clear_dungeon_cell_entries();

    i = 3;
    clearp = ((s16 *)D_800E3CD8);
    clearp += 12;
    do {
        *clearp = 0;
        i--;
        clearp -= 4;
    } while (i >= 0);

    page1 = (floor_generate_isolated_80285A70_Page8001 *)0x80010000;
    if ((u32)page1->level >= 100U) {
        page1->level = 99;
    }

    track_no = setup_dungeon_floor_encounters();
    if (track_no != 0) {
        floor_generate_isolated_80285A70_TrackRecord *tracks;

        track_no--;
        clear_thirty_six_table_fields();
        tracks = D_8001F62C;
        track = &tracks[track_no];
        create_default_state_object(track->track);
        file_load_com(D_8001F588[track->table_index]);
        runtime_load_packed_resource_chunks(track->kind, D_800F0000);
        clear_generation_cell_grid();
        clear_generation_region_entries();
        if (track->arg != 0) {
            load_dungeon_layout(track->arg);
        }
        if (track->special == 0) {
            ((floor_generate_isolated_80285A70_Page800E *)0x800E0000)->flags &= ~0x20000000;
        } else {
            run_indexed_callback_list(track->special - 1);
            ((floor_generate_isolated_80285A70_Page800E *)0x800E0000)->flags &= ~0x20000000;
        }
    } else {
        if (page1->mode != 2) {
            create_default_state_object(D_8001F584 % 24 + 3);
            action = D_8001F594[D_8001F584 % 24];
        } else {
            s32 random_remainder;

            random_remainder = generate_random_value() & 0xFFFF;
            random_remainder %= 24;
            create_default_state_object((s16)(random_remainder + 3));
            action = D_8001F594[random_remainder];
        }

        file_load_com(action);
        ((floor_generate_isolated_80285A70_Page800E *)0x800E0000)->flags |= 0x20000000;
        runtime_load_packed_resource_chunks(0x29, D_800F0000, (floor_generate_isolated_80285A70_Page800E *)0x800E0000);
        create_wrapped_texture_scroll(2);

        do {
            clear_generation_cell_grid();
            clear_generation_region_entries();
        } while ((generate_floor_layout() << 16) != 0 || (*(floor_generate_isolated_80285A70_SaveHead *)D_80081468).ready == 0);

    }
    apply_state_index_tile_masks();
    if (D_8001F586 == 0) {
        place_random_floor_elevators();
    }
    initialize_grid_border_cells();
}

