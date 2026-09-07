#include "common.h"

#include "common.h"

typedef struct {
    s32 word;
    s8 byte4;
    s8 byte5;
} __attribute__((packed)) Copy6;

typedef struct {
    s32 word0;
    s32 word4;
    s8 byte8;
    s8 byte9;
} __attribute__((packed)) Copy10;

extern void bzero(void *ptr, s32 size);
extern u8 D_80080AB4[10];
extern u8 D_8002D5B4[10];

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define LEGACY_ASM_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#define LEGACY_ASM_KEEP(value) ASM_KEEP(value)
#endif

void func_8003D468(void)
{
    u8 *page = (u8 *)0x80010000;
    void *clear_page = page;
    u8 saved_3186;
    u32 saved_3180;
    u8 saved_3184;
    u8 saved_2d6e;
    u16 saved_2094;
    u16 saved_2098;

    LEGACY_ASM_KEEP(page);
    LEGACY_ASM_KEEP(clear_page);

    saved_3186 = *(u8 *)(page + 0x3186);
    saved_3180 = *(u32 *)(page + 0x3180);
    saved_3184 = *(u8 *)(page + 0x3184);
    saved_2d6e = *(u8 *)(page + 0x2D6E);
    saved_2094 = *(u16 *)(page + 0x2094);
    saved_2098 = *(u16 *)(page + 0x2098);

    bzero(clear_page, 0x5C84);

    *(Copy6 *)0x8001020C = *(Copy6 *)D_80080AB4;
    *(Copy10 *)0x80010238 = *(Copy10 *)D_8002D5B4;

    *(u8 *)(page + 0x3186) = saved_3186;
    *(u32 *)(page + 0x3180) = saved_3180;
    *(u8 *)(page + 0x3184) = saved_3184;
    *(u8 *)(page + 0x2D6E) = saved_2d6e;
    *(u16 *)(page + 0x2094) = saved_2094;
    *(u16 *)(page + 0x2098) = saved_2098;
}
