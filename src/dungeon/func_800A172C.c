#include "shared/dungeon_item_entries.h"
#include "common.h"

extern int abs(int);

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 kind;
} Entity;



typedef struct {
    u8 x;
    u8 y;
    u8 pad02[10];
} RegionPos;

s32 func_8009FB34();
extern RegionPos D_800E36C8[];

/* Finds the nearest matching entry in the entity's region and writes its coordinates. */
u32 func_800A6E8C(Entity *entity, s32 filter, s16 *out_x, s16 *out_y) {
    s16 best_distance;
    s32 best_index;
    s32 i;
    s32 id;
    s32 type;
    s32 x;
    s32 y;
    s16 dx;
    s16 dy;
    s32 y_larger;
    s16 d;

    if (entity->kind < 0) {
        return 0;
    }
    best_distance = 0x100;
    best_index = -1;
    i = 0x3F;
    id = filter & 0xFF;
    type = (s16)filter >> 8;
    for (; i >= 0; i--) {
        if (D_800E3548[i].kind == id && (type == 0 || D_800E3548[i].unk_00 == type)) {
            x = D_800E36C8[i].x;
            y = D_800E36C8[i].y;
            if ((s16)func_8009FB34(x, y) == entity->kind) {
                dx = abs(x - entity->x);
                dy = abs(y - entity->y);
                y_larger = dx < dy;
                d = y_larger ? dy : dx;
                if (best_distance > d) {
                    best_distance = y_larger ? dy : dx;
                    *out_x = x;
                    *out_y = y;
                    best_index = i;
                }
            }
        }
    }
    return (s16)best_index >= 0;
}
