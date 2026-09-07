#include "common.h"

typedef union Fixed32 {
    s32 val;
    struct {
        u16 lo;
        s16 hi;
    } h;
} Fixed32;

typedef struct Motion {
    Fixed32 x;
    Fixed32 y;
    Fixed32 z;
    Fixed32 dx;
    Fixed32 dy;
    Fixed32 dz;
} Motion;

typedef struct Lookup {
    u8 pad00[8];
    void *key;
    u8 pad0C[8];
    u16 flags;
    u8 pad16[14];
    u8 cell_x;
    u8 cell_y;
} Lookup;

typedef struct RootPrefix {
    u8 pad00[8];
    Motion *motion;
    Lookup *lookup;
} RootPrefix;

typedef struct Child {
    u8 pad00[0x10];
    void (*update)(void);
    u8 pad14[0xA];
    u16 flags;
} Child;

typedef struct Controller {
    u8 *root;
    u16 *flags;
    u8 pad08;
    u8 kind;
    s16 state;
    s16 pad0C;
    u16 angle;
    s16 timer;
    s16 pad12;
    s16 active;
    s16 pad16;
    Child *children[8];
    Motion saved;
    Fixed32 target[3];
    u8 pad5C[12];
    s16 cell_x;
    s16 cell_y;
} Controller;

typedef struct LargeFlag {
    u32 value;
    u32 pad[2];
} LargeFlag;

typedef union WideProduct {
    long long value;
    struct {
#ifdef NON_MATCHING
        s32 lower;
        s32 upper;
#else
        s32 upper;
        s32 lower;
#endif
    } word;
} WideProduct;

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern LargeFlag D_800814A0;
extern u32 D_8008346C[3];
extern s32 func_8003DE58();
extern s32 func_800A44E0();
extern s32 func_800BCB04();
extern void func_800247D4();
extern Child *func_80024628();
extern void func_800A56E0();
extern void func_80024060();
extern void func_800244D4(void);

void func_80024C88(Controller *ctrl, Motion *motion, void *arg2)
{
    register Controller *p ASM_REG("$19") = ctrl;
    register Motion *m ASM_REG("$22") = motion;
    register u8 *root ASM_REG("$23");
    register void *third ASM_REG("$5");
    register RootPrefix *prefix ASM_REG("$17");
    register Lookup *lookup ASM_REG("$3");
    Motion *initial;
    register Motion *other ASM_REG("$16");
    Child *child;
    u8 *link;
    s16 delta[3];
    u16 last_y;
    u16 cell_x[1];
    s32 i;
    register s32 diff ASM_REG("$2");
    register void (*update)(void);
    s32 base;
    s32 result;
    register s32 x ASM_REG("$20");
    register s32 y ASM_REG("$21");
    u16 z;
    s32 state;
    u32 tick;
    Child **slot;

    tick = (u16)p->timer;
    state = p->state;
    root = p->root;
    p->timer = tick + 1;
    third = arg2;
    switch (state) {
    case 0:
    p->timer = 0;
    p->state++;
    p->angle = (*(u16 *)(root + 0x2A) >> 9) & 7;
    i = 7;
    slot = &p->children[1];
    do {
        slot[6] = 0;
        i--;
        slot--;
    } while (i >= 0);
    ((s32 *)third)[3] = 0x00808080;

    ASM_KEEP(third);
    case 1:
    prefix = (RootPrefix *)(root - 0x20);
    ASM_KEEP(prefix);
    if (func_8003DE58(prefix->lookup->key, prefix->lookup, delta, 0) == 0) {
        if (!(prefix->lookup->flags & 0x8000)) {
            goto finish;
        }
    }

    initial = prefix->motion;
    m->x.h.hi = initial->x.h.hi;
    m->y.h.hi = initial->y.h.hi;
    z = initial->z.h.hi;
    m->z.h.hi = z;
    if (!(prefix->lookup->flags & 0x8000)) {
        m->x.h.hi += delta[0];
        m->y.h.hi += delta[1];
        m->z.h.hi += delta[2];
    } else {
        m->z.h.hi = z - 64;
    }
    if (!(*p->flags & 0x80)) {
        goto finish;
    }

    p->saved = *m;
    link = *(u8 **)(root + 0x60);
    if (link != 0) {
        s32 div_magic = (s32)0x88880000;
        WideProduct product;

        ASM_KEEP_NV(div_magic);
        other = *(Motion **)(link - 0x18);

        base = m->x.h.hi;
        diff = other->x.h.hi - base;
        if (diff < 0) {
            diff = -diff;
        }
        delta[0] = diff;

        diff = other->y.h.hi;
        diff -= m->y.h.hi;
        if (diff < 0) {
            diff = -diff;
        }
        delta[1] = diff;

        link = *(u8 **)(root + 0x60);
        base = m->z.h.hi;
        diff = *(s16 *)(link + 0x88);
        diff -= base;
        if (diff < 0) {
            diff = -diff;
        }
        delta[2] = diff;

        link = *(u8 **)(root + 0x60);
        lookup = *(Lookup **)(link - 0x14);
        p->cell_x = lookup->cell_x;
        p->cell_y = lookup->cell_y;

        p->target[0].val = other->x.val;
        p->target[1].val = other->y.val;
        diff = *(volatile u16 *)(*(u8 **)(root + 0x60) + 0x88);
        *(volatile u16 *)&p->target[2].h.lo = 0;
        *(volatile u16 *)&p->target[2].h.hi = diff;

        div_magic |= 0x8889;
        diff = *(volatile s32 *)&p->target[0].val;
        diff -= m->x.val;
        product.value = (long long)diff * div_magic;
        m->dx.val = ((s32)((u32)product.word.upper -
                           (0U - (u32)diff)) >> 3) - (diff >> 31);
        diff = *(volatile s32 *)&p->target[1].val;
        diff -= m->y.val;
        product.value = (long long)diff * div_magic;
        m->dy.val = ((s32)((u32)product.word.upper -
                           (0U - (u32)diff)) >> 3) - (diff >> 31);
        diff = *(volatile s32 *)&p->target[2].val;
        diff -= m->z.val;
        product.value = (long long)diff * div_magic;
        m->dz.val = ((s32)((u32)product.word.upper -
                           (0U - (u32)diff)) >> 3) - (diff >> 31);
        goto advance;
    }

    ASM_SCHED_BARRIER();
    i = 0;
    ASM_KEEP(i);
    lookup = prefix->lookup;
    ASM_USE_NV(lookup);
    diff = (s32)0x80070000;
    ASM_USE_NV(diff);
    y = lookup->cell_y;
    x = lookup->cell_x;
    last_y = x;
    cell_x[0] = y;

    do {
        if ((s16)func_800A44E0(((s16)x << 6) & 0xFFC0,
                               ((s16)y << 6) & 0xFFC0,
                               *(s16 *)(root + 0x88),
                               (s16)(p->angle << 9)) != 0) {
            break;
        }

    {
        s16 *xptr;
        s16 *yptr;
        register s32 height ASM_REG("$6");
        s32 ang;
        u16 hraw;

        ang = (s16)p->angle;
        hraw = *(u16 *)(root + 0x88);
        xptr = &D_8006CCD8[ang];
        ASM_SCHED_BARRIER();
        height = (s16)(hraw - 32);
        yptr = &D_8006CCE8[ang];
        result = func_800BCB04((((s16)x + *xptr) << 6) + 32 & 0xFFE0,
                               (((s16)y + *yptr) << 6) + 32 & 0xFFE0,
                               height);
    }
    if ((s16)result >= 513) {
        break;
    }
    if ((s16)(result - *(u16 *)(root + 0x88)) < -63) {
        break;
    }

    {
        register s32 next_x ASM_REG("$4");
        register s32 next_y ASM_REG("$2");
        s16 *xptr;
        s16 *yptr;
        s32 ang;

        ang = (s16)p->angle;
        xptr = &D_8006CCD8[ang];
        i++;
        yptr = &D_8006CCE8[ang];
        next_x = x + (u16)*xptr;
        x = next_x;
        next_y = y + (u16)*yptr;
        y = next_y;
        last_y = next_x;
        cell_x[0] = next_y;
    }
    } while (i < 8);

search_done:
    {
        register Fixed32 *target ASM_REG("$16");

        target = p->target;
        ASM_KEEP(target);
        target[2].val = 0;
        target[1].val = 0;
        p->target[0].val = 0;
        target[0].h.hi = ((last_y << 16) >> 10) + 32;
        target[1].h.hi = ((cell_x[0] << 16) >> 10) + 32;
        target[2].h.hi = -1024;
        target[2].h.hi = func_800BCB04((u16)target[0].h.hi,
                                      (u16)target[1].h.hi, -1024);
        if ((s16)target[2].h.hi >= 513) {
            target[2].h.hi = m->z.h.hi + 32;
        }
    }

    m->dx.val = (p->target[0].val - m->x.val) / 15;
    m->dy.val = (p->target[1].val - m->y.val) / 15;
    m->dz.val = (p->target[2].val - m->z.val) / 15;
    p->cell_x = last_y;
    p->cell_y = cell_x[0];

advance:
    p->timer = 0;
    p->state++;
    goto finish;

    case 2:
    m->x.val += m->dx.val;
    m->y.val += m->dy.val;
    m->z.val += m->dz.val;
    func_800247D4(p, third);
    ASM_KEEP(p);
    if (p->timer < 15) {
        goto finish;
    }
    p->timer = 0;
    p->state++;
    {
        Child **walk;

        i = 7;
        walk = &p->children[1];
        do {
            walk[6] = func_80024628(p, m, (s16)i);
            i--;
            walk--;
        } while (i >= 0);
    }
    func_800A56E0(0x300);
    goto finish;

    case 3:
    i = 7;
    if (p->timer < 33) {
        goto finish;
    }
    update = func_800244D4;
    ASM_KEEP(update);
    p->timer = 0;
    p->state++;
    {
        Child **walk;

        walk = &p->children[1];
        do {
            if (walk[6] != 0) {
                walk[6]->update = update;
            }
            i--;
            walk--;
        } while (i >= 0);
    }
    goto finish;

    case 4:
    if (p->timer < 17) {
        goto finish;
    }
    func_80024060(p->cell_x, p->cell_y, root, p->kind);
    p->timer = 0;
    p->state++;
    {
        register Child **walk ASM_REG("$5");
        register u8 *global_page ASM_REG("$6");

        i = 7;
        global_page = (u8 *)0x80080000;
        walk = &p->children[1];
        ASM_KEEP(walk);
        ASM_KEEP(global_page);
        do {
            child = walk[6];
            if (child != 0) {
                register u16 flags ASM_REG("$2");
                register u32 used ASM_REG("$3");

                flags = child->flags;
                ASM_KEEP(flags);
                used = *(u32 *)(global_page + 0x14A0);
                flags |= 0x8000;
                used |= 0x8000;
                ASM_KEEP(used);
                child->flags = flags;
                *(u32 *)(global_page + 0x14A0) = used;
                walk[6] = 0;
            }
            i--;
            walk--;
        } while (i >= 0);
    }
    goto finish;

    case 5:
    if (p->active == 0) {
        D_8008346C[0] = 0;
        *(u16 *)((u8 *)p - 2) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

    default:
        break;
    }

finish:
    p->active = 0;
}
