#include "common.h"

#include "common.h"

typedef struct {
    void *f0;
    void *f1;
    void *f2;
    void *f3;
} S_80084538;
extern S_80084538 D_80084538;

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
} S_800847C0;
extern S_800847C0 D_800847C0;

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
} S_80084768;
extern S_80084768 D_80084768;

extern u8 D_801B9000[];

/* Initializes staging-buffer destinations and their parallel offset and size tables. */
void func_80055864(void) {
    s32 first_size = 0x3A980, second_offset = 0x3B990, second_size = 0x1BD50;
    s32 third_offset = 0x576E0, third_size = 0x11940, fourth_offset = 0x69020;

    D_80084538.f0 = D_801B9000;
    D_80084538.f1 = D_801B9000 + 0x3000;
    D_80084538.f2 = D_801B9000 + 0x4020;
    D_80084538.f3 = D_801B9000 + 0x4E40;

    D_800847C0.f0 = 0x1010;
    D_800847C0.f1 = second_offset;
    D_800847C0.f2 = third_offset;
    D_800847C0.f3 = fourth_offset;

    D_80084768.f0 = first_size;
    D_80084768.f1 = second_size;
    D_80084768.f2 = third_size;
    D_80084768.f3 = 0xFA00;
}
