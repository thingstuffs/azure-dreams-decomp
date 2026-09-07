typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u16 active;
    u16 pad;
    u32 data;
} TownRecord;

void func_800A63C8(TownRecord *arg0, s32 arg1)
{
    s32 offset;
    s32 end;

    while (arg0->active != 0) {
        offset = 0;
        do {
            if (*(u32 *)(offset + arg0->data) & 0x20) {
                *(s32 *)(offset + arg0->data + 8) = arg1;
            }
            end = *(u8 *)(offset + arg0->data) & 0x80;
            offset += 12;
        } while (!end);
        arg0++;
    }
}
