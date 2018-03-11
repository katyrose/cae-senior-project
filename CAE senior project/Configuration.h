//Configuration Class file
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Channel.h"

using namespace std;

class Configuration {

private:
	string name;
	int total_fov_h;
	int total_fov_v;
	float viewer_distance;
	int num_channels;
	int test_pattern;
	vector<Channel> channels;

public:
	//Constructors & Destructor
	Configuration(ifstream& in_file);
	Configuration();
	~Configuration();

	//Setters
	void set_name(string input);
	void set_total_fov_h(int input);
	void set_total_fov_v(int input);
	void set_viewer_distance(float input);
	void set_num_channels(int input);
	void set_test_pattern(int input);

	//Getters
	string get_name();
	int get_total_fov_h();
	int get_total_fov_v();
	float get_viewer_distance();
	int get_num_channels();
	int get_test_pattern();

	//TODO: Output
	void display_config_console();
	void display_config_file(ostream out_file);
	
	//TODO: Error detection

};

//Constructors & Destructor
Configuration::Configuration(ifstream& in_file) {
	std::string in_string;

	while (getline(in_file, in_string, ':')) {
		if (in_string == "name") {
			getline(in_file, in_string);
			this->set_name(in_string);
		} 
		else if (in_string == "total_fov_h") {
			getline(in_file, in_string);
			this->set_total_fov_h(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "total_fov_v") {
			getline(in_file, in_string);
			this->set_total_fov_v(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "viewer_distance") {
			getline(in_file, in_string);
			this->set_viewer_distance(stof(in_string, nullptr));
		}
		else if (in_string == "num_channels") {
			getline(in_file, in_string);
			this->set_num_channels(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "test_pattern") {
			getline(in_file, in_string);
			this->set_test_pattern(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "-") {
			getline(in_file, in_string);
			Channel* temp = new Channel(in_file);
			channels.push_back(*temp);
		}
		else {
			cout << "COnfiguration type not recognized" << endl;
		}
	}
}
Configuration::Configuration() {
	this->set_name("Untitled Configuration");
}

Configuration::~Configuration() {
	delete this;
}

//Setters
void Configuration::set_name(string input) {
	this->name = input;
}
void Configuration::set_total_fov_h(int input) {
	this->total_fov_h = input;
}
void Configuration::set_total_fov_v(int input) {
	this->total_fov_v = input;
}
void Configuration::set_viewer_distance(float input) {
	this->viewer_distance = input;
}
void Configuration::set_num_channels(int input) {
	this->num_channels = input;
}
void Configuration::set_test_pattern(int input) {
	this->test_pattern = input;
}

//Getters
string Configuration::get_name() {
	return this->name;
}
int Configuration::get_total_fov_h() {
	return this->total_fov_h;
}
int Configuration::get_total_fov_v() {
	return this->total_fov_v;
}
float Configuration::get_viewer_distance() {
	return this->viewer_distance;
}
int Configuration::get_num_channels() {
	return this->num_channels;
}
int Configuration::get_test_pattern() {
	return this->test_pattern;
}

//Output
void Configuration::display_config_console() {
	cout << "name:" << this->get_name() << endl;
	cout << "total_fov_h:" << this->get_total_fov_h() << endl;
	cout << "total_fov_v:" << this->get_total_fov_v() << endl;
	cout << "viewer_distance:" << this->get_viewer_distance() << endl;
	cout << "num_channels:" << this->get_num_channels() << endl;
	cout << "test_pattern:" << this->get_test_pattern() << endl;
	for (vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it) {
		cout << "-:" << endl;
		it->display_channel_console();
	}
}

void Configuration::display_config_file(ostream out_file) {

}