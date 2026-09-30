typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u16 active;
    u16 pad;
    u32 data;
} TownRecord;

// Sets the value at offset 8 in entries flagged 0x20 across active town records.
void func_800A63C8(TownRecord *record, s32 entryValue)
{
    s32 entryOffset;
    s32 lastEntryFlag;

    s32 i;

    for (i = 0; record[i].active != 0; i++) {
        entryOffset = 0;
        do {
            if (*(u32 *)(entryOffset + record[i].data) & 0x20) {
                *(s32 *)(entryOffset + record[i].data + 8) = entryValue;
            }
            lastEntryFlag = *(u8 *)(entryOffset + record[i].data) & 0x80;
            entryOffset += 12;
        } while (!lastEntryFlag);
    }
}
