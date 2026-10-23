#ifndef ENGINE_NODE_H
#define ENGINE_NODE_H
/* Prototypes of the functions defined in src/engine/node/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/object_node.h"

struct RegistrationNode;
struct S_8003FF2C;
struct S_8003FFF0;
struct S_80040060;
struct S_800511B4_entity;
struct S_800833E0;

/* allocate_list_node.c */
void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);

/* create_linked_zukan_task.c */
void *create_linked_zukan_task(struct S_800511B4_entity *related_entity);

/* evict_node_and_allocate.c */
void *evict_node_and_allocate(void *flags, void *excluded_node);

/* initialize_runtime_node_storage.c */
struct S_8003FF2C *initialize_runtime_node_storage(s32 flags, struct S_8003FF2C *storage, s16 word_count, struct S_8003FF2C **list_head);

/* insert_active_node_after.c */
void insert_active_node_after(struct S_80040060 *anchor, struct S_80040060 *node);

/* integrate_active_node_vectors.c */
void integrate_active_node_vectors(void);

/* register_node.c */
s32 func_8004491C(struct RegistrationNode *entry, s32 registration_id);
s32 register_node(struct RegistrationNode *entry, s32 registration_id);

/* register_node_if_unregistered.c */
void func_80033CD8(void *block_data, s32 registration_id);
void register_node_if_unregistered(void *block_data, s32 registration_id);

/* run_active_node_callbacks.c */
void run_active_node_callbacks(void);

/* run_node_callback_and_set_marker.c */
void run_node_callback_and_set_marker(void *entry, void *output, void *context);

/* table_set_bit_in_node_global_flags_node_exists.c */
void table_set_bit_hex_8000_in_node_global_flags_node_exists(struct ObjectNodeHeader *node);

/* unlink_active_node.c */
void unlink_active_node(struct S_8003FFF0 *node);

/* unlink_node.c */
void func_80044A50(struct S_800833E0 *node);
void unlink_node(struct S_800833E0 *node);

/* unlink_node_if_registered.c */
void func_80033D08(void *block_data);
void unlink_node_if_registered(void *block_data);

/* update_active_nodes.c */
void update_active_nodes(void);

/* update_node_registration.c */
void update_node_registration(void *state, void *context);


#include "shared/object_node_flags.h"

/* ObjectNodeHeader.flags (+0x1E); see allocation and callback loops. */
#define NODE_SKIP_CALLBACK 0x400
#define NODE_ACTIVE 0x4000

#endif
