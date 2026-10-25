#include "common.h"

extern void func_80025090(void);
extern void func_80025150(void);
extern void func_80025418(void);
extern void func_80025798(void);
extern void func_800257CC(void);
extern void create_and_initializes_copying_n_24_bytes_source_data(void);
extern void func_800258B0(void);
extern void func_80025948(void);
extern void func_800258E4(void);

/* Exact physical callback_vector span; owner unresolved. */
const void *const D_80024028[9] __attribute__((aligned(4))) = {
    func_80025090,
    func_80025150,
    func_80025418,
    func_80025798,
    func_800257CC,
    create_and_initializes_copying_n_24_bytes_source_data,
    func_800258B0,
    func_80025948,
    func_800258E4
};
