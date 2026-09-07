#include "common.h"


extern void *D_80024008[];
extern u8 D_80026470[];
extern u8 D_80026474[];
extern u8 D_80026476[];
extern u8 D_80026478[];
extern u8 D_80026484[];
extern u8 D_80026490[];
extern u8 D_80026472[];
extern u8 D_800265C0[];
extern u8 D_800265C4[];
extern u8 D_800269C8[];
extern u8 D_80045340[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern u8 D_8008346C[];
extern u8 D_800814A0[];

#ifdef __mips__
extern u8 D_80020000[];
__asm__(".set D_80020000, 0x80020000");
extern u8 D_80080000[];
__asm__(".set D_80080000, 0x80080000");
#endif

extern void func_800B835C(void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(u32);
extern void func_8002495C(void *, void *);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_80065F90(s16, s16);
extern s32 func_800262AC(s16, s16, s16);
extern void func_800A56E0(s32);
extern void func_80026404(void *, u8, void *);

#ifdef __mips__
static const u32 func_80024000_prefix[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x80024050, 0x00000000, 0x800240B4,
    0x80024160, 0x800243B4, 0x800245D4, 0x80024628,
    0x80024770, 0x80024770, 0x80024770, 0x80024770,
    0x80024770, 0x80024770, 0x80024770, 0x80024770,
    0x80024770, 0x80024770, 0x80024770,
    0x80024698, 0x80024738,
};
__asm__(".globl func_80024000\n"
        ".size func_80024000, 1964");
#define FUNC_8188C800_BODY func_80024000_impl
#else
#define FUNC_8188C800_BODY func_80024000
#endif


typedef struct S_FUNC_8188C800_BODY_0_pre {
    u16 unk_00;
} S_FUNC_8188C800_BODY_0_pre;   /* the 0x2 bytes before self in FUNC_8188C800_BODY, addressed as self[-1] */

typedef struct S_FUNC_8188C800_BODY_0 {
    u8 * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
    u16 unk_0E;
    union { u16 u; s16 s; } unk_10;   /* accessed as both */
    u8 unk_12;
    u8 pad_13[0x1];
    u16 unk_14;
    union { u16 u; s16 s; } unk_16;   /* accessed as both */
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u8 pad_1A[0x2];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; struct { u8 pad[0x2]; s8 v; } at02p; struct { u8 pad[0x3]; u8 v; } at03; struct { u8 pad[0x3]; s8 v; } at03u; } unk_1C;   /* overlapping accesses */
    union { struct { u8 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_20;   /* overlapping accesses */
    u8 pad_22[0xA];
    union { s32 i; void * p; } unk_2C;   /* accessed as both */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_30;   /* overlapping accesses */
} S_FUNC_8188C800_BODY_0;   /* self in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    void * unk_0C;
} S_FUNC_8188C800_BODY_1;   /* base in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_2 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_FUNC_8188C800_BODY_2;   /* part in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_3 {
    u16 unk_00;
} S_FUNC_8188C800_BODY_3;   /* D_80026470 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_4 {
    u16 unk_00;
} S_FUNC_8188C800_BODY_4;   /* D_80026474 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_5 {
    u16 unk_00;
} S_FUNC_8188C800_BODY_5;   /* D_80026476 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_6 {
    u32 unk_00;
} S_FUNC_8188C800_BODY_6;   /* D_800265C0 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_7 {
    u32 unk_00;
} S_FUNC_8188C800_BODY_7;   /* D_800265C4 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_8_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_FUNC_8188C800_BODY_8_pre;   /* the 0x14 bytes before owner in FUNC_8188C800_BODY, addressed as owner[-1] */

typedef struct S_FUNC_8188C800_BODY_8 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { u8 * p; void * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0xC];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; s8 v; } at02; struct { u8 pad[0x3]; s8 v; } at03; } unk_70;   /* overlapping accesses */
    u8 pad_74[0x14];
    u16 unk_88;
} S_FUNC_8188C800_BODY_8;   /* owner in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_9 {
    u8 pad_00[0x6484];
    u16 unk_6484;
} S_FUNC_8188C800_BODY_9;   /* page in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_10 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_FUNC_8188C800_BODY_10;   /* addr in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_11 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
} S_FUNC_8188C800_BODY_11;   /* motion in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_12 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_FUNC_8188C800_BODY_12;   /* record in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_FUNC_8188C800_BODY_13;   /* scratch in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_14_pre {
    u8 * unk_00;
    u8 pad_04[0x14];
} S_FUNC_8188C800_BODY_14_pre;   /* the 0x18 bytes before target in FUNC_8188C800_BODY, addressed as target[-1] */

typedef struct S_FUNC_8188C800_BODY_14 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_FUNC_8188C800_BODY_14;   /* target in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_15 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_FUNC_8188C800_BODY_15;   /* target_part in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_16 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_FUNC_8188C800_BODY_16;   /* target_record in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_17 {
    u16 unk_00;
} S_FUNC_8188C800_BODY_17;   /* D_800269C8 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_18 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_FUNC_8188C800_BODY_18;   /* D_80026472 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_19 {
    u8 pad_00[0x346C];
    u32 unk_346C;
} S_FUNC_8188C800_BODY_19;   /* tail_page0 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_20 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_FUNC_8188C800_BODY_20;   /* tail_page1 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_21 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_FUNC_8188C800_BODY_21;   /* ((S_FUNC_8188C800_BODY_1 *)base)->unk_0C in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_22 {
    u16 unk_00;
} S_FUNC_8188C800_BODY_22;   /* ((S_FUNC_8188C800_BODY_0 *)self)->unk_04 in FUNC_8188C800_BODY */

typedef struct S_FUNC_8188C800_BODY_23 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_FUNC_8188C800_BODY_23;   /* ((S_FUNC_8188C800_BODY_0 *)self)->unk_2C.p in FUNC_8188C800_BODY */

void FUNC_8188C800_BODY(void *arg0, void *arg1, void *arg2)
{
#ifdef __mips__
    u8 *self = (u8 *)arg0;
    u8 *motion = (u8 *)arg1;
    u8 *part;
    register u8 *owner ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *base;
    u8 *record;
    u8 *tail_page0;
    u8 *tail_page1;
#else
    u8 *self = (u8 *)arg0;
    u8 *motion = (u8 *)arg1;
    u8 *part = (u8 *)arg2;
    u8 *owner;
    u8 *base;
    u8 *record;
    u8 *tail_page0;
    u8 *tail_page1;
#endif
    register s32 state;
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_3, &&case_3,
        &&case_3, &&case_5, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&case_5_tail, &&done,
    };

    owner = ((S_FUNC_8188C800_BODY_0 *)self)->unk_00;
    state = ((S_FUNC_8188C800_BODY_0 *)self)->unk_0A.s;
    base = owner - 32;
    record = ((S_FUNC_8188C800_BODY_1 *)base)->unk_08;
    part = (u8 *)arg2;
    if (state < 0 || state >= 18) {
        goto done;
    }
    {
        void **table = D_80024008;
        s32 index = state << 2;
        (void)keepalive;
        goto *(*(void **)(index + (u32)table));
    }

case_0:
    {
    s32 scratch[4];
#ifdef __mips__
        u32 color = 0x00808080;
        u32 init0 = 0x01000340;
        u32 init1 = 0x00200020;
        u8 *page = (u8 *)0x80020000;
        register u8 *addr ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
        ASM_KEEP(page);   /* MATCH pin: retail basic-block layout depends on it */
#else
        u32 color = 0x00808080;
        u32 init0 = 0x01000340;
        u32 init1 = 0x00200020;
        u8 *page = D_80026484;
        u8 *addr;
#endif
    addr = page + 0x6484;
    ASM_KEEP(addr);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at00.v = color;
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_1E = 0x555;
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_1C = 0x555;
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_08 = D_80026490;
    ((S_FUNC_8188C800_BODY_3 *)D_80026470)->unk_00 = 0;
    ((S_FUNC_8188C800_BODY_4 *)D_80026474)->unk_00 = 0;
    ((S_FUNC_8188C800_BODY_5 *)D_80026476)->unk_00 = 0;
    ((S_FUNC_8188C800_BODY_6 *)D_800265C0)->unk_00 = 0;
    ((S_FUNC_8188C800_BODY_7 *)D_800265C4)->unk_00 = 0;
    {
        u16 packed = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_2A;
        ((S_FUNC_8188C800_BODY_9 *)page)->unk_6484 = 0x1010;
        ((S_FUNC_8188C800_BODY_10 *)addr)->unk_08 = 0;
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_16.u = (packed >> 9) & 7;
    }
    scratch[2] = init0;
    scratch[3] = init1;
    func_800B835C(addr - 12, scratch + 2, 1, 0);
    ((S_FUNC_8188C800_BODY_0 *)self)->unk_0A.u++;
    if (func_8003DF74(((S_FUNC_8188C800_BODY_21 *)(((S_FUNC_8188C800_BODY_1 *)base)->unk_0C))->unk_08,
                      ((S_FUNC_8188C800_BODY_1 *)base)->unk_0C, scratch, 0) == 0) {
        if (!(((S_FUNC_8188C800_BODY_21 *)(((S_FUNC_8188C800_BODY_1 *)base)->unk_0C))->unk_14 & 0x8000)) {
            goto done;
        }
    }
    ((S_FUNC_8188C800_BODY_11 *)motion)->unk_00.at02.v = ((S_FUNC_8188C800_BODY_12 *)record)->unk_02;
    ((S_FUNC_8188C800_BODY_11 *)motion)->unk_04.at02.v = ((S_FUNC_8188C800_BODY_12 *)record)->unk_06;
#ifdef __mips__
    {
        u16 height;
#else
    {
        u16 height;
#endif
        if (((S_FUNC_8188C800_BODY_21 *)(((S_FUNC_8188C800_BODY_1 *)base)->unk_0C))->unk_14 & 0x8000) {
            height = ((S_FUNC_8188C800_BODY_12 *)record)->unk_0A - 64;
        } else {
            height = ((S_FUNC_8188C800_BODY_12 *)record)->unk_0A;
#ifdef __mips__
            {
                register u16 addend ASM_REG("$3") = ((S_FUNC_8188C800_BODY_13 *)scratch)->unk_04;   /* MATCH pin: load-bearing for the whole function shape */
#else
            {
                u16 addend = ((S_FUNC_8188C800_BODY_13 *)scratch)->unk_04;
#endif
                height = height + addend;
            }
        }
        ((S_FUNC_8188C800_BODY_11 *)motion)->unk_08.at02.v = height;
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_30.at02.v = height;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    }
    if (!(((S_FUNC_8188C800_BODY_22 *)(((S_FUNC_8188C800_BODY_0 *)self)->unk_04))->unk_00 & 0x80)) {
        goto done;
    }
    if (!(((S_FUNC_8188C800_BODY_0 *)self)->unk_12 & 4)) {
        func_8004491C(self - 32, D_80045340);
        ((S_FUNC_8188C800_BODY_2 *)part)->unk_10 = 32;
        ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at02.v = 128;
        ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at01.v = 128;
        ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at00u.v = 128;
        ((S_FUNC_8188C800_BODY_2 *)part)->unk_14 |= 0xC;
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_12 |= 4;
    }
    {
        u8 *target = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_60.p;
        if (target != 0) {
            u8 *target_part = ((S_FUNC_8188C800_BODY_14_pre *)target)[-1].unk_00;
            ((S_FUNC_8188C800_BODY_0 *)self)->unk_0C = ((S_FUNC_8188C800_BODY_15 *)target_part)->unk_02;
            ((S_FUNC_8188C800_BODY_0 *)self)->unk_0E = ((S_FUNC_8188C800_BODY_15 *)target_part)->unk_06;
            ((S_FUNC_8188C800_BODY_0 *)self)->unk_10.u = ((S_FUNC_8188C800_BODY_15 *)target_part)->unk_0A -
                                      D_800DDC40[0];
            {
                u8 *target_record = ((S_FUNC_8188C800_BODY_8_pre *)owner)[-1].unk_00;
                u8 x = ((S_FUNC_8188C800_BODY_16 *)target_record)->unk_24 +
                       D_8006CCD8[((S_FUNC_8188C800_BODY_0 *)self)->unk_16.s * 2];
                ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at02.v = x;
                ((S_FUNC_8188C800_BODY_0 *)self)->unk_20.at00.v = x;
                {
                    u8 y = ((S_FUNC_8188C800_BODY_16 *)target_record)->unk_25 +
                           D_8006CCE8[((S_FUNC_8188C800_BODY_0 *)self)->unk_16.s * 2];
                    ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at03.v = y;
                    ((S_FUNC_8188C800_BODY_0 *)self)->unk_20.at01.v = y;
                }
                {
#ifdef __mips__
                    s32 lhs = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_70.at02.v;
                    register s32 rhs ASM_REG("$3") =
                        ((S_FUNC_8188C800_BODY_16 *)target_record)->unk_24;
#else
                    s32 lhs = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_70.at02.v;
                    s32 rhs = ((S_FUNC_8188C800_BODY_16 *)target_record)->unk_24;
#endif
                    s32 delta;
                    if (lhs == rhs) {
                        lhs = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_70.at03.v;
                        rhs = ((S_FUNC_8188C800_BODY_16 *)target_record)->unk_25;
                    }
                    delta = lhs - rhs;
                    if (delta < 0) {
                        delta = -delta;
                    }
                    ((S_FUNC_8188C800_BODY_0 *)self)->unk_14 = delta + 1;
                }
            }
            goto case_0_finish_coords;
        }
    }
    ((S_FUNC_8188C800_BODY_0 *)self)->unk_14 = 8;
    ((S_FUNC_8188C800_BODY_0 *)self)->unk_0C = ((S_FUNC_8188C800_BODY_11 *)motion)->unk_00.at02.v;
    ((S_FUNC_8188C800_BODY_0 *)self)->unk_0E = ((S_FUNC_8188C800_BODY_11 *)motion)->unk_04.at02.v;
    ((S_FUNC_8188C800_BODY_0 *)self)->unk_10.u = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_88 - 80;

case_0_finish_coords:
    ((S_FUNC_8188C800_BODY_11 *)motion)->unk_0C.at02.v =
        (*(s16 *)((u8 *)D_8006CCD8 + ((S_FUNC_8188C800_BODY_0 *)self)->unk_16.s * 2)) * 8;
    ((S_FUNC_8188C800_BODY_11 *)motion)->unk_10.at02.v =
        (*(s16 *)((u8 *)D_8006CCE8 + ((S_FUNC_8188C800_BODY_0 *)self)->unk_16.s * 2)) * 8;
    goto case_increment;
    }

case_1:
    {
#ifdef __mips__
        register s32 velocity ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
#else
        s32 velocity;
#endif
        s32 adjusted;
        s32 magnitude;
        velocity = ((S_FUNC_8188C800_BODY_11 *)motion)->unk_0C.at00.v;
        adjusted = velocity;
        ASM_KEEP_NV(adjusted);   /* MATCH pin: load-bearing for the whole function shape */
        (*(volatile s32 *)((u8 *)motion + 0)) += velocity;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
        adjusted += adjusted >> 4;
        magnitude = adjusted;
        if (adjusted < 0) {
            ASM_KEEP_NV(magnitude);   /* MATCH pin: retail register colouring depends on it */
            magnitude = -magnitude;
        }
        ((S_FUNC_8188C800_BODY_11 *)motion)->unk_0C.at00.v = adjusted;
        if (magnitude > 0x200000) {
            s32 limit = -0x200000;
            if (adjusted > 0) {
                limit = 0x200000;
            }
            ((S_FUNC_8188C800_BODY_11 *)motion)->unk_0C.at00.v = limit;
        }
    }
    {
#ifdef __mips__
        register s32 velocity ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
#else
        s32 velocity;
#endif
        s32 adjusted;
        s32 magnitude;
        velocity = ((S_FUNC_8188C800_BODY_11 *)motion)->unk_10.at00.v;
        adjusted = velocity;
        ASM_KEEP_NV(adjusted);   /* MATCH pin: load-bearing for the whole function shape */
        (*(volatile s32 *)((u8 *)motion + 4)) += velocity;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
        adjusted += adjusted >> 4;
        magnitude = adjusted;
        if (adjusted < 0) {
            ASM_KEEP_NV(magnitude);   /* MATCH pin: retail register colouring depends on it */
            magnitude = -magnitude;
        }
        ((S_FUNC_8188C800_BODY_11 *)motion)->unk_10.at00.v = adjusted;
        if (magnitude > 0x200000) {
            s32 limit = -0x200000;
            if (adjusted > 0) {
                limit = 0x200000;
            }
            ((S_FUNC_8188C800_BODY_11 *)motion)->unk_10.at00.v = limit;
        }
    }
    {
        s32 value = ((S_FUNC_8188C800_BODY_0 *)self)->unk_30.at00.v;
        s32 delta = (((s32)((S_FUNC_8188C800_BODY_0 *)self)->unk_10.s << 16) - value) >> 4;
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_30.at00.v = value + delta;
    }
    {
        s32 value = ((S_FUNC_8188C800_BODY_11 *)motion)->unk_08.at00.v;
        s32 delta = (((s32)((S_FUNC_8188C800_BODY_0 *)self)->unk_10.s << 16) - value) >> 4;
        ((S_FUNC_8188C800_BODY_11 *)motion)->unk_08.at00.v = value + delta;
    }
    ((S_FUNC_8188C800_BODY_11 *)motion)->unk_08.at00.v += func_800644B8((s32)((S_FUNC_8188C800_BODY_0 *)self)->unk_18.s << 7) << 6;
    func_8002495C(motion, part);
    {
        s32 x = ((S_FUNC_8188C800_BODY_11 *)motion)->unk_00.at02u.v;
        if (x < 0) {
            x += 63;
        }
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at02.v = x >> 6;
        {
            s32 y = ((S_FUNC_8188C800_BODY_11 *)motion)->unk_04.at02u.v;
            if (y < 0) {
                y += 63;
            }
            ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at03.v = y >> 6;
        }
    }
    if (((S_FUNC_8188C800_BODY_0 *)self)->unk_20.at00u.v == ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at02u.v) {
        goto done;
    }
    if (((S_FUNC_8188C800_BODY_8 *)owner)->unk_60.p2 != 0) {
        if ((((S_FUNC_8188C800_BODY_8 *)owner)->unk_70.at00.v & 0xFFFF0000) ==
            (((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at00.v & 0xFFFF0000)) {
            s32 snap_x = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_70.at02.v;
            s32 snap_y;
            snap_x <<= 6;
            snap_x += 32;
            ((S_FUNC_8188C800_BODY_11 *)motion)->unk_00.at02.v = snap_x;
            snap_y = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_70.at03.v;
            snap_y <<= 6;
            snap_y += 32;
            ((S_FUNC_8188C800_BODY_11 *)motion)->unk_04.at02.v = snap_y;
            ((S_FUNC_8188C800_BODY_11 *)motion)->unk_08.at02.v = ((S_FUNC_8188C800_BODY_0 *)self)->unk_10.u;
            func_8002495C(motion, part);
            {
                u8 *target = ((S_FUNC_8188C800_BODY_8 *)owner)->unk_60.p;
                u16 next = ((S_FUNC_8188C800_BODY_0 *)self)->unk_0A.u + 1;
                u16 height = ((S_FUNC_8188C800_BODY_14 *)target)->unk_88;
                ((S_FUNC_8188C800_BODY_0 *)self)->unk_0A.u = next;
                ((S_FUNC_8188C800_BODY_17 *)D_800269C8)->unk_00 = height;
            }
            goto done;
        }
    }

case_0_count_tail:
    {
        u8 old_x = ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at02.v;
        s16 count = ((S_FUNC_8188C800_BODY_0 *)self)->unk_14 - 1;
        u8 old_y = ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at03.v;
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_14 = count;
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_20.at00.v = old_x;
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_20.at01.v = old_y;
        if (count != 0) {
            s32 x = ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at02p.v;
            s32 height;
            s32 y;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
            height = ((S_FUNC_8188C800_BODY_0 *)self)->unk_30.at02u.v;
            ASM_USE_NV(height);   /* MATCH pin: retail schedule: same instructions, different order without it */
            x <<= 6;
            x += 32;
            x &= 0xFFE0;
            ASM_USE_NV(x);   /* MATCH pin: retail schedule: same instructions, different order without it */
            y = ((S_FUNC_8188C800_BODY_0 *)self)->unk_1C.at03u.v;
            y <<= 6;
            y += 32;
            y &= 0xFFE0;
            if ((func_800A45D8(x, y, height) << 16) == 0) {
                goto done;
            }
        }
    }
    ((S_FUNC_8188C800_BODY_0 *)self)->unk_0A.u = 16;
    goto done;

case_3:
    func_80065F90(((S_FUNC_8188C800_BODY_11 *)motion)->unk_0C.at02.v, ((S_FUNC_8188C800_BODY_11 *)motion)->unk_10.at02.v);
    ((S_FUNC_8188C800_BODY_0 *)self)->unk_2C.i =
        func_800262AC(((S_FUNC_8188C800_BODY_11 *)motion)->unk_00.at02u.v, ((S_FUNC_8188C800_BODY_11 *)motion)->unk_04.at02u.v,
                      ((S_FUNC_8188C800_BODY_11 *)motion)->unk_08.at02u.v);
    if (((S_FUNC_8188C800_BODY_0 *)self)->unk_2C.i == 0) {
        goto done;
    }
    if (((S_FUNC_8188C800_BODY_8 *)owner)->unk_60.p2 != 0) {
        func_800A56E0(0x300);
    }
    ((S_FUNC_8188C800_BODY_0 *)self)->unk_0A.u++;
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at00u.v -= ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at00u.v >> 2;
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at01.v -= ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at01.v >> 2;
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at02.v -= ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at02.v >> 2;
    if (!(((S_FUNC_8188C800_BODY_23 *)(((S_FUNC_8188C800_BODY_0 *)self)->unk_2C.p))->unk_1E & 0x8000)) {
        goto done;
    }
    if (((S_FUNC_8188C800_BODY_8 *)owner)->unk_60.p2 != 0) {
        func_80026404(((S_FUNC_8188C800_BODY_8 *)owner)->unk_60.p2, ((S_FUNC_8188C800_BODY_0 *)self)->unk_09, owner);
    }
    goto case_5_tail_prepare;

case_5:
    ((S_FUNC_8188C800_BODY_11 *)motion)->unk_00.at00.v += ((S_FUNC_8188C800_BODY_11 *)motion)->unk_0C.at00.v;
    ((S_FUNC_8188C800_BODY_11 *)motion)->unk_04.at00.v += ((S_FUNC_8188C800_BODY_11 *)motion)->unk_10.at00.v;
    {
        s32 value = ((s32)((S_FUNC_8188C800_BODY_0 *)self)->unk_10.s << 16) -
                    ((S_FUNC_8188C800_BODY_11 *)motion)->unk_08.at00.v;
        value >>= 4;
        ((S_FUNC_8188C800_BODY_11 *)motion)->unk_08.at00.v += value;
    }
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at00u.v -= ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at00u.v >> 1;
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at01.v -= ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at01.v >> 1;
    ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at02.v -= ((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at02.v >> 1;
    func_8002495C(motion, part);
    if (((S_FUNC_8188C800_BODY_2 *)part)->unk_0C.at00u.v < 2) {
case_increment:
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_0A.u++;
    }
    goto done;

case_5_tail:
    if (((S_FUNC_8188C800_BODY_18 *)D_80026472)->unk_00.s != 0) {
        goto done;
    }
case_5_tail_prepare:
    tail_page0 = (u8 *)0x80080000;
    ASM_KEEP(tail_page0);   /* MATCH pin: retail immediate-load split depends on it */
case_5_tail_effect:
    ((S_FUNC_8188C800_BODY_19 *)tail_page0)->unk_346C = 0;
    ((S_FUNC_8188C800_BODY_0_pre *)self)[-1].unk_00 |= 0x8000;
    tail_page1 = (u8 *)0x80080000;
    ((S_FUNC_8188C800_BODY_20 *)tail_page1)->unk_14A0 |= 0x8000;
    goto done;

done:
    {
        u16 frame = ((S_FUNC_8188C800_BODY_0 *)self)->unk_18.u;
        ((S_FUNC_8188C800_BODY_18 *)D_80026472)->unk_00.u = 0;
        ((S_FUNC_8188C800_BODY_0 *)self)->unk_18.u = frame + 1;
    }
}
