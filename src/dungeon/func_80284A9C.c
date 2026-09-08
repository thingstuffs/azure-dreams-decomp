typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} Cell;

extern s16 D_8008333C[12];
extern Cell D_800EA000[];

/* Initializes the grid border cells. */
void func_80017A9C(void)
{
    s32 edge_index;
    Cell *cell;
    s16 *grid_config = D_8008333C;

    edge_index = 0;
    if ((1 << grid_config[11]) > 0) {
        s32 border_type = 3;
        s32 border_attr = 0x400;
        s32 step = 1;

        do {
            cell = &D_800EA000[edge_index << grid_config[10]];
            cell->field_0 = border_type;
            cell->field_2 = border_attr;
            cell->field_4 |= 0x8001;

            cell = &D_800EA000[((step + edge_index) << grid_config[10]) - 1];
            cell->field_0 = border_type;
            cell->field_2 = border_attr;
            cell->field_4 |= 0x8001;
        } while (++edge_index < (step << grid_config[11]));
    }

    for (edge_index = 0; edge_index < (1 << grid_config[11]); edge_index++) {
        cell = &D_800EA000[edge_index];
        cell->field_0 = 3;
        cell->field_2 = 0x400;
        cell->field_4 |= 0x8001;

        cell = &D_800EA000[(((1 << grid_config[11]) - 1) << grid_config[10]) + edge_index - 1];
        cell->field_0 = 3;
        cell->field_2 = 0x400;
        cell->field_4 |= 0x8001;
    }
}
