/*
This file is part of XunGram,
a Telegram desktop client with an open plugin system.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "extra/extra.h"

#include "extra/host/engine.h"

namespace Extra {

void Initialize() {
	static auto engine = Host::Engine();
	engine.initialize();
}

} // namespace Extra
