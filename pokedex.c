// Assignment 2 19T3 COMP1511: Pokedex
// pokedex.c
//
// This program was written by Samuel Thorley (z5257239)
// on 10-11-2019
//
// Version 2.0.0: Release

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// TO DO: adjust length of functions (both directions), finish and fix bugs with stage 5

// Note you are not allowed to use <string.h> in this assignment

// ----------------------------------------------
// Add any extra #includes your code needs here.
// ----------------------------------------------

#include "pokedex.h"


// ----------------------------------------------
// Add your own #defines here.
// ----------------------------------------------

#define NOT_FOUND 0
#define FOUND 1

// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.
struct pokedex {
    struct pokenode *head;
    struct pokenode *curr_selected;
};


// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
//
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.
struct pokenode {
    Pokemon pokemon;
    struct pokenode *next;
    struct pokenode *evolution;
    int found;
};


// ----------------------------------------------
// Add your own structs here.
// ----------------------------------------------




// ----------------------------------------------
// Add prototypes for your own functions here.
// ----------------------------------------------

static void print_ID(Pokemon pokemon);
static void ast_name(char *name);
static void detail_found(Pokedex pokedex);
static void detail_not_found(Pokedex pokedex);
static void add_ordered(Pokedex pokedex, Pokemon pokemon);
static void add_found_pokemon(Pokedex pokedex, Pokemon pokemon);


// Creates a new pokenode struct and returns a pointer to it.
static struct pokenode *new_pokenode(Pokemon pokemon);


// You can find descriptions of what each function should do in pokedex.h


// Creates a new Pokedex, and returns a pointer to it.
Pokedex new_pokedex(void) {
    Pokedex pokedex = malloc(sizeof(struct pokedex));
    assert(pokedex != NULL);

    pokedex->head = NULL;
    pokedex->curr_selected = NULL;

    return pokedex;
}

// Creates a new pokenode struct and returns a pointer to it.
static struct pokenode *new_pokenode(Pokemon pokemon) {
    struct pokenode *node = malloc(sizeof(struct pokenode));
    assert(node != NULL);
    
    node->next = NULL;
    node->pokemon = pokemon;
    node->found = NOT_FOUND;
    node->evolution = NULL;
    
    return node;
}

// Creates a new pokenode like before but sets it to found instead for stage 5
static struct pokenode *new_found_pokenode(Pokemon pokemon) {
    struct pokenode *node = malloc(sizeof(struct pokenode));
    assert(node != NULL);
    
    node->next = NULL;
    node->pokemon = pokemon;
    node->found = FOUND;
    node->evolution = NULL;
    
    return node;
}

//////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                        //
//////////////////////////////////////////////////////////////////////

// Add a new Pokemon to the Pokedex.
void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
    struct pokenode *curr = pokedex->head;
    if (curr == NULL) {
        pokedex->head = new_pokenode(pokemon);
        pokedex->curr_selected = pokedex->head;
        return;
    } else if (curr != NULL && curr->next == NULL) {
        curr->next = new_pokenode(pokemon);
        return;
    }
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_pokenode(pokemon);
}

// Print out the details of the currently selected Pokemon.
void detail_pokemon(Pokedex pokedex) {
    if (pokedex->curr_selected == NULL) {
        printf("Pokedex currently empty. Exiting pokedex.");
        exit(1);
    } else {
        printf("ID: ");
        print_ID(pokedex->curr_selected->pokemon);
        printf("\n");
        if (pokedex->curr_selected->found == NOT_FOUND) {
            detail_not_found(pokedex);
        } else if (pokedex->curr_selected->found == FOUND) {
            detail_found(pokedex);
        }
    }
}

// Returns the currently selected Pokemon.
Pokemon get_current_pokemon(Pokedex pokedex) {
    if (pokedex->curr_selected == NULL) {
        return NULL;
    } else {
        return pokedex->curr_selected->pokemon;
    }
}

// Sets the currently selected Pokemon to be 'found'.
void find_current_pokemon(Pokedex pokedex) {
    if (pokedex->curr_selected != NULL) {
        pokedex->curr_selected->found = FOUND;
    }
}

// Print out all of the Pokemon in the Pokedex.
void print_pokemon(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        return;
    }
    struct pokenode *curr = pokedex->head;
    while (curr != NULL) {
        if (curr == pokedex->curr_selected) {
            printf("--> #");
        } else {
            printf("    #");
        }
        print_ID(curr->pokemon);
        printf(": ");
        if (curr->found == FOUND) {
            printf("%s\n", pokemon_name(curr->pokemon));
        } else if (curr->found == NOT_FOUND) {
            ast_name(pokemon_name(curr->pokemon));
        }
        if (curr->next != NULL) {
            curr = curr->next;
        } else {
            return;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                        //
//////////////////////////////////////////////////////////////////////

// Change the currently selected Pokemon to be the next Pokemon in the Pokedex.
void next_pokemon(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        return;
    }
    if (pokedex->curr_selected->next != NULL) {
        pokedex->curr_selected = pokedex->curr_selected->next;
    }
}

// Change the currently selected Pokemon to be the previous Pokemon in the Pokedex.
void prev_pokemon(Pokedex pokedex) {
    if (
        pokedex->head != NULL && 
        pokedex->curr_selected->pokemon != pokedex->head->pokemon
    ) {
        struct pokenode *temp = pokedex->head;
        while (temp->next->pokemon != pokedex->curr_selected->pokemon) {
            temp = temp->next;
        }
        pokedex->curr_selected = temp;
    }
}

// Change the currently selected Pokemon to be the Pokemon with the ID `id`.
void change_current_pokemon(Pokedex pokedex, int id) {
    if (pokedex->head != NULL) {
        struct pokenode *temp = pokedex->head;
        while (pokemon_id(temp->pokemon) != id && temp != NULL) {
            temp = temp->next;
        }
        if (temp == NULL) {
            return;
        }
        if (pokemon_id(temp->pokemon) == id) {
            pokedex->curr_selected = temp;
        }
    }
}

// Remove the currently selected Pokemon from the Pokedex.
void remove_pokemon(Pokedex pokedex) {
    struct pokenode *temp = pokedex->head;
    // if no pokenodes in pokedex
    if (temp == NULL) {
        return;
    }
    // if only one pokenode in pokedex
    if (temp->next == NULL) {
        pokedex->curr_selected = NULL;
        pokedex->head = NULL;
        destroy_pokemon(temp->pokemon);
        free(temp);
        return;
    }
    // if currently selected is the first but not only pokenode in pokedex
    if (temp == pokedex->curr_selected) {
        struct pokenode *curr = pokedex->curr_selected;
        pokedex->head = temp->next;
        pokedex->curr_selected = temp->next;
        destroy_pokemon(curr->pokemon);
        free(curr);
        return;
    }
    // if currently selected is the final but not only pokenode in pokedex
    while (temp->next->pokemon != pokedex->curr_selected->pokemon) {
        temp = temp->next;
    }
    if (pokedex->curr_selected->next == NULL) {
        struct pokenode *curr = pokedex->curr_selected;
        pokedex->curr_selected = temp;
        pokedex->curr_selected->next = NULL;
        destroy_pokemon(curr->pokemon);
        free(curr);
    // if pokenode is not first or last in multi-node pokedex
    } else {
        temp->next = pokedex->curr_selected->next;
        struct pokenode *curr = pokedex->curr_selected;
        pokedex->curr_selected = pokedex->curr_selected->next;
        destroy_pokemon(curr->pokemon);
        free(curr);
    }
}

// Destroy the given Pokedex and free all associated memory.
void destroy_pokedex(Pokedex pokedex) {
    if (pokedex->head != NULL) {
        struct pokenode *temp = pokedex->head;
        while (temp->next != NULL) {
            struct pokenode *curr = temp;
            temp = temp->next;
            destroy_pokemon(curr->pokemon);
            free(curr);
        }
        destroy_pokemon(temp->pokemon);
        free(temp);
        free(pokedex);
    } else {
        free(pokedex);
    }
}

//////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                        //
//////////////////////////////////////////////////////////////////////

// Print out all of the different types of Pokemon in the Pokedex.
void show_types(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        return;
    }
    struct pokenode *temp = pokedex->head;
    struct pokenode *curr = pokedex->head;
    int listed_types[MAX_TYPE];
    int i = 0;
    if (pokemon_first_type(temp->pokemon) != NONE_TYPE) {
        listed_types[i] = pokemon_first_type(temp->pokemon);
    }
    if (pokemon_second_type(temp->pokemon) != NONE_TYPE) {
        i++;
        listed_types[i] = pokemon_second_type(temp->pokemon);
    }
    temp = temp->next;
    while (temp != NULL) {
        while (curr != temp) {
            if (
                pokemon_first_type(temp->pokemon) != NONE_TYPE &&
                pokemon_first_type(temp->pokemon) != pokemon_first_type(curr->pokemon) &&
                pokemon_first_type(temp->pokemon) != pokemon_second_type(curr->pokemon)
            ) {
                int j = 0;
                while (j <= i && j != -1) {
                    if (pokemon_first_type(temp->pokemon) != listed_types[j]) {
                        j++;
                    } else {
                        j = -1;
                    }
                }
                if (j != -1) {
                    i++;
                    listed_types[i] = pokemon_first_type(temp->pokemon);
                }
            }
            if (
                pokemon_second_type(temp->pokemon) != NONE_TYPE &&
                pokemon_second_type(temp->pokemon) != pokemon_first_type(curr->pokemon) &&
                pokemon_second_type(temp->pokemon) != pokemon_second_type(curr->pokemon)
            ) {
                int j = 0;
                while (j <= i && j != -1) {
                    if (pokemon_second_type(temp->pokemon) != listed_types[j]) {
                        j++;
                    } else {
                        j = -1;
                    }
                }
                if (j != -1) {
                    i++;
                    listed_types[i] = pokemon_second_type(temp->pokemon);
                }
            }
            curr = curr->next;
        }
        temp = temp->next;
        curr = pokedex->head;
    }
    int k = 0;
    while (k <= i) {
        printf("%s\n", pokemon_type_to_string(listed_types[k]));
        k++;
    }
}

// Set the first not-yet-found Pokemon of each type to be found.
void go_exploring(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        return;
    }
    struct pokenode *temp = pokedex->head;
    int listed_types[MAX_TYPE];
    int i = 0;
    while (temp->found == FOUND) {
        temp = temp->next;
    }
    listed_types[i] = pokemon_first_type(temp->pokemon);
    temp->found = FOUND;
    if (pokemon_second_type(temp->pokemon) != NONE_TYPE) {
        i++;
        listed_types[i] = pokemon_second_type(temp->pokemon);
    }
    while (temp != NULL) {
        int j = 0;
        if (temp->found == NOT_FOUND) {
            while (j <= i && j != -1) {
                if (pokemon_first_type(temp->pokemon) != listed_types[j]) {
                    j++;
                } else {
                    j = -1;
                }
            }
            if (j > i) {
                i++;
                listed_types[i] = pokemon_first_type(temp->pokemon);
                temp->found = FOUND;
            }
            if (pokemon_second_type(temp->pokemon) != NONE_TYPE) {
                j = 0;
                while (j <= i && j != -1) {
                    if (pokemon_second_type(temp->pokemon) != listed_types[j]) {
                        j++;
                    } else {
                        j = -1;
                    }
                }
                if (j > i) {
                    i++;
                    listed_types[i] = pokemon_second_type(temp->pokemon);
                    temp->found = FOUND;
                }
            }
            temp = temp->next;
        } else {
            temp = temp->next;
        }
    }
}

// Return the total number of Pokemon in the Pokedex.
int count_total_pokemon(Pokedex pokedex) {
    int total_pokemon = 0;
    struct pokenode *temp = pokedex->head;
    while (temp != NULL) {
        total_pokemon++;
        temp = temp->next;
    }
    return total_pokemon;
}

// Return the number of Pokemon in the Pokedex that have been found.
int count_found_pokemon(Pokedex pokedex) {
    int total_found = 0;
    struct pokenode *temp = pokedex->head;
    while (temp != NULL) {
        if (temp->found == FOUND) {
            total_found++;
        }
        temp = temp->next;
    }
    return total_found;
}

//////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                        //
//////////////////////////////////////////////////////////////////////

// Add the information that the Pokemon with the ID `from_id` can
// evolve into the Pokemon with the ID `to_id`.
void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    if (pokedex->head == NULL) {
        return;
    }
    int i = 0;
    struct pokenode *from_pokemon = pokedex->head;
    while (from_pokemon != NULL && i != -1) {
        if (pokemon_id(from_pokemon->pokemon) == from_id) {
            i = -1;
        } else {
            from_pokemon = from_pokemon->next;
        }
    }
    struct pokenode *to_pokemon = pokedex->head;
    i = 0;
    while (to_pokemon != NULL && i != -1) {
        if (pokemon_id(to_pokemon->pokemon) == to_id) {
            i = -1;
        } else {
            to_pokemon = to_pokemon->next;
        }
    }
    if (
        from_pokemon == NULL || 
        to_pokemon == NULL || 
        (pokemon_id(from_pokemon->pokemon) == pokemon_id(to_pokemon->pokemon))
    ) {
        printf("Invalid evolution. Exiting pokedex.\n");
        exit(1);
    }
    
    from_pokemon->evolution = to_pokemon;
}

// Show the evolutions of the currently selected Pokemon.
void show_evolutions(Pokedex pokedex) {
    struct pokenode *curr = pokedex->curr_selected;
    if (pokedex->head == NULL) {
        return;
    }
    while (curr != NULL) {
        printf("#");
        print_ID(curr->pokemon);
        if (curr->found == FOUND) {
            printf(" %s ", pokemon_name(curr->pokemon));
            if (pokemon_second_type(curr->pokemon) == NONE_TYPE) {
                printf(
                    "[%s]", 
                    pokemon_type_to_string(pokemon_first_type(curr->pokemon))
                );
            } else {
                printf(
                    "[%s, %s]", 
                    pokemon_type_to_string(pokemon_first_type(curr->pokemon)), 
                    pokemon_type_to_string(pokemon_second_type(curr->pokemon))
                );
            }
        } else {
            printf(" ???? [????]");
        }
        if (curr->evolution != NULL) {
            printf(" --> ");
        }
        curr = curr->evolution;
    }
    printf("\n");
}

// Return the pokemon_id of the Pokemon that the currently selected
// Pokemon evolves into.
int get_next_evolution(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        printf("No pokenodes in pokedex. Exiting pokedex.");
        exit(1);
    } else if (pokedex->curr_selected->evolution == NULL) {
        return DOES_NOT_EVOLVE;
    } else {
        struct pokenode *next_evol = pokedex->curr_selected->evolution;
        int evolution_id = pokemon_id(next_evol->pokemon);
        return evolution_id;
    }
}

//////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                        //
//////////////////////////////////////////////////////////////////////

// Create a new Pokedex which contains only the Pokemon of a specified
// type from the original Pokedex.
Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    Pokedex type_pokedex = new_pokedex();
    if (pokedex->head == NULL) {
        return type_pokedex;
    }
    struct pokenode *temp = pokedex->head;
    Pokemon new_pokemon;
    while (temp != NULL) {
        if (
            temp->found == FOUND && 
            (pokemon_first_type(temp->pokemon) == type || 
            pokemon_second_type(temp->pokemon) == type)
        ) {
            new_pokemon = clone_pokemon(temp->pokemon);
            add_pokemon(type_pokedex, new_pokemon);
        } else {
            temp = temp->next;
        }
    }
    // set all pokenode in new pokedex to found
    struct pokenode *curr = type_pokedex->head;
    while (curr != NULL) {
        curr->found = FOUND;
        curr = curr->next;
    }
    return type_pokedex;
}

// Create a new Pokedex which contains only the Pokemon that have
// previously been 'found' from the original Pokedex.
Pokedex get_found_pokemon(Pokedex pokedex) {
    Pokedex found_pokedex = new_pokedex();
    if (pokedex->head == NULL) {
        return found_pokedex;
    }
    struct pokenode *temp = pokedex->head;
    Pokemon new_pokemon;
    while (temp != NULL) {
        if (temp->found == FOUND) {
            new_pokemon = clone_pokemon(temp->pokemon);
            add_ordered(found_pokedex, new_pokemon);            
            temp = temp->next;
        } else {
            temp = temp->next;
        }
    }
    return found_pokedex;
}

// Create a new Pokedex containing only the Pokemon from the original
// Pokedex which have the given string appearing in its name.
Pokedex search_pokemon(Pokedex pokedex, char *text) {
    fprintf(stderr, "exiting because you have not implemented the search_pokemon function\n");
    exit(1);
}

// Add definitions for your own functions here.

// Prints pokemon ID
static void print_ID(Pokemon pokemon) {
    if (pokemon_id(pokemon) < 10) {
        printf("00%d", pokemon_id(pokemon));
    } else if (pokemon_id(pokemon) > 9 && pokemon_id(pokemon) < 100) {
        printf("0%d", pokemon_id(pokemon));
    } else if (pokemon_id(pokemon) > 99) {
        printf("%d", pokemon_id(pokemon));
    }
}

// Prints name in asterix for pokemon not found
static void ast_name(char *name) {
    int strlength = 0;
    while (name[strlength] != '\0' && name[strlength] != '\n') {
        printf("*");
        strlength++;
    }
    printf("\n");
}

// Prints details of a found pokemon
static void detail_found(Pokedex pokedex) {
    printf("Name: %s\n", pokemon_name(pokedex->curr_selected->pokemon));
    printf("Height: %0.1lfm\n", pokemon_height(pokedex->curr_selected->pokemon));
    printf("Weight: %0.1lfkg\n", pokemon_weight(pokedex->curr_selected->pokemon));
    if (pokemon_second_type(pokedex->curr_selected->pokemon) != NONE_TYPE) {
        printf(
            "Type: %s %s\n", 
            pokemon_type_to_string(pokemon_first_type(pokedex->curr_selected->pokemon)), 
            pokemon_type_to_string(pokemon_second_type(pokedex->curr_selected->pokemon))
        );
    } else {
        printf(
            "Type: %s\n", 
            pokemon_type_to_string(pokemon_first_type(pokedex->curr_selected->pokemon))
        );
    }
}

// Prints details of a not yet found pokemon
static void detail_not_found(Pokedex pokedex) {
    printf("Name: ");
    ast_name(pokemon_name(pokedex->curr_selected->pokemon));
    printf("Height: --\n");
    printf("Weight: --\n");
    printf("Type: --\n");
}

// Adds a pokemon to a pokedex in order of pokemon_id
static void add_ordered(Pokedex pokedex, Pokemon pokemon) {
    struct pokenode *curr = pokedex->head;
    struct pokenode *prev = pokedex->head;
    struct pokenode *new = new_found_pokenode(pokemon);
    new->found = FOUND;
    // New pokenode added to empty pokedex
    if (curr == NULL) {
        pokedex->head = new;
        pokedex->curr_selected = pokedex->head;
        return;
    // New pokenode added added to beginning of pokedex
    } else if (pokemon_id(pokemon) < pokemon_id(curr->pokemon)) {
        new->next = curr;
        pokedex->head = new;
        pokedex->curr_selected = new;
        return;
    } else {
        while (curr != NULL && pokemon_id(pokemon) > pokemon_id(curr->pokemon)) {
            prev = curr;
            curr = curr->next;
        }
        // New pokenode being added at the end of pokedex
        if (curr == NULL) {
            prev->next = new;
        // New pokenode being added somewhere in the middle
        } else {
            prev->next = new;
            new->next = curr;
        }
    }
}

// Same as add_pokemon but sets it as FOUND instead of for stage 5
static void add_found_pokemon(Pokedex pokedex, Pokemon pokemon) {
    struct pokenode *curr = pokedex->head;
    if (curr == NULL) {
        pokedex->head = new_found_pokenode(pokemon);
        pokedex->curr_selected = pokedex->head;
        return;
    } else if (curr != NULL && curr->next == NULL) {
        curr->next = new_found_pokenode(pokemon);
        return;
    }
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_found_pokenode(pokemon);
}






