#ifndef CONTEXT_HH
#define CONTEXT_HH

class Context
{
public:
	virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual void SetClearColor(float r, float g, float b, float a = 1.0f) = 0;
};

#endif // INPUT_LAYOUT_HH