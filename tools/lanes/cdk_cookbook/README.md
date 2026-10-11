# CDK cookbook reproducer kit

From the repository root:

```sh
cd tools/lanes/cdk_cookbook
python3 tools/reproduce.py
```

Requires Python 3, GDB, nm, and GNU `mipsel-linux-gnu-{as,ld,objcopy,objdump}`.
Copies the repository's CDK compiler and relevant source into `scratch/` and
compiles header-free plain-C probes. It never edits repository rows, recipes,
headers, gate tools or certificates. BFM sources were read as data only; no
BFM executable or script participates.

`cases.json` selects 21 frozen probes. `expected.json` binds compiler/source
inputs and linked `.text` hashes. `tools/observe.py` uses symbol addresses from
that copied compiler to observe scheduler predicates, quantity/allocation
orders, CSE heads, loop reference weights, reload mutations and combine splits.
It never writes inferior state and requires traced assembly to equal the plain
compile. `tools/reproduce.py` checks each mechanism and writes the complete RTL,
assembly, object, diagnostic linked ELF/bytes/disassembly and observer logs to
`evidence/probes/`. Results carry `reviewer: pending`.

Diagnostic link addresses: text `0x80010000`; consume/sink/step/other/tick at
`0x80020000/20/40/60/80`; flags at `0x80030000`. These addresses fix relocation
values for reproducibility and assert no retail placement. Binary lengths
include assembler section padding. These are compiler mechanism proofs, not
production window gates, native-module membership evidence or retail matches.

See `tools/lanes/brief_paragraphs/cdk_cookbook.md` for symptom-keyed guidance.
No banned scaffold is an admissible lever. A mechanism working here is a
hypothesis for a production row; that row still needs its unchanged production
window gate and supported ABI/dataflow.
