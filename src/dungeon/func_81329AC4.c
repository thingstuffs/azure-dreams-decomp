#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) Unaligned32;

extern void func_8016F140(void *arg0);
extern void func_8009A028(void *arg0);

extern void *D_80174AB4[3];
extern s16 D_80174AB8[5];
extern u8 D_80174B38[];
extern void *D_80174CD8[3];
extern void *D_800E3D7C[3];
extern u32 D_800E296C[];
extern Unaligned32 D_80174C58;

void func_801712C4(void)
{
    s32 i;
    u8 *cd8;
    u8 *header;

    D_80174AB4[0] = D_80174B38;
    cd8 = (u8 *)D_80174CD8[0] + 0x20;
    D_80174AB8[0] = 0;
    {
        Unaligned32 *source;
        Unaligned32 *destination;

        *(s16 *)(cd8 + 0xB2) = 1;
        *(s16 *)(cd8 + 0xB0) = 1;

        destination = (Unaligned32 *)0x80013720;
        source = &D_80174C58;
        *destination = *source;

        {
            u32 value;
            register u8 *state_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            u32 flags;

            value = D_800E296C[0];
            value |= 0x08000000;
            state_page = (u8 *)0x80010000;
            D_800E296C[0] = value;
            flags = *(u16 *)(state_page + 0x3714);
            *(s16 *)(state_page + 0x371A) = 0;
            *(s16 *)(state_page + 0x3718) = 0;
            *(s16 *)(state_page + 0x3716) = 0;
            *(void **)(state_page + 0x371C) = (void *)&D_80174C58;
            *(u16 *)(state_page + 0x3714) = (flags | 9) & 0xFFEF;
        }
    }

    for (i = 0; i < 2; i++) {
        void *entry = *(void **)((u8 *)D_800E3D7C[0] + i * 4 + 0xAC);

        if (entry != 0) {
            func_8016F140(entry);
            func_8009A028(*(void **)((u8 *)D_800E3D7C[0] + i * 4 + 0xAC));
            header = *(u8 **)((u8 *)D_800E3D7C[0] + i * 4 + 0xAC);
            header -= 0x20;
            *(u32 *)(header + 0x10) |= 0x80000000;
        }
    }
}
