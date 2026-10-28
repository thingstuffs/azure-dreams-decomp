/* SPU DMA callbacks, transfer direction flags, register pairs and voice key-on submission. */
#include "common.h"
#include "engine/audio/spu.h"
#include "slus.h"

/* Partition owner: the seven slus/code functions that live inside the stock-2.7.2
 * sound TU (0x8005CA90-0x8005FA34, docs/evidence/sound_tu_code_partition.md).
 * Declarations transplanted unchanged from src/slus/code.c. */

extern int *D_8007996C[4];

extern void DMACallback(int a0, int a1);

typedef struct {
    u8 pad[0x1AA];
    u16 field_1AA;
} TargetStruct;

typedef struct {
    TargetStruct *ptr;
    u32 pad2[2]; /* keep total size > 8 bytes so hi/lo addressing (not gp_rel) is used */
} D_80079958_t;

extern D_80079958_t spu_registers;

#include "../build/partition_sources/code__sound_tu_code.c"
