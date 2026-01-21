// Not really finished yet.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

enum suit_e { SPADES, DIAMONDS, CLUBS, HEARTS };
enum rank_e { ACE, KING, QUEEN, JACK, TEN, NINE, EIGHT, SEVEN, SIX, FIVE, FOUR, THREE, TWO };
enum deck_type_e { NDO };

// Cards have a suit and rank
// They can only ever be of a suit or rank
struct card_s {
	enum suit_e suit;
	enum rank_e rank;
};

// Decks have metadata and an array containing cards
struct deck_s {
	uint32_t size;
	struct card_s cards[];
};


void push(struct deck_s* deck, struct card_s c) {

}

// Creates a deck of cards
// Default type is 'n', or New Deck Order
void create_deck() {

	void * cards = malloc( sizeof( struct card_s ) * 52 );
	struct deck_s deck = { 52, *cards };

	for (int suit = 0; suit < 3; suit++) {
		for (int rank = 0; rank < 12; rank++) {

			struct card_s new_card = { .suit = suit, .rank = rank };
			push(deck, new_card);

		}
	}
}

int main() {

}
