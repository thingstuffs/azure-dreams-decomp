#include "common.h"
#include "records/Rec_D_80083160.h"

typedef struct S_800253C0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { volatile s16 v; s16 n; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x10];
    void * unk_AC;
    void * unk_B0;
} S_800253C0_0;   /* arg0 in func_800253C0 */

typedef struct S_800253C0_1 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_800253C0_1;   /* arg3 in func_800253C0 */

typedef struct S_800253C0_2 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800253C0_2;   /* page1 in func_800253C0 */

typedef struct S_800253C0_3 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_800253C0_3;   /* fa0 in func_800253C0 */

typedef struct S_800253C0_4 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_4;   /* record in func_800253C0 */

typedef struct S_800253C0_5_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800253C0_5_pre;   /* the 0x18 bytes before object in func_800253C0, addressed as object[-1] */

typedef struct S_800253C0_5 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    union { u16 n; s16 n2; volatile u16 v; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
    u16 unk_8A;
} S_800253C0_5;   /* object in func_800253C0 */

typedef struct S_800253C0_6 {
    u8 pad_00[0xA8];
    u8 unk_A8;
} S_800253C0_6;   /* page in func_800253C0 */

typedef struct S_800253C0_7 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800253C0_7;   /* page_loop in func_800253C0 */

typedef struct S_800253C0_8 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800253C0_8;   /* arg2 in func_800253C0 */

typedef struct S_800253C0_9 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_800253C0_9;   /* prim in func_800253C0 */

typedef struct S_800253C0_10 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_800253C0_10;   /* arg1 in func_800253C0 */

typedef struct S_800253C0_11 {
    u32 unk_00;
} S_800253C0_11;   /* amounts in func_800253C0 */

typedef struct S_800253C0_12 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_12;   /* record2 in func_800253C0 */

typedef struct S_800253C0_13 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800253C0_13;   /* page3b in func_800253C0 */

typedef struct S_800253C0_14_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800253C0_14_pre;   /* the 0x18 bytes before other in func_800253C0, addressed as other[-1] */

typedef struct S_800253C0_15 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    u32 unk_0C;
    u8 pad_10[0xB8];
    s16 unk_C8;
} S_800253C0_15;   /* tb in func_800253C0 */

typedef struct S_800253C0_16_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800253C0_16_pre;   /* the 0x14 bytes before object2 in func_800253C0, addressed as object2[-1] */

typedef struct S_800253C0_17 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { volatile u8 v; } at00u; struct { u32 v; } at00p; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    union { u16 u; s16 s; } unk_12;   /* accessed as both */
    union { s16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800253C0_17;   /* child in func_800253C0 */

typedef struct S_800253C0_18 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_18;   /* (void *)((i << 2) + (s32)arg0) in func_800253C0 */

typedef struct S_800253C0_19 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800253C0_19;   /* page8 in func_800253C0 */




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
extern void Control_CD(s32, s32, s32);
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
    void *arg0 = arg0_in;
    void *arg1 = arg1_in;
    void *arg2 = arg2_in;
    register void *arg3 = arg3_in;
    u8 *page = D_80083160;
    register void *fa0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 fa2;
    register u8 *tp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 state;
    u32 sp20;

    state = ((S_800253C0_0 *)arg0)->unk_9B.n;
    switch (state) {
    case 0:
    if (((S_800253C0_0 *)arg0)->unk_AC == 0) {
        goto l0_empty;
    }
    if (((S_800253C0_0 *)arg0)->unk_B0 != 0) {
        goto l0_calls;
    }
l0_empty:
    ((S_800253C0_0 *)arg0)->unk_9B.n = 13;
    goto done;
l0_calls:
    {
        void *ca1 = *(void *volatile *)&D_8006CD58[0];
        func_8003F540(0, ca1, 0, 0x1000530);
    }
    {
        s32 value = func_800445E0();
        Control_CD(21, value, 0);
    }
    func_80025F78();

    case 1:
    {
        s32 index;
        u8 *page1;
        u16 nang;

        page1 = D_80083160;
        nang = ((S_800253C0_1 *)arg3)->unk_2A.u;
        index = ((((S_800253C0_2 *)page1)->unk_C8 +
                  ((S_800253C0_1 *)arg3)->unk_2A.s + 0x100) >> 9) & 7;
        if (index == 2) {
            fa0 = arg2;
            ((S_800253C0_3 *)fa0)->unk_2C = D_800DD148;
            fa2 = 0;
            tp = D_800DD148 + ((((((S_800253C0_2 *)page1)->unk_C8 +
                  ((S_800253C0_1 *)arg3)->unk_2A.s) + 0x100) >> 9) & 7);
            goto L_F6C;
        }
        ((S_800253C0_1 *)arg3)->unk_2A.s = nang + 0x200;
        goto done;
    }

    case 2:
    {
        s32 i = 0;
        u32 mask = 0x20000000;
        void *record = arg0;


        do {
            register void *object ASM_REG("$16") = ((S_800253C0_4 *)record)->unk_AC;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            if ((((S_800253C0_5 *)object)->unk_14 & mask) != 0) {
                func_800ACB98(object, ((S_800253C0_5_pre *)object)[-1].unk_00,
                              ((S_800253C0_5_pre *)object)[-1].unk_04, object);
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
        register s32 i ASM_REG("$17") = 0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u32 mask = 0x100000;
        void *record = arg0;
        do {
            register void *object ASM_REG("$16") = ((S_800253C0_4 *)record)->unk_AC;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u16 angle;
            record = (u8 *)record + 4;
            i++;
            ((S_800253C0_5 *)object)->unk_14 |= mask;
            angle = ((S_800253C0_5 *)object)->unk_2A.n;
            ((S_800253C0_5 *)object)->unk_8A = angle;
        } while (i < 2);
    }
    {
        register s32 i ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        void *record;
        u8 amount;
        s16 timer;
        s32 delta;
        u8 *amounts;
        register s32 num ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u8 *page_loop;
        s16 *table_x;
        s16 *table_y;

        ((S_800253C0_0 *)arg0)->unk_9B.n++;
        ((S_800253C0_0 *)arg0)->unk_96.v = 32;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        num = 32;
        amount = ((S_800253C0_6 *)page)->unk_A8;
        timer = ((S_800253C0_0 *)arg0)->unk_96.n;
        delta = (num - amount) / timer;
        amount = amount + delta;
        amounts = page + 0xA8;
        i = 0;
        record = arg0;
        page_loop = D_80083160;
        table_x = (s16 *)&D_8006CCD8;
        table_y = (s16 *)&D_8006CCE8;
        ASM_KEEP(amounts);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_800253C0_6 *)page)->unk_A8 = amount;
        amounts[1] = amount;
        amounts[2] = amount;
        do {
            register void *object ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            register void *prim ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 table_index ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 delta;
            register s32 old ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 dv;

            table_index = i << 11;
            object = ((S_800253C0_4 *)record)->unk_AC;
            old = ((S_800253C0_7 *)page_loop)->unk_C8;
            table_index = table_index - old;
            table_index = (table_index + 0x100) >> 8;
            table_index &= 0xE;
            x = (s32)((S_800253C0_8 *)arg2)->unk_24;
            dv = ((S_800253C0_0 *)arg0)->unk_96.n;
            x = x + table_x[table_index >> 1];
            x = x << 6;
            prim = ((S_800253C0_5_pre *)object)[-1].unk_00;
            old = ((S_800253C0_9 *)prim)->unk_02.s - 0x20;
            x = x - old;
            ((S_800253C0_9 *)prim)->unk_02.u = ((S_800253C0_9 *)prim)->unk_02.u + x / dv;
            x = (s32)((S_800253C0_8 *)arg2)->unk_25;
            {
                register s32 tv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                tv = table_y[table_index >> 1];
                x = x + tv;
            }
            x = x << 6;
            old = ((S_800253C0_9 *)prim)->unk_06.s - 0x20;
            x = x - old;
            ((S_800253C0_9 *)prim)->unk_06.u = ((S_800253C0_9 *)prim)->unk_06.u +
                                  x / ((S_800253C0_0 *)arg0)->unk_96.n;
            {
                s32 old3 = ((S_800253C0_9 *)prim)->unk_0A.s;
                s32 d3 = ((S_800253C0_10 *)arg1)->unk_0A.s - old3;
                ((S_800253C0_9 *)prim)->unk_0A.u = ((S_800253C0_9 *)prim)->unk_0A.u +
                                        d3 / ((S_800253C0_0 *)arg0)->unk_96.n;
            }

            {
                s32 angle = ((S_800253C0_7 *)page_loop)->unk_C8 + ((S_800253C0_5 *)object)->unk_2A.n2;
                u16 nang = ((S_800253C0_5 *)object)->unk_2A.n;
                if ((((angle + 0x100) >> 9) & 7) != 2) {
                    ((S_800253C0_5 *)object)->unk_2A.n = nang + 0x200;
                }
            }
            i++;
            record = (u8 *)record + 4;
        } while (i < 2);
        timer = ((S_800253C0_0 *)arg0)->unk_96.n - 1;
        ((S_800253C0_0 *)arg0)->unk_96.n = timer;
        if (timer > 0) {
            goto done;
        }
        func_800A56E0(0x300);
        {
        register s32 j ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *page3b;
        s16 *table_x2;
        s16 *table_y2;
        void *record2;
        ((S_800253C0_11 *)amounts)->unk_00 = 0x2C202020;
        j = 0;
        page3b = D_80083160;
        table_x2 = (s16 *)&D_8006CCD8;
        table_y2 = (s16 *)&D_8006CCE8;
        record2 = arg0;
        do {
            register void *object ASM_REG("$16") = ((S_800253C0_12 *)record2)->unk_AC;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            register void *prim ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 table_index = ((j << 11) - ((S_800253C0_13 *)page3b)->unk_C8 + 0x100) >> 8;
            s32 x;
            s32 y;
            ASM_KEEP_NV(table_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            table_index &= 0xE;
            x = (s32)((S_800253C0_8 *)arg2)->unk_24 + table_x2[table_index >> 1];
            prim = ((S_800253C0_5_pre *)object)[-1].unk_00;
            ((S_800253C0_9 *)prim)->unk_02.s = (x << 6) + 0x20;
            y = (s32)((S_800253C0_8 *)arg2)->unk_25 + table_y2[table_index >> 1];
            ((S_800253C0_9 *)prim)->unk_06.s = (y << 6) + 0x20;
            ((S_800253C0_9 *)prim)->unk_0A.u = ((S_800253C0_10 *)arg1)->unk_0A.u;
            record2 = (u8 *)record2 + 4;
            j++;
        } while (j < 2);
        {
            register s32 nv ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            nv = 16;
            (void)((S_800253C0_0 *)arg0)->unk_9B.v;
            ((S_800253C0_0 *)arg0)->unk_96.n = nv;
        }
        }
        func_80025F7C();
    }

    case 4:
    {
        s16 timer = ((S_800253C0_0 *)arg0)->unk_96.n - 1;
        ((S_800253C0_0 *)arg0)->unk_96.n = timer;
        if (timer > 0) {
            goto done;
        }
        func_80026C88(((S_800253C0_10 *)arg1)->unk_02, ((S_800253C0_10 *)arg1)->unk_06,
                      ((S_800253C0_10 *)arg1)->unk_0A.s, arg2);
        {
            register s32 nv ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            nv = 32;
            (void)((S_800253C0_0 *)arg0)->unk_9B.v;
            ((S_800253C0_0 *)arg0)->unk_96.n = nv;
        }
        func_80025F7C();
    }

    case 5:
    {
        s16 timer = ((S_800253C0_0 *)arg0)->unk_96.n - 1;
        s32 i;
        register void *record ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register void *object ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        ((S_800253C0_0 *)arg0)->unk_96.n = timer;
        if (timer > 0) {
            goto done;
        }
        i = 0;
        record = arg0;
        do {
            register void *ca0 ASM_REG("$4") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            register void *ca3 ASM_REG("$7") = arg2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            object = ((S_800253C0_4 *)record)->unk_AC;
            record = (u8 *)record + 4;
            i++;
            func_80026A84(ca0, ((S_800253C0_5_pre *)object)[-1].unk_00, object, ca3);
        } while (i < 2);
        {
            s16 sp18[4];
            ((S_800253C0_0 *)arg0)->unk_9B.n++;
            ((S_800253C0_0 *)arg0)->unk_96.n = 60;
            sp18[0] = 0x340;
            sp18[1] = 0x180;
            sp18[3] = 0x40;
            sp18[2] = 0x40;
            func_800B835C(D_800287F0, sp18, 1, 0);
        }
        goto done;
    }

    case 6:
    func_80025FF4(((S_800253C0_0 *)arg0)->unk_AC, ((S_800253C0_0 *)arg0)->unk_B0);
    {
        s16 timer = ((S_800253C0_0 *)arg0)->unk_96.n - 1;
        ((S_800253C0_0 *)arg0)->unk_96.n = timer;
        if (timer > 0) {
            goto done;
        }
        {
            register s32 nv ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            nv = 8;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            (void)((S_800253C0_0 *)arg0)->unk_9B.v;
            ((S_800253C0_0 *)arg0)->unk_96.n = nv;
        }
        func_80025F7C();
    }

    case 7:
    func_80025FF4(((S_800253C0_0 *)arg0)->unk_AC, ((S_800253C0_0 *)arg0)->unk_B0);
    {
        s16 timer = ((S_800253C0_0 *)arg0)->unk_96.n - 1;
        ((S_800253C0_0 *)arg0)->unk_96.n = timer;
        if (timer > 0) {
            goto done;
        }
    }
    if (func_8003FA44(13) == 0) {
        goto done;
    }
    {
        register s32 effect ASM_REG("$22") = func_800990FC();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 text = func_8009929C(8, effect);
        s32 saved_text;
        register s32 stv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        text = func_80099734(((S_800253C0_0 *)arg0)->unk_AC, text);
        text = func_80099194(D_80025000, text);
        text = func_80099734(((S_800253C0_0 *)arg0)->unk_B0, text);
        saved_text = func_80099194(D_80025024, text);
        {
        void *object =
            func_800280F4(((S_800253C0_0 *)arg0)->unk_AC,
                           ((S_800253C0_0 *)arg0)->unk_B0,
                           &sp20);
            ((S_800253C0_1 *)arg3)->unk_60 = object;
            if (object != 0) {
                s32 i = 0;
                register void *record ASM_REG("$20") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
L7_object_loop:
                {
                    register s32 call_i ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                    register s32 shifted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    void *other;
                    shifted = i << 16;
                    call_i = shifted >> 16;
                    other = ((S_800253C0_4 *)record)->unk_AC;
                    func_800264D4(((S_800253C0_14_pre *)other)[-1].unk_00, other,
                                  call_i, object == other);
                    if (object == ((S_800253C0_4 *)record)->unk_AC) {
                        register u8 *tb ASM_REG("$12") = D_80083160;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                        s32 angle;
                        s32 index;
                        s32 x;
                        s32 y;
                        ASM_USE_NV(tb);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        angle = ((S_800253C0_15 *)tb)->unk_C8;
                        angle = -angle;
                        index = ((angle + 0x500) >> 8) & 0xE;
                        tb = (u8 *)&D_8006CCD8;
                        x = ((S_800253C0_8 *)arg2)->unk_24 + *(s16 *)(tb + index);
                        tb = (u8 *)&D_8006CCE8;
                        y = ((S_800253C0_8 *)arg2)->unk_25 + *(s16 *)(tb + index);
                        func_80027070((s16)((x << 6) + 0x20),
                                      (s16)((y << 6) + 0x20),
                                      ((S_800253C0_1 *)arg3)->unk_88, call_i, object);
                    }
                    i++;
                    record = (u8 *)record + 4;
                }
                if (i < 2) {
                    goto L7_object_loop;
                }
                {
                    register s32 j ASM_REG("$17") = 0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    register s32 c32 = 32;
                    register s32 c12 = 12;
                    void *record2 = arg0;
                    do {
                        register void *object2 ASM_REG("$16") = ((S_800253C0_12 *)record2)->unk_AC;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                        register void *child ASM_REG("$5") = ((S_800253C0_16_pre *)object2)[-1].unk_00;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        u16 child_y = ((S_800253C0_17 *)child)->unk_12.u;
                        j++;
                        ((S_800253C0_17 *)child)->unk_10 = c32;
                        ((S_800253C0_17 *)child)->unk_14.s = c12;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                        ((S_800253C0_17 *)child)->unk_12.s = child_y - 128;
                        record2 = (u8 *)record2 + 4;
                    } while (j < 2);
                }
                stv = ((S_800253C0_0 *)arg0)->unk_9B.n;
                ((S_800253C0_0 *)arg0)->unk_96.n = 38;
                stv = stv + 1;
                goto L_AC4;
            }
        }
        saved_text = func_8009929C(10, saved_text);
        saved_text = func_80099194(D_80025028, saved_text);
        ASM_KEEP(saved_text);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        stv = ((S_800253C0_0 *)arg0)->unk_9B.n;
        ((S_800253C0_0 *)arg0)->unk_96.n = 32;
        stv = stv + 2;
L_AC4:
        ((S_800253C0_0 *)arg0)->unk_9B.n = stv;
        func_80099290(saved_text);
        func_800A5720(effect);
        goto done;
    }

    case 8:
    func_80025FF4(((S_800253C0_0 *)arg0)->unk_AC, ((S_800253C0_0 *)arg0)->unk_B0);
    {
        register s32 i ASM_REG("$17") = 0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        void *record = arg0;
        do {
            register void *object ASM_REG("$16") = ((S_800253C0_4 *)record)->unk_AC;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            void *child = ((S_800253C0_5_pre *)object)[-1].unk_04;
            u32 x = ((S_800253C0_17 *)child)->unk_0C.at00.v;
            register u32 y ASM_REG("$3") = ((S_800253C0_17 *)child)->unk_0C.at01.v;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u32 z;
            x = x - (x >> 1);
            ((S_800253C0_17 *)child)->unk_0C.at00.v = x;
            ASM_KEEP(x);
            y = y - (y >> 1);
            z = ((S_800253C0_17 *)child)->unk_0C.at02.v;
            x = ((S_800253C0_17 *)child)->unk_0C.at00u.v;
            ((S_800253C0_17 *)child)->unk_0C.at01.v = y;
            z = z - (z >> 1);
            ((S_800253C0_17 *)child)->unk_0C.at02.v = z;
            if (x < 5) {
                ((S_800253C0_17 *)child)->unk_0C.at02.v = 0;
                ((S_800253C0_17 *)child)->unk_0C.at01.v = 0;
                ((S_800253C0_17 *)child)->unk_0C.at00.v = 0;
            }
            i++;
            record = (u8 *)record + 4;
        } while (i < 2);
        {
            s16 timer = ((S_800253C0_0 *)arg0)->unk_96.n - 1;
            ((S_800253C0_0 *)arg0)->unk_96.n = timer;
            if (timer > 0) {
                goto done;
            }
        }
    }
    {
        void *object = ((S_800253C0_1 *)arg3)->unk_60;
        if (object != 0) {
            void **p;
            void **q;
            void **q3;
            void *new_object;
            register s32 raw ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 eff2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
            new_object = func_800277F4(((S_800253C0_0 *)arg0)->unk_AC,
                                       ((S_800253C0_0 *)arg0)->unk_B0, 0);
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
        s32 i = 0;
        u8 *page8 = D_80083160;
        s16 *table_x = (s16 *)&D_8006CCD8;
        do {
            register void *object ASM_REG("$16") =
                ((S_800253C0_18 *)((void *)((i << 2) + (s32)arg0)))->unk_AC;
            if (object != 0) {
                register void *prim ASM_REG("$8") = ((S_800253C0_5_pre *)object)[-1].unk_00;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register void *child ASM_REG("$5") = ((S_800253C0_5_pre *)object)[-1].unk_04;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 index;
                register u8 *tyb ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 sz;
                s32 x;
                s32 y;
                s32 z;
                ((S_800253C0_17 *)child)->unk_0C.at00p.v = 0x808080;
                ((S_800253C0_17 *)child)->unk_10 = 0;
                ((S_800253C0_17 *)child)->unk_12.u &= 0x3F;
                ((S_800253C0_17 *)child)->unk_14.u &= 0xFFF3;
                index = (((-((S_800253C0_19 *)page8)->unk_C8 + 0x500) >> 8) & 0xE);
                x = ((S_800253C0_8 *)arg2)->unk_24 + table_x[index >> 1];
                ((S_800253C0_9 *)prim)->unk_02.s = (x << 6) + 0x20;
                sz = 16;
                ASM_KEEP(sz);
                tyb = (u8 *)&D_8006CCE8;
                index = index + (s32)tyb;
                y = ((S_800253C0_8 *)arg2)->unk_25 + *(s16 *)index;
                ((S_800253C0_9 *)prim)->unk_06.s = (y << 6) + 0x20;
                z = ((S_800253C0_10 *)arg1)->unk_0A.u;
                ((S_800253C0_9 *)prim)->unk_0A.u = z;
                func_80027534(((S_800253C0_9 *)prim)->unk_02.s, ((S_800253C0_9 *)prim)->unk_06.s,
                              (s16)(z - 0x20), sz);
            }
            i++;
        } while (i < 2);
        {
            register s32 nv ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            nv = 64;
            (void)((S_800253C0_0 *)arg0)->unk_9B.v;
            ((S_800253C0_0 *)arg0)->unk_96.n = nv;
        }
        func_80025F7C();
    }

    case 9:
    {
        s16 timer = ((S_800253C0_0 *)arg0)->unk_96.n - 1;
        ((S_800253C0_0 *)arg0)->unk_96.n = timer;
        if (timer > 0) {
            goto done;
        }
        {
            register s32 nv ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            nv = 32;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            (void)((S_800253C0_0 *)arg0)->unk_9B.v;
            ((S_800253C0_0 *)arg0)->unk_96.n = nv;
        }
        func_80025F7C();
    }

    case 10:
    {
        register s32 i ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        void *record;
        register u8 *amounts ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 num;
        register void *object ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register void *prim ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        void *child;
        register void *record2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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

        step = (128 - ((S_800253C0_6 *)page)->unk_A8) / ((S_800253C0_0 *)arg0)->unk_96.n;
        amounts = page + 0xA8;
        i = 0;
        record = arg0;
        amount = ((S_800253C0_6 *)page)->unk_A8 + step;
        ((S_800253C0_6 *)page)->unk_A8 = amount;
        amounts[2] = amount;
        amounts[1] = amount;
        do {
            object = ((S_800253C0_4 *)record)->unk_AC;
            if (object != 0) {
                register s32 xv ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register s32 ov ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                child = ((S_800253C0_5_pre *)object)[-1].unk_04;
                prim = ((S_800253C0_5_pre *)object)[-1].unk_00;
                xv = (s32)((S_800253C0_17 *)child)->unk_24;
                xv = xv << 6;
                ov = ((S_800253C0_9 *)prim)->unk_02.s - 0x20;
                xv = xv - ov;
                ((S_800253C0_9 *)prim)->unk_02.u = ((S_800253C0_9 *)prim)->unk_02.u +
                                      xv / ((S_800253C0_0 *)arg0)->unk_96.n;
                xv = (s32)((S_800253C0_17 *)child)->unk_25;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                xv = xv << 6;
                ov = ((S_800253C0_9 *)prim)->unk_06.s - 0x20;
                xv = xv - ov;
                ((S_800253C0_9 *)prim)->unk_06.u = ((S_800253C0_9 *)prim)->unk_06.u +
                                      xv / ((S_800253C0_0 *)arg0)->unk_96.n;
                {
                    s32 old3 = ((S_800253C0_9 *)prim)->unk_0A.s;
                    s32 d3 = ((S_800253C0_5 *)object)->unk_88.s - old3;
                    ((S_800253C0_9 *)prim)->unk_0A.u = ((S_800253C0_9 *)prim)->unk_0A.u +
                                            d3 / ((S_800253C0_0 *)arg0)->unk_96.n;
                }
                h8a = ((S_800253C0_5 *)object)->unk_8A;
                ((S_800253C0_5 *)object)->unk_2A.v =
                    ((S_800253C0_5 *)object)->unk_2A.n & 0xFFF;
                cmp = ((S_800253C0_5 *)object)->unk_2A.n2;
                nang = ((S_800253C0_5 *)object)->unk_2A.n;
                h8a = h8a & 0xFFF;
                ((S_800253C0_5 *)object)->unk_8A = h8a;
                if (cmp != (s16)h8a) {
                    ((S_800253C0_5 *)object)->unk_2A.n = nang + 0x200;
                }
            }
            i++;
            record = (u8 *)record + 4;
        } while (i < 2);
        timer = ((S_800253C0_0 *)arg0)->unk_96.n - 1;
        ((S_800253C0_0 *)arg0)->unk_96.n = timer;
        if (timer > 0) {
            goto done;
        }
        ((S_800253C0_11 *)amounts)->unk_00 = 0x2C808080;
        i = 0;
        clearmask = 0xFFEFFFFF;
        record2 = arg0;
        do {
            object = ((S_800253C0_12 *)record2)->unk_AC;
            if (object != 0) {
                child = ((S_800253C0_5_pre *)object)[-1].unk_04;
                x = ((S_800253C0_17 *)child)->unk_24;
                prim = ((S_800253C0_5_pre *)object)[-1].unk_00;
                ((S_800253C0_9 *)prim)->unk_02.s = (x << 6) + 0x20;
                ((S_800253C0_9 *)prim)->unk_06.s = ((s32)((S_800253C0_17 *)child)->unk_25 << 6) + 0x20;
                ((S_800253C0_9 *)prim)->unk_0A.u = ((S_800253C0_5 *)object)->unk_88.u;
                ((S_800253C0_5 *)object)->unk_14 &= clearmask;
            }
            i++;
            record2 = (u8 *)record2 + 4;
        } while (i < 2);
        func_80025F78();
    }

    case 11:
    fa0 = arg2;
    ((S_800253C0_3 *)fa0)->unk_2C = D_800DD150;
    fa2 = 0;
    tp = D_800DD150 + ((((((Rec_D_80083160 *)D_80083160)->unk_C8.as_s16 +
          ((S_800253C0_1 *)arg3)->unk_2A.s) + 0x100) >> 9) & 7);
L_F6C:
    func_80048A44(fa0, *tp, fa2, 1);
    ((S_800253C0_0 *)arg0)->unk_9B.n++;
    goto done;

    case 12:
    if ((((S_800253C0_8 *)arg2)->unk_14 & 0xE000) == 0) {
        goto done;
    }
    {
        u8 *tb;
        u16 value;
        tb = D_80083460;
        value = ((S_800253C0_15 *)tb)->unk_02;
        ((S_800253C0_15 *)tb)->unk_0C = 0;
        ((S_800253C0_15 *)tb)->unk_02 = value | 0x812;
    }
    ((S_800253C0_0 *)arg0)->unk_8C = D_8008ACDC;

    case 13:
        break;
    }
done:
    return;
}
