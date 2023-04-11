# Requirements - Yukon Solitaire

## Meta

The report requirements for the game Yukon Solitaire.

![Report requirements](./report-requirements.png)

## Visual

![Game board layout\label{layout-board}](./layout.png)

This is what the game should look like.

- 7 horizontal rows

- 4 groups on the right side

- Console info at the bottom
  - LAST Command: The last command entered
  - Message: Any messages from the game
  - INPUT > : Where the user enters commands

## Commands (Console Input)

## Rules

To play Yukon Solitaire, the entire deck is dealt into 7 columns of 1, 6, 7, 8, 9, 10, and 11 cards from left to right.

At the start the cards are dealt in the following way.

- C1: 1 card - 1 visible
- C2: 6 card - 5 visible
- C3: 7 card - 5 visible
- C4: 8 card - 5 visible
- C5: 9 card - 5 visible
- C6: 10 card - 5 visible
- C7: 11 card - 5 visible

Game is won by moving all cards into the four foundations arranged by suit and in order from Ace - King.

Cards can be moved between the columns by placing a card (and the eventual cards below it) from a column to a new column, below the bottom card from that column, if that card that has a value one greater than the card that we want to move but is not of the same suit (it can also have the same color but from a different suit). If there are no cards below a hidden card on a column, then the card becomes visible. Once all cards are moved to the foundations, the player wins.
