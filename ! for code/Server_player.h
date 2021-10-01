#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "enet/enet.h"
#include "Server_core.h"
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
#include "bcrypt.h"
#include "crypt_blowfish/crypt_gensalt.c"
#include "crypt_blowfish/crypt_blowfish.h"
#include "crypt_blowfish/crypt_blowfish.c"
#include "crypt_blowfish/wrapper.c"
#include "bcrypt.c"
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
#include <stdexcept>
using namespace std;
using json = nlohmann::json;
int maxItems = 10015;
int eventgem = 5;
int coredatasize = 0;
ENetPeer* currentPeer;
#define cloth0 cloth_hair
#define cloth1 cloth_shirt
#define cloth2 cloth_pants
#define cloth3 cloth_feet
#define cloth4 cloth_face
#define cloth5 cloth_hand
#define cloth6 cloth_back
#define cloth7 cloth_mask
#define cloth8 cloth_necklace
#define cloth9 cloth_ances
#define STRINT(x, y) (*(int*)(&(x)[(y)]))
#define STR16(x, y) (*(uint16_t*)(&(x)[(y)]))
vector<string>guildmem;
vector<string>guildelder;
vector<string>guildco;
struct RankupInfo {
	string nextlvlName = "";
	int nextRankId = 0;
	int gems = 0;
	int amber = 0;
	int opal = 0;
	int gold = 0;
	int ruby = 0;
	int sapphire = 0;
	int diamond = 0;
	int emerald = 0;
};
struct InventoryItem {
	__int16 itemID;
	int itemCount;
};
struct PlayerInventory {
	vector<InventoryItem> items;
};
struct PlayerInfo {
	string lastTradeItems1 = "";
	bool BePlayer = false;
	string zf = "";
	bool isCrasher = true;
	bool evadeRID = false;
	int wrenchedBlockLocation = -1;
	bool isBot = true;
	int lastTradeItem;
	int LastTradeItem1;
	int lastTradeNetID = 0;
	int lastTradeAcceptCount;
	int isDoTrade;
	int lastCT1;
	int lastCT2;
	int lastCT3;
	int lastCT4;
	int isTradingWithUser;
	int lastTD1;
	int lastTD2;
	int lastTD3;
	int lastTD4;
	bool isDr = false;
	bool firstspamwarning = false;
	bool secondspamwarning = false;
	bool thirdspamwarning = false;
	//road to glory
	bool RoadtoGlory = false;
	//achievements
	bool achi = false;
	bool achi1 = false;
	bool achi2 = false;
	bool achi3 = false;
	bool achi4 = false;
	bool ding = false;
	//hair dyes
	int dyecolor = 0;
	int eyecolor = 0;
	int eyecolor2 = 0;
	//Premium tokens TOKEN
	int gtnewtokens = 0;
	int pmod;
	int pvip;
	bool passedname = false;
	bool passedheight = false;
	bool passedwidth = false;
	bool passedbackground = false;
	bool passedforeground = false;
	bool passedbedrock = false;
	bool isCreator = false;
	bool isDisableMessages = false;
	bool isDoTheTrade = false;
	// hp system
	int lastPVPcoord = 0;
	int lastPVPcoord2 = 0;
	int lastPVPcoord3 = 0;
	int lastPVPcoord4 = 0;
	int lastPVPcoord5 = 0;
	int lastPVPcoord6 = 0;
	int lastPVPcoord7 = 0;
	int health = 100;
	int totalKills = 0;
	int score = 0;
	// end hp

	int displayfg = 0;
	int displaybg = 0;
	int displaypunchx = 0;
	int displaypunchy = 0;
	/*ItemSuckers*/
	int magplantitemid = 0;
	int magplantx = 0;
	int magplanty = 0;
	string suckername = "";
	int suckerid = 0;
	//role stats
	int firefighterlevel = 0;
	int firefighterxp = 0;
	int providerlevel = 0;
	int providerxp = 0;
	int fishermanlevel = 0;
	int fishermanxp = 0;
	int geigerlevel = 0;
	int geigerxp = 0;
	//trade
	bool istrading = false;
	int item1 = 0;
	int item1count = 0;
	int item2 = 0;
	int item2count = 0;
	int item3 = 0;
	int item3count = 0;
	int item4 = 0;
	int item4count = 0;
	bool accepted = false;
	string tradingme = "";
	bool dotrade = false;
	//end trade
	int lastsavemyworld = 0;
	int lastdailyGems = 0;
	int packetinsec = 0;
	long long int packetsec = 0;
	int timeTogetToken = 0;
	int trashgemmeritem = 0;
	int eikiscia = 0;
	int wrenchx;
	bool chatnotifications = false;
	int wrenchy;
	RankupInfo rankupInfo;
	long long int lastSPIN = 0;
	int droppeditemcount = 0;
	int lastdroppeditemid = 0;
	int lastPunchX;
	int lastPunchY;
	bool isInWorld = false;
	bool isBannedWait = false;
	bool usedCP = false;
	bool tradeSomeone = false;
	string trdStarter = "";
	string skill = "None";
	string sid = "none";
	bool isIn = false;
	int netID;
	string Chatname = "";
	int lastdropitemcount = 0;
	int lastdropitem = 0;
	int lasttrashitem = 0;
	int lasttrashitemcount = 0;

	long long int lastwarn = 0;
	int lastwarnCount = 0;
	long long int lastcurse = 0;
	int lastcurseCount = 0;
	long long int lastban = 0;
	int lastbanCount = 0;
	long long int lastdelete = 0;
	int lastdeleteCount = 0;
	long long int lastbanip = 0;
	int lastbanipCount = 0;
	long long int lastdelstatus = 0;
	int lastdelstatusCount = 0;

	int wrenchsession;
	int bitShiftTest = 0;
	bool canLeave = true;
	bool haveGrowId = false;
	bool haveGuestId = false;
	bool isSpinSetByCreator = false;
	int	spinSetByCreatorValue = 2;
	int valgem;
	int fEarth = 0;
	int fDark = 0;
	int plantgems = 0;
	int fFire = 0;
	int lavaLevel = 0;
	bool RotatedLeft = false;
	int fWater = 0;
	bool isRotatedLeft = false;
	string tankIDName = "";
	string tankIDPass = "";
	string requestedName = "";
	string rawName = "";
	string playerinfo = "";
	bool isAAP = false;
	int warns = 0;
	int bans = 0;
	int rubblexp = 0;
	int rubble = 0;
	int amberxp = 0;
	int amber = 0;
	int opalxp = 0;
	int opal = 0;
	int goldxp = 0;
	int gold = 0;
	int sapphirexp = 0;
	int sapphire = 0;
	int diamondxp = 0;
	int diamond = 0;
	int emeraldxp = 0;
	int emerald = 0;
	int darkfragment = 0;
	string notebook = "";
	int earthfragment = 0;
	int firefragment = 0;
	int waterfragment = 0;
	bool transsuccess = false;
	bool isModState = false;
	string displayName = "";
	bool wrongpass = false;
	int guildBg = 0;
	int guildFg = 0;
	string guildStatement = "";
	string guildLeader = "";
	string displayNamebackup = "";
	string displayUsername = "";
	vector <string> guildmatelist;
	vector<string>guildMembers;
	vector<string>worldsowned;
	vector<string>lastworlds;
	int guildlevel = 0;
	int guildexp = 0;
	bool isinvited = false;
	string createGuildName = "";
	string createGuildStatement = "";
	string createGuildFlagBg = "";
	string createGuildFlagFg = "";
	string guild = "";
	bool joinguild = false;
	string lastgm = "";
	string lastgmname = "";
	string lastgmworld = "";
	string guildlast = "";
	string msgName = "";
	bool isNicked = false;
	string country = "";
	string gameversion = "";
	string rid = "none";
	string gid = "none";
	string aid = "none";
	bool canExit = true;
	string vid = "none";
	string wkid = "";
	string metaip = "";
	string hash2 = "";
	string hash = "";
	string fhash = "";
	string mac = "none";
	string token = "";
	string user = "";
	string deviceversion = "";
	string doorID = "";
	string cbits = "";
	string lmode = "";
	string gdpr = "";
	string f = "";
	string fz = "";
	string hpid = "";
	string platformID = "";
	string player_age = "1";
	int adminLevel = 0;
	string currentWorld = "EXIT";
	string plainip = "";
	string plainip2 = "";
	string plainip3 = "";
	string plainip4 = "";
	string buttonID = to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10);
	string firstnbr = to_string(rand() % 50);
	string secondnbr = to_string(rand() % 50);
	int resultnbr1 = std::atoi(firstnbr.c_str());
	int resultnbr2 = std::atoi(secondnbr.c_str());
	int Endresult = 0;
	bool radio = true;
	int x;
	int y;
	int x1;
	int y1;
	int posXY;
	int posX;
	int posY;
	int cpY;
	int cpX;
	int SignPosX;
	int SignPosY;
	bool characterLoaded = false;
	string charIP = "none";
	bool isDBanned = false;
	vector<string>friendinfo;
	vector<string>createfriendtable;
	vector<string>createworldsowned;
	string lastFrn = "";
	string lastFrnName = "";
	string lastFrnWorld = "";
	string lastMsger = "";
	string lastMsgerTrue = "";
	string lastMsgWorld = "";
	string lastSdbWorld = "";
	string lastSbbWorld = "";
	string lastfriend = "";
	string lastInfo = "";
	string lastInfoname = "";
	string lastSeller = "";
	string lastSellWorld = "";
	string lastBuyer = "";
	string lastInfoAboutPlayer = "none";
	int lastTradeAmount = 99999999999;
	string addgems = "1000 gems";
	int characterState = 0;
	int level = 1;
	int xp = 0;
	bool forcegemUpdate = false;
	bool isUpdating = false;
	bool joinClothesUpdated = false;
	int effect = 8421376;
	int peffect = 8421376;
	bool taped = false;
	bool canCreate = false;
	bool passedCaptcha = false;
	bool passedCaptcha2 = false;
	int cloth_hair = 0; // 0
	int cloth_shirt = 0; // 1
	int cloth_pants = 0; // 2
	int cloth_feet = 0; // 3
	int cloth_face = 0; // 4
	int cloth_hand = 0; // 5
	int cloth_back = 0; // 6
	int cloth_mask = 0; // 7
	int cloth_necklace = 0; // 8
	int cloth_ances = 0; // 9
	int cur = 0;
	int ipID = 0;
	int ban = 0;
	int istempBan = 0;
	int invcount = 0;
	int invitem1 = 0;
	int invitem2 = 0;
	int invitem3 = 0;
	int invitem4 = 0;
	int invitem5 = 0;
	int invitem6 = 0;
	int invitem7 = 0;
	int invitem8 = 0;
	int invitem9 = 0;
	bool canWalkInBlocks = false; // 1
	bool canDoubleJump = true; // 2
	bool cantsay = false;
	bool isInvisible = false; // 4
	bool noHands = false; // 8
	bool noEyes = false; // 16
	bool noBody = false; // 32	
	bool devilHorns = false; // 64
	bool goldenHalo = false; // 128
	bool isFrozen = false; // 2048
	bool isCursed = false; // 4096
	bool isDuctaped = false; // 8192
	unsigned long long int lastMuted = 0;
	unsigned long long int lastCursed = 0;
	bool haveCigar = false; // 16384
	bool isShining = false; // 32768
	bool isAncients = false; // 32768
	bool isAncients1 = false; // 32768
	bool isAncients2 = false; // 32768
	bool isAncients3 = false; // 32768
	bool isAncients4 = false; // 32768
	bool isAncients5 = false; // 32768
	bool isAncients6 = false; // 32768
	bool isZombie = false; // 65536
	bool isHitByLava = false; // 131072
	bool haveHauntedShadows = false; // 262144
	bool haveGeigerRadiation = false; // 524288
	bool haveReflector = false; // 1048576
	bool isEgged = false; // 2097152
	bool havePineappleFloag = false; // 4197584
	bool haveFlyingPineapple = false; // 8388608
	bool haveSuperSupporterName = false; // 16777216
	bool haveSupperPineapple = false; // 33554432
	bool isGhost = false;
	bool isinv = false;
	//string lastMsgWorld;
	bool unwheel = false;
	bool unsales = false;
	bool ghostalr = false;
	//bool 
	int skinColor = 0x8295C3FF; //normal SKIN color like gt!
	PlayerInventory inventory;
	short currentInventorySize = 0;
	long long int lastSB = 0;
	long long int lastSDB = 0;
	long long int lastSSB = 0;
	long long int lastINV = 0;
	long long int lastBREAK = 0;
	long long int lastMute = 0;
	long long int lastBan = 0;
	long long int lastCurse = 0;
	long long int lastATM = 0;
	long long int lastSYNC = 0;
	long long int lastDISPLAY = 0;
	int blockx;
	int blocky;
	bool isUseCode = false;
	bool isConfirmingCode = false;
	string registercode = "";
	string registermac = "";
	string registerrid = "";
	string registersid = "";
	string registergid = "";
	string registervid = "";
	string registeraid = "";
	string registerIP = "";
	string lastTradeName = "";
	int lastUserID = 0;
	int userID = 0;
	string currentTradeItems = "";
	int respawnX = 0;
	int respawnY = 0;
	bool ischeck = false;
	int checkx = 0;
	int checky = 0;
	bool loadedInventory = false;
	int updateReq = 0;
	long long int lastPunchTime = 0;
	long long int lastHitTime = 0;
	long long int lastJoinReq = 0;
	bool hasJoinedFromSubServer = false;
	long long int lastsendclient = 0;
	long long int lastpacketflood = 0;
	bool isQueuing = false;
	long long int lastenterdoor = 0;
	bool isWaitingForMatch = false;
	bool isInGame = false;
	bool queueEntered = false;
	uint32_t lavaHitAt = 0;
	uint32_t deadTime = 0;
	//vector<WorldAdministration> worldBan;
};
struct PlayerMoving {
	int packetType;
	int netID;
	float x;
	float y;
	int characterState;
	int plantingTree;
	float XSpeed;
	float YSpeed;
	int punchX;
	int punchY;
	int secondnetID;
};
struct Admin {
	string username;
	string password;
	int level = 0;
	long long int lastSB = 0;
	long long int lastWarp = 0;
	long long int lastSpawn = 0;
	long long int lastasb = 0;
};
struct GamePacket
{
	BYTE* data;
	int len;
	int indexes;
};
enum ClothTypes {
	HAIR,
	SHIRT,
	PANTS,
	FEET,
	FACE,
	HAND,
	BACK,
	MASK,
	NECKLACE,
	ANCES,
	NONE
};
bool verifyPassword(string password, string hash) {
	int ret;
	ret = bcrypt_checkpw(password.c_str(), hash.c_str());
	assert(ret != -1);
	return !ret;
}
string hashPassword(string password) {
	char salt[BCRYPT_HASHSIZE];
	char hash[BCRYPT_HASHSIZE];
	int ret;
	ret = bcrypt_gensalt(12, salt);
	assert(ret == 0);
	ret = bcrypt_hashpw(password.c_str(), salt, hash);
	assert(ret == 0);
	return hash;
}
inline int getState(PlayerInfo* info)
{
	auto val = 0;
	val |= info->canWalkInBlocks << 0;
	val |= info->canDoubleJump << 1;
	val |= info->cantsay << 13;
	val |= info->noHands << 3;
	val |= info->noEyes << 4;
	val |= info->noBody << 5;
	val |= info->goldenHalo << 7;
	val |= info->isFrozen << 8;
	val |= info->isCursed << 12;
	val |= info->isDuctaped << 13;
	val |= info->haveSuperSupporterName << 24;
	val |= info->isShining << 15;
	val |= info->isZombie << 16;
	val |= info->isHitByLava << 17;
	return val;
}

class Player {
public:
	static void OnConsoleMessage(ENetPeer* peer, string text);
	static void OnTalkBubble(ENetPeer* peer, int netID, string text, int chatColor, bool isOverlay);
	static void OnAddNotification(ENetPeer* peer, string text, string audiosound, string interfaceimage);
	static void OnRemove(ENetPeer* peer, int netID);
	static void OnSendToServer(ENetPeer* peer, int userID, int token, string ip, int port, string doorId, int lmode); // no need other args, sub servers done&working already... using fake data etc.
	static void PlayAudio(ENetPeer* peer, string audioFile, int delayMS);
	static void OnZoomCamera(ENetPeer* peer, float value1, int value2);
	static void SmoothZoom(ENetPeer* peer);
	static void OnRaceStart(ENetPeer* peer, int netID);
	static void OnRaceEnd(ENetPeer* peer, int netID);
	static void OnSetCurrentWeather(ENetPeer* peer, int weather);
	static void OnPlayPositioned(ENetPeer* peer, string audiofile, int netID, bool broadcastInWorld, ENetPacket* pk);
	static void OnCountdownStart(ENetPeer* peer, int netID, int time, int score);
	static void OnStartTrade(ENetPeer* peer, int netID1, int netID2);
	static void OnTextOverlay(ENetPeer* peer, string text);
	static void OnForceTradeEnd(ENetPeer* peer);
	static void OnFailedToEnterWorld(ENetPeer* peer);
	static void OnNameChanged(ENetPeer* peer, int netID, string name);
	static void OnTradeStatus(ENetPeer* peer, int netIDOther, string offerstatus, string offer);
	static void OnDialogRequest(ENetPeer* peer, string args);
	static void OnKilled(ENetPeer* peer, int netID);
	static void OnSetFreezeState(ENetPeer* peer, int state, int netID);
	static void OnSetPos(ENetPeer* peer, int netID, int x, int y);
	static void OnFlagMay2019(ENetPeer* peer, int state, int netID);
	static void OnBillboardChange(ENetPeer* peer, int netID);
	static void OnInvis(ENetPeer* peer, int state, int netID);
	static void OnChangeSkin(ENetPeer* peer, int skinColor, int netID);
	static void SetRespawnPos(ENetPeer* peer, int posX, int posY, int netID);
	static void OnSetBux(ENetPeer* peer, int gems, int accountstate);
	static void OnParticleEffect(ENetPeer* peer, int effect, float x, float y, int delay);
	static void SetHasGrowID(ENetPeer* peer, int status, string username, string password);
	static void Ping(ENetPeer* peer);
};
class PlayerDB {
public:
	static string getProperName(string name);
	static string PlayerDB::fixColors(string text);
	static int playerLogin(ENetPeer* peer, string username, string password);
	static int playerRegister(ENetPeer* peer, string username, string password, string passwordverify, string discord, string pin);
	static int playerChange(string username, string newpass);
	static int guildRegister(ENetPeer* peer, string guildName, string guildStatement, string guildFlagfg, string guildFlagbg);
};
string PlayerDB::getProperName(string name) {
	string newS;
	for (char c : name) newS += (c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c;
	string ret;
	for (int i = 0; i < newS.length(); i++)
	{
		if (newS[i] == '`') i++; else ret += newS[i];
	}
	string ret2;
	for (char c : ret) if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) ret2 += c;
	return ret2;
}

string PlayerDB::fixColors(string text) {
	string ret = "";
	int colorLevel = 0;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '`')
		{
			ret += text[i];
			if (i + 1 < text.length())
				ret += text[i + 1];
			if (i + 1 < text.length() && text[i + 1] == '`')
			{
				colorLevel--;
			}
			else {
				colorLevel++;
			}
			i++;
		}
		else {
			ret += text[i];
		}
	}
	for (int i = 0; i < colorLevel; i++) {
		ret += "``";
	}
	for (int i = 0; i > colorLevel; i--) {
		ret += "`w";
	}
	return ret;
}
GamePacket appendFloat(GamePacket p, float val)
{
	BYTE* n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 1;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}
GamePacket appendFloat(GamePacket p, float val, float val2)
{
	BYTE* n = new BYTE[p.len + 2 + 8];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 3;
	memcpy(n + p.len + 2, &val, 4);
	memcpy(n + p.len + 6, &val2, 4);
	p.len = p.len + 2 + 8;
	p.indexes++;
	return p;
}
GamePacket appendFloat(GamePacket p, float val, float val2, float val3)
{
	BYTE* n = new BYTE[p.len + 2 + 12];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 4;
	memcpy(n + p.len + 2, &val, 4);
	memcpy(n + p.len + 6, &val2, 4);
	memcpy(n + p.len + 10, &val3, 4);
	p.len = p.len + 2 + 12;
	p.indexes++;
	return p;
}
GamePacket appendInt(GamePacket p, int val)
{
	BYTE* n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 9;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}
GamePacket appendIntx(GamePacket p, int val)
{
	BYTE* n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 5;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}
GamePacket appendString(GamePacket p, string str)
{
	BYTE* n = new BYTE[p.len + 2 + str.length() + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 2;
	int sLen = str.length();
	memcpy(n + p.len + 2, &sLen, 4);
	memcpy(n + p.len + 6, str.c_str(), sLen);
	p.len = p.len + 2 + str.length() + 4;
	p.indexes++;
	return p;
}
GamePacket createPacket()
{
	BYTE* data = new BYTE[61];
	string asdf = "0400000001000000FFFFFFFF00000000080000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (int i = 0; i < asdf.length(); i += 2)
	{
		char x = ch2n(asdf[i]);
		x = x << 4;
		x += ch2n(asdf[i + 1]);
		memcpy(data + (i / 2), &x, 1);
		if (asdf.length() > 61 * 2) throw 0;
	}
	GamePacket packet;
	packet.data = data;
	packet.len = 61;
	packet.indexes = 0;
	return packet;
}
GamePacket packetEnd(GamePacket p)
{
	BYTE* n = new BYTE[p.len + 1];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	char zero = 0;
	memcpy(p.data + p.len, &zero, 1);
	p.len += 1;
	*(int*)(p.data + 56) = p.indexes;
	*(BYTE*)(p.data + 60) = p.indexes;
	return p;
}
BYTE* packPlayerMoving(PlayerMoving* dataStruct)
{
	BYTE* data = new BYTE[64];
	for (int i = 0; i < 64; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 4, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 20, &dataStruct->plantingTree, 4);
	memcpy(data + 24, &dataStruct->x, 4);
	memcpy(data + 28, &dataStruct->y, 4);
	memcpy(data + 32, &dataStruct->XSpeed, 4);
	memcpy(data + 36, &dataStruct->YSpeed, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	return data;
}
PlayerMoving* unpackPlayerMoving(BYTE* data)
{
	PlayerMoving* dataStruct = new PlayerMoving;
	memcpy(&dataStruct->packetType, data, 4);
	memcpy(&dataStruct->netID, data + 4, 4);
	memcpy(&dataStruct->characterState, data + 12, 4);
	memcpy(&dataStruct->plantingTree, data + 20, 4);
	memcpy(&dataStruct->x, data + 24, 4);
	memcpy(&dataStruct->y, data + 28, 4);
	memcpy(&dataStruct->XSpeed, data + 32, 4);
	memcpy(&dataStruct->YSpeed, data + 36, 4);
	memcpy(&dataStruct->punchX, data + 44, 4);
	memcpy(&dataStruct->punchY, data + 48, 4);
	return dataStruct;
}
long long GetCurrentTimeInternal()
{
	using namespace std::chrono;
	return (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
}
long long GetCurrentTimeInternalSeconds()
{
	using namespace std::chrono;
	return (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
}
int calcBanDuration(long long banDuration) {
	int duration = 0;
	duration = banDuration - GetCurrentTimeInternalSeconds();
	return duration;
}
string OutputBanTime(int n)
{
	string x;
	int day = n / (24 * 3600);
	if (day != 0) x.append(to_string(day) + " Days ");
	n = n % (24 * 3600);
	int hour = n / 3600;
	if (hour != 0) x.append(to_string(hour) + " Hours ");
	n %= 3600;
	int minutes = n / 60;
	if (minutes != 0) x.append(to_string(minutes) + " Minutes ");
	n %= 60;
	int seconds = n;
	if (seconds != 0) x.append(to_string(seconds) + " Seconds");
	return x;
}
void banlogin(ENetPeer* peer) {
	string text = "action|log\nmsg|`4Sorry, this account (`5" + ((PlayerInfo*)(peer->data))->rawName + "`4) has been suspended.\n";
	string text3 = "action|logon_fail\n";
	string dc = "https://dsc.gg/gtas";
	string url = "action|set_url\nurl|" + dc + "\nlabel|`5Reset your password\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE* data3 = new BYTE[5 + text3.length()];
	BYTE* dataurl = new BYTE[5 + url.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	memcpy(dataurl, &type, 4);
	memcpy(dataurl + 4, url.c_str(), url.length());
	memcpy(dataurl + 4 + url.length(), &zero, 1);
	memcpy(data3, &type, 4);
	memcpy(data3 + 4, text3.c_str(), text3.length());
	memcpy(data3 + 4 + text3.length(), &zero, 1);
	ENetPacket* p = enet_packet_create(data,
		5 + text.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p);
	ENetPacket* p3 = enet_packet_create(dataurl,
		5 + url.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p3);
	ENetPacket* p2 = enet_packet_create(data3,
		5 + text3.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p2);
	delete data;
	delete dataurl;
	delete data3;
}
void banLoginDevice(ENetPeer* peer, long long banDurationDefault, string sid, string mac) {
	int bantimeleft = calcBanDuration(banDurationDefault);
	if (bantimeleft < 1) {
		return;
	}
	string text = "action|log\nmsg|`4Sorry, this device or location is still banned for `w" + OutputBanTime(calcBanDuration(banDurationDefault)) + ".";
	string text3 = "action|logon_fail\n";
	string dc = "https://dsc.gg/gtas";
	string url = "action|set_url\nurl|" + dc + "\nlabel|`5Reset your password\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE* data3 = new BYTE[5 + text3.length()];
	BYTE* dataurl = new BYTE[5 + url.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	memcpy(dataurl, &type, 4);
	memcpy(dataurl + 4, url.c_str(), url.length());
	memcpy(dataurl + 4 + url.length(), &zero, 1);
	memcpy(data3, &type, 4);
	memcpy(data3 + 4, text3.c_str(), text3.length());
	memcpy(data3 + 4 + text3.length(), &zero, 1);
	ENetPacket* p = enet_packet_create(data,
		5 + text.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p);
	ENetPacket* p3 = enet_packet_create(dataurl,
		5 + url.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p3);
	ENetPacket* p2 = enet_packet_create(data3,
		5 + text3.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p2);
	enet_peer_disconnect_later(peer, 0);
	delete data;
	delete dataurl;
	delete data3;
}

inline void SendInventory(ENetPeer* peer, PlayerInventory inventory)
{
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	const int inventoryLen = inventory.items.size();
	const auto packetLen = 66 + (inventoryLen * 4) + 4;
	auto* data2 = new BYTE[packetLen];
	auto MessageType = 0x4;
	auto PacketType = 0x9;
	auto NetID = -1;
	auto CharState = 0x8;
	memset(data2, 0, packetLen);
	memcpy(data2, &MessageType, 4);
	memcpy(data2 + 4, &PacketType, 4);
	memcpy(data2 + 8, &NetID, 4);
	memcpy(data2 + 16, &CharState, 4);
	//int endianInvVal = __builtin_bswap32(inventoryLen);
	int endianInvVal = _byteswap_ulong(inventoryLen);
	memcpy(data2 + 66 - 4, &endianInvVal, 4);
	//endianInvVal = __builtin_bswap32(static_cast<PlayerInfo*>(peer->data)->currentInventorySize);
	endianInvVal = _byteswap_ulong(static_cast<PlayerInfo*>(peer->data)->currentInventorySize);
	memcpy(data2 + 66 - 8, &endianInvVal, 4);
	auto val = 0;
	for (auto i = 0; i < inventoryLen; i++)
	{
		val = 0;
		val |= inventory.items.at(i).itemID;
		val |= inventory.items.at(i).itemCount << 16;
		val &= 0x00FFFFFF;
		val |= 0x00 << 24;
		memcpy(data2 + (i * 4) + 66, &val, 4);
	}
	const auto packet3 = enet_packet_create(data2, packetLen, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete data2;
}

inline bool CheckItemExists(ENetPeer* peer, const int fItemId)
{
	auto isExists = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
	{
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemId)
		{
			isExists = true;
			break;
		}
	}
	return isExists;
}

inline bool CheckItemMaxed(ENetPeer* peer, const int fItemId, const int fQuantityAdd)
{
	auto isMaxed = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
	{
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemId && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount + fQuantityAdd > 200)
		{
			isMaxed = true;
			break;
		}
	}
	return isMaxed;
}

void checkAutoBan(ENetPeer* peer) {
	string rid = ((PlayerInfo*)(peer->data))->rid;
	string sid = ((PlayerInfo*)(peer->data))->sid;
	string gid = ((PlayerInfo*)(peer->data))->gid;
	string vid = ((PlayerInfo*)(peer->data))->vid;
	string aid = ((PlayerInfo*)(peer->data))->aid;
	string mac = ((PlayerInfo*)(peer->data))->mac;
	string ip = to_string(peer->address.host);
	Remove(mac, ":");
	bool exist = experimental::filesystem::exists("autoban/rid/" + rid + ".txt") ||
		experimental::filesystem::exists("autoban/gid/" + gid + ".txt") ||
		experimental::filesystem::exists("autoban/vid/" + vid + ".txt") ||
		experimental::filesystem::exists("autoban/aid/" + aid + ".txt") ||
		experimental::filesystem::exists("autoban/ip/" + ip + ".txt");
	if (exist) {
		string content = "0";
		if (experimental::filesystem::exists("autoban/ip/" + ip + ".txt")) {
			ifstream ifs("autoban/ip/" + ip + ".txt");
			if (ifs.fail()) {
				cout << "[Stream-ERROR]: failed to check whether '" + ((PlayerInfo*)(peer->data))->rawName + "' is auto banned by system." << endl;
				Player::OnConsoleMessage(peer, "`5[Stream-ERROR]: `@ failed to check whether '" + ((PlayerInfo*)(peer->data))->rawName + "' is auto banned by system. `5Please send this screenshot to GrowtopiaLR developers.");
				enet_peer_disconnect_later(peer, 0);
			}
			else
			{
				ifs >> content;
				ifs.close();
			}
		}
		if (content != "0") {
			long long banDuration = atoi(content.c_str());
			banLoginDevice(peer, banDuration, sid, mac);
		}
	}
}
void checkIpBan(ENetPeer* peer) {
	string rid = ((PlayerInfo*)(peer->data))->rid;
	string sid = ((PlayerInfo*)(peer->data))->sid;
	string gid = ((PlayerInfo*)(peer->data))->gid;
	string vid = ((PlayerInfo*)(peer->data))->vid;
	string aid = ((PlayerInfo*)(peer->data))->aid;
	string mac = ((PlayerInfo*)(peer->data))->mac;
	Remove(mac, ":");
	string ip_id = to_string(peer->address.host);

	char clientConnection[16];
	enet_address_get_host_ip(&peer->address, clientConnection, 16);
	string ip = clientConnection;

	bool exist = experimental::filesystem::exists("ipbans/rid/" + rid + ".txt") ||
		experimental::filesystem::exists("ipbans/gid/" + gid + ".txt") ||
		experimental::filesystem::exists("ipbans/vid/" + vid + ".txt") ||
		experimental::filesystem::exists("ipbans/aid/" + aid + ".txt") ||
		experimental::filesystem::exists("ipbans/sid/" + sid + ".txt") ||
		experimental::filesystem::exists("ipbans/mac/" + mac + ".txt") ||
		experimental::filesystem::exists("ipbans/ip_id/" + ip_id + ".txt") ||
		experimental::filesystem::exists("ipbans/ip/" + ip + ".txt");
	if (exist) {
		string text = "action|log\nmsg|`4Sorry, this device or location is perma banned.";
		string text3 = "action|logon_fail\n";
		string dc = "https://dsc.gg/gtas";
		string url = "action|set_url\nurl|" + dc + "\nlabel|`5Reset your password\n";
		BYTE* data = new BYTE[5 + text.length()];
		BYTE* data3 = new BYTE[5 + text3.length()];
		BYTE* dataurl = new BYTE[5 + url.length()];
		BYTE zero = 0;
		int type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		memcpy(dataurl, &type, 4);
		memcpy(dataurl + 4, url.c_str(), url.length());
		memcpy(dataurl + 4 + url.length(), &zero, 1);
		memcpy(data3, &type, 4);
		memcpy(data3 + 4, text3.c_str(), text3.length());
		memcpy(data3 + 4 + text3.length(), &zero, 1);
		ENetPacket* p = enet_packet_create(data,
			5 + text.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p);
		ENetPacket* p3 = enet_packet_create(dataurl,
			5 + url.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p3);
		ENetPacket* p2 = enet_packet_create(data3,
			5 + text3.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p2);
		enet_peer_disconnect_later(peer, 0);
		delete data;
		delete dataurl;
		delete data3;
	}
}
void checkTimeBan(ENetPeer* peer, string username) {
	bool exist = experimental::filesystem::exists("timebanned/" + PlayerDB::getProperName(username) + ".txt");
	if (exist)
	{
		ifstream fd("timebanned/" + PlayerDB::getProperName(username) + ".txt");
		long long banDuration = 0;
		string bannedBy;
		string bannedReason;
		if (fd.fail()) {
			cout << "[Stream-ERROR]: failed to check whether '" + username + "' is time banned." << endl;
			Player::OnConsoleMessage(peer, "`5[Stream-ERROR]: `@ failed to check whether '" + username + "' is time banned. `5Please send this screenshot to GrowtopiaLR developers.");
			enet_peer_disconnect_later(peer, 0);
		}
		else
		{
			fd >> banDuration;
			fd >> bannedBy;
			fd.ignore();
			getline(fd, bannedReason);
			fd.close();
		}
		int bantimeleft = calcBanDuration(banDuration);
		if (bantimeleft < 1) {
			return;
		}
		string text = "action|log\nmsg|`4Sorry, this account is temporary banned by `2" + bannedBy + " `4for `w" + OutputBanTime(calcBanDuration(banDuration)) + " `4for `w" + bannedReason + ".";
		string text3 = "action|logon_fail\n";
		string dc = "https://dsc.gg/gtas";
		string url = "action|set_url\nurl|" + dc + "\nlabel|`5Reset your password\n";
		BYTE* data = new BYTE[5 + text.length()];
		BYTE* data3 = new BYTE[5 + text3.length()];
		BYTE* dataurl = new BYTE[5 + url.length()];
		BYTE zero = 0;
		int type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		memcpy(dataurl, &type, 4);
		memcpy(dataurl + 4, url.c_str(), url.length());
		memcpy(dataurl + 4 + url.length(), &zero, 1);
		memcpy(data3, &type, 4);
		memcpy(data3 + 4, text3.c_str(), text3.length());
		memcpy(data3 + 4 + text3.length(), &zero, 1);
		ENetPacket* p = enet_packet_create(data,
			5 + text.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p);
		ENetPacket* p3 = enet_packet_create(dataurl,
			5 + url.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p3);
		ENetPacket* p2 = enet_packet_create(data3,
			5 + text3.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p2);
		enet_peer_disconnect_later(peer, 0);
		delete data;
		delete dataurl;
		delete data3;
	}
}
bool isHere(ENetPeer* peer, ENetPeer* peer2)
{
	return ((PlayerInfo*)(peer->data))->currentWorld == ((PlayerInfo*)(peer2->data))->currentWorld;
}
void autoBan(ENetPeer* peer, bool isInvalid, long long timeInH, string infoText) {
	ofstream x;
	ofstream e;
	ofstream b;
	string name;

	if (((PlayerInfo*)(peer->data))->haveGrowId == true)
	{
		name = ((PlayerInfo*)(peer->data))->rawName;
	}
	else
	{
		name = "PLAYER WITHOUT GROW-ID";
	}

	char clientConnection[16];
	enet_address_get_host_ip(&peer->address, clientConnection, 16);
	string hisIp = clientConnection;
	ofstream autobanLog("logs/autoban.txt", ios::app);
	autobanLog << "[IP: " << hisIp << "], " << "[Ip_id: " << peer->address.host << "], " << name << " auto-banned for " << infoText << endl;
	autobanLog.close();

	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		Player::OnConsoleMessage(currentPeer, "`4** `o" + name + " `4AUTO-BANNED BY SYSTEM **`o (/rules to view rules)");
	}
	if (isInvalid) {
		x.open("autoban/ip/" + to_string(peer->address.host) + ".txt");
		x << to_string(GetCurrentTimeInternalSeconds() + (timeInH * 3600));
		x.close();
		enet_peer_disconnect_later(peer, 0);
	}
	else {
		string mac = ((PlayerInfo*)(peer->data))->mac;
		Remove(mac, ":");
		x.open("autoban/ip/" + to_string(peer->address.host) + ".txt");
		x << to_string(GetCurrentTimeInternalSeconds() + (timeInH * 3600));
		x.close();
		enet_peer_disconnect_later(peer, 0);
	}
}

inline int PlayerDB::playerChange(string username, string newpass)
{

	auto exist = std::experimental::filesystem::exists("players/" + username + ".json");
	if (!exist) {
		return -1;
	}
	else {
		ifstream fg("players/" + PlayerDB::getProperName(username) + ".json");
		json j;
		fg >> j;
		fg.close();

		j["password"] = newpass;

		ofstream fs("players/" + PlayerDB::getProperName(username) + ".json");
		fs << j;
		fs.close();
		return -2;
	}
}

int PlayerDB::playerLogin(ENetPeer* peer, string username, string password) {
	string uname = username;
	toUpperCase(uname);
	string username1 = ((PlayerInfo*)(peer->data))->tankIDName;
	if (username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
		return -10;
	}
	if (configPort == 8080) {
		GamePacket p3 = packetEnd(appendInt(appendInt(appendString(appendString(createPacket(), "OnRedirectServer"), "35.247.185.254"), 17091), 1));

		//memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
		ENetPacket* packet3 = enet_packet_create(p3.data,
			p3.len,
			ENET_PACKET_FLAG_RELIABLE);

		enet_peer_send(peer, 0, packet3);
		delete p3.data;
	}
	if (username.length() < 3) return -2;
	if (username.length() > 20) return -2;
	if (uname == "CON" || uname == "NUL" || uname == "PRN" || uname == "AUX" || uname == "CLOCK$" || uname == "COM0" || uname == "COM1" || uname == "COM2" || uname == "COM3" || uname == "COM4" || uname == "COM5" || uname == "COM6" || uname == "COM7" || uname == "COM8" || uname == "COM9" || uname == "LPT0" || uname == "LPT1" || uname == "LPT2" || uname == "LPT3" || uname == "LPT4" || uname == "LPT5" || uname == "LPT6" || uname == "LPT7" || uname == "LPT8" || uname == "LPT9")
	{
		return -4;
	}
	if (uname == "" || uname == " " || uname == "  " || uname == "   " || uname == "    ")
	{
		return -5;
	}
	if (username1.find(" ") != string::npos || username1.find(".") != string::npos || username1.find(",") != string::npos || username1.find("@") != string::npos || username1.find("?") != string::npos || username1.find("[") != string::npos || username1.find("]") != string::npos || username1.find("#") != string::npos || username1.find("<") != string::npos || username1.find(">") != string::npos || username1.find(":") != string::npos || username1.find("{") != string::npos || username1.find("}") != string::npos || username1.find("|") != string::npos || username1.find("+") != string::npos || username1.find("_") != string::npos || username1.find("~") != string::npos || username1.find("-") != string::npos || username1.find("!") != string::npos || username1.find("$") != string::npos || username1.find("%") != string::npos || username1.find("^") != string::npos || username1.find("&") != string::npos || username1.find("`") != string::npos || username1.find("*") != string::npos || username1.find("(") != string::npos || username1.find(")") != string::npos || username1.find("=") != string::npos || username1.find("'") != string::npos || username1.find(";") != string::npos || username1.find("/") != string::npos) {
		return -5;
	}
	bool contains_non_alpha
		= !std::regex_match(uname, std::regex("^[0-9]+$"));
	if (contains_non_alpha)
	{
	}
	else {
		return -4;
	}
	checkTimeBan(peer, username);
	checkAutoBan(peer);
	checkIpBan(peer);
	if (std::experimental::filesystem::exists("creators/" + PlayerDB::getProperName(((PlayerInfo*)(peer->data))->rawName) + ".txt")) ((PlayerInfo*)(peer->data))->isCreator = true;
	bool skillexist = std::experimental::filesystem::exists("skill/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	if (!skillexist)
	{
		ofstream of("skill/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		of << "None";
		of.close();
	}
	else
	{
		ifstream myfile;
		myfile.open("skill/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		myfile >> ((PlayerInfo*)(peer->data))->skill;
		myfile.close();

	}

	bool inventoryExists = std::experimental::filesystem::exists("inventory/" + PlayerDB::getProperName(username) + ".json");
	if (!inventoryExists)
	{
		try {
			std::ofstream oo("inventory/" + username + ".json");
			if (!oo.is_open()) {
				cout << GetLastError() << endl;
				_getch();
			}
			json items;
			json jjall = json::array();
			json jj;
			jj["aposition"] = 1;
			jj["itemid"] = 18;
			jj["quantity"] = 1;
			jjall.push_back(jj);
			jj["aposition"] = 2;
			jj["itemid"] = 32;
			jj["quantity"] = 1;
			jjall.push_back(jj);
			for (int i = 2; i < 200; i++)
			{
				jj["aposition"] = i + 1;
				jj["itemid"] = 0;
				jj["quantity"] = 0;
				jjall.push_back(jj);
			}
			items["items"] = jjall;
			oo << items << std::endl;
			oo.close();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
		}
		catch (...) {
			cout << "reading file violation" << endl;
		}
	}
	bool atmexist = std::experimental::filesystem::exists("blocks/atm/" + PlayerDB::getProperName(username) + ".txt");
	if (!atmexist)
	{
		ofstream of("blocks/atm/" + PlayerDB::getProperName(username) + ".txt");
		of << 0;
		of.close();
	}
	else
	{
		ifstream fd("blocks/atm/" + PlayerDB::getProperName(username) + ".txt");
		fd >> ((PlayerInfo*)(peer->data))->lastATM;
		fd.close();
	}
	bool invsizeist = std::experimental::filesystem::exists("usersinventorysize/" + PlayerDB::getProperName(username) + ".txt");
	if (!invsizeist)
	{
		ofstream invof("usersinventorysize/" + PlayerDB::getProperName(username) + ".txt");
		invof << 200;
		invof.close();

	}
	try {
		std::ifstream ifs("players/" + PlayerDB::getProperName(username) + ".json");
		if (ifs.is_open()) {
			json j;
			ifs >> j;
			string pss = j["password"];
			int ban = j["isBanned"];
			int ipID = j["ipID"];
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
				if (ban == 1) {
					banlogin(peer);
				}
			if (verifyPassword(password, pss)) {
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					string mac = (((PlayerInfo*)(peer->data))->mac);
					if (mac.length() > 23)
					{
						GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Oh No! something is wrong and you will be disconnected..."));
						ENetPacket* packet = enet_packet_create(p.data,
							p.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet);
						delete p.data;
						enet_peer_disconnect_later(peer, 0);
					}
					string ip = std::to_string(peer->address.host);
					if (ip.length() > 23)
					{
						GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Oh No! something is wrong and you will be disconnected..."));
						ENetPacket* packet = enet_packet_create(p.data,
							p.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet);
						delete p.data;
						enet_peer_disconnect_later(peer, 0);
					}
					string tankid = ((PlayerInfo*)(peer->data))->tankIDName;
					if (tankid.length() > 25) {
						return -5;
					}
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (currentPeer == peer)
						continue;
					if (((PlayerInfo*)(currentPeer->data))->rawName == PlayerDB::getProperName(username))
					{
						{
							Player::OnConsoleMessage(currentPeer, "`4ALREADY ON!?`oIf you were disconnected its okay");
						}
						{
							Player::OnConsoleMessage(currentPeer, "`4ALREADY ON?!`o If you were play it before its okay");
						}
						enet_host_flush(server);
						enet_peer_disconnect_later(currentPeer, 0);
					}
				}
				return 1;
			}
			else {
				return -1;
			}
		}
		else {
			return -2;
		}
	}
	catch (...) {
		Player::OnConsoleMessage(peer, "It appears that this account is corrupted.");
	}

}
int PlayerDB::playerRegister(ENetPeer* peer, string username, string password, string passwordverify, string discord, string pin) {
	if (username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
		return -10;
	}
	if (pin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
		return -12;
	}
	if (pin.length() < 5)
	{
		return -13;
	}
	username = PlayerDB::getProperName(username);
	if (username.length() < 3) return -2;
	if (username.length() > 20) return -2;
	string uname = username;
	toUpperCase(uname);
	if (uname == "CON" || uname == "NUL" || uname == "PRN" || uname == "AUX" || uname == "CLOCK$" || uname == "COM0" || uname == "COM1" || uname == "COM2" || uname == "COM3" || uname == "COM4" || uname == "COM5" || uname == "COM6" || uname == "COM7" || uname == "COM8" || uname == "COM9" || uname == "LPT0" || uname == "LPT1" || uname == "LPT2" || uname == "LPT3" || uname == "LPT4" || uname == "LPT5" || uname == "LPT6" || uname == "LPT7" || uname == "LPT8" || uname == "LPT9")
	{
		return -6;
	}
	if (uname == "" || uname == " " || uname == "  " || uname == "   " || uname == "    ")
	{
		return -11;
	}
	std::ifstream ifs("players/" + username + ".json");
	if (ifs.is_open()) {
		return -1;
	}
	short registeringIpCount = 1;
	bool existsRegisteringIP = std::experimental::filesystem::exists("registeredIP/" + ((PlayerInfo*)(peer->data))->charIP + ".txt");
	if (existsRegisteringIP)
	{
		ifstream getIp("registeredIP/" + ((PlayerInfo*)(peer->data))->charIP + ".txt");
		getIp >> registeringIpCount;
		registeringIpCount += 1;
		if (registeringIpCount >= 4)
		{
			return -14;
		}
		ofstream writeIp("registeredIP/" + ((PlayerInfo*)(peer->data))->charIP + ".txt");
		writeIp << registeringIpCount;
		writeIp.close();
	}
	else
	{
		ofstream writeIp("registeredIP/" + ((PlayerInfo*)(peer->data))->charIP + ".txt");
		writeIp << 1;
		writeIp.close();
	}
	bool contains_non_alpha = !std::regex_match(pin, std::regex("^[0-9]+$"));
	ENetPeer* currentPeer;
	currentPeer = server->peers;
	try {
		std::ofstream o("players/" + username + ".json");
		if (!o.is_open()) {
			cout << GetLastError() << endl;
			_getch();
		}
		json j;
		j["username"] = username;
		j["password"] = hashPassword(password);
		j["ClothBack"] = 0;
		j["ClothHand"] = 0;
		j["ClothFace"] = 0;
		j["ClothShirt"] = 0;
		j["ClothPants"] = 0;
		j["ClothNeck"] = 0;
		j["ClothHair"] = 0;
		j["ClothFeet"] = 0;
		j["ClothMask"] = 0;
		j["ClothAnces"] = 0;
		j["isBanned"] = 0;
		j["ipID"] = peer->address.host;
		j["effect"] = 8421376;
		j["friends"] = ((PlayerInfo*)(peer->data))->createfriendtable;
		j["ip"] = ((PlayerInfo*)(peer->data))->charIP;
		j["aap"] = ((PlayerInfo*)(peer->data))->isAAP;
		j["receivedwarns"] = ((PlayerInfo*)(peer->data))->warns;
		j["receivedbans"] = ((PlayerInfo*)(peer->data))->bans;
		j["discord"] = discord;
		if (((PlayerInfo*)(peer->data))->adminLevel != 0)
		{
			autoBan(peer, true, 99999, "on register function, his adminLevel was no 0");
			return -11;
		}
		j["adminLevel"] = ((PlayerInfo*)(peer->data))->adminLevel;
		j["guild"] = "";
		j["joinguild"] = false;
		j["level"] = 1;
		j["xp"] = 0;
		j["rubble"] = 0;
		j["rubblexp"] = 0;
		j["amber"] = 0;
		j["amberxp"] = 0;
		j["opal"] = 0;
		j["opalxp"] = 0;
		j["gold"] = 0;
		j["goldxp"] = 0;
		j["sapphire"] = 0;
		j["sapphirexp"] = 0;
		j["diamond"] = 0;
		j["diamondxp"] = 0;
		j["emerald"] = 0;
		j["emeraldxp"] = 0;
		j["fishermanlevel"] = static_cast<PlayerInfo*>(peer->data)->fishermanlevel;
		j["geigerlevel"] = static_cast<PlayerInfo*>(peer->data)->geigerlevel;
		j["firefighterlevel"] = static_cast<PlayerInfo*>(peer->data)->firefighterlevel;
		j["providerlevel"] = static_cast<PlayerInfo*>(peer->data)->providerlevel;
		j["providerxp"] = static_cast<PlayerInfo*>(peer->data)->providerxp;
		j["geigerxp"] = static_cast<PlayerInfo*>(peer->data)->geigerxp;
		j["fishermanxp"] = static_cast<PlayerInfo*>(peer->data)->fishermanxp;
		j["firefighterxp"] = static_cast<PlayerInfo*>(peer->data)->firefighterxp;
		j["notebook"] = "";
		j["worldsowned"] = ((PlayerInfo*)(peer->data))->createworldsowned;
		o << j << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
	}
	catch (...) {
		cout << "reading file violation" << endl;
	}
	ofstream ofrags("gemstorage/" + username + ".txt");
	ofrags << 0 << endl;
	ofrags.close();
	ofstream ofrag("fragments/" + username + ".txt");
	ofrag << 0 << endl;
	ofrag.close();
	try {
		std::ofstream oo("inventory/" + username + ".json");
		if (!oo.is_open()) {
			cout << GetLastError() << endl;
			_getch();
		}
		json items;
		json jjall = json::array();
		json jj;
		jj["aposition"] = 1;
		jj["itemid"] = 18;
		jj["quantity"] = 1;
		jjall.push_back(jj);
		jj["aposition"] = 2;
		jj["itemid"] = 32;
		jj["quantity"] = 1;
		jjall.push_back(jj);
		for (int i = 2; i < 200; i++)
		{
			jj["aposition"] = i + 1;
			jj["itemid"] = 0;
			jj["quantity"] = 0;
			jjall.push_back(jj);
		}
		items["items"] = jjall;
		oo << items << std::endl;
		oo.close();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
	}
	catch (...) {
		cout << "reading file violation" << endl;
	}
	ofstream pGems("gemdb/" + username + ".txt");
	pGems << 0;
	pGems.close();
	ofstream fsCode("accountSecurity/" + username + ".txt");
	fsCode << "false" << endl;
	fsCode << pin << endl;
	fsCode << ((PlayerInfo*)(peer->data))->mac << endl;
	fsCode << ((PlayerInfo*)(peer->data))->rid << endl;
	fsCode << ((PlayerInfo*)(peer->data))->sid << endl;
	fsCode << ((PlayerInfo*)(peer->data))->gid << endl;
	fsCode << ((PlayerInfo*)(peer->data))->vid << endl;
	fsCode << ((PlayerInfo*)(peer->data))->aid << endl;
	fsCode << ((PlayerInfo*)(peer->data))->charIP << endl;
	fsCode.close();
	return 1;
}
vector<Admin> admins;
int getAdminLevel(string username, string password) {
	for (int i = 0; i < admins.size(); i++) {
		Admin admin = admins[i];
		if (admin.username == username && admin.password == password) {
			return admin.level;
		}
	}
	return 0;
}

void SavePlayerData(ENetPeer* peer) {
	if (((PlayerInfo*)(peer->data))->haveGrowId == true) {
		try {
			const auto p = static_cast<PlayerInfo*>(peer->data);
			ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
			json j;
			fg >> j;
			fg.close();

			j["ClothBack"] = to_string(p->cloth_back);
			j["ClothHand"] = to_string(p->cloth_hand);
			j["ClothFace"] = to_string(p->cloth_face);
			j["ClothShirt"] = to_string(p->cloth_shirt);
			j["ClothPants"] = to_string(p->cloth_pants);
			j["ClothNeck"] = to_string(p->cloth_necklace);
			j["ClothHair"] = to_string(p->cloth_hair);
			j["ClothFeet"] = to_string(p->cloth_feet);
			j["ClothMask"] = to_string(p->cloth_mask);
			j["ClothAnces"] = to_string(p->cloth_ances);
			j["level"] = static_cast<PlayerInfo*>(peer->data)->level;
			j["xp"] = static_cast<PlayerInfo*>(peer->data)->xp;
			j["adminLevel"] = static_cast<PlayerInfo*>(peer->data)->adminLevel;

			ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
			fs << j;
			fs.close();
		}
		catch (std::exception&) {
			enet_peer_disconnect_now(peer, 0);
			return;
		}
		catch (std::runtime_error&) {
			enet_peer_disconnect_now(peer, 0);
			return;
		}
		catch (...) {
			enet_peer_disconnect_now(peer, 0);
			return;
		}
	}
}

void PlayAudioWorld(ENetPeer* peer, string audioFile)
{
	string text = "action|play_sfx\nfile|" + audioFile + "\ndelayMS|0\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	ENetPeer* currentPeer;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			ENetPacket* packet2 = enet_packet_create(data,
				5 + text.length(),
				ENET_PACKET_FLAG_RELIABLE);

			enet_peer_send(currentPeer, 0, packet2);

			//enet_host_flush(server);
		}
	}
	delete data;
}
void OnTalkBubble(ENetPeer* peer, int netID, string text, bool isOverlay)
{
	if (isOverlay == true) {
		GamePacket p = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"),
			((PlayerInfo*)(peer->data))->netID), text), 0), 1));

		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	else
	{
		GamePacket p = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"),
			((PlayerInfo*)(peer->data))->netID), text), 0));

		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}

int adminlevel(string name) {
	try {
		std::ifstream ifff("players/" + PlayerDB::getProperName(name) + ".json");
		json j;
		ifff >> j;
		int adminlevel;
		adminlevel = j["adminLevel"];
		ifff.close();
		if (adminlevel == 0) {
			return 0;
		}
		else {
			return adminlevel;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
	}
	catch (...) {
		cout << "reading file violation" << endl;
	}
}

inline bool isMod(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 999) return true;
	else if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1000) return true;
	else return false;
}


string getModsOnlineCount()
{
	int modCount = 0;
	string text = "No mods are online";
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (((PlayerInfo*)(currentPeer->data))->adminLevel >= 777) {
			modCount++;
		}
	}
	if (modCount == 1)
	{
		text = to_string(modCount) + " mod is online";
	}
	if (modCount > 1)
	{
		text = to_string(modCount) + " mods are online";
	}
	return text;
}
void showModLogs(string textInfo)
{
	GamePacket p6 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), textInfo));
	string text = "action|play_sfx\nfile|audio/beep.wav\ndelayMS|0\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (!((PlayerInfo*)(currentPeer->data))->radio)
			continue;
		if (((PlayerInfo*)(currentPeer->data))->currentWorld == "EXIT")
			continue;
		if (((PlayerInfo*)(currentPeer->data))->isIn == false)
			continue;
		if (((PlayerInfo*)(currentPeer->data))->adminLevel >= 777) {
			ENetPacket* packet6 = enet_packet_create(p6.data,
				p6.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet6);
			ENetPacket* packet2 = enet_packet_create(data,
				5 + text.length(),
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
			//enet_host_flush(server);
		}
	}
	delete data;
	delete p6.data;
}
void AutoDemote(string playerName, string his_rank, string ipAddress, string whyDemote)
{
	bool existsPlayer = std::experimental::filesystem::exists("players/" + PlayerDB::getProperName(playerName) + ".json");
	if (existsPlayer)
	{
		try {
			std::ifstream iffff("players/" + playerName + ".json");
			json jj;
			if (iffff.fail()) {
				iffff.close();
				return;
			}
			if (iffff.is_open()) {
			}
			iffff >> jj; //load
			std::ofstream oo("players/" + playerName + ".json");
			if (!oo.is_open()) {
				cout << GetLastError() << endl;
				_getch();
			}

			jj["adminLevel"] = 0;

			oo << jj << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
		}
		catch (...) {
			cout << "reading file violation" << endl;
		}
		ofstream autodemoteLog("logs/autodemote.txt", ios::app);
		autodemoteLog << "[" << ipAddress << "] administrator " << playerName << " with rank: " + his_rank + " auto-demoted for: " << whyDemote << endl;
		autodemoteLog.close();

		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			Player::OnConsoleMessage(currentPeer, "`b[`4Anti`w-`4Abusing`b]`w: `1Moderator `4" + playerName + " `1just `4auto-demoted `1on suspicion of abusing.");
			if (((PlayerInfo*)(currentPeer->data))->rawName == playerName)
			{
				enet_peer_disconnect_later(currentPeer, 0);
			}
		}
	}
}

void GiveRank(string rankName, string playerName, bool& success)
{
	bool existsPlayer = std::experimental::filesystem::exists("players/" + PlayerDB::getProperName(playerName) + ".json");
	if (existsPlayer)
	{
		try {
			std::ifstream iffff("players/" + playerName + ".json");
			json jj;
			success = false;
			if (iffff.fail()) {
				iffff.close();
			}
			if (iffff.is_open()) {
			}
			iffff >> jj; //load
			std::ofstream oo("players/" + playerName + ".json");
			if (!oo.is_open()) {
				cout << GetLastError() << endl;
				_getch();
			}
			int countranks, rankNumber;
			string rankText;
			ifstream ranks("giverank.txt");
			ranks >> countranks;
			for (int i = 0; i < countranks; i++)
			{
				ranks >> rankNumber >> rankText;
				if (rankText == rankName)
				{
					jj["adminLevel"] = rankNumber;
					success = true;
					break;
				}
			}
			ranks.close();
			if (success) oo << jj << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
		}
		catch (...) {
			cout << "reading file violation" << endl;
		}
	}
	else
	{
		success = false;
	}
}
bool isMail(int id)
{
	if (id == 656 || id == 1006) {
		return true;
	}
	else {
		return false;
	}
	return false;
}
void sendDialog(ENetPeer* peer, string message) {
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), message));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

void SendTalkSelf(ENetPeer* peer, string text)
{
	GamePacket p2 = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), text), 0), 1));

	ENetPacket* packet2 = enet_packet_create(p2.data,
		p2.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete p2.data;
}
void sendInventory(ENetPeer* peer, PlayerInventory inventory)
{
	string asdf2 = "0400000009A7379237BB2509E8E0EC04F8720B050000000000000000FBBB0000010000007D920100FDFDFDFD04000000040000000000000000000000000000000000";
	int inventoryLen = inventory.items.size();
	int packetLen = (asdf2.length() / 2) + (inventoryLen * 4) + 4;
	BYTE* data2 = new BYTE[packetLen];
	for (int i = 0; i < asdf2.length(); i += 2)
	{
		char x = ch2n(asdf2[i]);
		x = x << 4;
		x += ch2n(asdf2[i + 1]);
		memcpy(data2 + (i / 2), &x, 1);
	}
	int endianInvVal = _byteswap_ulong(inventoryLen);
	memcpy(data2 + (asdf2.length() / 2) - 4, &endianInvVal, 4);
	endianInvVal = _byteswap_ulong(((PlayerInfo*)(peer->data))->currentInventorySize);
	memcpy(data2 + (asdf2.length() / 2) - 8, &endianInvVal, 4);
	int val = 0;
	for (int i = 0; i < inventoryLen; i++)
	{
		val = 0;
		val |= inventory.items.at(i).itemID;
		val |= inventory.items.at(i).itemCount << 16;
		val &= 0x00FFFFFF;
		val |= 0x00 << 24;
		memcpy(data2 + (i * 4) + (asdf2.length() / 2), &val, 4);
	}
	ENetPacket* packet3 = enet_packet_create(data2,
		packetLen,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete data2;
	//enet_host_flush(server);
}
void SearchInventoryItem(ENetPeer* peer, int fItemid, int fQuantity, bool& iscontains)
{
	iscontains = false;
	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount >= fQuantity) {
			iscontains = true;
			break;
		}
	}
}
bool SaveConvertedItemDls(int fItemid, int fQuantity, ENetPeer* peer)
{
		int invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;
		bool doesItemInInventryAlready = false;
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
		{
			if (((PlayerInfo*)(peer->data))->inventory.items[i].itemID == fItemid)
			{
				doesItemInInventryAlready = true;
				if (((PlayerInfo*)(peer->data))->inventory.items[i].itemCount >= 101) return false;
				break;
			}
		}
		try {
			std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			json jj;
			if (iffff.fail()) {
				iffff.close();
				cout << "SaveConvertedItem funkcijoje (ifstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
			}
			if (iffff.is_open()) {
			}
			iffff >> jj; //load
			std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			if (!oo.is_open()) {
				cout << GetLastError() << " SaveConvertedItem funkcijoje (ofstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
				_getch();
			}
			int howManyHasNow = 0;
			for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
			{
				int itemidFromJson = jj["items"][i]["itemid"];
				int quantityFromJson = jj["items"][i]["quantity"];;
				if (doesItemInInventryAlready)
				{
					if (itemidFromJson == fItemid)
					{
						howManyHasNow = jj["items"][i]["quantity"];
						howManyHasNow += fQuantity;
						jj["items"][i]["quantity"] = howManyHasNow;
						for (int k = 0; k < ((PlayerInfo*)(peer->data))->inventory.items.size(); k++)
						{
							if (((PlayerInfo*)(peer->data))->inventory.items[k].itemID == fItemid)
							{
								((PlayerInfo*)(peer->data))->inventory.items[k].itemCount += (short)fQuantity;
								break;
							}
						}
						sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
						break;
					}
				}
				else if (itemidFromJson == 0 && quantityFromJson == 0)
				{
					jj["items"][i]["quantity"] = fQuantity;
					jj["items"][i]["itemid"] = fItemid;
					InventoryItem item;
					item.itemID = fItemid;
					item.itemCount = fQuantity;
					((PlayerInfo*)(peer->data))->inventory.items.push_back(item);
					sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
					break;
				}
			}
			oo << jj << std::endl;
			//oo.close();
			return true;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
		}
		catch (...) {
			cout << "reading file violation" << endl;
		}
}
bool SaveConvertedItem(int fItemid, int fQuantity, ENetPeer* peer)
{
		int invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;
		bool doesItemInInventryAlready = false;
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
		{
			if (((PlayerInfo*)(peer->data))->inventory.items[i].itemID == fItemid)
			{
				doesItemInInventryAlready = true;
				if (((PlayerInfo*)(peer->data))->inventory.items[i].itemCount >= 200) return false;
				break;
			}
		}
		try {
			std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			json jj;
			if (iffff.fail()) {
				iffff.close();
				cout << "SaveConvertedItem funkcijoje (ifstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
			}
			if (iffff.is_open()) {
			}
			iffff >> jj; //load
			std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			if (!oo.is_open()) {
				cout << GetLastError() << " SaveConvertedItem funkcijoje (ofstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
				_getch();
			}
			int howManyHasNow = 0;
			for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
			{
				int itemidFromJson = jj["items"][i]["itemid"];
				int quantityFromJson = jj["items"][i]["quantity"];;
				if (doesItemInInventryAlready)
				{
					if (itemidFromJson == fItemid)
					{
						howManyHasNow = jj["items"][i]["quantity"];
						howManyHasNow += fQuantity;
						jj["items"][i]["quantity"] = howManyHasNow;
						for (int k = 0; k < ((PlayerInfo*)(peer->data))->inventory.items.size(); k++)
						{
							if (((PlayerInfo*)(peer->data))->inventory.items[k].itemID == fItemid)
							{
								((PlayerInfo*)(peer->data))->inventory.items[k].itemCount += (byte)fQuantity;
								break;
							}
						}
						sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
						break;
					}
				}
				else if (itemidFromJson == 0 && quantityFromJson == 0)
				{
					jj["items"][i]["quantity"] = fQuantity;
					jj["items"][i]["itemid"] = fItemid;
					InventoryItem item;
					item.itemID = fItemid;
					item.itemCount = fQuantity;
					((PlayerInfo*)(peer->data))->inventory.items.push_back(item);
					sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
					break;
				}
			}
			oo << jj << std::endl;
			//oo.close();
			return true;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
		}
		catch (...) {
			cout << "reading file violation" << endl;
		}
}
void SaveShopsItem(int fItemid, int fQuantity, ENetPeer* peer, bool& success)
{
		size_t invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;
		bool invfull = false;
		bool alreadyhave = false;
		if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsizee) {
			GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! Your inventory is full! You can purchase an inventory upgrade in the shop.|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|"));
			ENetPacket* packet = enet_packet_create(ps.data,
				ps.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete ps.data;
			alreadyhave = true;
		}
		bool iscontains = false;
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
		{
			if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid) {
				GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! Your inventory already contains this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|"));
				ENetPacket* packet = enet_packet_create(ps.data,
					ps.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete ps.data;
				iscontains = true;
			}
		}
		if (iscontains == true || alreadyhave == true)
		{
			success = false;
		}
		else
		{
			try {
				success = true;
				std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
				json jj;
				if (iffff.fail()) {
					iffff.close();
					cout << "SaveShopsItem funkcijoje (ifstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
				}
				if (iffff.is_open()) {
				}
				iffff >> jj; //load
				std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
				if (!oo.is_open()) {
					cout << GetLastError() << " SaveShopsItem funkcijoje (ofstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
					_getch();
				}
				//jj["items"][aposition]["aposition"] = aposition;
				for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
				{
					int itemid = jj["items"][i]["itemid"];
					int quantity = jj["items"][i]["quantity"];
					if (itemid == 0 && quantity == 0)
					{
						jj["items"][i]["itemid"] = fItemid;
						jj["items"][i]["quantity"] = fQuantity;
						break;
					}
				}
				oo << jj << std::endl;
				//oo.close();
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			catch (const std::out_of_range& e) {
				cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
			}
			catch (...) {
				cout << "reading file violation" << endl;
			}
			InventoryItem item;
			item.itemID = fItemid;
			item.itemCount = fQuantity;
			((PlayerInfo*)(peer->data))->inventory.items.push_back(item);
			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		}
}

int GetQuantityOfItem(ENetPeer* peer, int fItemId)
{
	int quantity = 0;

	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemId) {
			quantity = ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount;
			break;
		}
	}

	return quantity;
}
void SaveFindsItem(int fItemid, int fQuantity, ENetPeer* peer)
{
	try {
		std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		json jj;
		if (iffff.fail()) {
			iffff.close();
		}
		if (iffff.is_open()) {
		}
		iffff >> jj; //load
		std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		if (!oo.is_open()) {
			cout << GetLastError() << endl;
			_getch();
		}
		//jj["items"][aposition]["aposition"] = aposition;
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
		{
			int itemid = jj["items"][i]["itemid"];
			int quantity = jj["items"][i]["quantity"];
			if (itemid == 0 && quantity == 0)
			{
				jj["items"][i]["itemid"] = fItemid;
				jj["items"][i]["quantity"] = fQuantity;
				break;
			}
		}
		oo << jj << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
	}
	catch (...) {
		cout << "reading file violation" << endl;
	}
		InventoryItem item;
		item.itemID = fItemid;
		item.itemCount = fQuantity;
		((PlayerInfo*)(peer->data))->inventory.items.push_back(item);
		sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		//oo.close();
}
int countFreq(string& pat, string& txt)
{
	int M = pat.length();
	int N = txt.length();
	int res = 0;

	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++)
	{
		/* For current index i, check for
		   pattern match */
		int j;
		for (j = 0; j < M; j++)
			if (txt[i + j] != pat[j])
				break;

		// if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
		if (j == M)
		{
			res++;
			j = 0;
		}
	}
	return res;
}
bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}
void OnConsoleMessageAll(ENetPeer* peer, string message) {
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), message));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			enet_peer_send(currentPeer, 0, packet);
		}
	}
	delete p.data;
}
void RemoveItemFromInv(ENetPeer* peer, int itemId, int count, bool update)
{
	std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");

	json jj;

	if (iffff.fail()) {
		iffff.close();
		cout << "[!]  RemoveInventoryItem funkcijoje (ofstream dalyje) error: itemid - " << itemId << ", kiekis - " << count << endl;

	}
	if (iffff.is_open()) {


	}

	iffff >> jj; //load


	std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
	if (!oo.is_open()) {
		cout << GetLastError() << " RemoveInventoryItem funkcijoje (ofstream dalyje) error: itemid - " << itemId << ", kiekis - " << count << endl;
		_getch();
	}

	//jj["items"][aposition]["aposition"] = aposition;


	for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
	{
		int itemid = jj["items"][i]["itemid"];
		int quantity = jj["items"][i]["quantity"];
		if (itemid == itemId)
		{
			if (quantity - count == 0)
			{
				jj["items"][i]["itemid"] = 0;
				jj["items"][i]["quantity"] = 0;
			}
			else
			{
				jj["items"][i]["itemid"] = itemid;
				jj["items"][i]["quantity"] = quantity - count;
			}

			break;
		}

	}
	oo << jj << std::endl;

	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == itemId)
		{
			if ((unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount > count && (unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount != count)
			{
				((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount -= count;
			}
			else
			{
				((PlayerInfo*)(peer->data))->inventory.items.erase(((PlayerInfo*)(peer->data))->inventory.items.begin() + i);
			}
			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		}
	}


}

void RemoveInventoryItem(int fItemid, int fQuantity, ENetPeer* peer)
{
	try {
		std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		json jj;
		if (iffff.fail()) {
			iffff.close();
			cout << " RemoveInventoryItem funkcijoje (ofstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
		}
		if (iffff.is_open()) {
		}
		iffff >> jj; //load
		std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		if (!oo.is_open()) {
			cout << GetLastError() << " RemoveInventoryItem funkcijoje (ofstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
			_getch();
		}
		//jj["items"][aposition]["aposition"] = aposition;
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
		{
			int itemid = jj["items"][i]["itemid"];
			int quantity = jj["items"][i]["quantity"];
			if (itemid == fItemid)
			{
				if (quantity - fQuantity == 0)
				{
					jj["items"][i]["itemid"] = 0;
					jj["items"][i]["quantity"] = 0;
				}
				else
				{
					jj["items"][i]["itemid"] = itemid;
					jj["items"][i]["quantity"] = quantity - fQuantity;
				}
				break;
			}
		}
		oo << jj << std::endl;
		//oo.close();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
	}
	catch (...) {
		cout << "reading file violation" << endl;
	}
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
		{
			if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid)
			{
				if ((unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount > fQuantity && (unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount != fQuantity)
				{
					((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount -= fQuantity;
				}
				else
				{
					((PlayerInfo*)(peer->data))->inventory.items.erase(((PlayerInfo*)(peer->data))->inventory.items.begin() + i);
				}
				sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
			}
		}
}
void SaveInventoryWhenBuildingBlock(ENetPeer* peer)
{
	try {
		std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		json jj;
		if (iffff.fail()) {
			iffff.close();
			cout << "Klaida, skaitant inventoriu zaidejui " << ((PlayerInfo*)(peer->data))->rawName << " jam statant bloka worlde!" << endl;
		}
		if (iffff.is_open()) {
		}
		iffff >> jj; //load
		std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		if (!oo.is_open()) {
			cout << GetLastError() << endl;
			_getch();
		}
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
		{
			if (i < ((PlayerInfo*)(peer->data))->inventory.items.size())
			{
				jj["items"][i]["itemid"] = (unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID;
				jj["items"][i]["quantity"] = (unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount;
			}
			else
			{
				jj["items"][i]["itemid"] = 0;
				jj["items"][i]["quantity"] = 0;
			}
		}
		oo << jj << std::endl;
		if (oo.fail()) {
			oo.close();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
	}
	catch (...) {
		cout << "reading file violation" << endl;
	}
}
void GetPlayerFragments(string playerName, int& fEarth, int& fDark, int& fFire, int& fWater)
{
	ifstream fd("fragments/" + playerName + ".txt");
	fd >> fEarth;
	fd >> fDark;
	fd >> fFire;
	fd >> fWater;
	fd.close();
}
void GetPlayerGems(string playerName, int& plantgems)
{
	ifstream fd("gemstorage/" + playerName + ".txt");
	fd >> plantgems;
	fd.close();
}
void AddPlayerFragmentEarth(ENetPeer* peer, int count)
{
	int dabarTuriEarth = ((PlayerInfo*)(peer->data))->fEarth;
	int dabarTuriDark = ((PlayerInfo*)(peer->data))->fDark;
	int dabarTuriFire = ((PlayerInfo*)(peer->data))->fFire;
	int dabarTuriWater = ((PlayerInfo*)(peer->data))->fWater;
	ofstream ofrgm("fragments/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriEarth += count;
	ofrgm << dabarTuriEarth << endl;
	ofrgm << dabarTuriDark << endl;
	ofrgm << dabarTuriFire << endl;
	ofrgm << dabarTuriWater << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->fEarth = dabarTuriEarth;
}
void RemovePlayerPlantGems(ENetPeer* peer, int count)
{
	int dabarTuriPlantGems = ((PlayerInfo*)(peer->data))->plantgems;
	ofstream ofrgm("gemstorage/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriPlantGems -= count;
	ofrgm << dabarTuriPlantGems << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->plantgems = dabarTuriPlantGems;
}
void AddPlayerPlantGems(ENetPeer* peer, int count)
{
	int dabarTuriPlantGems = ((PlayerInfo*)(peer->data))->plantgems;
	ofstream ofrgm("gemstorage/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriPlantGems += count;
	ofrgm << dabarTuriPlantGems << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->plantgems = dabarTuriPlantGems;
}
void AddPlayerFragmentDark(ENetPeer* peer, int count)
{
	int dabarTuriEarth = ((PlayerInfo*)(peer->data))->fEarth;
	int dabarTuriDark = ((PlayerInfo*)(peer->data))->fDark;
	int dabarTuriFire = ((PlayerInfo*)(peer->data))->fFire;
	int dabarTuriWater = ((PlayerInfo*)(peer->data))->fWater;
	ofstream ofrgm("fragments/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriDark += count;
	ofrgm << dabarTuriEarth << endl;
	ofrgm << dabarTuriDark << endl;
	ofrgm << dabarTuriFire << endl;
	ofrgm << dabarTuriWater << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->fDark = dabarTuriDark;
}
void RemovePlayerFragmentDark(ENetPeer* peer, int count)
{
	int dabarTuriEarth = ((PlayerInfo*)(peer->data))->fEarth;
	int dabarTuriDark = ((PlayerInfo*)(peer->data))->fDark;
	int dabarTuriFire = ((PlayerInfo*)(peer->data))->fFire;
	int dabarTuriWater = ((PlayerInfo*)(peer->data))->fWater;
	ofstream ofrgm("fragments/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriDark -= count;
	ofrgm << dabarTuriEarth << endl;
	ofrgm << dabarTuriDark << endl;
	ofrgm << dabarTuriFire << endl;
	ofrgm << dabarTuriWater << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->fDark = dabarTuriDark;
}
void RemovePlayerFragmentFire(ENetPeer* peer, int count)
{
	int dabarTuriEarth = ((PlayerInfo*)(peer->data))->fEarth;
	int dabarTuriDark = ((PlayerInfo*)(peer->data))->fDark;
	int dabarTuriFire = ((PlayerInfo*)(peer->data))->fFire;
	int dabarTuriWater = ((PlayerInfo*)(peer->data))->fWater;
	ofstream ofrgm("fragments/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriFire -= count;
	ofrgm << dabarTuriEarth << endl;
	ofrgm << dabarTuriDark << endl;
	ofrgm << dabarTuriFire << endl;
	ofrgm << dabarTuriWater << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->fFire = dabarTuriFire;
}
void RemovePlayerFragmentEarth(ENetPeer* peer, int count)
{
	int dabarTuriEarth = ((PlayerInfo*)(peer->data))->fEarth;
	int dabarTuriDark = ((PlayerInfo*)(peer->data))->fDark;
	int dabarTuriFire = ((PlayerInfo*)(peer->data))->fFire;
	int dabarTuriWater = ((PlayerInfo*)(peer->data))->fWater;
	ofstream ofrgm("fragments/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriEarth -= count;
	ofrgm << dabarTuriEarth << endl;
	ofrgm << dabarTuriDark << endl;
	ofrgm << dabarTuriFire << endl;
	ofrgm << dabarTuriWater << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->fEarth = dabarTuriEarth;
}
void AddPlayerFragmentFire(ENetPeer* peer, int count)
{
	int dabarTuriEarth = ((PlayerInfo*)(peer->data))->fEarth;
	int dabarTuriDark = ((PlayerInfo*)(peer->data))->fDark;
	int dabarTuriFire = ((PlayerInfo*)(peer->data))->fFire;
	int dabarTuriWater = ((PlayerInfo*)(peer->data))->fWater;
	ofstream ofrgm("fragments/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriFire += count;
	ofrgm << dabarTuriEarth << endl;
	ofrgm << dabarTuriDark << endl;
	ofrgm << dabarTuriFire << endl;
	ofrgm << dabarTuriWater << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->fFire = dabarTuriFire;
}
void AddPlayerFragmentWater(ENetPeer* peer, int count)
{
	int dabarTuriEarth = ((PlayerInfo*)(peer->data))->fEarth;
	int dabarTuriDark = ((PlayerInfo*)(peer->data))->fDark;
	int dabarTuriFire = ((PlayerInfo*)(peer->data))->fFire;
	int dabarTuriWater = ((PlayerInfo*)(peer->data))->fWater;
	ofstream ofrgm("fragments/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	dabarTuriWater += count;
	ofrgm << dabarTuriEarth << endl;
	ofrgm << dabarTuriDark << endl;
	ofrgm << dabarTuriFire << endl;
	ofrgm << dabarTuriWater << endl;
	ofrgm.close();
	((PlayerInfo*)(peer->data))->fWater = dabarTuriWater;
}
void UpdateLocalPlayerFragments(ENetPeer* peer)
{
	ifstream ifrgm("fragments/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	ifrgm >> ((PlayerInfo*)(peer->data))->fEarth;
	ifrgm >> ((PlayerInfo*)(peer->data))->fDark;
	ifrgm >> ((PlayerInfo*)(peer->data))->fFire;
	ifrgm >> ((PlayerInfo*)(peer->data))->fWater;
	ifrgm.close();
}
void UpdateLocalPlayerGems(ENetPeer* peer)
{
	ifstream ifrgm("gemstorage/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	ifrgm >> ((PlayerInfo*)(peer->data))->plantgems;
	ifrgm.close();
}
void GiveChestPrizeGems(ENetPeer* peer, int gemsAmount)
{
	int currentGems = 0;
	ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	ifs >> currentGems;
	ifs.close();
	currentGems += gemsAmount;
	ofstream ofs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	ofs << currentGems;
	ofs.close();
	GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), currentGems));
	ENetPacket* packetpp = enet_packet_create(pp.data,
		pp.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packetpp);
	delete pp.data;
	Player::OnConsoleMessage(peer, "`9[LOOT] `^You have obtained `9" + to_string(gemsAmount) + "`# Gems`^!");
	Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`q" + ((PlayerInfo*)(peer->data))->displayName + " `^Have obtained `9" + to_string(gemsAmount) + " `#Gems`^!", 0, true);
	int effect = 30;
	int x = ((PlayerInfo*)(peer->data))->x;
	int y = ((PlayerInfo*)(peer->data))->y;
	Player::OnParticleEffect(peer, effect, x, y, 0);
}
void GiveChestPrizeCrystal(ENetPeer* peer, string crystalName, int crystalAmount)
{
	try {
		std::ifstream iffff("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		json jj;
		if (iffff.fail()) {
			iffff.close();
		}
		if (iffff.is_open()) {
		}
		iffff >> jj; //load
		int wonCrystalNow = jj[crystalName];
		int currentWonCrystals = wonCrystalNow + crystalAmount;
		jj[crystalName] = currentWonCrystals;
		std::ofstream oo("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		if (!oo.is_open()) {
			cout << GetLastError() << ". GiveChestPrizeCrystal funkcijoje. crystal name buvo " << crystalName << ". Amount - " << crystalAmount << endl;
			_getch();
		}
		if (crystalName == "emerald")
		{
			((PlayerInfo*)(peer->data))->emerald += crystalAmount;
		}
		else if (crystalName == "diamond")
		{
			((PlayerInfo*)(peer->data))->diamond += crystalAmount;
		}
		else if (crystalName == "sapphire")
		{
			((PlayerInfo*)(peer->data))->sapphire += crystalAmount;
		}
		else if (crystalName == "ruby")
		{
			((PlayerInfo*)(peer->data))->rubble += crystalAmount;
		}
		else if (crystalName == "gold")
		{
			((PlayerInfo*)(peer->data))->gold += crystalAmount;
		}
		else if (crystalName == "opal")
		{
			((PlayerInfo*)(peer->data))->opal += crystalAmount;
		}
		else if (crystalName == "amber")
		{
			((PlayerInfo*)(peer->data))->amber += crystalAmount;
		}
		oo << jj << std::endl;
		if (crystalAmount == 0)
		{
			GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`q" + ((PlayerInfo*)(peer->data))->displayName + " `^You wasnt lucky enought to get crystal..."), 0));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
		else {
			Player::OnConsoleMessage(peer, "`9[LOOT] `^You have obtained `4" + to_string(crystalAmount) + " `9" + crystalName + "'s`^!");
			GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`q" + ((PlayerInfo*)(peer->data))->displayName + " `^Have obtained `4" + to_string(crystalAmount) + " `9" + crystalName + "'s`^!"), 0));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
		int effect = 47;
		int x = ((PlayerInfo*)(peer->data))->x;
		int y = ((PlayerInfo*)(peer->data))->y;
		Player::OnParticleEffect(peer, effect, x, y, 0);
		//oo.close();
		iffff.close();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
	}
	catch (...) {
		cout << "reading file violation" << endl;
	}
}
void onPeerConnect(ENetPeer* peer)
{
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (peer != currentPeer)
		{
			if (isHere(peer, currentPeer))
			{
				string netIdS = std::to_string(((PlayerInfo*)(currentPeer->data))->netID);
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + netIdS + "\nuserID|" + netIdS + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(((PlayerInfo*)(currentPeer->data))->x) + "|" + std::to_string(((PlayerInfo*)(currentPeer->data))->y) + "\nname|``" + ((PlayerInfo*)(currentPeer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(currentPeer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\n")); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
				string netIdS2 = std::to_string(((PlayerInfo*)(peer->data))->netID);
				GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + netIdS2 + "\nuserID|" + netIdS2 + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(((PlayerInfo*)(peer->data))->x) + "|" + std::to_string(((PlayerInfo*)(peer->data))->y) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\n")); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
			}
		}
	}

}
void sendSound(ENetPeer* peer, string sound)
{
	string text = "action|play_sfx\nfile|audio/" + sound + "\ndelayMS|0\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	ENetPacket* packet2 = enet_packet_create(data,
		5 + text.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete data;
}
void sendTime(ENetPeer* peer)
{
	using namespace std::chrono;
	int kiekDarCurse = 0;
	int kiekDarMute = 0;
	string curseText = "none";
	string muteText = "none";
	if (std::experimental::filesystem::exists("cursedplayers/" + ((PlayerInfo*)(peer->data))->rawName + ".txt"))
	{
		int kiekDarCurse = ((PlayerInfo*)(peer->data))->lastCursed - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		curseText = "`4Curse expires in `2" + OutputBanTime(kiekDarCurse / 1000) + "";
	}
	if (std::experimental::filesystem::exists("timemuted/" + ((PlayerInfo*)(peer->data))->rawName + ".txt"))
	{
		int kiekDarMute = ((PlayerInfo*)(peer->data))->lastMuted - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		muteText = "`4Mute expires in `2" + OutputBanTime(kiekDarMute / 1000) + "";
	}
	time_t _tm = time(NULL);
	struct tm* curtime = localtime(&_tm);
	string test = asctime(curtime);
	GamePacket p;
	if (curseText == "none" && muteText == "none")
	{
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`2Current time is: " + test + "`7You are not `bcursed `7and `bmuted"));
	}
	else if (curseText != "none" && muteText == "none")
	{
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`2Current time is: " + test + "`4You are `bcursed!\n" + curseText + ""));
	}
	else if (curseText == "none" && muteText != "none")
	{
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`2Current time is: " + test + "`4You are `bmuted!\n" + muteText + ""));
	}
	else
	{
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`2Current time is: " + test + "`4You are `bcursed `4and `bmuted!\n" + curseText + "\n" + muteText));
	}
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

void sendnews(ENetPeer* peer)
{
	try {
		std::ifstream ifs("news.txt");
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		Player::OnDialogRequest(peer, content);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
	}
	catch (...) {
		cout << "reading file violation" << endl;
	}
}
void updateAllClothes(ENetPeer* peer)
{
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			GamePacket p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants), ((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand), ((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace), ((PlayerInfo*)(peer->data))->skinColor), ((PlayerInfo*)(peer->data))->cloth_ances, 0.0f, 0.0f));
			memcpy(p3.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
			ENetPacket* packet3 = enet_packet_create(p3.data,
				p3.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet3);
			delete p3.data;
			GamePacket p4 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(currentPeer->data))->cloth_hair, ((PlayerInfo*)(currentPeer->data))->cloth_shirt, ((PlayerInfo*)(currentPeer->data))->cloth_pants), ((PlayerInfo*)(currentPeer->data))->cloth_feet, ((PlayerInfo*)(currentPeer->data))->cloth_face, ((PlayerInfo*)(currentPeer->data))->cloth_hand), ((PlayerInfo*)(currentPeer->data))->cloth_back, ((PlayerInfo*)(currentPeer->data))->cloth_mask, ((PlayerInfo*)(currentPeer->data))->cloth_necklace), ((PlayerInfo*)(currentPeer->data))->skinColor), ((PlayerInfo*)(currentPeer->data))->cloth_ances, 0.0f, 0.0f));
			memcpy(p4.data + 8, &(((PlayerInfo*)(currentPeer->data))->netID), 4); // ffloor
			ENetPacket* packet4 = enet_packet_create(p4.data,
				p4.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet4);
			delete p4.data;
		}
	}
}
void sendClothes(ENetPeer* peer)
{
	if (((PlayerInfo*)(peer->data))->currentWorld == "EXIT")
	{
		return;
	}
	ENetPeer* currentPeer;
	GamePacket p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants), ((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand), ((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace), ((PlayerInfo*)(peer->data))->skinColor), ((PlayerInfo*)(peer->data))->cloth_ances, 0.0f, 0.0f));
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			memcpy(p3.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
			ENetPacket* packet3 = enet_packet_create(p3.data,
				p3.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet3);
		}
	}
	if (((PlayerInfo*)(peer->data))->haveGrowId) {
		try {
			std::ifstream ifff("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			PlayerInfo* p = ((PlayerInfo*)(peer->data));
			string username = PlayerDB::getProperName(p->rawName);
			if (ifff.fail()) {
				ifff.close();
			}
			if (ifff.is_open()) {
			}
			json j;
			ifff >> j; //load
			int clothback = p->cloth_back;
			int clothhand = p->cloth_hand;
			int clothface = p->cloth_face;
			int clothhair = p->cloth_hair;
			int clothfeet = p->cloth_feet;
			int clothpants = p->cloth_pants;
			int clothneck = p->cloth_necklace;
			int clothshirt = p->cloth_shirt;
			int clothmask = p->cloth_mask;
			int clothances = p->cloth_ances;
			j["ClothBack"] = clothback;
			j["ClothHand"] = clothhand;
			j["ClothFace"] = clothface;
			j["ClothShirt"] = clothshirt;
			j["ClothPants"] = clothpants;
			j["ClothNeck"] = clothneck;
			j["ClothHair"] = clothhair;
			j["ClothFeet"] = clothfeet;
			j["ClothMask"] = clothmask;
			j["ClothAnces"] = clothances;
			std::ofstream o("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json"); //save
			if (!o.is_open()) {
				cout << GetLastError() << endl;
				_getch();
			}
			o << j << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
		}
		catch (...) {
			cout << "reading file violation" << endl;
		}
	}
	delete p3.data;
}
void showWrong(ENetPeer* peer, string listFull, string itemFind) {
	Player::OnDialogRequest(peer, "add_label_with_icon|big|`9Find item: " + itemFind + "``|left|3146|\n" + listFull + "add_textbox|Enter a word below to find the item|\nadd_text_input|item|Item Name||30|\nend_dialog|findid|Cancel|Find the item!|\n");
}
void SaveShopsItemMoreTimesLoginis(int fItemid, int fQuantity, ENetPeer* peer, bool& success)
{
	size_t invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;
	bool invfull = false;
	bool alreadyhave = false;
	if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsizee) {
		Player::OnDialogRequest(peer, "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! Your inventory is full! You can purchase an inventory upgrade in the shop.|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|");
		alreadyhave = true;
	}
	bool isFullStock = false;
	bool isInInv = false;
	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount >= 101) {
			Player::OnDialogRequest(peer, "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! You already have full stock of this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|");
			isFullStock = true;
		}
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount < 200)	isInInv = true;
	}
	if (isFullStock == true || alreadyhave == true)
	{
		success = false;
	}
	else
	{
		try {
			success = true;
			std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			json jj;
			if (iffff.fail()) {
				iffff.close();
			}
			if (iffff.is_open()) {
			}
			iffff >> jj; //load
			std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			if (!oo.is_open()) {
				cout << GetLastError() << endl;
				_getch();
			}
			if (isInInv == false)
			{
				for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
				{
					int itemid = jj["items"][i]["itemid"];
					int quantity = jj["items"][i]["quantity"];
					if (itemid == 0 && quantity == 0)
					{
						jj["items"][i]["itemid"] = fItemid;
						jj["items"][i]["quantity"] = fQuantity;
						break;
					}
				}
				oo << jj << std::endl;
				InventoryItem item;
				item.itemID = fItemid;
				item.itemCount = fQuantity;
				((PlayerInfo*)(peer->data))->inventory.items.push_back(item);
				sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
			}
			else
			{
				for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
				{
					int itemid = jj["items"][i]["itemid"];
					int quantity = jj["items"][i]["quantity"];
					if (itemid == fItemid)
					{
						jj["items"][i]["quantity"] = quantity + fQuantity;
						break;
					}
				}
				oo << jj << std::endl;
				for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
				{
					if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid)
					{
						((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount += fQuantity;
						sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
					}
				}
			}
			iffff.close();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
		}
		catch (...) {
			cout << "reading file violation" << endl;
		}
	}
}
void SaveShopsItemMoreTimes(int fItemid, int fQuantity, ENetPeer* peer, bool& success)
{
	size_t invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;
	bool invfull = false;
	bool alreadyhave = false;
	if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsizee) {
		Player::OnDialogRequest(peer, "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! Your inventory is full! You can purchase an inventory upgrade in the shop.|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|");
		alreadyhave = true;
	}
	bool isFullStock = false;
	bool isInInv = false;
	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount >= 200) {
			Player::OnDialogRequest(peer, "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! You already have full stock of this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|");
			isFullStock = true;
		}
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount < 200)	isInInv = true;
	}
	if (isFullStock == true || alreadyhave == true)
	{
		success = false;
	}
	else
	{
		try {
			success = true;
			std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			json jj;
			if (iffff.fail()) {
				iffff.close();
			}
			if (iffff.is_open()) {
			}
			iffff >> jj; //load
			std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
			if (!oo.is_open()) {
				cout << GetLastError() << endl;
				_getch();
			}
			if (isInInv == false)
			{
				for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
				{
					int itemid = jj["items"][i]["itemid"];
					int quantity = jj["items"][i]["quantity"];
					if (itemid == 0 && quantity == 0)
					{
						jj["items"][i]["itemid"] = fItemid;
						jj["items"][i]["quantity"] = fQuantity;
						break;
					}
				}
				oo << jj << std::endl;
				InventoryItem item;
				item.itemID = fItemid;
				item.itemCount = fQuantity;
				((PlayerInfo*)(peer->data))->inventory.items.push_back(item);
				sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
			}
			else
			{
				for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
				{
					int itemid = jj["items"][i]["itemid"];
					int quantity = jj["items"][i]["quantity"];
					if (itemid == fItemid)
					{
						jj["items"][i]["quantity"] = quantity + fQuantity;
						break;
					}
				}
				oo << jj << std::endl;
				for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
				{
					if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid)
					{
						((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount += fQuantity;
						sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
					}
				}
			}
			iffff.close();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			cout << "[try-catch ERROR]: Out of Range error in id == 'wk'" << endl;
		}
		catch (...) {
			cout << "reading file violation" << endl;
		}

	}
}
void givequestkatanastep2xp(ENetPeer* peer, int amount)
{
	string cQuest = "None";
	ifstream fileStream213("quests/currentquest/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	fileStream213 >> cQuest;
	fileStream213.close();
	int sQuest = 1;
	ifstream fileStream216("quests/currentqueststep/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	fileStream216 >> sQuest;
	fileStream216.close();
	if (cQuest == "Katana" && sQuest == 2)
	{
		int alrdadded = 0;
		ifstream fileStream316("quests/katana/step2/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		fileStream316 >> alrdadded;
		fileStream316.close();
		int willaddnow = alrdadded + amount;
		ofstream fileStream219("quests/katana/step2/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		fileStream219 << willaddnow;
		fileStream219.close();
	}
}
void givequestkatanastep3storetoken(ENetPeer* peer, int amount)
{
	string cQuest = "None";
	ifstream fileStream213("quests/currentquest/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	fileStream213 >> cQuest;
	fileStream213.close();
	int sQuest = 1;
	ifstream fileStream216("quests/currentqueststep/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
	fileStream216 >> sQuest;
	fileStream216.close();
	if (cQuest == "Katana" && sQuest == 3)
	{
		int alrdadded = 0;
		ifstream fileStream316("quests/katana/step3/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		fileStream316 >> alrdadded;
		fileStream316.close();
		int willaddnow = alrdadded + amount;
		ofstream fileStream219("quests/katana/step3/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		fileStream219 << willaddnow;
		fileStream219.close();
	}
}
void Player::OnInvis(ENetPeer* peer, int state, int netID) {
	GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), state));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnFailedToEnterWorld(ENetPeer* peer) {
	GamePacket p = packetEnd(appendIntx(appendString(createPacket(), "OnFailedToEnterWorld"), 1));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnTextOverlay(ENetPeer* peer, string text) {
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), text));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnKilled(ENetPeer* peer, int netID) {
	GamePacket p = packetEnd(appendString(createPacket(), "OnKilled"));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::SetRespawnPos(ENetPeer* peer, int posX, int posY, int netID) {
	GamePacket p22 = packetEnd(appendInt(appendString(createPacket(), "SetRespawnPos"), posX + posY)); // (world->width * posY)
	memcpy(p22.data + 8, &netID, 4);
	ENetPacket* packet22 = enet_packet_create(p22.data,
		p22.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet22);
	delete p22.data;
}
void Player::OnZoomCamera(ENetPeer* peer, float value1, int value2) {
	GamePacket p = packetEnd(appendIntx(appendFloat(appendString(createPacket(), "OnZoomCamera"), value1), value2));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::SmoothZoom(ENetPeer* peer) {
	GamePacket p = packetEnd(appendIntx(appendFloat(appendString(createPacket(), "OnZoomCamera"), 10000.0f), 1000));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnRaceStart(ENetPeer* peer, int netID)
{
	GamePacket p = packetEnd(appendString(createPacket(), "OnRaceStart"));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnRaceEnd(ENetPeer* peer, int netID)
{
	GamePacket p = packetEnd(appendString(createPacket(), "OnRaceStart"));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::Ping(ENetPeer* peer)
{
	GamePacket p = packetEnd(appendString(createPacket(), "Ping"));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnDialogRequest(ENetPeer* peer, string args)
{
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), args));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnSetPos(ENetPeer* peer, int netID, int x, int y) {
	GamePacket p = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnSetFreezeState(ENetPeer* peer, int state, int netID) {
	GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), state));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnSetCurrentWeather(ENetPeer* peer, int weather) {
	GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), weather));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnTradeStatus(ENetPeer* peer, int netIDOther, string offerstatus, string offer)
{
	GamePacket p = packetEnd(appendString(appendString(appendString(appendInt(appendString(createPacket(), "OnTradeStatus"), netIDOther), ""), offerstatus + "'s offer"), offer));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnSetBux(ENetPeer* peer, int gems, int accountstate)
{
	GamePacket p = packetEnd(appendInt(appendInt(appendString(createPacket(), "OnSetBux"), gems), accountstate));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnParticleEffect(ENetPeer* peer, int effect, float x, float y, int delay) {
	GamePacket p = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), effect), x, y));
	int deathFlag = 0x19;
	memcpy(p.data + 24, &delay, 4);
	memcpy(p.data + 56, &deathFlag, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::SetHasGrowID(ENetPeer* peer, int status, string username, string password)
{
	GamePacket p2 = packetEnd(appendString(appendString(appendInt(appendString(createPacket(), "SetHasGrowID"), status), username), password));
	ENetPacket* packet2 = enet_packet_create(p2.data,
		p2.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete p2.data;
}
void Player::OnNameChanged(ENetPeer* peer, int netID, string name)
{
	GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`0`0" + name));
	memcpy(p3.data + 8, &netID, 4);
	ENetPacket* packet3 = enet_packet_create(p3.data,
		p3.len,
		ENET_PACKET_FLAG_RELIABLE);
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			enet_peer_send(currentPeer, 0, packet3);
		}
	}
	delete p3.data;
}
void Player::OnSendToServer(ENetPeer* peer, int userID, int token, string ip, int port, string doorId, int lmode)
{
	auto p = packetEnd(appendInt(appendString(appendInt(appendInt(appendInt(appendString(createPacket(), "OnSendToServer"), port), token), userID), ip + "|" + doorId), lmode));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnChangeSkin(ENetPeer* peer, int skinColor, int netID) {
	auto p = packetEnd(appendInt(appendString(createPacket(), "OnChangeSkin"), skinColor));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnCountdownStart(ENetPeer* peer, int netID, int time, int score) {
	if (score == -1) {
		auto p = packetEnd(appendInt(appendString(createPacket(), "OnCountdownStart"), time));
		memcpy(p.data + 8, &netID, 4);
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	else
	{
		auto p = packetEnd(appendInt(appendInt(appendString(createPacket(), "OnCountdownStart"), time), score));
		memcpy(p.data + 8, &netID, 4);
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}
void Player::OnPlayPositioned(ENetPeer* peer, string audiofile, int netID, bool broadcastInWorld, ENetPacket* pk) // packet only externally used when broadcasting / sending to multiple players to reduce memory leaks / cpu usage cuz we dont want to loop creating the packet for each player that would be insanely stupid.
{
	if (broadcastInWorld) {
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, pk);
			}
		}
	}
	else
	{
		auto p = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), audiofile));
		memcpy(p.data + 8, &netID, 4);
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}
void Player::OnBillboardChange(ENetPeer* peer, int netID) {
	GamePacket p = packetEnd(appendInt(appendInt(appendInt(appendInt(appendIntx(appendString(createPacket(), "OnBillboardChange"), 1), 12), 1), 5), 1)); //2 == ItemID
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnFlagMay2019(ENetPeer* peer, int state, int netID) {
	GamePacket p = packetEnd(appendIntx(appendString(createPacket(), "OnFlagMay2019"), state));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnStartTrade(ENetPeer* peer, int netID1, int netID2)
{
	GamePacket p = packetEnd(appendInt(appendInt(appendString(createPacket(), "OnStartTrade"), netID1), netID2));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnForceTradeEnd(ENetPeer* peer)
{
	GamePacket p = packetEnd(appendString(createPacket(), "OnForceTradeEnd"));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::PlayAudio(ENetPeer* peer, string audioFile, int delayMS)
{
	string text = "action|play_sfx\nfile|" + audioFile + "\ndelayMS|" + to_string(delayMS) + "\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	ENetPacket* packet = enet_packet_create(data,
		5 + text.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete data;
}
void Player::OnRemove(ENetPeer* peer, int netID)
{
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(netID) + "\n"));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnConsoleMessage(ENetPeer* peer, string text)
{
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), text));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void Player::OnTalkBubble(ENetPeer* peer, int netID, string text, int chatColor, bool isOverlay)
{
	if (isOverlay == true) {
		GamePacket p = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"),
			((PlayerInfo*)(peer->data))->netID), text), chatColor), 1));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	else
	{
		GamePacket p = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"),
			((PlayerInfo*)(peer->data))->netID), text), chatColor));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}
void Player::OnAddNotification(ENetPeer* peer, string text, string audiosound, string interfaceimage)
{
	auto p = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"),
		interfaceimage),
		text),
		audiosound),
		0));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}