#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_8003AD08();
extern s32 func_80041E70();
extern s32 func_800647A0();
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099254();
extern s32 func_80099290();
extern s32 func_8009929C();
extern s32 func_80099734();
extern s32 func_800A2AB8();
extern s32 func_800A56E0();
extern s32 func_800A5720();
extern s32 func_800B4C7C();

extern u16 D_80013714[];
extern u8 D_8006D168[];
extern u8 D_8006DE24[];
extern u16 D_80083460[];
extern s32 D_800835E8[];
extern M2C_UNK D_80089000;
extern s8 D_800DCF4F[];
extern u8 D_800DDCBC[];
extern M2C_UNK D_800E0458;
extern M2C_UNK D_800E098B;
extern M2C_UNK D_800E099A;
extern M2C_UNK D_800E09B2;
extern M2C_UNK D_800E09BB;

s32 func_800A2424(void *arg0, s32 arg1) {
    u8 flags[3];
    u8 *s1;
    u8 *s3;
    u8 *s4;
    s32 s2;
    s32 s5;
    s32 index;
    s32 i;
    s32 temp_v0;
    s32 value;
    s32 work;
    s32 shared_t0;
    volatile s32 *table;

    s1 = (u8 *)arg0;
    if (s1[0x11] < 2U) {
        func_800A2AB8();
        return 0;
    }
    s1[0x11] -= 1;
    s2 = s1[0x11];
    index = s1[0x13];
    table = D_800835E8;
    *(s32 *)(s1 + 0x18) = table[s2] - 1;
    s3 = D_800DDCBC + (index * 8);
    s5 = s2 - 1;
    s4 = D_8006D168 + (index * 0x18);

    {
        register s32 b ASM_REG("$6");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        s32 call_result;
        s32 first_left;
        s32 first_right;
        s32 second_left;
        s32 second_right;
        s32 second_partial;
        register s32 second_base ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
        s32 right;
        s32 partial;
        s32 current;
        call_result = func_800647A0((s5 * s3[5]) << 0xB, index);
        b = *(volatile u8 *)(s4 + 5);
        first_left = s3[5] * s5;
        if (first_left < 0) {
            first_left += 0xF;
        }
        first_right = s3[5] * call_result;
        partial = b + (first_left >> 4);
        if (first_right < 0) {
            first_right += 0x7FFF;
        }
        work = partial + (first_right >> 0xF);

        shared_t0 = s2 * s3[5];
        call_result = func_800647A0(shared_t0 << 0xB, first_right, b);
        second_base = *(volatile u8 *)(s4 + 5);
        second_left = s3[5] * s2;
        if (second_left < 0) {
            second_left += 0xF;
        }
        second_right = s3[5] * call_result;
        second_partial = second_base + (second_left >> 4);
        if (second_right < 0) {
            second_right += 0x7FFF;
        }
        right = second_partial + (second_right >> 0xF);
        ASM_KEEP(second_base);   /* MATCH pin: load-bearing for the whole function shape */

        current = s1[5] + (work - right);
        if (current == 0) {
            current = 1;
        }
        s1[5] = current;
    }

    {
        s32 left_product;
        s32 right_product;
        s32 right;
        s32 current;
        register s32 product ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
        {
            register s32 left_byte ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            s32 right_byte;
            left_byte = s3[4];
            right_byte = s4[4];
            product = left_byte * right_byte;
            left_product = product * s5;
        }
        if (left_product < 0) {
            left_product += 0x3FF;
        }
        right_product = product * s2;
        work = s4[4] + (left_product >> 0xA);
        if (right_product < 0) {
            right_product += 0x3FF;
        }
        ASM_KEEP_NV(work);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        right = s4[4] + (right_product >> 0xA);
        current = s1[4] + (work - right);
        if (current == 0) {
            current = 1;
        }
        s1[4] = current;
    }

    {
        register s32 left_byte ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        s32 right_byte;
        register s32 product ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
        s32 left_product;
        register s32 right_product ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        register s32 right ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        s32 current;
        left_byte = s3[0];
        right_byte = s4[0];
        product = left_byte * right_byte;
        left_product = product * s5;
        current = s1[0];
        if (left_product < 0) {
            left_product += 0x3F;
        }
        right_product = product * s2;
        work = s4[0] + (left_product >> 6);
        if (right_product < 0) {
            right_product += 0x3F;
        }
        right = s4[0] + (right_product >> 6);
        current += work - right;
        if (current == 0) {
            current = 1;
        }
        s1[0] = current;
    }

    {
        s32 decrement;
        register s32 left_byte ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        s32 right_byte;
        register s32 product ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
        s32 left_product;
        register s32 right_product ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        register s32 right ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        s32 current;
        decrement = s2 - 1;
        left_byte = s3[1];
        right_byte = s4[1];
        product = left_byte * right_byte;
        left_product = product * decrement;
        current = s1[1];
        if (left_product < 0) {
            left_product += 0x3F;
        }
        right_product = product * s2;
        work = right_byte + (left_product >> 6);
        if (right_product < 0) {
            right_product += 0x3F;
        }
        ASM_KEEP_NV(work);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        right = right_byte + (right_product >> 6);
        current += work - right;
        if (current == 0) {
            current = 1;
        }
        s1[1] = current;

        left_byte = s3[2];
        right_byte = s4[2];
        product = left_byte * right_byte;
        left_product = product * decrement;
        current = s1[2];
        if (left_product < 0) {
            left_product += 0x3F;
        }
        right_product = product * s2;
        work = right_byte + (left_product >> 6);
        if (right_product < 0) {
            right_product += 0x3F;
        }
        ASM_KEEP_NV(work);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        right = right_byte + (right_product >> 6);
        current += work - right;
        if (current == 0) {
            current = 1;
        }
        s1[2] = current;

        left_byte = s3[3];
        right_byte = s4[3];
        product = left_byte * right_byte;
        left_product = product * decrement;
        current = s1[3];
        if (left_product < 0) {
            left_product += 0x3FF;
        }
        right_product = product * s2;
        work = right_byte + (left_product >> 0xA);
        if (right_product < 0) {
            right_product += 0x3FF;
        }
        ASM_KEEP_NV(work);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        right = right_byte + (right_product >> 0xA);
        current += work - right;
        if (current == 0) {
            current = 1;
        }
        s1[3] = current;
    }

    {
        s16 height;
        register s32 height_product ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        s32 byte_product;
        s32 height_base;
        s32 product;
        u32 result;

        height = *(s16 *)(s4 + 6);
        height_product = s2 * height;
        byte_product = s3[6] * s2;
        ASM_KEEP(byte_product);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        shared_t0 = s2 * s2;
        height_base = height + byte_product;
        product = shared_t0 * height_base;
        result = height + height_product;
        if (product < 0) {
            product += 0x1FF;
        }
        result += product >> 9;
        if (result > 0xFFFFU) {
            result = 0xFFFF;
        }
        *(u16 *)(s1 + 6) = result;
    }

    if (s1[0x13] != 0) {
        i = 2;
        {
            register u8 *flags_base ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
            u8 *table2;
            register u8 *p ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 id ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            u8 *flagp;
            flags_base = flags;
            table2 = D_8006DE24;
            shared_t0 = 1;
            p = s1 + 6;
            do {
                flagp = flags_base + i;
                *flagp = 0;
                id = p[8];
                ASM_KEEP(id);   /* MATCH pin: retail delay-slot fill depends on it */
                if (id != 0 && (((table2[id * 0x14 + 0x10] >> 4) & (*(s32 *)(s1 + 0x14))) != 0)) {
                    u8 current = p[10];
                    if (current >= 2U) {
                        p[10] = current - 1;
                        *flagp = shared_t0;
                    }
                }
                i -= 1;
                p -= 3;
            } while (i >= 0);
        }
    }

    func_80041E70(s1);

    if (s1[0x29] < s1[0x28]) {
        s1[0x28] = s1[0x29];
    }
    if (s1[0x66] < s1[0x25]) {
        s1[0x25] = s1[0x66];
        s1[0x24] = (u8)0xFF;
    }
    if (s1[0x68] < s1[0x26]) {
        s1[0x26] = s1[0x68];
    }
    if (s1[0x69] < s1[0x27]) {
        s1[0x27] = s1[0x69];
    }

    if ((arg1 << 0x10) == 0) {
        return 1;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    {
        if (!(*(volatile u16 *)D_80013714 & 1)) {
            D_800DCF4F[0] = 1;
            D_80083460[5]++;
        }
        func_800B4C7C(0x8003, s1, -3, 1);
        func_800A56E0(0x615);

        temp_v0 = func_800990FC();
        value = func_80099194(&D_800E098B, temp_v0);
        value = func_8009929C(0xA, value);
        value = func_80099734(s1, value);
        value = func_80099194(&D_800E099A, value);
        value = func_8003AD08(s1[0x11], value);
        value = func_80099194(&D_80089000, value);

        if (s1[0x13] != 0 && ((*(s32 *)(s1 + 0x14) & 0x4000) != 0)) {
            i = 0;
            do {
                if (flags[i] != 0) {
                    value = func_8009929C(0xA, value);
                    value = func_80099194(*(s32 *)(D_8006DE24 + s1[8] * 0x14), value);
                    value = func_80099194(&D_800E09B2, value);
                    value = func_80099194(&D_800E09BB, value);
                }
                i += 1;
                s1 += 3;
            } while (i < 3);
        }

        if (!(D_80013714[0] & 1)) {
            value = func_8009929C(0x11, value);
            value = func_8009929C(0x4C, value);
            value = func_80099254(&D_800E0458, value);
        }
        func_80099290(value, value);
        func_800A5720(temp_v0);
    }
    return 1;
}
