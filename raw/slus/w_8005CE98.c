#include "common.h"

/* SPU hardware register mirror reached through D_80079958 (base 0x1F801C00). */
typedef struct {
    u8  pad000[0x1A6];
    volatile u16 dt_addr;   /* 0x1A6 */
    volatile u16 dt_fifo;   /* 0x1A8 */
    volatile u16 spucnt;    /* 0x1AA */
    u16 pad1AC;
    volatile u16 spustat;   /* 0x1AE */
} SpuRegs;

extern SpuRegs *D_80079958;
extern u16 D_80079970;
extern char D_800331F4[];
extern char D_80033214[];
extern char D_80033228[];

extern void func_8005D730(void);
extern void printf();

void func_8005CE98(u16 *src, u32 size)
{
    u16 *p;
    u16 stat;
    u16 mask;
    s32 n;
    s32 i;
    u32 tries;
    u32 m;
    u16 c;

    p = src;
    stat = D_80079958->spustat;
    D_80079958->dt_addr = D_80079970;
    mask = stat & 0x7FF;
    func_8005D730();

    while (size != 0) {
        n = 0x40;
        if (size < 0x41) {
            n = size;
        }
        for (i = 0; i < n; i += 2) {
            D_80079958->dt_fifo = *p++;
        }
        c = D_80079958->spucnt;
        c = (c & 0xFFCF) | 0x10;
        D_80079958->spucnt = c;
        func_8005D730();
        tries = 0;
        while (D_80079958->spustat & 0x400) {
            if (++tries >= 0xF01) {
                printf(D_800331F4, D_80033214);
                break;
            }
        }
        func_8005D730();
        func_8005D730();
        size -= n;
    }

    m = mask;
    tries = 0;
    c = D_80079958->spucnt;
    c &= 0xFFCF;
    D_80079958->spucnt = c;
    while ((D_80079958->spustat & 0x7FF) != m) {
        if (++tries >= 0xF01) {
            printf(D_800331F4, D_80033228);
            break;
        }
    }
}
