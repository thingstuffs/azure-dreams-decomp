#ifndef SLUS_ADDRESS_SLOT_H
#define SLUS_ADDRESS_SLOT_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

/* Regular (>8B) globals accessed via %hi/%lo. */
extern unsigned char cd_resource_primary_buffer[0x10];
extern unsigned char cd_resource_secondary_buffer[0x10];

/* <=8B global -> $gp small-data STORE, while address-of stays %hi/%lo. */
extern void *loaded_cd_resource_handle;

extern void queue_entity_resource_descriptor_pair(void *a0, void *a1, unsigned short a2);
extern void drain_cd_command_queue(void);
extern void *func_80047AB0(void *a0, unsigned short a1, int a2, int a3, void *a4);

/* Loads image data by resource ID, uploads its tiles, and returns the global object slot. */

void *load_cd_resource(int resource_id);
void *func_80047E78(int resource_id);

#endif
