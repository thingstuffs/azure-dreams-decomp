#!/usr/bin/env python3
"""Retain canonical row bodies while proving complete owner compiler identity."""
from pathlib import Path
import hashlib
import json
import re
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
PAYLOAD = HERE.parent / "transition/payload"
CCDIR = ROOT / "toolchain/compilers/gcc-2.7.2-cdk"
INCLUDE = HERE.parent / "live_fixture/include"

def sha(data):
    return hashlib.sha256(data).hexdigest()

def main():
    (HERE / ".ignore").write_text("*\n")
    before = HERE / "before"
    after = HERE / "after"
    before.mkdir(exist_ok=True)
    after.mkdir(exist_ok=True)
    d92_path = before / "gp_d92c_owned.c"
    if not d92_path.exists():
        d92_path.write_bytes((PAYLOAD / "src/slus/gp_d92c_owned.c").read_bytes())
    d92 = d92_path.read_text()
    assert sha(d92.encode()) == "094846f0ceafe918e5bee6cddf2267f44e3dd27cd6ad4777855d91492e11f146"
    defs = "short D_80080ABC = 0;\nshort D_80080ABE = 0;\n"
    assert d92.endswith(defs)
    (after / "w_8003D92C.c").write_text(d92[:-len(defs)])
    (after / "gp_d92c_owned.c").write_text('#include "w_8003D92C.c"\n\n' + defs)

    order_path = before / "gp_order_bytes_owner.c"
    if not order_path.exists():
        order_path.write_bytes((PAYLOAD / "src/slus/gp_order_bytes_owner.c").read_bytes())
    order = order_path.read_text()
    assert sha(order.encode()) == "b6faa63327ca26472cda02992d722eee347d639c75daffe7b17f4a03368da388"
    definition = "u8 D_80080B30[4] = { 1, 3, 2, 4 };"
    assert order.count(definition) == 1
    (after / "w_80049F68.c").write_text(order.replace(definition, "extern u8 D_80080B30[4];"))
    (after / "gp_order_bytes_owner.c").write_text('#include "common.h"\n\n' + definition + '\n\n#include "w_80049F68.c"\n')

    records = []
    for name, source, flags in (("gp_d92c_owned.c", d92, []),
                                ("gp_order_bytes_owner.c", order, ["-fno-strength-reduce"])):
        (before / name).write_text(source)
        streams = {}
        for folder in (before, after):
            command = [str(CCDIR / "gcc"), "-B" + str(CCDIR) + "/", "-S", "-O2",
                       *flags, "-I" + str(INCLUDE), "-w", name, "-o", name + ".s"]
            p = subprocess.run(command, cwd=folder, capture_output=True, text=True)
            (folder / (name + ".log")).write_text(p.stdout + p.stderr)
            assert p.returncode == 0, (name, p.stderr)
            streams[folder.name] = (folder / (name + ".s")).read_bytes()
        metadata = {arm: [line for line in stream.splitlines(keepends=True)
                          if re.match(rb"\s*\.file\s", line)]
                    for arm, stream in streams.items()}
        meaningful = {arm: b"".join(line for line in stream.splitlines(keepends=True)
                                    if not re.match(rb"\s*\.file\s", line))
                      for arm, stream in streams.items()}
        records.append({"owner": name, "recipe": "2.7.2-cdk " + " ".join(flags),
                        "before_source_sha256": sha(source.encode()),
                        "compiler_assembly_identical": streams["before"] == streams["after"],
                        "identical_except_file_metadata": meaningful["before"] == meaningful["after"],
                        "file_metadata": {arm: [line.decode().rstrip() for line in lines]
                                          for arm, lines in metadata.items()},
                        "instruction_and_directive_sha256": sha(meaningful["after"]),
                        "before_assembly_sha256": sha(streams["before"]),
                        "after_assembly_sha256": sha(streams["after"])})
    result = {"status": "MATCH_EXCEPT_FILE_METADATA" if all(r["identical_except_file_metadata"] for r in records) else "DIFF",
              "records": records,
              "proposed_sources": {p.name: sha(p.read_bytes()) for p in sorted(after.glob("*.c"))}}
    (HERE / "receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
