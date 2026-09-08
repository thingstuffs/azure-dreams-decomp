#include "common.h"

/* S_80045C34: the "flags/value" record pointed to by a2. Only two fields are
 * accessed by this function: a signed 16-bit value at 0x6 and a 16-bit flags
 * word at 0x14 (bit 0x80 tested). */
typedef struct S_80045C34 {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad1[0x14 - 0x8];
    /* 0x14 */ u16 unk14;
} S_80045C34;

extern void func_80045CC4(void *a0, s32 a1, S_80045C34 *a2, s16 a3);
extern s32 func_80045310(u32 a0);

/* D_80083160[0] points at a large shared-state struct; only the pointer field
 * at offset 0x8D0 is read here. */
extern void *D_80083160[3];

/* Processes unflagged list entries until the list ends or a stop is requested; returns zero. */
s32 func_80045C34(u8 *first_data, s32 link_value, S_80045C34 *value_record)
{
    u8 *link_data = first_data;
    void *next_link;

    do {
        if (!(value_record->unk14 & 0x80)) {
            func_80045CC4(link_data, link_value, value_record, value_record->unk6);
            if (func_80045310(*(u32 *)((u8 *)D_80083160[0] + 0x8D0))) {
                return 0;
            }
        }
        next_link = *(void **)(link_data - 8);
        if (next_link == 0) {
            return 0;
        }
        link_data = (u8 *)next_link + 0x20;
        link_value = *(s32 *)((u8 *)next_link + 8);
        value_record = *(S_80045C34 **)((u8 *)next_link + 0xC);
    } while (1);
}
