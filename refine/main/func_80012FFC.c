#include "common.h"

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

extern void func_8006733C(MainDescriptor *descriptor, void *entry);
extern void func_80067014(s32 arg0);

/* Copy the selected record into the destination and process three descriptor entries. */
void func_80025FFC(void *dest, s32 record_index)
{
    MainDescriptor descriptor;
    u8 *entry;
    s32 entry_index;

    descriptor = D_800200B8;
    *(MainRecord *)((u8 *)dest + 0x60) = D_80027E78[record_index];
    entry_index = 0;
    entry = (u8 *)(unsigned long)0x80010080;
    descriptor.second += record_index * 0x10;
    do {
        func_8006733C(&descriptor, entry);
        descriptor.first += 4;
        entry += 0x80;
    } while (++entry_index < 3);
    func_80067014(0);
}
