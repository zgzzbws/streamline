#include "Field2D.h"

VectorField2D::VectorField2D():m_nRows(0), m_nCols(0){}

VectorField2D::~VectorField2D(){}

void VectorField2D::clear()
{
	m_nRows = m_nCols = 0;
	m_minVal = m_maxVal = Vector2(0,0);
	m_data.clear();
}

bool VectorField2D::readFile( const char* fileName )
{
	ifstream file(fileName);
	if (!file)
		return false;

	clear();

	int ithRow = 0;
	while (true)
	{
		string line;
		file >> line;
		if (!file)
		{
			break;
		}

		stringstream ss;
		ss << line;

		int ithCol = 0;
		while (true)
		{
			char comma0, comma1;
			double x,y;
			ss >> x >> comma0 >> y >> comma1;
			if (!ss)break;

			++ithCol;
			m_data.push_back(Vector2(x,y));
		}

		if (m_nCols == 0)
		{
			m_nCols = ithCol;
		}
		else if (m_nCols != ithCol)
		{
			clear();
			return false;
		}
		++ithRow;
	}
	m_nRows = ithRow;
	computeBound();
	return true;
}

bool VectorField2D::writeFile( const char* fileName )
{
	ofstream file(fileName);
	if (!file)
		return false;

	for (int ithRow = 0, i = 0; ithRow < m_nRows; ++ithRow)
	{
		for (int ithCol = 0; ithCol < m_nCols; ++ithCol, ++i)
		{
			Vector2& v = m_data[i];
			file << v.x << ',' << v.y << ',';

		}
		file << endl;
	}
	file.close();
	return true;
}

//The following three setTo functions are used to test the case;
//set all the data to the same value;
bool VectorField2D::setToConstant( const Vector2& v, int nRows, int nCols )
{
	if (nRows <= 0 || nCols <= 0)
		return false;

	m_nRows = nRows;
	m_nCols = nCols;
	m_data.resize(m_nRows * m_nCols);
	for (int i = 0; i < m_nCols*m_nRows; ++i)
	{
		m_data[i] = v;
	}
	computeBound();
	return true;
}

//set the data radiate from the center
bool VectorField2D::setToRadical(int nRows, int nCols)
{
	if (nRows <= 0 || nCols <= 0)
		return false;

	m_nRows = nRows;
	m_nCols = nCols;
	m_data.resize(m_nRows * m_nCols);
	int center[2] = {nCols / 2, nRows/2};
	for (int y = 0, i = 0; y < m_nRows; y++)
	{
		for (int x = 0; x < m_nCols; x++, i++)
		{
			Vector2 v(x-center[0], y-center[1]);
			m_data[i] = v.normalized();
		}
	}
	computeBound();
	return true;
}

//set the data central symmetry
bool VectorField2D::setToCircular(int nRows, int nCols)
{
	if (nRows <= 0 || nCols <= 0)
		return false;

	m_nRows = nRows;
	m_nCols = nCols;
	m_data.resize(m_nRows * m_nCols);
	int center[2] = {nCols / 2, nRows/2};
	for (int y = 0, i = 0; y < m_nRows; y++)
	{
		for (int x = 0; x < m_nCols; x++, i++)
		{
			Vector2 v(x-center[0], y-center[1]);
			v.normalize();
			m_data[i] = Vector2(-v.y, v.x);
		}
	}
	computeBound();
	return true;
}

//retrieve the data values
bool VectorField2D::getValue( const Vector2& pnt , Vector2& dir)const
{
	double row = pnt.y;
	double col = pnt.x;
	if (row < 0 || row >= m_nRows-1 || col < 0 || col >= m_nCols-1)
		return false;
	int rowi = row, coli = col;
	double rowf = row - rowi, colf = col - coli;
	const Vector2& v00 = getCell(rowi, coli);
	const Vector2& v01 = getCell(rowi, coli+1);
	const Vector2& v10 = getCell(rowi+1, coli);
	const Vector2& v11 = getCell(rowi+1, coli+1);

	if (isInvalid(v00) || isInvalid(v01) || isInvalid(v10) || isInvalid(v11))
	{
		return false;
	}

	//bilinear intepolation
	Vector2 v0  = v00 * (1-colf) + v01 * colf;
	Vector2 v1  = v10 * (1-colf) + v11 * colf;

	dir = v0 * (1-rowf) + v1 * rowf;
	return true;
}

const vector<RGB> VectorField2D::getImage() const
{
    vector<RGB> image;
	if (m_nCols <= 0 || m_nRows <= 0)
	{
		return image;
	}

	for (int ithRow = 0, i = 0; ithRow < m_nRows; ++ithRow)
	{
		for (int ithCol = 0; ithCol < m_nCols; ++ithCol,++i)
		{
			const Vector2& v = m_data[i];
			int r = 0, g = 0, b = 0;
			if (!isInvalid(v))
			{
				//I assume that there is a function to
				//transfer the m_data to r,g,b
				r = v.x/v.length()*255;
				g = v.y/v.length()*255;
				b = v.x/v.length()*255;
			}
			image.push_back( RGB( r, g, b ) );
		}
	}
	return image;
}

bool VectorField2D::getLengthField( vector<double>& field ) const
{
	if (m_nRows <= 0 || m_nCols <= 0)
		return false;

	field.resize(m_nRows * m_nCols);
	for (int y = 0, i = 0; y < m_nRows; y++)
	{
		for (int x = 0; x < m_nCols; x++, i++)
		{
			const Vector2& cell = getCell(y, x);
			double length = isInvalid(cell) ? INVALID_VALUE : cell.length();
			field[i] = length;
		}
	}
	return true;
}

void VectorField2D::computeBound()
{
	double min[2] = {DBL_MAX, DBL_MAX};
	double max[2] = {-DBL_MAX, -DBL_MAX};

	for (int ithRow = 0, i = 0; ithRow < m_nRows; ++ithRow)
	{
		for (int ithCol = 0; ithCol < m_nCols; ++ithCol, ++i)
		{
			Vector2& v = m_data[i];
			if (v.x == INVALID_VALUE || v.y == INVALID_VALUE)
				continue;
			min[0] = min[0] < v.x ? min[0] : v.x;
			min[1] = min[1] < v.y ? min[1] : v.y;
			max[0] = max[0] > v.x ? max[0] : v.x;
			max[1] = max[1] > v.y ? max[1] : v.y;
		}
	}
	m_minVal = Vector2(min[0], min[1]);
	m_maxVal = Vector2(max[0], max[1]);
}
