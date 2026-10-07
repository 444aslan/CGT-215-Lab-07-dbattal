#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	//creating the window and wrold with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	
	//creating the ball and starting it to the left of the center rectangle/box 
	PhysicsCircle ball;
	ball.setCenter(Vector2f(100, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	//initial velocity towards the right/center 
	ball.applyImpulse(Vector2f(0.5, 0));
	
	//BOOM we have a floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true); 
	world.AddPhysicsBody(floor);

	//BOOM we have a ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(790, 300));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	//BABOOM we have a left wall
	PhysicsRectangle leftwall;
	leftwall.setSize(Vector2f(20, 600));
	leftwall.setCenter(Vector2f(10, 300));
	leftwall.setStatic(true);
	world.AddPhysicsBody(leftwall);

	//BOOMBBOOM we have a right wall wowowow
	PhysicsRectangle rightwall;
	rightwall.setSize(Vector2f(20, 600));
	rightwall.setCenter(Vector2f(10, 300));
	rightwall.setStatic(true);
	world.AddPhysicsBody(rightwall);

	//and we have a center brother
	PhysicsRectangle center;
	center.setSize(Vector2f(100, 100));
	center.setCenter(Vector2f(400, 300));
	center.setStatic(true);
	world.AddPhysicsBody(center);

	//all four walls have the shared thud counter 
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	leftwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	rightwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.display();
	}
}