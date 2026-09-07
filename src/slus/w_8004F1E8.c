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

Prim12 *func_8004F1E8(Prim12 *p) {
    p->code = 0x80;
    p->w = 0;
    p->h = 0;
    p->u = 0xFF;
    p->v = 0xFF;
    p++;

    p->code = 0x2C;
    p->x = GetTPage(1, 0, 0x380, 0x100);
    p->y = GetClut(0, 0x1F5);
    p->u = 0xA0;
    p->w = 0;
    p->h = 0;
    p->v = 0x70;
    p++;

    p->w = 0x70;
    p->h = 0xE0;
    p->code = 0x80;
    p->u = 8;
    p->v = 8;
    p++;

    p->code = 0x81;
    p->x = 0x20;
    p->y = 0;
    p->tag = 0x80;
    return p + 1;
}
