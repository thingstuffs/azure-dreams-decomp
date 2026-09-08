#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct State8081FF68 {
    u8 pad00[0x4C];
    void *slot[3];
    s32 work;
    s16 mode;
    u16 timer;
    u16 timer2;
    u16 flags;
    u16 count;
} State8081FF68;

extern u8 D_80020224[];
extern void *D_80020244[8];
extern u8 D_80083160[];
extern u8 D_80083780[];
extern s32 D_80012D5C[];
extern s32 D_80024638[];
extern s16 D_80024630[8];
extern s16 D_800244E8[16];
extern u8 D_800244B8[0x30];
extern u8 D_80024488[0x10];
extern u8 D_80024470[];
extern u8 D_80045340[];
extern u8 D_800236BC[];
extern u8 D_80023BCC[];
extern u8 D_8007947C[];
extern s16 D_800834C8[8];

__asm__(".set D_80020244, 0x80020244");
__asm__(".set D_80024630, 0x80024630");
__asm__(".set D_80024638, 0x80024638");
__asm__(".set D_800244E8, 0x800244e8");
__asm__(".set D_800244B8, 0x800244b8");
__asm__(".set D_80024488, 0x80024488");
__asm__(".set D_800236BC, 0x800236bc");
__asm__(".set D_80023BCC, 0x80023bcc");
__asm__(".set D_8007947C, 0x8007947c");
__asm__(".set D_800834C8, 0x800834c8");

extern s16 func_800C2AE8(void *arg0);
extern void func_80093864(void);
extern s32 func_800A2A18(void *arg0, void *arg1);
extern s16 func_80053DA8(s32 arg0);
extern void *func_800B1BEC(s32 arg0, s32 arg1, s32 arg2);
extern void *func_80093C70(void);
extern void func_800B1DBC(void *arg0);
extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_8008F074(void *arg0, void *arg1, void *arg2);

extern void func_80022804(void) __attribute__((noreturn));
extern void func_80022904(void) __attribute__((noreturn));
extern void func_80022F50(void) __attribute__((noreturn));
extern void func_800230D0(void) __attribute__((noreturn));
extern void func_80023280(void) __attribute__((noreturn));
extern void func_80023284(void) __attribute__((noreturn));


typedef struct S_80022768_0 {
    u8 pad_00[0x58];
    s32 unk_58;
    union { u16 u; s16 s; } unk_5C;   /* accessed as both */
    union { u16 u; s16 s; } unk_5E;   /* accessed as both */
    union { u16 u; s16 s; } unk_60;   /* accessed as both */
    u16 unk_62;
    u16 unk_64;
} S_80022768_0;   /* state in func_80022768 */

typedef struct S_80022768_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80022768_1;   /* angles in func_80022768 */

typedef struct S_80022768_2 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x4];
    u32 unk_10;
} S_80022768_2;   /* global in func_80022768 */

typedef struct S_80022768_3 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_80022768_3;   /* slotp in func_80022768 */

typedef struct S_80022768_4 {
    u8 pad_00[0x8];
    union { u8 * p; void * p2; } unk_08;   /* accessed as both */
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0x10];
    s16 unk_24;
} S_80022768_4;   /* obj in func_80022768 */

typedef struct S_80022768_5 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_80022768_5;   /* (u8 *)(((s32)index << 2) + (s32)state) in func_80022768 */

typedef struct S_80022768_6 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_80022768_6;   /* p in func_80022768 */

typedef struct S_80022768_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80022768_7;   /* arg1 in func_80022768 */

typedef struct S_80022768_8 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_80022768_8;   /* prim in func_80022768 */

typedef struct S_80022768_9 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x8];
    s16 unk_1C;
    s16 unk_1E;
} S_80022768_9;   /* draw in func_80022768 */

typedef struct S_80022768_10 {
    void * unk_00;
    u8 pad_04[0x4C];
    void * unk_50;
    s16 unk_54;
} S_80022768_10;   /* sub in func_80022768 */

typedef struct S_80022768_11 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80022768_11;   /* source in func_80022768 */

typedef struct S_80022768_12 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_80022768_12;   /* (u8 *)(((s32)(s16)((S_80022768_0 *)state)->unk_5E.s << 2) +
                          (s32)state) in func_80022768 */

typedef struct S_80022768_13 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80022768_13;   /* ((S_80022768_6 *)p)->unk_4C in func_80022768 */

typedef struct S_80022768_14 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80022768_14;   /* ((S_80022768_4 *)obj)->unk_08.p in func_80022768 */

void func_80022768(void *arg0, void *arg1_input)
{
    static void *const sw_keep[] = {
        &&sw_0, &&sw_1, &&sw_2, &&sw_3,
        &&sw_4, &&sw_5, &&sw_6, &&sw_7
    };
    State8081FF68 *state = arg0;
    register void *arg1 ASM_REG("$21") = arg1_input;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *global = D_80083160;
    u8 *callback;
    s32 values[3][3];

    (void)sw_keep;
    callback = D_80020224;

    if ((u32)((u16)((S_80022768_0 *)state)->unk_5C.u - 2) < 5U) {
        s16 *angles = (s16 *)D_80083780;
        register s32 angle ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        angle = func_800C2AE8(angles);
        if (angle > 0) {
            ((S_80022768_1 *)angles)->unk_08.at00.v = 0xFFEE0000;
            angle = func_800C2AE8(angles);
            func_80022804();
        }
        {
            s16 current = ((S_80022768_1 *)angles)->unk_08.at02.v;
            register s32 delta ASM_REG("$2") = angle - current;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 half ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            half = delta >> 1;
            {
                register s32 result ASM_REG("$2") = angle - half;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ((S_80022768_1 *)angles)->unk_08.at02.v = result;
            }
        }
    }

    {
        s32 mode = ((S_80022768_0 *)state)->unk_5C.s;
        if ((u32)mode >= 8U) {
            return;
        }
        goto *D_80020244[mode];
    }

sw_0:
    ((S_80022768_0 *)state)->unk_62 = 0;
    ((S_80022768_0 *)state)->unk_64 = 0;
    func_80093864();
    {
        s32 one = 1;
        do {
            ((S_80022768_0 *)state)->unk_5C.s = one;
        } while (0);
    }
    {
        s32 *money = D_80012D5C;
        if ((u32)money[0] < 100U) {
            return;
        }
        if (func_800A2A18(D_80024470, arg1) == 0) {
            return;
        }
        func_80053DA8(0x523);
        D_80024638[0] = (s32)func_800B1BEC(0, -80, 64);
        D_800834C8[0] = 0;
        func_80093C70();
        money[0] -= 100;
    }
    (*(u16 *)((u8 *)state + (0x64))) = 1;
    (*(u16 *)((u8 *)state + (0x5E))) = 5;
    (*(s16 *)((u8 *)state + (0x5C))) = 2;
    return;

sw_1:
    if ((((S_80022768_2 *)global)->unk_08 & 0x5000) != 0) {
        u16 timer = ((S_80022768_0 *)state)->unk_5E.u;
        ((S_80022768_0 *)state)->unk_5E.u = (u16)(timer - 1);
        if ((s16)timer < 0) {
            ((S_80022768_0 *)state)->unk_5E.u = 0;
            func_80022904();
        }
    } else {
        ((S_80022768_0 *)state)->unk_5E.u = 5;
    }

    if ((((S_80022768_2 *)global)->unk_10 & 0x1000) != 0 ||
        ((((S_80022768_2 *)global)->unk_08 & 0x1000) != 0 &&
         (s16)((S_80022768_0 *)state)->unk_5E.s <= 0)) {
        if (((S_80022768_0 *)state)->unk_64 < 3) {
            func_80053DA8(0x502);
            if ((u32)D_80012D5C[0] < 100U) {
                return;
            }
            ((S_80022768_0 *)state)->unk_64++;
            D_80012D5C[0] -= 100;
            return;
        }
    }

    if ((((S_80022768_2 *)global)->unk_10 & 0x4000) != 0 ||
        ((((S_80022768_2 *)global)->unk_08 & 0x4000) != 0 &&
         (s16)((S_80022768_0 *)state)->unk_5E.s <= 0)) {
        if (((S_80022768_0 *)state)->unk_64 >= 2) {
            func_80053DA8(0x502);
            D_80012D5C[0] += 100;
            ((S_80022768_0 *)state)->unk_64--;
            return;
        }
    }

    if ((((S_80022768_2 *)global)->unk_10 & 0x20) != 0) {
        ((S_80022768_0 *)state)->unk_5E.u = 10;
        ((S_80022768_0 *)state)->unk_5C.s = 3;
        return;
    }
       /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if ((((S_80022768_2 *)global)->unk_10 & 0x40) == 0 ||
        ((S_80022768_0 *)state)->unk_64 == 0) {
        return;
    }
    func_80053DA8(0x526);
    ((S_80022768_0 *)state)->unk_5E.u = 20;
    ((S_80022768_0 *)state)->unk_5C.s = 4;
    return;

sw_2:
    {
        u16 timer = (u16)(((S_80022768_0 *)state)->unk_5E.u - 1);
        ((S_80022768_0 *)state)->unk_5E.u = timer;
        if ((s16)timer > 0) {
            return;
        }
        D_80012D5C[0] += ((S_80022768_0 *)state)->unk_64 * 100;
        func_800B1DBC((void *)D_80024638[0]);
        ((S_80022768_0 *)state)->unk_5C.s = 0;
        return;
    }

sw_5:
    {
        u16 timer = (u16)(((S_80022768_0 *)state)->unk_5E.u - 1);
        u8 *slotp;
        register s32 i ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 value;
        ((S_80022768_0 *)state)->unk_5E.u = timer;
        if ((s16)timer > 0) {
            return;
        }
        i = 2;
        value = i;
        slotp = (u8 *)state + 8;
        do {
            void *obj = ((S_80022768_3 *)slotp)->unk_4C;
            slotp -= 4;
            i--;
            ((S_80022768_4 *)obj)->unk_24 = (s16)value;
        } while (i >= 0);
        ((S_80022768_0 *)state)->unk_5C.s = 5;
        return;
    }

sw_3:
    {
        s16 index = ((S_80022768_0 *)state)->unk_5E.s;
        void *obj = ((S_80022768_5 *)((u8 *)(((s32)index << 2) + (s32)state)))->unk_4C;
        if (((S_80022768_4 *)obj)->unk_24 != 3) {
            return;
        }
        ((S_80022768_0 *)state)->unk_5C.s = 6;
        ((S_80022768_0 *)state)->unk_60.u = 0;
        return;
    }

sw_4:
    func_80053DA8(0x524);
    {
        u16 timer = ((S_80022768_0 *)state)->unk_60.u;
        ((S_80022768_0 *)state)->unk_60.u = timer - 1;
        if ((s16)timer <= 0)
            ((S_80022768_0 *)state)->unk_60.u = 0;
    }
    if ((((S_80022768_2 *)global)->unk_10 & 0x40) != 0 &&
        ((S_80022768_0 *)state)->unk_60.s == 0) {
        void *obj;
        func_80053DA8(0x522);
        obj = ((S_80022768_12 *)((u8 *)(((s32)(s16)((S_80022768_0 *)state)->unk_5E.s << 2) +
                          (s32)state)))->unk_4C;
        ((S_80022768_4 *)obj)->unk_24 = 4;
        ((S_80022768_0 *)state)->unk_60.u = 10;
        ((S_80022768_0 *)state)->unk_5E.u++;
    }
    goto sw_6;

sw_6:
    {
        s32 i = 2;
    if (((S_80022768_0 *)state)->unk_5E.s != 3) {
        return;
    }
    ((S_80022768_0 *)state)->unk_58 = 0;
    {
        register u8 *slotp ASM_REG("$12") = (u8 *)state + 8;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u8 *table_base ASM_REG("$2") = D_800244B8;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *table ASM_REG("$10") = table_base + 0x18;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 *out = &values[2][0];
        register s32 j ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *row;
        u8 *p;
        s32 *q;

    outer_top:
        j = 2;
        row = table;
        p = slotp;
        q = out + 2;
    inner_top:
        {
            register s32 n ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            n = (s16)((S_80022768_13 *)(((S_80022768_6 *)p)->unk_4C))->unk_2A;
            *q = row[(j + n) % 12];
            q--;
        }
        if (--j >= 0) goto inner_top;
        slotp -= 4;
        table -= 12;
        out -= 3;
        if (--i >= 0) goto outer_top;

        {
            i = 0;
            if (((S_80022768_0 *)state)->unk_64 == 0)
                goto count_done;
            {
                s16 *lookup_base = D_800244E8;
                register s16 *lookup = lookup_base;
                do {
                s32 amount;
                s32 multiplier;
                s32 value;
                u16 flags;
                switch (i) {
                case 0:
                    if (values[0][1] == values[1][1] &&
                        values[0][1] == values[2][1]) {
                        value = values[0][1];
                        multiplier = (s32)lookup[value] * 100;
                        amount = ((S_80022768_0 *)state)->unk_64 * multiplier;
                        flags = ((S_80022768_0 *)state)->unk_62;
                        ((S_80022768_0 *)state)->unk_62 = flags | 4;
                        ((S_80022768_0 *)state)->unk_58 += amount;
                        if (values[1][1] == 0) {
                            ((S_80022768_0 *)state)->unk_62 = flags | 5;
                        }
                    }
                    break;
                case 1:
                    if (values[0][0] == values[1][0] &&
                        values[0][0] == values[2][0]) {
                        ((S_80022768_0 *)state)->unk_62 |= 0x10;
                        value = values[0][0];
                        multiplier = (s32)lookup[value] * 100;
                        amount = ((S_80022768_0 *)state)->unk_64 * multiplier;
                        ((S_80022768_0 *)state)->unk_58 += amount;
                        if (values[0][0] == 0) {
                            ((S_80022768_0 *)state)->unk_62 |= 1;
                        }
                    }
                    if (values[0][2] == values[1][2] &&
                        values[0][2] == values[2][2]) {
                        ((S_80022768_0 *)state)->unk_62 |= 8;
                        value = values[2][2];
                        multiplier = (s32)lookup[value] * 100;
                        amount = ((S_80022768_0 *)state)->unk_64 * multiplier;
                        ((S_80022768_0 *)state)->unk_58 += amount;
                        {
                            s32 tail_value = values[2][2];
                            ASM_KEEP(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        }
                        func_80022F50();
                    }
                    break;
                case 2:
                    if (values[0][0] == values[1][1] &&
                        values[2][2] == values[0][0]) {
                        ((S_80022768_0 *)state)->unk_62 |= 0x40;
                        value = values[1][1];
                        multiplier = (s32)lookup[value] * 100;
                        amount = ((S_80022768_0 *)state)->unk_64 * multiplier;
                        ((S_80022768_0 *)state)->unk_58 += amount;
                        if (values[1][1] == 0) {
                            ((S_80022768_0 *)state)->unk_62 |= 1;
                        }
                    }
                    if (values[0][2] == values[1][1] &&
                        values[2][0] == values[0][2]) {
                        ((S_80022768_0 *)state)->unk_62 |= 0x20;
                        value = values[1][1];
                        multiplier = (s32)lookup[value] * 100;
                        amount = ((S_80022768_0 *)state)->unk_64 * multiplier;
                        ((S_80022768_0 *)state)->unk_58 += amount;
                        if (values[1][1] == 0) {
                            ((S_80022768_0 *)state)->unk_62 |= 1;
                        }
                    }
                    break;
                }
                    i++;
                } while (i < ((S_80022768_0 *)state)->unk_64);
            }
        }
count_done:
    }
    if (((S_80022768_0 *)state)->unk_58 == 0) {
        ((S_80022768_0 *)state)->unk_5E.u = 10;
        ((S_80022768_0 *)state)->unk_64 = 0;
        ((S_80022768_0 *)state)->unk_5C.s = 3;
        return;
    }

    if ((((S_80022768_0 *)state)->unk_62 & 1) != 0) {
        register void *obj ASM_REG("$17") = func_8003FC64(0x100);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        if (obj != NULL) {
            ((S_80022768_4 *)obj)->unk_10 = D_80023BCC;
        }
    }

    {
        register s32 value ASM_REG("$2") = ((S_80022768_0 *)state)->unk_58;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 q2;
        s32 q3;
        s32 raw0;
        s32 raw1;
        s32 raw2;
        s32 d0;
        s32 d1;
        s32 d2;
        s32 product2;
        register s32 sum ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        i = value / 100;
        q2 = i / 10;
        value = q2 * 10;
        raw0 = i - value;
        value = raw0 << 16;
        d0 = value >> 16;
        ASM_KEEP_NV(d0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        q3 = q2 / 10;
        value = q3 * 10;
        raw1 = q2 - value;
        value = raw1 << 16;
        d1 = value >> 16;
        sum = d0 + d1;
        product2 = (q3 / 10) * 10;
        raw2 = q3 - product2;
        value = raw2 << 16;
        d2 = value >> 16;
        D_80024630[0] = raw0;
        D_80024630[1] = raw1;
        D_80024630[2] = raw2;
        {
        sum += d2;
        value = sum < 10;
        if (value) {
            if (d2 > 0) {
                s32 adjusted = raw2 - 1;
                D_80024630[2] = adjusted;
                adjusted = raw1 + 10;
                D_80024630[1] = adjusted;
            } else if (d1 > 0) {
                s32 adjusted = raw1 - 1;
                D_80024630[1] = adjusted;
                adjusted = raw0 + 10;
                D_80024630[0] = adjusted;
            }
        }
        }
    }
    ((S_80022768_0 *)state)->unk_5E.u = 0;
    ((S_80022768_0 *)state)->unk_5C.s = 7;
    return;
    }

sw_7:
    ((S_80022768_0 *)state)->unk_5E.u++;
    if ((s16)((S_80022768_0 *)state)->unk_5E.u == 9) {
        func_80093864();
    }
    if ((((S_80022768_0 *)state)->unk_5E.u & 3) != 0) {
        return;
    }
    {
        s16 *digits = D_80024630;
    if ((s16)digits[0] + (s16)digits[1] + (s16)digits[2] == 0) {
        if ((((S_80022768_0 *)state)->unk_62 & 2) == 0) {
            void *old_obj = (void *)D_80024638[0];
            ((S_80022768_0 *)state)->unk_64 = 0;
            func_800B1DBC(old_obj);
            ((S_80022768_0 *)state)->unk_5E.u = 10;
            ((S_80022768_0 *)state)->unk_5C.s = 3;
        }
        ((S_80022768_0 *)state)->unk_62 &= (u16)~2;
        return;
    }

    {
        void *obj = func_8003FC64(0x136);
        void *call_obj;
        u8 *prim;
        u8 *draw;
        register u8 *sub ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        if (obj == NULL) {
            return;
        }
        call_obj = obj;
        ((S_80022768_4 *)obj)->unk_10 = D_800236BC;
        ((S_80022768_14 *)(((S_80022768_4 *)obj)->unk_08.p))->unk_00 =
            ((S_80022768_7 *)arg1)->unk_00 + (s32)0xFEC00000;
        ((S_80022768_14 *)(((S_80022768_4 *)obj)->unk_08.p))->unk_04 =
            ((S_80022768_7 *)arg1)->unk_04 + (s32)0xFFC00000;
        ((S_80022768_14 *)(((S_80022768_4 *)obj)->unk_08.p))->unk_08 =
            ((S_80022768_7 *)arg1)->unk_08 + (s32)0xFFC00000;
        prim = ((S_80022768_4 *)obj)->unk_08.p;
        ((S_80022768_8 *)prim)->unk_10 = 0;
        ((S_80022768_8 *)prim)->unk_0C = 0;
        ((S_80022768_14 *)(((S_80022768_4 *)obj)->unk_08.p))->unk_14 = 0x40000;
        func_8004491C(call_obj, D_80045340);
        draw = ((S_80022768_4 *)obj)->unk_0C;
        ((S_80022768_9 *)draw)->unk_1E = 0x1000;
        ((S_80022768_9 *)draw)->unk_1C = 0x1000;
        sub = (u8 *)obj + 0x20;
        if (digits[2] != 0) {
            digits[2]--;
            ((S_80022768_10 *)sub)->unk_54 = 2;
        } else if (digits[1] != 0) {
            digits[1]--;
            ((S_80022768_10 *)sub)->unk_54 = 1;
            ((S_80022768_9 *)draw)->unk_12 = (u16)(((S_80022768_9 *)draw)->unk_12 - 5);
        } else if (digits[0] != 0) {
            digits[0]--;
            ((S_80022768_10 *)sub)->unk_54 = 0;
            ((S_80022768_9 *)draw)->unk_12 = (u16)((*(u16 *)((u8 *)draw + (0x12))) + 5);
        }
        {
            u8 *prim = draw;
            u8 *source = D_8007947C;
            (*(void * *)((u8 *)prim + (0))) = source;
            ((S_80022768_8 *)prim)->unk_08 = ((S_80022768_11 *)source)->unk_04;
            ((S_80022768_8 *)prim)->unk_04 = 0;
            ((S_80022768_8 *)prim)->unk_05 = 0;
            ((S_80022768_8 *)prim)->unk_0C = 0x00808080;
        }
        ((S_80022768_10 *)sub)->unk_00 = state;
        ((S_80022768_10 *)sub)->unk_50 = callback;
        func_8008F074(sub + 8, ((S_80022768_4 *)obj)->unk_08.p2, D_80024488);
    }
    }
}
