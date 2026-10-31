#include "common.h"
#include "engine/cd.h"
#include "slus.h"

typedef struct { u32 v; } __attribute__((packed)) UA32;

extern void allocate_item_without_data_override(void *a0, void *a1, s32 a2, void *a3);
extern UA32 D_80080B50[];

/*
 * Copies D_80080B50, submits and drains the CD command queue, then allocates the target item with
 * that copied data.
 */
void finish_cd_load_and_initialize_target(void *target)
{
    UA32 local_copy;
    *&local_copy = *D_80080B50;
    submit_global_cd_command_six();
    drain_cd_command_queue();
    allocate_item_without_data_override(target, 0, 0, &local_copy);
}
