#include "common.h"
#include "frontend/libcard/message.h"
#include "sdk/libgpu.h"

typedef struct MainDescriptor {
    u16 first;
    u16 second;
    u32 rest;
} __attribute__((packed)) MainDescriptor;

typedef struct MainRecord {
    u32 words[8];
} __attribute__((packed)) MainRecord;

extern MainDescriptor D_800200B8;
extern MainRecord D_80027E78[];

/* Copy the selected record into the destination and process three descriptor entries. */
void initialize_text_editor_context(void *dest, s32 record_index)
{
    MainDescriptor descriptor;
    u32 *entry;
    s32 entry_index;

    descriptor = D_800200B8;
    *(MainRecord *)((u8 *)dest + 0x60) = D_80027E78[record_index];
    entry_index = 0;
    entry = (u32 *)(unsigned long)0x80010080;
    descriptor.second += record_index * 0x10;
    do {
        StoreImage(&descriptor, entry);
        descriptor.first += 4;
        entry += 0x20;
    } while (++entry_index < 3);
    DrawSync(0);
}
