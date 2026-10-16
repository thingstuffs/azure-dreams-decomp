#include "common.h"

extern void clearResidentBitmapBit(s32 flag_id);
extern s16 D_800D15C0[];

/* Processes the terminated ID list, 54 evenly spaced IDs, and ID 0xD31. */
void townProcessTerminatedShopIds(void)
{
    s32 list_index;
    s32 range_index;

    if (D_800D15C0[0] != 0) {
        list_index = 0;
        do {
            clearResidentBitmapBit(D_800D15C0[list_index]);
            list_index++;
        } while (D_800D15C0[list_index] != 0);
    }

    range_index = 0;
    do {
        clearResidentBitmapBit((0x03F40000 + (range_index * 0x2B0000)) >> 16);
        range_index++;
    } while (range_index < 54);

    clearResidentBitmapBit(0xD31);
}
