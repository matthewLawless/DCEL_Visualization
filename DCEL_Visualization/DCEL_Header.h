#include <sstream>
#include <iostream>
#include <vector>

class HalfEdge;
class Face;
class Vertex;


class HalfEdge {

	private:
		

	public:
		Face* incidentFace;
		HalfEdge* twin;
		//Face* incidentFace;
		Vertex* origin;
		HalfEdge* next;
		HalfEdge* previous;
		static int count;
		int twinId;
		int mainId;
		char specialPrefix;

		HalfEdge() {
			twin = NULL;
			incidentFace = NULL;
			origin = NULL;
			next = NULL;
			previous = NULL;
			mainId = count;
			count++;
			specialPrefix = 'h';
		}

		void setTwinId(int id) {

			twinId = id;

		}

		void setSpecialPrefix(char c) {

			specialPrefix = c;

		}

		std::string shortName() const {

			std::ostringstream s;
			s << "e" << mainId/2 << "," << twinId;
			return s.str();

		}
};



class Face {

	private:
		

	public:
		HalfEdge* innerComponent;
		HalfEdge* outerComponent;
		int id;
		char specialPrefix;
		static int count;

		Face() {

			innerComponent = NULL;
			outerComponent = NULL;
			id = count;
			specialPrefix = 'f';

		}

		std::string shortName() const {

			std::ostringstream s;
			s << "f" << id;
			return s.str();

		}

		static void setStaticCount() {

			count = 1;

		}

};



class Vertex {

	private:
		

	public:
		double x;
		double y;
		HalfEdge* incidentHalfEdge;
		int id;
		char specialPrefix;
		static int count;

		Vertex(double x, double y) {

			this->x = x;
			this->y = y;
			id = count;
			count++;
			incidentHalfEdge = NULL;
			specialPrefix = 'v';

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

		static void setStaticCount() {
		
			count = 1;
		
		}
};

////HalfEdge toString()
//std::ostream& operator << (std::ostream& os, const HalfEdge& h) {
//	return (os << h.shortName() << " " << h.origin->shortName() << " " << h.twin->shortName() << " " << h.incidentFace->shortName() << " " << h.next->shortName() << " " << h.previous->shortName());
//}

//HalfEdge toString()
std::ostream& operator << (std::ostream& os, const HalfEdge& h) {
	std::string output = "";
	output = output + h.shortName() + " ";

	if (h.origin) {
		output += h.origin->shortName() + " ";
	}
	else {
		output += "NIL ";
	}

	if (h.twin) {
		output += h.twin->shortName() + " ";
	}
	else {
		output += "NIL ";
	}

	if (h.incidentFace) {
		output += h.incidentFace->shortName() + " ";
	}
	else {
		output += "NIL ";
	}

	if (h.next) {
		output += h.next->shortName() + " ";
	}
	else {
		output += "NIL ";
	}

	if (h.previous) {
		output += h.previous->shortName() + " ";
	}
	else {
		output += "NIL ";
	}

	return os << output;
}

//Vertex toString()
std::ostream& operator << (std::ostream& os, const Vertex& v) {
	std::string output = "";
	output += v.shortName() + " " + v.coordinateForm() + " ";
	if (v.incidentHalfEdge) {
		output += v.incidentHalfEdge->shortName() + " ";
	}
	else {
		output += "NIL";
	}
	return os << output;
}

//Face toString()
std::ostream& operator << (std::ostream& os, const Face& f) {
	std::string output = "";
	output += f.shortName() + " ";
	if (f.innerComponent) {
		output += f.innerComponent->shortName();
	}
	else {
		output += "NIL ";
	}

	if (f.outerComponent) {
		output += f.outerComponent->shortName() + " ";
	}
	else {
		output += "NIL ";
	}
	return os << output;
}

class DCEL {

public:

	std::vector<HalfEdge*> hedgeRecord;
	std::vector<Face*> faceRecord;
	std::vector<Vertex*> vertexRecord;

	DCEL() {};

};

std::ostream& operator << (std::ostream& os, const DCEL& d) {
	std::ostringstream s;

	for (Vertex* v : d.vertexRecord) {
		Vertex& cV = *v;
		s << cV << std::endl;
	}
	s << std::endl << std::endl;
	for (Face* f : d.faceRecord) {
		Face& cF = *f;
		s << cF << std::endl;
	}
	s << std::endl << std::endl;
	for (HalfEdge* h : d.hedgeRecord) {
		HalfEdge& hF = *h;
		s << hF << std::endl;
	}
	return (os << s.str() << std::endl);
}
