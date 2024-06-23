#include "SFML/Graphics.hpp"
#include <sstream>


int main() {

	



	return 0;

}

class DCEL {
	
	public:

		std::vector<HalfEdge> hedgeRecord;
		std::vector<Face> faceRecord;
		std::vector<Vertex> vertexRecord;

};

std::ostream& operator << (std::ostream &os, const DCEL &d) {
	std::ostringstream s;

	for (Vertex v : d.vertexRecord) {
		s << v << std::endl;
	}
	s << std::endl << std::endl;
	for (Face f : d.faceRecord) {
		s << f << std::endl;
	}
	s << std::endl << std::endl;
	for (HalfEdge h : d.hedgeRecord) {
		s << h << std::endl;
	}
	return (os << s.str() << std::endl);
}


class HalfEdge {

	public:
		HalfEdge *twin;
		Face *incidentFace;
		Vertex *origin;
		HalfEdge *next;
		HalfEdge *previous;

		int twinId;
		int mainId;
		char specialPrefix;
		static int count;

		HalfEdge() {
			twin = NULL;
			incidentFace = NULL;
			origin = NULL;
			next = NULL;
			previous = NULL;
		}

		void setTwinId(int id) {
		
			twinId = id;
		
		}

		void setSpecialPrefix(char c) {
		
			specialPrefix = c;
		
		}

		std::string shortName() const {
		
			std::ostringstream s;
			s << "e" << mainId << "," << twinId;
			return s.str();
		
		}
};

std::ostream& operator << (std::ostream &os, const HalfEdge &h) {
	return (os << h.shortName() << " " << h.origin->shortName() << " " << h.twin->shortName() << " " << h.incidentFace->shortName() << " " << h.next->shortName() << " " << h.previous->shortName());
}

class Face {

	public:
		HalfEdge *innerComponent;
		HalfEdge *outerComponent;
		int id;
		char specialPrefix;

		Face() {
		
			innerComponent = NULL;
			outerComponent = NULL;
		
		}

		std::string shortName() const {
		
			std::ostringstream s;
			s << "f" << id;
			return s.str();
		
		}

};

std::ostream& operator << (std::ostream &os, const Face &f) {
	return (os << "f" << f.innerComponent->shortName() << " " << f.outerComponent->shortName() << std::endl);
}

class Vertex {

	public:
		double x;
		double y;
		HalfEdge *incidentHalfEdge;
		int id;
		char specialPrefix;
		static int count;

		Vertex(double x, double y) {
			
			this->x = x;
			this->y = y;
			id = count;
		
		}

		std::string coordinateForm() const {
			
			std::ostringstream s;
			s << "(" << x << ", " << y << ")";
			return s.str();
		
		}

		std::string shortName() const {
		
			std::ostringstream s;
			s << "v" << id;
			return s.str();
		
		}
};

std::ostream& operator << (std::ostream &os, const Vertex &v) {
	return (os << "v" << v.id << " " << v.coordinateForm() << " " << v.incidentHalfEdge->shortName() << std::endl);
}

