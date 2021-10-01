#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "enet/enet.h"
#include "Server_player.h"
#include "Server_world.h"
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
#include <stdexcept>

void sendTileUpdate(int x, int y, int tile, int causedBy, ENetPeer* peer)
{
	if (serverIsFrozen == true) return;
	if (tile > itemDefs.size()) {
		return;
	}
	if (!((PlayerInfo*)(peer->data))->haveGrowId)
	{
		Player::OnConsoleMessage(peer, "`4Create your account first");
		return;
	}
	if (((PlayerInfo*)(peer->data))->isIn == false)
	{
		Player::OnConsoleMessage(peer, "`4Dumb haxor lol");
		return;
	}
	if (((PlayerInfo*)(peer->data))->dotrade == true || ((PlayerInfo*)(peer->data))->istrading == true)
	{
		Player::OnTextOverlay(peer, "You cant do that while trading!");
		return;
	}
	//if (tile == tile && ((PlayerInfo*)(peer->data))->x / 32 && ((PlayerInfo*)(peer->data))->y / 32) return;// this system is made by Kipas & some fixed by beath
	//bool isLock = false;
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
	if (world == NULL) return;
	bool isMonitor = false; // so noob
	int brokentile = world->items[x + (y * world->width)].foreground;
	if (((PlayerInfo*)(peer->data))->currentWorld == "EXIT") return;
	if (x<0 || y<0 || x>world->width - 1 || y>world->height - 1 || tile > itemDefs.size()) return; // needs - 1
	sendNothingHappened(peer, x, y);
	if (((PlayerInfo*)(peer->data))->cloth_hand == 9482)
	{
		if (((PlayerInfo*)(peer->data))->rawName == world->owner && ((PlayerInfo*)(peer->data))->haveGrowId == true) {
			int xlast = ((PlayerInfo*)(peer->data))->lastPunchX = x;
			int ylast = ((PlayerInfo*)(peer->data))->lastPunchX = y;
			changetile(peer, xlast, ylast);
			int hi = ((PlayerInfo*)(peer->data))->lastPunchX;
			int hi2 = ((PlayerInfo*)(peer->data))->lastPunchY;
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer)) {
					Player::OnParticleEffect(currentPeer, 170, hi, hi2, 0);
				}
			}
		}
	}
	if (world->items[x + (y * world->width)].foreground == 2946 && tile != 18 && tile != 32 && tile > 0) {
		if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
			using namespace std::chrono;
			if (((PlayerInfo*)(peer->data))->lastDISPLAY + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
			{
				((PlayerInfo*)(peer->data))->lastDISPLAY = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				bool iscontains = false;
				SearchInventoryItem(peer, tile, 1, iscontains);
				if (!iscontains)
				{
					Player::OnTextOverlay(peer, "Failed to display item!");
					return;
				}
				else {
					if (((PlayerInfo*)(peer->data))->dotrade == true || ((PlayerInfo*)(peer->data))->istrading == true)
					{
						Player::OnTextOverlay(peer, "You cant do that while trading!");
						return;
					}
					((PlayerInfo*)(peer->data))->blockx = x;
					((PlayerInfo*)(peer->data))->blocky = y;
					int hi = data.punchX;
					int hi2 = data.punchY;
					short dfg = world->items[x + (y * world->width)].foreground;
					short dbg = world->items[x + (y * world->width)].background;
					world->items[x + (y * world->width)].displayblock = tile;
					int n = tile;
					if (n == 6336 || n == 8552 || n == 1738 || n == 9482 || n == 9356 || n == 9492 || n == 1672 || n == 8774 || n == 1790 || n == 2592 || n == 1784 || n == 1792 || n == 1794 || n == 7734 || n == 8306 || n == 3162 || n == 2398)
					{
						Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "You can't display untradeable items.", 0, true);
						return;
					}
					if (getItemDef(n).blockType == BlockTypes::LOCK || n == 2946)
					{
						Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "Sorry, no displaying Display Blocks or Locks.", 0, true);
						return;
					}
					int squaresign = ((PlayerInfo*)(peer->data))->blockx + (((PlayerInfo*)(peer->data))->blocky * 100);
					string world = ((PlayerInfo*)(peer->data))->currentWorld;
					string receivedid;
					string currentworld = world + "X" + std::to_string(squaresign);
					ifstream getdisplay("display/" + currentworld + ".txt");
					getdisplay >> receivedid;
					getdisplay.close();

					bool displayexist = std::experimental::filesystem::exists("display/" + currentworld + ".txt");
					if (displayexist) {
						if (receivedid != "")
						{
							Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "Remove what's in there first!", 0, true);
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
									SendDisplayBlock(currentPeer, dfg, dbg, hi, hi2, n);
								}
							}
							ofstream displayupdate("display/" + world + "X" + std::to_string(squaresign) + ".txt");
							displayupdate << n;
							displayupdate.close();
							RemoveInventoryItem(n, 1, peer);
							updateplayerset(peer, n);
						}
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
								SendDisplayBlock(currentPeer, dfg, dbg, hi, hi2, n);
							}
						}
						ofstream displayinsert("display/" + world + "X" + std::to_string(squaresign) + ".txt");
						displayinsert << n;
						displayinsert.close();
						RemoveInventoryItem(n, 1, peer);
						updateplayerset(peer, n);
					}
					return;
				}
			}
			else {
				Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "Slow down while using display blocks!", 0, true);
				return;
			}
		}
		else {
			if (world->owner == "")
			{
				Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "This area must be locked to put your item on display!", 0, true);
			}
			else if (getPlyersWorld(peer)->isPublic)
			{
				Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "That area is owned by " + world->owner + "", 0, true);
			}
			else {
				Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "That area is owned by " + world->owner + "", 0, true);
			}
			return;
		}
	}
	if (world->items[x + (y * world->width)].foreground == 2946 && tile == 32)
	{
		if (((PlayerInfo*)(peer->data))->rawName == world->owner || world->owner == "" || getPlyersWorld(peer)->isPublic) {
			int itemid = world->items[x + (y * world->width)].foreground;
			int itembg = world->items[x + (y * world->width)].background;
			string world = ((PlayerInfo*)(peer->data))->currentWorld;
			((PlayerInfo*)(peer->data))->blockx = x;
			((PlayerInfo*)(peer->data))->blocky = y;
			int squaresign = ((PlayerInfo*)(peer->data))->blockx + (((PlayerInfo*)(peer->data))->blocky * 100);
			((PlayerInfo*)(peer->data))->displayfg = itemid;
			((PlayerInfo*)(peer->data))->displaybg = itembg;
			((PlayerInfo*)(peer->data))->displaypunchx = data.punchX;
			((PlayerInfo*)(peer->data))->displaypunchy = data.punchY;
			string receivedid;
			string currentworld = world + "X" + std::to_string(squaresign);
			ifstream getdisplay("display/" + currentworld + ".txt");
			getdisplay >> receivedid;
			getdisplay.close();
			bool displayexist = std::experimental::filesystem::exists("display/" + currentworld + ".txt");
			if (getPlyersWorld(peer)->isPublic && displayexist && ((PlayerInfo*)(peer->data))->rawName != getPlyersWorld(peer)->owner)
			{
				Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(stoi(receivedid)).name + " is on display here.|\nadd_button|chc000|Okay|0|0|\nadd_quick_exit|\n");
			}
			else if (displayexist && ((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner)
			{
				Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(stoi(receivedid)).name + " is on display here.|\nadd_button|pickupdisplayitem|Pick it up|0|0|\nadd_quick_exit|\n");
			}
			else if (getPlyersWorld(peer)->owner == "" && displayexist)
			{
				Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(stoi(receivedid)).name + " is on display here.|\nadd_button|pickupdisplayitem|Pick it up|0|0|\nadd_quick_exit|\n");
			}
			else {
				Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oThe Display Block is empty. Use an item on it to display the item!|\nend_dialog||Close||\n");
			}
			return;
		}
		else {
			Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "That area is owned by " + world->owner + "", 0, true);
			return;
		}
	}

	if (tile == 1240) {
		if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 1000 || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
			isMonitor = true;
		}
	}
	if (world->items[x + (y * world->width)].foreground == 2978 && tile == 32) {

		((PlayerInfo*)(peer->data))->wrenchedBlockLocation = x + (y * world->width);
		if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 1000 || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
			if (world->items[x + (y * world->width)].intdata != 0) {
				if (tile == 18) {
					GamePacket p2 = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`wEmpty the item first!"), 0), 1));
					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet2);
					delete p2.data;
					return;
				}
				else {
					string pricee = std::to_string(world->items[x + (y * world->width)].price);
					string sid = std::to_string(world->items[x + (y * world->width)].intdata);
					string sname = GetItemDef(world->items[x + (y * world->width)].intdata).name;
					string initial = "set_default_color|`o\n\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|small|`oThe machine contains 1 `2" + sname + "|left|" + sid + "|\nadd_spacer|small|\nadd_label|small|For a cost of:|\nadd_label_with_icon|small|" + pricee + " x `8World Locks|right|242|\nadd_spacer|small|\nadd_label|small|You will get:|\nadd_label_with_icon|small|1 x `2" + sname + "|right|" + sid + "|\nadd_spacer|small|\nadd_button|emptyvending123|Empty the machine|\nadd_smalltext|`5(Vending Machine will not function when price is set to 0)|\nadd_text_input|addprice|Price |" + pricee + "|6|\nadd_quick_exit|\nend_dialog|vendds|Close|Update";
					Player::OnDialogRequest(peer, initial);
				}
			}
			else if (world->items[x + (y * world->width)].sold == true) {
				if (tile == 18) {
					GamePacket p2 = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`wEmpty the World Locks First!"), 0), 1));
					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet2);
					delete p2.data;
					return;
				}
				else {
					string pricee = std::to_string(world->items[x + (y * world->width)].price);
					string sid = std::to_string(world->items[x + (y * world->width)].intdata);
					string sname = GetItemDef(world->items[x + (y * world->width)].intdata).name;
					string dialog = "set_default_color|`o\n\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label|small|`oThis machine is empty.|\nadd_label|small|This machine contains " + pricee + " World Locks.|\nadd_button|collectwls|Collect World Locks||nadd_quick_exit|\nend_dialog|emptyvends|Close|";
					Player::OnDialogRequest(peer, dialog);
				}
			}
			else {
				string dialog = "set_default_color|`o\n\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label|small|`oThis machine is empty.|\nadd_item_picker|venditem|`wPut an item in|Choose an item you want to put in the machine!|nadd_quick_exit|\nend_dialog|emptyvends|Close|";
				Player::OnDialogRequest(peer, dialog);

			}
		}
		else {
			int pricez = world->items[x + (y * world->width)].price;
			if (world->items[x + (y * world->width)].intdata != 0) {
				string sid = std::to_string(world->items[x + (y * world->width)].intdata);
				string pricee = std::to_string(world->items[x + (y * world->width)].price);

				string sname = GetItemDef(world->items[x + (y * world->width)].intdata).name;
				string buy = "set_default_color|`o\n\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|small|`oThe machine contains 1 `2" + sname + "|left|" + sid + "|\nadd_spacer|small|\nadd_label|small|For a cost of:|\nadd_label_with_icon|small|" + pricee + " x `8World Locks|right|242|\nadd_spacer|small|\nadd_label|small|You will get:|\nadd_label_with_icon|small|1 x `2" + sname + "|right|" + sid + "|\nadd_spacer|small|\nadd_text_input|buymanyhow|How many would you like to buy?||3||\nadd_quick_exit|\nend_dialog|buyvend|Close|Buy|";
				Player::OnDialogRequest(peer, buy);

			}
			else if (world->items[x + (y * world->width)].intdata != 0 || world->items[x + (y * world->width)].peritem) {
				string sid = std::to_string(world->items[x + (y * world->width)].intdata);
				string pricee = std::to_string(world->items[x + (y * world->width)].price);

				string sname = GetItemDef(world->items[x + (y * world->width)].intdata).name;
				string buy = "set_default_color|`o\n\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|small|`oThe machine contains 1 `2" + sname + "|left|" + sid + "|\nadd_spacer|small|\nadd_label|small|For a cost of:|\nadd_label_with_icon|small|1 x `8World Locks|right|242|\nadd_spacer|small|\nadd_label|small|You will get:|\nadd_label_with_icon|small|" + pricee + " x `2" + sname + "|right|" + sid + "|\nadd_spacer|small|\nadd_text_input|buymanyhow|How many would you like to buy?||3||\nadd_quick_exit|\nend_dialog|buyvend|Close|Buy|";
				Player::OnDialogRequest(peer, buy);
			}
			else if (pricez == 0 || world->items[x + (y * world->width)].sold) {
				string empty = "set_default_color|`o\n\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label|small|`oThis machine is out of order.|nadd_quick_exit|\nend_dialog|orderout|Close|";
				Player::OnDialogRequest(peer, empty);
			}

			else {
				string empty = "set_default_color|`o\n\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label|small|`oThis machine is empty.|nadd_quick_exit|\nend_dialog|venddsempty|Close|";
				Player::OnDialogRequest(peer, empty);
			}
		}

	}

	if (world->items[x + (y * world->width)].foreground == 2946 && tile == 18)
	{
		if (getPlyersWorld(peer)->isPublic || find(world->worldaccess.begin(), world->worldaccess.end(), ((PlayerInfo*)(peer->data))->rawName) != world->worldaccess.end())
		{
			Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "That area is owned by " + world->owner + "", 0, true);
			return;
		}
	}
	if (world != NULL) {
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DOOR)
		{
			if (world->owner != "") {
				if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
					if (tile == 32) {
						((PlayerInfo*)(peer->data))->wrenchsession = x + (y * world->width);
						WorldItem item = world->items[x + (y * world->width)];
						string a = item.destWorld + ":" + item.destId;
						if (a == ":") a = "";
						if (item.foreground == 762 || item.foreground == 4190)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit Password Door``|left|" + to_string(item.foreground) + "|\n\nadd_text_input|dest|`oTarget World|" + a + "|100|\nadd_text_input|label|Display Label (optional)|" + item.label + "|100|\nadd_text_input|doorpw|Password|" + item.password + "|35|\nend_dialog|editpdoor|Cancel|OK|");
						}
						else {
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit Door``|left|" + to_string(item.foreground) + "|\|\n\nadd_text_input|dest|`oTarget World|" + a + "|100|\nadd_text_input|label|Display Label (optional)|" + item.label + "|100|\nadd_text_input|doorid|ID (optional)|" + item.currId + "|35|\nend_dialog|editdoor|Cancel|OK|");
						}
					}
				}
			}
		}
		if (tile == 5640)
		{
			if (world->items[x + (y * world->width)].foreground == 0)
			{
				WorldInfo* world = getPlyersWorld(peer);
				int value = world->magitem;
				int jumlah = world->gaiajumlah;
				int pasang = tile == 5640;
				int xSize = world->width;
				int ySize = world->height;
				for (int i = 0; i < world->width * world->height; i++)
				{
					if (world->items[i].foreground != 0) {
						if (pasang >= world->items[i].gaiajumlah) {
							world->items[x + (y * world->width)].foreground = value;
							world->items[i].gaiajumlah = world->items[i].gaiajumlah - pasang;
						}
						else {
							if (pasang < world->items[i].gaiajumlah) {
								Player::OnConsoleMessage(peer, "`9You can`t put with 0 block!");
								continue;
							}
						}
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
						PlayerMoving data;
						data.packetType = 0x0;
						data.x = x;
						data.y = y;
						data.punchX = -1;
						data.punchY = -1;
						data.XSpeed = 0;
						data.YSpeed = 0;
						data.netID = ((PlayerInfo*)(currentPeer->data))->netID;
						data.plantingTree = 0x0;
						data.plantingTree = value;
						SendPacketRaw(4, packPlayerMoving(&data), 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
						Player::OnConsoleMessage(peer, "`9Please re-enter world");
						Player::PlayAudio(peer, "audio/trash.wav", 0);
					}
					continue;
				}
			}
		}
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SIGN)
		{
			if (tile == 32) {
				((PlayerInfo*)(peer->data))->wrenchx = x;
				((PlayerInfo*)(peer->data))->wrenchy = y;
				if (((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || find(world->worldaccess.begin(), world->worldaccess.end(), ((PlayerInfo*)(peer->data))->rawName) != world->worldaccess.end()) {
					string world = ((PlayerInfo*)(peer->data))->currentWorld;
					int squaresign = ((PlayerInfo*)(peer->data))->wrenchx + (((PlayerInfo*)(peer->data))->wrenchy * 100);
					bool exist = std::experimental::filesystem::exists("signs/" + world + "X" + to_string(squaresign) + ".txt");
					if (exist)
					{
						ifstream ifs("signs/" + world + "X" + to_string(squaresign) + ".txt");
						string content = "error";
						getline(ifs, content);
						ifs.close();
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit Sign``|left|20|\nadd_label|small|`oWhat would you like to write on this sign?|left|4|\nadd_text_input|ch3||" + content + "|100|\nembed_data|tilex|" + std::to_string(((PlayerInfo*)(peer->data))->wrenchx) + "\nembed_data|tiley|" + std::to_string(((PlayerInfo*)(peer->data))->wrenchy) + "\nend_dialog|sign_edit|Cancel|OK|");
						return;
					}
					else
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit Sign``|left|20|\nadd_label|small|`oWhat would you like to write on this sign?|left|4|\nadd_text_input|ch3|||100|\nembed_data|tilex|" + std::to_string(((PlayerInfo*)(peer->data))->wrenchx) + "\nembed_data|tiley|" + std::to_string(((PlayerInfo*)(peer->data))->wrenchy) + "\nend_dialog|sign_edit|Cancel|OK|");
						return;
					}
				}
			}
		}
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEST || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SWITCH_BLOCK || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND) {
			if (world->items[x + (y * world->width)].activated == true) {
				sendNothingHappened(peer, x, y);
				if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || isMod(peer))
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + GetItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_checkbox|checkbox_jammer|`oDissabled?|1|\nadd_checkbox|jammer_public|`oUsable for Public?|0|\nadd_checkbox|jammer_muted|`oSilence?|0|\nend_dialog|jammer_edit|Cancel|OK|");
					static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
					return;
				}
				else
				{
					SendTalkSelf(peer, "That area is owned by " + world->owner);
					return;
				}
				return;
			}
			else {
				sendNothingHappened(peer, x, y);
				if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || isMod(peer))
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + GetItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_checkbox|checkbox_jammer|`oEnabled?|0|\nadd_checkbox|jammer_public|`oUsable for Public?|0|\nadd_checkbox|jammer_muted|`oSilence?|0|\nend_dialog|jammer_edit|Cancel|OK|");
					static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
					return;
				}
				else
				{
					SendTalkSelf(peer, "That area is owned by " + world->owner);
					return;
				}
				return;
			}

		}
		string name = getItemDef(world->items[x + (y * world->width)].foreground).name;
		int id = getItemDef(world->items[x + (y * world->width)].foreground).id;
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::GATEWAY || world->items[x + (y * world->width)].foreground == 224 || world->items[x + (y * world->width)].foreground == 5036 || world->items[x + (y * world->width)].foreground == 3126 || world->items[x + (y * world->width)].foreground == 1162 || world->items[x + (y * world->width)].foreground == 3799 || world->items[x + (y * world->width)].foreground == 3798 || world->items[x + (y * world->width)].foreground == 7066 || world->items[x + (y * world->width)].foreground == 5820 || world->items[x + (y * world->width)].foreground == 5818 || world->items[x + (y * world->width)].foreground == 686) {

			if (tile == 32) {
				if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
					((PlayerInfo*)(peer->data))->wrenchx = x;
					((PlayerInfo*)(peer->data))->wrenchy = y;

					if (world->items[x + (y * world->width)].isOpened == false) {
						Player::OnDialogRequest(peer, "add_label_with_icon|big|" + name + "|left|" + to_string(id) + "|\nadd_spacer|small|\nadd_checkbox|opentopublic|`ois Open to Public?|0|\nend_dialog|entrance|Cancel|OK|\n");
					}
					else {
						Player::OnDialogRequest(peer, "add_label_with_icon|big|" + name + "|left|" + to_string(id) + "|\nadd_spacer|small|\nadd_checkbox|opentopublic|`ois Open to Public?|1|\nend_dialog|entrance|Cancel|OK|\n");
					}
				}
			}
		}
	}
	if (tile == 6336)
	{
		SendGrowpedia(peer);
		return;
	}
	if (tile == 764) {
		if (((PlayerInfo*)(peer->data))->isZombie == true) return;

		if (((PlayerInfo*)(peer->data))->canWalkInBlocks == true)
		{
			((PlayerInfo*)(peer->data))->canWalkInBlocks = false;
			((PlayerInfo*)(peer->data))->skinColor = 0x8295C3FF;
			sendState(peer);
		}

		sendSound(peer, "skel.wav");
		Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`@You have been `4Infected`@, Now you can `4Infect `@Others by Punching Them.", 0, true);
		((PlayerInfo*)(peer->data))->isZombie = true;
		sendState(peer);
		RemoveInventoryItem(764, 1, peer);
		playerconfig(peer, 1150, 130, 0x14);
		return;
	}
	if (tile == 782)
	{
		if (((PlayerInfo*)(peer->data))->isZombie == false) return;

		((PlayerInfo*)(peer->data))->isZombie = false;
		sendState(peer);
		RemoveInventoryItem(782, 1, peer);
		playerconfig(peer, 1150, 300, 0x14);
		return;
	}
	if (tile == 2410)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, 2410, 200, iscontains);
		if (!iscontains)
		{
			Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`oYou will need more `^Emerald Shards `oFor that!", 0, true);
		}
		else {
			Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`oThe power of `^Emerald Shards `oCompressed into `2Emerald Lock`o!", 0, true);
			RemoveInventoryItem(2410, 200, peer);
			bool success = true;
			SaveItemMoreTimes(2408, 1, peer, success);
			Player::OnConsoleMessage(peer, "`o>> You received emerald lock!");
		}
	}
	if (tile == 2480) {
		GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`w\n\nadd_label_with_icon|big|`wMegaphone|left|2480|\nadd_spacer|small|\nadd_label_with_icon|small|`oThis will broadcast to all players in the server!|left|486|\nadd_spacer|small|\nadd_text_input|sbtext|||50|\nend_dialog|sendsb|Cancel|Broadcast!|\n"));
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);

		enet_peer_send(peer, 0, packet2);
		delete p2.data;
		return;
	}
	if (tile == 4426)
	{
		bool iscontains = false;
		SearchInventoryItem(peer, 4426, 200, iscontains);
		if (!iscontains)
		{
			Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`oYou will need more `4Ruby Shards `oFor that!", 0, true);
		}
		else {
			Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`oThe power of `4Ruby Shards `oCompressed into `4Ruby Lock`o!", 0, true);
			RemoveInventoryItem(4426, 200, peer);
			bool success = true;
			SaveItemMoreTimes(4428, 1, peer, success);
			Player::OnConsoleMessage(peer, "`o>> You received ruby lock!");
		}
	}
	int xx = data.punchX;
	int yy = data.punchY;
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (tile == 274 && ((PlayerInfo*)(currentPeer->data))->x / 32 == xx && ((PlayerInfo*)(currentPeer->data))->y / 32 == yy)
		{
			bool iscontainseas = false;
			SearchInventoryItem(peer, 274, 1, iscontainseas);
			if (!iscontainseas)
			{
				autoBan(peer, false, 24 * 7, "failed to find 274 item in sendtileupdate");
				break;
			}
			else {
				RemoveInventoryItem(274, 1, peer);
				((PlayerInfo*)(currentPeer->data))->isFrozen = true;
				((PlayerInfo*)(currentPeer->data))->skinColor = -37500;
				sendClothes(currentPeer);
				sendFrozenState(currentPeer);
				GamePacket pf = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`wSHUSH... pretty cold here. `!(Frozen)`w mod added."));
				ENetPacket* packetf = enet_packet_create(pf.data,
					pf.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packetf);
				delete pf.data;
			}
		}
		if (tile == 276 && ((PlayerInfo*)(currentPeer->data))->x / 32 == xx && ((PlayerInfo*)(currentPeer->data))->y / 32 == yy)
		{
			bool iscontainseas = false;
			SearchInventoryItem(peer, 276, 1, iscontainseas);
			if (!iscontainseas)
			{
				autoBan(peer, false, 24 * 7, "failed to find 276 item in sendtileupdate");
				break;
			}
			else {
				RemoveInventoryItem(276, 1, peer);
				playerRespawn(currentPeer, true);
				int hi = ((PlayerInfo*)(currentPeer->data))->x;
				int hi2 = ((PlayerInfo*)(currentPeer->data))->y;
				Player::OnParticleEffect(currentPeer, 152, hi, hi2, 0);
				Player::OnParticleEffect(currentPeer, 4, hi, hi2, 0);
			}
		}
		if (tile == 732 && ((PlayerInfo*)(currentPeer->data))->x / 32 == xx && ((PlayerInfo*)(currentPeer->data))->y / 32 == yy)
		{
			bool iscontainseas = false;
			SearchInventoryItem(peer, 732, 1, iscontainseas);
			if (!iscontainseas)
			{
				autoBan(peer, false, 24 * 7, "failed to find 732 item in sendtileupdate");
				break;
			}
			else {
				RemoveInventoryItem(732, 1, peer);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`#** `$The Ancient Ones `ohave `4banned `w" + ((PlayerInfo*)(currentPeer->data))->rawName + " `#** `o(`4/rules `oto see the rules!)"));
				ENetPeer* currentPeer2;
				time_t now = time(0);
				char* dt = ctime(&now);
				for (currentPeer2 = server->peers;
					currentPeer2 < &server->peers[server->peerCount];
					++currentPeer2)
				{
					if (currentPeer2->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (((PlayerInfo*)(currentPeer2->data))->haveGrowId == false) continue;
					if (((PlayerInfo*)(currentPeer->data))->rawName == ((PlayerInfo*)(currentPeer2->data))->rawName)
					{
						GamePacket ps2 = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"), "interface/atomic_button.rttex"), "`0Warning from `4System`0: You've been `4BANNED `0from GrowtopiaLR for 730 days"), "audio/hub_open.wav"), 0));
						ENetPacket* packet2 = enet_packet_create(ps2.data,
							ps2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer2, 0, packet2);
						GamePacket ps3 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`oWarning from `4System`o: You've been `4BANNED `ofrom GrowtopiaLR for 730 days"));
						ENetPacket* packet3 = enet_packet_create(ps3.data,
							ps3.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer2, 0, packet3);
						GamePacket pto = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "Applied punishment on " + ((PlayerInfo*)(currentPeer2->data))->rawName + "."));
						ENetPacket* packetto = enet_packet_create(pto.data,
							pto.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packetto);
						if (((PlayerInfo*)(currentPeer2->data))->haveGrowId) {
							PlayerInfo* p = ((PlayerInfo*)(currentPeer2->data));
							p->ban = 1;
							string username = PlayerDB::getProperName(p->rawName);
							std::ifstream ifff("players/" + ((PlayerInfo*)(currentPeer2->data))->rawName + ".json");
							if (ifff.fail()) {
								ifff.close();
							}
							if (ifff.is_open()) {
							}
							json j;
							ifff >> j;
							int effect = p->effect;
							j["isBanned"] = 1;
							std::ofstream o("players/" + ((PlayerInfo*)(currentPeer2->data))->rawName + ".json"); //save
							if (!o.is_open()) {
								cout << GetLastError() << endl;
								_getch();
							}
							o << j << std::endl;
							string bannamed = ((PlayerInfo*)(currentPeer2->data))->rawName;
							std::ofstream outfile("bans/" + bannamed + ".txt");
							outfile << "user who banned this ID: " + ((PlayerInfo*)(peer->data))->rawName;
							outfile.close();
						}
						enet_peer_disconnect_later(currentPeer2, 0);
					}
					ENetPacket* packet7 = enet_packet_create(p7.data,
						p7.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer2, 0, packet7);

				}
			}
		}
		if (tile == 278 && ((PlayerInfo*)(currentPeer->data))->x / 32 == xx && ((PlayerInfo*)(currentPeer->data))->y / 32 == yy)
		{
			bool iscontainseas = false;
			SearchInventoryItem(peer, 278, 1, iscontainseas);
			if (!iscontainseas)
			{
				autoBan(peer, false, 24 * 7, "failed to find 278 item in sendtileupdate");
				break;
			}
			else {
				RemoveInventoryItem(278, 1, peer);
				string cursename = ((PlayerInfo*)(currentPeer->data))->rawName;
				bool existx = std::experimental::filesystem::exists("players/" + PlayerDB::getProperName(cursename) + ".json");
				if (!existx)
				{
					continue;
				}
				std::ofstream outfile("cursedplayers/" + cursename + ".txt");
				outfile << "caused by: " + ((PlayerInfo*)(peer->data))->rawName;
				outfile.close();
				if (((PlayerInfo*)(currentPeer->data))->haveGrowId == false && ((PlayerInfo*)(currentPeer->data))->haveGuestId == false) continue;
				Player::OnConsoleMessage(currentPeer, "`#** `$The Ancient Ones `ohave used `#Curse `oon `2" + ((PlayerInfo*)(currentPeer->data))->rawName + "`o! `#**");
				Player::OnAddNotification(currentPeer, "`0Warning from `4System`0: You've been `bCURSED `0from GrowtopiaLR.", "audio/explode.wav", "interface/hommel.rttex");
				Player::OnConsoleMessage(currentPeer, "`oWarning from `4System`o: You've been `bCursed `ofrom GrowtopiaLR by `2" + ((PlayerInfo*)(peer->data))->rawName + "`o.");
				((PlayerInfo*)(currentPeer->data))->isCursed = true;
				sendPlayerToWorld(currentPeer, (PlayerInfo*)(currentPeer->data), "HELL");
			}
		}
	}
	if (tile == 32)
	{
		if (world->items[x + (y * world->width)].foreground == 7864 || world->items[x + (y * world->width)].foreground == 2252 || world->items[x + (y * world->width)].foreground == 1482)
		{
			if (tile == 18) {
				GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`wTime:  `2(" + currentDateTime() + ")"));
				ENetPacket* packet = enet_packet_create(p3.data,
					p3.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p3.data;
			}
		}
		if (world->owner == "" || isWorldOwner(peer, world) || static_cast<PlayerInfo*>(peer->data)->adminLevel > 1337) {
			if (world->items[x + (y * world->width)].foreground == 3528 && tile == 32) {// Made by hypercold
				Player::OnDialogRequest(peer, "add_label_with_icon|big|`wArt Canvas|left|3528|\nadd_spacer|small|\nadd_textbox|`oThe Canvas is " + GetItemDef(world->items[x + (y * world->width)].intdata).name + ". |\nadd_item_picker|paints|`oPaint Something|Select any item to Paint|\nadd_text_input|psign|`wSigned: |`4fked oof!|100|\nend_dialog|painting|cancel|ok|");
				static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);


			}
		}
		if (world->items[x + (y * world->width)].foreground == 1790)
		{
			if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
				string cQuest = "None";
				ifstream fileStream213("quests/currentquest/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
				fileStream213 >> cQuest;
				fileStream213.close();
				if (cQuest == "None")
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Legendary Wizard``|left|1790|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Select a `^Quest `5Which you want to complete, each `^Quest `5Has `210 `5Steps, after completing all of them you will earn the `^Quest Item`5!|\n\nadd_spacer|small|\nadd_button|questkatana|`9Quest For Legendary Katana|\nadd_button|questbot|`9Quest of Steel|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
				}
				else if (cQuest == "Katana")
				{
					int sQuest = 1;
					ifstream fileStream216("quests/currentqueststep/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
					fileStream216 >> sQuest;
					fileStream216.close();
					if (sQuest == 1)
					{
						int s1Quest = 0;
						ifstream fileStream216("quests/katana/step1/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
						fileStream216 >> s1Quest;
						fileStream216.close();
						std::ifstream ifsz("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
						std::string content((std::istreambuf_iterator<char>(ifsz)),
							(std::istreambuf_iterator<char>()));
						int b = atoi(content.c_str());
						int togive = 3000000 - s1Quest;
						int cangive = b - togive;
						if (cangive >= 0)
						{
							cangive = 3000000 - s1Quest;
						}
						else {
							cangive = b;
						}
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 1: Welcome adventurer, your first `^Quest `5Will be to bring me `43m `9Gems`5, Hope that not too much for you`5!|\nadd_textbox|`5Progress: `^" + to_string(s1Quest) + "/3000000 `5Gems|\nadd_button|s1sgemsgive|`9Give `^" + to_string(cangive) + " `9Gems|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
					}
					else if (sQuest == 2)
					{
						int s2Quest = 0;
						ifstream fileStream216("quests/katana/step2/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
						fileStream216 >> s2Quest;
						fileStream216.close();
						if (s2Quest < 50000)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 2: This step will be maybe more challenging, but i want you to earn `450k `5Experience`5!|\nadd_textbox|`5Progress: `^" + to_string(s2Quest) + "/50000 `5Experience|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
						else {
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 2: This step will be maybe more challenging, but i want you to earn `450k `5Experience`5!|\nadd_textbox|`5Progress: `^50000/50000 `5Experience|\nadd_button|s2scomplete|`9Complete!|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}

					}
					else if (sQuest == 3)
					{
						int s3Quest = 0;
						ifstream fileStream216("quests/katana/step3/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
						fileStream216 >> s3Quest;
						fileStream216.close();
						if (s3Quest < 3)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 3: I challenge you to earn `43 `5Growtokens, You can keep them. I'm more popular than you can imagine`5!|\nadd_textbox|`5Progress: `^" + to_string(s3Quest) + "/3 `5Growtokens|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
						else {
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 3: I challenge you to earn `43 `5Growtokens, You can keep them. I'm more popular than you can imagine`5!|\nadd_textbox|`5Progress: `^3/3 `5Growtokens|\nadd_button|s3scomplete|`9Complete!|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}

					}
					else if (sQuest == 4)
					{
						int s4Quest = 0;
						ifstream fileStream216("quests/katana/step4/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
						fileStream216 >> s4Quest;
						fileStream216.close();
						bool iscontains = false;
						SearchInventoryItem(peer, 9758, 1, iscontains);
						if (!iscontains)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 4: I challenge you to bring me `4One `5Golden Digger Spade`5!|\nadd_textbox|`5Progress: `^" + to_string(s4Quest) + "/1 `5Golden Digger Spade|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
						else {
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 4: I challenge you to bring me `4One `5Golden Digger Spade`5!|\nadd_textbox|`5Progress: `^1/1 `5Golden Digger Spade|\nadd_button|s4scomplete|`9Complete!|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
					}
					else if (sQuest == 5)
					{
						int s5Quest = 0;
						ifstream fileStream216("quests/katana/step5/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
						fileStream216 >> s5Quest;
						fileStream216.close();
						bool iscontains = false;
						SearchInventoryItem(peer, 1794, 1, iscontains);
						if (!iscontains)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 5: Congratulations on Beating all of my Steps, Now bring me The Legendary Orb`5!|\nadd_textbox|`5Progress: `^" + to_string(s5Quest) + "/1 `5Legendary Orb|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
						else {
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 5: Congratulations on Beating all of my Steps, Now bring me The Legendary Orb`5!|\nadd_textbox|`5Progress: `^1/1 `5Legendary Orb|\nadd_button|s5scomplete|`cDary!|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
					}
				}
			}

			else {
				Player::OnTextOverlay(peer, "`#You must be world owner to use `#Legendary Wizard`#!");
			}
		}
		if (world->items[x + (y * world->width)].foreground == 5000)
		{
			if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 1000 || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
				if (tile == 32)
				{
					string itemname = GetItemDef(world->bgID).name;
					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\nadd_label_with_icon|big|`wWeather Machine - Background``|left|5000|\nadd_spacer|small|\nadd_textbox|`oYou can scan any Background Block to set it up in your weather machine.|\nadd_item_picker|bg_pick|Item: `2" + itemname + "|Select any Background Block|\nadd_quick_exit|\nend_dialog|bg_weather|Cancel|Okay|"));
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet);
					delete p.data;
					((PlayerInfo*)(peer->data))->wrenchedBlockLocation = x + (y * world->width);

				}
			}
		}
		if (world->items[x + (y * world->width)].foreground == 3832) { // stuff weather dialog
			if (tile == 32) {
				if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel >= 999 || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
					if (x != 0)
					{
						((PlayerInfo*)(peer->data))->lastPunchX = x;
					}
					if (y != 0)
					{
						((PlayerInfo*)(peer->data))->lastPunchY = y;
					}
					string stuff_dialog = "set_default_color|`o\nadd_label_with_icon|big|`wWeather Machine - Stuff``|left|3832|\nadd_spacer|small|\nadd_item_picker|stuff_pick|Item: `2" + GetItemDef(world->stuffID).name + "|Select any item to rain down|\nadd_text_input|stuff_gravity|Gravity:|" + to_string(world->stuff_gravity) + "|3|\nadd_checkbox|stuff_spin|Spin Items|" + to_string(world->stuff_spin) + "|\nadd_checkbox|stuff_invert|Invert Sky Colors|" + to_string(world->stuff_invert) + "|\nadd_textbox|`oSelect item and click okay to continue!|\nend_dialog|stuff_weather|Cancel|Okay|";

					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), stuff_dialog));
					ENetPacket* packet = enet_packet_create(p.data,
						p.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packet);
					delete p.data;
					((PlayerInfo*)(peer->data))->wrenchedBlockLocation = x + (y * world->width);
				}
			}
		}
		if (world->items[x + (y * world->width)].foreground == 6016) {
			static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
			static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
			SendGScan(peer, world, x, y);
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 3898) {
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wTelephone`|left|3898|\n\nadd_spacer|small|\nadd_label|small|`oDial a number to call somebody in Growtopia. Phone numbers have 5 digits. Most numbers are not in service!|\nadd_spacer|small|\nadd_text_input|telephonenumber|Phone #||5|\nend_dialog|usetelephone|Hang Up|`wDial|\n");
		}
	}
	if (world->items[x + (y * world->width)].foreground == 3794) {
		if (tile == 32) {
			if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel > 3) {
				static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
				string dshelf1;
				string dshelf2;
				string dshelf3;
				string dshelf4;
				if (world->items[x + (y * world->width)].dshelf1 != 0) {
					dshelf1 = "`$" + getItemDef(world->items[x + (y * world->width)].dshelf1).name + "";
				}
				else {
					dshelf1 = "`4EMPTY";
				}
				if (world->items[x + (y * world->width)].dshelf2 != 0) {
					dshelf2 = "`$" + getItemDef(world->items[x + (y * world->width)].dshelf2).name + "";
				}
				else {
					dshelf2 = "`4EMPTY";
				}
				if (world->items[x + (y * world->width)].dshelf3 != 0) {
					dshelf3 = "`$" + getItemDef(world->items[x + (y * world->width)].dshelf3).name + "";
				}
				else {
					dshelf3 = "`4EMPTY";
				}
				if (world->items[x + (y * world->width)].dshelf4 != 0) {
					dshelf4 = "`$" + getItemDef(world->items[x + (y * world->width)].dshelf4).name + "";
				}
				else {
					dshelf4 = "`4EMPTY";
				}
				string gscan = "set_default_color|`o\nadd_label_with_icon|big|`wDisplay Shelf``|left|3794|\nadd_spacer|small|\nadd_button|dshelf1|`wItem 1:" + dshelf1 + "|left|\nadd_button|dshelf2|`wItem 2:" + dshelf2 + "|left|\nadd_button|dshelf3|`wItem 3:" + dshelf3 + "|left|\nadd_button|dshelf4|`wItem 4:" + dshelf4 + "|left|\nadd_spacer|small|\nend_dialog||Close|";
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), gscan));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
			}
		}
	}
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].foreground == 3)
		{
			int hi = data.punchX * 32;
			int hi2 = data.punchY * 32;
		}
		if (world->items[x + (y * world->width)].foreground == 5)
		{
			updateDoor(peer, 5, data.punchX, data.punchY, "`4na tai jo keista kam sitas cia``");
		}
		if (world->items[x + (y * world->width)].foreground == 120 || world->items[x + (y * world->width)].foreground == 4174) {
			if (((PlayerInfo*)(peer->data))->cloth_hand == 5480)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `wRayman`@!");
				return;
			}
			else if (((PlayerInfo*)(peer->data))->cloth_hand == 9758)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `4Phoenix Sword`@!");
				return;
			}
			else if (((PlayerInfo*)(peer->data))->cloth_hand == 7956)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `#Burnished Sword`@!");
				return;
			}
			else if (((PlayerInfo*)(peer->data))->cloth_hand == 9716)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `cCrystal Infused Sword`@!");
				return;
			}
			else if (((PlayerInfo*)(peer->data))->cloth_hand == 9456)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `9Neptune `oTrident`@!");
				return;
			}
			else if (((PlayerInfo*)(peer->data))->cloth_hand == 3162)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `1Twin Swords`@!");
				return;
			}
		}
		if (world->items[x + (y * world->width)].foreground == 1008) {
			if (((PlayerInfo*)(peer->data))->haveGrowId && ((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner || ((PlayerInfo*)(peer->data))->rawName == "beath") {
				int valgem;
				valgem = rand() % 40;
				std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
				std::string content((std::istreambuf_iterator<char>(ifs)),
					(std::istreambuf_iterator<char>()));
				if (((PlayerInfo*)(peer->data))->level < 15)
				{
					Player::OnConsoleMessage(peer, "`@You Must Be Aleast `9Level `415 `@To Harvest `eATM Machines`@!");
				}
				else {
					using namespace std::chrono;
					if (((PlayerInfo*)(peer->data))->lastATM + 1200 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
					{
						((PlayerInfo*)(peer->data))->lastATM = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						ofstream fd("blocks/atm/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
						fd << ((PlayerInfo*)(peer->data))->lastATM;
						fd.close();
					}
					else {
						int kiekDar = (((PlayerInfo*)(peer->data))->lastATM + 1200 - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count());
						long milli = kiekDar;
						long hr = milli / 3600000;
						milli = milli - 3600000 * hr;
						long min = milli / 60000;
						milli = milli - 60000 * min;
						long sec = milli / 1000;
						Player::OnConsoleMessage(peer, "`9Cooldown `@Please Wait `9" + to_string(sec) + "s. `@To Use ATM!");
						return;
					}
					if (((PlayerInfo*)(peer->data))->chatnotifications == true)
					{
						Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2gems `^from the `eATM Machine`^!");
					}
					Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, true);
					int gembux = atoi(content.c_str());
					int fingembux = gembux + valgem;
					ofstream myfile;
					myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
					myfile << fingembux;
					myfile.close();
					int gemcalc = gembux + valgem;
					GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
					ENetPacket* packetpp = enet_packet_create(pp.data,
						pp.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(peer, 0, packetpp);
					delete pp.data;
					int hi = data.punchX * 32;
					int hi2 = data.punchY * 32;
					Player::OnParticleEffect(peer, 30, hi, hi2, 0);
				}
			}
			else {
				Player::OnConsoleMessage(peer, "`@You don't have access to break this `eATM Machine`@!");
			}
		}
		if (world->items[x + (y * world->width)].foreground == 1636) {
			if (((PlayerInfo*)(peer->data))->haveGrowId && ((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner) {
				if (((PlayerInfo*)(peer->data))->level < 40)
				{
					Player::OnConsoleMessage(peer, "`@You Must Be Aleast `9Level `440 `@To Harvest `#Unicorns`@!");
				}
				else {
					using namespace std::chrono;
					if (((PlayerInfo*)(peer->data))->lastATM + 3200 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
					{
						((PlayerInfo*)(peer->data))->lastATM = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						ofstream fd("unicorn/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
						fd << ((PlayerInfo*)(peer->data))->lastATM;
						fd.close();
					}
					else {
						int kiekDar = (((PlayerInfo*)(peer->data))->lastATM + 3200 - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count());
						long milli = kiekDar;
						long hr = milli / 3600000;
						milli = milli - 3600000 * hr;
						long min = milli / 60000;
						milli = milli - 60000 * min;
						long sec = milli / 1000;
						Player::OnConsoleMessage(peer, "`9Cooldown `@Please Wait `9" + to_string(sec) + "s. `@To Use `#Unicorn!");
						return;
					}
					string crystaluMas[26] = { "gold", "sapphire", "sapphire", "diamond", "rubble", "sapphire", "rubble", "rubble", "opal", "opal", "opal", "opal", "gold", "emerald", "amber", "sapphire", "amber", "sapphire", "amber", "amber", "amber", "emerald", "gold", "gold", "gold", "amber" };
					int crystalChance = rand() % 3;
					int randIndex = rand() % 26;
					string crystalName = crystaluMas[randIndex];
					GiveChestPrizeCrystal(peer, crystalName, crystalChance);
					int hi = data.punchX * 32;
					int hi2 = data.punchY * 32;
					Player::OnParticleEffect(peer, 73, hi, hi2, 0);
				}
			}
			else {
				Player::OnConsoleMessage(peer, "`@You don't have access to break this `#Unicorn`@!");
			}
		}
	}
	if (world->items[x + (y * world->width)].foreground == 6)
	{
		GamePacket p2 = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`wIt's too strong to break."), 0), 1));
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
		return;
	}
	if (((PlayerInfo*)(peer->data))->isCreator != true)
	{
		if (world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 7372 || world->items[x + (y * world->width)].foreground == 3760) {
			if (((PlayerInfo*)(peer->data))->cloth_hand == 8452) {
			}
			else {
				GamePacket p2 = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`wIt's too strong to break."), 0), 1));
				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2);
				delete p2.data;
				return;
			}
		}

		if (tile == 9444)
		{
			if (((PlayerInfo*)(peer->data))->cloth_hand == 2952 || ((PlayerInfo*)(peer->data))->cloth_hand == 9758 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312 || ((PlayerInfo*)(peer->data))->cloth_hand == 7956 || ((PlayerInfo*)(peer->data))->cloth_hand == 2592) {
			}
			else {
				Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`5This stone is too strong!", 0, true);
				return;
			}
		}

		if (tile == 6 || tile == 3760 || tile == 1000 || tile == 7372 || tile == 1770 || tile == 1832 || tile == 4720)
		{
			GamePacket p2 = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`wIt's too heavy to place."), 0), 1));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			return;
		}
	}
	if (world->name == "ADMIN" && !((PlayerInfo*)(peer->data))->adminLevel)
	{
		return;
	}
	if (world->name == "HELL" && !((PlayerInfo*)(peer->data))->adminLevel)
	{
		return;
	}
	if (world->name != "ADMIN" || world->name != "HELL") {
		if (world->owner != "") {
		}
	}
	if (tile == 1866)
	{
		if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel > 1336) {
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
			{
				return;
			}
			world->items[x + (y * world->width)].glue = !world->items[x + (y * world->width)].glue;
			UpdateVisualsForBlock(peer, true, x, y, world);
			return;
		}
	}
	if (((PlayerInfo*)(peer->data))->cloth_hand == 3494)
	{
		if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel > 1336) {
			switch (tile)
			{
			case 3478:
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
				{
					return;
				}
				world->items[x + (y * world->width)].red = true;
				world->items[x + (y * world->width)].green = false;
				world->items[x + (y * world->width)].blue = false;
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			case 3480:
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
				{
					return;
				}
				world->items[x + (y * world->width)].red = true;
				world->items[x + (y * world->width)].green = true;
				world->items[x + (y * world->width)].blue = false;
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			case 3482:
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
				{
					return;
				}
				world->items[x + (y * world->width)].red = false;
				world->items[x + (y * world->width)].green = true;
				world->items[x + (y * world->width)].blue = false;
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			case 3484:
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
				{
					return;
				}
				world->items[x + (y * world->width)].red = false;
				world->items[x + (y * world->width)].green = true;
				world->items[x + (y * world->width)].blue = true;
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			case 3486:
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
				{
					return;
				}
				world->items[x + (y * world->width)].red = false;
				world->items[x + (y * world->width)].green = false;
				world->items[x + (y * world->width)].blue = true;
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			case 3488:
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
				{
					return;
				}
				world->items[x + (y * world->width)].red = true;
				world->items[x + (y * world->width)].green = false;
				world->items[x + (y * world->width)].blue = true;
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			case 3490:
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
				{
					return;
				}
				world->items[x + (y * world->width)].red = true;
				world->items[x + (y * world->width)].green = true;
				world->items[x + (y * world->width)].blue = true;
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			case 3492:
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
				{
					return;
				}
				world->items[x + (y * world->width)].red = false;
				world->items[x + (y * world->width)].green = false;
				world->items[x + (y * world->width)].blue = false;
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			default: break;
			}
		}
	}
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].foreground == 758)
		{
			sendRoulete(peer);
		}
	}
	if (tile == 540) {
		int netid = ((PlayerInfo*)(peer->data))->netID;
		RemoveInventoryItem(540, 1, peer);
		GamePacket p3 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`2BURRRPPP...!"), 0));
		ENetPacket* packet3 = enet_packet_create(p3.data,
			p3.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet3);
		delete p3.data;
		return;
	}
	if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::BULLETIN_BOARD && tile == 32 || world->items[x + (y * world->width)].foreground == 658 && tile == 32)
	{
		string mail_message;
		((PlayerInfo*)(peer->data))->lastPunchX = x;
		((PlayerInfo*)(peer->data))->lastPunchY = y;
		string clearbutton = "\nadd_button|clearbulletin|`4Clear Board``|noflags|0|0|";
		if (world->items[x + (y * world->width)].bulletinhide == 0)
		{
			mail_message = world->items[x + (y * world->width)].mail;
		}
		else
		{
			mail_message = world->items[x + (y * world->width)].bulletinmsg;
		}
		if (mail_message == "")
		{
			mail_message = "\nadd_textbox|The Bulletin Board is empty.|left|";
		}
		if (world->items[x + (y * world->width)].mailcount == 0)
		{
			clearbutton = "";
		}
		if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 1000 || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
			sendDialog(peer, "set_default_color|`o\nadd_label_with_icon|big|`wBulletin Board``|left|658|\nadd_spacer|small|" + mail_message + "\nadd_spacer|small|\nadd_textbox|Add to conversation?|left|\nadd_text_input|sign_text|||128|\nadd_spacer|small|\nadd_button|send|`2Add``|noflags|0|0|\nadd_spacer|small|\nadd_label_with_icon|big|`wOwner Options|left|242|\nadd_spacer|small|\nadd_textbox|To remove an individual comment, press the icon to the left of it.|left|\nadd_spacer|small|\nadd_spacer|small|" + clearbutton + "|\nadd_checkbox|checkbox_locked|Public can add|" + to_string(world->items[x + (y * world->width)].bulletinpublic) + "\nadd_checkbox|checkbox_hide|Hide names|" + to_string(world->items[x + (y * world->width)].bulletinhide) + "\nend_dialog|bulletin_edit|Cancel|OK|");
		}
		else
		{
			//	to_string(world->items[x + (y * world->width)].bulletinpublic)
			if (world->items[x + (y * world->width)].bulletinpublic == 1)
			{
				sendDialog(peer, "set_default_color|`o\nadd_label_with_icon|big|`wBulletin Board``|left|658|\nadd_spacer|small|" + mail_message + "\n\nadd_textbox|Add to conversation?|left|\nadd_text_input|sign_text|||128|\nadd_spacer|small|\nadd_button|send|`2Add``|noflags|0|0|\nend_dialog|bulletin_edit|Cancel||");
			}
			else
			{
				sendDialog(peer, "set_default_color|`o\nadd_label_with_icon|big|`wBulletin Board``|left|658|\nadd_spacer|small|" + mail_message + "\n\nend_dialog|bulletin_edit|Continue||");
			}

		}
		return;
	}
	if (world->items[x + (y * world->width)].foreground == 656 && tile == 18 || world->items[x + (y * world->width)].foreground == 1006 && tile == 18) {
		SendTalkSelf(peer, " There are `5" + to_string(world->items[x + (y * world->width)].mailcount) + "`` letter(s) in the mailbox.");
	}
	if (world->items[x + (y * world->width)].foreground == 656 && tile == 32 || world->items[x + (y * world->width)].foreground == 1006 && tile == 32) {
		string mailbox = "\nadd_textbox|Write a letter to yourself?|left|\nadd_text_input|sign_text|||128|\nadd_spacer|small|\nadd_button|send|`2Send Letter``|noflags|0|0|";
		((PlayerInfo*)(peer->data))->lastPunchX = x;
		((PlayerInfo*)(peer->data))->lastPunchY = y;
		string mail_message = world->items[x + (y * world->width)].mail;
		if (mail_message == "")
		{
			mail_message = "\nadd_textbox|Your mailbox is currently empty.|left|";
		}
		if (world->items[x + (y * world->width)].mailcount == 10)
		{
			mailbox = "";
		}
		if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 1000 || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
			string mail = "set_default_color|`o\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|You have `w" + to_string(world->items[x + (y * world->width)].mailcount) + "`` letter:|left|\nadd_spacer|small|" + mail_message + "\nadd_spacer|small|\nadd_spacer|small|\nadd_button|mailbox_empty|`4Empty Mailbox``|noflags|0|0|" + mailbox + "\nend_dialog|mailbox_edit|Cancel||";
			Player::OnDialogRequest(peer, mail);
		}
		else
		{
			if (world->items[x + (y * world->width)].mailcount == 10)
			{
				string mail = "set_default_color|`o\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|There's already have 10 message, try again later.|left|\nend_dialog|mailbox_edit|Cancel||";
				Player::OnDialogRequest(peer, mail);
				return;
			}
			string mail = "set_default_color|`o\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|Want to leave a message for the owner?|left|\nadd_text_input|sign_text|||128|\nadd_spacer|small|\nadd_button|send|`2Send Letter``|noflags|0|0|\nend_dialog|mailbox_edit|Cancel||";
			Player::OnDialogRequest(peer, mail);
		}
		return;
	}
	if (world->items[x + (y * world->width)].foreground == 3898 && tile == 32) {
		if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 1000 || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
			string telephone = "set_default_color|`o\nadd_label_with_icon|big|`wTelephone``|left|3898|\nadd_textbox|Dial a number to call somebody in Growtopia. Phone numbers have 5 digits, like 12345 (try it - you'd be crazy not to!). Most numbers are not in service!|left|\nadd_text_input|dial|Phone #||5|\nend_dialog|phonecall|Hang Up|Dial|";
			Player::OnDialogRequest(peer, telephone);
		}
	}
	
	if (world->items[x + (y * world->width)].foreground == 9752 && tile == 32) {
		string mailbox = "\nadd_textbox|Write a letter to yourself?|left|\nadd_text_input|sign_text|||128|\nadd_spacer|small|\nadd_button|send|`2Send Letter``|noflags|0|0|";
		((PlayerInfo*)(peer->data))->lastPunchX = x;
		((PlayerInfo*)(peer->data))->lastPunchY = y;
		string mail_message = world->items[x + (y * world->width)].mail;
		if (mail_message == "")
		{
			mail_message = "\nadd_textbox|This bottle is currently empty.|left|";
		}
		if (world->items[x + (y * world->width)].mailcount == 1)
		{
			mailbox = "";
		}
		if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 1000 || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
			string mail = "set_default_color|`o\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|You have `w" + to_string(world->items[x + (y * world->width)].mailcount) + "`` letter:|left|\nadd_spacer|small|" + mail_message + "\nadd_spacer|small|\nadd_spacer|small|\nadd_button|mailbox_empty|`4Clear Bottle``|noflags|0|0|" + mailbox + "\nend_dialog|mailbox_edit|Cancel||";
			Player::OnDialogRequest(peer, mail);
		}
		else
		{
			if (world->items[x + (y * world->width)].mailcount == 1)
			{
				string mail = "set_default_color|`o\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|There's already have 1 message, try again later.|left|\nend_dialog|mailbox_edit|Cancel||";
				Player::OnDialogRequest(peer, mail);
				return;
			}
			string mail = "set_default_color|`o\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|Want to leave a message for the owner?|left|\nadd_text_input|sign_text|||128|\nadd_spacer|small|\nadd_button|send|`2Send Letter``|noflags|0|0|\nend_dialog|mailbox_edit|Cancel||";
			Player::OnDialogRequest(peer, mail);
		}
		return;
	}
	if (tile == 8428) {
		bool iscontainsss = false;
		SearchInventoryItem(peer, 8428, 1, iscontainsss);
		if (!iscontainsss)
		{
			autoBan(peer, true, 1, "he tried to punch 8428 item, but did not has it.");
		}
		else {
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wUranus Blast`|left|8428|\n\nadd_spacer|small|\nadd_label|small|`oThis item creates a new world! Enter a unique name for it.|\nadd_spacer|small|\nadd_text_input|uranusname|New World Name||30|\nend_dialog|useuranusblast|Cancel|`5Create!|\n");
		}
	}
	if (tile == 32)
	{
		if (world->items[x + (y * world->width)].foreground == 2978) {
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|\nadd_label_with_icon|big|`wVending Machine|left|2978|\nadd_textbox|`oAn Item is on display here.!|\nadd_spacer|small|\nend_dialog|dialbro|Pick it up|Leave it|"));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		}
	}
	string gay = world->items[x + (y * world->width)].text;
	int gay2 = world->items[x + (y * world->width)].foreground;
	if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SIGN || world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214)
	{
		if (world->owner != "") {
			if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
				if (tile == 32) {
					((PlayerInfo*)(peer->data))->wrenchx = x;
					((PlayerInfo*)(peer->data))->wrenchy = y;
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(gay2) + "|\n\nadd_textbox|`oWhat would you like to write on this sign?|\nadd_text_input|ch3||" + gay + "|100|\nembed_data|tilex|" + std::to_string(((PlayerInfo*)(peer->data))->wrenchx) + "\nembed_data|tiley|" + std::to_string(((PlayerInfo*)(peer->data))->wrenchy) + "\nend_dialog|sign_edit|Cancel|OK|");
				}
			}
		}
	}
	if (world->items[x + (y * world->width)].foreground == 1436) {
		{
			if (tile == 32)
				if (((PlayerInfo*)(peer->data))->haveGrowId && ((PlayerInfo*)(peer->data))->rawName == getPlyersWorld(peer)->owner) {

					{
						string line;
						GTDialog allLog;

						ifstream banlog("worldlogs/" + world->name + ".txt");
						allLog.addLabelWithIcon("`wSecurity Camera", 1436, LABEL_BIG);
						allLog.addSpacer(SPACER_SMALL);
						allLog.addButton("clearlogs", "`4Clear Logs");
						allLog.addSpacer(SPACER_SMALL);
						while (getline(banlog, line))
						{
							allLog.addLabelWithIcon("" + line + "", 32, LABEL_SMALL);
						}
						banlog.close();
						allLog.addSpacer(SPACER_SMALL);

						allLog.addQuickExit();
						allLog.endDialog("Close", "", "Close");

						Player::OnDialogRequest(peer, allLog.finishDialog());
					}
				}


		}
	}

	if (tile == 1436) {
		std::ofstream outfile("worldlogs/" + world->name + ".txt");
	}
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
					treeModify(currentPeer, x, y, ((PlayerInfo*)(peer->data))->netID);
					int chance = (rand() % 100) + 1;
					int numb = (rand() % 5) + 1;
					if (chance < 10) {



						DropItem(
							peer, -1,
							x * 32 + (rand() % 16),
							y * 32 + (rand() % 16),
							112,
							1, 0);

					}
					if (chance < 10) {
						GamePacket p3 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "A " + GetItemDef(world->items[x + (y * world->width)].foreground).name + " seed falls out!"), 0));


						ENetPacket* packet3 = enet_packet_create(p3.data,
							p3.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, packet3);
						delete p3.data;
						DropItem(
							peer, -1,
							x * 32 - (rand() % 8),
							y * 32 + (rand() % 8),
							world->items[x + (y * world->width)].foreground,
							1, 0);
					}

					DropItem(
						peer, -1,
						x * 32 + (rand() % 16),
						y * 32 + (rand() % 16),
						world->items[x + (y * world->width)].foreground - 1,
						numb, 0);
					break;
				}
			}
		}
		world->items[x + (y * world->width)].foreground = 0;
		return;
	}


	if (tile == 1436) {
		std::ofstream outfile("worldlogs/" + world->name + ".txt");
	}
	if (world->name != "ADMIN" || world->name != "HELL") {
		if (world->owner != "") {

			string name = ((PlayerInfo*)(peer->data))->rawName;
			if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel == 1000 || ((PlayerInfo*)(peer->data))->adminLevel == 1337 || (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
				if (((PlayerInfo*)(peer->data))->rawName == "") return;
				// WE ARE GOOD TO GO

				if (world->items[x + (y * world->width)].foreground == 242 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || world->items[x + (y * world->width)].foreground == 1796 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || world->items[x + (y * world->width)].foreground == 4428 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || world->items[x + (y * world->width)].foreground == 2408 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || world->items[x + (y * world->width)].foreground == 7188 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || world->items[x + (y * world->width)].foreground == 5980 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || world->items[x + (y * world->width)].foreground == 2950 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || world->items[x + (y * world->width)].foreground == 5638 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()))
				{
					return;
				}

				if (tile == 32 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end())) {
					return;
				}
				string offlinelist = "";
				string offname = "";
				int ischecked;
				int ischecked1;
				int ischecked2;
				for (std::vector<string>::const_iterator i = world->accessed.begin(); i != world->accessed.end(); ++i) {
					offname = *i;
					offlinelist += "\nadd_checkbox|isAccessed|" + offname + "|0|\n";

				}


				if (world->isPublic == true) {
					ischecked = 1;
				}
				else {
					ischecked = 0;
				}
				int noclap = 0;
				bool casin = world->isCasino;
				if (casin == true) {
					noclap = 1;
				}
				else {
					noclap = 0;
				}
				if (world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 2408 || world->items[x + (y * world->width)].foreground == 7188 || world->items[x + (y * world->width)].foreground == 5814 || world->items[x + (y * world->width)].foreground == 4428 || world->items[x + (y * world->width)].foreground == 5260 || world->items[x + (y * world->width)].foreground == 8470)
				{
					int publicx = 0;
					if (world->isPublic == true)
					{
						publicx = 1;
					}
					else
					{
						publicx = 0;
					}
					string publik = to_string(publicx);
					//testlol
					int publicx1 = 0;
					if (world->allowMod == true)
					{
						publicx1 = 1;
					}
					else
					{
						publicx1 = 0;
					}
					string publik1 = to_string(publicx1);
					//testlol
					int rainbows = world->rainbows;
					int muted = world->silence;
					if (tile == 32) {
						if (world->accessed.size() == 0) {
							((PlayerInfo*)(peer->data))->lastPunchX = x;
							((PlayerInfo*)(peer->data))->lastPunchY = y;

							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + GetItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|netid|`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + publik + "|\nadd_checkbox|checkbox_noclip|Allow anyone to `2walktrough walls|" + publik1 + "|\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|" + to_string(world->disable_music) + "\nadd_text_input|tempo|Music BPM|" + to_string(world->tempo) + "|3|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|" + to_string(world->disable_music_render) + "\nadd_text_input|minimum_entry_level|World Level: |1|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|getKey|Get World Key|noflags|0|0|\nend_dialog|lock_editz|Cancel|OK|"));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							delete p.data;
						}

						else {
							((PlayerInfo*)(peer->data))->lastPunchX = x;
							((PlayerInfo*)(peer->data))->lastPunchY = y;
							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + GetItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|" + offlinelist + "add_spacer|small|\nadd_player_picker||`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + publik + "|\nadd_checkbox|checkbox_noclip|Allow anyone to `2walktrough walls|" + publik1 + "|\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|" + to_string(world->disable_music) + "\nadd_text_input|tempo|Music BPM|" + to_string(world->tempo) + "|3|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|" + to_string(world->disable_music_render) + "\nadd_text_input|minimum_entry_level|World Level: |1|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|getKey|Get World Key|noflags|0|0|\nend_dialog|lock_editz|Cancel|OK|"));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							delete p.data;
						}
					}
				}

			}


			/*		else if (((PlayerInfo*)(peer->data))->rawName == accessname)
			{
			if (world->items[x + (y*world->width)].foreground == 242)
			{
			string ownername = world->owner;

			GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`0" + ownername + "'s `$World Lock`0. (Access granted)"), 0));


			ENetPacket * packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			return;
			}
			}
			*/

			else if (world->isPublic)
			{
				if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) < 1200 && ((PlayerInfo*)(peer->data))->BePlayer == false) {
					if (world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 5814 || world->items[x + (y * world->width)].foreground == 2408 || world->items[x + (y * world->width)].foreground == 7188 || world->items[x + (y * world->width)].foreground == 4802 || world->items[x + (y * world->width)].foreground == 4428 || world->items[x + (y * world->width)].foreground == 5260 || world->items[x + (y * world->width)].foreground == 8470)
					{
						string ownername = world->Displayowner;
						OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`0" + ownername + "'s `$" + GetItemDef(world->items[x + (y * world->width)].foreground).name + "`0. (`9Open to Public`w)", true);
						PlayAudioWorld(peer, "audio/punch_locked.wav");
						return;
					}
				}
			}


			else {
				if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) < 1200 && ((PlayerInfo*)(peer->data))->BePlayer == false) {
					if (tile == 18)
					{
						if (GetItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = world->Displayowner;
							OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`w" + ownername + "'s `$" + GetItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", true);

						}
						if (world->items[x + (y * world->width)].foreground != 0 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 6)
						{
							PlayAudioWorld(peer, "audio/punch_locked.wav");
						}
						return;
					}
					else if (tile == 32)
					{
						if (GetItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							if (getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass) < 1200 || ((PlayerInfo*)(peer->data))->BePlayer == false) {
								OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`wI'm `4unable`w to pick the lock.", true);
							}
						}
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
					if (tile != 18)
					{
						if (tile != 32)
						{
							if (GetItemDef(tile).blockType != BlockTypes::CONSUMABLE) {
								OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`wThat area is owned by " + world->Displayowner, true);
								PlayAudioWorld(peer, "audio/punch_locked.wav");
								return;
							}
						}
					}
				}
				else
				{
					if (tile == 32)
					{
						if (GetItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + GetItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|small|\nadd_textbox|`oThis lock is owned by `w" + world->Displayowner + "`o, but i have access on it.|small|\nend_dialog|removemyaccess|Cancel|`wRemove my Access|"));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							delete p.data;
							return;
						}

					}
				}
			}

			if (tile == 242 || tile == 1796 || tile == 2408 || tile == 7188 || tile == 4802 || tile == 5814 || tile == 4428 || tile == 5260 || tile == 8470) {

				OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`0Only one `$World Lock`0 can be placed in a world!", true);
				return;
			}

		}
		if (world->name != "ADMIN") {
			if (world->owner != "") {

				string name = ((PlayerInfo*)(peer->data))->rawName;
				if (((PlayerInfo*)(peer->data))->rawName == world->owner || ((PlayerInfo*)(peer->data))->adminLevel > 1000 || (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()) || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "beath" || ((PlayerInfo*)(peer->data))->rawName == "lim") {
					if (((PlayerInfo*)(peer->data))->rawName == "") return;
					// WE ARE GOOD TO GO

					if (world->items[x + (y * world->width)].foreground == 4802 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end()))
					{
						return;
					}

					if (tile == 32 && (find(world->accessed.begin(), world->accessed.end(), name) != world->accessed.end())) {
						return;
					}
					string offlinelist = "";
					string offname = "";
					int ischecked;
					int ischecked1;
					int ischecked2;
					for (std::vector<string>::const_iterator i = world->accessed.begin(); i != world->accessed.end(); ++i) {
						offname = *i;
						offlinelist += "\nadd_checkbox|isAccessed|" + offname + "|0|\n";

					}


					if (world->isPublic == true) {
						ischecked = 1;
					}
					else {
						ischecked = 0;
					}
					int noclap = 0;
					bool casin = world->isCasino;
					if (casin == true) {
						noclap = 1;
					}
					else {
						noclap = 0;
					}
					if (world->items[x + (y * world->width)].foreground == 4802)
					{
						int publicx = 0;
						if (world->isPublic == true)
						{
							publicx = 1;
						}
						else
						{
							publicx = 0;
						}
						string publik = to_string(publicx);

						int publicx1 = 0;
						if (world->allowMod == true)
						{
							publicx1 = 1;
						}
						else
						{
							publicx1 = 0;
						}
						string publik1 = to_string(publicx1);
						//testlol
						int rainbows = world->rainbows;
						int muted = world->silence;
						if (tile == 32) {
							if (world->accessed.size() == 0) {
								((PlayerInfo*)(peer->data))->lastPunchX = x;
								((PlayerInfo*)(peer->data))->lastPunchY = y;

								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + GetItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|netid|`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + publik + "|\nadd_checkbox|checkbox_noclip|Allow anyone to `2walktrough walls|" + publik1 + "|\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|" + to_string(world->disable_music) + "\nadd_text_input|tempo|Music BPM|" + to_string(world->tempo) + "|3|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|" + to_string(world->disable_music_render) + "|\nadd_checkbox|checkbox_rainbow|Enable Rainbows!|" + to_string(rainbows) + "|\nadd_checkbox|checkbox_muted|Silence, Peasants!|" + to_string(muted) + "|\nadd_text_input|minimum_entry_level|World Level: |1|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|getKey|Get World Key|noflags|0|0|\nend_dialog|lock_editz|Cancel|OK|"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;
							}

							else {
								((PlayerInfo*)(peer->data))->lastPunchX = x;
								((PlayerInfo*)(peer->data))->lastPunchY = y;
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + GetItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|" + offlinelist + "add_spacer|small|\nadd_player_picker||`wAdd``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + publik + "|\nadd_checkbox|checkbox_noclip|Allow anyone to `2walktrough walls|" + publik1 + "|\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|" + to_string(world->disable_music) + "\nadd_text_input|tempo|Music BPM|" + to_string(world->tempo) + "|3|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|" + to_string(world->disable_music_render) + "|\nadd_checkbox|checkbox_rainbow|Enable Rainbows!|" + to_string(rainbows) + "|\nadd_checkbox|checkbox_muted|Silence, Peasants!|" + to_string(muted) + "|\nadd_text_input|minimum_entry_level|World Level: |1|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|getKey|Get World Key|noflags|0|0|\nend_dialog|lock_editz|Cancel|OK|"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;
							}
						}
					}

				}

			}
		}
		if (tile == 5638) {
			bool aryra = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 5638)
				{
					aryra = true;
				}
			}
			if (aryra == false)
			{
				if (((PlayerInfo*)(peer->data))->rawName != world->owner) {
					Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`0You need to be world owner to place `9magplant`0!", 0, true);
					return;
				}
				else {
				}
			}
			else
			{
				Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`0You cant place more than one `9magplant`0!", 0, true);
				return;
			}
		}
		if (tile == 1790) {
			if (((PlayerInfo*)(peer->data))->rawName != world->owner) {
				Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`0You need to be world owner to place `#Legendary Wizard`0!", 0, true);
				return;
			}
			else if (getPlyersWorld(peer)->isPublic == true)
			{
				Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`0You cannot place `#Legendary Wizard `0In public worlds`0!", 0, true);
				return;
			}
		}
	}
	// WEATHERS STARTS HERE WEATHERS STARTS HERE WEATHERS STARTS HERE WEATHERS STARTS HERE WEATHERS STARTS HERE
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].foreground == 1490)
		{
			if (world->weather == 10)
			{
				world->weather = 0;
			}
			else
			{
				world->weather = 10;
			}
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
		}
	}
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].foreground == 934)
		{
			if (world->weather == 2)
			{
				world->weather = 0;
			}
			else
			{
				world->weather = 2;
			}
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
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 946)
			{
				if (world->weather == 3)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 3;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1490)
			{
				if (world->weather == 10)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 10;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 932)
			{
				if (world->weather == 4)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 4;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 984)
			{
				if (world->weather == 5)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 5;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1210)
			{
				if (world->weather == 8)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 8;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1364)
			{
				if (world->weather == 11)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 11;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1750)
			{
				if (world->weather == 15)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 15;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2046)
			{
				if (world->weather == 17)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 17;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2284)
			{
				if (world->weather == 18)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 18;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2744)
			{
				if (world->weather == 19)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 19;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3252)
			{
				if (world->weather == 20)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 20;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3446)
			{
				if (world->weather == 21)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 21;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3534)
			{
				if (world->weather == 22)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 22;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3694)
			{
				if (world->weather == 25)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 25;
				}
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
			}
		}
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1490)
			{
				if (world->weather == 10)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 10;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4242)
			{
				if (world->weather == 30)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 30;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4486)
			{
				if (world->weather == 31)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 31;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4776)
			{
				if (world->weather == 32)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 32;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4892)
			{
				if (world->weather == 33)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 33;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5000)
			{
				if (world->weather == 34)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 34;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5112)
			{
				if (world->weather == 35)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 35;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5654)
			{
				if (world->weather == 36)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 36;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5716)
			{
				if (world->weather == 37)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 37;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5958)
			{
				if (world->weather == 38)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 38;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 6854)
			{
				if (world->weather == 42)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 42;
				}
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
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 7644)
			{
				if (world->weather == 44)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 44;
				}
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
			}
		}
	}
	if (tile == 3764) {
		if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|\nadd_label_with_icon|small|`4Use atomic fireball on this world? Warning! This will delete all blocks placed in your world!``|left|3764|\nadd_spacer|\nadd_button|nukeyes|`4YES!|\nadd_button|`2Cancel|cancel|\nadd_quick_exit|"));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		}
		else {
			GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`#You must be world owner to use `4Atomic Fireball`#!"));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
	}
	if (tile == 6204) {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|\nadd_label_with_icon|small|`oAre You Sure You Want To Open `8Bronze `oChest`9?``|left|6204|\nadd_spacer|\nadd_button|openbronze|`2Open!|\nadd_quick_exit|"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	if (world->items[x + (y * world->width)].foreground == 2978) {
		// VEND UPDATE
		bool isPer = false;
		bool hasLocksInIt = true;
		TileExtra data;
		data.packetType = 0x5;
		data.characterState = 8;
		data.punchX = x;
		data.punchY = y;
		data.charStat = 13;
		data.blockid = 2978;
		data.backgroundid = world->items[x + (y * world->width)].background;
		data.visual = 0x00410000; //0x00210000
		if (hasLocksInIt == true) data.visual = 0x02410000;

		int n = 1796;
		string hex = "";
		{
			std::stringstream ss;
			ss << std::hex << n; // int decimal_value
			std::string res(ss.str());
			hex = res + "18";
		}
		int x;
		std::stringstream ss;
		ss << std::hex << hex;
		ss >> x;
		data.displayblock = x;

		int xes;
		{
			int wl = 2;
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
		raw = NULL; // prevent memory leak
		/*Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`oThis `wfeature `ois going to be available soon``", 0, true);*/
	}
	if (tile == 6202) {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|\nadd_label_with_icon|small|`oAre You Sure You Want To Open `sSilver `oChest`9?``|left|6202|\nadd_spacer|\nadd_button|opensilver|`2Open!|\nadd_quick_exit|"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	if (tile == 6200) {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|\nadd_label_with_icon|small|`oAre You Sure You Want To Open `9Gold `oChest`9?``|left|6200|\nadd_spacer|\nadd_button|opengold|`2Open!|\nadd_quick_exit|"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	if (tile == 7484) {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|\nadd_label_with_icon|small|`oAre You Sure You Want To Open `qWinter `oChest`9?``|left|7484|\nadd_spacer|\nadd_button|openwinter|`2Open!|\nadd_quick_exit|"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	if (tile == 7954) {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|\nadd_label_with_icon|small|`9Are You Sure You Want To Open `2Spring `oChest`9?``|left|7954|\nadd_spacer|\nadd_button|openspring|`2Open!|\nadd_quick_exit|"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	if (tile == 1404) {
		if (world->width != 100 && world->height != 60) {
			Player::OnTextOverlay(peer, "`@Door Mover Cant Be Used In Mutated Worlds`@!");
			return;
		}
		if (((PlayerInfo*)(peer->data))->rawName != world->owner) {
			Player::OnTextOverlay(peer, "`@You Must Be `2World-Owner `@To Use `wDoor Mover`@!");
			return;
		}
		if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
			if (world->items[x + (y * world->width)].foreground != 0) {
				Player::OnTextOverlay(peer, "`@There Is `4No `@Space For `wMain Door`@!");
				return;
			}
			else
			{
				for (int i = 0; i < world->width * world->height; i++)
				{
					if (i >= 5400) {
						world->items[i].foreground = 8;
					}
					else if (world->items[i].foreground == 6) {
						world->items[i].foreground = 0;
					}
					else if (world->items[i].foreground != 6) {
						world->items[x + (y * world->width)].foreground = 6;
					}
				}

				WorldInfo* wrld = getPlyersWorld(peer);
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						string act = ((PlayerInfo*)(peer->data))->currentWorld;
						sendPlayerLeave(currentPeer, (PlayerInfo*)(currentPeer->data));
						joinWorld(currentPeer, act, 0, 0);

						Player::OnTextOverlay(peer, "`^You Have `2Used `wDoor Mover`^!");
					}
				}
			}
			return;
		}
	}

	if (tile == 32) {
		return;
	}
	if (tile == 822) {
		if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->isCreator == true) {
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
			{
				return;
			}
			world->items[x + (y * world->width)].water = !world->items[x + (y * world->width)].water;
			UpdateVisualsForBlock(peer, true, x, y, world);
			return;
		}
	}
	if (tile == 3062)
	{
		if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->isCreator == true) {
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
			{
				return;
			}
			world->items[x + (y * world->width)].fire = !world->items[x + (y * world->width)].fire;
			UpdateVisualsForBlock(peer, true, x, y, world);
			return;
		}
	}
	if (tile == 3062)
	{
		world->items[x + (y * world->width)].fire = !world->items[x + (y * world->width)].fire;
		return;
	}
	if (tile == 1866)
	{
		world->items[x + (y * world->width)].glue = !world->items[x + (y * world->width)].glue;
		return;
	}
	ItemDefinition def;
	try {
		def = getItemDef(tile);
		if (def.clothType != ClothTypes::NONE) return;
	}
	catch (int e) {
		def.breakHits = 5;
		if (def.blockType = BlockTypes::SEED) return;
		def.blockType = BlockTypes::UNKNOWN;
#ifdef TOTAL_LOG
		cout << "Ugh, unsupported item " << tile << endl;
#endif
	}
	int test;
	if (((PlayerInfo*)(peer->data))->cloth_hand == 2952 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312 || ((PlayerInfo*)(peer->data))->cloth_hand == 9758 || ((PlayerInfo*)(peer->data))->cloth_hand == 7956 || ((PlayerInfo*)(peer->data))->cloth_hand == 9508 || ((PlayerInfo*)(peer->data))->cloth_hand == 9456 || ((PlayerInfo*)(peer->data))->cloth_hand == 3162 || ((PlayerInfo*)(peer->data))->cloth_hand == 2592 || ((PlayerInfo*)(peer->data))->cloth_hand == 10014) {
		test = 1;
	}
	else {
		test = getItemDef(world->items[x + (y * world->width)].foreground).breakHits * 2;
	}
	bool iscontains = false;
	SearchInventoryItem(peer, tile, 1, iscontains);
	if (!iscontains)
	{
		return;
	}
	iscontains = false;
	if (getItemDef(tile).blockType == BlockTypes::CONSUMABLE) return;
	if (tile == 544 || tile == 54600 || tile == 4520 || tile == 382 || tile == 3116 || tile == 4520 || tile == 1792 || tile == 5666 || tile == 732 || tile == 2994 || tile == 4368 || tile == 274 || tile == 276 || tile == 278) return;
	if (tile == 5708 || tile == 5709 || tile == 5780 || tile == 5781 || tile == 5782 || tile == 5783 || tile == 5784 || tile == 5785 || tile == 5710 || tile == 5711 || tile == 5786 || tile == 5787 || tile == 5788 || tile == 5789 || tile == 5790 || tile == 5791 || tile == 6146 || tile == 6147 || tile == 6148 || tile == 6149 || tile == 6150 || tile == 6151 || tile == 6152 || tile == 6153 || tile == 5670 || tile == 5671 || tile == 5798 || tile == 5799 || tile == 5800 || tile == 5801 || tile == 5802 || tile == 5803 || tile == 5668 || tile == 5669 || tile == 5792 || tile == 5793 || tile == 5794 || tile == 5795 || tile == 5796 || tile == 5797 || tile == 544 || tile == 54600 || tile == 4520 || tile == 382 || tile == 3116 || tile == 1792 || tile == 5666 || tile == 2994 || tile == 4368 || tile == 6204 || tile == 6202 || tile == 6200 || tile == 7484 || tile == 7954) return;
	if (tile == 1902 || tile == 1508 || tile == 428 || tile == 3764 || tile == 8428 || tile == 3808 || tile == 5132 || tile == 7166 || tile == 5078 || tile == 5080 || tile == 5082 || tile == 5084 || tile == 5126 || tile == 5128 || tile == 5130 || tile == 5144 || tile == 5146 || tile == 5148 || tile == 5150 || tile == 5162 || tile == 5164 || tile == 5166 || tile == 5168 || tile == 5180 || tile == 5182 || tile == 5184 || tile == 5186 || tile == 7168 || tile == 7170 || tile == 7172 || tile == 7174 || tile == 2480) return;
	if (tile == 9999 || tile == 1770 || tile == 4720 || tile == 980 || tile == 4882 || tile == 6392 || tile == 3212 || tile == 1832 || tile == 4742 || tile == 3496 || tile == 3270 || tile == 9212 || tile == 5134 || tile == 5152 || tile == 5170 || tile == 5188) return;
	if (tile == 6336)
	{
		return;
	}
	if (tile == 2410)
	{
		return;
	}
	if (tile == 4426)
	{
		return;
	}
	if (tile == 18) {
		if (world->items[x + (y * world->width)].background == 6864 && world->items[x + (y * world->width)].foreground == 0) return;
		if (world->items[x + (y * world->width)].background == 0 && world->items[x + (y * world->width)].foreground == 0) return;
		data.packetType = 0x8;
		data.plantingTree = 4;
		using namespace std::chrono;
		//if (world->items[x + (y*world->width)].foreground == 0) return;
		if ((duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() - world->items[x + (y * world->width)].breakTime >= 5000)
		{
			world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			world->items[x + (y * world->width)].breakLevel = 5; // TODO
		}
		else
			if (y < world->height && world->items[x + (y * world->width)].breakLevel + 5 >= def.breakHits * test) { // TODO
				data.packetType = 0x3;// 0xC; // 0xF // World::HandlePacketTileChangeRequest
				data.netID = causedBy;
				data.plantingTree = 18;
				data.punchX = x;
				data.punchY = y;
				world->items[x + (y * world->width)].breakLevel = 0;
				int hi = data.punchX * 32;
				int hi2 = data.punchY * 32;
				if (((PlayerInfo*)(peer->data))->cloth_hand == 9456) {
					std::vector<int> lists{ 0, 0, 0, 242, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
					srand(GetTickCount());
					int indexs = rand() % lists.size();
					int values = lists[indexs];
					if (values == 242)
					{
						Player::OnConsoleMessage(peer, "`9[POWER] `8The `@Ancient `9Power `^Dropped `2World Lock`^!");
						int droplocs = rand() % 18;
						int droploc = rand() % 18;
						DropItem(peer, -1, hi + droploc, hi2 + droplocs, 242, 1, 0);
						Player::OnParticleEffect(peer, 40, hi, hi2, 0);

					}
					else {
						Player::OnParticleEffect(peer, 73, hi, hi2, 0);
					}
				}
				if (((PlayerInfo*)(peer->data))->cloth_hand == 9716) {
					Player::OnParticleEffect(peer, 110, hi, hi2, 0);
				}
				if (((PlayerInfo*)(peer->data))->cloth_hand == 7956) {
					Player::OnParticleEffect(peer, 45, hi, hi2, 0);
				}
				if (((PlayerInfo*)(peer->data))->cloth_hand == 6312) {
					Player::OnParticleEffect(peer, 59, hi, hi2, 0);
				}
				if (((PlayerInfo*)(peer->data))->cloth_hand == 1874) {
					Player::OnParticleEffect(peer, 98, hi, hi2, 0);
				}
				if (((PlayerInfo*)(peer->data))->cloth_hand == 2952) {
					Player::OnParticleEffect(peer, 98, hi, hi2, 0);
				}
				if (((PlayerInfo*)(peer->data))->cloth_hand == 9758) {
					Player::OnParticleEffect(peer, 98, hi, hi2, 0);
				}
				//BLOKAI
				int crystalChange;
				if (world->items[x + (y * world->width)].foreground == 4762) {
					int hi = data.punchX * 32;
					int hi2 = data.punchY * 32;
					Player::OnParticleEffect(peer, 293, hi, hi2, 0);
				}
				else if (world->items[x + (y * world->width)].foreground == 3146)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4426 };
					int index = rand() % list.size(); // pick a random index
					int value = list[index];
					if (value == 4426) {
						bool success = true;
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 4426, 1, 0);
						if (((PlayerInfo*)(peer->data))->chatnotifications == true)
						{
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ The block dropped `4Ruby Shard`^!");
						}
						int hi = data.punchX * 32;
						int hi2 = data.punchY * 32;
						Player::OnParticleEffect(peer, 38, hi, hi2, 0);
					}
					else {
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 3948)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2410 };
					int index = rand() % list.size(); // pick a random index
					int value = list[index];
					if (value == 2410) {
						bool success = true;
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 2410, 1, 0);
						if (((PlayerInfo*)(peer->data))->chatnotifications == true)
						{
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ The block dropped `2Emerald Shard`^!");
						}
						int hi = data.punchX * 32;
						int hi2 = data.punchY * 32;
						Player::OnParticleEffect(peer, 39, hi, hi2, 0);
					}
					else {
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 7382)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9240 };
					int index = rand() % list.size(); // pick a random index
					int value = list[index];
					if (value == 9240) {
						bool success = true;
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9240, 1, 0);
						if (((PlayerInfo*)(peer->data))->chatnotifications == true)
						{
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ The block dropped `#Fragment Crystal`^!");
						}
						int hi = data.punchX * 32;
						int hi2 = data.punchY * 32;
						Player::OnParticleEffect(peer, 88, hi, hi2, 0);
					}
					else {
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 2478) {
					world->items[x + (y * world->width)].foreground = 0;
					int kuriPrizaDuot = rand() % 3 + 1;
					if (kuriPrizaDuot == 1)
					{
						int gemChance = rand() % 12000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int luck = rand() % 3 + 1;
						if (luck == 1) {
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^Your `1Luck `^Shines Away..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
						if (luck == 2) {
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^The `1Locke `9Gods `^Didn't Want To Play With You..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
						if (luck == 3) {
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You `9Starting `^To Feel `1Tired`^..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
					}
					if (kuriPrizaDuot == 3)
					{
						int itemuMas[62] = { 9416, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 9416, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 2478, 2478, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 2478, 1796, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328 };
						int ItemChance = 1;
						int randIndex = rand() % 62;
						int itemId = itemuMas[randIndex];
						GiveLockePrize(peer, itemId, ItemChance, 1);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 3402) {
					world->items[x + (y * world->width)].foreground = 0;
					int kuriPrizaDuot = rand() % 3 + 1;
					if (kuriPrizaDuot == 1)
					{
						int gemChance = rand() % 2000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						string crystaluMas[18] = { "gold", "sapphire", "sapphire", "sapphire","diamond", "diamond", "diamond", "diamond", "rubble", "opal", "opal", "gold", "amber", "emerald", "emerald", "emerald", "emerald", "gold" };
						int crystalChance = rand() % 3;
						int randIndex = rand() % 18;
						string crystalName = crystaluMas[randIndex];
						GiveChestPrizeCrystal(peer, crystalName, crystalChance);
					}
					if (kuriPrizaDuot == 3)
					{
						int itemuMas[62] = { 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 9408, 9408, 242, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1458, 242, 242, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
						int ItemChance = 1;
						int randIndex = rand() % 62;
						int itemId = itemuMas[randIndex];
						GiveGBCPrize(peer, itemId, ItemChance, 1);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 192 || world->items[x + (y * world->width)].foreground == 1004)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9490 };
					int index = rand() % list.size();
					int value = list[index];
					if (value == 9490) {
						bool success = true;
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9490, 1, 0);
						if (((PlayerInfo*)(peer->data))->chatnotifications == true)
						{
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ The block dropped `2Tree `9Block`^!");
						}
						int hi = data.punchX * 32;
						int hi2 = data.punchY * 32;
						Player::OnParticleEffect(peer, 88, hi, hi2, 0);
					}
					else {
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 2)
				{
					if (((PlayerInfo*)(peer->data))->cloth_back == 9506)
					{
						std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7382 };
						int index = rand() % list.size();
						int value = list[index];
						if (value == 7382) {
							bool success = true;
							srand(GetTickCount());
							int droploc = rand() % 18;
							int droplocs = rand() % 18;
							DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 7382, 1, 0);
							if (((PlayerInfo*)(peer->data))->chatnotifications == true)
							{
								Player::OnConsoleMessage(peer, "`9[LOGS]`^ The block dropped `bOnyx `9Block`^!");
							}
							int hi = data.punchX * 32;
							int hi2 = data.punchY * 32;
							Player::OnParticleEffect(peer, 88, hi, hi2, 0);
						}
						else {
						}
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 3948 || world->items[x + (y * world->width)].foreground == 3606)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8226 };
					int index = rand() % list.size();
					int value = list[index];
					if (value == 8226) {
						bool success = true;
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 8226, 1, 0);
						if (((PlayerInfo*)(peer->data))->chatnotifications == true)
						{
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ The block dropped `eXP `9Block`^!");
						}
						int hi = data.punchX * 32;
						int hi2 = data.punchY * 32;
						Player::OnParticleEffect(peer, 88, hi, hi2, 0);
					}
					else {
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 7382) {
					int hi = data.punchX * 32;
					int hi2 = data.punchY * 32;
					Player::OnParticleEffect(peer, 118, hi, hi2, 0);
				}
				else if (((PlayerInfo*)(peer->data))->cloth_hand == 8452) {
					int hi = data.punchX * 32;
					int hi2 = data.punchY * 32;
					Player::OnParticleEffect(peer, 151, hi, hi2, 0);
				}
				else if (((PlayerInfo*)(peer->data))->cloth_hand == 9058) {
					int hi = data.punchX * 32;
					int hi2 = data.punchY * 32;
					Player::OnParticleEffect(peer, 264, hi, hi2, 0);
				}
				else if (((PlayerInfo*)(peer->data))->cloth_hand == 5480) {
					int hi = data.punchX * 32;
					int hi2 = data.punchY * 32;
					Player::OnParticleEffect(peer, 30, hi, hi2, 0);
				}
				if (world->items[x + (y * world->width)].foreground != 0)
				{
					if (world->items[x + (y * world->width)].foreground == 5638)
					{
						int magplantgems = 0;
						ifstream fileStream213("magplant/gems/" + ((PlayerInfo*)(peer->data))->currentWorld + ".txt");
						fileStream213 >> magplantgems;
						fileStream213.close();
						if (magplantgems > 0)
						{
							Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`wEmpty this magplant, before breaking it!", 0, true);
							return;
						}
						remove(("magplant/gems/" + ((PlayerInfo*)(peer->data))->currentWorld + ".txt").c_str());
						Player::OnConsoleMessage(peer, "You received your magplant back to inventory!");
						bool success = true;
						SaveItemMoreTimes(5638, 1, peer, success);
					}
					bool aryra = false;
					for (int i = 0; i < world->width * world->height; i++)
					{
						if (world->items[i].foreground == 583838)
						{
							int magplantstatus = 0;
							ifstream fileStream213("magplant/status/" + ((PlayerInfo*)(peer->data))->currentWorld + ".txt");
							fileStream213 >> magplantstatus;
							fileStream213.close();
							if (magplantstatus == 1)
							{
								aryra = true;
							}
						}
					}
					if (aryra == true)
					{
						int current = 0;
						ifstream fileStream213("magplant/gems/" + ((PlayerInfo*)(peer->data))->currentWorld + ".txt");
						fileStream213 >> current;
						fileStream213.close();
						int maxdropgem = 10;
						int val = rand() % maxdropgem;
						int randomsudailol = val + current;
						std::ofstream outfile("magplant/gems/" + ((PlayerInfo*)(peer->data))->currentWorld + ".txt");
						outfile << randomsudailol;
						outfile.close();
					}
					else
					{
						int iditem = ((PlayerInfo*)(peer->data))->cloth_ances;
						int valgem;
						if (world->items[x + (y * world->width)].foreground == 120)
						{
							srand(GetTickCount());
							int droploc = rand() % 18;
							int droplocs = rand() % 18;
							int itemid = rand() % maxItems;
							string name = getItemDef(itemid).name;
							if (itemid % 2 == 0) {
								Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "The power of the Mystery Blocks droped " + name + "!", 0, true);
								DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, itemid, 1, 0);
								int hi = data.punchX * 32;
								int hi2 = data.punchY * 32;
								ENetPeer* currentPeer;
								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;
									if (isHere(peer, currentPeer)) {
										Player::OnParticleEffect(currentPeer, 184, hi, hi2, 0);
									}
								}
							}
							else {
								itemid += 1;
								string name321 = getItemDef(itemid).name;
								Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "The power of the Mystery Blocks dropped " + name321 + "!", 0, true);
								DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, itemid, 1, 0);
								int hi = data.punchX * 32;
								int hi2 = data.punchY * 32;
								ENetPeer* currentPeer;
								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
										continue;
									if (isHere(peer, currentPeer)) {
										Player::OnParticleEffect(currentPeer, 184, hi, hi2, 0);
									}
								}
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 4762) {
							world->items[x + (y * world->width)].foreground = 0;
							if (((PlayerInfo*)(peer->data))->skill == "Farmer")
							{
								valgem = rand() % 300;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
								givequestkatanastep2xp(peer, 2);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Boosted The `4Gems`^!");
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `#Amethyst `9Block`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							else {
								valgem = rand() % 200;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
								givequestkatanastep2xp(peer, 2);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `#Amethyst `9Block`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							if (((PlayerInfo*)(peer->data))->guild != "")
							{
								int currentgpoints = 0;
								ifstream guildstream1("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
								guildstream1 >> currentgpoints;
								guildstream1.close();
								if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
								{
									int newgpoints = currentgpoints + 2;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								else {
									int newgpoints = currentgpoints + 1;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								// M CONTRIBUTION
								int currentplayercontribution = 0;
								namespace fs = std::experimental::filesystem;
								if (!fs::is_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild) || !fs::exists("guildrewards / contribution / " + ((PlayerInfo*)(peer->data))->guild)) {
									fs::create_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild);
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 2;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 1;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								else {
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 2;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 1;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@2 `^Guild Points!");
									}
									else {
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@1 `^Guild Points!");
									}
								}
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 7382) {
							world->items[x + (y * world->width)].foreground = 0;
							if (((PlayerInfo*)(peer->data))->skill == "Farmer")
							{
								valgem = rand() % 400;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
								givequestkatanastep2xp(peer, 2);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Boosted The `4Gems`^!");
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `bOnyx `9Block`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							else {
								valgem = rand() % 300;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
								givequestkatanastep2xp(peer, 2);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `bOnyx `9Block`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							
							if (((PlayerInfo*)(peer->data))->guild != "")
							{
								int currentgpoints = 0;
								ifstream guildstream1("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
								guildstream1 >> currentgpoints;
								guildstream1.close();
								if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
								{
									int newgpoints = currentgpoints + 4;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								else {
									int newgpoints = currentgpoints + 2;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								// M CONTRIBUTION
								int currentplayercontribution = 0;
								namespace fs = std::experimental::filesystem;
								if (!fs::is_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild) || !fs::exists("guildrewards / contribution / " + ((PlayerInfo*)(peer->data))->guild)) {
									fs::create_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild);
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 4;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 2;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								else {
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 4;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 2;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@4 `^Guild Points!");
									}
									else {
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@2 `^Guild Points!");
									}
								}
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 4174) {
							std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9476 };
							int index = rand() % list.size();
							int value = list[index];
							if (value == 9476) {
								bool success = true;
								srand(GetTickCount());
								int droploc = rand() % 18;
								int droplocs = rand() % 18;
								DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9476, 1, 0);
								Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`wThe `oMystery Box `wDropped `4Hell Wings`w!", 0, true);
								int hi = data.punchX * 32;
								int hi2 = data.punchY * 32;
								Player::OnParticleEffect(peer, 88, hi, hi2, 0);
							}
							else {
								valgem = rand() % 900000;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 30;
								givequestkatanastep2xp(peer, 30);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `8Mystery Box`^!");
								}
								Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, true);
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 3606) {
							world->items[x + (y * world->width)].foreground = 0;
							if (((PlayerInfo*)(peer->data))->skill == "Farmer")
							{
								valgem = rand() % 1300;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 10;
								givequestkatanastep2xp(peer, 10);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Boosted The `4Gems`^!");
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `1Diamond `9Stone`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							else {
								valgem = rand() % 1100;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 10;
								givequestkatanastep2xp(peer, 10);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `1Diamond `9Stone`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							if (((PlayerInfo*)(peer->data))->guild != "")
							{
								int currentgpoints = 0;
								ifstream guildstream1("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
								guildstream1 >> currentgpoints;
								guildstream1.close();
								if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
								{
									int newgpoints = currentgpoints + 10;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								else {
									int newgpoints = currentgpoints + 5;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								// M CONTRIBUTION
								int currentplayercontribution = 0;
								namespace fs = std::experimental::filesystem;
								if (!fs::is_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild) || !fs::exists("guildrewards / contribution / " + ((PlayerInfo*)(peer->data))->guild)) {
									fs::create_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild);
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 10;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 5;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								else {
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 10;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 5;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@10 `^Guild Points!");
									}
									else {
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@5 `^Guild Points!");
									}
								}
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 3146) {
							world->items[x + (y * world->width)].foreground = 0;
							if (((PlayerInfo*)(peer->data))->skill == "Farmer")
							{
								valgem = rand() % 2400;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 10;
								givequestkatanastep2xp(peer, 10);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Boosted The `4Gems`^!");
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `#Rainbow Crystal Block`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							else {
								valgem = rand() % 2200;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 10;
								givequestkatanastep2xp(peer, 10);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `#Rainbow Crystal Block`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							if (((PlayerInfo*)(peer->data))->guild != "")
							{
								int currentgpoints = 0;
								ifstream guildstream1("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
								guildstream1 >> currentgpoints;
								guildstream1.close();
								if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
								{
									int newgpoints = currentgpoints + 14;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								else {
									int newgpoints = currentgpoints + 7;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								// M CONTRIBUTION
								int currentplayercontribution = 0;
								namespace fs = std::experimental::filesystem;
								if (!fs::is_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild) || !fs::exists("guildrewards / contribution / " + ((PlayerInfo*)(peer->data))->guild)) {
									fs::create_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild);
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 14;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 7;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								else {
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 14;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 7;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@14 `^Guild Points!");
									}
									else {
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@7 `^Guild Points!");
									}
								}
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 3948) {
							world->items[x + (y * world->width)].foreground = 0;
							if (((PlayerInfo*)(peer->data))->skill == "Farmer")
							{
								valgem = rand() % 800;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 5;
								givequestkatanastep2xp(peer, 5);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Boosted The `4Gems`^!");
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `2Amber `9Block`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							else {
								valgem = rand() % 600;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 5;
								givequestkatanastep2xp(peer, 5);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `2Amber `9Block`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							if (((PlayerInfo*)(peer->data))->guild != "")
							{
								int currentgpoints = 0;
								ifstream guildstream1("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
								guildstream1 >> currentgpoints;
								guildstream1.close();
								if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
								{
									int newgpoints = currentgpoints + 6;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								else {
									int newgpoints = currentgpoints + 3;
									ofstream guildstream3("guildrewards/guildpoints/" + ((PlayerInfo*)(peer->data))->guild + ".txt");
									guildstream3 << newgpoints;
									guildstream3.close();
								}
								// M CONTRIBUTION
								int currentplayercontribution = 0;
								namespace fs = std::experimental::filesystem;
								if (!fs::is_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild) || !fs::exists("guildrewards / contribution / " + ((PlayerInfo*)(peer->data))->guild)) {
									fs::create_directory("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild);
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 6;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 3;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								else {
									ifstream mcontr("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									mcontr >> currentplayercontribution;
									mcontr.close();
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										int newcontr = currentplayercontribution + 6;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
									else {
										int newcontr = currentplayercontribution + 3;
										ofstream savecon("guildrewards/contribution/" + ((PlayerInfo*)(peer->data))->guild + "/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										savecon << newcontr;
										savecon.close();
									}
								}
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									if (((PlayerInfo*)(peer->data))->cloth_hand == 9508)
									{
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@6 `^Guild Points!");
									}
									else {
										Player::OnConsoleMessage(peer, "`8[GPOINTS] `^You have obtained `@3 `^Guild Points!");
									}
								}
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 7628) {
							std::vector<int> lists{ 1, 2, 3, 4 };
							srand(GetTickCount());
							int indexs = rand() % lists.size();
							int values = lists[indexs];
							if (values == 1)
							{
								std::vector<int> lists{ 3, 3, 3, 6, 6, 6, 5, 5, 5 };
								srand(GetTickCount());
								int indexs = rand() % lists.size();
								int droplocs = rand() % 18;
								int droploc = rand() % 18;
								int values = lists[indexs];
								DropItem(peer, -1, hi + droploc, hi2 + droplocs, 1486, values, 0);
							}
							if (values == 2)
							{
								std::vector<int> lists{ 30, 30, 30, 60, 60, 60, 50, 50, 50 };
								srand(GetTickCount());
								int indexs = rand() % lists.size();
								int droplocs = rand() % 18;
								int droploc = rand() % 18;
								int values = lists[indexs];
								DropItem(peer, -1, hi + droploc, hi2 + droplocs, 242, values, 0);
							}
							if (values == 3)
							{
								srand(GetTickCount());
								int droplocs = rand() % 18;
								int droploc = rand() % 18;
								DropItem(peer, -1, hi + droploc, hi2 + droplocs, 1796, 1, 0);
							}
							if (values == 4)
							{
								std::vector<int> lists{ 30, 30, 30, 60, 60, 60, 50, 50, 50 };
								srand(GetTickCount());
								int indexs = rand() % lists.size();
								int droplocs = rand() % 18;
								int droploc = rand() % 18;
								int values = lists[indexs];
								DropItem(peer, -1, hi + droploc, hi2 + droplocs, 9440, values, 0);
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 9442) {
							string crystaluMas[26] = { "gold", "sapphire", "sapphire", "diamond", "rubble", "sapphire", "rubble", "rubble", "opal", "opal", "opal", "opal", "gold", "emerald", "amber", "sapphire", "amber", "sapphire", "amber", "amber", "amber", "emerald", "gold", "gold", "gold", "amber" };
							int crystalChance = rand() % 3;
							int randIndex = rand() % 26;
							string crystalName = crystaluMas[randIndex];
							GiveChestPrizeCrystal(peer, crystalName, crystalChance);
							int hi = data.punchX * 32;
							int hi2 = data.punchY * 32;
							Player::OnParticleEffect(peer, 73, hi, hi2, 0);
						}
						else if (world->items[x + (y * world->width)].foreground == 7960) {
							valgem = rand() % 9;
							if (valgem > 0) {
								if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 8;
									givequestkatanastep2xp(peer, 8);
								}
								else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 12;
									givequestkatanastep2xp(peer, 12);
								}
								else {
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
									givequestkatanastep2xp(peer, 4);
								}
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `@" + std::to_string(valgem) + " `4Fire `9Fragments`^!");
								}
								AddPlayerFragmentFire(peer, valgem);
							}
							else
							{
								Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`^Your `2Luck `^Shines away...", 0, true);
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 9440) {
							std::vector<int> list{ 112 };
							std::vector<int> lists{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
							srand(GetTickCount());
							int indexs = rand() % lists.size();
							int droplocs = rand() % 18;
							int droploc = rand() % 18;
							int droplocs1 = rand() % 18;
							int droploc1 = rand() % 18;
							int droplocs3 = rand() % 18;
							int droploc3 = rand() % 18;
							int values = lists[indexs];
							std::vector<int> lists1{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
							int indexs1 = rand() % lists1.size();
							int values1 = lists[indexs1];
							std::vector<int> lists3{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
							int indexs3 = rand() % lists3.size();
							int values3 = lists[indexs3];
							DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
							DropItem(peer, -1, hi + droploc1, hi2 + droplocs1, 112, values1, 0);
							DropItem(peer, -1, hi + droploc3, hi2 + droplocs3, 112, values3, 0);
						}
						else if (world->items[x + (y * world->width)].foreground == 9240) {
							world->items[x + (y * world->width)].foreground = 0;
							if (((PlayerInfo*)(peer->data))->skill == "Farmer")
							{
								valgem = rand() % 1500;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
								givequestkatanastep2xp(peer, 3);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Boosted The `4Gems`^!");
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `#Fragment Crystal`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
							else {
								valgem = rand() % 1200;
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
								givequestkatanastep2xp(peer, 3);
								std::ifstream ifs("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								std::string content((std::istreambuf_iterator<char>(ifs)),
									(std::istreambuf_iterator<char>()));
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `9" + std::to_string(valgem) + " `2Gems `^from the `#Fragment Crystal`^!");
								}
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet3);
								delete p3.data;
								int gembux = atoi(content.c_str());
								int fingembux = gembux + valgem;
								ofstream myfile;
								myfile.open("gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
								myfile << fingembux;
								myfile.close();
								int gemcalc = gembux + valgem;
								GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
								ENetPacket* packetpp = enet_packet_create(pp.data,
									pp.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packetpp);
								delete pp.data;
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 8226) {
							world->items[x + (y * world->width)].foreground = 0;
							std::vector<int> list{ 112 };
							std::vector<int> lists{ 50, 100, 50, 100, 50, 100, 50, 100 };
							srand(GetTickCount());
							int indexs = rand() % lists.size();
							int droploc = rand() % 18; // pick a random index
							int droplocs = rand() % 18;
							int values = lists[indexs];
							DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 112, values, 0);
							std::vector<int> listsss{ 5, 10, 15, 50, 40, 25, 30, 20 };
							srand(GetTickCount());
							int indexsss = rand() % listsss.size();
							int xpvalue = listsss[indexsss];
							Player::OnConsoleMessage(peer, "`9[LOOT] `^You have obtained `@" + std::to_string(xpvalue) + " `!Experience`^!");
							((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + xpvalue;
							givequestkatanastep2xp(peer, xpvalue);
						}
						else if (world->items[x + (y * world->width)].foreground == 8) {
							world->items[x + (y * world->width)].foreground = 0;
							valgem = rand() % 6;
							if (valgem > 0) {
								if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
									givequestkatanastep2xp(peer, 2);
								}
								else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
									givequestkatanastep2xp(peer, 3);
								}
								else {
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
									givequestkatanastep2xp(peer, 1);
								}
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[LOGS]`^ You found `@" + std::to_string(valgem) + " `bDark `9Fragments`^!");
								}
								AddPlayerFragmentDark(peer, valgem);
							}
						}
						else if (world->items[x + (y * world->width)].foreground == 758) {}
						else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							for (int i = 0; i < world->width * world->height; i++)
							{
								if (world->items[i].foreground == 1790) {
									Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "`oTake all `cUntradeable `oBlocks, before breaking The `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`o!", 0, true);
									return;
								}
							}
							updateworldremove(peer);
							bool success = true;
							WorldInfo* world = getPlyersWorld(peer);
							string nameworld = world->name;
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + " `^Back to your `#Inventory`^!");
							SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success);
							ENetPeer* currentPeer;
							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (isHere(peer, currentPeer))
								{
									Player::OnConsoleMessage(currentPeer, "`5[`w" + nameworld + " `ohas had its `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + " `oremoved!`5]");
									string text = "action|play_sfx\nfile|audio/fireball.wav\ndelayMS|0\n";
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
								}
							}
							world->owner = "";
							world->Displayowner = "";
							world->worldaccess.clear();
							world->pIsVip = false;
							world->pIsMod = false;
							world->pIsDev = false;
							world->pIsPlay = false;
							world->isPublic = false;
							((PlayerInfo*)(peer->data))->worldsowned.erase(std::remove(((PlayerInfo*)(peer->data))->worldsowned.begin(), ((PlayerInfo*)(peer->data))->worldsowned.end(), nameworld), ((PlayerInfo*)(peer->data))->worldsowned.end());
							world->items[x + (y * world->width)].foreground = 0;
						}
						else if (world->items[x + (y * world->width)].foreground == 9488) {
							bool success = true;
							SaveItemMoreTimes(9488, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `9WOTW Trophy `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 4428) {
							bool success = true;
							SaveItemMoreTimes(4428, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `4Ruby Lock `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 2408) {
							bool success = true;
							SaveItemMoreTimes(2408, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `2Emerald Lock `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 9504) {
							bool success = true;
							SaveItemMoreTimes(9504, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `4Ban Lock `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 6946) {
							bool success = true;
							SaveItemMoreTimes(6946, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `5WGM `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 9170) {
							bool success = true;
							SaveItemMoreTimes(9170, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `9Magic Machine `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 6950) {
							bool success = true;
							SaveItemMoreTimes(6950, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `#Gem Storage `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 1008) {
							bool success = true;
							SaveItemMoreTimes(1008, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `eATM Machine `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 1636) {
							bool success = true;
							SaveItemMoreTimes(1636, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `#Unicorn `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 1790) {
							bool success = true;
							SaveItemMoreTimes(1790, 1, peer, success);
							Player::OnConsoleMessage(peer, "`9[LOGS]`^ You have received your `#Legendary Wizard `^Back to your `#Inventory`^!");
						}
						else if (world->items[x + (y * world->width)].foreground == 2946)
						{
							if (((PlayerInfo*)(peer->data))->rawName == world->owner || world->owner == "")
							{
								string world = ((PlayerInfo*)(peer->data))->currentWorld;
								((PlayerInfo*)(peer->data))->blockx = x;
								((PlayerInfo*)(peer->data))->blocky = y;
								int squaresign = ((PlayerInfo*)(peer->data))->blockx + (((PlayerInfo*)(peer->data))->blocky * 100);
								string currentworld = world + "X" + std::to_string(squaresign);
								bool displayexist = std::experimental::filesystem::exists("display/" + currentworld + ".txt");
								if (displayexist) {
									int item;
									ifstream getdisplay("display/" + currentworld + ".txt");
									getdisplay >> item;
									getdisplay.close();
									bool success = true;
									SaveItemMoreTimes(item, 1, peer, success);
									Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "You picked up 1 " + getItemDef(item).name + ".", 0, true);
									remove(("display/" + currentworld + ".txt").c_str());
								}
							}
							else {
								Player::OnTalkBubble(peer, ((PlayerInfo*)(peer->data))->netID, "Only the block's owner can break it!", 0, true);
								return;
							}
						}
						else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SIGN)
						{
							string world = ((PlayerInfo*)(peer->data))->currentWorld;

							if (std::experimental::filesystem::exists("signs/" + world + "X" + to_string(y) + to_string(x) + ".txt"))
							{
								const int result = remove(("signs/" + world + "X" + to_string(y) + to_string(x) + ".txt").c_str());
								if (result != 0) {
									cout << "error removing sign " << world + to_string(x) + to_string(y) << endl;
								}
							}
						}
						else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity != 999)
						{
						if (((PlayerInfo*)(peer->data))->cloth_feet == 8834) {
							if (iditem == 7166 || iditem == 5078 || iditem == 5080 || iditem == 5082 || iditem == 5084 || iditem == 5134 || iditem == 5126 || iditem == 5128 || iditem == 5130 || iditem == 5132 || iditem == 5152 || iditem == 5144 || iditem == 5146 || iditem == 5148 || iditem == 5150 || iditem == 5170 || iditem == 5162 || iditem == 5164 || iditem == 5166 || iditem == 5168 || iditem == 5188 || iditem == 5180 || iditem == 5182 || iditem == 5184 || iditem == 5186 || iditem == 9212 || iditem == 7168 || iditem == 7170 || iditem == 7172 || iditem == 7174)
							{
								if (((PlayerInfo*)(peer->data))->skill == "Farmer")
								{
									std::vector<int> list{ 112 };
									std::vector<int> lists{ 50, 10, 50, 10, 50, 10, 10, 50, 10, 10 };
									srand(GetTickCount());
									int indexs = rand() % lists.size(); // pick a random index
									int droplocs = rand() % 18;
									int droploc = rand() % 18;
									int values = lists[indexs];
									DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
									if (values == 10 || values == 50)
									{
										Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Dropped `2More `4Gems`^!");
										Player::OnConsoleMessage(peer, "`2[BONUS] `#TK69 `^And `@Ancestral `^Dropped `2More `4Gems`^!");
									}
								}
								else {
									std::vector<int> list{ 112 };
									std::vector<int> lists{ 5, 10, 10, 10, 50, 10, 10, 10, 10, 10 };
									srand(GetTickCount());
									int indexs = rand() % lists.size(); // pick a random index
									int droplocs = rand() % 18;
									int droploc = rand() % 18;
									int values = lists[indexs];
									DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
									if (values == 10 || values == 50)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `#TK69 `^And `@Ancestral `^Dropped `2More `4Gems`^!");
									}
								}
							}
							else {
								if (((PlayerInfo*)(peer->data))->skill == "Farmer")
								{
									std::vector<int> list{ 112 };
									std::vector<int> lists{ 10, 5, 10, 5, 10, 5, 10, 50, 10, 10, 10 };
									srand(GetTickCount());
									int indexs = rand() % lists.size(); // pick a random index
									int droplocs = rand() % 18;
									int droploc = rand() % 18;
									int values = lists[indexs];
									DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
									if (values == 10 || values == 50)
									{
										Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Dropped `2More `4Gems`^!");

										Player::OnConsoleMessage(peer, "`2[BONUS] `#TK69 `^Dropped `2More `4Gems`^!");
									}
								}
								else {
									std::vector<int> list{ 112 };
									std::vector<int> lists{ 1, 5, 5, 5, 5, 10, 10, 10, 5, 10, 10 };
									srand(GetTickCount());
									int indexs = rand() % lists.size(); // pick a random index
									int droplocs = rand() % 18;
									int droploc = rand() % 18;
									int values = lists[indexs];
									DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
									if (values == 10 || values == 50)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `#TK69 `^Dropped `2More `4Gems`^!");
									}
								}
							}
						}
						else if (((PlayerInfo*)(peer->data))->cloth_hand == 7912) {
							if (iditem == 7166 || iditem == 5078 || iditem == 5080 || iditem == 5082 || iditem == 5084 || iditem == 5134 || iditem == 5126 || iditem == 5128 || iditem == 5130 || iditem == 5132 || iditem == 5152 || iditem == 5144 || iditem == 5146 || iditem == 5148 || iditem == 5150 || iditem == 5170 || iditem == 5162 || iditem == 5164 || iditem == 5166 || iditem == 5168 || iditem == 5188 || iditem == 5180 || iditem == 5182 || iditem == 5184 || iditem == 5186 || iditem == 9212 || iditem == 7168 || iditem == 7170 || iditem == 7172 || iditem == 7174)
							{
								if (((PlayerInfo*)(peer->data))->skill == "Farmer")
								{
									std::vector<int> list{ 112 };
									std::vector<int> lists{ 50, 10, 10, 10, 5, 10, 10, 10, 10, 10 };
									srand(GetTickCount());
									int indexs = rand() % lists.size(); // pick a random index
									int droplocs = rand() % 18;
									int droploc = rand() % 18;
									int values = lists[indexs];
									DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
									if (values == 10 || values == 50)
									{
										Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Dropped `2More `4Gems`^!");

										Player::OnConsoleMessage(peer, "`2[BONUS] `!War Hammers `^And `@Ancestral `^Dropped `2More `4Gems`^!");
									}
								}
								else {
									std::vector<int> list{ 112 };
									std::vector<int> lists{ 5, 10, 5, 10, 5, 10, 10, 10, 10, 10 };
									srand(GetTickCount());
									int indexs = rand() % lists.size(); // pick a random index
									int droplocs = rand() % 18;
									int droploc = rand() % 18;
									int values = lists[indexs];
									DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
									if (values == 10 || values == 50)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `!War Hammers `^And `@Ancestral `^Dropped `2More `4Gems`^!");
									}
								}
							}
							else {
								if (((PlayerInfo*)(peer->data))->skill == "Farmer")
								{
									std::vector<int> list{ 112 };
									std::vector<int> lists{ 10, 1, 10, 5, 10, 10, 10, 5, 10, 5 };
									srand(GetTickCount());
									int indexs = rand() % lists.size(); // pick a random index
									int droplocs = rand() % 18;
									int droploc = rand() % 18;
									int values = lists[indexs];
									DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
									if (values == 10 || values == 50)
									{
										Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Dropped `2More `4Gems`^!");

										Player::OnConsoleMessage(peer, "`2[BONUS] `!War Hammers `^Dropped `2More `4Gems`^!");
									}
								}
								else {
									std::vector<int> list{ 112 };
									std::vector<int> lists{ 1, 1, 1, 5, 5, 10, 10, 5, 10, 5 };
									srand(GetTickCount());
									int indexs = rand() % lists.size(); // pick a random index
									int droplocs = rand() % 18;
									int droploc = rand() % 18;
									int values = lists[indexs];
									DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
									if (values == 10 || values == 50)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `!War Hammers `^Dropped `2More `4Gems`^!");
									}
								}
							}
						}
						else if (iditem == 7166 || iditem == 5078 || iditem == 5080 || iditem == 5082 || iditem == 5084 || iditem == 5134 || iditem == 5126 || iditem == 5128 || iditem == 5130 || iditem == 5132 || iditem == 5152 || iditem == 5144 || iditem == 5146 || iditem == 5148 || iditem == 5150 || iditem == 5170 || iditem == 5162 || iditem == 5164 || iditem == 5166 || iditem == 5168 || iditem == 5188 || iditem == 5180 || iditem == 5182 || iditem == 5184 || iditem == 5186 || iditem == 9212 || iditem == 7168 || iditem == 7170 || iditem == 7172 || iditem == 7174)
						{
							if (((PlayerInfo*)(peer->data))->skill == "Farmer")
							{
								std::vector<int> list{ 112 };
								std::vector<int> lists{ 5, 10, 50, 10, 10, 10, 10, 10, 10, 10 };
								srand(GetTickCount());
								int indexs = rand() % lists.size(); // pick a random index
								int droplocs = rand() % 18;
								int droploc = rand() % 18;
								int values = lists[indexs];
								DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
								if (values == 10 || values == 50)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Dropped `2More `4Gems`^!");

									Player::OnConsoleMessage(peer, "`2[BONUS] `@Ancestral `^Dropped `2More `4Gems`^!");
								}
							}
							else {
								std::vector<int> list{ 112 };
								std::vector<int> lists{ 5, 5, 5, 10, 5, 10, 10, 10, 10, 10 };
								srand(GetTickCount());
								int indexs = rand() % lists.size(); // pick a random index
								int droplocs = rand() % 18;
								int droploc = rand() % 18;
								int values = lists[indexs];
								DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
								if (values == 10 || values == 50)
								{
									Player::OnConsoleMessage(peer, "`2[BONUS] `@Ancestral `^Dropped `2More `4Gems`^!");
								}
							}
						}
						else {
							if (((PlayerInfo*)(peer->data))->skill == "Farmer")
							{
								std::vector<int> list{ 112 };
								std::vector<int> lists{ 5, 5, 5, 5, 5, 10, 10, 10 };
								srand(GetTickCount());
								int indexs = rand() % lists.size(); // pick a random index
								int droplocs = rand() % 18;
								int droploc = rand() % 18;
								int values = lists[indexs];
								DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 112, values, 0);
								if (values == 10)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Farmer Skill `^Dropped `2More `4Gems`^!");
								}
							}
							else {
								WorldInfo* worldInfo = getPlyersWorld(peer);
								int strtointx = data.punchX;
								int strtointy = data.punchY;
								int x1 = 0;
								int y1 = 0;
								int xSize = worldInfo->width;
								int ySize = worldInfo->height;
								for (int i = 0; i < xSize; i++) {
									for (int j = 0; j < ySize; j++) {
										int squaresign = i + (j * 100);
										x1 = (strtointx % worldInfo->width) * 32;
										y1 = (strtointy % ySize) * 32;
									}
								}
								int brokentileseed = brokentile + 1;
								std::vector<int> list{ 112, 112, 112, 112, 112, 112, brokentile };
								std::vector<int> listseed{ 112, 112, 112, brokentileseed };
								int index = rand() % list.size(); // pick a random index
								int indexseed = rand() % listseed.size(); // pick a random index
								int value = list[index];
								int valueseed = listseed[indexseed];
								int xx = ((PlayerInfo*)(peer->data))->x;
								int netid = -1;
								int yy = ((PlayerInfo*)(peer->data))->y;
								int randomgem = rand() % 10;
								int randomgem2 = rand() % 20;
								int randomgem3 = rand() % 20;
								int randomgem4 = rand() % 30;
								int randomgem5 = rand() % 50;
								int randomgem6 = rand() % 20;
								int x2 = x1 + (32 * -0.1);
								int x22 = x1 + (32 * -0.2);
								int y2 = x1 + (32 * 0.1);
								int y22 = x1 + (32 * 0.2);
								if (getItemDef(brokentile).rarity != 999)
								{
									if (value == 112)
									{
										if (getItemDef(brokentile).rarity < 1)
										{
											DropItem(
												peer, -1,
												x * 32 + (rand() % 16),
												y * 32 + (rand() % 16),
												112,
												1, 0);
											for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
										}
										else if (getItemDef(brokentile).rarity < 5)
										{
											DropItem(
												peer, -1,
												x * 32 + (rand() % 16),
												y * 32 + (rand() % 16),
												112,
												1, 0);
											for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
										}
										else if (getItemDef(brokentile).rarity < 10)
										{
											DropItem(
												peer, -1,
												x * 32 + (rand() % 16),
												y * 32 + (rand() % 16),
												112,
												1, 0);
											for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
										}
										else if (getItemDef(brokentile).rarity < 50)
										{
											DropItem(
												peer, -1,
												x * 32 + (rand() % 16),
												y * 32 + (rand() % 16),
												112,
												1, 0);
											for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
										}
										else if (getItemDef(brokentile).rarity < 70)
										{
											DropItem(
												peer, -1,
												x * 32 + (rand() % 16),
												y * 32 + (rand() % 16),
												112,
												1, 0);
											for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
										}
										else if (getItemDef(brokentile).rarity < 99)
										{
											DropItem(
												peer, -1,
												x * 32 + (rand() % 16),
												y * 32 + (rand() % 16),
												112,
												1, 0);
											for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
										}
									}
									else
									{
										if (value == world->magitem)
										{
											int gemvalue = rand() % 15;
											world->gaiajumlah += gemvalue;
										}
										else {
											DropItem(peer, netid, x1, y1, value, 1, 0);
										}
									}
								}

							}
						}
							}
							}

					ItemDefinition yologay;
					yologay = getItemDef(world->items[x + (y * world->width)].foreground);
					if (yologay.MultiFacing == "MultiFacing")
					{
						world->items[x + (y * world->width)].rotatedLeft = false;
					}
					// buvo cia
					int valgem;
					int crystalChange;
					if (((PlayerInfo*)(peer->data))->cloth_hand == 7912) {
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 3948 || world->items[x + (y * world->width)].foreground == 3606 || world->items[x + (y * world->width)].foreground == 8226 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1636 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308) {
							world->items[x + (y * world->width)].foreground = 0;
						}
						else {
							if (world->items[x + (y * world->width)].foreground == 2) {
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
									givequestkatanastep2xp(peer, 2);
								}
								else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
									givequestkatanastep2xp(peer, 3);
								}
								else {
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
									givequestkatanastep2xp(peer, 1);
								}
								AddPlayerFragmentEarth(peer, valgem);
							}
							else {
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
									givequestkatanastep2xp(peer, 2);
								}
								else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
									givequestkatanastep2xp(peer, 3);
								}
								else {
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
									givequestkatanastep2xp(peer, 1);
								}
							}
						}
					}
					else if (((PlayerInfo*)(peer->data))->cloth_ances == 7166) {
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 3948 || world->items[x + (y * world->width)].foreground == 3606 || world->items[x + (y * world->width)].foreground == 8226 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1636 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308) {
							world->items[x + (y * world->width)].foreground = 0;
						}
						else {
							if (world->items[x + (y * world->width)].foreground == 2) {
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								if (((PlayerInfo*)(peer->data))->cloth_necklace == 942 || ((PlayerInfo*)(peer->data))->cloth_hand == 63128)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
									givequestkatanastep2xp(peer, 2);
								}
								else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
									givequestkatanastep2xp(peer, 3);
								}
								else {
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
									givequestkatanastep2xp(peer, 1);
								}
								AddPlayerFragmentEarth(peer, valgem);
							}
							else {
								world->items[x + (y * world->width)].foreground = 0;
								valgem = rand() % 20;
								if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
									givequestkatanastep2xp(peer, 2);
								}
								else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
									givequestkatanastep2xp(peer, 3);
								}
								else {
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
									givequestkatanastep2xp(peer, 1);
								}
							}
						}
					}
					else if (((PlayerInfo*)(peer->data))->cloth_feet == 8834) {
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 3948 || world->items[x + (y * world->width)].foreground == 3606 || world->items[x + (y * world->width)].foreground == 8226 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1636 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308) {
							world->items[x + (y * world->width)].foreground = 0;
						}
						else {
							if (world->items[x + (y * world->width)].foreground == 2) {
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
									givequestkatanastep2xp(peer, 2);
								}
								else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
									givequestkatanastep2xp(peer, 3);
								}
								else {
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
									givequestkatanastep2xp(peer, 1);
								}
								AddPlayerFragmentEarth(peer, valgem);
							}
							else {
								world->items[x + (y * world->width)].foreground = 0;
								valgem = rand() % 13;
								if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
									givequestkatanastep2xp(peer, 2);
								}
								else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
									}
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
									givequestkatanastep2xp(peer, 3);
								}
								else {
									((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
									givequestkatanastep2xp(peer, 1);
								}
							}
						}
					}
					else {
						if (world->items[x + (y * world->width)].foreground == 2) {
							world->items[x + (y * world->width)].foreground = 0;
							srand(GetTickCount());
							if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
							{
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
								}
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
								givequestkatanastep2xp(peer, 2);
							}
							else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
							{
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
								}
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
								givequestkatanastep2xp(peer, 3);
							}
							else {
								((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
								givequestkatanastep2xp(peer, 1);
							}
							valgem = rand() % 10;
							AddPlayerFragmentEarth(peer, valgem);
						}
						else {
							valgem = rand() % 5;
							world->items[x + (y * world->width)].foreground = 0;
						}
					}
#pragma region crystals
					if (world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1636 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308) {
						world->items[x + (y * world->width)].foreground = 0;
					}
					else {
						if (((PlayerInfo*)(peer->data))->skill == "Miner")
						{
							int valshouldfind = rand() % 100 + 1;
							if (valshouldfind < 15)
							{
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Miner Skill `^Boosted The `4Crystals`^!");
								}
								vector<Crystal> crystals;
								crystals.push_back(Crystal("emerald", 30));
								crystals.push_back(Crystal("diamond", 60));
								crystals.push_back(Crystal("sapphire", 90));
								crystals.push_back(Crystal("ruby", 120));
								crystals.push_back(Crystal("gold", 150));
								crystals.push_back(Crystal("opal", 250));
								crystals.push_back(Crystal("amber", 330));
								string foundcrystalname = "";
								int val2 = rand() % 1000 + 1;
								for (int i = 0; foundcrystalname == ""; i++)
								{
									if (val2 < crystals[i].probability) foundcrystalname = crystals[i].name;
									val2 -= crystals[i].probability;
								}
								if (foundcrystalname == "emerald")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `2Emerald`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->emerald += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 10;
										givequestkatanastep2xp(peer, 10);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 15;
										givequestkatanastep2xp(peer, 15);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 5;
										givequestkatanastep2xp(peer, 5);
									}
								}
								else if (foundcrystalname == "diamond")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `3Diamond`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->diamond += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 8;
										givequestkatanastep2xp(peer, 8);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 12;
										givequestkatanastep2xp(peer, 12);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
										givequestkatanastep2xp(peer, 4);
									}
								}
								else if (foundcrystalname == "sapphire")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `bSapphire`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->sapphire += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
										givequestkatanastep2xp(peer, 4);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 6;
										givequestkatanastep2xp(peer, 6);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
								}
								else if (foundcrystalname == "ruby")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `4Ruby`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->rubble += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "gold")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `9Gold`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->gold += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "opal")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `1Opal`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->opal += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "amber")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `8Amber`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->amber += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								crystals.clear();
							}
						}
						else {
							int valshouldfind = rand() % 100 + 1;
							if (valshouldfind < 9)
							{
								vector<Crystal> crystals;
								crystals.push_back(Crystal("emerald", 30));
								crystals.push_back(Crystal("diamond", 60));
								crystals.push_back(Crystal("sapphire", 90));
								crystals.push_back(Crystal("ruby", 120));
								crystals.push_back(Crystal("gold", 150));
								crystals.push_back(Crystal("opal", 250));
								crystals.push_back(Crystal("amber", 330));
								string foundcrystalname = "";
								int val2 = rand() % 1000 + 1;
								for (int i = 0; foundcrystalname == ""; i++)
								{
									if (val2 < crystals[i].probability) foundcrystalname = crystals[i].name;
									val2 -= crystals[i].probability;
								}
								if (foundcrystalname == "emerald")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `2Emerald`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->emerald += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 10;
										givequestkatanastep2xp(peer, 10);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 15;
										givequestkatanastep2xp(peer, 15);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 5;
										givequestkatanastep2xp(peer, 5);
									}
								}
								else if (foundcrystalname == "diamond")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `3Diamond`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->diamond += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 8;
										givequestkatanastep2xp(peer, 8);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 12;
										givequestkatanastep2xp(peer, 12);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
										givequestkatanastep2xp(peer, 4);
									}
								}
								else if (foundcrystalname == "sapphire")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `bSapphire`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->sapphire += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
										givequestkatanastep2xp(peer, 4);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 6;
										givequestkatanastep2xp(peer, 6);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
								}
								else if (foundcrystalname == "ruby")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `4Ruby`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->rubble += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "gold")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `9Gold`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->gold += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "opal")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `1Opal`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->opal += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "amber")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `8Amber`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->amber += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								crystals.clear();

							}

						}
					}

#pragma endregion
					if (((PlayerInfo*)(peer->data))->xp >= (((PlayerInfo*)(peer->data))->level * 1500)) {
						((PlayerInfo*)(peer->data))->xp = 0;
						((PlayerInfo*)(peer->data))->level = ((PlayerInfo*)(peer->data))->level + 1;
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;
							if (isHere(peer, currentPeer)) {
								string name = ((PlayerInfo*)(peer->data))->displayName;
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), name + " `wis now level " + std::to_string(((PlayerInfo*)(peer->data))->level) + "!"));
								string text = "action|play_sfx\nfile|audio/levelup2.wav\ndelayMS|0\n";
								BYTE* data = new BYTE[5 + text.length()];
								BYTE zero = 0;
								int type = 3;
								memcpy(data, &type, 4);
								memcpy(data + 4, text.c_str(), text.length());
								memcpy(data + 4 + text.length(), &zero, 1);
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(currentPeer, 0, packet);
								ENetPacket* packet2 = enet_packet_create(data,
									5 + text.length(),
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(currentPeer, 0, packet2);
								delete data;
								delete p.data;
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), name + " `wis now level " + std::to_string(((PlayerInfo*)(peer->data))->level) + "!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(currentPeer, 0, packet3);
							}
						}
					}
				}
				else {
					world->items[x + (y * world->width)].background = 6864;
					int valgem = rand() % 5;
					if (world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1636 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308) {
						world->items[x + (y * world->width)].foreground = 0;
					}
					else {
						if (((PlayerInfo*)(peer->data))->skill == "Miner")
						{
							int valshouldfind = rand() % 100 + 1;
							if (valshouldfind < 30)
							{
								if (((PlayerInfo*)(peer->data))->chatnotifications == true)
								{
									Player::OnConsoleMessage(peer, "`9[SKILL] `#Miner Skill `^Boosted The `4Crystals`^!");
								}
								vector<Crystal> crystals;
								crystals.push_back(Crystal("emerald", 30));
								crystals.push_back(Crystal("diamond", 60));
								crystals.push_back(Crystal("sapphire", 90));
								crystals.push_back(Crystal("ruby", 120));
								crystals.push_back(Crystal("gold", 150));
								crystals.push_back(Crystal("opal", 250));
								crystals.push_back(Crystal("amber", 330));
								string foundcrystalname = "";
								int val2 = rand() % 1000 + 1;
								for (int i = 0; foundcrystalname == ""; i++)
								{
									if (val2 < crystals[i].probability) foundcrystalname = crystals[i].name;
									val2 -= crystals[i].probability;
								}
								if (foundcrystalname == "emerald")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `2Emerald`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->emerald += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 10;
										givequestkatanastep2xp(peer, 10);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 15;
										givequestkatanastep2xp(peer, 15);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 5;
										givequestkatanastep2xp(peer, 5);
									}
								}
								else if (foundcrystalname == "diamond")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `3Diamond`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->diamond += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 8;
										givequestkatanastep2xp(peer, 8);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 12;
										givequestkatanastep2xp(peer, 12);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
										givequestkatanastep2xp(peer, 4);
									}
								}
								else if (foundcrystalname == "sapphire")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `bSapphire`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->sapphire += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
										givequestkatanastep2xp(peer, 4);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 6;
										givequestkatanastep2xp(peer, 6);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
								}
								else if (foundcrystalname == "ruby")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `4Ruby`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->rubble += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "gold")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `9Gold`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->gold += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "opal")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `1Opal`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->opal += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "amber")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `8Amber`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->amber += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								crystals.clear();
							}
						}
						else {
							int valshouldfind = rand() % 100 + 1;
							if (valshouldfind < 9)
							{
								vector<Crystal> crystals;
								crystals.push_back(Crystal("emerald", 30));
								crystals.push_back(Crystal("diamond", 60));
								crystals.push_back(Crystal("sapphire", 90));
								crystals.push_back(Crystal("ruby", 120));
								crystals.push_back(Crystal("gold", 150));
								crystals.push_back(Crystal("opal", 250));
								crystals.push_back(Crystal("amber", 330));
								string foundcrystalname = "";
								int val2 = rand() % 1000 + 1; // 0 - 1000
								for (int i = 0; foundcrystalname == ""; i++)
								{
									if (val2 < crystals[i].probability) foundcrystalname = crystals[i].name;
									val2 -= crystals[i].probability;
								}
								if (foundcrystalname == "emerald")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `2Emerald`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->emerald += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 10;
										givequestkatanastep2xp(peer, 10);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 15;
										givequestkatanastep2xp(peer, 15);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 5;
										givequestkatanastep2xp(peer, 5);
									}
								}
								else if (foundcrystalname == "diamond")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `3Diamond`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->diamond += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 8;
										givequestkatanastep2xp(peer, 8);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 12;
										givequestkatanastep2xp(peer, 12);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
										givequestkatanastep2xp(peer, 4);
									}
								}
								else if (foundcrystalname == "sapphire")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `bSapphire`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->sapphire += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 4;
										givequestkatanastep2xp(peer, 4);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 6;
										givequestkatanastep2xp(peer, 6);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
								}
								else if (foundcrystalname == "ruby")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `4Ruby`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->rubble += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "gold")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `9Gold`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->gold += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "opal")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `1Opal`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->opal += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								else if (foundcrystalname == "amber")
								{
									if (((PlayerInfo*)(peer->data))->chatnotifications == true)
									{
										GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`9[LOGS]`^ You found `8Amber`^!"));
										ENetPacket* packet = enet_packet_create(p2.data,
											p2.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p2.data;
									}
									((PlayerInfo*)(peer->data))->amber += 1;
									if (((PlayerInfo*)(peer->data))->cloth_necklace == 9428 || ((PlayerInfo*)(peer->data))->cloth_hand == 6312)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Double XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 2;
										givequestkatanastep2xp(peer, 2);
									}
									else if (((PlayerInfo*)(peer->data))->cloth_back == 9466)
									{
										if (((PlayerInfo*)(peer->data))->chatnotifications == true)
										{
											Player::OnConsoleMessage(peer, "`2[BONUS] `^You Got `2Triple XP`^!");
										}
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 3;
										givequestkatanastep2xp(peer, 3);
									}
									else {
										((PlayerInfo*)(peer->data))->xp = ((PlayerInfo*)(peer->data))->xp + 1;
										givequestkatanastep2xp(peer, 1);
									}
								}
								crystals.clear();

							}
						}
					}
					if (((PlayerInfo*)(peer->data))->xp >= (((PlayerInfo*)(peer->data))->level * 1500)) {
						((PlayerInfo*)(peer->data))->xp = 0;
						((PlayerInfo*)(peer->data))->level = ((PlayerInfo*)(peer->data))->level + 1;
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;
							if (isHere(peer, currentPeer)) {
								string name = ((PlayerInfo*)(peer->data))->displayName;
								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), name + " `wis now level " + std::to_string(((PlayerInfo*)(peer->data))->level) + "!"));
								string text = "action|play_sfx\nfile|audio/levelup2.wav\ndelayMS|0\n";
								BYTE* data = new BYTE[5 + text.length()];
								BYTE zero = 0;
								int type = 3;
								memcpy(data, &type, 4);
								memcpy(data + 4, text.c_str(), text.length());
								memcpy(data + 4 + text.length(), &zero, 1);
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(currentPeer, 0, packet);
								ENetPacket* packet2 = enet_packet_create(data,
									5 + text.length(),
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(currentPeer, 0, packet2);
								delete data;
								delete p.data;
								GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), name + " `wis now level " + std::to_string(((PlayerInfo*)(peer->data))->level) + "!"));
								ENetPacket* packet3 = enet_packet_create(p3.data,
									p3.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(currentPeer, 0, packet3);
							}
							data.plantingTree = tile;
						}
					}
				}
				if (((PlayerInfo*)(peer->data))->haveGrowId) {
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
					j["level"] = p->level;
					j["xp"] = p->xp;
					j["rubblexp"] = p->rubblexp;
					j["rubble"] = p->rubble;
					j["amberxp"] = p->amberxp;
					j["amber"] = p->amber;
					j["opalxp"] = p->opalxp;
					j["opal"] = p->opal;
					j["goldxp"] = p->goldxp;
					j["gold"] = p->gold;
					j["sapphirexp"] = p->sapphirexp;
					j["sapphire"] = p->sapphire;
					j["diamondxp"] = p->diamondxp;
					j["diamond"] = p->diamond;
					j["emeraldxp"] = p->emeraldxp;
					j["emerald"] = p->emerald;
					std::ofstream o("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json"); //save
					if (!o.is_open()) {
						cout << GetLastError() << endl;
						_getch();
					}
					o << j << std::endl;
				}
			}
			else
				if (y < world->height)
				{
					world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					world->items[x + (y * world->width)].breakLevel += 6; // TODO
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
					SaveInventoryWhenBuildingBlock(peer);
				}
				else {
					((PlayerInfo*)(peer->data))->inventory.items.erase(((PlayerInfo*)(peer->data))->inventory.items.begin() + i);
					SaveInventoryWhenBuildingBlock(peer);
				}
			}
		}
		if (world->areLogsEnabled == true)
		{
			ofstream savelogs("worldlogs/" + world->name + ".txt", std::ios_base::app);
			savelogs << ((PlayerInfo*)(peer->data))->rawName << " placed " << getItemDef(tile).name << "(" << tile << ")" << endl;
		}
		ItemDefinition yologay;
		if (def.blockType == BlockTypes::BACKGROUND)
		{
			world->items[x + (y * world->width)].background = tile;
			data.plantingTree = tile;
		}
		else {
			if (world->items[x + (y * world->width)].foreground != 0) return;

			if (getItemDef(tile).blockType == BlockTypes::LOCK) {
				world->items[x + (y * world->width)].foreground = tile;
				world->owner = ((PlayerInfo*)(peer->data))->rawName;
				world->Displayowner = ((PlayerInfo*)(peer->data))->displayName;
				world->isPublic = false;
				((PlayerInfo*)(peer->data))->worldsowned.push_back(world->name);
				std::ifstream ifff("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
				if (ifff.fail()) {
					ifff.close();
				}
				if (ifff.is_open()) {
				}
				json j;
				ifff >> j; //load
				j["worldsowned"] = ((PlayerInfo*)(peer->data))->worldsowned; //edit
				std::ofstream o("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json"); //save
				if (!o.is_open()) {
					cout << GetLastError() << endl;
					_getch();
				}
				o << j << std::endl;
				if (((PlayerInfo*)(peer->data))->haveGrowId)
				{
					if (((PlayerInfo*)(peer->data))->isNicked == false)
					{
						GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`2" + ((PlayerInfo*)(peer->data))->displayName));
						memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
						ENetPacket* packet7 = enet_packet_create(p7.data,
							p7.len,
							ENET_PACKET_FLAG_RELIABLE);
						delete p7.data;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;
							if (isHere(peer, currentPeer)) {
								if (((PlayerInfo*)(peer->data))->adminLevel >= 0) {
									enet_peer_send(currentPeer, 0, packet7);
								}
							}
						}
					}
				}
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer)) {
						if (((PlayerInfo*)(peer->data))->adminLevel == 1337 && ((PlayerInfo*)(peer->data))->isCreator != true) {
							world->pIsDev = true;
						}
						else if (((PlayerInfo*)(peer->data))->isCreator == true && ((PlayerInfo*)(peer->data))->adminLevel == 1337)
						{
							world->pIsPlay = true;
						}
						else if (((PlayerInfo*)(peer->data))->isCreator == true && ((PlayerInfo*)(peer->data))->adminLevel == 999)
						{
							world->pIsPlay = true;
						}
						else if (((PlayerInfo*)(peer->data))->adminLevel == 999 && ((PlayerInfo*)(peer->data))->isCreator != true) {
							world->pIsDev = true;
						}
						else if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
							world->pIsMod = true;
						}
						else if (((PlayerInfo*)(peer->data))->adminLevel == 555) {
							world->pIsVip = true;
						}
						else if (((PlayerInfo*)(peer->data))->adminLevel == 888) {
							world->pIsAdmin = true;
						}
						else if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
							world->pIsKing = true;
						}
						else
						{
							world->pIsPlay = false;
							world->pIsDev = false;
							world->pIsMod = false;
							world->pIsVip = false;
							world->pIsAdmin = false;
							world->pIsKing = false;
						}
						if (((PlayerInfo*)(peer->data))->adminLevel >= 0)
						{
							//isLock = true;
							string text = "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0\n";
							BYTE* data = new BYTE[5 + text.length()];
							BYTE zero = 0;
							int type = 3;
							memcpy(data, &type, 4);
							memcpy(data + 4, text.c_str(), text.length()); // change memcpy here
							memcpy(data + 4 + text.length(), &zero, 1); // change memcpy here, revert to 4
							ENetPacket* packetsou = enet_packet_create(data,
								5 + text.length(),
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(currentPeer, 0, packetsou);
							Player::OnConsoleMessage(currentPeer, "`3[`w" + world->name + " `ohas been `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "ed `oBy `w" + ((PlayerInfo*)(peer->data))->displayName + "`3]");
							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								if (isHere(peer, currentPeer)) {
									bool achi = std::experimental::filesystem::exists("achievements/wl/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
									if (achi == false)
									{
										int effect = 48;
										int x = ((PlayerInfo*)(currentPeer->data))->x;
										int y = ((PlayerInfo*)(currentPeer->data))->y;
										GamePacket psp = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), effect), x, y));

										ENetPacket* packetd = enet_packet_create(psp.data,
											psp.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packetd);
										GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), ((PlayerInfo*)(peer->data))->displayName + " `5earned the achievement This Is My Land!"));
										ENetPacket* packet3 = enet_packet_create(p3.data,
											p3.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(currentPeer, 0, packet3);
										delete p3.data;

										ofstream myfile;
										myfile.open("achievements/wl/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
										myfile << "true";
										myfile.close();
									}
									Player::OnConsoleMessage(currentPeer, "`3[`w" + world->name + " `ohas been `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "ed `oBy `w" + static_cast<PlayerInfo*>(peer->data)->rawName + "`3]");
									Player::PlayAudio(currentPeer, "audio/use_lock.wav", 0);
								}
							}
						}
					}
				}
			}
			world->items[x + (y * world->width)].foreground = tile;
			yologay = getItemDef(tile);
			if (yologay.MultiFacing == "MultiFacing") {
				if (((PlayerInfo*)(peer->data))->RotatedLeft == true) {
					((PlayerInfo*)(peer->data))->wrenchx = x;
					((PlayerInfo*)(peer->data))->wrenchy = y;
					int squaresign = x + (y * 100);
					//world->items[x + (y * world->width)].rotatedLeft = true;
					world->items[squaresign].rotatedLeft = true;
				}
				else {
					world->items[x + (y * world->width)].rotatedLeft = false;
				}
			}
			else {
				world->items[x + (y * world->width)].foreground = tile;
			}
		}
		world->items[x + (y * world->width)].breakLevel = 0;
	}
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
			SendPacketRaw(4, packPlayerMoving(&data), 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		ItemDefinition retard;
		retard = getItemDef(tile);
		if (retard.MultiFacing == "MultiFacing") {
			if (((PlayerInfo*)(peer->data))->RotatedLeft == true) {
				int squaresign = x + (y * 100);
				world->items[squaresign].rotatedLeft = true;
				updateRotatedItem(peer, world->items[squaresign].foreground, squaresign % world->width, squaresign / world->width, "", world->items[squaresign].background);
			}
		}
	}
}