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
extern s32 func_800A5720();
extern s32 func_800B4C7C();

extern u16 D_80013714[];
extern u8 D_8006D168[];
extern u8 D_8006DE24[];
extern u16 D_80083460[];
extern M2C_UNK D_80089000;
extern s8 D_800DCF4F[];
extern u8 D_800DDCBC[];
extern M2C_UNK D_800E0458;
extern M2C_UNK D_800E0953;
extern M2C_UNK D_800E095F;
extern M2C_UNK D_800E0970;
extern M2C_UNK D_800E0979;

s32 func_800A1D4C(void *arg0, s32 arg1) {
    u8 flags[3];
    u8 *s2;
    u8 *s3;
    u8 *s4;
    register s32 s1 ASM_REG("$17");
    s32 s5;
    s32 index;
    s32 i;
    s32 temp_v0;
    s32 value;
    s32 mode;
    s32 work;
    s32 shared_t0;

    s2 = (u8 *)arg0;
    if (s2[0x11] < 99U) {
        s1 = s2[0x11];
        index = s2[0x13];
        s2[0x11] = s1 + 1;
        s3 = D_800DDCBC + (index * 8);
        s5 = s1 - 1;
        s4 = D_8006D168 + (index * 0x18);

        {
            register s32 b ASM_REG("$6");
            s32 call_result;
            s32 first_left;
            s32 first_right;
            s32 second_left;
            s32 second_right;
            s32 second_partial;
            register s32 second_base ASM_REG("$5");
            s32 right;
            s32 partial;
            s32 current;
            s32 old;
            register s32 delta ASM_REG("$4");
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

            shared_t0 = s1 * s3[5];
            call_result = func_800647A0(shared_t0 << 0xB, first_right, b);
            second_base = *(volatile u8 *)(s4 + 5);
            second_left = s3[5] * s1;
            if (second_left < 0) {
                second_left += 0xF;
            }
            second_right = s3[5] * call_result;
            second_partial = second_base + (second_left >> 4);
            if (second_right < 0) {
                second_right += 0x7FFF;
            }
            right = second_partial + (second_right >> 0xF);
            ASM_KEEP(second_base);

            current = s2[5];
            old = current;
            current += right - work;
            if ((u32) current >= 0x100) {
                current = 0xFF;
            }
            delta = current - old;
            s2[5] = current;
            s2[0x28] += delta;
        }

        {
            s32 left_product;
            s32 right_product;
            s32 right;
            s32 current;
            s32 old;
            register s32 delta ASM_REG("$4");
            register s32 product ASM_REG("$16");
            {
                register s32 left_byte ASM_REG("$2");
                s32 right_byte;
                left_byte = s3[4];
                right_byte = s4[4];
                product = left_byte * right_byte;
                left_product = product * s5;
            }
            if (left_product < 0) {
                left_product += 0x3FF;
            }
            right_product = product * s1;
            work = s4[4] + (left_product >> 0xA);
            if (right_product < 0) {
                right_product += 0x3FF;
            }
            ASM_KEEP_NV(work);
            right = s4[4] + (right_product >> 0xA);
            current = s2[4];
            old = current;
            current += right - work;
            if ((u32) current >= 0x100) {
                current = 0xFF;
            }
            delta = current - old;
            s2[4] = current;
            s2[0x25] += delta;
        }

        {
            register s32 left_byte ASM_REG("$2");
            s32 right_byte;
            register s32 product ASM_REG("$16");
            s32 left_product;
            register s32 right_product ASM_REG("$4");
            register s32 right ASM_REG("$2");
            s32 current;
            s32 old;
            register s32 delta ASM_REG("$4");
            left_byte = s3[0];
            right_byte = s4[0];
            product = left_byte * right_byte;
            left_product = product * s5;
            current = s2[0];
            old = current;
            if (left_product < 0) {
                left_product += 0x3F;
            }
            right_product = product * s1;
            work = s4[0] + (left_product >> 6);
            if (right_product < 0) {
                right_product += 0x3F;
            }
            right = s4[0] + (right_product >> 6);
            current += right - work;
            if ((u32) current >= 0x100) {
                current = 0xFF;
            }
            delta = current - old;
            s2[0] = current;
            s2[0x26] += delta;
        }

        {
            s32 decrement;
            register s32 left_byte ASM_REG("$2");
            s32 right_byte;
            register s32 product ASM_REG("$16");
            s32 left_product;
            register s32 right_product ASM_REG("$4");
            register s32 right ASM_REG("$2");
            s32 current;
            s32 old;
            register s32 delta ASM_REG("$4");
            decrement = s1 - 1;

            left_byte = s3[1];
            right_byte = s4[1];
            product = left_byte * right_byte;
            left_product = product * decrement;
            current = s2[1];
            old = current;
            if (left_product < 0) {
                left_product += 0x3F;
            }
            right_product = product * s1;
            work = right_byte + (left_product >> 6);
            if (right_product < 0) {
                right_product += 0x3F;
            }
            right = right_byte + (right_product >> 6);
            current += right - work;
            if ((u32) current >= 0x100) {
                current = 0xFF;
            }
            delta = current - old;
            s2[1] = current;
            s2[0x27] += delta;

            left_byte = s3[2];
            right_byte = s4[2];
            product = left_byte * right_byte;
            left_product = product * decrement;
            current = s2[2];
            if (left_product < 0) {
                left_product += 0x3F;
            }
            right_product = product * s1;
            work = right_byte + (left_product >> 6);
            if (right_product < 0) {
                right_product += 0x3F;
            }
            ASM_KEEP_NV(work);
            right = right_byte + (right_product >> 6);
            current += right - work;
            if ((u32) current >= 0x100) {
                current = 0xFF;
            }
            s2[2] = current;

            left_byte = s3[3];
            right_byte = s4[3];
            product = left_byte * right_byte;
            left_product = product * decrement;
            current = s2[3];
            if (left_product < 0) {
                left_product += 0x3FF;
            }
            right_product = product * s1;
            work = right_byte + (left_product >> 0xA);
            if (right_product < 0) {
                right_product += 0x3FF;
            }
            ASM_KEEP_NV(work);
            right = right_byte + (right_product >> 0xA);
            current += right - work;
            if ((u32) current >= 0x100) {
                current = 0xFF;
            }
            s2[3] = current;
        }

        {
            s16 height;
            register s32 height_product ASM_REG("$4");
            s32 byte_product;
            s32 height_base;
            s32 product;
            u32 result;

            height = *(s16 *)(s4 + 6);
            height_product = s1 * height;
            byte_product = s3[6] * s1;
            ASM_KEEP(byte_product);
            shared_t0 = s1 * s1;
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
            *(u16 *)(s2 + 6) = result;
        }

        if (s2[0x13] != 0) {
            u8 *flags_base;
            s32 one;
            u8 *table2;
            s32 limit;
            register u8 *p ASM_REG("$5");
            u8 *flagp;
            s32 id;

            i = 2;
            flags_base = flags;
            table2 = D_8006DE24;
            one = 1;
            limit = 100 - s1;
            p = s2 + 6;
            do {
                flagp = flags_base + i;
                *flagp = 0;
                id = p[8];
                if (id != 0) {
                    s32 mask = table2[id * 0x14 + 0x10] >> 4;
                    if ((mask & (*(s32 *)(s2 + 0x14))) || !(mask & 7)) {
                        s32 cur = p[10];
                        if ((u32) cur < 99U) {
                            s32 nv;
                            s32 t;
                            p[10] = cur + 1;
                            *flagp = one;
                            id = p[10];
                            t = 99;
                            t = t - id;
                            t = t / limit;
                            nv = t + id;
                            if (nv >= 100) {
                                nv = 99;
                            }
                            p[10] = nv;
                        }
                    }
                }
                i -= 1;
                p -= 3;
            } while (i >= 0);
        }

        func_80041E70(s2);

        if ((arg1 << 0x10) != 0) {
            if (!(D_80013714[0] & 1)) {
                D_800DCF4F[0] = 1;
                D_80083460[5]++;
            }
            mode = 0x8003;
            if ((*(s32 *)(s2 + 0x14) & 0x2000) != 0) {
                mode = 0x8002;
            }
            func_800B4C7C(mode, s2, -2, 1);

            temp_v0 = func_800990FC();
            value = func_80099194(&D_800E0953, temp_v0);
            value = func_8009929C(0xA, value);
            value = func_80099734(s2, value);
            value = func_80099194(&D_800E095F, value);
            value = func_8003AD08(s2[0x11], value);
            value = func_80099194(&D_80089000, value);

            if (s2[0x13] != 0 && ((*(s32 *)(s2 + 0x14) & 0x4000) != 0)) {
                u8 *p;
                u8 *tbl;
                i = 0;
                tbl = D_8006DE24;
                p = s2;
                do {
                    if (flags[i] != 0) {
                        value = func_8009929C(0xA, value);
                        value = func_80099194(*(s32 *)(tbl + p[8] * 0x14), value);
                        value = func_80099194(&D_800E0970, value);
                        value = func_80099194(&D_800E0979, value);
                    }
                    i += 1;
                    p += 3;
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
    }
}
