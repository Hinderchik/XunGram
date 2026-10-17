/*
This file is part of XunGram,
a Telegram desktop client with an open plugin system.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "extra/host/manifest.h"

#include <QtCore/QByteArray>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonParseError>
#include <QtCore/QJsonValue>

namespace Extra::Host {
namespace {

[[nodiscard]] QString ReadString(const QJsonObject &object, const char *key) {
	return object.value(QLatin1String(key)).toString();
}

} // namespace

std::optional<Manifest> ParseManifest(
		const QString &directory,
		QString *error) {
	const auto manifestPath = directory + u"/manifest.json"_q;
	auto file = QFile(manifestPath);
	if (!file.open(QIODevice::ReadOnly)) {
		*error = u"cannot open "_q + manifestPath;
		return std::nullopt;
	}
	auto parseError = QJsonParseError();
	const auto document = QJsonDocument::fromJson(file.readAll(), &parseError);
	if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
		*error = u"invalid manifest.json"_q;
		return std::nullopt;
	}
	const auto object = document.object();
	auto result = Manifest();
	result.path = directory;
	result.id = ReadString(object, "id");
	result.name = ReadString(object, "name");
	result.version = ReadString(object, "version");
	result.apiVersion = object.value(u"api_version"_q).toInt();
	result.author = ReadString(object, "author");
	result.entry = ReadString(object, "entry");
	const auto permissions = object.value(u"permissions"_q).toArray();
	for (const auto &value : permissions) {
		result.permissions.push_back(value.toString());
	}
	if (result.id.isEmpty()) {
		*error = u"manifest.json has no id"_q;
		return std::nullopt;
	}
	if (result.apiVersion != kApiVersion) {
		*error = u"unsupported api_version "_q
			+ QString::number(result.apiVersion);
		return std::nullopt;
	}
	if (result.entry.isEmpty()) {
		result.entry = u"main.py"_q;
	}
	if (!QFileInfo::exists(directory + u"/"_q + result.entry)) {
		*error = u"entry not found: "_q + result.entry;
		return std::nullopt;
	}
	return result;
}

} // namespace Extra::Host
