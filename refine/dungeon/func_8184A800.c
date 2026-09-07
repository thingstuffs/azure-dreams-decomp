#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 rand(void);
extern s32 D_800814A0[3];

extern void func_80025090(void);
extern void func_80025080(void);
extern void func_80025058(void);
extern void func_80025068(void);
extern void func_80025078(void);
extern void func_8002510C(void);
extern void func_8002515C(void);
extern void func_80025674(void);
extern void func_80025730(void);
extern void func_80025770(void);
extern void func_80025824(void);
extern void func_80025878(void);
extern void func_800258B0(void);

typedef void (*Callback)(void);

#ifdef __mips__
static Callback const func_8184A800_table[]
    __attribute__((section(".text.func_8184A800"))) = {
    func_80025090,
    0,
    func_80025080,
    func_80025080,
    func_80025080,
    func_80025058,
    func_80025068,
    func_80025078,
    func_80025080,
    0,
    func_8002510C,
    func_8002515C,
    func_80025674,
    func_80025730,
    func_80025770,
    func_80025824,
    func_80025878,
    func_800258B0,
};

#define FUNC_8184A800_BODY func_8184A800
#else
#define FUNC_8184A800_BODY func_8184A800
#endif

/* Apply a random number of updates to the target and propagate its status flags. */
void FUNC_8184A800_BODY(void *owner, void *unused, void *target)
{
    s32 random_value;
    register s32 quotient ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s16 update_count;
    s16 update_index;
    s16 next_index;
    void *owner_data;

    owner_data = *(void **)((u8 *)owner + 0xC);
    *(u16 *)((u8 *)owner_data + 0x16) += 1;
    *(s16 *)((u8 *)target + 0x1A) = 0;

    quotient = rand();
    ASM_KEEP(quotient);   /* MATCH pin: retail register colouring depends on it */
    random_value = quotient;
    quotient >>= 2;
    if (random_value < 0) {
        quotient = (random_value + 3) >> 2;
    }
    update_count = (random_value - (quotient * 4)) + 1;

    update_index = 0;
    if (update_count > 0) {
        do {
            func_800478B8(target);
            next_index = update_index + 1;
            update_index = next_index;
        } while (next_index < update_count);
    }

    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        *(u16 *)((u8 *)owner - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

#ifdef __mips__
#endif
