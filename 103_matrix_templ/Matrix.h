#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;
 public:
  Matrix():numRows(0),numColumns(0){};
  Matrix(int r, int c);
  Matrix(const Matrix<T> & rhs);
  Matrix<T> & operator=(const Matrix<T> & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);

template<typename T>
Matrix<T>::Matrix(int r, int c):numRows(r), numColumns(c),rows(r) {
  for(int i = 0;i < r; i++){
    std::vector<T> row(c);
    rows[i] = row;
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs)  {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
}


template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  if(!(this == &rhs)){
    rows =rhs.rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;

  }
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;

}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(0 <= index && index < numRows);
  return rows[index];

}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index){
  assert(0 <= index && index < numRows);
  return rows[index];
}


template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns){
    return false;
  }
  for(int i = 0; i < numRows; i++){
    if(rows[i] != rhs.rows[i]){
      return false;
      }
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix<T> ans(numRows,numColumns);
  for(int i = 0; i < ans.numRows; i++){
    for(int j = 0; j < ans.numColumns;j++){
      ans.rows[i][j] = rows[i][j] + rhs.rows[i][j];
    }
  }
  return ans;  
}



template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for(int i = 0; i < rhs.getRows();i++){
    s << "{";
    for(int j = 0; j < rhs.getColumns();j++){
      s << rhs[i][j];
      if(j !=rhs.getColumns()-1){
	s<<", ";
      }
    }
    s << "}";
    if( i != rhs.getRows()-1){
    s <<",\n";
    }
  }
  s << " ]";
  return s;
}


#endif
