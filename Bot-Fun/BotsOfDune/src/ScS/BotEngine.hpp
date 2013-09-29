
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

	void Tick();
	void DestroyedBy( Unit *pAttacker );
	void Killed( Unit *pAttacker );
	void TookDamage( Unit *pAttacker );

	void Spawn( Unit *pUnit );
};

class cBotEngine {
private:
	std::vector< cBot* >		 mBots;

public:
						 cBotEngine();
						~cBotEngine();

void					 Tick();
void					 Bot_Spawn_Unit( Unit *pUnit );
void					 Bot_Unit_Damage( Unit *pUnit, Unit *pAttacker );
void					 Bot_Unit_Destroyed( Unit *pUnit, Unit *pAttacker );
void					 Bot_Unit_Damage_Natural( Unit *pUnit );
	
void					 Bot_Unit_Remove( Unit *pUnit );
};

extern cBotEngine *g_BotEngine;

