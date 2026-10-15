#include "modules/dungeon_ovl_19a332c.h"

void *func_80024B2C(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor) {
    ovl_19a332c_8198332C_Actor *actor;
    ovl_19a332c_8198332C_Coord *coord;
    ovl_19a332c_8198332C_Prim *prim;
    s16 step_x;
    s16 step_y;
    s16 step_z;
    s16 path_x;
    s16 path_y;
    s16 path_z;
    s32 point_index;

    actor = NULL;
    if (spawn_actor != 0) {
        actor = func_8003FC64(514);
        if (actor != NULL) {
            actor->update = (void *)func_80024AB4;
            func_8004491C(actor, func_80045340);
            coord = actor->pos;
            coord->x = x;
            coord->y = y;
            coord->z = z;
            prim = actor->prim;
            prim->unk1E = 2048;
            prim->unk1C = 2048;
            prim->unk8 = D_800269EC;
            prim->color = 0x808080;
            prim->unk10 = 96;
            prim->unk14 |= 0xC;
            actor->unk50 = 16;
        }
    } else {
        if (D_80026B28 == 3) {
            step_x = (D_80027CA4.x - x) / 16;
            step_y = (D_80027CA4.y - y) / 16;
            step_z = (D_80027CA4.z - z) / 16;
            path_x = x + step_x;
            path_y = y + step_y;
            path_z = z + step_z;
            for (point_index = 0; point_index < 16; point_index++) {
                func_80024B2C(path_x + ((func_80064584(angle) * func_800644B8(point_index << 7)) >> 21),
                              path_y + ((func_800644B8(angle) * func_800644B8(point_index << 7)) >> 21),
                              path_z, angle, 1);
                path_x += step_x;
                path_y += step_y;
                path_z += step_z;
            }
        }
        if (D_80026B28 == 0) {
            D_80027CA4.x = x;
            D_80027CA4.y = y;
            D_80027CA4.z = z;
        }
        D_80026B28 = D_80026B28 + 1;
    }
    return actor;
}
