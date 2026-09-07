#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

void func_818FA12C(void *arg0, void *arg1, void *volatile arg2)
{
    register u8 *self ASM_REG("$22") = arg0;
    u8 *out = arg1;
    register u8 *parent ASM_REG("$23");
    u8 *base;
    register u8 *src ASM_REG("$17");
    register s16 *table_entry ASM_REG("$17");
    OutPair out_pair;
    Copy24 copy;
    s32 state;

    Copy24 *src24;
    src24 = &D_80024014;
    ASM_KEEP(self);
    parent = FIELD(self, u8 *, 0);
    copy = *src24;
    FIELD(self, s16, 0x0A);
    base = parent - 0x20;
    state = FIELD(self, s16, 0x0A);
    table_entry = FIELD(base, s16 *, 8);
    switch (state) {

case 0:
    {
        register u8 *packet ASM_REG("$9") = arg2;
        register s32 magic_a ASM_REG("$8");
        s32 magic_b;
        register s32 call_zero ASM_REG("$7");
        u8 *colors;
        s32 value;
        FIELD(packet, u32, 0x0C) = 0x00808080;
        magic_a = 0x1400340;
        call_zero = 0;
        ASM_KEEP(magic_a);
        ASM_KEEP(call_zero);
        FIELD(self, Copy12, 0xA2) = D_80026698;
        magic_b = 0x400040;
        colors = (u8 *)&D_800266A4;
        FIELD(packet, u32, 8) = (u32)(self + 0xA2);
        FIELD(self, u16, 0x7E) = (FIELD(parent, u16, 0x2A) >> 9) & 7;
        FIELD(colors, u8, 0x10) = 0x80;
        FIELD(colors, u8, 0x11) = 0x80;
        FIELD(colors, u8, 0x12) = 0x80;
        FIELD(colors, u8, 0x14) = 4;
        FIELD(colors, u8, 0x15) = 4;
        FIELD(colors, u8, 0x16) = 4;
        out_pair.pair.a = magic_a;
        out_pair.pair.b = magic_b;
        func_800B835C(colors, &out_pair.pair, 1, call_zero);
        value = FIELD(self, u16, 0x0A);
        D_800266BC[0] = 1;
        FIELD(self, u16, 0x0A) = value + 1;
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
    register s32 flags ASM_REG("$2");
    register s32 sqa ASM_REG("$3");
    register s32 sqb ASM_REG("$2");
    u32 uvalue;
    s32 diff;
    register s32 prod ASM_REG("$9");
    register u8 *packet ASM_REG("$9");

    value = func_8003DF74(FIELD(FIELD(base, u8 *, 0x0C), void *, 8),
                          FIELD(base, u8 *, 0x0C), &out_pair, 0);
    if (value == 0 && !(FIELD(FIELD(base, u8 *, 0x0C), u16, 0x14) & 0x8000)) {
        goto done;
    }
    FIELD(out, u16, 2) = FIELD(table_entry, u16, 2);
    FIELD(out, u16, 6) = FIELD(table_entry, u16, 6);
    tz = FIELD(table_entry, u16, 0x0A);
    FIELD(out, u16, 0x0A) = tz;
    if (!(FIELD(FIELD(base, u8 *, 0x0C), u16, 0x14) & 0x8000)) {
        FIELD(out, u16, 2) += out_pair.x;
        FIELD(out, u16, 6) += out_pair.y;
        value3 = FIELD(out, u16, 0x0A) + out_pair.z;
        ASM_TAILSLOT_PIN(value3);
        func_80025BA0();
    } else {
        ASM_SCHED_BARRIER();   /* reorg CALL+BARRIER flip: keep the bnez slot a nop */
        FIELD(out, u16, 0x0A) = tz - 0x40;
    }
    if (!(FIELD(FIELD(self, void *, 4), u16, 0) & 0x80)) {
        goto done;
    }
    if (!(FIELD(self, u8, 0x7A) & 4)) {
        func_8004491C(self - 0x20, D_80045340);
        packet = arg2;
        FIELD(packet, volatile u16, 0x10) = 0x20;
        FIELD(packet, volatile u8, 0x0E) = 0x20;
        FIELD(packet, volatile u8, 0x0C) = 0x20;
        flags = FIELD(packet, volatile u16, 0x14);
        FIELD(packet, volatile u8, 0x0D) = 0xE0;
        FIELD(packet, volatile u16, 0x1E) = 2000;
        FIELD(packet, volatile u16, 0x1C) = 2000;
        flags |= 0x0C;
        FIELD(packet, volatile u16, 0x14) = flags;
        flags &= 0xFFFC;
        FIELD(packet, volatile u16, 0x14) = flags;
        FIELD(self, u8, 0x7A) |= 4;
    }
    if ((obj = FIELD(parent, u8 *, 0x60)) != 0) {
        src = FIELD(obj - 0x18, u8 *, 0);
        uvalue = D_800DDC40[FIELD(obj, u8, 0x13)];
        FIELD(self, u16, 0x78) = FIELD(src, u16, 0x0A) - (uvalue >> 1);
        obj_data = FIELD(parent, u8 *, -0x14);
        FIELD(self, u8, 0xBA) = FIELD(obj_data, u8, 0x24)
                                + D_8006CCD8[FIELD(self, s16, 0x7E) * 2];
        FIELD(self, u8, 0xBB) = FIELD(obj_data, u8, 0x25)
                                + D_8006CCE8[FIELD(self, s16, 0x7E) * 2];
        flags = (s8)FIELD(parent, u8, 0x72);
        if (flags != FIELD(obj_data, u8, 0x24)) {
            diff = flags - FIELD(obj_data, u8, 0x24);
        } else {
            flags = (s8)FIELD(parent, u8, 0x73);
            diff = flags - FIELD(obj_data, u8, 0x25);
        }
        if (diff < 0) {
            diff = -diff;
        }
        FIELD(self, u8, 0x7B) = diff * 2 - 1;
        func_80025D08();
    } else {
        FIELD(self, u16, 0x78) = FIELD(parent, u16, 0x88) - 0x50;
        FIELD(self, u8, 0x7B) = 0x20;
    }
    ASM_SCHED_BARRIER();   /* block boundary the deleted join label used to give */
    FIELD(out, s32, 0x0C) = (s32)copy.entries[FIELD(self, s16, 0x7E)].x << 16;
    FIELD(out, s32, 0x10) = (u32)copy.entries[FIELD(self, s16, 0x7E)].y << 16;
    FIELD(out, s32, 0x14) = (((s32)FIELD(self, s16, 0x78) << 16) - FIELD(out, s32, 8))
                             / (s8)FIELD(self, u8, 0x7B);
    FIELD(self, u16, 0x82) = 0;
    FIELD(self, u16, 0x90) = 0;
    FIELD(self, u16, 0x92) = 0;
    FIELD(self, u16, 0x94) = 5;
    FIELD(self, u16, 0x96) = 200;
    FIELD(self, u16, 0x0A)++;
    FIELD(self, s16, 0x88) = (s8)FIELD(self, u8, 0x7B);
    value = FIELD(self, u8, 0x7B) << 24;
    ASM_KEEP_NV(value);
    sqa = value >> 24;
    sqb = sqa;
    ASM_KEEP_NV(sqb);
    prod = sqa * sqb;
    FIELD(self, s16, 0x8A) = prod;
    func_80026634();
    }

case 2:
    {
    register s32 i ASM_REG("$16");
    s32 random;
    s32 value;
    register s32 angle ASM_REG("$3");
    s16 count;
    s32 phase90;
    register u8 *obj ASM_REG("$20");
    register u8 *obj2 ASM_REG("$21");
    register u8 *obj2_data ASM_REG("$7");
    register u8 *obj_hdr ASM_REG("$19");
    void *aim;
    void *link2;
    register s32 flg2 ASM_REG("$2");
    u8 *obj_data;
    register s32 *vec ASM_REG("$18");
    u8 *cursor;

    i = 0;
    do {
        register u8 *a0v ASM_REG("$4");
        register s32 a1v ASM_REG("$5");
        register s32 a2v ASM_REG("$6");
        register s32 a3v ASM_REG("$7");
        random = func_80069EF8();
        a0v = self - 0x20;
        a2v = 0x40E020;
        ASM_KEEP_NV(a2v);
        a3v = (random & 0xFF) | 0x80;
        ASM_KEEP_NV(a3v);
        a1v = FIELD(self, s16, 0x7E);
        func_80025228(a0v, a1v, a2v, a3v, 0, 0, 0);
        i++;
    } while (i < 8);
    value = func_800A4778(FIELD(out, u16, 2), FIELD(out, u16, 6),
                          FIELD(out, s16, 0x0A), FIELD(parent, void *, 0x60));
    if (value << 16) {
        register u8 *packet ASM_REG("$9");
        FIELD(self, u16, 0x0A) = 8;
        FIELD(self, u16, 0x82) = 0;
        packet = arg2;
        FIELD(packet, u8, 0x0E) = 0;
        FIELD(packet, u8, 0x0D) = 0;
        FIELD(packet, u8, 0x0C) = 0;
        func_80026634();
    }
    {
    register u8 *packet ASM_REG("$9") = arg2;
    s32 sum1e;
    angle = FIELD(packet, u16, 0x1A) + 0x400;
    ASM_KEEP(angle);
    if (angle >= 0x1001) {
        angle -= 0x1000;
    }
    FIELD(packet, u16, 0x1A) = angle;
    phase90 = FIELD(self, s16, 0x90);
    if (phase90 == 0) {
        FIELD(packet, u16, 0x1C) += FIELD(self, u16, 0x96);
        sum1e = FIELD(packet, u16, 0x1E) + FIELD(self, u16, 0x96);
        ASM_TAILSLOT_PIN(sum1e);
        func_80025EC8();
    } else {
        packet = arg2;
        FIELD(packet, u16, 0x1C) -= FIELD(self, u16, 0x96);
        FIELD(packet, u16, 0x1E) -= FIELD(self, u16, 0x96);
    }
    }
    count = FIELD(self, s16, 0x92) + 1;
    FIELD(self, s16, 0x92) = count;
    if (count >= FIELD(self, s16, 0x94)) {
        FIELD(self, s16, 0x92) = 0;
        FIELD(self, s16, 0x90) ^= 1;
    }
    FIELD(self, u8, 0x7B)--;
    if ((s8)FIELD(self, u8, 0x7B) > 0) {
        goto update_position;
    }
    if (FIELD(parent, u8 *, 0x60) == 0) {
        goto missing_target;
    }
    FIELD(self, u16, 0x0A) = 3;
    FIELD(self, u16, 0x82) = 0;
    src = FIELD(FIELD(parent, u8 *, 0x60) - 0x18, u8 *, 0);
    FIELD(out, u16, 2) = FIELD(src, u16, 2);
    FIELD(out, u16, 6) = FIELD(src, u16, 6);
    FIELD(out, u16, 0x0A) = FIELD(src, u16, 0x0A) - D_800DDC40[FIELD(FIELD(parent, u8 *, 0x60), u8, 0x13)];
    func_800A56E0(0x300);
    obj2 = func_8003FC64(0x212);
    if (obj2 != 0) {
        FIELD(obj2, u16, 0x22) = 120;
        FIELD(obj2, u32, 0x10) = (u32)D_80025348;
        func_8004491C(obj2, D_80045340);
        obj2_data = FIELD(obj2, u8 *, 0x0C);
        FIELD(obj2_data, u16, 0x14) |= 0x0C;
        FIELD(obj2_data, u16, 0x10) = 0;
        FIELD(obj2_data, u16, 6) = 0;
        FIELD(obj2_data, u16, 0x14) |= 0x80;
        src = FIELD(FIELD(parent, u8 *, 0x60) - 0x18, u8 *, 0);
        vec = FIELD(obj2, s32 *, 8);
        vec[0] = FIELD(src, s32, 0);
        vec[1] = FIELD(src, s32, 4);
        vec[2] = FIELD(src, s32, 8);
        obj2_data = FIELD(obj2, u8 *, 0x0C);
        FIELD(obj2_data, u16, 0x1E) = 0x1000;
        FIELD(obj2_data, u16, 0x1C) = 0x1000;
        FIELD(obj2_data, u8, 0x0E) = 0x80;
        FIELD(obj2_data, u8, 0x0D) = 0x80;
        FIELD(obj2_data, u8, 0x0C) = 0x80;
        FIELD(obj2, Copy12, 0x3A) = D_80026680;
        FIELD(obj2_data, void *, 8) = obj2 + 0x3A;
    }
    obj = func_8003FC64(0x212);
    if (obj == 0) {
        goto cleanup_packet;
    }
    obj_hdr = obj + 0x20;
    i = 95;
    cursor = obj_hdr + 95;
    FIELD(obj_hdr, u16, 2) = 0x50;
    FIELD(obj_hdr, u16, 0x0A) = 0x14;
    FIELD(obj_hdr, u16, 4) = 0;
    FIELD(obj_hdr, void *, 0x28) = parent;
    FIELD(obj_hdr, void *, 0x2C) = FIELD(parent, void *, 0x60);
    FIELD(obj_hdr, void *, 0x30) = self;
    aim = obj2 + 0x20;
    FIELD(obj_hdr, void *, 0x34) = aim;
    ASM_USE(obj2);
    for (; i >= 0; i--) {
        FIELD(cursor, u8, 0x38) = 0;
        cursor--;
    }
    i = 96;
    FIELD(obj_hdr, u16, 0x9A) = 0;
    FIELD(obj, u32, 0x10) = (u32)D_80025398;
    func_8004491C(obj, D_80045340);
    obj_data = FIELD(obj, u8 *, 0x0C);
    flg2 = 0x0C;
    ASM_KEEP_NV(flg2);
    FIELD(obj_data, u16, 0x14) = flg2;
    FIELD(obj_data, s16, 0x10) = i;
    FIELD(obj_data, u16, 6) = 6;
    FIELD(obj_data, u16, 0x14) = flg2 | 0x80;
    vec = FIELD(obj, s32 *, 8);
    vec[0] = FIELD(out, s32, 0);
    vec[1] = FIELD(out, s32, 4);
    vec[2] = FIELD(out, s32, 8) + 0x400000;
    obj_data = FIELD(obj, u8 *, 0x0C);
    FIELD(obj_data, u16, 0x1C) = 0x2000;
    FIELD(obj_data, u16, 0x1E) = 0x1800;
    FIELD(obj_data, u8, 0x0E) = 0;
    FIELD(obj_data, u8, 0x0D) = 0;
    FIELD(obj_data, u8, 0x0C) = 0;
    FIELD(obj_hdr, Copy12, 0x1A) = D_80026674;
    link2 = obj_hdr + 0x1A;
    ASM_USE(obj_hdr);
    FIELD(obj_data, void *, 8) = link2;
    func_800261AC();
    }

missing_target:
    FIELD(self, u16, 0x0A) = 8;
    FIELD(self, u16, 0x82) = 0;

cleanup_packet:
    {
        register u8 *packet ASM_REG("$9") = arg2;
        FIELD(packet, u8, 0x0E) = 0;
        FIELD(packet, u8, 0x0D) = 0;
        FIELD(packet, u8, 0x0C) = 0;
        FIELD(packet, u16, 0x1E) = 0;
        FIELD(packet, u16, 0x1C) = 0;
        func_80026634();
    }

update_position:
    FIELD(out, s32, 0) += FIELD(out, s32, 0x0C);
    FIELD(out, s32, 4) += FIELD(out, s32, 0x10);
    FIELD(out, s32, 8) += FIELD(out, s32, 0x14);
    func_80026634();

case 3:
    {
    s16 count;
    register u8 *obj ASM_REG("$20");
    register u8 *obj_header ASM_REG("$19");
    register u8 *obj_data ASM_REG("$7");
    register s32 *vec ASM_REG("$18");
    u8 *cursor;
    s32 value;
    register s32 i ASM_REG("$16");

    count = FIELD(self, u16, 0x82) + 1;
    FIELD(self, u16, 0x82) = count;
    if ((s16)count != 4) {
        goto done;
    }
    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj_header = obj + 0x20;
        i = 95;
        FIELD(obj_header, void *, 0x28) = parent;
        FIELD(obj_header, void *, 0x2C) = FIELD(parent, void *, 0x60);
        FIELD(obj_header, void *, 0x30) = self;
        cursor = obj_header + 95;
        for (; i >= 0; i--) {
            FIELD(cursor, u8, 0x38) = 0;
            cursor--;
        }
        FIELD(obj_header, u16, 0x9A) = 0;
        FIELD(obj, u32, 0x10) = (u32)D_80025648;
        func_8004491C(obj, D_80045340);
        obj_data = FIELD(obj, u8 *, 0x0C);
        value = FIELD(obj_data, u16, 0x14) & 0xFFF3;
        FIELD(obj_data, u16, 0x14) = value;
        FIELD(obj_data, u16, 0x10) = 0x20;
        FIELD(obj_data, u16, 0x14) = value | 0x80;
        src = FIELD(FIELD(parent, u8 *, 0x60) - 0x18, u8 *, 0);
        vec = FIELD(obj, s32 *, 8);
        vec[0] = FIELD(src, s32, 0);
        vec[1] = FIELD(src, s32, 4);
        vec[2] = FIELD(src, s32, 8);
        obj_data = FIELD(obj, u8 *, 0x0C);
        FIELD(obj_data, u16, 0x1E) = 0x1000;
        FIELD(obj_data, u16, 0x1C) = 0x1000;
        FIELD(obj_data, u8, 0x0E) = 0x80;
        FIELD(obj_data, u8, 0x0D) = 0x80;
        FIELD(obj_data, u8, 0x0C) = 0x80;
        FIELD(obj_header, Copy12, 0x1A) = D_80026668;
    FIELD(obj_data, void *, 8) = obj_header + 0x1A;
    ASM_USE(obj_header);
    }
    if ((s16)FIELD(self, u16, 0x82) != 4) {
        goto done;
    }
    FIELD(self, u16, 0x0A) = 4;
    FIELD(self, u16, 0x82) = 0;
    FIELD(self, u16, 0x9C) = 0;
    func_80026634();
    }

case 4:
    {
    s16 count;
    register u8 *obj ASM_REG("$20");
    register u8 *obj_data ASM_REG("$7");
    register u8 *obj_hdr ASM_REG("$19");
    register s32 *vec ASM_REG("$18");
    u8 *tmpsrc;
    s32 rnd2;
    s32 amt;
    s32 random;
    register s32 random3 ASM_REG("$2");
    register s32 prod ASM_REG("$9");
    register s32 shifted ASM_REG("$3");
    s32 value;
    s16 phase;
    s32 tbyte;

    count = FIELD(self, u16, 0x82) + 1;
    FIELD(self, u16, 0x82) = count;
    if ((count & 3) != 0 || (s16)count >= 80) {
        goto case_4_tail;
    }
    obj = func_8003FC64(0x212);
    if (obj == 0) {
        goto case_4_tail;
    }
    obj_hdr = obj + 0x20;
    FIELD(obj_hdr, u16, 2) = 20;
    FIELD(obj_hdr, u16, 0x0A) = 10;
    FIELD(obj_hdr, u16, 4) = 0;
    FIELD(obj, u32, 0x10) = (u32)D_8002558C;
    func_8004491C(obj, D_80045340);
    obj_data = FIELD(obj, u8 *, 0x0C);
    FIELD(obj_data, u16, 0x10) = 0x20;
    FIELD(obj_data, u16, 0x14) |= 0x0C;
    src = FIELD(FIELD(parent, u8 *, 0x60) - 0x18, u8 *, 0);
    vec = FIELD(obj, s32 *, 8);
    random = func_80069EF8();
    value = func_8002512C();
    random &= 0x1F;
    random += 16;
    prod = random * value;
    shifted = prod << 16;
    vec[0] = FIELD(src, s32, 0) + shifted;
    random = func_80069EF8();
    value = func_8002512C();
    random &= 0x1F;
    random += 16;
    prod = random * value;
    shifted = prod << 16;
    vec[1] = FIELD(src, s32, 4) + shifted;
    random3 = func_80069EF8();
    vec[2] = FIELD(src, s32, 8)
             - (D_800DDC40[FIELD(parent, u8 *, 0x60)[0x13]] << 15)
             - ((random3 & 0x1F) << 16);
    obj_data = FIELD(obj, u8 *, 0x0C);
    tmpsrc = FIELD(FIELD(parent, u8 *, 0x60) - 0x14, u8 *, 0);
    FIELD(obj_data, u16, 0x1C) = FIELD(tmpsrc, u16, 0x1C) >> 1;
    FIELD(obj_data, u16, 0x1E) = FIELD(tmpsrc, u16, 0x1E) >> 1;
    FIELD(obj_data, u8, 0x0E) = 0;
    FIELD(obj_data, u8, 0x0D) = 0;
    FIELD(obj_data, u8, 0x0C) = 0;
    FIELD(obj, Copy12, 0x3A) = D_80026668;
    FIELD(obj_data, void *, 8) = obj + 0x3A;
    ASM_USE(obj);

case_4_tail:
    if ((s16)FIELD(self, u16, 0x82) == 80) {
        if (func_8009D218(FIELD(parent, void *, 0x60), 4, parent) == 0) {
            rnd2 = func_800A6D30();
            value = FIELD(self, u8, 9) >> 2;
            rnd2 = (rnd2 & 3) + 4;
            amt = value + rnd2;
            if (D_800E3D68[0] == 0xFF) {
                phase = 0xFF;
            } else {
                phase = 16;
            }
            func_800C8A3C(FIELD(parent, void *, 0x60), phase, amt);
        }
    }
    if ((s16)FIELD(self, u16, 0x82) < 120) {
        func_80026634();
    }
    goto state_advance;
    }

case 5:
    {
    if (FIELD(self, s16, 0x9C) == 0) {
        goto done;
    }
    }

state_advance:
    FIELD(self, u16, 0x0A)++;
    FIELD(self, u16, 0x82) = 0;
    func_80026634();

case 6:
    {
    s16 count;
    count = FIELD(self, u16, 0x82) + 1;
    FIELD(self, u16, 0x82) = count;
    if ((s16)count < 11) {
        goto done;
    }
    FIELD(self, u16, 0x0A) = 8;
    FIELD(self, u16, 0x82) = 30;
    func_80026634();
    }

case 8:
    {
    s16 count;
    s32 flag;
    count = FIELD(self, u16, 0x82);
    FIELD(self, u16, 0x82) = count + 1;
    if ((s16)(count + 1) < 31) {
        goto done;
    }
    flag = D_800266BC[0];
    FIELD(self, u16, 0x82) = count;
    if (flag == 0) {
        D_8008346C[0] = 0;
        FIELD(self, u16, -2) |= 0x8000;
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
    ASM_KEEP(out);
    return;
}
