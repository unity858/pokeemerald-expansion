#ifndef GUARD_NEW_GAME_PLUS_H
#define GUARD_NEW_GAME_PLUS_H

// New Game Plus (after R.O.W.E.'s, reduced to a single "is a plus game" flag).
//
// Picked with NEW GAME+ on the main menu, which is only shown when the loaded save
// has beaten the game and the PC has room for the party. The new game resets as
// usual, except that the bag (every pocket but Key Items), the PC items and the PC
// boxes are kept: the party is moved into the PC, every stored Pokémon goes back to
// level 1 (IVs and EVs kept, level 1 moves, healed), and their species are
// registered as seen and caught in the fresh Pokédex.
// FLAG_IS_NEW_GAME_PLUS is set for the whole playthrough; a normal new game
// clears it with the other flags.

// TRUE if NEW GAME+ can be offered: the loaded save is valid, has beaten the
// game, and the PC has a free slot for every Pokémon in the party.
bool32 IsNewGamePlusAvailable(void);
// TRUE if the loaded save is valid and has beaten the game (PC room not checked).
bool32 CanStartNewGamePlus(void);
u32 NewGamePlus_CountFreePcSlots(void);

// Used by NewGameInitData.
// Before the reset: moves the party's Pokémon into free PC slots. Any that do not
// fit are copied to leftovers[] (PARTY_SIZE entries) and their count returned.
u32 NewGamePlus_MovePartyToPC(struct Pokemon *leftovers);
// After the reset: level 1, level 1 moves and healed for every stored Pokémon (eggs untouched).
void NewGamePlus_LevelDownStorage(void);
// After the party reset: puts the leftovers back in the party, levelled down.
void NewGamePlus_RestoreLeftoverParty(const struct Pokemon *leftovers, u32 count);
// After the Pokédex reset: every species in the PC and party is seen and caught.
void NewGamePlus_RegisterOwnedMonsInPokedex(void);

void NewGamePlus_LevelDownBoxMon(struct BoxPokemon *boxMon);

// Before the reset: copies every bag pocket except Key Items, and the PC items, to a heap
// buffer (NULL if it could not be allocated; the items then reset as in a normal new game).
void *NewGamePlus_SaveItems(void);
// After ClearBag and NewGameInitPCItems: puts them back (dropping any key items from the PC
// items) and frees the buffer.
void NewGamePlus_RestoreItems(void *savedItems);

#endif // GUARD_NEW_GAME_PLUS_H
