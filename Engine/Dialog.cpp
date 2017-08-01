//
//  Dialog.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Dialog.h"

using namespace Adventure;

sf::RenderWindow* Dialog::window = nullptr;

Dialog::Dialog(const std::string& font) {
	textControl = new Core::TextControl(font);
	textHeight = textControl->getHeight("QWERTYUIOPASDFGHJKLZXCVBNM1234567890_+{}|-=[]:;<>?,./!@#$%ˆ&*()~");

	textControl->setScale(.5);
	textControl->setSpacing(5);
	speechIndex = speechScreenIndex = questionIndex = optionIndex = 0;
	speechInnerBorder = optionInnerBorder = 0;
	renderingQuestion = optionBoxByLargest = false;
	speechColor = questionColor = optionColor = Color(100, 100, 100, 255);
	textControl->setText("");
	dialogBoxSize = questionBoxSize = sf::Vector2i(-1, -1);
}
Dialog::~Dialog() {
	delete textControl;
	textControl = nullptr;
}

std::vector<Dialog::Question>::iterator Dialog::getQuestion(int id) const {
	std::vector<Question>::iterator i;
	//If it finds an id it breaks the loop
	for (i = questions.begin(); i != questions.end() && (*i).id != id; ++i);

	return i;
}

bool Dialog::addQuestion(int id, const std::string& title, std::function<void(int, int, int, Dialog*)> func) {
	if (getQuestion(id) != questions.end())
		return false;
	questions.push_back({ id, title, func, {}, -1 });
	return true;
}
bool Dialog::removeQuestion(int id) {
	std::vector<Question>::iterator i;
	//return the iterator of the Id
	if ((i = getQuestion(id)) == questions.end())
		return false;
	questions.erase(i);
	return true;

}
bool Dialog::addOption(int questionId, int id, const std::string& option) {

	std::vector<Question>::iterator i = getQuestion(questionId);

	//If i did not found the question
	if (i == questions.end()) {
		std::stringstream ss;
		ss << "[Dialog] Question with id: " << questionId << " does not exists" << std::endl;
		throw std::runtime_error(ss.str());
	}

	for (auto option : (*i).options)
		if (option.id == id)
			return false;

	i->options.push_back({ id, option });
	i->widestSize = getWidestOptionSize(i->options);
	if (i->widestSize < textControl->getWidth(i->title))
		i->widestSize = textControl->getWidth(i->title);

	return true;
}
bool Dialog::removeOption(int questionId, int id) {
	std::vector<Question>::iterator i = getQuestion(id);

	//If i did not found the question
	if (i == questions.end()) {
		std::stringstream ss;
		ss << "[Dialog] Question with id: " << id << " does not exists" << std::endl;
		throw std::runtime_error(ss.str());
	}

	for (auto _i = (*i).options.begin(); _i != (*i).options.end(); _i++) {
		if ((*_i).id == id) {
			i->options.erase(_i);
			return true;
		}
	}

	return false;
}
bool Dialog::prevOption() {
	if (optionIndex > 0) {
		--optionIndex;
		return true;
	}
	return false;
}
bool Dialog::nextOption() {
	if (optionIndex + 1 < questions.at(questionIndex).options.size()) {
		++optionIndex;
		return true;
	}
	return false;
}
bool Dialog::addDialogHandle(DialogHandle dh) {
	//tq => Text - Question
	for (auto tq : dialogToQuestion) {
		if (tq.speechId == dh.speechId) {
			return false;
		}
	}
	dialogToQuestion.push_back(dh);
	return true;

}
bool Dialog::addDialogHandle(int speechId, int questionIndex) {
	for (auto tq : dialogToQuestion) {
		if (tq.speechId == speechId) {
			return false;
		}
	}
	dialogToQuestion.push_back({ speechId, questionIndex });
	return true;
}

void Dialog::removeDialogHandle(int id) {
	for (auto i = dialogToQuestion.begin(); i != dialogToQuestion.end(); i++) {
		if ((*i).speechId == id) {
			dialogToQuestion.erase(i);
		}
	}
}
void Dialog::renderSpeech() {
	if (dialogBoxSize.x < 0 || dialogBoxSize.y < 0) {
		throw std::runtime_error("[Dialog] Invalid dialogBoxSize");
	}
	if (speechBoxShape != nullptr) {
		speechBoxShape->setPosition(dialogBoxPosition);
		speechBoxShape->setSize(dialogBoxSize);
		speechBoxShape->render();
	}
	textControl->setColor(speechColor);
	textControl->renderScreen(dialogBoxPosition.x + speechInnerBorder, dialogBoxPosition.y + speechInnerBorder, speechScreenIndex);
}
bool Dialog::gotoSpeech(int id) {
	for (int x = 0; x < speeches.size(); x++) {
		if (speeches.at(x).id == id) {
			speechIndex = x;
			textControl->setText(speeches.at(speechIndex).speech);
			textControl->clearScreens();
			textControl->splitInScreens(dialogBoxSize);
			speechScreenIndex = 0;
			return true;
		}
	}

	return false;
}
bool Dialog::nextSpeech() {
	if (renderingQuestion) {
		return false;
	}
	if (speechScreenIndex < textControl->getNumberOfScreens() - 1) {
		speechScreenIndex++;
		return true;
	}
	//If i need to finish the speech on that text
	else if (speeches.at(speechIndex).isEnd == true) {
		return false;
	}
	//If i need to change the speech i set the new text
	//Split it
	//Reset the index
	else if (speechIndex < speeches.size() - 1) {
		++speechIndex;
		textControl->clearScreens();
		textControl->setText(speeches.at(speechIndex).speech);
		textControl->splitInScreens(dialogBoxSize);
		speechScreenIndex = 0;
		return true;
	}
	return false;
}
bool Dialog::prevSpeech() {
	if (renderingQuestion) {
		return false;
	}
	if (speechScreenIndex > 0) {
		--speechScreenIndex;
		return true;
	}
	else if (speechIndex > 0) {
		--speechIndex;
		textControl->setText(speeches.at(speechIndex).speech);
		textControl->clearScreens();
		textControl->splitInScreens(dialogBoxSize);
		speechScreenIndex = textControl->getNumberOfScreens() - 1;
		return true;
	}

	return false;
}
int Dialog::getSpeechId() const {
	return speechIndex >= speeches.size() ? -1 : speeches.at(speechIndex).id;
}
bool Dialog::haveQuestion() {
	for (auto &dtq : dialogToQuestion) {
		if (dtq.speechId == speeches.at(speechIndex).id) {
			return true;
		}
	}
	return false;
}
int Dialog::getQuestionId() const {
	return questionIndex >= questions.size() ? -1 : questions.at(questionIndex).id;
}
void Dialog::renderQuestion() {
	std::vector<Option> options = questions.at(questionIndex).options;

	//Every letter have the same size
	int optionsPerScreen = questionBoxSize.y / textHeight;

	if (questionBoxSize.x < 0 || questionBoxSize.y < 0) {
		throw std::runtime_error("[Dialog] Invalid questionBoxSize");
	}
	if (optionsPerScreen == 0) {
		throw std::runtime_error("[Dialog] questionBoxSize is too small, cannot even render one option");
	}

	if (questionBoxShape != nullptr) {
		questionBoxShape->setPosition(Point2i(questionBoxPosition.x + 2, questionBoxPosition.y + 2));
		if (optionBoxByLargest) {
			questionBoxShape->setSize(questions.at(questionIndex).widestSize + optionInnerBorder + 4 + optionInnerBorder * 2 /*Each side of the option*/, questionBoxSize.y + 4 + optionInnerBorder * 2 * optionsPerScreen /* top and down of the option + number of the options on the screen*/);
		}
		else {
			questionBoxShape->setSize(Vector2i(questionBoxSize.x + 4 + optionInnerBorder * 2, questionBoxSize.y + 4 + optionInnerBorder * 2 * optionsPerScreen));
		}
		questionBoxShape->render();
	}
	textControl->setColor(questionColor);
	textControl->renderSimpleText(questionBoxPosition.x + 2, questionBoxPosition.y, questions.at(questionIndex).title);

	//Calculate what options i need to render
	// Calculated using the height so i round down.
	int initOption = (optionIndex / (optionsPerScreen - 1)*(optionsPerScreen - 1));
	//The initial position is
	//questionBoxPosition.y <= the position i set to the questio box +
	//textControl->returnHeight(questions.at(questionIndex).title <= the height of the text +
	//optionInnerBorder*2 <= the optionBorder times 2 because the subsequent options have the top border + bottom border of the previous element
	int y = questionBoxPosition.y + textControl->getHeight(questions.at(questionIndex).title) + optionInnerBorder * 2;

	//optionsPerScreen-1 because it is (zero indexed)
	for (size_t option = initOption; option < initOption + (optionsPerScreen - 1) && option < options.size(); option++) {
		if (optionIndex == option)
			if (optionShape != nullptr) {
				//The index option -
				//(Integer) option divided by number of screens
				// Multiplied by number of screens +
				// _y
				//Example:
				// 3 per screen
				// I am at index 7
				// 7/3
				optionShape->setPosition(questionBoxPosition.x + optionInnerBorder, y);
				if (optionBoxByLargest)
					optionShape->setSize(questions.at(questionIndex).widestSize + optionInnerBorder + 4 + optionInnerBorder /*Each side of the option*/, textHeight + optionInnerBorder * 2 /* top and down of the option + number of the options on the screen*/);
				else
					optionShape->setSize(questionBoxSize.x - 4 - optionInnerBorder * 2, textHeight + optionInnerBorder);
				optionShape->render();
			}
		textControl->setColor(optionColor);
		textControl->renderSimpleText(questionBoxPosition.x + optionInnerBorder, y, options.at(option).text);
		y += textHeight + optionInnerBorder * 2;
	}

}
void Dialog::selectOption() {
	questions.at(questionIndex).func(speeches.at(speechIndex).id,
		questions.at(questionIndex).id,
		questions.at(questionIndex).options.at(optionIndex).id
		, this);
}
int Dialog::getOptionId() const {
	if (questionIndex >= questions.size() || optionIndex >= questions.at(questionIndex).options.size()) {
		return -1;
	}
	return questions.at(questionIndex).options.at(optionIndex).id;
}
void Dialog::setSpeechBoxShape(BackgroundShape* speechBoxShape) {
	this->speechBoxShape = speechBoxShape;
}
BackgroundShape* Dialog::getSpeechBoxShape() {
	return speechBoxShape;
}

void Dialog::setQuestionBoxShape(BackgroundShape* questionBoxShape) {
	this->questionBoxShape = questionBoxShape;
}
BackgroundShape* Dialog::getQuestionBoxShape() const {
	return questionBoxShape;
}

void Dialog::setOptionShape(BackgroundShape* optionShape) {
	this->optionShape = optionShape;
}
BackgroundShape* Dialog::getOptionShape() const {
	return optionShape;
}

void Dialog::setFontScale(float scale) {
	textControl->setScale(scale);
}
float Dialog::getFontScale() const {
	return textControl->getScalef();
}

void Dialog::setQuestionBoxByLargest(bool largest) {
	optionBoxByLargest = largest;
}
bool Dialog::getQuestionBoxByLargest() const {
	return optionBoxByLargest;
}
void Dialog::setWindow(sf::RenderWindow *window) {
	Dialog::window = window;
}
bool Dialog::addSpeech(Speech speech) {
	for (auto s : speeches) {
		if (s.id == speech.id) {
			return false;
		}
	}
	speeches.push_back(speech);
	sort(speeches.begin(), speeches.end(), [](const Dialog::Speech& s1, const Dialog::Speech& s2) -> bool {return (s1.id < s2.id); });
	textControl->setText(speeches.at(0).speech);
	textControl->clearScreens();
	textControl->splitInScreens(dialogBoxSize);
	return true;
}
bool Dialog::addSpeech(int id, const std::string& speech, bool isEnd) {
	return addSpeech(Speech{ id, speech, isEnd });
}
bool Dialog::removeSpeech(int id) {
	for (auto i = speeches.begin(); i != speeches.end(); i++) {
		if (i->id == id) {
			speeches.erase(i);
			return true;
		}
	}
	return false;
}
Dialog::Speech Dialog::getSpeech(int id) const {
	for (auto s : speeches) {
		if (s.id == id) {
			return s;
		}
	}
	return Speech({ -1, "" });
}

void Dialog::setDialogBoxSize(Vector2i size) {
	dialogBoxSize = size;
}
void Dialog::setDialogBoxSize(int width, int height) {
	dialogBoxSize = sf::Vector2i(width, height);
}

int Dialog::getDialogBoxWidth() const {
	return dialogBoxSize.x;
}
int Dialog::getDialogBoxHeight() const {
	return dialogBoxSize.y;
}
Vector2i Dialog::getDialogBoxSize() const {
	return dialogBoxSize;
}

void Dialog::setDialogBoxPosition(Point2i position) {
	dialogBoxPosition = position;
}
void Dialog::setDialogBoxPositon(int x, int y) {
	dialogBoxPosition = Point2i(x, y);
}

int Dialog::getDialogBoxX() const {
	return dialogBoxPosition.x;
}
int Dialog::getDialogBoxY() const {
	return dialogBoxPosition.y;
}
Point2i Dialog::getDialogBoxPosition() const {
	return dialogBoxPosition;
}

void Dialog::setQuestionBoxSize(Vector2i size) {
	questionBoxSize = size;
}
void Dialog::setQuestionBoxSize(int width, int height) {
	questionBoxSize = sf::Vector2i(width, height);
}

int Dialog::getQuestionBoxWidth() const {
	return questionBoxSize.x;
}
int Dialog::getQuestionBoxHeight() const {
	return questionBoxSize.y;
}
Vector2i Dialog::getQuestionBoxSize() const {
	return questionBoxSize;
}

void Dialog::setQuestionBoxPosition(Point2i position) {
	questionBoxPosition = position;
}
void Dialog::setQuestionBoxPositon(int x, int y) {
	questionBoxPosition = Point2i(x, y);
}

int Dialog::getQuestionBoxX() const {
	return questionBoxPosition.x;
}
int Dialog::getQuestionBoxY() const {
	return questionBoxPosition.y;
}
Point2i Dialog::getQuestionBoxPosition() const {
	return questionBoxPosition;
}
void Dialog::setSpeechInnerBorder(int speechInnerBorder) {
	this->speechInnerBorder = speechInnerBorder;
}
int Dialog::getSpeechInnerBorder() const {
	return speechInnerBorder;
}
void Dialog::setOptionInnerBorder(int optionInnerBorder) {
	this->optionInnerBorder = optionInnerBorder;
}
int Dialog::getOptionInnerBorder() const {
	return optionInnerBorder;
}

void Dialog::setSpeechColor(Color speechColor) {
	this->speechColor = speechColor;
}
void Dialog::setSpeechColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	speechColor = Color(r, g, b, a);
}
Color Dialog::getSpeechColor() const {
	return speechColor;
}
void Dialog::setQuestionColor(Color questionColor) {
	this->questionColor = questionColor;
}
void Dialog::setQuestionColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	questionColor = Color(r, g, b, a);
}
Color Dialog::getQuestionColor() const {
	return questionColor;
}

void Dialog::setOptionColor(Color optionColor) {
	this->optionColor = optionColor;
}
void Dialog::setOptionColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	optionColor = Color(r, g, b, a);
}
Color Dialog::getOptionColor() const {
	return optionColor;
}
int Dialog::getWidestOptionSize(std::vector<Option> options) const {
	if (options.empty()) {
		return 0;
	}
	std::vector<Option>::const_iterator ci = std::max_element(options.begin(), options.end(), [&](const Option& lhs, const Option& rhs)
	{return textControl->getWidth(lhs.text) < textControl->getWidth(rhs.text); });

	return textControl->getWidth(ci->text);
}
void Dialog::setRenderingQuestion(bool renderingQuestion) {
	this->renderingQuestion = renderingQuestion;
}
bool Dialog::getRenderingQuestion() const {
	return renderingQuestion;
}
