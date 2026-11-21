# BootLoadEx
Common files for creating Rebootex and Payloadex.

The PSP boot scanners support 6.20, 6.39 and 6.60 without selecting a firmware
version in `BootLoadExConfig`. Loadcore's memlmd imports identify the NID pair
and scan range in `bootloadex.c`; the reboot and IPL hooks use instruction
patterns. The 6.20 loadcore import table needs a larger scan range than 6.60.
Vita continues to use the 6.60 NIDs, although its loadcore does not necessarily
import the sign-check function.

To add another firmware, inspect its decrypted reboot, IPL and loadcore for
the required patch sites and memlmd imports. Add its decrypt/sign-check NID
pair and necessary loadcore scan range to `memlmd_nids`, then verify that the
boot patterns locate the correct instructions without matching unrelated code.
Also check the loadcore entry point, import table and both unpatch scans fit
the selected range. A bootloader hook does not make firmware-specific CFW
modules compatible with a different firmware.

On Linux, the host regression test can be run with:

```
python3 tests/test_bootloadex_firmware.py /path/to/flash0_dumps
```

It compiles the production patch and import scanners into a host harness and
checks the available decrypted images and reference patch sites. The harness
stubs cache operations and recreates relocated import descriptors for the host;
it does not execute PSP instructions or replace hardware testing. Some 6.39
dumps may still contain encrypted reboot images, which cannot be checked by
this test.
