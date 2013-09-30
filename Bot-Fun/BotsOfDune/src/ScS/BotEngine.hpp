
class cBot {
private:	// Members
	std::string		 mName;
	cNetwork		*mNetwork;

	vector<uint16>	 mDamage;
	vector< Unit*>	 mDamagers;

	double			 mInput[ 7 ];
	double			 mInputs;

	double			 mTotalHitpoints;
	unsigned int	 mSeed;

private:	// Functions
	void			 Load();
	void			 Save();
	void			 Train( unsigned int pSeed );

protected:

	void			 Move();

public:
	size_t			 mSelfDeath;
	size_t			 mDeaths;
	size_t			 mKills;
	Unit			*mUnit;
	bool			 mBusy;

	cBot( std::string pName );
	~cBot( );

	void Tick();
	void Think();
	void DestroyedBy( Unit *pAttacker );
	void Killed( Unit *pAttacker );
	void TookDamage( Unit *pAttacker, uint16 pDamage );
	void GaveDamage( Unit *pUnit, uint16 pDamage );

	void Spawn( Unit *pUnit );
};

class cBotEngine {
private:
	std::vector< cBot* >		 mBots;

public:
	double						 mMap[64 * 64];

public:
						 cBotEngine();
						~cBotEngine();

void					 Tick();
void					 Bot_Spawn_Unit( Unit *pUnit );
void					 Bot_Unit_Damage( Unit *pUnit, Unit *pAttacker, uint16 pDamage );
void					 Bot_Unit_Destroyed( Unit *pUnit, Unit *pAttacker );
void					 Bot_Unit_Damage_Natural( Unit *pUnit );
	
void					 Bot_Unit_Remove( Unit *pUnit );
void					 Bot_Map_Update( uint16 pX, uint16 pY, uint8 pColor );

};

extern cBotEngine *g_BotEngine;

