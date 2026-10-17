---
tags: [xungram, build, deps]
---
# tde2e

E2E-библиотека Telegram (шифрование). Зависимость [[Сборка нативный Arch]].

## Как получают (из Dockerfile)
```bash
git init tde2e
git remote add origin https://github.com/tdlib/td.git
git fetch --depth=1 origin 51743dfd01dff6179e2d8f7095729caa4e2222e9
git reset --hard FETCH_HEAD
cmake -B build . -DTD_E2E_ONLY=ON
cmake --build build
cmake --install build --prefix <prefix>   # tde2e::tde2e
```

## Что важно
- Это **не** полный TDLib, а режим `TD_E2E_ONLY`.
- CMake ждёт: `find_package(tde2e REQUIRED)` → `tde2e::tde2e`
  (`cmake/external/tde2e/CMakeLists.txt:11`).

## Сделано у нас
- Собран коммит `51743df…`, установлен в `.deps/tde2e`.
- Ошибка «Could not find tde2e» → решена через `CMAKE_PREFIX_PATH`.

## Связанные заметки
- [[Внешние зависимости]]
- [[Исправления сборки]]
