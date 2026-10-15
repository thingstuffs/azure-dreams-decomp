# CDK C89 promoted filter parameter at 8001A768

Scope: the complete floor-generation cohort, GCC 2.7.2-cdk -O2 -G0 and genuine ASPSX 2.79 -q -G0 -0. This is a source/ABI observation, not a unique compiler-lineage attribution.

The shared prototype takes its final filter argument as an s32 word. A C89 definition declaring that parameter s16 is compatible after default argument promotions; the isolated compatibility test compiles with -Werror. This preserves the retail caller evaluation and the callee's signed-halfword view without an incompatible function-pointer cast or a second prototype.

An ANSI short prototype changed twelve words in the caller's division/pointer block. An ANSI word definition changed six t0/t1 register fields in the callee. Eagerly truncating the word at entry removed four bytes and changed load scheduling. The C89 promoted definition reproduces the original 1,120-byte callee and the complete 49-function/52-byte-table 27,888-byte TU, unmasked retail and genuine MATCH. The final cohort also includes its separately proved eight-byte empty routine.

Separate source fixes matter: retain multidimensional external-array strides; use a single typed six-byte map-cell array directly instead of introducing redundant pointer views at its accesses. These findings are conditional on this C shape and recipe. They grant no generic flag, assembly rewrite or register constraint.

Lane receipts: candidates/dungeon_floor_generate_isolated/header_feature_probes/, multidimensional_view_repairs.json, whole_tu_result.json; tools/tests/test_native_switch_allocations.py.
