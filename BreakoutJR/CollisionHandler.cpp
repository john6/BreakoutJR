#include "CollisionHandler.h"

/* Old version of calculating surface normal where everything is either verticle or hoirzontal*/
sf::Vector2f CollisionHandler::CalculateBounceDir(sf::Vector2f ballDir, sf::Vector2f surfaceDir) {
	sf::Vector2f surfNorm1(-surfaceDir.y, surfaceDir.x);
	sf::Vector2f surfNorm2(surfaceDir.y, -surfaceDir.x);
	return sf::Vector2f(0.0f, 0.0f);
}

CollisionHandler::CollisionHandler() {}

CollisionHandler::~CollisionHandler() {}

sf::Vector2f CollisionHandler::DetectBallCollision(sf::CircleShape ball, sf::Vector2f ballVel, sf::RectangleShape rectSize, sf::Vector2f rectPos, bool verticle) {
	sf::Vector2f rectCenter((rectPos.x + (rectSize.getSize().x / 2)), rectPos.y + (rectSize.getSize().y / 2));
	float distX = abs(ball.getPosition().x - rectCenter.x);
	float distY = abs(ball.getPosition().y - rectCenter.y);
	float shapeWidthX = abs(ball.getRadius() + (rectSize.getSize().x / 2));
	float shapeHeightY = abs(ball.getRadius() + (rectSize.getSize().y / 2));
	if ((shapeWidthX > distX) && (shapeHeightY > distY)) {
		if (verticle) { return sf::Vector2f(-ballVel.x, ballVel.y); }
		else { return sf::Vector2f(ballVel.x, -ballVel.y); }
	}
	else { return sf::Vector2f(0.0f, 0.0f); }
}

bool CollisionHandler::DetectLineIntersection(sf::CircleShape ball, sf::Vector2f point1, sf::Vector2f point2) {
	//https://www.geeksforgeeks.org/program-find-line-passing-2-points/, https://www.geeksforgeeks.org/check-line-touches-intersects-circle/
	float a = (point2.y - point1.y);
	float b = (point1.x - point2.x);
	float constant = -((a * point1.x) + (b * point1.y));
	std::vector<float> lineInterceptForm = std::vector<float>{ a, b, constant };
	float distance = (   (abs((a * ball.getPosition().x) + (b * ball.getPosition().y) + constant)) / sqrt((a * a) + (b * b)) );
	if (ball.getRadius() > distance) { return true; }
	else { return false; }
}

float CollisionHandler::VectorLengthSqaured(sf::Vector2f point1, sf::Vector2f point2) {
	return pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2);
}

float CollisionHandler::DotProd(sf::Vector2f v1, sf::Vector2f v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float CollisionHandler::VectorDistance(sf::Vector2f point1, sf::Vector2f point2) {
	return  sqrt(pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2));
}

sf::Vector2f CollisionHandler::VectorSubtract(sf::Vector2f v1, sf::Vector2f v2) {
	return sf::Vector2f((v1.x - v2.x), (v1.y - v2.y));
}

sf::Vector2f CollisionHandler::VectorAdd(sf::Vector2f v1, sf::Vector2f v2) {
	return sf::Vector2f((v1.x + v2.x), (v1.y + v2.y));
}

bool CollisionHandler::DetectLineSegmentIntersection(sf::CircleShape ball, sf::Vector2f point1, sf::Vector2f point2) {
	//https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment?page=1&tab=votes#tab-top
	const float lengthSquared = VectorLengthSqaured(point1, point2);
	float distBallToLine;
	if (lengthSquared == 0.0f) { distBallToLine = VectorDistance(point1, ball.getPosition());  }
	else {
		//I dont honestly understand why we get t
		const float t = std::max(0.0f, std::min(1.0f, DotProd(VectorSubtract(ball.getPosition(), point1), VectorSubtract(point2, point1)) / lengthSquared));
		const sf::Vector2f projection = VectorAdd(point1, sf::Vector2f(t * (point2.x - point1.x), t * (point2.y - point1.y)));
		distBallToLine = VectorDistance(ball.getPosition(), projection);
	}
		if (distBallToLine > ball.getRadius()) { return false; }
		else { return true; }
}

float CollisionHandler::GetLineSegmentDist(sf::CircleShape ball, sf::Vector2f point1, sf::Vector2f point2) {
	//https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment?page=1&tab=votes#tab-top
	const float lengthSquared = VectorLengthSqaured(point1, point2);
	float distBallToLine;
	if (lengthSquared == 0.0f) { distBallToLine = VectorDistance(point1, ball.getPosition()); }
	else {
		//I dont honestly understand why we get t
		const float t = std::max(0.0f, std::min(1.0f, DotProd(VectorSubtract(ball.getPosition(), point1), VectorSubtract(point2, point1)) / lengthSquared));
		const sf::Vector2f projection = VectorAdd(point1, sf::Vector2f(t * (point2.x - point1.x), t * (point2.y - point1.y)));
		distBallToLine = VectorDistance(ball.getPosition(), projection);
	}
	return distBallToLine;
}

float CollisionHandler::DegrToRad(float dAngle) {
	return (dAngle * PI) / 180.0f;
}

sf::Vector2f CollisionHandler::RotateVector(sf::Vector2f point, float rotationDegrees) {
	float x = point.x;
	float y = point.y;
	float rotation = DegrToRad(rotationDegrees);
	return sf::Vector2f((x*cos(rotation)) - (y* sin(rotation)), (y * cos(rotation)) + (x * sin(rotation)));
}

sf::Vector2f CollisionHandler::RotateVectorAboutAxis(sf::Vector2f point, sf::Vector2f axisPoint, float rotationDegrees) {
	float offsetX = point.x - axisPoint.x;
	float offsetY = point.y - axisPoint.y;
	float rotation = DegrToRad(rotationDegrees);
	return sf::Vector2f((offsetX*cos(rotation)) - (offsetY* sin(rotation)), (offsetY * cos(rotation)) + (offsetX * sin(rotation)));
}

sf::Vector2f CollisionHandler::BounceBall(sf::CircleShape ball, sf::Vector2f ballVel, Rect rect) {
	//Detect which was hit
	sf::Vector2f surfaceNormal;
	std::vector<sf::Vector2f> points = rect.GetPoints();
	////Top side
	//if (DetectLineSegmentIntersection(ball, points[0], points[1])) { surfaceNormal = RotateVector(sf::Vector2f(0.0f, 1.0f), rect.GetRotation()); }
	////Left side
	//else if (DetectLineSegmentIntersection(ball, points[0], points[2])) { surfaceNormal = RotateVector(sf::Vector2f(-1.0f, 0.0f), rect.GetRotation()); }
	////Right side
	//else if (DetectLineSegmentIntersection(ball, points[1], points[3])) { surfaceNormal = RotateVector(sf::Vector2f(1.0f, 0.0f), rect.GetRotation()); }
	////Bottom side
	//else if (DetectLineSegmentIntersection(ball, points[2], points[3])) { surfaceNormal = RotateVector(sf::Vector2f(0.0f, -1.0f), rect.GetRotation()); }
	
	//Top side
	float topDist = GetLineSegmentDist(ball, points[0], points[1]);
	//Left side
	float leftDist = GetLineSegmentDist(ball, points[0], points[2]);
	//Right side
	float rightDist = GetLineSegmentDist(ball, points[1], points[3]);
	//Bottom side
	float bottomDist = GetLineSegmentDist(ball, points[2], points[3]);
	float radius = ball.getRadius();

	if ((topDist <= std::max(leftDist, std::max(rightDist, bottomDist))) && (topDist <= radius)) {
		surfaceNormal = RotateVector(sf::Vector2f(0.0f, 1.0f), rect.GetRotation());
	}
	else if ((leftDist <= std::max(topDist, std::max(rightDist, bottomDist))) && (leftDist <= radius)) {
		surfaceNormal = RotateVector(sf::Vector2f(-1.0f, 0.0f), rect.GetRotation());
	}
	else if ((rightDist <= std::max(topDist, std::max(leftDist, bottomDist))) && (rightDist <= radius)) {
		surfaceNormal = RotateVector(sf::Vector2f(1.0f, 0.0f), rect.GetRotation());
	}
	else if ((bottomDist <= std::max(topDist, std::max(leftDist, rightDist)) && (bottomDist <= radius))) {
		surfaceNormal = RotateVector(sf::Vector2f(0.0f, -1.0f), rect.GetRotation());
	}
	else {
		return sf::Vector2f(0.0f, 0.0f);
	}

	float dotProd = DotProd(ballVel, surfaceNormal);
	float bounceDirX = ballVel.x - (2 * dotProd * surfaceNormal.x);
	float bounceDirY = ballVel.y - (2 * dotProd * surfaceNormal.y);
	return sf::Vector2f(bounceDirX, bounceDirY);
}
