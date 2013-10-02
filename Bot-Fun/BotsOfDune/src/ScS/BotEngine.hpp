/**
*    Dune 2 Bot
*                      
* Copyright (c) 2013 
*
*              Strobs Canardly Systems
*
*                                  ScS
**/

#define WALL 0
#define SAND 1
#define ROCK 2
#define FRIEND 3
#define ENEMY 4

struct sTrainingData {
	double mInput[7];
	size_t mInputs;

	double mOutput[4];
	size_t mOutputs;

	sTrainingData( double pInputVision0, double pInputVision1, double pInputVision2, double pInputVision3, double pInputVision4, double pDamageOverLast5Ticks, double pEnemyInRange,
					double pOutputForward, double pOutputTurnLeft, double pOutputTurnRight, double pOutputFire ) {
		
		mInputs = 7;
		mOutputs = 4;

		Zero( &mInput[0], mInputs );
		Zero( &mOutput[0], mOutputs );

		size_t count = 0;

		mInput[0] = pInputVision0;
		mInput[1] = pInputVision1;
		mInput[2] = pInputVision2;
		mInput[3] = pInputVision3;
		mInput[4] = pInputVision3;
		mInput[5] = pDamageOverLast5Ticks;
		mInput[6] = pEnemyInRange;

		mOutput[0] = pOutputForward;
		mOutput[1] = pOutputTurnLeft;
		mOutput[2] = pOutputTurnRight;
		mOutput[3] = pOutputFire;

	}


};

struct sTrainingSet {
	vector< sTrainingData* > mData;


	 vector< double > Create( double pType0, double pType1, double pType2, double pType3, double pType4  ) {
		 vector< double > Row;
		/*[5](
		          [4](29 '',29 '',29 '',29 ''),
		 [6](88 'X',88 'X',88 'X',88 'X',88 'X',215 '×'),
		 [8](88 'X',88 'X',88 'X',88 'X',88 'X',215 '×',215 '×',215 '×'),
		[10](88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',215 '×',89 'Y'),
		[12](88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',89 'Y',0))
		*/

		Row.push_back( pType0 );
		Row.push_back( pType1 );
		Row.push_back( pType2 );
		Row.push_back( pType3 );
		Row.push_back( pType4 );

		return Row;
	}

	sTrainingSet() {

		// Forward
		mData.push_back( new sTrainingData( ROCK, ROCK, ROCK, ROCK, ROCK, 0, 0,   1, 0, 0, 0 ) );

		// Left/Rigt
		mData.push_back( new sTrainingData( ROCK, ROCK, SAND, ROCK, ROCK, 0, 0,   0, 1, 1, 0 ) );


		// Left
		mData.push_back( new sTrainingData( SAND, SAND, WALL, WALL, SAND, 0, 0,   0, 1, 0, 0 ) );
		mData.push_back( new sTrainingData( ROCK, ROCK, WALL, WALL, ROCK, 0, 0,   0, 1, 0, 0 ) );

		// Right
		mData.push_back( new sTrainingData( ROCK, WALL, WALL, ROCK, ROCK, 0, 0,   0, 0, 1, 0 ) );

		// Forward
		mData.push_back( new sTrainingData( WALL, SAND, ROCK, SAND, WALL, 0, 0,   1, 0, 0, 0 ) );
		mData.push_back( new sTrainingData( WALL, WALL, WALL, WALL, WALL, 0, 0,   0, 1, 1, 0 ) );

		// Enemy in range
		mData.push_back( new sTrainingData( SAND, SAND, SAND, SAND, SAND, 0, 1,   0, 1, 1, 1 ) );
		
	}

};

class cBot {
private:	// Members
	std::string		 mName;
	cNetwork		*mNetwork;

	vector<uint16>	 mDamage;
	vector< Unit*>	 mDamagers;

	double			 mInput[ 7 ];
	size_t			 mInputs;

	double			 mTotalHitpoints;
	unsigned int	 mSeed;
	unsigned int	 mLastDirChange;
	unsigned int	 mLastTrain;

private:	// Functions
	void			 Load();
	void			 Save();
	void			 Train( unsigned int pSeed );
	void			 DoTrain(  std::vector<sTrainingData*> *pData, const double pType );
	void			 LayerInputsLoad();
	void			 LayerOutputsFire( cConnection *pLayerOutputs );
 
protected:

public:
	size_t			 mSelfDeath;
	size_t			 mDeaths;
	size_t			 mKills;
	Unit			*mUnit;
	bool			 mBusy;
	size_t			 mTick;

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

