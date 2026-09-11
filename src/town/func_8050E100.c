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

/* Installs the town callback, enforces a minimum town value of 40, and runs the setup sequence. */
void func_8050E100(void)
{
    s32 current_town_value;
    S_8050E100_1 *town = ((S_8050E100_0 *)(*(void **)D_80016000))->unk_38;

    current_town_value = town->unk_35BE;
    D_80017618 = func_80017560;
    if (current_town_value < 40) {
        town->unk_35BE = 40;
    }
    func_800173F8(0xAE3, town);
    func_800173F8(0xAE4);
    D_80017614 = 0;
    func_800173F8(0xAE6);
}
