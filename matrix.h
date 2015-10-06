#ifndef MATRIX_H
#define MATRIX_H
#include<initializer_list>
#include<stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstdlib>
template <typename T> class GeneralSlowMatrix
{
	public:
		
		//GeneralSlowMatrix(unsigned int row, unsigned int col,...);//variable input contructor->not implementable
		GeneralSlowMatrix();//default contructor
		~GeneralSlowMatrix();//destructor
		GeneralSlowMatrix(const unsigned int row, const unsigned int col, const T a[], const unsigned long long length);//array input contructor
		GeneralSlowMatrix(const unsigned int row, const unsigned int col, const std::initializer_list<T> il);//initializer list contructor
		GeneralSlowMatrix(const unsigned int row, const unsigned int col);//determined dimension default contructor
		GeneralSlowMatrix(const GeneralSlowMatrix&);//copy contructor
		GeneralSlowMatrix& operator=(const GeneralSlowMatrix&);//copy assignment

	class Proxy//auxiliary class for implementing double subscripting operator [][]
		{
			public:
				Proxy(T* input):mm(input){}
				T& operator[](const unsigned int col){return mm[col];}
				T operator[](const unsigned int col) const {return mm[col];}
			private:
				T* mm;
		};


		Proxy operator[](const unsigned int row){return Proxy(m[row]);}
		Proxy operator[](const unsigned int row) const {return Proxy(m[row]);}

		T  operator()(const unsigned int row, const unsigned int col) const {return m[row][col];}
		T& operator()(const unsigned int row, const unsigned int col) {return m[row][col];}

		unsigned int getRow() const {return row;}//need to be "const"
		unsigned int getCol() const {return col;}

		bool operator==(const GeneralSlowMatrix&);
		GeneralSlowMatrix operator+(const GeneralSlowMatrix&) const;
		GeneralSlowMatrix operator-(const GeneralSlowMatrix&) const;
		GeneralSlowMatrix operator*(const GeneralSlowMatrix&) const;
		GeneralSlowMatrix operator*(const int&) const;
		GeneralSlowMatrix operator*(const long&) const;
		GeneralSlowMatrix operator*(const float&) const;
		GeneralSlowMatrix operator*(const double&) const;
		//GeneralSlowMatrix operator/(const GeneralSlowMatrix&) const;
		GeneralSlowMatrix Transpose() const;
		GeneralSlowMatrix Inverse() const;
		T Determinant() const;
		GeneralSlowMatrix Adjoint() const;

	protected:
		unsigned int row,col;
		T** m;
		GeneralSlowMatrix Minor(const unsigned int row, const unsigned int col) const;
		GeneralSlowMatrix Cofactor() const;

};

template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrixZero(const unsigned int row, const unsigned int col);
template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrixIdentity(const unsigned int row, const unsigned int col);
template <typename T> bool GeneralSlowMatrixIsIdentity(const GeneralSlowMatrix<T>&);


template <typename T> GeneralSlowMatrix<T>::GeneralSlowMatrix()
{
	row=0;
	col=0;
	m=0;
}

template <typename T> GeneralSlowMatrix<T>::~GeneralSlowMatrix()
{
	for(unsigned int i=0;i<row;++i)
		delete []m[i];

	delete []m;
	row=0;
	col=0;
}
template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrixZero(const unsigned int r, const unsigned int c)
{

	GeneralSlowMatrix<T> M(r,c);
	return M;
}

template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrixIdentity(const unsigned int r, const unsigned int c)
{
	GeneralSlowMatrix<T> M(r,c);

	
	for(unsigned int i=0;i<r;++i)
		M[i][i]=1;

	return M;
}
template <typename T> bool GeneralSlowMatrixIsIdentity(const GeneralSlowMatrix<T>& M)
{
	auto row=M.getRow();
	auto col=M.getCol();
	for(unsigned int i=0;i<row;++i)
	{
		for(unsigned int j=0;j<col;++j)
		{
			if(j==i && M[i][j]!=1)
				return false;
			else if(j!=i && M[i][j]!=0)
				return false;
		}
	}
	return true;
}
template <typename T> GeneralSlowMatrix<T>::GeneralSlowMatrix(const unsigned int r, const unsigned int c)
{
	row=0;
	col=0;
	m=0;
	if(r>1073741823||c>1073741823)
		throw std::runtime_error("The matrix does not support dimension larger than 1073741823!");
	row=r;
	col=c;
	m=new T*[row];

	for(unsigned int i=0;i<row;++i)
		m[i]=new T[col];

	for(unsigned int i=0;i<r;++i)
	{
		for(unsigned int j=0;j<c;++j)
				m[i][j]=0;
	}
}

template <typename T> GeneralSlowMatrix<T>::GeneralSlowMatrix(const unsigned int r, const unsigned int c, const T a[], const unsigned long long length)
{
	row=r;
	col=c;
	if(row>1073741823||col>1073741823||length>288230376151711743)//seems never ">" since it will overflow first-->test this!
		throw std::runtime_error("The matrix does not support dimension larger than 1073741823!");
	//else?
	m=new T*[row];
	for(unsigned int i=0;i<row;++i)
		m[i]=new T[col];

	
	for(unsigned int i=0;i<row;++i)
	{
		for(unsigned int j=0;j<col;++j)
		{
			if(i*col+j+1>length)//current element in the matrix has exceeded the number of input array.
				m[i][j]=0;
			else
				m[i][j]=a[i*col+j];
		}
	}
}

template <typename T> GeneralSlowMatrix<T>::GeneralSlowMatrix(const unsigned int r, const unsigned int c, const std::initializer_list<T> il)
{
	if(r>1073741823||c>1073741823)
		throw std::runtime_error("The matrix does not support dimension larger than 1073741823!");
	row=r;
	col=c;
	m=new T*[row];
	for(unsigned int i=0;i<row;++i)
		m[i]=new T[col];
	unsigned long long counter=0;
	auto iter=il.begin();
	for(unsigned int i=0;i<row;++i)
	{
		for(unsigned int j=0;j<col;++j)
		{
			if(counter==288230376151711743)
				throw std::runtime_error("The number of matrix elements exceeds the class limit:288230376151711743!");
			else
			{
				counter++;
				if(counter>il.size())//if the number of input is not enough, use 0 for the rest of matrix
					m[i][j]=0;
				else
					m[i][j]=*iter++;
			}
		}
	}
}

template <typename T> GeneralSlowMatrix<T>::GeneralSlowMatrix(const GeneralSlowMatrix& rhs)
{
	row=rhs.getRow();
	col=rhs.getCol();

	m=new T*[row];
	for(unsigned int i=0;i<row;++i)
		m[i]=new T[col];

	for(unsigned int i=0;i<row;++i)
	{
		for(unsigned int j=0;j<col;++j)
			//m[i][j]=rhs[i][j];
			m[i][j]=rhs(i,j);
	}

}
template <typename T> GeneralSlowMatrix<T>& GeneralSlowMatrix<T>::operator=(const GeneralSlowMatrix& rhs)
{
	this->~GeneralSlowMatrix();//release previous probably different dimension matrix memory
	row=rhs.getRow();
	col=rhs.getCol();

	m=new T*[row];
	for(unsigned int i=0;i<row;++i)
		m[i]=new T[col];

	for(unsigned int i=0;i<row;++i)
	{
		for(unsigned int j=0;j<col;++j)
			m[i][j]=rhs[i][j];
	}
}



template <typename T> bool GeneralSlowMatrix<T>::operator==(const GeneralSlowMatrix& rhs)
{
	if(row==rhs.getRow()&&col==rhs.getCol())
	{
		for(unsigned int i=0;i<row;++i)
		{
			for(unsigned int j=0;j<col;++j)
				if(m[i][j]!=rhs(i,j)) return false;
		}
		return true;
	}
	else
	return false;
}
template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrix<T>::operator+(const GeneralSlowMatrix& rhs) const
{
	if(row==rhs.getRow()&&col==rhs.getCol())
	{
		GeneralSlowMatrix ret(*this);
		for(unsigned int i=0;i<row;++i)
		{
			for(unsigned int j=0;j<col;++j)
				ret(i,j)=m[i][j]+rhs(i,j);
		}
		return ret;
	}
	else
		throw std::runtime_error("The two matrices have different dimensions!");
}

template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrix<T>::operator-(const GeneralSlowMatrix& rhs) const
{
	if(row==rhs.getRow()&&col==rhs.getCol())
	{
		GeneralSlowMatrix ret(*this);
		for(unsigned int i=0;i<row;++i)
		{
			for(unsigned int j=0;j<col;++j)
				ret(i,j)=m[i][j]-rhs(i,j);
		}
		return ret;
	}
	else
		throw std::runtime_error("The two matrices have different dimensions!");
}


template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrix<T>::operator*(const GeneralSlowMatrix& rhs) const
{
	if(col==rhs.getRow())
	{
		GeneralSlowMatrix ret(row,rhs.getCol());

		for(unsigned int i=0;i<row;++i)
		{
			for(unsigned int j=0;j<rhs.getCol();++j)
			{
				ret(i,j)=0;
				for(unsigned int k=0;k<col;++k)//k<col or k<rhs.getRow() the same
					ret(i,j)+=m[i][k]*rhs(k,j);
			}
		}
		return ret;
	}
	else
		throw std::runtime_error("Matrix is singlar!");
}



template <typename T> GeneralSlowMatrix<T>	GeneralSlowMatrix<T>::operator*(const int& scaler) const
{
		GeneralSlowMatrix ret(*this);
		for(unsigned int i=0;i<row;++i)
		{
			for(unsigned int j=0;j<col;++j)
				ret(i,j)*=scaler;
		}
		return ret;	
}

template <typename T> GeneralSlowMatrix<T>	GeneralSlowMatrix<T>::operator*(const long& scaler) const
{
		GeneralSlowMatrix ret(*this);
		for(unsigned int i=0;i<row;++i)
		{
			for(unsigned int j=0;j<col;++j)
				ret(i,j)*=scaler;
		}
		return ret;	
}

template <typename T> GeneralSlowMatrix<T>	GeneralSlowMatrix<T>::operator*(const float& scaler) const
{
		GeneralSlowMatrix ret(*this);
		for(unsigned int i=0;i<row;++i)
		{
			for(unsigned int j=0;j<col;++j)
				ret(i,j)*=scaler;
		}
		return ret;	
}

template <typename T> GeneralSlowMatrix<T>	GeneralSlowMatrix<T>::operator*(const double& scaler) const
{
		GeneralSlowMatrix ret(*this);
		for(unsigned int i=0;i<row;++i)
		{
			for(unsigned int j=0;j<col;++j)
				ret(i,j)*=scaler;
		}
		return ret;	
}



template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrix<T>::Minor(const unsigned int r, const unsigned int c) const
{
	if(row!=col)
		throw std::runtime_error("non-square matrix has no minor!");

	GeneralSlowMatrix ret(row-1,col-1);
	unsigned int row_counter=0,col_counter=0;
	for(unsigned int i=0;i<row;++i)
	{
		if(i!=r)
		{
			for(unsigned int j=0;j<col;++j)
			{
				if(j!=c)
				{
					ret(row_counter,col_counter)=m[i][j];
					col_counter++;
				}
			}
			col_counter=0;//don't forget clear col_counter, or you will get malloc() memory corruption
			row_counter++;
		}
	}

	return ret;
}


template <typename T> T GeneralSlowMatrix<T>::Determinant() const
{
	if(row!=col)
		throw std::runtime_error("non-square matrix has no determinant!");

	if(row==1)
		return m[0][0];
	else
		{
			T ret=0;
			for(unsigned int j=0;j<col;++j)
				ret+=m[0][j]*static_cast<T>(pow(-1,j))*(this->Minor(0,j)).Determinant();
			return ret;
		}
}

template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrix<T>::Transpose() const
{
	GeneralSlowMatrix ret(col,row);
	for(unsigned int i=0;i<row;++i)
	{
			for(unsigned int j=0;j<col;++j)
					ret(j,i)=m[i][j];
	}
	return ret;
}

template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrix<T>::Cofactor() const
{
	if(row!=col)
		throw std::runtime_error("non-square matrix has no cofactor matrix!");

	GeneralSlowMatrix ret(row,col);
	for(unsigned int i=0;i<row;++i)
	{
		for(unsigned int j=0;j<col;++j)
			ret(i,j)=static_cast<T>(pow(-1,i+j))*(this->Minor(i,j)).Determinant();
	}
	return ret;
}


template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrix<T>::Adjoint() const
{
	return GeneralSlowMatrix((this->Cofactor()).Transpose());
}

template <typename T> GeneralSlowMatrix<T> GeneralSlowMatrix<T>::Inverse() const
{
	return GeneralSlowMatrix(1.0/static_cast<double>(this->Determinant())*this->Adjoint());
}













template <typename T> GeneralSlowMatrix<T>	operator*(const int& scaler,const GeneralSlowMatrix<T>& m){return m*scaler;}
template <typename T> GeneralSlowMatrix<T>	operator*(const long& scaler,const GeneralSlowMatrix<T>& m){return m*scaler;}
template <typename T> GeneralSlowMatrix<T>	operator*(const float& scaler,const GeneralSlowMatrix<T>& m){return m*scaler;}
template <typename T> GeneralSlowMatrix<T>	operator*(const double& scaler,const GeneralSlowMatrix<T>& m){return m*scaler;}

template <typename T> std::ostream& operator<<(std::ostream& os, GeneralSlowMatrix<T> m)
{

	std::vector<unsigned int> maxcol;
	for(unsigned int i=0;i<m.getCol();++i)//for column alignment
	{
		unsigned int max_col_alignment=0;
		for(unsigned int j=0;j<m.getRow();++j)
		{
			std::stringstream ss;
			ss<<m[j][i];
			std::string str;
			ss>>str;
			if(str.size()>max_col_alignment)
				max_col_alignment=str.size();
		}
		maxcol.push_back(max_col_alignment);
	}

	for(unsigned int i=0;i<m.getRow();++i)
	{
		os<<"| ";
		for(unsigned int j=0;j<m.getCol();++j)
		{
			os<<std::right<<std::setw(maxcol[j])<<m[i][j]<<" ";
		}
		os<<" |"<<std::endl;
	}

	return os;
}


#endif

/*
template <typename T> SlowGenrealMatrix<T>::GeneralSlowMatrix(unsigned int row, unsigned int col, ...)
{
	va_list va;
	va_start(va,col);

	va_arg(va,T);


	va_end(va);
}*/
