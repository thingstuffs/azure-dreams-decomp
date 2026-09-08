#include "common.h"


extern u16 D_80013714;
extern u8 D_80082E80[];
extern s32 D_800E296C[];
extern void *D_800E3D7C;


typedef struct S_800A5C70_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A5C70_0_pre;   /* the 0x14 bytes before cursor in func_800A5C70, addressed as cursor[-1] */

typedef struct S_800A5C70_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_800A5C70_0;   /* cursor in func_800A5C70 */

typedef struct S_800A5C70_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A5C70_1;   /* coords in func_800A5C70 */

typedef struct S_800A5C70_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A5C70_2;   /* other in func_800A5C70 */

s32 func_800A5C70(void) {
    u16 buttons;
    u8 *coords;
    void **cursor_addr;
    void *cursor;
    void *start;
    S_800A5C70_2 *other;

    cursor_addr = &D_800E3D7C;
    do {
        buttons = D_80013714;
    } while (0);
    cursor = *cursor_addr;
    if (buttons & 2) {
        return 1;
    }
    if (buttons & 9) {
        return 0;
    }
    if (D_800E296C[0] & 0x200000) {
        return 0;
    }

    coords = D_80082E80;
    start = cursor;
    do {
        if (!(((S_800A5C70_0 *)cursor)->unk_1C & 0x2208)) {
            register s32 delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            other = ((S_800A5C70_0_pre *)cursor)[-1].unk_00;
            delta = ((S_800A5C70_1 *)coords)->unk_24;
            delta -= other->unk_24;
            if (delta < 0) {
                delta = -delta;
            }
            if (delta < 5) {
                delta = ((S_800A5C70_1 *)coords)->unk_25;
                delta -= other->unk_25;
                if (delta < 0) {
                    delta = -delta;
                }
                if (delta < 5) {
                    return 0;
                }
            }
        }
        cursor = (u8 *)((S_800A5C70_0 *)cursor)->unk_5C + 0x20;
    } while (cursor != start);

    return 1;
}
