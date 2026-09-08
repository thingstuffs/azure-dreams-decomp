typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern void func_800B2D00(s32 a0, void *a1, s32 a2);

/* Forwards a value and the referenced record's data to func_800B2D00. */
void func_800B2DA0(s32 value, void **record_ptr) {
    void *record;

    record = *record_ptr;
    func_800B2D00(value, (u8 *)record + 0x1C, *(s32 *)((u8 *)record + 0x3C));
}
