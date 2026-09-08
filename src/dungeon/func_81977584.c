#include "common.h"

typedef struct {
    s16 u0[2];
    s16 type;
    s16 index;
    s16 add;
    s16 scale0;
    s16 step;
    s16 u14[3];
    s16 scale10;
    s16 scale11;
    s16 u24[23];
    s16 f35;
    s16 f36;
    s16 u37[3];
    s16 f40;
    s16 f41;
    s16 f42;
    s16 u43[22];
    s16 f65;
    s16 f66;
    s16 u67[3];
    s16 f70;
    s16 f71;
    s16 f72;
} Record;

extern s32 func_80024E38(void) __attribute__((noreturn));
extern void func_80024770(s32, s32, s32);
extern void func_80024A30(s32, s32, s32, s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

s32 func_81977584(Record *a) {
    register s32 s2 = 0;
    register s16 *p;
    s32 *out;
    s32 s4;
    register s32 s5;
    s32 s6;
    register s32 s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 t0;
    s32 t1;

    out = (s32 *)0x1F800000;

    if (a->type == 1) {
        goto type_1_or_2;
    }
    if (a->type >= 2) {
        goto type_ge_2;
    }
    if (a->type == 0) {
        goto type_0;
    }
    ASM_KEEP(s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s2 &= 0xffff;
    ASM_TAILSLOT_PIN(s2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024E38();

type_ge_2:
    if (a->type == 2) {
        goto type_1_or_2;
    }
    if (a->type == 3) {
        goto type_3;
    }
    ASM_KEEP(s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s2 &= 0xffff;
    ASM_TAILSLOT_PIN(s2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024E38();

type_0:
    {
        s32 index = a->index;
        s32 value;

        value = (index << 2) + index;
        s2 = value << 18;
        ASM_TAILSLOT_PIN(s2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024E38();
    }

type_1_or_2:
    s2 = 0xA0 << 16;
    ASM_TAILSLOT_PIN(s2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024E38();

type_3:
            {
                s32 value = a->index;
                register s32 product ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                ASM_KEEP_NV(value);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                product = (value << 2) + value;
                product <<= 2;
                value = 160 - product;
                s2 = value << 16;
            }
            s2 /= 29;


            {
                s32 scale;
                s32 product;
                s32 shifted;
                s32 result;

                result = func_800644B8(a->f40 + a->add);
                scale = a->scale10;
                product = (result >> 4) * scale;
                shifted = product << 8;
                out[12] = shifted;

                result = func_800644B8(a->f41 + a->add);
                scale = a->scale11;
                product = (result >> 4) * scale;
                shifted = product << 8;
                out[16] = shifted;

                result = func_800644B8(a->f35 + a->add);
                scale = a->scale0;
                product = (result >> 4) * scale;
                shifted = product << 8;
                out[20] = shifted;

                result = func_80064584(a->f40 + a->add);
                scale = a->scale10;
                product = (result >> 4) * scale;
                shifted = product << 8;
                out[13] = shifted;

                result = func_80064584(a->f41 + a->add);
                scale = a->scale11;
                product = (result >> 4) * scale;
                shifted = product << 8;
                out[17] = shifted;

                {
                    s32 angle;

                    angle = a->f35 + a->add;
                    s6 = 0;
                    result = func_80064584(angle);
                }
                {
                register s32 v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 v1;
                register s32 a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register s32 a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register s32 a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                a1 = (s2 * 3) << 3;
                v1 = ((a1 - s2) >> 16) & 0xff;
                ASM_KEEP_NV(v1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                a0 = (v1 << 8) + v1;
                s5 = (a0 << 8) + v1;
                ASM_KEEP_NV(s5);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                result >>= 4;
                ASM_KEEP_NV(result);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

                v1 = s2 << 3;
                v1 -= s2;
                v1 <<= 2;
                v1 += s2;
                a0 = a->scale0;
                v1 >>= 16;
                product = result * a0;
                ASM_KEEP(v1);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                v1 &= 0xff;
                ASM_KEEP_NV(v1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                a1 = (a1 >> 16) & 0xff;
                ASM_KEEP_NV(a1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                v0 = (v1 << 8) + v1;
                s7 = (v0 << 8) + v1;

                a0 = (a1 << 8) + a1;
                a0 = (a0 << 8) | a1;

                shifted = product << 8;
                out[21] = shifted;

                out[14] = a->f70 << 16;
                a1 = s5;
                out[18] = a->f71 << 16;
                a2 = s7;
                out[22] = a->f65 << 16;
                s4 = a2;
                func_80024770(a0, a1, a2);
            }
            }

            p = (s16 *)a;
            out[24] = out[20];
            out[25] = out[21];
            out[26] = out[22];
            do {
                s32 pr;
                s32 old5;
                s32 old4;
                s32 final_result;
                s32 final_product;
                s32 saved22;

                ASM_KEEP_NV(p);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                out[12] = out[16];
                pr = (func_800644B8(p[42] + a->add) >> 4) * p[12];
                out[20] = out[24];
                out[16] = pr << 8;
                pr = (func_800644B8(p[36] + a->add) >> 4) * p[6];
                out[13] = out[17];
                out[24] = pr << 8;
                pr = (func_80064584(p[42] + a->add) >> 4) * p[12];
                ASM_KEEP_NV(pr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                out[21] = out[25];
                out[17] = pr << 8;
                final_result = func_80064584(p[36] + a->add);

                t0 = (22 - s6) * s2;
                t1 = (28 - s6) * s2;
                s7 = s4;
                old5 = s5;
                old4 = s7;
                final_product = (final_result >> 4) * p[6];
                out[14] = out[18];
                s5 = (((t0 >> 16) & 0xff) * 0x10101);
                s4 = (((t1 >> 16) & 0xff) * 0x10101);
                saved22 = out[26];
                out[25] = final_product << 8;
                out[18] = p[72] << 16;
                out[22] = saved22;
                out[26] = p[66] << 16;
                func_80024A30(old5, s5, old4, s4);
                p++;
                ++s6;
            } while (s6 < 23);

            out[12] = out[16];
            out[16] = out[24];
            out[13] = out[17];
            out[17] = out[25];
            out[14] = out[18];
            out[18] = out[26];
            func_80024770(s5, s4, s7);
            return 0;
}
