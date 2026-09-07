#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
extern void func_80022F6C(void) __attribute__((noreturn));
extern void func_80022F50(void) __attribute__((noreturn));
extern void func_800230D0(void) __attribute__((noreturn));
extern void func_80023280(void) __attribute__((noreturn));
extern void func_80023284(void) __attribute__((noreturn));
extern void func_800232C8(void) __attribute__((noreturn));

void func_80022768(void *arg0, void *arg1_input)
{
    static void *const sw_keep[] = {
        &&sw_0, &&sw_1, &&sw_2, &&sw_3,
        &&sw_4, &&sw_5, &&sw_6, &&sw_7
    };
    State8081FF68 *state = arg0;
    register void *arg1 ASM_REG("$21") = arg1_input;
    u8 *global = D_80083160;
    u8 *callback;
    s32 values[3][3];

    (void)sw_keep;
    callback = D_80020224;

    if ((u32)((u16)FIELD(state, u16, 0x5C) - 2) < 5U) {
        s16 *angles = (s16 *)D_80083780;
        register s32 angle ASM_REG("$6");

        angle = func_800C2AE8(angles);
        if (angle > 0) {
            FIELD(angles, s32, 8) = 0xFFEE0000;
            angle = func_800C2AE8(angles);
            func_80022804();
        }
        {
            s16 current = FIELD(angles, s16, 0xA);
            register s32 delta ASM_REG("$2") = angle - current;
            register s32 half ASM_REG("$7");
            ASM_KEEP_NV(delta);
            half = delta >> 1;
            {
                register s32 result ASM_REG("$2") = angle - half;
                ASM_KEEP_NV(result);
                FIELD(angles, s16, 0xA) = result;
            }
        }
    }

    {
        s32 mode = FIELD(state, s16, 0x5C);
        if ((u32)mode >= 8U) {
            return;
        }
        goto *D_80020244[mode];
    }

sw_0:
    FIELD(state, u16, 0x62) = 0;
    FIELD(state, u16, 0x64) = 0;
    func_80093864();
    {
        s32 one = 1;
        do {
            FIELD(state, s16, 0x5C) = one;
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
    FIELD(state, u16, 0x64) = 1;
    FIELD(state, u16, 0x5E) = 5;
    FIELD(state, s16, 0x5C) = 2;
    func_800232C8();

sw_1:
    if ((FIELD(global, u32, 8) & 0x5000) != 0) {
        u16 timer = FIELD(state, u16, 0x5E);
        FIELD(state, u16, 0x5E) = (u16)(timer - 1);
        if ((s16)timer < 0) {
            FIELD(state, u16, 0x5E) = 0;
            func_80022904();
        }
    } else {
        FIELD(state, u16, 0x5E) = 5;
    }

    if ((FIELD(global, u32, 0x10) & 0x1000) != 0 ||
        ((FIELD(global, u32, 8) & 0x1000) != 0 &&
         (s16)FIELD(state, s16, 0x5E) <= 0)) {
        if (FIELD(state, u16, 0x64) < 3) {
            func_80053DA8(0x502);
            if ((u32)D_80012D5C[0] < 100U) {
                return;
            }
            FIELD(state, u16, 0x64)++;
            D_80012D5C[0] -= 100;
            func_800232C8();
        }
    }

    if ((FIELD(global, u32, 0x10) & 0x4000) != 0 ||
        ((FIELD(global, u32, 8) & 0x4000) != 0 &&
         (s16)FIELD(state, s16, 0x5E) <= 0)) {
        if (FIELD(state, u16, 0x64) >= 2) {
            func_80053DA8(0x502);
            D_80012D5C[0] += 100;
            FIELD(state, u16, 0x64)--;
            func_800232C8();
        }
    }

    if ((FIELD(global, u32, 0x10) & 0x20) != 0) {
        FIELD(state, u16, 0x5E) = 10;
        FIELD(state, s16, 0x5C) = 3;
        func_800232C8();
    }
    ASM_SCHED_BARRIER();
    if ((FIELD(global, u32, 0x10) & 0x40) == 0 ||
        FIELD(state, u16, 0x64) == 0) {
        return;
    }
    func_80053DA8(0x526);
    FIELD(state, u16, 0x5E) = 20;
    FIELD(state, s16, 0x5C) = 4;
    func_800232C8();

sw_2:
    {
        u16 timer = (u16)(FIELD(state, u16, 0x5E) - 1);
        FIELD(state, u16, 0x5E) = timer;
        if ((s16)timer > 0) {
            return;
        }
        D_80012D5C[0] += FIELD(state, u16, 0x64) * 100;
        func_800B1DBC((void *)D_80024638[0]);
        FIELD(state, s16, 0x5C) = 0;
        func_800232C8();
    }

sw_5:
    {
        u16 timer = (u16)(FIELD(state, u16, 0x5E) - 1);
        u8 *slotp;
        register s32 i ASM_REG("$7");
        s32 value;
        FIELD(state, u16, 0x5E) = timer;
        if ((s16)timer > 0) {
            return;
        }
        i = 2;
        value = i;
        slotp = (u8 *)state + 8;
        do {
            void *obj = FIELD(slotp, void *, 0x4C);
            slotp -= 4;
            i--;
            FIELD(obj, s16, 0x24) = (s16)value;
        } while (i >= 0);
        FIELD(state, s16, 0x5C) = 5;
        func_800232C8();
    }

sw_3:
    {
        s16 index = FIELD(state, s16, 0x5E);
        void *obj = FIELD((u8 *)(((s32)index << 2) + (s32)state),
                          void *, 0x4C);
        if (FIELD(obj, s16, 0x24) != 3) {
            return;
        }
        FIELD(state, s16, 0x5C) = 6;
        FIELD(state, u16, 0x60) = 0;
        func_800232C8();
    }

sw_4:
    func_80053DA8(0x524);
    {
        u16 timer = FIELD(state, u16, 0x60);
        FIELD(state, u16, 0x60) = timer - 1;
        if ((s16)timer <= 0)
            FIELD(state, u16, 0x60) = 0;
    }
    if ((FIELD(global, u32, 0x10) & 0x40) != 0 &&
        FIELD(state, s16, 0x60) == 0) {
        void *obj;
        func_80053DA8(0x522);
        obj = FIELD((u8 *)(((s32)(s16)FIELD(state, s16, 0x5E) << 2) +
                          (s32)state), void *, 0x4C);
        FIELD(obj, s16, 0x24) = 4;
        FIELD(state, u16, 0x60) = 10;
        FIELD(state, u16, 0x5E)++;
    }
    goto sw_6;

sw_6:
    {
        s32 i = 2;
    if (FIELD(state, s16, 0x5E) != 3) {
        return;
    }
    FIELD(state, s32, 0x58) = 0;
    {
        register u8 *slotp ASM_REG("$12") = (u8 *)state + 8;
        register u8 *table_base ASM_REG("$2") = D_800244B8;
        register u8 *table ASM_REG("$10") = table_base + 0x18;
        register s32 *out ASM_REG("$8") = &values[2][0];
        register s32 j ASM_REG("$6");
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
            register s32 n ASM_REG("$4");
            n = (s16)FIELD(FIELD(p, void *, 0x4C), s16, 0x2A);
            *q = row[(j + n) % 12];
            q--;
        }
        if (--j >= 0) goto inner_top;
        slotp -= 4;
        table -= 12;
        out -= 3;
        if (--i >= 0) goto outer_top;

        {
            register s32 k ASM_REG("$7");
            k = 0;
            if (FIELD(state, u16, 0x64) == 0)
                goto count_done;
            {
                s16 *lookup_base = D_800244E8;
                register s16 *lookup = lookup_base;
                do {
                s32 amount;
                s32 multiplier;
                s32 value;
                u16 flags;
                switch (k) {
                default:
                    func_80022F6C();
                case 0:
                    if (values[0][1] == values[1][1] &&
                        values[0][1] == values[2][1]) {
                        value = values[0][1];
                        multiplier = (s32)lookup[value] * 100;
                        amount = FIELD(state, u16, 0x64) * multiplier;
                        flags = FIELD(state, u16, 0x62);
                        FIELD(state, u16, 0x62) = flags | 4;
                        FIELD(state, s32, 0x58) += amount;
                        if (values[1][1] == 0) {
                            FIELD(state, u16, 0x62) = flags | 5;
                            func_80022F6C();
                        }
                    }
                    break;
                case 1:
                    if (values[0][0] == values[1][0] &&
                        values[0][0] == values[2][0]) {
                        FIELD(state, u16, 0x62) |= 0x10;
                        value = values[0][0];
                        multiplier = (s32)lookup[value] * 100;
                        amount = FIELD(state, u16, 0x64) * multiplier;
                        FIELD(state, s32, 0x58) += amount;
                        if (values[0][0] == 0) {
                            FIELD(state, u16, 0x62) |= 1;
                        }
                    }
                    if (values[0][2] == values[1][2] &&
                        values[0][2] == values[2][2]) {
                        FIELD(state, u16, 0x62) |= 8;
                        value = values[2][2];
                        multiplier = (s32)lookup[value] * 100;
                        amount = FIELD(state, u16, 0x64) * multiplier;
                        FIELD(state, s32, 0x58) += amount;
                        {
                            s32 tail_value = values[2][2];
                            ASM_KEEP(tail_value);
                        }
                        func_80022F50();
                    }
                    break;
                case 2:
                    if (values[0][0] == values[1][1] &&
                        values[2][2] == values[0][0]) {
                        FIELD(state, u16, 0x62) |= 0x40;
                        value = values[1][1];
                        multiplier = (s32)lookup[value] * 100;
                        amount = FIELD(state, u16, 0x64) * multiplier;
                        FIELD(state, s32, 0x58) += amount;
                        if (values[1][1] == 0) {
                            FIELD(state, u16, 0x62) |= 1;
                        }
                    }
                    if (values[0][2] == values[1][1] &&
                        values[2][0] == values[0][2]) {
                        FIELD(state, u16, 0x62) |= 0x20;
                        value = values[1][1];
                        multiplier = (s32)lookup[value] * 100;
                        amount = FIELD(state, u16, 0x64) * multiplier;
                        FIELD(state, s32, 0x58) += amount;
                        if (values[1][1] == 0) {
                            FIELD(state, u16, 0x62) |= 1;
                        }
                    }
                    break;
                }
                    k++;
                } while (k < FIELD(state, u16, 0x64));
            }
        }
count_done:
    }
    if (FIELD(state, s32, 0x58) == 0) {
        FIELD(state, u16, 0x5E) = 10;
        FIELD(state, u16, 0x64) = 0;
        FIELD(state, s16, 0x5C) = 3;
        func_800232C8();
    }

    if ((FIELD(state, u16, 0x62) & 1) != 0) {
        register void *obj ASM_REG("$17") = func_8003FC64(0x100);
        if (obj != NULL) {
            FIELD(obj, void *, 0x10) = D_80023BCC;
        }
    }

    {
        register s32 value ASM_REG("$2") = FIELD(state, s32, 0x58);
        register s32 q1 ASM_REG("$7");
        s32 q2;
        s32 q3;
        register s32 raw0 ASM_REG("$8");
        s32 raw1;
        s32 raw2;
        s32 d0;
        register s32 d1 ASM_REG("$9");
        s32 d2;
        s32 product2;
        register s32 sum ASM_REG("$6");
        q1 = value / 100;
        q2 = q1 / 10;
        value = q2 * 10;
        raw0 = q1 - value;
        value = raw0 << 16;
        d0 = value >> 16;
        ASM_KEEP_NV(d0);
        q3 = q2 / 10;
        value = q3 * 10;
        raw1 = q2 - value;
        value = raw1 << 16;
        d1 = value >> 16;
        ASM_KEEP_NV(d1);
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
    FIELD(state, u16, 0x5E) = 0;
    FIELD(state, s16, 0x5C) = 7;
    func_800232C8();
    }

sw_7:
    FIELD(state, u16, 0x5E)++;
    if ((s16)FIELD(state, u16, 0x5E) == 9) {
        func_80093864();
    }
    if ((FIELD(state, u16, 0x5E) & 3) != 0) {
        return;
    }
    {
        s16 *digits = D_80024630;
    if ((s16)digits[0] + (s16)digits[1] + (s16)digits[2] == 0) {
        if ((FIELD(state, u16, 0x62) & 2) == 0) {
            void *old_obj = (void *)D_80024638[0];
            FIELD(state, u16, 0x64) = 0;
            func_800B1DBC(old_obj);
            FIELD(state, u16, 0x5E) = 10;
            FIELD(state, s16, 0x5C) = 3;
        }
        FIELD(state, u16, 0x62) &= (u16)~2;
        func_800232C8();
    }

    {
        void *obj = func_8003FC64(0x136);
        void *call_obj;
        u8 *prim;
        u8 *draw;
        register u8 *sub ASM_REG("$18");
        if (obj == NULL) {
            return;
        }
        call_obj = obj;
        ASM_KEEP_NV(call_obj);
        FIELD(obj, void *, 0x10) = D_800236BC;
        FIELD(FIELD(obj, u8 *, 8), s32, 0) =
            FIELD(arg1, s32, 0) + (s32)0xFEC00000;
        FIELD(FIELD(obj, u8 *, 8), s32, 4) =
            FIELD(arg1, s32, 4) + (s32)0xFFC00000;
        FIELD(FIELD(obj, u8 *, 8), s32, 8) =
            FIELD(arg1, s32, 8) + (s32)0xFFC00000;
        prim = FIELD(obj, u8 *, 8);
        FIELD(prim, s32, 0x10) = 0;
        FIELD(prim, s32, 0xC) = 0;
        FIELD(FIELD(obj, u8 *, 8), s32, 0x14) = 0x40000;
        func_8004491C(call_obj, D_80045340);
        draw = FIELD(obj, u8 *, 0xC);
        FIELD(draw, s16, 0x1E) = 0x1000;
        FIELD(draw, s16, 0x1C) = 0x1000;
        sub = (u8 *)obj + 0x20;
        if (digits[2] != 0) {
            digits[2]--;
            FIELD(sub, s16, 0x54) = 2;
        } else if (digits[1] != 0) {
            digits[1]--;
            FIELD(sub, s16, 0x54) = 1;
            FIELD(draw, u16, 0x12) = (u16)(FIELD(draw, u16, 0x12) - 5);
        } else if (digits[0] != 0) {
            digits[0]--;
            FIELD(sub, s16, 0x54) = 0;
            FIELD(draw, u16, 0x12) = (u16)(FIELD(draw, u16, 0x12) + 5);
        }
        {
            u8 *prim = draw;
            u8 *source = D_8007947C;
            FIELD(prim, void *, 0) = source;
            FIELD(prim, s32, 8) = FIELD(source, s32, 4);
            FIELD(prim, u8, 4) = 0;
            FIELD(prim, u8, 5) = 0;
            FIELD(prim, s32, 0xC) = 0x00808080;
        }
        FIELD(sub, void *, 0) = state;
        FIELD(sub, void *, 0x50) = callback;
        func_8008F074(sub + 8, FIELD(obj, void *, 8), D_80024488);
    }
    }
}
