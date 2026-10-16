#include "modules/dungeon_ovl_18c4828.h"

void *func_80024148(s32 user_data, Row_818A4948_S_func_818A4948_2 *source_coords) {
    Row_818A4948_S_func_818A4948_0 *obj;
    Row_818A4948_S_func_818A4948_1 *render_data;
    Row_818A4948_S_func_818A4948_2 *coords;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->unk_10 = func_800240C4;
        render_data = obj->unk_0C;
        obj->unk_20 = user_data;
        render_data->unk_0E = 0x80;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        func_8003DB94(render_data, D_80025238, 0);
        render_data->unk_1E = 0x800;
        render_data->unk_1C = 0x800;
        render_data->unk_12 = 0x7E07;
        render_data->unk_14 |= 0x100;
        func_8004491C(obj, (s32) func_80045340);
        coords = obj->unk_08;
        coords->unk_02 = source_coords->unk_02;
        coords->unk_06 = source_coords->unk_06;
        coords->unk_0A = source_coords->unk_0A;
        return obj;
    }
    return 0;
}
