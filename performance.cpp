//Kate was given a birthday gift of three theater tickets. Now she is browsing the theater program for the next N days. On the program, performances are named by integers. Every day, one performance is staged. Kate wants to choose three days (not necessarily consecutive) to go to the theater.
//In how many ways can she use her tickets? Two ways are different if the sequences of watched performances are different. Kate likes the theater, so she may watch one performance more than once. For example, if N = 4 and theater program looks as following: [1, 2, 1, 1], Kate has four possibilities to choose the dates: [1, 2, 1, 1], [1, 2, 1, 1], [1, 2, 1, 1], and [1, 2, 1, 1], but they create only three different sequences: (1, 2, 1), (1, 1, 1) and (2, 1, 1). The correct answer for this example is 3. Notice that the order of performances matters, so the first and the last sequences are considered different.
//Write a function:
//
//	class Solution { public int solution(int[] A); }
//
//	that, given an array A consisting of N integers, denoting names of performances for the next N days, returns the number of possible ways to spend the tickets. Since the answer can be very large, provide it modulo 109 + 7 (1,000,000,007).
//	For example, given A = [1, 2, 1, 1], the function should return 3 as exmplained above.
//	Given A = [1, 2, 3, 4], the function should return 4. There are four ways to spend tickets: (1, 2, 3), (1, 2, 4), (1, 3, 4) and (2, 3, 4).
//	Given A = [2, 2, 2, 2], the function should return 1. There is only one way to spend tickets: (2, 2, 2).
//	Given A = [2, 2, 1, 2, 2], the function should return 4. There are four ways to spend tickets: (1, 2, 2), (2, 1, 2), (2, 2, 1) and (2, 2, 2).
//	Given A = [1, 2], the function should return 0. Kate cannot use all three tickets in only two days.
//

#include <iostream>
#include <unordered_map>
#include "performance.h"

int Solution::solution(int arr[], int n){
	std::unordered_map<int, int> wtf_umap;
	int *single_digit_distinguish = new int[n+1];
	int *two_digits_distinguish = new int[n+1];
	single_digit_distinguish[n] = two_digits_distinguish[n] = 0;

	std::unordered_map<int, int>::iterator got;
	for (int i = n-1; i >= 0; i--){
		got = wtf_umap.find(arr[i]);
		single_digit_distinguish[i] = single_digit_distinguish[i+1];
		if (got == wtf_umap.end()) {
			single_digit_distinguish[i] += 1;
		}
		
		two_digits_distinguish[i] = single_digit_distinguish[i+1] + two_digits_distinguish[i+1];
		if (got != wtf_umap.end()){
			two_digits_distinguish[i] -= single_digit_distinguish[got->second+1];
		}
	//if (got == wtf_umap.end()){
	//	two_digits_distinguish[i] = single_digit_distinguish[i+1] + two_digits_distinguish[i+1];
	//}
	//else {
	//	two_digits_distinguish[i] = single_digit_distinguish[i+1]-single_digit_distinguish[got->second] + two_digits_distinguish[i+1]
	//}
		wtf_umap[arr[i]] = i;
	}

	wtf_umap.clear();
	int ret = 0;
	for(int i = 0; i < n; i++){
		got = wtf_umap.find(arr[i]);
		if (got == wtf_umap.end()) {
			ret = ret + two_digits_distinguish[i+1];
		}
		wtf_umap[arr[i]] = i;
	}
//std::cout<<"single: ";
//for (int i = 0; i < n+1; ++i) {
//	std::cout<<single_digit_distinguish[i]<<' ';
//}
//std::cout<<"\ntwo   : ";
//for (int i = 0; i < n+1; ++i) {
//	std::cout<<two_digits_distinguish[i]<<' ';
//}
//std::cout<<std::endl;
	delete[] single_digit_distinguish;
	delete[] two_digits_distinguish;
	return ret;
}


int Solution::solution2(int arr[], int n, int nNum) {
	std::unordered_map<int, int> wtf_umap;
	int **digit = new int*[nNum];
	for(int i = 0; i < nNum; ++i){
		digit[i] = new int[n+1];
		digit[i][0] = 0;
	}
	std::unordered_map<int, int>::iterator got;
	for(int i = 1; i < n+1; ++i) {
		got = wtf_umap.find(arr[i-1]);

		digit[0][i] = digit[0][i-1];
		if(got == wtf_umap.end()){
			digit[0][i]++;
		}
		for(int j = 1; j < nNum; ++j) {
			digit[j][i] = digit[j][i-1] + digit[j-1][i-1];
			if(got != wtf_umap.end()){
				digit[j][i] -= digit[j-1][got->second];
			}
		}
		wtf_umap[arr[i-1]] = i-1;
	}

//for(int i = 0; i < nNum; i++){
//	std::cout<<"digit :"<<i<<std::endl;
//	for(int j = 0; j < n+1; j++){
//		std::cout<<digit[i][j]<<' ';
//	}
//	std::cout<<std::endl;
//}
	int ret = digit[nNum-1][n];


	for(int i = 0; i < nNum; ++i){
		delete[] digit[i];
	}
	delete[] digit;
	return ret;
}
