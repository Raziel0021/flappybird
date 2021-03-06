#include "menu.h"

#include "Logic/game.h"
#include "Utility/buttons.h"
#include "Characters/Player/player.h"
namespace flappybird {
	namespace menu {
		using namespace game;

		//Images
		Texture2D menu_bg;
		Texture2D menu_title;

		Vector2 title_position;

		buttons::BTNTEX play;
		buttons::BTNTEX play2;
		buttons::BTNTEX credits;
		buttons::BTNTEX quit;

		void init() {
			menu_bg = LoadTexture("res/assets/Textures/GAMEPLAY_BG.png");
			menu_title = LoadTexture("res/assets/Textures/TITLE_MENU.png");
			players::twoPlayers = false;
			title_position = { (float)GetScreenWidth() / 2 - menu_title.width / 2,50 };

			play.btn_texture = LoadTexture("res/assets/Textures/PLAY_BTN.png");
			play2.btn_texture = LoadTexture("res/assets/Textures/2PLAYERS_BTN.png");
			credits.btn_texture = LoadTexture("res/assets/Textures/CREDITS_BTN.png");
			quit.btn_texture = LoadTexture("res/assets/Textures/QUIT_BTN.png");
			play.btnOnHover_texture = LoadTexture("res/assets/Textures/PLAYONHOVER_BTN.png");
			play2.btnOnHover_texture = LoadTexture("res/assets/Textures/2PLAYERSHOVER_BTN.png");
			credits.btnOnHover_texture = LoadTexture("res/assets/Textures/CREDITSONHOVER_BTN.png");
			quit.btnOnHover_texture = LoadTexture("res/assets/Textures/QUITONHOVER_BTN.png");

			buttons::createButton(play, play.btn_texture.height, play.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - play.btn_texture.width / 2), 
				                 (float)(GetScreenHeight() - 400), WHITE);

			buttons::createButton(play2, play2.btn_texture.height, play2.btn_texture.width,
				(float)(GetScreenWidth() / 2 - play2.btn_texture.width / 2),
				(float)(GetScreenHeight() - 330), WHITE);

			buttons::createButton(credits, credits.btn_texture.height, credits.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - credits.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 260), WHITE);

			buttons::createButton(quit, quit.btn_texture.height, quit.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - quit.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 190), WHITE);

		}

		void update(bool &endGame) {
			Vector2 mousePoint = GetMousePosition();

			buttons::isMouseOverButton(play);
			if (CheckCollisionPointRec(mousePoint, play.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
				}
			}

			buttons::isMouseOverButton(play2);
			if (CheckCollisionPointRec(mousePoint, play2.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
					players::twoPlayers = true;
				}
			}

			buttons::isMouseOverButton(credits);
			if (CheckCollisionPointRec(mousePoint, credits.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Credits;
				}
			}

			buttons::isMouseOverButton(quit);
			if (CheckCollisionPointRec(mousePoint, quit.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					endGame = true;
				}
			}
		}

		void draw() {
			ClearBackground(WHITE);

			//Draw UI
			DrawTexture(menu_bg,0,0,WHITE);
			DrawTexture(menu_title, title_position.x, title_position.y, WHITE);

			//Draw buttons
			buttons::draw(play);
			buttons::draw(play2);
			buttons::draw(credits);
			buttons::draw(quit);
			DrawText("v1.0", screenWidth - 50, screenHeight - 20, 20, WHITE);
		}

		void deInit() {
			//images
			UnloadTexture(menu_bg);
			UnloadTexture(menu_title);
			//buttons
			UnloadTexture(play.btn_texture);
			UnloadTexture(play2.btn_texture);
			UnloadTexture(credits.btn_texture);
			UnloadTexture(quit.btn_texture);
			UnloadTexture(play.btnOnHover_texture);
			UnloadTexture(play2.btnOnHover_texture);
			UnloadTexture(credits.btnOnHover_texture);
			UnloadTexture(quit.btnOnHover_texture);	
		}
	}
}

