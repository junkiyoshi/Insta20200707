#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->hexagon_height = 64;
	this->hexagon_width = 15;

	for (float x = -100; x <= 100; x += 200) {
		
		for (float y = -150; y <= 150; y += 150) {

			for (float z = -100; z <= 100; z += 25) {

				this->number_list.push_back(make_pair(glm::vec3(x, y, z), 0));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	for (auto& number : this->number_list) {

		int number_index = ofMap(ofNoise(number.first.x * 0.005, number.first.y * 0.005, number.first.z * 0.0015 + ofGetFrameNum() * 0.01), 0, 1, 0, 10);
		this->draw_digital(number.first, number_index);
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_digital(glm::vec3 location, int number_index) {

	vector<pair<glm::vec3, float>> part_list = {
		make_pair<glm::vec3, float>(location + glm::vec2(0, -this->hexagon_height), 90),
		make_pair<glm::vec3, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec3, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec3, float>(location + glm::vec2(0, 0), 90),
		make_pair<glm::vec3, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec3, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec3, float>(location + glm::vec2(0, this->hexagon_height), 90)
	};

	vector<vector<int>> index_list = {
		{ 0, 1, 2, 4, 5, 6 },
		{ 2, 5 },
		{ 0, 1, 3, 5, 6 },
		{ 0, 2, 3, 5, 6 },
		{ 2, 3, 4, 5 },
		{ 0, 2, 3, 4, 6 },
		{ 0, 1, 2, 3, 4, 6 },
		{ 0, 2, 5 },
		{ 0, 1, 2, 3, 4, 5, 6 },
		{ 0, 2, 3, 4, 5, 6 },
	};

	for (auto& index : index_list[number_index]) {

		this->draw_hexagon(part_list[index].first, part_list[index].second);
	}
}

//--------------------------------------------------------------
void ofApp::draw_hexagon(glm::vec3 location, float deg) {

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(deg);

	vector<glm::vec2> vertices;
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * 0.5));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * -0.5));

	ofFill();
	ofSetColor(39, ofMap(location.z, -100, 100, 255, 0));

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(239);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}