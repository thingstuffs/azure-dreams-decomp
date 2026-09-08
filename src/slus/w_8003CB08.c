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

/* Swap draw buffers and update the animated coordinate history on a new display field. */
void func_8003CB08(void)
{
    void **draw_buffer = &D_80083160[0];

    if ((D_80082E60.field_0 & 3) == 1) {
        u8 field_id = (u8)((u32)VSync(1) >> 8);

        if (field_id != D_80080AAA) {
            u8 *next_buffer;
            s32 layer;
            s32 trig_value;
            s32 wave_offset;
            s32 center_offset;

            D_80080AAA = field_id;
            PutDispEnv((u8 *)D_80083160[0] + 0x5C);
            PutDrawEnv(*draw_buffer);

            next_buffer = D_801C9E40[0];
            if (*draw_buffer == D_801C9E40[0]) {
                next_buffer += 0x108D4;
            }
            D_80083160[0] = next_buffer;
            *(u32 *)(next_buffer + 0x8D0) = (u32)next_buffer + 0x8D4;

            if (D_80080AA6 != D_80083960[0]) {
                D_80080AA6 = D_80083960[0];
                D_80080AA8 = 8;
            }

            {
                register s32 remaining ASM_REG("$16") = 63;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                s16 *y_history = D_800838D8;
                s16 *y_dst = y_history + 63;
                s16 *y_src = y_history + 62;
                s16 *x_history = D_80083858;
                s16 *x_dst = x_history + 63;
                s16 *x_src = x_history + 62;

                do {
                    *x_dst = *x_src;
                    x_src--;
                    remaining--;
                    *y_dst = *y_src;
                    y_src--;
                    x_dst--;
                    y_dst--;
                } while (remaining > 0);
            }

            layer = 3;
            trig_value = rcos(D_80080AA4 * 80);
            {
                s16 *x_head = D_80083858;
                wave_offset = trig_value >> 7;
                ASM_KEEP(wave_offset);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                center_offset = shift10(trig_value) + 0x100;
                *x_head = (s16)(wave_offset + center_offset);
            }

            trig_value = rsin(D_80080AA4 * 80);
            {
                s16 *y_head = D_800838D8;
                wave_offset = trig_value >> 7;
                ASM_KEEP(wave_offset);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                center_offset = shift10(trig_value) + 0xB0;
                *y_head = (s16)(wave_offset + center_offset);
            }

            func_8003D0F0();
            for (; layer >= 0; layer--) {
                func_8003CCB0(layer);
            }

            if (D_80080AA8 != 0) {
                D_80080AA8--;
            }
            DrawSync(0);
            D_80080AA4++;
        }
    }
}
