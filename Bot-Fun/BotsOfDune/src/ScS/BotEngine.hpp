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
	double mInput[81];
	size_t mInputs;

	double mOutput[5];
	size_t mOutputs;

	sTrainingData( vector< vector< double > >  pInput, double pDamage,
					double pOutputForward, double pOutputTurnLeft, double pOutputTurnRight, double pOutputFire ) {
		
		mInputs = 81;
		mOutputs = 4;

		Zero( &mInput[0], mInputs );
		Zero( &mOutput[0], mOutputs );

		size_t count = 0;

		for( size_t x = 0; x < pInput.size(); ++x ) {

			for( size_t y = 0; y < pInput[x].size(); y+=2 ) {

				mInput[count] = pInput[x][y];
				mInput[count+1] = pInput[x][y+1];

				count += 2;
			}

		}

		mInput[80] = pDamage;

		mOutput[0] = pOutputForward;
		mOutput[1] = pOutputTurnLeft;
		mOutput[2] = pOutputTurnRight;
		mOutput[3] = pOutputFire;

	}


};

struct sTrainingSet {
	vector< sTrainingData* > mData;

	vector< double > CreateRow( size_t pCount, double pData, double pWeight ) {
		vector< double > Row;

		for( size_t x = 0; x < pCount; ++x) {
			Row.push_back( pData );
			Row.push_back( pWeight );
		}

		return Row;
	}

	vector< vector< double > > CreateAll( double pType ) {
		vector< vector< double > > Rows;
		/*[5](
		          [4](29 '',29 '',29 '',29 ''),
		 [6](88 'X',88 'X',88 'X',88 'X',88 'X',215 '×'),
		 [8](88 'X',88 'X',88 'X',88 'X',88 'X',215 '×',215 '×',215 '×'),
		[10](88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',215 '×',89 'Y'),
		[12](88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',88 'X',89 'Y',0))
		*/

		Rows.push_back(CreateRow(4, pType, 5 ));
		Rows.push_back(CreateRow(6, pType, 4 ));
		Rows.push_back(CreateRow(8, pType, 3 ));
		Rows.push_back(CreateRow(10, pType, 2 ));
		Rows.push_back(CreateRow(12, pType, 1 ));

		return Rows;
	}

	sTrainingSet() {

		vector< vector< double > > Rocks = CreateAll( ROCK );
		vector< vector< double > > Sand = CreateAll( SAND );
		vector< vector< double > > Enemy = CreateAll( ENEMY );
		vector< vector< double > > Wall = CreateAll( WALL );


		mData.push_back( new sTrainingData( Wall, 0, 0, 1, 1 , 0 ) );
		mData.push_back( new sTrainingData( Wall, 0, 0, 0, 1 , 0 ) );
		mData.push_back( new sTrainingData( Wall, 0, 0, 1, 0 , 0 ) );

		mData.push_back( new sTrainingData( Rocks, 0, 0, 1, 1, 0 ) );
		mData.push_back( new sTrainingData( Sand,  0, 0, 1, 1, 0 ) );

		mData.push_back( new sTrainingData( Rocks, 0, 1, 0, 0, 0 ) );
		mData.push_back( new sTrainingData( Sand,  0, 1, 0, 0, 0 ) );

		mData.push_back( new sTrainingData( Enemy, 0, 0, 0, 0, 1 ) );

	}

};

class cBot {
private:	// Members
	std::string		 mName;
	cNetwork		*mNetwork;

	vector<uint16>	 mDamage;
	vector< Unit*>	 mDamagers;

	double			 mInput[ 81 ];
	double			 mInputs;

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

