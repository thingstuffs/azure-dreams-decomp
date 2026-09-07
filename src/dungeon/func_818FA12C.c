#include "common.h"


typedef struct {
    s16 x;
    u16 y;
} Copy4;

typedef struct {
    Copy4 entries[8];
} __attribute__((packed)) Copy24;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

typedef struct {
    s32 a;
    s32 b;
} Pair;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    Pair pair;
} OutPair;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Triple;

extern Copy24 D_80024014;
extern Copy12 D_80026668;
extern Copy12 D_80026674;
extern Copy12 D_80026680;
extern Copy12 D_80026698;
extern Copy12 D_800266A4;
extern s16 D_800266BC[5];
extern u8 D_80045340[9];
extern u8 D_80025348[12];
extern u8 D_80025398[12];
extern u8 D_8002558C[12];
extern u8 D_80025648[12];
extern u8 D_8006CCD8[64];
extern u8 D_8006CCE8[64];
extern s32 D_800814A0[3];
extern s32 D_8008346C[2];
extern u8 D_800DDC40[256];
extern u8 D_800E3D68[256];

extern void func_800B835C(void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern s32 func_8002512C(void);
extern void func_80025228(void *, s32, s32, s32, s32, s32, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);
extern void *func_8003FC64(s32);
extern s32 func_8009D218(void *, s32, void *);
extern s32 func_800A6D30(void);
extern void func_800C8A3C(void *, s32, s32);

/* In-row shared tails, spelled as absolute noreturn calls (the row's own true
   range is [0x8002592C, 0x80026668); these are words 834, 157, 247, 359 and
   544 of this same function -- NORETURN-DECL AUDIT case (a)). */
extern void func_80026634(void) __attribute__((noreturn));
extern void func_800261AC(void) __attribute__((noreturn));
extern void func_80025D08(void) __attribute__((noreturn));
extern void func_80025BA0(void) __attribute__((noreturn));
extern void func_80025EC8(void) __attribute__((noreturn));


typedef struct S_818FA12C_0 {
    u8 pad_00[0x8];
    s16 * unk_08;
    u8 * unk_0C;
} S_818FA12C_0;   /* base in func_818FA12C */

typedef struct S_818FA12C_1 {
    u8 pad_00[0x8];
    u32 unk_08;
    union { struct { u32 v; } at00; struct { volatile u8 v; } at00u; struct { u8 v; } at00p; struct { u8 pad[0x1]; volatile u8 v; } at01; struct { u8 pad[0x1]; u8 v; } at01u; struct { u8 pad[0x2]; volatile u8 v; } at02; struct { u8 pad[0x2]; u8 v; } at02u; } unk_0C;   /* overlapping accesses */
    volatile u16 unk_10;
    u8 pad_12[0x2];
    volatile u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    union { volatile u16 v; u16 n; } unk_1C;   /* accessed as both */
    union { volatile u16 v; u16 n; } unk_1E;   /* accessed as both */
} S_818FA12C_1;   /* packet in func_818FA12C */

typedef struct S_818FA12C_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_818FA12C_2_pre;   /* the 0x14 bytes before parent in func_818FA12C, addressed as parent[-1] */

typedef struct S_818FA12C_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { u8 * p; void * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_818FA12C_2;   /* parent in func_818FA12C */

typedef struct S_818FA12C_3 {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
} S_818FA12C_3;   /* colors in func_818FA12C */

typedef struct S_818FA12C_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818FA12C_4;   /* out in func_818FA12C */

typedef struct S_818FA12C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818FA12C_5;   /* table_entry in func_818FA12C */

typedef struct S_818FA12C_6 {
    u8 * unk_00;
} S_818FA12C_6;   /* obj - 0x18 in func_818FA12C */

typedef struct S_818FA12C_7 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_818FA12C_7;   /* src in func_818FA12C */

typedef struct S_818FA12C_8 {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_818FA12C_8;   /* obj_data in func_818FA12C */

typedef struct S_818FA12C_9 {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818FA12C_9;   /* obj2_data in func_818FA12C */

typedef struct S_818FA12C_10 {
    u8 pad_00[0x38];
    u8 unk_38;
} S_818FA12C_10;   /* cursor in func_818FA12C */

typedef struct S_818FA12C_11 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_818FA12C_11;   /* tmpsrc in func_818FA12C */

typedef struct S_818FA12C_12 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_818FA12C_12;   /* ((S_818FA12C_0 *)base)->unk_0C in func_818FA12C */

typedef struct S_818FA12C_13 {
    u16 unk_00;
} S_818FA12C_13;   /* (*(void * *)((u8 *)self + 4)) in func_818FA12C */

typedef struct S_818FA12C_14 {
    u8 * unk_00;
} S_818FA12C_14;   /* ((S_818FA12C_2 *)parent)->unk_60.p - 0x18 in func_818FA12C */

typedef struct S_818FA12C_15 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FA12C_15;   /* ((S_818FA12C_2 *)parent)->unk_60.p in func_818FA12C */

typedef struct S_818FA12C_16 {
    u8 * unk_00;
} S_818FA12C_16;   /* ((S_818FA12C_2 *)parent)->unk_60.p - 0x14 in func_818FA12C */

void func_818FA12C(void *arg0, void *arg1, void *volatile arg2)
{
    u8 *self = arg0;
    u8 *out = arg1;
    register u8 *parent ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *base;
    u8 *src;
    s16 *table_entry;
    OutPair out_pair;
    Copy24 copy;
    s32 state;

    Copy24 *src24;
    src24 = &D_80024014;
    ASM_KEEP(self);   /* MATCH pin: load-bearing for the whole function shape */
    parent = (*(u8 * *)((u8 *)self + 0));
    copy = *src24;
    (*(s16 *)((u8 *)self + 0x0A));
    base = parent - 0x20;
    state = (*(s16 *)((u8 *)self + 0x0A));
    table_entry = ((S_818FA12C_0 *)base)->unk_08;
    switch (state) {

case 0:
    {
        register u8 *packet ASM_REG("$9") = arg2;   /* MATCH pin: load-bearing for the whole function shape */
        s32 magic_a;
        s32 magic_b;
        s32 call_zero;
        u8 *colors;
        s32 value;
        ((S_818FA12C_1 *)packet)->unk_0C.at00.v = 0x00808080;
        magic_a = 0x1400340;
        call_zero = 0;
        ASM_KEEP(call_zero);   /* MATCH pin: keeps a statement from moving across a call/branch */
        (*(Copy12 *)((u8 *)self + 0xA2)) = D_80026698;
        magic_b = 0x400040;
        colors = (u8 *)&D_800266A4;
        ((S_818FA12C_1 *)packet)->unk_08 = (u32)(self + 0xA2);
        (*(u16 *)((u8 *)self + 0x7E)) = (((S_818FA12C_2 *)parent)->unk_2A >> 9) & 7;
        ((S_818FA12C_3 *)colors)->unk_10 = 0x80;
        ((S_818FA12C_3 *)colors)->unk_11 = 0x80;
        ((S_818FA12C_3 *)colors)->unk_12 = 0x80;
        ((S_818FA12C_3 *)colors)->unk_14 = 4;
        ((S_818FA12C_3 *)colors)->unk_15 = 4;
        ((S_818FA12C_3 *)colors)->unk_16 = 4;
        out_pair.pair.a = magic_a;
        out_pair.pair.b = magic_b;
        func_800B835C(colors, &out_pair.pair, 1, call_zero);
        value = (*(u16 *)((u8 *)self + 0x0A));
        D_800266BC[0] = 1;
        (*(u16 *)((u8 *)self + 0x0A)) = value + 1;
    }

case 1:
    {
    u8 *obj;
    u8 *obj_data;
    s16 index;
    s32 value;
    s32 value2;
    s32 value3;
    s32 tz;
    register s32 flags ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 sqa ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 sqb ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u32 uvalue;
    s32 diff;
    register s32 prod ASM_REG("$9");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *packet ASM_REG("$9");   /* MATCH pin: load-bearing for the whole function shape */

    value = func_8003DF74(((S_818FA12C_12 *)(((S_818FA12C_0 *)base)->unk_0C))->unk_08,
                          ((S_818FA12C_0 *)base)->unk_0C, &out_pair, 0);
    if (value == 0 && !(((S_818FA12C_12 *)(((S_818FA12C_0 *)base)->unk_0C))->unk_14 & 0x8000)) {
        goto done;
    }
    ((S_818FA12C_4 *)out)->unk_00.at02.v = ((S_818FA12C_5 *)table_entry)->unk_02;
    ((S_818FA12C_4 *)out)->unk_04.at02.v = ((S_818FA12C_5 *)table_entry)->unk_06;
    tz = ((S_818FA12C_5 *)table_entry)->unk_0A;
    ((S_818FA12C_4 *)out)->unk_08.at02.v = tz;
    if (!(((S_818FA12C_12 *)(((S_818FA12C_0 *)base)->unk_0C))->unk_14 & 0x8000)) {
        ((S_818FA12C_4 *)out)->unk_00.at02.v += out_pair.x;
        ((S_818FA12C_4 *)out)->unk_04.at02.v += out_pair.y;
        value3 = ((S_818FA12C_4 *)out)->unk_08.at02.v + out_pair.z;
        ASM_TAILSLOT_PIN(value3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80025BA0();
    } else {
        ASM_SCHED_BARRIER();   /* reorg CALL+BARRIER flip: keep the bnez slot a nop */
        ((S_818FA12C_4 *)out)->unk_08.at02.v = tz - 0x40;
    }
    if (!(((S_818FA12C_13 *)((*(void * *)((u8 *)self + 4))))->unk_00 & 0x80)) {
        goto done;
    }
    if (!((*(u8 *)((u8 *)self + 0x7A)) & 4)) {
        func_8004491C(self - 0x20, D_80045340);
        packet = arg2;
        ((S_818FA12C_1 *)packet)->unk_10 = 0x20;
        ((S_818FA12C_1 *)packet)->unk_0C.at02.v = 0x20;
        ((S_818FA12C_1 *)packet)->unk_0C.at00u.v = 0x20;
        flags = ((S_818FA12C_1 *)packet)->unk_14;
        ((S_818FA12C_1 *)packet)->unk_0C.at01.v = 0xE0;
        ((S_818FA12C_1 *)packet)->unk_1E.v = 2000;
        ((S_818FA12C_1 *)packet)->unk_1C.v = 2000;
        flags |= 0x0C;
        ((S_818FA12C_1 *)packet)->unk_14 = flags;
        flags &= 0xFFFC;
        ((S_818FA12C_1 *)packet)->unk_14 = flags;
        (*(u8 *)((u8 *)self + 0x7A)) |= 4;
    }
    if ((obj = ((S_818FA12C_2 *)parent)->unk_60.p) != 0) {
        src = ((S_818FA12C_6 *)(obj - 0x18))->unk_00;
        uvalue = D_800DDC40[(*(u8 *)((u8 *)obj + 0x13))];
        (*(u16 *)((u8 *)self + 0x78)) = ((S_818FA12C_7 *)src)->unk_08.at02.v - (uvalue >> 1);
        obj_data = ((S_818FA12C_2_pre *)parent)[-1].unk_00;
        (*(u8 *)((u8 *)self + 0xBA)) = ((S_818FA12C_8 *)obj_data)->unk_24
                                + D_8006CCD8[(*(s16 *)((u8 *)self + 0x7E)) * 2];
        (*(u8 *)((u8 *)self + 0xBB)) = ((S_818FA12C_8 *)obj_data)->unk_25
                                + D_8006CCE8[(*(s16 *)((u8 *)self + 0x7E)) * 2];
        flags = (s8)((S_818FA12C_2 *)parent)->unk_72;
        if (flags != ((S_818FA12C_8 *)obj_data)->unk_24) {
            diff = flags - ((S_818FA12C_8 *)obj_data)->unk_24;
        } else {
            flags = (s8)((S_818FA12C_2 *)parent)->unk_73;
            diff = flags - ((S_818FA12C_8 *)obj_data)->unk_25;
        }
        if (diff < 0) {
            diff = -diff;
        }
        (*(u8 *)((u8 *)self + 0x7B)) = diff * 2 - 1;
        func_80025D08();
    } else {
        (*(u16 *)((u8 *)self + 0x78)) = ((S_818FA12C_2 *)parent)->unk_88 - 0x50;
        (*(u8 *)((u8 *)self + 0x7B)) = 0x20;
    }
    ASM_SCHED_BARRIER();   /* block boundary the deleted join label used to give */
    ((S_818FA12C_4 *)out)->unk_0C = (s32)copy.entries[(*(s16 *)((u8 *)self + 0x7E))].x << 16;
    ((S_818FA12C_4 *)out)->unk_10 = (u32)copy.entries[(*(s16 *)((u8 *)self + 0x7E))].y << 16;
    ((S_818FA12C_4 *)out)->unk_14 = (((s32)(*(s16 *)((u8 *)self + 0x78)) << 16) - ((S_818FA12C_4 *)out)->unk_08.at00.v)
                             / (s8)(*(u8 *)((u8 *)self + 0x7B));
    (*(u16 *)((u8 *)self + 0x82)) = 0;
    (*(u16 *)((u8 *)self + 0x90)) = 0;
    (*(u16 *)((u8 *)self + 0x92)) = 0;
    (*(u16 *)((u8 *)self + 0x94)) = 5;
    (*(u16 *)((u8 *)self + 0x96)) = 200;
    (*(u16 *)((u8 *)self + 0x0A))++;
    (*(s16 *)((u8 *)self + 0x88)) = (s8)(*(u8 *)((u8 *)self + 0x7B));
    value = (*(u8 *)((u8 *)self + 0x7B)) << 24;
    ASM_KEEP_NV(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    sqa = value >> 24;
    sqb = sqa;
    ASM_KEEP_NV(sqb);   /* MATCH pin: retail delay-slot fill depends on it */
    prod = sqa * sqb;
    (*(s16 *)((u8 *)self + 0x8A)) = prod;
    func_80026634();
    }

case 2:
    {
    s32 i;
    s32 random;
    s32 value;
    register s32 angle ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s16 count;
    s32 phase90;
    register u8 *obj ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *obj2 ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *obj2_data;
    register u8 *obj_hdr ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *aim;
    void *link2;
    register s32 flg2 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *obj_data;
    register s32 *vec ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *cursor;

    i = 0;
    do {
        u8 *a0v;   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 a1v;
        s32 a2v;   /* MATCH pin: retail basic-block layout depends on it */
        s32 a3v;
        random = func_80069EF8();
        a0v = self - 0x20;
        a2v = 0x40E020;
        a3v = (random & 0xFF) | 0x80;
        a1v = (*(s16 *)((u8 *)self + 0x7E));
        func_80025228(a0v, a1v, a2v, a3v, 0, 0, 0);
        i++;
    } while (i < 8);
    value = func_800A4778(((S_818FA12C_4 *)out)->unk_00.at02.v, ((S_818FA12C_4 *)out)->unk_04.at02.v,
                          ((S_818FA12C_4 *)out)->unk_08.at02u.v, ((S_818FA12C_2 *)parent)->unk_60.p2);
    if (value << 16) {
        register u8 *packet ASM_REG("$9");   /* MATCH pin: load-bearing for the whole function shape */
        (*(u16 *)((u8 *)self + 0x0A)) = 8;
        (*(u16 *)((u8 *)self + 0x82)) = 0;
        packet = arg2;
        ((S_818FA12C_1 *)packet)->unk_0C.at02u.v = 0;
        ((S_818FA12C_1 *)packet)->unk_0C.at01u.v = 0;
        ((S_818FA12C_1 *)packet)->unk_0C.at00p.v = 0;
        func_80026634();
    }
    {
    register u8 *packet ASM_REG("$9") = arg2;   /* MATCH pin: load-bearing for the whole function shape */
    s32 sum1e;
    angle = ((S_818FA12C_1 *)packet)->unk_1A + 0x400;
    ASM_KEEP(angle);   /* MATCH pin: load-bearing for the whole function shape */
    if (angle >= 0x1001) {
        angle -= 0x1000;
    }
    ((S_818FA12C_1 *)packet)->unk_1A = angle;
    phase90 = (*(s16 *)((u8 *)self + 0x90));
    if (phase90 == 0) {
        ((S_818FA12C_1 *)packet)->unk_1C.n += (*(u16 *)((u8 *)self + 0x96));
        sum1e = ((S_818FA12C_1 *)packet)->unk_1E.n + (*(u16 *)((u8 *)self + 0x96));
        ASM_TAILSLOT_PIN(sum1e);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80025EC8();
    } else {
        packet = arg2;
        ((S_818FA12C_1 *)packet)->unk_1C.n -= (*(u16 *)((u8 *)self + 0x96));
        ((S_818FA12C_1 *)packet)->unk_1E.n -= (*(u16 *)((u8 *)self + 0x96));
    }
    }
    count = (*(s16 *)((u8 *)self + 0x92)) + 1;
    (*(s16 *)((u8 *)self + 0x92)) = count;
    if (count >= (*(s16 *)((u8 *)self + 0x94))) {
        (*(s16 *)((u8 *)self + 0x92)) = 0;
        (*(s16 *)((u8 *)self + 0x90)) ^= 1;
    }
    (*(u8 *)((u8 *)self + 0x7B))--;
    if ((s8)(*(u8 *)((u8 *)self + 0x7B)) > 0) {
        goto update_position;
    }
    if (((S_818FA12C_2 *)parent)->unk_60.p == 0) {
        goto missing_target;
    }
    (*(u16 *)((u8 *)self + 0x0A)) = 3;
    (*(u16 *)((u8 *)self + 0x82)) = 0;
    src = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
    ((S_818FA12C_4 *)out)->unk_00.at02.v = ((S_818FA12C_7 *)src)->unk_00.at02.v;
    ((S_818FA12C_4 *)out)->unk_04.at02.v = ((S_818FA12C_7 *)src)->unk_04.at02.v;
    ((S_818FA12C_4 *)out)->unk_08.at02.v = ((S_818FA12C_7 *)src)->unk_08.at02.v - D_800DDC40[((S_818FA12C_15 *)(((S_818FA12C_2 *)parent)->unk_60.p))->unk_13];
    func_800A56E0(0x300);
    obj2 = func_8003FC64(0x212);
    if (obj2 != 0) {
        (*(u16 *)((u8 *)obj2 + 0x22)) = 120;
        (*(u32 *)((u8 *)obj2 + 0x10)) = (u32)D_80025348;
        func_8004491C(obj2, D_80045340);
        obj2_data = (*(u8 * *)((u8 *)obj2 + 0x0C));
        ((S_818FA12C_9 *)obj2_data)->unk_14 |= 0x0C;
        ((S_818FA12C_9 *)obj2_data)->unk_10 = 0;
        ((S_818FA12C_9 *)obj2_data)->unk_06 = 0;
        ((S_818FA12C_9 *)obj2_data)->unk_14 |= 0x80;
        src = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
        vec = (*(s32 * *)((u8 *)obj2 + 8));
        vec[0] = ((S_818FA12C_7 *)src)->unk_00.at00.v;
        vec[1] = ((S_818FA12C_7 *)src)->unk_04.at00.v;
        vec[2] = ((S_818FA12C_7 *)src)->unk_08.at00.v;
        obj2_data = (*(u8 * *)((u8 *)obj2 + 0x0C));
        ((S_818FA12C_9 *)obj2_data)->unk_1E = 0x1000;
        ((S_818FA12C_9 *)obj2_data)->unk_1C = 0x1000;
        ((S_818FA12C_9 *)obj2_data)->unk_0E = 0x80;
        ((S_818FA12C_9 *)obj2_data)->unk_0D = 0x80;
        ((S_818FA12C_9 *)obj2_data)->unk_0C = 0x80;
        (*(Copy12 *)((u8 *)obj2 + 0x3A)) = D_80026680;
        ((S_818FA12C_9 *)obj2_data)->unk_08 = obj2 + 0x3A;
    }
    obj = func_8003FC64(0x212);
    if (obj == 0) {
        goto cleanup_packet;
    }
    obj_hdr = obj + 0x20;
    i = 95;
    cursor = obj_hdr + 95;
    (*(u16 *)((u8 *)obj_hdr + 2)) = 0x50;
    (*(u16 *)((u8 *)obj_hdr + 0x0A)) = 0x14;
    (*(u16 *)((u8 *)obj_hdr + 4)) = 0;
    (*(void * *)((u8 *)obj_hdr + 0x28)) = parent;
    (*(void * *)((u8 *)obj_hdr + 0x2C)) = ((S_818FA12C_2 *)parent)->unk_60.p2;
    (*(void * *)((u8 *)obj_hdr + 0x30)) = self;
    aim = obj2 + 0x20;
    (*(void * *)((u8 *)obj_hdr + 0x34)) = aim;
    ASM_USE(obj2);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    for (; i >= 0; i--) {
        ((S_818FA12C_10 *)cursor)->unk_38 = 0;
        cursor--;
    }
    i = 96;
    (*(u16 *)((u8 *)obj_hdr + 0x9A)) = 0;
    (*(u32 *)((u8 *)obj + 0x10)) = (u32)D_80025398;
    func_8004491C(obj, D_80045340);
    obj_data = (*(u8 * *)((u8 *)obj + 0x0C));
    flg2 = 0x0C;
    ((S_818FA12C_8 *)obj_data)->unk_14 = flg2;
    ((S_818FA12C_8 *)obj_data)->unk_10.s = i;
    ((S_818FA12C_8 *)obj_data)->unk_06 = 6;
    ((S_818FA12C_8 *)obj_data)->unk_14 = flg2 | 0x80;
    vec = (*(s32 * *)((u8 *)obj + 8));
    vec[0] = ((S_818FA12C_4 *)out)->unk_00.at00.v;
    vec[1] = ((S_818FA12C_4 *)out)->unk_04.at00.v;
    vec[2] = ((S_818FA12C_4 *)out)->unk_08.at00.v + 0x400000;
    obj_data = (*(u8 * *)((u8 *)obj + 0x0C));
    ((S_818FA12C_8 *)obj_data)->unk_1C = 0x2000;
    ((S_818FA12C_8 *)obj_data)->unk_1E = 0x1800;
    ((S_818FA12C_8 *)obj_data)->unk_0E = 0;
    ((S_818FA12C_8 *)obj_data)->unk_0D = 0;
    ((S_818FA12C_8 *)obj_data)->unk_0C = 0;
    (*(Copy12 *)((u8 *)obj_hdr + 0x1A)) = D_80026674;
    link2 = obj_hdr + 0x1A;
    ASM_USE(obj_hdr);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ((S_818FA12C_8 *)obj_data)->unk_08 = link2;
    func_800261AC();
    }

missing_target:
    (*(u16 *)((u8 *)self + 0x0A)) = 8;
    (*(u16 *)((u8 *)self + 0x82)) = 0;

cleanup_packet:
    {
        register u8 *packet ASM_REG("$9") = arg2;   /* MATCH pin: load-bearing for the whole function shape */
        ((S_818FA12C_1 *)packet)->unk_0C.at02u.v = 0;
        ((S_818FA12C_1 *)packet)->unk_0C.at01u.v = 0;
        ((S_818FA12C_1 *)packet)->unk_0C.at00p.v = 0;
        ((S_818FA12C_1 *)packet)->unk_1E.n = 0;
        ((S_818FA12C_1 *)packet)->unk_1C.n = 0;
        func_80026634();
    }

update_position:
    ((S_818FA12C_4 *)out)->unk_00.at00.v += ((S_818FA12C_4 *)out)->unk_0C;
    ((S_818FA12C_4 *)out)->unk_04.at00.v += ((S_818FA12C_4 *)out)->unk_10;
    ((S_818FA12C_4 *)out)->unk_08.at00.v += ((S_818FA12C_4 *)out)->unk_14;
    func_80026634();

case 3:
    {
    s16 count;
    u8 *obj;
    register u8 *obj_header ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *obj_data;
    register s32 *vec ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *cursor;
    s32 value;
    register s32 i ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    count = (*(u16 *)((u8 *)self + 0x82)) + 1;
    (*(u16 *)((u8 *)self + 0x82)) = count;
    if ((s16)count != 4) {
        goto done;
    }
    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj_header = obj + 0x20;
        i = 95;
        (*(void * *)((u8 *)obj_header + 0x28)) = parent;
        (*(void * *)((u8 *)obj_header + 0x2C)) = ((S_818FA12C_2 *)parent)->unk_60.p2;
        (*(void * *)((u8 *)obj_header + 0x30)) = self;
        cursor = obj_header + 95;
        for (; i >= 0; i--) {
            ((S_818FA12C_10 *)cursor)->unk_38 = 0;
            cursor--;
        }
        (*(u16 *)((u8 *)obj_header + 0x9A)) = 0;
        (*(u32 *)((u8 *)obj + 0x10)) = (u32)D_80025648;
        func_8004491C(obj, D_80045340);
        obj_data = (*(u8 * *)((u8 *)obj + 0x0C));
        value = ((S_818FA12C_8 *)obj_data)->unk_14 & 0xFFF3;
        ((S_818FA12C_8 *)obj_data)->unk_14 = value;
        ((S_818FA12C_8 *)obj_data)->unk_10.u = 0x20;
        ((S_818FA12C_8 *)obj_data)->unk_14 = value | 0x80;
        src = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
        vec = (*(s32 * *)((u8 *)obj + 8));
        vec[0] = ((S_818FA12C_7 *)src)->unk_00.at00.v;
        vec[1] = ((S_818FA12C_7 *)src)->unk_04.at00.v;
        vec[2] = ((S_818FA12C_7 *)src)->unk_08.at00.v;
        obj_data = (*(u8 * *)((u8 *)obj + 0x0C));
        ((S_818FA12C_8 *)obj_data)->unk_1E = 0x1000;
        ((S_818FA12C_8 *)obj_data)->unk_1C = 0x1000;
        ((S_818FA12C_8 *)obj_data)->unk_0E = 0x80;
        ((S_818FA12C_8 *)obj_data)->unk_0D = 0x80;
        ((S_818FA12C_8 *)obj_data)->unk_0C = 0x80;
        (*(Copy12 *)((u8 *)obj_header + 0x1A)) = D_80026668;
    ((S_818FA12C_8 *)obj_data)->unk_08 = obj_header + 0x1A;
    ASM_USE(obj_header);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    }
    if ((s16)(*(u16 *)((u8 *)self + 0x82)) != 4) {
        goto done;
    }
    (*(u16 *)((u8 *)self + 0x0A)) = 4;
    (*(u16 *)((u8 *)self + 0x82)) = 0;
    (*(u16 *)((u8 *)self + 0x9C)) = 0;
    func_80026634();
    }

case 4:
    {
    s16 count;
    register u8 *obj ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *obj_data;
    register u8 *obj_hdr ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 *vec ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *tmpsrc;
    s32 rnd2;
    s32 amt;
    s32 random;
    s32 random3;
    register s32 prod ASM_REG("$9");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 shifted ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 value;
    s16 phase;
    s32 tbyte;

    count = (*(u16 *)((u8 *)self + 0x82)) + 1;
    (*(u16 *)((u8 *)self + 0x82)) = count;
    if ((count & 3) != 0 || (s16)count >= 80) {
        goto case_4_tail;
    }
    obj = func_8003FC64(0x212);
    if (obj == 0) {
        goto case_4_tail;
    }
    obj_hdr = obj + 0x20;
    (*(u16 *)((u8 *)obj_hdr + 2)) = 20;
    (*(u16 *)((u8 *)obj_hdr + 0x0A)) = 10;
    (*(u16 *)((u8 *)obj_hdr + 4)) = 0;
    (*(u32 *)((u8 *)obj + 0x10)) = (u32)D_8002558C;
    func_8004491C(obj, D_80045340);
    obj_data = (*(u8 * *)((u8 *)obj + 0x0C));
    ((S_818FA12C_8 *)obj_data)->unk_10.u = 0x20;
    ((S_818FA12C_8 *)obj_data)->unk_14 |= 0x0C;
    src = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
    vec = (*(s32 * *)((u8 *)obj + 8));
    random = func_80069EF8();
    value = func_8002512C();
    random &= 0x1F;
    random += 16;
    prod = random * value;
    shifted = prod << 16;
    vec[0] = ((S_818FA12C_7 *)src)->unk_00.at00.v + shifted;
    random = func_80069EF8();
    value = func_8002512C();
    random &= 0x1F;
    random += 16;
    prod = random * value;
    shifted = prod << 16;
    vec[1] = ((S_818FA12C_7 *)src)->unk_04.at00.v + shifted;
    random3 = func_80069EF8();
    vec[2] = ((S_818FA12C_7 *)src)->unk_08.at00.v
             - (D_800DDC40[((S_818FA12C_2 *)parent)->unk_60.p[0x13]] << 15)
             - ((random3 & 0x1F) << 16);
    obj_data = (*(u8 * *)((u8 *)obj + 0x0C));
    tmpsrc = ((S_818FA12C_16 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x14))->unk_00;
    ((S_818FA12C_8 *)obj_data)->unk_1C = ((S_818FA12C_11 *)tmpsrc)->unk_1C >> 1;
    ((S_818FA12C_8 *)obj_data)->unk_1E = ((S_818FA12C_11 *)tmpsrc)->unk_1E >> 1;
    ((S_818FA12C_8 *)obj_data)->unk_0E = 0;
    ((S_818FA12C_8 *)obj_data)->unk_0D = 0;
    ((S_818FA12C_8 *)obj_data)->unk_0C = 0;
    (*(Copy12 *)((u8 *)obj + 0x3A)) = D_80026668;
    ((S_818FA12C_8 *)obj_data)->unk_08 = obj + 0x3A;
    ASM_USE(obj);   /* MATCH pin: retail callee-saved set / frame layout depends on it */

case_4_tail:
    if ((s16)(*(u16 *)((u8 *)self + 0x82)) == 80) {
        if (func_8009D218(((S_818FA12C_2 *)parent)->unk_60.p2, 4, parent) == 0) {
            rnd2 = func_800A6D30();
            value = (*(u8 *)((u8 *)self + 9)) >> 2;
            rnd2 = (rnd2 & 3) + 4;
            amt = value + rnd2;
            if (D_800E3D68[0] == 0xFF) {
                phase = 0xFF;
            } else {
                phase = 16;
            }
            func_800C8A3C(((S_818FA12C_2 *)parent)->unk_60.p2, phase, amt);
        }
    }
    if ((s16)(*(u16 *)((u8 *)self + 0x82)) < 120) {
        func_80026634();
    }
    goto state_advance;
    }

case 5:
    {
    if ((*(s16 *)((u8 *)self + 0x9C)) == 0) {
        goto done;
    }
    }

state_advance:
    (*(u16 *)((u8 *)self + 0x0A))++;
    (*(u16 *)((u8 *)self + 0x82)) = 0;
    func_80026634();

case 6:
    {
    s16 count;
    count = (*(u16 *)((u8 *)self + 0x82)) + 1;
    (*(u16 *)((u8 *)self + 0x82)) = count;
    if ((s16)count < 11) {
        goto done;
    }
    (*(u16 *)((u8 *)self + 0x0A)) = 8;
    (*(u16 *)((u8 *)self + 0x82)) = 30;
    func_80026634();
    }

case 8:
    {
    s16 count;
    s32 flag;
    count = (*(u16 *)((u8 *)self + 0x82));
    (*(u16 *)((u8 *)self + 0x82)) = count + 1;
    if ((s16)(count + 1) < 31) {
        goto done;
    }
    flag = D_800266BC[0];
    (*(u16 *)((u8 *)self + 0x82)) = count;
    if (flag == 0) {
        D_8008346C[0] = 0;
        (*(u16 *)((u8 *)self + -2)) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80026634();
    }
    D_800266BC[0] = 0;
    goto done;
    }

case 7:
default:
    goto done;
    }

done:
    return;
}
