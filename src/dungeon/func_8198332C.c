#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Coord {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
} Coord;

typedef struct Prim {
    s32 unk0;
    s32 unk4;
    void *unk8;
    u32 color;
    s16 unk10;
    s16 unk12;
    u16 unk14;
    s16 unk16;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
} Prim;

typedef struct Actor {
    s32 unk0;
    s32 unk4;
    Coord *pos;
    Prim *prim;
    void *update;
    u8 pad14[0x50 - 0x14];
    s16 unk50;
} Actor;

extern u8 D_80045340[];
extern s16 D_80026B28;
extern Coord D_80027CA4;
extern u8 D_800269EC[];
extern u8 D_80024AB4[];

extern void *func_8003FC64(s32 arg0);
extern s32 func_8004491C(void *arg0, void *arg1);
extern s32 func_800644B8(s32 arg0);
extern s32 func_80064584(s32 arg0);
void *func_80024B2C(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor);

/* Spawns an effect actor or builds a curved trail to the saved position. */
void *func_80024B2C(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor) {
    Actor *actor;
    Coord *coord;
    Prim *prim;
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
            actor->update = D_80024AB4;
            func_8004491C(actor, D_80045340);
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
