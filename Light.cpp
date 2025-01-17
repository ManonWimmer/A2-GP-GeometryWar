#include "Light.h"
#include "RayCast.h"
#include <iostream>


Light::Light(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, float radius)
	:	Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), _radius(radius)
{
	_lightShape.setFillColor(sf::Color::Yellow);
	_lightShape.setRadius(5.0f);
	_lightShape.setOrigin(_lightShape.getRadius(), _lightShape.getRadius());

	InitializedRays();
}




void Light::Update(sf::RenderWindow& window, float deltaTime)
{


std::list<sf::ConvexShape> shadowTriangles;

std::list<RayCast>::iterator currentit;

for (currentit = _rays.begin(); currentit != _rays.end(); currentit++)
{
	currentit->SetRayOrigin(_lightShape.getPosition());
	currentit->DrawRayCast(window, managerEntity);
}





for (currentit = _rays.begin(); currentit != _rays.end(); currentit++)
{


	if (currentit == _rays.begin()) {
		
		// If the current ray is getting contact but he is isolated (between two null ray points).
		if (!_rays.back().GetContact() && currentit->GetContact() && !std::next(currentit)->GetContact()) {
			// Do nothing yet;
		}

		//If the current and next ray is getting contact but the previous ray is null.
		if (!_rays.back().GetContact() && currentit->GetContact() && std::next(currentit)->GetContact()) {

			sf::ConvexShape middleTriangle;
			middleTriangle.setPointCount(3);
			middleTriangle.setPoint(0, sf::Vector2f(0, 0));
			middleTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setPoint(2, MathLib::NormalizedVector(std::next(currentit)->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setOrigin(middleTriangle.getPoint(0));
			middleTriangle.setPosition(currentit->GetImpactPoint());
			middleTriangle.setFillColor(_shadowColor);

			shadowTriangles.push_back(middleTriangle);
		}


		//If the current and previous ray is getting contact but the next ray is null.
		if (_rays.back().GetContact() && currentit->GetContact() && !std::next(currentit)->GetContact()) {

			sf::ConvexShape leftTriangle;
			leftTriangle.setPointCount(3);
			leftTriangle.setPoint(0, sf::Vector2f(0, 0));
			leftTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			leftTriangle.setPoint(2, currentit->GetImpactPoint() - _rays.back().GetImpactPoint());
			leftTriangle.setOrigin(leftTriangle.getPoint(0));
			leftTriangle.setPosition(_rays.back().GetImpactPoint());
			leftTriangle.setFillColor(_shadowColor);


			shadowTriangles.push_back(leftTriangle);
		}





		//If all the rays are getting contacts.
		if (_rays.back().GetContact() && currentit->GetContact() && std::next(currentit)->GetContact()) {


			sf::ConvexShape leftTriangle;
			leftTriangle.setPointCount(3);
			leftTriangle.setPoint(0, sf::Vector2f(0, 0));
			leftTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			leftTriangle.setPoint(2, currentit->GetImpactPoint() - _rays.back().GetImpactPoint());
			leftTriangle.setOrigin(leftTriangle.getPoint(0));
			leftTriangle.setPosition(_rays.back().GetImpactPoint());
			leftTriangle.setFillColor(_shadowColor);



			sf::ConvexShape middleTriangle;

			sf::Vector2f leftPoint = leftTriangle.getPoint(1) + leftTriangle.getPosition();
			middleTriangle.setPointCount(3);
			middleTriangle.setPoint(0, sf::Vector2f(0, 0));
			middleTriangle.setPoint(1, MathLib::NormalizedVector(leftPoint - currentit->GetImpactPoint()) * _shadowLength);
			middleTriangle.setPoint(2, MathLib::NormalizedVector(std::next(currentit)->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setOrigin(middleTriangle.getPoint(0));
			middleTriangle.setPosition(currentit->GetImpactPoint());
			middleTriangle.setFillColor(_shadowColor);


			shadowTriangles.push_back(leftTriangle);
			shadowTriangles.push_back(middleTriangle);
		}
	}
	else if (currentit == std::prev(_rays.end())) {


		// If the current ray is getting contact but he is isolated (between two null ray points).
		if (!std::prev(currentit)->GetContact() && currentit->GetContact() && !_rays.begin()->GetContact()) {
			// Do nothing yet;
		}

		//If the current and next ray is getting contact but the previous ray is null.
		if (!std::prev(currentit)->GetContact() && currentit->GetContact() && _rays.begin()->GetContact()) {

			sf::ConvexShape middleTriangle;
			middleTriangle.setPointCount(3);
			middleTriangle.setPoint(0, sf::Vector2f(0, 0));
			middleTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setPoint(2, MathLib::NormalizedVector(_rays.begin()->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setOrigin(middleTriangle.getPoint(0));
			middleTriangle.setPosition(currentit->GetImpactPoint());
			middleTriangle.setFillColor(_shadowColor);

			shadowTriangles.push_back(middleTriangle);
		}


		//If the current and previous ray is getting contact but the next ray is null.
		if (std::prev(currentit)->GetContact() && currentit->GetContact() && !_rays.begin()->GetContact()) {

			sf::ConvexShape leftTriangle;
			leftTriangle.setPointCount(3);
			leftTriangle.setPoint(0, sf::Vector2f(0, 0));
			leftTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			leftTriangle.setPoint(2, currentit->GetImpactPoint() - std::prev(currentit)->GetImpactPoint());
			leftTriangle.setOrigin(leftTriangle.getPoint(0));
			leftTriangle.setPosition(std::prev(currentit)->GetImpactPoint());
			leftTriangle.setFillColor(_shadowColor);


			shadowTriangles.push_back(leftTriangle);
		}





		//If all the rays are getting contacts.
		if (std::prev(currentit)->GetContact() && currentit->GetContact() && _rays.begin()->GetContact()) {


			sf::ConvexShape leftTriangle;
			leftTriangle.setPointCount(3);
			leftTriangle.setPoint(0, sf::Vector2f(0, 0));
			leftTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			leftTriangle.setPoint(2, currentit->GetImpactPoint() - std::prev(currentit)->GetImpactPoint());
			leftTriangle.setOrigin(leftTriangle.getPoint(0));
			leftTriangle.setPosition(std::prev(currentit)->GetImpactPoint());
			leftTriangle.setFillColor(_shadowColor);



			sf::ConvexShape middleTriangle;

			sf::Vector2f leftPoint = leftTriangle.getPoint(1) + leftTriangle.getPosition();
			middleTriangle.setPointCount(3);
			middleTriangle.setPoint(0, sf::Vector2f(0, 0));
			middleTriangle.setPoint(1, MathLib::NormalizedVector(leftPoint - currentit->GetImpactPoint()) * _shadowLength);
			middleTriangle.setPoint(2, MathLib::NormalizedVector(_rays.begin()->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setOrigin(middleTriangle.getPoint(0));
			middleTriangle.setPosition(currentit->GetImpactPoint());
			middleTriangle.setFillColor(_shadowColor);


			shadowTriangles.push_back(leftTriangle);
			shadowTriangles.push_back(middleTriangle);
		}
	}
	else {



		// If the current ray is getting contact but he is isolated (between two null ray points).
		if (!std::prev(currentit)->GetContact() && currentit->GetContact() && !std::next(currentit)->GetContact()) {
			// Do nothing yet;
		}

		//If the current and next ray is getting contact but the previous ray is null.
		if (!std::prev(currentit)->GetContact() && currentit->GetContact() && std::next(currentit)->GetContact()) {

			sf::ConvexShape middleTriangle;
			middleTriangle.setPointCount(3);
			middleTriangle.setPoint(0, sf::Vector2f(0, 0));
			middleTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setPoint(2, MathLib::NormalizedVector(std::next(currentit)->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setOrigin(middleTriangle.getPoint(0));
			middleTriangle.setPosition(currentit->GetImpactPoint());
			middleTriangle.setFillColor(_shadowColor);

			shadowTriangles.push_back(middleTriangle);
		}


		//If the current and previous ray is getting contact but the next ray is null.
		if (std::prev(currentit)->GetContact() && currentit->GetContact() && !std::next(currentit)->GetContact()) {

			sf::ConvexShape leftTriangle;
			leftTriangle.setPointCount(3);
			leftTriangle.setPoint(0, sf::Vector2f(0, 0));
			leftTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			leftTriangle.setPoint(2, currentit->GetImpactPoint() - std::prev(currentit)->GetImpactPoint());
			leftTriangle.setOrigin(leftTriangle.getPoint(0));
			leftTriangle.setPosition(std::prev(currentit)->GetImpactPoint());
			leftTriangle.setFillColor(_shadowColor);


			shadowTriangles.push_back(leftTriangle);
		}





		//If all the rays are getting contacts.
		if (std::prev(currentit)->GetContact() && currentit->GetContact() && std::next(currentit)->GetContact()) {


			sf::ConvexShape leftTriangle;
			leftTriangle.setPointCount(3);
			leftTriangle.setPoint(0, sf::Vector2f(0, 0));
			leftTriangle.setPoint(1, MathLib::NormalizedVector(currentit->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			leftTriangle.setPoint(2, currentit->GetImpactPoint() - std::prev(currentit)->GetImpactPoint());
			leftTriangle.setOrigin(leftTriangle.getPoint(0));
			leftTriangle.setPosition(std::prev(currentit)->GetImpactPoint());
			leftTriangle.setFillColor(_shadowColor);



			sf::ConvexShape middleTriangle;

			sf::Vector2f leftPoint = leftTriangle.getPoint(1) + leftTriangle.getPosition();
			middleTriangle.setPointCount(3);
			middleTriangle.setPoint(0, sf::Vector2f(0, 0));
			middleTriangle.setPoint(1, MathLib::NormalizedVector(leftPoint - currentit->GetImpactPoint()) * _shadowLength);
			middleTriangle.setPoint(2, MathLib::NormalizedVector(std::next(currentit)->GetImpactPoint() - _lightShape.getPosition()) * _shadowLength);
			middleTriangle.setOrigin(middleTriangle.getPoint(0));
			middleTriangle.setPosition(currentit->GetImpactPoint());
			middleTriangle.setFillColor(_shadowColor);


			shadowTriangles.push_back(leftTriangle);
			shadowTriangles.push_back(middleTriangle);
		}

	}


}







	std::list<sf::ConvexShape>::iterator currentShape = shadowTriangles.begin();
	while (currentShape != shadowTriangles.end()) {
		window.draw(*currentShape);
		currentShape++;
	}

	/*std::list<sf::Vector2f> shadowShape;
	std::list<RayCast>::iterator currentit;
	for (currentit = _rays.begin(); currentit != _rays.end(); currentit++)
	{
		shadowShape.push_back(currentit->GetImpactPoint());
	}

	sf::Vector2u windowSize = window.getSize();
	sf::Texture renderTexture;
	renderTexture.create(windowSize.x, windowSize.y);

	sf::Vector2f newPosition = window.mapPixelToCoords(sf::Vector2i(0, 0), window.getView());
	sf::Sprite sprite(renderTexture);
	sprite.setPosition(newPosition.x, newPosition.y);

	sf::Image image;
	image.create(windowSize.x, windowSize.y, sf::Color::Transparent);
*/



	/*for (int x = 0; x < image.getSize().x; x++) {

		for (int y = 0; y < image.getSize().y; y++) {

			sf::Vector2f pixelPosition = window.mapPixelToCoords(sf::Vector2i(x, y), window.getView());

			std::cout << "Pixel Position: " << pixelPosition.x << " ; " << pixelPosition.y << std::endl;

			if (MathLib::IsPointInsideConvexShape(pixelPosition, shadowShape) == true) {
				image.setPixel(x, y, sf::Color::Black);
			}
		}
	}*/

	//renderTexture.update(image);

	//window.draw(sprite);
}

void Light::SetPosition(sf::Vector2f position)
{
	_lightShape.setPosition(position);
}

void Light::InitializedRays()
{
	std::set<RayCast>::iterator it;
	for (int i = 0; i < 200; i++) {

		sf::Vector2f origin = _lightShape.getPosition();

		float angle = static_cast<float>(i) * (360.0f / static_cast<float>(200));
		float radians = angle * (3.14159265f / 180.0f); // Convert degrees to radians

		float x = _radius * std::cos(radians);
		float y = _radius * std::sin(radians);

		sf::Vector2f target = sf::Vector2f(x, y);
		sf::Vector2f localDirection = target;

		_rays.push_back(RayCast(origin, localDirection, _radius, false));
	}
}
