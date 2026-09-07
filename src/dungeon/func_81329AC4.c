#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) Unaligned32;

extern void func_8016F140(void *arg0);
extern void func_8009A028(void *arg0);

extern void *D_80174AB4;
extern s16 D_80174AB8;
extern u8 D_80174B38[];
extern void *D_80174CD8;
extern Unaligned32 D_80013720;
extern u16 D_80013714;
extern s16 D_80013716;
extern s32 D_80013718;
extern s16 D_8001371A;
extern void *D_8001371C;
extern u32 D_800E296C[];
extern void *D_800E3D7C;

void func_801712C4(void)
{
    s32 i;
    u8 *cd8;
    u8 *header;
    u8 *source_page;
    u8 *state_page;

    D_80174AB4 = D_80174B38;
    cd8 = (u8 *)D_80174CD8 + 0x20;
    source_page = (u8 *)0x80170000;
    D_80174AB8 = 0;
    *(s16 *)(cd8 + 0xB2) = 1;
    *(s16 *)(cd8 + 0xB0) = 1;
    *(Unaligned32 *)0x80013720 =
        *(Unaligned32 *)(source_page + 0x4C58);
    D_800E296C[0] |= 0x08000000;
    state_page = (u8 *)0x80010000;
    *(s16 *)(state_page + 0x371A) = 0;
    *(s16 *)(state_page + 0x3718) = 0;
    *(s16 *)(state_page + 0x3716) = 0;
    *(void **)(state_page + 0x371C) = source_page + 0x4C58;
    *(u16 *)(state_page + 0x3714) =
        (*(u16 *)(state_page + 0x3714) | 9) & 0xFFEF;

    for (i = 0; i < 2; i++) {
        void *entry = *(void **)((u8 *)D_800E3D7C + i * 4 + 0xAC);

        if (entry != 0) {
            func_8016F140(entry);
            func_8009A028(*(void **)((u8 *)D_800E3D7C + i * 4 + 0xAC));
            header = *(u8 **)((u8 *)D_800E3D7C + i * 4 + 0xAC);
            header -= 0x20;
            *(u32 *)(header + 0x10) |= 0x80000000;
        }
    }
}
