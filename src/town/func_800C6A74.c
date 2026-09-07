typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u8 pad0;
    u8 field1;
    u8 pad2[6];
} S_80082660;

extern s32 D_800C3988;
extern S_80082660 D_80082660[];

void func_800C41D4(void *arg0) {
    s32 idx;
    *(void **)((u8 *)arg0 + 0x54) = &D_800C3988;
    idx = *(s32 *)((u8 *)arg0 + 0x60);
    D_80082660[idx].field1 = 0;
}
