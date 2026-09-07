#include "common.h"

extern u32 D_80029548;
extern u32 D_8002954C;

void *func_80028654(void *a0, void *a1) {
    register u32 type ASM_REG("$6");
    u8 *src = (u8 *)a1;

    *(u32 *)((u8 *)a0 + 4) = D_8002954C;
    *((u8 *)a0 + 1) = 0x48;
    *((u8 *)a0 + 2) = src[0];
    do { *((u8 *)a0 + 3) = src[2]; } while (0);
    *((u8 *)a0 + 0xA) = src[4];
    *((u8 *)a0 + 0xB) = src[6];

    a0 = (u8 *)a0 + 0xC;

    *(u32 *)((u8 *)a0 + 4) = D_8002954C;
    *((u8 *)a0 + 1) = 0x48;
    *((u8 *)a0 + 2) = src[0];
    *((u8 *)a0 + 3) = src[2];
    *((u8 *)a0 + 0xA) = src[4] + 1;
    *((u8 *)a0 + 0xB) = src[6] + 1;

    a0 = (u8 *)a0 + 0xC;

    *(u32 *)((u8 *)a0 + 4) = D_80029548;
    *((u8 *)a0 + 1) = 0x48;
    *((u8 *)a0 + 2) = src[0];
    *((u8 *)a0 + 3) = src[2];
    *((u8 *)a0 + 0xA) = src[4];
    *((u8 *)a0 + 0xB) = src[6];
    type = 3;
    ASM_KEEP(type);
    *((u8 *)a0 + 0) = type;

    a0 = (u8 *)a0 + 0xC;

    *(u32 *)((u8 *)a0 + 4) = D_80029548;
    *((u8 *)a0 + 1) = 0x48;
    *((u8 *)a0 + 2) = src[0];
    *((u8 *)a0 + 3) = src[2];
    *((u8 *)a0 + 0xA) = src[4] + 1;
    *((u8 *)a0 + 0xB) = src[6] + 1;
    *((u8 *)a0 + 0) = type;
    return a0;
}
