#include "DigitArchType.h"

bool FPoints::Contains(CameraType device)
{
	if (this->DeviceType == device) { return true; }
	else { return false; }
}
