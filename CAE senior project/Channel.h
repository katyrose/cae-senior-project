//Class file for the Channel class

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Channel {
private:
	int number;
	int fov_h;
	int fov_v;
	int location_h;
	int location_v;

public:
	//channel constructor from config file 
	Channel(ifstream& in_file);
	//channel constructor w/o config file for image generation
	Channel();
	//destructor
	~Channel();

	//Setters
	void set_number(int input);
	void set_fov_h(int input);
	void set_fov_v(int input);
	void set_location_h(int input);
	void set_location_v(int input);

	//Getters
	int get_number();
	int get_fov_h();
	int get_fov_v();
	int get_location_h();
	int get_location_v();

	//Output
	void display_channel_console();
	void display_channel_file(ofstream& out_file);

};

//Constructor w/o config file for image generation
Channel::Channel() {
	set_number(0);
	set_fov_h(0);
	set_fov_v(0);
	set_location_h(0);
	set_location_v(0);
}

Channel::Channel(ifstream& in_file) {
	string in_string;
	int peek;
	int keep_reading = 1;

	while (keep_reading) {
		getline(in_file, in_string, ':');
		if (in_string == "number") {
			getline(in_file, in_string);
			this->set_number(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "fov_h") {
			getline(in_file, in_string);
			this->set_fov_h(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "fov_v") {
			getline(in_file, in_string);
			this->set_fov_v(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "location_h") {
			getline(in_file, in_string);
			this->set_location_h(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "location_v") {
			getline(in_file, in_string);
			this->set_location_v(stoi(in_string, nullptr, 0));
		}
		else {
			cout << "Channel type not recognized." << endl;
		}

		peek = in_file.peek();

		if (peek == '-' || peek == -1)
			keep_reading = 0;
	}
}

Channel::~Channel() {
}

//Setters
void Channel::set_number(int input) {
	this->number = input;
}
void Channel::set_fov_h(int input) {
	this->fov_h = input;
}
void Channel::set_fov_v(int input) {
	this->fov_v = input;
}
void Channel::set_location_h(int input) {
	this->location_h = input;
}
void Channel::set_location_v(int input) {
	this->location_v = input;
}

//Getters
int Channel::get_number() {
	return this->number;
}
int Channel::get_fov_h() {
	return this->fov_h;
}
int Channel::get_fov_v() {
	return this->fov_v;
}
int Channel::get_location_h() {
	return this->location_h;
}
int Channel::get_location_v() {
	return this->location_v;
}

//Output
void Channel::display_channel_console() {
	cout << "number:" << this->get_number() << endl;
	cout << "fov_h:" << this->get_fov_h() << endl;
	cout << "fov_v:" << this->get_fov_h() << endl;
	cout << "location_h:" << this->get_location_h() << endl;
	cout << "location_v:" << this->get_location_v() << endl;
}
void Channel::display_channel_file(ofstream& out_file) {

}