#ifndef HJ_COLOR_H_
#define HJ_COLOR_H_

#include <algorithm>
#include <cassert>

// all is in [0..1] range
template <typename T, typename T1, typename T2>
void hsv2rgb(const T1 &hsv, T2 &rgb)
{
	int i;
	T f, p, q, t, h0 = hsv[0];
	if(fabs(hsv[1]) < 1e-8) { // achromatic (grey)		
		rgb[0] = rgb[1] = rgb[2] = hsv[2];
		return;
	}
	h0 *= 6;
	h0 -= 6*floor(h0/6);
	i = static_cast<int>(floor(h0));
	assert(i >= 0 && i <= 5);
	f = h0 - i;			// factorial part of hsv[0]
	p = hsv[2] * (1-hsv[1]);
	q = hsv[2] * (1-hsv[1]*f);
	t = hsv[2] * (1-hsv[1]*(1-f));
	switch(i) {
	case 0:
		rgb[0] = hsv[2]; rgb[1] = t; rgb[2] = p; break;
	case 1:
		rgb[0] = q; rgb[1] = hsv[2]; rgb[2] = p; break;
	case 2:
		rgb[0] = p; rgb[1] = hsv[2]; rgb[2] = t; break;
	case 3:
		rgb[0] = p; rgb[1] = q; rgb[2] = hsv[2]; break;
	case 4:
		rgb[0] = t; rgb[1] = p; rgb[2] = hsv[2]; break;
	default: // case 5:
		rgb[0] = hsv[2]; rgb[1] = p; rgb[2] = q;
		break;
	}
}

#endif
