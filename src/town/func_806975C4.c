#include "common.h"

typedef struct {
    s32 value;
} __attribute__((packed)) PackedWord;

extern PackedWord D_80018A98[3];

/* Initialize a record with the default header and field values. */
void *func_806975C4(void *record) {
    *(PackedWord *)record = D_80018A98[0];
    ((u8 *)record)[5] = 15;
    ((u8 *)record)[4] = 2;
    ((u8 *)record)[7] = 0;
    ((u8 *)record)[6] = 0;
    ((u8 *)record)[8] = 1;
    ((u8 *)record)[9] = 1;
    ((u8 *)record)[11] = 0;
    ((u8 *)record)[10] = 0;
    ((u8 *)record)[13] = 0;
    ((u8 *)record)[12] = 0;
    return record;
}
