#include "common.h"

typedef struct {
    s32 value;
} __attribute__((packed)) PackedWord;

extern PackedWord D_80018A98[3];

void *func_806975C4(void *arg0) {
    *(PackedWord *)arg0 = D_80018A98[0];
    ((u8 *)arg0)[5] = 15;
    ((u8 *)arg0)[4] = 2;
    ((u8 *)arg0)[7] = 0;
    ((u8 *)arg0)[6] = 0;
    ((u8 *)arg0)[8] = 1;
    ((u8 *)arg0)[9] = 1;
    ((u8 *)arg0)[11] = 0;
    ((u8 *)arg0)[10] = 0;
    ((u8 *)arg0)[13] = 0;
    ((u8 *)arg0)[12] = 0;
    return arg0;
}
