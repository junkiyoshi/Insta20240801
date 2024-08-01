#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(200, 8);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	auto noise_seed = ofRandom(1000);
	for (int i = 0; i < this->triangle_list.size(); i++) {

		glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
		auto noise_value = ofNoise(noise_seed, avg.y * 0.01 + ofGetFrameNum() * 0.03, avg.x * 0.01, avg.z * 0.01);

		if (noise_value < 0.47 || noise_value > 0.53) { continue; }

		vector<glm::vec3> vertices;

		vertices.push_back(this->triangle_list[i].getVertex(0));
		vertices.push_back(this->triangle_list[i].getVertex(1));
		vertices.push_back(this->triangle_list[i].getVertex(2));

		this->mesh.addVertices(vertices);

		ofColor color;
		color.setHsb(ofMap(ofNoise(glm::vec4(noise_seed, avg * 0.005)), 0, 1, 100, 192), 130, 255);

		for (int k = 0; k < vertices.size(); k++) {

			this->mesh.addColor(color);
		}

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.35);

	this->mesh.draw();

	ofDrawSphere(199);

	this->cam.end();

	/*
	int start = 1;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}