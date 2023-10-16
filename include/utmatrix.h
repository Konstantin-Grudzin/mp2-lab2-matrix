// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);// конструктор копирования
    ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(TVector &v);     // сложение
  TVector  operator-(TVector &v);     // вычитание
  ValType  operator*(TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.StartIndex+v.Size; i++)
      in >> v[i];
    return in;
  }
  friend ostream& operator<<(ostream &out,TVector &v)
  {
    for (int i = 0; i < v.StartIndex + v.Size; i++)
      out << v[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si):Size(s), StartIndex(si)
{
    if (s <= 0 || s>MAX_VECTOR_SIZE)
        throw "Incorrect size";
    if (si < 0)
        throw "You cannot start at negative index!";
    pVector = new ValType[s]();
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v) 
{
  Size = v.Size;
  StartIndex = v.StartIndex;
  pVector = new ValType[Size];
  std::copy(v.pVector, v.pVector + v.Size, pVector);  
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos) 
{
    ValType x = ValType();

    if (pos < 0 || pos>=MAX_VECTOR_SIZE)
        throw "Wrong position";
    if (pos < StartIndex)
        return x;

    if (pos - StartIndex < Size)
        return pVector[pos - StartIndex];
    else
        return x;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    TVector<ValType> B(*this);
    TVector<ValType> C(v);
    //Реализация рассчитана на то, что в значимых элементах тоже могут быть нули
    if (B.StartIndex + B.Size != C.StartIndex + C.Size)
        return 0;
    

    for (int i = std::min(StartIndex, v.StartIndex); i < std::min(StartIndex, v.StartIndex)+std::max(Size, v.Size); ++i)
    {
        if (B[i] != C[i])
            return 0;
    }
    return 1;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (*this == v)
        return *this;

    if (Size != v.Size)
    {
        ValType* Tmp = new ValType[v.Size];
        delete[] pVector;
        pVector = Tmp;
    }

    Size = v.Size;
    StartIndex = v.StartIndex;
    std::copy(v.pVector, v.pVector + v.Size, pVector);
} /*-------------------------------------------------------------------------*/




template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector<ValType> A(Size+StartIndex);
    for (int i = 0; i < A.Size; ++i)
    {
        ValType x = (*this)[i] + val;
        A[i] = x;
    }
    return A;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector<ValType> A(Size + StartIndex);
    for (int i = 0; i < A.Size; ++i)
    {
        A[i] = (*this)[i] - val;
    }
    return A;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector<ValType> A(Size , StartIndex);
    for (int i = 0; i < A.Size; ++i)
    {
        A[i] = (*this)[i] * val;
    }
    return A;
} /*-------------------------------------------------------------------------*/



template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(TVector<ValType> &v) 
{
    TVector <ValType> B(std::max(v.Size, Size), std::min(v.StartIndex, StartIndex));
    //TVector <ValType> B(v);
    for (int i = 0; i < std::min(v.StartIndex, StartIndex)+std::max(v.Size, Size); ++i)
    {
        
        ValType x = (*this)[i] + v[i];
        B[i] =  x;
        
    }
    //cout << B << endl;
    return B;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(TVector<ValType> &v)
{
    TVector <ValType> B(std::max(v.Size, Size), std::min(v.StartIndex, StartIndex));
    //TVector <ValType> B(v);
    for (int i = 0; i < std::min(v.StartIndex, StartIndex) + std::max(v.Size, Size); ++i)
    {

        ValType x = (*this)[i] - v[i];
        B[i] = x;

    }
    //cout << B << endl;
    return B;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(TVector<ValType> &v)
{
    ValType ans=ValType();

    for (int i = std::min(v.StartIndex, StartIndex); i < std::max(v.Size, Size); ++i)
    {
        ValType x = (*this)[i] * v[i];
        ans = ans + x;
    }
    return ans;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+  (TMatrix &mt);        // сложение
  TMatrix  operator- (TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }

};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType>>(s)
{
    if(s> MAX_MATRIX_SIZE)
        throw "Too Large Matrix";
    for (int i = 0; i < Size; ++i)
    {
        TVector<ValType> x(Size - i, i);
        pVector[i] = x;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):TVector<TVector<ValType>>(mt) 
{
    for (int i = 0; i < Size; ++i)
    {
        pVector[i] = mt.pVector[i];
    }
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>> &mt):TVector<TVector<ValType>>(mt) 
{
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    for (int i = 0; i < Size; ++i)
    {
        if (pVector[i] != mt.pVector[i])
            return 0;
    }
    return 1;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (*this == mt)
        return *this;

    if (Size != mt.Size)
    {
        TVector<ValType>* Tmp  = new TVector<ValType>[mt.Size];
        delete[] pVector;
        pVector = Tmp;
    }

    Size = mt.Size;
    std::copy(mt.pVector, mt.pVector + mt.Size, pVector);
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(TMatrix<ValType> &mt)
{
    
    TMatrix<ValType> A(std::max(Size, mt.Size));
    for (int i = 0; i < max(Size, mt.Size); ++i)
    {
        TVector<ValType> tmp;
        if (i >= mt.Size)
            tmp = (*this)[i];
        else if (i >= Size)
            tmp = mt[i];
        else
            tmp = (*this)[i] + mt[i];
        A[i] = tmp;
    }
    return A;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(TMatrix<ValType> &mt)
{
    TMatrix<ValType> A(std::max(Size, mt.Size));
    for (int i = 0; i < max(Size, mt.Size); ++i)
    {
        TVector<ValType> tmp;
        if (i >= mt.Size)
            tmp = (*this)[i];
        else if (i >= Size)
            tmp =   mt[i]*(-1);
        else
            tmp = (*this)[i] - mt[i];
        A[i] = tmp;
    }
    return A;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
