#include "common.h"

typedef struct {
    u8 bytes[24];
} __attribute__((packed)) Packed24;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

extern Packed24 D_800D16E4;
extern Packed12 D_800D16D8;

void func_800B40E0(void *arg0) {
    void *src;

    src = &D_800D16E4;
    *(Packed24 *)arg0 = *(Packed24 *)src;
    src = &D_800D16D8;
    *(Packed12 *)((u8 *)arg0 + 24) = *(Packed12 *)src;
}

/* MECHANISM: A frameless true-space leaf assigns packed 24-byte and 12-byte objects.
   The packed types force retail's grouped lwl/lwr then swl/swr copy idiom.
   Reorienting the structurally moved source to 2.7.2-cdk-G0 removes 2.91.66's hoisted second page and register rotation. */
