#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template0;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

extern Template0 D_8002E5D8;
extern Vec3 D_8002E5E8;

/* Initialize nine records and vectors from templates, setting each record's last byte to 4. */
void func_800DCC3C(u8 *object) {
    u8 *header;
    s32 entry_index;
    u8 *record_page;
    Template0 *record_template;
    u8 tail_byte;
    u8 *vector_page;
    Vec3 *vector_template;
    register s32 vector_offset ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 record_offset;
    register s32 vector_addr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 vector_z;

    header = object;
    entry_index = 0;
    ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    record_page = (u8 *)0x80030000;
    ASM_KEEP(record_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    record_template = (Template0 *)(record_page - 0x1A28);
    ASM_KEEP(record_template);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    tail_byte = 4;
    ASM_KEEP(tail_byte);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    vector_page = (u8 *)0x80030000;
    ASM_KEEP(vector_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    vector_template = (Vec3 *)(vector_page - 0x1A18);
    ASM_KEEP(vector_template);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    vector_offset = entry_index;

    do {
        record_offset = entry_index * 0x10;
        *(s32 *)(record_offset + *(s32 *)(header + 4)) =
            *(s32 *)(record_page - 0x1A28);
        *(s32 *)(record_offset + *(s32 *)(header + 4) + 4) = record_template->unk4;
        *(s32 *)(record_offset + *(s32 *)(header + 4) + 8) = record_template->unk8;
        *(s32 *)(record_offset + *(s32 *)(header + 4) + 0xC) = record_template->unkC;
        *(u8 *)(record_offset + *(s32 *)(header + 4) + 0xF) = tail_byte;
        entry_index++;
        *(s32 *)(vector_offset + *(s32 *)(header + 8)) =
            *(s32 *)(vector_page - 0x1A18);
        *(s32 *)(vector_offset + *(s32 *)(header + 8) + 4) = vector_template->y;
        vector_addr = *(s32 *)(header + 8);
        vector_z = vector_template->z;
        vector_addr = vector_offset + vector_addr;
        *(s32 *)(vector_addr + 8) = vector_z;
        vector_offset += 0xC;
    } while (entry_index < 9);
}

