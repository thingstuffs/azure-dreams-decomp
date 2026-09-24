from pathlib import Path
import hashlib
import importlib.util
import json
import sys

root = Path(__file__).resolve().parent
repo = Path('<repo>')
source = repo / 'work/native_lane/gp_partition_only_tools/candidate'
pins = json.loads((repo / 'work/native_lane/gp_partition_only_tools/tool_pins.json').read_text())
for rel, digest in pins.items():
    assert hashlib.sha256((root / rel).read_bytes()).hexdigest() == digest, rel
    assert hashlib.sha256((source / rel).read_bytes()).hexdigest() == digest, rel

sys.path[:0] = [str(root / 'tools'), str(root / 'tools/build')]
import configure
import row_db
import slus_modules
import slus_partitions
import slus_module_context
import slus_module_evidence
from fidelity import prove_slus_ownership, certify_slus_module, slus_iso

modules = {name: module for name, module in locals().copy().items()
           if name in {'configure', 'row_db', 'slus_modules', 'slus_partitions',
                       'slus_module_context', 'slus_module_evidence',
                       'prove_slus_ownership', 'certify_slus_module', 'slus_iso'}}
paths = {name: str(Path(module.__file__).resolve()) for name, module in modules.items()}
for name, path in paths.items():
    assert Path(path).is_relative_to(root / 'tools'), (name, path)

test = root / 'tools/tests/test_slus_physical_certificate.py'
spec = importlib.util.spec_from_file_location('private_physical_certificate_pathcheck', test)
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)
assert mod.REPO == root, (mod.REPO, root)
assert Path(mod.E.__file__).resolve() == root / 'tools/slus_module_evidence.py'
assert Path(mod.O.__file__).resolve() == root / 'tools/fidelity/prove_slus_ownership.py'
paths.update({'physical_certificate_test': str(test),
              'physical_certificate_E': str(Path(mod.E.__file__).resolve()),
              'physical_certificate_O': str(Path(mod.O.__file__).resolve()),
              'physical_certificate_repo': str(mod.REPO)})

report = {'schema': 1, 'root': str(root), 'candidate_pins': pins,
          'imports': paths, 'all_candidate_paths': True}
(root / 'import_assertions.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(paths, indent=2))
