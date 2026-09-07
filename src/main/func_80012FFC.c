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

void func_80025FFC(void *arg0, s32 arg1)
{
    MainDescriptor descriptor;
    u8 *entry;
    s32 i;

    descriptor = D_800200B8;
    *(MainRecord *)((u8 *)arg0 + 0x60) = D_80027E78[arg1];
    i = 0;
    entry = (u8 *)(unsigned long)0x80010080;
    descriptor.second += arg1 * 0x10;
    do {
        func_8006733C(&descriptor, entry);
        descriptor.first += 4;
        entry += 0x80;
    } while (++i < 3);
    func_80067014(0);
}
