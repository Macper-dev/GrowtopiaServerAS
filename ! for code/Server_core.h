#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "enet/enet.h"
#include <cmath>
#include <string>
#include <windows.h>
#include <vector>
#include <ctime>
#include <time.h>
#include <sstream>
#include <chrono>
#include <fstream>
#include "json.hpp"
#include <conio.h>
#include <thread>
#include <experimental/filesystem>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <regex>
#include <filesystem>
#include <wininet.h>
#include <cstring>
#include <locale>
#include <iomanip> 
#include <stdexcept>
#pragma warning(disable:4996)
using namespace std;
using json = nlohmann::json;
#define REGISTRATION
int configPort = 17091;
ENetHost* server;
int cId = 1;
BYTE* itemsDat = 0;
int itemsDatSize = 0;
int resultnbr1 = 0;
int resultnbr2 = 0;
int hasil = 0;
int prize = 0;
bool serverIsFrozen = false;
bool usedgenworld = false;
bool useduranusblast = false;
int genwidth = 0;
int genheight = 0;
int genforeground = 0;
int genbedrock = 0;
int genbackground = 0;
long long int quest = 0;
bool restartForUpdate = false;
long long int restartTime = 0;
unsigned short tipqueue = 0;
bool worldproperlock;
int serverhash;
int serverversion;
int serverport;
string music = "";
int serverrolecount;
enum LabelStyles {
	LABEL_BIG,
	LABEL_SMALL
};
enum SpacerTypes
{
	SPACER_BIG,
	SPACER_SMALL
};
enum CheckboxTypes
{
	CHECKBOX_SELECTED,
	CHECKBOX_NOT_SELECTED
};
void  toUpperCase(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}
template<typename T>
void Remove(std::basic_string<T>& Str, const T* CharsToRemove)
{
	std::basic_string<T>::size_type pos = 0;
	while ((pos = Str.find_first_of(CharsToRemove, pos)) != std::basic_string<T>::npos)
	{
		Str.erase(pos, 1);
	}
}
string ReadAllFile(const string& fileName)
{
	ifstream f(fileName);
	stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y/%m/%d %X", &tstruct);
	return buf;
}
void sendData(ENetPeer* peer, int num, char* data, int len)
{
	ENetPacket* packet = enet_packet_create(0,
		len + 5,
		ENET_PACKET_FLAG_RELIABLE);
	memcpy(packet->data, &num, 4);
	if (data != NULL)
	{
		memcpy(packet->data + 2, data, len);
	}
	char zero = 0;
	memcpy(packet->data + 2 + len, &zero, 1);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(server);
}
int getPacketId(char* data)
{
	return *data;
}
char* getPacketData(char* data)
{
	return data + 4;
}
string text_encode(char* text)
{
	string ret = "";
	while (text[0] != 0)
	{
		switch (text[0])
		{
		case '\n':
			ret += "\\n";
			break;
		case '\t':
			ret += "\\t";
			break;
		case '\b':
			ret += "\\b";
			break;
		case '\\':
			ret += "\\\\";
			break;
		case '\r':
			ret += "\\r";
			break;
		default:
			ret += text[0];
			break;
		}
		text++;
	}
	return ret;
}
int ch2n(char x)
{
	switch (x)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	default:
		break;
	}
}
char* GetTextPointerFromPacket(ENetPacket* packet)
{
	char zero = 0;
	memcpy(packet->data + packet->dataLength - 1, &zero, 1);
	return (char*)(packet->data + 4);
}
BYTE* GetStructPointerFromTankPacket(ENetPacket* packet)
{
	unsigned int packetLenght = packet->dataLength;
	BYTE* result = NULL;
	if (packetLenght >= 0x3C)
	{
		BYTE* packetData = packet->data;
		result = packetData + 4;
		if (*(BYTE*)(packetData + 16) & 8)
		{
			if (packetLenght < *(int*)(packetData + 56) + 60)
			{
				cout << "Packet too small for extended packet to be valid" << endl;
				cout << "Sizeof float is 4.  TankUpdatePacket size: 56" << endl;
				result = 0;
			}
		}
		else
		{
			int zero = 0;
			memcpy(packetData + 56, &zero, 4);
		}
	}
	return result;
}
int GetMessageTypeFromPacket(ENetPacket* packet)
{
	int result;
	if (packet->dataLength > 3u)
	{
		result = *(packet->data);
	}
	else
	{
		cout << "Bad packet length, ignoring message" << endl;
		result = 0;
	}
	return result;
}
vector<string> explode(const string& delimiter, const string& str)
{
	vector<string> arr;
	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return arr;
	int i = 0;
	int k = 0;
	while (i < strleng)
	{
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng)
		{
			arr.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else
		{
			i++;
		}
	}
	arr.push_back(str.substr(k, i - k));
	return arr;
}
string getStrLower(string txt) {
	string ret;
	for (char c : txt) ret += tolower(c);
	return ret;
}
string getStrUpper(string txt) {
	string ret;
	for (char c : txt) ret += toupper(c);
	return ret;
}
bool has_only_digits(const string s) {
	return s.find_first_not_of("0123456789") == string::npos;
}
bool has_only_digits_wnegative(const string s) {
	return s.find_first_not_of("-0123456789") == string::npos;
}
static inline void ltrim(string& s)
{
	s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
		return !isspace(ch);
		}));
}
static inline void rtrim(string& s)
{
	s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
		return !isspace(ch);
		}).base(), s.end());
}
static inline void trim(string& s)
{
	ltrim(s);
	rtrim(s);
}
static inline string trimString(string s)
{
	trim(s);
	return s;
}
int countSpaces(string& str)
{
	int count = 0;
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		int c = str[i];
		if (isspace(c))
			count++;
	}
	return count;
}
void loadConfig()
{

	cout << "[!] loading config" << endl;
	std::ifstream ifs("configp.json");
	if (ifs.is_open()) {


		json j;
		ifs >> j;

		configPort = j["Port"];

		music = j["Music"].get<string>();

		cout << "[~] Config loaded." << endl;
		cout << "[-] Hosting on Port: " << configPort << endl;
		cout << "[!] Music theme: " << music << endl;




	}




	ifs.close();
	// finished
}
void removeExtraSpaces(string& str)
{
	int n = str.length();
	int i = 0, j = -1;
	bool spaceFound = false;
	while (++j < n && str[j] == ' ');
	while (j < n)
	{
		if (str[j] != ' ')
		{
			if ((str[j] == '.' || str[j] == ',' ||
				str[j] == '?') && i - 1 >= 0 &&
				str[i - 1] == ' ')
				str[i - 1] = str[j++];
			else
				str[i++] = str[j++];
			spaceFound = false;
		}
		else if (str[j++] == ' ')
		{
			if (!spaceFound)
			{
				str[i++] = ' ';
				spaceFound = true;
			}
		}
	}
	if (i <= 1)
		str.erase(str.begin() + i, str.end());
	else
		str.erase(str.begin() + i, str.end());
}
std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}
uint32_t HashString(unsigned char* str, int len)
{
	if (!str) return 0;
	unsigned char* n = (unsigned char*)str;
	uint32_t acc = 0x55555555;
	if (len == 0)
	{
		while (*n)
			acc = (acc >> 27) + (acc << 5) + *n++;
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			acc = (acc >> 27) + (acc << 5) + *n++;
		}
	}
	return acc;
}
unsigned char* getA(string fileName, int* pSizeOut, bool bAddBasePath, bool bAutoDecompress)
{
	unsigned char* pData = NULL;
	FILE* fp = fopen(fileName.c_str(), "rb");
	if (!fp)
	{
		cout << "File not found" << endl;
		if (!fp) return NULL;
	}
	fseek(fp, 0, SEEK_END);
	*pSizeOut = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	pData = (unsigned char*)new unsigned char[((*pSizeOut) + 1)];
	if (!pData)
	{
		printf("Out of memory opening %s?", fileName.c_str());
		return 0;
	}
	pData[*pSizeOut] = 0;
	fread(pData, *pSizeOut, 1, fp);
	fclose(fp);
	return pData;
}
void logtofile(string log) {
	fstream logfile;
	ofstream createfile;

	logfile.open("logpacket.txt", std::ios_base::app);

	if (logfile.fail()) {
		createfile.open("logpacket.txt");
	}
	logfile << log + "\n";
}
std::string hexStr(BYTE* data, int len)
{
	std::stringstream ss;
	ss << std::hex;
	for (int i(0); i < len; ++i)
	{
		ss << std::hex << std::setfill('0');
		ss << std::setw(2) << static_cast<int>(data[i]);
	}
	return ss.str();
}
class GTDialog
{
public:
	string dialogstr = "";
	void addSpacer(SpacerTypes type);
	void addLabelWithIcon(string text, int tileid, LabelStyles type);
	void addButton(string buttonname, string buttontext);
	void addPicker(string pickername, string pickertext, string headText);
	void addCheckbox(string checkboxname, string string, CheckboxTypes type);
	void addTextBox(string str);
	void addSmallText(string str);
	void addItemWithCustomText(string itemID, string textUnderButton, string buttonName);
	void addStaticBlueFrame(string itemID, string textUnderFrame, string buttonName, bool isEndLine);
	void addNewLineAfterFrame();
	void addInputBox(string name, string text, string cont, int size);
	void addQuickExit();
	void endDialog(string name, string accept, string nvm);
	void addCustom(string name);
	string finishDialog();
	operator string() {
		return this->dialogstr;
	}
};
void GTDialog::addSpacer(SpacerTypes type) {
	switch (type)
	{
	case SPACER_BIG:
		this->dialogstr.append("add_spacer|big|\n");
		break;
	case SPACER_SMALL:
		this->dialogstr.append("add_spacer|small|\n");
		break;
	default:
		break;
	}
}
void GTDialog::addStaticBlueFrame(string itemID, string textUnderFrame, string buttonName, bool isEndLine)
{
	if (isEndLine == false)
	{
		this->dialogstr.append("\nadd_button_with_icon|"+ buttonName +"||staticBlueFrame|" + itemID + "|" + textUnderFrame + "|");
	}
	else
	{
		this->dialogstr.append("\nadd_button_with_icon||END_LIST|noflags|0|0|\nadd_button_with_icon|"+ buttonName +"||staticBlueFrame|" + itemID + "|" + textUnderFrame + "|");
	}
	
}
void GTDialog::addItemWithCustomText(string itemID, string textUnderButton, string buttonName)
{
	//this->dialogstr.append("\nadd_button_with_icon|" + buttonName + "|"+ textUnderButton +"|left|" + itemID + "|");
	this->dialogstr.append("\nadd_button_with_icon|"+ buttonName +"|" + textUnderButton + "|staticBlueFrame|"+ itemID +"|\nadd_button_with_icon||END_LIST|noflags|0|0|");
}
void GTDialog::addNewLineAfterFrame()
{
	this->dialogstr.append("\nadd_button_with_icon||END_LIST|noflags|0|0|");
}
void GTDialog::addLabelWithIcon(string text, int tileid, LabelStyles type) {
	switch (type)
	{
	case LABEL_BIG:
		this->dialogstr.append("add_label_with_icon|big|" + text + "|left|" + to_string(tileid) + "|\n");
		break;
	case LABEL_SMALL:
		this->dialogstr.append("add_label_with_icon|small|" + text + "|left|" + to_string(tileid) + "|\n");
		break;
	default:
		break;
	}
}
void GTDialog::addButton(string buttonname, string buttontext) {
	this->dialogstr.append("add_button|" + buttonname + "|" + buttontext + "|noflags|0|0|\n");
}
void GTDialog::addPicker(string pickername, string pickertext, string headText)
{
	this->dialogstr.append("\nadd_item_picker|" + pickername + "|" + pickertext + "|"+ headText +"|");
}
void GTDialog::addCheckbox(string checkboxname, string string, CheckboxTypes type) {
	switch (type)
	{
	case CHECKBOX_SELECTED:
		this->dialogstr.append("add_checkbox|" + checkboxname + "|" + string + "|1|\n");
		break;
	case CHECKBOX_NOT_SELECTED:
		this->dialogstr.append("add_checkbox|" + checkboxname + "|" + string + "|0|\n");
		break;
	default:
		break;
	}
}
void GTDialog::addTextBox(string str) {
	this->dialogstr.append("add_textbox|" + str + "|left|\n");
}
void GTDialog::addSmallText(string str) {
	this->dialogstr.append("add_smalltext|" + str + "|\n");
}
void GTDialog::addInputBox(string name, string text, string cont, int size) {
	this->dialogstr.append("add_text_input|" + name + "|" + text + "|" + cont + "|" + to_string(size) + "|\n");
}
void GTDialog::addQuickExit() {
	this->dialogstr.append("add_quick_exit|\n");
}
void GTDialog::endDialog(string name, string accept, string nvm) {
	this->dialogstr.append("end_dialog|" + name + "|" + nvm + "|" + accept + "|\n");
}
void GTDialog::addCustom(string name) {
	this->dialogstr.append(name + "\n");
}
string GTDialog::finishDialog() {
	return this->dialogstr;
}