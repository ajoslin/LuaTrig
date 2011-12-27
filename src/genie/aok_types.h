#ifndef AOK_TYPES_H_
#define AOK_TYPES_H_

/**
 	AOKPT AND AOKRECT taken from: AOK Trigger Studio

	DiGiT: AOK points are y,x apparently (or at least the way I'm seeing them).
*/
class AOKPT
{
public:
	long y, x;

	AOKPT(long yy = -1, long xx = -1)
		: y(yy), x(xx)
	{
	}
};

class AOKRECT
{
public:
	AOKPT ll;
	AOKPT ur;
	AOKRECT(long ll_y=-1, long ll_x=-1, long ur_y=-1, long ur_x=-1)
		: ll(ll_y, ll_x), ur(ur_y, ur_y)
	{
	}
};

#endif