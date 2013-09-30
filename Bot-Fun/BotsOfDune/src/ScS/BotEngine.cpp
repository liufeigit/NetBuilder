/**
*    Dune 2 Bot
*                      
* Copyright (c) 2013 
*
*              Strobs Canardly Systems
*
*                                  ScS
**/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef TYPES_H
#define TYPES_H

/** @file include/types.h Basic definitions and data types. */

#if defined(__TINYC__)
	/* Some includes set __attribute__ to nothing, making it fail */
	#undef __attribute__
#endif /* __TINYC__ */

#define MSVC_PACKED_BEGIN
#define MSVC_PACKED_END
#define GCC_PACKED
#define GCC_UNUSED
#define PACK

#define BIT_S8  int8
#define BIT_S16 int16
#define BIT_S32 int32
#define BIT_U8  uint8
#define BIT_U16 uint16
#define BIT_U32 uint32

#define VARIABLE_NOT_USED(variable) (void)variable;

#if defined(__GNUC__)
	#undef GCC_PACKED
	#define GCC_PACKED __attribute__((packed))
	#undef GCC_UNUSED
	#define GCC_UNUSED __attribute__((unused))

	#undef BIT_S8
	#undef BIT_S16
	#undef BIT_S32
	#undef BIT_U8
	#undef BIT_U16
	#undef BIT_U32

	#define BIT_S8  int32
	#define BIT_S16 int32
	#define BIT_S32 int32
	#define BIT_U8  uint32
	#define BIT_U16 uint32
	#define BIT_U32 uint32
#elif defined(_MSC_VER)
	#undef MSVC_PACKED_BEGIN
	#undef MSVC_PACKED_END
	#define MSVC_PACKED_BEGIN __pragma(pack(push, 1))
	#define MSVC_PACKED_END __pragma(pack(pop))
	#pragma warning(disable:4102) /* unreferenced label */
	#pragma warning(disable:4996) /* deprecated functions */
#elif defined(__TINYC__)
	/* For Tiny C Compiler to pack the content of a struct, it needs the
	 *  __attribute__((packed)) attribute on every member in the struct.
	 * For that reason we define PACK here, which has to be added before
	 *  every member in a struct you want to pack. This solves the
	 *  problem without making things very ugly (it still is not pretty,
	 *  but at least not very ugly). */
	#undef PACK
	#define PACK __attribute__((packed))
#endif /* __GNUC__ / _MSC_VER / __TINYC__ */

/* Compile time assertions. Prefer c++0x static_assert() */
#if defined(__STDCXX_VERSION__) || defined(__GXX_EXPERIMENTAL_CXX0X__) || defined(__GXX_EXPERIMENTAL_CPP0X__) || defined(static_assert)
	/* __STDCXX_VERSION__ is c++0x feature macro, __GXX_EXPERIMENTAL_CXX0X__ is used by gcc, __GXX_EXPERIMENTAL_CPP0X__ by icc */
	#define assert_compile(expr) static_assert(expr, #expr )
#elif defined(__OS2__) || (defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ < 4)
	/* Disabled for OS/2 or GCC < 3.4 */
	#define assert_compile(expr)
#else
	/* GCC warns about redundant redeclartion; to avoid it, we add __LINE__ to
	 *  the variable name. This of course doesn't avoid most warnings, but
	 *  should at least avoid most.
	 * We need a second indirection to resolve __LINE__ correctly. */
	#define __assert_compile(expr, line) extern const int __ct_assert_##line##__[1 - 2 * !(expr)] GCC_UNUSED
	#define _assert_compile(expr, line) __assert_compile(expr, line)
	#define assert_compile(expr) _assert_compile(expr, __LINE__)
#endif

typedef unsigned char  uint8;
typedef   signed char   int8;
typedef unsigned short uint16;
typedef   signed short  int16;
typedef unsigned int   uint32;
typedef   signed int    int32;
assert_compile(sizeof(uint8 ) == 1);
assert_compile(sizeof( int8 ) == 1);
assert_compile(sizeof(uint16) == 2);
assert_compile(sizeof( int16) == 2);
assert_compile(sizeof(uint32) == 4);
assert_compile(sizeof( int32) == 4);

/**
 * bits 0 to 7 are the offset in the tile.
 * bits 8 to 13 are the position on the map.
 * bits 14 and 15 are never used (or should never be used).
 */
typedef struct tile32 {
	uint16 x;
	uint16 y;
} tile32;


#endif /* TYPES_H */

#define _Bot_Skips 1

#include "../tools.h"
#include "../tile.h"
#include "../unit.h"
#include "../map.h"

extern "C" UnitInfo g_table_unitInfo[UNIT_MAX];
extern "C" const LandscapeInfo g_table_landscapeInfo[LST_MAX];
extern "C" bool Unit_Move(Unit *unit, uint16 distance);
extern "C" tile32 Tile_MoveByOrientation(tile32 position, uint8 orientation);
extern "C" uint16 Tile_PackTile(tile32 tile);
extern "C" uint16 Map_GetLandscapeType(uint16 packed);
extern "C" int16 Unit_GetTileEnterScore(Unit *unit, uint16 packed, uint16 orient8);
extern "C" uint16 Unit_FindBestTargetEncoded(Unit *unit, uint16 mode);
extern "C" void Unit_SetTarget(Unit* unit, uint16 encoded);
extern "C" void Unit_Rotate(Unit *unit, uint16 level);
extern "C" void Unit_SetDestination(Unit *u, uint16 destination);
extern "C" Object *Object_GetByPackedTile(uint16 packed);
extern "C" uint16 Tools_Index_Encode(uint16 index, IndexType type);
extern "C" void Unit_SetAction(Unit *u, ActionType action);

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

double RandomNumber(double pMin, double pMax) {

	return pMin + ((double)rand() / RAND_MAX) * (pMax - pMin);
}

void Zero( double *pVals, size_t pCount ) {

	for( size_t count = 0; count < pCount; ++count ) {

		pVals[count] = 0;
	}
}

#include "Network.hpp"
#include "BotEngine.hpp"



cBotEngine *g_BotEngine = 0;


extern "C" void Bot_Init() {

	g_BotEngine = new cBotEngine();
}

extern "C" void Bot_Tick() {

	g_BotEngine->Tick();
}

extern "C" void Bot_Spawn_Unit( Unit *pUnit ) {

	g_BotEngine->Bot_Spawn_Unit( pUnit );
}

extern "C" void Bot_Unit_Destroyed( Unit *pUnit, Unit *pAttacker ) {
	
	g_BotEngine->Bot_Unit_Destroyed( pUnit, pAttacker );
}

extern "C" void Bot_Unit_Damage( Unit *pUnit, Unit *pAttacker, uint16 pDamage ) {

	g_BotEngine->Bot_Unit_Damage( pUnit, pAttacker, pDamage );
}

extern "C" void Bot_Unit_Damage_Natural( Unit *pUnit ) {

	g_BotEngine->Bot_Unit_Damage_Natural( pUnit );
}

extern "C" void Bot_Unit_Remove( Unit *pUnit ) {

	g_BotEngine->Bot_Unit_Remove( pUnit );
}

extern "C" void Bot_Map_Update( uint16 pX, uint16 pY, uint8 pColor ) {

	g_BotEngine->Bot_Map_Update( pX, pY, pColor );
}

cBot::cBot( std::string pName ) {

	mName = pName;
	mNetwork = new cNetwork();

	mSelfDeath = 0;
	mKills = 0;
	mDeaths = 0;
	mBusy = false;
	mUnit = 0;
	mTick = 0;

	mInputs = 5;

	for( size_t Input = 0; Input < mInputs; ++Input ) {
		mInput[ Input ] = 0;
	}
	mSeed = 0;

	Load();
	Train( time(NULL) );
}

cBot::~cBot() {

	Save();
	delete mNetwork;
}

void cBot::Load() {

	mNetwork->Load( mName );
}

void cBot::Save() {

	mNetwork->Save( mName );
}

/*
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
		*/

void cBot::DoTrain( std::vector<sTrainingData*> *pData, const double pType ) {

	// Remember, we train towards these outputs.. but there are no guarantees in life :)
	
	for( int x = 0; x < 10; ++x ) {
		// Forward tile not accessable, Turn Base
		pData->push_back( new sTrainingData(
					pType, 0, 256, 0, 0, 0, 0,		// Inputs
					0, 1, 0, 0						// Outputs
					));
	}

	for( int x = 0; x < 10; ++x ) {
		
		// Move Forward for scores < 10
		pData->push_back( new sTrainingData(
				pType, 0, x, 0, 0, 0, 0,		// Inputs
				1, 0, 0, 0						// Outputs
				));
	}

	// Rotate bottom and move forward if hostile in range
	pData->push_back( new sTrainingData(
		pType, 0, 0, 0, 0, 1, 0,		// Inputs
		1, 1, 0, 0						// Outputs
		));

	// Attack if hostile in range
	pData->push_back( new sTrainingData(
		pType, 0, 0, 0, 0, 1, 0,		// Inputs
		0, 0, 0, 1						// Outputs
		));

	// Receiving Damage over last 5 ticks, Rotate Bottom, move forward 
	pData->push_back( new sTrainingData(
		pType, 0, 0, 0, 10, 1, 0,		// Inputs
		1, 1, 0, 0						// Outputs
		));
}

void cBot::Train( unsigned int pSeed ) {
	if( !mSeed )
		mSeed = pSeed;

	srand ( pSeed );

	std::vector<sTrainingData*> Training[15];

	size_t x = 0;
	for( size_t UnitType = UNIT_INFANTRY; UnitType <= UNIT_QUAD; ++UnitType ) {
		
		DoTrain( &Training[x++], (double) UnitType );

	}


	for( size_t x = 0; x < 15; ++x ) {

		for( std::vector<sTrainingData*>::iterator TrainIT = Training[ x ].begin(); TrainIT != Training[ x ].end(); ++TrainIT ) {
			
			double Error = mNetwork->Backward( (*TrainIT)->mInput, (*TrainIT)->mInputs, (*TrainIT)->mOutput, (*TrainIT)->mOutputs );

		// Should this be?
			if( Error < 0.005 )
				break;
		}
	}

}

void cBot::Tick() {
	const UnitInfo *ui;
	int8 orientation;
	tile32 position;
	uint16 packed;
	uint16 type;
	uint16 speed;
	int16 score;
	++mTick;

	if(!mUnit)
		return;

	if(  mUnit->actionID == ACTION_MOVE || mUnit->actionID == ACTION_ATTACK )
		return;

	// Inputs

	// 0: Unit Type
	// 1: Current Speed on this tile
	// 2: Score to enter forward tile
	// 3: Damaged Percent
	// 4: Average Damage over last 5 ticks
	// 5: pHostileInRange
	// 6: pFriendlyInRange

	mInput[0] = mUnit->o.type;

	ui = &g_table_unitInfo[mUnit->o.type];
	orientation = (int8)((mUnit->orientation[0].current) & 0xE0);
	position = Tile_MoveByOrientation(mUnit->o.position, orientation);
	packed = Tile_PackTile(position);
	score = Unit_GetTileEnterScore(mUnit, packed, orientation / 32);
	if( score == 256 )
		mLastDirChange = 0;

	type = Map_GetLandscapeType(packed);
	if (type == LST_STRUCTURE) 
		type = LST_CONCRETE_SLAB;
	speed = g_table_landscapeInfo[type].movementSpeed[ui->movementType];

	mInput[1] = (double) speed;

	mInput[2] = (double) score;

	mInput[3] = mUnit->o.hitpoints / mTotalHitpoints;

	mInput[4]  = 0;
	if( mDamage.size() > 0 ) {
		for( vector< uint16 >::iterator DmgIT = mDamage.begin(); DmgIT != mDamage.end(); ++DmgIT ) {
			mInput[4]  += (*DmgIT);
		}
		mInput[4] /= mDamage.size(); 
	}

	// Hostile  in range
	mInput[5] = (Unit_FindBestTargetEncoded( mUnit, 1 ) == 0 ? 0 : 1);

	// Friendly in range
	mInput[6] = 0;

	cConnection *Output = mNetwork->Forward( mInput, mInputs );

	double Act = 0.51;
	
	// Outputs

	// 0: Move Forward
	// 1: Rotate Bottom
	// 2: Rotate Top
	// 3: Attack

	if( Output->mActions[0]->mResult > Act && Output->mActions[1]->mResult < Act ) {
		
		Unit_SetAction(mUnit, ACTION_MOVE);

		orientation = (int8)((mUnit->orientation[0].current) & 0xE0);
		position = Tile_MoveByOrientation(mUnit->o.position, orientation);
		packed = Tile_PackTile(position);
		if (Object_GetByPackedTile(packed) == NULL)  
			Unit_SetDestination(mUnit, Tools_Index_Encode(packed, IT_TILE));
	}


	if( Output->mActions[1]->mResult > Act || mTick - mLastDirChange > 10 ) {
		mLastDirChange = mTick;

		Unit_SetAction(mUnit, ACTION_MOVE);

		orientation = (int8)((mUnit->orientation[0].current + 32) & 0xE0);
		position = Tile_MoveByOrientation(mUnit->o.position, orientation);
		packed = Tile_PackTile(position);
		if (Object_GetByPackedTile(packed) == NULL)  
			Unit_SetDestination(mUnit, Tools_Index_Encode(packed, IT_TILE));
	}


	if( Output->mActions[2]->mResult > Act ) {
		
	}


	if( Output->mActions[3]->mResult > Act )  {

		uint16 newPosition = Unit_FindBestTargetEncoded( mUnit, 1 );

		Unit_SetAction( mUnit, ACTION_ATTACK );
		Unit_SetTarget( mUnit, newPosition );
	}
}

void cBot::DestroyedBy( Unit *pAttacker ) {

	if( pAttacker == 0 )
		++mSelfDeath;

	++mDeaths;

	mUnit = 0;
}

void cBot::Killed( Unit *pTarget ) {

	mKills++;
}

void cBot::TookDamage( Unit *pAttacker, uint16 pDamage  ) {
	
	mDamage.push_back( pDamage );
	mDamagers.push_back( pAttacker );

	if( mDamage.size() > 4 )
		mDamage.erase( mDamage.begin() );

	if( mDamagers.size() > 4 )
		mDamagers.erase( mDamagers.begin() );
}

void cBot::GaveDamage( Unit *pUnit, uint16 pDamage ) {
	
}

void cBot::Spawn( Unit *pUnit ) {

	mUnit = pUnit;

	mTotalHitpoints = mUnit->o.hitpoints;
}

cBotEngine::cBotEngine() {

	for(uint16 y = 0; y < 64 * 64; ++y ) {
		
		mMap[y] = 0;
	}

	cout << "Creating Bots\n";
	mBots.push_back( new cBot( "0" ) );
	mBots.push_back( new cBot( "1" ) );
	mBots.push_back( new cBot( "2" ) );
	mBots.push_back( new cBot( "3" ) );
	mBots.push_back( new cBot( "4" ) );
	mBots.push_back( new cBot( "5" ) );
	mBots.push_back( new cBot( "6" ) );
	mBots.push_back( new cBot( "7" ) );
	mBots.push_back( new cBot( "8" ) );
	mBots.push_back( new cBot( "9" ) );
	mBots.push_back( new cBot( "10" ) );
}

cBotEngine::~cBotEngine() {

}

void cBotEngine::Bot_Unit_Remove( Unit *pUnit ) {
	
	for( std::vector< cBot* >::iterator BotIT = mBots.begin(); BotIT != mBots.end(); ++BotIT ) {

		if( (*BotIT)->mUnit == pUnit ) {
			
			std::cout << "Removed Unit!\nwe have a destroy we missed\n";
			(*BotIT)->mUnit = 0;
			return;
		}
	}
}

void cBotEngine::Bot_Spawn_Unit( Unit *pUnit ) {

	// Only control certain types of units
	if( pUnit->o.type < UNIT_INFANTRY || pUnit->o.type > UNIT_QUAD )
		return;

	for( std::vector< cBot* >::iterator BotIT = mBots.begin(); BotIT != mBots.end(); ++BotIT ) {

		if( (*BotIT)->mUnit != 0 )
			continue;

		(*BotIT)->Spawn( pUnit );
		break;
	}
}

void cBotEngine::Bot_Unit_Destroyed( Unit *pDestroyed, Unit *pAttacker ) {

	for( std::vector< cBot* >::iterator BotIT = mBots.begin(); BotIT != mBots.end(); ++BotIT ) {

		// Was this the destroyed unit?
		if( (*BotIT)->mUnit == pDestroyed ) {

			for( std::vector< cBot* >::iterator BotOIT = mBots.begin(); BotOIT != mBots.end(); ++BotOIT ) {

				// Was this the attacking bot? or was there no attacker
				if( (*BotOIT)->mUnit == pAttacker || pAttacker == 0 ) {
					
					(*BotIT)->DestroyedBy( pAttacker );

					if( pAttacker != 0 )
						(*BotOIT)->Killed( pDestroyed );

					return;
				}
			}

			(*BotIT)->DestroyedBy( 0 );

			return;
		}
	}
}

void cBotEngine::Bot_Unit_Damage( Unit *pUnit, Unit *pAttacker, uint16 pDamage ) {

	for( std::vector< cBot* >::iterator BotIT = mBots.begin(); BotIT != mBots.end(); ++BotIT ) {

		// Was this the destroyed unit?
		if( (*BotIT)->mUnit == pUnit ) {

			for( std::vector< cBot* >::iterator BotOIT = mBots.begin(); BotOIT != mBots.end(); ++BotOIT ) {

				// Was this the attacking bot? or was there no attacker
				if( (*BotOIT)->mUnit == pAttacker || pAttacker == 0 ) {

					(*BotIT)->TookDamage( pAttacker, pDamage );
					(*BotOIT)->GaveDamage( pUnit, pDamage );
					return;
				}
			}

			(*BotIT)->TookDamage( 0, pDamage );
			return;
		}
	}
}

void cBotEngine::Bot_Unit_Damage_Natural( Unit *pUnit ) {

}

void cBotEngine::Bot_Map_Update( uint16 pX, uint16 pY, uint8 pColor ) {
	
	mMap[(pY * 64) + pX] = (double) pColor;

}

void cBotEngine::Tick() {

	for( std::vector< cBot* >::iterator BotIT = mBots.begin(); BotIT != mBots.end(); ++BotIT ) {

		(*BotIT)->Tick();
	}
}
