#include "common.h"

typedef struct Source {
    s16 f00;
    unsigned char pad02[2];
    s16 f04;
    s16 f06;
    s16 f08;
    unsigned char pad0a[2];
    s16 f0c;
    s16 f0e;
    s16 f10;
    unsigned char pad12[2];
    u16 f14;
    u16 f16;
    u16 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    u16 f30;
    u16 f32;
    s32 f34;
    s32 f38;
    s32 f3c;
    s32 f40;
    s32 f44;
    s32 f48;
    u16 f4c;
    u16 f4e;
} Source;

typedef struct Destination {
    unsigned char pad00[8];
    u16 f08;
    u16 f0a;
    u16 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    unsigned char pad1c[4];
    u16 f20;
    u16 f22;
    u16 f24;
    u16 f26;
    s32 f28;
    s32 f2c;
    s32 f30;
    s32 f34;
    s32 f38;
    u16 f3c;
    u16 f3e;
    u16 f40;
    u16 f42;
    unsigned char pad44[0x1c];
    s32 f60;
} Destination;

typedef struct Container {
    Destination *ptr;
    unsigned char pad04[8];
    s32 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    u16 f20;
    u16 f22;
    u16 f24;
    u16 f26;
    s32 f28;
    s32 f2c;
    s32 f30;
    s32 f34;
    s32 f38;
    u16 f3c;
    u16 f3e;
    u16 f40;
    u16 f42;
} Container;

/* Copy source fields into the container and its destination, clearing four container fields. */
void func_800375C0(Container *container, Source *source) {
    container->ptr->f60 = source->f00;
    container->ptr->f10 = source->f04;
    container->ptr->f14 = source->f06;
    container->ptr->f18 = source->f08;
    container->ptr->f30 = source->f0c;
    container->ptr->f34 = source->f0e;
    container->ptr->f38 = source->f10;
    container->ptr->f08 = source->f14;
    container->ptr->f0a = source->f16;
    container->ptr->f0c = source->f18;
    container->f0c = source->f1c;
    container->f10 = source->f20;
    container->f14 = source->f24;
    container->f18 = source->f28;
    container->f1c = source->f2c;
    container->f20 = source->f30;
    container->f22 = source->f32;
    container->f26 = 0;
    container->f24 = 0;
    container->f28 = source->f38;
    container->f2c = source->f3c;
    container->f30 = source->f40;
    container->f34 = source->f44;
    container->f38 = source->f48;
    container->f3c = source->f4c;
    container->f3e = source->f4e;
    container->f42 = 0;
    container->f40 = 0;
}
