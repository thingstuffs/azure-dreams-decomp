#include "common.h"

/* The type-0x13 table consists of 32 records, each 21 words (0x54 bytes). */
typedef struct Copy84 {
    s32 word[21];
} Copy84;

/* These are the real external routines used by this function. */
extern void *func_8003FD64(s32 size, void *template);
extern s32 func_8004A658(s32 type, s32 value);
extern void func_8008F0D4(void *object, void *part_a, void *table);
extern void func_8009B218(void *object, void *part_a, void *part_b,
                           void *callback);
extern void func_8009C1B4(void *object, void *object_again, void *part_a,
                           void *part_b);
extern void func_8009DC8C(void *object, void *part_b, s32 value,
                           void *callback);
extern void func_800B2244(void *arg0);

extern Copy84 D_800102F0[];
extern s32 D_8006E240;
extern u8 D_80083498[];
extern u8 D_8009DEBC[];
extern u8 D_800D073C[];
extern u8 D_800D0754[];
extern u8 D_800D076C[];
extern u8 D_800D0788[];
extern Copy84 D_80100AF8;
extern void *D_80100B0C;

/* The fixed table is intentionally addressed by its period source literal.
 * Retail emits `lui 0x8001` / `ori 0x02f0`; naming it as a linked extern
 * changes that pair to `%hi` / `%lo` (`lui` / `addiu`) under cdk. */
#define COPY_TABLE_ADDRESS ((Copy84 *)0x800102F0)

/* Typed byte/halfword/word/pointer accessors for the established object maps. */
#define BYTE_AT(base, offset) (*(u8 *)((u8 *)(base) + (offset)))
#define HALF_AT(base, offset) (*(u16 *)((u8 *)(base) + (offset)))
#define WORD_AT(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define POINTER_AT(base, offset) (*(void **)((u8 *)(base) + (offset)))

void *func_8009DFD8(void *arg0, void *arg1, s32 arg2)
{
    void *created;
    void *part_b;
    void *part_a;
    void *object;
    u8 type;

    created = func_8003FD64(0x136, D_80083498);
    if (created == 0) {
        return 0;
    }

    part_a = POINTER_AT(created, 8);
    part_b = POINTER_AT(created, 0xC);
    HALF_AT(part_a, 2) = HALF_AT(arg1, 2);
    HALF_AT(part_a, 6) = HALF_AT(arg1, 6);
    HALF_AT(part_a, 0xA) = HALF_AT(arg1, 0xA);

    object = (u8 *)created + 0x20;
    HALF_AT(part_b, 0x1E) = 0x1000;
    HALF_AT(part_b, 0x1C) = 0x1000;
    WORD_AT(part_b, 0xC) = 0x00808080;
    WORD_AT(object, 0x48) = 0;
    WORD_AT(object, 0x98) = 0;
    BYTE_AT(object, 0x93) = 0;

    BYTE_AT(object, 0x4C) = BYTE_AT(arg0, 0);
    BYTE_AT(object, 0x4D) = BYTE_AT(arg0, 1);
    BYTE_AT(object, 0x4E) = BYTE_AT(arg0, 2);
    BYTE_AT(object, 0x4F) = BYTE_AT(arg0, 3);
    type = BYTE_AT(object, 0x4D);

    if (type == 0x13) {
        Copy84 *copy_table = COPY_TABLE_ADDRESS;
        Copy84 *copy_src;

        copy_src = (Copy84 *)((u32)(BYTE_AT(object, 0x4F) & 0x1F) * 84U
                              + (u32)copy_table);
        D_80100AF8 = *copy_src;
    }

    func_8008F0D4(object, part_a, D_800D073C);
    if (arg2 != 0) {
        func_8009B218(object, part_a, part_b, D_800D0788);
    } else {
        func_8009B218(object, part_a, part_b, D_800D076C);
    }

    if ((u32)(BYTE_AT(object, 0x4D) - 0x12) < 2) {
        POINTER_AT(object, 0xC) = D_800D0754;
    }
    type = BYTE_AT(object, 0x4D);

    if (type == 0x12) {
        POINTER_AT(part_b, 8) = &D_8006E240;
    } else if (type == 0x13) {
        func_8009DC8C(object, part_b, BYTE_AT(object, 0x4C), D_80100B0C);
        goto set_callback;
    } else {
        POINTER_AT(part_b, 8) = (void *)func_8004A658(
            BYTE_AT(object, 0x4D), BYTE_AT(object, 0x4C));
    }

set_callback:
    POINTER_AT(created, 0x10) = D_8009DEBC;
    func_8009C1B4(object, object, part_a, part_b);
    func_800B2244(arg0);
    return created;
}
