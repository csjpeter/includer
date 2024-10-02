/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

class IInputStream
{
	public:

	virtual ~IInputStream()	      = default;
	virtual bool hasNext() const  = 0;
	virtual char readChar() const = 0;
};
