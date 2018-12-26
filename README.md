# GREEDY CRASH v0.1
Greedy Crash is a cars fighting game for two players where the objective is to make the opponent lose all its coins.

This game was developed by students Jaume Avinyó and Lucho Suaya for Physics II subject in Game Design and Development degree of UPC, Barcelona (CITM School).

## Instructions & Controls
Player 1 moves the car with Arrow keys and boosts with Right Control. Y key to reset car position (costs 2 coins).

Player 2 moves the car with WASD keys and boosts with Left Shift. T key to reset car position (costs 2 coins).

All the UI information is on the window title. From main menu and game over screen switch to game scene with SPACEBAR.

ESC key to quit at any moment.

## Gameplay
When the game starts, 10 coins appear randomly on the ground. Each time one coin is taken, another will appear, with 10 coins always scattered on the floor.

Each player starts with 6 coins and can accumulate up to a maximum of 12. Every 3 coins, the turbo is filled, and each time it hits the opponent with the turbo stall and going to a minimum speed of 150 km/h, the opponent lose 2 coins.

The objective is to get the opponent to lose all its coins, but be careful, restarting the position of the car, flying very high or leaving the boundaries of the terrain, will also subtract 2 coins so skillfully use the obstacles of the field (both to attack and to protect yourself).

### Debug Keys
-F1 to activate/deactivate debug mode (only in debug compilation)
-F2 to fill both cars boost
-F3 to add each player a coin
-F4 to launch a ball from camera position (to test collisions, only in debug compilation)
-IJKL to move camera
-UH to control camera height
-N to boost camera movement
-Right Mouse Button + Mouse movement to look around with the   camera

## Game Special Details
-Cars light their lights when moving forward/backward
-Music altered to make the loops unnoticeable

## Developers & GitHub web
-Lucho Suaya - @lucho1
-Jaume Avinyó - @jas3
-Project Github: https://github.com/lucho1/GreedyCrash-Project

## Credits
Music by Loquillo and Desgraciaus and modified by Lucho Suaya. Done with SDL, OpenGL, Bullet Library and Visual Studio. Game licensed under a MIT License (see full license at game folder or github repository). By Lucho Suaya and Jaume Avinyó.




