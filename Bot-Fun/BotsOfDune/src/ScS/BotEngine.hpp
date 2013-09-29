class cBot {
private:

public:

};

class cBotEngine {
private:
	std::vector< cBot* >		 mBots;

public:
						 cBotEngine();
						~cBotEngine();

void					 Bot_Spawn_Unit( Unit *pUnit );
void					 Bot_Unit_Destroyed( Unit *pAttacker, Unit *pDestroyed );
	

};

extern cBotEngine *g_BotEngine;

