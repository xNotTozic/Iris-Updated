#pragma once

class TextInput
{
public:
	static const char DarkBlue[4]; // dark colors
	static const char DarkGreen[4];
	static const char DarkAqua[4];
	static const char DarkRed[4];
	static const char DarkPurple[4];
	static const char DarkGray[4];

	static const char Black[4]; // colors
	static const char Gold[4];
	static const char Gray[4];
	static const char Blue[4];
	static const char Green[4];
	static const char Aqua[4];
	static const char Red[4];
	static const char Yellow[4];
	static const char White[4];

	static const char LightPurple[4]; // light colors

	static const char Obfuscated[4]; // extra formatting code
	static const char Bold[4];
	static const char StrikeThrough[4];
	static const char Underlined[4];
	static const char Italic[4];
	static const char Reset[4];
};

const char TextInput::Black[4] = "§0"; // numpad colors
const char TextInput::DarkBlue[4] = "§1";
const char TextInput::DarkGreen[4] = "§2";
const char TextInput::DarkAqua[4] = "§3";
const char TextInput::DarkRed[4] = "§4";
const char TextInput::DarkPurple[4] = "§5";
const char TextInput::Gold[4] = "§6";
const char TextInput::Gray[4] = "§7";
const char TextInput::DarkGray[4] = "§8";
const char TextInput::Blue[4] = "§9";

const char TextInput::Green[4] = "§a"; // text colors
const char TextInput::Aqua[4] = "§b";
const char TextInput::Red[4] = "§c";
const char TextInput::LightPurple[4] = "§d";
const char TextInput::Yellow[4] = "§e";
const char TextInput::White[4] = "§f";

const char TextInput::Obfuscated[4] = "§k"; // extra formatting code
const char TextInput::Bold[4] = "§l";
const char TextInput::StrikeThrough[4] = "§m";
const char TextInput::Underlined[4] = "§n";
const char TextInput::Italic[4] = "§o";
const char TextInput::Reset[4] = "§r";