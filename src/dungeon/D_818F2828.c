#include "common.h"

extern void func_80025090(void);
extern void func_80025150(void);
extern void func_80025418(void);
extern void func_80025798(void);
extern void func_800257CC(void);
extern void func_80025874(void);
extern void func_800258B0(void);
extern void func_80025948(void);
extern void func_800258E4(void);

/* Exact physical callback_vector span; owner unresolved. */
const u32 D_80024028[9] __attribute__((aligned(4))) = {
    (u32)func_80025090,
    (u32)func_80025150,
    (u32)func_80025418,
    (u32)func_80025798,
    (u32)func_800257CC,
    (u32)func_80025874,
    (u32)func_800258B0,
    (u32)func_80025948,
    (u32)func_800258E4
};
