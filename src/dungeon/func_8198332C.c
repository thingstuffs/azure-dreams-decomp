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
void *func_80024B2C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);

void *func_80024B2C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Actor *actor;
    Coord *coord;
    Prim *prim;
    s16 dx;
    s16 dy;
    s16 dz;
    s16 cx;
    s16 cy;
    s16 cz;
    s32 i;

    actor = NULL;
    if (arg4 != 0) {
        actor = func_8003FC64(514);
        if (actor != NULL) {
            actor->update = D_80024AB4;
            func_8004491C(actor, D_80045340);
            coord = actor->pos;
            coord->x = arg0;
            coord->y = arg1;
            coord->z = arg2;
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
            dx = (D_80027CA4.x - arg0) / 16;
            dy = (D_80027CA4.y - arg1) / 16;
            dz = (D_80027CA4.z - arg2) / 16;
            cx = arg0 + dx;
            cy = arg1 + dy;
            cz = arg2 + dz;
            for (i = 0; i < 16; i++) {
                func_80024B2C(cx + ((func_80064584(arg3) * func_800644B8(i << 7)) >> 21),
                              cy + ((func_800644B8(arg3) * func_800644B8(i << 7)) >> 21),
                              cz, arg3, 1);
                cx += dx;
                cy += dy;
                cz += dz;
            }
        }
        if (D_80026B28 == 0) {
            D_80027CA4.x = arg0;
            D_80027CA4.y = arg1;
            D_80027CA4.z = arg2;
        }
        D_80026B28 = D_80026B28 + 1;
    }
    return actor;
}
