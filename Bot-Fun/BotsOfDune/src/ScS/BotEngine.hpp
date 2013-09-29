
class cBot {
private:
	std::string		 mName;
	cNetwork		*mNetwork;

	void			 Load();
	void			 Save();

public:
	size_t			 mSelfDeath;
	size_t			 mDeaths;
	size_t			 mKills;
	Unit			*mUnit;

	cBot( std::string pName );
	~cBot( );

};

class cBotEngine {
private:
	std::vector< cBot* >		 mBots;
	std::vector< cBot* >		 mBotsFree;

public:
						 cBotEngine();
						~cBotEngine();

void					 Bot_Spawn_Unit( Unit *pUnit );
void					 Bot_Unit_Destroyed( Unit *pAttacker, Unit *pDestroyed );
	

};

extern cBotEngine *g_BotEngine;

