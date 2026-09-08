#include "common.h"

typedef struct S_8050E100_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8050E100_0;   /* *(void **)D_80016000 in func_8050E100 */

typedef struct S_8050E100_1 {
    u8 pad_00[0x35BE];
    s16 unk_35BE;
} S_8050E100_1;   /* town in func_8050E100 */



extern u8 D_80016000[0x10];
extern void (*D_80017618)(void);
extern s16 D_80017614;

extern void func_800173F8();
extern void func_80017560(void);

void func_8050E100(void)
{
    s32 value;
#ifndef NON_MATCHING
    u8 *func_page;
#endif
    S_8050E100_1 *town = ((S_8050E100_0 *)(*(void **)D_80016000))->unk_38;
#ifndef NON_MATCHING
    u8 *page = (u8 *)0x80010000;

    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    func_page = (u8 *)0x80010000;
    ASM_KEEP(func_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
#endif
    value = town->unk_35BE;

    do {
#ifdef NON_MATCHING
        D_80017618 = func_80017560;
#else
        *(void (**)(void))(page + 0x7618) =
            (void (*)(void))(func_page + 0x7560);
#endif
    } while (0);
    if (value < 40) {
        town->unk_35BE = 40;
    }
    func_800173F8(0xAE3, town);
    func_800173F8(0xAE4);
    do {
        D_80017614 = 0;
    } while (0);
    func_800173F8(0xAE6);
}
