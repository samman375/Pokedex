// Assignment 2 19T3 COMP1511: Pokedex
// test_pokedex.c
//
// This file allows you to automatically test the functions you
// implement in pokedex.c.
//
// This program was written by Samuel Thorley (z5257239)
// on 24-11-2019
//
// Version 1.0.0: Assignment released.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pokedex.h"

// Sample data on Bulbasaur, the Pokemon with pokemon_id 1.
#define BULBASAUR_ID 1
#define BULBASAUR_NAME "Bulbasaur"
#define BULBASAUR_HEIGHT 0.7
#define BULBASAUR_WEIGHT 6.9
#define BULBASAUR_FIRST_TYPE GRASS_TYPE
#define BULBASAUR_SECOND_TYPE POISON_TYPE

// Sample data on Ivysaur, the Pokemon with pokemon_id 2.
#define IVYSAUR_ID 2
#define IVYSAUR_NAME "Ivysaur"
#define IVYSAUR_HEIGHT 1.0
#define IVYSAUR_WEIGHT 13.0
#define IVYSAUR_FIRST_TYPE GRASS_TYPE
#define IVYSAUR_SECOND_TYPE POISON_TYPE

// Additional Sample data
#define SQUIRTLE_ID 7
#define SQUIRTLE_NAME "Squirtle"
#define SQUIRTLE_HEIGHT 0.5
#define SQUIRTLE_WEIGHT 9.0
#define SQUIRTLE_FIRST_TYPE WATER_TYPE
#define SQUIRTLE_SECOND_TYPE NONE_TYPE

#define PIKACHU_ID 25
#define PIKACHU_NAME "Pikachu"
#define PIKACHU_HEIGHT 0.4
#define PIKACHU_WEIGHT 6.0
#define PIKACHU_FIRST_TYPE ELECTRIC_TYPE
#define PIKACHU_SECOND_TYPE NONE_TYPE

#define JIGGLYPUFF_ID 39
#define JIGGLYPUFF_NAME "Jigglypuff"
#define JIGGLYPUFF_HEIGHT 0.5
#define JIGGLYPUFF_WEIGHT 5.5
#define JIGGLYPUFF_FIRST_TYPE FAIRY_TYPE
#define JIGGLYPUFF_SECOND_TYPE NORMAL_TYPE

#define DIGLETT_ID 50
#define DIGLETT_NAME "Diglett"
#define DIGLETT_HEIGHT 0.2
#define DIGLETT_WEIGHT 0.8
#define DIGLETT_FIRST_TYPE GROUND_TYPE
#define DIGLETT_SECOND_TYPE NONE_TYPE

#define MACHOKE_ID 67
#define MACHOKE_NAME "Machoke"
#define MACHOKE_HEIGHT 1.5
#define MACHOKE_WEIGHT 70.5
#define MACHOKE_FIRST_TYPE FIGHTING_TYPE
#define MACHOKE_SECOND_TYPE NONE_TYPE

#define KRABBY_ID 98
#define KRABBY_NAME "Krabby"
#define KRABBY_HEIGHT 0.4
#define KRABBY_WEIGHT 6.5
#define KRABBY_FIRST_TYPE WATER_TYPE
#define KRABBY_SECOND_TYPE NONE_TYPE

#define LICKITUNG_ID 108
#define LICKITUNG_NAME "Lickitung"
#define LICKITUNG_HEIGHT 1.2
#define LICKITUNG_WEIGHT 65.5
#define LICKITUNG_FIRST_TYPE NORMAL_TYPE
#define LICKITUNG_SECOND_TYPE NONE_TYPE

#define MAGIKARP_ID 129
#define MAGIKARP_NAME "Magikarp"
#define MAGIKARP_HEIGHT 0.9
#define MAGIKARP_WEIGHT 10.0
#define MAGIKARP_FIRST_TYPE WATER_TYPE
#define MAGIKARP_SECOND_TYPE NONE_TYPE

// Add your own prototypes here.
static void test_add_2_pokemon(Pokedex pokedex);
static void test_add_6_pokemon(Pokedex pokedex);
static Pokemon create_squirtle(void);
static Pokemon create_pikachu(void);
static Pokemon create_jigglypuff(void);
static Pokemon create_diglett(void);
static Pokemon create_machoke(void);
static Pokemon create_krabby(void);
static Pokemon create_lickitung(void);
static Pokemon create_magikarp(void);

// Tests for Pokedex functions from pokedex.c.
static void test_new_pokedex(void);
static void test_add_pokemon(void);
static void test_get_found_pokemon(void);
static void test_next_pokemon(void);
static void test_get_current_pokemon(void);
static void test_find_current_pokemon(void);
static void test_prev_pokemon(void);
static void test_remove_pokemon(void);

// Helper functions for creating/comparing Pokemon.
static Pokemon create_bulbasaur(void);
static Pokemon create_ivysaur(void);
static int is_same_pokemon(Pokemon first, Pokemon second);
static int is_copied_pokemon(Pokemon first, Pokemon second);


int main(int argc, char *argv[]) {
    printf("Welcome to the COMP1511 Pokedex Tests!\n");

    printf("\n==================== Pokedex Tests ====================\n");

    test_new_pokedex();
    test_add_pokemon();
    test_next_pokemon();
    test_get_current_pokemon();
    test_find_current_pokemon();
    test_prev_pokemon();
    test_remove_pokemon();
    test_get_found_pokemon();
    
    printf("\nAll Pokedex tests passed, you are Awesome!\n");
}


////////////////////////////////////////////////////////////////////////
//                     Pokedex Test Functions                         //
////////////////////////////////////////////////////////////////////////

// `test_new_pokedex` checks whether the new_pokedex and destroy_pokedex
// functions work correctly, to the extent that it can.
//
// It does this by creating a new Pokedex, checking that it's not NULL,
// then calling destroy_pokedex.
//
// Note that it isn't possible to check whether destroy_pokedex has
// successfully destroyed/freed the Pokedex, so the best we can do is to
// call the function and make sure that it doesn't crash..
static void test_new_pokedex(void) {
    printf("\n>> Testing new_pokedex\n");

    printf("    ... Creating a new empty Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("       --> Checking that the returned Pokedex is not NULL\n");
    assert(pokedex != NULL);
    
    /*printf("       --> Checking that the returned pointers head and curr_selected are NULL\n");
    assert(pokedex->head == NULL);
    assert(pokedex->curr_selected == NULL);*/

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed new_pokedex tests!\n");
}

// `test_add_pokemon` checks whether the add_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur (using the helper
// functions in this file and the provided code in pokemon.c), and
// calling add_pokemon to add it to the Pokedex.
//
// Some of the ways that you could extend these test would include:
//   - adding additional Pokemon other than just Bulbasaur,
//   - checking whether the currently selected Pokemon is correctly set,
//   - checking that functions such as `count_total_pokemon` return the
//     correct result after more Pokemon are added,
//   - ... and more!
static void test_add_pokemon(void) {
    printf("\n>> Testing add_pokemon\n");
    
    // Testing pokedex with 2 pokenodes being added, 
    // also tests head and curr_selected are correct
    printf("    ... Creating a new Pokedex with 2 pokemon\n");
    Pokedex pokedex = new_pokedex();
    test_add_2_pokemon(pokedex);
    printf("    --> Checking curr_selected is set to Bulbasaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));
    printf("    --> Checking pokedex contains 2 pokemon\n");
    assert(count_total_pokemon(pokedex) == 2);
    printf("    --> Checking Pokedex contains 0 found pokemon\n");
    assert(count_found_pokemon(pokedex) == 0);
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    // Same test but with 6 pokenodes being added
    printf("    ... Creating a new Pokedex with 6 pokemon\n");
    pokedex = new_pokedex();
    test_add_6_pokemon(pokedex);
    printf("    Checking curr_selected is pointed at Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));
    printf("    --> Checking pokedex contains 6 pokemon\n");
    assert(count_total_pokemon(pokedex) == 6);
    printf("    --> Checking Pokedex contains 0 found pokemon\n");
    assert(count_found_pokemon(pokedex) == 0);
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed add_pokemon tests!\n");
}

// `test_next_pokemon` checks whether the next_pokemon function works
// correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, then checks that calling the
// next_pokemon function changes the currently selected Pokemon from
// Bulbasaur to Ivysaur.
//
// Some of the ways that you could extend these tests would include:
//   - adding even more Pokemon to the Pokedex,
//   - calling the next_pokemon function when there is no "next" Pokemon,
//   - calling the next_pokemon function when there are no Pokemon in
//     the Pokedex,
//   - ... and more!
static void test_next_pokemon(void) {
    printf("\n>> Testing next_pokemon\n");

    // Tests a pokedex with 2 pokenodes
    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();
    test_add_2_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 2 pokemon\n");
    assert(count_total_pokemon(pokedex) == 2);
    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    Pokemon ivysaur = create_ivysaur();
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    // Tests a pokedex with 2 pokenodes and next command used while next == NULL
    printf("    ... Creating a new Pokedex\n");
    pokedex = new_pokedex();
    test_add_2_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 2 pokemon\n");
    assert(count_total_pokemon(pokedex) == 2);
    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("       --> Checking that the current Pokemon is still Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    // Tests a pokedex with 6 pokenodes and testing next when at end of pokedex
    printf("    ... Creating a new Pokedex\n");
    pokedex = new_pokedex();
    test_add_6_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 6 pokemon\n");
    assert(count_total_pokemon(pokedex) == 6);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Ivysaur\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Squirtle\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Pikachu\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Jigglypuff\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Diglett\n");
    printf("    End of pokedex reached\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("       --> Checking that the current Pokemon is still Diglett\n");
    Pokemon diglett = create_diglett();
    assert(is_same_pokemon(get_current_pokemon(pokedex), diglett));
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    // tests function on an empty pokedex
    printf("    ... Creating a new empty Pokedex\n");
    pokedex = new_pokedex();
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed next_pokemon tests!\n");
}

// tests get_current_pokemon function returns correct current pokemon
static void test_get_current_pokemon(void) {
    printf("\n>> Testing get_current_pokemon\n");
    
    // Tests function on empty pokedex
    printf("    ... Creating a new empty Pokedex\n");
    Pokedex pokedex = new_pokedex();
    printf("    --> Checking Pokedex contains 0 pokemon\n");
    assert(count_total_pokemon(pokedex) == 0);
    printf("    --> Checking current pokemon\n");
    assert(get_current_pokemon(pokedex) == NULL);
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    // Tests pokedex with a few pokenodes and movement commands used
    printf("    ... Creating a new Pokedex\n");
    pokedex = new_pokedex();
    test_add_6_pokemon(pokedex);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Moving to the previous pokemon\n");
    prev_pokemon(pokedex);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    Pokemon pikachu = create_pikachu();
    assert(is_same_pokemon(get_current_pokemon(pokedex), pikachu));
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    printf(">> Passed get_current_pokemon tests!\n");
}

// tests find_current_pokemon function correctly sets functions to found
static void test_find_current_pokemon(void) {
    printf("\n>> Testing find_current_pokemon\n");

    // Tests function on empty pokedex
    printf("    ... Creating a new empty Pokedex\n");
    Pokedex pokedex = new_pokedex();
    printf("    ... Setting currently selected to be found\n");
    find_current_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 0 found pokemon\n");
    assert(count_found_pokemon(pokedex) == 0);
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    // Greater number of pokemon and
    // also tests funciton being used on same pokemon twice
    printf("    ... Creating a new Pokedex\n");
    pokedex = new_pokedex();
    test_add_6_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 6 pokemon\n");
    assert(count_total_pokemon(pokedex) == 6);
    printf("    --> Checking Pokedex contains 0 found pokemon\n");
    assert(count_found_pokemon(pokedex) == 0);
    printf("    ... Setting currently selected to be found\n");
    find_current_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 1 found pokemon\n");
    assert(count_found_pokemon(pokedex) == 1);
    printf("    ... Setting currently selected to be found again\n");
    find_current_pokemon(pokedex);
    printf("    --> Checking Pokedex still contains 1 found pokemon\n");
    assert(count_found_pokemon(pokedex) == 1);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Setting currently selected to be found\n");
    find_current_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 2 found pokemon\n");
    assert(count_found_pokemon(pokedex) == 2);

    printf(">> Passed find_current_pokemon tests!\n");
}

static void test_prev_pokemon(void) {
    printf("\n>> Testing prev_pokemon\n");

    // Testing prev_pokemon function on empty pokedex
    printf("    ... Creating a new empty Pokedex\n");
    Pokedex pokedex = new_pokedex();
    printf("    --> Checking Pokedex contains 0 pokemon\n");
    assert(count_total_pokemon(pokedex) == 0);
    printf("    ... Moving to the previous pokemon\n");
    prev_pokemon(pokedex);
    printf("    ... Moving to the previous pokemon\n");
    prev_pokemon(pokedex);
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    // Tests prev_pokemon command on 6 pokenode pokedex
    printf("    ... Creating a new Pokedex\n");
    pokedex = new_pokedex();
    test_add_6_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 6 pokemon\n");
    assert(count_total_pokemon(pokedex) == 6);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    ... Moving to the previous pokemon\n");
    prev_pokemon(pokedex);
    printf("    ... Moving to the previous pokemon\n");
    prev_pokemon(pokedex);
    Pokemon ivysaur = create_ivysaur();
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed prev_pokemon tests!\n");
}

static void test_remove_pokemon(void) {
    printf("\n>> Testing remove_pokemon\n");
    
    // testing remove_pokemon on empty pokedex
    printf("    ... Creating a new empty Pokedex\n");
    Pokedex pokedex = new_pokedex();
    printf("    --> Checking Pokedex contains 0 pokemon\n");
    assert(count_total_pokemon(pokedex) == 0);
    printf("    ... Removing pokemon\n");
    remove_pokemon(pokedex);
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    // testing removing first pokenode
    printf("    ... Creating a new Pokedex\n");
    pokedex = new_pokedex();
    test_add_6_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 6 pokemon\n");
    assert(count_total_pokemon(pokedex) == 6);
    printf("    ... Removing pokemon\n");
    remove_pokemon(pokedex);
    printf("    --> Checking Pokedex contains now 5 pokemon\n");
    assert(count_total_pokemon(pokedex) == 5);
    printf("    --> Checking curr_selected is Ivysaur\n");
    Pokemon ivysaur = create_ivysaur();
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    // testing removing last pokenode
    printf("    ... Creating a new Pokedex\n");
    pokedex = new_pokedex();
    test_add_6_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 6 pokemon\n");
    assert(count_total_pokemon(pokedex) == 6);
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Ivysaur\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Squirtle\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Pikachu\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Jigglypuff\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Diglett\n");
    printf("    ... Removing pokemon\n");
    remove_pokemon(pokedex);
    printf("    --> Checking Pokedex contains now 5 pokemon\n");
    assert(count_total_pokemon(pokedex) == 5);
    printf("    --> Checking curr_selected is now Jigglypuff\n");
    Pokemon jigglypuff = create_jigglypuff();
    assert(is_same_pokemon(get_current_pokemon(pokedex), jigglypuff));
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    // testing removing 3rd and 4th pokenode
    printf("    ... Creating a new Pokedex\n");
    pokedex = new_pokedex();
    test_add_6_pokemon(pokedex);
    printf("    --> Checking Pokedex contains 6 pokemon\n");
    assert(count_total_pokemon(pokedex) == 6);
    printf("    Current pokemon is Bulbasaur\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Ivysaur\n");
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    printf("    Current pokemon is Squirtle\n");
    printf("    ... Removing pokemon\n");
    remove_pokemon(pokedex);
    printf("    --> Checking Pokedex contains now 5 pokemon\n");
    assert(count_total_pokemon(pokedex) == 5);
    printf("    --> Checking curr_selected is now Pikachu\n");
    Pokemon pikachu = create_pikachu();
    assert(is_same_pokemon(get_current_pokemon(pokedex), pikachu));
    printf("    ... Removing pokemon\n");
    remove_pokemon(pokedex);
    printf("    --> Checking Pokedex contains now 4 pokemon\n");
    assert(count_total_pokemon(pokedex) == 4);
    printf("    --> Checking curr_selected is now Jigglypuff\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), jigglypuff));
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    printf(">> Passed remove_pokemon tests!\n");
}

// `test_get_found_pokemon` checks whether the get_found_pokemon
// function works correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, sets Bulbasaur to be found, and
// then calls the get_found_pokemon function to get all of the Pokemon
// which have been found (which should be just the one, Bulbasaur).
//
// Some of the ways that you could extend these tests would include:
//   - calling the get_found_pokemon function on an empty Pokedex,
//   - calling the get_found_pokemon function on a Pokedex where none of
//     the Pokemon have been found,
//   - checking that the Pokemon in the new Pokedex are in ascending
//     order of pokemon_id (regardless of the order that they appeared
//     in the original Pokedex),
//   - checking that the currently selected Pokemon in the returned
//     Pokedex has been set correctly,
//   - checking that the original Pokedex has not been modified,
//   - ... and more!
static void test_get_found_pokemon(void) {
    printf("\n>> Testing get_found_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Getting all found Pokemon\n");
    Pokedex found_pokedex = get_found_pokemon(pokedex);

    printf("       --> Checking the correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(found_pokedex) == 1);
    assert(count_found_pokemon(found_pokedex) == 1);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur));

    printf("    ... Destroying both Pokedexes\n");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    printf(">> Passed get_found_pokemon tests!\n");
}


// Write your own Pokedex tests here!


////////////////////////////////////////////////////////////////////////
//                     Helper Functions                               //
////////////////////////////////////////////////////////////////////////

// Helper function to create Bulbasaur for testing purposes.
static Pokemon create_bulbasaur(void) {
    Pokemon pokemon = new_pokemon(
            BULBASAUR_ID, BULBASAUR_NAME,
            BULBASAUR_HEIGHT, BULBASAUR_WEIGHT,
            BULBASAUR_FIRST_TYPE,
            BULBASAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Ivysaur for testing purposes.
static Pokemon create_ivysaur(void) {
    Pokemon pokemon = new_pokemon(
            IVYSAUR_ID, IVYSAUR_NAME,
            IVYSAUR_HEIGHT, IVYSAUR_WEIGHT,
            IVYSAUR_FIRST_TYPE,
            IVYSAUR_SECOND_TYPE
    );
    return pokemon;
}

// Additional Helper functions to create pokemon for testing purposes
static Pokemon create_squirtle(void) {
    Pokemon pokemon = new_pokemon(
            SQUIRTLE_ID, SQUIRTLE_NAME,
            SQUIRTLE_HEIGHT, SQUIRTLE_WEIGHT,
            SQUIRTLE_FIRST_TYPE,
            SQUIRTLE_SECOND_TYPE
    );
    return pokemon;
}

static Pokemon create_pikachu(void) {
    Pokemon pokemon = new_pokemon(
            PIKACHU_ID, PIKACHU_NAME,
            PIKACHU_HEIGHT, PIKACHU_WEIGHT,
            PIKACHU_FIRST_TYPE,
            PIKACHU_SECOND_TYPE
    );
    return pokemon;
}

static Pokemon create_jigglypuff(void) {
    Pokemon pokemon = new_pokemon(
            JIGGLYPUFF_ID, JIGGLYPUFF_NAME,
            JIGGLYPUFF_HEIGHT, JIGGLYPUFF_WEIGHT,
            JIGGLYPUFF_FIRST_TYPE,
            JIGGLYPUFF_SECOND_TYPE
    );
    return pokemon;
}

static Pokemon create_diglett(void) {
    Pokemon pokemon = new_pokemon(
            DIGLETT_ID, DIGLETT_NAME,
            DIGLETT_HEIGHT, DIGLETT_WEIGHT,
            DIGLETT_FIRST_TYPE,
            DIGLETT_SECOND_TYPE
    );
    return pokemon;
}

static Pokemon create_machoke(void) {
    Pokemon pokemon = new_pokemon(
            MACHOKE_ID, MACHOKE_NAME,
            MACHOKE_HEIGHT, MACHOKE_WEIGHT,
            MACHOKE_FIRST_TYPE,
            MACHOKE_SECOND_TYPE
    );
    return pokemon;
}

static Pokemon create_krabby(void) {
    Pokemon pokemon = new_pokemon(
            KRABBY_ID, KRABBY_NAME,
            KRABBY_HEIGHT, KRABBY_WEIGHT,
            KRABBY_FIRST_TYPE,
            KRABBY_SECOND_TYPE
    );
    return pokemon;
}

static Pokemon create_lickitung(void) {
    Pokemon pokemon = new_pokemon(
            LICKITUNG_ID, LICKITUNG_NAME,
            LICKITUNG_HEIGHT, LICKITUNG_WEIGHT,
            LICKITUNG_FIRST_TYPE,
            LICKITUNG_SECOND_TYPE
    );
    return pokemon;
}

static Pokemon create_magikarp(void) {
    Pokemon pokemon = new_pokemon(
            MAGIKARP_ID, MAGIKARP_NAME,
            MAGIKARP_HEIGHT, MAGIKARP_WEIGHT,
            MAGIKARP_FIRST_TYPE,
            MAGIKARP_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to compare whether two Pokemon are the same.
// This checks that the two pointers contain the same address, i.e.
// they are both pointing to the same pokemon struct in memory.
//
// Pokemon ivysaur = new_pokemon(0, 'ivysaur', 1.0, 13.0, GRASS_TYPE, POISON_TYPE)
// Pokemon also_ivysaur = ivysaur
// is_same_pokemon(ivysaur, also_ivysaur) == TRUE
static int is_same_pokemon(Pokemon first, Pokemon second) {
    return first == second;
}

// Helper function to compare whether one Pokemon is a *copy* of
// another, based on whether their attributes match (e.g. pokemon_id,
// height, weight, etc).
// 
// It also checks that the pointers do *not* match -- i.e. that the
// pointers aren't both pointing to the same pokemon struct in memory.
// If the pointers both contain the same address, then the second
// Pokemon is not a *copy* of the first Pokemon.
// 
// This function doesn't (yet) check that the Pokemon's names match
// (but perhaps you could add that check yourself...).
static int is_copied_pokemon(Pokemon first, Pokemon second) {
    return (pokemon_id(first) == pokemon_id(second))
    &&  (first != second)
    &&  (pokemon_height(first) == pokemon_height(second))
    &&  (pokemon_weight(first) == pokemon_weight(second))
    &&  (pokemon_first_type(first) == pokemon_first_type(second))
    &&  (pokemon_second_type(first) == pokemon_second_type(second));
}

// Write your own helper functions here!

// Adds 2 pokemon to given pokedex
static void test_add_2_pokemon(Pokedex pokedex) {
    printf("    ... Creating Bulbasaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    printf("    ... Adding Bulbasaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    printf("    ... Creating Ivysaur\n");
    Pokemon ivysaur = create_ivysaur();
    printf("    ... Adding Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, ivysaur);
}

// Adds 6 pokemon to given pokedex
static void test_add_6_pokemon(Pokedex pokedex) {
    printf("    ... Creating Bulbasaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    printf("    ... Adding Bulbasaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    printf("    ... Creating Ivysaur\n");
    Pokemon ivysaur = create_ivysaur();
    printf("    ... Adding Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, ivysaur);
    printf("    ... Creating Squirtle\n");
    Pokemon squirtle = create_squirtle();
    printf("    ... Adding Squirtle to the Pokedex\n");
    add_pokemon(pokedex, squirtle);
    printf("    ... Creating Pikachu\n");
    Pokemon pikachu = create_pikachu();
    printf("    ... Adding Pikachu to the Pokedex\n");
    add_pokemon(pokedex, pikachu);
    printf("    ... Creating Jigglypuff\n");
    Pokemon jigglypuff = create_jigglypuff();
    printf("    ... Adding Jigglypuff to the Pokedex\n");
    add_pokemon(pokedex, jigglypuff);
    printf("    ... Creating Digglett\n");
    Pokemon diglett = create_diglett();
    printf("    ... Adding Diglett to the Pokedex\n");
    add_pokemon(pokedex, diglett);
}
