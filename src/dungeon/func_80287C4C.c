#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} Pos;

typedef struct {
    s16 unused[10];
    s16 stride;
} DungeonState;

typedef struct {
    s16 kind;
    s16 value;
    u16 flags;
} DungeonCell;

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8 pad08[2];
    s16 active;
    u8 pad0C[8];
} Room;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_8001F660;
extern DungeonState D_8008333C;
extern Room D_800E2970[];
extern DungeonCell D_800EA000[];

extern void func_800177D8(s16, s16, s16, s32);
extern void func_800A6D60(s32);
extern u32 func_800A07D0(s16, s16, s16, s16);
extern void func_8001CCEC(s16, s16 *, s16 *, Room *);
extern s16 func_8001C06C(Pos *, Pos *, s16, s16 *, s16 *);
extern s16 func_8001C5E4(Pos *, Pos *, s16, s16 *, s16 *, s32 *, s32 *);
extern s32 func_8001CE14(s16, s32, s16);

s32 func_8001AC4C(s16 dir0, s16 dir1, s16 from, s16 to, u8 *marks) {
    Pos a;
    Pos b;
    Pos c;
    s16 ox1;
    s16 oy1;
    s16 ox2;
    s16 oy2;
    s16 rx;
    s16 ry;
    s32 accA[1];
    s32 step[1];
    s32 accB[1];
    s32 ex;
    s32 ey;
    s16 back;
    Room *r1;
    s16 total;
    s16 sdir;
    Room *r2;
    DungeonState *st;
    DungeonCell *p;
    DungeonCell *q;
    s16 dir;
    s16 d3;
    s16 idx;
    s16 dx;
    s16 dy;
    s32 bx;
    s32 by;
    s32 cx;
    s32 cy;
    s32 hA;
    s32 hB;
    s32 dh;
    s32 adh;

    st = &D_8008333C;
    r1 = &D_800E2970[from];
    r2 = &D_800E2970[to];
    total = 0;
    func_8001CCEC(dir0, &ox1, &oy1, r1);
    func_8001CCEC((dir1 + 4) & 6, &ox2, &oy2, r2);
    dir = dir0;
    sdir = dir0;
    if (D_800E2970[from].active) {
        func_800177D8(from, r1->x + ox1, r1->y + oy1, 0);
    }
    if (D_800E2970[to].active) {
        func_800177D8(to, r2->x + ox2, r2->y + oy2, 0);
    }
    func_800A6D60(1);
    a.x = r1->x + ox1;
    a.y = r1->y + oy1;
    a.dir = dir0;
    if (D_800E2970[from].active) {
        a.x = a.x + D_8006CCD8[dir];
        a.y = a.y + D_8006CCE8[dir];
    }
    cx = (s16)(from % D_8001F660) + D_8006CCD8[dir];
    cy = (s16)(from / D_8001F660) + D_8006CCE8[dir];
    dx = to % D_8001F660;
    dy = to / D_8001F660;
    for (;;) {
        if (cx == dx && cy == dy) {
            if (D_800E2970[to].active) {
                b.x = r2->x + ox2;
                b.y = r2->y + oy2;
            } else {
                b.x = r2->x;
                b.y = r2->y;
            }
            b.x = b.x - D_8006CCD8[dir1];
            b.y = b.y - D_8006CCE8[dir1];
            total += func_8001C06C(&a, &b, 1, &rx, &ry);
            a.x = a.x + D_8006CCD8[(dir + 2) & 7];
            a.y = a.y + D_8006CCE8[(dir + 2) & 7];
            b.x = b.x + D_8006CCD8[(dir1 + 2) & 7];
            b.y = b.y + D_8006CCE8[(dir1 + 2) & 7];
            rx = rx - D_8006CCD8[dir];
            ry = ry - D_8006CCE8[dir];
            func_8001C06C(&a, &b, 0, &rx, &ry);
            break;
        }
        idx = cy * D_8001F660 + cx;
        marks[idx] = 2;
        b.x = D_800E2970[idx].x;
        b.y = D_800E2970[idx].y;
        total += func_8001C06C(&a, &b, 1, &rx, &ry);
        c = a;
        c.x = c.x + D_8006CCD8[(dir + 2) & 7];
        c.y = c.y + D_8006CCE8[(dir + 2) & 7];
        rx = rx - D_8006CCD8[dir];
        ry = ry - D_8006CCE8[dir];
        func_8001C06C(&c, &b, 0, &rx, &ry);
        a.x = b.x;
        a.y = b.y;
        if (D_8006CCD8[dir] != 0) {
            if (cx == dx) {
                a.dir = (func_800A07D0(cx, cy, dx, dy) >> 9) & 6;
            }
        } else {
            if (cy == dy) {
                a.dir = (func_800A07D0(cx, cy, dx, dy) >> 9) & 6;
            }
        }
        cx = cx + D_8006CCD8[a.dir];
        cy = cy + D_8006CCE8[a.dir];
        dir = a.dir;
    }

    dir = sdir;
    back = (dir + 4) & 7;
    bx = r1->x + ox1;
    by = r1->y + oy1;
    p = &D_800EA000[(by << st->stride) + bx];
    q = &D_800EA000[((by + D_8006CCE8[back]) << st->stride) + bx + D_8006CCD8[back]];
    ex = r2->x + ox2;
    ey = r2->y + oy2;
    if (func_8001CE14(p->kind, 15, 18)) {
        p->kind = (q->flags >> 1) + (dir / 2) * 5 + 79;
        p->value = q->value - ((q->flags & 1) << 5);
        if (func_8001CE14(q->kind, 99, 103)) {
            p->value = p->value + 96;
        }
    }
    if (func_8001CE14(q->kind, 19, 28)) {
        q->kind = q->flags + (dir / 2) * 10 + 39;
    } else if (func_8001CE14(q->kind, 99, 103)) {
        q->kind = q->flags + (dir / 2) * 10 + 39;
        q->value = q->value + 96;
    }

    cx = bx + D_8006CCD8[(dir + 2) & 7];
    cy = by + D_8006CCE8[(dir + 2) & 7];
    p = &D_800EA000[(cy << st->stride) + cx];
    q = &D_800EA000[((cy + D_8006CCE8[back]) << st->stride) + cx + D_8006CCD8[back]];
    if (func_8001CE14(p->kind, 15, 18)) {
        p->kind = (q->flags >> 1) + (dir / 2) * 5 + 79;
        p->value = q->value - ((q->flags & 1) << 5);
        if (func_8001CE14(q->kind, 99, 103)) {
            p->value = p->value + 96;
        }
    }
    if (func_8001CE14(q->kind, 19, 28)) {
        q->kind = q->flags + (dir / 2) * 10 + 39;
    } else if (func_8001CE14(q->kind, 99, 103)) {
        q->kind = q->flags + (dir / 2) * 10 + 39;
        q->value = q->value + 96;
    }

    if (D_800E2970[to].active) {
        back = dir1;
        cx = ex;
        cy = ey;
        p = &D_800EA000[(cy << st->stride) + cx];
        cx = cx + D_8006CCD8[dir1];
        cy = cy + D_8006CCE8[dir1];
        q = &D_800EA000[(cy << st->stride) + cx];
        d3 = (dir1 + 4) & 6;
        if (func_8001CE14(p->kind, 15, 18)) {
            p->kind = (q->flags >> 1) + (d3 / 2) * 5 + 79;
            p->value = q->value - ((q->flags & 1) << 5);
            if (func_8001CE14(q->kind, 99, 103)) {
                p->value = p->value + 96;
            }
        }
        if (func_8001CE14(q->kind, 19, 28)) {
            q->kind = q->flags + (d3 / 2) * 10 + 39;
        } else if (func_8001CE14(q->kind, 99, 103)) {
            q->kind = q->flags + (dir / 2) * 10 + 39;
            q->value = q->value + 96;
        }

        cx = ex + D_8006CCD8[(d3 - 2) & 7];
        cy = ey + D_8006CCE8[(d3 - 2) & 7];
        p = &D_800EA000[(cy << st->stride) + cx];
        q = &D_800EA000[((cy + D_8006CCE8[back]) << st->stride) + cx + D_8006CCD8[back]];
        if (func_8001CE14(p->kind, 15, 18)) {
            p->kind = (q->flags >> 1) + (d3 / 2) * 5 + 79;
            p->value = q->value - ((q->flags & 1) << 5);
            if (func_8001CE14(q->kind, 99, 103)) {
                p->value = p->value + 96;
            }
        }
        if (func_8001CE14(q->kind, 19, 28)) {
            q->kind = q->flags + (d3 / 2) * 10 + 39;
        } else if (func_8001CE14(q->kind, 99, 103)) {
            q->kind = q->flags + (dir / 2) * 10 + 39;
            q->value = q->value + 96;
        }
    }

    func_800A6D60(0);
    dir = sdir;
    if (D_800E2970[from].active) {
        hA = D_800EA000[((r1->y + oy1) << st->stride) + r1->x + ox1].value;
    } else {
        hA = D_800EA000[(r1->y << st->stride) + r1->x].value;
    }
    if (D_800E2970[to].active) {
        hB = D_800EA000[((r2->y + oy2) << st->stride) + r2->x + ox2].value;
    } else {
        hB = D_800EA000[(r2->y << st->stride) + r2->x].value;
    }
    if (total == 0) {
        total = 1;
    }
    dh = hB - hA;
    adh = __builtin_abs(dh);
    if ((adh + 31) / 32 > total) {
    ret1:
        return 1;
    }
    step[0] = (adh << 16) / total;
    if (hB < hA) {
        step[0] = -step[0];
    }
    accA[0] = accB[0] = hA << 16;

    a.x = r1->x + ox1;
    a.y = r1->y + oy1;
    a.dir = dir;
    if (D_800E2970[from].active) {
        a.x = a.x + D_8006CCD8[dir];
        a.y = a.y + D_8006CCE8[dir];
    }
    cx = (s16)(from % D_8001F660) + D_8006CCD8[dir];
    cy = (s16)(from / D_8001F660) + D_8006CCE8[dir];
    dx = to % D_8001F660;
    dy = to / D_8001F660;
    for (;;) {
        if (cx == dx && cy == dy) {
            if (D_800E2970[to].active) {
                b.x = r2->x + ox2;
                b.y = r2->y + oy2;
            } else {
                b.x = r2->x;
                b.y = r2->y;
            }
            b.x = b.x - D_8006CCD8[dir1];
            b.y = b.y - D_8006CCE8[dir1];
            if (func_8001C5E4(&a, &b, 1, &rx, &ry, accA, step) < 0) {
                goto ret1;
            }
            a.x = a.x + D_8006CCD8[(dir + 2) & 7];
            a.y = a.y + D_8006CCE8[(dir + 2) & 7];
            b.x = b.x + D_8006CCD8[(dir1 + 2) & 7];
            b.y = b.y + D_8006CCE8[(dir1 + 2) & 7];
            rx = rx - D_8006CCD8[dir];
            ry = ry - D_8006CCE8[dir];
            if (func_8001C5E4(&a, &b, 0, &rx, &ry, accB, step) < 0) {
                goto ret1;
            }
            break;
        }
        idx = cy * D_8001F660 + cx;
        marks[idx] = 2;
        b.x = D_800E2970[idx].x;
        b.y = D_800E2970[idx].y;
        if (func_8001C5E4(&a, &b, 1, &rx, &ry, accA, step) < 0) {
            goto ret1;
        }
        c = a;
        c.x = c.x + D_8006CCD8[(dir + 2) & 7];
        c.y = c.y + D_8006CCE8[(dir + 2) & 7];
        rx = rx - D_8006CCD8[dir];
        ry = ry - D_8006CCE8[dir];
        if (func_8001C5E4(&c, &b, 0, &rx, &ry, accB, step) < 0) {
            goto ret1;
        }
        a.x = b.x;
        a.y = b.y;
        if (D_8006CCD8[dir] != 0) {
            if (cx == dx) {
                a.dir = (func_800A07D0(cx, cy, dx, dy) >> 9) & 6;
            }
        } else {
            if (cy == dy) {
                a.dir = (func_800A07D0(cx, cy, dx, dy) >> 9) & 6;
            }
        }
        cx = cx + D_8006CCD8[a.dir];
        cy = cy + D_8006CCE8[a.dir];
        dir = a.dir;
    }
    return 0;
}
