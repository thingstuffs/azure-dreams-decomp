#include "modules/dungeon_ovl_1936800.h"

void create_a_type_hex_212_initializes_handler_mode(s32 initial_value) {
    Row_81916D2C_S_8002452C_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = &D_8002441C;
        ((Row_81916D2C_S_8002452C_2 *)(((Row_81916D2C_S_8002452C_1 *)object)->unk_0C))->unk_05 = 4;
        object->unk_20 = initial_value;
    }
}
