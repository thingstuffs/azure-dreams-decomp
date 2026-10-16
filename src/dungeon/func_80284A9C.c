#include "modules/dungeon_floor_generate.h"

void dungeonInitializeGridBorderCells(void)
{
    s32 edge_index;
    floor_generate_isolated_80284A9C_Cell *cell;
    MapGrid *grid_config = &gameWork.map;

    edge_index = 0;
    if ((1 << grid_config->shiftY) > 0) {
        s32 border_type = 3;
        s32 border_attr = 0x400;
        s32 step = 1;

        do {
            cell = &((floor_generate_isolated_80284A9C_Cell *)D_800EA000)[edge_index << grid_config->shiftX];
            cell->field_0 = border_type;
            cell->field_2 = border_attr;
            cell->field_4 |= 0x8001;

            cell = &((floor_generate_isolated_80284A9C_Cell *)D_800EA000)[((step + edge_index) << grid_config->shiftX) - 1];
            cell->field_0 = border_type;
            cell->field_2 = border_attr;
            cell->field_4 |= 0x8001;
        } while (++edge_index < (step << grid_config->shiftY));
    }

    for (edge_index = 0; edge_index < (1 << grid_config->shiftY); edge_index++) {
        cell = &((floor_generate_isolated_80284A9C_Cell *)D_800EA000)[edge_index];
        cell->field_0 = 3;
        cell->field_2 = 0x400;
        cell->field_4 |= 0x8001;

        cell = &((floor_generate_isolated_80284A9C_Cell *)D_800EA000)[(((1 << grid_config->shiftY) - 1) << grid_config->shiftX) + edge_index - 1];
        cell->field_0 = 3;
        cell->field_2 = 0x400;
        cell->field_4 |= 0x8001;
    }
}
