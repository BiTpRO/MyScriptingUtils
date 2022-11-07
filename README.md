# MyScriptingUtils

This is basically just a wrapper for some commonly used trinity core functions.
I use this to make my scripting faster and simpler.

## Gossip

	//This will clear the gossip menu.
	void CGM(Player* player);

	//This adds a gossip menu item.
	void AGI(Player* player, const std::string& text, uint32 action);

	//Sends the gossip menu to the player. It uses npc text id of 1 by default. Use overload if you wish to set the npc text id.
	void SGM(Player* player, Object* obj);

	//Sends the gossip menu to the player
	void SGM(Player* player, uint32 npcTextID, Object* obj);

	//Exits the player's current open gossip menu.
	void EGM(Player* player);

	//Checks to see if a player is in Combat, BG, Arena, or Flying returns a true if they are not and false if they are.
	bool ATOG(Player* player);
  
  ## How to use it.
  
  Define your includes.
  
  #include "Utils.h"
  
  Declare your variable.
  
  Utils* util;
  
  Then you can call the functions.
  util->CGM(player);
  
  See my implementation inside Example.cpp
