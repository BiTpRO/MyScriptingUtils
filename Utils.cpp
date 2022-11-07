#include "Utils.h"

void Utils::CGM(Player* player) {
	ClearGossipMenuFor(player);
}

void Utils::AGI(Player* player, const std::string& text, uint32 action) {
	AddGossipItemFor(player, GossipOptionIcon::GOSSIP_ICON_DOT, text, GOSSIP_SENDER_MAIN, action);
}

void Utils::SGM(Player * player, Object * obj) {
	SendGossipMenuFor(player, 1, obj->GetGUID());
}

void Utils::SGM(Player * player, uint32 npcTextID, Object * obj) {
	SendGossipMenuFor(player, npcTextID, obj->GetGUID());
}

void Utils::EGM(Player * player) {
	CloseGossipMenuFor(player);
}

bool Utils::ATOG(Player * player) {
	if (player->GetMap()->IsBattlegroundOrArena() || player->IsInCombat() || player->IsInFlight()) {
		player->GetSession()->SendNotification("This can not be used in Combat, BG, Arena, or in Flight!");
		return false;
	}
	else
		return true;
}