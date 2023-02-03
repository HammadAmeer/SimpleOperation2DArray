#include <iostream>
#include <fstream>
using namespace std;
// creating an array by extracting no. of rows and columns from file and inserting data in array
float **create_arr(ifstream &in,int *&cols,int &rows) {
	rows = 0;		//rows initail with zero
	in >> rows;			//extraxt first line of file (file's first line contain no. of rows)
	float** new_arr = new float* [rows];	// dynamically initail rows to new_arr
		
		cols = new int[rows];		//create array for columns of each line in file
		int column = 0;					
		int i = 0;
		if (in.is_open()) {
			while (!in.eof()) {
				in >> column;		//each first number indicates the no. of column of that line or rows
				new_arr[i] = new float[column];			//dynamically assign memory of columns to rows
				
				// storing data in each rows one by one.
				for (int j = 0;j < column;j++) {
					in>>new_arr[i][j];
				}
				cols[i] = column;	// storing cols for each rows for future use
				i++;
			}
		}	
		return new_arr;
}
// calculating the sum of rows of each column
float* sum_of_rows(float** arr, int rows, int* cols) {
	int *max_index = new int [rows+1];

	for (int i = 0;i < rows;i++) {
		if (cols[i] > max_index[0])
			max_index[0] = cols[i];
		max_index[i + 1] = cols[i];
	}
	float* sumRows = new float[max_index[0]]{};
	for (int i = 0;i < max_index[0];i++) {
		for (int j = 0;j < rows;j++) {
			if(max_index[j+1]!=0)
			sumRows[i] += arr[j][i];
		}
		for (int i = 1;i < rows;i++) {
			if (max_index[i] != 0)
				max_index[i]--;
		}
	}
	return sumRows;
}
// calculating the sum of column of each rows
float* sum_of_cols(float** arr, int rows, int* cols) {
	
	float* sumCols = new float[rows] {};
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < cols[i];j++) {
			sumCols[i] += arr[i][j];
		}
	}
	return sumCols;
}
// calculating the sum diagnally
float* sum_of_diagonal(float** arr, int rows, int* cols) {

	int max_index = 0;
	for (int i = 0;i < rows;i++) {
		if (cols[i] > max_index)
			max_index = cols[i];
	}
	float* sumDiagonal = new float[2] {};
	if (max_index == rows) {
		for (int i = 0;i < rows;i++) {
			for (int j = 0;j < rows;j++) {
				if (i == j)
					sumDiagonal[0] += arr[i][j];
				if ((i + j) == rows - 1)
					sumDiagonal[1] += arr[i][j];
			}
		}
	}
	if (sumDiagonal[0]==0 &&sumDiagonal[0]==0)
		return 0;
	else
	return sumDiagonal;
}

int main() {
	ifstream input;
	input.open("Text.txt");
	float** jagged_arr;
	int rows, *cols;

	jagged_arr = create_arr(input,cols,rows);
	cout << "\t\t\t-------------------------------------------------------"<<endl;
	cout << "\t\t\t\tInformation Extract From File In Array Is:" << endl;
	cout << "\t\t\t-------------------------------------------------------" << endl;
	for (int i = 0;i < rows;i++) {
		cout << "\t\t\t\t";	
		for (int j = 0;j < cols[i];j++)
			cout << jagged_arr[i][j] << "\t";
		cout << endl;
	}
	cout << "\t\t\t-------------------------------------------------------" << endl;

	float* sum_rows;
	sum_rows = sum_of_rows(jagged_arr, rows, cols);
	cout << "\t\t\t-------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tSum of each Rows Is:" << endl;
	cout << "\t\t\t-------------------------------------------------------" << endl;
	for (int i = 0;i < rows;i++) {
		cout << "\t\t\t\t\t";
		cout <<"Row "<<i+1<<" : " << sum_rows[i] << endl;
	}
	cout << "\t\t\t-------------------------------------------------------" << endl;

	delete[]sum_rows;
	
	int max_index = 0;
	for (int i = 0;i < rows;i++) {
			max_index = cols[i];
	}
	float* sum_cols;
	sum_cols = sum_of_cols(jagged_arr, rows, cols);
	cout << "\t\t\t-------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tSum of each Column Is:" << endl;
	cout << "\t\t\t-------------------------------------------------------" << endl;
	for (int i = 0;i < max_index;i++) {
		cout << "\t\t\t\t\t";
		cout << "Column " << i+1 << " : " << sum_cols[i] << endl;
	}
	cout << "\t\t\t-------------------------------------------------------" << endl;
	
	delete[]sum_cols;

	float* sum_diagonal;
	sum_diagonal = sum_of_diagonal(jagged_arr, rows, cols);
	cout << "\t\t\t-------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tSum of each Column Is:" << endl;
	cout << "\t\t\t-------------------------------------------------------" << endl;
	if (sum_diagonal != 0) {
		for (int i = 0;i < 2;i++) {
			if (sum_diagonal[i] >= 0) {
				cout << "\t\t\t\t\t";
				cout << "Diagonal " << i + 1 << " : " << sum_diagonal[i] << endl;
			}
			else
				cout << "\t\t\t\t\t" << "Diagonal" << i + 1 << " : Not Possible" << endl;

		}
	}
	else {
		cout << "\t\t\t\t\tSum Diagonal Wise: Not Possible" << endl;
	}
	cout << "\t\t\t-------------------------------------------------------" << endl;

	delete[]sum_diagonal;

	for (int i = 0;i < rows;i++)
		delete[]jagged_arr[i];
	delete[] jagged_arr;

}
