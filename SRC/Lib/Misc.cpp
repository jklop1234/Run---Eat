//求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求//
//	Convert Moving Direction to 8-way
//求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求求//
float AngleConvert(float fAngle)
{
	/*
	0    - 22.5		=>	0
	22.5 - 67.5		=>	45
	67.5 - 112.5	=>	90
	112.5- 157.5	=>	135
	157.5- 202.5	=>	180
	202.5- 247.5	=>	225
	247.5- 292.5	=>	270
	292.5- 337.5	=>	315
	337.5- 359		=>	0
	*/
	if (fAngle < 22.5)
	{
		return	0.0f;
	}
	else if (fAngle < 67.5)
	{
		return	45.0f;
	}
	else if (fAngle < 112.5)
	{
		return	90.0f;
	}
	else if (fAngle < 157.5)
	{
		return	135.0f;
	}
	else if (fAngle < 202.5)
	{
		return	180.0f;
	}
	else if (fAngle < 247.5)
	{
		return	225.0f;
	}
	else if (fAngle < 292.5)
	{
		return	270.0f;
	}
	else if (fAngle < 337.5)
	{
		return	315.0f;
	}
	else
	{
		return	0.0;
	}
}