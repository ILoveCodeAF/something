#include <iostream>
#include <fstream>
#include <stdio.h>

enum class Input { input_file, file_1, file_2 };

struct File {
	std::string filename1;
	std::string filename2;
	std::ifstream infile;
	std::ofstream outfile;
};

void sort(std::string filename){
	int n = 10;
	File file[10];
	for(int i = 0; i < n; ++i) {
		file[i].filename1 = "temp_file_" + char(i+'0');
		file[i].filename2 = "temp_file0_" + char(i+'0');
	}
	Input in = Input::input_file;

	for (int i = 2; i >= 0; --i) {
		// open file
		if (in != Input::file_2) {
			for(int i = 0; i < n; ++i){
				file[i].infile.open(file[i].filename1);
				file[i].outfile.open(file[i].filename2);
			}
		} else {
			for(int i = 0; i < n; ++i){
				file[i].infile.open(file[i].filename2);
				file[i].outfile.open(file[i].filename1);
			}
		}

		if (in == Input::input_file) {
			std::fstream infile;
			infile.open(filename);
			if(infile.is_open()){
				std::string line;
				while(getline(infile, line)){
					file[line[i]].outfile << line << "\n";
				}
				infile.close();
			}
		}
		for(int i = 0; i < n; ++i) {
			if(file[i].infile.is_open()){
				std::string line;
				while(getline(file[i].infile, line)){
					file[line[i]].outfile << line << "\n";
				}
			}
		}
		for(int i = 0; i < n; ++i){
			file[i].infile.close();
			file[i].outfile.close();
		}
		if(in != Input::file_2){
			in = Input::file_2;
		} else {
			in = Input::file_1;
		}
	}
	if (in != Input::file_2) {
		for(int i = 0; i < n; ++i){
			file[i].infile.open(file[i].filename1);
			file[i].outfile.open(file[i].filename2);
		}
	} else {
		for(int i = 0; i < n; ++i){
			file[i].infile.open(file[i].filename2);
			file[i].outfile.open(file[i].filename1);
		}
	}
	std::ofstream out_file(filename);
	
	for(int i = 0; i < n; ++i){
		if(file[i].infile.is_open()){
			std::string line;
			while(getline(file[i].infile, line)){
				out_file << line << "\n";
			}
		}
	}
	out_file.close();
	
	for(int i = 0; i < n; ++i){
			file[i].infile.close();
			file[i].outfile.close();
		}
	for(int i = 0; i < n; ++i){
		remove(file[i].filename1.c_str());
		remove(file[i].filename2.c_str());
	}
}
int main() {
	std::string filename = "input.txt";
	std::ofstream outfile(filename);
	outfile << "132\n" << "155\n";
	outfile.close();
	sort(filename);
	return 0;
}
