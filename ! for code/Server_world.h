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
#include "psapi.h"
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
#include <stdexcept>

struct Crystal
{
	string name;
	int probability;
	Crystal(string s, int p) :name(s), probability(p) {}
};
struct WorldItem {
	bool active = false;
	__int16 foreground = 0;
	__int16 background = 0;
	int bulletinpublic = 0; // lol skid
	string bulletinmsg = "";
	int mailcount = 0;
	int bulletinhide = 0;
	string mail = "";
	/*hmonitor*/
	string monitorname = "";
	bool monitoronline = false;

	/*magplant*/
	int mid = 0;
	int mc = 0;
	bool rm = false;
	int vid = 0;
	int vcount = 0;

	/*display shelf*/
	int dshelf2 = 0;
	int dshelf1 = 0;
	int dshelf4 = 0;
	int dshelf3 = 0;

	/*painting easel*/
	bool sign = false;
	/*entrance*/
	bool opened = false;
	/*seeds*/
	int growth_time = 0;
	int fruit = 0;
	/*rocks*/
	int evolvestage = 0;
	bool atnaujino = false;
	int firehousestate = 0;
	/*etc*/
	bool activated = false;
	string worldinput = "";
	string doorid = "";
	bool activeWeather = false;
	int yellowGems = 0;
	int blueGems = 0;
	int redGems = 0;
	int greenGems = 0;
	int purpleGems = 0;
	bool dropCollectBlocked = false;
	int displayblock = 0;
	int breakLevel = 0;
	long long int breakTime = 0;
	bool water = false;
	bool rotatedLeft = false;
	bool fire = false;
	bool glue = false;
	bool pinfo= false;
	bool red = false;
	bool green = false;
	bool flipped = false;
	bool blue = false;
	int displayBlock = 0;
	int gravity = 100;
	int intdata = 0;
	bool isInverted = false;
	bool isRotating = false;
	string label = "";
	string destWorld = "";
	string destId = "";
	string currId = "";
	string password = "";
	string text = "";
	vector<string> mailbox;
	bool isOpened = false;
	int packetrandom111 = 0;
	int packetrandom222 = 0;
	int packetrandom333 = 0;
	int jumlahitem5 = 0;
	int jumlahitem4 = 0;
	int jumlahitem3 = 0;
	int jumlahitem2 = 0;
	int jumlahitem1 = 0;
	int jenisitem5 = 0;
	int jenisitem4 = 0;
	int jenisitem3 = 0;
	int jenisitem2 = 0;
	int jenisitem1 = 0;
	int geigerX = 0;
	int geigerY = 0;
	float rating = 0;
	int entrylevel = 1;
	bool canbuild = false;
	int clothHair;
	int clothHead;
	int clothMask;
	int clothHand;
	int clothNeck;
	int clothShirt;
	int clothPants;
	int clothFeet;
	int clothBack;
	bool gaiaplant = false;
	int gaiajumlah = 0;
	int publics = 0;
	int legends = 0;
	int displayshelf;
	int price = 0;
	bool sold = false;
	bool peritem = false;
	bool packetrandom11 = false;
	bool packetrandom22 = false;
	bool packetrandom33 = false;
	string packetrandom1 = "";
	string packetrandom2 = "";
	string packetrandom3 = "";
	string monitor = "";
};
struct InfoDropedItems {
	int itemid = 0;
	int quantity = 0;
	int positionx = 0;
	int positiony = 0;
};
struct DroppedItem { // TODO
	int id = 0;
	int uid = -1;
	int count = 0;
	int x = -1, y = -1;
};
vector<InfoDropedItems> dropedItems;
struct WorldInfo {
	int gravity = 0;
	int width = 100;
	vector<string> accessed;
	int stuffID = 0;
	int height = 60;
	int bgID = 0;
	bool nuked = false;
	int magY = 100;
	int magX = 60;
	int hw_red = false;
	int hw_green = false;
	int hw_blue = false;
	string name = "TEST";
	int ownerID = 0;
	bool areLogsEnabled = false;
	bool squaresign = 0;
	WorldItem* items;
	int droppedCount = 0;
	string owner = "";
	string Displayowner = "";
	vector<DroppedItem> droppedItems;
	int droppedItemUid = 0;
	int geigerX = 0;
	int geigerY = 0;
	bool isPublic = false;
	bool islegend = false;
	bool isdoctor = false;
	bool islvltitle = false;
	bool allowMod = false;
	bool pIsVip = false;
	bool pIsMod = false;
	bool pIsDev = false;
	bool pIsPlay = false;
	bool pIsAdmin = false;
	bool pIsKing = false;
	bool isEvent = true;
	bool noclip = false;
	int ghostalr = 0;
	int invisalr = 0;
	int weather = 0;
	int stuff_gravity = 0;
	int stuff_invert = 0;
	int stuff_spin = 0;
	bool rainbows = true;
	bool silence = false;
	int magitem = 0;

	bool isXenonite = false;
	bool isCreated = false;
	bool canbuild = false;
	bool magplant = false;
	bool gaiaplant = false;
	int maggems = 0;
	int gaiajumlah = 0;
	int jumlahitem1 = 0;
	int jenisitem1 = 0;
	int jumlahitem2 = 0;
	int jenisitem2 = 0;
	int jumlahitem3 = 0;
	int jenisitem3 = 0;
	int jumlahitem4 = 0;
	int jenisitem4 = 0;
	int jumlahitem5 = 0;
	int jenisitem5 = 0;
	int jumlahitem6 = 0;
	int jenisitem6 = 0;
	int jumlahitem7 = 0;
	int jenisitem7 = 0;
	int venditem = 0;
	int jumlahvend = 0;
	int pricevend = 0;
	int remote = 0;
	int tempo = 100;
	int disable_music_render = 0;
	int disable_music = 0;
	bool vendsold = false;
	bool isCasino = false;
	vector<string> banned;
	vector<string> worldaccess;
};
struct AWorld {
	WorldInfo* ptr;
	WorldInfo info;
	int id;
};
struct TileExtra {
	int packetType;
	int characterState;
	float objectSpeedX;
	int punchX;
	int punchY;
	int charStat;
	int blockid;
	int visual;
	int signs;
	int backgroundid;
	int displayblock;
	int time;
	int netID;
	int weatherspeed;
	int bpm;
};
struct BlockVisual {
	int packetType;
	int characterState;
	int punchX;
	int punchY;
	float x;
	float y;
	int plantingTree;
	float XSpeed;
	float YSpeed;
	int charStat;
	int blockid;
	int visual;
	int signs;
	int backgroundid;
	int displayblock;
	int time;
	int netID;
};
enum BlockTypes {
	FOREGROUND,
	BACKGROUND,
	CONSUMABLE,
	SEED,
	PAIN_BLOCK,
	BEDROCK,
	MAIN_DOOR,
	SIGN,
	DOOR,
	CLOTHING,
	FIST,
	WRENCH,
	CHECKPOINT,
	LOCK,
	GATEWAY,
	TREASURE,
	WEATHER,
	TRAMPOLINE,
	TOGGLE_FOREGROUND,
	CHEMICAL_COMBINER,
	SWITCH_BLOCK,
	SFX_FOREGROUND,
	RANDOM_BLOCK,
	PORTAL,
	PLATFORM,
	MAILBOX,
	MAGIC_EGG,
	CRYSTAL,
	GEMS,
	DEADLY,
	CHEST,
	FACTION,
	BULLETIN_BOARD,
	BOUNCY,
	ANIM_FOREGROUND,
	COMPONENT,
	SUCKER,
	FISH,
	STEAM,
	GROUND_BLOCK,
	DISPLAY,
	STORAGE,
	VENDING,
	DONATION,
	PHONE,
	SEWINGMACHINE,
	CRIME_VILLAIN,
	PROVIDER,
	UNKNOWN
};
#define Property_Zero 0
#define Property_NoSeed 1
#define Property_Dropless 2
#define Property_Beta 4
#define Property_Mod 8
#define Property_Untradable 16
#define Property_Wrenchable 32
#define Property_MultiFacing 64
#define Property_Permanent 128
#define Property_AutoPickup 256
#define Property_WorldLock 512
#define Property_NoSelf 1024
#define Property_RandomGrow 2048
#define Property_Public 4096
class WorldDB {
public:
	WorldInfo get(string name);
	AWorld get2(string name);
	void flush(WorldInfo info);
	void flush2(AWorld info);
	void save(AWorld info);
	void saveAll();
	void saveRedundant();
	void remove(string name);
	vector<WorldInfo> getRandomWorlds();
	WorldDB();
private:
	vector<WorldInfo> worlds;
};
namespace packet {
	void storerequest(ENetPeer* peer, string message) {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnStoreRequest"), message));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	void hubrequest(ENetPeer* peer, string message) {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnCommunityHubRequest"), message));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}
WorldDB::WorldDB() {
}
WorldInfo generateCleanWorld(string name, int width, int height)
{
	WorldInfo world;
	world.name = name;
	world.nuked = false;
	world.width = width;
	world.height = height;
	world.items = new WorldItem[world.width * world.height];
	for (int i = 0; i < world.width * world.height; i++)
	{
		if (i >= 3800 && i < 5400 && !(rand() % 50)) { world.items[i].foreground = 0; }
		else if (i >= 3700 && i < 5400) {
			if (i > 5000) {
				if (i % 7 == 0) { world.items[i].foreground = 0; }
				else { world.items[i].foreground = 0; }
			}
			else { world.items[i].foreground = 0; }
		}
		else if (i >= 5400) { world.items[i].foreground = 8; }
		if (i >= 3700)
			world.items[i].background = 14;
		if (i == 3650)
			world.items[i].foreground = 6; //BALTOS DURYS
		else if (i >= 3600 && i < 3700)
			world.items[i].foreground = 0; //TUSCIA DURU LYGIS
		if (i == 3750)
			world.items[i].foreground = 8; //BEDROCK
	}
	return world;
}
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
WorldInfo generateUranusWorld(string name, int width, int height)
{
	WorldInfo world;
	world.name = name;
	world.nuked = false;
	world.width = width;
	world.height = height;
	int mainDoorX = (rand() % (world.width - 4)) + 2;
	world.items = new WorldItem[world.width * world.height];
	int treasure = (rand() % 4400);
	for (int i = 0; i < world.width * world.height; i++)
	{
		if (i >= 100 && i < 4470 && !(rand() % 99)) { world.items[i].foreground = 9440; }
		else if (i == treasure) { world.items[i].foreground = 7628; }
		else if (i > 1200 && i < 4470 && !(rand() % 99)) { world.items[i].foreground = 9442; }
		else if (i > 2500 && i < 4470 && !(rand() % 99)) { world.items[i].foreground = 7960; }
		else if (i >= 0 && i < 4500) {
			world.items[i].foreground = 1132;
		}
		if (i >= 0 && i <= 29)
			world.items[i].foreground = 8;
		if (i >= 0)
			world.items[i].background = 9438;
		if (i == 550 + mainDoorX) {
			world.items[i].foreground = 6;
		}
		if (i >= 1000 && i <= 1030)
			world.items[i].foreground = 9444;
		if (i >= 4470)
			world.items[i].foreground = 8;
	}
	return world;
}
WorldInfo MakeWorldFromScratch(string name, int width, int height, int dirtType = 2, int lavaType = 4, int mainDoorType = 6, int bedrockType = 8, int rockType = 10, int caveBackgroundType = 14)
{
	if (usedgenworld == true)
	{
		usedgenworld = false;
		int width3 = genwidth;
		int height3 = genheight;
		int dirttype3 = genforeground;
		int bedrocktype3 = genbedrock;
		int cavebackgroundtype3 = genbackground;
		WorldInfo world;
		world.name = name;
		world.width = width;
		world.height = height;
		world.items = new WorldItem[world.width * world.height];
		GenerateRegularWorld(&world, width3, height3, dirttype3, lavaType, mainDoorType, bedrocktype3, rockType, cavebackgroundtype3);
		genwidth = 0;
		genheight = 0;
		genforeground = 0;
		genbedrock = 0;
		genbackground = 0;
		return world;
	}
	else {
		WorldInfo world;
		world.name = name;
		world.width = width;
		world.height = height;
		world.items = new WorldItem[world.width * world.height];
		GenerateRegularWorld(&world, width, height, dirtType, lavaType, mainDoorType, bedrockType, rockType, caveBackgroundType);
		return world;
	}

}
WorldInfo generateMarsWorld(string name, int width, int height)
{
	WorldInfo world;
	world.name = name;
	world.nuked = false;
	world.width = width;
	world.height = height;
	world.items = new WorldItem[world.width * world.height];
	for (int i = 0; i < world.width * world.height; i++)
	{
		if (i >= 3800 && i < 5400 && !(rand() % 50)) { world.items[i].foreground = 150; }
		else if (i >= 3700 && i < 5400) {
			if (i > 5000) {
				if (i % 7 == 0) { world.items[i].foreground = 45; }
				else { world.items[i].foreground = 25; }
			}
			else { world.items[i].foreground = 52; }
		}
		else if (i >= 5400) { world.items[i].foreground = 82; }
		if (i >= 3700)
			world.items[i].background = 114;
		if (i == 3650)
			world.items[i].foreground = 63;
		else if (i >= 3600 && i < 3700)
			world.items[i].foreground = 16;
		if (i == 3750)
			world.items[i].foreground = 84;
	}
	return world;
}
WorldInfo ClearWorld(string name, int width, int height)
{
	WorldInfo world;
	world.name = name;
	world.nuked = false;
	world.width = width;
	world.height = height;
	world.items = new WorldItem[world.width * world.height];
	for (int i = 0; i < world.width * world.height; i++)
	{
		if (i >= 3800 && i < 5400 && !(rand() % 50)) { world.items[i].foreground = 0; }
		else if (i >= 3700 && i < 5400) {
			if (i > 5000) {
				if (i % 7 == 0) { world.items[i].foreground = 0; }
				else { world.items[i].foreground = 0; }
			}
			else { world.items[i].foreground = 2; }
		}
		else if (i >= 5400) { world.items[i].foreground = 8; }
		if (i >= 3700)
			world.items[i].background = 0;
		if (i == 3650)
			world.items[i].foreground = 6;
		else if (i >= 3600 && i < 3700)
			world.items[i].foreground = 16; //fixed the grass in the world!
		if (i == 3750)
			world.items[i].foreground = 8;
	}
	return world;
}
int PlayerDB::guildRegister(ENetPeer* peer, string guildName, string guildStatement, string guildFlagfg, string guildFlagbg) {
	string uname = guildName;
	if (guildName.find(" ") != string::npos || guildName.find(".") != string::npos || guildName.find(",") != string::npos || guildName.find("?") != string::npos || guildName.find("@") != string::npos || guildName.find("[") != string::npos || guildName.find("]") != string::npos || guildName.find("#") != string::npos || guildName.find("<") != string::npos || guildName.find(">") != string::npos || guildName.find(":") != string::npos || guildName.find("{") != string::npos || guildName.find("}") != string::npos || guildName.find("|") != string::npos || guildName.find("+") != string::npos || guildName.find("_") != string::npos || guildName.find("~") != string::npos || guildName.find("-") != string::npos || guildName.find("!") != string::npos || guildName.find("$") != string::npos || guildName.find("%") != string::npos || guildName.find("^") != string::npos || guildName.find("&") != string::npos || guildName.find("`") != string::npos || guildName.find("*") != string::npos || guildName.find("(") != string::npos || guildName.find(")") != string::npos || guildName.find("=") != string::npos || guildName.find("'") != string::npos || guildName.find(";") != string::npos || guildName.find("/") != string::npos) {
		return -1;
	}
	toUpperCase(uname);
	if (guildName.length() < 3) {
		return -2;
	}
	if (uname == "CON" || uname == "NUL" || uname == "PRN" || uname == "AUX" || uname == "CLOCK$" || uname == "COM0" || uname == "COM1" || uname == "COM2" || uname == "COM3" || uname == "COM4" || uname == "COM5" || uname == "COM6" || uname == "COM7" || uname == "COM8" || uname == "COM9" || uname == "LPT0" || uname == "LPT1" || uname == "LPT2" || uname == "LPT3" || uname == "LPT4" || uname == "LPT5" || uname == "LPT6" || uname == "LPT7" || uname == "LPT8" || uname == "LPT9")
	{
		return -1;
	}
	if (guildName.length() > 15) {
		return -3;
	}
	int fg;
	int bg;
	try {
		fg = stoi(guildFlagfg);
	}
	catch (std::invalid_argument& e) {
		return -6;
	}
	try {
		bg = stoi(guildFlagbg);
	}
	catch (std::invalid_argument& e) {
		return -5;
	}
	if (guildFlagbg.length() > 4) {
		return -7;
	}
	if (guildFlagfg.length() > 4) {
		return -8;
	}
	string fixedguildName = PlayerDB::getProperName(guildName);
	std::ifstream ifs("guilds/" + fixedguildName + ".json");
	if (ifs.is_open()) {
		return -4;
	}
	return 1;
}
void WorldDB::remove(string name) {
	try {
		for (int i = 0; i < worlds.size(); i++)
		{
			WorldInfo w = worlds.at(i);
			if (getStrLower(name) == getStrLower(w.name))
			{
				worlds.erase(worlds.begin() + i);
			}
		}
		std::remove(("worlds/" + name + ".json").c_str());
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
			throw 3; // wrong name
	}
	if (name == "EXIT") {
		throw 3;
	}
	if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
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
	try {
		std::ifstream ifs("worlds/" + name + ".json");
		if (ifs.is_open()) {
			json j;
			ifs >> j;
			WorldInfo info;
			info.name = j["name"].get<string>();
			info.width = j["width"];
			info.nuked = j["nuked"];
			info.magY = j["magY"];
			info.magX = j["magX"];
			info.nuked = j["nuked"];
			info.height = j["height"];
			info.weather = j["weather"].get<int>();
			info.stuff_gravity = j["stuff_gravity"].get<int>();
			info.stuff_invert = j["stuff_invert"].get<int>();
			info.stuff_spin = j["stuff_spin"].get<int>();
			info.bgID = j["bgID"].get<int>();
			info.hw_red = j["hwr"].get<int>();
			info.hw_green = j["hwg"].get<int>();
			info.hw_blue = j["hwb"].get<int>();
			info.owner = j["owner"].get<string>();
			vector <string>frns;
			for (int i = 0; i < j["access"].size(); i++) {
				info.accessed.push_back(j["access"][i]);
			}
			vector<string>accessed;
			vector<DroppedItem> droppedItems;
			info.droppedCount = j["dc"].get<int>();
			info.Displayowner = j["Displayowner"].get<string>();
			info.isPublic = j["isPublic"];
			info.islegend = j["lname"];
			info.allowMod = j["allowMod"];
			info.isXenonite = j["isXenonite"];
			info.pIsVip = j["isVip"];
			info.pIsMod = j["isMod"];
			info.stuffID = j["stuff"].get<int>();
			info.droppedItemUid = j["droppedItemUid"].get<int>();
			info.gravity = j["gravity"].get<int>();
			info.pIsDev = j["isDev"];
			info.pIsPlay = j["isPlay"];
			info.magplant = j["magplant"].get<bool>();
			info.canbuild = j["canbuild"].get<bool>();
			info.gaiaplant = j["gaiaplant"].get<bool>();
			info.rainbows = j["rainbows"].get<bool>();
			info.silence = j["silence"].get<bool>();
			info.maggems = j["maggems"].get<int>();
			info.magitem = j["magitem"].get<int>();
			info.gaiajumlah = j["gaiajumlah"].get<int>();
			info.jumlahitem1 = j["jumlahitem1"].get<int>();
			info.venditem = j["venditem"].get<int>();
			info.pricevend = j["pricevend"].get<int>();
			info.jumlahvend = j["jumlahvend"].get<int>();
			info.jenisitem1 = j["jenisitem1"].get<int>();
			info.jumlahitem2 = j["jumlahitem2"].get<int>();
			info.jenisitem2 = j["jenisitem2"].get<int>();
			info.jumlahitem6 = j["jumlahitem6"].get<int>();
			info.jenisitem6 = j["jenisitem6"].get<int>();
			info.jumlahitem3 = j["jumlahitem3"].get<int>();
			info.jenisitem3 = j["jenisitem3"].get<int>();
			info.jumlahitem4 = j["jumlahitem4"].get<int>();
			info.jenisitem4 = j["jenisitem4"].get<int>();
			info.jumlahitem7 = j["jumlahitem7"].get<int>();
			info.jenisitem7 = j["jenisitem7"].get<int>();
			info.jumlahitem5 = j["jumlahitem5"].get<int>();
			info.jenisitem5 = j["jenisitem5"].get<int>();
			info.disable_music = j["disable_music"].get<int>();
			info.disable_music_render = j["disable_music_render"].get<int>();
			info.tempo = j["tempo"].get<int>();

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
				info.items[i].foreground = tiles[i]["fg"];
				info.items[i].background = tiles[i]["bg"];
				info.items[i].text = tiles[i]["text"].get<string>();
				info.items[i].label = tiles[i]["label"].get<string>();
				info.items[i].destWorld = tiles[i]["destWorld"].get<string>();
				info.items[i].destId = tiles[i]["destId"].get<string>();
				info.items[i].currId = tiles[i]["currId"].get<string>();
				info.items[i].password = tiles[i]["password"].get<string>();
				info.items[i].monitor = tiles[i]["monitor"].get<string>();
				info.items[i].mail = tiles[i]["mail"].get<string>();
				info.items[i].packetrandom1 = tiles[i]["packetrandom1"].get<string>();
				info.items[i].packetrandom2 = tiles[i]["packetrandom2"].get<string>();
				info.items[i].packetrandom3 = tiles[i]["packetrandom3"].get<string>();
				info.items[i].bulletinmsg = tiles[i]["bulletinmsg"].get<string>();
				info.items[i].flipped = tiles[i]["flip"].get<bool>();
				info.items[i].packetrandom11 = tiles[i]["packetrandom11"].get<bool>();
				info.items[i].packetrandom22 = tiles[i]["packetrandom22"].get<bool>();
				info.items[i].packetrandom33 = tiles[i]["packetrandom33"].get<bool>();
				info.items[i].water = tiles[i]["water"].get<bool>();
				info.items[i].green = tiles[i]["green"].get<bool>();
				info.items[i].red = tiles[i]["red"].get<bool>();
				info.items[i].blue = tiles[i]["blue"].get<bool>();
				info.items[i].fire = tiles[i]["fire"].get<bool>();
				info.items[i].active = tiles[i]["a"].get<bool>();
				info.items[i].sold = tiles[i]["sold"].get<bool>();
				info.items[i].canbuild = tiles[i]["canbuild"].get<bool>();
				info.items[i].peritem = tiles[i]["peritem"].get<bool>();
				info.items[i].gaiajumlah = tiles[i]["gaiajumlah"].get<int>();
				info.items[i].jenisitem1 = tiles[i]["jenisitem1"].get<int>();
				info.items[i].jumlahitem2 = tiles[i]["jumlahitem2"].get<int>();
				info.items[i].jenisitem2 = tiles[i]["jenisitem2"].get<int>();
				info.items[i].jumlahitem3 = tiles[i]["jumlahitem3"].get<int>();
				info.items[i].jenisitem3 = tiles[i]["jenisitem3"].get<int>();
				info.items[i].jumlahitem4 = tiles[i]["jumlahitem4"].get<int>();
				info.items[i].jenisitem4 = tiles[i]["jenisitem4"].get<int>();
				info.items[i].jumlahitem5 = tiles[i]["jumlahitem5"].get<int>();
				info.items[i].jenisitem5 = tiles[i]["jenisitem5"].get<int>();
				info.items[i].intdata = tiles[i]["intdata"].get<int>();
				info.items[i].packetrandom111 = tiles[i]["packetrandom111"].get<int>();
				info.items[i].packetrandom222 = tiles[i]["packetrandom222"].get<int>();
				info.items[i].packetrandom333 = tiles[i]["packetrandom333"].get<int>();
				info.items[i].bulletinhide = tiles[i]["bulletinhide"].get<int>();
				info.items[i].bulletinpublic = tiles[i]["bulletinpublic"].get<int>();
				info.items[i].mailcount = tiles[i]["mailcount"].get<int>();
				info.items[i].clothHair = tiles[i]["clothHair"].get<int>();
				info.items[i].clothHead = tiles[i]["clothHead"].get<int>();
				info.items[i].clothMask = tiles[i]["clothMask"].get<int>();
				info.items[i].clothHand = tiles[i]["clothHand"].get<int>();
				info.items[i].clothNeck = tiles[i]["clothNeck"].get<int>();
				info.items[i].clothShirt = tiles[i]["clothShirt"].get<int>();
				info.items[i].clothPants = tiles[i]["clothPants"].get<int>();
				info.items[i].clothFeet = tiles[i]["clothFeet"].get<int>();
				info.items[i].clothBack = tiles[i]["clothBack"].get<int>();
				info.items[i].price = tiles[i]["price"].get<int>();
				info.items[i].publics = tiles[i]["publics"].get<int>();
				info.items[i].legends = tiles[i]["legends"].get<int>();
			}
			worlds.push_back(info);
			ret.id = worlds.size() - 1;
			ret.info = info;
			ret.ptr = &worlds.at(worlds.size() - 1);
			ifs.close();
			return ret;
		}
		else {
			if (useduranusblast == true)
			{
				useduranusblast = false;
				WorldInfo info = generateUranusWorld(name, 30, 150);
				worlds.push_back(info);
				ret.id = worlds.size() - 1;
				ret.info = info;
				ret.ptr = &worlds.at(worlds.size() - 1);
				return ret;
			}
			else {
				WorldInfo info = MakeWorldFromScratch(name, 100, 60);
				worlds.push_back(info);
				ret.id = worlds.size() - 1;
				ret.info = info;
				ret.ptr = &worlds.at(worlds.size() - 1);
				return ret;
			}
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
	throw 1;
}
WorldInfo WorldDB::get(string name) {
	return this->get2(name).info;
}
void WorldDB::flush(WorldInfo info)
{
	try {
		std::ofstream o("worlds/" + info.name + ".json");
		if (!o.is_open()) {
			cout << GetLastError() << endl;
		}
		json j;
		j["name"] = info.name;
		j["width"] = info.width;
		j["height"] = info.height;
		j["magY"] = info.magY;
		j["magX"] = info.magX;
		j["nuked"] = info.nuked;
		j["owner"] = info.owner;
		j["weather"] = info.weather;
		j["stuff_gravity"] = info.stuff_gravity;
		j["stuff_invert"] = info.stuff_invert;
		j["stuff_spin"] = info.stuff_spin;
		j["bgID"] = info.bgID;
		j["hwr"] = info.hw_red;
		j["hwg"] = info.hw_green;
		j["hwb"] = info.hw_blue;
		j["access"] = info.accessed;
		j["Displayowner"] = info.Displayowner;
		j["allowMod"] = info.allowMod;
		j["isXenonite"] = info.isXenonite;
		j["magplant"] = info.magplant;
		j["canbuild"] = info.canbuild;
		j["gaiaplant"] = info.gaiaplant;
		j["rainbows"] = info.rainbows;
		j["silence"] = info.silence;
		j["maggems"] = info.maggems;
		j["magitem"] = info.magitem;
		j["gaiajumlah"] = info.gaiajumlah;
		j["jenisitem1"] = info.jenisitem1;
		j["jumlahitem1"] = info.jumlahitem1;
		j["jenisitem2"] = info.jenisitem2;
		j["jumlahitem2"] = info.jumlahitem2;
		j["jenisitem3"] = info.jenisitem3;
		j["jumlahitem3"] = info.jumlahitem3;
		j["jenisitem4"] = info.jenisitem4;
		j["jumlahitem4"] = info.jumlahitem4;
		j["jenisitem5"] = info.jenisitem5;
		j["jumlahitem5"] = info.jumlahitem5;
		j["jenisitem6"] = info.jenisitem6;
		j["jumlahitem6"] = info.jumlahitem6;
		j["jenisitem7"] = info.jenisitem7;
		j["jumlahitem7"] = info.jumlahitem7;
		j["venditem"] = info.venditem;
		j["pricevend"] = info.pricevend;
		j["jumlahvend"] = info.jumlahvend;
		j["isVip"] = info.pIsVip;
		j["stuff"] = info.stuffID;
		j["droppedItemUid"] = info.droppedItemUid;
		j["gravity"] = info.gravity;
		j["isMod"] = info.pIsMod;
		j["isDev"] = info.pIsDev;
		j["isPlay"] = info.pIsPlay;
		j["isPublic"] = info.isPublic;
		j["disable_music"] = info.disable_music;
		j["disable_music_render"] = info.disable_music_render;
		j["tempo"] = info.tempo;
		j["dc"] = info.droppedItems.size();
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
			tile["text"] = info.items[i].text;
			tile["label"] = info.items[i].label;
			tile["destWorld"] = info.items[i].destWorld;
			tile["destId"] = info.items[i].destId;
			tile["currId"] = info.items[i].currId;
			tile["password"] = info.items[i].password;
			tile["monitor"] = info.items[i].monitor;
			tile["a"] = info.items[i].active;
			tile["r"] = info.items[i].flipped;
			tile["int"] = info.items[i].intdata;
			tile["a"] = info.items[i].activated;
			tile["dshelf1"] = info.items[i].dshelf1;
			tile["dshelf2"] = info.items[i].dshelf2;
			tile["dshelf3"] = info.items[i].dshelf3;
			tile["dshelf4"] = info.items[i].dshelf4;
			tile["cg"] = info.items[i].growth_time;
			tile["fu"] = info.items[i].fruit;
			tile["w"] = info.items[i].water;
			tile["f"] = info.items[i].fire;
			tile["red"] = info.items[i].red;
			tile["gre"] = info.items[i].green;
			tile["blu"] = info.items[i].blue;
			tile["es"] = info.items[i].evolvestage;
			tile["fire"] = info.items[i].fire;
			tile["sold"] = info.items[i].sold;
			tile["canbuild"] = info.items[i].canbuild;
			tile["intdata"] = info.items[i].intdata;
			tile["gaiajumlah"] = info.items[i].gaiajumlah;
			tile["packetrandom111"] = info.items[i].packetrandom111;
			tile["packetrandom222"] = info.items[i].packetrandom222;
			tile["packetrandom333"] = info.items[i].packetrandom333;
			tile["bulletinhide"] = info.items[i].bulletinhide;
			tile["mail"] = info.items[i].mail;
			tile["mailcount"] = info.items[i].mailcount;
			tile["bulletinpublic"] = info.items[i].bulletinpublic;
			tile["bulletinmsg"] = info.items[i].bulletinmsg;
			tile["packetrandom1"] = info.items[i].packetrandom1;
			tile["packetrandom2"] = info.items[i].packetrandom2;
			tile["packetrandom3"] = info.items[i].packetrandom3;
			tile["packetrandom11"] = info.items[i].packetrandom11;
			tile["packetrandom22"] = info.items[i].packetrandom22;
			tile["packetrandom33"] = info.items[i].packetrandom33;
			tile["jenisitem1"] = info.items[i].jenisitem1;
			tile["jumlahitem1"] = info.items[i].jumlahitem1;
			tile["jenisitem2"] = info.items[i].jenisitem2;
			tile["jumlahitem2"] = info.items[i].jumlahitem2;
			tile["jenisitem3"] = info.items[i].jenisitem3;
			tile["jumlahitem3"] = info.items[i].jumlahitem3;
			tile["jenisitem4"] = info.items[i].jenisitem4;
			tile["jumlahitem4"] = info.items[i].jumlahitem4;
			tile["jenisitem5"] = info.items[i].jenisitem5;
			tile["jumlahitem5"] = info.items[i].jumlahitem5;
			tile["peritem"] = info.items[i].peritem;
			tile["clothHair"] = info.items[i].clothHair;
			tile["clothHead"] = info.items[i].clothHead;
			tile["clothMask"] = info.items[i].clothMask;
			tile["clothHand"] = info.items[i].clothHand;
			tile["clothNeck"] = info.items[i].clothNeck;
			tile["clothShirt"] = info.items[i].clothShirt;
			tile["clothPants"] = info.items[i].clothPants;
			tile["clothFeet"] = info.items[i].clothFeet;
			tile["clothBack"] = info.items[i].clothBack;
			tile["price"] = info.items[i].price;
			tile["publics"] = info.items[i].publics;
			tile["legends"] = info.items[i].legends;
			tiles.push_back(tile);
		}
		j["tiles"] = tiles;
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
	try {
		if (info.items != nullptr)
		{
			delete[] info.items;
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
void WorldDB::flush2(AWorld info)
{
	this->flush(info.info);
}
void WorldDB::save(AWorld info)
{
	flush2(info);
	//delete info.info.items;
	worlds.erase(worlds.begin() + info.id);
}
void WorldDB::saveAll()
{
	for (int i = 0; i < worlds.size(); i++) {
		flush(worlds.at(i));
		//delete worlds.at(i).items;
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
BYTE* packBlockVisual222(TileExtra* dataStruct)
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
WorldDB worldDB;
bool isHereSave(ENetPeer* peer, ENetPeer* peer2)
{
	return ((PlayerInfo*)(peer->data))->currentWorld == ((PlayerInfo*)(peer2->data))->currentWorld;
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

int getPlayersCountInWorldSave(string name)
{
	int count = 0;
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (((PlayerInfo*)(currentPeer->data))->isinv == false)
		{
			if (((PlayerInfo*)(currentPeer->data))->currentWorld == name)
				count++;
		}
	}
	return count;
}
void sendPlayerLeaveSave(ENetPeer* peer, PlayerInfo* player)
{
	ENetPeer* currentPeer;
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(player->netID) + "\n"));
	GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorldSave(player->currentWorld)) + "`` `5others here>```w"));
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (((PlayerInfo*)(currentPeer->data))->currentWorld == "EXIT")
			continue;
		if (((PlayerInfo*)(currentPeer->data))->isIn == false)
			continue;
		if (isHereSave(peer, currentPeer)) {
			{
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				{
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet);
				}
			}
			{
			}
		}
	}
	delete p.data;
	delete p2.data;
}
void saveAllWorlds()
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

void saveMyWorld(ENetPeer* peer)
{
	AWorld info = worldDB.get2(((PlayerInfo*)(peer->data))->currentWorld);
	worldDB.save(info);
	cout << "[INFO] Player " + ((PlayerInfo*)(peer->data))->rawName << " saved his " << ((PlayerInfo*)(peer->data))->currentWorld << " world" << endl;
	Player::OnConsoleMessage(peer, "`w[`4SYSTEM`w] `5World Saved`o!");
	Player::OnConsoleMessage(peer, "`w[`4SYSTEM`w] `5Dropped Items Cleared`o!");
}
struct ItemDefinition {
	int id;
	string name;
	int rarity;
	int breakHits;
	int growTime;
	ClothTypes clothType;
	BlockTypes blockType;
	string description = "This item has no description.";
	string MultiFacing = "This item can be placed in both directions.";
	int properties;
};
vector<ItemDefinition> itemDefs;
vector<DroppedItem> droppedItems;
ItemDefinition getItemDef(int id)
{
	if (id < itemDefs.size() && id > -1)
		return itemDefs.at(id);
	throw 0;
	return itemDefs.at(0);
}
ItemDefinition GetItemDef(int id)
{
	if (id < itemDefs.size() && id > -1)
		return itemDefs.at(id);
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
void buildItemsDatabase()
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
			def.breakHits = atoi(ex[7].c_str());
			vector<string> properties = explode(", ", ex[3]);
			def.properties = Property_Zero;
			for (auto &prop : properties)
			{
				if (prop == "NoSeed")
					def.properties += Property_NoSeed;
				if (prop == "Dropless")
					def.properties += Property_Dropless;
				if (prop == "Beta")
					def.properties += Property_Beta;
				if (prop == "Mod")
					def.properties += Property_Mod;
				if (prop == "Untradable")
					def.properties += Property_Untradable;
				if (prop == "Wrenchable")
					def.properties += Property_Wrenchable;
				if (prop == "MultiFacing")
					def.properties += Property_MultiFacing;
				if (prop == "Permanent")
					def.properties += Property_Permanent;
				if (prop == "AutoPickup")
					def.properties += Property_AutoPickup;
				if (prop == "WorldLock")
					def.properties += Property_WorldLock;
				if (prop == "NoSelf")
					def.properties += Property_NoSelf;
				if (prop == "RandomGrow")
					def.properties += Property_RandomGrow;
				if (prop == "Public")
					def.properties += Property_Public;
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
			else if (bt == "Crystal") {
				def.blockType = BlockTypes::CRYSTAL;
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
				//cout << "[!] Unknown property for ID: " << def.id << " which wants property " << bt << endl;
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
				cout << "[!] Critical error! Unordered database at item " << std::to_string(current) << "/" << std::to_string(def.id) << "!" << endl;
			}
			maxItems = def.id;
			itemDefs.push_back(def);
		}
	}
	craftItemDescriptions();
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
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 4);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	return data;
}
BYTE* packStuffVisual(TileExtra* dataStruct, int options, int gravity)
{
	BYTE* data = new BYTE[102];
	for (int i = 0; i < 102; i++)
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
	memcpy(data + 56, &dataStruct->blockid, 2);
	memcpy(data + 58, &dataStruct->backgroundid, 2);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	memcpy(data + 68, &gravity, 4);
	memcpy(data + 70, &options, 4);
	return data;
}
void SendPacketRaw(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
{
	ENetPacket* p;
	if (peer)
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
void SendPacketRaw2(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
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
void updatetile(ENetPeer* peer, int netID, int x, int y)
{
	BlockVisual data3;
	data3.packetType = 0x5;
	data3.characterState = 8;
	data3.charStat = 8;
	data3.blockid = 2;
	data3.backgroundid = 2;
	data3.visual = 0x03000000; //replace this with active blockstate.(Im on phone cant remember rn) 
	data3.punchX = x;
	data3.punchY = y;
	data3.netID = netID;
	SendPacketRaw2(192, packBlockVisual(&data3), 100, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}
void updateRotatedItem(ENetPeer* peer, int foreground, int x, int y, string text, int background)
{
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
	int hmm = 8, wot = text.length(), lol = 0x00200000, wut = 5;
	int yeh = hmm + 3 + 1, idk = 15 + wot, lmao = -1, yey = 2; //idk = text_len + 15, wut = type(?), wot = text_len, yey = len of text_len
	int ok = 52 + idk;
	int kek = ok + 4, yup = ok - 8 - idk;
	int thonk = 4, magic = 56, wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, thonk);
	memcpy(data + yeh, &hmm, thonk); //read discord
	memcpy(data + yup, &x, 4);
	memcpy(data + yup + 4, &y, 4);
	memcpy(data + 4 + yup + 4, &idk, thonk);
	memcpy(data + magic, &foreground, yey);
	memcpy(data + magic + 2, &background, yey); // gai?
	memcpy(data + thonk + magic, &lol, thonk);
	memcpy(data + magic + 4 + thonk, &yey, 1);
	memcpy(data + wow, &wot, yey); //data + wow = text_len
	memcpy(data + yey + wow, text.c_str(), wot); //data + text_len_len + text_len_offs = text
	memcpy(data + ok, &lmao, thonk); //end ?
	memcpy(p->data, &thonk, thonk);
	memcpy((char*)p->data + thonk, data, kek); //kek = data_len
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
void updateEntrance(ENetPeer* peer, int foreground, int x, int y, bool open, int bg) {
	BYTE* data = new BYTE[69];// memset(data, 0, 69);
	for (int i = 0; i < 69; i++) data[i] = 0;
	int four = 4; int five = 5; int eight = 8;
	int huhed = (65536 * bg) + foreground; int loled = 128;

	memcpy(data, &four, 4);
	memcpy(data + 4, &five, 4);
	memcpy(data + 16, &eight, 4);
	memcpy(data + 48, &x, 4);
	memcpy(data + 52, &y, 4);
	memcpy(data + 56, &eight, 4);
	memcpy(data + 60, &foreground, 4);
	memcpy(data + 62, &bg, 4);

	if (open) {
		int state = 0;
		memcpy(data + 66, &loled, 4);
		memcpy(data + 68, &state, 4);
	}
	else {
		int state = 100;
		int yeetus = 25600;
		memcpy(data + 67, &yeetus, 5);
		memcpy(data + 68, &state, 4);
	}
	ENetPacket* p = enet_packet_create(data, 69, ENET_PACKET_FLAG_RELIABLE);

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
inline void SendGrowpedia(ENetPeer* peer) {
	string level1 = "", level2 = "", level3 = "", level4 = "", level5 = "", level6 = "", level7 = "", level8 = "", level9 = "", level10 = "", level11 = "", level12 = "", level13 = "", level14 = "", level15 = "", level16 = "", level17 = "", level18 = "", level19 = "", level20 = "";
	if (static_cast<PlayerInfo*>(peer->data)->level >= 1) {
		level1 = "`oUnlocked: 1000 Gems``";
	}
	else {
		level1 = "`a(Locked) 1000 Gems``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 2) {
		level2 = "`oUnlocked: 75 Chandelier``";
	}
	else {
		level2 = "`a(Locked) 75 Chandelier``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 3) {
		level3 = "`oUnlocked: Growtoken``";
	}
	else {
		level3 = "`a(Locked) Growtoken``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 4) {
		level4 = "`oUnlocked: Earth Mastery: 1% chance to break dirt in a single hit``|left|5050|\nadd_label_with_icon|sml|`oUnlocked: Diamond Wings``";
	}
	else {
		level4 = "`a(Locked) Earth Mastery: 1% chance to break dirt in a single hit``|left|5050|\nadd_label_with_icon|sml|`a(Locked) Diamond Wings``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 5) {
		level5 = "`oUnlocked: 5 Growtokens``";
	}
	else {
		level5 = "`a(Locked) 5 Growtokens``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 6) {
		level6 = "`oUnlocked: Earth Mastery (level 2) - Chance increase to 2%``";
	}
	else {
		level6 = "`a(Locked) Earth Mastery (level 2) - Chance increase to 2%``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 7) {
		level7 = "`oUnlocked: Punch Potion``";
	}
	else {
		level7 = "`a(Locked) Punch Potion``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 8) {
		level8 = "`oUnlocked: Flawless: 1% chance to decrease seed grow time when planting``|left|7186|\nadd_label_with_icon|sml|`oUnlocked: Earth Mastery (level 3) - Chance increase to 3%``";
	}
	else {
		level8 = "`a(Locked) Flawless: 1% chance to decrease seed grow time when planting``|left|7186|\nadd_label_with_icon|sml|`a(Locked) Earth Mastery (level 3) - Chance increase to 3%``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 9) {
		level9 = "`oUnlocked: 5000 Gems``";
	}
	else {
		level9 = "`a(Locked) 5000 Gems``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 10) {
		level10 = "`oUnlocked: Harvester: 1% chance to obtain extra block drop when harvesting trees``|left|1966|\nadd_label_with_icon|sml|`oUnlocked: Unique Prize``";
	}
	else {
		level10 = "`a(Locked) Harvester: 1% chance to obtain extra block drop when harvesting trees``|left|1966|\nadd_label_with_icon|sml|`a(Locked) Unique Prize``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 11) {
		level11 = "`oUnlocked: Flawless (level 2) - Chance increase to 2%``";
	}
	else {
		level11 = "`a(Locked) Flawless (level 2) - Chance increase to 2%``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 12) {
		level12 = "`oUnlocked: 15000 Gems``";
	}
	else {
		level12 = "`a(Locked) 15000 Gems``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 13) {
		level13 = "`oUnlocked: Harvester (level 2) - Chance increase to 2%``|left|1966|\nadd_label_with_icon|sml|`oUnlocked: Hands of the Void``";
	}
	else {
		level13 = "`a(Locked) Harvester (level 2) - Chance increase to 2%``|left|1966|\nadd_label_with_icon|sml|`a(Locked) Hands of the Void``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 14) {
		level14 = "`oUnlocked: 5 Growtokens``";
	}
	else {
		level14 = "`a(Locked) 5 Growtokens``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 15) {
		level15 = "`oUnlocked: Ultimate Seediary Ability: Randomize all seed recipes into higher tier``";
	}
	else {
		level15 = "`a(Locked) Ultimate Seediary Ability: Randomize all seed recipes into higher tier``";
	}
	Player::OnDialogRequest(peer, "add_label_with_icon|big|`wLevel up Rewards``|left|18|\nadd_spacer|small|\nadd_textbox|`9Here are all the Level up rewards that you have earned so far!``|left|\nadd_spacer|small|\nadd_spacer|small|\nadd_smalltext|Level 1 rewards:|left|\nadd_label_with_icon|sml|" + level1 + "|left|112|\nadd_spacer|small|\nadd_smalltext|Level 2 rewards:|left|\nadd_label_with_icon|sml|" + level2 + "|left|340|\nadd_spacer|small|\nadd_smalltext|Level 3 rewards:|left|\nadd_label_with_icon|sml|" + level3 + "|left|1486|\nadd_spacer|small|\nadd_smalltext|Level 4 rewards:|left|\nadd_label_with_icon|sml|" + level4 + "|left|1938|\nadd_spacer|small|\nadd_smalltext|Level 5 rewards:|left|\nadd_label_with_icon|sml|" + level5 + "|left|1486|\nadd_spacer|small|\nadd_smalltext|Level 6 rewards:|left|\nadd_label_with_icon|sml|" + level6 + "|left|5050|\nadd_spacer|small|\nadd_smalltext|Level 7 rewards:|left|\nadd_label_with_icon|sml|" + level7 + "|left|6918|\nadd_spacer|small|\nadd_smalltext|Level 8 rewards:|left|\nadd_label_with_icon|sml|" + level8 + "|left|5050|\nadd_spacer|small|\nadd_smalltext|Level 9 rewards:|left|\nadd_label_with_icon|sml|" + level9 + "|left|112|\nadd_spacer|small|\nadd_smalltext|Level 10 rewards:|left|\nadd_label_with_icon|sml|" + level10 + "|left|2478|\nadd_spacer|small|\nadd_smalltext|Level 11 rewards:|left|\nadd_label_with_icon|sml|" + level11 + "|left|7186|\nadd_spacer|small|\nadd_smalltext|Level 12 rewards:|left|\nadd_label_with_icon|sml|" + level12 + "|left|112|\nadd_smalltext|Level 13 rewards:|left|\nadd_label_with_icon|sml|" + level13 + "|left|8452|\nadd_spacer|small|\nadd_smalltext|Level 14 rewards:|left|\nadd_label_with_icon|sml|" + level14 + "|left|1486|\nadd_spacer|small|\nadd_smalltext|Level 15 rewards:|left|\nadd_label_with_icon|sml|" + level15 + "|left|6128|\nadd_spacer|small|\nadd_button|back|Close|noflags|0|0||\nadd_quick_exit|");
}

inline bool isWorldOwner(ENetPeer* peer, WorldInfo* world)
{
	return static_cast<PlayerInfo*>(peer->data)->rawName == world->owner;
}

inline bool isWorldAdmin(ENetPeer* peer, WorldInfo* world)
{
	const auto uid = static_cast<PlayerInfo*>(peer->data)->rawName;
	for (const auto i = 0; world->accessed.size();)
	{
		const auto x = world->accessed.at(i);
		if (uid == x.substr(0, x.find("|")))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
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
	delete[] ExtendedData; // fix memleak by playingo
}


inline void SendGScan(ENetPeer* peer, WorldInfo* world, int x, int y) {
	string EditableDialog = "";
	string ButtonDialog = "";
	string allowFloat = "0";
	string allowDrop = "0";
	string endDialog = "";
	if (world->items[x + (y * world->width)].rm) allowFloat = "1";
	if (world->items[x + (y * world->width)].opened) allowDrop = "1";
	if (((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel == 1337) {
		endDialog = "\nend_dialog|statsblock|Cancel|Apply|";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|\nadd_button|floatingItems|Floating Items|noflags|0|0|";
		EditableDialog = "\nadd_textbox|`wYou can set the stats to be usable by the public.|left\nadd_checkbox|isStatsWorldBlockUsableByPublic|World blocks is usable by public|" + allowDrop + "\nadd_checkbox|isStatsFloatingItemsUsableByPublic|Floating items is usable by public|" + allowFloat + "\nadd_spacer|small|";
	}
	else if (world->items[x + (y * world->width)].rm && world->items[x + (y * world->width)].opened) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|\nadd_button|floatingItems|Floating Items|noflags|0|0|";
	}
	else if (world->items[x + (y * world->width)].rm) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|floatingItems|Floating Items|noflags|0|0|";
	}
	else if (world->items[x + (y * world->width)].opened) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|";
	}
	else {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wThis growscan options are set to private!|left";
	}
	Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wWorld Stats``|left|6016|\nadd_spacer|small|\nadd_textbox|`wThis amazing block can show the stats for the whole world!|left\nadd_spacer|small|" + ButtonDialog + "\nadd_spacer|small|" + EditableDialog + "" + endDialog + "");
}

inline void LogAccountActivity(ENetPeer* peer, string log) {
	string qss = "SELECT * FROM PlayerDatabase WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
	string account_history; {
	}
	time_t currentTime;
	time(&currentTime);
	const auto localTime = localtime(&currentTime);
	const auto Hour = localTime->tm_hour;
	const auto Min = localTime->tm_min;
	const auto Sec = localTime->tm_sec;
	const auto Year = localTime->tm_year + 1900;
	const auto Day = localTime->tm_mday;
	const auto Month = localTime->tm_mon + 1;
	account_history += "" + to_string(Month) + "/" + to_string(Day) + "/" + to_string(Year) + " " + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + ": " + static_cast<PlayerInfo*>(peer->data)->rawName + " - >> " + log + "|";
	string stringsa = "UPDATE GTAS player database made by HyperCold = '" + account_history + "' GTAS username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT-1";
}

//playtime
void ThreadPlaytime(ENetPeer* peer) {
	while (1) {
		Sleep(1000);
		if (peer->state != ENET_PEER_STATE_CONNECTED) return;
		if (!((PlayerInfo*)(peer->data))->isIn) return;
		int hours = 0;
		ifstream fd("playtime/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		if (fd.is_open()) {
			fd >> hours;
			fd.close();
		}
		ofstream savebantime2("playtime/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		savebantime2 << hours + 1 << endl;
		savebantime2.close();
	}
}

//counter
int rdn(int y, int m, int d) {
	if (m < 3) y--, m += 12;
	return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

void SendRainbowShitData(ENetPeer* peer, short fg, short bg, int x, int y, bool rainbow, int netid) {
	byte* ExtendedData = new byte[26];
	int state = 0x0010000;
	int extendedLen = 26;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	int NetID = netid;
	byte* raw = new byte[56 + 26];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	memcpy(ExtendedData + 4, &state, 4);
	ExtendedData[8] = 0x3;
	int flags = 0;
	if (rainbow) {
		flags = 128;
	}
	else {
		flags = 0;
	}
	ExtendedData[9] = flags;
	memcpy(ExtendedData + 10, &NetID, 4);
	ExtendedData[15] = 0;
	ExtendedData[16] = 0;
	ExtendedData[17] = 0;
	ExtendedData[18] = 0;
	ExtendedData[19] = 1;
	ExtendedData[20] = 0;
	ExtendedData[21] = 0;
	ExtendedData[22] = 0;
	ExtendedData[23] = 0;
	ExtendedData[24] = 0;
	ExtendedData[25] = 0;
	ExtendedData[26] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 26, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	delete[] ExtendedData;

}

void updateSign(ENetPeer* peer, int foreground, int x, int y, string text, int background) // kazkas su mailbox
{
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
	int hmm = 8, wot = text.length(), lol = 0, wut = 5;
	int yeh = hmm + 3 + 1, idk = 15 + wot, lmao = -1, yey = 2; //idk = text_len + 15, wut = type(?), wot = text_len, yey = len of text_len
	int ok = 52 + idk;
	int kek = ok + 4, yup = ok - 8 - idk;
	int thonk = 4, magic = 56, wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, thonk);
	memcpy(data + yeh, &hmm, thonk); //read discord
	memcpy(data + yup, &x, 4);
	memcpy(data + yup + 4, &y, 4);
	memcpy(data + 4 + yup + 4, &idk, thonk);
	memcpy(data + magic, &foreground, yey);
	memcpy(data + magic + 2, &background, yey); //p100 fix by the one and only lapada
	memcpy(data + thonk + magic, &lol, thonk);
	memcpy(data + magic + 4 + thonk, &yey, 1);
	memcpy(data + wow, &wot, yey); //data + wow = text_len
	memcpy(data + yey + wow, text.c_str(), wot); //data + text_len_len + text_len_offs = text
	memcpy(data + ok, &lmao, thonk); //end ?
	memcpy(p->data, &thonk, thonk);
	memcpy((char*)p->data + thonk, data, kek); //kek = data_len
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
void playerconfig(ENetPeer* peer, int yspeed, int xspeed, int packettype)
{
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
			float water = 125.0f;
			data.packetType = packettype;
			data.characterState = ((PlayerInfo*)(peer->data))->characterState; // animation
			data.x = 1000;
			if (((PlayerInfo*)(peer->data))->cloth_hand == 366) {
				data.y = -400; // - is hbow
			}
			else {
				data.y = 400;
			}
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = xspeed;
			data.YSpeed = yspeed;
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
void updateGuild(ENetPeer* peer) {
	string guildname = PlayerDB::getProperName(((PlayerInfo*)(peer->data))->guild);
	if (guildname != "") {
		try {
			std::ifstream ifff("guilds/" + guildname + ".json");
			if (ifff.fail()) {
				ifff.close();
				cout << "Failed loading guilds/" + guildname + ".json! From " + ((PlayerInfo*)(peer->data))->displayName + "." << endl;
				((PlayerInfo*)(peer->data))->guild = "";
				updateGuild;
			}
			json j;
			ifff >> j;

			int gfbg, gffg;

			string gstatement, gleader;

			vector<string> gmembers;

			gfbg = j["backgroundflag"];
			gffg = j["foregroundflag"];
			gstatement = j["GuildStatement"].get<string>();
			gleader = j["Leader"].get<string>();
			for (int i = 0; i < j["Member"].size(); i++) {
				gmembers.push_back(j["Member"][i]);
			}

			if (find(gmembers.begin(), gmembers.end(), ((PlayerInfo*)(peer->data))->rawName) == gmembers.end()) {
				((PlayerInfo*)(peer->data))->guild = "";
			}
			else {
				((PlayerInfo*)(peer->data))->guildBg = gfbg;
				((PlayerInfo*)(peer->data))->guildFg = gffg;
				((PlayerInfo*)(peer->data))->guildStatement = gstatement;
				((PlayerInfo*)(peer->data))->guildLeader = gleader;
				((PlayerInfo*)(peer->data))->guildMembers = gmembers;
			}

			ifff.close();
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
void RestartForUpdate()
{
	if (restartForUpdate)
	{
		ofstream ofrest("restartedmaintenance.txt");
		ofrest << 1;
		ofrest.close();
		GamePacket p;
		ENetPacket* packet;
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Global System Message : `6 Restarting server for update in `415 `6seconds"));
		packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete p.data;
		Sleep(10000);
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Global System Message : `6 Restarting server for update in `410 `6seconds"));
		packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete p.data;
		Sleep(10000);
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Global System Message : `6 Restarting server for update in `44 `6seconds"));
		packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete p.data;
		Sleep(1000);
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Global System Message : `6 Restarting server for update in `43 `6seconds"));
		packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete p.data;
		Sleep(1000);
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Global System Message : `6 Restarting server for update in `42 `6seconds"));
		packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete p.data;
		Sleep(1000);
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Global System Message : `6 Restarting server for update in `41 `6seconds"));
		packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete p.data;
		Sleep(1000);
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Global System Message : `6 Restarting server for update! See you later!"));
		packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete p.data;
		Sleep(2000);
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			enet_peer_disconnect_now(currentPeer, 0);
		}
		saveAllWorlds();
		restartForUpdate = false;
	}
}
void sendPuncheffectpeer(ENetPeer* peer, int punch) {
	PlayerInfo* info = ((PlayerInfo*)(peer->data));
	int netID = info->netID;
	int state = getState(info);
	PlayerMoving data;
	float water = 125.0f;
	data.packetType = 0x14;
	data.characterState = ((PlayerInfo*)(peer->data))->characterState; // animation
	data.x = 1000;
	//data.y = 100;
	if (((PlayerInfo*)(peer->data))->cloth_hand == 366) {
		data.y = -400; // - is hbow
	}
	else {
		data.y = 400;
	}
	data.punchX = -1;
	data.punchY = -1;
	data.XSpeed = 300;
	if (((PlayerInfo*)(peer->data))->cloth_back == 1738) {
		data.YSpeed = 600;
	}
	else {
		data.YSpeed = 1150;
	}
	data.netID = netID;
	data.plantingTree = state;
	BYTE* raw = packPlayerMoving(&data);
	int var = punch;
	memcpy(raw + 1, &var, 3);
	memcpy(raw + 16, &water, 4);
	SendPacketRaw(4, raw, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	if (((PlayerInfo*)(peer->data))->isZombie == true)
	{
		playerconfig(peer, 1150, 130, 0x14);
	}
}
void sendPuncheffect(ENetPeer* peer, int punch) {
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
			if (peer != currentPeer) {
				PlayerMoving data;
				data.packetType = 0x14;
				data.characterState = ((PlayerInfo*)(peer->data))->characterState; // animation
				data.x = 1000;
				data.y = 100;
				data.x = 1000;
				data.y = 1000;
				data.punchX = 0;
				data.punchY = 0;
				data.XSpeed = 300;
				data.YSpeed = 600;
				data.netID = netID;
				data.plantingTree = state;
				BYTE* raw = packPlayerMoving(&data);
				int var = punch;
				memcpy(raw + 1, &var, 3);
				SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			if (((PlayerInfo*)(peer->data))->haveGrowId && ((PlayerInfo*)(peer->data))->isIn == true && ((PlayerInfo*)(peer->data))->currentWorld != "EXIT") {
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
					ifff >> j;
					int effect = p->effect;
					j["effect"] = p->effect;
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
		}
	}
	if (((PlayerInfo*)(peer->data))->isZombie == true)
	{
		playerconfig(peer, 1150, 130, 0x14);
	}
}
void updatepeffect(ENetPeer* peer)
{
	if (((PlayerInfo*)(peer->data))->haveGrowId) {
		PlayerInfo* p = ((PlayerInfo*)(peer->data));
		std::ifstream ifff("players/" + PlayerDB::getProperName(p->rawName) + ".json");
		json j;
		ifff >> j;
		((PlayerInfo*)(peer->data))->effect = j["effect"];
		ifff.close();
		sendPuncheffectpeer(peer, ((PlayerInfo*)(peer->data))->effect);
	}
}
void changetile(ENetPeer* peer, int x, int y)
{
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			BlockVisual data3;
			data3.packetType = 0x5;
			data3.characterState = 8;
			data3.charStat = 8;
			data3.blockid = 260;
			data3.backgroundid = 260;
			data3.visual = 0x00400000;
			data3.punchX = x;
			data3.punchY = y;
			data3.netID = ((PlayerInfo*)(peer->data))->netID;
			SendPacketRaw2(192, packBlockVisual(&data3), 100, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
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
		if (((PlayerInfo*)(currentPeer->data))->isinv == false)
		{
			if (((PlayerInfo*)(currentPeer->data))->currentWorld == name)
				count++;
		}
	}
	return count;
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

inline void sendArrow(ENetPeer* peer, const uint16_t itemid, const bool droppeditem)
{
	PlayerMoving pmov;
	memset(&pmov, 0, sizeof(PlayerMoving));
	*reinterpret_cast<uint32_t*>(&pmov) = 37 | (droppeditem << 8);
	pmov.netID = itemid;
	const auto pmovpacked = packPlayerMoving(&pmov);
	const auto packet = new uint8_t[4 + 56];
	memset(packet, 0, 4 + 56);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, sizeof(PlayerMoving));
	const auto epacket = enet_packet_create(packet, 4 + 56, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, epacket);
	delete pmovpacked;
	delete packet;
}

void tradestatus(ENetPeer* peer, int netid, string s2, string offername, string box)
{
	try
	{
		GamePacket p2t = packetEnd(appendString(appendString(appendString(appendInt(appendString(createPacket(), "OnTradeStatus"), netid), s2), offername + "`o's offer."), box));
		ENetPacket* packet4 = enet_packet_create(p2t.data,
			p2t.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet4);
		delete p2t.data;
	}
	catch (const std::runtime_error &ex)
	{
		std::wcout << L"[ERROR]: Failure at tradestatus " << ex.what() << std::endl;
	}
}
void updateStuffWeather(ENetPeer* peer, int x, int y, int tile, int bg, int gravity, bool isInverted, bool isSpinning) {
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			//cout << "bruh" << endl;
			TileExtra data;
			data.packetType = 0x5;
			data.characterState = 8;
			data.punchX = x;
			data.punchY = y;
			data.charStat = 18; // 13
			data.blockid = 3832;
			data.backgroundid = bg; // 2946
								   //data.netID = ((PlayerInfo)(peer->data))->netID;
								   //dataxx.backgroundid = 65536;
			data.visual = 0; //0x00210000
										//world->items[x + (yworld->width)].displayblock = tile;
			int n = tile;
			string hex = "";
			{
				std::stringstream ss;
				ss << std::hex << n; // int decimal_value
				std::string res(ss.str());
				hex = res + "31";
			}
			int gravi = gravity;
			string hexg = "";
			{
				int temp = gravi;
				if (gravi < 0) temp = -gravi;
				std::stringstream ss;
				ss << std::hex << temp; // int decimal_value
				std::string res(ss.str());
				hexg = res + "00";
			}
			int xx = 0;
			std::stringstream ss;
			ss << std::hex << hex;
			if (!ss.fail()) {
				ss >> xx;
			}
			//cout << xx << endl;
			data.displayblock = xx;
			int xxs = 0;
			std::stringstream sss;
			sss << std::hex << hexg;
			if (!sss.fail()) {
				sss >> xxs;
			}
			if (gravi < 0) xxs = -xxs;
			//cout << to_string(xxs) << endl;
			if (gravi < 0) {
				SendPacketRaw2(192, packStuffVisual(&data, 0x03FFFFFF, xxs), 102, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			else
			{
				SendPacketRaw2(192, packStuffVisual(&data, 0x02000000, xxs), 102, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), 29));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
			delete p2.data;
		}
	}
}

inline void send_state(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT")
	{
		return;
	}
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	const auto state = getState(info);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			auto water = 125.0f;
			data.packetType = 0x14;
			data.characterState = static_cast<PlayerInfo*>(peer->data)->characterState;
			data.x = 1000;
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 366)
			{
				data.y = -400;
			}
			else
			{
				data.y = 400;
			}
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9472)
			{
				data.YSpeed = 600;
			}
			else
			{
				data.YSpeed = 1000;
			}
			data.netID = netID;
			data.plantingTree = state;
			const auto raw = packPlayerMoving(&data);
			auto var = 0x818100;
			memcpy(raw + 1, &var, 3);
			memcpy(raw + 16, &water, 4);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->skill == "Farmer")
	{
		auto p2 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 1), 2), 7064), 0));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		const auto packet3 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, packet3);
			}
		}
		delete p2.data;
	}
	if (static_cast<PlayerInfo*>(peer->data)->skill == "Miner")
	{
		auto p2 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 1), 2), 98), 0));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		const auto packet3 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, packet3);
			}
		}
		delete p2.data;
	}
	if (static_cast<PlayerInfo*>(peer->data)->isZombie == true || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 898 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1830 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1966)
	{
		playerconfig(peer, 1150, 130, 0x14);
	}
}

void sendPlayerLeave(ENetPeer* peer, PlayerInfo* player)
{
	//((PlayerInfo*)(peer->data))->cpX = 3040;
	//((PlayerInfo*)(peer->data))->cpY = 736;
	((PlayerInfo*)(peer->data))->cpY = 0;
	((PlayerInfo*)(peer->data))->cpY = 0;
	((PlayerInfo*)(peer->data))->usedCP = false;
	ENetPeer* currentPeer;
	if (find(((PlayerInfo*)(peer->data))->lastworlds.begin(), ((PlayerInfo*)(peer->data))->lastworlds.end(), player->currentWorld) != ((PlayerInfo*)(peer->data))->lastworlds.end()) {
	}
	else {
		((PlayerInfo*)(peer->data))->lastworlds.push_back(player->currentWorld);
	}
	((PlayerInfo*)(peer->data))->ischeck = false;
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(player->netID) + "\n")); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
	GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(player->currentWorld) - 1) + "`` `5others here>```w"));
	string name = ((PlayerInfo*)(peer->data))->displayName;
	string text = "action|play_sfx\nfile|audio/door_shut.wav\ndelayMS|0\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (((PlayerInfo*)(currentPeer->data))->currentWorld == "EXIT")
			continue;
		if (((PlayerInfo*)(currentPeer->data))->isIn == false)
			continue;
		if (isHere(peer, currentPeer)) {
			{
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				{
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet);
					ENetPacket* packet3 = enet_packet_create(data,
						5 + text.length(),
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet3);
				}
				if (((PlayerInfo*)(peer->data))->isinv == false)
				{
					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet2);
					GamePacket p4 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(player->currentWorld) - 1) + "`` `5others here>```w"));
					ENetPacket* packet4 = enet_packet_create(p4.data,
						p4.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet4);
					delete p4.data;
				}
			}
			{
			}
		}
	}
	delete p.data;
	delete p2.data;
	delete[] data;
}
void sendRoulete(ENetPeer* peer)
{
	using namespace std::chrono;
	if (((PlayerInfo*)(peer->data))->lastSPIN + 1500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
	{
		((PlayerInfo*)(peer->data))->lastSPIN = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
	}
	else {
		return;
	}
	ENetPeer* currentPeer;
	int val = rand() % 36;

	if (((PlayerInfo*)(peer->data))->isSpinSetByCreator == true)
	{
		val = ((PlayerInfo*)(peer->data))->spinSetByCreatorValue;
		((PlayerInfo*)(peer->data))->isSpinSetByCreator = false;
	}

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			string name = ((PlayerInfo*)(peer->data))->displayName;

			if (val == 1 || val == 3 || val == 5 || val == 7 || val == 9 || val == 12 || val == 14 || val == 16 || val == 18 || val == 19 || val == 21 || val == 23 || val == 25 || val == 27 || val == 30 || val == 32 || val == 34 || val == 36) {
				GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`w[" + name + " `wspun the wheel and got `4" + std::to_string(val) + "`w!]"), 0));
				int respawnTimeout = 2000;
				int deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				GamePacket p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `4" + std::to_string(val) + "`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				ENetPacket* packet2s = enet_packet_create(p2s.data,
					p2s.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;

			}
			else if (val == 2 || val == 4 || val == 6 || val == 8 || val == 10 || val == 11 || val == 13 || val == 15 || val == 17 || val == 20 || val == 22 || val == 24 || val == 26 || val == 28 || val == 29 || val == 31 || val == 33 || val == 35) {

				GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`w[" + name + " `wspun the wheel and got `b" + std::to_string(val) + "`w!]"), 0));
				int respawnTimeout = 2000;
				int deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				GamePacket p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `b" + std::to_string(val) + "`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				ENetPacket* packet2s = enet_packet_create(p2s.data,
					p2s.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;

			}
			else if (val == 0 || val == 37) {
				GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`w[" + name + " `wspun the wheel and got `20`w!]"), 0));
				int respawnTimeout = 2000;
				int deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				GamePacket p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `20`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				ENetPacket* packet2s = enet_packet_create(p2s.data,
					p2s.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;
			}
		}
	}
}
void onSignBubble(ENetPeer* peer, int foreground, int x, int y, string text, int background)
{
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
	int hmm = 8, wot = text.length(), lol = 0, wut = 5;
	int yeh = hmm + 3 + 1, idk = 15 + wot, lmao = -1, yey = 2; //idk = text_len + 15, wut = type(?), wot = text_len, yey = len of text_len
	int ok = 52 + idk;
	int kek = ok + 4, yup = ok - 8 - idk;
	int thonk = 4, magic = 56, wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, thonk);
	memcpy(data + yeh, &hmm, thonk); //read discord
	memcpy(data + yup, &x, 4);
	memcpy(data + yup + 4, &y, 4);
	memcpy(data + 4 + yup + 4, &idk, thonk);
	memcpy(data + magic, &foreground, yey);
	memcpy(data + magic + 2, &background, yey); //p100 fix by the one and only Secret3
	memcpy(data + thonk + magic, &lol, thonk);
	memcpy(data + magic + 4 + thonk, &yey, 1);
	memcpy(data + wow, &wot, yey); //data + wow = text_len
	memcpy(data + yey + wow, text.c_str(), wot); //data + text_len_len + text_len_offs = text
	memcpy(data + ok, &lmao, thonk); //end ?
	memcpy(p->data, &thonk, thonk);
	memcpy((char*)p->data + thonk, data, kek); //kek = data_len
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
void updateSeedText(ENetPeer* peer, int foreground, int x, int y, string text)
{
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
	int hmm = 8;
	int text_len = text.length();
	int lol = 0;
	int wut = 5;
	int yeh = hmm + 3 + 1;
	int idk = 15 + text_len;
	int is_locked = 0;
	int bubble_type = 1;
	int ok = 52 + idk;
	int kek = ok + 4;
	int yup = ok - 8 - idk;
	int four = 4;
	int magic = 56;
	int wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, four); //4
	memcpy(data + yeh, &hmm, four); //8
	memcpy(data + yup, &x, 4); //12
	memcpy(data + yup + 4, &y, 4); //16
	memcpy(data + 4 + yup + 4, &idk, four); //20
	memcpy(data + magic, &foreground, 2); //22
	memcpy(data + four + magic, &lol, four); //26
	memcpy(data + magic + 4 + four, &bubble_type, 1); //27
	memcpy(data + wow, &text_len, 2); //data + wow = text_len, pos 29
	memcpy(data + 2 + wow, text.c_str(), text_len); //data + text_len_len + text_len_offs = text, pos 94
	memcpy(data + ok, &is_locked, four); //98
	memcpy(p->data, &four, four); //4
	memcpy((char*)p->data + four, data, kek); //kek = data_len
	ENetPeer* currentPeer;
	enet_peer_send(peer, 0, p);
	delete data;
}
void updateDoor(ENetPeer* peer, int foreground, int x, int y, string text)
{
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
	int hmm = 8;
	int text_len = text.length();
	int lol = 0;
	int wut = 5;
	int yeh = hmm + 3 + 1;
	int idk = 15 + text_len;
	int is_locked = 0;
	int bubble_type = 1;
	int ok = 52 + idk;
	int kek = ok + 4;
	int yup = ok - 8 - idk;
	int four = 4;
	int magic = 56;
	int wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, four); //4
	memcpy(data + yeh, &hmm, four); //8
	memcpy(data + yup, &x, 4); //12
	memcpy(data + yup + 4, &y, 4); //16
	memcpy(data + 4 + yup + 4, &idk, four); //20
	memcpy(data + magic, &foreground, 2); //22
	memcpy(data + four + magic, &lol, four); //26
	memcpy(data + magic + 4 + four, &bubble_type, 1); //27
	memcpy(data + wow, &text_len, 2); //data + wow = text_len, pos 29
	memcpy(data + 2 + wow, text.c_str(), text_len); //data + text_len_len + text_len_offs = text, pos 94
	memcpy(data + ok, &is_locked, four); //98
	memcpy(p->data, &four, four); //4
	memcpy((char*)p->data + four, data, kek); //kek = data_len
	ENetPeer* currentPeer;
	enet_peer_send(peer, 0, p);
	delete data;
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
void UpdateTreeVisuals(ENetPeer* peer, int foreground, int x, int y, int background, int fruitCount) {
	//int val = 1 + rand() % 4;
	string text = "tree";
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
	int hmm = 8;
	int text_len = 4;
	int zero = 0;
	int packetType = 5;
	int yeh = hmm + 3 + 1;
	int idk = 15 + text_len;
	int blockState = 0;
	int bubble_type = 4;
	int ok = 52 + idk;
	int packetSize = ok + 4;
	int yup = ok - 8 - idk;
	int four = 4;
	int magic = 56;
	int wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	short a = (short)fruitCount;
	int treedata = 0x0002000a;
	BYTE* data = new BYTE[packetSize];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	memset(data, 0, packetSize);
	memcpy(data, &packetType, sizeof(int));
	memcpy(data + yeh, &hmm, sizeof(int));
	memcpy(data + yup, &x, sizeof(int));
	memcpy(data + yup + 4, &y, sizeof(int));
	memcpy(data + 4 + yup + 4, &idk, sizeof(int));
	memcpy(data + magic, &foreground, sizeof(short));
	memcpy(data + four + magic, &background, sizeof(int));
	memcpy(data + magic + 4 + four, &bubble_type, sizeof(byte));
	memcpy(data + wow, &text_len, sizeof(short));
	memcpy(data + 2 + wow, &treedata, text_len);
	memcpy(data + ok, &blockState, sizeof(int));
	memcpy(p->data, &four, four);
	memcpy((char*)p->data + four, data, packetSize);
	enet_peer_send(peer, 0, p);
	delete data;
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
void sendblockstate(ENetPeer* peer, int x, int y, int state)
{
	BlockVisual data;
	data.packetType = 0x5;
	data.characterState = 8;
	data.charStat = 8;
	data.blockid = 0;
	data.backgroundid = 0;
	data.visual = state;
	data.punchX = x;
	data.punchY = y;
	data.netID = ((PlayerInfo*)(peer->data))->netID;
	SendPacketRaw2(192, packBlockVisual(&data), 100, 0, peer, ENET_PACKET_FLAG_RELIABLE);
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
	else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::MAIN_DOOR)
	{
		UpdateUnlockedDoorVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, "EXIT", forEveryone, blockStateFlags);
	}
	else if (worldInfo->items[i].foreground == 2946) // display block
	{
		UpdateDisplayVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, worldInfo->items[i].intdata);
	}
	else if (worldInfo->items[i].foreground % 2 == 1)
	{
		UpdateTreeVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, 3);
	}
	else if (blockStateFlags != 0)
	{
		UpdateMessageVisuals(peer, worldInfo->items[i].foreground, x, y, "", worldInfo->items[i].background, 0, forEveryone, blockStateFlags);
	}
}
void doorlocked(ENetPeer* peer, int foreground, int x, int y, string text)
{
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
	int hmm = 8;
	int text_len = text.length();
	int lol = 0;
	int wut = 5;
	int yeh = hmm + 3 + 1;
	int idk = 15 + text_len;
	int is_locked = -1;
	int bubble_type = 1;
	int ok = 52 + idk;
	int kek = ok + 4;
	int yup = ok - 8 - idk;
	int four = 4;
	int magic = 56;
	int wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, four); //4
	memcpy(data + yeh, &hmm, four); //8
	memcpy(data + yup, &x, 4); //12
	memcpy(data + yup + 4, &y, 4); //16
	memcpy(data + 4 + yup + 4, &idk, four); //20
	memcpy(data + magic, &foreground, 2); //22
	memcpy(data + four + magic, &lol, four); //26
	memcpy(data + magic + 4 + four, &bubble_type, 1); //27
	memcpy(data + wow, &text_len, 2); //data + wow = text_len, pos 29
	memcpy(data + 2 + wow, text.c_str(), text_len); //data + text_len_len + text_len_offs = text, pos 94
	memcpy(data + ok, &is_locked, four); //98
	memcpy(p->data, &four, four); //4
	memcpy((char*)p->data + four, data, kek); //kek = data_len
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
void SendDropSingle(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect)
{
	if (item >= maxItems) return;
	if (item < 0) return;
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
	SendPacketRaw(4, raw, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void sendDShelf(ENetPeer* peer, int x, int y, int item1, int item2, int item3, int item4)
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
	*(int*)(packet + 4 + 56 + 9 + 3 * 4) = item4;
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 16, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}

void UpdateVend(ENetPeer* peer, int x, int y, int id, bool locks, int price)
{
	bool isPer = false;
	WorldInfo* world = getPlyersWorld(peer);
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			TileExtra data;
			data.packetType = 0x5;
			data.characterState = 8;
			data.punchX = x;
			data.punchY = y;
			data.charStat = 13; // 13
			data.blockid = 2978; // 2946 3794 = display shelf
								 //data.netID = ((PlayerInfo*)(peer->data))->netID;
			data.backgroundid = 6864;
			data.visual = 0x00410000; //0x00210000
			if (locks == true) data.visual = 0x02410000;



			int n = id;
			string hex = "";
			{
				std::stringstream ss;
				ss << std::hex << n; // int decimal_value
				std::string res(ss.str());
				hex = res + "18";
			}

			int xx;
			std::stringstream ss;
			ss << std::hex << hex;
			ss >> xx;
			data.displayblock = xx;
			int xes;
			{
				int wl = price;
				string hex = "";
				{
					std::stringstream ss;
					ss << std::hex << wl; // int decimal_value
					std::string res(ss.str());
					hex = res + "00";
				}
				int x;
				std::stringstream ss;
				ss << std::hex << hex;
				ss >> x;

				xes = x;
			}
			BYTE* raw = NULL;
			if (isPer) {
				raw = packStuffVisual(&data, 16777215, -xes);
			}
			else
			{
				raw = packStuffVisual(&data, 0, xes);
			}
			SendPacketRaw2(192, raw, 102, 0, peer, ENET_PACKET_FLAG_RELIABLE);
			raw = NULL; // prevent memory leak*/
		}
	}
}
void UpdateBlockState(ENetPeer* peer, int x, int y, bool forEveryone, WorldInfo* worldInfo) {
	if (!worldInfo) return;
	int i = y * worldInfo->width + x;
	int blockStateFlags = 0;
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
}

inline void updateVendMsg(ENetPeer* peer, int foreground, int x, int y, string text)
{



	int hmm = 8;
	int text_len = text.length();
	int lol = 0;
	int wut = 5;
	int yeh = hmm + 3 + 1;
	int idk = 15 + text_len;
	int is_locked = 0;
	int bubble_type = 21;
	int ok = 52 + idk;
	int kek = ok + 4;
	int yup = ok - 8 - idk;
	int four = 4;
	int magic = 56;
	int wew = ok + 5 + 4;
	int wow = magic + 4 + 5;

	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (auto i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, four);
	memcpy(data + yeh, &hmm, four);
	memcpy(data + yup, &x, 4);
	memcpy(data + yup + 4, &y, 4);
	memcpy(data + 4 + yup + 4, &idk, four);
	memcpy(data + magic, &foreground, 2);
	memcpy(data + four + magic, &lol, four);
	memcpy(data + magic + 4 + four, &bubble_type, 1);
	memcpy(data + wow, &text_len, 2);
	memcpy(data + 2 + wow, text.c_str(), text_len);
	memcpy(data + ok, &is_locked, four);
	memcpy(p->data, &four, four);
	memcpy(reinterpret_cast<char*>(p->data) + four, data, kek);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			enet_peer_send(currentPeer, 0, p);
		}
	}
	delete data;
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
inline void UpdateVend(ENetPeer* peer, int x, int y, int id, bool locks, int price, int background)
{
	auto options321 = 0;
	if (price >= 256 && price < 512) options321 = 1;
	else if (price >= 512 && price < 768) options321 = 2;
	else if (price >= 768 && price < 1024) options321 = 3;
	else if (price >= 1024 && price < 1280) options321 = 4;
	else if (price >= 1280 && price < 1536) options321 = 5;
	else if (price >= 1536 && price < 1792) options321 = 6;
	else if (price >= 1792 && price < 2048) options321 = 7;
	else if (price >= 2048 && price < 2304) options321 = 8;
	else if (price >= 2304 && price < 2560) options321 = 9;
	else if (price >= 2560 && price < 2816) options321 = 10;
	else if (price >= 2816 && price < 3072) options321 = 11;
	else if (price >= 3072 && price < 3328) options321 = 12;
	else if (price >= 3328 && price < 3584) options321 = 13;
	else if (price >= 3584 && price < 3840) options321 = 14;
	else if (price >= 3840 && price < 4096) options321 = 15;
	else if (price >= 4096 && price < 4352) options321 = 16;
	else if (price >= 4352 && price < 4608) options321 = 17;
	else if (price >= 4608 && price < 4864) options321 = 18;
	else if (price >= 4864 && price < 5120) options321 = 19;
	else if (price >= 5120 && price < 5376) options321 = 20;
	else if (price >= 5376 && price < 5632) options321 = 21;
	else if (price >= 5632 && price < 5888) options321 = 22;
	else if (price >= 5888 && price < 6144) options321 = 23;
	else if (price >= 6144 && price < 6400) options321 = 24;
	else if (price >= 6400 && price < 6656) options321 = 25;
	else if (price >= 6656 && price < 6912) options321 = 26;
	else if (price >= 6912 && price < 7168) options321 = 27;
	else if (price >= 7168 && price < 7424) options321 = 28;
	else if (price >= 7424 && price < 7680) options321 = 29;
	else if (price >= 7680 && price < 7936) options321 = 30;
	else if (price >= 7936 && price < 8192) options321 = 31;
	else if (price >= 8192 && price < 8448) options321 = 32;
	else if (price >= 8448 && price < 8704) options321 = 33;
	else if (price >= 8704 && price < 8960) options321 = 34;
	else if (price >= 8960 && price < 9216) options321 = 35;
	else if (price >= 9216 && price < 9472) options321 = 36;
	else if (price >= 9472 && price < 9728) options321 = 37;
	else if (price >= 9728 && price < 9984) options321 = 38;
	else if (price >= 9984 && price < 10240) options321 = 39;
	else if (price >= 10240 && price < 10496) options321 = 40;
	else if (price >= 10496 && price < 10752) options321 = 41;
	else if (price >= 10752 && price < 11008) options321 = 42;
	else if (price >= 11008 && price < 11264) options321 = 43;
	else if (price >= 11264 && price < 11520) options321 = 44;
	else if (price >= 11520 && price < 11776) options321 = 45;
	else if (price >= 11776 && price < 12032) options321 = 46;
	else if (price >= 12032 && price < 12288) options321 = 47;
	else if (price >= 12288 && price < 12544) options321 = 48;
	else if (price >= 12544 && price < 12800) options321 = 49;
	else if (price >= 12800 && price < 13056) options321 = 50;
	else if (price >= 13056 && price < 13312) options321 = 51;
	else if (price >= 13312 && price < 13568) options321 = 52;
	else if (price >= 13568 && price < 13824) options321 = 53;
	else if (price >= 13824 && price < 14080) options321 = 54;
	else if (price >= 14080 && price < 14336) options321 = 55;
	else if (price >= 14336 && price < 14592) options321 = 56;
	else if (price >= 14592 && price < 14848) options321 = 57;
	else if (price >= 14848 && price < 15104) options321 = 58;
	else if (price >= 15104 && price < 15360) options321 = 59;
	else if (price >= 15360 && price < 15616) options321 = 60;
	else if (price >= 15616 && price < 15872) options321 = 61;
	else if (price >= 15872 && price < 16128) options321 = 62;
	else if (price >= 16128 && price < 16384) options321 = 63;
	else if (price >= 16384 && price < 16640) options321 = 64;
	else if (price >= 16640 && price < 16896) options321 = 65;
	else if (price >= 16896 && price < 17152) options321 = 66;
	else if (price >= 17152 && price < 17408) options321 = 67;
	else if (price >= 17408 && price < 17664) options321 = 68;
	else if (price >= 17664 && price < 17920) options321 = 69;
	else if (price >= 17920 && price < 18176) options321 = 70;
	else if (price >= 18176 && price < 18432) options321 = 71;
	else if (price >= 18432 && price < 18688) options321 = 72;
	else if (price >= 18688 && price < 18944) options321 = 73;
	else if (price >= 18944 && price < 19200) options321 = 74;
	else if (price >= 19200 && price < 19456) options321 = 75;
	else if (price >= 19456 && price < 19712) options321 = 76;
	else if (price >= 19712 && price < 19968) options321 = 77;
	else if (price >= 19968 && price <= 20000) options321 = 78;
	//else return;
	price -= 256 * options321;
	auto isPer = false;
	TileExtra data;
	data.packetType = 0x5;
	data.characterState = 8;
	data.punchX = x;
	data.punchY = y;
	data.charStat = 13;
	data.blockid = 2978;
	data.backgroundid = background;
	data.visual = 0x00410000;
	if (locks == true) data.visual = 0x02410000;
	auto n = id;

	string hex = "";
	{
		std::stringstream ss;
		ss << std::hex << n;
		string res(ss.str());
		hex = res + "18";
	}
	int xx;
	std::stringstream ss;
	ss << std::hex << hex;
	ss >> xx;
	data.displayblock = xx;
	int xes;
	{
		//int wl = price;
		//string wl = to_string(price);
		int wl = price;
		string basic_string = "";
		{
			std::stringstream stringstream;
			stringstream << std::hex << wl;
			string res(stringstream.str());
			basic_string = res + "00";
		}
		int i;
		std::stringstream basic_stringstream;
		basic_stringstream << std::hex << basic_string;
		basic_stringstream >> i;
		xes = i;
	}
	BYTE* raw = nullptr;
	if (isPer)
	{
		raw = packStuffVisual(&data, 16777215, -xes);
	}
	else
	{
		raw = packStuffVisual(&data, options321, xes);
	}
	SendPacketRaw2(192, raw, 102, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	raw = nullptr;
}

void restoreplayernick(ENetPeer* peer)
{
	if (((PlayerInfo*)(peer->data))->isNicked == false)
	{
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 0) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 0) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 0) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 0) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 111) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 111) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 111) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 111) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 222) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 222) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 222) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 222) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 333) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 333) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 333) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 333) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr." + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 555) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 555) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 555) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 555) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 666) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 666) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 666) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`2" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 666) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`#@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`#@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`#@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`#@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 888) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`q@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 888) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`q@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 888) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`q@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 888) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`q@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 998) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`@@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 998) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`@@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 998) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`@@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 998) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`@@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 999) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`4@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 999) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`4@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 999) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`4@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 999) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`4@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 1000 || ((PlayerInfo*)(peer->data))->adminLevel == 1337) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else if (((PlayerInfo*)(peer->data))->isCreator == true) {
						((PlayerInfo*)(peer->data))->displayName = "`c@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`9@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 1337) {
					//if (((PlayerInfo*)(peer->data))->rawName == "btw") {
						//((PlayerInfo*)(peer->data))->displayName = "`w[`#MOMO`w] " + ((PlayerInfo*)(peer->data))->tankIDName;
					//}
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						if (((PlayerInfo*)(peer->data))->isCreator == true) {
							((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
						}
						else
						{
							((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
						}
					}
					else if (((PlayerInfo*)(peer->data))->isCreator == true) {
						((PlayerInfo*)(peer->data))->displayName = "`c@" + ((PlayerInfo*)(peer->data))->tankIDName;
						((PlayerInfo*)(peer->data))->country = "../";
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`c@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 1337) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
					}
					else if (((PlayerInfo*)(peer->data))->isCreator == true) {
						((PlayerInfo*)(peer->data))->displayName = "`c@" + ((PlayerInfo*)(peer->data))->tankIDName;
						((PlayerInfo*)(peer->data))->country = "../";
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`c@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->adminLevel == 1337) {
					if (((PlayerInfo*)(peer->data))->cloth_back == 8552) {
						if (((PlayerInfo*)(peer->data))->isCreator == true) {
							((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
						}
						else
						{
							((PlayerInfo*)(peer->data))->displayName = "`4@Dr. " + ((PlayerInfo*)(peer->data))->tankIDName;
						}
					}
					else if (((PlayerInfo*)(peer->data))->isCreator == true) {
						((PlayerInfo*)(peer->data))->displayName = "`c@" + ((PlayerInfo*)(peer->data))->tankIDName;
						((PlayerInfo*)(peer->data))->country = "../";
					}
					else {
						((PlayerInfo*)(peer->data))->displayName = "`c@" + ((PlayerInfo*)(peer->data))->tankIDName;
					}
				}
			}
		}
	}
}
void updateplayer(ENetPeer* peer) {
	int item = ((PlayerInfo*)(peer->data))->cloth_back;
	if (item == 8552)
	{
		((PlayerInfo*)(peer->data))->isDr = true;
		((PlayerInfo*)(peer->data))->canDoubleJump = true;
	}
	else if (item == 1784 || item == 1674 || item == 9434 || item == 10012 || item == 9466 || item == 10016 || item == 5136 || item == 9760 || item == 2264 || item == 9506 || item == 9476 || item == 1970 || item == 8286 || item == 156 || item == 9434 || item == 8552 || item == 362 || item == 678 || item == 736 || item == 7734 || item == 7762 || item == 818 || item == 1206 || item == 1460 || item == 1550 || item == 1574 || item == 1668 || item == 1672 || item == 1824 || item == 1936 || item == 1938 || item == 2254 || item == 2256 || item == 2258 || item == 2260 || item == 2262 || item == 2264 || item == 2390 || item == 2392 || item == 3120 || item == 3308 || item == 3512 || item == 4534 || item == 4986 || item == 5754 || item == 6144 || item == 6334 || item == 6694 || item == 6818 || item == 6842 || item == 1934 || item == 3134 || item == 6004 || item == 1780 || item == 2158 || item == 2160 || item == 2162 || item == 2164 || item == 2166 || item == 2168 || item == 2438 || item == 2538 || item == 2778 || item == 3858 || item == 350 || item == 998 || item == 1738 || item == 2642 || item == 2982 || item == 3104 || item == 3144 || item == 5738 || item == 3112 || item == 2722 || item == 3114 || item == 4970 || item == 4972 || item == 5020 || item == 6284 || item == 4184 || item == 4628 || item == 5322 || item == 4112 || item == 4114 || item == 3442 || item == 9466 || item == 5136 || item == 9416 || item == 9356 || item == 7104 || item == 8308 || item == 8620)
	{
		((PlayerInfo*)(peer->data))->canDoubleJump = true;
	}
	updatepeffect(peer);
}
void sendState(ENetPeer* peer) {
	if (((PlayerInfo*)(peer->data))->currentWorld == "EXIT")
	{
		return;
	}
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
			float water = 125.0f;
			data.packetType = 0x14;
			data.characterState = ((PlayerInfo*)(peer->data))->characterState; // animation
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
			if (((PlayerInfo*)(peer->data))->cloth_back == 1738) {
				data.YSpeed = 600;
			}
			else {
				data.YSpeed = 1150;
			}
			data.netID = netID;
			data.plantingTree = state;
			BYTE* raw = packPlayerMoving(&data);
			int var = 0x818100;
			memcpy(raw + 1, &var, 3);
			memcpy(raw + 16, &water, 4);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	restoreplayernick(peer);

	Player::OnNameChanged(peer, ((PlayerInfo*)(peer->data))->netID, ((PlayerInfo*)(peer->data))->displayName);

	if (((PlayerInfo*)(peer->data))->cloth_back == 8552)
	{
		GamePacket p2 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 1), 2), 7068), 0));
		memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
		ENetPacket* packet3 = enet_packet_create(p2.data,
			p2.len,
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
		delete p2.data;
	}
	if (((PlayerInfo*)(peer->data))->skill == "Farmer")
	{
		GamePacket p2 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 1), 2), 7064), 0));
		memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
		ENetPacket* packet3 = enet_packet_create(p2.data,
			p2.len,
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
		delete p2.data;
	}
	if (((PlayerInfo*)(peer->data))->skill == "Miner")
	{
		GamePacket p2 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 1), 2), 98), 0));
		memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
		ENetPacket* packet3 = enet_packet_create(p2.data,
			p2.len,
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
		delete p2.data;
	}
	updateplayer(peer);
	if (((PlayerInfo*)(peer->data))->isZombie == true)
	{
		playerconfig(peer, 1150, 130, 0x14);
	}
}
void SendDisplayBlock(ENetPeer* peer, int16_t fg, int16_t bg, int32_t x, int32_t y, int32_t item) {

	int8_t* ExtendedData = new int8_t[13];
	int32_t extendedLen = 13;

	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;

	int8_t* raw = new int8_t[69];

	memcpy(raw, packPlayerMoving(&pmov), 56);
	*(int32_t*)(raw + 52) = extendedLen;

	*(int16_t*)(ExtendedData + 0) = fg;
	*(int16_t*)(ExtendedData + 2) = bg;
	*(int32_t*)(ExtendedData + 4) = 0x0010000;
	ExtendedData[8] = 0x17;
	*(int32_t*)(ExtendedData + 9) = item;

	memcpy(raw + 56, ExtendedData, extendedLen);

	ENetPacket* p = enet_packet_create(0, 74, 1);
	*(int32_t*)(p->data) = 4;
	memcpy(p->data + 4, raw, 69);
	enet_peer_send(peer, 0, p);

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

void sendWorld(ENetPeer* peer, WorldInfo* worldInfo)
{
	int zero = 0;
	((PlayerInfo*)(peer->data))->droppeditemcount = 0;
#ifdef TOTAL_LOG
	cout << "[!] Entering a world..." << endl;
#endif
	if (serverIsFrozen == false)
	{
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
		int allocMem = payloadLen + 2 + nameLen + 12 + (square * 8) + 4 + 16000 + 100 + (worldInfo->droppedCount * 20);
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
			sizeofblockstruct = 8;

			if (getItemDef(tile).blockType == BlockTypes::SIGN || tile == 1420 || tile == 6124) {
				int type = 0x00010000;
				memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
				memcpy(blockPtr + 4, &type, 4);
				BYTE btype = 2;
				memcpy(blockPtr + 8, &btype, 1);
				string signText = worldInfo->items[i].text;
				const char* signTextChars = signText.c_str();
				short length = (short)signText.size();
				memcpy(blockPtr + 9, &length, 2);
				memcpy(blockPtr + 11, signTextChars, length);
				int minus1 = -1;
				memcpy(blockPtr + 11 + length, &minus1, 4);
				sizeofblockstruct += 3 + length + 4;
				dataLen += 3 + length + 4; // it's already 8.
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
			else if (tile == 3832) {
				int type = 0x00010000;
				memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
				memcpy(blockPtr + 4, &type, 4);
				BYTE btype = 0x31;
				memcpy(blockPtr + 8, &btype, 1);


				short flags = 0;
				int item = worldInfo->stuffID;
				int gravity = worldInfo->gravity;
				flags = 3;

				memcpy(blockPtr + 9, &item, 4);
				memcpy(blockPtr + 13, &gravity, 4);
				memcpy(blockPtr + 17, &flags, 2);
				sizeofblockstruct += 10;
				dataLen += 10;
			}
			else if ((worldInfo->items[i].foreground == 0) || (worldInfo->items[i].foreground == 2) || (worldInfo->items[i].foreground == 8) || (worldInfo->items[i].foreground == 100) || (worldInfo->items[i].foreground == 4))
			{
				memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
				int type = 0x00000000;
				// type 1 = locked
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
			}
			else
			{
				memcpy(blockPtr, &zero, 2);
			}
			memcpy(blockPtr + 2, &worldInfo->items[i].background, 2);
			blockPtr += sizeofblockstruct;
		}
		offsetData = dataLen - 100;
		string asdf2 = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		BYTE* data2 = new BYTE[101];
		memcpy(data2 + 0, &zero, 4);
		for (int i = 0; i < asdf2.length(); i += 2)
		{
			char x = ch2n(asdf2[i]);
			x = x << 4;
			x += ch2n(asdf2[i + 1]);
			memcpy(data2 + (i / 2), &x, 1);
		}
		int weather = worldInfo->weather;
		memcpy(data2 + 4, &weather, 4);
		memcpy(data + offsetData, data2, 100);
		memcpy(data + dataLen - 4, &smth, 4);
		ENetPacket* packet2 = enet_packet_create(data,
			dataLen,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		for (int i = 0; i < square; i++) {
			ItemDefinition pro;
			pro = getItemDef(worldInfo->items[i].foreground);
			if ((worldInfo->items[i].foreground == 0) || (getItemDef(worldInfo->items[i].foreground).blockType) == BlockTypes::SIGN || worldInfo->items[i].foreground == 1420 || worldInfo->items[i].foreground == 6214 || (worldInfo->items[i].foreground == 3832) || (worldInfo->items[i].foreground == 4) || (worldInfo->items[i].foreground == 2) || (worldInfo->items[i].foreground == 8) || (worldInfo->items[i].foreground == 100))
				;
			else if (worldInfo->items[i].foreground == 3794)
			{
				int xx = i % xSize, yy = i / xSize;
				sendDShelf(peer, xx, yy, worldInfo->items[i].dshelf1, worldInfo->items[i].dshelf2, worldInfo->items[i].dshelf3, worldInfo->items[i].dshelf4);
			}
			else if (worldInfo->items[i].foreground == 6) updateDoor(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, "`2EXIT``");
			else
			{
				PlayerMoving data;
				data.packetType = 0x3;
				data.characterState = 0x0;
				data.x = i % worldInfo->width;
				data.y = i / worldInfo->height;
				data.punchX = i % worldInfo->width;
				data.punchY = i / worldInfo->width;
				data.XSpeed = 0;
				data.YSpeed = 0;
				data.netID = -1;
				data.plantingTree = worldInfo->items[i].foreground;
				SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
				int x = i % xSize, y = i / xSize;
				UpdateBlockState(peer, x, y, true, worldInfo);
			}
		}
		int idx = 0;
		for (int i = 0; i < worldInfo->droppedItemUid; i++)
		{
			bool found = false;
			for (int j = 0; j < worldInfo->droppedItems.size(); j++)
			{
				if (worldInfo->droppedItems.at(j).uid == i)
				{
					SendDropSingle(peer, -1, worldInfo->droppedItems.at(j).x, worldInfo->droppedItems.at(j).y, worldInfo->droppedItems.at(j).id, worldInfo->droppedItems.at(j).count, 0);
					found = true;
					break;
				}
			}
			if (!found) SendDropSingle(peer, -1, -1000, -1000, 0, 1, 0);
		}
		((PlayerInfo*)(peer->data))->currentWorld = worldInfo->name;
		for (int i = 0; i < xSize; i++) {
			for (int j = 0; j < ySize; j++) {
				int squaresign = i + (j * 100);
				if (worldInfo->items[squaresign].foreground == 2946)
				{
					bool displayexist = std::experimental::filesystem::exists("display/" + worldInfo->name + "X" + std::to_string(squaresign) + ".txt");
					if (displayexist) {
						int x = squaresign % worldInfo->width;
						int y = squaresign / worldInfo->width;
						WorldInfo* world = getPlyersWorld(peer);
						int realid;
						string currentworld = worldInfo->name + "X" + std::to_string(squaresign);
						ifstream getdisplay("display/" + currentworld + ".txt");
						getdisplay >> realid;
						getdisplay.close();
						SendDisplayBlock(peer, world->items[x + (y * world->width)].foreground, world->items[x + (y * world->width)].background, x, y, realid);
					}
				}
				if (getItemDef(worldInfo->items[squaresign].foreground).blockType == BlockTypes::SIGN)
				{
					bool cmdhadi = std::experimental::filesystem::exists("signs/" + worldInfo->name + "X" + std::to_string(squaresign) + ".txt");
					if (cmdhadi) {
						int x123 = squaresign % worldInfo->width;
						int y123 = squaresign / worldInfo->width;
						WorldInfo* world = getPlyersWorld(peer);
						ifstream ifs("signs/" + worldInfo->name + "X" + std::to_string(squaresign) + ".txt");
						string content = "";
						getline(ifs, content);
						onSignBubble(peer, world->items[x123 + (y123 * world->width)].foreground, x123, y123, content, world->items[x123 + (y123 * world->width)].background);
					}
				}
			}
		}
		int otherpeople = 0;
		int count = 0;
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			count++;
			if (isHere(peer, currentPeer))
				otherpeople++;
		}

		int otherpeoples = otherpeople - 1;
		delete[] data;
		delete[] data2;
		Player::PlayAudio(peer, "audio/door_open.wav", 0);
		std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		int gembux = std::atoi(content.c_str());
		Player::OnSetBux(peer, gembux, 1);

		if (((PlayerInfo*)(peer->data))->haveGrowId) {
			PlayerInfo* p = ((PlayerInfo*)(peer->data));
			try {
				std::ifstream ifff("players/" + PlayerDB::getProperName(p->rawName) + ".json");
				json j;
				ifff >> j;
				p->currentWorld = worldInfo->name;
				int bac, han, fac, hai, fee, pan, nec, shi, mas, anc, ban, lgk, lgw, lgb, lgd, lkw, cwd, rfs, cdg, join, level, xp, adminlevel, rubble, rubblexp, amber, amberxp, opal, opalxp, gold, goldxp, sapphire, sapphirexp, diamond, diamondxp, emerald, emeraldxp;
				bool joinguild;
				bac = j["ClothBack"];
				han = j["ClothHand"];
				fac = j["ClothFace"];
				hai = j["ClothHair"];
				fee = j["ClothFeet"];
				pan = j["ClothPants"];
				nec = j["ClothNeck"];
				shi = j["ClothShirt"];
				mas = j["ClothMask"];
				anc = j["ClothAnces"];
				ban = j["isBanned"];
				adminlevel = j["adminLevel"];
				vector <string>frns;
				if (j.count("worldsowned") == 1) {
					for (int i = 0; i < j["worldsowned"].size(); i++) {
						frns.push_back(j["worldsowned"][i]);
					}
				}
				else {
					frns = {};
				}
				level = j["level"];
				xp = j["xp"];
				string guild;
				if (j.count("guild") == 1) {
					guild == j["guild"];
				}
				else {
					guild = "";
				}
				if (j.count("joinguild") == 1) {
					join = j["joinguild"];
				}
				else {
					join = false;
				}
				if (j.count("rubble") == 1) {
					rubble = j["rubble"];
				}
				else {
					rubble = 0;
				}
				if (j.count("rubblexp") == 1) {
					rubblexp = j["rubblexp"];
				}
				else {
					rubblexp = 0;
				}
				// Mining update starts here
				if (j.count("amber") == 1) {
					amber = j["amber"];
				}
				else {
					amber = 0;
				}
				if (j.count("amberxp") == 1) {
					amberxp = j["amberxp"];
				}
				else {
					amberxp = 0;
				}
				if (j.count("opal") == 1) {
					opal = j["opal"];
				}
				else {
					opal = 0;
				}
				if (j.count("opalxp") == 1) {
					opalxp = j["opalxp"];
				}
				else {
					opalxp = 0;
				}
				if (j.count("gold") == 1) {
					gold = j["gold"];
				}
				else {
					gold = 0;
				}
				if (j.count("goldxp") == 1) {
					goldxp = j["goldxp"];
				}
				else {
					goldxp = 0;
				}
				if (j.count("sapphire") == 1) {
					sapphire = j["sapphire"];
				}
				else {
					sapphire = 0;
				}
				if (j.count("sapphirexp") == 1) {
					sapphirexp = j["sapphirexp"];
				}
				else {
					sapphirexp = 0;
				}
				if (j.count("diamond") == 1) {
					diamond = j["diamond"];
				}
				else {
					diamond = 0;
				}
				if (j.count("diamondxp") == 1) {
					diamondxp = j["diamondxp"];
				}
				else {
					diamondxp = 0;
				}
				if (j.count("emerald") == 1) {
					emerald = j["emerald"];
				}
				else {
					emerald = 0;
				}
				if (j.count("emeraldxp") == 1) {
					emeraldxp = j["emeraldxp"];
				}
				else {
					emeraldxp = 0;
				}
				// Mining update ends here
				p->worldsowned = frns;
				p->adminLevel = adminlevel;
				p->cloth_back = bac;
				p->cloth_hand = han;
				p->cloth_face = fac;
				p->cloth_hair = hai;
				p->cloth_feet = fee;
				p->cloth_pants = pan;
				p->cloth_necklace = nec;
				p->cloth_shirt = shi;
				p->cloth_mask = mas;
				p->guild = guild;
				p->joinguild = join;
				p->level = level;
				p->xp = xp;
				p->rubble = rubble;
				p->rubblexp = rubblexp;
				// Mining update starts here
				p->amber = amber;
				p->amberxp = amberxp;
				p->opal = opal;
				p->opalxp = opalxp;
				p->gold = gold;
				p->goldxp = goldxp;
				p->sapphire = sapphire;
				p->sapphirexp = sapphirexp;
				p->diamond = diamond;
				p->diamondxp = diamondxp;
				p->emerald = emerald;
				p->emeraldxp = emeraldxp;
				// Mining update ends here
				//p->friendinfo = frns;
				//p->cloth_ances = anc;
				updateAllClothes(peer);
				ifff.close();
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
			PlayerInventory inventory;
			InventoryItem item;
			item.itemCount = 1;
			item.itemID = 18;
			inventory.items.push_back(item);
			item.itemCount = 1;
			item.itemID = 32;
			inventory.items.push_back(item);
			sendInventory(peer, inventory);
			string guildname = PlayerDB::getProperName(((PlayerInfo*)(peer->data))->guild);
			if (guildname != "") {
				try {
					std::ifstream ifff("guilds/" + guildname + ".json");
					if (ifff.fail()) {
						ifff.close();
						cout << "Failed loading guilds/" + guildname + ".json! From " + ((PlayerInfo*)(peer->data))->displayName + "." << endl;
						((PlayerInfo*)(peer->data))->guild = "";
					}
					json j;
					ifff >> j;
					int gfbg, gffg;
					string gstatement, gleader;
					vector<string> gmembers;
					gfbg = j["backgroundflag"];
					gffg = j["foregroundflag"];
					gstatement == j["GuildStatement"];
					gleader == j["Leader"];
					for (int i = 0; i < j["Member"].size(); i++) {
						gmembers.push_back(j["Member"][i]);
					}
					((PlayerInfo*)(peer->data))->guildBg = gfbg;
					((PlayerInfo*)(peer->data))->guildFg = gffg;
					((PlayerInfo*)(peer->data))->guildStatement = gstatement;
					((PlayerInfo*)(peer->data))->guildLeader = gleader;
					((PlayerInfo*)(peer->data))->guildMembers = gmembers;
					ifff.close();
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
			if (!std::experimental::filesystem::exists("gemstorage/" + PlayerDB::getProperName(p->rawName) + ".txt"))
			{
				ofstream create("gemstorage/" + PlayerDB::getProperName(p->rawName) + ".txt");
				create << 0;
				create.close();
			}
			ifstream fdss("gemstorage/" + PlayerDB::getProperName(p->rawName) + ".txt");
			fdss >> p->plantgems;
			fdss.close();
			if (!std::experimental::filesystem::exists("fragments/" + PlayerDB::getProperName(p->rawName) + ".txt"))
			{
				ofstream create("fragments/" + PlayerDB::getProperName(p->rawName) + ".txt");
				create << 0;
				create << 0;
				create << 0;
				create << 0;
				create.close();
			}
			ifstream fd("fragments/" + PlayerDB::getProperName(p->rawName) + ".txt");
			fd >> p->fEarth;
			fd >> p->fDark;
			fd >> p->fFire;
			fd >> p->fWater;
			fd.close();
			if (p->isDuctaped) sendClothes(peer);
		}
		if (getPlyersWorld(peer)->allowMod != true)
		{
			((PlayerInfo*)(peer->data))->canWalkInBlocks = false;
			((PlayerInfo*)(peer->data))->skinColor = 0x8295C3FF;
			sendState(peer);
		}
		else
		{
			if (((PlayerInfo*)(peer->data))->isZombie == false)
			{
				Player::OnConsoleMessage(peer, "`2Owner `ohas `2enabled `5Mod-Noclip `oin this world.");
				((PlayerInfo*)(peer->data))->canWalkInBlocks = true;
				sendState(peer);
			}
		}
		if (((PlayerInfo*)(peer->data))->effect != 8421376)
		{
			((PlayerInfo*)(peer->data))->effect = ((PlayerInfo*)(peer->data))->effect;
			sendState(peer);
			sendPuncheffectpeer(peer, ((PlayerInfo*)(peer->data))->effect);
		}
	}
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
void sendDrop(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect)
{
	if (item >= maxItems) return;
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

void DropItem(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect)
{
	WorldInfo* world = getPlyersWorld(peer);
	if (!world) return;
	if (item >= maxItems) return;
	if (item < 0) return;
	DroppedItem itemDropped;
	itemDropped.id = item;
	itemDropped.count = count;
	itemDropped.x = x;
	itemDropped.y = y;
	itemDropped.uid = world->droppedItemUid++;
	world->droppedItems.push_back(itemDropped);
	world->droppedCount - 1;
	sendDrop(peer, netID, x, y, item, count, specialEffect);
}

void SaveItemMoreTimes(int fItemid, int fQuantity, ENetPeer* peer, bool& success)
{
		size_t invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;
		bool invfull = false;
		bool alreadyhave = false;
		if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsizee && CheckItemExists(peer, fItemid) == false) {
			GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! Your inventory is full! You can purchase an inventory upgrade in the shop.`5Your item was dropped near to you.|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|"));
			ENetPacket* packet = enet_packet_create(ps.data,
				ps.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete ps.data;
			int xx = ((PlayerInfo*)(peer->data))->x + (32 * (((PlayerInfo*)(peer->data))->isRotatedLeft ? -1 : 1));
			int netid = -1;
			int yy = ((PlayerInfo*)(peer->data))->y;
			DropItem(peer, netid, xx, yy, fItemid, fQuantity, 0);
			alreadyhave = true;
		}
		bool isFullStock = false;
		bool isInInv = false;
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
		{
			if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount >= 200) {
				GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! You already have full stock of this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|"));
				ENetPacket* packet = enet_packet_create(ps.data,
					ps.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete ps.data;
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
				//jj["items"][aposition]["aposition"] = aposition;
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
					//oo.close();
					for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
					{
						if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid)
						{
							((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount += fQuantity;
							sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
						}
					}
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
}
void GiveChestPrizeItem(ENetPeer* peer, int itemid, int itemAmount, int chestWls)
{
	bool success = false;
	SaveItemMoreTimes(itemid, itemAmount, peer, success);
	if (success)
	{
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOOT] `^You Have Obtained `9" + getItemDef(itemid).name + "`^."));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
		GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`q" + ((PlayerInfo*)(peer->data))->displayName + " `^Have obtained the `9" + getItemDef(itemid).name + "`^!"), 0));
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
		int effect = 92;
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
				Player::OnParticleEffect(currentPeer, effect, x, y, 0);
			}
		}
	}
}
void GiveLockePrize(ENetPeer* peer, int itemid, int itemAmount, int chestWls)
{
	bool success = false;
	SaveItemMoreTimes(itemid, itemAmount, peer, success);
	if (success)
	{
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`1[Locke] `^You Have Obtained `9" + getItemDef(itemid).name + "`^."));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
		GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`q" + ((PlayerInfo*)(peer->data))->displayName + " `^Have obtained the `9" + getItemDef(itemid).name + "`^!"), 0));
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
		int effect = 19;
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
				Player::OnParticleEffect(currentPeer, effect, x, y, 0);
			}
		}
	}
}
void GiveGBCPrize(ENetPeer* peer, int itemid, int itemAmount, int chestWls)
{
	bool success = false;
	SaveItemMoreTimes(itemid, itemAmount, peer, success);
	if (success)
	{
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4[VALENTINE] `^You Have Obtained `9" + getItemDef(itemid).name + "`^."));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
		GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`q" + ((PlayerInfo*)(peer->data))->displayName + " `^Have obtained the `9" + getItemDef(itemid).name + "`^!"), 0));
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
		int effect = 19;
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
				Player::OnParticleEffect(currentPeer, effect, x, y, 0);
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
					hmon_owner = world->items[i].monitor;
					ENetPeer* currentPeer;

					for (currentPeer = server->peers;
						currentPeer < &server->peers[server->peerCount];
						++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
							continue;
						PlayerInfo* cp = ((PlayerInfo*)(currentPeer->data));
						if (cp->displayName == hmon_owner) {
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
void joinWorld(ENetPeer* peer, string act, int x2, int y2)
{
	if (((PlayerInfo*)(peer->data))->isBot == true) {
		enet_peer_disconnect_now(peer, 0);
	}
	if (((PlayerInfo*)(peer->data))->isConfirmingCode == true) {
		enet_peer_disconnect_now(peer, 0);
	}
	if (act.length() > 24) {
		Player::OnConsoleMessage(peer, "`4Sorry, but world names with more than 24 characters are not allowed!");
		Player::OnFailedToEnterWorld(peer);
	}
	if (act.length() < 0) {
		Player::OnConsoleMessage(peer, "`4Sorry, but world names less than 0 characters are not allowed!");
		Player::OnFailedToEnterWorld(peer);
	}
	else {
		string upsd = act;
		std::transform(upsd.begin(), upsd.end(), upsd.begin(), ::toupper);
		if (upsd == "CON" || upsd == "PRN" || upsd == "AUX" || upsd == "NUL" || upsd == "COM1" || upsd == "COM2" || upsd == "COM3" || upsd == "COM4" || upsd == "COM5" || upsd == "COM6" || upsd == "COM7" || upsd == "COM8" || upsd == "COM9" || upsd == "LPT1" || upsd == "LPT2" || upsd == "LPT3" || upsd == "LPT4" || upsd == "LPT5" || upsd == "LPT6" || upsd == "LPT7" || upsd == "LPT8" || upsd == "LPT9" || upsd == "con" || upsd == "prn" || upsd == "aux" || upsd == "nul" || upsd == "com1" || upsd == "com2" || upsd == "com3" || upsd == "com4" || upsd == "com5" || upsd == "com6" || upsd == "com7" || upsd == "com8" || upsd == "com9" || upsd == "lpt1" || upsd == "lpt2" || upsd == "lpt3" || upsd == "lpt4" || upsd == "lpt5" || upsd == "lpt6" || upsd == "lpt7" || upsd == "lpt8" || upsd == "lpt9")
		{
			((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
			Player::OnConsoleMessage(peer, "`4To reduce confusion, this is not a valid world name`w. `oTry another one`w?``");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (upsd.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
			Player::OnTextOverlay(peer, "Symbols not allowed!");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (upsd == "LEGENDARYMOUNTAIN")
		{
			if (((PlayerInfo*)(peer->data))->level <= 39)
			{
				Player::OnConsoleMessage(peer, "`$You are not Legendary enough for this MOUNTAIN.");
				Player::OnFailedToEnterWorld(peer);
				return;
			}
		}
		if (std::experimental::filesystem::exists("worlds/" + act + ".json"))
		{
			std::streampos fsize = 0;
			std::ifstream myfile("worlds/" + act + ".json", ios::in);  // File is of type const char*
			fsize = myfile.tellg();         // The file pointer is currently at the beginning
			myfile.seekg(0, ios::end);      // Place the file pointer at the end of file
			fsize = myfile.tellg() - fsize;
			myfile.close();
			static_assert(sizeof(fsize) >= sizeof(long long), "Oops.");
			if (fsize <= 90000)
			{
				Player::OnConsoleMessage(peer, "`4Oh no! ``This world have been corrupted.");
				Player::OnFailedToEnterWorld(peer);
				return;
			}
		}
		using namespace std::chrono;
		if (((PlayerInfo*)(peer->data))->lastJoinReq + 500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
		{
			((PlayerInfo*)(peer->data))->lastJoinReq = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		}
		else {
			Player::OnConsoleMessage(peer, "`oPlease Do not Spam Entering World button it don't helps you ;-;``");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId == false)
		{
			if (act != "START")
			{
				WorldInfo info1 = worldDB.get("START");
				sendWorld(peer, &info1);
				Player::OnTextOverlay(peer, "`7Create `^Grow-ID `7First!");
				int id = 244;
				int xde = 3040;
				int yde = 736;
				for (int j = 0; j < info1.width * info1.height; j++)
				{
					if (info1.items[j].foreground == 6) {
						xde = (j % info1.width) * 32;
						yde = (j / info1.width) * 32;
					}
				}
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(xde) + "|" + std::to_string(yde) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
				((PlayerInfo*)(peer->data))->netID = cId;
				onPeerConnect(peer);
				cId++;
				sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
				return;
			}
		}
		if (((PlayerInfo*)(peer->data))->isCursed == true)
		{
			if (act != "HELL")
			{
				WorldInfo info1 = worldDB.get("HELL");
				sendWorld(peer, &info1);
				Player::OnTextOverlay(peer, "You are cursed!");
				int id = 244;
				int xde = 3040;
				int yde = 736;
				for (int j = 0; j < info1.width * info1.height; j++)
				{
					if (info1.items[j].foreground == 6) {
						xde = (j % info1.width) * 32;
						yde = (j / info1.width) * 32;
					}
				}
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(xde) + "|" + std::to_string(yde) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
				((PlayerInfo*)(peer->data))->netID = cId;
				onPeerConnect(peer);
				cId++;
				sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
				return;
			}
		}
		WorldInfo info = worldDB.get(act);
		WorldInfo info2 = worldDB.get("HELL");
		WorldInfo info3 = worldDB.get("START");

		int playeriai = getPlayersCountInWorldSave(info.name);
		if (playeriai >= 20)
		{
			Player::OnConsoleMessage(peer, "World is at max capacity. Try again later...");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		bool existsban = std::experimental::filesystem::exists("worldbans/" + info.name + "/" + ((PlayerInfo*)(peer->data))->rawName);
		if (existsban)
		{
			Player::OnConsoleMessage(peer, "`4Oh no! ``You've been banned from that world by its owner! Try again later after ban wears off.");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (((PlayerInfo*)(peer->data))->isUseCode == false)
		{
			Player::OnConsoleMessage(peer, "`@Your account is `4Not `@Protected, To Secure Your account Wrench on yourself!");
		}
		if (((PlayerInfo*)(peer->data))->haveGrowId)
		{
			if (((PlayerInfo*)(peer->data))->lastdailyGems <= GetCurrentTimeInternalSeconds() / 60)
			{
				((PlayerInfo*)(peer->data))->lastdailyGems = (GetCurrentTimeInternalSeconds() / 60) + 1440; // 1440 - 24 valandos minutemis.
				int haveGems = 0;
				ifstream getgems("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
				getgems >> haveGems;
				getgems.close();
				int gemsReward = 50000;
				haveGems += gemsReward;
				Player::OnConsoleMessage(peer, "`6[REWARD] `^You got `2" + to_string(gemsReward) + " `9Gems `^For joining the server!");
				GamePacket ps2notf = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"), "interface/science_button.rttex"), "`^You Received `2" + to_string(gemsReward) + " `9Gems `^For joining the server!"), "audio/hub_open.wav"), 0));
				ENetPacket* packet3s = enet_packet_create(ps2notf.data,
					ps2notf.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet3s);
				delete ps2notf.data;
				ofstream myfileGems("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
				myfileGems << haveGems;
				myfileGems.close();
				ofstream updateLastDailyGems("dailyrewards/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
				updateLastDailyGems << ((PlayerInfo*)(peer->data))->lastdailyGems;
				updateLastDailyGems.close();
			}
			bool iscontains = false;
			SearchInventoryItem(peer, 6336, 1, iscontains);
			if (!iscontains)
			{
				bool success = true;
				SaveItemMoreTimes(6336, 1, peer, success);
				Player::OnAddNotification(peer, "`^You Received the `9Growpedia", "audio/hub_open.wav", "interface/science_button.rttex");
			}
			bool iscontainss = false;
			SearchInventoryItem(peer, 3162, 1, iscontainss);
			if (!iscontainss)
			{
				bool success = true;
				SaveItemMoreTimes(3162, 1, peer, success);
				Player::OnAddNotification(peer, "`^You Received the `9Twin Swords", "audio/hub_open.wav", "interface/science_button.rttex");
			}
			

			if (((PlayerInfo*)(peer->data))->timeTogetToken == 0)
			{
				((PlayerInfo*)(peer->data))->timeTogetToken = GetCurrentTimeInternalSeconds() + 10800; // 18000 seconds - 5 hours
			}
			if (((PlayerInfo*)(peer->data))->timeTogetToken <= GetCurrentTimeInternalSeconds())
			{
				bool checkSuccess = false;
				SaveItemMoreTimes(1486, 1, peer, checkSuccess);
				if (!checkSuccess)
				{
					Player::OnConsoleMessage(peer, "`6[REWARD] `@Error issuing a reward!");
				}
				else
				{
					((PlayerInfo*)(peer->data))->timeTogetToken = GetCurrentTimeInternalSeconds() + 10800; // 18000 seconds - 5 hours
					givequestkatanastep3storetoken(peer, 1);
					Player::OnConsoleMessage(peer, "`6[REWARD] `^You Obtained 1 `@Growtoken `^For `23 `^hours online in GrowtopiaLR!");
				}
			}
		}
		sendWorld(peer, &info);
		int x = 3040;
		int y = 736;
		for (int j = 0; j < info.width * info.height; j++)
		{
			if (info.items[j].foreground == 6) {
				x = (j % info.width) * 32;
				y = (j / info.width) * 32;
			}
		}
		if (x2 != 0 && y2 != 0)
		{
			x = x2;
			y = y2;
		}

		if (((PlayerInfo*)(peer->data))->adminLevel >= 777)
		{
			int id = 244;
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|1\ntype|local\n"));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
			((PlayerInfo*)(peer->data))->netID = cId;
			onPeerConnect(peer);
			cId++;
			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		}
		else {
			int id = 245;
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
			((PlayerInfo*)(peer->data))->netID = cId;
			onPeerConnect(peer);
			cId++;
			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		}
		WorldInfo* world = getPlyersWorld(peer);
		string nameworld = world->name;
		string ownerworld = world->owner;
		int count = 0;
		ENetPeer* currentPeer;
		string name = "";
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			count++;
		}
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
					GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet2);
					delete p2.data;
					continue;
					int x = ((PlayerInfo*)(peer->data))->x;
					int y = ((PlayerInfo*)(peer->data))->y;
					updateAllClothes(peer);
				}
			}
		}
		Player::OnConsoleMessage(peer, "`oWorld `w" + nameworld+ " [`2Haunted!`w]`o Entered. There are `w" + to_string(getPlayersCountInWorld(info.name)) + "`o other people here, `w" + to_string(GetPlayerCountServer()) + " `oonline.");
		int otherpeople = 0;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer))
				otherpeople++;
		}
		int otherpeoples = otherpeople - 1;
		if (((PlayerInfo*)(peer->data))->isinv == false)
		{
			Player::OnConsoleMessage(peer, "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + "`` `5entered, `w" + std::to_string(otherpeoples) + "`` `5others here>```w");
			Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`5<`w" + ((PlayerInfo*)(peer->data))->displayName + " `5entered, `w" + std::to_string(getPlayersCountInWorld(((PlayerInfo*)(peer->data))->currentWorld) - 1) + "`` others here>``", 0, false);
		}
		if (ownerworld != "") {
			Player::OnConsoleMessage(peer, "`5[`0" + nameworld + " `$World Locked `oby `w" + ownerworld + "`5]");
		}
	}
}
void testCount(ENetPeer* peer) {
	using namespace std::chrono;
	if (((PlayerInfo*)(peer->data))->packetsec + 1000 > (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
		if (((PlayerInfo*)(peer->data))->packetinsec >= 50) {
			enet_peer_reset(peer);
		}
		else {
			((PlayerInfo*)(peer->data))->packetinsec = ((PlayerInfo*)(peer->data))->packetinsec + 1;
		}
	}
	else {
		((PlayerInfo*)(peer->data))->packetsec = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		((PlayerInfo*)(peer->data))->packetinsec = 0;
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
void sendPlayerToWorld(ENetPeer* peer, PlayerInfo* player, string wrldname)
{
	toUpperCase(wrldname);



	if (wrldname == "CON" || wrldname == "NUL" || wrldname == "PRN" || wrldname == "AUX" || wrldname == "CLOCK$" || wrldname == "COM0" || wrldname == "COM1" || wrldname == "COM2" || wrldname == "COM3" || wrldname == "COM4" || wrldname == "COM5" || wrldname == "COM6" || wrldname == "COM7" || wrldname == "COM8" || wrldname == "COM9" || wrldname == "LPT0" || wrldname == "LPT1" || wrldname == "LPT2" || wrldname == "LPT3" || wrldname == "LPT4" || wrldname == "LPT5" || wrldname == "LPT6" || wrldname == "LPT7" || wrldname == "LPT8" || wrldname == "LPT9")
	{
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`ono"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	else if (((PlayerInfo*)(peer->data))->isConfirmingCode == true) {
		enet_peer_disconnect_now(peer, 0);
	}
	else
	{
		{
			sendPlayerLeave(peer, (PlayerInfo*)(peer->data));
		}
		WorldInfo info = worldDB.get(wrldname);
		sendWorld(peer, &info);
		int x = 3040;
		int y = 736;
		for (int j = 0; j < info.width * info.height; j++)
		{
			if (info.items[j].foreground == 6) {
				x = (j % info.width) * 32;
				y = (j / info.width) * 32;
			}
		}
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
		((PlayerInfo*)(peer->data))->netID = cId;
		onPeerConnect(peer);
		cId++;
		sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
	}
}
void sendFrozenState(ENetPeer* peer)
{
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
			data.packetType = 0x14;
			data.characterState = 0; // animation
			data.x = 1000;
			data.y = 100;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 600;
			data.netID = netID;
			data.plantingTree = 2048;
			BYTE* raw = packPlayerMoving(&data);
			int var = info->effect; // placing and breking
			memcpy(raw + 1, &var, 3);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}
void sendWorldOffers(ENetPeer* peer)
{
	if (!((PlayerInfo*)(peer->data))->isIn) return;
	vector<WorldInfo> worlds = worldDB.getRandomWorlds();
	string worldOffers = "default|";
	if (worlds.size() > 0) {
		worldOffers += worlds[0].name;
	}
	worldOffers += "\nadd_button|Start|START|0.6|3629161471|\n";
	for (int i = 0; i < worlds.size(); i++) {
		worldOffers += "add_floater|" + worlds[i].name + "|" + std::to_string(getPlayersCountInWorld(worlds[i].name)) + "|0.55|3529161471\n";
	}
	GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnRequestWorldSelectMenu"), worldOffers));
	ENetPacket* packet3 = enet_packet_create(p3.data,
		p3.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete p3.data;
	//enet_host_flush(server);
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
bool isSeed(int block)
{
	return block % 2 == 1;
}

void sendHeatwave(ENetPeer* peer, uint8_t red, uint8_t green, uint8_t blue)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
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

void playerRespawn(ENetPeer* peer, bool isDeadByTile) {
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
	GamePacket p5 = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 2));
	memcpy(p5.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	ENetPacket* packet5 = enet_packet_create(p5.data,
		p5.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet5);
	GamePacket p2;
	WorldInfo* world = getPlyersWorld(peer);
	int x = 3040;
	int y = 736;
	if (!world) return;
	for (int i = 0; i < world->width * world->height; i++)
	{
		if (world->items[i].foreground == 6) {
			x = (i % world->width) * 32;
			y = (i / world->width) * 32;
		}
	}
	if (((PlayerInfo*)(peer->data))->ischeck == true) {
		p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), ((PlayerInfo*)(peer->data))->checkx, ((PlayerInfo*)(peer->data))->checky));
	}
	else {
		p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
	}
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
void sendChatMessage(ENetPeer* peer, int netID, string message)
{
	if (((PlayerInfo*)(peer->data))->currentWorld == "EXIT") return;
	if (((PlayerInfo*)(peer->data))->isIn == false) return;
	if (message.length() >= 80) return;
	if (message.length() == 0) return;
	if (1 > (message.size() - countSpaces(message))) return;
	removeExtraSpaces(message);
	message = trimString(message);
	if (((PlayerInfo*)(peer->data))->haveGrowId == true) {

		string ccode;
		if (((PlayerInfo*)(peer->data))->adminLevel == 7) {
			ccode = "5";
		}
		if (((PlayerInfo*)(peer->data))->adminLevel == 6) {
			ccode = "5";
		}
		if (((PlayerInfo*)(peer->data))->adminLevel == 5) {
			ccode = "1";
		}
		if (((PlayerInfo*)(peer->data))->adminLevel == 4) {
			ccode = "^";
		}
		if (((PlayerInfo*)(peer->data))->adminLevel == 3) {
			ccode = "3";
		}
		if (((PlayerInfo*)(peer->data))->adminLevel == 2) {
			ccode = "2";
		}
		if (((PlayerInfo*)(peer->data))->adminLevel == 1) {
			ccode = "c";
		}
		if (((PlayerInfo*)(peer->data))->adminLevel == 0) {
			ccode = "w";
		}
		if (((PlayerInfo*)(peer->data))->isNicked == true)
		{
			ccode = "w";
		}
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
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[WR]_ `6<`w" + name + "`6> `" + ccode + message));
		GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`" + ccode + message), 0));
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
		if (isHere(peer, currentPeer) && ((PlayerInfo*)(currentPeer->data))->isinv == false)
		{
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
void sendTake(ENetPeer* peer, int netID, int x, int y, int item)
{
	if (item >= 2147480000) return;
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
			SendPacketRaw(4, packPlayerMoving(&data), 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void ngentot(ENetPeer* peer)
{
	json items;
	auto jjall = json::array();
	json jj;
	auto invsize = static_cast<PlayerInfo*>(peer->data)->inventory.items.size();
	try
	{
		ofstream ofs("inventory/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		for (auto i = 0; i < 200; i++)
		{
			if (i < invsize)
			{
				jj["aposition"] = i + 1;
				jj["itemid"] = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID;
				jj["quantity"] = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
				jjall.push_back(jj);
			}
			else
			{
				jj["aposition"] = i + 1;
				jj["itemid"] = 0;
				jj["quantity"] = 0;
				jjall.push_back(jj);
			}
		}
		items["items"] = jjall;
		ofs << items << std::endl;
		ofs.close();
	}
	catch (std::exception&)
	{
		enet_peer_disconnect_now(peer, 0);
	}
	catch (std::runtime_error&)
	{
		enet_peer_disconnect_now(peer, 0);
	}
	catch (...)
	{
		enet_peer_disconnect_now(peer, 0);
	}
}

int FixCountItem(int number)
{
	if (number == -128)
	{
		return 128;
	}
	else if (number == -127)
	{
		return 129;
	}
	else if (number == -126)
	{
		return 130;
	}
	else if (number == -125)
	{
		return 131;
	}
	else if (number == -124)
	{
		return 132;
	}
	else if (number == -123)
	{
		return 133;
	}
	else if (number == -122)
	{
		return 134;
	}
	else if (number == -121)
	{
		return 135;
	}
	else if (number == -120)
	{
		return 136;
	}
	else if (number == -119)
	{
		return 137;
	}
	else if (number == -118)
	{
		return 138;
	}
	else if (number == -117)
	{
		return 139;
	}
	else if (number == -116)
	{
		return 140;
	}
	else if (number == -115)
	{
		return 141;
	}
	else if (number == -114)
	{
		return 142;
	}
	else if (number == -113)
	{
		return 143;
	}
	else if (number == -112)
	{
		return 144;
	}
	else if (number == -111)
	{
		return 145;
	}
	else if (number == -110)
	{
		return 146;
	}
	else if (number == -109)
	{
		return 147;
	}
	else if (number == -108)
	{
		return 148;
	}
	else if (number == -107)
	{
		return 149;
	}
	else if (number == -106)
	{
		return 150;
	}
	else if (number == -105)
	{
		return 151;
	}
	else if (number == -104)
	{
		return 152;
	}
	else if (number == -103)
	{
		return 153;
	}
	else if (number == -102)
	{
		return 154;
	}
	else if (number == -101)
	{
		return 155;
	}
	else if (number == -100)
	{
		return 156;
	}
	else if (number == -99)
	{
		return 157;
	}
	else if (number == -98)
	{
		return 158;
	}
	else if (number == -97)
	{
		return 159;
	}
	else if (number == -96)
	{
		return 160;
	}
	else if (number == -95)
	{
		return 161;
	}
	else if (number == -94)
	{
		return 162;
	}
	else if (number == -93)
	{
		return 163;
	}
	else if (number == -92)
	{
		return 164;
	}
	else if (number == -91)
	{
		return 165;
	}
	else if (number == -90)
	{
		return 166;
	}
	else if (number == -89)
	{
		return 167;
	}
	else if (number == -88)
	{
		return 168;
	}
	else if (number == -87)
	{
		return 169;
	}
	else if (number == -86)
	{
		return 170;
	}
	else if (number == -85)
	{
		return 171;
	}
	else if (number == -84)
	{
		return 172;
	}
	else if (number == -83)
	{
		return 173;
	}
	else if (number == -82)
	{
		return 174;
	}
	else if (number == -81)
	{
		return 175;
	}
	else if (number == -80)
	{
		return 176;
	}
	else if (number == -79)
	{
		return 177;
	}
	else if (number == -78)
	{
		return 178;
	}
	else if (number == -77)
	{
		return 179;
	}
	else if (number == -76)
	{
		return 180;
	}
	else if (number == -75)
	{
		return 181;
	}
	else if (number == -74)
	{
		return 182;
	}
	else if (number == -73)
	{
		return 183;
	}
	else if (number == -72)
	{
		return 184;
	}
	else if (number == -71)
	{
		return 185;
	}
	else if (number == -70)
	{
		return 186;
	}
	else if (number == -69)
	{
		return 187;
	}
	else if (number == -68)
	{
		return 188;
	}
	else if (number == -67)
	{
		return 189;
	}
	else if (number == -66)
	{
		return 190;
	}
	else if (number == -65)
	{
		return 191;
	}
	else if (number == -64)
	{
		return 192;
	}
	else if (number == -63)
	{
		return 193;
	}
	else if (number == -62)
	{
		return 194;
	}
	else if (number == -61)
	{
		return 195;
	}
	else if (number == -60)
	{
		return 196;
	}
	else if (number == -59)
	{
		return 197;
	}
	else if (number == -58)
	{
		return 198;
	}
	else if (number == -57)
	{
		return 199;
	}
	else if (number == -56)
	{
		return 200;
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

void AddItemToInv2(ENetPeer* peer, int itemId, int count)
{
	PlayerInventory* inventory = &((PlayerInfo*)(peer->data))->inventory;
	bool iscontains = false;
	SearchInventoryItem(peer, itemId, 1, iscontains);
	if (!iscontains)
	{
		bool success = true;
		SaveShopsItemMoreTimes(itemId, count, peer, success);
	}
	else
	{
		short int currentItemCount = 0;
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
		{
			if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == itemId)
			{
				currentItemCount = (unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount;
				if (currentItemCount < 0)
				{
					currentItemCount = FixCountItem((unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount);
				}
			}
		}
		int plusItem = currentItemCount + count;
		int idx = HasItemsInInv(peer, itemId, 1);
		if (plusItem > 200)
		{
			Player::OnConsoleMessage(peer, "Taked 200." + to_string(((PlayerInfo*)(peer->data))->x) + " / " + to_string(((PlayerInfo*)(peer->data))->y) + to_string(plusItem - 200));
			inventory->items.at(idx).itemCount = 200;
			int xx = ((PlayerInfo*)(peer->data))->x;
			int netid = -1;
			int yy = ((PlayerInfo*)(peer->data))->y;
			DropItem(peer, netid, xx, yy, itemId, plusItem - 200, 0);
		}
		else
		{
			inventory->items.at(idx).itemCount = currentItemCount + count;
		}
	}
	sendInventory(peer, *inventory);
}
void sendResetState(ENetPeer* peer)
{
	if (((PlayerInfo*)(peer->data))->isCursed)
	{
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
				data.packetType = 0x14;
				data.characterState = 0; // animation
				data.x = 1000;
				data.y = 100;
				data.punchX = 0;
				data.punchY = 0;
				data.XSpeed = 300;
				data.YSpeed = 600;
				data.netID = netID;
				data.plantingTree = 4096;
				BYTE* raw = packPlayerMoving(&data);
				int var = info->effect; // placing and breking
				memcpy(raw + 1, &var, 3);
				SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			else
			{
				if (((PlayerInfo*)(peer->data))->isDuctaped)
				{
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
							data.packetType = 0x14;
							data.characterState = 0; // animation
							data.x = 1000;
							data.y = 100;
							data.punchX = 0;
							data.punchY = 0;
							data.XSpeed = 300;
							data.YSpeed = 600;
							data.netID = netID;
							data.plantingTree = 8192;
							BYTE* raw = packPlayerMoving(&data);
							int var = info->effect; // placing and breking
							memcpy(raw + 1, &var, 3);
							SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
						}
						else
						{
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
							data.plantingTree = 2;
							BYTE* raw = packPlayerMoving(&data);
							int var = info->effect; // placing and breking
							memcpy(raw + 1, &var, 3);
							SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
						}
					}
				}
			}
		}
	}
}
void sendPlayerToPlayer(ENetPeer* peer, ENetPeer* otherpeer)
{
	sendPlayerLeave(peer, (PlayerInfo*)(peer->data));
	WorldInfo info = worldDB.get(((PlayerInfo*)(otherpeer->data))->currentWorld);
	sendWorld(peer, &info);
	int x = ((PlayerInfo*)(otherpeer->data))->x;
	int y = ((PlayerInfo*)(otherpeer->data))->y;
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
	((PlayerInfo*)(peer->data))->netID = cId;
	onPeerConnect(peer);
	cId++;
	sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
}
void sendPlayerToWorld2(ENetPeer* peer, PlayerInfo* player, string wrldname, int x_ = -1, int y_ = -1)
{
	toUpperCase(wrldname);
	if (wrldname == "CON" || wrldname == "NUL" || wrldname == "PRN" || wrldname == "AUX" || wrldname == "CLOCK$" || wrldname == "COM0" || wrldname == "COM1" || wrldname == "COM2" || wrldname == "COM3" || wrldname == "COM4" || wrldname == "COM5" || wrldname == "COM6" || wrldname == "COM7" || wrldname == "COM8" || wrldname == "COM9" || wrldname == "LPT0" || wrldname == "LPT1" || wrldname == "LPT2" || wrldname == "LPT3" || wrldname == "LPT4" || wrldname == "LPT5" || wrldname == "LPT6" || wrldname == "LPT7" || wrldname == "LPT8" || wrldname == "LPT9")
	{
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`eWhoops! `wThis `oworld`w can't be warped to, as it is used by `4System`w.``"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	else
	{
		{
			sendPlayerLeave(peer, (PlayerInfo*)(peer->data));
		}
		WorldInfo info = worldDB.get(wrldname);
		sendWorld(peer, &info);
		int x = 3040;
		int y = 736;
		for (int j = 0; j < info.width * info.height; j++)
		{
			if (info.items[j].foreground == 6) {
				x = (j % info.width) * 32;
				y = (j / info.width) * 32;
			}
		}
		if (x_ != -1 && y_ != -1) { x = x_ * 32; y = y_ * 32; }
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
		((PlayerInfo*)(peer->data))->netID = cId;
		onPeerConnect(peer);
		cId++;
		sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
	}
}
void SendGamePacket(ENetPeer* peer, GamePacket* p)
{
	ENetPacket* packet1 = enet_packet_create(p->data,
		p->len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet1);
}
void DoCancelTransitionAndTeleport(ENetPeer* peer, int x, int y)
{
	GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnZoomCamera"), 2));
	SendGamePacket(peer, &p);
	GamePacket p2 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
	memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	SendGamePacket(peer, &p2);
	GamePacket p3 = packetEnd(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1));
	SendGamePacket(peer, &p3);
	GamePacket p4 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x * 32, y * 32));
	memcpy(p4.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	SendGamePacket(peer, &p4);
}
void DoEnterDoor(ENetPeer* peer, WorldInfo* world, int x, int y)
{
	using namespace::std::chrono;
	if (((PlayerInfo*)(peer->data))->lastenterdoor + 1200 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
	{
		((PlayerInfo*)(peer->data))->lastenterdoor = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
	}
	else {
		Player::OnConsoleMessage(peer, "slow down before entering doors");
		x = 0;
		y = 0;
		for (int j = 0; j < world->width * world->height; j++)
		{
			if (world->items[j].foreground == 6) {
				x = (j % world->width);
				y = (j / world->width);
			}
		}
		DoCancelTransitionAndTeleport(peer, x, y);
		return;
	}
	int idx = x + world->width * y;
	{
		WorldItem block = world->items[idx];
		if (block.destWorld == "EXIT")
		{
			if (((PlayerInfo*)(peer->data))->canExit)
			{
				string online = "";
				int total = 0;
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (((PlayerInfo*)(currentPeer->data))->adminLevel >= 0) {
						total++;
					}
				}
				Player::OnConsoleMessage(peer, "Where would you like to go? (`w" + to_string(total) + " `oonline)");
				sendPlayerLeave(peer, (PlayerInfo*)(peer->data));
				sendWorldOffers(peer);
				((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
			}
		}
		if (std::experimental::filesystem::exists("worlds/" + block.destWorld + ".json"))
		{
			std::streampos fsize = 0;
			std::ifstream myfile("worlds/" + block.destWorld + ".json", ios::in);  // File is of type const char*
			fsize = myfile.tellg();         // The file pointer is currently at the beginning
			myfile.seekg(0, ios::end);      // Place the file pointer at the end of file
			fsize = myfile.tellg() - fsize;
			myfile.close();
			static_assert(sizeof(fsize) >= sizeof(long long), "Oops.");
			if (fsize <= 90000)
			{
				Player::OnConsoleMessage(peer, "`4Oh no! ``This world have been corrupted.");
				DoCancelTransitionAndTeleport(peer, x, y);
				return;
			}
		}
		if (block.destWorld == "QQ")
		{
			if (((PlayerInfo*)(peer->data))->level <= 9)
			{
				Player::OnTextOverlay(peer, "You must be at least level 10!");
				DoCancelTransitionAndTeleport(peer, x, y);
				return;
			}
		}
		if (block.destWorld == "")
		{
			// it's this world, find a door here
			int x = 0;
			int y = 0;
			for (int i = 0; i < world->width * world->height; i++)
			{
				ItemDefinition def = getItemDef(world->items[i].foreground);
				if (def.blockType == BlockTypes::DOOR) {
					WorldItem blockDest = world->items[i];
					if (blockDest.currId == block.destId)
					{
						x = (i % world->width);
						y = (i / world->width);
						DoCancelTransitionAndTeleport(peer, x, y);
						return;
					}
				}
			}
			x = 0;
			y = 0;
			for (int j = 0; j < world->width * world->height; j++)
			{
				if (world->items[j].foreground == 6) {
					x = (j % world->width);
					y = (j / world->width);
				}
			}
			DoCancelTransitionAndTeleport(peer, x, y);
		}
		else
		{
			try
			{
				WorldInfo worldDest = worldDB.get(block.destWorld);

				bool existsban = std::experimental::filesystem::exists("worldbans/" + block.destWorld + "/" + ((PlayerInfo*)(peer->data))->rawName);
				if (existsban)
				{
					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Oh no! ``You've been banned from that world by its owner! Try again later after ban wears off."));
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet);
					delete p.data;
					DoCancelTransitionAndTeleport(peer, x, y);
					return;
				}

				if (block.destId == "")
				{
					int x_ = 0;
					int y_ = 0;
					for (int j = 0; j < worldDest.width * worldDest.height; j++)
					{
						if (worldDest.items[j].foreground == 6) {
							x_ = (j % worldDest.width);
							y_ = (j / worldDest.width);
						}
					}
					sendPlayerToWorld2(peer, ((PlayerInfo*)(peer->data)), block.destWorld, x_, y_);
					return;
				}
				else
				{

					int x_ = 0;
					int y_ = 0;
					bool found = false;
					for (int i = 0; i < worldDest.width * worldDest.height; i++)
					{
						ItemDefinition def = getItemDef(worldDest.items[i].foreground);
						if (def.blockType == BlockTypes::DOOR) {
							WorldItem blockDest = worldDest.items[i];
							if (block.currId == blockDest.destId)
							{
								x_ = (i % world->width);
								y_ = (i / world->width);
								sendPlayerToWorld2(peer, ((PlayerInfo*)(peer->data)), block.destWorld, x_, y_);
								found = true;
								break;
							}
						}
					}
					if (!found)
					{
						int x = 0;
						int y = 0;
						for (int j = 0; j < worldDest.width * worldDest.height; j++)
						{
							if (worldDest.items[j].foreground == 6) {
								x = (j % worldDest.width);
								y = (j / worldDest.width);
							}
						}
						sendPlayerToWorld2(peer, ((PlayerInfo*)(peer->data)), block.destWorld, x, y);
					}
				}
			}
			catch (int e)
			{
				DoCancelTransitionAndTeleport(peer, x, y);
			}
		}
	}
	GamePacket p5 = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 0));
	memcpy(p5.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	ENetPacket* packet5 = enet_packet_create(p5.data,
		p5.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet5);
	enet_host_flush(server);
	GamePacket p4 = packetEnd(appendIntx(appendString(createPacket(), "OnFailedToEnterWorld"), 1));
	ENetPacket* packet4 = enet_packet_create(p4.data,
		p4.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet4);
	enet_host_flush(server);
}
void WhiteDoor(int x, int y, int tile, int causedBy, ENetPeer* peer)
{
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
	WorldInfo* world = getPlyersWorld(peer);
	if (world->items[x + (y * world->width)].foreground == 6)
	{
		if (((PlayerInfo*)(peer->data))->canExit)
		{
			string online = "";
			int total = 0;
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (((PlayerInfo*)(currentPeer->data))->adminLevel >= 0) {
					total++;
				}
			}
			Player::OnConsoleMessage(peer, "Where would you like to go? (`w" + to_string(total) + " `oonline)");
			sendPlayerLeave(peer, (PlayerInfo*)(peer->data));
			sendWorldOffers(peer);
			((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
		}
	}
}
void CheckPlayerState(ENetPeer* peer)
{
	using namespace std::chrono;

	while (1)
	{
		Sleep(60000); // each 1 minute check

		if (peer->data == NULL) break;


		if (((PlayerInfo*)(peer->data))->currentWorld == "EXIT") continue;

		// check if cursed
		if (((PlayerInfo*)(peer->data))->isCursed == true)
		{
			long kiekDar = ((PlayerInfo*)(peer->data))->lastCursed - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			long min = kiekDar / 60000;
			ofstream fs("cursedplayers/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
			fs << min;
			fs.close();
			if (((PlayerInfo*)(peer->data))->lastCursed < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
			{
				if (std::experimental::filesystem::exists("cursedplayers/" + ((PlayerInfo*)(peer->data))->rawName + ".txt"))
				{
					Player::OnTextOverlay(peer, "`^Your `4Curse `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					Player::OnConsoleMessage(peer, "`^Your `4Curse `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");

					((PlayerInfo*)(peer->data))->skinColor = 0x8295C3FF;
					sendClothes(peer);
					((PlayerInfo*)(peer->data))->isCursed = false;
					sendState(peer);

					remove(("cursedplayers/" + ((PlayerInfo*)(peer->data))->rawName + ".txt").c_str());
					sendPlayerToWorld(peer, (PlayerInfo*)(peer->data), "START");
				}
			}
		}

		//check if muted isDuctaped
		if (((PlayerInfo*)(peer->data))->isDuctaped == true)
		{
			long kiekDar = ((PlayerInfo*)(peer->data))->lastMuted - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			long min = kiekDar / 60000;
			ofstream saveMuteTime("timemuted/" + PlayerDB::getProperName(((PlayerInfo*)(peer->data))->rawName) + ".txt");
			saveMuteTime << min;
			saveMuteTime.close();
			if (((PlayerInfo*)(peer->data))->lastMuted < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
			{
				if (std::experimental::filesystem::exists("timemuted/" + ((PlayerInfo*)(peer->data))->rawName + ".txt"))
				{
					Player::OnTextOverlay(peer, "`^Your `4Mute `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					Player::OnConsoleMessage(peer, "`^Your `4Mute `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					((PlayerInfo*)(peer->data))->taped = false;
					((PlayerInfo*)(peer->data))->isDuctaped = false;
					((PlayerInfo*)(peer->data))->cantsay = false;
					sendState(peer);
					sendClothes(peer);
					remove(("timemuted/" + ((PlayerInfo*)(peer->data))->rawName + ".txt").c_str());
				}
			}
		}


	}
}
/*void checkmem()
{
	while (1)
	{
		Sleep(600000);
		MEMORYSTATUSEX memInfo;
		PROCESS_MEMORY_COUNTERS_EX pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
		int realmb = virtualMemUsedByMe / 1024;
		int superrealmb = realmb / 1024;
		if (superrealmb >= 2000)
		{
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4SERVER OVERLOADED, RESTARTING SERVER."));
			string text = "action|play_sfx\nfile|audio/sungate.wav\ndelayMS|0\n";
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
			saveAllWorlds();
			Sleep(3000);
			abort();
		}
	}
}*/

void SendTips()
{
	while (1)
	{
		Sleep(600000); // 10 minutes in mili s.
		string text2 = "action|play_sfx\nfile|audio/beep.wav\ndelayMS|0\n";
		BYTE* data2 = new BYTE[5 + text2.length()];
		BYTE zero2 = 0;
		int type2 = 3;
		memcpy(data2, &type2, 4);
		memcpy(data2 + 4, text2.c_str(), text2.length());
		memcpy(data2 + 4 + text2.length(), &zero2, 1);
		ENetPacket* packet22 = enet_packet_create(data2,
			5 + text2.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet22);

		const unsigned short totalTips = 7;
		string tips[totalTips] = { "`5Account Security you could find at self wrench>AAP Config!"};

		string tip = tips[tipqueue];

		if (tipqueue >= totalTips - 1)
		{
			tipqueue = 0;
		}
		else
		{
			tipqueue++;
		}
		GamePacket p222 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`2[`5GTOS`2] `5" + tip + ""));
		ENetPacket* packet222 = enet_packet_create(p222.data,
			p222.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet222);
		delete data2;
		delete p222.data;

	}
}
void autoSaveWorlds() {

	bool exist = std::experimental::filesystem::exists("save.txt");
	if (!exist)
	{
		ofstream save("save.txt");
		save << 0;
		save.close();
	}
	std::ifstream ok("save.txt");
	std::string limits((std::istreambuf_iterator<char>(ok)),
		(std::istreambuf_iterator<char>()));
	int a = atoi(limits.c_str());
	if (a == 0)
	{
		ofstream ok;
		ok.open("save.txt");
		ok << 50;
		ok.close();
		worldDB.saveAll();
		cout << "`4[`5GTOS`4] `2Saving Data`5!" << endl;
	}
	else
	{
		int aa = a - 1;
		ofstream ss;
		ss.open("save.txt");
		ss << aa;
		ss.close();
		if (aa == 0)
		{
			ofstream ok;
			ok.open("save.txt");
			ok << 50;
			ok.close();
			worldDB.saveAll();
			cout << "`4[`5GTOS`4] `2Saving Data`5!" << endl;
		}
	}
}
void updateInvis(ENetPeer* peer)
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
			autoSaveWorlds();
			GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), ((PlayerInfo*)(peer->data))->isinv));
			memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
			delete p2.data;
			GamePacket p3 = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), ((PlayerInfo*)(currentPeer->data))->isinv));
			memcpy(p3.data + 8, &(((PlayerInfo*)(currentPeer->data))->netID), 4);
			ENetPacket* packet3 = enet_packet_create(p3.data,
				p3.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet3);
			delete p3.data;
			if (((PlayerInfo*)(peer->data))->adminLevel == 0) {

			}
			if (((PlayerInfo*)(peer->data))->level >= 100) {
				GamePacket p2ww = packetEnd(appendString(appendString(createPacket(), "OnCountryState"), ((PlayerInfo*)(peer->data))->country + "|showGuild"));
				memcpy(p2ww.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
				ENetPacket* packet2ww = enet_packet_create(p2ww.data,
					p2ww.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2ww);
				delete p2ww.data;
				GamePacket p2wwee = packetEnd(appendString(appendString(createPacket(), "OnCountryState"), ((PlayerInfo*)(currentPeer->data))->country + "|showGuild"));
				memcpy(p2wwee.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
				ENetPacket* packet2wwee = enet_packet_create(p2wwee.data,
					p2wwee.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2wwee);
				delete p2wwee.data;
			}
			else {
				GamePacket p2ww = packetEnd(appendString(appendString(createPacket(), "OnCountryState"), ((PlayerInfo*)(peer->data))->country + "|showGuild"));
				memcpy(p2ww.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
				ENetPacket* packet2ww = enet_packet_create(p2ww.data,
					p2ww.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2ww);
				delete p2ww.data;
				GamePacket p2wwee = packetEnd(appendString(appendString(createPacket(), "OnCountryState"), ((PlayerInfo*)(currentPeer->data))->country + "|showGuild"));
				memcpy(p2wwee.data + 8, &(((PlayerInfo*)(currentPeer->data))->netID), 4);
				ENetPacket* packet2wwee = enet_packet_create(p2wwee.data,
					p2wwee.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2wwee);
				delete p2wwee.data;
			}
			int flag1 = (65536 * ((PlayerInfo*)(peer->data))->guildBg) + ((PlayerInfo*)(peer->data))->guildFg;
			if (((PlayerInfo*)(currentPeer->data))->rawName == ((PlayerInfo*)(currentPeer->data))->guildLeader) {
				GamePacket p2gg = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 41179607), 41179607), flag1), 0));
				memcpy(p2gg.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
				ENetPacket* packet2gg = enet_packet_create(p2gg.data,
					p2gg.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2gg);
				delete p2gg.data;
				int flag2 = (65536 * ((PlayerInfo*)(currentPeer->data))->guildBg) + ((PlayerInfo*)(currentPeer->data))->guildFg;
				GamePacket p2xd = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 41179607), 41179607), flag2), 0));
				memcpy(p2xd.data + 8, &(((PlayerInfo*)(currentPeer->data))->netID), 4);
				ENetPacket* packet2xd = enet_packet_create(p2xd.data,
					p2xd.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2xd);
				delete p2xd.data;
			}
			else {
				GamePacket p2gg = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 41179607), 41179607), flag1), 0));
				memcpy(p2gg.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
				ENetPacket* packet2gg = enet_packet_create(p2gg.data,
					p2gg.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2gg);
				delete p2gg.data;
				int flag2 = (65536 * ((PlayerInfo*)(currentPeer->data))->guildBg) + ((PlayerInfo*)(currentPeer->data))->guildFg;
				GamePacket p2xd = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 41179607), 41179607), flag2), 0));
				memcpy(p2xd.data + 8, &(((PlayerInfo*)(currentPeer->data))->netID), 4);
				ENetPacket* packet2xd = enet_packet_create(p2xd.data,
					p2xd.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2xd);
				delete p2xd.data;
			}
		}
	}
}
void gemevents() {
	while (1) {
		Sleep(24000000);
		int	valgem = rand() % 1 + 5;
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
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5[EVENT]: `1Gems event started! `^(" + std::to_string(valgem) + ")``"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete data;
		delete p.data;
		Sleep(5500);
	eventgem = valgem;
	}
}
void Respawn(ENetPeer* peer) {
	int x = 3040;
	int y = 736;
	WorldInfo* world = getPlyersWorld(peer);
	if (world)
	{
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
				GamePacket psp = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), 3), x, (y + 8)));
				ENetPacket* packetd = enet_packet_create(psp.data,
					psp.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packetd);
				delete psp.data;
				string text = "action|play_sfx\nfile|audio/male_scream.wav\ndelayMS|0\n";
				BYTE* data = new BYTE[5 + text.length()];
				BYTE zero = 0;
				int type = 3;
				memcpy(data, &type, 4);
				memcpy(data + 4, text.c_str(), text.length());
				memcpy(data + 4 + text.length(), &zero, 1);
				{
					ENetPacket* packetres = enet_packet_create(data,
						5 + text.length(),
						ENET_PACKET_FLAG_RELIABLE);
					if (isHere(peer, currentPeer)) {
						enet_peer_send(currentPeer, 0, packetres);
					}
				}
			}
		}
		for (int i = 0; i < world->width * world->height; i++)
		{
			if (world->items[i].foreground == 6) {
				x = (i % world->width) * 32;
				y = (i / world->width) * 32;
				//world->items[i].foreground = 8;
			}
		}
		{
			PlayerMoving data;
			data.packetType = 0x0;
			data.characterState = 0x924; // animation
			data.x = x;
			data.y = y;
			data.punchX = -1;
			data.punchY = -1;
			data.XSpeed = 0;
			data.YSpeed = 0;
			data.netID = ((PlayerInfo*)(peer->data))->netID;
			data.plantingTree = 0x0; // 0x0
			SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
		}
		{
			int x = 3040;
			int y = 736;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 6) {
					x = (i % world->width) * 32;
					y = (i / world->width) * 32;
					//world->items[i].foreground = 8;
				}
			}
			GamePacket p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
			memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			//enet_host_flush(server);
		}
		{
			int x = 3040;
			int y = 736;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 6) {
					x = (i % world->width) * 32;
					y = (i / world->width) * 32;
					//world->items[i].foreground = 8;
				}
			}
			GamePacket p2 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
			memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			enet_host_flush(server);
		}
	}
	if (((PlayerInfo*)(peer->data))->usedCP == false)
	{
		GamePacket p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
		memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
	}
	else
	{
		GamePacket p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), ((PlayerInfo*)(peer->data))->cpX, ((PlayerInfo*)(peer->data))->cpY));
		memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
	}
}
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	saveAllWorlds();
	return FALSE;
}
void FindGeiger(ENetPeer* peer)
{
	const auto world = getPlyersWorld(peer);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (world->geigerX == 0 && world->geigerY == 0)
		{
			srand(GetTickCount());
			const auto geigercounterx = rand() % 3000;
			const auto geigercountery = rand() % 1500;
			world->geigerX = geigercounterx;
			world->geigerY = geigercountery;
		}
		if (static_cast<PlayerInfo*>(peer->data)->x >= world->geigerX - 30 && static_cast<PlayerInfo*>(peer->data)->x <= world->geigerX + 30 && static_cast<PlayerInfo*>(peer->data)->y >= world->geigerY - 30 && static_cast<PlayerInfo*>(peer->data)->y <= world->geigerY + 30)
		{
			std::vector<int> list{ 1498, 1500, 2804, 2806, 8270, 8272, 8274, 2242, 2244, 2246, 2248, 9512, 2250 };
			const int index = rand() % list.size();
			const auto value = list[index];
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You found " + getItemDef(value).name + "!", 0, true);
			auto success = true;
			SaveItemMoreTimes(value, 1, peer, success);
			srand(GetTickCount());
			const auto geigercounterx = rand() % 3000;
			const auto geigercountery = rand() % 1500;
			world->geigerX = geigercounterx;
			world->geigerY = geigercountery;
		}
		else
		{
			const auto checkx = world->geigerX - static_cast<PlayerInfo*>(peer->data)->x;
			const auto checky = static_cast<PlayerInfo*>(peer->data)->y - world->geigerY;
			if (checkx > 200 || checkx < -200)
			{
			}
			else if (checky > 200 || checky < -200)
			{
			}
			else
			{
			}
		}
	}
}

void updateplayerset(ENetPeer* peer, int targetitem)
{
	int clothitem = ((PlayerInfo*)(peer->data))->cloth_hand;
	int clothface = ((PlayerInfo*)(peer->data))->cloth_face;
	int clothneck = ((PlayerInfo*)(peer->data))->cloth_necklace;
	int clothshirt = ((PlayerInfo*)(peer->data))->cloth_shirt;
	int clothback = ((PlayerInfo*)(peer->data))->cloth_back;
	int clothances = ((PlayerInfo*)(peer->data))->cloth_ances;
	int clothpants = ((PlayerInfo*)(peer->data))->cloth_pants;
	int clothfeet = ((PlayerInfo*)(peer->data))->cloth_feet;
	int clothhair = ((PlayerInfo*)(peer->data))->cloth_hair;
	int clothmask = ((PlayerInfo*)(peer->data))->cloth_mask;
	int item = targetitem;

	if (clothmask == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_mask = 0;
			sendClothes(peer);
		}
		else {

		}
	}

	if (clothitem == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_hand = 0;
			sendClothes(peer);
			((PlayerInfo*)(peer->data))->effect = 8421376;
			sendPuncheffectpeer(peer, ((PlayerInfo*)(peer->data))->effect);
		}
		else {

		}
	}

	if (clothface == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_face = 0;
			sendClothes(peer);
		}
		else {

		}
	}

	if (clothneck == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_necklace = 0;
			sendClothes(peer);
		}
		else {

		}
	}

	if (clothshirt == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_shirt = 0;
			sendClothes(peer);
		}
		else {

		}
	}

	if (clothback == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_back = 0;
			sendClothes(peer);
		}
		else {

		}
	}

	if (clothances == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_ances = 0;
			sendClothes(peer);
		}
		else {

		}
	}

	if (clothpants == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_pants = 0;
			sendClothes(peer);
		}
		else {

		}
	}

	if (clothfeet == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_feet = 0;
			sendClothes(peer);
		}
		else {

		}
	}

	if (clothhair == item)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			((PlayerInfo*)(peer->data))->cloth_hair = 0;
			sendClothes(peer);
		}
		else {

		}
	}
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

void updateworldremove(ENetPeer* peer) {
	/*if (((PlayerInfo*)(peer->data))->isNicked == true)
	{
		((PlayerInfo*)(peer->data))->isNicked = false;
		((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->displayNamebackup;
		GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->displayNamebackup));
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
				if (((PlayerInfo*)(peer->data))->adminLevel >= 0) {
					enet_peer_send(currentPeer, 0, packet7);
				}
			}
		}
		delete p7.data;
	}*/
	if (((PlayerInfo*)(peer->data))->isNicked == false)
	{
		if (((PlayerInfo*)(peer->data))->adminLevel == 0) {
			{
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
				if (((PlayerInfo*)(peer->data))->adminLevel == 0) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 0) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 111) {
			{
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 111) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 111) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 222) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 222) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 222) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 333) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 333) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 333) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 555) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 555) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 555) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 666) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 666) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 666) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`#@" + ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 888) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`q@" + ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 888) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 888) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 998) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`9@" + ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 998) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 998) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 999) {
			{
				//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`4@" + ((PlayerInfo*)(peer->data))->tankIDName));
				memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				if (((PlayerInfo*)(peer->data))->adminLevel == 999) {
					((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
				}
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
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 999) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
				delete p7.data;
			}
		}
		else if (((PlayerInfo*)(peer->data))->adminLevel == 1337) {
			{
				if (((PlayerInfo*)(peer->data))->isCreator == true) {
					//string name2 = "``" + str.substr(6, cch.length() - 6 - 1);
					GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`6@" + ((PlayerInfo*)(peer->data))->tankIDName));
					memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
					((PlayerInfo*)(peer->data))->country = "../";
					if (((PlayerInfo*)(peer->data))->adminLevel == 1000 || ((PlayerInfo*)(peer->data))->adminLevel == 1337) {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
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
						if (isHere(peer, currentPeer)) {
							if (((PlayerInfo*)(peer->data))->adminLevel == 1000 || ((PlayerInfo*)(peer->data))->adminLevel == 1337) {
								enet_peer_send(currentPeer, 0, packet7);
							}
						}
					}
					delete p7.data;
				}
				else {
					GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`6@" + ((PlayerInfo*)(peer->data))->tankIDName));
					memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
					if (((PlayerInfo*)(peer->data))->adminLevel == 1000 || ((PlayerInfo*)(peer->data))->adminLevel == 1337) {
						((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName;
					}
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
						if (isHere(peer, currentPeer)) {
							if (((PlayerInfo*)(peer->data))->adminLevel == 1000 || ((PlayerInfo*)(peer->data))->adminLevel == 1337) {
								enet_peer_send(currentPeer, 0, packet7);
							}
						}
					}
					delete p7.data;
				}
			}
		}
	}
}
