#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80016000[0x10];
extern void (*D_80017618)(void);
extern s16 D_80017614;

extern void func_800173F8();
extern void func_80017560(void);

void func_8050E100(void)
{
    register s32 value ASM_REG("$3");
#ifndef NON_MATCHING
    register u8 *func_page ASM_REG("$2");
#endif
    void *town = FIELD(*(void **)D_80016000, void *, 0x38);
#ifndef NON_MATCHING
    register u8 *page ASM_REG("$4") = (u8 *)0x80010000;

    ASM_KEEP(page);
    func_page = (u8 *)0x80010000;
    ASM_KEEP(func_page);
#endif
    value = FIELD(town, s16, 0x35BE);
    ASM_KEEP(value);

    do {
#ifdef NON_MATCHING
        D_80017618 = func_80017560;
#else
        *(void (**)(void))(page + 0x7618) =
            (void (*)(void))(func_page + 0x7560);
#endif
    } while (0);
    if (value < 40) {
        FIELD(town, s16, 0x35BE) = 40;
    }
    func_800173F8(0xAE3, town);
    func_800173F8(0xAE4);
    do {
        D_80017614 = 0;
    } while (0);
    func_800173F8(0xAE6);
}
