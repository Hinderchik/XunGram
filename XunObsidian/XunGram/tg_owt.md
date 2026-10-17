---
tags: [xungram, build, deps, webrtc]
---
# tg_owt

Форк WebRTC. Самая тяжёлая зависимость [[Сборка нативный Arch]]. **Ещё не собрана.**

## Как получают (из Dockerfile)
```bash
git init tg_owt
git remote add origin https://github.com/desktop-app/tg_owt.git
git fetch --depth=1 origin d1cf250ea73de26c4c1f0a3c8173eb2648efbb04
git reset --hard FETCH_HEAD
git submodule update --init --recursive --depth=1
cmake -B build . -DTG_OWT_DLOPEN_PIPEWIRE=ON
cmake --build build
cmake --install build --prefix <prefix>
```

## Прогресс
- ✅ клон + сабмодули (abseil, boringssl, libyuv, libsrtp, crc32c/…)
- ✅ configure (нашёл X-библиотеки; Crc32c — bundled, warning не критичен)
- ⏳ сборка — запущена, затем прервана пользователем

## CMake ждёт
`find_package(tg_owt REQUIRED)` → `tg_owt::tg_owt` (`cmake/external/webrtc/CMakeLists.txt:11`).

## Риски
- Очень долгая сборка, много RAM (может OOM при `-j$(nproc)`; снизить `-j`).

## Связанные заметки
- [[Внешние зависимости]]
- [[Исправления сборки]]
