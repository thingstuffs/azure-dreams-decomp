# Three MAIN coverage gaps: retail audit, 2026-09-24

These routines remain outside the 423 registered MAIN C rows. Their split records
exist, but no current C source represents them. This audit makes the gap
reproducible; it does not mark them implemented, parked, or impossible in C.

| Routine | MAIN_MAIN.BIN offset | Bytes | Split result | SHA-256 |
|---|---|---:|---|---|
| `func_800217C8` | `0x2717C8` | 104 | NOMATCH | `3b175235864c739f6d9fa48c4589d1f3631317a5aac4855140ac2bb0bf9eef6e` |
| `func_800218A0` | `0x2718A0` | 136 | CFAIL | `bf2101ffd41591f38a4f0dd260b22289c6eeb3e8b91416c96dd686bbef1fb1a0` |
| `func_80021958` | `0x271958` | 108 | CFAIL | `00fb85f0f54031f2fa57511044aefda649acbccb70d413f5903165dae51000a8` |

`tools/fidelity/audit_main_kernel.py` independently extracts these ranges and
disassembles them using the derived mapping in `main_boot.overlay.yaml`. The first
digest matches the historical ledger proof. Retail-slice hashes are not rebuild
or C-equivalence proofs.

The instructions confirm zero stack frames, `$ra` saved to fixed globals, inline
BIOS vector `0xB0` calls with selectors `0x56`, `0x56`, `0x57`, template/handler
manipulation, and restoration of `$ra`. Save slots are `0x8040922C` for 217C8 and
`0x8040923C` for the other two. These facts support the recorded kernel-installer
behavior; they do not independently identify an SDK release or original authorship.

An offset clarification: 21958 loads from target `+0x9C8`, advances the pointer by
four, then stores at `+0x9C4` in the branch delay slot. Its first effective store
is original target `+0x9C8`, followed by `+0x9CC` through `+0x9D8`. Its source
template advances from `0x80408928` to exclusive end `0x8040893C`. The split note's
`+0x9C4/+0x9C8` names instruction displacements, not two starting destinations.

```sh
python3 tools/fidelity/audit_main_kernel.py
```

Outputs: `work/fidelity/main_kernel_audit/` (slices, disassemblies, `SHA256SUMS`).
Luna's detailed inventory: `work/native_lane/main_coverage_inventory/REPORT.md`.

The initial audit left incoming callers unverified; the follow-up below now
identifies direct calls. No source-name hits alone could establish that these
routines are unused. Their historical lane note is absent at its exact
working-tree and checked archive paths. Follow-up implementation should establish
callers and the platform boundary, then reproduce code through the real build
gate. Do not inherit the old notes' universal C-impossibility claims without a
new feature-attribution audit.

## Follow-up: callers and linked-address boundary

The [caller audit](main_kernel_callers/REPORT.md) identifies four direct `jal`
instructions in two MAIN caller functions. Their encoded targets use the
independently evidenced link mapping of the memory-card front-end image, rather
than the derived names assigned by `main_boot.overlay.yaml`:

| Historical row name | Linked target | Direct callsite VMAs |
| --- | --- | --- |
| `func_800217C8` | `0x804087C8` | `0x80408780` |
| `func_800218A0` | `0x804088A0` | `0x80408704` |
| `func_80021958` | `0x80408958` | `0x8040870C`, `0x80408778` |

TOWN contains the same 208-byte caller block, byte for byte; it is counted as a
physical copy, not four additional independent source callers. A separate
TOWN word containing the derived `0x80021958` spelling lies in table-like data
and has no confirmed relationship to the installer. The scan and root review
confirm the four MAIN instruction encodings against the held binary.

The existing assertion-site audit classifies the containing image as devkit-linked.
These linked addresses do not, by themselves, prove runtime loading or execution
on retail hardware. The routines remain a BIOS-vector/kernel-patching boundary
inside that image. Held libcard labels and neighboring Sony `c_server.c` evidence
support the memory-card context, but the exact SDK object and release for these
three routines remain unknown. The scan excludes neither indirect calls nor
constructed/relocated pointers.

All three remain explicit unregistered C-coverage gaps. This follow-up supplies
callers and a more precise address/provenance boundary; it neither implements
them nor establishes a universal C-impossibility claim. Their existing row IDs
and source mapping are retained pending an independently verified mapping change.
