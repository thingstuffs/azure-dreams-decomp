# Goal completion evidence audit

Read-only audit of module-pilot item 3, MAIN item 4, and the separate pending production toolchain transition. No source, production configuration, certificate, or documentation inputs were changed. The newest checked generated status snapshot is `STATUS.md` at `2026-09-24T21:49:41Z`; its level rows were generated at `2026-09-24 21:49:40Z`, immediately after the module certificate at `21:49:18Z`.

## Item 3 — runtime-directory module pilot

**The verified-pilot requirement is already met.** The implementation and manifest are present in `src/slus/konami_runtime_directory.c`, the three canonical row fragments, `include/slus/runtime_directory.h`, and `config/slus_modules.json`. The aggregator defines the exact four-byte `D_80080A6C` object and includes the three row fragments in address order. The member rows remain distinct logical IDs. Membership is explicitly described as an inferred partial call-graph/address-range cluster; excluded neighboring users, uncertain historical translation-unit ownership, and the still-external `func_8003C6F8` are documented in `docs/evidence/runtime_directory_module.md`.

The durable build receipt, `docs/evidence/slus_module_build_receipt.json`, records 884 logical rows matching the pinned recipe, a 524,288-byte retail-identical image, unchanged member function addresses and sizes, and candidate checks that reject both a function change and a sibling-function regression. The module evidence and `ledger/modules/runtime_directory.json` record fresh genuine-ASPSX 2.79 plus retail equality for all three member functions: 104 words total and no masked relocations. The live `STATUS.md` module table reports placement as current. This demonstrates the grouping, whole-image build check, placement certificate, and refreshed status view required by item 3.

The current level result is mixed within the module, as the ladder requires:

| Row | Level in `ledger/levels.jsonl` | Pins | Tail jumps | Remaining L5 residue |
|---|---:|---:|---:|---|
| `slus/konami_runtime_w_8003C634` | L5 | 0 | 0 | none |
| `slus/konami_runtime_w_8003C758` | L4 | 0 | 0 | `fidelity_site` (`PASSTHRU` in `ledger/census.jsonl`) |
| `slus/konami_runtime_w_8003C920` | L5 | 0 | 0 | none |

Thus all three currently meet L4; the module as a whole must not be described as L5. Reaching L5 for C758 requires clearing its recorded fidelity site and regenerating the affected module proof/certificate and level/status views, since the certificate fingerprints member sources. That is an L5 follow-up, not a missing verified-pilot deliverable. The checked certificate rows also show `maspsx_exact: true` and no fired assembler passes for these three rows under their existing pinned recipe.

The repeat workflow and its exact gates are documented in `docs/SLUS_MODULES.md` under “Build, verify, and certify.” The evidence supports claiming the pilot is done while preserving the one member’s actual L5 residue.

## Item 4 — three unregistered MAIN routines

The gap audit in `docs/evidence/main_kernel_coverage_audit.md` records each routine separately from the 423 registered MAIN C rows, including slice offsets, sizes, and hashes. It also records the observed zero-stack-frame BIOS-vector installer behavior and the corrected store-offset interpretation for `func_80021958`.

The follow-up in `docs/evidence/main_kernel_callers/REPORT.md` establishes four direct MAIN `jal` callsites to linked targets `0x804087C8`, `0x804088A0`, and `0x80408958`; the same 208-byte caller block appears byte-for-byte in TOWN. The evidence identifies this as a devkit-linked memory-card/kernel-patching boundary and supports memory-card provenance from neighboring Sony/libcard evidence. It does not establish the TOWN runtime load address or retail execution/loading.

**Still unresolved:** the exact SDK object and release for these three routines, and whether/how the devkit-linked block is loaded and executed on retail hardware. There is no C implementation or retail-byte C/build proof for the three functions, and they remain explicit unregistered C-coverage gaps. If a suitable implementation and retail proof can be recovered, item 4 calls for that work. Otherwise its stated completion fallback is already being followed: keep these precise evidence-backed gaps visible, avoid a universal “impossible in C” claim, and do not infer whole-game C completeness from registered rows alone. No level rows can be assigned to them from the registered-row level ledger.

## Separate global toolchain transition

The global assembler proposal is substantially proven in private, but it is not yet a production transition. `docs/GOAL_TOOLCHAIN_AND_MODULES.md` records the private six-version census over 6,767 registered rows (6,600 genuine-ASPSX matches, 167 still dependent), the full private ownership rehearsal and two placement certificates, and the passing private full-SLUS/overlay gates. It also explicitly leaves the final combined proposal review and owner sign-off, production activation, and a fresh production census outstanding. The sink-pass removal remains in full-gate rehearsal, and the function-address split pass still has one required consumer.

These are global toolchain activation/recertification tasks. They do not invalidate the runtime-directory pilot’s current certificate, which proves the pilot against its existing pinned recipe; they also do not close the three MAIN C-coverage gaps.

The current module certificate is fresh against the current production recipe (`certificate_reason` returns no reason; its gate is `MATCH` with recipe hash `c74e83b131ea6c04c2cc4f62dc042b45ebaf28dfc1d37350b8159a699a52d7f2`). After a toolchain switch is activated, rerun the module certificate/status flow against the switched recipe; that future recertification is part of transition integration, not evidence that the present pilot certificate is stale.

## Evidence references

- `docs/GOAL_TOOLCHAIN_AND_MODULES.md:36-56, 209-225`
- `docs/SLUS_MODULES.md:128-255`
- `docs/evidence/runtime_directory_module.md:1-64`
- `docs/evidence/slus_module_build_receipt.json`
- `config/slus_modules.json:1-52`
- `ledger/modules/runtime_directory.json`
- `ledger/levels.jsonl:6187,6190,6194`; `ledger/census.jsonl:6187,6190,6194`
- `STATUS.md:1-49`
- `docs/evidence/main_kernel_coverage_audit.md:1-72`
- `docs/evidence/main_kernel_callers/REPORT.md:1-32`
