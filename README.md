# Fantasy Combat RPG

This program is an RPG game where the user takes control of a character on a grid that serves as a gameboard. The ultimate goal is to defeat the boss without dying and within the move limit of 50 moves. In order to reach the boss, the player must first find the key to unlock the boss's chambers. Each space the player lands on has the chance to trigger several events, including fighting an enemy or picking up an item.

## Symbols
```
+: Character
!: Boss
K: Key
?: Item
#: Border
```

## Combat System

Each combat between 2 characters ends when one of the characters die.

Each round consists of two attacks, one for each character. For each attack, attacker and defender both generate dice rolls. The type and number of dice for each character is listed below.

The actual damage inflicted from the attacker onto the defender is calculated as follows:

Damage = attacker’s roll – defender’s roll – defender’s armor

Then the value of that damage is subtracted from the defender’s strength points.


Example: 
```
Character A attacks with dice roll of: 8 10, which means it has an attack of 18,
and character B defends with dice roll of 5 6, which means it has defense of 11,
character B also has an armor of 3. So the actual damage inflicted from A to B
is 18 – 11 – 3 = 4.

If character B has strength point of 8 during that round, the new strength point
would be 8 – 4 = 4, which means next round B will have strength point of 4.

If character B has strength point of 3 during that round, the new strength point 
would be 3 – 4 = -1, which means character B dies.
```

## Player and Enemies

Note: “1d12” means rolling one 12-sided die, and “2d6” means rolling 2 6-sided dice, etc.

### Player
```
Attack: 1d16
Defense: 2d6
Armor: 0
Strength Points: 40
Special Ability: Second Wind - If an attack were to kill a player, the player will get a 
second wind and come back with 10 hp. This ability can only be used once per game.
```

### Vampire
```
Attack: 1d12
Defense: 1d6
Armor: 1
Strength Points: 18
Special Ability: Charm - Vampires can charm an opponent into not attacking. 
For a given attack there is a 50% chance that their opponent does not actually attack them.
```

### Barbarian
```
Attack: 2d6
Defense: 2d6
Armor: 0
Strength Points: 12
Special Ability: None
```

### Medusa
```
Attack: 2d6
Defense: 1d6
Armor: 3
Strength Points: 8
Special Ability: Glare - If a Medusa rolls a 12 when attacking then the target 
instantly gets turned into stone and Medusa wins! If Medusa uses Glare on the player 
when they have second wind, then second wind is used.
```

### Blue Men(Boss)
```
Attack: 2d10
Defense: 3d6
Armor: 3
Strength Points: 12
Special Ability: Mob - Blue Men are actually a swarm of small individuals. 
For every 4 points of damage, they lose one defense die. 
For example, if they have a strength of 8, they would have 2d6 for defense.
```

## Items
Note: The player can only have 6 items in their inventory at one time.
```
Potion: Raises the player's HP by 50% of their current HP or to max HP, whichever is lower.
Sword: Raise the player's bonus attack by 3.
Armor: Raise the player's armor by 3.
Key: Key to unlock the bosses room.
```

### Notes

    If Medusa uses “glare” on Harry Potter on his first life, 
    then Harry Potter comes back to life after using “hogwarts”.
    
    If the Vampire’s “charm” ability activates when Medusa uses “glare”, 
    the Vampire’s charm trumps Medusa’s glare.

## Installing and Running the Program

Compile the program with this command:

```
make rpg
```

Run the program with this command:

```
./rpg
```

Clean files with this command:

```
make rpg
```

## Built With

* C++
