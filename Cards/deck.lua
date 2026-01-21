DECK = {}
SUITS = { "Spades", "Diamonds", "Clubs", "Hearts" }
RANKS = { "Ace", "King", "Queen", "Jack", "Ten", "Nine", "Eight", "Seven", "Six", "Five", "Four", "Three", "Two" }

-- If given a number, returns the index of the enum
-- If given a non number, attempts to find value and returns the index
local function find(t, e)
	if type(e) == "number" and e <= #t and e > 0 then
		local index = math.floor(e)
		return t[index]
	else
		for key, value in pairs(t) do
			if value == e then
				return key
			end
		end
	end
end

local function CheckCard(card)
	assert(type(card) == "table")

	if not find(SUITS, card[1]) or not find(RANKS, card[2]) then
		return false
	end

	return true
end

-- card[1] is suit
-- card[2] is rank
local function CreateCard(suit, rank)
	assert(suit and rank)
	local card = { suit, rank }

	if CheckCard(card) then
		return card
	else
		return false
	end
end

local function AddCard(deck, card)
	if card ~= false then
		table.insert(deck, card)
	end
end

local function Draw(deck)
	return table.remove(deck)
end

local function PrintCard(card)
	local rank = RANKS[card[2]]
	local suit = SUITS[card[1]]
	print(rank .. " of " .. suit)
end

local function PrintDeck(deck)
	print("Deck size: " .. #deck)
	for i = 1, #deck do
		local card = deck[i]
		PrintCard(card)
	end
end

local function CreateDeck()
	local deck = {}

	for suit = 1, #SUITS do
		for rank = 1, #RANKS do
			local card = CreateCard(suit, rank)
			AddCard(deck, card)
		end
	end

	return deck
end

-- Knuth's shuffling algorithm in Lua
local function Shuffle(deck)
	local shuf = {}

	for i = #deck, 1, -1 do
		local j = math.random(1, i)

		local temp = deck[i]
		deck[i] = deck[j]
		deck[j] = temp
	end
end

local function Peek(deck)
	PrintCard(deck[1])
end

math.randomseed(os.time())

local newDeck = CreateDeck()
PrintDeck(newDeck)
Shuffle(newDeck)
PrintDeck(newDeck)
