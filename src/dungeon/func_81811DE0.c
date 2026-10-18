#include "modules/dungeon_ovl_1831cd8.h"

s32 configure_menu_resource(s32 setup_value, M2C_UNK setup_data) {
    s32 resource;

    resource = func_8004B404(0x91);
    if (resource != 0) {
        resource = func_80025040(resource, setup_value, setup_data, 0x48);
    }
    return resource;
}
