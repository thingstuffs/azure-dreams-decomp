#include "common.h"

struct S_80082E60 {
    s32 field_0;
    u8 pad[12];
};

extern struct S_80082E60 D_80082E60;
extern void *D_80083160[3];
extern u8 D_801C9E40[2][0x108D4];
extern u16 D_80083960[5];
extern s16 D_80080AA4;
extern u16 D_80080AA6;
extern u16 D_80080AA8;
extern u8 D_80080AAA;
extern s16 D_80083858[64];
extern s16 D_800838D8[64];
extern s32 VSync(s32 mode);
extern void PutDispEnv(void *env);
extern void PutDrawEnv(void *env);
extern void DrawSync(s32 mode);
extern s32 rcos(s32 arg0);
extern s32 rsin(s32 arg0);
extern void func_8003D0F0(void);
extern void func_8003CCB0(s32 arg0);

static inline s32 shift10(s32 value)
{
    return value >> 10;
}
void func_8003CB08(void)
{
    void **display = &D_80083160[0];

    if ((D_80082E60.field_0 & 3) == 1) {
        u8 field = (u8)((u32)VSync(1) >> 8);

        if (field != D_80080AAA) {
            u8 *next;
            s32 i;
            s32 result;
            s32 high;
            s32 low;

            D_80080AAA = field;
            PutDispEnv((u8 *)D_80083160[0] + 0x5C);
            PutDrawEnv(*display);

            next = D_801C9E40[0];
            if (*display == D_801C9E40[0]) {
                next += 0x108D4;
            }
            D_80083160[0] = next;
            *(u32 *)(next + 0x8D0) = (u32)next + 0x8D4;

            if (D_80080AA6 != D_80083960[0]) {
                D_80080AA6 = D_80083960[0];
                D_80080AA8 = 8;
            }

            {
                register s32 count ASM_REG("$16") = 63;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                s16 *base2 = D_800838D8;
                s16 *dst2 = base2 + 63;
                s16 *src2 = base2 + 62;
                s16 *base1 = D_80083858;
                s16 *dst1 = base1 + 63;
                s16 *src1 = base1 + 62;

                do {
                    *dst1 = *src1;
                    src1--;
                    count--;
                    *dst2 = *src2;
                    src2--;
                    dst1--;
                    dst2--;
                } while (count > 0);
            }

            i = 3;
            result = rcos(D_80080AA4 * 80);
            {
                s16 *out = D_80083858;
                high = result >> 7;
                ASM_KEEP(high);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                low = shift10(result) + 0x100;
                *out = (s16)(high + low);
            }

            result = rsin(D_80080AA4 * 80);
            {
                s16 *out = D_800838D8;
                high = result >> 7;
                ASM_KEEP(high);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                low = shift10(result) + 0xB0;
                *out = (s16)(high + low);
            }

            func_8003D0F0();
            for (; i >= 0; i--) {
                func_8003CCB0(i);
            }

            if (D_80080AA8 != 0) {
                D_80080AA8--;
            }
            DrawSync(0);
            D_80080AA4++;
        }
    }
}
