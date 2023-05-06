# Requirements

1. The game should have a graphical user interface with the following components:
   - 7 horizontal rows for the columns of cards
   - 4 groups on the right side for the foundations
   - Console info at the bottom showing the LAST CommandType and any messages from the game
   - INPUT > prompt where the user can enter commands
2. The game should support the following commands (Console Input) in all phases:
   - LD <filename>: Load cards from <filename>. If no filename is given, load from cards.txt
   - SW: Shows cards on the terminal in the order they are placed in the deck
   - SI <split>: Shuffle Interleaved. <split> is optional and determines the size of pile 1. The rest of the cards are put into pile 2. When one of the piles is empty, the remaining cards are put into the BOTTOM of pile 3.
   - SR: Shuffles cards in a random manner by taking one card from deck and putting it into random position in a new empty pile.
   - SD <filename>: Save to <filename>. If no filename is given, save to cards.txt
   - QQ: Quit program
3. The game should support the following commands (Console Input) in the Play phase:
   - Q: Go to startup phase
   - \<from> -> \<to>: Make a move by moving a card (and the eventual cards below it) from <from> to <to>. <from> can be a column number (C1 to C7) or a foundation number (F1 to F4). <to> is a column number (C1 to C7).
4. The game should also support the following optional commands in the Play phase:
   - U: Undo the last move
   - R: Redo the last move
   - S <filename>: Save the game state to <filename>
   - L <filename>: Load the game state from <filename>
5. The game should follow the general rules of Yukon Solitaire. 
   - The game should be won by moving all cards into the four foundations arranged by suit and in order from Ace to King. 
   - Cards can be moved between the columns by placing a card (and the eventual cards below it) from a column to a new column, below the bottom card from that column, if that card has a value one greater than the card that we want to move but is not of the same suit. 
   - If there are no cards below a hidden card on a column, then the card becomes visible. 
   - Once all cards are moved to the foundations, the player wins.
# Analysis
1. User Interface Requirements
   - The game should have a text-based interface with a command line prompt for input.
   - The game should display the following elements:
   - Seven horizontal rows of cards, representing the seven columns of the game.
   - Four foundation piles on the right side of the screen.
   - Console information at the bottom of the screen, including:
   - The last command entered by the user.
   - Any messages from the game.
   - A prompt for user input.
2. Game Functionality Requirements
   - The game should start in the "Startup" phase, during which the player can use the following commands:
   - "LD" to load card data from a file.
   - "SW" to show the cards in the order they are placed in the deck.
   - "SI" to shuffle the cards in an interleaved manner, with an optional parameter to determine the size of the first pile.
   - "SR" to shuffle the cards in a random manner.
   - "SD" to save card data to a file.
   - "P" to go to the "Play" phase.
   - "QQ" to quit the program.
   - The game should then move to the "Play" phase, during which the player can use the following commands:
   - "\<from> -> \<to>" to move cards from one column to another.
   - "Q" to return to the "Startup" phase.
   - "U" to undo the last move.
   - "R" to redo the last undone move.
   - "S <filename>" to save the game state to a file.
   - "L <filename>" to load a saved game state from a file.
   - The game should enforce the following rules:
   - The deck should be dealt into 7 columns of 1, 6, 7, 8, 9, 10, and 11 cards from left to right.
   - The game is won by moving all cards into the four foundation piles, arranged by suit and in order from Ace to King.
   - Cards can be moved between columns by placing a card (and the cards below it) from a column to a new column, below the bottom card from that column, if that card has a value one greater than the card that is being moved but is not of the same suit (it can also have the same color but from a different suit).
   - If there are no cards below a hidden card on a column, then the card becomes visible.
   - Once all cards are moved to the foundations, the player wins.
3. Implementation Requirements
   - The game should use appropriate data structures (e.g. linked lists, structs).
   - The game should use functions to modularize the code and make it easier to maintain and test.
   - The game should have appropriate error handling to deal with unexpected inputs or actions.
   - The game should have appropriate commenting and documentation to make it easy for other developers to understand and work on the code.

# Design 


# Implementation


# Tests 


# Conclusion 


# Contribution


# Appendix