<p align="center">
  <img src="assets/meccha-camouflage-banner.png" alt="Meccha Camouflage banner" width="100%" />
</p>

# Meccha Camouflage Runtime

This repository is now centered on the Xenos-injected `p` runtime. The active runtime lives at the repository root:

- `src/`: Python orchestration service and CLI.
- `native/`: C++ injector and injected bridge.
- `scripts/`: build, deploy, and SDK dump workflow scripts.
- `dumper-sdk/`: managed Dumper7 SDK output for the target game build.
- `tools/Dumper-7/`: local Dumper-7 tool source.

The old UE4SS runtime is not part of the active build/deploy path.

## Build

From the repository root:

```bash
./scripts/dev_flow.sh -Action build
```

Build output is written under `.build/`:

```text
.build/
  native/bin/                 # injected DLL and injector exe
  native/obj/                 # native object files
  pyinstaller/                # PyInstaller work/spec files
  venv/                       # Python virtualenv
  dist/meccha-camouflage.exe  # runtime exe
```

## Deploy

```bash
./scripts/dev_flow.sh -Action deploy -GameRoot 'C:\Program Files (x86)\Steam\steamapps\common\MECCHA CHAMELEON'
```

The deploy script installs `.build/dist/meccha-camouflage.exe` into:

```text
C:\Program Files (x86)\Steam\steamapps\common\MECCHA CHAMELEON\Chameleon\Binaries\Win64
```

If the target exe is locked, deploy stages a `.pending.exe` and starts the replacement watcher.

## Run

The default runtime mode is the Xenos service path:

```bash
./scripts/dev_flow.sh -Action run
```

Direct Python usage is still supported for development:

```bash
python -m src --mode service --adapter xenos --print-summary
python -m src --mode loop --adapter noop --loop-frames 5 --print-summary
```

Runtime diagnostics are written to:

```text
%LOCALAPPDATA%\MecchaCamouflage\runtime\events.jsonl
%LOCALAPPDATA%\MecchaCamouflage\runtime\last_status.json
%LOCALAPPDATA%\MecchaCamouflage\runtime\runtime.log
```

## Route policy

Current route policy is documented in `native/README.md`.

High-level rules:

- Active multiplayer candidates must go through Xenos/native SDK routes.
- Local-only texture import is not a default runtime path.
- Material swap, synthetic UV placement, and memory-scan fallback are forbidden.
- Python remains as orchestration in phase 1; a C++ service replacement is tracked in `docs/cpp-service-roadmap.md`.
