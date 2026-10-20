# XunGram – Telegram Desktop Client with Plugin System

**XunGram** is a fork of [Telegram Desktop](https://desktop.telegram.org) with an open plugin architecture, allowing developers to extend the client with Python plugins.

Based on the [Telegram API](https://core.telegram.org) and [MTProto](https://core.telegram.org/mtproto) secure protocol.

![Build Status](https://github.com/Hinderchik/XunGram/actions/workflows/ci.yml/badge.svg)
![Version](https://badge.fury.io/gh/Hinderchik%2FXunGram.svg)

The source code is published under GPLv3 with OpenSSL exception.

## Features

- **Python Plugin System** — Load and manage plugins without recompilation
- **Plugin SDK** — Write plugins with a clean Python API
- **Settings Integration** — Plugins can add their own settings pages
- **Message Hooks** — Intercept and modify incoming/outgoing messages
- **Safe Mode** — Automatically disables broken plugins on crash
- **Built on Telegram Desktop** — All original Telegram features preserved

## Supported systems

* **Linux** (x86_64) — Built via GitHub Actions (Release artifact)

## Build instructions

### Linux (Docker)
```bash
git clone https://github.com/Hinderchik/XunGram.git --recursive
cd XunGram
./Telegram/build/docker/centos_env/build.sh -D CMAKE_CONFIGURATION_TYPES=Release -D TDESKTOP_API_TEST=ON
```

The binary will be at `out/Release/Telegram`.

## Plugin Development

See [SDK documentation](sdk/xungram/) and [examples](plugins/).

Quick start:
```bash
cd plugins
mkdir my_plugin
cat > my_plugin/manifest.json << 'EOF'
{
  "id": "com.example.my_plugin",
  "name": "My Plugin",
  "version": "1.0.0",
  "api_version": 1,
  "author": "you",
  "entry": "main.py",
  "permissions": ["messages.read"]
}
EOF
cat > my_plugin/main.py << 'EOF'
from xungram import BasePlugin, hooks

class MyPlugin(BasePlugin):
    @hooks.on_incoming_message
    def handle(self, message):
        if message.text == "hi":
            hooks.replace_text("hello 👋")
EOF
```
Then place in `~/.local/share/XunGram/plugins/my_plugin/`.

## Third-party licenses

Same as Telegram Desktop — see [LEGAL](LEGAL).

## Thanks

Based on [Telegram Desktop](https://github.com/telegramdesktop/tdesktop) by Telegram team.

---

*XunGram is an unofficial fork. Not affiliated with Telegram Messenger Inc.*