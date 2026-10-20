#include "dungeon/level/generate.h"

void load_dungeon_layout(s16 layout_number)
{
    MapGrid *cfg;
    floor_generate_isolated_80285464_MapCell *map;
    floor_generate_isolated_80285464_RecB *placed_record;
    u8 *data;
    u8 *data_2;
    u16 *room_header;
    s32 entry_index;
    s16 layout_index;
    s32 x_or_marker;
    s32 layout_id;
    s32 map_value;
    u16 tile_value;
    u16 shift_y;

    layout_index = layout_number - 1;
    data_2 = (*(u8 * *)D_8008148C);
    (*(u8 * *)D_80081480) = data_2;
    layout_id = D_8001F604[layout_index];
    cfg = &g_game_work.map;
    map = ((floor_generate_isolated_80285464_MapCell *)cfg->cells);
    Control_CD(6, layout_id, 0);
    drain_cd_command_queue();
    entry_index = 0;

    room_header = (u16 *)(data_2 + 4);
    cfg->shiftX = ((u16 *)data_2)[0];
    cfg->maskX = (1 << cfg->shiftX) - 1;
    shift_y = ((u16 *)data_2)[1];
    cfg->spanX = 64 << cfg->shiftX;
    cfg->shiftY = shift_y;
    cfg->maskY = (1 << cfg->shiftY) - 1;
    cfg->spanY = 64 << cfg->shiftY;

    while (room_header[2] != 0) {
        ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].active = 1;
        ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].x = room_header[0];
        ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].y = room_header[1];
        ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].w = room_header[2];
        ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].h = room_header[3];
        ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].count = 0;
        room_header += 4;
        data = (u8 *)room_header;
        while (*data != 0) {
            ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].tiles = &D_800E2C40[entry_index << 6];
            floor_generate_isolated_80285464_ROOM_CELL(entry_index, ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].count).a = *data++;
            floor_generate_isolated_80285464_ROOM_CELL(entry_index, ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].count).b = *data++;
            floor_generate_isolated_80285464_ROOM_CELL(entry_index, ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].count).c = *data;
            data += 2;
            ((floor_generate_isolated_80285464_Room *)D_800E2970)[entry_index].count++;
        }
        entry_index++;
        data += 2;
        room_header = (u16 *)data;
    }
    room_header += 4;
    data = (u8 *)room_header;
    (*(s16 *)D_8008146E) = entry_index;
    entry_index = 0;
    while (*data != 0) {
        ((floor_generate_isolated_80285464_Ent8 *)D_800E3CD8)[entry_index].kind = data[2] + 2;
        ((floor_generate_isolated_80285464_Ent8 *)D_800E3CD8)[entry_index].x = data[0];
        ((floor_generate_isolated_80285464_Ent8 *)D_800E3CD8)[entry_index].y = data[1];
        tile_value = map[data[0] + (data[1] << cfg->shiftX)].value - 32;
        map[data[0] + (data[1] << cfg->shiftX)].value = tile_value;
        ((floor_generate_isolated_80285464_Ent8 *)D_800E3CD8)[entry_index].value = tile_value;
        if (((floor_generate_isolated_80285464_Ent8 *)D_800E3CD8)[entry_index].kind == 2) {
            map[data[0] + (data[1] << cfg->shiftX)].kind = 1;
        }
        cycle_map_cell_flags(data[0], data[1], 32);
        entry_index++;
        data += 4;
    }
    if (try_add_second_tower_entry(entry_index) != 0) {
        entry_index++;
    }
    D_8001F586 = 1;
    entry_index++;
    while (entry_index < 4) {
        ((floor_generate_isolated_80285464_Ent8 *)D_800E3CD8)[entry_index].kind = 0;
        entry_index++;
    }

    data += 2;
    entry_index = 0;
    while ((x_or_marker = *data) != 0) {
        if (x_or_marker == 99) {
            D_800E3D6C |= 2;
            data += 6;
            break;
        }
        data++;
        ((floor_generate_isolated_80285464_RecB *)D_800E36C8)[entry_index].f0 = x_or_marker;
        ((floor_generate_isolated_80285464_RecB *)D_800E36C8)[entry_index].f1 = *data++;
        D_800E3548[entry_index].unk_00 = *data++;
        D_800E3548[entry_index].kind = *data++;
        D_800E3548[entry_index].unk_03 = *data++;
        D_800E3548[entry_index].unk_02 = *data++;
        ((floor_generate_isolated_80285464_RecB *)D_800E36C8)[entry_index].f8 = get_item_category_value(&D_800E3548[entry_index]);
        entry_index++;
    }
    while (entry_index < 64) {
        D_800E3548[entry_index].kind = 0;
        D_800E3548[entry_index].unk_00 = 0;
        entry_index++;
    }

    data += 2;
    entry_index = 0;
    while ((x_or_marker = *data) != 0) {
        if (x_or_marker == 99) {
            D_800E3D6C |= 8;
            data += 6;
            break;
        }
        data++;
        ((floor_generate_isolated_80285464_RecC *)D_800E39C8)[entry_index].f6 = x_or_marker;
        ((floor_generate_isolated_80285464_RecC *)D_800E39C8)[entry_index].f7 = *data++;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f0 = *data++;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f1 = *data++;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f3 = *data++;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f2 = *data++;
        ((floor_generate_isolated_80285464_RecC *)D_800E39C8)[entry_index].f8 = D_800DF258[((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f0];
        cycle_map_cell_flags(((floor_generate_isolated_80285464_RecC *)D_800E39C8)[entry_index].f6, ((floor_generate_isolated_80285464_RecC *)D_800E39C8)[entry_index].f7, 32);
        entry_index++;
    }

    data += 2;
    while (*data != 0) {
        D_800E296C |= 0x10000000;
        ((floor_generate_isolated_80285464_RecC *)D_800E39C8)[entry_index].f6 = *data++;
        ((floor_generate_isolated_80285464_RecC *)D_800E39C8)[entry_index].f7 = *data++;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f0 = *data++;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f1 = *data++;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f3 = *data++;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f2 = *data++;
        entry_index++;
    }
    data += 2;
    while (entry_index < 32) {
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f1 = 0;
        ((floor_generate_isolated_80285464_RecD *)D_800E3648)[entry_index].f0 = 0;
        entry_index++;
    }

    decompress_lz(data, ((u8 *)D_800EA000));
    for (entry_index = 0; D_800E3548[entry_index].kind != 0; entry_index++) {
        placed_record = &((floor_generate_isolated_80285464_RecB *)D_800E36C8)[entry_index];
        map_value = get_surface_height_at_coordinates(placed_record->f0 << 6, placed_record->f1 << 6);
        placed_record->f4 = map_value;
        *(s16 *)&placed_record->f2 = map_value;
    }
}
