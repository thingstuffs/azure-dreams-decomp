#ifndef ENGINE_CD_H
#define ENGINE_CD_H
/* Prototypes of the functions defined in src/engine/cd/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_80083968;

/* cd_poll_and_get_sector.c */
int cd_poll_and_get_sector(void);

/* drain_cd_command_queue.c */
void drain_cd_command_queue(void);
void func_8003F320(void);

/* drain_cd_command_queue_second.c */
void finish_cd_load_and_initialize_target(void *target);

/* enqueue_cd_command_record.c */
struct S_80083968 *enqueue_cd_command_record(s16 entry_type, s32 entry_value, s32 payload);

/* get_cd_command_queue_depth.c */
s32 get_cd_command_queue_depth(void);

/* load_cd_resource.c */
void *func_80047E78(int resource_id);
void *load_cd_resource(int resource_id);

/* Data declarations. */
extern s32 cd_read_command_second_word;
extern void *loaded_cd_resource_handle;

#endif
