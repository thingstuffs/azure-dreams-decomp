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

void func_80017A9C(void)
{
    s32 i;
    Cell *cell;
    s16 *config = D_8008333C;

    i = 0;
    if ((1 << config[11]) > 0) {
        s32 value_0 = 3;
        s32 value_2 = 0x400;
        s32 one = 1;

        do {
            cell = &D_800EA000[i << config[10]];
            cell->field_0 = value_0;
            cell->field_2 = value_2;
            cell->field_4 |= 0x8001;

            cell = &D_800EA000[((one + i) << config[10]) - 1];
            cell->field_0 = value_0;
            cell->field_2 = value_2;
            cell->field_4 |= 0x8001;
        } while (++i < (one << config[11]));
    }

    for (i = 0; i < (1 << config[11]); i++) {
        cell = &D_800EA000[i];
        cell->field_0 = 3;
        cell->field_2 = 0x400;
        cell->field_4 |= 0x8001;

        cell = &D_800EA000[(((1 << config[11]) - 1) << config[10]) + i - 1];
        cell->field_0 = 3;
        cell->field_2 = 0x400;
        cell->field_4 |= 0x8001;
    }
}
