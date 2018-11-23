#pragma once
struct ShaderFloat
{
	float _value;
	ShaderFloat(float f)
	{
		_value = f;
	}

	ShaderFloat operator= (const float& f)
	{
		return ShaderFloat(f);
	}
};