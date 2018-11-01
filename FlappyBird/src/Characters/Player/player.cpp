#include "player.h"

#include "Characters\Enemys\columns.h"
#include "Logic\game.h"
#include "Utility\animations.h"

namespace flappybird {
	namespace players {
		using namespace columns_enemys;
		using namespace game;

		Player player;
		Player player2;
		Sound birdFlap;
		Sound birdHit;
		bool twoPlayers;
		bool isDead,isDead2;
		bool deadSFX;
		float delayTime = 0.1f;
		static int currentFrame = 0;
		static int currentFrame2 = 0;
		const int GRAVITY = 2000;
		const int PLAYER_ON_CLICK_ROTATION = -45;
		const int GRAVITY_ROTATION = 250;
		const float PLAYER_SPEED = -500;
		
		static float timer; //Animations coming soon

		void init() {
			//player 1
			player.texture = LoadTexture("res/assets/Textures/space_ship.png");
			player.position = { (float)GetScreenWidth() / 2 - player.texture.width / 2 - 200,
								(float)GetScreenHeight() / 2 - player.texture.height / 2 };
			player.color = WHITE;
			player.acceleration = {0,0};
			player.rotation = 0;
			player.speed.x = 0;
			player.speed.y = 0;
			player.radius = (float)(player.texture.width /3)/2 - 15;
			player.score = 0;
			isDead = false;
			isDead2 = false;
			deadSFX = true;
			// NOTE: Source rectangle (part of the texture to use for drawing)
			player.sourceRec = { 0.0f, 0.0f, (float)player.texture.width / 3, (float)player.texture.height };

			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			player.destRec = { player.position.x, player.position.y, (float)player.texture.width,
				(float)player.texture.height };

			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			player.origin = { ((float)player.texture.width / 3) / 2, (float)player.texture.height / 2 };

			//player 2
			player2.texture = LoadTexture("res/assets/Textures/space_ship2.png");
			player2.position = { (float)GetScreenWidth() / 2 - player.texture.width / 2 - 200,
				(float)GetScreenHeight() / 2 - player.texture.height / 2 };
			player2.color = WHITE;
			player2.acceleration = { 0,0 };
			player2.rotation = 0;
			player2.speed.x = 0;
			player2.speed.y = 0;
			player2.radius = (float)(player.texture.width / 3) / 2 - 15;
			player2.score = 0;
			// NOTE: Source rectangle (part of the texture to use for drawing)
			player2.sourceRec = { 0.0f, 0.0f, (float)player.texture.width / 3, (float)player.texture.height };

			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			player2.destRec = { player.position.x, player.position.y, (float)player.texture.width,
				(float)player.texture.height };

			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			player2.origin = { ((float)player.texture.width / 3) / 2, (float)player.texture.height / 2 };

			//FrameTimeCounter
			timer = GetFrameTime();
			#ifdef AUDIO
				birdFlap = LoadSound("res/assets/Sound/flap.wav");
				birdHit = LoadSound("res/assets/Sound/hit.wav");
			#endif // AUDIO
		}

		void update() {
			timer += GetFrameTime();
			if (!twoPlayers) {
				// Player logic: acceleration
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isDead) {

					if (player.position.y >= player.texture.height) {
#ifdef AUDIO
						PlaySound(birdFlap);
#endif // AUDIO	
						player.rotation = PLAYER_ON_CLICK_ROTATION;
						player.speed.y = PLAYER_SPEED;

						if (player.position.y <= player.texture.height) {
							player.position.y = player.texture.height;
						}

						currentFrame = 1;
						player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
						timer = 0;
					}
				}
				else {
					if (timer > delayTime) {
						if (player.rotation < 90) {
							player.rotation += GRAVITY_ROTATION * GetFrameTime();
						}
						currentFrame = 0;
						player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
					}
				}

				if (isDead) {
					if (deadSFX) {
#ifdef AUDIO
						PlaySound(birdHit);
#endif // AUDIO		
						deadSFX = false;
					}
					currentFrame = 2;
					player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
				}

				if (player.position.y != animations::ground_collider.y) {
					player.speed.y += GRAVITY * GetFrameTime();
					player.position.y += player.speed.y * GetFrameTime();
				}
				// Collision logic: player vs ground
				if (CheckCollisionCircleRec(player.position, player.radius, animations::ground_collider)) {
					currentFrame = 2;
					player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
					player.position.y = animations::ground_collider.y;
					isDead = true;
				}
				player.destRec = { player.position.x, player.position.y, (float)player.texture.width / 3,
					(float)player.texture.height };
			}
			if (twoPlayers) {
				// Player logic: acceleration
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isDead) {

					if (player.position.y >= player.texture.height) {
#ifdef AUDIO
						PlaySound(birdFlap);
#endif // AUDIO	
						player.rotation = PLAYER_ON_CLICK_ROTATION;
						player.speed.y = PLAYER_SPEED;

						if (player.position.y <= player.texture.height) {
							player.position.y = player.texture.height;
						}

						currentFrame = 1;
						player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
						timer = 0;
					}
				}
				else {
					if (timer > delayTime) {
						if (player.rotation < 90) {
							player.rotation += GRAVITY_ROTATION * GetFrameTime();
						}
						currentFrame = 0;
						player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
					}
				}

				if (isDead) {
					if (deadSFX) {
#ifdef AUDIO
						PlaySound(birdHit);
#endif // AUDIO		
						deadSFX = false;
					}
					currentFrame = 2;
					player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
				}

				if (player.position.y != animations::ground_collider.y) {
					player.speed.y += GRAVITY * GetFrameTime();
					player.position.y += player.speed.y * GetFrameTime();
				}
				//Player2 logic:acceleration
				if (IsKeyPressed(KEY_UP) && !isDead2) {

					if (player2.position.y >= player2.texture.height) {
#ifdef AUDIO
						PlaySound(birdFlap);
#endif // AUDIO	
						player2.rotation = PLAYER_ON_CLICK_ROTATION;
						player2.speed.y = PLAYER_SPEED;

						if (player2.position.y <= player2.texture.height) {
							player2.position.y = player2.texture.height;
						}

						currentFrame2 = 1;
						player2.sourceRec.x = (float)currentFrame2*(float)player2.texture.width / 3;
						timer = 0;
					}
				}
				else {
					if (timer > delayTime) {
						if (player2.rotation < 90) {
							player2.rotation += GRAVITY_ROTATION * GetFrameTime();
						}
						currentFrame2 = 0;
						player2.sourceRec.x = (float)currentFrame2*(float)player2.texture.width / 3;
					}
				}

				if (isDead2) {
					if (deadSFX) {
#ifdef AUDIO
						PlaySound(birdHit);
#endif // AUDIO		
						deadSFX = false;
					}
					currentFrame2 = 2;
					player2.sourceRec.x = (float)currentFrame2*(float)player2.texture.width / 3;
				}

				if (player2.position.y != animations::ground_collider.y) {
					player2.speed.y += GRAVITY * GetFrameTime();
					player2.position.y += player2.speed.y * GetFrameTime();
				}
			}
			// Collision logic: player vs ground
			if (!isDead) {
				if (CheckCollisionCircleRec(player.position, player.radius, animations::ground_collider)) {
					currentFrame = 2;
					player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
					player.position.y = animations::ground_collider.y;
					isDead = true;
				}
			}
			
				// Collision logic: player2 vs ground
				if (!isDead2) {
					if (CheckCollisionCircleRec(player2.position, player2.radius, animations::ground_collider)) {
						currentFrame = 2;
						player2.sourceRec.x = (float)currentFrame*(float)player2.texture.width / 3;
						player2.position.y = animations::ground_collider.y;
						isDead2 = true;
					}
				}
			
			
			player.destRec = { player.position.x, player.position.y, (float)player.texture.width/3, 
																	 (float)player.texture.height };
			player2.destRec = { player2.position.x, player2.position.y, (float)player2.texture.width / 3,
					(float)player2.texture.height };
		}

		void draw() {
			if (!twoPlayers) {
				DrawTexturePro(player.texture, player.sourceRec, player.destRec,
					player.origin, player.rotation, player.color);
			}
			if (twoPlayers) {
				if (!isDead) {
					DrawTexturePro(player.texture, player.sourceRec, player.destRec,
						player.origin, player.rotation, player.color);
				}
				if (!isDead2) {
					DrawTexturePro(player2.texture, player2.sourceRec, player2.destRec,
						player2.origin, player2.rotation, player2.color);
				}
			}
		#ifdef _DEBUG
			if (!twoPlayers) {
				DrawCircleV(player.position, player.radius, GREEN);
			}
			if (twoPlayers) {
				if (!isDead) {
					DrawCircleV(player.position, player.radius, GREEN);
				}
				if (!isDead2) {
					DrawCircleV(player2.position, player2.radius, GREEN);
				}
			}
		#endif // DEBUG	
		}

		void deInit() {
			UnloadTexture(player.texture);
			UnloadTexture(player2.texture);
		#ifdef AUDIO
			UnloadSound(birdFlap);
			UnloadSound(birdHit);
		#endif // AUDIO

			
		}
	}
}