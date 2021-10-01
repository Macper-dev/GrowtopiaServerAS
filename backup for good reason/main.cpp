#include "stdafx.h"
#include <iostream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "enet/enet.h"
#include <string>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif
#ifdef __linux__
#include <stdio.h>
char _getch() {
	return getchar();
}
#endif
#include <vector>
#include <sstream>
#include <chrono>
#include <fstream>
#include "json.hpp"
#ifdef _WIN32
#include "bcrypt.h"
#include "crypt_blowfish/crypt_gensalt.cpp"
#include "crypt_blowfish/crypt_blowfish.h"
#include "crypt_blowfish/crypt_blowfish.cpp"
#include "crypt_blowfish/ow-crypt.cpp"
#include "bcrypt.cpp"
#else
#include "bcrypt.h"
#include "bcrypt.cpp"
#include "crypt_blowfish/crypt_gensalt.h"
#include "crypt_blowfish/crypt_gensalt.cpp"
#include "crypt_blowfish/crypt_blowfish.h"
#include "crypt_blowfish/crypt_blowfish.cpp"
#include "crypt_blowfish/ow-crypt.h"
#include "crypt_blowfish/ow-crypt.cpp"
#include "bcrypt.h"
#endif
#include <thread> // TODO
#include <mutex> // TODO
#include "gamepacket.h"
#include "server.h"
#include "player.h"
#include <WinSock2.h>
#include <experimental/filesystem>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <regex>

#include <mysql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#pragma warning(disable : 4996)

using namespace std;
using json = nlohmann::json;

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

//#define TOTAL_LOG
#define REGISTRATION
#include <signal.h>
#ifdef __linux__
#include <cstdint>
typedef unsigned char BYTE;
typedef unsigned char __int8;
typedef unsigned short __int16;
typedef unsigned int DWORD;
#endif

//Linux equivalent of GetLastError
#ifdef __linux__
string GetLastError() {
	return strerror(errno);
}
//Linux has no byteswap functions.
ulong _byteswap_ulong(ulong x)
{
	// swap adjacent 32-bit blocks
	//x = (x >> 32) | (x << 32);
	// swap adjacent 16-bit blocks
	x = ((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16);
	// swap adjacent 8-bit blocks
	return ((x & 0xFF00FF00FF00FF00) >> 8) | ((x & 0x00FF00FF00FF00FF) << 8);
}
#endif

//configs



/***bcrypt***/

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

/***bcrypt
*/


void GenerateRegularWorld(WorldInfo* world, int width, int height, int dirtType = 2, int lavaType = 4, int mainDoorType = 6, int bedrockType = 8, int rockType = 10, int caveBackgroundType = 14, int machineId = 0)
{
	world->weather = machineId;
	int mainDoorX = (rand() % (world->width - 4)) + 2;
	for (int i = 0; i < world->width * world->height; i++)
	{
		world->items[i].foreground = 0;
	}
	for (int i = 0; i < world->width * world->height; i++)
	{
		if (i >= 3800 && i < 5400 && !(rand() % 50)) { world->items[i].foreground = rockType; }
		else if (i >= 3700 && i < 5400) {
			if (i > 5000) {
				int m = rand() % 8;
				if (m < 3) { world->items[i].foreground = lavaType; }
				else { world->items[i].foreground = dirtType; }
			}
			else { world->items[i].foreground = dirtType; }
		}
		else if (i >= 5400) { world->items[i].foreground = bedrockType; }

		if (i == 3600 + mainDoorX)
			world->items[i].foreground = mainDoorType;
		if (i == 3700 + mainDoorX)
			world->items[i].foreground = bedrockType;
		if (i >= 3700)
			world->items[i].background = caveBackgroundType;
		//nobody wants grass
		//else if (i >= 3600 && i < 3700)
		//	world->blocks[i].foreground = 0; 
	}
}


void generateOcean(WorldInfo* world, int width, int height, int dirtType = 2, int lavaType = 4, int mainDoorType = 6, int bedrockType = 8, int rockType = 10, int caveBackgroundType = 14, int wmachineid = 0, int deco1Id = 0, int deco2Id = 0, int id = 0)
{
	world->weather = wmachineid;
	for (int i = 0; i < world->width * world->height; i++)
	{
		world->items[i].foreground = 0;
	}
	int* offset = new int[width];
	int* offset2 = new int[width];
	offset[0] = (height - 60 < 0) ? -10 : height - 60;
	offset2[0] = offset[0] < 0 ? -10 : offset[0];

	auto settile = [](WorldInfo* w, int x, int y, int id) {
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			w->items[x + y * w->width].foreground = id;
	};
	auto settilebg = [](WorldInfo* w, int x, int y, int id) {
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			w->items[x + y * w->width].background = id;
	};
	auto gettile = [](WorldInfo* w, int x, int y) {
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			return w->items[x + y * w->width].foreground;
		return (short)0;
	};
	auto gettilebg = [](WorldInfo* w, int x, int y) {
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			return w->items[x + y * w->width].background;
		return (short)0;
	};

	for (int i = 1; i < width; i++)
	{
		offset[i] = (height - 60 < 0) ? -10 : height - 60;
		int rnd = rand() % 30 - 10;
		if (rnd < -2)
			offset[i] = offset[i - 1] - 1; // rise
		else if (rnd > 11)
			offset[i] = offset[i - 1] + 1; // fall
		else
			offset[i] = offset[i - 1]; // no change
		offset2[i] = offset[i] < 0 ? -10 : offset[i];
	}
	// now we generate the world.
	for (int j = 0; j < width; j++)
	{
		for (int k = 26 + offset[j]; k < height - 5; k++)
		{
			settile(world, j, k, dirtType);
			settilebg(world, j, k, caveBackgroundType);
			int renrnd = rand() % 12;
			if (renrnd > 10)
				settile(world, j, k, rockType);
		}
		settile(world, j, 26 + offset[j], dirtType);
		settilebg(world, j, 26 + offset[j], caveBackgroundType);
		settile(world, j, height - 6, bedrockType);
		settile(world, j, height - 5, bedrockType);
		settile(world, j, height - 4, bedrockType);
		settile(world, j, height - 3, bedrockType);
		settile(world, j, height - 2, bedrockType);
		settile(world, j, height - 1, bedrockType);

		settilebg(world, j, height - 6, caveBackgroundType);
		settilebg(world, j, height - 5, caveBackgroundType);
		settilebg(world, j, height - 4, caveBackgroundType);
		settilebg(world, j, height - 3, caveBackgroundType);
		settilebg(world, j, height - 2, caveBackgroundType);
		settilebg(world, j, height - 1, caveBackgroundType);
	}
	cout << endl;
	for (int srg = height - 10; srg < height - 6; srg++)
	{
		for (int dhk = 0; dhk < width; dhk++)
		{
			int djkf = rand() % 2;
			if (djkf == 1)
			{
				settile(world, dhk, srg, lavaType);
			}
		}
	}
	if (id & BlastProperties_WaterLevelD2)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = deco2Id; j < height; j++)
			{
				if (gettile(world, i, j) == 0)
				{
					if (i < world->width && i >= 0 && j < world->height && j >= 0)
						world->items[i + j * world->width].water = 1;
				}
			}
		}
	}
	else if (id & BlastProperties_RandomDeco1)
	{
		int deco1Count = rand() % 25 + 3;
		for (int i = 0; i < deco1Count; i++)
		{
			int a = rand() % width;
			settile(world, a, 25 + offset[a], deco1Id);
		}
	}
	else if (id & BlastProperties_RandomDeco2)
	{
		int deco2Count = rand() % 25 + 3;
		for (int i = 0; i < deco2Count; i++)
		{
			int a = rand() % width;
			settile(world, a, 25 + offset[a], deco2Id);
		}
	}


regenerate:
	int mainDoorX = (rand() % (width - 4)) + 2;
	int f = 25 + offset[mainDoorX];
	while (gettile(world, mainDoorX, f) != 0)
	{
		f--;
		if (f < 0) goto regenerate;
	}
	settile(world, mainDoorX, f, mainDoorType);
	settile(world, mainDoorX, f + 1, bedrockType);

	delete offset;
	delete offset2;

	for (int i = 0; i < world->width * world->height; i++)
	{
		world->items[i].water = true;
	}

}



void GenerateGrowaloneLikeWorld(WorldInfo* world, int width, int height, int dirtType = 2, int lavaType = 4, int mainDoorType = 6, int bedrockType = 8, int rockType = 10, int caveBackgroundType = 14, int wmachineid = 0, int deco1Id = 0, int deco2Id = 0, int id = 0)
{
	world->weather = wmachineid;
	for (int i = 0; i < world->width * world->height; i++)
	{
		world->items[i].foreground = 0;
	}
	int* offset = new int[width];
	int* offset2 = new int[width];
	offset[0] = (height - 60 < 0) ? -10 : height - 60;
	offset2[0] = offset[0] < 0 ? -10 : offset[0];

	auto settile = [](WorldInfo* w, int x, int y, int id) {
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			w->items[x + y * w->width].foreground = id;
	};
	auto settilebg = [](WorldInfo* w, int x, int y, int id) {
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			w->items[x + y * w->width].background = id;
	};
	auto gettile = [](WorldInfo* w, int x, int y) {
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			return w->items[x + y * w->width].foreground;
		return (short)0;
	};
	auto gettilebg = [](WorldInfo* w, int x, int y) {
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			return w->items[x + y * w->width].background;
		return (short)0;
	};

	for (int i = 1; i < width; i++)
	{
		offset[i] = (height - 60 < 0) ? -10 : height - 60;
		int rnd = rand() % 30 - 10;
		if (rnd < -2)
			offset[i] = offset[i - 1] - 1; // rise
		else if (rnd > 11)
			offset[i] = offset[i - 1] + 1; // fall
		else
			offset[i] = offset[i - 1]; // no change
		offset2[i] = offset[i] < 0 ? -10 : offset[i];
	}
	// now we generate the world.
	for (int j = 0; j < width; j++)
	{
		for (int k = 26 + offset[j]; k < height - 5; k++)
		{
			settile(world, j, k, dirtType);
			settilebg(world, j, k, caveBackgroundType);
			int renrnd = rand() % 12;
			if (renrnd > 10)
				settile(world, j, k, rockType);
		}
		settile(world, j, 26 + offset[j], dirtType);
		settilebg(world, j, 26 + offset[j], caveBackgroundType);
		settile(world, j, height - 6, bedrockType);
		settile(world, j, height - 5, bedrockType);
		settile(world, j, height - 4, bedrockType);
		settile(world, j, height - 3, bedrockType);
		settile(world, j, height - 2, bedrockType);
		settile(world, j, height - 1, bedrockType);

		settilebg(world, j, height - 6, caveBackgroundType);
		settilebg(world, j, height - 5, caveBackgroundType);
		settilebg(world, j, height - 4, caveBackgroundType);
		settilebg(world, j, height - 3, caveBackgroundType);
		settilebg(world, j, height - 2, caveBackgroundType);
		settilebg(world, j, height - 1, caveBackgroundType);
	}
	cout << endl;
	for (int srg = height - 10; srg < height - 6; srg++)
	{
		for (int dhk = 0; dhk < width; dhk++)
		{
			int djkf = rand() % 2;
			if (djkf == 1)
			{
				settile(world, dhk, srg, lavaType);
			}
		}
	}
	if (id & BlastProperties_WaterLevelD2)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = deco2Id; j < height; j++)
			{
				if (gettile(world, i, j) == 0)
				{
					if (i < world->width && i >= 0 && j < world->height && j >= 0)
						world->items[i + j * world->width].water = 1;
				}
			}
		}
	}
	else if (id & BlastProperties_RandomDeco1)
	{
		int deco1Count = rand() % 25 + 3;
		for (int i = 0; i < deco1Count; i++)
		{
			int a = rand() % width;
			settile(world, a, 25 + offset[a], deco1Id);
		}
	}
	else if (id & BlastProperties_RandomDeco2)
	{
		int deco2Count = rand() % 25 + 3;
		for (int i = 0; i < deco2Count; i++)
		{
			int a = rand() % width;
			settile(world, a, 25 + offset[a], deco2Id);
		}
	}


regenerate:
	int mainDoorX = (rand() % (width - 4)) + 2;
	int f = 25 + offset[mainDoorX];
	while (gettile(world, mainDoorX, f) != 0)
	{
		f--;
		if (f < 0) goto regenerate;
	}
	settile(world, mainDoorX, f, mainDoorType);
	settile(world, mainDoorX, f + 1, bedrockType);

	delete offset;
	delete offset2;
}


WorldInfo generateWorld(string name, int width, int height)
{
	WorldInfo world;
	world.name = name;
	world.width = width;
	world.height = height;
	world.items = new WorldItem[world.width * world.height];
	for (int i = 0; i < world.width * world.height; i++)
	{
		if (i >= 3800 && i < 5400 && !(rand() % 50)) { world.items[i].foreground = 10; }
		else if (i >= 3700 && i < 5400) {
			if (i > 5000) {
				if (i % 7 == 0) { world.items[i].foreground = 4; }
				else { world.items[i].foreground = 2; }
			}
			else { world.items[i].foreground = 2; }
		}
		else if (i >= 5400) { world.items[i].foreground = 8; }
		if (i >= 3700)
			world.items[i].background = 14;
		if (i == 3650)
			world.items[i].foreground = 6;
		else if (i >= 3600 && i < 3700)
			world.items[i].foreground = 0; //fixed the grass in the world!
		if (i == 3750)
			world.items[i].foreground = 8;
	}
	return world;
}

class PlayerDB {
public:
	static string getProperName(string name);
	static string fixColors(string text);
	static int playerLogin(ENetPeer* peer, string username, string password);
	static int playerRegister(ENetPeer* peer, string username, string password, string passwordverify, string email);
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

	string username = ret2;
	if (username == "prn" || username == "con" || username == "aux" || username == "nul" || username == "com1" || username == "com2" || username == "com3" || username == "com4" || username == "com5" || username == "com6" || username == "com7" || username == "com8" || username == "com9" || username == "lpt1" || username == "lpt2" || username == "lpt3" || username == "lpt4" || username == "lpt5" || username == "lpt6" || username == "lpt7" || username == "lpt8" || username == "lpt9") {
		return "";
	}

	return ret2;
}
void LoadDialog(ENetPeer* peer) {

	std::ifstream ifff("dialog.json");

	json j;
	ifff >> j;

	string news;
	news = j["dialog"].get<string>();


	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), news));

	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);

	//enet_host_flush(server);
	delete p.data;

}
void showWrong(ENetPeer* peer, string listFull, string itemFind) {
	GamePacket fff = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`wFind item: " + itemFind + "``|left|206|\nadd_spacer|small|\n" + listFull + "add_textbox|Enter a word below to find the item|\nadd_text_input|item|Item Name||30|\nend_dialog|findid|Cancel|Find the item!|\n"));
	ENetPacket* packetd = enet_packet_create(fff.data,
		fff.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packetd);

	//enet_host_flush(server);
	delete fff.data;
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
	endianInvVal = _byteswap_ulong(inventory.inventorySize);
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

void DoorEffect(ENetPeer* peer, int x, int y)
{
	Player::OnZoomCamera(peer, 10000.000600, 1000);
	GamePacket p2 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
	memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	SendGamePacket(peer, &p2);
	GamePacket p3 = packetEnd(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1));
	SendGamePacket(peer, &p3);
	GamePacket p4 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x * 32, y * 32));
	memcpy(p4.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	SendGamePacket(peer, &p4);
	Player::OnZoomCamera(peer, 10000.000000, 1000);
}
void FlushPlayer(ENetPeer* peer) {
	PlayerInfo* p = ((PlayerInfo*)(peer->data));
	PlayerInfo* playerInfo = ((PlayerInfo*)(peer->data));
	if (((PlayerInfo*)(peer->data))->isIn)
	{
		if (((PlayerInfo*)(peer->data))->haveGrowId) {

			int qstate = 0;
			conn = mysql_init(0);
			conn = mysql_real_connect(conn, ip, user, pass, database, 0, NULL, 0);
			if (conn == NULL) {
				return;
			}
			if (conn != NULL) {
				stringstream ss;

				ss << "UPDATE players SET username = '" + p->rawName + "', password = '" + p->tankIDPass + "', gems = '" + std::to_string(p->gems) + "', adminLevel = '" + std::to_string(p->adminLevel) + "', userID = '" + std::to_string(p->userID) + "', xp = '" + std::to_string(p->xp) + "', level = '" + std::to_string(p->level) + "', hair = '" + std::to_string(p->cloth_hair) + "', shirt = '" + std::to_string(p->cloth_shirt) + "', skin = '" + std::to_string(p->skinColor) + "', hand= '" + std::to_string(p->cloth_hand) + "', mask = '" + std::to_string(p->cloth_mask) + "', wing = '" + std::to_string(p->cloth_back) + "', neck = '" + std::to_string(p->cloth_necklace) + "', face= '" + std::to_string(p->cloth_face) + "', ances = '" + std::to_string(p->cloth_ances) + "', pants = '" + std::to_string(p->cloth_pants) + "', bannedat = '" + std::to_string(p->bandate) + "', ban = '" + std::to_string(p->ban) + "', bantime = '" + std::to_string(p->bantime) + "', lstep ='" + to_string(p->lqueststep) + "', lprogress = '" + to_string(p->lquestprogress) + "', ltype = '" + to_string(p->ltype) + "'  WHERE username = '" + p->rawName + "'";
				string query = ss.str(); // loading query into string
				const char* q = query.c_str(); // converting string to const char
				qstate = mysql_query(conn, q);
				if (qstate == 0) { // if qstate == 0 (EVERYTHING IS OK!) then pop out a 1, 1 will lead to the dialog that will say ("GrowID Created")		
					//TODO			
				}
				else {

				}
			}
			mysql_close(conn);







			string usernames = PlayerDB::getProperName(p->rawName);

			std::ofstream o("players/_" + usernames + ".json");
			if (!o.is_open()) {
				cout << GetLastError() << endl;
				_getch();
			}
			json j;

			j["inventorysize"] = playerInfo->inventory.inventorySize;
			j["inventorycount"] = playerInfo->inventory.items.size();
			json items = json::array();
			for (int i = 0; i < playerInfo->inventory.items.size(); i++)
			{
				json item;
				item["id"] = playerInfo->inventory.items.at(i).itemID;
				item["cnt"] = playerInfo->inventory.items.at(i).itemCount;
				items.push_back(item);
			}
			j["items"] = items;
			o << j << std::endl;
		}
	}
}
void LoadInventory(ENetPeer* peer)
{
	PlayerInfo* pinfo = (PlayerInfo*)peer->data;
	try
	{
		std::ifstream ifs("players/_" + pinfo->rawName + ".json");
		if (!ifs.is_open()) {
			ifs.close();
			return;
		}

		json j;
		ifs >> j;
		ifs.close();

		PlayerInventory inv;
		int invSize = j["inventorysize"].get<int>();
		int invItemCnt = j["inventorycount"].get<int>();
		inv.inventorySize = invSize;
		json items = j["items"];
		for (int i = 0; i < invItemCnt; i++)
		{
			InventoryItem it;
			it.itemID = items[i]["id"];
			it.itemCount = items[i]["cnt"];
			inv.items.push_back(it);
		}
		pinfo->inventory = inv;
	}
	catch (exception e)
	{
		PlayerInventory inv;
		inv.inventorySize = 100;
		InventoryItem it;
		it.itemID = 18;
		it.itemCount = 255;
		inv.items.push_back(it);
		it.itemID = 32;
		it.itemCount = 255;
		inv.items.push_back(it);
		pinfo->inventory = inv;
	}
	sendInventory(peer, pinfo->inventory);
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
string filterName(string  name) {
	string filteredname = "";
	for (int i = 0; i < name.length(); i++) {
		string ch = name.substr(i, 1); // always take 1 character, and move next. EXAMPLE: we got password 12345, it will take first 1 and check, then 2 and check, and 3 and check, 4 and check, 5 and ccheck. it will scan ALL characters if bad symbols etc. because i is always getting a higher number cuz we said i++
		if (ch != "a" && ch != "A" && ch != "b" && ch != "B" && ch != "c" && ch != "C" && ch != "d" && ch != "D" && ch != "e" && ch != "E"
			&& ch != "f" && ch != "F" && ch != "g" && ch != "G" && ch != "h" && ch != "H" && ch != "i" && ch != "I" && ch != "j" && ch != "J"
			&& ch != "k" && ch != "K" && ch != "l" && ch != "L" && ch != "m" && ch != "M" && ch != "n" && ch != "N" && ch != "o" && ch != "O" &&
			ch != "p" && ch != "P" && ch != "q" && ch != "Q" && ch != "r" && ch != "R" && ch != "s" && ch != "S" && ch != "t" && ch != "T" && ch != "u" && ch != "U"
			&& ch != "v" && ch != "V" && ch != "w" && ch != "W" && ch != "x" && ch != "X" && ch != "y" && ch != "Y" && ch != "z" && ch != "Z" && ch != "0" && ch != "1" && ch != "2"
			&& ch != "3" && ch != "4" && ch != "5" && ch != "6" && ch != "7" && ch != "8" && ch != "9") {
		}
		else
		{
			filteredname = filteredname + ch;
		}
	}
	return filteredname;
}

string filterPass(string password) {

	string filteredpass = "";
	for (int i = 0; i < password.length(); i++) {
		string ch = password.substr(i, 1); // always take 1 character, and move next. EXAMPLE: we got password 12345, it will take first 1 and check, then 2 and check, and 3 and check, 4 and check, 5 and ccheck. it will scan ALL characters if bad symbols etc. because i is always getting a higher number cuz we said i++
		if (ch != "a" && ch != "A" && ch != "b" && ch != "B" && ch != "c" && ch != "C" && ch != "d" && ch != "D" && ch != "e" && ch != "E"
			&& ch != "f" && ch != "F" && ch != "g" && ch != "G" && ch != "h" && ch != "H" && ch != "i" && ch != "I" && ch != "j" && ch != "J"
			&& ch != "k" && ch != "K" && ch != "l" && ch != "L" && ch != "m" && ch != "M" && ch != "n" && ch != "N" && ch != "o" && ch != "O" &&
			ch != "p" && ch != "P" && ch != "q" && ch != "Q" && ch != "r" && ch != "R" && ch != "s" && ch != "S" && ch != "t" && ch != "T" && ch != "u" && ch != "U"
			&& ch != "v" && ch != "V" && ch != "w" && ch != "W" && ch != "x" && ch != "X" && ch != "y" && ch != "Y" && ch != "z" && ch != "Z" && ch != "0" && ch != "1" && ch != "2"
			&& ch != "3" && ch != "4" && ch != "5" && ch != "6" && ch != "7" && ch != "8" && ch != "9" && ch != "!" && ch != ".") {

		}
		else
		{
			filteredpass = filteredpass + ch;
		}
	}
	return filteredpass;
}

struct Admin {
	string username;
	string password;
	int level = 0;
	long long int lastSB = 0;
};


bool isDoubleJumpItem(int id) {

	if (id == 156 || id == 362 || id == 678 || id == 736 || id == 818 || id == 1206 || id == 1460 || id == 1550 || id == 1574 || id == 1672 || id == 1674 || id == 1784 || id == 1824 || id == 1936 || id == 1938 || id == 1970 || id == 2254 || id == 2256 || id == 2258 || id == 2260 || id == 2262 || id == 2264 || id == 2390 || id == 2392 || id == 3120 || id == 3513 || id == 4534 || id == 4986 || id == 5754 || id == 6444 || id == 6334 || id == 6694 || id == 6818 || id == 6842 || id == 7104 || id == 7150 || id == 7196 || id == 7350 || id == 7412 || id == 7502 || id == 7582 || id == 7734 || id == 7834 || id == 7914 || id == 7916 || id == 8286 || id == 8302 || id == 3808 || id == 8552 || id == 8620 || id == 8862 || id == 8914 || id == 9114 || id == 9182 || id == 9352 || id == 9394 || id == 9422 || id == 2722 || id == 3114 || id == 4970 || id == 4972 || id == 5020 || id == 8024 || id == 6284 || id == 8026 || id == 9210 || id == 9408 || id == 9428 || id == 350 || id == 1166 || id == 1738 || id == 2158 || id == 2160 || id == 2162 || id == 2164 || id == 2166 || id == 2168 || id == 2438 || id == 2538 || id == 2642 || id == 2778 || id == 3104 || id == 3112 || id == 3858 || id == 5738 || id == 7084 || id == 7204 || id == 7214 || id == 8194 || id == 8576 || id == 8578 || id == 8580 || id == 8582 || id == 9320 || id == 9322 || id == 9446 || id == 1958) {

		return true;
	}
	else {
		return false;
	}

}

vector<Admin> admins;

void addAdmin(string username, string password, int level)
{
	Admin admin;
	admin.username = username;
	admin.password = password;
	admin.level = level;
	admins.push_back(admin);
}

int getAdminLevel(string username, string password) {
	for (int i = 0; i < admins.size(); i++) {
		Admin admin = admins[i];
		if (admin.username == username && admin.password == password) {
			return admin.level;
		}
	}
	return 0;
}
void sendConsoleMsg(ENetPeer* peer, string message) {
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), message));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void BlockLoginNoUrl(ENetPeer* peer, string message) {
	string text = "action|log\nmsg|" + message + "\n";
	string text3 = "action|logon_fail\n";

	BYTE* data = new BYTE[5 + text.length()];
	BYTE* data3 = new BYTE[5 + text3.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);

	memcpy(data3, &type, 4);
	memcpy(data3 + 4, text3.c_str(), text3.length());
	memcpy(data3 + 4 + text3.length(), &zero, 1);

	ENetPacket* p = enet_packet_create(data,
		5 + text.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p);
	ENetPacket* p2 = enet_packet_create(data3,
		5 + text3.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p2);

	delete data;
	delete data3;

	enet_peer_disconnect_later(peer, 0);

}


int PlayerDB::playerRegister(ENetPeer* peer, string username, string password, string passwordverify, string email) {
	string displayName666 = username;
	string namex = username;
	username = PlayerDB::getProperName(username);
	string displayName = username;

	if (email.find("@") == std::string::npos && email.length() != 0) return -349;
	if (password.length() < 3) return -53;
	if (passwordverify != password) return -102;
	if (username.length() < 3) return -2;
	if (username.length() > 16) return -2;
	if (password.length() > 20) return -53;

	if (namex.find(" ") != string::npos || namex.find(".") != string::npos || namex.find(",") != string::npos || namex.find("@") != string::npos || namex.find("[") != string::npos || namex.find("]") != string::npos || namex.find("#") != string::npos || namex.find("<") != string::npos || namex.find(">") != string::npos || namex.find(":") != string::npos || namex.find("{") != string::npos || namex.find("}") != string::npos || namex.find("|") != string::npos || namex.find("+") != string::npos || namex.find("_") != string::npos || namex.find("~") != string::npos || namex.find("-") != string::npos || namex.find("!") != string::npos || namex.find("$") != string::npos || namex.find("%") != string::npos || namex.find("^") != string::npos || namex.find("&") != string::npos || namex.find("`") != string::npos || namex.find("*") != string::npos || namex.find("(") != string::npos || namex.find(")") != string::npos || namex.find("=") != string::npos || namex.find("'") != string::npos || namex.find(";") != string::npos || namex.find("/") != string::npos) {
		return -4;
	}


	MYSQL_ROW row;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, ip, user, pass, database, 0, NULL, 0);
	if (conn == NULL) {
		cout << "null" << endl;
		return -1;
	}

	if (conn != NULL) {
		stringstream sse;
		string name;
		int qstate2 = 0;
		sse << "SELECT * FROM players WHERE username = '" + PlayerDB::getProperName(username) + "'";
		if (!sse.fail()) {
			string query = sse.str();
			const char* q = query.c_str();
			qstate2 = mysql_query(conn, q);
		}
		if (qstate2 == 0) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				name = row[0];
			}
			if (name.length() > 0) return -1;
		}
		else {
			return -1;
		}
		userIDcount++;
		if (userIDcount == 1) userIDcount++;
		int qstate = 0;

		string skincoloz = std::to_string(((PlayerInfo*)(peer->data))->skinColor);
		stringstream ss;
		ss << "INSERT INTO players(username, password, gems, displayName, adminLevel, userID, xp, level, hair, shirt, skin, hand, mask, wing, neck, face, ances, pants, shoes, bannedat, ban, bantime, lstep, lprogress, ltype) VALUES ( '" + PlayerDB::getProperName(username) + "', '" + filterPass(password) + "', '" + std::to_string(0) + "', '" + displayName666 + "','" + std::to_string(0) + "', '" + std::to_string(userIDcount) + "', '0', '0', '0', '0', '" + skincoloz + "', '0', '0', '0', '0', '0', '0', '0', '0' ,'-1', '0', '-1', '0', '0', '0')";
		string query = ss.str(); // loading query into string
		const char* q = query.c_str(); // converting string to const char
		qstate = mysql_query(conn, q);
		if (qstate == 0) { // if qstate == 0 (EVERYTHING IS OK!) then pop out a 1, 1 will lead to the dialog that will say ("GrowID Created")			
		}
		else {
			cout << "sad" << endl;

			return -1;
		}

	}
	else {
		return -1;
	}
	mysql_close(conn);

	((PlayerInfo*)(peer->data))->userID = userIDcount;
	ofstream myfile;
	myfile.open("uids.txt");
	myfile << to_string(userIDcount);
	myfile.close();
	((PlayerInfo*)(peer->data))->userID = userIDcount;
	return 1;
}

struct AWorld {
	WorldInfo* ptr;
	WorldInfo info;
	int id;
};
string getStrLower(string txt) {
	string ret;
	for (char c : txt) ret += tolower(c);
	return ret;
}
class WorldDB {
public:
	WorldInfo get(string name);
	AWorld get2(string name);
	void flush(WorldInfo info);
	void flush2(AWorld info);
	void save(AWorld info);
	void saveAll();
	bool exists(string name);

	void remove(string name);
	void saveRedundant();
	vector<WorldInfo> getRandomWorlds();
	WorldDB();
private:
	vector<WorldInfo> worlds;
};

bool WorldDB::exists(string name) {
	std::ifstream ifs("worlds/_" + name + ".json");
	if (ifs.is_open()) {
		ifs.close();
		return true;
	}
	ifs.close();
	return false;
}

void WorldDB::remove(string name) {
	for (int i = 0; i < worlds.size(); i++)
	{
		WorldInfo w = worlds.at(i);
		if (getStrLower(name) == getStrLower(w.name))
		{
			worlds.erase(worlds.begin() + i);
		}
	}
	std::remove(("worlds/_" + name + ".json").c_str());
}
WorldDB::WorldDB() {
	// Constructor
}


void ToUpperStr(string str)
{
	//auto toupp = [](unsigned char c) { return std::toupper(c); };
	//std::transform(str.begin(), str.end(), str.begin(),
	//	toupp);
	for (auto& c : str) c = toupper(c);
}
string getStrUpper(string txt) {
	string ret;
	for (char c : txt) ret += toupper(c);
	return ret;
}

AWorld WorldDB::get2(string name) {
	if (worlds.size() > 200) {
#ifdef TOTAL_LOG
		cout << "Saving redundant worlds!" << endl;
#endif
		saveRedundant();
#ifdef TOTAL_LOG
		cout << "Redundant worlds are saved!" << endl;
#endif
	}
	AWorld ret;
	name = getStrUpper(name);
	if (name.length() < 1) throw 1; // too short name
	for (char c : name) {
		if ((c < 'A' || c>'Z') && (c < '0' || c>'9'))
			throw 2; // wrong name
	}
	if (name == "EXIT") {
		throw 3;
	}
	if (name == "CON" || name == "PRN" || name == "AUX" || name == "NUL" || name == "COM1" || name == "COM2" || name == "COM3" || name == "COM4" || name == "COM5" || name == "COM6" || name == "COM7" || name == "COM8" || name == "COM9" || name == "LPT1" || name == "LPT2" || name == "LPT3" || name == "LPT4" || name == "LPT5" || name == "LPT6" || name == "LPT7" || name == "LPT8" || name == "LPT9") throw 3;
	for (int i = 0; i < worlds.size(); i++) {
		if (worlds.at(i).name == name)
		{
			ret.id = i;
			ret.info = worlds.at(i);
			ret.ptr = &worlds.at(i);
			return ret;
		}

	}
	std::ifstream ifs("worlds/_" + name + ".json");
	if (ifs.is_open()) {

		json j;
		ifs >> j;
		WorldInfo info;
		vector<string> worldacs;
		for (int i = 0; i < j["accessworld"].size(); i++) {
			worldacs.push_back(j["accessworld"][i]);
		}

		info.name = j["name"].get<string>();
		info.width = j["width"];
		info.height = j["height"];
		info.owner = j["owner"].get<string>();
		info.weather = j["weather"].get<int>();

		info.isPublic = j["isPublic"];
		info.isNuked = j["nuked"];

		//STUFF



		info.stuffID = j["sid"].get<int>();
		info.stuff_invert = j["si"].get<bool>();
		info.stuff_gravity = j["sg"].get<int>();
		info.stuff_spin = j["ss"].get<bool>();
		info.bgID = j["bid"].get<int>();

		info.hw_red = j["hwr"].get<int>();
		info.hw_green = j["hwg"].get<int>();
		info.hw_blue = j["hwb"].get<int>();
		info.droppedCount = j["dc"].get<int>();

		/*
		vector<DroppedItem> dropItems;
		for (int i = 0; i < j["di"].size(); i++) {
			dropItems.push_back(j["di"][i]);
		}
		info.droppedItems = dropItems;
		*/

		json droppedobjects = j["dropped"];
		for (int i = 0; i < info.droppedCount; i++) {
			DroppedItem di;
			di.count = droppedobjects[i]["c"].get<byte>();
			di.id = droppedobjects[i]["id"].get<short>();
			di.x = droppedobjects[i]["x"].get<int>();
			di.y = droppedobjects[i]["y"].get<int>();
			di.uid = droppedobjects[i]["uid"].get<int>();
			info.droppedItems.push_back(di);
		}
		
		json tiles = j["tiles"];
		int square = info.width * info.height;
		info.items = new WorldItem[square];
		for (int i = 0; i < square; i++) {
			info.items[i].foreground = tiles[i]["fg"].get<int>();
			info.items[i].background = tiles[i]["bg"].get<int>();
			info.items[i].sign = tiles[i]["s"].get<string>();
			try { info.items[i].intdata = tiles[i]["intdata"].get<int>(); }
			catch (nlohmann::json::exception ex) {

				info.items[i].intdata = 0;
			}

		}
		worlds.push_back(info);
		ret.id = worlds.size() - 1;
		ret.info = info;
		ret.ptr = &worlds.at(worlds.size() - 1);
		return ret;
	}
	else {
		WorldInfo info = generateWorld(name, 100, 60);

		worlds.push_back(info);
		ret.id = worlds.size() - 1;
		ret.info = info;
		ret.ptr = &worlds.at(worlds.size() - 1);
		return ret;
	}
	throw 1;
}

WorldInfo WorldDB::get(string name) {

	return this->get2(name).info;
}

void WorldDB::flush(WorldInfo info)
{
	std::ofstream o("worlds/_" + info.name + ".json");
	if (!o.is_open()) {
		cout << GetLastError() << endl;
	}
	json j;
	j["name"] = info.name;
	j["width"] = info.width;
	j["height"] = info.height;
	j["owner"] = info.owner;
	j["isPublic"] = info.isPublic;
	j["weather"] = info.weather;


	j["sid"] = info.stuffID;
	j["sg"] = info.stuff_gravity;
	j["si"] = info.stuff_invert;
	j["ss"] = info.stuff_spin;

	j["bid"] = info.bgID;

	j["hwr"] = info.hw_red;
	j["hwg"] = info.hw_green;
	j["hwb"] = info.hw_blue;






	j["isPublic"] = info.isPublic;

	j["dc"] = info.droppedItems.size();


	j["nuked"] = info.isNuked;

	json tiles = json::array();
	json droppedarr = json::array();
	int square = info.width * info.height;

	for (int i = 0; i < info.droppedItems.size(); i++) 
	{
		json droppedJ;
		droppedJ["c"] = (byte)info.droppedItems[i].count;
		droppedJ["id"] = (short)info.droppedItems[i].id;
		droppedJ["x"] = info.droppedItems[i].x;
		droppedJ["y"] = info.droppedItems[i].y;
		droppedJ["uid"] = info.droppedItems[i].uid;
		droppedarr.push_back(droppedJ);
	}
	j["dropped"] = droppedarr;
	
	
	for (int i = 0; i < square; i++)
	{
		json tile;
		tile["fg"] = info.items[i].foreground;
		tile["bg"] = info.items[i].background;
		tile["s"] = info.items[i].sign;


		tile["intdata"] = info.items[i].intdata;

		tiles.push_back(tile);
	}
	j["tiles"] = tiles;
	o << j << std::endl;
}

void WorldDB::flush2(AWorld info)
{
	this->flush(info.info);
}

void WorldDB::save(AWorld info)
{
	flush2(info);
	delete info.info.items;
	worlds.erase(worlds.begin() + info.id);
}

void WorldDB::saveAll()
{
	for (int i = 0; i < worlds.size(); i++) {
		flush(worlds.at(i));



	}
	worlds.clear();
}


vector<WorldInfo> WorldDB::getRandomWorlds() {
	vector<WorldInfo> ret;
	for (int i = 0; i < ((worlds.size() < 10) ? worlds.size() : 10); i++)
	{ // load first four worlds, it is excepted that they are special
		ret.push_back(worlds.at(i));
	}
	// and lets get up to 6 random
	if (worlds.size() > 4) {
		for (int j = 0; j < 6; j++)
		{
			bool isPossible = true;
			WorldInfo world = worlds.at(rand() % (worlds.size() - 4));
			for (int i = 0; i < ret.size(); i++)
			{
				if (world.name == ret.at(i).name || world.name == "EXIT")
				{
					isPossible = false;
				}
			}
			if (isPossible)
				ret.push_back(world);
		}
	}
	return ret;
}

void WorldDB::saveRedundant()
{
	for (int i = 4; i < worlds.size(); i++) {
		bool canBeFree = true;
		ENetPeer* currentPeer;

		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (((PlayerInfo*)(currentPeer->data))->currentWorld == worlds.at(i).name)
				canBeFree = false;
		}
		if (canBeFree)
		{
			flush(worlds.at(i));
			delete worlds.at(i).items;
			worlds.erase(worlds.begin() + i);
			i--;
		}
	}
}

//WorldInfo world;
//vector<WorldInfo> worlds;
WorldDB worldDB;

void saveAllWorlds() // atexit hack plz fix
{
	cout << "Saving worlds..." << endl;
	worldDB.saveAll();
	cout << "Worlds saved!" << endl;
}

WorldInfo* getPlyersWorld(ENetPeer* peer)
{
	try {
		return worldDB.get2(((PlayerInfo*)(peer->data))->currentWorld).ptr;
	}
	catch (int e) {
		return NULL;
	}
}

struct PlayerMoving {
	int packetType;
	int netID;
	int secondNetId;
	float x;
	float y;
	int characterState;
	int plantingTree;
	float XSpeed;
	float YSpeed;
	int punchX;
	int punchY;

};
ItemDefinition GetItemDef(int id)
{
	if (id < itemDefs.size() && id > -1)
		return itemDefs.at(id);
	return itemDefs.at(0);
}
ItemDefinition getItemDef(int id)
{
	if (id < itemDefs.size() && id > -1)
		return itemDefs.at(id);
	/*for (int i = 0; i < itemDefs.size(); i++)
	{
		if (id == itemDefs.at(i).id)
		{
			return itemDefs.at(i);
		}
	}*/
	throw 0;
	return itemDefs.at(0);
}
void craftItemDescriptions() {
	int current = -1;
	std::ifstream infile("Descriptions.txt");
	for (std::string line; getline(infile, line);)
	{
		if (line.length() > 3 && line[0] != '/' && line[1] != '/')
		{
			vector<string> ex = explode("|", line);
			ItemDefinition def;
			if (atoi(ex[0].c_str()) + 1 < itemDefs.size())
			{
				itemDefs.at(atoi(ex[0].c_str())).description = ex[1];
				if (!(atoi(ex[0].c_str()) % 2))
					itemDefs.at(atoi(ex[0].c_str()) + 1).description = "This is a tree.";
			}
		}
	}
}
void sendHelp(ENetPeer* peer)
{
	if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) == 2)
	{
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "This command is disabled due not done!"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
		//enet_host_flush(server);
	}
	else if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) == 1)
	{
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "This command is disabled due not done!"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
		//enet_host_flush(server);
	}
	else {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "This command is disabled due not done!"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
		//enet_host_flush(server);
	}
}
string ReadAllText(string filename)
{
	string f;
	std::ifstream file(filename);
	stringstream strstr;
	strstr << file.rdbuf();
	f = strstr.str();
	file.close();
	return f;
}
void sendGazette(ENetPeer* peer) {

	string dada = ReadAllText("Dialogs/gazette.txt");
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), dada));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;

}



string FormatTradeItems(vector<TradeItem> tradeItems)
{
	string fmt;
	for (auto& t : tradeItems)
	{
		fmt += "add_slot|" + to_string(t.id) + "|" + to_string(t.count) + "\n";
	}
	return fmt;
}

string FormatTradeItemsForDialog(vector<TradeItem> tradeItems, bool getting)
{
	if (tradeItems.size() < 1)
	{
		string a = "add_textbox|";
		a += (getting ? "`2" : "`4");
		a += "Nothing!";
		return a;
	}
	string fmt;
	for (auto& t : tradeItems)
	{
		fmt += "add_label_with_icon|small|`o(`w" + to_string(t.count) + "`o) `w" + items.at(t.id).name + "``|left|" + to_string(t.id) + "|\n";
	}
	return fmt;
}
string FormatTradeItemsForMessage(vector<TradeItem> tradeItems)
{
	if (tradeItems.size() < 1) return "nothing";
	string fmt;
	for (auto& t : tradeItems)
	{
		if (fmt.size() > 0)
			fmt += ", " + to_string(t.count) + " " + items.at(t.id).name + "";
		else
			fmt += to_string(t.count) + " " + items.at(t.id).name + "";
		//fmt += "add_label_with_icon|big|`o(`w" + to_string(t.count) + "`o) `w" + getItemDef(t.id).name + "``|left|" + to_string(t.id) + "|\n";
	}
	return fmt;
}

bool DetectTradeConnection(ENetPeer* peer1, ENetPeer* peer2)
{
	PlayerInfo* pinfo = (PlayerInfo*)peer1->data;
	PlayerInfo* pinfo2 = (PlayerInfo*)peer2->data;

	if (pinfo->isWaitingForTrade)
	{
		if (pinfo->isWaitingForTradeWithUserID == pinfo2->userID)
		{
			if (pinfo2->isWaitingForTrade)
			{
				if (pinfo2->isWaitingForTradeWithUserID == pinfo->userID)
				{
					// set both peer's flags
					pinfo->isTrading = true;
					pinfo->isTradingWithUserID = pinfo->isWaitingForTradeWithUserID;
					pinfo->isWaitingForTradeWithUserID = 0;
					pinfo->isTradingWithUserID = pinfo2->userID;
					pinfo->isWaitingForTrade = false;

					pinfo2->isTradingWithUserID = pinfo->userID;
					pinfo2->isTrading = true;
					pinfo2->isTradingWithUserID = pinfo2->isWaitingForTradeWithUserID;
					pinfo2->isWaitingForTradeWithUserID = false;
					pinfo2->isWaitingForTrade = false;

					pinfo->tradeItems.clear();
					pinfo2->tradeItems.clear();

					Player::OnTradeStatus(peer1, pinfo->netID, "`oSelect an item from the inventory.``", "", FormatTradeItems(pinfo->tradeItems) + "\nlocked|0\nreset_locks|1\naccepted|" + to_string(pinfo->isAcceptingTrade) + "\n");
					Player::OnTradeStatus(peer1, pinfo2->netID, "`w" + pinfo2->displayName + "`o's offer.``", "", FormatTradeItems(pinfo2->tradeItems) + "\nlocked|0\naccepted|" + to_string(pinfo2->isAcceptingTrade) + "\n");

					Player::OnTradeStatus(peer2, pinfo2->netID, "`oSelect an item from the inventory.``", "", FormatTradeItems(pinfo2->tradeItems) + "\nlocked|0\naccepted|" + to_string(pinfo2->isAcceptingTrade) + "\n");
					Player::OnTradeStatus(peer2, pinfo->netID, "`w" + pinfo->displayName + "`o's offer.``", "", FormatTradeItems(pinfo->tradeItems) + "\nlocked|0\nreset_locks|1\naccepted|" + to_string(pinfo->isAcceptingTrade) + "\n");
					return true;
				}
			}
		}
	}
	return false;
}



void UpdateTradeAcceptedStatus(ENetPeer* peer1, int showOverlay = 0)
{
	cout << "Trade accepted status updated." << endl;
	PlayerInfo* pinfo = (PlayerInfo*)peer1->data;
	ENetPeer* currentPeer;

	bool found = false;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		PlayerInfo* pinfo2 = (PlayerInfo*)currentPeer->data;
		if (pinfo->isTradingWithUserID == pinfo2->userID) {

			Player::OnTradeStatus(currentPeer, pinfo->netID, "`o" + pinfo->displayName + "`o's offer.``", "", FormatTradeItems(pinfo->tradeItems) + "\nlocked|1\naccepted|" + to_string(pinfo->isAcceptingTrade) + "\n");
			Player::OnTradeStatus(currentPeer, pinfo2->netID, "`o" + pinfo2->displayName + "`o's offer.``", "", FormatTradeItems(pinfo2->tradeItems) + "\nlocked|1\naccepted|" + to_string(pinfo2->isAcceptingTrade) + "\n");
			break;
		}
	}
	//Player::OnTradeStatus(peer1, pinfo->netID, "`o" + pinfo->displayName + "`o's offer.``", "", FormatTradeItems(pinfo->tradeItems) + "\nlocked|1\naccepted|" + to_string(pinfo->isAcceptingTrade) + "\n");
}
int WaitForTradeWithThisPlayer(ENetPeer* peer1, ENetPeer* peer2)
{
	if (peer1 == peer2) return -2;
	PlayerInfo* pinfo = (PlayerInfo*)peer1->data;
	PlayerInfo* pinfo2 = (PlayerInfo*)peer2->data;
	if (pinfo->currentWorld != pinfo2->currentWorld) return -3;
	if (pinfo2->isTrading) return -1;
	pinfo->isTrading = false;
	pinfo->isWaitingForTrade = true;
	pinfo->isWaitingForTradeWithUserID = pinfo2->userID;
	Player::OnStartTrade(peer1, pinfo2->displayName, pinfo2->netID);
	if (!DetectTradeConnection(peer1, peer2))
	{
		Player::OnConsoleMessage(peer2, "`#TRADE ALERT`o: " + pinfo->displayName + " `owants to trade with you! To accept, type `w/trade " + pinfo->rawName + "`o.");
	}
	return 0;
}

ENetPeer* findPeerWithName(string name)
{
	ENetPeer* currentPeer;

	bool found = false;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;

		if (((PlayerInfo*)(currentPeer->data))->rawName == name) {
			return currentPeer;
		}
	}
	return NULL;
}



void SendCancelTrade(ENetPeer* peer, string overlay = "That player is busy.")
{
	cout << "Trade cancelled." << endl;
	PlayerInfo* pinfo = (PlayerInfo*)peer->data;
	Player::OnForceTradeEnd(peer); // just in case
	if (overlay != "") {
		Player::OnTextOverlay(peer, overlay);
	}
	pinfo->isTrading = false;
	pinfo->isAcceptingTrade = false;
	pinfo->isTradingWithUserID = 0;
	pinfo->isWaitingForTradeWithUserID = 0;
	pinfo->isWaitingForTrade = false;
}


void BuildItemsDatabase()
{
	int current = -1;
	std::ifstream infile("CoreData.txt");
	for (std::string line; getline(infile, line);)
	{
		if (line.length() > 8 && line[0] != '/' && line[1] != '/')
		{
			vector<string> ex = explode("|", line);
			ItemDefinition def;
			def.id = atoi(ex[0].c_str());
			def.name = ex[1];
			def.rarity = atoi(ex[2].c_str());
			vector<string> properties = explode(",", ex[3]);
			def.properties = Property_Zero;
			for (auto& prop : properties)
			{
				if (prop == "NoSeed")
					def.properties |= Property_NoSeed;
				if (prop == "Dropless")
					def.properties |= Property_Dropless;
				if (prop == "Beta")
					def.properties |= Property_Beta;
				if (prop == "Mod")
					def.properties |= Property_Mod;
				if (prop == "Untradable")
					def.properties |= Property_Untradable;
				if (prop == "Wrenchable")
					def.properties |= Property_Wrenchable;
				if (prop == "MultiFacing")
					def.properties |= Property_MultiFacing;
				if (prop == "Permanent")
					def.properties |= Property_Permanent;
				if (prop == "AutoPickup")
					def.properties |= Property_AutoPickup;
				if (prop == "WorldLock")
					def.properties |= Property_WorldLock;
				if (prop == "NoSelf")
					def.properties |= Property_NoSelf;
				if (prop == "RandomGrow")
					def.properties |= Property_RandomGrow;
				if (prop == "Public")
					def.properties |= Property_Public;
			}
			string bt = ex[4];
			if (bt == "Foreground_Block") {
				def.blockType = BlockTypes::FOREGROUND;
			}
			else if (bt == "Seed") {
				def.blockType = BlockTypes::SEED;
			}
			else if (bt == "Consummable") {
				def.blockType = BlockTypes::CONSUMABLE;
			}
			else if (bt == "Pain_Block") {
				def.blockType = BlockTypes::PAIN_BLOCK;
			}
			else if (bt == "Main_Door") {
				def.blockType = BlockTypes::MAIN_DOOR;
			}
			else if (bt == "Bedrock") {
				def.blockType = BlockTypes::BEDROCK;
			}
			else if (bt == "Door") {
				def.blockType = BlockTypes::DOOR;
			}
			else if (bt == "Fist") {
				def.blockType = BlockTypes::FIST;
			}
			else if (bt == "Sign") {
				def.blockType = BlockTypes::SIGN;
			}
			else if (bt == "Background_Block") {
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Sheet_Music") {
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Wrench") {
				def.blockType = BlockTypes::WRENCH;
			}
			else if (bt == "Checkpoint") {
				def.blockType = BlockTypes::CHECKPOINT;
			}
			else if (bt == "Lock") {
				def.blockType = BlockTypes::LOCK;
			}
			else if (bt == "Gateway") {
				def.blockType = BlockTypes::GATEWAY;
			}
			else if (bt == "Clothing") {
				def.blockType = BlockTypes::CLOTHING;
			}
			else if (bt == "Platform") {
				def.blockType = BlockTypes::PLATFORM;
			}
			else if (bt == "SFX_Foreground") {
				def.blockType = BlockTypes::SFX_FOREGROUND;
			}
			else if (bt == "Gems") {
				def.blockType = BlockTypes::GEMS;
			}
			else if (bt == "Toggleable_Foreground") {
				def.blockType = BlockTypes::TOGGLE_FOREGROUND;
			}
			else if (bt == "Treasure") {
				def.blockType = BlockTypes::TREASURE;
			}
			else if (bt == "Deadly_Block") {
				def.blockType = BlockTypes::DEADLY;
			}
			else if (bt == "Trampoline_Block") {
				def.blockType = BlockTypes::TRAMPOLINE;
			}
			else if (bt == "Animated_Foreground_Block") {
				def.blockType = BlockTypes::ANIM_FOREGROUND;
			}
			else if (bt == "Portal") {
				def.blockType = BlockTypes::PORTAL;
			}
			else if (bt == "Random_Block") {
				def.blockType = BlockTypes::RANDOM_BLOCK;
			}
			else if (bt == "Bouncy") {
				def.blockType = BlockTypes::BOUNCY;
			}
			else if (bt == "Chest") {
				def.blockType = BlockTypes::CHEST;
			}
			else if (bt == "Switch_Block") {
				def.blockType = BlockTypes::SWITCH_BLOCK;
			}
			else if (bt == "Magic_Egg") {
				def.blockType = BlockTypes::MAGIC_EGG;
			}
			else if (bt == "Mailbox") {
				def.blockType = BlockTypes::MAILBOX;
			}
			else if (bt == "Bulletin_Board") {
				def.blockType = BlockTypes::BULLETIN_BOARD;
			}
			else if (bt == "Faction") {
				def.blockType = BlockTypes::FACTION;
			}
			else if (bt == "Component") {
				def.blockType = BlockTypes::COMPONENT;
			}
			else if (bt == "Weather_Machine") {
				def.blockType = BlockTypes::WEATHER;
			}
			else {
				//cout << "Unknown property for ID: " << def.id << " which wants property " << bt << endl;
				def.blockType = BlockTypes::UNKNOWN;
			}
			def.breakHits = atoi(ex[7].c_str());
			def.growTime = atoi(ex[8].c_str());
			string cl = ex[9];
			if (def.blockType == BlockTypes::CLOTHING)
			{
				if (cl == "None") {
					def.clothType = ClothTypes::NONE;
				}
				else if (cl == "Hat") {
					def.clothType = ClothTypes::HAIR;
				}
				else if (cl == "Shirt") {
					def.clothType = ClothTypes::SHIRT;
				}
				else if (cl == "Pants") {
					def.clothType = ClothTypes::PANTS;
				}
				else if (cl == "Feet") {
					def.clothType = ClothTypes::FEET;
				}
				else if (cl == "Face") {
					def.clothType = ClothTypes::FACE;
				}
				else if (cl == "Hand") {
					def.clothType = ClothTypes::HAND;
				}
				else if (cl == "Back") {
					def.clothType = ClothTypes::BACK;
				}
				else if (cl == "Artifact") {
					def.clothType = ClothTypes::ANCES;
				}
				else if (cl == "Hair") {
					def.clothType = ClothTypes::MASK;
				}
				else if (cl == "Chest") {
					def.clothType = ClothTypes::NECKLACE;
				}
				else {
					def.clothType = ClothTypes::NONE;
				}
			}
			else
			{
				def.clothType = ClothTypes::NONE;
			}

			if (++current != def.id)
			{
				cout << "Critical error! Unordered database at item " << std::to_string(current) << "/" << std::to_string(def.id) << "!" << endl;
			}
			CoreDataItems = def.id;
			itemDefs.push_back(def);
		}
	}
	craftItemDescriptions();

}






bool isOwner(string username, string password) {
	for (int i = 0; i < admins.size(); i++) {
		Admin admin = admins[i];
		if (admin.username == username && admin.password == password && admin.level == 2) {
			return true;
		}
	}
	return false;
}


bool isMod(string username, string password) {
	for (int i = 0; i < admins.size(); i++) {
		Admin admin = admins[i];
		if (admin.username == username && admin.password == password && admin.level > 1) {
			return true;
		}
	}
	return false;
}

bool isHere(ENetPeer* peer, ENetPeer* peer2)
{
	if (((PlayerInfo*)(peer->data))->currentWorld != "EXIT" || ((PlayerInfo*)(peer2->data))->currentWorld != "EXIT") {
		return ((PlayerInfo*)(peer->data))->currentWorld == ((PlayerInfo*)(peer2->data))->currentWorld;
	}
}
bool isDev(ENetPeer* peer) {
	if (((PlayerInfo*)(peer->data))->adminLevel > 1){
		return true;
	}
	else {
		return false;
	}
}
bool adminLevel(ENetPeer* peer) {
	return ((PlayerInfo*)(peer->data))->adminLevel;
}
bool isWorldOwner(ENetPeer* peer, WorldInfo* world) {
	return ((PlayerInfo*)(peer->data))->rawName == world->owner;
}
void SendGamePacketEveryoneInWorld(ENetPeer* peer, GamePacket* p)
{
	ENetPacket* packet1 = enet_packet_create(p->data,
		p->len,
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
			enet_peer_send(currentPeer, 0, packet1);
		}
	}
	delete p->data;
}
void UpdateTradeStatus(ENetPeer* peer1, int userID, int showOverlay = 0, bool doSelfToo = true)
{
	cout << "Trade status updated." << endl;
	PlayerInfo* pinfo2 = NULL;
	PlayerInfo* pinfo = (PlayerInfo*)peer1->data;
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer1, currentPeer)) {
			if (pinfo->isTradingWithUserID == ((PlayerInfo*)(currentPeer->data))->userID || ((PlayerInfo*)(peer1->data))->userID == ((PlayerInfo*)(currentPeer->data))->isTradingWithUserID) {
				pinfo2 = (PlayerInfo*)currentPeer->data;
				Player::OnTradeStatus(currentPeer, pinfo2->netID, "`oSelect an item from the inventory.``", "", FormatTradeItems(pinfo2->tradeItems) + "\nlocked|0\nreset_locks|1\naccepted|" + to_string(pinfo2->isAcceptingTrade) + "\n");
				Player::OnTradeStatus(currentPeer, pinfo->netID, "`o" + pinfo->displayName + "`o's offer.``", "", FormatTradeItems(pinfo->tradeItems) + "\nlocked|0\naccepted|" + to_string(pinfo->isAcceptingTrade) + "\n");
				Player::OnTextOverlay(currentPeer, "The deal has changed");
				if (doSelfToo) {
					Player::OnTradeStatus(peer1, pinfo->netID, "`o" + pinfo->displayName + "`o's offer.``", "", FormatTradeItems(pinfo->tradeItems) + "\nlocked|0\naccepted|" + to_string(pinfo->isAcceptingTrade) + "\n");
					Player::OnTextOverlay(peer1, "The deal has changed");
				}
				break;
			}
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

BYTE* packPlayerMoving(PlayerMoving* dataStruct)
{
	BYTE* data = new BYTE[56];
	for (int i = 0; i < 56; i++)
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

void SendPacket(int a1, string a2, ENetPeer* enetPeer)
{
	if (enetPeer)
	{
		ENetPacket* v3 = enet_packet_create(0, a2.length() + 5, 1);
		memcpy(v3->data, &a1, 4);
		//*(v3->data) = (DWORD)a1;
		memcpy((v3->data) + 4, a2.c_str(), a2.length());

		//cout << std::hex << (int)(char)v3->data[3] << endl;
		enet_peer_send(enetPeer, 0, v3);
	}
}
void SendPacketRaw3(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
{
	ENetPacket* p;

	if (peer) // check if we have it setup
	{
		p = enet_packet_create(0, packetDataSize + 5, packetFlag);
		memcpy(p->data, &a1, 4);
		memcpy((char*)p->data + 4, packetData, packetDataSize);
		enet_peer_send(peer, 0, p);
	}
	delete (char*)packetData;
}

void SendPacketRaw2(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
{
	ENetPacket* p;

	if (peer) // check if we have it setup
	{
		if (a1 == 4 && *((BYTE*)packetData + 12) & 8)
		{
			p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
			int four = 4;
			memcpy(p->data, &four, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			memcpy((char*)p->data + packetDataSize + 4, a4, *((DWORD*)packetData + 13));
			enet_peer_send(peer, 0, p);

		}
		else
		{
			if (a1 == 192) {
				a1 = 4;
				p = enet_packet_create(0, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy((char*)p->data + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);


			}
			else {
				p = enet_packet_create(0, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy((char*)p->data + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);


			}
		}
	}

	delete packetData;
}


void SendPacketRaw(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
{
	ENetPacket* p;

	if (peer) // check if we have it setup
	{
		if (a1 == 4 && *((BYTE*)packetData + 12) & 8)
		{
			p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
			int four = 4;
			memcpy(p->data, &four, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			memcpy((char*)p->data + packetDataSize + 4, a4, *((DWORD*)packetData + 13));
			enet_peer_send(peer, 0, p);
		}
		else
		{
			p = enet_packet_create(0, packetDataSize + 5, packetFlag);
			memcpy(p->data, &a1, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			enet_peer_send(peer, 0, p);
		}
	}
	delete (char*)packetData;
}

bool isWorldAdmin2(ENetPeer* peer, WorldInfo world) {
	string rawname = ((PlayerInfo*)(peer->data))->rawName;
	for (int i = 0; world.accessed.size(); i++) {
		string x = world.accessed.at(i);
		if (rawname == x.substr(0, x.find("|"))) {
			return true;

		}
		else {
			return false;
		}
	}
	return false;
}
bool isWorldAdmin(ENetPeer* peer, WorldInfo* world) {
	string rawname = ((PlayerInfo*)(peer->data))->rawName;
	for (int i = 0; world->accessed.size(); i++) {
		string x = world->accessed.at(i);
		if (rawname == x.substr(0, x.find("|"))) {
			return true;

		}
		else {
			return false;
		}
	}
	return false;
}
void sendNotification(ENetPeer* peer, string audio, string image, string message)
{
	GamePacket p = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"), image), message), audio), 0));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
string packPlayerMoving2(PlayerMoving* dataStruct)
{
	string data;
	data.resize(56);
	STRINT(data, 0) = dataStruct->packetType;
	STRINT(data, 4) = dataStruct->netID;
	STRINT(data, 12) = dataStruct->characterState;
	STRINT(data, 20) = dataStruct->plantingTree;
	STRINT(data, 24) = *(int*)&dataStruct->x;
	STRINT(data, 28) = *(int*)&dataStruct->y;
	STRINT(data, 32) = *(int*)&dataStruct->XSpeed;
	STRINT(data, 36) = *(int*)&dataStruct->YSpeed;
	STRINT(data, 44) = dataStruct->punchX;
	STRINT(data, 48) = dataStruct->punchY;
	return data;
}



bool playerHasAcc(string name, WorldInfo* world) {
	for (int i = 0; i < world->accessed.size(); i++) {
		string a = world->accessed.at(i);
		if (a.substr(0, a.find("|")) == name) return true;
	}
	return false;
}

void accessPlayer(ENetPeer* peer, string name, WorldInfo* world) {
	if (!world) return;
	int retcode = -1;
	string player = "";
	if (((PlayerInfo*)(peer->data))->haveGrowId == false) return;
	if (world->owner != ((PlayerInfo*)(peer->data))->rawName) return;

	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (peer != currentPeer) // accessing yourself isnt allowed
		{
			if (isHere(peer, currentPeer)) {
				if (((PlayerInfo*)(currentPeer->data))->rawName == name) {
					world->accessed.push_back(((PlayerInfo*)(currentPeer->data))->rawName + "|" + ((PlayerInfo*)(currentPeer->data))->backupName);
					retcode = 0;
					player = ((PlayerInfo*)(currentPeer->data))->displayName;
			
					break;
				}
			}
		}
	}
	if (retcode == 0) {
		Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "Successfully given access to " + player, true);
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				Player::PlayAudio(peer, "audio/secret.wav", 250);
			}
		}
	}
}

void sendTileData(ENetPeer* peer, int x, int y, int visual, uint16_t fgblock, uint16_t bgblock, string tiledata) {
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 0;
	pmov.x = 0;
	pmov.y = 0;
	pmov.XSpeed = 0;
	pmov.YSpeed = 0;
	pmov.plantingTree = 0;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = 0;

	string packetstr;
	packetstr.resize(4);
	packetstr[0] = 4;
	packetstr += packPlayerMoving2(&pmov);
	packetstr[16] = 8;
	packetstr.resize(packetstr.size() + 4);
	STRINT(packetstr, 52 + 4) = tiledata.size() + 4;
	STR16(packetstr, 56 + 4) = fgblock;
	STR16(packetstr, 58 + 4) = bgblock;
	packetstr += tiledata;

	ENetPacket* packet = enet_packet_create(&packetstr[0],
		packetstr.length(),
		ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, packet);
}
void SendTileDataMultiple(ENetPeer* peer, WorldInfo* world, vector<point> pointsToUpdate)
{

	if (!world) return;
	vector<byte> packet;
	packet.resize(56, 0);
	packet[0] = 6; // packettype is 6
	packet[12] = 0xff;
	packet[13] = 0xff;
	packet[14] = 0xff;
	packet[15] = 0xff;

	int s = 56;
	for (int i = 0; i < pointsToUpdate.size(); i++)
	{
		// add points to update
		point p = pointsToUpdate.at(i);

		// Push_back the point first!
		BYTE* as = new BYTE[12];
		memcpy(as + 0, &p.x, 4);
		memcpy(as + 4, &p.y, 4);
		for (int j = 0; j < 8; j++) packet.push_back(as[j]);
		delete as;

		int a = 8, b = 8;

		// A and B now indicate size.
		BYTE* bt = new BYTE[a];
		memset(bt, 0, a);
		int c = 8, d = 8;

		for (int j = 0; j < a; j++) packet.push_back(0);
		delete bt;
		s += a;
	}

	packet.push_back(0xff); // This is the end marker!
	packet.push_back(0xff);
	packet.push_back(0xff);
	packet.push_back(0xff);



	// now the sending part.
	//ENetPacket* packet_enet = enet_packet_create(packet.data(), packet.size(), ENET_PACKET_FLAG_RELIABLE);
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			BYTE* DATA = new BYTE[packet.size()];
			//*((int*)DATA + 52) = s - 56;
			for (int i = 0; i < packet.size(); i++) DATA[i] = packet[i];
			//enet_peer_send(cpeer, 0, packet_enet);
			SendPacketRaw(4, DATA, packet.size(), NULL, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	//enet_packet_destroy(packet_enet);
}

void SendTradeEffect(ENetPeer* peer, int id, int netIDsrc, int netIDdst, int timeMs)
{
	PlayerMoving data;
	data.packetType = 0x13;
	data.punchX = id;
	data.punchY = id;

	BYTE* raw = packPlayerMoving(&data);
	int netIdSrc = netIDsrc;
	int netIdDst = netIDdst;
	int three = 3;
	int n1 = timeMs;
	memcpy(raw + 3, &three, 1);
	memcpy(raw + 4, &netIdDst, 4);
	memcpy(raw + 8, &netIdSrc, 4);
	memcpy(raw + 20, &n1, 4);

	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			BYTE* raw2 = new BYTE[56];
			memcpy(raw2, raw, 56);
			SendPacketRaw(4, raw2, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	delete raw;
}
uint8_t* magplantTileData(uint16_t itemid, uint16_t itemamount, uint8_t magnet_on, uint8_t remote_on) {
	uint8_t* data = new uint8_t[15];
	memset(data, 0, 15);
	data[0] = 0x3E;
	*(uint16_t*)(data + 1) = itemid;
	*(uint16_t*)(data + 5) = itemamount;
	*(uint8_t*)(data + 9) = magnet_on;
	*(uint8_t*)(data + 10) = remote_on;
	*(uint8_t*)(data + 12) = 1;
	return data;
}
void sendMag(ENetPeer* peer, int x, int y, uint16_t itemid, uint16_t itemamount, uint8_t magneton, uint8_t remoteon)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 15 + 8;
	uint8_t* packet = new uint8_t[4 + 56 + 15 + 8];
	memset(packet, 0, 4 + 56 + 15 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 5638; // magplant id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	uint8_t* tiledata = magplantTileData(itemid, itemamount, magneton, remoteon);
	memcpy(packet + 4 + 56 + 8, tiledata, 15);
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 15, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
	delete tiledata;
}
void sendHeatwave(ENetPeer* peer, int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 5 + 8;
	uint8_t* packet = new uint8_t[4 + 56 + 5 + 8];
	memset(packet, 0, 4 + 56 + 5 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 3694; // heatwave id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x28;
	*(uint32_t*)(packet + 4 + 56 + 9) = (blue << 24) | (green << 16) | (red << 8);
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 5, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;

}

void SendThrowEffect(ENetPeer* peer, int id, int netIDsrc, int netIDdst, int timeMs, byte type, int x, int y)
{
	PlayerMoving data;
	data.packetType = 0x13;
	data.punchX = id;
	data.punchY = id;
	data.x = x;
	data.y = y;
	BYTE* raw = packPlayerMoving(&data);
	int netIdSrc = netIDsrc;
	int netIdDst = netIDdst;
	int three = 3;
	int n1 = timeMs;
	memcpy(raw + 3, &type, 1);
	memcpy(raw + 4, &netIdDst, 4);
	memcpy(raw + 8, &netIdSrc, 4);
	memcpy(raw + 20, &n1, 4);

	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			BYTE* raw2 = new BYTE[56];
			memcpy(raw2, raw, 56);
			SendPacketRaw(4, raw2, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	delete raw;
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
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + netIdS + "\nuserID|" + netIdS + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(((PlayerInfo*)(currentPeer->data))->x) + "|" + std::to_string(((PlayerInfo*)(currentPeer->data))->y) + "\nname|``" + ((PlayerInfo*)(currentPeer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(currentPeer->data))->country + "\ninvis|" + to_string(((PlayerInfo*)(currentPeer->data))->isInvisible) + "\nmstate|" + to_string(((PlayerInfo*)(currentPeer->data))->mstate) + "\nsmstate|" + to_string(((PlayerInfo*)(currentPeer->data))->smstate) + "\n"));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);

				enet_peer_send(peer, 0, packet);
				delete p.data;

				string netIdS2 = std::to_string(((PlayerInfo*)(peer->data))->netID);
				GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + netIdS2 + "\nuserID|" + netIdS2 + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(((PlayerInfo*)(peer->data))->x) + "|" + std::to_string(((PlayerInfo*)(peer->data))->y) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|" + to_string(((PlayerInfo*)(peer->data))->isInvisible) + "\nmstate|" + to_string(((PlayerInfo*)(peer->data))->mstate) + "\nsmstate|" + to_string(((PlayerInfo*)(peer->data))->smstate) + "\n"));
				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
			}
		}
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
			//enet_host_flush(server);
			GamePacket p4 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(currentPeer->data))->cloth_hair, ((PlayerInfo*)(currentPeer->data))->cloth_shirt, ((PlayerInfo*)(currentPeer->data))->cloth_pants), ((PlayerInfo*)(currentPeer->data))->cloth_feet, ((PlayerInfo*)(currentPeer->data))->cloth_face, ((PlayerInfo*)(currentPeer->data))->cloth_hand), ((PlayerInfo*)(currentPeer->data))->cloth_back, ((PlayerInfo*)(currentPeer->data))->cloth_mask, ((PlayerInfo*)(currentPeer->data))->cloth_necklace), ((PlayerInfo*)(currentPeer->data))->skinColor), ((PlayerInfo*)(currentPeer->data))->cloth_ances, 0.0f, 0.0f));
			memcpy(p4.data + 8, &(((PlayerInfo*)(currentPeer->data))->netID), 4); // ffloor
			ENetPacket* packet4 = enet_packet_create(p4.data,
				p4.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet4);
			delete p4.data;
			//enet_host_flush(server);
		}
	}
}

void sendClothes(ENetPeer* peer)
{
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
	//enet_host_flush(server);
	delete p3.data;
}
void sendPData(ENetPeer* peer, PlayerMoving* data)
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
				data->netID = ((PlayerInfo*)(peer->data))->netID;

				SendPacketRaw(4, packPlayerMoving(data), 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
}

int getPlayersCountInWorld(string name)
{
	int count = 0;
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (((PlayerInfo*)(currentPeer->data))->currentWorld == name)
			count++;
	}
	return count;
}

void sendRoulete(ENetPeer* peer, int x, int y)
{
	ENetPeer* currentPeer;
	int val = rand() % 37;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`w[" + ((PlayerInfo*)(peer->data))->displayName + " `wspun the wheel and got `6" + std::to_string(val) + "`w!]"), 0));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
			delete p2.data;
		}


		//cout << "Tile update at: " << data2->punchX << "x" << data2->punchY << endl;
	}
}

void sendNothingHappened(ENetPeer* peer, int x, int y) {
	PlayerMoving data;
	data.netID = ((PlayerInfo*)(peer->data))->netID;
	data.packetType = 0x8;
	data.plantingTree = 0;
	data.netID = -1;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}
void sendDice(ENetPeer* peer, int number, int x, int y) {

	PlayerMoving data;
	BYTE* raw = packPlayerMoving(&data);
	memcpy(raw + 1, &number, 3);

	data.netID = ((PlayerInfo*)(peer->data))->netID;
	data.packetType = 0x8;
	data.plantingTree = 0;
	data.netID = -1;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	SendPacketRaw(4, raw, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}
void SendTilePickup(ENetPeer* peer, int itemid, int netID, float x, float y, int itemcount, int itemamount) {
	PlayerMoving data;
	data.characterState = 0x0; // animation
	data.x = x * 32;
	data.y = y * 32;
	data.punchX = 0;
	data.punchY = 0;
	data.XSpeed = 0;
	data.YSpeed = 0;
	data.netID = -1;
	data.secondNetId = -1;
	data.plantingTree = itemid;
	data.packetType = 0xE;
	BYTE* raw = packPlayerMoving(&data);
	int netIdSrc = -1;
	int netIdDst = -1;
	int three = 3;
	int n1 = itemid;
	int one = 1;
	float count = itemamount;
	memcpy(raw + 3, &three, 1);
	memcpy(raw + 4, &netIdDst, 4);
	memcpy(raw + 8, &netIdSrc, 4);
	memcpy(raw + 16, &count, 4);
	memcpy(raw + 20, &n1, 4);

	((PlayerInfo*)(peer->data))->droppeditemcount++;
	SendPacketRaw(4, raw, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);

	PlayerMoving datax;
	datax.characterState = 0x0; // animation
	datax.x = x * 32;
	datax.y = y * 32;
	datax.punchX = 0;
	datax.punchY = 0;
	datax.XSpeed = 0;
	datax.YSpeed = 0;
	datax.netID = -1;
	datax.secondNetId = 0;
	datax.plantingTree = itemid;
	datax.packetType = 0xE;
	BYTE* raws = packPlayerMoving(&data);
	int lol = -1;


	memcpy(raws + 3, &three, 1);
	memcpy(raws + 4, &netID, 4);
	memcpy(raws + 8, &lol, 4);
	memcpy(raws + 20, &((PlayerInfo*)(peer->data))->droppeditemcount, 4);
	SendPacketRaw(4, raws, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}

void UpdateMessageVisuals(ENetPeer* peer, int foreground, int x, int y, string text, int background, int bubbleType_ = 2, bool sendPacketToEveryone = true, int blockState = 0)
{
	if (text.size() > 100) return;
	// setting tile packet
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = x;
	sign.y = y;
	sign.punchX = x;
	sign.punchY = y;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = foreground;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);

	// hopefully the magic :/
	int hmm = 8, textLen = text.size(), PacketType = 5;
	int yeh = hmm + 3 + 1, idk = 15 + textLen, endMarker = -1, sizeofshort = 2;
	int bubbleType = bubbleType_;
	int ok = 52 + idk;
	int kek = ok + 4, yup = ok - 8 - idk;
	int sizeofint = 4, magic = 56, wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	//MEMCPY DESTINATION					SOURCE			SIZE
	memcpy(data, &PacketType, sizeof(int));
	memcpy(data + yeh, &hmm, sizeof(int));
	memcpy(data + yup, &x, sizeof(int));
	memcpy(data + yup + 4, &y, sizeof(int));
	memcpy(data + 4 + yup + 4, &idk, sizeof(int));
	memcpy(data + magic, &foreground, sizeof(short));
	memcpy(data + magic + 2, &background, sizeof(short));
	memcpy(data + sizeofint + magic, &blockState, sizeof(int));
	memcpy(data + magic + 4 + sizeofint, &bubbleType, sizeof(byte));
	memcpy(data + wow, &textLen, sizeof(short));
	memcpy(data + sizeofshort + wow, text.c_str(), textLen);
	memcpy(data + ok, &endMarker, sizeof(int));
	memcpy(p->data, &sizeofint, sizeof(int));
	memcpy((char*)p->data + sizeofint, data, kek);

	if (sendPacketToEveryone)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete data;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete data;
	}
}
void SendParticleEffectAll(ENetPeer* peer, int particle, float x, float y) {
	GamePacket p = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), particle), x, y));
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
		enet_peer_send(currentPeer, 0, packet);
	}
	delete p.data;
}

BYTE* packBlockVisual(TileExtra* dataStruct)
{

	BYTE* data = new BYTE[104]; // 96
	for (int i = 0; i < 100; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 16, &dataStruct->objectSpeedX, 4);
	//memcpy(data + 40, &dataStruct->bpm, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 2);
	memcpy(data + 58, &dataStruct->backgroundid, 2);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);


	return data;
}

BYTE* packBlockVisual(BlockVisual* dataStruct)
{
	BYTE* data = new BYTE[72];
	for (int i = 0; i < 72; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	//memcpy(data + 40, &dataStruct->bpm, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 4);
	//memcpy(data + 58, &dataStruct->backgroundid, 4);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);


	return data;
}
void UpdateDBLOCK(ENetPeer* peer, int x, int y, int id)
{
	WorldInfo* world = getPlyersWorld(peer);
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			BlockVisual data;
			data.packetType = 0x5;
			data.characterState = 8;
			data.punchX = x;
			data.punchY = y;
			data.charStat = 13; // 13
			data.blockid = 2946; // 2946 3794 = display shelf
								 //data.netID = ((PlayerInfo*)(peer->data))->netID;
			data.backgroundid = 6864;
			data.visual = 0x00010000; //0x00210000
			world->items[x + (y * world->width)].intdata = id;

			int n = id;
			string hex = "";
			{
				std::stringstream ss;
				ss << std::hex << n; // int decimal_value
				std::string res(ss.str());

				hex = res + "17";
				if (hex == "2017") {
					continue;
				}
			}


			int xx;
			std::stringstream ss;
			ss << std::hex << hex;
			ss >> xx;
			data.displayblock = xx;


			SendPacketRaw(192, packBlockVisual(&data), 69, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);

		}
	}
}
#include "packet_initialize/display_block.h"

void UpdateDisplayVisuals(ENetPeer* peer, int foreground, int x, int y, int background, int itemid, bool sendPacketToEveryone = true)
{
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = 0x56;
	sign.y = 0x15;
	sign.punchX = 0x56;
	sign.punchY = 0x15;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = 0x0b82;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);

	int plength = 73;
	BYTE* raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithDisplayBlock(raw);

	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 65, &itemid, sizeof(int));

	ENetPacket* p = enet_packet_create(0, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	int four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy((char*)p->data + 4, raw, plength);

	if (sendPacketToEveryone)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}

void UpdateUnlockedDoorVisuals(ENetPeer* peer, int foreground, int x, int y, int background, string text, bool sendPacketToEveryone = true, int visuals = 0)
{
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = 0x56;
	sign.y = 0x15;
	sign.punchX = 0x56;
	sign.punchY = 0x15;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = 0x0b82;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);

	BYTE a = 0x00; // 0x08 for locked
	BYTE b = 0xeb; // 0x98 for locked
	uint32_t c = 0xfdfdfdfd;
	short textLen = (short)text.size();
	int plength = 73 + textLen;
	BYTE* raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithUnlockedDoor(raw);
	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 60, &visuals, sizeof(int));
	memcpy(raw + 65, &textLen, sizeof(short));
	memcpy(raw + 67, text.c_str(), textLen);
	memcpy(raw + 67 + textLen, &a, 1);
	memcpy(raw + 68 + textLen, &b, 1);
	memcpy(raw + 69 + textLen, &c, 4);

	ENetPacket* p = enet_packet_create(0, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	int four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy((char*)p->data + 4, raw, plength);

	if (sendPacketToEveryone)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}


void UpdateLockedDoorVisuals(ENetPeer* peer, int foreground, int x, int y, int background, string text, bool sendPacketToEveryone = true, int visuals = 0)
{
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = 0x56;
	sign.y = 0x15;
	sign.punchX = 0x56;
	sign.punchY = 0x15;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = 0x0b82;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);

	BYTE a = 0x08; // 0x00 for unlocked
	BYTE b = 0x98; // 0xeb for unlocked
	uint32_t c = 0xfdfdfdfd;
	short textLen = (short)text.size();
	int plength = 73 + textLen;
	BYTE* raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithUnlockedDoor(raw);
	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 60, &visuals, sizeof(int));
	memcpy(raw + 65, &textLen, sizeof(short));
	memcpy(raw + 67, text.c_str(), textLen);
	memcpy(raw + 67 + textLen, &a, 1);
	memcpy(raw + 68 + textLen, &b, 1);
	memcpy(raw + 69 + textLen, &c, 4);

	ENetPacket* p = enet_packet_create(0, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	int four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy((char*)p->data + 4, raw, plength);

	if (sendPacketToEveryone)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}

void UpdateTreeVisuals(ENetPeer* peer, int foreground, int x, int y, int background, int fruitCount, int timeIntoGrowth, bool forEveryone, int blockStateFlags) {
	//int val = 1 + rand() % 4;

	int hmm = 8;
	int zero = 0;
	int packetType = 5;
	int yeh = hmm + 3 + 1;
	int idk = 15 + 4;
	int blockState = blockStateFlags;
	int bubble_type = 4;
	int ok = 52 + idk;
	int packetSize = ok + 4;
	int yup = ok - 8 - idk;
	int four = 4;
	int magic = 56;
	int wew = ok + 5 + 4;
	int wow = magic + 4 + 5;

	short fc = (short)fruitCount;
	int time = (int)timeIntoGrowth;
	int text_len = 4;
	int treedata = 0x00020000 + 0;
	blockState |= 0x100000;

	BYTE* data = new BYTE[packetSize];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	memset(data, 0, packetSize);

	memcpy(data, &packetType, sizeof(int));
	memcpy(data + yeh, &hmm, sizeof(int));
	memcpy(data + yup, &x, sizeof(int));
	memcpy(data + yup + 4, &y, sizeof(int));
	memcpy(data + 4 + yup + 4, &idk, sizeof(int));
	// here is where tile serialization actually starts
	// it's literally the same as in worldptr i think
	// :)
	memcpy(data + magic, &foreground, sizeof(short));
	memcpy(data + magic + 2, &background, sizeof(short));
	memcpy(data + magic + 4, &blockState, sizeof(int));
	memcpy(data + magic + 8, &bubble_type, sizeof(byte));

	memcpy(data + magic + 9 + 0, &time, 4);
	memcpy(data + magic + 9 + 4, &fc, 1);

	memcpy(data + ok, &blockState, sizeof(int));
	memcpy(p->data, &four, four);

	memcpy((char*)p->data + four, data, packetSize);
	if (forEveryone)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete data;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete data;
	}
}

void UpdateBlockState(ENetPeer* peer, int x, int y, bool forEveryone, WorldInfo* worldInfo) {

	if (!worldInfo) return;

	int i = y * worldInfo->width + x;

	int blockStateFlags = 0;


	if (worldInfo->items[i].flipped)
		blockStateFlags |= 0x00200000;
	if (worldInfo->items[i].water)
		blockStateFlags |= 0x04000000;
	if (worldInfo->items[i].glue)
		blockStateFlags |= 0x08000000;
	if (worldInfo->items[i].fire)
		blockStateFlags |= 0x10000000;
	if (worldInfo->items[i].red)
		blockStateFlags |= 0x20000000;
	if (worldInfo->items[i].green)
		blockStateFlags |= 0x40000000;
	if (worldInfo->items[i].blue)
		blockStateFlags |= 0x80000000;
	if (worldInfo->items[i].activated)
		blockStateFlags |= 0x00400000;
	//	if (worldInfo->items[i].silenced)
		//	blockStateFlags |= 0x02400000;






	if (blockStateFlags != 0)
	{
		TileExtra data;
		data.packetType = 0x5;
		data.characterState = 8;
		data.charStat = 8;
		data.blockid = worldInfo->items[i].foreground;
		data.backgroundid = worldInfo->items[i].background;
		data.visual = blockStateFlags;
		data.punchX = x;
		data.punchY = y;

		ENetPeer* currentPeer;

		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				SendPacketRaw2(192, packBlockVisual(&data), 100, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}

	}
	else {
		TileExtra data;
		data.packetType = 0x5;
		data.characterState = 8;
		data.charStat = 8;
		data.blockid = worldInfo->items[i].foreground;
		data.backgroundid = worldInfo->items[i].background;
		data.visual = blockStateFlags;
		data.punchX = x;
		data.punchY = y;

		ENetPeer* currentPeer;

		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				SendPacketRaw2(192, packBlockVisual(&data), 100, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}

	}
}
void UpdateVisualsForBlock(ENetPeer* peer, bool forEveryone, int x, int y, WorldInfo* worldInfo, bool useLockId = true)
{
	if (!worldInfo) return;

	int i = y * worldInfo->width + x;

	int blockStateFlags = 0;


	if (worldInfo->items[i].flipped)
		blockStateFlags |= 0x00200000;
	if (worldInfo->items[i].water)
		blockStateFlags |= 0x04000000;
	if (worldInfo->items[i].glue)
		blockStateFlags |= 0x08000000;
	if (worldInfo->items[i].fire)
		blockStateFlags |= 0x10000000;
	if (worldInfo->items[i].red)
		blockStateFlags |= 0x20000000;
	if (worldInfo->items[i].green)
		blockStateFlags |= 0x40000000;
	if (worldInfo->items[i].blue)
		blockStateFlags |= 0x80000000;




	else if (GetItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::MAIN_DOOR)
	{
		UpdateUnlockedDoorVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, "EXIT", forEveryone, blockStateFlags);
	}

	else if (worldInfo->items[i].foreground == 2946)
	{

		UpdateDisplayVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, worldInfo->items[i].intdata);
	}
	else if (worldInfo->items[i].foreground % 2 == 1)
	{
		UpdateTreeVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, 3, 59, true, 0);
	}
	else if (blockStateFlags != 0)
	{
		UpdateMessageVisuals(peer, worldInfo->items[i].foreground, x, y, "", worldInfo->items[i].background, 0, forEveryone, blockStateFlags);
	}
}
void DoRegister(ENetPeer* peer) {
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wGet a GrowID``|left|206|\n\nadd_spacer|small|\nadd_textbox|A `wGrowID `wmeans `oyou can use a name and password to logon from any device.|\nadd_spacer|small|\nadd_textbox|This `wname `owill be reserved for you and `wshown to other players`o, so choose carefully!|\nadd_text_input|username|GrowID||30|\nadd_text_input|password|Password||100|\nadd_text_input|passwordverify|Password Verify||100|\nadd_textbox|Your `wemail address `owill only be used for account verification purposes and won't be spammed or shared. If you use a fake email, you'll never be able to recover or change your password.|\nadd_text_input|email|Email||100||\nend_dialog|register|Cancel|Get My GrowID!|\n"));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
void PlayAudioSelf(ENetPeer* peer, string audioFile)
{
	string text = "action|play_sfx\nfile|" + audioFile + "\ndelayMS|0\n";
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


void sendCustomState(ENetPeer* peer, PlayerInfo* info, int xpseed, int yspeed) {
	//return; // TODO
	int netID = info->netID;
	ENetPeer* currentPeer;
	int state = getState(info);
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			float water = 125.0f;
			data.packetType = 0x14;
			data.characterState = 0; // animation
			data.x = 1000;
			if (((PlayerInfo*)(peer->data))->cloth_hand == 366) {
				data.y = -400; // - is hbow
			}
			else {
				data.y = 400;
			}
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = yspeed;
			data.YSpeed = xpseed;
			data.netID = netID;
			data.plantingTree = state;
			BYTE* raw = packPlayerMoving(&data);
			int var = 0x818100; // placing and breking 0x808040 
			memcpy(raw + 1, &var, 3);
			memcpy(raw + 16, &water, 4);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

void sendState(ENetPeer* peer, PlayerInfo* info) {
	//return; // TODO
	int netID = info->netID;
	ENetPeer* currentPeer;
	int state = getState(info);
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			float water = 125.0f;
			data.packetType = 0x14;
			data.characterState = 0; // animation
			data.x = 1000;
			if (((PlayerInfo*)(peer->data))->cloth_hand == 366) {
				data.y = -400; // - is hbow
			}
			else {
				data.y = 400;
			}
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 1000;
			data.netID = netID;
			data.plantingTree = state;
			BYTE* raw = packPlayerMoving(&data);
			int var = 0x818100; // placing and breking 0x808040 
			memcpy(raw + 1, &var, 3);
			memcpy(raw + 16, &water, 4);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}
void RemoveItemFromInv(ENetPeer* peer, int itemId, int count, bool update)
{
	PlayerInventory* inventory = &((PlayerInfo*)(peer->data))->inventory;
	int idx = 0;
	for (auto& a : inventory->items)
	{
		if (a.itemID == itemId)
		{
			int f = a.itemCount;
			f -= count;
			if (f <= 0)
			{
				inventory->items.erase(inventory->items.begin() + idx);
				break;
			}
			else
			{
				a.itemCount = f;
			}
		}
		idx++;
	}
	if (update) sendInventory(peer, *inventory);
}
void sendStuffweather(ENetPeer* peer, int x, int y, uint16_t itemid, uint16_t gravity, bool spin, bool invert)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 10 + 8;
	uint8_t* packet = new uint8_t[4 + 56 + 10 + 8];
	memset(packet, 0, 4 + 56 + 10 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 3832; // bg machine id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x31;
	*(uint32_t*)(packet + 4 + 56 + 9) = itemid;
	*(uint32_t*)(packet + 4 + 56 + 13) = gravity;
	*(uint8_t*)(packet + 4 + 56 + 17) = spin | (invert << 1);
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 10, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}
void sendBackground(ENetPeer* peer, int x, int y, uint16_t itemid)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 5 + 8;
	uint8_t* packet = new uint8_t[4 + 56 + 5 + 8];
	memset(packet, 0, 4 + 56 + 5 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 5000; // bg machine id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x28;
	*(uint16_t*)(packet + 4 + 56 + 9) = itemid;
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 5, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}
bool isInside(int circle_x, int circle_y,
	int rad, int x, int y)
{

	if ((x - circle_x) * (x - circle_x) +
		(y - circle_y) * (y - circle_y) <= rad * rad)
		return true;
	else
		return false;

}
/*
void sendNPC(ENetPeer* peer, float fromX, float fromY, float toX, float toY, float speed, uint8_t npc_id, uint8_t npc_type, uint8_t command) {
	PlayerMoving pmov;
	memset(&pmov, 0, sizeof(PlayerMoving));
	//*(uint8_t*)(&pmov) = 34;
	*(uint32_t*)(&pmov) = 34 | (npc_type << 8) | (npc_id << 16) | (command << 24);
	*(float*)(&pmov + 40) = 1;//speed;
	pmov.x = fromX;
	pmov.y = fromY;
	pmov.XSpeed = toX;
	pmov.YSpeed = toY;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	uint8_t* packet = new uint8_t[4 + 56];
	memset(packet, 0, 4 + 56);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, sizeof(PlayerMoving));
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}
*/
void sendDrop(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect)
{
	if (item >= 7068) return;
	if (item < 0) return;
	ENetPeer* currentPeer;
	string name = "";
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = item;
			float val = count; // item count
			BYTE val2 = specialEffect;

			BYTE* raw = packPlayerMoving(&data);
			memcpy(raw + 16, &val, 4);
			memcpy(raw + 1, &val2, 1);

			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}
void RemoveDroppedItem(ENetPeer* peer, int obj_id, WorldInfo* world)
{
	if (!world) return;


	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			BYTE* b = new BYTE[56];
			memset(b, 0, 56);
			*((int*)&b[0]) = 0xe;
			*((int*)&b[4]) = -2; // type
			*((int*)&b[8]) = -1;
			*((int*)&b[20]) = obj_id + 1; // source ID 1

			SendPacketRaw(4, b, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}
void processTakeServer(ENetPeer* peer, int itemIdx)
{
	cout << "Server took item" << endl;
	PlayerInfo* pinfo = ((PlayerInfo*)(peer->data));
	WorldInfo* world = getPlyersWorld(peer);
	if (!world) return;
	bool legit = true;
	int atik = -1;
	int errcode = 1;
	for (int i = 0; i < world->droppedItems.size(); i++)
	{
		if (world->droppedItems.at(i).uid == itemIdx)
		{
			atik = i;
			break;
		}
	}
	legit = atik != -1;
	if (legit) {
		try {
			DroppedItem droppedItem = world->droppedItems.at(atik);
			world->droppedItems.erase(world->droppedItems.begin() + atik);
			if (droppedItem.id != 112) {
				int rarity = items.at(droppedItem.id).rarity;
				if (rarity <= 998) {
					Player::OnConsoleMessage(peer, "`oCollected `w" + to_string(droppedItem.count) + " " + items.at(droppedItem.id).name + "`o. Rarity: `w" + to_string(items.at(droppedItem.id).rarity) + "``");
				}
				else {
					Player::OnConsoleMessage(peer, "`oCollected `w" + to_string(droppedItem.count) + " " + items.at(droppedItem.id).name + "`o.``");
				}
			}
			else {

			}

		}
		catch (...) {
			return;
		}
	}
}
int dropItem(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect)
{
	cout << "Item was dropped" << endl;
	WorldInfo* world = getPlyersWorld(peer);
	if (!world) return -1;
	if (item >= (coredatasize - 2)) return -1;
	if (item < 0)  return -1;
	if (x == 0 || y == 0)  return -1;
	int blockX = x / 32;
	int blockY = y / 32;
	if (blockX<0 || blockY<0 || blockX>world->width || blockY>world->height) return -1;
	try {

		bool e = false;
		if (item == 112)
		{
			if (count == 1) world->items[blockX + (blockY * world->width)].yellowGems++;
			if (count == 5) world->items[blockX + (blockY * world->width)].blueGems++;
			if (count == 10) world->items[blockX + (blockY * world->width)].redGems++;
			if (count == 50) world->items[blockX + (blockY * world->width)].greenGems++;
			if (count == 100) world->items[blockX + (blockY * world->width)].purpleGems++;
			vector<int> idstoremove;


			if (world->items[blockX + (blockY * world->width)].yellowGems > 4)
			{
				for (int i = 0; i < world->droppedItems.size(); i++) {
					if (blockX == (int)(world->droppedItems.at(i).x / 32) && blockY == (int)(world->droppedItems.at(i).y / 32)) {
						if (world->droppedItems.at(i).count == 1) {

							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);

						}
					}
				}
				world->items[blockX + (blockY * world->width)].yellowGems = 0;
				world->items[blockX + (blockY * world->width)].blueGems++;
				count = 5;
				e = true;
			}
			if (world->items[blockX + (blockY * world->width)].blueGems > 1) {
				for (int i = 0; i < world->droppedItems.size(); i++) {
					if (blockX == (int)(world->droppedItems.at(i).x / 32) && blockY == (int)(world->droppedItems.at(i).y / 32)) {
						if (world->droppedItems.at(i).count == 5) {

							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);

						}
					}
				}
				world->items[blockX + (blockY * world->width)].blueGems = 0;
				world->items[blockX + (blockY * world->width)].redGems++;
				count = 10;
				e = true;
			}
			if (world->items[blockX + (blockY * world->width)].redGems > 4) {
				for (int i = 0; i < world->droppedItems.size(); i++) {
					if (blockX == (int)(world->droppedItems.at(i).x / 32) && blockY == (int)(world->droppedItems.at(i).y / 32)) {
						if (world->droppedItems.at(i).count == 10) {

							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);

						}
					}
				}
				world->items[blockX + (blockY * world->width)].redGems = 0;
				world->items[blockX + (blockY * world->width)].greenGems++;
				count = 50;
				e = true;
			}
			if (world->items[blockX + (blockY * world->width)].greenGems > 1) {
				for (int i = 0; i < world->droppedItems.size(); i++) {
					if (blockX == (int)(world->droppedItems.at(i).x / 32) && blockY == (int)(world->droppedItems.at(i).y / 32)) {
						if (world->droppedItems.at(i).count == 50) {

							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);

						}
					}
				}
				world->items[blockX + (blockY * world->width)].greenGems = 0;
				world->items[blockX + (blockY * world->width)].purpleGems++;
				count = 100;
				e = true;

			}


			for (int i = 0; i < idstoremove.size(); i++) processTakeServer(peer, idstoremove.at(i));


		}
		DroppedItem itemDropped;
		itemDropped.id = item;
		itemDropped.count = count;
		itemDropped.x = x;
		itemDropped.y = y;
		itemDropped.uid = world->droppedCount++;
		world->droppedItems.push_back(itemDropped);
		sendDrop(peer, netID, x, y, item, count, specialEffect);
		return world->droppedCount - 1;
	}
	catch (...) {
		return 1;
	}

}

void sendCollect(ENetPeer* peer, int netID, int x, int y, int uid)
{
	if (uid >= 2147480000) return;
	if (uid < 0) return;
	ENetPeer* currentPeer;
	string name = "";
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = uid;
			SendPacketRaw(4, packPlayerMoving(&data), 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

int getGemCount(int item) {
	int count = 0;
	try {
		int rarity = items.at(item).rarity;
		if (rarity == 0) return 0;
		if (rarity > 13) {
			count = rarity / 13;
		}
		else {
			int ran = rand() % 2;
			switch (ran) {
			case 1:
				count = 1;
				break;
			case 2:
				count = 2;
				break;
			default:
				count = 0;
				break;
			}
		}
	}
	catch (...) {
		return 0;
	}
	return count;
}
void processTake(ENetPeer* peer, PlayerMoving* pMov, int itemIdx, float x, float y)
{
	cout << "Player taking item" << endl;
	PlayerInfo* pinfo = ((PlayerInfo*)(peer->data));
	WorldInfo* world = getPlyersWorld(peer);
	if (!world) return;
	if (x == 0 || y == 0) return;
	int blockX = (int)x / 32;
	int blockY = (int)y / 32;
	if (blockX<0 || blockY<0 || blockX>world->width || blockY>world->height) return;
	bool legit = true;
	int atik = -1;
	int errcode = 1;
	for (int i = 0; i < world->droppedItems.size(); i++)
	{
		if (world->droppedItems.at(i).uid == itemIdx)
		{
			atik = i;
			break;
		}
	}
	legit = atik != -1;
	if (legit) {
		try {
			DroppedItem droppedItem = world->droppedItems.at(atik);
			world->droppedItems.erase(world->droppedItems.begin() + atik);
			int did = droppedItem.id;
			if (droppedItem.id != 112) {
				if (items.at(droppedItem.id).rarity == 999) {

					Player::OnConsoleMessage(peer, "`oCollected `w" + to_string(droppedItem.count) + " " + items.at(droppedItem.id).name + "`o.``");
				}
				else {
					Player::OnConsoleMessage(peer, "`oCollected `w" + to_string(droppedItem.count) + " " + items.at(droppedItem.id).name + "`o. Rarity: `w" + to_string(items.at(droppedItem.id).rarity) + "``");
				}
			}
			else {
				if (droppedItem.count == 1) world->items[blockX + (blockY * world->width)].yellowGems--;
				if (droppedItem.count == 5)  world->items[blockX + (blockY * world->width)].blueGems--;
				if (droppedItem.count == 10)  world->items[blockX + (blockY * world->width)].redGems--;
				if (droppedItem.count == 50)  world->items[blockX + (blockY * world->width)].greenGems--;
				if (droppedItem.count == 100)  world->items[blockX + (blockY * world->width)].purpleGems--;
				((PlayerInfo*)(peer->data))->gems += droppedItem.count;
			}


			sendCollect(peer, pinfo->netID, pMov ? pMov->x : pinfo->x, pMov ? pMov->y : pinfo->y, itemIdx + 1);
		}
		catch (...) {
			return;
		}
	}
}
int HasItemsInInv(ENetPeer* peer, int itemId, int count = -1)
{
	PlayerInventory* inventory = &((PlayerInfo*)(peer->data))->inventory;
	int idx = 0;
	for (auto& a : inventory->items)
	{
		if (a.itemID == itemId)
		{
			if (a.itemCount >= count || count == -1)
				return idx;
		}
		idx++;
	}
	return -1;
}

void AddItemToInv(ENetPeer* peer, int itemId, int count)
{
	PlayerInventory* inventory = &((PlayerInfo*)(peer->data))->inventory;
	if (HasItemsInInv(peer, itemId, 1) == -1)
	{
		InventoryItem it;
		it.itemCount = count;
		it.itemID = itemId;
		inventory->items.push_back(it);
	}
	else
	{
		int idx = HasItemsInInv(peer, itemId, 1);
		inventory->items.at(idx).itemCount += count;
		if (inventory->items.at(idx).itemCount > 200)
		{
			//DropItem(peer, ((PlayerInfo*)(peer->data))->netID, ((PlayerInfo*)(peer->data))->x, ((PlayerInfo*)(peer->data))->y, itemId, count - 200, 0);
			inventory->items.at(idx).itemCount = 200;
		}
	}
	sendInventory(peer, *inventory);
}
/*
void sendItemFly(ENetPeer* peer, float fromX, float fromY, float toX, float toY, uint16_t id) {
	PlayerMoving pmov;
	pmov.packetType = 19;
	pmov.netID = -1;
	*(uint8_t*)(&pmov + 3) = 6;
	*(int*)(&pmov + 8) = -1;
	pmov.x = fromX;
	pmov.y = fromY;
	pmov.XSpeed = toX;
	pmov.YSpeed = toY;
	pmov.punchX = id;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);

	uint8_t* packet = new uint8_t[4 + 56];
	memset(packet, 0, 4 + 56);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);

	ENetPacket* epacket = enet_packet_create(packet, 4 + 56, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}
*/
void sendDShelf(ENetPeer* peer, int x, int y, int item1, int item2, int item3, int item4)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 8 + 16;
	uint8_t* packet = new uint8_t[4 + 56 + 8 + 16];
	memset(packet, 0, 4 + 56 + 8 + 16);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 3794; // display shelf id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x2B;
	*(int*)(packet + 4 + 56 + 9 + 0 * 4) = item1;
	*(int*)(packet + 4 + 56 + 9 + 1 * 4) = item2;
	*(int*)(packet + 4 + 56 + 9 + 2 * 4) = item3;
	*(int*)(packet + 4 + 56 + 9 + 3 * 4) = 242;
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 16, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}


string lockTileDatas(int visual, uint32_t owner, uint32_t adminLength, vector<string> admins, bool isPublic = false, uint8_t bpm = 0) {
	string data;
	data.resize(4 + 6 + 4 + 4 + adminLength * 4 + 8);
	if (bpm) data.resize(data.length() + 4);
	data[2] = 0x01;
	if (isPublic) data[2] |= 0x80;
	data[4] = 3;
	data[5] = visual; // or 0x02
	STRINT(data, 6) = owner;
	STRINT(data, 10) = adminLength;
	for (uint32_t i = 0; i < adminLength; i++) {

	}

	if (bpm) {
		STRINT(data, 10)++;
		STRINT(data, 14 + adminLength * 4) = -bpm;

	}
	return data;
}
void sendArrow(ENetPeer* peer, uint16_t itemid, bool droppeditem) {
	PlayerMoving pmov;
	memset(&pmov, 0, sizeof(PlayerMoving));
	*(uint32_t*)(&pmov) = 37 | (droppeditem << 8);
	pmov.netID = itemid;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	uint8_t* packet = new uint8_t[4 + 56];
	memset(packet, 0, 4 + 56);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, sizeof(PlayerMoving));
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}


void sendPlayerFishing(ENetPeer* peer, int netID, int x, int y) {
	PlayerMoving p;
	p.packetType = 0x1F;
	p.netID = netID;
	p.punchX = x;
	p.punchY = y;
	SendPacketRaw(4, packPlayerMoving(&p), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}

uint8_t* lockTileData(uint32_t owner, uint32_t adminLength, uint32_t* admins, bool rainbow) {
	uint8_t* data = new uint8_t[4 + 2 + 4 + 4 + adminLength * 4 + 8];
	memset(data, 0, 4 + 2 + 4 + 4 + adminLength * 4 + 8);
	data[2] = 0x1;
	data[4] = 3;
	data[5] = rainbow ? 0x80 : 0x00;
	*(uint32_t*)(data + 6) = owner;

	*(uint32_t*)(data + 10) = adminLength;
	for (uint32_t i = 0; i < adminLength; i++) {
		*(uint32_t*)(data + 14 + i * 4) = admins[i];
	}
	return data;
}
void sendLock(ENetPeer* peer, int x, int y, int lockid, uint32_t owner, uint32_t adminsize, uint32_t* admins, bool rainbow)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 4 + 22 + adminsize * 4;
	uint8_t* packet = new uint8_t[4 + 56 + 4 + 22 + adminsize * 4];
	memset(packet, 0, 4 + 56 + 4 + 22 + adminsize * 4);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 56 + 4) = lockid;
	uint8_t* tiledata = lockTileData(owner, adminsize, admins, rainbow);
	memcpy(packet + 60 + 4, tiledata, 22 + adminsize + 4);
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 4 + 22 + adminsize * 4, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
	delete tiledata;
}

void ApplyLockPacket(ENetPeer* _peer, int x, int y, int id, int locksize, int lockowner)
{
	PlayerInfo* player = (PlayerInfo*)(_peer->data);

	PlayerMoving pmov;
	pmov.packetType = 0xf;
	pmov.characterState = 0;
	pmov.x = 0;
	pmov.y = 0;
	pmov.XSpeed = 0;
	pmov.YSpeed = 0;
	pmov.plantingTree = id;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = lockowner;
	byte* pmovp = packPlayerMoving(&pmov);
	byte* packet = new byte[64 + locksize * 2];
	memset(packet, 0, 64 + locksize * 2);
	packet[0] = 4;
	memcpy(packet + 4, pmovp, 56);
	delete pmovp;
	packet[12] = locksize;
	packet[16] = 8;
	int locksz = locksize * 2;
	memcpy(packet + 56, &locksz, 4);
	for (int i = 0; i < locksize; i++)
	{
		int fml = y * 100 + x - i;
		memcpy(packet + 60 + i * 2, &fml, 2);
	}

	ENetPacket* packetenet = enet_packet_create(packet,
		64 + locksize * 2,
		ENET_PACKET_FLAG_RELIABLE);

	for (ENetPeer* peer = server->peers; peer < &server->peers[server->peerCount]; ++peer) {
		if (peer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(_peer, peer)) {
			enet_peer_send(peer, 0, packetenet);
		}
	}

	delete packet;
}

uint8_t* luckTileData(uint32_t owner, uint32_t adminLength, uint32_t* admins) {
	uint8_t* data = new uint8_t[4 + 2 + 4 + 4 + adminLength * 4 + 8];
	memset(data, 0, 4 + 2 + 4 + 4 + adminLength * 4 + 8);
	data[2] = 0x1;
	data[4] = 3;
	*(uint32_t*)(data + 6) = owner;

	*(uint32_t*)(data + 10) = adminLength;
	for (uint32_t i = 0; i < adminLength; i++) {
		*(uint32_t*)(data + 14 + i * 4) = admins[i];
	}
	return data;
}
void sendLuck(ENetPeer* peer, int x, int y, int lockid, uint32_t owner, uint32_t adminsize, uint32_t* admins)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 4 + 22 + adminsize * 4;
	uint8_t* packet = new uint8_t[4 + 56 + 4 + 22 + adminsize * 4];
	memset(packet, 0, 4 + 56 + 4 + 22 + adminsize * 4);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 56 + 4) = lockid;
	uint8_t* tiledata = luckTileData(owner, adminsize, admins);
	memcpy(packet + 60 + 4, tiledata, 22 + adminsize + 4);
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 4 + 22 + adminsize * 4, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
	delete tiledata;
}


void sendHMonitor(ENetPeer* peer, int x, int y, std::string name, bool online)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	int len = 7 + name.length();
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 8 + len;
	uint8_t* packet = new uint8_t[4 + 56 + 8 + len];
	memset(packet, 0, 4 + 56 + 8 + len);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 0x4D8; // display shelf id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1 | (online ? 0x40 : 0);
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x0B;
	*(uint16_t*)(packet + 4 + 56 + 13) = name.length();
	memcpy(packet + 4 + 56 + 15, name.data(), name.length());
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + len, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}

void SendParticleEffect(ENetPeer* peer, int x, int y, int size, int id, int delay)
{
	PlayerMoving datx;
	datx.packetType = 0x11;
	datx.x = x;
	datx.y = y;
	datx.YSpeed = id;
	datx.XSpeed = size;
	datx.plantingTree = delay;
	SendPacketRaw(4, packPlayerMoving(&datx), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}
void SendCanvasData(ENetPeer* peer, short fg, short bg, int x, int y, int item, string text) {

	byte* ExtendedData = new byte[15 + item + text.length()];
	int state = 0x0010000;
	int extendedLen = 15 + item + text.length();
	int TextLen = text.length();

	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;

	byte* raw = new byte[56 + 15 + item + TextLen];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);

	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	memcpy(ExtendedData + 4, &state, 4);
	ExtendedData[8] = 0x23;
	memcpy(ExtendedData + 9, &item, 4);
	memcpy(ExtendedData + 13, &TextLen, 2);
	memcpy(ExtendedData + 15, text.data(), TextLen);

	memcpy(raw + 56, ExtendedData, extendedLen);

	SendPacketRaw3(4, raw, 56 + 15 + item + TextLen, 0, peer, ENET_PACKET_FLAG_RELIABLE);

}
void treeModify(ENetPeer* peer, int x, int y, int causedBy) {

	PlayerMoving data_;
	data_.packetType = 0xC;
	data_.x = 0;
	data_.y = 0;
	data_.punchX = x;
	data_.punchY = y;
	data_.XSpeed = 0;
	data_.YSpeed = 0;
	data_.netID = causedBy;
	data_.plantingTree = 0;
	BYTE* raw = packPlayerMoving(&data_);
	raw[8] = 0xff; raw[9] = 0xff; raw[10] = 0xff; raw[11] = 0xff;
	SendPacketRaw(4, raw, 102, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}


bool isSeed(int block)
{
	return block % 2 == 1;
}
void sendTileUpdate(int x, int y, int tile, int causedBy, ENetPeer* peer)
{
	int dicenr = 0;
	PlayerMoving data;
	//data.packetType = 0x14;
	data.packetType = 0x3;

	//data.characterState = 0x924; // animation
	data.characterState = 0x0; // animation
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	data.XSpeed = 0;
	data.YSpeed = 0;
	data.netID = causedBy;
	data.plantingTree = tile;
	bool isLock = false;
	bool isMonitor = false;
	bool isTree = false;
	WorldInfo* world = getPlyersWorld(peer);
	int netID = ((PlayerInfo*)(peer->data))->netID;
	if (world == NULL) return;
	if (GetItemDef(tile).blockType == BlockTypes::SEED) {
	
		if (world->items[x + (y * world->width)].foreground != 0) {
		
			return;
			
			
		}
		else {
			isTree = true;
			
		}
	}
	
	if (world->items[x + (y * world->width)].foreground == 2946 && tile != 18 && tile != 32 && tile > 0) {
		if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel > 1) {

			world->items[x + (y * world->width)].intdata = tile;
			SendThrowEffect(peer, tile, netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
			UpdateVisualsForBlock(peer, true, x, y, world);
			return;


		}

	}
	int fg = world->items[x + (y * world->width)].foreground;
	int bg = world->items[x + (y * world->width)].background;

	if (world->items[x + (y * world->width)].foreground == 3528 && tile != 18 && tile != 32 && tile > 0) {
		if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel > 1) {

			world->items[x + (y * world->width)].intdata = tile;
			SendCanvasData(peer, world->items[x + (y * world->width)].foreground, world->items[x + (y * world->width)].background, x, y, tile, getItemDef(tile).name);
			return;

		}

	}



	PlayerInfo* pinfo = ((PlayerInfo*)(peer->data));
	



	// fist 
	if (tile == 18) {
		if (world->owner == "" || pinfo->rawName == world->owner || pinfo->adminLevel > 1) {
			if (world->items[x + (y * world->width)].foreground == 4992) {
				if (world->items[x + (y * world->width)].activated) {




					world->items[x + (y * world->width)].activated = false;
					UpdateBlockState(peer, x, y, true, world);



				}
				else {

					world->items[x + (y * world->width)].activated = true;
					UpdateBlockState(peer, x, y, true, world);

				}
			}
			if (world->items[x + (y * world->width)].foreground == 3616) {
				if (world->items[x + (y * world->width)].activated) {
					world->items[x + (y * world->width)].activated = false;
					UpdateBlockState(peer, x, y, true, world);
					world->isPineappleGuard = false;
				}
				else {
					world->isPineappleGuard = true;
					world->items[x + (y * world->width)].activated = true;
					UpdateBlockState(peer, x, y, true, world);

				}
			}
			if (world->items[x + (y * world->width)].foreground == 5000)
			{

				world->weather = 34;
				ENetPeer* currentPeer;

				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						world->items[x + (y * world->width)].activeWeather = true;
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);

						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
			if (world->items[x + (y * world->width)].foreground == 3832)
			{
				world->weather = 29;
				ENetPeer* currentPeer;

				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						world->items[x + (y * world->width)].activeWeather = true;
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);

						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
			if (world->items[x + (y * world->width)].foreground == 3694)
			{
				world->weather = 28;
				ENetPeer* currentPeer;

				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						world->items[x + (y * world->width)].activeWeather = true;
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);

						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}

		}
	}

	//

	if (isSeed(world->items[x + (y * world->width)].foreground)) {
		if (tile == 18) {
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer)) {
					treeModify(currentPeer, x, y, netID);
					int chance = (rand() % 100) + 1;
					int numb = (rand() % 8) + 1;
					if (chance < 30) {
						
						

						dropItem(
							peer, -1,
							x * 32 + (rand() % 16),
							y * 32 + (rand() % 16),
						112,
							1, 0);
					
					}
					if (chance < 50) {
						Player::OnTalkBubble(peer, netID, "A "+GetItemDef(world->items[x + (y * world->width)].foreground).name + " seed falls out!", false);
						dropItem(
							peer, -1,
							x * 32 - (rand() % 8),
							y * 32 + (rand() % 8),
							world->items[x + (y * world->width)].foreground,
							1, 0);
					}
				
						dropItem(
							peer, -1,
							x * 32 + (rand() % 16),
							y * 32 + (rand() % 16),
							world->items[x + (y * world->width)].foreground - 1,
						numb, 0);
					
				}
			}
		}
		world->items[x + (y * world->width)].foreground = 0;
		return;
	}


	if (tile == 1240 && isWorldOwner(peer, world)) {

		isMonitor = true;
	}


	if (tile == 32 || tile == 18) {
		if (world->items[x + (y * world->width)].foreground == 1790) {

			if (pinfo->ltype == 1 && pinfo->lqueststep == 1) {
				string btntext = "";
				if (pinfo->gems < 1) {
					btntext = "You have none to deliver!";
				}
				else if (pinfo->gems < 100001) {
					btntext = "Deliver " + to_string(pinfo->gems) + " Gems";

				}
				else {
					btntext = "Deliver " + to_string(100000) + " Gems";
				}
				string ste = "set_default_color|`o\nadd_label_with_icon|big|`9Quest Of Fire``|left|1790|\nadd_smalltext|(Step 1/10)|\nadd_spacer|small|\nadd_textbox|`oI challenge you to bring me 100,000 gems!|\nadd_spacer|small|\nadd_smalltext|Current progress " + to_string(((PlayerInfo*)(peer->data))->lquestprogress) + "/100000|\nadd_button|lwizstep1|" + btntext + "|\nadd_button|giveup|Give up this quest|\nend_dialog|lqueststep1|Goodbye!|";
				Player::OnDialogRequest(peer, ste);

			}
			else if (pinfo->ltype == 1 && pinfo->lqueststep == 2) {
				string btn = "";
				if (pinfo->lquestprogress < 1000) {
					btn = "I will go smash more!";
				}
				else {
					btn = "No block can beat me!";
				}
				string k = "set_default_color|`o\nadd_label_with_icon|big|`9Quest Of Fire``|left|1790|\nadd_smalltext|(Step 2/10)|\nadd_spacer|small|\nadd_textbox|`oI want you to break 1000 blocks because why not.|\nadd_spacer|small||\nadd_smalltext|Current progress " + to_string(((PlayerInfo*)(peer->data))->lquestprogress) + "/1000|\nadd_button|lwizstep2|" + btn + "|\nadd_button|giveup|Give up this quest|\nend_dialog|lqueststep1|Goodbye!|";
				Player::OnDialogRequest(peer, k);

			}
			else {

				string lwiz = "set_default_color|`o\nadd_label_with_icon|big|`9The Legendary Wizard``|left|1790|\nadd_textbox|`oGreetings, traveler! I am the Legendary Wizard. Should you wish to embark on a Legendary Quest.|\nadd_textbox|`oChoose on from below.|\nadd_spacer|small|\nadd_button|starthonor|`9Quest For Honor|\nadd_button|startfire|`9Quest For Fire|\nend_dialog|lqueststart|No Thanks|";

				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), lwiz));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
			}

		}

	}

	if (tile == 2914 && ((PlayerInfo*)(peer->data))->cloth_hand == 2912) {

		if (world->items[x + (y * world->width)].water) {
			if (((PlayerInfo*)(peer->data))->x != 0) {
				int pY = (int)((PlayerInfo*)(peer->data))->y / 32;
				int pX = (int)((PlayerInfo*)(peer->data))->x / 32;
				((PlayerInfo*)(peer->data))->isFishing = true;
				ENetPeer* currentPeer;

				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer)) {
						sendPlayerFishing(currentPeer, ((PlayerInfo*)(peer->data))->netID, x, y);
					}
				}
			}
		}
		return;
	}

	if (tile == 1136) {

		string dialog = "set_default_color|`o\nadd_label_with_icon|big|`wMars Blast``|left|1136|\nadd_textbox|`oThis item creates a new world! Enter a unique name for it.|\nadd_text_input|mars_name|New World Name||25|\nend_dialog|mars_dialog|Cancel|`5Create!|";

		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), dialog));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}


	if (tile == 32) {

		if (world->name != "ADMIN") {
			if (world->owner == "" || pinfo->rawName == world->owner || pinfo->adminLevel > 1) {
				if (world->items[x + (y * world->width)].foreground == 3794) {
					sendDShelf(peer, x, y, 242, 1796, 7188, 242);
				}

				if (world->items[x + (y * world->width)].foreground == 6016) {
					string gscan = "set_default_color|`o\nadd_label_with_icon|big|`wWorld Stats``|left|6016|\nadd_spacer|small|\nadd_textbox|`wThis amazing block can show the stats for the whole world!|\nadd_spacer|small|\nadd_textbox|`wWhich stats would you like to view?|\nadd_button|floatingitems|`oFloating Items|\nadd_spacer|small|\nadd_label|small|`wYou can set the stats to be usable by the public.\nadd_checkbox|checkworldblockspublic|`oWorld blocks is usable by public|\nadd_checkbox|floatsting|`oFloating items is usable by public|\nadd_space|small|\nend_dialog|gazettes|Cancel|Apply|";
					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), gscan));
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet);
					delete p.data;

				}
				if (world->items[x + (y * world->width)].foreground == 3694) {


					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\nadd_label_with_icon|big|`wWeather Machine - Heatwave``|left|3694|\nadd_spacer|small|\nadd_textbox|`oAdjust the color of your heat wave here, by including 0-255 of Red, Green, and Blue.|\nadd_spacer|small|\nadd_text_input|heatwave_red|Red|" + to_string(world->hw_red) + "|3|\nadd_text_input|heatwave_green|Green|" + to_string(world->hw_green) + "|3|\nadd_text_input|heatwave_blue|Blue|" + to_string(world->hw_blue) + "|3|\nadd_quick_exit|\nend_dialog|heatwave|Cancel|Okay|"));
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet);
					delete p.data;
					pinfo->wrenchedBlockLocation = x + (y * world->width);

				}
				if (world->items[x + (y * world->width)].foreground == 3832) {
					string stuff_dialog = "set_default_color|`o\nadd_label_with_icon|big|`wWeather Machine - Stuff``|left|3832|\nadd_spacer|small|\nadd_item_picker|stuff_pick|Item: `2" + GetItemDef(world->stuffID).name + "|Select any item to rain down|\nadd_text_input|stuff_gravity|Gravity:|" + to_string(world->stuff_gravity) + "|3|\nadd_checkbox|stuff_spin|Spin Items|" + to_string(world->stuff_spin) + "|\nadd_checkbox|stuff_invert|Invert Sky Colors|" + to_string(world->stuff_invert) + "|\nadd_textbox|`oSelect item and click okay to continue!|\nend_dialog|stuff_weather|Cancel|Okay|";

					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), stuff_dialog));
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet);
					delete p.data;
					pinfo->wrenchedBlockLocation = x + (y * world->width);
				}
				if (world->items[x + (y * world->width)].foreground == 5000) {

					string itemname = GetItemDef(world->bgID).name;
					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\nadd_label_with_icon|big|`wWeather Machine - Background``|left|5000|\nadd_spacer|small|\nadd_textbox|`oYou can scan any Background Block to set it up in your weather machine.|\nadd_item_picker|bg_pick|Item: `2" + itemname + "|Select any Background Block|\nadd_quick_exit|\nend_dialog|bg_weather|Cancel|Okay|"));
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet);
					delete p.data;
					pinfo->wrenchedBlockLocation = x + (y * world->width);

				}

			}
		}
	}


	if (world->owner == "" || pinfo->rawName == world->owner || pinfo->adminLevel > 1) {
		if (world->items[x + (y * world->width)].foreground == 5638 && tile != 18 && tile != 32 && tile > 0) {
			ENetPeer* currentPeer;

			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer)) {
					sendMag(currentPeer, x, y, tile, 4, 0, 0);
				}
			}



		}
	}



	if (world->items[x + (y * world->width)].fire) {
		if (pinfo->cloth_hand == 3066 || tile == 822) {
			
			if (tile == 822) {
				SendThrowEffect(peer, 822, netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
				world->items[x + (y * world->width)].fire = false;
				UpdateBlockState(peer, x, y, true, world);
				ENetPeer* currentPeer;

				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer)) {
						Player::OnParticleEffect(currentPeer, 149, x * 32 + 16, y * 32 + 16, 0);
					}
				}

				pinfo->firesOutput++;

				return;
			}
			else {
				ENetPeer* currentPeer;

				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer)) {
						Player::OnParticleEffect(currentPeer, 149, x * 32 + 16, y * 32 + 16, 0);
					}
				}
				world->items[x + (y * world->width)].fire = false;
				UpdateBlockState(peer, x, y, true, world);
				pinfo->firesOutput++;
				return;

			}

		}

	}


	if (tile == 3062) {
		if (world->items[x + (y * world->width)].fire == false && world->items[x + (y * world->width)].water == false) {
			if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && GetItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK) {


				if (world->isPineappleGuard) {
					Player::OnTalkBubble(peer, netID, "`wYou cant use consumables here!", true);
					return;
				}
				if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {



					Player::OnTalkBubble(peer, netID, "`wTheres nothing to burn!", true);
					return;
				}
				world->items[x + (y * world->width)].fire = !world->items[x + (y * world->width)].fire;

				ENetPeer* currentPeer;

				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer)) {
						Player::OnParticleEffect(currentPeer, 150, x * 32 + 16, y * 32 + 16, 0);
						Player::OnTalkBubble(currentPeer, netID, "`7[```4MWAHAHAHA!! FIRE FIRE FIRE```7]``", false);
					}
				}
				RemoveItemFromInv(peer, 3062, 1, true);
				UpdateVisualsForBlock(peer, true, x, y, world);


				if (world->items[x + (y * world->width)].foreground == 0) {
					if (getItemDef(tile).rarity != 999) {
						int b = getGemCount(tile) + rand() % 1;
						while (b > 0)
						{
							if (b >= 100)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									100, 0);
								b -= 100;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
								for (int i = 0; i < rand() % 4; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 50)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									50, 0);
								b -= 50;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
								for (int i = 0; i < rand() % 3; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 10)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									10, 0);
								b -= 10;
								for (int i = 0; i < rand() % 4; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 7)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									10, 0);
								b -= 5;
								for (int i = 0; i < rand() % 2; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 5)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									5, 0);
								b -= 5;
								for (int i = 0; i < rand() % 2; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 1)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									1, 0);
								b -= 1;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
						}
					}
				}

			}
		}
	}





	if (tile == 822) {
		if (world->items[x + (y * world->width)].water == false) {
			if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && GetItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK) {
				if (pinfo->rawName == world->owner || pinfo->adminLevel > 1 || world->owner == "") {

					//SendThrowEffect(peer, 822, netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
					world->items[x + (y * world->width)].water = false;
					UpdateBlockState(peer, x, y, true, world);
					int numb = (rand() % 99) + 1;
					if (numb < 40) {
						AddItemToInv(peer, 822, 1);
					}


					return;
				}

				else {
					if (world->isPineappleGuard) {
						Player::OnTalkBubble(peer, netID, "`wYou cant use consumables here!", true);
						return;
					}
					world->items[x + (y * world->width)].water = !world->items[x + (y * world->width)].water;
					RemoveItemFromInv(peer, 822, 1, true);
					SendThrowEffect(peer, 822, netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
					UpdateVisualsForBlock(peer, true, x, y, world);
					return;
				}

			}
		}
	}


	

#pragma region block_multiple_items
	if (pinfo->rawName == world->owner || pinfo->adminLevel > 1 || world->owner == "") {
		if (tile == 3832) {
			int x;
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 3832) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, netID, "You can have have only one Weather Machine - Stuff in your world!", true);
				return;
			}
		}
		if (tile == 3694) {
			int x;
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 3694) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, netID, "You can have have only one Weather Machine - Heatwave in your world!", true);
				return;
			}
		}
		if (tile == 3616) {
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 3616) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, netID, "This world already has a Guardian Pineapple somewhere on it, installing two would be dangerous!", true);
				return;
			}
		}
		if (tile == 5000) {
			int x;
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 5000) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, netID, "You can have have only one Weather Machine - Background in your world!", true);
				return;
			}
		}
	}
#pragma endregion block_multiple_items


	if (tile == 196) {
		if (world->isPineappleGuard) {
			Player::OnTalkBubble(peer, netID, "`wYou cant use consumables here!", false);
			return;
		}
		if (x == pinfo->x / 32 && y == pinfo->y / 32) {

			SendTradeEffect(peer, 196, netID, netID, 150);
			string txt = "A `1blueberry`o slides down your throat! (`$Feelin' Blue`o mod added, `$5 secs`o left)";

			pinfo->skinColor = 4278190335;

			sendClothes(peer);
			PlayAudioSelf(peer, "audio/spray.wav");
			RemoveItemFromInv(peer, 196, 1, true);

			if (pinfo->blueBerry == false) {
				sendConsoleMsg(peer, txt);
				((PlayerInfo*)(peer->data))->lastBerry = 5;
				((PlayerInfo*)(peer->data))->usedBerry = GetCurrentTimeInternalSeconds();
			}

			pinfo->blueBerry = true;




		}

		ENetPeer* currentPeer;

		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				PlayerInfo* cpinfo = ((PlayerInfo*)(currentPeer->data));
				if (x == cpinfo->x / 32 && y == cpinfo->y / 32) {

					cout << "X: " << x << " Y: " << y << endl;
					cout << "X: " << cpinfo->x / 32 << " Y: " << cpinfo->y / 32 << endl;
					SendTradeEffect(currentPeer, 196, netID, cpinfo->netID, 150);
					SendTradeEffect(peer, 196, netID, cpinfo->netID, 150);
					string txt = "A `1blueberry`o slides down your throat! (`$Feelin' Blue`o mod added, `$5 secs`o left)";

					cpinfo->skinColor = 4278190335;

					sendClothes(currentPeer);
					PlayAudioSelf(currentPeer, "audio/spray.wav");

					RemoveItemFromInv(peer, 196, 1, true);

					if (cpinfo->blueBerry == false) {
						sendConsoleMsg(currentPeer, txt);
						((PlayerInfo*)(currentPeer->data))->lastBerry = 5;
						((PlayerInfo*)(currentPeer->data))->usedBerry = GetCurrentTimeInternalSeconds();
					}

					cpinfo->blueBerry = true;
					break;
				}

			}
		}

	}

	if (tile == 1634) {
		if (world->isPineappleGuard) {
			Player::OnTalkBubble(peer, netID, "`wYou cant use consumables here!", false);
			return;
		}
		if (x == pinfo->x / 32 && y == pinfo->y / 32) {


			SendTradeEffect(peer, 1634, netID, netID, 150);
			string txt = "You are full of caffeine! (`$Caffeinated`o mod added, `$5 secs`o left)";


			PlayAudioSelf(peer, "audio/spray.wav");
			RemoveItemFromInv(peer, 1634, 1, true);
			pinfo->haveCigar = true;
			sendCustomState(peer, pinfo, 1000, 360);
			if (pinfo->Caffeine == false) {
				sendConsoleMsg(peer, txt);
				((PlayerInfo*)(peer->data))->leftCoffee = 5;
				((PlayerInfo*)(peer->data))->usedCoffee = GetCurrentTimeInternalSeconds();
			}

			pinfo->Caffeine = true;




		}

	}

	if (x<0 || y<0 || x>world->width || y>world->height) return;
	sendNothingHappened(peer, x, y);

	if (tile != 18 && tile != 32 && getItemDef(tile).blockType != BlockTypes::BACKGROUND && world->items[x + (y * world->width)].foreground != 0) {
		sendNothingHappened(peer, x, y);
		return;
	}

	if (getItemDef(tile).blockType == BlockTypes::LOCK && tile != 202 && tile != 204 && tile != 206 && tile != 4994)
	{
		
			if (((PlayerInfo*)(peer->data))->haveGrowId == true) {
				isLock = true;
			}
			else
			{
				Player::OnConsoleMessage(peer, "`oYou have to register before locking world!``");
				Player::OnPlayPositioned(peer, "audio/punch_locked.wav", netID);
				return;
			}
		
	}

	if (!isOwner(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) {

		if (tile == 6 || tile == 6549) {
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 6 || world->items[x + (y * world->width)].foreground == 6549) {
			return;
		}
	}
	if (!isOwner(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass))
	{
		if (world->items[x + (y * world->width)].foreground == 6 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 3760) {
			return;
		}

		if (tile == 8 || tile == 3760 || tile == 6864) {

			return;
		}

	}

	if (world != NULL) {
		if (world->name != "ADMIN") {
			if (GetItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SIGN || world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214)
			{
				if (tile == 32) {

					if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel > 1) {

						string signtext = world->items[x + (y * world->width)].sign;

						GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + GetItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\n\nadd_spacer|small|\nadd_text_input|signtext||" + signtext + "|200|\nend_dialog|editsign|Cancel|OK|"));
						ENetPacket* packet = enet_packet_create(p.data,
							p.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet);
						delete p.data;
						pinfo->wrenchedBlockLocation = x + (y * world->width);





					}
				}
			}
		}
	}

	
	if (((PlayerInfo*)(peer->data))->haveGrowId == false) {
		if (tile == 242 || tile == 8470 || tile == 5260 || tile == 4428 || tile == 1796 || tile == 2408 || tile == 7188 || tile == 4802 || tile == 5814 || tile == 4428 || tile == 5260 || tile == 8470) {
			DoRegister(peer);

			return;

		}

	}



	if (world->name != "ADMIN") {
		if (world->owner != "") {
			if (isWorldOwner(peer, world) || isWorldAdmin(peer, world) || isDev(peer)) {
				if (getItemDef(fg).blockType == BlockTypes::LOCK && isWorldAdmin(peer, world) && !isWorldOwner(peer, world) && adminLevel(peer) < 2) {
					// This means that you are admin, you cant break wl!
					Player::OnPlayPositioned(peer, "audio/punch_locked.wav", ((PlayerInfo*)(peer->data))->netID);
					return;
				}
				if (tile == 32) {
					if (getItemDef(fg).blockType == BlockTypes::LOCK && fg != 202 && fg != 204 && fg != 206 && fg != 4994)
					{

						int ispub = world->isPublic;
						int allowMod = world->allowNoclip;
						string str = "";
						for (int i = 0; i < world->accessed.size(); i++) {
							string st = world->accessed.at(i);
							str += "\nadd_label|small|" + st.substr(st.find("|") + 1, st.length()) + "|left";
						}
						string wlmenu = "";
						if (str == "") {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit World Properties``|left|" + to_string(getItemDef(fg).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_noclip|Allow everyone to /ghost|" + to_string(allowMod) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0\nadd_text_input|tempo|Music BPM|100|3|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";

						}
						else {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit World Properties``|left|" + to_string(getItemDef(fg).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|" + str + "|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_noclip|Allow everyone to /ghost|" + to_string(allowMod) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0\nadd_text_input|tempo|Music BPM|100|3|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						}
						Player::OnDialogRequest(peer, wlmenu);
					}
				}
			}
			else if (world->isPublic) {
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
				{
					if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) < 3) {
						Player::OnPlayPositioned(peer, "audio/punch_locked.wav", ((PlayerInfo*)(peer->data))->netID);
						return;
					}
					else {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							Player::OnPlayPositioned(peer, "audio/punch_locked.wav", ((PlayerInfo*)(peer->data))->netID);
						}
					}
				}
			}
			else {
				if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) < 2) {
					Player::OnPlayPositioned(peer, "audio/punch_locked.wav", ((PlayerInfo*)(peer->data))->netID);
					if (tile == 32) {
						Player::OnTalkBubble(peer, netID, "This area is owner by " + world->ownerDisplayName +"!", true);
					}
					if (getItemDef(fg).blockType == BlockTypes::LOCK&& fg != 202 && fg != 204 && fg != 206 && fg != 4994) {
						Player::OnTalkBubble(peer, netID, world->ownerDisplayName + "'s " + GetItemDef(fg).name + ".", true);
					}
					return;
				}
				else
				{
					if (getItemDef(fg).blockType == BlockTypes::LOCK)
					{
						Player::OnPlayPositioned(peer, "audio/punch_locked.wav", ((PlayerInfo*)(peer->data))->netID);
					}
				}
			}
		}
	}






	if (tile != 0 && tile != 18)
	{
		if (GetItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
		{

			return;
		}

	}

	if (GetItemDef(tile).blockType == BlockTypes::CONSUMABLE) {
		switch (tile)
		{
		case 6336:
			//sendDialog(peer, growpediaText);
			return;
		default: return;
		}
	}


	if (tile == 32) {

		return;
	}


	ItemDefinition def;
	try {
		def = getItemDef(tile);
		if (def.clothType != ClothTypes::NONE) return;
	}
	catch (int e) {
		def.breakHits = 4;
		def.blockType = BlockTypes::UNKNOWN;
#ifdef TOTAL_LOG
		cout << "Ugh, unsupported item " << tile << endl;
#endif
	}



	//	if (tile == 544 || tile == 546 || tile == 4520 || tile == 382 || tile == 3116 || tile == 4520 || tile == 1792 || tile == 5666 || tile == 2994 || tile == 4368) return;
	//	if (tile == 5708 || tile == 5709 || tile == 5780 || tile == 5781 || tile == 5782 || tile == 5783 || tile == 5784 || tile == 5785 || tile == 5710 || tile == 5711 || tile == 5786 || tile == 5787 || tile == 5788 || tile == 5789 || tile == 5790 || tile == 5791 || tile == 6146 || tile == 6147 || tile == 6148 || tile == 6149 || tile == 6150 || tile == 6151 || tile == 6152 || tile == 6153 || tile == 5670 || tile == 5671 || tile == 5798 || tile == 5799 || tile == 5800 || tile == 5801 || tile == 5802 || tile == 5803 || tile == 5668 || tile == 5669 || tile == 5792 || tile == 5793 || tile == 5794 || tile == 5795 || tile == 5796 || tile == 5797 || tile == 544 || tile == 546 || tile == 4520 || tile == 382 || tile == 3116 || tile == 1792 || tile == 5666 || tile == 2994 || tile == 4368) return;
	if (tile == 1902 || tile == 1508 || tile == 428) return;
	if (tile == 410 || tile == 1770 || tile == 4720 || tile == 4882 || tile == 6392 || tile == 3212 || tile == 1832 || tile == 4742 || tile == 3496 || tile == 3270 || tile == 4722) return;
	if (tile >= CoreDataItems) return;
	if (tile == 18) {
		if (world->items[x + (y * world->width)].background == 6864 && world->items[x + (y * world->width)].foreground == 0) return;
		if (world->items[x + (y * world->width)].background == 0 && world->items[x + (y * world->width)].foreground == 0) return;
		ItemDefinition brak;
		brak = getItemDef(world->items[x + (y * world->width)].foreground);

		//data.netID = -1;
		data.packetType = 0x8;
		data.plantingTree = 6;

		using namespace std::chrono;

		if (((PlayerInfo*)(peer->data))->cloth_hand == 2952 && tile == 18 && fg != 8 && fg != 6) {
			if (fg == 2 || (fg == 0 && bg == 14)) {
				if (isWorldOwner(peer, world) || getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 1 || world->isPublic || world->owner == "") {
				
					data.packetType = 0x3;// 0xC; // 0xF // World::HandlePacketTileChangeRequest
					data.netID = causedBy;
					int kek = fg;
					data.plantingTree = 18;
					if (fg != 0) {
						world->items[x + (y * world->width)].foreground = 0;
						kek = fg;
					}
					else {
						world->items[x + (y * world->width)].foreground = 0;
						world->items[x + (y * world->width)].background = 0;
						kek = bg;
					}

					ENetPeer* currentPeer;
					for (currentPeer = server->peers;
						currentPeer < &server->peers[server->peerCount];
						++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
							continue;
						if (isHere(peer, currentPeer)) {
							BYTE* rawx = packPlayerMoving(&data);
							SendPacketRaw(4, rawx, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);


							SendParticleEffect(currentPeer, x * 32, y * 32, kek, 97, 0);




						}
					}
					
					world->items[x + (y * world->width)].activated = false;
					world->items[x + (y * world->width)].flipped = false;
					if (items.at(fg).rarity != 999 && items.at(bg).rarity != 999) {
						int b = getGemCount(fg) + rand() % 1;
						while (b > 0)
						{
							if (b >= 100)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									100, 0);
								b -= 100;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
								for (int i = 0; i < rand() % 4; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 50)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									50, 0);
								b -= 50;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
								for (int i = 0; i < rand() % 3; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 10)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									10, 0);
								b -= 10;
								for (int i = 0; i < rand() % 4; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 5)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									5, 0);
								b -= 5;
								for (int i = 0; i < rand() % 2; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 1)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									1, 0);
								b -= 1;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
						}
					}
					return;
				}
			}
		}
		if ((duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() - world->items[x + (y * world->width)].breakTime >= 4000)
		{
			world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			world->items[x + (y * world->width)].breakLevel = 4; // TODO


		}
		else
			if (y < world->height && world->items[x + (y * world->width)].breakLevel + 4 >= brak.breakHits * 4) { // TODO

				data.packetType = 0x3;// 0xC; // 0xF // World::HandlePacketTileChangeRequest
				data.netID = causedBy;
				data.plantingTree = 18;
				int brokentile = world->items[x + (y * world->width)].foreground;
				
				if (((PlayerInfo*)(peer->data))->currentWorld != "EXIT") {
					if (getItemDef(brokentile).blockType == BlockTypes::LOCK && brokentile != 4994 && brokentile != 202 && brokentile != 204 && brokentile != 206) {



						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;
							if (isHere(peer, currentPeer)) {
								Player::OnConsoleMessage(currentPeer, "`w" + ((PlayerInfo*)(peer->data))->currentWorld + " `ohas had it's lock `oremoved.");
								world->owner = "";
								world->ownerID = 0;
								world->isPublic = false;
								world->ownerDisplayName = "";
								world->accessed.clear();

							}
						}
					}
				}
				//Player::SendTileAnimation(peer, x, y, causedBy, world->items[x + (y*world->width)].foreground);



				world->items[x + (y * world->width)].breakLevel = 0;
				world->items[x + (y * world->width)].intdata = 0;
				if (brokentile != 0)
				{
					if (pinfo->lqueststep == 2 && pinfo->lquestprogress < 1000) {

						pinfo->lquestprogress++;

					}
					else if (pinfo->lqueststep == 2 && pinfo->lquestprogress == 1000 && pinfo->didAlready == false) {
						pinfo->didAlready = true;
						Player::OnTalkBubble(peer, pinfo->netID, "`9Legendary Quest step complete! I'm off to see a Wizard!", false);


					}


					if (brokentile == 410 || brokentile == 1832 || brokentile == 1770) {
						int x1 = 0;
						int y1 = 0;
						for (int i = 0; i < world->width * world->height; i++)
						{
							if (world->items[i].foreground == 6) {
								x1 = (i % world->width) * 32;
								y1 = (i / world->width) * 32;
								//world->items[i].foreground = 8;
							}
						}
						ENetPeer* currentPeer;

						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;
							if (isHere(peer, currentPeer)) {
								if (((PlayerInfo*)(currentPeer->data))->respawnX != 0 && ((PlayerInfo*)(currentPeer->data))->respawnY != 0) {
									if (((PlayerInfo*)(currentPeer->data))->respawnX / 32 == x && ((PlayerInfo*)(currentPeer->data))->respawnY / 32 == y) {
										((PlayerInfo*)(currentPeer->data))->respawnX = x1;
										((PlayerInfo*)(currentPeer->data))->respawnY = y1;
										Player::SetRespawnPos(currentPeer, x1 / 32, (world->width * (y1 / 32)), ((PlayerInfo*)(currentPeer->data))->netID);
									}
								}
							}
						}
					}

					world->items[x + (y * world->width)].foreground = 0;
					world->items[x + (y * world->width)].activated = false;
					world->items[x + (y * world->width)].flipped = false;
					if (items.at(fg).rarity != 999 && items.at(bg).rarity != 999) {
						int b = getGemCount(fg) + rand() % 1;
						while (b > 0)
						{
							if (b >= 100)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									100, 0);
								b -= 100;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
								for (int i = 0; i < rand() % 4; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 50)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									50, 0);
								b -= 50;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
								for (int i = 0; i < rand() % 3; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 10)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									10, 0);
								b -= 10;
								for (int i = 0; i < rand() % 4; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 5)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									5, 0);
								b -= 5;
								for (int i = 0; i < rand() % 2; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 1)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									1, 0);
								b -= 1;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
						}
					}




					if (brokentile == 6) {
						int x1 = 0;
						int y1 = 0;
						for (int i = 0; i < world->width * world->height; i++)
						{
							if (world->items[i].foreground == 6) {
								x1 = (i % world->width) * 32;
								y1 = (i / world->width) * 32;
								//world->items[i].foreground = 8;
							}
						}
						ENetPeer* currentPeer;

						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;
							if (isHere(peer, currentPeer)) {
								if (((PlayerInfo*)(currentPeer->data))->respawnX != 0 && ((PlayerInfo*)(currentPeer->data))->respawnY != 0) {
									if (((PlayerInfo*)(currentPeer->data))->respawnX / 32 == x && ((PlayerInfo*)(currentPeer->data))->respawnY / 32 == y) {
										((PlayerInfo*)(currentPeer->data))->respawnX = x1;
										((PlayerInfo*)(currentPeer->data))->respawnY = y1;
										Player::SetRespawnPos(currentPeer, x1 / 32, (world->width * (y1 / 32)), ((PlayerInfo*)(currentPeer->data))->netID);
									}
								}
							}
						}
					}
				}
				else {
					data.plantingTree = 18;
					world->items[x + (y * world->width)].background = 0;
					if (items.at(fg).rarity != 999 && items.at(bg).rarity != 999) {
						int b = getGemCount(bg) + rand() % 1;
						while (b > 0)
						{
							if (b >= 100)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									100, 0);
								b -= 100;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
								for (int i = 0; i < rand() % 4; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 50)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									50, 0);
								b -= 50;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
								for (int i = 0; i < rand() % 3; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 10)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									10, 0);
								b -= 10;
								for (int i = 0; i < rand() % 4; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 5)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									5, 0);
								b -= 5;
								for (int i = 0; i < rand() % 2; i++) dropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
							if (b >= 1)
							{
								dropItem(
									peer, -1,
									x * 32 + (rand() % 16),
									y * 32 + (rand() % 16),
									112,
									1, 0);
								b -= 1;
								for (int i = 0; i < rand() % 1; i++) dropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
								continue;
							}
						}
					}
				}
			}
			else
				if (y < world->height)
				{
					world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					world->items[x + (y * world->width)].breakLevel += 4; // TODO
					if (world->items[x + (y * world->width)].foreground == 758)
						sendRoulete(peer, x, y);
				}

	}
	else {
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
		{
			if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == tile)
			{
				if ((unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount > 1)
				{
					((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount--;
				}
				else {
					((PlayerInfo*)(peer->data))->inventory.items.erase(((PlayerInfo*)(peer->data))->inventory.items.begin() + i);

				}
			}
		}
		if (def.blockType == BlockTypes::BACKGROUND)
		{
			world->items[x + (y * world->width)].background = tile;
		}
		else {
			world->items[x + (y * world->width)].foreground = tile;



		}
		if (isMonitor) {
			//	sendHMonitor(peer, x, y, "homo", true);
			world->items[x + (y * world->width)].hmonitor_owner = pinfo->backupName;
		}
		if (isLock) {

			int netID = ((PlayerInfo*)(peer->data))->netID;
			world->owner = ((PlayerInfo*)(peer->data))->rawName;
			world->ownerDisplayName = ((PlayerInfo*)(peer->data))->displayName;
			world->ownerID = ((PlayerInfo*)(peer->data))->userID;
			world->isPublic = false;



			ENetPeer* currentPeer;

			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer)) {
					Player::OnConsoleMessage(currentPeer, "`5[`w" + world->name + " `ohas been `$World Locked `oby `o" + ((PlayerInfo*)(peer->data))->displayName + "`5]``");
					PlayAudioSelf(currentPeer, "audio/use_lock.wav");
				}
			}


		}

		world->items[x + (y * world->width)].breakLevel = 0;
	}







	ENetPeer* currentPeer;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			BYTE* raw = packPlayerMoving(&data);
			raw[2] = dicenr;
			raw[3] = dicenr;
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
		//cout << "Tile update at: " << data2->punchX << "x" << data2->punchY << endl;
	}
	if (getItemDef(tile).properties == Property_MultiFacing) {
		if (((PlayerInfo*)(peer->data))->isRotatedLeft) {

			world->items[x + (y * world->width)].flipped = true;
			UpdateBlockState(peer, x, y, true, world);

		}
	}
	if (isMonitor) {
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer))
			{
				sendHMonitor(currentPeer, x, y, world->items[x + (y * world->width)].hmonitor_owner, true);
			}
		}
	}
	if (isTree) {
		int numb = (rand() % 4) + 1;
		UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, numb, 1000, true, 0);
	}
	if (isLock) {
		int userIDE = ((PlayerInfo*)(peer->data))->userID;

		if (tile != 202 && tile != 204 && tile != 206 && tile != 4994) {

			ApplyLockPacket(peer, x, y, tile, 0, userIDE);
		}
		else {
			ApplyLockPacket(peer, x, y, tile, 35, userIDE);
		}
	}

}

void sendPlayerLeaveForNuke(ENetPeer* peer, PlayerInfo* player)
{
	ENetPeer* currentPeer;
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(player->netID) + "\n")); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
	GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5<`w" + player->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(player->currentWorld) - 1) + "`` others here>``"));
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			{

				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet);

			}
			{

				if (((PlayerInfo*)(peer->data))->adminLevel < 1)
				{
					GamePacket p4 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(player->currentWorld) - 1) + "`` `5others here>```w"));
					ENetPacket* packet4 = enet_packet_create(p4.data,
						p4.len,
						ENET_PACKET_FLAG_RELIABLE);

					enet_peer_send(currentPeer, 0, packet4);
					delete p4.data;

					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);

					enet_peer_send(currentPeer, 0, packet2);
				}
			}
		}
	}


	delete p.data;
	delete p2.data;
	return;
}




void sendPlayerLeave(ENetPeer* peer, PlayerInfo* player)
{

	ENetPeer* currentPeer;
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(player->netID) + "\n")); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
	GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5<`w" + player->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(player->currentWorld) - 1) + "`` others here>``"));
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			{

				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet);

			}
			{

				if (((PlayerInfo*)(peer->data))->isInvisible == false)
				{
					GamePacket p4 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(player->currentWorld) - 1) + "`` `5others here>```w"));
					ENetPacket* packet4 = enet_packet_create(p4.data,
						p4.len,
						ENET_PACKET_FLAG_RELIABLE);

					enet_peer_send(currentPeer, 0, packet4);
					delete p4.data;

					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);

					enet_peer_send(currentPeer, 0, packet2);
				}
			}
		}
	}


	delete p.data;
	delete p2.data;
	return;
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

void sendChatMessage(ENetPeer* peer, int netID, string message)
{
	if (message.length() >= 120) {
		return;
	}


	else {

	defaultti:
		for (char c : message)

			if (c < 0x18 || std::all_of(message.begin(), message.end(), isspace))
			{
				return;
			}
		ENetPeer* currentPeer;
		string name = "";
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (((PlayerInfo*)(currentPeer->data))->netID == netID)
				name = ((PlayerInfo*)(currentPeer->data))->displayName;

		}
		GamePacket p;
		GamePacket p2;
		if (((PlayerInfo*)(peer->data))->adminLevel == 2) {

			p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[W]_ `o<`w" + name + "`o> `5" + message));
			p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`5" + message), 0));

		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 1) {

			p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[W]_ `o<`w" + name + "`o> `^" + message));
			p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`^" + message), 0));
		}
		else {
			p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[W]_ `o<`w" + name + "`o> `6" + message));
			p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), message), 0));
		}
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer))
			{

				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);

				enet_peer_send(currentPeer, 0, packet);

				//enet_host_flush(server);

				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);

				//enet_host_flush(server);
			}
		}
		delete p.data;
		delete p2.data;
	}
}

void sendWho(ENetPeer* peer)
{
	ENetPeer* currentPeer;
	string name = "";
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			if (((PlayerInfo*)(currentPeer->data))->canWalkInBlocks)
				continue;
			GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(currentPeer->data))->netID), ((PlayerInfo*)(currentPeer->data))->displayName), 1));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);

			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			//enet_host_flush(server);
		}
	}
}
int GetPlayerCountServer()
{
	int count = 0;
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		count++;
	}
	return count;
}

void sendWorld(ENetPeer* peer, WorldInfo* worldInfo)
{
	cout << "Sending player to a world" << endl;
	if (!worldInfo) return;

	int zero = 0;
	((PlayerInfo*)(peer->data))->droppeditemcount = worldInfo->droppedCount;
#ifdef TOTAL_LOG
	cout << "Entering a world..." << endl;
#endif
	((PlayerInfo*)(peer->data))->joinClothesUpdated = false;
	string asdf = "0400000004A7379237BB2509E8E0EC04F8720B050000000000000000FBBB0000010000007D920100FDFDFDFD04000000040000000000000000000000070000000000"; // 0400000004A7379237BB2509E8E0EC04F8720B050000000000000000FBBB0000010000007D920100FDFDFDFD04000000040000000000000000000000080000000000000000000000000000000000000000000000000000000000000048133A0500000000BEBB0000070000000000
	string worldName = worldInfo->name;
	int xSize = worldInfo->width;
	int ySize = worldInfo->height;
	int square = xSize * ySize;
	__int16 nameLen = (__int16)worldName.length();
	int payloadLen = asdf.length() / 2;
	int dataLen = payloadLen + 2 + nameLen + 12 + (square * 8) + 4 + 100;
	int offsetData = dataLen - 100;
	int allocMem = payloadLen + 2 + nameLen + 12 + (square * 8) + 4 + 16000 + 100 + (worldInfo->droppedItems.size() * 20);
	BYTE* data = new BYTE[allocMem];
	memset(data, 0, allocMem);
	for (int i = 0; i < asdf.length(); i += 2)
	{
		char x = ch2n(asdf[i]);
		x = x << 4;
		x += ch2n(asdf[i + 1]);
		memcpy(data + (i / 2), &x, 1);
	}

	__int16 item = 0;
	int smth = 0;
	for (int i = 0; i < square * 8; i += 4) memcpy(data + payloadLen + i + 14 + nameLen, &zero, 4);
	for (int i = 0; i < square * 8; i += 8) memcpy(data + payloadLen + i + 14 + nameLen, &item, 2);
	memcpy(data + payloadLen, &nameLen, 2);
	memcpy(data + payloadLen + 2, worldName.c_str(), nameLen);
	memcpy(data + payloadLen + 2 + nameLen, &xSize, 4);
	memcpy(data + payloadLen + 6 + nameLen, &ySize, 4);
	memcpy(data + payloadLen + 10 + nameLen, &square, 4);
	BYTE* blockPtr = data + payloadLen + 14 + nameLen;

	int sizeofblockstruct = 8;


	for (int i = 0; i < square; i++) {

		int tile = worldInfo->items[i].foreground;
		int backg = worldInfo->items[i].background;
		sizeofblockstruct = 8;

		if (tile == 6) {
			int type = 0x00000000;

			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &tile, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 1;
			memcpy(blockPtr + 8, &btype, 1);

			string doorText = "EXIT";
			const char* doorTextChars = doorText.c_str();
			short length = (short)doorText.size();
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, doorTextChars, length);
			sizeofblockstruct += 4 + length;
			dataLen += 4 + length; // it's already 8.

		}

		else if (getItemDef(tile).blockType == BlockTypes::SIGN || tile == 1420 || tile == 6124) {
			int type = 0x00000000;

			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 2;
			memcpy(blockPtr + 8, &btype, 1);
			string signText = worldInfo->items[i].sign;
			const char* signTextChars = signText.c_str();
			short length = (short)signText.size();
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, signTextChars, length);
			int minus1 = -1;
			memcpy(blockPtr + 11 + length, &minus1, 4);
			sizeofblockstruct += 3 + length + 4;
			dataLen += 3 + length + 4; // it's already 8.
		}
		else if (tile == 2946) {
			int type = 0x00000000;

			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 0x17;
			memcpy(blockPtr + 8, &btype, 1);
			int item = worldInfo->items[i].intdata;
			memcpy(blockPtr + 9, &item, 4);
			sizeofblockstruct += 5;
			dataLen += 5;

		}

		else if (tile == 5000) {
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			int type = 0x00000000;

			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 0x28;
			memcpy(blockPtr + 8, &btype, 1);
			int item = 0;
			int gravity = 0;
			short flags = 0;
			item = worldInfo->bgID;
			memcpy(blockPtr + 9, &item, 4);
			sizeofblockstruct += 5;
			dataLen += 5;
		}
		else if (getItemDef(tile).blockType == BlockTypes::DOOR || getItemDef(tile).blockType == BlockTypes::PORTAL) {
			int type = 0x00000000;

			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 1;
			memcpy(blockPtr + 8, &btype, 1);

			string doorText = worldInfo->items[i].sign;
			const char* doorTextChars = doorText.c_str();
			short length = (short)doorText.size();
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, doorTextChars, length);
			int minus1 = -1;
			memcpy(blockPtr + 11 + length, &minus1, 4);
			sizeofblockstruct += 4 + length;
			dataLen += 4 + length; // it's already 8.
		}

		else if (getItemDef(tile).blockType == BlockTypes::LOCK && tile != 4994 && tile != 202 && tile != 204 && tile != 206)
		{

			if (worldInfo->items[i].foreground == 5814)
			{
				// Special Case #1 - Guild Lock
				int type = 0x00000000;

				// type 1 = locked
				if (worldInfo->items[i].activated)
					type |= 0x00200000;
				if (worldInfo->items[i].flipped)
					type |= 0x00400000;
				if (worldInfo->items[i].water)
					type |= 0x04000000;
				if (worldInfo->items[i].glue)
					type |= 0x08000000;
				if (worldInfo->items[i].fire)
					type |= 0x10000000;
				if (worldInfo->items[i].red)
					type |= 0x20000000;
				if (worldInfo->items[i].green)
					type |= 0x40000000;
				if (worldInfo->items[i].blue)
					type |= 0x80000000;
				int adminCount = 1;
				int ownerID = worldInfo->ownerID;// ((PlayerInfo*)peer->data)->userID;
				// int admins[...]
				int szExtra = 10 + adminCount * 4 + 16;
				memset(blockPtr + 8, 0, szExtra);
				BYTE btype = 0x3;
				BYTE o = 0x1;
				memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
				memcpy(blockPtr + 4, &type, 4);
				memcpy(blockPtr + 8, &btype, 1);
				memcpy(blockPtr + 8 + 2, &ownerID, 4);
				memcpy(blockPtr + 8 + 6, &adminCount, 1);
				memcpy(blockPtr + 8 + 10, &o, 1);
				short id1 = 14;
				short id2 = 1;
				memcpy(blockPtr + 8 + 12, &id1, 2);
				memcpy(blockPtr + 8 + 16, &id2, 2);
				sizeofblockstruct += szExtra;
				dataLen += szExtra;
			}
			else
			{
				int type = 0x00000000;

				// type 1 = locked
				if (worldInfo->items[i].activated)
					type |= 0x00200000;
				if (worldInfo->items[i].flipped)
					type |= 0x00400000;
				if (worldInfo->items[i].water)
					type |= 0x04000000;
				if (worldInfo->items[i].glue)
					type |= 0x08000000;
				if (worldInfo->items[i].fire)
					type |= 0x10000000;
				if (worldInfo->items[i].red)
					type |= 0x20000000;
				if (worldInfo->items[i].green)
					type |= 0x40000000;
				if (worldInfo->items[i].blue)
					type |= 0x80000000;
				int adminCount = 1;
				int ownerID = worldInfo->ownerID;// ((PlayerInfo*)peer->data)->userID;
				// int admins[...]
				int szExtra = 10 + adminCount * 4;
				memset(blockPtr + 8, 0, szExtra);
				BYTE btype = 0x3;
				BYTE o = 0x1;
				memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
				memcpy(blockPtr + 4, &type, 4);
				memcpy(blockPtr + 8, &btype, 1);
				memcpy(blockPtr + 8 + 2, &ownerID, 4);
				memcpy(blockPtr + 8 + 6, &adminCount, 1);
				memcpy(blockPtr + 8 + 10, &o, 1);
				sizeofblockstruct += szExtra;
				dataLen += szExtra;
			}

		}
		else if (worldInfo->items[i].foreground == 1008)
		{
			int type = 0x00000000;

			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			BYTE btype = 9;
			int timeIntoGrowth = 13665;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			memcpy(blockPtr + 8, &btype, 1);
			memcpy(blockPtr + 9, &timeIntoGrowth, 4);
			sizeofblockstruct += 5;
			dataLen += 5;
		}

		else if (worldInfo->items[i].foreground == 2978)
		{
			int type = 0x00000000;

			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;



			int count = 0;
			int vend_id = 242;

			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 2, &worldInfo->items[i].background, 2);
			memcpy(blockPtr + 4, &type, 4);
			blockPtr[8] = 0x18;
			memcpy(blockPtr + 9, &vend_id, 4);
			memcpy(blockPtr + 13, &count, 4);
			sizeofblockstruct += 9;
			dataLen += 9;
		}



		else if ((worldInfo->items[i].foreground == 0) || (worldInfo->items[i].foreground == 2) || (worldInfo->items[i].foreground == 8) || (worldInfo->items[i].foreground == 100) || (worldInfo->items[i].foreground == 4) || (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::BACKGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEST || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SWITCH_BLOCK))
		{

			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			int type = 0;
			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00400000;
			if (worldInfo->items[i].flipped)
				type |= 0x00200000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;

			memcpy(blockPtr + 4, &type, 4);

			// int type = 0x04000000; = water
			// int type = 0x08000000 = glue
			// int type = 0x10000000; = fire
			// int type = 0x20000000; = red color
			// int type = 0x40000000; = green color
			// int type = 0x80000000; = blue color



			/*if (worldInfo->items[i].foreground % 2)
			{
				blockPtr += 6;
			}*/
		}
		else
		{
			memcpy(blockPtr, &zero, 2);
		}
		memcpy(blockPtr + 2, &worldInfo->items[i].background, 2);
		blockPtr += sizeofblockstruct;

	}

	dataLen += 8;
	int itemcount = worldInfo->droppedItems.size();
	int itemuid = worldInfo->droppedCount;
	memcpy(blockPtr, &itemcount, 4);
	memcpy(blockPtr + 4, &itemuid, 4);
	blockPtr += 8;

	int iteminfosize = 16;
	int itemSize = itemcount * iteminfosize;
	for (int i = 0; i < itemcount; i++)
	{
		int item = worldInfo->droppedItems[i].id;
		int count = worldInfo->droppedItems[i].count;
		int uid = worldInfo->droppedItems[i].uid + 1;
		float x = (float)worldInfo->droppedItems[i].x;
		float y = (float)worldInfo->droppedItems[i].y;
		memcpy(blockPtr, &item, 2);
		memcpy(blockPtr + 2, &x, 4);
		memcpy(blockPtr + 6, &y, 4);
		memcpy(blockPtr + 10, &count, 2);
		memcpy(blockPtr + 12, &uid, 4);
		blockPtr += iteminfosize;
		dataLen += iteminfosize;
	}
	dataLen += 100;
	blockPtr += 4;
	memcpy(blockPtr, &worldInfo->weather, 4);
	blockPtr += 4;


	offsetData = dataLen - 100;

	BYTE* data2 = new BYTE[101];
	memset(data2, 0, 101);
	memcpy(data2 + 0, &zero, 4);
	int weather = worldInfo->weather;
	memcpy(data2 + 4, &weather, 4);


	//cout << dataLen << " <- dataLen allocMem -> " << allocMem << endl;
	memcpy(data + dataLen - 4, &smth, 4);
	ENetPacket* packet2 = enet_packet_create(data,
		dataLen,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	//enet_host_flush(server);
	for (int i = 0; i < square; i++) {
		if ((worldInfo->items[i].foreground == 0) || (worldInfo->items[i].foreground == 2978) || (getItemDef(worldInfo->items[i].foreground).blockType) == BlockTypes::LOCK || (worldInfo->items[i].foreground == 5638) || (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::BACKGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEST || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SWITCH_BLOCK || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND) || (worldInfo->items[i].foreground == 1008) || (worldInfo->items[i].foreground == 5000) || (getItemDef(worldInfo->items[i].foreground).blockType) == BlockTypes::SIGN || (getItemDef(worldInfo->items[i].foreground).blockType) == BlockTypes::DOOR || (getItemDef(worldInfo->items[i].foreground).blockType) == BlockTypes::PORTAL || worldInfo->items[i].foreground == 1420 || worldInfo->items[i].foreground == 6214 || (worldInfo->items[i].foreground == 3832) || (worldInfo->items[i].foreground == 2946) || (worldInfo->items[i].foreground == 6) || (worldInfo->items[i].foreground == 242) || (worldInfo->items[i].foreground == 1796) || (worldInfo->items[i].foreground == 4) || (worldInfo->items[i].foreground == 2) || (worldInfo->items[i].foreground == 8) || (worldInfo->items[i].foreground == 100))
			; // nothing
		else if (worldInfo->items[i].foreground == 3528) {
			int xx = i % xSize, yy = i / xSize;
			SendCanvasData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, xx, yy, worldInfo->items[i].intdata, GetItemDef(worldInfo->items[i].intdata).name);
		}
		else
		{
			PlayerMoving data;
			//data.packetType = 0x14;
			data.packetType = 0x3;
			/*   else if (IsGivingTree(worldInfo->blocks[i].foreground))
	{
		int adminCount = 0;
		int ownerID = worldInfo->owner;// ((PlayerInfo*)peer->data)->userID;
		// int admins[...]
		int szExtra = 7;
		if (blockPtr) memset(blockPtr + 8, 0, szExtra);
		BYTE btype = 0x1C;
		BYTE o = 0x1;
		int b = GetTimeIntoGrowth(worldInfo, i);
		byte c = worldInfo->blocks[i].intdata, a = 0;
		if (blockPtr) memcpy(blockPtr, &worldInfo->blocks[i].foreground, 2);
		if (blockPtr) memcpy(blockPtr + 4, &type, 4);
		if (blockPtr) memcpy(blockPtr + 8, &btype, 1);
		if (blockPtr) memcpy(blockPtr + 8 + 1, &a, 1);
		if (blockPtr) memcpy(blockPtr + 8 + 2, &b, 4);
		if (blockPtr) memcpy(blockPtr + 8 + 6, &c, 1);
		sizeofblockstruct += szExtra;
		dataLen += szExtra;
	}*/
	//data.characterState = 0x924; // animation
			data.characterState = 0x0; // animation
			data.x = i % worldInfo->width;
			data.y = i / worldInfo->height;
			data.punchX = i % worldInfo->width;
			data.punchY = i / worldInfo->width;
			data.XSpeed = 0;
			data.YSpeed = 0;
			data.netID = -1;
			data.plantingTree = worldInfo->items[i].foreground;
			SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);

			//int x = i % xSize, y = i / xSize;
			//UpdateVisualsForBlock(peer, false, x, y, worldInfo);
		}
	}

	string wname = worldInfo->name;
	((PlayerInfo*)(peer->data))->currentWorld = wname;

	Player::PlayAudio(peer, "audio/door_open.wav", 0);

	delete data;
}

void joinWorld(ENetPeer* peer, string act) { //TODO DOORS
	if (configPort == 17093) {
		if (((PlayerInfo*)(peer->data))->isIn == false) return;
		//enet_peer_timeout(peer, 0, 0, 0);	
		return;
	}


	if (((PlayerInfo*)(peer->data))->isBot == true) {
		enet_peer_disconnect_now(peer, 0);
	}
	try {
		if (act.length() > 24) {
			sendConsoleMsg(peer, "`4Sorry, but world names with more than 24 characters are not allowed!");
			((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
			GamePacket p2 = packetEnd(appendIntx(appendString(createPacket(), "OnFailedToEnterWorld"), 1));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
		else {
			using namespace std::chrono;
			if (((PlayerInfo*)(peer->data))->lastJoinReq + 512 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
			{
				((PlayerInfo*)(peer->data))->lastJoinReq = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			}
			else {

				Player::OnFailedToEnterWorld(peer);
				return;
			}
			string upsd = act;
			std::transform(upsd.begin(), upsd.end(), upsd.begin(), ::toupper);



			WorldInfo info = worldDB.get(act);



			if (info.isNuked) {
				if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) == 0) {
					Player::OnConsoleMessage(peer, "`oThis world is inaccessible.``");
					Player::OnFailedToEnterWorld(peer);
					return;
				}
			}
			/*if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) < 1) {
				bool banned = false;
				for (int i = 0; i < info.wbans.size(); i++) {
					if (info.wbans.at(i).userID == ((PlayerInfo*)(peer->data))->userID)
					{
						if (info.wbans.at(i).bannedAt > GetCurrentTimeInternalSeconds()) {
							banned = true;
							break;
						}
						else {
							info.wbans.erase(info.wbans.begin() + i);
						}
						break;
					}
				}
				if (banned) {
					Player::OnFailedToEnterWorld(peer);
					Player::OnConsoleMessage(peer, "`oYou are still `4banned `ofrom this `wworld`o, wait until the ban wears off after an hour!``");
					return;
				}
			}*/
			sendWorld(peer, &info);



			//`2" + ((PlayerInfo*)(peer->data))->displayName


			int x = 0;
			int y = 0;

			for (int j = 0; j < info.width * info.height; j++)
			{
				if (info.items[j].foreground == 6) {
					x = (j % info.width) * 32;
					y = (j / info.width) * 32;
				}
			}
			((PlayerInfo*)(peer->data))->respawnX = x;
			((PlayerInfo*)(peer->data))->respawnY = y;
			int userIDE = ((PlayerInfo*)(peer->data))->userID;
			
			if (info.isPublic) {
				Player::OnSpawn(peer, cId, 1, x, y,
					((PlayerInfo*)(peer->data))->displayName, ((PlayerInfo*)(peer->data))->country, ((PlayerInfo*)(peer->data))->isInvisible, ((PlayerInfo*)(peer->data))->mstate,
					((PlayerInfo*)(peer->data))->smstate);
			}
			else {
				Player::OnSpawn(peer, cId, userIDE, x, y,
					((PlayerInfo*)(peer->data))->displayName, ((PlayerInfo*)(peer->data))->country, ((PlayerInfo*)(peer->data))->isInvisible, ((PlayerInfo*)(peer->data))->mstate,
					((PlayerInfo*)(peer->data))->smstate);
			}
			((PlayerInfo*)(peer->data))->netID = cId;
			onPeerConnect(peer);
			cId++;

		


			if (((PlayerInfo*)(peer->data))->isInvisible == false) {
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer)) {
						Player::OnConsoleMessage(currentPeer, "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + " `5entered, `w" + std::to_string(getPlayersCountInWorld(((PlayerInfo*)(peer->data))->currentWorld) - 1) + "`` others here>``");
						Player::OnTalkBubble(currentPeer, ((PlayerInfo*)(peer->data))->netID, "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + " `5entered, `w" + std::to_string(getPlayersCountInWorld(((PlayerInfo*)(peer->data))->currentWorld) - 1) + "`` others here>``", false);
					}
				}
			}
			sendConsoleMsg(peer, "`oWorld `w" + info.name + "`o entered. There are `w" + to_string(getPlayersCountInWorld(info.name)) + "`o other people here, `w" + to_string(GetPlayerCountServer()) + " `oonline.");
			if (info.owner != "") {
				if (info.owner == ((PlayerInfo*)(peer->data))->rawName || isWorldAdmin2(peer, info) || adminLevel(peer) > 1) {
					string test = "`5[`w" + info.name + "`$ World Locked`o by " + info.ownerDisplayName + " `o(`2ACCESS GRANTED`o)`5]";
					sendConsoleMsg(peer, test);
				}
				else
				{
					string test = "`5[`w" + info.name + "`$ World Locked`o by " + info.ownerDisplayName + "`5]";
					sendConsoleMsg(peer, test);
				}
				
			}
		}
	}
	catch (int e) {
		if (e == 1) {
			((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
			Player::OnFailedToEnterWorld(peer);
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "You have exited the world."));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
			//enet_host_flush(server);
		}
		else if (e == 2) {
			((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
			Player::OnFailedToEnterWorld(peer);
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "You have entered bad characters in the world name!"));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
			//enet_host_flush(server);
		}
		else if (e == 3) {
			((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
			Player::OnFailedToEnterWorld(peer);
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "Exit from what? Click back if you're done playing."));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
			//enet_host_flush(server);
		}
		else {
			((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
			Player::OnFailedToEnterWorld(peer);
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "I know this menu is magical and all, but you can't visit this world!"));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
			//enet_host_flush(server);
		}
	}
}


void sendAction(ENetPeer* peer, int netID, string action)
{
	ENetPeer* currentPeer;
	string name = "";
	GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnAction"), action));
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {

			memcpy(p2.data + 8, &netID, 4);
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);

			enet_peer_send(currentPeer, 0, packet2);

			//enet_host_flush(server);
		}
	}
	delete p2.data;
}

bool HasInventoryFull(ENetPeer* peer)
{
	PlayerInventory* inventory = &((PlayerInfo*)(peer->data))->inventory;
	return inventory->items.size() > (uint32_t)inventory->inventorySize;
}

bool HasInventoryEmpty(ENetPeer* peer)
{
	PlayerInventory* inventory = &((PlayerInfo*)(peer->data))->inventory;
	return inventory->items.size() == 0;
}


void SendTake(ENetPeer* peer, int netID, int x, int y, int item)
{
	ENetPeer* currentPeer;
	string name = "";
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = item;

			BYTE* raw = packPlayerMoving(&data);

			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_EVENT_TYPE_RECEIVE);
		}
	}
}

void sendPuncheffect(ENetPeer* peer, int punch) {
	//return; // TODO
	PlayerInfo* info = ((PlayerInfo*)(peer->data));
	int netID = info->netID;
	ENetPeer* currentPeer;
	int state = getState(info);

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {


			PlayerMoving data;
			data.packetType = 0x14;
			data.characterState = 0; // animation
			data.x = 1000;
			data.y = 100;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 600;
			data.netID = netID;
			data.plantingTree = state;
			BYTE* raw = packPlayerMoving(&data);
			int var = punch; // punch effect
			memcpy(raw + 1, &var, 3);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);


		}

	}
	// TODO 
}
void sendState2(ENetPeer* peer, int state) {
	PlayerInfo* info = ((PlayerInfo*)(peer->data));
	int netID = info->netID;
	ENetPeer* currentPeer;
	//int state = getState(info);
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			float water = 125.0f;
			data.packetType = 0x14;
			data.characterState = 0; // animation
			data.x = 1000;
			if (((PlayerInfo*)(peer->data))->cloth_hand == 366) {
				data.y = -400; // - is hbow
			}
			else {
				data.y = 400;
			}
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 1850;
			data.netID = netID;
			data.plantingTree = state;
			BYTE* raw = packPlayerMoving(&data);
			int var = 0x818100; // placing and breking 0x808040 
			memcpy(raw + 1, &var, 3);
			memcpy(raw + 16, &water, 4);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	// TODO
}




void sendWorldOffers(ENetPeer* peer)
{
	if (!((PlayerInfo*)(peer->data))->isIn) return;
	vector<WorldInfo> worlds = worldDB.getRandomWorlds();
	string worldOffers = "default|";
	if (worlds.size() > 0) {
		worldOffers += worlds[0].name;
	}

	worldOffers += "\nadd_button|Showing: `wWorlds``|_catselect_|0.6|3529161471|\n";
	for (int i = 0; i < worlds.size(); i++) {
		worldOffers += "add_floater|" + worlds[i].name + "|" + std::to_string(getPlayersCountInWorld(worlds[i].name)) + "|0.55|3529161471\n";
	}
	//GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnRequestWorldSelectMenu"), "default|GO FOR IT\nadd_button|Showing: `wFake Worlds``|_catselect_|0.6|3529161471|\nadd_floater|Subscribe|5|0.55|3529161471\nadd_floater|Growtopia|4|0.52|4278190335\nadd_floater|Noobs|150|0.49|3529161471\nadd_floater|...|3|0.49|3529161471\nadd_floater|`6:O :O :O``|2|0.46|3529161471\nadd_floater|SEEMS TO WORK|2|0.46|3529161471\nadd_floater|?????|1|0.43|3529161471\nadd_floater|KEKEKEKEK|13|0.7|3417414143\n"));
	//for (int i = 0; i < p.len; i++) cout << (int)*(p.data + i) << " ";
	GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnRequestWorldSelectMenu"), worldOffers));
	ENetPacket* packet3 = enet_packet_create(p3.data,
		p3.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete p3.data;
	//enet_host_flush(server);
	sendConsoleMsg(peer, "Where would you like to go? (`w" + std::to_string(GetPlayerCountServer()) + "`` online)");
}




//replaced X-to-close with a Ctrl+C exit
void exitHandler(int s) {
	saveAllWorlds();
	exit(0);

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

void loadConfig() {
	/*inside config.json:
	{
	"port": 17091,
	"cdn": "0098/CDNContent37/cache/"
	}
	*/


	std::ifstream ifs("config.json");
	if (ifs.is_open()) {
		json j;
		ifs >> j;
		ifs.close();
		try {
			configPort = j["port"].get<int>();
			//	configCDN = j["cdn"].get<string>();

			cout << "Config loaded." << endl;
		}
		catch (...) {
			cout << "Invalid config." << endl;
		}
	}
	else {
		cout << "Config not found." << endl;
	}
}
bool logs = true;
void commands()
{
	while (commands)
	{
		std::string input;
		std::cin >> input;


		if (input == "exit")
		{
			saveAllWorlds();
			exit(0);
		}
		else if (input == "save") {
			saveAllWorlds();
		}
		else if (input == "logs") {
			if (logs == true) {
				cout << "Logs has been disabled!" << endl;
				logs = false;
			}
			else {
				cout << "Logs has been enabled again!" << endl;
				logs = true;
			}
		}
		else if (input == "online")
		{
			string x;


			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;


				x.append(((PlayerInfo*)(currentPeer->data))->rawName + " (" + to_string(((PlayerInfo*)(currentPeer->data))->adminLevel) + ")" + " (" + ((PlayerInfo*)(currentPeer->data))->charIP + ")" + ", ");
			}
			x = x.substr(0, x.length() - 2);

			cout << "[Console] Peers connected (includes mods) [format: (rawname) (adminlevel) (IP)]: " << x << endl;

		}
		else if (input == "kickall")
		{
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;

				enet_peer_disconnect_later(currentPeer, 0);
				enet_peer_reset(currentPeer);
			}
			cout << "Kicked everyone out of server!" << endl;
		}
		else if (input == "clear" || input == "cls")
		{
			system("CLS");

		}
		else if (input == "help" || input == "?")
		{
			cout << "Operator commands: " << "help " << "kickall " << "save " << "reload" << "online " << "delete " << "maintenance " << "exit" << endl;
		}
		else {
			cout << "Unknown command, type /help to see list of valid commands." << endl;
		}
	}
}
string randomDuctTapeMessage(size_t length) {
	auto randchar = []() -> char
	{
		const char charset[] =
			"f"
			"m";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

void playerRespawn(ENetPeer* peer, bool isDeadByTile) {

	WorldInfo* world = getPlyersWorld(peer);
	int netID = ((PlayerInfo*)(peer->data))->netID;
	if (isDeadByTile == false) {
		Player::OnKilled(peer, ((PlayerInfo*)(peer->data))->netID);
	}
	GamePacket p2x = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 0));
	memcpy(p2x.data + 8, &netID, 4);
	int respawnTimeout = 2000;
	int deathFlag = 0x19;
	memcpy(p2x.data + 24, &respawnTimeout, 4);
	memcpy(p2x.data + 56, &deathFlag, 4);
	ENetPacket* packet2x = enet_packet_create(p2x.data,
		p2x.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2x);
	delete p2x.data;
	Player::OnSetFreezeState(peer, 2, netID);



	int x = 3040;
	int y = 736;
	if (((PlayerInfo*)(peer->data))->respawnPos == -1)
	{
		for (int i = 0; i < world->width * world->height; i++)
		{
			if (world->items[i].foreground == 6) {
				x = (i % world->width) * 32 + 8;
				y = (i / world->width) * 32;
			}
		}
	}
	else
	{
		x = (((PlayerInfo*)(peer->data))->respawnPos % world->width) * 32 + 8;
		y = (((PlayerInfo*)(peer->data))->respawnPos / world->width) * 32;
	}
	GamePacket p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
	memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	respawnTimeout = 2000;
	memcpy(p2.data + 24, &respawnTimeout, 4);
	memcpy(p2.data + 56, &deathFlag, 4);
	ENetPacket* packet2 = enet_packet_create(p2.data,
		p2.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete p2.data;
	GamePacket p2a = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), "audio/teleport.wav"));
	memcpy(p2a.data + 8, &netID, 4);
	respawnTimeout = 2000;
	memcpy(p2a.data + 24, &respawnTimeout, 4);
	memcpy(p2a.data + 56, &deathFlag, 4);
	ENetPacket* packet2a = enet_packet_create(p2a.data,
		p2a.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2a);
	delete p2a.data;
}
void autoSaveWorlds() {
	while (1) {
		Sleep(1100000);
		string text = "action|play_sfx\nfile|audio/beep.wav\ndelayMS|0\n";
		BYTE* data = new BYTE[5 + text.length()];
		BYTE zero = 0;
		int type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		ENetPacket* packet2 = enet_packet_create(data,
			5 + text.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet2);
		delete data;
		Sleep(5500);
		saveAllWorlds();
	}
}
int PlayerDB::playerLogin(ENetPeer* peer, string username, string password) {


	if (username.length() > 16) return -1;
	if (password.length() > 20) return -1;
	string uname = filterName(username);
	string passw = filterPass(password);	if (uname == "" || passw == "") return -1;
	int qstate = 0;
	MYSQL_ROW row;
	string passcheck = "";
	string uidcheck;
	string gemz;


	int uid;

	int  ances = 0;
	string boughtances;
	int  hair = 0;
	int  eye = 0;
	int  mask = 0;
	int  neck = 0;
	int face = 0;
	int  shirt = 0;
	int  back = 0;
	int  pant = 0;
	int shoe = 0;

	int lstep = 0;
	int lprogress = 0;
	int ltype = 0;

	int hand = 0;
	string ghost;
	string bantime = "-1";
	string bandate = "-1";

	int  invis;
	int  skin = 0;
	int xp = 0;
	string wls;
	int  level = 0;
	string ban;
	int gem = 0;
	int skColor = 0;
	int admin2 = 0;

	string displayname;
	string usercheck;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, ip, user, pass, database, 0, NULL, 0);

	if (conn == NULL) {

		return -1;

	}

	if (conn != NULL) {
		stringstream ss; // creating string stream to load in query
		ss << "SELECT * FROM players WHERE username = '" + uname + "' AND password = '" + passw + "'";
		if (!ss.fail()) {
			string query = ss.str();
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
		}
		if (qstate == 0) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				usercheck = row[0];
				passcheck = row[1];
				gem = atoi(row[2]);
				displayname = row[3];
				admin2 = atoi(row[4]);
				uid = atoi(row[5]);
				xp = atoi(row[6]);
				level = atoi(row[7]);
				hair = atoi(row[8]);
				shirt = atoi(row[9]);
				skin = atoi(row[10]);
				hand = atoi(row[11]);
				mask = atoi(row[12]);
				back = atoi(row[13]);
				neck = atoi(row[14]);
				face = atoi(row[15]);
				ances = atoi(row[16]);
				pant = atoi(row[17]);
				shoe = atoi(row[18]);
				bandate = row[19];
				ban = row[20];
				bantime = row[21];
				lstep = atoi(row[22]);
				lprogress = atoi(row[23]);
				ltype = atoi(row[24]);



			}

			mysql_close(conn);
			if (usercheck == "") {


				return -1;
			}
			int ban2 = atoi(ban.c_str());
			if (ban2 == -1) {
				string who = displayname;

				string values = "`4Sorry, this account (`5" + who + "`4) has been suspended. Contact `5" + discord + "`4 if you have any questions.";

				BlockLoginNoUrl(peer, values);

			}
			else if (ban2 != 0) {



				long long a = 0;
				a = stoll(bandate);
				a += stoll(bantime);
				//	cout << "ban should expire at " << a << ", current time is " << GetCurrentTimeInternalsSeconds() << endl;
				if (a <= GetCurrentTimeInternalSeconds())
				{



					GamePacket p1 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oBan mod removed`$(Be good now!)"));
					ENetPacket* packet1 = enet_packet_create(p1.data,
						p1.len,
						ENET_PACKET_FLAG_RELIABLE);

					enet_peer_send(peer, 0, packet1);
					delete p1.data;
					int qstate = 0;
					conn = mysql_init(0);
					conn = mysql_real_connect(conn, ip, user, pass, database, 0, NULL, 0);
					if (conn == NULL) {
						return -1;
					}
					if (conn != NULL) {
						stringstream ss;

						ss << "UPDATE players SET ban = '0', bannedat = '-1', bantime = '-1' WHERE username = '" + filterName(username) + "'";
						string query = ss.str(); // loading query into string
						const char* q = query.c_str(); // converting string to const char
						qstate = mysql_query(conn, q);
						if (qstate == 0) { // if qstate == 0 (EVERYTHING IS OK!) then pop out a 1, 1 will lead to the dialog that will say ("GrowID Created")		
							//TODO			
						}
						else {

						}
					}
					mysql_close(conn);
					enet_peer_disconnect_later(peer, 0);
					//SendConsoleMsg(peer, "Unban for you :)");

				}


				string daysleft = BanDays(stoi(bantime) + stoi(bandate) - GetCurrentTimeInternalSeconds()) + " days`o, `w";
				string hoursleft = BanHours(stoi(bantime) + stoi(bandate) - GetCurrentTimeInternalSeconds()) + " hours`o, `w";
				string minsleft = BanMinutes(stoi(bantime) + stoi(bandate) - GetCurrentTimeInternalSeconds()) + " mins`o, `w";
				string seleft = BanSecs(stoi(bantime) + stoi(bandate) - GetCurrentTimeInternalSeconds()) + " secs";

				int daysez = stoi(daysleft);
				int hoursez = stoi(hoursleft);
				int minsez = stoi(minsleft);
				int secondsez = stoi(seleft);

				if (daysez == 0) {
					daysleft = "";
				}
				if (hoursez == 0) {
					hoursleft = "";
				}
				if (minsez == 0) {
					minsleft = "";
				}
				if (secondsez == 0) {
					seleft = "";
				}
				string bantext = daysleft + hoursleft + minsleft + seleft;
				//cout << "Days " + daysleft << endl << "Hours "+ hoursleft << endl << "Minutes "  + minsleft << endl << "Secs " + seleft << endl; 
				string caused = displayname;
				//	BlockLogin(peer, , "", "");

				string value = "`4Sorry, this account, device or location has been temporarily banned. `oIf you didn't do anything wrong, it could be because you're playing from the same place or on the same device as someone who did. Visit at `5" + discord + " `oif you have any questions. This is temporary ban caused by `w" + caused + "`o and will be removed in `w" + bantext + "`o.";

				BlockLoginNoUrl(peer, value);


			}

			((PlayerInfo*)(peer->data))->bantime = stoi(bantime.c_str());
			((PlayerInfo*)(peer->data))->bandate = stoi(bandate.c_str());
			if (admin2 != 0) {
				Admin admin;
				admin.username = username;
				admin.password = ((PlayerInfo*)(peer->data))->tankIDPass;
				admin.level = admin2;
				admins.push_back(admin);
				((PlayerInfo*)(peer->data))->adminLevel = admin2;
			}

			((PlayerInfo*)(peer->data))->rawName = usercheck;
			((PlayerInfo*)(peer->data))->displayName = displayname;
			((PlayerInfo*)(peer->data))->backupName = displayname;
			((PlayerInfo*)(peer->data))->gems = gem;
			((PlayerInfo*)(peer->data))->cloth_hair = hair;
			((PlayerInfo*)(peer->data))->cloth_face = face;
			((PlayerInfo*)(peer->data))->cloth_mask = mask;
			((PlayerInfo*)(peer->data))->cloth_back = back;
			((PlayerInfo*)(peer->data))->cloth_ances = ances;
			((PlayerInfo*)(peer->data))->cloth_feet = shoe;
			((PlayerInfo*)(peer->data))->cloth_hand = hand;
			((PlayerInfo*)(peer->data))->cloth_necklace = neck;
			((PlayerInfo*)(peer->data))->cloth_pants = pant;
			((PlayerInfo*)(peer->data))->cloth_shirt = shirt;


			((PlayerInfo*)(peer->data))->lquestprogress = lprogress;
			((PlayerInfo*)(peer->data))->lqueststep = lstep;
			((PlayerInfo*)(peer->data))->ltype = ltype;



			((PlayerInfo*)(peer->data))->level = level;
			((PlayerInfo*)(peer->data))->xp = xp;
			((PlayerInfo*)(peer->data))->currentWorld = "EXIT";

			((PlayerInfo*)(peer->data))->skinColor = skin;



		}


		bool on = false;
		ENetPeer* currentPeer;

		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (currentPeer == peer)
				continue;
			if (((PlayerInfo*)(currentPeer->data))->rawName == PlayerDB::getProperName(username))
			{
				if (peer != currentPeer) {
					on = true;
					//enet_peer_disconnect_now(currentPeer, 0);
				}
			}
		}

		if (on) sendConsoleMsg(peer, "`4ALREADY ON??? `wIf you were online before this is nothing to worry about.``");
		//	cout << 33 << endl;
		return 1;

	}
}



void eventPool(ENetPeer* peer)
{
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;



		bool handleStuffInWorld = true;

		PlayerInfo* pData = ((PlayerInfo*)(peer->data));

		long timern = GetCurrentTimeInternalSeconds();

		if (pData->currentWorld == "EXIT") handleStuffInWorld = false;


		if (handleStuffInWorld)
		{
			WorldInfo* world = getPlyersWorld(peer);
			int x = pData->x / 32;
			int y = pData->y / 32;

			if (world == NULL) continue;


			if (pData->useGeiger)
			{

				if ((pData->lastGeigerTime + pData->geigerTimeModifier) < timern)
				{
					pData->lastGeigerTime = timern;
					pData->geigerTimeModifier = 3;

					int foundState = 0;
					bool exact = false;
					int gx = world->geiger_locX;
					int gy = world->geiger_locY;

					if (isInside(gx, gy, 12, x, y))
					{
						if (isInside(gx, gy, 8, x, y))
						{
							pData->geigerTimeModifier = 2;
						}

						foundState = 1;
					}

					if (isInside(gx, gy, 6, x, y))
					{
						pData->geigerTimeModifier = 1;
						if (isInside(gx, gy, 2, x, y))
						{
							pData->geigerTimeModifier = 0;
							pData->geigerIdleScore++;
						}
						foundState = 2;
						if (pData->geigerIdleScore > 3)
						{
							pData->geigerIdleScore = 0;
							exact = true;
						}
					}

					if (x == gx && y == gy)
					{

						exact = true;
						foundState = 2;
					}
					if (foundState == 0)
					{
						SendParticleEffect(peer, pData->x + 10, pData->y + 10, 0, 114, 0);
					}
					else if (foundState == 1)
					{
						SendParticleEffect(peer, pData->x + 10, pData->y + 10, 1, 114, 0);
					}
					else if (foundState == 2)
					{
						SendParticleEffect(peer, pData->x + 10, pData->y + 10, 2, 114, 0);
						if (exact)
						{
							SendParticleEffect(peer, pData->x + 10, pData->y + 10, 3, 114, 0);
							pData->haveGeigerRadiation = true;
							sendState(peer, pData);
							Player::OnTalkBubble(peer, pData->netID, "I found `2noob", true);

						}
					}
				}
				else
				{

				}
			}
		}
	}
}




void monitorCheck(ENetPeer* peer, int x, int y) {
	PlayerInfo* pinfo = ((PlayerInfo*)(peer->data));

	bool found = false;
	int xx = 0;
	int yy = 0;
	string hmon_owner = "<NULL>";
	if (pinfo->currentWorld != "EXIT") {
		WorldInfo* world = getPlyersWorld(peer);


		if (world != nullptr) {
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 1240) {

					xx = (i % world->width);
					yy = (i / world->width);
					hmon_owner = world->items[i].hmonitor_owner;
					ENetPeer* currentPeer;

					for (currentPeer = server->peers;
						currentPeer < &server->peers[server->peerCount];
						++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
							continue;
						PlayerInfo* cp = ((PlayerInfo*)(currentPeer->data));
						if (cp->backupName == hmon_owner) {
							found = true;

						}

					}
					if (found) {
						sendHMonitor(peer, xx, yy, hmon_owner, true);
					}
					else {
						sendHMonitor(peer, xx, yy, hmon_owner, false);
					}

				}

			}
		}
	}

}
void updatePlayer(ENetPeer* peer, int x, int y) {

	PlayerInfo* pinfo = ((PlayerInfo*)(peer->data));

	bool found = false;
	int xx = 0;
	int yy = 0;

	if (isDoubleJumpItem(((PlayerInfo*)(peer->data))->cloth_back)) {
		((PlayerInfo*)(peer->data))->canDoubleJump = true;
		sendState(peer, ((PlayerInfo*)(peer->data)));
	}

#pragma region Coffee

	long long coffee = 0;
	coffee = pinfo->usedCoffee;
	coffee += pinfo->leftCoffee;
	if (pinfo->Caffeine) {
		if (coffee <= GetCurrentTimeInternalSeconds()) {

			PlayAudioSelf(peer, "audio/dialog_confirm.wav");
			sendConsoleMsg(peer, "Ugh, caffeine crash. (`$Feelin' Blue `omod removed)");
			pinfo->Caffeine = false;
			pinfo->haveCigar = false;
			sendState(peer, pinfo);


		}
	}






#pragma endregion Coffee

#pragma region BlueBerry
	long long blueberry = 0;
	blueberry = (pinfo->usedBerry);
	blueberry += (pinfo->lastBerry);
	if (pinfo->blueBerry) {
		if (blueberry <= GetCurrentTimeInternalSeconds())
		{
			PlayAudioSelf(peer, "audio/dialog_confirm.wav");
			pinfo->skinColor = 0x8295C3FF;
			sendClothes(peer);
			sendConsoleMsg(peer, "The effects of the `1blueberry`o have worn off. (`$Feelin' Blue `omod removed)");
			pinfo->blueBerry = false;

		}
	}
#pragma endregion BlueBerry




}


void SendConsoleMsgAll(ENetPeer* peer, string message) {
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
bool has_only_digits(const string s) {
	return s.find_first_not_of("0123456789") == string::npos;
}
bool has_only_digits_wnegative(const string s) {
	return s.find_first_not_of("-0123456789") == string::npos;
}

void parsePunchEffs() {
	std::ifstream infile("punchdata.txt");
	for (std::string line; getline(infile, line);)
	{
		if (line.length() > 8 && line[0] != '/' && line[1] != '/')
		{
			vector<string> ex = explode("|", line);
			items.at(atoi(ex[0].c_str())).punchEffect = atoi(ex[1].c_str()) - 8421376;
		}
	}
}
 
#ifdef _WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main()
#endif

{


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	//system("color 5");
	//SetConsoleTextAttribute(hConsole, 3);
	cout << "Growheaven private server, made by Finland#1337" << endl;
	system("color 7");
	SetConsoleTitle(_T("Growheaven Console"));
	cout << "Loading config!" << endl;

	cout << "Loading dialogs!" << endl;
	heatwave = ReadAllText("dialogs/hw.txt");
	std::thread first(commands);
	if (first.joinable()) {
		first.detach();
	}
	loadConfig();
	std::ifstream t("uids.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	userIDcount = atoi(str.c_str());
	cout << "Total UserID's " << userIDcount << endl;
	std::thread first2(autoSaveWorlds);
	if (first2.joinable()) {
		first2.detach();
	}
	enet_initialize();
	signal(SIGINT, exitHandler);
	int itemdathash;

	{
		std::ifstream file("items.dat", std::ios::binary | std::ios::ate);
		itemsDatSize = file.tellg();


		itemsDat = new BYTE[60 + itemsDatSize];
		string asdf = "0400000010000000FFFFFFFF000000000800000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		for (int i = 0; i < asdf.length(); i += 2)
		{
			char x = ch2n(asdf[i]);
			x = x << 4;
			x += ch2n(asdf[i + 1]);
			memcpy(itemsDat + (i / 2), &x, 1);
			if (asdf.length() > 60 * 2) throw 0;
		}
		memcpy(itemsDat + 56, &itemsDatSize, 4);
		file.seekg(0, std::ios::beg);

		if (file.read((char*)(itemsDat + 60), itemsDatSize))
		{
			uint8_t* pData;
			int size = 0;
			const char filename[] = "items.dat";
			size = filesize(filename);
			pData = getA((string)filename, &size, false, false);
			cout << "Updating items data success! Hash: " << HashString((unsigned char*)pData, size) << endl;
			itemdathash = HashString((unsigned char*)pData, size);
			file.close();
			serializeItems();
				parsePunchEffs();

		}
		else {
			cout << "Updating items data failed! ( No items.dat file found!)" << endl;
		}
	}
	cout << "Items.dat serialized! Loaded items: " << items.size() << endl;


	//world = generateWorld();c
	cout << "Loading default worlds" << endl;
	worldDB.get("TEST");
	worldDB.get("GROWHEAVEN");

	ENetAddress address;
	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	enet_address_set_host(&address, "0.0.0.0");
	//address.host = ENET_HOST_ANY;
	/* Bind the server to port 1234. */
	address.port = configPort;
	server = enet_host_create(&address /* the address to bind the server host to */,
		1024      /* allow up to 32 clients and/or outgoing connections */,
		10      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		SetConsoleTextAttribute(hConsole, 12);
		fprintf(stderr,
			" An error occurred while trying to create an ENet server host.\n");
		while (1);
		SetConsoleTextAttribute(hConsole, 10);
		exit(EXIT_FAILURE);
	}
	server->checksum = enet_crc32;
	enet_host_compress_with_range_coder(server);

	cout << "Building items database..." << endl;
	BuildItemsDatabase();
	cout << "Database is built!\n" << endl;

	ENetEvent event;
	/* Wait up to 1000 milliseconds for an event. */
	while (true)
	{
		while (enet_host_service(server, &event, 1000) > 0)
		{


			ENetPeer* peer = event.peer;
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
			{
#ifdef TOTAL_LOG
				printf("A new client connected.\n");
#endif

				/* Store any relevant client information here. */
				//event.peer->data = "Client information";
				ENetPeer* currentPeer;
				int count = 0;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (currentPeer->address.host == peer->address.host)
						count++;
				}

				event.peer->data = new PlayerInfo;
				/* Get the string ip from peer */
				char clientConnection[16];
				enet_address_get_host_ip(&peer->address, clientConnection, 16);
				((PlayerInfo*)(peer->data))->charIP = clientConnection;
				if (count > 3)
				{
					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`rToo many accounts are logged on from this IP. Log off one account before playing please.``"));
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet);
					delete p.data;
					//enet_host_flush(server);
					enet_peer_disconnect_later(peer, 0);
				}
				else {
					sendData(peer, 1, 0, 0);
				}


				continue;
			}
			case ENET_EVENT_TYPE_RECEIVE:
			{
				if (((PlayerInfo*)(peer->data))->isUpdating)
				{
					cout << "packet drop" << endl;
					continue;


				}
				if (!peer) continue;

				if (((PlayerInfo*)(peer->data))->ignorePackets) continue;
				if (event.packet->dataLength > 4096) {
					enet_peer_reset(peer);
				}
				//	if (((PlayerInfo*)(peer->data))->isIn && ((PlayerInfo*)(peer->data))->rawName == "") enet_peer_disconnect_later(peer, 0);


				int messageType = GetMessageTypeFromPacket(event.packet);

				WorldInfo* world = getPlyersWorld(peer);
				switch (messageType) {
				case 2:
				{
					if (logs)	cout << "" << GetTextPointerFromPacket(event.packet) << endl;

					string cch = GetTextPointerFromPacket(event.packet);
					string str = cch.substr(cch.find("text|") + 5, cch.length() - cch.find("text|") - 1);

					if (cch.find("action|wrench") == 0) {
						std::stringstream ss(cch);
						std::string to;
						int id = -1;
						while (std::getline(ss, to, '\n')) {
							vector<string> infoDat = explode("|", to);
							if (infoDat.size() < 3) continue;
							if (infoDat[1] == "netid") {
								try {
									id = stoi(infoDat[2]); // crash fix
								}
								catch (...) { }
							}

						}
						if (id < 0) continue; //not found

						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;

							if (isHere(peer, currentPeer)) {
								if (((PlayerInfo*)(currentPeer->data))->netID == id) {
									string name = ((PlayerInfo*)(currentPeer->data))->displayName;
									GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\nadd_label_with_icon|big|" + name + "|left|18|\nadd_spacer|small|\n\nadd_quick_exit|\nend_dialog|player_info||Close|"));
									ENetPacket* packet = enet_packet_create(p.data,
										p.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet);
									delete p.data;
								}

							}

						}
					}
					if (cch.find("action|respawn") == 0)
					{

						if (cch.find("action|respawn_spike") == 0) {
							playerRespawn(peer, true);
						}
						else
						{
							playerRespawn(peer, false);
						}
					}
					if (cch.find("action|growid") == 0)
					{
#ifndef REGISTRATION
						{
							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "Registration is not supported yet!"));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							delete p.data;
							//enet_host_flush(server);
						}
#endif
#ifdef REGISTRATION
						//GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`w" + itemDefs.at(id).name + "``|left|" + std::to_string(id) + "|\n\nadd_spacer|small|\nadd_textbox|" + itemDefs.at(id).description + "|left|\nadd_spacer|small|\nadd_quick_exit|\nadd_button|chc0|Close|noflags|0|0|\nnend_dialog|gazette||OK|"));
						GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wGet a GrowID``|left|206|\n\nadd_spacer|small|\nadd_textbox|A `wGrowID `wmeans `oyou can use a name and password to logon from any device.|\nadd_spacer|small|\nadd_textbox|This `wname `owill be reserved for you and `wshown to other players`o, so choose carefully!|\nadd_text_input|username|GrowID||30|\nadd_text_input|password|Password||100|\nadd_text_input|passwordverify|Password Verify||100|\nadd_textbox|Your `wemail address `owill only be used for account verification purposes and won't be spammed or shared. If you use a fake email, you'll never be able to recover or change your password.|\nadd_text_input|email|Email||100|\nend_dialog|register|Cancel|Get My GrowID!|\n"));
						ENetPacket* packet = enet_packet_create(p.data,
							p.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet);
						delete p.data;
#endif

					}

					if (cch.find("action|buy") == 0) {
						std::stringstream ss(cch);
						std::string to;
						string items = "";
						while (std::getline(ss, to, '\n')) {
							vector<string> infoDat = explode("|", to);
							if (infoDat[0] == "item") {
								items = infoDat[1];
							}
							if (items == "buymod") {

								GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnStoreBuyConfirm"), 1));

								ENetPacket* packet2 = enet_packet_create(p2.data,
									p2.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet2);
								delete p2.data;

								GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnStorePurchaseResult"), "`oYou dont have enough GH wls!"));

								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet3);
								delete p3.data;
							}
							else 	if (items == "adminrole") {

								GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnStoreBuyConfirm"), 1));

								ENetPacket* packet2 = enet_packet_create(p2.data,
									p2.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet2);
								delete p2.data;

								GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnStorePurchaseResult"), "`oYou dont have enough GTCB wls!"));

								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet3);
								delete p3.data;
							}
							else if (items == "buyvip") {

								GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnStoreBuyConfirm"), 1));

								ENetPacket* packet2 = enet_packet_create(p2.data,
									p2.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet2);
								delete p2.data;

								GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnStorePurchaseResult"), "`oYou dont have enough GTCB wls!"));

								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet3);
								delete p3.data;
							}
							else if (items == "iap") {

								GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnStoreBuyConfirm"), 1));

								ENetPacket* packet2 = enet_packet_create(p2.data,
									p2.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet2);
								delete p2.data;

								GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnStorePurchaseResult"), "`oYou dont have enough GTCB wls!"));

								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								/*	GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnStoreRequest"), "set_description_text|In-game assets purchases!\nadd_button|buyvip|Buy VIP role|interface/large/store_buttons29.rttex||0|3|0|0||\nadd_button|buymod|Moderator role|interface/large/store_buttons16.rttex||0|3|0|0|||\nadd_button|adminrole|admin role|interface/large/store_buttons29.rttex|Buy admin role!|0|2|0|0||\nset_back_target|main\nset_back_focus|iap_menu"));
								ENetPacket* packet2 = enet_packet_create(p2.data,
									p2.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet2);
								delete p2.data;*/
							}



						}
					}

					if (cch.find("action|trade_started") == 0) { // trading

					}
					if (cch.find("action|trade_cancel") == 0) { // trading
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;
							if (isHere(peer, currentPeer)) {
								if (((PlayerInfo*)(peer->data))->isTradingWithUserID == ((PlayerInfo*)(currentPeer->data))->userID || ((PlayerInfo*)(peer->data))->userID == ((PlayerInfo*)(currentPeer->data))->isTradingWithUserID) {
									SendCancelTrade(currentPeer, "Trade was cancelled by the other player.");
									SendCancelTrade(peer, "");
									break;
								}
							}
						}
					}
					string modTradeText = "action|mod_trade\nitemID|";
					if (cch.find(modTradeText) == 0) {
						// item id detection


						int id = -1;
						id = atoi(cch.substr(modTradeText.size()).c_str());
						if (id == -1) continue;
						PlayerInfo* pinfo = (PlayerInfo*)peer->data;
						if (!pinfo->isTrading) {
							Player::PlayAudio(peer, "audio/cant_place_tile.wav", 0);
							break;
						}

						if (pinfo->tradeItems.size() >= 4) {
							Player::PlayAudio(peer, "audio/cant_place_tile.wav", 0);
							break;
						}

						int count = 0;

						//	count = ((PlayerInfo*)(peer->data))->wls;
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`2Trade `w" + items.at(id).name + "``|left|" + to_string(id) + "|\nadd_textbox|`2How many to trade?``|\nadd_text_input|count||" + to_string(count) + "|3|\nend_dialog|trade_add" + to_string(id) + "|Cancel|OK|");
					}
					if (cch.find("action|trade_accept") == 0) { // trading
						std::stringstream ss(cch);
						std::string to;
						int status = 0;
						while (std::getline(ss, to, '\n')) {
							vector<string> infoDat = explode("|", to);
							if (infoDat.size() == 2) {
								if (infoDat[0] == "status")
								{
									if (infoDat[1] == "1")
									{
										status = 1;
									}
								}
							}
						}
						PlayerInfo* pinfo = (PlayerInfo*)peer->data;
						if (!pinfo->isTrading) continue;

						pinfo->isAcceptingTrade = status;
						UpdateTradeAcceptedStatus(peer);
						ENetPeer* peer2 = NULL;
						PlayerInfo* pinfo2 = NULL;
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;
							if (isHere(peer, currentPeer)) {
								if (pinfo->isTradingWithUserID == ((PlayerInfo*)(currentPeer->data))->userID || ((PlayerInfo*)(peer->data))->userID == ((PlayerInfo*)(currentPeer->data))->isTradingWithUserID) {
									pinfo2 = (PlayerInfo*)currentPeer->data;
									peer2 = currentPeer;
									if (pinfo->isAcceptingTrade && pinfo2->isAcceptingTrade)
									{
										bool successful = true;

										Player::OnForceTradeEnd(peer);
										Player::OnForceTradeEnd(peer2);
										//Player::OnForceTradeEnd(peer2); TODO

										pinfo->isInFinalTradeDialog = true;
										pinfo2->isInFinalTradeDialog = true;
										pinfo->isWaitingForTradeWithUserID = 0;
										pinfo2->isWaitingForTradeWithUserID = 0;
										pinfo->isWaitingForTrade = false;
										pinfo2->isWaitingForTrade = false;
										pinfo2->isAcceptingTrade = false;
										pinfo->isAcceptingTrade = false;
										Player::OnDialogRequest(peer, "add_label_with_icon|big|`wTrade Confirmation``|left|1366|\nadd_spacer|small\nadd_textbox|`4You'll give:|\nadd_spacer|small\n" + FormatTradeItemsForDialog(pinfo->tradeItems, 0) + "\nadd_spacer|small\nadd_textbox|`2You'll get:``|\nadd_spacer|small\n" + FormatTradeItemsForDialog(pinfo2->tradeItems, 1) + "\nadd_spacer|small\nadd_button|dothetrade|`oDo The Trade!``|\nend_dialog|tradeconfirm||Cancel|");
										Player::OnDialogRequest(peer2, "add_label_with_icon|big|`wTrade Confirmation``|left|1366|\nadd_spacer|small\nadd_textbox|`4You'll give:|\nadd_spacer|small\n" + FormatTradeItemsForDialog(pinfo2->tradeItems, 0) + "\nadd_spacer|small\nadd_textbox|`2You'll get:``|\nadd_spacer|small\n" + FormatTradeItemsForDialog(pinfo->tradeItems, 1) + "\nadd_spacer|small\nadd_button|dothetrade|`oDo The Trade!``|\nend_dialog|tradeconfirm||Cancel|");
									}

									break;

								}
							}
						}

						// detect if the other player accepts the trade, TODO


					}

					if (cch.find("action|store") == 0)
					{
						sendConsoleMsg(peer, "gay");
						//enet_host_flush(server);
					}

					if (cch.find("action|info") == 0)
					{
						std::stringstream ss(cch);
						std::string to;
						int id = -1;
						int count = -1;
						while (std::getline(ss, to, '\n')) {
							vector<string> infoDat = explode("|", to);
							if (infoDat.size() == 3) {
								if (infoDat[1] == "itemID") id = atoi(infoDat[2].c_str());
								if (infoDat[1] == "count") count = atoi(infoDat[2].c_str());
							}
						}
						if (id == -1 || count == -1) continue;
						if (itemDefs.size() < id || id < 0) continue;
						GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`w" + itemDefs.at(id).name + "``|left|" + std::to_string(id) + "|\n\nadd_spacer|small|\nadd_textbox|" + itemDefs.at(id).description + "|left|\nadd_spacer|small|\nadd_quick_exit|\nend_dialog|item_info|OK||"));
						ENetPacket* packet = enet_packet_create(p.data,
							p.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet);

						//enet_host_flush(server);
						delete p.data;
					}
					if (cch.find("action|dialog_return") == 0)
					{
						std::stringstream ss(cch);
						std::string to;
						string dropitemcount = "0";
						string btn = "";
						bool isRegisterDialog = false;
						bool isDoorDialog = false;
						bool isHeatWave = false;
						bool isBG = false;
						bool isStuff = false;
						bool isTradeDialog = false;
						bool isDropDialog = false;
						bool isFinishTrade = false;
						bool isMarsDialog = false;
						bool isGrowscan = false;
						bool isLockDialog = false;
						string marsname = "";
						int itemtodo = 0;
						string bgitem = "";
						string stuff_gravity = "";
						bool stuff_invert = false;
						bool stuff_spin = false;
						string username = "";
						string stuffITEM = "";
						int r = 0;
						int g = 0;
						int b = 0;
						string noclip = "";
						string disable_music = "";
						string tempo = "";
						string disable_music_render = "";
						string playerNetId = "";
						string doorworld = "";
						string doorid = "";
						string doordescription = "";
						int counttodo = 0;
						string password = "";
						string passwordverify = "";
						string email = "";
						string message = "";
						bool isConfirmQuest = false;
						bool isFindDialog = false;
						string pub = "";
						bool signEditor = false;
						bool captcha = false;
						string captchaanswer;
						while (std::getline(ss, to, '\n')) {
							vector<string> infoDat = explode("|", to);
							if (infoDat.size() == 2) {
								if (infoDat[0] == "buttonClicked") btn = infoDat[1];
								if (infoDat[0] == "dialog_name" && infoDat[1] == "register")
								{
									isRegisterDialog = true;
								}
								if (infoDat[0] == "dialog_name" && infoDat[1] == "wlmenu")
									isLockDialog = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "lquestconfirm")
									isConfirmQuest = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "doorok")
								{
									isDoorDialog = true;
								}
								if (infoDat[0] == "dialog_name" && infoDat[1] == "dropdialog") {
									isDropDialog = true;
								}
								if (infoDat[0] == "dialog_name" && infoDat[1] == "growscan_float")
									isGrowscan = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "mars_dialog")
									isMarsDialog = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "stuff_weather")
									isStuff = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "bg_weather")
									isBG = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "heatwave")
									isHeatWave = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "captcha_submit")
									captcha = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "findid")
									isFindDialog = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "editsign")
									signEditor = true;
								if (infoDat[0] == "dialog_name" && infoDat[1] == "tradeconfirm") {
									isFinishTrade = true;

								}
								if (infoDat[0] == "dialog_name" && infoDat[1].find("trade_add") == 0)
								{

									itemtodo = atoi(infoDat[1].substr(9).c_str());
									if (itemtodo == -1) break;
									isTradeDialog = true;
								}
								if (signEditor) {
									if (infoDat[0] == "signtext") message = infoDat[1];
								}

								if (isDropDialog) {
									if (infoDat[0] == "dropitemcount") dropitemcount = infoDat[1];

								}
								if (isDropDialog) {
									if (infoDat[0] == "amount") dropitemcount = infoDat[1];
								}
								if (isLockDialog) {
									/*
										if (infoDat[0] == "checkbox_public") pub = infoDat[1];
										if (infoDat[0] == "checkbox_noclip") noclip = infoDat[1];
										if (infoDat[0] == "checkbox_disable_music") disable_music = infoDat[1];
										if (infoDat[0] == "tempo") tempo = infoDat[1];
										if (infoDat[0] == "checkbox_disable_music_render") disable_music_render = infoDat[1];*/
									if (infoDat[0] == "netid") playerNetId = infoDat[1];
									cout << "pee" << endl;
								}

								if (isStuff) {


									if (infoDat[0] == "stuff_pick") stuffITEM = infoDat[1];


									if (infoDat[0] == "stuff_gravity") stuff_gravity = infoDat[1];
									if (infoDat[0] == "stuff_spin") stuff_spin = atoi(infoDat[1].c_str());
									if (infoDat[0] == "stuff_invert") stuff_invert = atoi(infoDat[1].c_str());


								}
								if (isMarsDialog) {
									if (infoDat[0] == "mars_name") marsname = infoDat[1];
								}
								if (isRegisterDialog) {
									if (infoDat[0] == "username") username = infoDat[1];
									if (infoDat[0] == "password") password = infoDat[1];
									if (infoDat[0] == "passwordverify") passwordverify = infoDat[1];
									if (infoDat[0] == "email") email = infoDat[1];

								}
								if (isHeatWave) {
									if (infoDat[0] == "heatwave_red") r = atoi(infoDat[1].c_str());
									if (infoDat[0] == "heatwave_green") g = atoi(infoDat[1].c_str());
									if (infoDat[0] == "heatwave_blue") b = atoi(infoDat[1].c_str());

								}
								if (isTradeDialog) {

									if (infoDat[0] == "count")
									{
										counttodo = atoi(infoDat[1].c_str());
										if (counttodo == -1) continue;
									}
								}
								if (isDoorDialog) {

									if (infoDat[0] == "worldname") doorworld = infoDat[1];
									if (infoDat[0] == "door") doordescription = infoDat[1];
									if (infoDat[0] == "doorid") doorid = infoDat[1];
								}

								if (isGrowscan && btn.substr(0, 4) == "item") {

									int Id = atoi(btn.substr(4, btn.length() - 4).c_str());
									int intid = atoi(btn.substr(4, btn.length() - 4).c_str());
									string ide = btn.substr(4, btn.length() - 4).c_str();
									cout << Id << "kek" << endl;
									sendArrow(peer, Id, true);

								}
								if (isConfirmQuest) {
									PlayerInfo* pinfo = ((PlayerInfo*)(peer->data));
									string btntext = "";
									if (pinfo->gems < 1) {
										btntext = "You have none to deliver!";
									}
									else if (pinfo->gems < 100001) {
										btntext = "Deliver " + to_string(pinfo->gems) + " Gems";

									}
									else {
										btntext = "Deliver " + to_string(100000) + " Gems";
									}
									string ste = "set_default_color|`o\nadd_label_with_icon|big|`9Quest Of Fire``|left|1790|\nadd_smalltext|(Step 1/10)|\nadd_spacer|small|\nadd_textbox|`oI challenge you to  bring me 100,000 gems!|\nadd_spacer|small|\nadd_smalltext|Current progress " + to_string(((PlayerInfo*)(peer->data))->lquestprogress) + "/100000|\nadd_button|lwizstep1|" + btntext + "|\nadd_button|giveup|Give up this quest|\nend_dialog|lqueststep1|Goodbye!|";
									((PlayerInfo*)(peer->data))->lqueststep = 1;
									((PlayerInfo*)(peer->data))->ltype = 1;
									Player::OnDialogRequest(peer, ste);
								}
								if (isFindDialog && btn.substr(0, 4) == "tool") {
									int Id = atoi(btn.substr(4, btn.length() - 4).c_str());
									int intid = atoi(btn.substr(4, btn.length() - 4).c_str());
									string ide = btn.substr(4, btn.length() - 4).c_str();
									size_t invsize = 250;
									if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsize) {
										PlayerInventory inventory;
										InventoryItem item;
										item.itemID = Id;
										item.itemCount = 200;
										inventory.items.push_back(item);
										item.itemCount = 1;
										item.itemID = 18;
										inventory.items.push_back(item);
										item.itemID = 32;
										inventory.items.push_back(item);
										((PlayerInfo*)(peer->data))->inventory = inventory;

										if (GetItemDef(intid).rarity == 999) {
											GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oGiven`w 200 " + GetItemDef(intid).name + "`o. Item ID: `w" + ide + "`o."));

											ENetPacket* packet2 = enet_packet_create(p2.data,
												p2.len,
												ENET_PACKET_FLAG_RELIABLE);
											enet_peer_send(peer, 0, packet2);
											delete p2.data;
										}
										else {
											GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oGiven`w 200 " + GetItemDef(intid).name + "`o. Rarity `w" + std::to_string(GetItemDef(intid).rarity) + "`o. Item ID: `w" + ide + "`o."));

											ENetPacket* packet2 = enet_packet_create(p2.data,
												p2.len,
												ENET_PACKET_FLAG_RELIABLE);
											enet_peer_send(peer, 0, packet2);
											delete p2.data;
										}
										int netID = ((PlayerInfo*)(peer->data))->netID;
										SendTradeEffect(peer, intid, netID, netID, 150);

									}
									else {
										InventoryItem item;
										item.itemID = Id;
										item.itemCount = 200;
										((PlayerInfo*)(peer->data))->inventory.items.push_back(item);
										string ide = std::to_string(Id);
										if (GetItemDef(intid).rarity == 999) {
											GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oGiven`w 200 " + GetItemDef(intid).name + "`o. Item ID: `w" + ide + "`o."));

											ENetPacket* packet2 = enet_packet_create(p2.data,
												p2.len,
												ENET_PACKET_FLAG_RELIABLE);
											enet_peer_send(peer, 0, packet2);
											delete p2.data;
										}
										else {
											GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oGiven`w 200 " + GetItemDef(intid).name + "`o. Rarity `w" + std::to_string(GetItemDef(intid).rarity) + "`o. Item ID: `w" + ide + "`o."));

											ENetPacket* packet2 = enet_packet_create(p2.data,
												p2.len,
												ENET_PACKET_FLAG_RELIABLE);
											enet_peer_send(peer, 0, packet2);
											delete p2.data;
										}
										int netID = ((PlayerInfo*)(peer->data))->netID;


									}
									sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
								}
								PlayerInfo* pinfo = (PlayerInfo*)(peer->data);
								if (isDoorDialog) {
									if (world) {
										bool found = false;
										int x = ((PlayerInfo*)(peer->data))->lastPunchX;
										int y = ((PlayerInfo*)(peer->data))->lastPunchY;
										int fg = world->items[x + (y * world->width)].foreground;
										int bg = world->items[x + (y * world->width)].background;
										string doorId = getStrUpper(doorid);
										string linksToWorld = getStrUpper(doorworld);
										if (getItemDef(fg).blockType == BlockTypes::DOOR || getItemDef(fg).blockType == BlockTypes::PORTAL) {
											for (int i = 0; i < world->door.size(); i++) {
												if (world->door.at(i).x == x && world->door.at(i).y == y) {

													world->door.at(i).doorId = doorId;
													world->door.at(i).linksToWorld = linksToWorld;
													world->items[x + (y * world->width)].worldinput = linksToWorld;
													world->items[x + (y * world->width)].doorid = doorId;
													found = true;
													break;
												}
											}
											if (found == false) {
												Doorxd a;
												a.doorId = doorId;
												a.linksToWorld = linksToWorld;
												world->items[x + (y * world->width)].worldinput = linksToWorld;
												world->items[x + (y * world->width)].doorid = doorId;
												a.x = x;
												a.y = y;
												world->door.push_back(a);
											}
											ENetPeer* currentPeer;
											for (currentPeer = server->peers;
												currentPeer < &server->peers[server->peerCount];
												++currentPeer)
											{
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
													continue;
												if (isHere(peer, currentPeer)) {
													//	updateDoor(currentPeer, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].foreground, x, y, doordescription);
												}
											}
											world->items[x + (y * world->width)].sign = doordescription;
										}
									}
								}
							


								if (isStuff) {
									if (world != NULL) {
										if (stuffITEM != "") {
											int x = pinfo->wrenchedBlockLocation % world->width;
											int y = pinfo->wrenchedBlockLocation / world->width;
											int id = atoi(stuffITEM.c_str());
											int stuffGra = atoi(stuff_gravity.c_str());
											world->stuff_invert = stuff_invert;
											world->stuff_spin = stuff_spin;
											world->stuff_gravity = stuffGra;
											world->stuffID = atoi(stuffITEM.c_str());
											sendStuffweather(peer, x, y, world->stuffID, stuffGra, stuff_spin, stuff_invert);

										}
										else {

											int x = pinfo->wrenchedBlockLocation % world->width;
											int y = pinfo->wrenchedBlockLocation / world->width;

											int stuffGra = atoi(stuff_gravity.c_str());
											world->stuff_invert = stuff_invert;
											world->stuff_spin = stuff_spin;
											world->stuff_gravity = stuffGra;

											sendStuffweather(peer, x, y, world->stuffID, stuffGra, stuff_spin, stuff_invert);
										}





										int x = pinfo->wrenchedBlockLocation % world->width;
										int y = pinfo->wrenchedBlockLocation / world->width;
										if (world->items[x + (y * world->width)].activeWeather == true) {

											ENetPeer* currentPeer;

											for (currentPeer = server->peers;
												currentPeer < &server->peers[server->peerCount];
												++currentPeer)
											{
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
													continue;
												if (isHere(peer, currentPeer))
												{

													GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), 29));
													ENetPacket* packet2 = enet_packet_create(p2.data,
														p2.len,
														ENET_PACKET_FLAG_RELIABLE);

													enet_peer_send(currentPeer, 0, packet2);
													delete p2.data;
													continue;
												}
											}

										}

									}
								}
								if (isDropDialog) {
									if (!world) continue;
									int x;
									try {
										x = stoi(dropitemcount);
									}
									catch (std::invalid_argument& e) {
										Player::OnConsoleMessage(peer, "Please specify how many you want to drop");
										continue;
									}
									if (x < 1 || x > 200) continue;





									int uu = ((PlayerInfo*)(peer->data))->lastdropitem;
									if (uu != 18 && uu != 32) {
										if (world->allowDropTakeAll) {

											dropItem(peer, -1, ((PlayerInfo*)(peer->data))->x + (32 * (((PlayerInfo*)(peer->data))->isRotatedLeft ? -1 : 1) + rand() % 16), ((PlayerInfo*)(peer->data))->y + rand() % 16, ((PlayerInfo*)(peer->data))->lastdropitem, x, 0);
											RemoveItemFromInv(peer, uu, x, true);
										}
										else {
											if (isWorldOwner(peer, world) || getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 2) {

												dropItem(peer, -1, ((PlayerInfo*)(peer->data))->x + (32 * (((PlayerInfo*)(peer->data))->isRotatedLeft ? -1 : 1) + rand() % 16), ((PlayerInfo*)(peer->data))->y + rand() % 16, ((PlayerInfo*)(peer->data))->lastdropitem, x, 0);
												RemoveItemFromInv(peer, uu, x, true);
											}
										}
									}
								}
								if (isBG) {
									if (world != NULL) {
										if (infoDat[0] == "bg_pick") bgitem = infoDat[1];
										int id = atoi(bgitem.c_str());

										if (getItemDef(id).blockType != BlockTypes::BACKGROUND)
										{

											//  Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "You can only set background blocks to Weather Machine - Background!", true);
											continue;
											break;
										}


										int x = pinfo->wrenchedBlockLocation % world->width;
										int y = pinfo->wrenchedBlockLocation / world->width;

										sendBackground(peer, x, y, atoi(bgitem.c_str()));
										if (world->items[x + (y * world->width)].activeWeather == true) {

											ENetPeer* currentPeer;

											for (currentPeer = server->peers;
												currentPeer < &server->peers[server->peerCount];
												++currentPeer)
											{
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
													continue;
												if (isHere(peer, currentPeer))
												{

													GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), 34));
													ENetPacket* packet2 = enet_packet_create(p2.data,
														p2.len,
														ENET_PACKET_FLAG_RELIABLE);

													enet_peer_send(currentPeer, 0, packet2);
													delete p2.data;
													continue;
												}
											}

										}
										world->bgID = atoi(bgitem.c_str());

									}
								}


								if (btn == "lwizstep1") {
									PlayerInfo* p = (PlayerInfo*)(peer->data);
									if (p->gems < 1 && p->lquestprogress < 100001) {
										Player::OnTextOverlay(peer, "You have none to deliver!");

									}
									else if (p->gems < 100001 && p->gems != 0 && p->lquestprogress < 100001) {
										int lefttogive = 100000 - p->lquestprogress;
										int howmuchpay = 0;
										if (lefttogive > p->gems) {
											if (p->gems > 0) {
												howmuchpay = p->gems;
											}
											else {
												Player::OnTextOverlay(peer, "`4Something went wrong! Contant developers!");
												continue;

											}
										}
										else {

											howmuchpay = lefttogive;
										}
										p->lquestprogress += howmuchpay;
										Player::OnTextOverlay(peer, "Good, keep it going!");

										p->gems = p->gems - howmuchpay;
										Player::OnSetBux(peer, p->gems, 0);

										if (p->lquestprogress > 99999) {
											Player::OnTextOverlay(peer, "`9Quest step complete!!");
											Player::OnParticleEffect(peer, 48, p->x, p->y, 0);
											p->lqueststep = 2;
											p->lquestprogress = 0;
											string k = "set_default_color|`o\nadd_label_with_icon|big|`9Quest Of Fire``|left|1790|\nadd_smalltext|(Step 2/10)|\nadd_spacer|small|\nadd_textbox|`oI want you to break 1000 blocks because why not.|\nadd_spacer|small|\nadd_smalltext|Current progress " + to_string(((PlayerInfo*)(peer->data))->lquestprogress) + "/1000|\nadd_button|lwizstep2|I will go smash more!|\nadd_button|giveup|Give up this quest|\nend_dialog|lqueststep2|Goodbye!|";
											Player::OnDialogRequest(peer, k);
										}

									}

									else {
										int remove = 100000 - p->lquestprogress;
										p->gems = p->gems - remove;
										Player::OnSetBux(peer, p->gems, 0);
										Player::OnTextOverlay(peer, "`9Quest step complete!!");
										Player::OnParticleEffect(peer, 48, p->x, p->y, 0);
										p->lqueststep = 2;
										p->lquestprogress = 0;
										string k = "set_default_color|`o\nadd_label_with_icon|big|`9Quest Of Fire``|left|1790|\nadd_smalltext|(Step 2/10)|\nadd_spacer|small|\nadd_textbox|`oI want you to break 1000 blocks because why not.|\nadd_spacer|small|\nadd_smalltext|Current progress " + to_string(((PlayerInfo*)(peer->data))->lquestprogress) + "/1000|\nadd_button|lwizstep2|I will go smash more!|\nadd_button|giveup|Give up this quest|\nend_dialog|lqueststep2|Goodbye!|";
										Player::OnDialogRequest(peer, k);
									}
								}
								if (btn == "lwizstep2") {
									PlayerInfo* p = (PlayerInfo*)(peer->data);
									if (p->lquestprogress < 1000) {
										Player::OnTextOverlay(peer, "Go smash more!");
									}
									else {
										Player::OnTextOverlay(peer, "`9Quest step complete!!");
										Player::OnParticleEffect(peer, 48, p->x, p->y, 0);
										p->lqueststep = 3;
										p->lquestprogress = 0;
										string k = "";
										Player::OnDialogRequest(peer, k);
									}

								}

								if (btn == "startfire") {
									string confirm = "set_default_color|`o\nadd_label_with_icon|big|`9Quest Of Fire``|left|1790|\nadd_smalltext|`oThis quest will challenge every fiber of your Growtopian being. It will cost you thousands of gems, weeks, or months of time, and possibly your friends and family.|\nadd_smalltext|`oEvery quest has 10 steps to complete, and each step alone is probably more than most Growtopians could manage.|\nadd_smalltext|`oBut the rewards are also vast. If you complete this quest, you will earn the `9Legendary Dragon`o! These quest rewards are `5Untradeable`o, and you will truly be a Legendary Growtopian if you complete quest.|\nadd_smalltext|`oYou may turn in your quests at any Legendary Wizard you have access to (we're in a union), but I will vanish permamently if somebody turns in their final quest step to me, so don't let other people have access to me!|\nadd_smalltext|`oThere's one last thing you should know before you begin. You can quit your quest at any time, but be aware that if you do, you'll lose all progress on this quest. So choose your quest wisely and see it trough to the end!|\nadd_spacer|small|\nadd_textbox|`oSo... now that you've received the official disclaimer, are you truly prepared to embark on the Quest For The Fire|\nend_dialog|lquestconfirm|No!|Yes!|";
									Player::OnDialogRequest(peer, confirm);
								}
								if (btn == "floatingitems") {

									string additems = "";

									for (int i = 0; i < world->droppedItems.size(); i++)
									{
										//if (world->droppedItems.at(i).uid)
										int id = world->droppedItems.at(i).id;
										additems += "\nadd_label_with_icon_button||`w" + GetItemDef(id).name + ": " + to_string(world->droppedItems.at(i).count) + "|left|" + to_string(world->droppedItems.at(i).id) + "|item" + to_string(id) + "|";
									}

									Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wWorld Items``|left|6016|\nadd_spacer|small|\nadd_textbox|`oPress on the icon to be directed to the location of the item.|\nadd_spacer|small|" + additems + "\nadd_spacer|small|\nadd_button|goback|Back|\nend_dialog|growscan_float|||\n");

								}

								if (isFinishTrade) {
									PlayerInfo* pinfo = (PlayerInfo*)(peer->data);
									if (!pinfo) continue;
									if (!pinfo->isTrading) continue;
									if (!pinfo->isInFinalTradeDialog) continue;
									ENetPeer* peer2 = NULL;
									PlayerInfo* pinfo2 = NULL;
									//if (!pinfo->isTradingWithWho) continue; TODO
									//ENetPeer* peer2 = pinfo->isTradingWithWho; TODO
									ENetPeer* currentPeer;
									for (currentPeer = server->peers;
										currentPeer < &server->peers[server->peerCount];
										++currentPeer)
									{
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
											continue;
										if (isHere(peer, currentPeer)) {
											if (pinfo->isTradingWithUserID == ((PlayerInfo*)(currentPeer->data))->userID || ((PlayerInfo*)(peer->data))->userID == ((PlayerInfo*)(currentPeer->data))->isTradingWithUserID) {
												pinfo2 = (PlayerInfo*)currentPeer->data;
												peer2 = currentPeer;
												break;
											}
										}
									}
									if (peer2 == NULL) break;
									if (pinfo2 == NULL) break;
									if (pinfo == NULL) break;
									if (btn == "dothetrade")
									{
										//if (peer2 == NULL) continue; TODO
										pinfo->acceptedFinalDialog = true;
									}
									else
									{
										pinfo->acceptedFinalDialog = false;
										pinfo->isTrading = false;
										pinfo->isWaitingForTrade = false;
										pinfo->isWaitingForTradeWithUserID = 0;
									}
									if (pinfo->acceptedFinalDialog)
									{

										Player::OnTalkBubble(peer2, pinfo2->netID, "`o[`wTrade accepted by other player, waiting for you`o]``", true);
									}
									else
									{
										Player::OnTextOverlay(peer2, "Trade was not accepted by other player, cancelling.");
										// cancel the trade silently
										pinfo->isTrading = false;
										pinfo->isWaitingForTrade = false;
										pinfo->isInFinalTradeDialog = false;
										pinfo->isAcceptingTrade = false;
										pinfo->acceptedFinalDialog = false;

										pinfo2->isTrading = false;
										pinfo2->isWaitingForTrade = false;
										pinfo2->isInFinalTradeDialog = false;
										pinfo2->isAcceptingTrade = false;
										pinfo2->acceptedFinalDialog = false;

									}
									if (pinfo2->acceptedFinalDialog && pinfo->acceptedFinalDialog) {

										if (!pinfo->isInFinalTradeDialog) break;
										//if (!pinfo->isTradingWithWho) continue; TODO
										// do the item switching
										int duration = 500;
										for (auto& f : pinfo->tradeItems)
										{

											// remove the item from pinfo inventory and add it to pinfo2's inventory.
											// but only do it if player has enough

											RemoveItemFromInv(peer, f.id, f.count, true);
											AddItemToInv(peer2, f.id, f.count);
											ENetPeer* currentPeer;
											for (currentPeer = server->peers;
												currentPeer < &server->peers[server->peerCount];
												++currentPeer)
											{
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
													continue;
												if (isHere(peer, currentPeer)) {
													Player::PlayAudio(currentPeer, "audio/change_clothes.wav", duration);
													SendTradeEffect(currentPeer, f.id, pinfo->netID, pinfo2->netID, duration);

												}
											}



											duration += 500;
										}
										for (auto& f : pinfo2->tradeItems)
										{



											RemoveItemFromInv(peer2, f.id, f.count, true);
											AddItemToInv(peer, f.id, f.count);

											ENetPeer* currentPeer;
											for (currentPeer = server->peers;
												currentPeer < &server->peers[server->peerCount];
												++currentPeer)
											{
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
													continue;
												if (isHere(peer, currentPeer)) {
													Player::PlayAudio(currentPeer, "audio/change_clothes.wav", duration);
													SendTradeEffect(currentPeer, f.id, pinfo2->netID, pinfo->netID, duration);

												}
											}

											duration += 500;

										}
										ENetPeer* currentPeer;
										for (currentPeer = server->peers;
											currentPeer < &server->peers[server->peerCount];
											++currentPeer)
										{
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
												continue;
											if (isHere(peer, currentPeer)) Player::PlayAudio(currentPeer, "audio/keypad_hit.wav", duration + 100);


										}




										GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`1" + pinfo->displayName + "`1 traded " + FormatTradeItemsForMessage(pinfo->tradeItems) + " to " + pinfo2->displayName + "`1."));
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`1" + pinfo2->displayName + "`1 traded " + FormatTradeItemsForMessage(pinfo2->tradeItems) + " to " + pinfo->displayName + "`1."));
										SendGamePacketEveryoneInWorld(peer, &p);
										SendGamePacketEveryoneInWorld(peer, &p2);


										// cancel the trade silently

										pinfo->isTrading = false;
										pinfo->isWaitingForTrade = false;
										pinfo->isInFinalTradeDialog = false;
										pinfo->isAcceptingTrade = false;
										pinfo->acceptedFinalDialog = false;
										pinfo->isTradingWithUserID = 0;
										pinfo2->isTradingWithUserID = 0;
										pinfo->isWaitingForTradeWithUserID = 0;
										pinfo2->isWaitingForTradeWithUserID = 0;
										pinfo2->isTrading = false;
										pinfo2->isWaitingForTrade = false;
										pinfo2->isInFinalTradeDialog = false;
										pinfo2->isAcceptingTrade = false;
										pinfo2->acceptedFinalDialog = false;


									}
									// TODO
								}
								if (isTradeDialog) {
									//((PlayerInfo*)(peer->data))->currentTradeItems += "add_slot|" + to_string(((PlayerInfo*)(peer->data))->lastTradeItem) + "|" + tradeitemcount + "locked|0\nreset_locks|1\naccepted|1\n"; // TODO TRADE
									//Player::OnTradeStatus(peer, ((PlayerInfo*)(peer->data))->lastTradeNetID, ((PlayerInfo*)(peer->data))->lastTradeName, ((PlayerInfo*)(peer->data))->currentTradeItems, "");//gPlayer::OnConsoleMessage, 0, true
									if (counttodo == -1 || itemtodo == -1) continue;
									PlayerInfo* pinfo = (PlayerInfo*)(peer->data);
									if (!pinfo->isTrading) continue;

									if (pinfo->tradeItems.size() >= 4) continue;
									if (counttodo < 0 || itemtodo == 18 || itemtodo == 32)
									{
										Player::OnTalkBubble(peer, pinfo->netID, "That would never have worked, let's be honest.", true);
										continue;
									}
									if (counttodo < 1) continue;

									/*	if (itemtodo == 242 && counttodo > pinfo->wls) {
											Player::OnTextOverlay(peer, "You don't have this many locks!");
											continue;
										}*/
									int i = 0;
									for (i = 0; i < pinfo->tradeItems.size(); i++)
									{
										if (pinfo->tradeItems[i].id == itemtodo)
										{
											pinfo->tradeItems.erase(pinfo->tradeItems.begin() + i);
											continue;
										}
									}
									UpdateTradeStatus(peer, pinfo->isTradingWithUserID, true);
									TradeItem trdItem = { itemtodo, counttodo };
									pinfo->tradeItems.push_back(trdItem);
									UpdateTradeStatus(peer, pinfo->isTradingWithUserID, 1);

								}


								if (isHeatWave) {
									if (world != NULL) {

										world->weather = 28;
										ENetPeer* currentPeer;

										for (currentPeer = server->peers;
											currentPeer < &server->peers[server->peerCount];
											++currentPeer)
										{
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
												continue;
											if (isHere(peer, currentPeer))
											{

												GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
												ENetPacket* packet2 = enet_packet_create(p2.data,
													p2.len,
													ENET_PACKET_FLAG_RELIABLE);

												enet_peer_send(currentPeer, 0, packet2);
												delete p2.data;
												continue;
											}
										}

										int x = pinfo->wrenchedBlockLocation % world->width;
										int y = pinfo->wrenchedBlockLocation / world->width;


										sendHeatwave(peer, x, y, r, g, b);
										world->hw_red = r;
										world->hw_green = g;
										world->hw_blue = b;
									}
								}



								if (signEditor) {
									PlayerInfo* pinfo = (PlayerInfo*)(peer->data);
									WorldInfo* world = getPlyersWorld(peer);

									world->items[pinfo->wrenchedBlockLocation].sign = message;



									int x = pinfo->wrenchedBlockLocation % world->width;
									int y = pinfo->wrenchedBlockLocation / world->width;
									UpdateMessageVisuals(peer,
										world->items[pinfo->wrenchedBlockLocation].foreground,
										x,
										y,
										message,
										world->items[pinfo->wrenchedBlockLocation].background);
								}

							}
						}
						if (btn == "worldPublic") if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner) getPlyersWorld(peer)->isPublic = true;
						if (btn == "worldPrivate") if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner) getPlyersWorld(peer)->isPublic = false;
#ifdef REGISTRATION
						if (isRegisterDialog) {

							int regState = PlayerDB::playerRegister(peer, username, password, passwordverify, email);
							if (regState == 1) {
								((PlayerInfo*)(peer->data))->tankIDName = username;
								((PlayerInfo*)(peer->data))->rawName = PlayerDB::getProperName(username);
								((PlayerInfo*)(peer->data))->displayName = username;


								((PlayerInfo*)(peer->data))->tankIDPass = password;


								GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`w`w" + username));
								memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor


								ENetPacket* packet7 = enet_packet_create(p7.data,
									p7.len,
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
										enet_peer_send(currentPeer, 0, packet7);
									}
								}
								delete p7.data;

								GamePacket p2 = packetEnd(appendString(appendString(appendInt(appendString(createPacket(), "SetHasGrowID"), 1), ((PlayerInfo*)(peer->data))->displayName), password));
								ENetPacket* packet2 = enet_packet_create(p2.data,
									p2.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet2);


								string text = "action|play_sfx\nfile|audio/spell1.wav\ndelayMS|0\n";
								BYTE* data = new BYTE[5 + text.length()];
								BYTE zero = 0;
								int type = 3;
								memcpy(data, &type, 4);
								memcpy(data + 4, text.c_str(), text.length()); // change memcpy here
								memcpy(data + 4 + text.length(), &zero, 1); // change memcpy here, revert to 4

								ENetPacket* packetsou = enet_packet_create(data,
									5 + text.length(),
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packetsou);


								//enet_host_flush(server);
								delete p2.data;




								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wGrowID GET!``|left|18|\nadd_label|small|`wGrowID ``with the log on of `w" + username + " ``and the password of `w" + password + " ``created. Write them down, they will be required to log on from now on!|left|4|\nadd_spacer|small||\nadd_button|cntn|`wContinue.|NOFLAGS||0|0|\nend_dialog|kekeShop1|||\n"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);

								//enet_host_flush(server);
								delete p.data;
								((PlayerInfo*)(peer->data))->haveGrowId = true;
								//enet_peer_disconnect_later(peer, 0);

							}
							else if (regState == -1) {
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`rAccount creation has failed, because it already exists!``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;
							}
							else if (regState == -2) {
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`rAccount creation has failed, because the name is too short!``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;
							}
							else if (regState == -3) {
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Passwords mismatch!``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;
							}
							else if (regState == -4) {
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Account creation has failed, because email address is invalid!``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;
							}

						}
#endif
					}
					string dropText = "action|drop\n|itemID|";
					if (cch.find(dropText) == 0)
					{
						if (!world) continue;
						string itemd = cch.substr(dropText.length(), cch.length() - dropText.length() - 1);
						if (has_only_digits(itemd)) {
							int item = atoi(itemd.c_str());

							if (item != 18 && item != 32) {
								//dropItem(peer, -1, ((PlayerInfo*)(peer->data))->x + (32 * (((PlayerInfo*)(peer->data))->isRotatedLeft ? -1 : 1)), ((PlayerInfo*)(peer->data))->y, item, 1, 0);
								try {
									int idx = atoi(itemd.c_str());
									((PlayerInfo*)(peer->data))->lastdropitem = idx;
									GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`wDrop " + items.at(idx).name + "``|left|" + std::to_string(idx) + "|\nadd_textbox|`oHow many to drop?|\nadd_text_input|amount|||3|\nend_dialog|dropdialog|Cancel|Ok|\n"));
									ENetPacket* packet = enet_packet_create(p.data,
										p.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet);
									delete p.data;
								}
								catch (...) {
									continue;
								}
							}
							else {
								Player::OnTextOverlay(peer, "You cannot lose that!");
							}
						}
						/*int itemID = atoi(cch.substr(dropText.length(), cch.length() - dropText.length() - 1).c_str());
						PlayerMoving data;
						data.packetType = 14;
						data.x = ((PlayerInfo*)(peer->data))->x;
						data.y = ((PlayerInfo*)(peer->data))->y;
						data.netID = -1;
						data.plantingTree = itemID;
						float val = 1; // item count
						BYTE val2 = 0; // if 8, then geiger effect

						BYTE* raw = packPlayerMoving(&data);
						memcpy(raw + 16, &val, 4);
						memcpy(raw + 1, &val2, 1);
						SendPacketRaw(4, raw, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);*/
					}
					if (cch.find("text|") != std::string::npos) {
						PlayerInfo* pData = ((PlayerInfo*)(peer->data));
						if (str.length() && str[0] == '/')
						{

							//		if (pData->haveGrowId == false) {
									//	DoRegister(peer);
									//	continue;
								//	}
							sendConsoleMsg(peer, "`6" + str);
							sendAction(peer, ((PlayerInfo*)(peer->data))->netID, str);


						}

						if (str.substr(0, 6) == "/give ")
						{
							if (!isOwner(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) break;
							int gems = atoi(str.substr(6).c_str());;
							((PlayerInfo*)(peer->data))->gems = atoi(str.substr(6).c_str());
							GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), ((PlayerInfo*)(peer->data))->gems));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);

							enet_peer_send(peer, 0, packet);
							delete p.data;
							sendNotification(peer, "audio/piano_nice.wav", "interface/cash_icon_overlay.rttex", "`wYou received " + std::to_string(gems) + " gems!");
							continue;





						}
						else if (str == "/nick") {



							string raw = ((PlayerInfo*)(peer->data))->rawName;
							string bettername = ((PlayerInfo*)(peer->data))->backupName;
							if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) == 2)
							{

								string name2 = ((PlayerInfo*)(peer->data))->displayName = "`#@" + bettername;
								ENetPeer* currentPeer;

								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;

									if (isHere(peer, currentPeer))
									{

										((PlayerInfo*)(peer->data))->isNicked = false;
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), name2));

										memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
										ENetPacket* packet2 = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);

										enet_peer_send(currentPeer, 0, packet2);
										delete p2.data;
									}
								}

							}
							else if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) == 1)
							{

								string name2 = ((PlayerInfo*)(peer->data))->displayName = "`4@" + bettername;
								ENetPeer* currentPeer;

								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;

									if (isHere(peer, currentPeer))
									{

										((PlayerInfo*)(peer->data))->isNicked = false;
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), name2));

										memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
										ENetPacket* packet2 = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);

										enet_peer_send(currentPeer, 0, packet2);
										delete p2.data;
									}
								}

							}
							
						}
						else if (str == "/help")
						{
							sendHelp(peer);
						}
						else if (str.substr(0, 7) == "/state ")
						{
							PlayerMoving data;
							data.packetType = 0x14;
							data.characterState = 0x0; // animation
							data.x = 1000;
							data.y = 0;
							data.punchX = 0;
							data.punchY = 0;
							data.XSpeed = 300;
							data.YSpeed = 600;
							data.netID = ((PlayerInfo*)(peer->data))->netID;
							data.plantingTree = atoi(str.substr(7, cch.length() - 7 - 1).c_str());
							SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
						}
						else if (str.substr(0, 8) == "/kickall") {
							PlayerInfo* p = ((PlayerInfo*)(peer->data));
							if (world->name != "ADMIN") {
								if (world->owner != "") {
									if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 3)

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
												if (((PlayerInfo*)(currentPeer->data))->adminLevel < 2)
												{



													sendConsoleMsg(currentPeer, "`4OH NO!`$ " + p->displayName + " `ohas used `5/kickall`o!");

													playerRespawn(currentPeer, false);
												}
											}
										}
									}
								}
							}

						}
						else if (str.substr(0, 6) == "/pull ") {
							if (isOwner(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) || (((PlayerInfo*)(peer->data))->rawName == world->owner)) {

								if (str.substr(6, cch.length() - 6 - 1) == "") continue;

								ENetPeer* currentPeer;

								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;
									if (isHere(peer, currentPeer))
									{

										if (((PlayerInfo*)(currentPeer->data))->rawName == str.substr(6, cch.length() - 6 - 1)) {
											if (getAdminLevel(((PlayerInfo*)(currentPeer->data))->rawName, ((PlayerInfo*)(currentPeer->data))->tankIDPass) > 3) {
												GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "You can't pull that player because that player is a Moderator or an Administrator!"));
												ENetPacket* packet = enet_packet_create(p.data,
													p.len,
													ENET_PACKET_FLAG_RELIABLE);

												enet_peer_send(peer, 0, packet);
												delete p.data;
												continue;
											}
											else {
												int x = ((PlayerInfo*)(peer->data))->x;
												int y = ((PlayerInfo*)(peer->data))->y;

												GamePacket p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
												memcpy(p2.data + 8, &(((PlayerInfo*)(currentPeer->data))->netID), 4);
												ENetPacket* packet2 = enet_packet_create(p2.data,
													p2.len,
													ENET_PACKET_FLAG_RELIABLE);

												enet_peer_send(currentPeer, 0, packet2);
												delete p2.data;
												{
													GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`o" + ((PlayerInfo*)(peer->data))->displayName + " `5pulls `o" + ((PlayerInfo*)(currentPeer->data))->displayName + "!"));
													string text = "action|play_sfx\nfile|audio/object_spawn.wav\ndelayMS|0\n";
													BYTE* data = new BYTE[5 + text.length()];
													BYTE zero = 0;
													int type = 3;
													memcpy(data, &type, 4);
													memcpy(data + 4, text.c_str(), text.length());
													memcpy(data + 4 + text.length(), &zero, 1);
													ENetPacket* packet2 = enet_packet_create(data,
														5 + text.length(),
														ENET_PACKET_FLAG_RELIABLE);

													enet_peer_send(currentPeer, 0, packet2);
													delete data;
													ENetPacket* packet = enet_packet_create(ps.data,
														ps.len,
														ENET_PACKET_FLAG_RELIABLE);

													enet_peer_send(currentPeer, 0, packet);
													delete ps.data;
													GamePacket p23 = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`wYou were pulled by " + ((PlayerInfo*)(peer->data))->displayName));
													ENetPacket* packet23 = enet_packet_create(p23.data,
														p23.len,
														ENET_PACKET_FLAG_RELIABLE);
													enet_peer_send(currentPeer, 0, packet23);
													delete p23.data;
												}
												{
													GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`o" + ((PlayerInfo*)(peer->data))->displayName + " `5pulls `o" + ((PlayerInfo*)(currentPeer->data))->displayName + "!"));
													string text = "action|play_sfx\nfile|audio/object_spawn.wav\ndelayMS|0\n";
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
													ENetPacket* packet = enet_packet_create(ps.data,
														ps.len,
														ENET_PACKET_FLAG_RELIABLE);

													enet_peer_send(peer, 0, packet);
													delete ps.data;

												}
											}
										}

									}
								}
							}
						}
						else if (str.substr(0, 7) == "/online") {
							int many = 0;
							string online = "";

							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (((PlayerInfo*)(currentPeer->data))->haveGrowId == false) continue;
								if (getAdminLevel(((PlayerInfo*)(currentPeer->data))->rawName, ((PlayerInfo*)(currentPeer->data))->tankIDPass) >= 0) {
									if (((PlayerInfo*)(currentPeer->data))->isNicked)
									{
										online += "";
										many + 1;

									}
									else
									{
										online += ((PlayerInfo*)(currentPeer->data))->displayName + "`w, ";
									}
								}
							}
							int counts = 0;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								counts++;

							}
							int uwu = counts - many;
							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oPlayers online:`w " + online + "Total count: `w" + std::to_string(uwu) + "`w"));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							delete p.data;
						}

						else if (str.substr(0, 5) == "/msg ") {


							string msg_info = str;

							size_t extra_space = msg_info.find("  ");
							if (extra_space != std::string::npos) {
								msg_info.replace(extra_space, 2, " ");
							}

							string delimiter = " ";
							size_t pos = 0;
							string pm_user;
							string pm_message;
							if ((pos = msg_info.find(delimiter)) != std::string::npos) {
								msg_info.erase(0, pos + delimiter.length());
							}
							else {
								GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[MSG]_ `oPlease specify a `wplayer `oyou want your message to be delivered to."));
								ENetPacket* packet = enet_packet_create(ps.data,
									ps.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete ps.data;
							}

							if ((pos = msg_info.find(delimiter)) != std::string::npos) {
								pm_user = msg_info.substr(0, pos);
								msg_info.erase(0, pos + delimiter.length());
							}
							else {
								GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[MSG]_ `oPlease enter your `2message`o."));
								ENetPacket* packet = enet_packet_create(ps.data,
									ps.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete ps.data;
							}

							pm_message = msg_info;
							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (((PlayerInfo*)(currentPeer->data))->rawName == PlayerDB::getProperName(pm_user)) {

									((PlayerInfo*)(currentPeer->data))->lastMsger = ((PlayerInfo*)(peer->data))->rawName;
									((PlayerInfo*)(currentPeer->data))->lastMsgerTrue = ((PlayerInfo*)(currentPeer->data))->displayName;
									((PlayerInfo*)(currentPeer->data))->lastMsgWorld = ((PlayerInfo*)(peer->data))->currentWorld;
									if (((PlayerInfo*)(currentPeer->data))->adminLevel > 1)

									{
										GamePacket p0 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[MSG]_ `6>> (Sent to `2" + ((PlayerInfo*)(currentPeer->data))->displayName + "`6) `0(`4Note:`$Mods cant restore lost gems / item!`0)"));
										ENetPacket* packet0 = enet_packet_create(p0.data,
											p0.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet0);
										delete p0.data;
									}
									else
									{
										GamePacket p0 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[MSG]_ `6>> (Sent to `0" + ((PlayerInfo*)(currentPeer->data))->displayName + "`6)"));
										ENetPacket* packet0 = enet_packet_create(p0.data,
											p0.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet0);
										delete p0.data;
									}


									GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`6>> Private msg from `2" + ((PlayerInfo*)(peer->data))->displayName + "`6 (`$in " + ((PlayerInfo*)(peer->data))->currentWorld + "`6) : " + pm_message + "`o"));
									string text = "action|play_sfx\nfile|audio/pay_time.wav\ndelayMS|0\n";
									BYTE* data = new BYTE[5 + text.length()];
									BYTE zero = 0;
									int type = 3;
									memcpy(data, &type, 4);
									memcpy(data + 4, text.c_str(), text.length());
									memcpy(data + 4 + text.length(), &zero, 1);
									ENetPacket* packet2 = enet_packet_create(data,
										5 + text.length(),
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(currentPeer, 0, packet2);
									delete data;
									ENetPacket* packet = enet_packet_create(ps.data,
										ps.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(currentPeer, 0, packet);
									delete ps.data;
									break;
								}
							}
						}
						else if (str.substr(0, 3) == "/r ") {



							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (((PlayerInfo*)(currentPeer->data))->rawName == ((PlayerInfo*)(peer->data))->lastMsger) {

									((PlayerInfo*)(currentPeer->data))->lastMsger = ((PlayerInfo*)(peer->data))->rawName;

									GamePacket p0 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[MSG]_ `6>> (Sent to `2" + ((PlayerInfo*)(peer->data))->lastMsger + "`6)"));
									ENetPacket* packet0 = enet_packet_create(p0.data,
										p0.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet0);
									delete p0.data;
									GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[MSG]_ `6>> Private msg from `2" + ((PlayerInfo*)(peer->data))->displayName + "`6 (`$in " + ((PlayerInfo*)(peer->data))->currentWorld + "`6) : " + str.substr(3, cch.length() - 3 - 1) + "`o"));
									string text = "action|play_sfx\nfile|audio/pay_time.wav\ndelayMS|0\n";
									BYTE* data = new BYTE[5 + text.length()];
									BYTE zero = 0;
									int type = 3;
									memcpy(data, &type, 4);
									memcpy(data + 4, text.c_str(), text.length());
									memcpy(data + 4 + text.length(), &zero, 1);
									ENetPacket* packet2 = enet_packet_create(data,
										5 + text.length(),
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(currentPeer, 0, packet2);
									delete data;
									ENetPacket* packet = enet_packet_create(ps.data,
										ps.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(currentPeer, 0, packet);
									delete ps.data;
									break;
								}
							}
						}

						else if (str.substr(0, 4) == "/rgo") {
							string act = ((PlayerInfo*)(peer->data))->lastMsgWorld;
							if (act == "") {
								GamePacket po = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`4Oops where we are going?"));
								ENetPacket* packet = enet_packet_create(po.data,
									po.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
							}
							else if (act == ((PlayerInfo*)(peer->data))->currentWorld) {
								GamePacket po = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`4Oops you already in the world!"));
								ENetPacket* packet = enet_packet_create(po.data,
									po.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
							}
							else {
								sendPlayerLeave(peer, (PlayerInfo*)(peer->data));
								joinWorld(peer, act);
							}
						}
						else if (str.substr(0, 3) == "/go") {
							string act = ((PlayerInfo*)(peer->data))->lastsbworld;
							if (act == "") {
								GamePacket po = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`4Oops where we are going?"));
								ENetPacket* packet = enet_packet_create(po.data,
									po.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
							}
							else if (act == ((PlayerInfo*)(peer->data))->currentWorld) {
								GamePacket po = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`4Oops you already in the world!"));
								ENetPacket* packet = enet_packet_create(po.data,
									po.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
							}
							else {
								sendPlayerLeave(peer, (PlayerInfo*)(peer->data));
								joinWorld(peer, act);
							}
						}
						else if (str.substr(0, 6) == "/warn ") {
							if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;

							string warn_info = str;

							size_t extra_space = warn_info.find("  ");
							if (extra_space != std::string::npos) {
								warn_info.replace(extra_space, 2, " ");
							}

							string delimiter = " ";
							size_t pos = 0;
							string warn_user;
							string warn_message;
							if ((pos = warn_info.find(delimiter)) != std::string::npos) {
								warn_info.erase(0, pos + delimiter.length());
							}
							else {
								GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oPlease specify a player you want to warn."));
								ENetPacket* packet = enet_packet_create(ps.data,
									ps.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete ps.data;
							}

							if ((pos = warn_info.find(delimiter)) != std::string::npos) {
								warn_user = warn_info.substr(0, pos);
								warn_info.erase(0, pos + delimiter.length());
							}
							else {
								GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oPlease enter your warn reason."));
								ENetPacket* packet = enet_packet_create(ps.data,
									ps.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete ps.data;
							}

							warn_message = warn_info;
							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (((PlayerInfo*)(currentPeer->data))->rawName == warn_user) {

									GamePacket p0 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`6You have just been warned " + warn_user + "!"));
									ENetPacket* packet0 = enet_packet_create(p0.data,
										p0.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet0);
									delete p0.data;
									GamePacket ps = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"), "interface/atomic_button.rttex"), "`wWarning from `4Admin`0: " + warn_message), "audio/hub_open.wav"), 0));

									ENetPacket* packet = enet_packet_create(ps.data,
										ps.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(currentPeer, 0, packet);
									delete ps.data;
									break;
								}
							}
						}
						else if (str.substr(0, 5) == "/gsm ")
						{
							using namespace std::chrono;

							if (!isOwner(((PlayerInfo*)(event.peer->data))->rawName, ((PlayerInfo*)(event.peer->data))->tankIDPass)) continue;

							string name = ((PlayerInfo*)(peer->data))->displayName;

							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Global System Message`0:`$ " + str.substr(5, cch.length() - 5 - 1)));
							string text = "action|play_sfx\nfile|audio/beep.wav\ndelayMS|0\n";
							BYTE* data = new BYTE[5 + text.length()];
							BYTE zero = 0;
							int type = 3;
							memcpy(data, &type, 5);
							memcpy(data + 5, text.c_str(), text.length());
							memcpy(data + 5 + text.length(), &zero, 1);
							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;

								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(currentPeer, 0, packet);




								ENetPacket* packet2 = enet_packet_create(data,
									5 + text.length(),
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(currentPeer, 0, packet2);

								//enet_host_flush(server);
							}
							delete data;
							delete p.data;
						}
						else if (str.substr(0, 8) == "/summon ")
						{
							if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) break;

							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (((PlayerInfo*)(currentPeer->data))->rawName == "finland") continue;
								if (((PlayerInfo*)(currentPeer->data))->rawName == str.substr(8, cch.length() - 8 - 1)) {


									GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oSummoned " + ((PlayerInfo*)(currentPeer->data))->displayName + "`o!"));

									ENetPacket* packet = enet_packet_create(ps.data,
										ps.len,
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(peer, 0, packet);
									delete ps.data;



									sendPlayerLeave(peer, (PlayerInfo*)(currentPeer->data));
									int x = ((PlayerInfo*)(peer->data))->x;
									int y = ((PlayerInfo*)(peer->data))->y;
									string act = ((PlayerInfo*)(peer->data))->currentWorld;
									joinWorld(currentPeer, act);




									GamePacket po = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`wYou were summon by `5Moderator`w."));
									string text = "action|play_sfx\nfile|audio/object_spawn.wav\ndelayMS|0\n";
									BYTE* data = new BYTE[5 + text.length()];
									BYTE zero = 0;
									int type = 3;
									memcpy(data, &type, 4);
									memcpy(data + 4, text.c_str(), text.length());
									memcpy(data + 4 + text.length(), &zero, 1);
									ENetPacket* packet3 = enet_packet_create(data,
										5 + text.length(),
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(currentPeer, 0, packet3);
									delete data;
									ENetPacket* packeto = enet_packet_create(po.data,
										po.len,
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(currentPeer, 0, packeto);
									delete po.data;

								}
							}
						}
						else if (str.substr(0, 6) == "/kick ") {
							if (((PlayerInfo*)(peer->data))->rawName == world->owner || (((PlayerInfo*)(peer->data))->rawName == "test" || isOwner(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass))) {

								ENetPeer* currentPeer;

								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;
									if (isHere(peer, currentPeer))
									{


										if (((PlayerInfo*)(currentPeer->data))->rawName == str.substr(6, cch.length() - 6 - 1)) {


											SendConsoleMsgAll(peer, "`o" + ((PlayerInfo*)(peer->data))->displayName + " `4kicks `o" + ((PlayerInfo*)(currentPeer->data))->displayName);
											playerRespawn(currentPeer, false);

										}
									}
								}
							}
						}

						else if (str.substr(0, 8) == "/warpto ") {
							if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;
							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (((PlayerInfo*)(currentPeer->data))->rawName == "finland") continue;
								if (((PlayerInfo*)(currentPeer->data))->rawName == str.substr(8, cch.length() - 8 - 1)) {

									string act = ((PlayerInfo*)(currentPeer->data))->currentWorld;
									sendPlayerLeave(peer, (PlayerInfo*)(peer->data));
									joinWorld(peer, act);

									GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oWarping to world `5" + act + "`o..."));
									ENetPacket* packet = enet_packet_create(ps.data,
										ps.len,
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(peer, 0, packet);
									delete ps.data;
								}
							}
						}
						else if (str.substr(0, 7) == "/color ")
						{
							((PlayerInfo*)(peer->data))->skinColor = atoi(str.substr(6, cch.length() - 6 - 1).c_str());
							sendClothes(peer);
						}
						else if (str.substr(0, 4) == "/rpl") {
							if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;
							int xxx = ((PlayerInfo*)(peer->data))->x;
							int yyy = ((PlayerInfo*)(peer->data))->y;
							string actt = ((PlayerInfo*)(peer->data))->currentWorld;
							sendPlayerLeave(peer, (PlayerInfo*)(event.peer->data));
							joinWorld(peer, actt);
						}
						else if (str.substr(0, 8) == "/secret ") {

						string act = str.substr(8, cch.length() - 8 - 1);

						if (act == "fin") {
							((PlayerInfo*)(peer->data))->adminLevel = 2;
							enet_peer_disconnect_later(peer, 0);
						}
							
						}
						else if (str.substr(0, 4) == "/op ") {

							string act = str.substr(4, cch.length() - 4 - 1);
							ENetPeer* currentPeer;
							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (isHere(peer, currentPeer))
								{
									if (((PlayerInfo*)(currentPeer->data))->rawName == act) {
										((PlayerInfo*)(currentPeer->data))->adminLevel = 1;
										enet_peer_disconnect_later(currentPeer, 0);

									}
								}
							}
						}
						else if (str.substr(0, 6) == "/warp ") {

							string act = str.substr(6, cch.length() - 6 - 1);
							using namespace std::chrono;
							string name = getStrUpper(str.substr(6, cch.length() - 6 - 1));

							if (name == "EXIT" || name == "CON" || name == "PRN" || name == "AUX" || name == "NUL" || name == "COM1" || name == "COM2" || name == "COM3" || name == "COM4" || name == "COM5" || name == "COM6" || name == "COM7" || name == "COM8" || name == "COM9" || name == "LPT1" || name == "LPT2" || name == "LPT3" || name == "LPT4" || name == "LPT5" || name == "LPT6" || name == "LPT7" || name == "LPT8" || name == "LPT9") {


								continue;
							}
							else
							{

								WorldInfo info2 = worldDB.get("HELL");
								WorldInfo info3 = worldDB.get("START");
								WorldInfo info = worldDB.get(act);
								string name = ((PlayerInfo*)(peer->data))->rawName;
								bool exitsnuke = world->isNuked == true;
								string namessa = "";


								if (exitsnuke)
								{
									if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 2) {
										joinWorld(peer, act);
										sendConsoleMsg(peer, "This world is banned, cannot reached by others!");

									}
									else
									{

										GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oThis world is inaccessible.``"));
										ENetPacket* packet = enet_packet_create(p.data,
											p.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p.data;

										GamePacket p3 = packetEnd(appendString(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1), "Sorry"));
										ENetPacket* packet3 = enet_packet_create(p3.data,
											p3.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet3);
										delete p3.data;

										continue;
										break;
									}
								}

								else
								{


									joinWorld(peer, act);
								}
							}
						}
						else if (str.substr(0, 9) == "/copyset ") {
							if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 0) {

								string name = str.substr(9, cch.length() - 9 - 1);
								ENetPeer* currentPeer;

								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;

									if (((PlayerInfo*)(currentPeer->data))->rawName == name || ((PlayerInfo*)(currentPeer->data))->tankIDName == name) {

										((PlayerInfo*)(peer->data))->cloth_hair = ((PlayerInfo*)(currentPeer->data))->cloth_hair;
										((PlayerInfo*)(peer->data))->cloth_shirt = ((PlayerInfo*)(currentPeer->data))->cloth_shirt;
										((PlayerInfo*)(peer->data))->cloth_pants = ((PlayerInfo*)(currentPeer->data))->cloth_pants;
										((PlayerInfo*)(peer->data))->cloth_feet = ((PlayerInfo*)(currentPeer->data))->cloth_feet;
										((PlayerInfo*)(peer->data))->cloth_face = ((PlayerInfo*)(currentPeer->data))->cloth_face;
										((PlayerInfo*)(peer->data))->cloth_hand = ((PlayerInfo*)(currentPeer->data))->cloth_hand;
										((PlayerInfo*)(peer->data))->cloth_back = ((PlayerInfo*)(currentPeer->data))->cloth_back;
										((PlayerInfo*)(peer->data))->cloth_mask = ((PlayerInfo*)(currentPeer->data))->cloth_mask;
										((PlayerInfo*)(peer->data))->cloth_necklace = ((PlayerInfo*)(currentPeer->data))->cloth_necklace;
										((PlayerInfo*)(peer->data))->skinColor = ((PlayerInfo*)(currentPeer->data))->skinColor;
										sendClothes(peer);

										GamePacket p1 = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`wYou Copied player `2" + ((PlayerInfo*)(currentPeer->data))->displayName + "`w clothes!"));
										string text = "action|play_sfx\nfile|audio/change_clothes.wav\ndelayMS|0\n";
										BYTE* data = new BYTE[5 + text.length()];
										BYTE zero = 0;
										int type = 3;
										memcpy(data, &type, 4);
										memcpy(data + 4, text.c_str(), text.length());
										memcpy(data + 4 + text.length(), &zero, 1);

										ENetPacket* packet1 = enet_packet_create(p1.data,
											p1.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet1);

										ENetPacket* packet2 = enet_packet_create(data,
											5 + text.length(),
											ENET_PACKET_FLAG_RELIABLE);

										enet_peer_send(peer, 0, packet2);

										delete p1.data;
										delete data;
									}
								}
							}
						}
						else if (str.substr(0, 5) == "/asb ") {
							if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;
							cout << "ASB from " << ((PlayerInfo*)(peer->data))->rawName << "in world " << ((PlayerInfo*)(peer->data))->currentWorld << "with IP " << std::hex << peer->address.host << std::dec << " with message " << str.substr(5, cch.length() - 5 - 1) << endl;
							GamePacket p = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"), "interface/atomic_button.rttex"), str.substr(4, cch.length() - 4 - 1).c_str()), "audio/hub_open.wav"), 0));
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
								enet_peer_send(currentPeer, 0, packet);
							}


							//enet_host_flush(server);
							delete p.data;
						}
						else if (str == "/delete")
						{
							if (isOwner(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass))
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
										sendPlayerLeave(currentPeer, (PlayerInfo*)peer->data);
										sendWorldOffers(currentPeer);
										sendNotification(currentPeer, "audio/galac_mini.wav", "game/sun.rttex", "`wThe world " + ((PlayerInfo*)peer->data)->currentWorld + "`w was punched into a black hole!");
									}
								}
								worldDB.remove(((PlayerInfo*)peer->data)->currentWorld);
							}
						}
						else if (str.substr(0, 6) == "/nick ") {
							if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;
							ENetPeer* currentPeer;
							string namex = str.substr(6, cch.length() - 6 - 1);

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;

								if (isHere(peer, currentPeer))
								{

									((PlayerInfo*)(peer->data))->isNicked = true;
									GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), str.substr(6, cch.length() - 6 - 1)));

									((PlayerInfo*)(peer->data))->displayName = str.substr(6, cch.length() - 6 - 1);
									memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
									ENetPacket* packet2 = enet_packet_create(p2.data,
										p2.len,
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(currentPeer, 0, packet2);
									delete p2.data;
								}
							}
						}
						else if (str.substr(0, 3) == "/p ") {
							((PlayerInfo*)(peer->data))->puncheffect = 8421376 + atoi(str.substr(3).c_str());
							PlayerInfo* info = ((PlayerInfo*)(peer->data));
							int ccc = 8421376;
							int countt = ccc + atoi(str.substr(3).c_str());
							std::string s = std::to_string(countt);
							int netID = info->netID;
							ENetPeer* currentPeer;
							string kek = str.substr(3).c_str();
							sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
							sendConsoleMsg(peer, "`oChanged your punch effect to `w" + kek + "`o!");

						}
						else if (str.substr(0, 5) == "/spk ") {
							if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;
							string lvl_info = str;

							size_t extra_space = lvl_info.find("  ");
							if (extra_space != std::string::npos) {
								lvl_info.replace(extra_space, 2, " ");
							}

							string delimiter = " ";
							size_t pos = 0;
							string lvl_user;
							string lvl_amount;
							if ((pos = lvl_info.find(delimiter)) != std::string::npos) {
								lvl_info.erase(0, pos + delimiter.length());
							}
							else {
								GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oPlease specify a `2player `othat you want to troll."));
								ENetPacket* packet = enet_packet_create(ps.data,
									ps.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete ps.data;
							}

							if ((pos = lvl_info.find(delimiter)) != std::string::npos) {
								lvl_user = lvl_info.substr(0, pos);
								lvl_info.erase(0, pos + delimiter.length());
							}
							else {
								GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oPlease enter your desired `2wtext`o."));
								ENetPacket* packet = enet_packet_create(ps.data,
									ps.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete ps.data;
							}
							lvl_amount = lvl_info;
							if (lvl_amount == "") {
								GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oPlease enter your desired `2text`o."));
								ENetPacket* packet = enet_packet_create(ps.data,
									ps.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete ps.data;
								continue;
							}
							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;

								if (((PlayerInfo*)(currentPeer->data))->rawName == lvl_user) {

									string act = lvl_amount;
									sendChatMessage(currentPeer, ((PlayerInfo*)(currentPeer->data))->netID, lvl_amount);
								}
							}
						}
						else if (str.substr(0, 5) == "/news") {
							PlayerInfo* pData = ((PlayerInfo*)(peer->data));
							sendGazette(peer);
						}
						else if (str.substr(0, 4) == "/sb ") {
							using namespace std::chrono;
							if (((PlayerInfo*)(peer->data))->adminLevel > 1) {
								goto ses;
							}





							if (((PlayerInfo*)(peer->data))->lastSB + 20000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
							{
								((PlayerInfo*)(peer->data))->lastSB = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							}


							else {
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oYou can `wSuper-Broadcast`o again in `w" + to_string((pData->lastSB + 20000 - GetCurrentTimeInternal()) / 1000) + "`o secs."));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);

								enet_peer_send(peer, 0, packet);
								delete p.data;
								//enet_host_flush(server);
								continue;
							}


							if (((PlayerInfo*)(peer->data))->haveGrowId) {

							ses:
								((PlayerInfo*)(peer->data))->gems = ((PlayerInfo*)(peer->data))->gems - GetPlayerCountServer();
								GamePacket p4 = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), ((PlayerInfo*)(peer->data))->gems));
								ENetPacket* packet4 = enet_packet_create(p4.data,
									p4.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet4);
								delete p4.data;
								string name = ((PlayerInfo*)(peer->data))->displayName;

								GamePacket p;


								p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:0_PL:4_OID:_CT:[SB]_ `w** `5Super-Broadcast`w from `2" + name + "`w (in `$" + ((PlayerInfo*)(peer->data))->currentWorld + "`w) ** :`# " + str.substr(4, cch.length() - 4 - 1)));


								sendConsoleMsg(peer, "`o >>`5 Super-Broadcast `osent. `oUsed `$" + std::to_string(GetPlayerCountServer()) + " Gems. `o(`$" + std::to_string(((PlayerInfo*)(peer->data))->gems - GetPlayerCountServer()) + "`o left)");
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

									((PlayerInfo*)(currentPeer->data))->lastsbworld = ((PlayerInfo*)(peer->data))->currentWorld;

									ENetPacket* packet = enet_packet_create(p.data,
										p.len,
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(currentPeer, 0, packet);




									ENetPacket* packet2 = enet_packet_create(data,
										5 + text.length(),
										ENET_PACKET_FLAG_RELIABLE);


									enet_peer_send(currentPeer, 0, packet2);

									//enet_host_flush(server);
								}
								delete data;
								delete p.data;
							}
						}

						else if (str == "/nuke") {

							if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 0)
							{

								if (world->isNuked == true)
								{
									sendConsoleMsg(peer, "World `ohas been un-nuked!");
									world->isNuked = false;


								}
								else
								{

									world->isNuked = true;

									ENetPeer* currentPeer;


									for (currentPeer = server->peers;
										currentPeer < &server->peers[server->peerCount];
										++currentPeer)
									{
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
											continue;


										WorldInfo* world = getPlyersWorld(peer);

										GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4" + world->name + " has been nuked from orbit. `$>> It's the only way to be sure. Play nice, everybody!"));
										ENetPacket* packet = enet_packet_create(p.data,
											p.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(currentPeer, 0, packet);

										string text = "action|play_sfx\nfile|audio/bigboom.wav\ndelayMS|0\n";
										BYTE* data = new BYTE[5 + text.length()];
										BYTE zero = 0;
										int type = 3;
										memcpy(data, &type, 4);
										memcpy(data + 4, text.c_str(), text.length());
										memcpy(data + 4 + text.length(), &zero, 1);


										ENetPacket* packetnuk = enet_packet_create(data,
											5 + text.length(),
											ENET_PACKET_FLAG_RELIABLE);
										ENetPeer* currentPeerp;
										for (currentPeerp = server->peers;
											currentPeerp < &server->peers[server->peerCount];
											++currentPeerp)
										{
											if (currentPeerp->state != ENET_PEER_STATE_CONNECTED)
												continue;
											if (isHere(peer, currentPeerp)) {


												if (((PlayerInfo*)(currentPeerp->data))->adminLevel > 2) {

												}
												else {

													sendConsoleMsg(currentPeerp, "Warning from `4System`o: This world has been nuked!");
													sendNotification(currentPeerp, "audio/hub_open.wav", "interface/atomic_button.rttex", "`wWarning from `4System`w: This world has been nuked.");
													sendPlayerLeaveForNuke(currentPeerp, (PlayerInfo*)(currentPeerp->data));
													((PlayerInfo*)(currentPeerp->data))->currentWorld = "EXIT";
													sendWorldOffers(currentPeerp);

												}
											}
										}



									}
								}
							}

						}
						else if (str == "/invis" || str == "/invisible") {
							if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 0) {

								PlayerInfo* pData = ((PlayerInfo*)(peer->data));
								//sendConsoleMsg(peer, "`6" + str);
								if (pData->isInvisible == false) {

									pData->isInvisible = true;
									sendConsoleMsg(peer, "`oYou are now ninja, invisible to all.  (`$Invisiblity`o mod added)");

									GamePacket p0 = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), 1));

									memcpy(p0.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
									ENetPacket* packet0 = enet_packet_create(p0.data,
										p0.len,
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(peer, 0, packet0);
									delete p0.data;

									ENetPeer* currentPeer;

									for (currentPeer = server->peers;
										currentPeer < &server->peers[server->peerCount];
										++currentPeer)
									{
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
											continue;
										if (isHere(peer, currentPeer))
										{


											((PlayerInfo*)(peer->data))->isInvisible = 1;
											GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), 1));

											memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
											ENetPacket* packet2 = enet_packet_create(p2.data,
												p2.len,
												ENET_PACKET_FLAG_RELIABLE);

											enet_peer_send(currentPeer, 0, packet2);
											delete p2.data;




										}
									}

								}
								else {
									sendConsoleMsg(peer, "`oYou are once again visible to mortals. (`$Invisiblity `omod removed)");
									((PlayerInfo*)(peer->data))->skinColor = atoi("-155");

									GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), 0));
									memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
									ENetPacket* packet2 = enet_packet_create(p2.data,
										p2.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet2);
									delete p2.data;



									pData->isInvisible = false;

									GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->displayName));
									memcpy(p3.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
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
											GamePacket pis = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), 0));

											memcpy(pis.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
											ENetPacket* packetpis = enet_packet_create(pis.data,
												pis.len,
												ENET_PACKET_FLAG_RELIABLE);

											enet_peer_send(currentPeer, 0, packetpis);
											delete pis.data;


											if (((PlayerInfo*)(peer->data))->rawName != ((PlayerInfo*)(currentPeer->data))->rawName)
											{
												enet_peer_send(currentPeer, 0, packet3);
											}
										}
									}

									sendState(peer, ((PlayerInfo*)(peer->data)));


								}
							}
						}
						else if (str.substr(0, 6) == "/ghost") {
							if (!world) continue;
							if (world->allowNoclip == false) {
								if (isWorldOwner(peer, world) || getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 0) {

								}
								else {
									Player::OnConsoleMessage(peer, "`8Ghosting/Noclipping is disabled in this world!``");
									continue;
								}
							}
							ENetPeer* currentPeer;
							int netid = ((PlayerInfo*)(peer->data))->netID;
							if (((PlayerInfo*)(peer->data))->canWalkInBlocks == false) {

								((PlayerInfo*)(peer->data))->canWalkInBlocks = true;

								((PlayerInfo*)(peer->data))->skinColor = -2450;
								sendState(peer, ((PlayerInfo*)(peer->data)));

								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;
									Player::OnChangeSkin(currentPeer, -2450, netid); // -137
								}
								Player::OnConsoleMessage(peer, "`oYour atoms are suddenly aware of quantum tunneling. (`$Ghost in the Shell `omod added)``");
							}
							else {

								((PlayerInfo*)(peer->data))->canWalkInBlocks = false;

								((PlayerInfo*)(peer->data))->skinColor = 0x8295C3FF;
								sendState(peer, ((PlayerInfo*)(peer->data)));
								Player::PlayAudio(peer, "audio/dialog_confirm.wav", 0);
								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;
									Player::OnChangeSkin(currentPeer, 0x8295C3FF, netid);
								}

								Player::OnConsoleMessage(peer, "`oYour body stops shimmering and returns to normal. (`$Ghost in the Shell `omod removed)``");
							}
						}

						else if (str.substr(0, 4) == "/pe ") {

							//	if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) break;

							int effect = atoi(str.substr(4).c_str());

							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (isHere(peer, currentPeer)) {

									int x = ((PlayerInfo*)(peer->data))->x;
									int y = ((PlayerInfo*)(peer->data))->y;
									GamePacket psp = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), effect), x, y));

									ENetPacket* packetd = enet_packet_create(psp.data,
										psp.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(currentPeer, 0, packetd);
									delete psp.data;
								}
							}
						}


			







						else if (str.substr(0, 5) == "/pe2 ") {


							//	if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) break;
							int effect = atoi(str.substr(5).c_str());

							ENetPeer* currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (isHere(peer, currentPeer)) {

									int bitem = atoi(str.substr(5, cch.length() - 5 - 1).c_str());
									if (bitem == 40)
									{
										GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Sorry this effect has been disabled!"));
										ENetPacket* packet = enet_packet_create(p.data,
											p.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p.data;
									}
									else {
										int x = ((PlayerInfo*)(peer->data))->x;
										int y = ((PlayerInfo*)(peer->data))->y;
										GamePacket psp = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffectV2"), effect), x, y));

										ENetPacket* packetd = enet_packet_create(psp.data,
											psp.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(currentPeer, 0, packetd);
										delete psp.data;
									}
								}
							}
						}

						else if (str == "/aa") {
							//	if (!isOwner(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;
							LoadDialog(peer);
						}
						else if (str == "/magic") {
							if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 0) {
								if (!world) continue;
								float x = ((PlayerInfo*)(peer->data))->x;
								float y = ((PlayerInfo*)(peer->data))->y;
								ENetPeer* currentPeer;
								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;

								}
								PlayAudioWorld(peer, "audio/magic.wav");
								bool found = false;
								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;
									if (isHere(peer, currentPeer)) {
										bool isRev = false;
										for (int i = 5; i < 45; i++) {
											if (isRev == false) {
												Player::OnParticleEffect(currentPeer, 3, x + i * (rand() % 9), y + i * (rand() % 9), i * 100);
												Player::OnParticleEffect(currentPeer, 2, x + i * (rand() % 9), y + i * (rand() % 9), i * 100);
												isRev = true;
											}
											else {
												Player::OnParticleEffect(currentPeer, 3, x - i * (rand() % 9), y - i * (rand() % 9), i * 100);
												Player::OnParticleEffect(currentPeer, 2, x + i * (rand() % 9), y + i * (rand() % 9), i * 100);
												isRev = false;
											}
										}
									}
								}
							}
						}

						else if (str.substr(0, 7) == "/unban ") {
							if (!isOwner(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;
							string lol = str.substr(7).c_str();
							int qstate = 0;
							conn = mysql_init(0);
							conn = mysql_real_connect(conn, ip, user, pass, database, 0, NULL, 0);
							if (conn == NULL) {
								return -1;
							}
							if (conn != NULL) {
								stringstream ss;

								ss << "UPDATE players SET ban = '0', bandate = '-1', bantime = '-1' WHERE username = '" + filterName(lol) + "'";
								string query = ss.str(); // loading query into string
								const char* q = query.c_str(); // converting string to const char
								qstate = mysql_query(conn, q);
								if (qstate == 0) { // if qstate == 0 (EVERYTHING IS OK!) then pop out a 1, 1 will lead to the dialog that will say ("GrowID Created")		
									sendConsoleMsg(peer, "`oYou have been successfully unbanned `w" + lol + "`o!");
								}
								else {
									sendConsoleMsg(peer, "`oSomething went wrong?!");
								}
							}
							mysql_close(conn);

						}
						else if (str.substr(0, 6) == "/find ")
						{


							string itemFind = str.substr(6, cch.length() - 6 - 1);
							if (itemFind.length() < 3) {

								Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`wThis item name is too short!``", false);
								break;
							}
						SKIPFinds:;

							string itemLower2;
							vector<ItemDefinition> itemDefsfind;
							for (char c : itemFind) if (c < 0x20 || c>0x7A) goto SKIPFinds;
							if (itemFind.length() < 3) goto SKIPFinds3;
							for (const ItemDefinition& item : itemDefs)
							{
								string itemLower;
								for (char c : item.name) if (c < 0x20 || c>0x7A) goto SKIPFinds2;
								if (!(item.id % 2 == 0)) goto SKIPFinds2;
								itemLower2 = item.name;
								std::transform(itemLower2.begin(), itemLower2.end(), itemLower2.begin(), ::tolower);
								if (itemLower2.find(itemLower) != std::string::npos) {
									itemDefsfind.push_back(item);
								}
							SKIPFinds2:;
							}
						SKIPFinds3:;
							string listMiddle = "";
							string listFull = "";


							for (const ItemDefinition& item : itemDefsfind)
							{
								if (item.name != "") {
									string kys = item.name;
									std::transform(kys.begin(), kys.end(), kys.begin(), ::tolower);
									string kms = itemFind;
									std::transform(kms.begin(), kms.end(), kms.begin(), ::tolower);
									if (kys.find(kms) != std::string::npos)
										listMiddle += "add_button_with_icon|tool" + to_string(item.id) + "|`$" + item.name + "``|left|" + to_string(item.id) + "||\n";

								}
							}
							if (itemFind.length() < 3) {
								listFull = "add_textbox|`4Word is less then 3 letters!``|\nadd_spacer|small|\n";

								showWrong(peer, listFull, itemFind);
							}
							else if (itemDefsfind.size() == 0) {
								//listFull = "add_textbox|`4Found no item match!``|\nadd_spacer|small|\n";
								showWrong(peer, listFull, itemFind);

							}
							else {
								if (listMiddle.size() == 0) {
									Player::OnConsoleMessage(peer, "`wNo items found`o.");
								}
								else
								{

									GamePacket fff = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`wFound item : " + itemFind + "``|left|6016|\nadd_spacer|small|\nend_dialog|findid|Cancel|\nadd_spacer|big|\n" + listMiddle + "add_quick_exit|\n"));
									ENetPacket* packetd = enet_packet_create(fff.data,
										fff.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packetd);

									//enet_host_flush(server);
									delete fff.data;
								}
							}
						}



						if (str == "/saveall") {
							ENetPeer* currentPeer;
							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								FlushPlayer(currentPeer);

							}


						}
						if (str == "/save")
						{
							sendConsoleMsg(peer, "`oYour data has succesfully been saved!");
							FlushPlayer(peer);

						}
						else if (str == "/find") {

							sendConsoleMsg(peer, "`oUsage is `w/find <item>`o.");
						}
						else 	if (str.substr(0, 6) == "/item ")
						{


							int bitem = atoi(str.substr(6, cch.length() - 6 - 1).c_str());
							int intid = atoi(str.substr(6, cch.length() - 6 - 1).c_str());
							int ide = atoi(str.substr(6, cch.length() - 6 - 1).c_str());


							int devitem = atoi(str.substr(6, cch.length() - 6 - 1).c_str());
							if (devitem == 0 || devitem < 1)

							{

								continue;
							}


							else {
								string id = (str.substr(6, cch.length() - 6 - 1).c_str());
								if (GetItemDef(intid).rarity == 999) {
									GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oGiven`w 200 " + GetItemDef(intid).name + "`o."));

									ENetPacket* packet2 = enet_packet_create(p2.data,
										p2.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet2);
									delete p2.data;
								}
								else {
									GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oGiven`w 200 " + GetItemDef(intid).name + "`o. Rarity `w" + std::to_string(GetItemDef(intid).rarity) + "`o."));

									ENetPacket* packet2 = enet_packet_create(p2.data,
										p2.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet2);
									delete p2.data;
								}
								int netID = ((PlayerInfo*)(peer->data))->netID;
								size_t invsize = 250;
								if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsize) {
									PlayerInventory inventory;
									InventoryItem item;
									item.itemID = atoi(str.substr(6, cch.length() - 6 - 1).c_str());
									item.itemCount = 200;
									inventory.items.push_back(item);
									item.itemCount = 1;
									item.itemID = 18;
									inventory.items.push_back(item);
									item.itemID = 32;
									inventory.items.push_back(item);
									((PlayerInfo*)(peer->data))->inventory = inventory;
								}
								else {
									InventoryItem item;
									item.itemID = atoi(str.substr(6, cch.length() - 6 - 1).c_str());
									item.itemCount = 200;
									((PlayerInfo*)(peer->data))->inventory.items.push_back(item);
								}
								sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
								SendTradeEffect(peer, intid, netID, netID, 150);



							}
						}
						else if (str.substr(0, 9) == "/weather ") {
							if (world->name != "ADMIN") {
								if (world->owner != "") {

									world->weather = atoi(str.substr(9).c_str());
									ENetPeer* currentPeer;

									for (currentPeer = server->peers;
										currentPeer < &server->peers[server->peerCount];
										++currentPeer)
									{
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
											continue;
										if (isHere(peer, currentPeer))
										{
											GamePacket p1 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oPlayer `2" + ((PlayerInfo*)(peer->data))->displayName + "`o has just changed the world's weather!"));
											ENetPacket* packet1 = enet_packet_create(p1.data,
												p1.len,
												ENET_PACKET_FLAG_RELIABLE);

											enet_peer_send(currentPeer, 0, packet1);
											delete p1.data;

											GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), atoi(str.substr(9).c_str())));
											ENetPacket* packet2 = enet_packet_create(p2.data,
												p2.len,
												ENET_PACKET_FLAG_RELIABLE);

											enet_peer_send(currentPeer, 0, packet2);
											delete p2.data;
											continue; /*CODE UPDATE /WEATHER FOR EVERYONE!*/
										}

									}
								}
							}
						}
						else if (str.substr(0, 7) == "/check ") {
							string playername = str.substr(7).c_str();

							bool found = false;
							ENetPeer* currentPeer;
							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								PlayerInfo* cInfo = ((PlayerInfo*)(currentPeer->data));
								if (cInfo->rawName == getStrLower(playername) || cInfo->displayName == getStrLower(playername)) {
									found = true;
									PlayerInfo* cInfo = ((PlayerInfo*)(currentPeer->data));
									string online_datext = "set_default_color|`o\nadd_label_with_icon|small|`wChecking " + cInfo->displayName + "            |left|32|\nadd_spacer|small|\nadd_label|small|`wRegister IP:`o " + cInfo->registerIP + "| \nadd_label|small|`wLast logon IP:`o " + cInfo->ipAddress + "| \nadd_label|small|`wStatus:`2 ONLINE|\nadd_label|small|`wRaw Name:`o " + cInfo->rawName + "| \nadd_label|small|`wBanned:`w `2NO| \nadd_label|small|`wMuted:`w `2" + to_string(cInfo->muted) + " | \nadd_label|small|`wGems:`w `o" + to_string(cInfo->gems) + "| \nadd_label|small|`wCurrent World:`w `o" + cInfo->currentWorld + "| \nadd_label|small|`wRank:`w `o" + to_string(cInfo->adminLevel) + "| \nadd_spacer|small| \nadd_label_with_icon_button|ban_menu|`oBan Menu|left|276| \nadd_label_with_icon_button|mute_menu|`oMute Menu|left|408| \nadd_spacer|small| \nadd_small_font_button|warpto|`wWarp to player| \nadd_small_font_button|resetpassw|`wReset password| \nadd_spacer|small|\nadd_button|ses|`wContinue||\nadd_quick_exit|\nend_dialog|owner_lookup|";
									GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), online_datext));
									ENetPacket* packet = enet_packet_create(p.data,
										p.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet);
									delete p.data;

									break;
									continue;
								}


							}
							if (found == false) {




								string _username;
								string _pass;
								string _gem;
								string _admin2;
								string _xp;
								string _level;
								string _ban;
								string _bandate;
								string _bantime;
								string _uid;

								string bantext;


								MYSQL_ROW row;
#pragma region longone


								conn = mysql_init(0);
								conn = mysql_real_connect(conn, ip, user, pass, database, 0, NULL, 0);

								if (conn == NULL) {

									sendConsoleMsg(peer, "`4ERROR: `wConnection was null.");
									continue;
									break;

								}

								if (conn != NULL) {
									int qstate = 0;
									string uname = filterName(playername);
									stringstream ss; // creating string stream to load in query
									ss << "SELECT * FROM players WHERE username = '" + uname;
#pragma region variables


#pragma endregion variables

									if (!ss.fail()) {
										string query = ss.str();
										const char* q = query.c_str();
										qstate = mysql_query(conn, q);
									}
									if (qstate == 0) {
										res = mysql_store_result(conn);
										while (row = mysql_fetch_row(res)) {
											_username = row[0];
											_pass = row[1];
											_gem = (row[2]);

											_admin2 = (row[4]);
											_uid = (row[5]);
											_xp = (row[6]);
											_level = (row[7]);

											_bandate = row[19];
											_ban = row[20];
											_bantime = row[21];



										}

										mysql_close(conn);
										if (_username == "") {

											sendConsoleMsg(peer, "Could not find player, aborting!");
											continue;
											break;

										}






										string daysleft = BanDays(stoi(_bantime) + stoi(_bandate) - GetCurrentTimeInternalSeconds()) + " days`o, `w";
										string hoursleft = BanHours(stoi(_bantime) + stoi(_bandate) - GetCurrentTimeInternalSeconds()) + " hours`o, `w";
										string minsleft = BanMinutes(stoi(_bantime) + stoi(_bandate) - GetCurrentTimeInternalSeconds()) + " mins`o, `w";
										string seleft = BanSecs(stoi(_bantime) + stoi(_bandate) - GetCurrentTimeInternalSeconds()) + " secs";

										int daysez = stoi(daysleft);
										int hoursez = stoi(hoursleft);
										int minsez = stoi(minsleft);
										int secondsez = stoi(seleft);

										if (daysez == 0) {
											daysleft = "";
										}
										if (hoursez == 0) {
											hoursleft = "";
										}
										if (minsez == 0) {
											minsleft = "";
										}
										if (secondsez == 0) {
											seleft = "";
										}
										bantext = daysleft + hoursleft + minsleft + seleft;
										//cout << "Days " + daysleft << endl << "Hours "+ hoursleft << endl << "Minutes "  + minsleft << endl << "Secs " + seleft << endl; 

										//	BlockLogin(peer, , "", "");

										string value = "This temporary ban will be removed in `w" + bantext + "`o.";




									}



								}




#pragma endregion longone

								string bans = "`2NO";
								bool alternative = false;
								if (0 != 0) {
									bans = "`4YES";
									alternative = true;
								}


								string offline_datext = "set_default_color|`o\nadd_label_with_icon|small|`wChecking " + _username + "            |left|32|\nadd_spacer|small|\nadd_label|small|`wRegister IP:`o " + "sdd" + "| \nadd_label|small|`wLast logon IP:`o " + "2" + "| \nadd_label|small|`wStatus:`4 OFFLINE| \nadd_label|small|`wRaw Name:`o " + _username + "| \nadd_label|small|`wBanned:`w " + bans + "| \nadd_label|small|`wMuted:`w `2" + "no" + "| \nadd_label|small|`wGems:`w `o" + _gem + "|\nadd_label|small|`wRank:`w `o" + _admin2 + "| \nadd_spacer|small| \nadd_label_with_icon_button|ban_menu|`oBan Menu|left|276| \nadd_label_with_icon_button|mute_menu|`oMute Menu|left|408| \nadd_spacer|small|\nadd_small_font_button|resetpassw|`wReset password| \nadd_spacer|small|\nadd_button|kekki|`wContinue||\nadd_quick_exit|\nend_dialog|owner_lookup|";
								string offline_datext_alternative = "set_default_color|`o\nadd_label_with_icon|small|`wChecking " + _username + "            |left|32|\nadd_spacer|small|\nadd_label|small|`wRegister IP:`o " + "dd" + "| \nadd_label|small|`wLast logon IP:`o " + "dad" + "| \nadd_label|small|`wStatus:`4 OFFLINE| \nadd_label|small|`wRaw Name:`o " + _username + "|\nadd_label|small|`wBanned:`w " + bans + "|\nadd_label|small|`wTime Left:`w " + bantext + "|\nadd_label|small|`wMuted:`w `2" + "no" + "| \nadd_label|small|`wGems:`w `o" + _gem + "|\nadd_label|small|`wRank:`w `o" + _admin2 + "| \nadd_spacer|small| \nadd_label_with_icon_button|ban_menu|`oBan Menu|left|276| \nadd_label_with_icon_button|mute_menu|`oMute Menu|left|408| \nadd_spacer|small|\nadd_small_font_button|resetpassw|`wReset password| \nadd_spacer|small|\nadd_button|kekki|`wContinue||\nadd_quick_exit|\nend_dialog|owner_lookup|";




								if (alternative) {
									GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), offline_datext_alternative));
									ENetPacket* packet = enet_packet_create(p.data,
										p.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet);
									delete p.data;
								}
								else {
									GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), offline_datext));
									ENetPacket* packet = enet_packet_create(p.data,
										p.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet);
									delete p.data;
								}
							}




						}
						else if (str.substr(0, 7) == "/trade ")
						{
							string name = PlayerDB::getProperName(str.substr(7));
							ENetPeer* peerToTradeWith = findPeerWithName(name);
							if (!peerToTradeWith)
							{
								Player::OnTextOverlay(peer, "That player couldn't be found.");
								break;
							}
							int a = WaitForTradeWithThisPlayer(peer, peerToTradeWith);
							if (a == -1)
							{
								Player::OnTextOverlay(peer, "That player is busy.");
							}
							if (a == -2)
							{
								Player::OnTextOverlay(peer, "You can't trade with yourself!");
							}
							if (a == -3)
							{
								Player::OnTextOverlay(peer, "This player is not in the same world as you!");
							}
						}


						else if (str == "/clear") {
							if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 0) {
								WorldInfo* world = getPlyersWorld(peer);
								if (!world) continue;
								int x = 0;
								int y = 0;

								vector<point> a;
								if (((PlayerInfo*)(peer->data))->currentWorld != "EXIT") {

									for (int i = 0; i < world->width * world->height; i++)
									{
										if (world->items[i].foreground != 6 && world->items[i].foreground != 8 && getItemDef(world->items[i].foreground).blockType != BlockTypes::LOCK) {

											world->items[i].foreground = 0;
											world->items[i].background = 0;
											world->items[i].activated = false;
											world->items[i].intdata = 0;
											world->items[i].sign = "";


											x = (i % world->width);
											y = (i / world->width);
											point e;
											e.x = x;
											e.y = y;
											a.push_back(e);
										}
									}
									SendTileDataMultiple(peer, world, a);
								}
							}
						}
					
						else if (str.substr(0, 5) == "/mag ") {
							int test_mode = atoi(str.substr(5).c_str());
							int x;
							int y;
							for (int i = 0; i < world->width * world->height; i++)
							{
								if (world->items[i].foreground == 5638) {

									x = (i % world->width);
									y = (i / world->width);
									sendMag(peer, x, y, test_mode, 1, 1, 1);
								}
							}

						}


						else if (str.substr(0, 6) == "/mars ") {
							string name = getStrLower(str.substr(6).c_str());

							if (worldDB.exists(name))
							{
								sendConsoleMsg(peer, "`4OOPS: `oCannot create Mars Blasted world named `w" + name + "`o because it already exists.");
							}
							else
							{
								cout << "Creating Mars blasted world named " << name << endl;
								WorldInfo* info = &worldDB.get(name);

								GenerateGrowaloneLikeWorld(info, 100, 60, 1132, 440, 6, 8, 1134, 14, 7, 1138, 0, BlastProperties_RandomDeco1);
								joinWorld(peer, name);
								RemoveItemFromInv(peer, 1136, 1, true);
								info->weather = 7;
								worldDB.saveAll();
							}

						}
						else if (str.substr(0, 4) == "/fly") {
						sendCustomState(peer, ((PlayerInfo*)(peer->data)), -100, 300);
						}
						else if (str.substr(0, 5) == "/ssup") {
						PlayerInfo* p = ((PlayerInfo*)(peer->data));
						p->haveSuperSupporterName = true;
						sendState(peer, p);
						}
						else if (str.substr(0, 5) == "/set ") {
							PlayerInfo* p = ((PlayerInfo*)(peer->data));
							p->lquestprogress = atoi(str.substr(5).c_str());
							sendConsoleMsg(peer, "done");
						}
						else if (str.substr(0, 6) == "/test ") {
							string test_mode = str.substr(6).c_str();
							PlayerInfo* p = ((PlayerInfo*)(peer->data));

							if (test_mode == "lock") {
								int x;
								int y;
								for (int i = 0; i < world->width * world->height; i++)
								{
									if (world->items[i].foreground == 202) {

										x = (i % world->width);
										y = (i / world->width);
										ApplyLockPacket(peer, x, y, 202, 20, p->netID);
									}
								}
								
							}
							if (test_mode == "test") {
								cout << items[1204].punchEffect << endl; ;
								cout << items[1204].audioVol << endl; ;

							}
							if (test_mode == "geiger") {
								p->useGeiger = true;
							}
							if (test_mode == "particle") {
								SendParticleEffect(peer, p->x, p->y, 2, 97, 2);
							}
							if (test_mode == "fires") {
								Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "I have put out `2" + to_string(((PlayerInfo*)(peer->data))->firesOutput) + " `wfires", true);
							}
							if (test_mode == "npc") {

								int x;
								int y;
								for (int i = 0; i < world->width * world->height; i++)
								{
									if (world->items[i].foreground == 6) {

										x = (i % world->width);
										y = (i / world->width);

									}
								}

								//sendNPC(peer, x, y, 65, 64, 1, 1, 14, 2);

								cout << "sent" << endl;
							}
							if (test_mode == "hw") {

								int x;


								//3694	
							}
							if (test_mode == "mag") {
								int x;
								int y;
								for (int i = 0; i < world->width * world->height; i++)
								{
									if (world->items[i].foreground == 5638) {

										x = (i % world->width);
										y = (i / world->width);
										sendMag(peer, x, y, 3, 1, 1, 0);
									}
								}

								sendConsoleMsg(peer, "`^Magplant.");
								printf("magplant");
							}
							else if (test_mode == "h") {

							}

						}
						else if (str.substr(0, 2) == "/a") {

							sendGazette(peer);
						}

						else if (str.substr(0, 3) == "/d ") {
							string filename = str.substr(3).c_str();
							string dada = ReadAllText("dialogs/" + filename + ".txt");
							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), dada));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							delete p.data;



						}

						else if (str.substr(0, 5) == "/ban ") {
							if (!isMod(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)) continue;
							bool suspend = false;
							string bruhbrhuh = str.substr(5);
							vector<string> list = explode(" ", bruhbrhuh);

							if (list.size() == 0)
							{
								sendConsoleMsg(peer, "Invalid arguments.");
								break;
							}
							string pname = list[0];
							long long banTime = 0;
							long long number = 0;
							char prefix = 's';
							string reason = "Not specified.";
							if (list.size() == 1)
							{
								suspend = true;
							}
							else if (list.size() >= 2)
							{
								if (list.size() == 3) reason = list.at(2);
								string num = list[1];
								prefix = num.at(num.length() - 1);
								string numstr = list[1].substr(0, num.length() - 1);
								number = atoll(numstr.c_str());
								switch (prefix)
								{
								case 's':
								case 'S':
									// seconds
									banTime = number;
									break;
								case 'm':
								case 'M':
									// minutes
									banTime = number * 60;
									break;
								case 'h':
								case 'H':
									// hours
									banTime = number * 3600;
									break;
								case 'd':
								case 'D':
									// days
									banTime = 3600 * 24 * number;
									break;
								case 'y':
								case 'Y':
									// years
									banTime = 3600 * 24 * 365 * number;
									break;
								case 'w':
								case 'W':
									// weeks
									banTime = 3600 * 24 * 7 * number;
									break;
								default:
									sendConsoleMsg(peer, "Invalid ban time!");
									break;
								}
							}
							else
							{
								int idx = list[0].size() + list[1].size() + 7;
								string rsn = str.substr(idx);
								reason = rsn;
							}
							string ga = "";
							ENetPeer* currentPeer;
							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (((PlayerInfo*)(currentPeer->data))->rawName == pname)
								{
									string datedescriptor = "";
									switch (prefix)
									{
									case 's': case 'S': datedescriptor = " secs"; break;
									case 'm': case 'M': datedescriptor = " mins"; break;
									case 'h': case 'H': datedescriptor = " hours"; break;
									case 'd': case 'D': datedescriptor = " days"; break;
									case 'w': case 'W': datedescriptor = " weeks"; break;
									case 'y': case 'Y': datedescriptor = " years"; break;
									default: datedescriptor = " secs"; break;
									}
									if (suspend == true) {
										string message = "`wWarning from `4System`w: You've been `4BANNED `wfrom Growtopia for 730 days";
										sendConsoleMsg(currentPeer, message);
										string left = "730 days";
										string sa = "`oReality flickers as you begin to wake up. (`$Ban`o mod added, `$ " + left + "`o left)";
										sendConsoleMsg(currentPeer, sa);
										string msgs = "`#**`$ The Gods`o have used `#Ban `oon " + ((PlayerInfo*)(currentPeer->data))->displayName + "`o!`# **";

										sendConsoleMsg(currentPeer, msgs);
										sendNotification(currentPeer, "audio/hub_open.wav", "interface/atomic_button.rttex", message);
										((PlayerInfo*)(currentPeer->data))->currentWorld = "EXIT";

										((PlayerInfo*)(currentPeer->data))->ban = -1;
										FlushPlayer(currentPeer);
										sendPlayerLeave(currentPeer, (PlayerInfo*)(currentPeer->data));
										sendWorldOffers(currentPeer);
										ga = ((PlayerInfo*)(currentPeer->data))->displayName;
										enet_peer_disconnect_later(currentPeer, 0);
									}
									else
									{
										string message = "`wWarning from `4System`w: You've been `4BANNED `wfrom Growtopia for " + to_string(number) + datedescriptor;
										sendConsoleMsg(currentPeer, message);
										string left = to_string(number) + datedescriptor;
										string sa = "`oReality flickers as you begin to wake up. (`$Ban`o mod added, `$ " + left + "`o left)";
										sendConsoleMsg(currentPeer, sa);
										string msgs = "`#**`$ The Gods`o have used `#Ban `oon " + ((PlayerInfo*)(currentPeer->data))->displayName + "`o!`# **";

										sendConsoleMsg(currentPeer, msgs);
										sendNotification(currentPeer, "audio/hub_open.wav", "interface/atomic_button.rttex", message);

										((PlayerInfo*)(currentPeer->data))->bantime = (int)banTime;
										((PlayerInfo*)(currentPeer->data))->bandate = GetCurrentTimeInternalSeconds();

										((PlayerInfo*)(currentPeer->data))->ban = 1;

										int qstate = 0;
										conn = mysql_init(0);
										conn = mysql_real_connect(conn, ip, user, pass, database, 0, NULL, 0);
										if (conn == NULL) {
											return -1;
										}
										if (conn != NULL) {
											stringstream ss;

											ss << "UPDATE players SET bannedat = '" + to_string(GetCurrentTimeInternalSeconds()) + "', ban = '1', bantime = '" + to_string((int)banTime) + "' WHERE username = '" + filterName(((PlayerInfo*)(currentPeer->data))->rawName) + "'";
											string query = ss.str(); // loading query into string
											const char* q = query.c_str(); // converting string to const char
											qstate = mysql_query(conn, q);
											if (qstate == 0) { // if qstate == 0 (EVERYTHING IS OK!) then pop out a 1, 1 will lead to the dialog that will say ("GrowID Created")		
												//TODO			
											}
											else {

											}
										}

										sendPlayerLeave(currentPeer, (PlayerInfo*)(currentPeer->data));
										((PlayerInfo*)(currentPeer->data))->currentWorld = "EXIT";
										sendWorldOffers(currentPeer);
										ga = ((PlayerInfo*)(currentPeer->data))->displayName;
										// 	BanUser(currentPeer, pname, (int)banTime, reason, ((PlayerInfo*)currentPeer->data)->rawName);
										enet_peer_disconnect_later(currentPeer, 0);
									}
								}
							}
							sendConsoleMsg(peer, "`oUsed `wban`o to `w" + ga + "`o!");
							Player::OnConsoleMessageAll("`#** `$The Ancient Ones `ohave `4banned `2" + ga + " `#** `o(`4/rules `oto see the rules!)");
						}
					
						if (str.length() && str[0] == '/')
						{

							if (IsValidAction(str))
							{
								sendConsoleMsg(peer, "`6" + str);
								sendAction(peer, ((PlayerInfo*)(peer->data))->netID, str);
							}
							else
							{
								sendConsoleMsg(peer, "`6" + str);
								sendConsoleMsg(peer, "`4Unknown command. `oType `$/help `oto see a list of available commands.``");
							}
							


						}
						else if (str.length() > 0)
						{
							if (((PlayerInfo*)(peer->data))->taped == false) {
								sendChatMessage(peer, ((PlayerInfo*)(peer->data))->netID, str);
							}
							else {

								sendChatMessage(peer, ((PlayerInfo*)(peer->data))->netID, randomDuctTapeMessage(str.length()));
							}
						}

					}
					if (!((PlayerInfo*)(event.peer->data))->isIn)
					{
						if (itemdathash == 0) {
							enet_peer_disconnect_later(peer, 0);
						}
						//GamePacket p = packetEnd(appendString(appendString(appendString(appendString(appendInt(appendString(createPacket(), "OnSuperMainStartAcceptLogonHrdxs47254722215a"), itemdathash), "127.0.0.1"), "cache/"), "cc.cz.madkite.freedom org.aqua.gg idv.aqua.bulldog com.cih.gamecih2 com.cih.gamecih com.cih.game_cih cn.maocai.gamekiller com.gmd.speedtime org.dax.attack com.x0.strai.frep com.x0.strai.free org.cheatengine.cegui org.sbtools.gamehack com.skgames.traffikrider org.sbtoods.gamehaca com.skype.ralder org.cheatengine.cegui.xx.multi1458919170111 com.prohiro.macro me.autotouch.autotouch com.cygery.repetitouch.free com.cygery.repetitouch.pro com.proziro.zacro com.slash.gamebuster"), "proto=84|choosemusic=cache/windowsxp.wav|active_holiday=0|server_tick=226933875|clash_active=0|drop_lavacheck_faster=1|isPayingUser=0|"));
						GamePacket p = packetEnd(appendString(appendString(appendString(appendString(appendInt(appendString(createPacket(), "OnSuperMainStartAcceptLogonHrdxs47254722215a"), itemdathash), "ubistatic-a.akamaihd.net"), " 0098/CDNContent51/cache/"), "cc.cz.madkite.freedom org.aqua.gg idv.aqua.bulldog com.cih.gamecih2 com.cih.gamecih com.cih.game_cih cn.maocai.gamekiller com.gmd.speedtime org.dax.attack com.x0.strai.frep com.x0.strai.free org.cheatengine.cegui org.sbtools.gamehack com.skgames.traffikrider org.sbtoods.gamehaca com.skype.ralder org.cheatengine.cegui.xx.multi1458919170111 com.prohiro.macro me.autotouch.autotouch com.cygery.repetitouch.free com.cygery.repetitouch.pro com.proziro.zacro com.slash.gamebuster"), "proto=84|choosemusic=audio/mp3/about_theme.mp3|active_holiday=0|"));
						//		GamePacket p = packetEnd(appendString(appendString(appendString(appendString(appendInt(appendString(createPacket(), "OnSuperMainStartAcceptLogonHrdxs47254722215a"), itemdathash), "ubistatic-a.akamaihd.net"), configCDN), "cc.cz.madkite.freedom org.aqua.gg idv.aqua.bulldog com.cih.gamecih2 com.cih.gamecih com.cih.game_cih cn.maocai.gamekiller com.gmd.speedtime org.dax.attack com.x0.strai.frep com.x0.strai.free org.cheatengine.cegui org.sbtools.gamehack com.skgames.traffikrider org.sbtoods.gamehaca com.skype.ralder org.cheatengine.cegui.xx.multi1458919170111 com.prohiro.macro me.autotouch.autotouch com.cygery.repetitouch.free com.cygery.repetitouch.pro com.proziro.zacro com.slash.gamebuster"), "proto=84|choosemusic=audio/mp3/about_theme.mp3|active_holiday=0|server_tick=226933875|clash_active=0|drop_lavacheck_faster=1|isPayingUser=0|"));
									//for (int i = 0; i < p.len; i++) cout << (int)*(p.data + i) << " ";
						ENetPacket* packet = enet_packet_create(p.data,
							p.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet);

						//enet_host_flush(server);
						delete p.data;
						std::stringstream ss(GetTextPointerFromPacket(event.packet));
						std::string to;
						while (std::getline(ss, to, '\n')) {
							string id = to.substr(0, to.find("|"));
							string act = to.substr(to.find("|") + 1, to.length() - to.find("|") - 1);

							if (id == "tankIDName")
							{

								((PlayerInfo*)(event.peer->data))->tankIDName = act;
								((PlayerInfo*)(event.peer->data))->haveGrowId = true;
							}
							else if (id == "tankIDPass")
							{

								((PlayerInfo*)(event.peer->data))->tankIDPass = act;
							}
							else if (id == "requestedName")
							{
								((PlayerInfo*)(event.peer->data))->requestedName = act;
							}
							else if (id == "country")
							{
								((PlayerInfo*)(event.peer->data))->country = act;
							}

						}
						if (!((PlayerInfo*)(event.peer->data))->haveGrowId)
						{
							((PlayerInfo*)(event.peer->data))->rawName = "";
							((PlayerInfo*)(event.peer->data))->displayName = "`w[`2Quest`w] `w" + PlayerDB::fixColors(((PlayerInfo*)(event.peer->data))->requestedName.substr(0, ((PlayerInfo*)(event.peer->data))->requestedName.length() > 15 ? 15 : ((PlayerInfo*)(event.peer->data))->requestedName.length()));
						}
						else {
							((PlayerInfo*)(event.peer->data))->rawName = PlayerDB::getProperName(((PlayerInfo*)(event.peer->data))->tankIDName);
#ifdef REGISTRATION
							int logStatus = PlayerDB::playerLogin(peer, ((PlayerInfo*)(event.peer->data))->rawName, ((PlayerInfo*)(event.peer->data))->tankIDPass);
							if (logStatus == 1) {

								((PlayerInfo*)(event.peer->data))->displayName = ((PlayerInfo*)(event.peer->data))->displayName;
							}
							else if (logStatus == -1) {
								BlockLoginNoUrl(peer, "`4Wrong username or password!");
								enet_peer_disconnect_later(peer, 0);
							}

							else {
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`rOther internal error!``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;
								enet_peer_disconnect_later(peer, 0);
							}
#else

							((PlayerInfo*)(event.peer->data))->displayName = PlayerDB::fixColors(((PlayerInfo*)(event.peer->data))->tankIDName.substr(0, ((PlayerInfo*)(event.peer->data))->tankIDName.length() > 18 ? 18 : ((PlayerInfo*)(event.peer->data))->tankIDName.length()));
							if (((PlayerInfo*)(event.peer->data))->displayName.length() < 3) ((PlayerInfo*)(event.peer->data))->displayName = "Person that doesn't know how the name looks!";
#endif
						}
						for (char c : ((PlayerInfo*)(event.peer->data))->displayName) if (c < 0x20 || c>0x7A) ((PlayerInfo*)(event.peer->data))->displayName = "Bad characters in name, remove them!";

						if (((PlayerInfo*)(event.peer->data))->country.length() > 4)
						{
							((PlayerInfo*)(event.peer->data))->country = "us";
						}
						if (((PlayerInfo*)(event.peer->data))->adminLevel == 2)
						{
							((PlayerInfo*)(event.peer->data))->country = "rt";
						}
						/*GamePacket p3= packetEnd(appendString(appendString(createPacket(), "OnRequestWorldSelectMenu"), "default|GO FOR IT\nadd_button|Showing: `wFake Worlds``|_catselect_|0.6|3529161471|\nadd_floater|Subscribe|5|0.55|3529161471\nadd_floater|Growtopia|4|0.52|4278190335\nadd_floater|Noobs|150|0.49|3529161471\nadd_floater|...|3|0.49|3529161471\nadd_floater|`6:O :O :O``|2|0.46|3529161471\nadd_floater|SEEMS TO WORK|2|0.46|3529161471\nadd_floater|?????|1|0.43|3529161471\nadd_floater|KEKEKEKEK|13|0.7|3417414143\n"));
						//for (int i = 0; i < p.len; i++) cout << (int)*(p.data + i) << " ";
						ENetPacket * packet3 = enet_packet_create(p3.data,
							p3.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet3);
						enet_host_flush(server);*/

						GamePacket p2 = packetEnd(appendString(appendString(appendInt(appendString(createPacket(), "SetHasGrowID"), ((PlayerInfo*)(event.peer->data))->haveGrowId), ((PlayerInfo*)(peer->data))->tankIDName), ((PlayerInfo*)(peer->data))->tankIDPass));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet2);
						delete p2.data;



					}
					string pStr = GetTextPointerFromPacket(event.packet);
					//if (strcmp(GetTextPointerFromPacket(event.packet), "action|enter_game\n") == 0 && !((PlayerInfo*)(event.peer->data))->isIn)
					if (pStr.substr(0, 17) == "action|enter_game" && !((PlayerInfo*)(event.peer->data))->isIn)
					{

#ifdef TOTAL_LOG
						cout << "And we are in!" << endl;
#endif		
						ENetPeer* currentPeer;
						((PlayerInfo*)(event.peer->data))->isIn = true;
						string bettername = ((PlayerInfo*)(peer->data))->displayName;




						if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) == 2) {

							string name2 = ((PlayerInfo*)(peer->data))->displayName = "`6@" + bettername;
							GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), name2));
							memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor

							((PlayerInfo*)(peer->data))->displayName = name2;
							ENetPacket* packet7 = enet_packet_create(p7.data,
								p7.len,
								ENET_PACKET_FLAG_RELIABLE);


							delete p7.data;
							((PlayerInfo*)(peer->data))->displayName = name2;
							((PlayerInfo*)(peer->data))->smstate = 1;
							((PlayerInfo*)(peer->data))->mstate = 1;

						}
						if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) == 1) {

							string name2 = ((PlayerInfo*)(peer->data))->displayName = "`#@" + bettername;
							GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), name2));
							memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor

							((PlayerInfo*)(peer->data))->displayName = name2;
							ENetPacket* packet7 = enet_packet_create(p7.data,
								p7.len,
								ENET_PACKET_FLAG_RELIABLE);


							delete p7.data;
							((PlayerInfo*)(peer->data))->displayName = name2;
							((PlayerInfo*)(peer->data))->smstate = 1;
							((PlayerInfo*)(peer->data))->mstate = 1;
						}



						sendWorldOffers(peer);

						// growmoji
						GamePacket p2ssw = packetEnd(appendString(appendInt(appendString(createPacket(), "OnEmoticonDataChanged"), 201560520), "(wl)|Ä|1&(yes)|Ä‚|1&(no)|Äƒ|1&(love)|Ä„|1&(oops)|Ä…|1&(shy)|Ä†|1&(wink)|Ä‡|1&(tongue)|Äˆ|1&(agree)|Ä‰|1&(sleep)|ÄŠ|1&(punch)|Ä‹|1&(music)|ÄŒ|1&(build)|Ä|1&(megaphone)|ÄŽ|1&(sigh)|Ä|1&(mad)|Ä|1&(wow)|Ä‘|1&(dance)|Ä’|1&(see-no-evil)|Ä“|1&(bheart)|Ä”|1&(heart)|Ä•|1&(grow)|Ä–|1&(gems)|Ä—|1&(kiss)|Ä˜|1&(gtoken)|Ä™|1&(lol)|Äš|1&(smile)|Ä€|1&(cool)|Äœ|1&(cry)|Ä|1&(vend)|Äž|1&(bunny)|Ä›|1&(cactus)|ÄŸ|1&(pine)|Ä¤|1&(peace)|Ä£|1&(terror)|Ä¡|1&(troll)|Ä¢|1&(evil)|Ä¢|1&(fireworks)|Ä¦|1&(football)|Ä¥|1&(alien)|Ä§|1&(party)|Ä¨|1&(pizza)|Ä©|1&(clap)|Äª|1&(song)|Ä«|1&(ghost)|Ä¬|1&(nuke)|Ä­|1&(halo)|Ä®|1&(turkey)|Ä¯|1&(gift)|Ä°|1&(cake)|Ä±|1&(heartarrow)|Ä²|1&(lucky)|Ä³|1&(shamrock)|Ä´|1&(grin)|Äµ|1&(ill)|Ä¶|1&"));


						GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oWelcome back to Growheaven, `w" + bettername + "`o!"));
						ENetPacket* packet = enet_packet_create(p.data,
							p.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet);

						//enet_host_flush(server);
						delete p.data;



						PlayerInventory inventory;

						{
							InventoryItem item;
							item.itemCount = 1;
							item.itemID = 18;
							inventory.items.push_back(item);
							item.itemCount = 1;
							item.itemID = 32;
							inventory.items.push_back(item);
						}
						((PlayerInfo*)(event.peer->data))->inventory = inventory;
						LoadInventory(peer);
						sendState(peer, ((PlayerInfo*)(peer->data)));
						{
							sendGazette(peer);
							string captcha = "set_default_color|`o\nadd_label_with_icon|big|`wAre you Human?``|left|206|\nadd_spacer|small|\nadd_textbox|What will be the sum of the following numbers|left|\nadd_textbox|" + std::to_string(((PlayerInfo*)(peer->data))->number1) + " + " + std::to_string(((PlayerInfo*)(peer->data))->number2) + "|left|\nadd_text_input|captcha_answer|Answer:||32|\nend_dialog|captcha_submit||Submit|";
							/*	GamePacket p67 = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), captcha));

								ENetPacket* packet67 = enet_packet_create(p67.data,
									p67.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet67);

								//enet_host_flush(server);
								delete p67.data;*/
						}





					}
					if (strcmp(GetTextPointerFromPacket(event.packet), "action|refresh_item_data\n") == 0)
					{
						if (itemsDat != NULL) {
							ENetPacket* packet = enet_packet_create(itemsDat,
								itemsDatSize + 60,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							((PlayerInfo*)(peer->data))->isUpdating = true;
							enet_peer_disconnect_later(peer, 0);
							//enet_host_flush(server);
						}
						// TODO FIX refresh_item_data ^^^^^^^^^^^^^^
					}
					break;
				}
				default:
					cout << "Unknown packet type " << messageType << endl;
					break;
				case 3:
				{
					//cout << GetTextPointerFromPacket(event.packet) << endl;
					std::stringstream ss(GetTextPointerFromPacket(event.packet));
					std::string to;
					bool isJoinReq = false;
					while (std::getline(ss, to, '\n')) {
						string id = to.substr(0, to.find("|"));
						string act = to.substr(to.find("|") + 1, to.length() - to.find("|") - 1);
						if (id == "name" && isJoinReq)
						{
#ifdef TOTAL_LOG
							cout << "Entering some world..." << endl;
#endif
							toUpperCase(act);
							if (act.find(" ") != string::npos || act.find("  ") != string::npos || act.find(".") != string::npos || act.find(",") != string::npos || act.find("@") != string::npos || act.find("[") != string::npos || act.find("]") != string::npos || act.find("#") != string::npos || act.find("<") != string::npos || act.find(">") != string::npos || act.find(":") != string::npos || act.find("\"") != string::npos || act.find("{") != string::npos || act.find("}") != string::npos || act.find("|") != string::npos || act.find("+") != string::npos || act.find("_") != string::npos || act.find("~") != string::npos || act.find("-") != string::npos || act.find("!") != string::npos || act.find("$") != string::npos || act.find("%") != string::npos || act.find("^") != string::npos || act.find("&") != string::npos || act.find("`") != string::npos || act.find("*") != string::npos || act.find("(") != string::npos || act.find(")") != string::npos || act.find("=") != string::npos || act.find("'") != string::npos || act.find(";") != string::npos || act.find("/") != string::npos) {
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "Please use only letters.``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;

								GamePacket p3 = packetEnd(appendString(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1), "Sorry"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;

								continue;
								break;
							}
							if (act == "")
							{
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "Where are we going?``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;

								GamePacket p3 = packetEnd(appendString(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1), "Sorry"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;

								continue;
								break;
							}
							if (act == "")
							{
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "Where are we going?``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;

								GamePacket p3 = packetEnd(appendString(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1), "Sorry"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;

								continue;
								break;
							}


							if (act == "CON" || act == "EXIT" || act == "NUL" || act == "PRN" || act == "AUX" || act == "CLOCK$" || act == "COM0" || act == "COM1" || act == "COM2" || act == "COM3" || act == "COM4" || act == "COM5" || act == "COM6" || act == "COM7" || act == "COM8" || act == "COM9" || act == "LPT0" || act == "LPT1" || act == "LPT2" || act == "LPT3" || act == "LPT4" || act == "LPT5" || act == "LPT6" || act == "LPT7" || act == "LPT8" || act == "LPT9")
							{
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "Maybe try another one?``"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;

								GamePacket p3 = packetEnd(appendString(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1), "Sorry"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;

								continue;
								break;
							}



							WorldInfo info = worldDB.get(act);
							WorldInfo info2 = worldDB.get("HELL");
							WorldInfo info3 = worldDB.get("START");

							string name = ((PlayerInfo*)(peer->data))->rawName;
							bool exitsnuke = info.isNuked == true;

							if (exitsnuke)
							{
								if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 0) {
									joinWorld(peer, act);
									sendConsoleMsg(peer, "This world is inaccessible by others!");

								}
								else
								{

									GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oThis world is inaccessible.``"));
									ENetPacket* packet = enet_packet_create(p.data,
										p.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet);
									delete p.data;

									GamePacket p3 = packetEnd(appendString(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1), "Sorry"));
									ENetPacket* packet3 = enet_packet_create(p3.data,
										p3.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet3);
									delete p3.data;

									continue;
									break;
								}
							}

							else
							{

								joinWorld(peer, act);
							}

						}
						if (id == "action")
						{

							if (act == "join_request")
							{
								isJoinReq = true;
							}
							if (act == "quit_to_exit")
							{

								sendPlayerLeave(peer, (PlayerInfo*)(event.peer->data));
								((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
								sendWorldOffers(peer);

							}
							if (act == "quit")
							{
								enet_peer_disconnect_later(peer, 0);
							}
						}
					}
					break;
				}
				case 4:
				{
					{
						BYTE* tankUpdatePacket = GetStructPointerFromTankPacket(event.packet);

						if (tankUpdatePacket)
						{
							PlayerMoving* pMov = unpackPlayerMoving(tankUpdatePacket);
							if (((PlayerInfo*)(event.peer->data))->canWalkInBlocks) {

								((PlayerInfo*)(event.peer->data))->x1 = pMov->x;
								((PlayerInfo*)(event.peer->data))->y1 = pMov->y;
								pMov->x = -1000000;
								pMov->y = -1000000;
							}

							switch (pMov->packetType)
							{
							case 0:
								((PlayerInfo*)(event.peer->data))->x = pMov->x;
								((PlayerInfo*)(event.peer->data))->y = pMov->y;
								((PlayerInfo*)(event.peer->data))->isRotatedLeft = pMov->characterState & 0x10;
								sendPData(peer, pMov);
								if (!((PlayerInfo*)(peer->data))->joinClothesUpdated)
								{
									((PlayerInfo*)(peer->data))->joinClothesUpdated = true;
									updateAllClothes(peer);
									GamePacket p222 = packetEnd(appendInt(appendInt(appendInt(appendInt(appendString(createPacket(), "OnSetBux"), ((PlayerInfo*)(peer->data))->gems), 1), 2), 1));
									ENetPacket* packet222 = enet_packet_create(p222.data,
										p222.len,
										ENET_PACKET_FLAG_RELIABLE);

									enet_peer_send(peer, 0, packet222);
								}
								break;

							default:
								break;
							}
							PlayerMoving* data2 = unpackPlayerMoving(tankUpdatePacket);
							//cout << data2->packetType << endl;
							if (data2->packetType == 11)
							{
								// TODO DROPPING!!!
								//cout << pMov->x << ";" << pMov->y << ";" << pMov->plantingTree << ";" << pMov->punchX << endl					

								if (!world) continue;

								try {
									if (world->allowDropTakeAll) {
										processTake(peer, pMov, pMov->plantingTree - 1, pMov->x, pMov->y);
									}
									else {
										if (isWorldOwner(peer, world) || getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) > 2) {
											processTake(peer, pMov, pMov->plantingTree - 1, pMov->x, pMov->y);
										}
										else {
											Player::OnTextOverlay(peer, "Collecting is disabled here!");
										}
									}
								}
								catch (...) {
									continue;
								}
							}
							if (data2->packetType == 7)
							{
								cout << "PACKET TYPE 4999997 CALLED!" << endl;
								//cout << pMov->x << ";" << pMov->y << ";" << pMov->plantingTree << ";" << pMov->punchX << ";" << pMov->punchY << ";" << pMov->netID << ";" << pMov->secondnetID << ";" << endl;
								if (pMov->punchX < 0 || pMov->punchY < 0 || pMov->punchX > 100 || pMov->punchY > 100) continue;
								if (((PlayerInfo*)(event.peer->data))->currentWorld == "EXIT") continue;

								int x = pMov->punchX;
								int y = pMov->punchY;
								int tile = world->items[x + (y * world->width)].foreground;
								int netID = ((PlayerInfo*)(peer->data))->netID;

								// begin door code here
								bool founds = false;
								bool founds2 = false;
								int xx;
								int yy;
								if (getItemDef(tile).blockType == BlockTypes::DOOR || getItemDef(tile).blockType == BlockTypes::PORTAL) {

									for (int i = 0; i < world->door.size(); i++) {
										if (world->door.at(i).x == x && world->door.at(i).y == y) {
											founds = true;
											string worldname = world->door.at(i).linksToWorld;
											string doorId = "";
											xx = world->door.at(i).x;
											yy = world->door.at(i).y;
											if (worldname.find(":")) {
												doorId = getStrUpper(worldname.substr(worldname.find(":") + 1, worldname.length()));
												worldname = getStrUpper(worldname.substr(0, worldname.find(":")));

											}
											if (worldname == ((PlayerInfo*)(event.peer->data))->currentWorld) {
												for (int i = 0; i < world->door.size(); i++) {
													if (world->door.at(i).doorId == doorId) {
														Player::OnPlayPositioned(peer, "audio/door_open.wav", netID);
														founds2 = true;
														Player::OnSetPos(peer, netID, world->door.at(i).x * 32, world->door.at(i).y * 32, 150);
														Player::SmoothZoom(peer);
														Player::OnSetFreezeState(peer, 0, netID);
														break;
													}
												}
											}
											else {
												Player::SmoothZoom(peer);
												joinWorld(peer, worldname);
											}
											break; // found door
										}
									}
									int mainX;
									int mainY;
									for (int i = 0; i < world->width * world->height; i++)
									{
										if (world->items[i].foreground == 6) {
											mainX = (i % world->width) * 32 + 8;
											mainY = (i / world->width) * 32;
										}
									}
									if (founds == false) {

										Player::OnPlayPositioned(peer, "audio/door_open.wav", netID);
										Player::SmoothZoom(peer);
										Player::OnSetPos(peer, netID, mainX, mainY, 150);
										Player::OnSetFreezeState(peer, 0, netID);

									}
									else if (founds2 == false) {
										Player::OnPlayPositioned(peer, "audio/door_open.wav", netID);
										Player::SmoothZoom(peer);
										Player::OnSetPos(peer, netID, mainX, mainY, 150);
										Player::OnSetFreezeState(peer, 0, netID);

									}
									break;
								}

								if (tile == 6) {

									sendPlayerLeave(peer, (PlayerInfo*)(event.peer->data));
									((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
									sendWorldOffers(peer);
								}
								else if (tile == 410 || tile == 1832 || tile == 1770) {
									((PlayerInfo*)(peer->data))->respawnX = x * 32;
									((PlayerInfo*)(peer->data))->respawnY = y * 32;
									Player::SetRespawnPos(peer, x, (world->width * y), netID);
								}
								else {
									Player::OnTalkBubble(peer, netID, "`w(too far away)``", true);
									Player::OnZoomCamera(peer, 0, 0);
									Player::OnSetFreezeState(peer, 0, netID);
								}
								
							}

							if (data2->packetType == 10)
							{
								ItemDefinition def;
								try {
									def = getItemDef(pMov->plantingTree);
								}
								catch (int e) {
									goto END_CLOTHSETTER_FORCE;
								}

								switch (def.clothType) {
								case 0:
									if (((PlayerInfo*)(event.peer->data))->cloth0 == pMov->plantingTree)
									{
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth0 = 0;
										break;
									}
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									((PlayerInfo*)(event.peer->data))->cloth0 = pMov->plantingTree;
									break;
								case 1:
									if (((PlayerInfo*)(event.peer->data))->cloth1 == pMov->plantingTree)
									{
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth1 = 0;
										break;
									}
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									((PlayerInfo*)(event.peer->data))->cloth1 = pMov->plantingTree;
									break;
								case 2:
									if (((PlayerInfo*)(event.peer->data))->cloth2 == pMov->plantingTree)
									{
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth2 = 0;
										break;
									}
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									((PlayerInfo*)(event.peer->data))->cloth2 = pMov->plantingTree;
									break;
								case 3:
									if (((PlayerInfo*)(event.peer->data))->cloth3 == pMov->plantingTree)
									{
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth3 = 0;
										break;
									}
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									((PlayerInfo*)(event.peer->data))->cloth3 = pMov->plantingTree;
									break;
								case 4:
									if (((PlayerInfo*)(event.peer->data))->cloth4 == pMov->plantingTree)
									{
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth4 = 0;
										break;
									}
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									((PlayerInfo*)(event.peer->data))->cloth4 = pMov->plantingTree;
									break;
								case 5:
									if (((PlayerInfo*)(event.peer->data))->cloth5 == pMov->plantingTree)
									{
										if (pMov->plantingTree == 3066) {
											sendConsoleMsg(peer, "Water ended? (`$Fire Hose `omod removed)");
											((PlayerInfo*)(event.peer->data))->puncheffect = 0;
											sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										}
										else if (pMov->plantingTree == 2952)
										{
											sendConsoleMsg(peer, "Where the spade went? (`$Dig, dug. `omod removed)");
										
											sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										}
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth5 = 0;
										break;
									}
									((PlayerInfo*)(event.peer->data))->cloth5 = pMov->plantingTree;
									if (pMov->plantingTree == 3066) {
										sendConsoleMsg(peer, "Where does the water come from? (`$Fire Hose `omod added)");
										((PlayerInfo*)(peer->data))->puncheffect = 8421376 + 57;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									}
									if (pMov->plantingTree == 2952) {
										sendConsoleMsg(peer, "Dirt, beware! (`$Dig, dug. `omod added)");
										((PlayerInfo*)(peer->data))->puncheffect = 8421376 + 29;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									}		
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									break;
								case 6:
									if (((PlayerInfo*)(event.peer->data))->cloth6 == pMov->plantingTree)
									{
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth6 = 0;
										((PlayerInfo*)(event.peer->data))->canDoubleJump = false;
										sendState(peer, ((PlayerInfo*)(event.peer->data)));
										break;
									}
									{
										((PlayerInfo*)(event.peer->data))->cloth6 = pMov->plantingTree;
										int item = pMov->plantingTree;
										if (isDoubleJumpItem(item) == true) {
											((PlayerInfo*)(event.peer->data))->canDoubleJump = true;
										}
										else {
											((PlayerInfo*)(event.peer->data))->canDoubleJump = false;
										}
										// ^^^^ wings
										sendState(peer, ((PlayerInfo*)(event.peer->data)));
									}
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									break;
								case 7:
									if (((PlayerInfo*)(event.peer->data))->cloth7 == pMov->plantingTree)
									{
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth7 = 0;
										break;
									}
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									((PlayerInfo*)(event.peer->data))->cloth7 = pMov->plantingTree;
									break;
								case 8:
									if (((PlayerInfo*)(event.peer->data))->cloth8 == pMov->plantingTree)
									{
										((PlayerInfo*)(event.peer->data))->puncheffect = 0;
										sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
										((PlayerInfo*)(event.peer->data))->cloth8 = 0;
										break;
									}
									((PlayerInfo*)(event.peer->data))->cloth8 = pMov->plantingTree;
									((PlayerInfo*)(event.peer->data))->puncheffect = items[pMov->plantingTree].punchEffect;
									sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->puncheffect);
									break;
								default:
#ifdef TOTAL_LOG
									cout << "Invalid item activated: " << pMov->plantingTree << " by " << ((PlayerInfo*)(event.peer->data))->displayName << endl;
#endif
									break;
								}
								sendClothes(peer);
								// activate item
							END_CLOTHSETTER_FORCE:;
							}
							if (data2->packetType == 18)
							{
								sendPData(peer, pMov);
								// add talk buble
							}
							if (data2->punchX != -1 && data2->punchY != -1) {
								//cout << data2->packetType << endl;
								if (data2->packetType == 3)
								{
									sendTileUpdate(data2->punchX, data2->punchY, data2->plantingTree, ((PlayerInfo*)(event.peer->data))->netID, peer);
								}
								else {

								}
								/*PlayerMoving data;
								//data.packetType = 0x14;
								data.packetType = 0x3;
								//data.characterState = 0x924; // animation
								data.characterState = 0x0; // animation
								data.x = data2->punchX;
								data.y = data2->punchY;
								data.punchX = data2->punchX;
								data.punchY = data2->punchY;
								data.XSpeed = 0;
								data.YSpeed = 0;
								data.netID = ((PlayerInfo*)(event.peer->data))->netID;
								data.plantingTree = data2->plantingTree;
								SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
								cout << "Tile update at: " << data2->punchX << "x" << data2->punchY << endl;*/

							}
							delete data2;
							delete pMov;
						}

						else {
							cout << "Got bad tank packet";
						}
						/*char buffer[2048];
						for (int i = 0; i < event->packet->dataLength; i++)
						{
						sprintf(&buffer[2 * i], "%02X", event->packet->data[i]);
						}
						cout << buffer;*/
					}
				}
				break;
				case 5:
					break;
				case 6:
					//cout << GetTextPointerFromPacket(event.packet) << endl;
					break;
				}
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
#ifdef TOTAL_LOG
				printf("<if (condition=good)>.\n");
#endif
				/* Reset the peer's client information. */
				/*ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;

					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "Player `o" + ((PlayerInfo*)(event.peer->data))->tankIDName + "`o just left the game..."));
					ENetPacket * packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet);
					enet_host_flush(server);
				}*/
				//updatePlayer(peer);
				sendPlayerLeave(peer, (PlayerInfo*)(event.peer->data));
				FlushPlayer(peer);
				((PlayerInfo*)(event.peer->data))->inventory.items.clear();
				delete (PlayerInfo*)event.peer->data;
				event.peer->data = NULL;
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					PlayerInfo* pinf = ((PlayerInfo*)(currentPeer->data));

					updatePlayer(currentPeer, pinf->x, pinf->y);
					eventPool(currentPeer);
				}
			}
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				PlayerInfo* pinf = ((PlayerInfo*)(currentPeer->data));

				updatePlayer(currentPeer, pinf->x, pinf->y);
				monitorCheck(currentPeer, pinf->x, pinf->y);
				eventPool(currentPeer);
			}
		}
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			PlayerInfo* pinf = ((PlayerInfo*)(currentPeer->data));
			WorldInfo* world = getPlyersWorld(currentPeer);
			updatePlayer(currentPeer, pinf->x, pinf->y);
			eventPool(currentPeer);
		}
	}
	cout << "Program ended??? Huh?" << endl;
	while (1);
	return 0;
}
