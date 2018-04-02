/*
 *  TextControl.cpp
 *  AFMac
 *
 *  Created by Alex Peixoto on 9/8/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "TextControl.h"

using namespace sf;
using namespace Core;
using std::cout;
using sf::RenderWindow;
RenderWindow* TextControl::window = nullptr;
std::string TextControl::relativePath = "";

TextControl::TextControl()
{
	font = new Font();
	fontScale.x = fontScale.y = .5f;
	textRender = new sf::Text();
	textRender->setFont(*font);
	word = std::vector<std::string>();
	line = std::vector<std::string>();
	screen = std::vector<std::pair<int, int>>();
	textSpacing = 0;
	if (Game::window != nullptr)
		TextControl::window = Game::window;

}
//Constructor delegation C++11
TextControl::TextControl(const std::string& path, const std::string& text) : TextControl::TextControl()
{
	std::string loadPath;
	if (relativePath.size() > 0) {
		size_t lastIndex = path.find_last_of("/");
		if (lastIndex != std::string::npos)
			//if path have the / on the end
			loadPath = path[path.size() - 1] == '/' ? relativePath + path.substr(lastIndex + 1) : relativePath + "/" + path.substr(lastIndex + 1);
		else
			loadPath = path[path.size() - 1] == '/' ? relativePath + path : relativePath + "/" + path;
	}
	else
		loadPath = path;
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif
	if (font != nullptr && !font->loadFromFile(loadPath)) {
		throw std::runtime_error("[TextControl] Could not load the file:" + loadPath);
	}
	else {
		textRender = new sf::Text(text, *font, 30);
		textRender->setScale(fontScale);
		this->text = text;
		fontPath = path;
	}
}
TextControl::~TextControl()
{
	if (textRender != nullptr) {
		delete textRender;
		textRender = nullptr;
	}

	if (font != nullptr) {
		delete font;
		font = nullptr;

	}
}
void TextControl::setWindow(RenderWindow *window) {
	TextControl::window = window;
}
void TextControl::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	textRender->setFillColor(sf::Color(r, g, b, a));
}
void TextControl::setColor(Color color) {
	textRender->setFillColor(color);
}
void TextControl::setScale(float scale) {
	fontScale.x = fontScale.y = scale;
	textRender->setScale(fontScale);
}
float TextControl::getScalef() const {
	return fontScale.x;
}
void TextControl::setScale(Vector2f scale) {
	fontScale = scale;
	textRender->setScale(fontScale);
}
Vector2f TextControl::getScale() const {
	return fontScale;
}
void TextControl::clearWords() {
	word.erase(word.begin(), word.end());
	word.clear();
}
void TextControl::clearLines() {
	line.erase(line.begin(), line.end());
	line.clear();
}
void TextControl::clearScreens() {
	screen.erase(screen.begin(), screen.end());
	screen.clear();
}
sf::Font* TextControl::getFont(const std::string& path) const {
	sf::Font* returnFont = new Font();
	if (returnFont->loadFromFile(path))
		return returnFont;
	else
		return nullptr;
}
void TextControl::setText(const std::string& text) {
	this->text = text;
	textRender->setString(text);
}
bool TextControl::setFont(const std::string& path) {
	//i load the font on another variable so i can keep rendering if i do the font change on a mulithread process.
	if (font != nullptr)
	{
		Font* font2 = new Font();
		if (font2 && font2->loadFromFile(path)) {
			delete font;
			font = font2;
			textRender->setFont(*font);
			return true;
		}
		else return false;
	}
	else {
		font = new Font();
		if (font->loadFromFile(path)) {
			textRender->setFont(*font);
			fontPath = path;
			return true;
		}
	}
	return true;

}
void TextControl::setSpacing(int spacing) {
	this->textSpacing = spacing;
}
int TextControl::getWidth(const std::string& text) const {
	sf::Text cs;
	cs.setFont(*font);
	cs.setString(text);
	return (int)(cs.getLocalBounds().width * fontScale.x);

}
int TextControl::getHeight(const std::string& text) const {
	sf::Text cs;
	cs.setFont(*this->font);
	cs.setString(text);
	return (int)(cs.getLocalBounds().height * fontScale.y);

}
void TextControl::splitInWords()
{
	size_t position = 0;
	while (text.size() > 0)
	{
		position = text.find(" ");

		if (position == std::string::npos) {
			position = text.find('\n');
		}
		if (position != std::string::npos)
		{
			word.push_back(text.substr(0, position + 1));
			text.erase(text.begin(), text.begin() + static_cast<int>(position + 1));
		}
		else if (text.size() != 0)
		{
			word.push_back(text);
			text = "";
			break;
		}
	}

}
void TextControl::splitInLines(int width)
{
	splitInWords();//delete words
	std::string tempLine = "";
	while (word.size() != 0)
	{
		if (getWidth(word.at(0)) > width) {
			clearWords();
			clearLines();
			clearScreens();
			throw std::domain_error("Your string is bigger than the size you defined");
		}

		//check if the word size is bigger than the screen size, if it is... return false STOP
		if (getWidth(tempLine + word.at(0)) <= width && word.at(0).find_first_of('\n') == std::string::npos)//check if actual status + next word < limit size
		{
			tempLine += word.at(0);
			word.erase(word.begin());
		}
		//The text is broken into lines on the screen, but its internal representation shows it as just one line
		else if (word.at(0).find_first_of('\n') != std::string::npos)
		{
			word.at(0).erase(word.at(0).find_first_of('\n'), 1);
			tempLine += word.at(0);
			word.erase(word.begin());
			line.push_back(tempLine);
			tempLine = "";
		}
		else if (getWidth(tempLine + word.at(0)) > width)
		{
			line.push_back(tempLine);
			tempLine = "";
		}
	}
	//if i removed the word and the size is zero i need to push the word on the line vector
	if (word.size() == 0 && getWidth(tempLine.c_str()) <= width)
	{
		line.push_back(tempLine);
	}
	clearWords();
}
void TextControl::splitInScreens(Vector2i size) {
	splitInScreens(size.x, size.y);
}
void TextControl::splitInScreens(int width, int height)
{
	clearLines();
	splitInLines(width);
	//Number of lines that fit in this screen
	int lineCount = 0;
	int start = 0;
	int end = 0;
	//Size in pixels, used to check if the total size is not bigger than the screen
	int size = 0;
	//Ussed to calculate the height of the text
	int tmpSize;
	while (lineCount != line.size())
	{
		tmpSize = getHeight(line.at(lineCount).c_str()) + textSpacing;
		//If there is just one line I create a screen.
		if (line.size() == 1) {
			screen.push_back(std::make_pair(0, 0));
			break;
		}
		//Check if adding the line to the screen will surpass the maximum height, if not, add 
		if ((size + tmpSize) < height)
		{
			size += tmpSize;
			++lineCount;
		}
		//This is the last line that can fit inside the screen
		else
		{
			end = lineCount;
			screen.push_back(std::make_pair(start, end));
			++lineCount;
			start = lineCount;
			size = 0;
		}

		//If this is the last line I will add it and break the loop
		if (size <= height && lineCount == line.size() - 1)
		{
			screen.push_back(std::make_pair(start, lineCount)); // if just one screen
			break;
		}
	}
}
void TextControl::renderScreen(int x, int y, size_t screen)
{
	if (screen <= this->screen.size())
	{
		int line = this->screen.at(screen).first;
		int limit = this->screen.at(screen).second;
		int _y = y;
		while (line <= limit){
			std::string utf8str = this->line.at(line);
			std::basic_string<sf::Uint32> utf32str;
			sf::Utf8::toUtf32(utf8str.begin(), utf8str.end(), std::back_inserter(utf32str));
			sf::String sfstr = utf32str;
			textRender->setString(sfstr);
			textRender->setPosition(static_cast<float>(x), static_cast<float>(_y));
			_y += getHeight(this->line.at(line)) + textSpacing;
			++line;
			if (TextControl::window != nullptr) {
				TextControl::window->draw(*textRender);
			}
		}
	}
}
void TextControl::renderScreen(Point2i position, size_t screen) {
	renderScreen(position.x, position.y, screen);
}
void TextControl::renderSimpleText(int x, int y, const std::string& text) {
	std::string utf8str = text;
	std::basic_string<sf::Uint32> utf32str;
	sf::Utf8::toUtf32(utf8str.begin(), utf8str.end(), std::back_inserter(utf32str));
	sf::String sfstr = utf32str;
	textRender->setString(sfstr);
	textRender->setPosition((float)x, (float)y);
	if (TextControl::window != nullptr)
		TextControl::window->draw(*textRender);
}
void TextControl::renderSimpleText(Point2i position, const std::string& text) {
	renderSimpleText(position.x, position.y, text);
}
size_t TextControl::getNumberOfScreens() const {
	return screen.size();
}
size_t TextControl::getNumberOfLines() const {
	return line.size();
}
size_t TextControl::getNumberOfWords() const {
	return word.size();
}
std::string TextControl::getText() const {
	return text;
}
std::vector<std::pair<int, int>> TextControl::getScreen() const {
	return screen;
}
std::vector<std::string> TextControl::getLine() const {
	return line;
}
std::vector<std::string> TextControl::getWord() const {
	return word;
}
std::string TextControl::getFontPath() const {
	return fontPath;
}