/**
 * Alexander Rodriguez
 * CS3010.03
 * 3/17/2022
 * 
 * Project 1 - Gaussian Elimination with Scaled Partial Pivoting
 * 
 * 
*/

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string>
using namespace std;

void displayMatrix(vector< vector<double> > &matrix);
void displayMatrix(vector<double> &matrix);
void gaussianElim(vector< vector<double> > &matrix);

int main(){
    int numEquations = 0;
    int variable = 0;
    char choice = ' ';
    char* endPointer;
    char equationString[1024];

    //Ask user to read from file or input equations. repeat if invalid
    cout << "Enter 'a' if you would like to type the linear equations in the command line\nor 'b' if you would like to read equations from a file.\n";
    do{
        cin >> choice;
        if(choice != 'a' && choice != 'b'){
            cout << "\nInvalid choice, please try again.\n";
        }
    }while(choice != 'a' && choice != 'b');




    if(choice == 'a'){  //If a user enters equations and solve
        cout << "Please enter the number of linear equations to solve: ";   //Ask user to enter # of equations
        cin >>  numEquations;   //# rows in matrix

        vector<vector<double> > matrix(numEquations, vector<double> (numEquations+1, 0)); //Initialize 2D-vector with numEquation rows and numEquation+1 cols

        cout << "\nInserting " << numEquations << " equations into matrix: (Enter " << numEquations+1 << " coefficients with a space; the last one will represent the b value)\n";

        for (int i = 0; i < numEquations; i++){
            cout << "Equation " << i+1 << ": "; //prompt user to insert all coefficients for row i of matrix
            cin.ignore();
            scanf("%[^\n]s",equationString);

            for(int j = 0; j < numEquations+1; j++){    //use strtod to parse input and assign to appropraite vector indexes.
                if(j == 0){                             //the last column entered is for the b value of the linear equation.
                    matrix[i][j] = strtod(equationString, &endPointer);
                } else {
                    matrix[i][j] = strtod(endPointer, &endPointer);
                }
            }
        }

        //matrix created do Gaussian elim w/ scaled partial pivoting
        gaussianElim(matrix);

    } else {   //If b read equations from file and solve
        int i = 0;
    }

    




    

    return 0;
}

void displayMatrix(vector< vector<double> > &matrix){
    cout << endl;
    for (int i = 0; i < matrix.size(); i++) //rows
    {
        for (int j = 0; j < matrix[i].size(); j++)  //cols
        {
            cout << matrix[i][j] << " ";
        }   
        cout << endl;
    }
    cout << endl;
}

void displayMatrix(vector<int> &matrix){
    for (int i = 0; i < matrix.size(); i++)
    {
        cout << matrix[i] << " ";
    }
    cout << endl;
}

void gaussianElim(vector< vector<double> > &matrix){

    //initialize scale vector to hold largest coefficient in row
    vector<double>scaleVector (matrix.size());
    for(int i = 0; i < matrix.size(); i++){ //for each row in matrix
        for(int j = 0; j < matrix[i].size()-1; j++ ){ //evaluate the abs value of row elements besides the last element and save highest to i index of scale vector
            if(j == 0){ //first number in row, initially assign
                if(matrix[i][j] < 0){   //if neg num
                    scaleVector[i] = (matrix[i][j])*(-1);
                } else {    //if pos num
                    scaleVector[i] = (matrix[i][j]);
                }
            } else {    //evaluate if next numbers have greater abs value. If true swap abs value into scale vector at i
                if(matrix[i][j] < 0){   //if neg num
                    if((matrix[i][j]*(-1)) > scaleVector[i]){
                        scaleVector[i] = (matrix[i][j])*(-1);
                    }
                } else {    //if pos num
                    if(matrix[i][j] > scaleVector[i]){
                        scaleVector[i] = matrix[i][j];
                    }
                }
            }
        }
    }
    //cout << "Scale vector: "; 
    //displayMatrix(scaleVector);

    //initialize index vector to size of # rows in the matrix.
    vector<int>indexVector (matrix.size());
    for(int i = 0; i < matrix.size(); i++){
        indexVector[i] = i+1;
    }
    cout << "Index vector: "; 
    displayMatrix(indexVector);

    //displayMatrix(matrix);

    //ALGORITHM
    for(int i = 0; i < indexVector.size()-1; i++){
        int scaledRatioIndex = 0;

        cout << "[" << i << "] before: ";
        displayMatrix(indexVector);
        cout << endl;

        vector<double>scaledRatioVector (matrix.size()-i, 0);  //initialize vector for scaled ratios to be compared size rows-i
        for(int j = 0; j < scaledRatioVector.size(); j++){  //for each element of the scale vector length


            if(matrix[indexVector[j]-1][i] < 0){
                scaledRatioVector[j] = ( (matrix[ indexVector[j]-1 ][i])*(-1) / scaleVector[indexVector[j]-1] );
            } else {
                scaledRatioVector[j] = ( matrix[ indexVector[j]-1 ][i] / scaleVector[indexVector[j]-1] );
            }
            
            cout << "scaled ratio " << j+1 << ": " << scaledRatioVector[j] << "\t";

            if(j == 0){
                continue;
            } else {
                if(scaledRatioVector[j] > scaledRatioVector[j-1]){
                    scaledRatioIndex = j;
                }
            }
        }

        int temp = indexVector[i];
        indexVector[i] = indexVector[scaledRatioIndex];
        indexVector[scaledRatioIndex] = temp;

        cout << "[" << i << "] after: ";
        displayMatrix(indexVector);
        cout << endl;
    }
}