typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

// Sets the value at offset 8 in records flagged 0x20 in each record list.
void func_800A6328(u32 *recordLists, s32 value)
{
    s32 recordOffset;
    s32 isLastRecord;

    while (*recordLists != 0) {
        recordOffset = 0;
        do {
            if (*(u32 *)(recordOffset + *recordLists) & 0x20) {
                *(s32 *)(recordOffset + *recordLists + 8) = value;
            }
            isLastRecord = *(u8 *)(recordOffset + *recordLists) & 0x80;
            recordOffset += 12;
        } while (!isLastRecord);
        recordLists++;
    }
}
