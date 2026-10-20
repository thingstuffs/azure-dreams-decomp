"""Disc-backed generator controls, including object context and actual encoding."""
import importlib.util
import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SPEC = importlib.util.spec_from_file_location('main_sdk_asm', ROOT/'tools/build/main_sdk_asm.py')
SDK = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SDK)


class MainSdkAsm(unittest.TestCase):
    def setUp(self):
        (ROOT/'tmp').mkdir(exist_ok=True)
        self.temp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR', ROOT/'tmp'))
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.container = self.root/'work/disc/containers/MAIN_MAIN.BIN'
        self.container.parent.mkdir(parents=True)
        with (ROOT/'work/disc/containers/MAIN_MAIN.BIN').open('rb') as source:
            source.seek(SDK.OBJECT_START)
            self.obj = source.read(SDK.OBJECT_SIZE)
        with self.container.open('wb') as target:
            target.seek(SDK.OBJECT_START)
            target.write(self.obj)

    def test_regeneration_and_assembled_extent(self):
        result = SDK.generate(self.root)
        path = self.root/result['source']
        expected = path.read_bytes()
        path.unlink()
        SDK.generate(self.root)
        self.assertEqual(path.read_bytes(), expected)
        # This proves the mnemonic branch really encodes the branch-to-self,
        # including both delay slots and the unpadded 24-byte section size.
        obj = self.root/'delay.o'
        subprocess.run(['mipsel-linux-gnu-as', '-I'+str(ROOT/'include'), '-march=r3000',
                        '-mtune=r3000', '-no-pad-sections', '-O1', '-G0', '-EL',
                        '-o', str(obj), str(path)], check=True, capture_output=True)
        blob = self.root/'delay.bin'
        subprocess.run(['mipsel-linux-gnu-objcopy', '-O', 'binary', '--only-section=.text',
                        str(obj), str(blob)], check=True, capture_output=True)
        self.assertEqual(blob.read_bytes(), struct.pack('<6I', *SDK.WORDS))
        headers = subprocess.check_output(['mipsel-linux-gnu-objdump', '-r', '-t', str(obj)], text=True)
        self.assertNotIn('RELOCATION RECORDS FOR [.text]', headers)
        # macro.inc emits an ordinary .pdr function-metadata relocation.
        # That discarded metadata is outside the SDK text extent.
        self.assertIn(SDK.SYMBOL, headers)

    def test_mutated_row_refused_before_write(self):
        with self.container.open('r+b') as target:
            target.seek(SDK.OBJECT_START + SDK.ROW_OFFSET)
            target.write(bytes([self.obj[SDK.ROW_OFFSET] ^ 1]))
        with self.assertRaises(ValueError):
            SDK.generate(self.root)
        self.assertFalse((self.root/SDK.OUTPUT).exists())

    def test_mutated_object_outside_row_refused(self):
        with self.container.open('r+b') as target:
            target.seek(SDK.OBJECT_START)
            target.write(bytes([self.obj[0] ^ 1]))
        with self.assertRaises(ValueError):
            SDK.generate(self.root)
        self.assertFalse((self.root/SDK.OUTPUT).exists())

    def test_truncated_object_refused(self):
        with self.container.open('r+b') as target:
            target.truncate(SDK.OBJECT_START + SDK.OBJECT_SIZE - 1)
        with self.assertRaises(ValueError):
            SDK.generate(self.root)

    def test_generated_output_cannot_escape_root(self):
        outside = self.root/'outside'
        outside.mkdir()
        build = self.root/'build_slus'
        build.mkdir()
        (build/'asm').symlink_to(outside)
        # A symlink inside this isolated root is safe. An external target is
        # refused; use its parent, which is outside the selected sub-root.
        child = self.root/'child'
        child.mkdir()
        shutil.copytree(self.root/'work', child/'work')
        (child/'build_slus').symlink_to(build)
        with self.assertRaises(ValueError):
            SDK.generate(child)
        self.assertFalse((outside/'psyq/libcard/main_patch_delay.s').exists())


if __name__ == '__main__':
    unittest.main()
