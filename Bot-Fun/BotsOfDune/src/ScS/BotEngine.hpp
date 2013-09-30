struct sTrainingData {
	double mInput[7];
	size_t mInputs;

	double mOutput[4];
	size_t mOutputs;

	sTrainingData( double pUnitType, double pCurrentSpeed, double pScoreToEnter, double pDamagedPercent, double pDamageAverageTicks, double pHostileInRange, double  pFriendlyInRange,
				   double pOutMoveForward, double pOutRotateBottom, double pOutRotateTop, double pAttack ) {
		
					   mInputs = 7;
		mOutputs = 4;

		Zero( &mInput[0], mInputs );
		Zero( &mOutput[0], mOutputs );

		mInput[0] = pUnitType;				// Type of unit
		mInput[1] = pCurrentSpeed;			// Speed on the current tile
		mInput[2] = pScoreToEnter;			// 256 if tile is not accessable, -1 when it is an accessable structure, or a score to enter the tile otherwise.
		mInput[3] = pDamagedPercent;		// Percentage of damage 
		mInput[4] = pDamageAverageTicks;	// average damage over the last 5 engine ticks
		mInput[5] = pHostileInRange;		// hostile in attack range
		mInput[6] = pFriendlyInRange;		// friendly in attack range
		mInputs = 7;

		mOutput[0] = pOutMoveForward;		// Mov forward
		mOutput[1] = pOutRotateBottom;		// Rotate bottom of unit
		mOutput[2] = pOutRotateTop;			// Rotate top of unit
		mOutput[3] = pAttack;				// Attack best in range target
		mOutputs=4;
	}

};

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
	void			 DoTrain(  std::vector<sTrainingData*> *pData, const double pType );

protected:

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

