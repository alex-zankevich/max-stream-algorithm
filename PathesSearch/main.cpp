#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

int n, in_n, out_n;
int** mtrx;
int* in_arr;
int* out_arr;
bool* used;
int* deg;

int* d;
int* p;

int count = 0;

std::queue<int> que;

void remove_way(int f,int t){
	mtrx[f][t]++;
	mtrx[t][f]--;
}

void clear_path(int f, int t){
	if (!used[t]){
		return;
	}
	else{
		for (int v = t; p[v] != -1; v = p[v]){
			remove_way(v,p[v]);
		}
	}
}

void make_path(int start, int end){
	for (int i = 0; i < n; i++){
		d[i] = 0;
		p[i] = 0;
		used[i] = false;
	}
	while (!que.empty()){
		que.pop();
	}
	que.push(start);
	used[start] = true;
	p[start] = -1;

	while (!que.empty()){
		int v = que.front();
		que.pop();
		for (int i = 0; i < n; i++){
			if (mtrx[v][i]){
				int to = i;
				if (!used[to]){
					used[to] = true;
					que.push(to);
					d[to] = d[v] + 1;
					p[to] = v;
					if (to == end){
						clear_path(start,end);
						return;
					}
				}
			}
		}
	}
}

void max_path(int start, int end){
	do{
		make_path(start, end);
	} while (used[end] && ++count);
}

int main(int** argv, int argc){

	std::ifstream in("input.in");
	std::ofstream out("output.out");

	in >> n;
	in >> in_n;
	in >> out_n;

	d = new int[n];
	p = new int[n];

	mtrx = new int*[n];
	for (int i = 0; i < n; i++){
		mtrx[i] = new int[n];
	}

	deg = new int[n];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			in >> mtrx[i][j];
			if (mtrx[i][j] == 1){
				deg[i]++;
			}
		}
	}

	in_arr = new int[in_n];
	out_arr = new int[out_n];

	for (int i = 0; i < in_n; i++){
		in >> in_arr[i] ;
		in_arr[i]--;
	}
	for (int i = 0; i < out_n; i++){
		in >> out_arr[i];
		out_arr[i]--;
	}

	used = new bool[n];
	for (int i = 0; i < n; i++){
		used[i] = false;
	}
	for (int i = 0; i < in_n; i++){
		for (int j = 0; j < out_n; j++){
			max_path(in_arr[i], out_arr[j]);
		}
	}
	
	out << count;

	return 0;
}