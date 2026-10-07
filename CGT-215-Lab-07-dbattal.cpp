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
	ball.setCenter(Vector2f(110, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	//initial velocity towards the right/center 
	ball.applyImpulse(Vector2f(0.6, 0));
	
	// we have a floor setting the position and size 
	PhysicsRectangle floor;
	floor.setSize(Vector2f(759, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true); 
	world.AddPhysicsBody(floor);

	//BOOM we have a ceiling too
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(759, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	//BABOOM and we have a left wall
	PhysicsRectangle leftwall;
	leftwall.setSize(Vector2f(20, 600));
	leftwall.setCenter(Vector2f(10, 300));
	leftwall.setStatic(true);
	world.AddPhysicsBody(leftwall);

	//BOOMBBOOM we have a right wall wowowow
	PhysicsRectangle rightwall;
	rightwall.setSize(Vector2f(20, 600));
	rightwall.setCenter(Vector2f(790, 300));
	rightwall.setStatic(true);
	world.AddPhysicsBody(rightwall);

	//and we have a center! setting it as the visual center and sizing it
	PhysicsRectangle center;
	center.setSize(Vector2f(100, 100));
	center.setCenter(Vector2f(400, 300));
	center.setStatic(true);
	world.AddPhysicsBody(center);

	//all four walls have the thud counter, "thud" is printed out with every wall bounce 
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

	//separate counter "bang" for the center box/rectangle. "bang" isprinted out every center bounce 
	int bangCount(0);
	center.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang" << bangCount << endl;
		bangCount++;
		if (bangCount >= 3) {
			exit(0);
		}
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
		window.draw(ceiling);
		window.draw(leftwall);
		window.draw(rightwall);
		window.draw(center);
		window.display();
	}
}