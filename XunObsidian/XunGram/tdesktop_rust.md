---
tags: [xungram, build, deps, rust]
---
# tdesktop_rust

Rust-сборка для крипто-кошелька. Зависимость [[Сборка нативный Arch]].

## Почему один крейт
Каждый Rust staticlib тянет свою копию std → дубли символов рантайма.
Поэтому **tlottie + wallet-engine** собираются в один архив `libtdesktop_rust.a`.

## Как получают (из Dockerfile)
```bash
RUST_TOOLCHAIN=1.96.1   # rustup
# tlottie @ 92df98dc…, wallet-engine @ e59e0d89… (+ патч desktop-app/patches)
cargo new --lib --vcs none tdesktop_rust
printf 'pub use ::tlottie;\npub use ::wallet_engine;\n' > src/lib.rs
cargo add --path ../tlottie --features c-api
cargo add --path ../wallet-engine
cargo rustc --lib --release --crate-type staticlib --crate-type cdylib
# затем uniffi-bindgen-cpp → wallet_engine.hpp/.cpp
```

## Наши артефакты (`.deps/tdesktop_rust`)
- `lib/libtdesktop_rust.a`
- `include/tlottie/tlottie.h`
- `include/wallet_engine/wallet_engine.hpp` + `.cpp` + `_scaffolding.hpp`

## CMake ждёт
- `find_library(tdesktop_rust)` (`cmake/external/tdesktop_rust/CMakeLists.txt`)
- `find_path(wallet_engine.hpp)` + `wallet_engine.cpp` (`cmake/external/wallet_engine/…`)

## Заметки
- Rust 1.96.1 поставили через `rustup` (pacman) + `rustup toolchain install`.
- native-static-libs: `-lgcc_s -lutil -lrt -lpthread -lm -ldl -lc`.

## Связанные заметки
- [[Внешние зависимости]]
- [[Исправления сборки]]
