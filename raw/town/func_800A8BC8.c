typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

void func_800A6328(u32 *arg0, s32 arg1)
{
    s32 offset;
    s32 end;

    while (*arg0 != 0) {
        offset = 0;
        do {
            if (*(u32 *)(offset + *arg0) & 0x20) {
                *(s32 *)(offset + *arg0 + 8) = arg1;
            }
            end = *(u8 *)(offset + *arg0) & 0x80;
            offset += 12;
        } while (!end);
        arg0++;
    }
}
