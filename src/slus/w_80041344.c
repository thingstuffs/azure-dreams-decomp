#include "common.h"

#include "common.h"

typedef struct {
    u16 cmd;
    u16 size;
    s32 arg0;
    union {
        struct { u16 x, y, w; } t;
        struct { s32 a, b; } m;
    } u;
} S_80041344;

extern void *jtbl_8002D630[];
extern u32 D_80080A8C[3];
extern void func_8004068C(void *src, void *dst);
extern void func_8003F80C(void *src, s32 x, s32 y, s32 flags);
extern void LoadImage(void *rect, void *data);
extern void DrawSync(s32 mode);
extern void *memcpy(void *dst, void *src, s32 size);

void func_80041344(s32 base, void *arg)
{
    S_80041344 *e = (S_80041344 *)base;
    u16 step;
    s32 i, j, n;
    s32 x, y;
    u32 idx;
    register u16 raw_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u16 *walk;
    void *src;
    register void *short_src ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 flags ASM_REG("$7");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    S_80041344 *op;
    void **tbl = jtbl_8002D630;
    static void *const keepalive[] = {
        &&LA, &&LB, &&LC, &&LD, &&LE, &&LF, &&LG, &&LH, &&LI
    };
    (void)keepalive;

    for (;;) {
        idx = e->cmd - 1;
        op = e;
        if (idx >= 9) {
            goto done;
        }
        goto *tbl[idx];

LA:
        func_8004068C((void *)(base + op->arg0), arg);
        LoadImage((void *)&e->u, arg);
        DrawSync(0);
        goto next;
LB:
        LoadImage((void *)&e->u, (void *)(base + op->arg0));
        DrawSync(0);
        goto next;
LC:
        x = e->u.t.x;
        y = e->u.t.y;
        short_src = (void *)op->arg0;
        flags = (s16)e->u.t.w;
        short_src = (void *)(base + (s32)short_src);
        src = short_src;
        goto call_tile;
LD:
        raw_flags = e->u.t.w;
        x = e->u.t.x;
        y = e->u.t.y;
        short_src = (void *)op->arg0;
        raw_flags |= 2;
        short_src = (void *)(base + (s32)short_src);
        src = short_src;
        goto sign_flags;
LE:
        src = (void *)(base + op->arg0);
        n = e->u.t.y << 4;
        walk = (u16 *)src + 1;
        for (j = 1; j < n; j++) {
            *walk |= 0x8000;
            walk++;
        }
        raw_flags = e->u.t.w;
        x = e->u.t.x;
        y = e->u.t.y;
        raw_flags |= 4;
        goto sign_flags;
LF:
        src = (void *)(base + op->arg0);
        walk = (u16 *)src;
        n = e->u.t.y;
        for (j = 0; j < n; j++) {
            walk++;
            for (i = 1; i < 16; i++) {
                *walk |= 0x8000;
                walk++;
            }
        }
        raw_flags = e->u.t.w;
        x = e->u.t.x;
        y = e->u.t.y;
        raw_flags |= 2;
sign_flags:
        flags = (s16)raw_flags;
        ASM_KEEP(raw_flags);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
call_tile:
        func_8003F80C(src, x, y, flags);
        DrawSync(0);
        goto next;
LG:
        short_src = (void *)op->arg0;
        ASM_KEEP(short_src);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        func_8004068C((void *)(base + (s32)short_src),
                      (void *)(D_80080A8C[0] + op->u.m.a));
        goto next;
LH:
        short_src = (void *)0x80080000;
        memcpy((void *)((u32 *)short_src)[0x2A3],
               (void *)(base + op->arg0),
               op->u.m.b + op->u.m.a);
        goto next;
LI:
        n = base + op->arg0;
        for (j = e->u.t.x; j > 0; j--) {
            *(s32 *)(n + 4) = base + *(s32 *)(n + 4);
        }
        goto next;

next:
        step = e->size;
        e = (S_80041344 *)((u8 *)e + step);
        if (step == 0) {
            *(u32 *)0x80080A8C = 0;
            goto done;
        }
    }
done:
    return;
}
