#pragma once

class Datum
{
	enum class DatumType
	{
		Unknown = -1,
		Integer = 0,
		Float,
		Vector,
		Matrix,
		Table,
		String,
		Pointer
	};

public:

	Datum();
	Datum(const Datum& rhs);
	Datum(const Datum&& rhs);
	~Datum();

	Datum& operator=(const Datum& rhs);
	Datum operator=(const Datum&& rhs);
};