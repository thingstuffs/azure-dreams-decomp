#include "common.h"

typedef struct {
    u16 *tiles;
    u8 pad04[0x10];
    s16 row_shift;
} DungeonMap;

extern u16 D_800273CC[8];
extern u8 D_8002744C[9];
extern u8 D_8002744D[9];
extern u8 D_80083160[0x200];

void func_8196048C(void)
{
    s8 *base;
    DungeonMap *map;
    register s16 row ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    s16 column;
    s32 outer;
    s32 inner;
    u16 *source;
    u16 *cursor;
    u16 value;
    register u8 row_byte ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 column_byte;

    base = D_80083160;
    map = (DungeonMap *)(base + 0x1DC);
    ASM_KEEP(map);   /* MATCH pin: keeps a statement from moving across a call/branch */
    outer = 0;
    source = D_800273CC;
    row_byte = D_8002744D[0];
    column_byte = D_8002744C[0];
    row = row_byte - 3;
    column = column_byte - 3;
    ASM_KEEP(row_byte);   /* MATCH pin: load-bearing for the whole function shape */
    do {
        s16 x;
        s32 signed_row;

        x = column;
        inner = 0;
        signed_row = row;
        cursor = source;
loop:
        value = *cursor++;
        inner++;
        map->tiles[(x + (signed_row << map->row_shift)) * 3 + 1] = value;
        x++;
        if (inner < 7) {
            goto loop;
        }
        source += 8;
        outer++;
        row++;
    } while (outer < 7);
}

/* MECHANISM: Frameless leaf; a hoisted signed row and held base/map fences restore the 41-word layout.
   Short byte pins preserve the $v0/$v1 load roles, while DEPIN lets source and signed_row split through $v0.
   gcc 2.7.2-cdk-G0 supplies retail's two-register %hi/%lo address emission. */
