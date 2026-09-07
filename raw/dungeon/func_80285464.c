#include "common.h"

typedef struct MapCell {
    s16 kind;
    u16 value;
    s16 flags;
} MapCell;

typedef struct DungeonCfg {
    MapCell *cells;
    u8 pad04[16];
    s16 shift_x;
    s16 shift_y;
    s16 mask_x;
    s16 mask_y;
    s16 span_x;
    s16 span_y;
} DungeonCfg;

typedef struct Room {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8 pad08[2];
    s16 active;
    u8 pad0C[2];
    s16 count;
    u8 *tiles;
} Room;

typedef struct RoomCell {
    u8 a;
    u8 b;
    u16 c;
} RoomCell;

typedef struct Ent8 {
    s16 kind;
    s16 x;
    s16 y;
    s16 value;
} Ent8;

typedef struct RecA {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} RecA;

typedef struct RecB {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    s16 f4;
    s16 f6;
    s32 f8;
} RecB;

typedef struct RecC {
    u8 pad00[6];
    u8 f6;
    u8 f7;
    s32 f8;
    u8 pad0C[12];
} RecC;

typedef struct RecD {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} RecD;

#define ROOM_CELL(r, n) (*(RoomCell *)&D_800E2C40[((n) << 2) + ((r) << 6)])

extern void func_8003E4FC(s32, s32, s32);
extern void func_8003F320(void);
extern s32 func_800199C8(s16);
extern void func_8009A21C(s32, s32, s32);
extern s32 func_800A7A38(RecA *);
extern void func_8004068C(u8 *, u8 *);
extern s32 func_800BCA68(s32, s32);

extern s32 D_8001F604[];
extern s16 D_8001F586;
extern u8 *D_8008148C;
extern u8 *D_80081480;
extern s16 D_8008146E;
extern DungeonCfg D_8008333C;
extern s32 D_800DF258[];
extern Room D_800E2970[];
extern s32 D_800E296C;
extern u8 D_800E2C40[];
extern RecA D_800E3548[];
extern RecD D_800E3648[];
extern RecB D_800E36C8[];
extern RecC D_800E39C8[];
extern Ent8 D_800E3CD8[];
extern s32 D_800E3D6C;
extern u8 D_800EA000[];

void func_80018464(s16 arg0)
{
    DungeonCfg *cfg;
    MapCell *map;
    RecB *rb;
    u8 *p;
    u16 *q;
    s32 i;
    s16 idx;
    s32 c;
    register s32 tbl ASM_REG("$5");
    s32 v;
    u16 mv;
    u16 sy;

    idx = arg0 - 1;
    tbl = D_8001F604[idx];
    p = D_8008148C;
    D_80081480 = p;
    cfg = &D_8008333C;
    map = cfg->cells;
    func_8003E4FC(6, tbl, 0);
    func_8003F320();
    i = 0;

    q = (u16 *)(p + 4);
    cfg->shift_x = ((u16 *)p)[0];
    cfg->mask_x = (1 << cfg->shift_x) - 1;
    sy = ((u16 *)p)[1];
    cfg->span_x = 64 << cfg->shift_x;
    cfg->shift_y = sy;
    cfg->mask_y = (1 << cfg->shift_y) - 1;
    cfg->span_y = 64 << cfg->shift_y;

    while (q[2] != 0) {
        D_800E2970[i].active = 1;
        D_800E2970[i].x = q[0];
        D_800E2970[i].y = q[1];
        D_800E2970[i].w = q[2];
        D_800E2970[i].h = q[3];
        D_800E2970[i].count = 0;
        p = (u8 *)(q + 4);
        ASM_KEEP_NV(q);
        while (*p != 0) {
            D_800E2970[i].tiles = &D_800E2C40[i << 6];
            ROOM_CELL(i, D_800E2970[i].count).a = *p++;
            ROOM_CELL(i, D_800E2970[i].count).b = *p++;
            ROOM_CELL(i, D_800E2970[i].count).c = *p;
            p += 2;
            D_800E2970[i].count++;
        }
        i++;
        p += 2;
        q = (u16 *)p;
    }
    p = (u8 *)(q + 4);
    ASM_KEEP_NV(p);
    D_8008146E = i;
    i = 0;
    while (*p != 0) {
        D_800E3CD8[i].kind = p[2] + 2;
        D_800E3CD8[i].x = p[0];
        D_800E3CD8[i].y = p[1];
        mv = map[p[0] + (p[1] << cfg->shift_x)].value - 32;
        map[p[0] + (p[1] << cfg->shift_x)].value = mv;
        D_800E3CD8[i].value = mv;
        if (D_800E3CD8[i].kind == 2) {
            map[p[0] + (p[1] << cfg->shift_x)].kind = 1;
        }
        func_8009A21C(p[0], p[1], 32);
        i++;
        p += 4;
    }
    if (func_800199C8(i) != 0) {
        i++;
    }
    D_8001F586 = 1;
    i++;
    while (i < 4) {
        D_800E3CD8[i].kind = 0;
        i++;
    }

    p += 2;
    i = 0;
    while ((c = *p) != 0) {
        if (c == 99) {
            D_800E3D6C |= 2;
            p += 6;
            break;
        }
        p++;
        D_800E36C8[i].f0 = c;
        D_800E36C8[i].f1 = *p++;
        D_800E3548[i].f0 = *p++;
        D_800E3548[i].f1 = *p++;
        D_800E3548[i].f3 = *p++;
        D_800E3548[i].f2 = *p++;
        D_800E36C8[i].f8 = func_800A7A38(&D_800E3548[i]);
        i++;
    }
    while (i < 64) {
        D_800E3548[i].f1 = 0;
        D_800E3548[i].f0 = 0;
        i++;
    }

    p += 2;
    i = 0;
    while ((c = *p) != 0) {
        if (c == 99) {
            D_800E3D6C |= 8;
            p += 6;
            break;
        }
        p++;
        D_800E39C8[i].f6 = c;
        D_800E39C8[i].f7 = *p++;
        D_800E3648[i].f0 = *p++;
        D_800E3648[i].f1 = *p++;
        D_800E3648[i].f3 = *p++;
        D_800E3648[i].f2 = *p++;
        D_800E39C8[i].f8 = D_800DF258[D_800E3648[i].f0];
        func_8009A21C(D_800E39C8[i].f6, D_800E39C8[i].f7, 32);
        i++;
    }

    p += 2;
    while (*p != 0) {
        D_800E296C |= 0x10000000;
        D_800E39C8[i].f6 = *p++;
        D_800E39C8[i].f7 = *p++;
        D_800E3648[i].f0 = *p++;
        D_800E3648[i].f1 = *p++;
        D_800E3648[i].f3 = *p++;
        D_800E3648[i].f2 = *p++;
        i++;
    }
    p += 2;
    while (i < 32) {
        D_800E3648[i].f1 = 0;
        D_800E3648[i].f0 = 0;
        i++;
    }

    func_8004068C(p, D_800EA000);
    for (i = 0; D_800E3548[i].f1 != 0; i++) {
        rb = &D_800E36C8[i];
        v = func_800BCA68(rb->f0 << 6, rb->f1 << 6);
        rb->f4 = v;
        *(s16 *)&rb->f2 = v;
    }
}
