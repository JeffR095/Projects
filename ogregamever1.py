def show_status(player_location, inventory, rooms):
    """
    Display the player's current status, including their location,
    inventory, and any item available in the current room.
    """
    print("\n--- Player Status ---")
    print(f"You are in the {player_location}")
    print(f"Inventory: {', '.join(inventory) if inventory else 'Empty'}")
    item = rooms[player_location].get("item")
    if item:
        print(f"Item in this room: {item}")
    else:
        print("No items in this room.")
    print("----------------------\n")

def show_commands(player_location, rooms):
    """
    Display the list of commands the player can use, including only
    the available directions based on the current room.
    """
    print("Available commands:")

    # Get available directions based on the current room
    available_directions = [direction for direction in rooms[player_location] if direction != "item"]

    if available_directions:
        print(f"- go [{', '.join(available_directions)}]")

    print("- get [item name] (if an item is in the current room)")
    print("- check status (to see your current status)")
    print("- quit (to end the game)")

def main():
    rooms = {
        "Security Office": {"West": "Locker Room", "South": "Indoor Range", "item": None},
        "Locker Room": {"East": "Security Office", "West": "Kitchen", "item": "ID badge"},
        "Kitchen": {"East": "Locker Room", "item": "treat"},
        "Indoor Range": {"North": "Security Office", "South": "Armory Lockup", "West": "Chemical Lab", "item": "grenade casing"},
        "Armory Lockup": {"North": "Indoor Range", "item": "tranquilizer launcher"},
        "Chemical Lab": {"East": "Indoor Range", "West": "Operations Office", "item": "immobilizing agent"},
        "Operations Office": {"East": "Chemical Lab", "South": "Containment Room", "item": "vault combination"},
        "Containment Room": {"North": "Operations Office", "item": None}  # Villain Room
    }

    # Game state variables
    player_location = "Security Office"
    inventory = []
    required_items = ["tranquilizer launcher", "immobilizing agent", "grenade casing", "treat", "ID badge", "vault combination"]
    max_turns = 20
    turns_used = 0
    game_over = False
    correct_combination = "6589"
    max_combination_attempts = 3

    while not game_over:
        show_status(player_location, inventory, rooms)
        show_commands(player_location, rooms)  # Pass player_location and rooms here

        # Get player input
        player_input = input("Enter your command: ").strip().lower()

        if player_input.startswith("go "):
            direction = player_input[3:].capitalize()
            if direction in rooms[player_location]:
                player_location = rooms[player_location][direction]
                turns_used += 1
                print(f"You move to the {player_location}")
            else:
                print("You cannot go that way from here.")
        elif player_input.startswith("get "):
            item_name = player_input[4:]
            item = rooms[player_location].get("item")
            if item and item.lower() == item_name:
                inventory.append(item)
                rooms[player_location]["item"] = None
                print(f"You picked up the {item_name}.")
            else:
                print("That item is not here.")
        elif player_input == "check status":
            show_status(player_location, inventory, rooms)
        elif player_input == "quit":
            print("Thanks for playing!")
            game_over = True
        else:
            print("Invalid command. Please try again.")

        # Timer check
        if turns_used >= max_turns and not game_over:
            print("Time’s up! The ogre escaped while you were preparing.")
            print("Game Over.")
            game_over = True

if __name__ == "__main__":
    main()
