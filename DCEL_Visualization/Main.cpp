#include "SFML/Graphics.hpp"


#include <sstream>
#include <iostream>
#include "DCEL_Header.h"

void visualizeDCEL(DCEL d);
void drawPointsToWindow(std::vector<sf::Vertex> pointList, sf::RenderWindow* window);

int HalfEdge::count = 2;
int Vertex::count = 1;
int Face::count = 1;
//class DCEL {
//	
//	public:
//
//		std::vector<HalfEdge*> hedgeRecord;
//		std::vector<Face*> faceRecord;
//		std::vector<Vertex*> vertexRecord;
//
//		DCEL() {};
//
//};
//
//std::ostream& operator << (std::ostream &os, const DCEL &d) {
//	std::ostringstream s;
//
//	for (Vertex *v : d.vertexRecord) {
//		s << (*v) << std::endl;
//	}
//	s << std::endl << std::endl;
//	for (Face *f : d.faceRecord) {
//		s << (*f) << std::endl;
//	}
//	s << std::endl << std::endl;
//	for (HalfEdge *h : d.hedgeRecord) {
//		s << (*h) << std::endl;
//	}
//	return (os << s.str() << std::endl);
//}
//
//
//class HalfEdge {
//
//	public:
//		HalfEdge *twin;
//		Face *incidentFace;
//		Vertex *origin;
//		HalfEdge *next;
//		HalfEdge *previous;
//
//		int twinId;
//		int mainId;
//		char specialPrefix;
//		static int count;
//
//		HalfEdge() {
//			twin = NULL;
//			incidentFace = NULL;
//			origin = NULL;
//			next = NULL;
//			previous = NULL;
//		}
//
//		void setTwinId(int id) {
//		
//			twinId = id;
//		
//		}
//
//		void setSpecialPrefix(char c) {
//		
//			specialPrefix = c;
//		
//		}
//
//		std::string shortName() const {
//		
//			std::ostringstream s;
//			s << "e" << mainId << "," << twinId;
//			return s.str();
//		
//		}
//};
//
//std::ostream& operator << (std::ostream &os, const HalfEdge &h) {
//	return (os << h.shortName() << " " << h.origin->shortName() << " " << h.twin->shortName() << " " << h.incidentFace->shortName() << " " << h.next->shortName() << " " << h.previous->shortName());
//}
//
//class Face {
//
//	public:
//		HalfEdge *innerComponent;
//		HalfEdge *outerComponent;
//		int id;
//		char specialPrefix;
//
//		Face() {
//		
//			innerComponent = NULL;
//			outerComponent = NULL;
//		
//		}
//
//		std::string shortName() const {
//		
//			std::ostringstream s;
//			s << "f" << id;
//			return s.str();
//		
//		}
//
//};
//
//std::ostream& operator << (std::ostream &os, const Face &f) {
//	return (os << "f" << f.innerComponent->shortName() << " " << f.outerComponent->shortName() << std::endl);
//}
//
//class Vertex {
//
//	public:
//		double x;
//		double y;
//		HalfEdge *incidentHalfEdge;
//		int id;
//		char specialPrefix;
//		static int count;
//
//		Vertex(double x, double y) {
//			
//			this->x = x;
//			this->y = y;
//			id = count;
//		
//		}
//
//		std::string coordinateForm() const {
//			
//			std::ostringstream s;
//			s << "(" << x << ", " << y << ")";
//			return s.str();
//		
//		}
//
//		std::string shortName() const {
//		
//			std::ostringstream s;
//			s << "v" << id;
//			return s.str();
//		
//		}
//};
//
//std::ostream& operator << (std::ostream &os, const Vertex &v) {
//	return (os << "v" << v.id << " " << v.coordinateForm() << " " << v.incidentHalfEdge->shortName() << std::endl);
//}

//int main() {
//	
//	std::cout << "Hello World!" << std::endl;
//	return 0;
//}

int main() {

	DCEL* d = new DCEL();

	HalfEdge* h1 = new HalfEdge();
	HalfEdge* h2 = new HalfEdge();
	h1->twin = h2;
	h2->twin = h1;

	h1->setTwinId(1);
	h2->setTwinId(2);

	HalfEdge* h3 = new HalfEdge();
	HalfEdge* h4 = new HalfEdge();
	h3->twin = h4;
	h4->twin = h3;

	h3->setTwinId(1);
	h4->setTwinId(2);

	h1->next = h3;
	
	h3->previous = h1;

	h2->previous = h4;
	h4->next = h2;

	HalfEdge& test = *h1;
	

	
	
	


	Face* f1 = new Face();

	h1->incidentFace = f1;
	h2->incidentFace = f1;
	h3->incidentFace = f1;
	h4->incidentFace = f1;

	Vertex* v1 = new Vertex(400, 400);
	Vertex* v2 = new Vertex(1, 1);
	Vertex* v3 = new Vertex(1, 0);

	h1->origin = v1;
	v1->incidentHalfEdge = h1;

	d->hedgeRecord.push_back(h1);
	d->hedgeRecord.push_back(h2);
	d->hedgeRecord.push_back(h3);
	d->hedgeRecord.push_back(h4);
	d->faceRecord.push_back(f1);
	d->vertexRecord.push_back(v1);
	d->vertexRecord.push_back(v2);
	d->vertexRecord.push_back(v3);



	DCEL& cD = *d;
	

	std::cout << cD << std::endl;

	visualizeDCEL(*d);

	return 0;

}

void visualizeDCEL(DCEL d) {

	std::vector<sf::Vertex> vertexList;
	for (Vertex* v : d.vertexRecord) {
		Vertex& cV = *v;
		std::ostringstream s;
		s << cV;
		int x = int(s.str()[4]);
		int y = int(s.str()[7]);
		sf::Vector2f *position = new sf::Vector2f(x, y);
		sf::Vertex *newV = new sf::Vertex(*position, sf::Color::Black);
		vertexList.push_back(*newV);
		
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "DCEL", sf::Style::Resize);
	while (window.isOpen()) {

		drawPointsToWindow(vertexList, &window);
		window.display();

	}



}

void drawPointsToWindow(std::vector<sf::Vertex> pointList, sf::RenderWindow* window) {
	for (sf::Vertex v : pointList) {
		//Draw each point and a circle around it
		window->draw(&v, 1, sf::Points);
		sf::CircleShape c(20);
		c.setFillColor(sf::Color::Blue);
		c.setPosition(v.position.x, v.position.y);
		c.setOrigin(c.getRadius(), c.getRadius());
		window->draw(c);
	}
}

