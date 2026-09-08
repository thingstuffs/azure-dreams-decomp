#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern void func_80098B38(void *, void *);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A6D30(void);
extern s16 func_800A70E4(s16, s16, s16);
extern s32 func_800C8310(void *, void *);
extern void func_8016AADC() __attribute__((noreturn));

extern s32 D_80010248[];
extern s32 D_8001029C[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_800E3548[];
extern s32 D_800E3D7C[];
extern s32 D_8016EFE4[];

#ifdef __mips__
static const u32 identity_bank[] __asm__("func_80E91000")
    __attribute__((section(".text.func_80E91000"), aligned(4))) = {
    0x8016AAF4, 0x8016ACC8, 0x8016B504, 0x8016B504,
    0x8016B504, 0x8016B530, 0x8016B4B0, 0x8016B4B0,
    0x8016B4B0, 0x8016B430, 0x8016B484, 0x8016B468,
    0x8016B530, 0x8016B4F4, 0x8016CD30, 0x8016CFF4,
    0x8016D074, 0x8016D0B8, 0x8016D11C, 0x8016D1E8,
    0x8016D294, 0x8016D3F0, 0x8016D3F0, 0x8016D3F0,
    0x8016D3F0, 0x8016D3F0, 0x8016D3F0, 0x8016D3F0,
    0x8016D3F0, 0x8016D3F0, 0x8016D304, 0x00000000,
    0x8016CDEC, 0x8016CDE4, 0x8016CDDC, 0x8016CDF4,
    0x8016CD98, 0x8016CD90, 0x8016CD88, 0x93824081,
    0x8F829482, 0x85828C82, 0x00000000, 0x94828982,
    0x8D828582, 0x00004081, 0x00004981, 0x83824081,
    0x95828F82, 0x84828C82, 0x66818E82, 0x40819482,
    0x94829382, 0x81828582, 0x40818C82, 0x88829482,
    0x40818582, 0x94828982, 0x8D828582, 0x00004481,
    0x8016E4B8, 0x8016E558, 0x8016E5E8, 0x8016E674,
    0x8016E6E4, 0x8016E7C4,
};
__asm__(".type func_80E91000,@function\n.size func_80E91000,756\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80E91000")))
#else
#define BODY_NAME func_80E91000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE s32 BODY_NAME(void *, void *) BODY_ATTR;
BODY_STORAGE s32 BODY_NAME(void *arg0, void *arg1)
{
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

        destination = (s32 *)0x80170000;
        ASM_KEEP(destination);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        selected = D_800E3548[result];
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        dead_destination = destination - 1031;
        ASM_KEEP(dead_destination);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        destination[-1031] = selected;
        D_800E3548[result] = 0;
        func_8016AADC(selected, destination);
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
            register s32 i ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            s16 count;
            register s32 *scan ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
            offset =
                (s32)((((func_800A6D30() & 0xFFFF) % count) << 16) >> 14);
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
                register s32 tail_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
#else
                s32 tail_value;
#endif
                value = (u8 *)(offset + 0x80010248);
                loaded = *(s32 *)value;
                ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                destination = (s32 *)0x80170000;
                ASM_KEEP(destination);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                destination[-1031] = loaded;
                destination -= 1031;
                func_80098B38(value, entry);
                tail_value = (s32)destination;
                ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_8016AADC();
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
        register s32 *dead_destination ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
#else
        s32 *destination;
        s32 *dead_destination;
#endif
        s32 selected;

        destination = (s32 *)0x80170000;
        ASM_KEEP(destination);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        selected = *(s32 *)((u8 *)found + 0x48);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        dead_destination = destination - 1031;
        ASM_KEEP(dead_destination);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        destination[-1031] = selected;
        *(s32 *)((u8 *)found + 0x48) = 0;
        func_8016AADC(selected, found);
        __builtin_unreachable();
    }
entry_zero:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
return_zero:
    return 0;
}
