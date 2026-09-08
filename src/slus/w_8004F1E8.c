#include "common.h"

#include "common.h"

typedef struct Prim12 {
    u8 tag;
    u8 code;
    u8 pad2[2];
    s16 x;
    s16 y;
    u8 w;
    u8 h;
    u8 u;
    u8 v;
} Prim12;

extern s16 GetClut();
extern s16 GetTPage();

/* Initializes four primitive records and returns the next free record. */
Prim12 *func_8004F1E8(Prim12 *prim) {
    prim->code = 0x80;
    prim->w = 0;
    prim->h = 0;
    prim->u = 0xFF;
    prim->v = 0xFF;
    prim++;

    prim->code = 0x2C;
    prim->x = GetTPage(1, 0, 0x380, 0x100);
    prim->y = GetClut(0, 0x1F5);
    prim->u = 0xA0;
    prim->w = 0;
    prim->h = 0;
    prim->v = 0x70;
    prim++;

    prim->w = 0x70;
    prim->h = 0xE0;
    prim->code = 0x80;
    prim->u = 8;
    prim->v = 8;
    prim++;

    prim->code = 0x81;
    prim->x = 0x20;
    prim->y = 0;
    prim->tag = 0x80;
    return prim + 1;
}
