#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80083160[];
extern s8 D_8006CCD8[];
extern s8 D_8006CCE8[];
extern void *D_8006CD58[];
extern s16 D_8008346A[1];
extern u8 D_80083460[];
extern u8 D_800DD148[];
extern u8 D_800DD150[];
extern u8 D_8008ACDC[];
extern u8 D_80025000[];
extern u8 D_80025024[];
extern u8 D_80025028[];
extern u8 D_80025068[];
extern u8 D_800287F0[];

extern void func_8003F540(void *, void *, void *, s32);
extern s32 func_800445E0(void);
extern void func_8003E4FC(s32, s32, s32);
extern void func_800ACB98(void *, void *, void *, void *);
extern void func_800A56E0(s32);
extern void func_80026C88(s16, s16, s16, void *);
extern void func_80026A84(void *, void *, void *, void *);
extern void func_800B835C(void *, void *, s32, s32);
extern void func_80025FF4(void *, void *);
extern s32 func_8003FA44(s32);
extern s32 func_800990FC(void);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(void *, s32);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_800999B0(s32);
extern void func_800A5720(s32);
extern void *func_800280F4(void *, void *, void *);
extern void func_800264D4(void *, void *, s32, s32);
extern void func_80027070(s16, s16, s16, s32, void *);
extern void *func_800277F4(void *, void *, s32);
extern s32 func_80028208(void *, s32);
extern void func_80027534(s16, s16, s16, s32);
extern void func_80048A44(void *, s32, s32, s32);

extern void func_80025F78(void) __attribute__((noreturn));
extern void func_80025F7C(void) __attribute__((noreturn));

void func_800253C0(void *arg0_in, void *arg1_in, void *arg2_in, void *arg3_in)
{
    register void *arg0 ASM_REG("$21") = arg0_in;
    register void *arg1 ASM_REG("$19") = arg1_in;
    register void *arg2 ASM_REG("$23") = arg2_in;
    register void *arg3 = arg3_in;
    u8 *page = D_80083160;
    register void *fa0 ASM_REG("$4");
    register s32 fa2 ASM_REG("$6");
    register u8 *tp ASM_REG("$2");
    u8 state;
    u32 sp20;

    ASM_KEEP_NV(arg0);
    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
    if (FIELD(arg0, void *, 0xAC) == 0) {
        goto l0_empty;
    }
    if (FIELD(arg0, void *, 0xB0) != 0) {
        goto l0_calls;
    }
l0_empty:
    FIELD(arg0, u8, 0x9B) = 13;
    goto done;
l0_calls:
    {
        void *ca1 = *(void *volatile *)&D_8006CD58[0];
        func_8003F540(0, ca1, 0, 0x1000530);
    }
    {
        s32 value = func_800445E0();
        func_8003E4FC(21, value, 0);
    }
    func_80025F78();

    case 1:
    {
        s32 index;
        u8 *page1;
        u16 nang;

        page1 = D_80083160;
        ASM_USE_NV(page1);
        nang = FIELD(arg3, u16, 0x2A);
        index = ((FIELD(page1, s16, 0xC8) +
                  FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        if (index == 2) {
            fa0 = arg2;
            FIELD(fa0, void *, 0x2C) = D_800DD148;
            ASM_KEEP(page1);
            fa2 = 0;
            tp = D_800DD148 + ((((FIELD(page1, s16, 0xC8) +
                  FIELD(arg3, s16, 0x2A)) + 0x100) >> 9) & 7);
            goto L_F6C;
        }
        FIELD(arg3, s16, 0x2A) = nang + 0x200;
        goto done;
    }

    case 2:
    {
        register s32 i ASM_REG("$17") = 0;
        register u32 mask ASM_REG("$19") = 0x20000000;
        register void *record ASM_REG("$18") = arg0;

        ASM_KEEP(i);
        ASM_KEEP(record);
        ASM_KEEP(mask);

        do {
            register void *object ASM_REG("$16") = FIELD(record, void *, 0xAC);
            ASM_KEEP(object);
            if ((FIELD(object, u32, 0x14) & mask) != 0) {
                func_800ACB98(object, FIELD(object, void *, -0x18),
                              FIELD(object, void *, -0x14), object);
            }
            i++;
            record = (u8 *)record + 4;
        } while (i < 2);
    }
    func_80025F78();

    case 3:
    if (D_8008346A[0] != 0) {
        goto done;
    }
    {
        register s32 i ASM_REG("$17") = 0;
        register u32 mask ASM_REG("$5") = 0x100000;
        register void *record ASM_REG("$4") = arg0;
        ASM_KEEP(i);
        ASM_KEEP(record);
        ASM_KEEP(mask);
        do {
            register void *object ASM_REG("$16") = FIELD(record, void *, 0xAC);
            register u16 angle ASM_REG("$3");
            ASM_KEEP(object);
            record = (u8 *)record + 4;
            i++;
            FIELD(object, u32, 0x14) |= mask;
            angle = FIELD(object, u16, 0x2A);
            ASM_KEEP(angle);
            FIELD(object, u16, 0x8A) = angle;
        } while (i < 2);
    }
    {
        register s32 i ASM_REG("$17");
        register void *record ASM_REG("$6");
        u8 amount;
        s16 timer;
        s32 delta;
        register u8 *amounts ASM_REG("$18");
        register s32 num ASM_REG("$3");
        u8 *page_loop;
        s16 *table_x;
        s16 *table_y;

        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg0, volatile s16, 0x96) = 32;
        ASM_SCHED_BARRIER();
        num = 32;
        amount = FIELD(page, u8, 0xA8);
        timer = FIELD(arg0, s16, 0x96);
        delta = (num - amount) / timer;
        amount = amount + delta;
        amounts = page + 0xA8;
        i = 0;
        record = arg0;
        page_loop = D_80083160;
        table_x = (s16 *)&D_8006CCD8;
        table_y = (s16 *)&D_8006CCE8;
        ASM_KEEP(i);
        ASM_KEEP(record);
        ASM_KEEP(amounts);
        FIELD(page, u8, 0xA8) = amount;
        amounts[1] = amount;
        amounts[2] = amount;
        do {
            register void *object ASM_REG("$16");
            register void *prim ASM_REG("$8");
            register s32 table_index ASM_REG("$5");
            register s32 x ASM_REG("$3");
            s32 delta;
            register s32 old ASM_REG("$2");
            register s32 dv ASM_REG("$4");

            table_index = i << 11;
            object = FIELD(record, void *, 0xAC);
            ASM_KEEP(object);
            old = FIELD(page_loop, s16, 0xC8);
            table_index = table_index - old;
            table_index = (table_index + 0x100) >> 8;
            ASM_KEEP_NV(table_index);
            table_index &= 0xE;
            x = (s32)FIELD(arg2, u8, 0x24);
            dv = FIELD(arg0, s16, 0x96);
            x = x + table_x[table_index >> 1];
            x = x << 6;
            prim = FIELD(object, void *, -0x18);
            old = FIELD(prim, s16, 2) - 0x20;
            x = x - old;
            FIELD(prim, u16, 2) = FIELD(prim, u16, 2) + x / dv;
            x = (s32)FIELD(arg2, u8, 0x25);
            {
                register s32 tv ASM_REG("$2");
                tv = table_y[table_index >> 1];
                x = x + tv;
            }
            x = x << 6;
            old = FIELD(prim, s16, 6) - 0x20;
            x = x - old;
            FIELD(prim, u16, 6) = FIELD(prim, u16, 6) +
                                  x / FIELD(arg0, s16, 0x96);
            {
                s32 old3 = FIELD(prim, s16, 0xA);
                s32 d3 = FIELD(arg1, s16, 0xA) - old3;
                FIELD(prim, u16, 0xA) = FIELD(prim, u16, 0xA) +
                                        d3 / FIELD(arg0, s16, 0x96);
            }

            {
                s32 angle = FIELD(page_loop, s16, 0xC8) + FIELD(object, s16, 0x2A);
                u16 nang = FIELD(object, u16, 0x2A);
                if ((((angle + 0x100) >> 9) & 7) != 2) {
                    FIELD(object, u16, 0x2A) = nang + 0x200;
                }
            }
            i++;
            record = (u8 *)record + 4;
        } while (i < 2);
        timer = FIELD(arg0, s16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if (timer > 0) {
            goto done;
        }
        func_800A56E0(0x300);
        {
        register s32 j ASM_REG("$17");
        u8 *page3b;
        s16 *table_x2;
        s16 *table_y2;
        register void *record2 ASM_REG("$5");
        FIELD(amounts, u32, 0) = 0x2C202020;
        j = 0;
        page3b = D_80083160;
        table_x2 = (s16 *)&D_8006CCD8;
        table_y2 = (s16 *)&D_8006CCE8;
        record2 = arg0;
        do {
            register void *object ASM_REG("$16") = FIELD(record2, void *, 0xAC);
            register void *prim ASM_REG("$8");
            s32 table_index = ((j << 11) - FIELD(page3b, s16, 0xC8) + 0x100) >> 8;
            s32 x;
            s32 y;
            ASM_KEEP_NV(table_index);
            table_index &= 0xE;
            x = (s32)FIELD(arg2, u8, 0x24) + table_x2[table_index >> 1];
            prim = FIELD(object, void *, -0x18);
            FIELD(prim, s16, 2) = (x << 6) + 0x20;
            y = (s32)FIELD(arg2, u8, 0x25) + table_y2[table_index >> 1];
            FIELD(prim, s16, 6) = (y << 6) + 0x20;
            FIELD(prim, u16, 0xA) = FIELD(arg1, u16, 0xA);
            record2 = (u8 *)record2 + 4;
            j++;
        } while (j < 2);
        {
            register s32 nv ASM_REG("$3");
            nv = 16;
            (void)FIELD(arg0, volatile u8, 0x9B);
            FIELD(arg0, s16, 0x96) = nv;
        }
        }
        func_80025F7C();
    }

    case 4:
    {
        s16 timer = FIELD(arg0, s16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if (timer > 0) {
            goto done;
        }
        func_80026C88(FIELD(arg1, s16, 2), FIELD(arg1, s16, 6),
                      FIELD(arg1, s16, 0xA), arg2);
        {
            register s32 nv ASM_REG("$3");
            nv = 32;
            (void)FIELD(arg0, volatile u8, 0x9B);
            FIELD(arg0, s16, 0x96) = nv;
        }
        func_80025F7C();
    }

    case 5:
    {
        s16 timer = FIELD(arg0, s16, 0x96) - 1;
        register s32 i ASM_REG("$17");
        register void *record ASM_REG("$18");
        register void *object ASM_REG("$16");

        FIELD(arg0, s16, 0x96) = timer;
        if (timer > 0) {
            goto done;
        }
        i = 0;
        record = arg0;
        do {
            register void *ca0 ASM_REG("$4") = arg1;
            register void *ca3 ASM_REG("$7") = arg2;
            object = FIELD(record, void *, 0xAC);
            record = (u8 *)record + 4;
            i++;
            func_80026A84(ca0, FIELD(object, void *, -0x18), object, ca3);
        } while (i < 2);
        {
            s16 sp18[4];
            FIELD(arg0, u8, 0x9B)++;
            FIELD(arg0, s16, 0x96) = 60;
            sp18[0] = 0x340;
            sp18[1] = 0x180;
            sp18[3] = 0x40;
            sp18[2] = 0x40;
            func_800B835C(D_800287F0, sp18, 1, 0);
        }
        goto done;
    }

    case 6:
    func_80025FF4(FIELD(arg0, void *, 0xAC), FIELD(arg0, void *, 0xB0));
    {
        s16 timer = FIELD(arg0, s16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if (timer > 0) {
            goto done;
        }
        {
            register s32 nv ASM_REG("$3");
            nv = 8;
            ASM_SCHED_BARRIER();
            (void)FIELD(arg0, volatile u8, 0x9B);
            FIELD(arg0, s16, 0x96) = nv;
        }
        func_80025F7C();
    }

    case 7:
    func_80025FF4(FIELD(arg0, void *, 0xAC), FIELD(arg0, void *, 0xB0));
    {
        s16 timer = FIELD(arg0, s16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if (timer > 0) {
            goto done;
        }
    }
    if (func_8003FA44(13) == 0) {
        goto done;
    }
    {
        register s32 effect ASM_REG("$22") = func_800990FC();
        s32 text = func_8009929C(8, effect);
        register s32 saved_text ASM_REG("$18");
        register s32 stv ASM_REG("$2");
        ASM_KEEP(effect);
        text = func_80099734(FIELD(arg0, void *, 0xAC), text);
        text = func_80099194(D_80025000, text);
        text = func_80099734(FIELD(arg0, void *, 0xB0), text);
        saved_text = func_80099194(D_80025024, text);
        ASM_KEEP(saved_text);
        {
        register void *object ASM_REG("$16") =
            func_800280F4(FIELD(arg0, void *, 0xAC),
                           FIELD(arg0, void *, 0xB0),
                           &sp20);
            ASM_KEEP(object);
            FIELD(arg3, void *, 0x60) = object;
            if (object != 0) {
                register s32 i ASM_REG("$17") = 0;
                register void *record ASM_REG("$20") = arg0;
                ASM_KEEP(i);
                ASM_KEEP(record);
L7_object_loop:
                {
                    register s32 call_i ASM_REG("$19");
                    register s32 shifted ASM_REG("$2");
                    void *other;
                    shifted = i << 16;
                    call_i = shifted >> 16;
                    ASM_KEEP(call_i);
                    other = FIELD(record, void *, 0xAC);
                    func_800264D4(FIELD(other, void *, -0x18), other,
                                  call_i, object == other);
                    if (object == FIELD(record, void *, 0xAC)) {
                        register u8 *tb ASM_REG("$12") = D_80083160;
                        s32 angle;
                        s32 index;
                        s32 x;
                        s32 y;
                        ASM_USE_NV(tb);
                        angle = FIELD(tb, s16, 0xC8);
                        angle = -angle;
                        index = ((angle + 0x500) >> 8) & 0xE;
                        tb = (u8 *)&D_8006CCD8;
                        x = FIELD(arg2, u8, 0x24) + *(s16 *)(tb + index);
                        tb = (u8 *)&D_8006CCE8;
                        y = FIELD(arg2, u8, 0x25) + *(s16 *)(tb + index);
                        func_80027070((s16)((x << 6) + 0x20),
                                      (s16)((y << 6) + 0x20),
                                      FIELD(arg3, s16, 0x88), call_i, object);
                    }
                    i++;
                    record = (u8 *)record + 4;
                }
                if (i < 2) {
                    goto L7_object_loop;
                }
                {
                    register s32 j ASM_REG("$17") = 0;
                    register s32 c32 = 32;
                    register s32 c12 = 12;
                    register void *record2 ASM_REG("$3") = arg0;
                    ASM_KEEP(j);
                    ASM_KEEP_NV(c32);
                    ASM_KEEP_NV(c12);
                    ASM_KEEP(record2);
                    do {
                        register void *object2 ASM_REG("$16") = FIELD(record2, void *, 0xAC);
                        register void *child ASM_REG("$5") = FIELD(object2, void *, -0x14);
                        register u16 child_y ASM_REG("$2") = FIELD(child, u16, 0x12);
                        ASM_KEEP(object2);
                        ASM_KEEP(child);
                        ASM_KEEP(child_y);
                        j++;
                        FIELD(child, s16, 0x10) = c32;
                        FIELD(child, s16, 0x14) = c12;
                        ASM_SCHED_BARRIER();
                        FIELD(child, s16, 0x12) = child_y - 128;
                        record2 = (u8 *)record2 + 4;
                    } while (j < 2);
                }
                stv = FIELD(arg0, u8, 0x9B);
                FIELD(arg0, s16, 0x96) = 38;
                stv = stv + 1;
                goto L_AC4;
            }
        }
        saved_text = func_8009929C(10, saved_text);
        saved_text = func_80099194(D_80025028, saved_text);
        ASM_KEEP(saved_text);
        stv = FIELD(arg0, u8, 0x9B);
        FIELD(arg0, s16, 0x96) = 32;
        stv = stv + 2;
L_AC4:
        FIELD(arg0, u8, 0x9B) = stv;
        func_80099290(saved_text);
        func_800A5720(effect);
        goto done;
    }

    case 8:
    func_80025FF4(FIELD(arg0, void *, 0xAC), FIELD(arg0, void *, 0xB0));
    {
        register s32 i ASM_REG("$17") = 0;
        register void *record ASM_REG("$6") = arg0;
        ASM_KEEP(i);
        ASM_KEEP(record);
        do {
            register void *object ASM_REG("$16") = FIELD(record, void *, 0xAC);
            register void *child ASM_REG("$5") = FIELD(object, void *, -0x14);
            register u32 x ASM_REG("$2") = FIELD(child, u8, 0xC);
            register u32 y ASM_REG("$3") = FIELD(child, u8, 0xD);
            register u32 z ASM_REG("$4");
            ASM_KEEP(object);
            ASM_KEEP(child);
            ASM_KEEP(x);
            ASM_KEEP(y);
            x = x - (x >> 1);
            FIELD(child, u8, 0xC) = x;
            ASM_KEEP(x);
            y = y - (y >> 1);
            ASM_KEEP(y);
            z = FIELD(child, u8, 0xE);
            x = FIELD(child, volatile u8, 0xC);
            FIELD(child, u8, 0xD) = y;
            z = z - (z >> 1);
            FIELD(child, u8, 0xE) = z;
            if (x < 5) {
                FIELD(child, u8, 0xE) = 0;
                FIELD(child, u8, 0xD) = 0;
                FIELD(child, u8, 0xC) = 0;
            }
            i++;
            record = (u8 *)record + 4;
        } while (i < 2);
        {
            s16 timer = FIELD(arg0, s16, 0x96) - 1;
            FIELD(arg0, s16, 0x96) = timer;
            if (timer > 0) {
                goto done;
            }
        }
    }
    {
        void *object = FIELD(arg3, void *, 0x60);
        if (object != 0) {
            register void **p ASM_REG("$17");
            void **q;
            register void **q3 ASM_REG("$3");
            void *new_object;
            register s32 raw ASM_REG("$22");
            register s32 eff2 ASM_REG("$18");
            s32 effect;

            raw = func_800990FC();
            p = (void **)((u8 *)arg0 + 0xAC);
            effect = raw;
            q = p;
            if (*p != object) {
                q = (void **)((u8 *)arg0 + 0xB0);
            }
            effect = func_80099734(*q, effect);
            eff2 = func_80099194(D_80025068, effect);
            q = p;
            if (*p == object) {
                q = (void **)((u8 *)arg0 + 0xB0);
            }
            effect = func_80099734(*q, eff2);
            effect = func_80099194(D_80025024, effect);
            effect = func_800999B0(effect);
            effect = func_80099290(effect);
            effect = func_8009929C(17, effect);
            func_800A5720(raw);
            new_object = func_800277F4(FIELD(arg0, void *, 0xAC),
                                       FIELD(arg0, void *, 0xB0), 0);
            ASM_KEEP_NV(new_object);
            q3 = p;
            if (*p == new_object) {
                q3 = (void **)((u8 *)arg0 + 0xB0);
            }
            *q3 = 0;
            raw = func_800990FC();
            effect = func_80028208(new_object, raw);
            effect = func_80099290(effect);
            func_800A5720(raw);
        }
    }
    {
        register s32 i ASM_REG("$17") = 0;
        u8 *page8 = D_80083160;
        s16 *table_x = (s16 *)&D_8006CCD8;
        ASM_KEEP(i);
        do {
            register void *object ASM_REG("$16") =
                FIELD((void *)((i << 2) + (s32)arg0), void *, 0xAC);
            ASM_KEEP(object);
            if (object != 0) {
                register void *prim ASM_REG("$8") = FIELD(object, void *, -0x18);
                register void *child ASM_REG("$5") = FIELD(object, void *, -0x14);
                register s32 index ASM_REG("$3");
                register u8 *tyb ASM_REG("$2");
                register s32 sz ASM_REG("$7");
                s32 x;
                s32 y;
                s32 z;
                FIELD(child, u32, 0xC) = 0x808080;
                FIELD(child, s16, 0x10) = 0;
                FIELD(child, u16, 0x12) &= 0x3F;
                FIELD(child, u16, 0x14) &= 0xFFF3;
                index = (((-FIELD(page8, s16, 0xC8) + 0x500) >> 8) & 0xE);
                x = FIELD(arg2, u8, 0x24) + table_x[index >> 1];
                FIELD(prim, s16, 2) = (x << 6) + 0x20;
                sz = 16;
                ASM_KEEP(sz);
                ASM_SCHED_BARRIER();
                tyb = (u8 *)&D_8006CCE8;
                index = index + (s32)tyb;
                ASM_KEEP_NV(index);
                y = FIELD(arg2, u8, 0x25) + *(s16 *)index;
                FIELD(prim, s16, 6) = (y << 6) + 0x20;
                z = FIELD(arg1, u16, 0xA);
                FIELD(prim, u16, 0xA) = z;
                func_80027534(FIELD(prim, s16, 2), FIELD(prim, s16, 6),
                              (s16)(z - 0x20), sz);
            }
            i++;
        } while (i < 2);
        {
            register s32 nv ASM_REG("$3");
            nv = 64;
            (void)FIELD(arg0, volatile u8, 0x9B);
            FIELD(arg0, s16, 0x96) = nv;
        }
        func_80025F7C();
    }

    case 9:
    {
        s16 timer = FIELD(arg0, s16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if (timer > 0) {
            goto done;
        }
        {
            register s32 nv ASM_REG("$3");
            nv = 32;
            ASM_SCHED_BARRIER();
            (void)FIELD(arg0, volatile u8, 0x9B);
            FIELD(arg0, s16, 0x96) = nv;
        }
        func_80025F7C();
    }

    case 10:
    {
        register s32 i ASM_REG("$17");
        register void *record ASM_REG("$6");
        register u8 *amounts ASM_REG("$18");
        register s32 num ASM_REG("$3");
        register void *object ASM_REG("$16");
        register void *prim ASM_REG("$8");
        register void *child ASM_REG("$5");
        register void *record2 ASM_REG("$3");
        s16 timer;
        s32 step;
        s32 amount;
        s32 old;
        s32 delta;
        s32 x;
        s32 cmp;
        u16 nang;
        u32 h8a;
        register u32 clearmask;

        step = (128 - FIELD(page, u8, 0xA8)) / FIELD(arg0, s16, 0x96);
        amounts = page + 0xA8;
        i = 0;
        record = arg0;
        amount = FIELD(page, u8, 0xA8) + step;
        FIELD(page, u8, 0xA8) = amount;
        amounts[2] = amount;
        amounts[1] = amount;
        do {
            object = FIELD(record, void *, 0xAC);
            if (object != 0) {
                register s32 xv ASM_REG("$3");
                register s32 ov ASM_REG("$2");
                child = FIELD(object, void *, -0x14);
                prim = FIELD(object, void *, -0x18);
                xv = (s32)FIELD(child, u8, 0x24);
                xv = xv << 6;
                ov = FIELD(prim, s16, 2) - 0x20;
                xv = xv - ov;
                FIELD(prim, u16, 2) = FIELD(prim, u16, 2) +
                                      xv / FIELD(arg0, s16, 0x96);
                xv = (s32)FIELD(child, u8, 0x25);
                ASM_SCHED_BARRIER();
                xv = xv << 6;
                ov = FIELD(prim, s16, 6) - 0x20;
                xv = xv - ov;
                FIELD(prim, u16, 6) = FIELD(prim, u16, 6) +
                                      xv / FIELD(arg0, s16, 0x96);
                {
                    s32 old3 = FIELD(prim, s16, 0xA);
                    s32 d3 = FIELD(object, s16, 0x88) - old3;
                    FIELD(prim, u16, 0xA) = FIELD(prim, u16, 0xA) +
                                            d3 / FIELD(arg0, s16, 0x96);
                }
                h8a = FIELD(object, u16, 0x8A);
                FIELD(object, volatile u16, 0x2A) =
                    FIELD(object, u16, 0x2A) & 0xFFF;
                cmp = FIELD(object, s16, 0x2A);
                ASM_KEEP_NV(cmp);
                nang = FIELD(object, u16, 0x2A);
                ASM_SCHED_BARRIER();
                h8a = h8a & 0xFFF;
                FIELD(object, u16, 0x8A) = h8a;
                if (cmp != (s16)h8a) {
                    FIELD(object, u16, 0x2A) = nang + 0x200;
                }
            }
            i++;
            record = (u8 *)record + 4;
        } while (i < 2);
        timer = FIELD(arg0, s16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if (timer > 0) {
            goto done;
        }
        FIELD(amounts, u32, 0) = 0x2C808080;
        i = 0;
        clearmask = 0xFFEFFFFF;
        ASM_KEEP_NV(clearmask);
        record2 = arg0;
        do {
            object = FIELD(record2, void *, 0xAC);
            if (object != 0) {
                child = FIELD(object, void *, -0x14);
                x = FIELD(child, u8, 0x24);
                prim = FIELD(object, void *, -0x18);
                FIELD(prim, s16, 2) = (x << 6) + 0x20;
                FIELD(prim, s16, 6) = ((s32)FIELD(child, u8, 0x25) << 6) + 0x20;
                FIELD(prim, u16, 0xA) = FIELD(object, u16, 0x88);
                FIELD(object, u32, 0x14) &= clearmask;
            }
            i++;
            record2 = (u8 *)record2 + 4;
        } while (i < 2);
        func_80025F78();
    }

    case 11:
    fa0 = arg2;
    FIELD(fa0, void *, 0x2C) = D_800DD150;
    fa2 = 0;
    tp = D_800DD150 + ((((FIELD(D_80083160, s16, 0xC8) +
          FIELD(arg3, s16, 0x2A)) + 0x100) >> 9) & 7);
L_F6C:
    func_80048A44(fa0, *tp, fa2, 1);
    FIELD(arg0, u8, 0x9B)++;
    goto done;

    case 12:
    if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
        goto done;
    }
    {
        register u8 *tb ASM_REG("$3");
        u16 value;
        tb = D_80083460;
        ASM_USE_NV(tb);
        value = FIELD(tb, u16, 2);
        FIELD(tb, u32, 0xC) = 0;
        FIELD(tb, u16, 2) = value | 0x812;
    }
    FIELD(arg0, void *, 0x8C) = D_8008ACDC;

    case 13:
        break;
    }
done:
    return;
}
