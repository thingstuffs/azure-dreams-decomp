#include "common.h"

extern s32 D_8002D690[4];
extern s32 D_8002D6A0[3];
extern s32 D_8002D6A4[3];
extern s32 D_8002D6A8[3];

/* Initialize entry pointers, per-entry defaults, and shared data. */
void func_8001DB84(void *object, s32 entry_count) {
    s32 entry_index;
    s32 entry_offset;
    s32 data_offset;
    void *entry_data;
    s32 *defaults;
    void *shared_data;
    s32 pad[2];

    entry_index = 0;
    if (entry_count > 0) {
        defaults = D_8002D690;
        shared_data = (u8 *) object + 0x204;
        data_offset = 0x294;
        do {
            entry_offset = 0x224 + entry_index * 0x10;
            *((s32 *) *(s32 **) ((u8 *) object + 0x220) + entry_index) = (s32) ((u8 *) object + entry_offset);
            *(s32 *) ((u8 *) object + entry_index * 0x10 + 0x294) = defaults[0];
            entry_data = (u8 *) object + data_offset;
            *(s32 *) ((u8 *) object + entry_index * 0x10 + 0x298) = defaults[1];
            *(s32 *) ((u8 *) object + entry_index * 0x10 + 0x29C) = defaults[2];
            data_offset += 0x10;
            *(s32 *) ((u8 *) object + entry_index * 0x10 + 0x2A0) = defaults[3];
            *(void **) ((u8 *) object + entry_index * 0x10 + 0x228) = entry_data;
            *(s32 *) ((u8 *) object + entry_index * 0x10 + 0x22C) = (s32) shared_data;
            entry_index += 1;
        } while (entry_index < entry_count);
    }
    *(s32 *) ((u8 *) object + 0x204) = D_8002D6A0[0];
    *(s32 *) ((u8 *) object + 0x208) = D_8002D6A4[0];
    *(s32 *) ((u8 *) object + 0x20C) = D_8002D6A8[0];
}
