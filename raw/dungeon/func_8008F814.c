#include "common.h"

typedef struct Slot {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
} Slot;

typedef struct Ent {
    u8 a;
    u8 b;
    u8 pad[10];
} Ent;

typedef struct Sys {
    s32 f0;
    s32 f4;
    s32 f8;
} Sys;

typedef struct Ctx {
    u8 pad0[0xA2];
    u16 flags;
    u8 pad1[0x18];
    void *link;
    u8 pad2[0x3B];
    u8 done;
    s32 total;
    s16 mode;
} Ctx;

typedef struct Item {
    u8 pad[0x24];
    u8 kind;
    u8 sub;
} Item;

typedef struct Unit {
    u8 pad[0x88];
    s16 id;
} Unit;

extern Sys D_80083160;
extern u8 D_80081485[16];
extern u16 D_80013714[8];
extern u16 D_80012094;
extern u16 D_80012096;
extern Slot D_800E3548[];
extern Ent D_800E36C8[];
extern char D_80088A80[];
extern char D_80088A84[];
extern char D_800E0A76[];
extern char D_800E0A83[];
extern char D_800E0A90[];
extern char D_800E0AA1[];
extern char D_800E0ABC[];
extern char D_800E0AD8[];
extern char D_800E0AFA[];
extern char D_800E0B07[];

s32 func_800A70E4(s32, s32, s32);
void func_80095DD0(Ctx *, char *, Item *, Unit *);
s32 func_800990FC(void);
char *func_8009929C(s32, s32);
char *func_80099194(char *, char *);
char *func_80099368(Slot *, char *);
void func_80099290(char *);
void func_800A5720(s32);
s32 func_80098FB0(void);
s32 func_80098FF8(void);
void func_8009F644(Unit *, s32, s32, s32);
u8 *func_8009F868(void);
void func_8009F988(void);
s32 func_800438E4(void);
void func_800B4C7C(s32, Unit *, s32, s32);
void func_8009A3D0(s32, s32, s32);

s32 func_80094F74(Ctx *arg0, char *arg1, Item *arg2, Unit *arg3) {
    Sys *sys;
    s32 ret;
    s16 id;
    char *str;
    s32 handle;
    s32 b;
    s32 a;
    s16 x;
    s16 y;
    s32 v;
    Slot *e;
    Slot *t;
    Slot *t2;
    Slot *t3;
    Slot *t4;
    u16 *pp;
    s32 three;
    void **p;
    u8 *q;
    s32 i;
    s16 j;
    u32 *slot;
    Slot *base0;
    Slot *base1;
    Slot *base2;
    u8 *pagebase;
    u8 *entpage;
    Ent *entbase;
    s32 tb1;

    sys = &D_80083160;
    ret = func_800A70E4(arg2->kind, arg2->sub, arg3->id);
    id = ret;
    if (id < 0) {
        if (arg0->mode < 0) {
            return 1;
        }
        func_80095DD0(arg0, arg1, arg2, arg3);
        return 0;
    }
    handle = func_800990FC();
    str = func_8009929C(8, handle);
    if (D_80081485[0] != 0) {
        func_80099290(func_80099194(D_80088A80, func_80099368(&D_800E3548[id], func_80099194(D_800E0A76, str))));
        func_800A5720(handle);
        return 1;
    }
    a = func_80098FB0();
    b = func_80098FF8();
    if ((D_80013714[0] & 1) == 0) {
        if ((sys->f8 & 0x20) != 0) {
            func_8009F644(arg3, 64, 0, 0);
            func_80099290(func_80099194(D_80088A80, func_80099368(&D_800E3548[id], func_80099194(D_800E0A83, str))));
            func_800A5720(handle);
            return 1;
        }
    } else {
        q = func_8009F868();
        if (q != 0) {
            if ((q[1] & 0xF8) == 0x40) {
                return 1;
            }
            func_8009F988();
        }
    }
    base0 = D_800E3548;
    e = &base0[(s16) ret];
    if ((e->b1 == 14) || ((e->b1 == 12) && (e->b0 == 4)) || ((e->b1 == 18) && (e->b0 == 1))) {
        t = &D_800E3548[(s16) ret];
        str = func_80099368(t, str);
        if (t->b1 == 14) {
            str = func_80099194(D_80088A84, str);
        } else {
            str = func_80099194(D_800E0A90, str);
        }
        base1 = D_800E3548;
        arg0->flags |= 0x80;
        t2 = &base1[(s16) ret];
        tb1 = t2->b1;
        if (tb1 == 12) {
            ASM_USE2(t2, tb1);
            str = func_80099194(D_800E0ABC, func_8009929C(10, func_80099194(D_800E0AA1, func_8009929C(10, str))));
            arg0->done = 1;
            pp = (u16 *) 0x80010000;
            if (D_80012094 != 3) {
                pp[0x104B] = 3;
            } else {
                pp[0x104B] = 5;
            }
            ASM_KEEP(pp);
            *(u16 *) 0x8001209A = 0;
        } else if (tb1 == 14) {
            v = func_800438E4();
            arg0->total += v;
            func_800B4C7C(151, arg3, (s16) v, 1);
        }
        i = (s16) ret;
        slot = (u32 *) 0x80010298;
        base2 = D_800E3548;
        t4 = &base2[i];
        *slot = *(u32 *) t4;
        t4->b0 = 0;
        t4->b1 = 0;
        func_8009A3D0(D_800E36C8[i].a, D_800E36C8[i].b, 0x800);
        arg0->link = slot;
    } else {
        x = a;
        y = b;
        if ((x < 0) || (y < 0)) {
            str = func_80099194(D_80088A80, func_80099368(&D_800E3548[(s16) ret], func_80099194(D_800E0AFA, func_8009929C(10, func_80099194(D_800E0AD8, str)))));
        } else {
            j = ret;
            t3 = &D_800E3548[j];
            str = func_80099194(D_800E0B07, func_80099368(t3, str));
            p = (void **) 0x80010248 + x;
            *p = *(void **) t3;
            pagebase = (u8 *) 0x80010000;
            *(void ***) (pagebase + (y * 4) + 0x29C) = p;
            arg0->flags |= 0x80;
            t3->b0 = 0;
            t3->b1 = 0;
            entpage = (u8 *) 0x800E0000;
            ASM_KEEP_NV(entpage);
            entbase = (Ent *) (entpage + 0x36C8);
            func_8009A3D0(entbase[j].a, entbase[j].b, 0x800);
            arg0->link = p;
        }
    }
    func_80099290(str);
    func_800A5720(handle);
    return 1;
}
