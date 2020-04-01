#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "performance.h"


#define SSTR( x ) static_cast< std::ostringstream & >( \
		( std::ostringstream() << std::dec << x ) ).str()

enum class Input { input_file, file_1, file_2 };

struct File {
	std::string filename1;
	std::string filename2;
	std::ifstream infile;
	std::ofstream outfile;
};

void sort(std::string filename, std::string output_filename = "outfile.txt"){
	int n = 11;
	File file[11];
	for(int i = 0; i < n; ++i) {
		char c = i+'0';
		file[i].filename1 = "temp_file_";
		file[i].filename1 += c;
		file[i].filename2 = "temp_file0_";
		file[i].filename2 = file[i].filename2 + c;
//		std::cout<<file[i].filename1<<"  "<<file[i].filename2<<std::endl;
	}
	Input in = Input::input_file;
	int index = 0;
	int max_length = 0;
	std::ifstream infile;
	infile.open(filename);
	if(infile.is_open()){
		std::string line;
		while(getline(infile, line)){
			max_length = (max_length > line.length())? max_length:line.length();
		}
		infile.close();
	}
	
	for (int j = max_length-1; j >= 0; --j) {
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
			std::ifstream infile;
			infile.open(filename);
			if(infile.is_open()){
				std::string line;
				while(getline(infile, line)){
					if (j >= line.length() || line[j] < '0' || line[j] > '9')
						index = 0;
					else
						index = line[j] - '0' + 1;
					file[index].outfile << line << "\n";
				}
				infile.close();
			}
		}
		for(int i = 0; i < n; ++i) {
			if(file[i].infile.is_open()){
				std::string line;
				while(getline(file[i].infile, line)){
					if (j >= line.length() || line[j] < '0' || line[j] > '9')
						index = 0;
					else
						index = line[j] - '0' + 1;
					file[index].outfile << line << "\n";
				}
			}
		}
		for(int i = 0; i < n; ++i){
			if(file[i].infile.is_open())
				file[i].infile.close();
			if(file[i].outfile.is_open())
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
		}
	} else {
		for(int i = 0; i < n; ++i){
			file[i].infile.open(file[i].filename2);
		}
	}
	
	std::ofstream out_file(output_filename);
	
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
		if (file[i].infile.is_open())
			file[i].infile.close();
	}
	for(int i = 0; i < n; ++i){
		remove(file[i].filename1.c_str());
		remove(file[i].filename2.c_str());
	}
}

int count(std::string filename) {
	std::string outfile = "output.dat";
	sort(filename, outfile);

	std::string line;
	std::string cmp = "";
	std::ifstream infile(outfile);
	int ret = 0;
	if(infile.is_open()){
		while(getline(infile, line)){
			if ( line != cmp ) {
				cmp = line;
				ret++;
			}
		}
	}
	infile.close();
	remove(outfile.c_str());
	return ret;
}

//// variadic template
//template < typename... Args >
//std::string sstr( Args &&... args )
//{
//	std::ostringstream sstr;
//	// fold expression
//	( sstr << std::dec << ... << args );
//	return sstr.str();
//}
int main() {
//std::string s = SSTR(1 << 3 << 4);
//std::cout<<s<<std::endl;
	int n = 200;
	int arr[200];
	srand(time(NULL));
	for(int i = 0; i < n; ++i) {
		arr[i] = rand() % (n/4) + 1;
	}
	
	std::string filename = "input.txt";
	std::ofstream outfile(filename);
	for(int i = 0; i < n-2; ++i)
		for(int j = i+1; j < n-1; ++j)
			for(int k = j+1; k < n; ++k)
				outfile << SSTR(arr[i] << " " << arr[j] << " " << arr[k]) <<std::endl;
	outfile.close();
	
//std::cout<<"read content in file: " << filename << std::endl;
//std::ifstream infile(filename);
//std::string line;
//if(infile.is_open()){
//	while(getline(infile, line)){
//		std::cout<<line<<std::endl;
//	}
//}
//infile.close();
	std::cout<<"expected result: "<<count(filename)<<std::endl;
	Solution s;
	std::cout<<"my result: " << s.solution(arr, n) <<std::endl;
	return 0;
}
