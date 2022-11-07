#include "Utils.h"
#include "Item.h"
#include "GameObjectAI.h"
#include "GameObject.h"

// This class is here so we can define our gossip script in 1 place and then call it from anywhere.
class CustomGossip {
	Utils* util;

public:
	void GetMenu(Player* player, Object* obj) {
		if (util->ATOG(player)) {
			util->CGM(player);
			util->AGI(player, "Exit", 999);
			util->SGM(player, obj);
		}
		else {
			util->EGM(player);
		}
	}

	void MenuSelect(Player* player, Object* obj, uint32 sender, uint32 action) {
		util->CGM(player);

		switch (action) {
			case 998:
				GetMenu(player, obj);
				break;

			case 999:
				util->EGM(player);
				break;
		}
	}
};

//Item Script For Gossip
class ItemGossip : public ItemScript {
public:
	ItemGossip() : ItemScript("ItemGossip") {}

	CustomGossip CG = CustomGossip();

	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) {
		CG.GetMenu(player, item);
		return true;
	}

	void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) {
		if (sender != GOSSIP_SENDER_MAIN)
			CloseGossipMenuFor(player);

		CG.MenuSelect(player, item, sender, action);
	}
};

//Creature Script For Gossip
struct CreatureGossipAI : public ScriptedAI {
	explicit CreatureGossipAI(Creature* creature) : ScriptedAI(creature) {}

	CustomGossip CG = CustomGossip();

	bool OnGossipHello(Player* player) {
		CG.GetMenu(player, me);
		return true;
	}

	bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipListId) {
		uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
		uint32 const sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);

		if (sender != GOSSIP_SENDER_MAIN)
			CloseGossipMenuFor(player);

		CG.MenuSelect(player, me, sender, action);
		return true;
	}
};

//Gameobject Script For Gossip
struct GameObjectGossipAI : public GameObjectAI {
	explicit GameObjectGossipAI(GameObject* go) : GameObjectAI(go) { }

	CustomGossip CG = CustomGossip();

	bool OnGossipHello(Player* player) {
		CG.GetMenu(player, me);
		return true;
	}

	bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipListId) {
		uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
		uint32 const sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);

		if (sender != GOSSIP_SENDER_MAIN)
			CloseGossipMenuFor(player);

		CG.MenuSelect(player, me, sender, action);
		return true;
	}
};

void AddSC_Example() {
	new ItemGossip();
	RegisterCreatureAI(CreatureGossipAI);
	RegisterGameObjectAI(GameObjectGossipAI);
}