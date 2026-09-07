#include "common.h"

typedef struct {
    u8 pad00[0x68];
    void (*func68)(void *, void *, s32, void *);
} CallbackTable;

typedef struct {
    u8 pad00[0x68];
    void (*func68)(void *, void *, u32);
} CallbackTable3;

typedef struct {
    s32 w[4];
} Block;

typedef struct {
    s32 value;
    u8 pad04[8];
} IntGlobal;

typedef struct {
    volatile CallbackTable *value;
    u8 pad04[8];
} CallbackGlobal;

extern u8 D_807030AC[];
extern IntGlobal D_807030A8;
extern CallbackGlobal D_807030B8;
extern u8 D_807028B0[];
extern u8 D_807028BC[];
extern u8 D_807028C4[];
extern u8 D_807028D4[];
extern u8 D_807028E8[];

void func_80878974(s32 *arg0) {
    register u32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */
    Block *src;
    Block *end;
    Block *dst;

    dst = (Block *)(D_807030AC - 0xC);
    src = (Block *)arg0;
    end = (Block *)((u8 *)arg0 + 0x30);
    ASM_USE(dst);   /* MATCH pin: retail register colouring depends on it */
    do {
        *dst++ = *src++;
    } while (src != end);
    dst->w[0] = src->w[0];
    ASM_USE(dst);   /* MATCH pin: retail register colouring depends on it */

    D_807030B8.value->func68(D_807028B0, D_807028BC, *(s32 *)((u8 *)arg0 + 8), dst);
    ((CallbackTable3 *)D_807030B8.value)->func68(D_807028B0, D_807028C4, D_807030A8.value);
    ((CallbackTable3 *)D_807030B8.value)->func68(D_807028D4, D_807028E8, zero | 0x2F);
}
