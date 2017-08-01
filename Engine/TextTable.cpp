//
//  TextTable.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/14/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "TextTable.h"


using namespace Core;

std::string TextTable::relativePath = "";

std::map<std::string, std::string> TextTable::text;
/* Load using the format
	Key
	Text Text Text Text
	Text Text Text Text
	EOK
	Key
	Text Text Text Text
	Text Text Text Text
	EOK
 */
void TextTable::loadFromFile(const std::string& path) {
	std::string loadPath;
	if (relativePath.size() > 0) {
		size_t lastIndex = path.find_last_of("/");
		if (lastIndex != std::string::npos) {
			//if path have the / on the end
			loadPath = path[path.size() - 1] == '/' ? relativePath + path.substr(lastIndex + 1) : relativePath + "/" + path.substr(lastIndex + 1);
		}
		else {
			loadPath = path[path.size() - 1] == '/' ? relativePath + path : relativePath + "/" + path;
		}
	}
	else {
		loadPath = path;
	}
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif
	std::ifstream file(loadPath);
	if (!file.is_open()) {
		throw std::runtime_error("[TextTable] Impossible to load file: " + loadPath);
	}
	std::string line;
	std::string key;
	std::stringstream text;
	int mode = 0;
	//Mode 0 = reading key
	//Mode 1 = reading text
	while (!file.eof()) {
		getline(file, line);
		if (mode == 0) {
			// Remove the : on the end of the key
			key = line.substr(0, line.length() - 1);
			mode = 1;
		}
		else if (mode == 1 && line != "EOK") {
			text << line;
		}
		else if (line == "EOK") {
			std::map<std::string, std::string>::iterator it;
			if ((it = TextTable::text.find(key)) != TextTable::text.end()) {
				it->second = text.str();
			}
			else {
				TextTable::text.insert(make_pair(key, text.str()));
			}
			text.str("");
			mode = 0;
		}
	}
}
std::string TextTable::getByKey(const std::string& key) {
	std::map<std::string, std::string>::iterator it;
	if (((it = TextTable::text.find(key)) != TextTable::text.end())) {
		return it->second;
	}
	throw std::runtime_error("[TextTable] Could not find the key: " + key);
}
bool TextTable::addKeyValue(const std::string& key, const std::string& value) {
	std::map<std::string, std::string>::iterator it;
	if (((it = TextTable::text.find(key)) != TextTable::text.end())) {
		return false;
	}
	TextTable::text.insert(make_pair(key, value));
	return true;
}
bool TextTable::updateKeyValue(const std::string& key, const std::string& value) {
	std::map<std::string, std::string>::iterator it;
	if (((it = TextTable::text.find(key)) != TextTable::text.end())) {
		it->second = value;
		return true;
	}
	return false;
}
bool TextTable::removeKey(const std::string& key) {
	std::map<std::string, std::string>::iterator it;
	if (((it = TextTable::text.find(key)) != TextTable::text.end())) {
		TextTable::text.erase(it);
		return true;
	}
	return false;

}
void TextTable::removeAll() {
	TextTable::text.clear();
}
std::map<std::string, std::string> TextTable::getAllKeyValues() {
	return text;
}