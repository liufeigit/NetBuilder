/**
*    Dune 2 Bot
*                      
* Copyright (c) 2013 
*
*              Strobs Canardly Systems
*
*                                  ScS
**/

extern void Bot_Init();

extern void Bot_Spawn_Unit( Unit *pUnit );
extern void Bot_Unit_Destroyed( Unit *pUnit, Unit *pAttacker );
extern void Bot_Unit_Damage( Unit *pUnit, Unit *pAttacker, uint16 pDamage );
extern void Bot_Unit_Damage_Natural( Unit *pUnit );

extern void Bot_Unit_Remove( Unit *pUnit );

extern void Bot_Map_Update( uint16 pX, uint16 pY, uint8 pColor );
