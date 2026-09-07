#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern void func_80098B38(void *, void *);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A6D30(void);
extern s16 func_800A70E4(s16, s16, s16);
extern s32 func_800C8310(void *, void *);
extern void func_80158ADC() __attribute__((noreturn));
extern s32 D_80010248[];
extern s32 D_8001029C[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_800E3548[];
extern s32 D_800E3D7C[];
extern s32 D_8015CFE4[];

#ifdef __mips__
static const u32 identity_bank[] __asm__("func_80EA3000")
    __attribute__((section(".text.func_80EA3000"), aligned(4))) = {
    0x80158AF4, 0x80158CC8, 0x80159504, 0x80159504,
    0x80159504, 0x80159530, 0x801594B0, 0x801594B0,
    0x801594B0, 0x80159430, 0x80159484, 0x80159468,
    0x80159530, 0x801594F4, 0x8015AD30, 0x8015AFF4,
    0x8015B074, 0x8015B0B8, 0x8015B11C, 0x8015B1E8,
    0x8015B294, 0x8015B3F0, 0x8015B3F0, 0x8015B3F0,
    0x8015B3F0, 0x8015B3F0, 0x8015B3F0, 0x8015B3F0,
    0x8015B3F0, 0x8015B3F0, 0x8015B304, 0x00000000,
    0x8015ADEC, 0x8015ADE4, 0x8015ADDC, 0x8015ADF4,
    0x8015AD98, 0x8015AD90, 0x8015AD88, 0x93824081,
    0x8F829482, 0x85828C82, 0x00000000, 0x94828982,
    0x8D828582, 0x00004081, 0x00004981, 0x83824081,
    0x95828F82, 0x84828C82, 0x66818E82, 0x40819482,
    0x94829382, 0x81828582, 0x40818C82, 0x88829482,
    0x40818582, 0x94828982, 0x8D828582, 0x00004481,
    0x8015C4B8, 0x8015C558, 0x8015C5E8, 0x8015C674,
    0x8015C6E4, 0x8015C7C4,
};
__asm__(".type func_80EA3000,@function\n.size func_80EA3000,756\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80EA3000")))
#else
#define BODY_NAME func_80EA3000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE s32 BODY_NAME(void *, void *) BODY_ATTR;
BODY_STORAGE s32 BODY_NAME(void *arg0, void *arg1) {
    u8 *p0 = (u8 *)arg0;
    u8 *p1 = (u8 *)arg1;
    s32 selector;
    s16 result;
    void *found;
    s32 offset;
    u8 *entry;
    u8 *value;

    selector = (*(u16 *)(p1 + 0x2A) >> 8) & 0xE;
    result = func_800A70E4(
        (s16)(*(u8 *)(p0 + 0x24) + *(u16 *)(D_8006CCD8 + selector)),
        (s16)(*(u8 *)(p0 + 0x25) + *(u16 *)(D_8006CCE8 + selector)),
        *(s16 *)(p1 + 0x88));
    if (result >= 0) {
#ifdef __mips__
        s32 *destination;
        s32 *dead_destination;
#else
        s32 *destination;
        s32 *dead_destination;
#endif
        s32 selected;

        destination = (s32 *)0x80160000;
        ASM_KEEP(destination);   /* MATCH pin: keeps a statement from moving across a call/branch */
        selected = D_800E3548[result];
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        dead_destination = destination - 3079;
        ASM_KEEP(dead_destination);   /* MATCH pin: load-bearing for the whole function shape */
        destination[-3079] = selected;
        D_800E3548[result] = 0;
        func_80158ADC(selected, destination);
        __builtin_unreachable();
    }

    found = func_800A04F0(arg1, *(u8 *)(p0 + 0x24), *(u8 *)(p0 + 0x25),
                          *(s16 *)(p1 + 0x2A));
    if (found == NULL) {
        goto return_zero;
    }
    if (found == (void *)D_800E3D7C[0]) {
        if (func_800C8310(found, found) != 0) {
            return 0;
        }
        {
#ifdef __mips__
        register s32 i ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s16 count;
        register s32 *scan ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
#else
        s32 i;
        s16 count;
        s32 *scan;
#endif
        i = 0;
        count = i;
        scan = (s32 *)0x80010000;
        do {
            if (scan[167] != 0) {
                count++;
            }
            i++;
            scan++;
        } while (i < 20);
        if (count == 0) {
            return 0;
        }
        offset = (s32)((((func_800A6D30() & 0xFFFF) % count) << 16) >> 14);
        entry = (u8 *)(offset + 0x80010000);
        if (*(u8 *)(entry + 0x249) == 0) {
            goto return_zero;
        }
        if (*(u8 *)(entry + 0x249) == 0x13) {
            return 0;
        }
        if (*(u8 *)(entry + 0x24B) & 0x20) {
            goto entry_zero;
        }
        {
            s32 loaded;
            s32 *destination;
#ifdef __mips__
            register s32 tail_value ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
#else
            s32 tail_value;
#endif
            value = (u8 *)(offset + 0x80010248);
            loaded = *(s32 *)value;
            ASM_MEM_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
            destination = (s32 *)0x80160000;
            ASM_KEEP(destination);   /* MATCH pin: keeps a statement from moving across a call/branch */
            destination[-3079] = loaded;
            destination -= 3079;
            func_80098B38(value, entry);
            tail_value = (s32)destination;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_80158ADC();
            __builtin_unreachable();
        }
        }
    }
    if (*(u8 *)((u8 *)found + 0x49) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)found + 0x4B) & 0x20) {
        return 0;
    }
    {
#ifdef __mips__
        s32 *destination;
        register s32 *dead_destination ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
#else
        s32 *destination;
        s32 *dead_destination;
#endif
        s32 selected;

        destination = (s32 *)0x80160000;
        ASM_KEEP(destination);   /* MATCH pin: keeps a statement from moving across a call/branch */
        selected = *(s32 *)((u8 *)found + 0x48);
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        dead_destination = destination - 3079;
        ASM_KEEP(dead_destination);   /* MATCH pin: load-bearing for the whole function shape */
        destination[-3079] = selected;
        *(s32 *)((u8 *)found + 0x48) = 0;
        func_80158ADC(selected, found);
        __builtin_unreachable();
    }
entry_zero:
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
return_zero:
    return 0;
}
