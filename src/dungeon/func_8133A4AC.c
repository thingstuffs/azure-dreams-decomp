#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"

extern void func_800982A8(void *, void *);
extern s16 D_80173AFC[];
extern u8 *D_80175D54;
extern u8 D_80175DBC[];

/* Initializes an offset position and sends a message at action phase three. */
void func_801714AC(void *action, void *position)
{
    u8 *object = D_80175D54;
    u8 *object_position = *(u8 **)(object + 8);
    u8 *object_data = object + 0x20;

    if (*(s16 *)((u8 *)action + 0x12) == 0) {
        s16 *direction_offsets = D_80173AFC;

        ((s32 *)position)[0] = ((s32 *)object_position)[0];
        ((s32 *)position)[1] = ((s32 *)object_position)[1];
        ((s32 *)position)[2] = ((s32 *)object_position)[2];
        *(u16 *)((u8 *)position + 2) +=
            *(s16 *)((u8 *)direction_offsets +
                     ((*(u16 *)(object_data + 0x2A) >> 7) & 0x1C)) * 6;
        *(u16 *)((u8 *)position + 6) +=
            *(s16 *)((u8 *)direction_offsets +
                     ((*(u16 *)(object_data + 0x2A) >> 7) & 0x1C) + 2) * 6;
    }

    if (*(s16 *)((u8 *)action + 0x12) == 3) {
        u8 *message;

        D_80175DBC[0] = 11;
        message = D_80175DBC;
        message[1] = 15;
        message[2] = 0;
        message[3] = 0;
        func_800982A8(((u8 *)D_800E3D7C), message);
        ((u16 *)action)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
